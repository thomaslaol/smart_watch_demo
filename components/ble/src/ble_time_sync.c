#include "ble_time_sync.h"
// #include "mrtc.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_device.h"
#include "esp_bt_defs.h"
#include "esp_gatt_defs.h"

/**=========================================================================================== */
/**                                     DEFIN                                                  */
/**=========================================================================================== */
// 蓝牙模式（仅启用 BLE）
#define BLE_MODE ESP_BT_MODE_BLE
// 自定义服务 UUID（16位）
#define TIME_SERVICE_UUID 0x1805
// 时间特征 UUID（16位，用于读写时间戳）
#define TIME_CHARACTERISTIC_UUID 0x2A2B

/**=========================================================================================== */
/**                                     DATA                                                   */
/**=========================================================================================== */
// 全局变量
static uint16_t s_time_char_handle = 0;            // 时间特征句柄
static esp_gatt_if_t s_gatt_if = ESP_GATT_IF_NONE; // GATT接口
static bool s_is_connected = false;                // 连接状态标志
static esp_ble_adv_params_t adv_params;            // 广播参数（用于断开后重启广播）
// 日志标签
static const char *TAG = "BLE_TIME_SYNC";

/**=========================================================================================== */
/**                                     FUNCTION                                               */
/**=========================================================================================== */
static esp_err_t nvs_init(void);
static esp_err_t bt_controller_init(void);
static esp_err_t bluedroid_init(void);
static void timezone_init(void);
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
static void ble_adv_config(const char *device_name);

/**=========================================================================================== */
/**                                     PUBLIC                                                 */
/**=========================================================================================== */
/**
 * @brief 蓝牙初始化入口函数
 *
 * @note 初始化顺序：NVS -> 时区 -> 蓝牙控制器 -> Bluedroid -> GAP 回调 -> GATT 回调 -> GATT 应用 -> 广播配置
 *
 * @param device_name 设备名称
 * @return ESP_OK 成功，其他失败
 */
esp_err_t ble_time_sync_init(const char *device_name)
{
    esp_err_t ret;

    // 初始化 NVS
    ret = nvs_init();
    if (ret != ESP_OK)
    {
        return ret;
    }

    // 初始化时区
    timezone_init();

    // 初始化蓝牙控制器
    ret = bt_controller_init();
    if (ret != ESP_OK)
    {
        return ret;
    }

    // 初始化 Bluedroid 协议栈
    ret = bluedroid_init();
    if (ret != ESP_OK)
    {
        return ret;
    }

    // 注册 GAP 回调
    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "注册 GAP 回调失败: %d", ret);
        return ret;
    }

    // 注册 GATT 回调
    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "注册 GATT 回调失败: %d", ret);
        return ret;
    }

    // 注册 GATT 应用
    ret = esp_ble_gatts_app_register(0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "注册 GATT 应用失败: %d", ret);
        return ret;
    }

    // 配置并启动广播
    ble_adv_config(device_name);

    ESP_LOGI(TAG, "蓝牙时间同步服务初始化完成");
    return ESP_OK;
}
/**
 * 获取当前连接状态
 */
bool ble_is_connected(void)
{
    return s_is_connected;
}

/**=========================================================================================== */
/**                                     STATIC                                                 */
/**=========================================================================================== */

/**
 * GATT 事件回调（处理服务/特征、连接、数据收发）
 */
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                esp_ble_gatts_cb_param_t *param)
{
    switch (event)
    {
    case ESP_GATTS_REG_EVT:
        // GATT 应用注册完成，创建时间同步服务
        s_gatt_if = gatts_if;
        ESP_LOGI(TAG, "GATT 应用注册成功，接口: %d", gatts_if);

        // 配置服务 UUID（适配 esp_bt_uuid_t 无 type 字段）
        esp_gatt_srvc_id_t service_id = {
            .is_primary = true,
            .id = {
                .uuid = {
                    .len = ESP_UUID_LEN_16,               // 16位 UUID
                    .uuid = {.uuid16 = TIME_SERVICE_UUID} // 服务 UUID 值
                },
                .inst_id = 0 // 实例 ID，默认0
            }};
        // 创建服务（需要4个句柄）
        esp_ble_gatts_create_service(gatts_if, &service_id, 4);
        break;

    case ESP_GATTS_CREATE_EVT:
        // 服务创建完成，添加时间特征
        ESP_LOGI(TAG, "时间同步服务创建完成，句柄: %d", param->create.service_handle);

        // 配置特征属性（可读写）
        esp_gatt_char_prop_t prop = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ;

        // 特征 UUID（适配 esp_bt_uuid_t 无 type 字段）
        esp_bt_uuid_t char_uuid = {
            .len = ESP_UUID_LEN_16,                      // 16位 UUID
            .uuid = {.uuid16 = TIME_CHARACTERISTIC_UUID} // 特征 UUID 值
        };

        // 特征初始值（适配 esp_attr_value_t 字段）
        uint8_t initial_time[8] = {0};
        esp_attr_value_t char_val = {
            .attr_max_len = 8,         // 最大长度8字节
            .attr_len = 8,             // 当前长度8字节
            .attr_value = initial_time // 初始值指针
        };

        // 添加特征到服务
        esp_ble_gatts_add_char(
            param->create.service_handle,
            &char_uuid,
            ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
            prop,
            &char_val,
            NULL);
        break;

    case ESP_GATTS_ADD_CHAR_EVT:
        // 特征添加完成，启动服务
        s_time_char_handle = param->add_char.attr_handle;
        ESP_LOGI(TAG, "时间特征添加完成，句柄: %d", s_time_char_handle);
        esp_ble_gatts_start_service(param->add_char.service_handle);
        break;

    case ESP_GATTS_CONNECT_EVT:
        // 设备连接成功
        s_is_connected = true;
        ESP_LOGI(TAG, "设备已连接，conn_id: %d，地址: " ESP_BD_ADDR_STR,
                 param->connect.conn_id, ESP_BD_ADDR_HEX(param->connect.remote_bda));
        break;

    case ESP_GATTS_DISCONNECT_EVT:
        // 设备断开连接，重启广播
        s_is_connected = false;
        ESP_LOGI(TAG, "设备已断开，conn_id: %d，原因: %d",
                 param->disconnect.conn_id, param->disconnect.reason);
        esp_ble_gap_start_advertising(&adv_params);
        break;

    case ESP_GATTS_WRITE_EVT:
        // 处理时间特征写入（接收时间戳）
        if (param->write.handle == s_time_char_handle)
        {
            // 验证数据长度（必须是8字节，64位时间戳）
            if (param->write.len != 4 && param->write.len != 8)
            {
                ESP_LOGE(TAG, "时间戳格式错误，需4或8字节，实际接收: %d字节", param->write.len);
                break;
            }

            // 解析时间戳（处理32位/64位）
            int64_t unix_timestamp = 0;
            if (param->write.len == 4)
            {
                // 32位时间戳（如1754815647）
                uint32_t ts32;
                memcpy(&ts32, param->write.value, 4);
                unix_timestamp = ts32; // 自动转换为64位
            }
            else
            {
                // 64位时间戳
                memcpy(&unix_timestamp, param->write.value, 8);
            }

            printf("接收到的Unix时间戳: %lld\n", unix_timestamp);

            // 初始化时间
            // mrtc_set_time(unix_timestamp);
            struct timeval val = {.tv_sec = (time_t)unix_timestamp, .tv_usec = 0};
            settimeofday(&val, NULL);

            // // 回复写入确认
            esp_ble_gatts_send_response(
                gatts_if,
                param->write.conn_id,
                param->write.trans_id,
                ESP_GATT_OK,
                NULL);
        }
        break;

    default:
        break;
    }
}

/**
 * 初始化 NVS（蓝牙依赖）
 */
static esp_err_t nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_LOGW(TAG, "NVS 分区需要擦除，正在处理...");
        ret = nvs_flash_erase();
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "NVS 擦除失败: %d", ret);
            return ret;
        }
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "NVS 初始化失败: %d", ret);
    }
    else
    {
        ESP_LOGI(TAG, "NVS 初始化成功");
    }
    return ret;
}

/**
 * 初始化蓝牙控制器（硬件层）
 */
static esp_err_t bt_controller_init(void)
{
    // 释放经典蓝牙内存（仅保留 BLE）
    esp_err_t ret = esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "释放经典蓝牙内存失败: %d", ret);
        return ret;
    }

    // 配置蓝牙控制器（默认参数）
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "蓝牙控制器初始化失败: %d", ret);
        return ret;
    }

    // 启用 BLE 模式
    ret = esp_bt_controller_enable(BLE_MODE);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "启用 BLE 模式失败: %d", ret);
        return ret;
    }

    ESP_LOGI(TAG, "蓝牙控制器初始化成功（仅启用 BLE 4.2）");
    return ESP_OK;
}

/**
 * 初始化 Bluedroid 协议栈（适配蓝牙 4.2）
 */
static esp_err_t bluedroid_init(void)
{
    esp_bluedroid_config_t bluedroid_config = {
        .ssp_en = false // 禁用经典蓝牙的安全简单配对（因仅使用 BLE）
    };

    // 初始化 Bluedroid
    esp_err_t ret = esp_bluedroid_init_with_cfg(&bluedroid_config);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Bluedroid 初始化失败: %d", ret);
        return ret;
    }

    // 启用协议栈
    ret = esp_bluedroid_enable();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "启用 Bluedroid 失败: %d", ret);
        esp_bluedroid_deinit();
        return ret;
    }

    ESP_LOGI(TAG, "Bluedroid 协议栈（蓝牙 4.2）初始化成功");
    return ret;
}

/**
 * 初始化时区（北京时间 UTC+8）
 */
static void timezone_init(void)
{
    setenv("TZ", "CST-8", 1); // 设置时区为北京时间
    tzset();                  // 应用时区设置
    ESP_LOGI(TAG, "时区已设置为北京时间（UTC+8）");
}

/**
 * GAP 事件回调（处理广播相关事件）
 */
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event)
    {
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        // 广播启动结果
        if (param->adv_start_cmpl.status == ESP_BT_STATUS_SUCCESS)
        {
            ESP_LOGI(TAG, "BLE 广播已启动");
        }
        else
        {
            ESP_LOGE(TAG, "广播启动失败，状态: %d", param->adv_start_cmpl.status);
        }
        break;

    default:
        break;
    }
}

/**
 * 配置并启动广播
 */
static void ble_adv_config(const char *device_name)
{
    // 设置设备名称
    esp_err_t ret = esp_bt_dev_set_device_name(device_name);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "设置设备名称失败: %d", ret);
        return;
    }

    // 配置广播数据
    esp_ble_adv_data_t adv_data = {
        .include_name = true,
        .include_txpower = false,
        .flag = ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT};
    ret = esp_ble_gap_config_adv_data(&adv_data);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "配置广播数据失败: %d", ret);
        return;
    }

    // 配置广播参数（保存到全局变量，用于断开后重启）
    adv_params.adv_int_min = 0x20;
    adv_params.adv_int_max = 0x40;
    adv_params.adv_type = ADV_TYPE_IND;
    adv_params.own_addr_type = BLE_ADDR_TYPE_PUBLIC;
    adv_params.channel_map = ADV_CHNL_ALL;
    adv_params.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY;

    // 启动广播
    ret = esp_ble_gap_start_advertising(&adv_params);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "启动广播失败: %d", ret);
    }
    else
    {
        ESP_LOGI(TAG, "广播已启动，设备名称: %s", device_name);
    }
}
