#include "mpu6050_api.h"
#include "iic_bus.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

/**=========================================================================================== */
/**                                     DEFINE                                                 */
/**=========================================================================================== */
#define PRINT_ACCEL (0x01)
#define PRINT_GYRO (0x02)
#define PRINT_QUAT (0x04)
#define ACCEL_ON (0x01)
#define GYRO_ON (0x02)
#define MOTION (0)
#define NO_MOTION (1)
#define DEFAULT_MPU_HZ (100)
#define FLASH_SIZE (512)
#define FLASH_MEM_START ((void *)0x1800)

/**=========================================================================================== */
/**                                     DATA                                                   */
/**=========================================================================================== */
struct rx_s
{
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s
{
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};

static struct hal_s hal;
volatile unsigned char rx_new;

static TaskHandle_t mpu6050_task_handle = NULL;
static i2c_port_t mpu6050_i2c_port = I2C_NUM_0;
static const char *TAG = "mpu6050";
mpu6050_step_t g_mpu6050_step;
/**=========================================================================================== */
/**                                     FUNCTION                                               */
/**=========================================================================================== */
static signed char gyro_orientation[9] = {-1, 0, 0, 0, -1, 0, 0, 0, 1};
static inline unsigned short inv_row_2_scale(const signed char *row);
static inline unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);
void system_reset(void);
void gyro_data_ready_cb(void);
static int mpu6050_check_whoami(void);
static inline int run_self_test(void);
static int mpu6050_get_step(void);
static void mpu6050_task(void *pvParameters);

/**=========================================================================================== */
/**                                     PUBILIC                                                */
/**=========================================================================================== */
/**
 * @brief mpu6050初始化
 *
 * 自动检测I2C总线是否已初始化，如果没有则初始化
 * 初始化成功后，将自动启动DMP固件，并设置采样率为100Hz，加速度计量程为±2g，加速度计高通滤波（5Hz截止）
 * 自动启动任务，每1秒更新一次步数，并存放在s_mpu6050_data中
 *
 * 检测是初始化iic总线->初始化mpu6050-启动DMP固件-设置采样率-设置加速度计量程-设置加速度计高通滤波-启动任务
 *
 * @param  无
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t mpu6050_init(void)
{
    // 初始化iic
    esp_err_t err;
    int result;

    esp_log_level_set(TAG, ESP_LOG_WARN);

    // 确保I2C总线已初始化
    if (i2c_is_inited(mpu6050_i2c_port) == false)
    {
        err = i2c_bus_init(mpu6050_i2c_port, GPIO_NUM_7, GPIO_NUM_8, 100000);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C总线初始化失败: %d", err);
            return err;
        }
    }

    mpu6050_check_whoami();

    result = mpu_init();
    if (result != 0)
    {
        ESP_LOGE(TAG, "mpu_init 初始化失败: %d", result);
        return result;
    }

    ESP_LOGI(TAG, "mpu_init 初始化成功");

    result = mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    if (result != 0)
    {
        ESP_LOGE(TAG, "mpu_set_sensors 设置传感器失败");
        return result;
    }

    result = mpu_set_accel_fsr(2); // 2表示±2g，可选值：2/4/8/16
    if (result != 0)
    {
        ESP_LOGE(TAG, "设置加速度计量程失败");
    }
    else
    {
        ESP_LOGI(TAG, "加速度计量程已设置为±2g");
    }

    // 正确设置加速度计高通滤波（修正参数传递）
    uint8_t hpf_data = 0x01; // 要写入寄存器的数据（5Hz截止频率）
    if (i2c_bus_write_bytes(mpu6050_i2c_port, 0x68, 0x1D, &hpf_data, 1) != ESP_OK)
    {
        ESP_LOGE(TAG, "设置加速度计高通滤波失败");
    }
    else
    {
        ESP_LOGI(TAG, "加速度计高通滤波已启用（5Hz截止）");
    }

    result = mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    if (result != 0)
    {
        ESP_LOGE(TAG, "mpu_configure_fifo 设置FIFO失败");
        return result;
    }

    result = mpu_set_sample_rate(100);
    if (result != 0)
    {
        ESP_LOGE(TAG, "mpu_set_sample_rate 设置采样率失败");
        return result;
    }

    result = dmp_load_motion_driver_firmware();
    if (result != 0)
    {
        ESP_LOGE(TAG, "dmp_load_motion_driver_firmware 加载固件失败");
        return result;
    }

    result = dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
    if (result != 0)
    {
        ESP_LOGE(TAG, "dmp_set_orientation 设置方向失败");
        return result;
    }

    result = dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
                                DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL |
                                DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL |
                                DMP_FEATURE_PEDOMETER);
    if (result != 0)
    {
        ESP_LOGE(TAG, "dmp_enable_feature 启用功能失败");
        return result;
    }

    result = dmp_set_fifo_rate(100);
    if (result != 0)
    {
        ESP_LOGE(TAG, "dmp_set_fifo_rate 设置FIFO速率失败");
        return result;
    }

    // 自检
    result = run_self_test();
    if (result != 0)
    {
        ESP_LOGE(TAG, "自检失败");
        return result;
    }

    result = mpu_set_dmp_state(1);
    if (result != 0)
    {
        ESP_LOGE(TAG, "mpu_set_dmp_state 启用DMP失败");
        return result;
    }

    hal.dmp_on = 1;

    // 延迟一小段时间，确保DMP稳定
    vTaskDelay(pdMS_TO_TICKS(100));

    unsigned char dmp_state;
    if (mpu_get_dmp_state(&dmp_state) == 0)
    {
        ESP_LOGI(TAG, "DMP状态: %s", dmp_state ? "已启动" : "未启动");
    }

    // 新增：重置FIFO
    mpu_reset_fifo();
    ESP_LOGI(TAG, "FIFO已重置");

    // 重置步数（放在DMP启用后）
    result = dmp_set_pedometer_step_count(0);
    if (result != 0)
    {
        ESP_LOGE(TAG, "dmp_set_pedometer_step_count 重置步数失败");
        return result;
    }

    // 启动任务
    BaseType_t xReturned = xTaskCreatePinnedToCore((TaskFunction_t)mpu6050_task, "mpu6050_task", 4096, NULL, 5, &mpu6050_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("mpu6050_task", "Failed to create task");
    }
    ESP_LOGI("mpu6050_task", "Task created");

    return ESP_OK;
}

/**=========================================================================================== */
/**                                     STATIC                                                 */
/**=========================================================================================== */
/**
 * @brief mpu6050任务
 * @param pvParameters
 */
static void mpu6050_task(void *pvParameters)
{
    while (1)
    {
        mpu6050_get_step();
        // printf("步数：%lu\n", count);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static int mpu6050_get_step(void)
{
    // 直接读取计步器当前值（更可靠）
    int result = dmp_get_pedometer_step_count(&g_mpu6050_step.step_count);
    if (result != 0)
    {
        ESP_LOGE(TAG, "dmp_get_pedometer_step_count 读取失败: %d", result);
        return 1;
    }
    ESP_LOGD(TAG, "步数: %lu", g_mpu6050_step.step_count);
    return 0;
}

// /* The sensors can be mounted onto the board in any orientation. The mounting
//  * matrix seen below tells the MPL how to rotate the raw data from thei
//  * driver(s).
//  * TODO: The following matrices refer to the configuration on an internal test
//  * board at Invensense. If needed, please modify the matrices to match the
//  * chip-to-body matrix for your particular set up.
//  */
// static signed char gyro_orientation[9] = {-1, 0, 0,
//                                           0, -1, 0,
//                                           0, 0, 1};

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7; // error
    return b;
}

static inline unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}

// 重启系统
void system_reset(void)
{
    esp_restart();
}

void gyro_data_ready_cb(void)
{
    hal.new_gyro = 1;
}

// 读取MPU6050的WHO_AM_I寄存器（地址0x75，默认值0x68）
static int mpu6050_check_whoami(void)
{
    uint8_t whoami;
    // 使用底层I2C函数直接读取（绕过库，验证硬件通信）
    esp_err_t err = i2c_bus_read_bytes(mpu6050_i2c_port, 0x68, 0x75, &whoami, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "WHO_AM_I读取失败，I2C错误: %d", err);
        return -1;
    }
    if (whoami != 0x68)
    {
        ESP_LOGE(TAG, "WHO_AM_I值异常: 0x%x（预期0x68）", whoami);
        return -2;
    }
    ESP_LOGI(TAG, "WHO_AM_I验证成功: 0x%x", whoami);
    return 0;
}

static inline int run_self_test(void)
{
    int result;
    // char test_packet[4] = {0};
    long gyro[3], accel[3];
    unsigned char i = 0;

#if defined(MPU6500) || defined(MPU9250)
    result = mpu_run_6500_self_test(gyro, accel, 0);
#elif defined(MPU6050) || defined(MPU9150)
    result = mpu_run_self_test(gyro, accel);
    ESP_LOGD(TAG, "MPU6050自检结果: %d", result);
#endif
    if ((result & 0x03) == 0x3)
    {
        ESP_LOGI(TAG, "自检通过");
        // 六轴不是九轴
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        for (i = 0; i < 3; i++)
        {
            gyro[i] = (long)(gyro[i] * 32.8f); // convert to +-1000dps
            accel[i] *= 2048.f;                // convert to +-16G
            accel[i] = accel[i] >> 16;
            gyro[i] = (long)(gyro[i] >> 16);
        }

        result = mpu_set_gyro_bias_reg(gyro);
        if (result != 0)
        {
            ESP_LOGE(TAG, "设置陀螺仪偏置失败: %d", result);
            return result;
        }

#if defined(MPU6500) || defined(MPU9250)
        mpu_set_accel_bias_6500_reg(accel);
#elif defined(MPU6050) || defined(MPU9150)
        result = mpu_set_accel_bias_6050_reg(accel);
        if (result != 0)
        {
            ESP_LOGE(TAG, "设置加速度计偏置失败: %d", result);
            return result;
        }
#endif
    }
    else
    {
        ESP_LOGE(TAG, "自检失败");
        return -1;
    }
    return 0;
}
