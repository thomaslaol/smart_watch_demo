#ifndef _JFH142_H_
#define _JFH142_H_

#include <stdbool.h>
#include "esp_err.h"

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
#define RX_BUF_SIZE 88     // 接收缓冲区大小
#define RT_PACKET_SIZE 88   // 实时数据包大小
#define TST_PACKET_SIZE 196 // 体检数据包大小

// 指令定义
#define JFH142_CMD_START_COLLECT 0x8A                  // 采集开
#define JFH142_CMD_STOP_COLLECT 0x88                   // 采集关
#define JFH142_CMD_START_TEST {0x84, 0x00, 0x00, 0x8E} // 体检开
#define JFH142_CMD_STOP_TEST 0x8C                      // 体检关
#define JFH142_CMD_SLEEP 0x98                          // 休眠开

// 实时包和体检包常量定义（严格匹配手册）
#define RT_PACKET_MAGIC        0xFF        // 实时包包头
#define RT_PACKET_SIZE         88          // 实时包固定长度
#define TST_PACKET_MAGIC       0xFFFF      // 体检包包头
#define TST_PACKET_SIZE        196         // 体检包固定长度

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


// 健康数据结构体(供应用层使用)
typedef struct
{
    uint8_t heartrate;          // 心率
    uint8_t spo2;               // 血氧
    uint8_t bk;                 // 微循环
    uint8_t fatigue_index;      // 疲劳指数
    uint8_t systolic_pressure;  // 收缩压 (高压)
    uint8_t diastolic_pressure; // 舒张压 （低压）
    bool is_detected;           // 是否检测到人体
} jfh142_health_data_t;



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

esp_err_t jfh142_init(void);

#endif // _JFH142_H_