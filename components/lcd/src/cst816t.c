#include "cst816t.h"
#include "lcd_common.h"

#include "iic_bus.h"
#include "driver/gpio.h"

static i2c_port_t cst816t_i2c_port = I2C_NUM_1;
static const char *TAG = "CST816T";
static QueueHandle_t touch_queue;

// 手势名称映射
static const char *gesture_names[] = {
    "无", "上滑", "下滑", "左滑", "右滑",
    "单击", "未知", "未知", "未知", "未知",
    "未知", "双击", "长按"};

// 读寄存器
static esp_err_t cst816t_read_reg(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(cst816t_i2c_port, CST816T_ADDR, &reg_addr, 1,
                                       data, len, 1000 / portTICK_PERIOD_MS);
}

// 写寄存器
static esp_err_t cst816t_write_reg(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};
    return i2c_master_write_to_device(cst816t_i2c_port, CST816T_ADDR, write_buf,
                                     sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
}

// 中断处理函数
static void IRAM_ATTR cst816t_isr_handler(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t gpio_num = (uint32_t)arg;
    
    if (uxQueueMessagesWaitingFromISR(touch_queue) < 10) {
        xQueueSendFromISR(touch_queue, &gpio_num, &xHigherPriorityTaskWoken);
    }
    
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

// 注册中断
static esp_err_t cst816t_register_isr(void)
{
    if (touch_queue) vQueueDelete(touch_queue);
    touch_queue = xQueueCreate(10, sizeof(uint32_t));
    if (!touch_queue) {
        ESP_LOGE(TAG, "创建触摸队列失败");
        return ESP_FAIL;
    }

    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "安装中断服务失败: %d", err);
        return err;
    }

    gpio_isr_handler_remove(CST816T_INT_PIN);
    err = gpio_isr_handler_add(CST816T_INT_PIN, cst816t_isr_handler, (void *)CST816T_INT_PIN);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "添加中断处理函数失败: %d", err);
        return err;
    }

    ESP_LOGI(TAG, "中断注册成功");
    return ESP_OK;
}

// 初始化
esp_err_t cst816t_init(void)
{
    esp_err_t ret;
    uint8_t chip_id;

    if (i2c_is_inited(cst816t_i2c_port) == false)
    {
        int err = i2c_bus_init(cst816t_i2c_port, CST816T_SDA_PIN, CST816T_SCL_PIN, 50000);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "I2C初始化失败");
            return err;
        }
    }

    // 引脚配置
    gpio_config_t rst_config = {
        .pin_bit_mask = (1ULL << CST816T_RST_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&rst_config);
    
    gpio_config_t int_config = {
        .pin_bit_mask = (1ULL << CST816T_INT_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_ANYEDGE
    };
    gpio_config(&int_config);

    // 复位流程
    gpio_set_level(CST816T_RST_PIN, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(CST816T_RST_PIN, 1);
    vTaskDelay(300 / portTICK_PERIOD_MS);

    // 验证芯片ID
    ret = cst816t_read_reg(CST816T_CHIP_ID, &chip_id, 1);
    if (ret != ESP_OK || chip_id != 0xB5) {
        ESP_LOGE(TAG, "芯片ID验证失败: 0x%02X", chip_id);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "初始化成功 (ID:0x%02X)", chip_id);

    // 寄存器配置
    cst816t_write_reg(0xFA, 0x71);  // 中断控制
    cst816t_write_reg(0xED, 0x64);  // 中断脉冲宽度
    return ESP_OK;
}

// 读取触摸数据（核心：交换上滑/下滑手势ID）
static esp_err_t cst816t_read_touch_data(cst816t_data_t *data)
{
    uint8_t reg_data[6];
    esp_err_t ret = cst816t_read_reg(CST816T_GESTURE_ID, reg_data, 6);
    if (ret != ESP_OK) return ret;

    // 解析原始数据
    data->gesture = reg_data[0];
    data->touch_num = reg_data[1];
    uint8_t xh = reg_data[2];
    uint8_t xl = reg_data[3];
    uint8_t yh = reg_data[4];
    uint8_t yl = reg_data[5];

    // 计算坐标（X、Y均使用原始值，匹配屏幕逻辑）
    data->x = (int16_t)(((xh & 0x0F) << 8) | xl);
    data->y = (int16_t)(((yh & 0x0F) << 8) | yl);

    // 核心修正：交换上滑（1）和下滑（2）的手势ID
    // 因为Y值增大（从上到下）应识别为下滑，原识别为上滑，故交换
    if (data->gesture == 1) {
        data->gesture = 2;  // 上滑→下滑
    } else if (data->gesture == 2) {
        data->gesture = 1;  // 下滑→上滑
    }

    return ESP_OK;
}

// 触摸处理任务
// 修改触摸处理任务，将数据更新到供LVGL使用的变量
static void cst816t_task(void *arg)
{
    uint32_t io_num;
    cst816t_data_t touch_data_raw;
    uint8_t clear_reg;
    int16_t last_x = -1, last_y = -1;

    // 检查互斥锁是否已经初始化
    if (touch_mutex == NULL) {
        ESP_LOGE(TAG, "触摸互斥锁未初始化");
        vTaskDelete(NULL);
    }

    while (1)
    {
        if (xQueueReceive(touch_queue, &io_num, portMAX_DELAY))
        {
            if (cst816t_read_touch_data(&touch_data_raw) == ESP_OK)
            {
                xSemaphoreTake(touch_mutex, portMAX_DELAY);
                
                // 更新坐标
                touch_data.point.x = touch_data_raw.x;
                touch_data.point.y = touch_data_raw.y;

                // 根据触摸数量更新状态
                if (touch_data_raw.touch_num > 0) {
                    touch_data.state = LV_INDEV_STATE_PR; // 按下状态
                    
                    // 处理手势（如果需要）
                    if (touch_data_raw.gesture == 1) { // 上滑
                        // 可以在这里添加自定义处理
                    } else if (touch_data_raw.gesture == 2) { // 下滑
                        // 可以在这里添加自定义处理
                    }
                } else {
                    touch_data.state = LV_INDEV_STATE_REL; // 释放状态
                }

                xSemaphoreGive(touch_mutex);

                // 打印调试信息
                if (touch_data_raw.touch_num > 0) {
                    // const char *gesture_str = (touch_data_raw.gesture < sizeof(gesture_names)/sizeof(char*)) ?
                    //                          gesture_names[touch_data_raw.gesture] : "无效";
                    // ESP_LOGI(TAG, "触摸: %s (x=%d, y=%d)", gesture_str, touch_data_raw.x, touch_data_raw.y);
                    
                    last_x = touch_data_raw.x;
                    last_y = touch_data_raw.y;
                }
            }
            cst816t_read_reg(0x00, &clear_reg, 1);  // 清除中断
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
}
// static void cst816t_task(void *arg)
// {
//     uint32_t io_num;
//     cst816t_data_t touch_data;
//     uint8_t clear_reg;
//     int16_t last_x = -1, last_y = -1;

//     while (1)
//     {
//         if (xQueueReceive(touch_queue, &io_num, portMAX_DELAY))
//         {
//             if (cst816t_read_touch_data(&touch_data) == ESP_OK && touch_data.touch_num > 0)
//             {
//                 // 过滤微小变化
//                 bool need_print = (touch_data.gesture != 0) ||
//                                  (abs(touch_data.x - last_x) > 5) ||
//                                  (abs(touch_data.y - last_y) > 5);

//                 if (need_print)
//                 {
//                     const char *gesture_str = (touch_data.gesture < sizeof(gesture_names)/sizeof(char*)) ?
//                                              gesture_names[touch_data.gesture] : "无效";
//                     ESP_LOGI(TAG, "触摸: %s (x=%d, y=%d)", gesture_str, touch_data.x, touch_data.y);
                    
//                     last_x = touch_data.x;
//                     last_y = touch_data.y;
//                 }
//             }
//             cst816t_read_reg(0x00, &clear_reg, 1);  // 清除中断
//             vTaskDelay(20 / portTICK_PERIOD_MS);
//         }
//     }
// }

// 启动函数
void cst816t_start_verify(void)
{
    if (cst816t_init() != ESP_OK) return;
    
    if (cst816t_register_isr() != ESP_OK) {
        ESP_LOGE(TAG, "中断注册失败");
        return;
    }
    
    xTaskCreate(cst816t_task, "cst816t_task", 4096, NULL, 5, NULL);
    ESP_LOGI(TAG, "系统启动完成（滑动方向修正）");
}
    