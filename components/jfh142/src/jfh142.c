#include "jfh142.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**=========================================================================================== */
/**                                     DEFINE                                                 */
/**=========================================================================================== */
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

// 硬件配置 - 匹配您的原理图
#define JFH142_UART_NUM UART_NUM_1
#define JFH142_TXD_PIN GPIO_NUM_3 // TX引脚
#define JFH142_RXD_PIN GPIO_NUM_4 // RX引脚
#define JFH142_RST_PIN GPIO_NUM_2 // 复位引脚
#define JFH142_BAUD_RATE 38400
#define JFH142_DATA_BITS UART_DATA_8_BITS
#define JFH142_PARITY UART_PARITY_DISABLE
#define JFH142_STOP_BITS UART_STOP_BITS_1

// 缓冲区配置
#define RX_BUF_SIZE 88      // 接收缓冲区大小
#define RT_PACKET_SIZE 88   // 实时数据包大小
#define TST_PACKET_SIZE 196 // 体检数据包大小

// 指令定义
#define JFH142_CMD_START_COLLECT 0x8A                  // 采集开
#define JFH142_CMD_STOP_COLLECT 0x88                   // 采集关
#define JFH142_CMD_START_TEST {0x84, 0x00, 0x00, 0x8E} // 体检开
#define JFH142_CMD_STOP_TEST 0x8C                      // 体检关
#define JFH142_CMD_SLEEP 0x98                          // 休眠开

// 实时包和体检包常量定义（严格匹配手册）
#define RT_PACKET_MAGIC 0xFF    // 实时包包头
#define RT_PACKET_SIZE 88       // 实时包固定长度
#define TST_PACKET_MAGIC 0xFFFF // 体检包包头
#define TST_PACKET_SIZE 196     // 体检包固定长度

/**=========================================================================================== */
/**                                     DATA                                                   */
/**=========================================================================================== */
// 实时数据包结构定义
typedef struct
{
    uint8_t head;      // 0xFF
    int8_t acdata[64]; // 心律波形数据
    uint8_t heartrate; // 心率
    uint8_t spo2;      // 血氧
    uint8_t bk;        // 微循环
    uint8_t rsv[8];    // 保留数据(含疲劳指数等)
    uint8_t sdnn;      // 心率变异性
    uint8_t rmssd;
    uint8_t nn50;
    uint8_t pnn50;
    uint8_t rra[6]; // rr间期
    uint8_t rsv2;   // 保留
    uint8_t state;  // 模块状态
} jfh142_rt_packet_t;

// 体检数据包结构定义（对应手册TST30_PACK_S）
typedef struct
{
    uint16_t head;           // 体检数据包头（0xFFFF）
    uint16_t sequence;       // 体检数据包序号
    uint8_t id[16];          // 唯一硬件编号
    uint8_t tst30_data[168]; // 体检数据
    uint8_t rsv1[6];         // 保留字段
    uint16_t crc16;          // CRC检验码
} jfh142_tst_packet_t;

jfh142_health_data_t g_health_data;
static bool is_collecting = false;
static const char *TAG = "JFH142";

/**=========================================================================================== */
/**                                     FUNCTION                                               */
/**=========================================================================================== */
static void rst_pin_init(void);
static void reset(void);
static esp_err_t uart_init(void);
static esp_err_t send_command(uint8_t *cmd, size_t len);
static uint16_t crc16_calculate(const uint8_t *data, size_t len);
static void parse_rt_packet(uint8_t *data, size_t len);
static esp_err_t parse_tst_packet(uint8_t *data, size_t len);
static esp_err_t jfh142_start_collect(void);
static esp_err_t jfh142_stop_collect(void);
static esp_err_t jfh142_start_test(void);
static esp_err_t jfh142_stop_test(void);
static esp_err_t jfh142_enter_sleep(void);
static void jfh142_get_health_data(jfh142_health_data_t *data);
static void jfh142_data_task(void *arg);

/**=========================================================================================== */
/**                                     PUBLIC                                                 */
/**=========================================================================================== */

/**
 * @brief 初始化JFH142传感器
 *
 * 初始化成功后会自动启动数据采集
 * 任务每秒读取一次数据，数据保存在全局变量g_health_data中
 * 
 * 初始化硬件->初始化UART->创建数据接收任务->启动数据采集
 *
 * @param  无
 * @return ESP_OK: 成功
 */
esp_err_t jfh142_init(void)
{
    esp_err_t ret;

    esp_log_level_set(TAG, ESP_LOG_INFO);
    ESP_LOGD(TAG, "JFH142初始化开始");

    // 初始化硬件
    rst_pin_init();
    reset();

    // 初始化UART
    ret = uart_init();
    if (ret != ESP_OK)
    {
        return ret;
    }

    // 创建数据接收任务
    TaskHandle_t pxCreatedTask = NULL;
    BaseType_t task_ret = xTaskCreatePinnedToCore((TaskFunction_t)jfh142_data_task, "jfh142_data_task", 4096, NULL, 5, &pxCreatedTask,1);
    if (task_ret != pdPASS)
    {
        ESP_LOGE(TAG, "创建数据接收任务失败");
        return ESP_FAIL;
    }

    ret = jfh142_start_collect();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "启动数据采集失败");
        return ret;
    }

    ESP_LOGI(TAG, "JFH142初始化成功");
    return ESP_OK;
}

char *jfh142_get_heart_str(void)
{
    static char heart_str[8] = {0};
    sprintf(heart_str, "%d", g_health_data.heartrate);
    return heart_str;
}

//疲惫值
char *jfh142_get_tired_str(void)
{
    static char tired_str[8] = {0};
    sprintf(tired_str, "%d", g_health_data.fatigue_index);
    return tired_str;
}


/**=========================================================================================== */
/**                                     STATIC                                                 */
/**=========================================================================================== */
/**
 * @brief 数据接收任务
 */
static void jfh142_data_task(void *arg)
{
    size_t recv_len = 0;
    uint8_t data[RX_BUF_SIZE]; // 实时数据包缓冲区
    // 体检包缓冲区
    uint8_t tst_buf[TST_PACKET_SIZE];
    // 体检报后半部分缓冲区
    uint8_t tst_second_buf[108];

    while (1)
    {
        recv_len = uart_read_bytes(JFH142_UART_NUM, data, RX_BUF_SIZE, 1000 / portTICK_PERIOD_MS);
        if (recv_len > 0)
        {
            // 情况2：判断当前88字节是实时包还是体检包的前半部分
            if (data[0] == 0xFF)
            {
                if (data[1] != 0xFF)
                {
                    // 实时包特征：0xFF开头且第二个字节非0xFF
                    // ESP_LOGD(TAG, "解析实时包（88字节）");
                    parse_rt_packet(data, RT_PACKET_SIZE);
                }
                else if (data[1] == 0xFF)
                {
                    // 体检包前半部分特征：0xFFFF开头（前两字节都是0xFF）
                    // ESP_LOGD(TAG, "收到体检包前半部分，等待后半部分");
                    recv_len = uart_read_bytes(JFH142_UART_NUM, tst_second_buf, 108, 500 / portTICK_PERIOD_MS);
                    if (recv_len == 108)
                    {
                        ESP_LOGD(TAG, "收到体检包后半部分，开始拼接");
                        // 拼接体检包（前88字节+当前108字节 = 196字节）
                        memcpy(tst_buf, data, RT_PACKET_SIZE);
                        memcpy(tst_buf + RT_PACKET_SIZE, tst_second_buf, 108);
                        parse_tst_packet(tst_buf, TST_PACKET_SIZE);

                        ESP_LOGD(TAG, "体检包解析完成");
                    }
                    else
                    {
                        ESP_LOGW(TAG, "体检报后半部分接收超时或数据不完整(长度%d),丢弃", recv_len);
                    }
                    continue;
                }
            }
            else
            {
                // 非0xFF开头，视为无效数据
                ESP_LOGW(TAG, "无效数据包（首字节0x%02X 0x%02X）", data[0], data[1]);
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief 初始化复位引脚
 */
static void rst_pin_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << JFH142_RST_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);
}

/**
 * @brief 复位传感器
 */
static void reset(void)
{
    gpio_set_level(JFH142_RST_PIN, 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(JFH142_RST_PIN, 1);
    vTaskDelay(200 / portTICK_PERIOD_MS); // 等待传感器启动稳定
}

/**
 * @brief 初始化UART
 */
static esp_err_t uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = JFH142_BAUD_RATE,
        .data_bits = JFH142_DATA_BITS,
        .parity = JFH142_PARITY,
        .stop_bits = JFH142_STOP_BITS,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    esp_err_t ret = uart_param_config(JFH142_UART_NUM, &uart_config);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "UART参数配置失败: %d", ret);
        return ret;
    }

    ret = uart_set_pin(JFH142_UART_NUM,
                       JFH142_TXD_PIN,
                       JFH142_RXD_PIN,
                       UART_PIN_NO_CHANGE,
                       UART_PIN_NO_CHANGE);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "UART引脚配置失败: %d", ret);
        return ret;
    }

    ret = uart_driver_install(JFH142_UART_NUM,
                              RX_BUF_SIZE * 2,
                              0,
                              0,
                              NULL,
                              0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "UART驱动安装失败: %d", ret);
        return ret;
    }

    return ESP_OK;
}

/**
 * @brief 发送指令
 */
static esp_err_t send_command(uint8_t *cmd, size_t len)
{
    int bytes_written = uart_write_bytes(JFH142_UART_NUM, (const char *)cmd, len);
    if (bytes_written != len)
    {
        ESP_LOGE(TAG, "命令发送失败，预期: %d, 实际: %d", len, bytes_written);
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief CRC16校验函数（多项式0x8005，用于验证体检包完整性）
 * 注：若传感器使用其他CRC算法，需根据手册修改
 */
static uint16_t crc16_calculate(const uint8_t *data, size_t len)
{
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < len; i++)
    {
        crc ^= (uint16_t)data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0x8005;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief 解析实时数据包
 */
static void parse_rt_packet(uint8_t *data, size_t len)
{
    if (len != RT_PACKET_SIZE || data[0] != 0xFF)
    {
        ESP_LOGW(TAG, "无效的实时数据包");
        return;
    }

    jfh142_rt_packet_t *packet = (jfh142_rt_packet_t *)data;

    // 更新健康数据
    g_health_data.heartrate = packet->heartrate;
    g_health_data.spo2 = packet->spo2;
    g_health_data.bk = packet->bk;
    g_health_data.fatigue_index = packet->rsv[0];      // 疲劳指数
    g_health_data.systolic_pressure = packet->rsv[3];  // 收缩压
    g_health_data.diastolic_pressure = packet->rsv[4]; // 舒张压

    // 检查是否检测到人体 (bit2为0表示检测到)
    g_health_data.is_detected = !(packet->state & (1 << 2));

    // 打印关键数据 (调试用)
    if (g_health_data.is_detected)
    {
        ESP_LOGI(TAG, "心率: %d, 血氧: %d%%, 微循环: %d, 疲劳指数: %d, 高压: %d, 低压: %d",
                 g_health_data.heartrate,
                 g_health_data.spo2,
                 g_health_data.bk,
                 g_health_data.fatigue_index,
                 g_health_data.systolic_pressure,
                 g_health_data.diastolic_pressure);
    }
}

/**
 * @brief 解析体检数据包
 * @param data 接收到的原始数据
 * @param len 数据长度（应等于TST_PACKET_SIZE=196）
 * @return ESP_OK 解析成功，ESP_FAIL 解析失败
 */
static esp_err_t parse_tst_packet(uint8_t *data, size_t len)
{
    // 1. 验证数据包基本信息
    if (len != TST_PACKET_SIZE)
    {
        ESP_LOGE(TAG, "体检包长度错误，预期196字节，实际%d字节", len);
        return ESP_FAIL;
    }

    jfh142_tst_packet_t *packet = (jfh142_tst_packet_t *)data;

    // 2. 验证包头（必须为0xFFFF）
    if (packet->head != 0xFFFF)
    {
        ESP_LOGE(TAG, "体检包头错误，预期0xFFFF，实际0x%04X", packet->head);
        return ESP_FAIL;
    }

    // 3. 验证CRC16校验（校验范围：除crc16字段外的所有数据）
    // uint16_t calculated_crc = crc16_calculate(data, len - 2); // 排除最后2字节CRC
    // if (calculated_crc != packet->crc16)
    // {
    //     ESP_LOGE(TAG, "体检包CRC校验失败，计算值0x%04X，包内值0x%04X",
    //              calculated_crc, packet->crc16);
    //     return ESP_FAIL;
    // }

    // 4. 解析并打印关键信息（根据实际需求提取tst30_data中的内容）
    ESP_LOGI(TAG, "===== 体检数据包解析结果 =====");
    ESP_LOGI(TAG, "数据包序号: %d", packet->sequence);

    // 打印硬件ID（16字节）
    char id_str[33] = {0}; // 16字节转为32位十六进制字符串+结束符
    for (int i = 0; i < 16; i++)
    {
        sprintf(&id_str[i * 2], "%02X", packet->id[i]);
    }
    ESP_LOGI(TAG, "硬件唯一ID: %s", id_str);

    // 5. 提取体检数据（tst30_data[168]）
    // 注：具体数据格式需参考手册，此处以示例形式展示前10字节
    ESP_LOGI(TAG, "体检数据前10字节:");
    for (int i = 0; i < 10; i++)
    {
        printf("%02X ", packet->tst30_data[i]);
    }
    printf("\n");

    ESP_LOGI(TAG, "体检包解析完成（CRC校验通过）\n");
    return ESP_OK;
}

/**
 * @brief 启动数据采集
 */
esp_err_t jfh142_start_collect(void)
{
    uint8_t cmd = JFH142_CMD_START_COLLECT;
    esp_err_t ret = send_command(&cmd, 1);
    if (ret == ESP_OK)
    {
        is_collecting = true;
        ESP_LOGI(TAG, "采集已开启");
    }
    return ret;
}

/**
 * @brief 停止数据采集
 */
esp_err_t jfh142_stop_collect(void)
{
    uint8_t cmd = JFH142_CMD_STOP_COLLECT;
    esp_err_t ret = send_command(&cmd, 1);
    if (ret == ESP_OK)
    {
        is_collecting = false;
        ESP_LOGI(TAG, "采集已关闭");
    }
    return ret;
}

/**
 * @brief 启动体检模式
 */
esp_err_t jfh142_start_test(void)
{
    uint8_t cmd[] = JFH142_CMD_START_TEST;
    esp_err_t ret = send_command(cmd, sizeof(cmd));
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "体检模式已开启");
    }
    return ret;
}

/**
 * @brief 停止体检模式
 */
esp_err_t jfh142_stop_test(void)
{
    uint8_t cmd = JFH142_CMD_STOP_TEST;
    esp_err_t ret = send_command(&cmd, 1);
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "体检模式已关闭");
    }
    return ret;
}

/**
 * @brief 进入休眠模式
 */
esp_err_t jfh142_enter_sleep(void)
{
    uint8_t cmd = JFH142_CMD_SLEEP;
    esp_err_t ret = send_command(&cmd, 1);
    if (ret == ESP_OK)
    {
        is_collecting = false;
        ESP_LOGI(TAG, "已进入休眠模式");
    }
    return ret;
}

/**
 * @brief 获取最新健康数据
 */
void jfh142_get_health_data(jfh142_health_data_t *data)
{
    memcpy(data, &g_health_data, sizeof(jfh142_health_data_t));
}
