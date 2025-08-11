/*
 * Copyright 2023 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <math.h>
#include "lvgl.h"
#include "custom.h"
#include "gui_guider.h" // 包含lv_ui结构体定义
#include "qmc5883l.h"

/*********************
 *      DEFINES
 *********************/
// 调整画布参数以容纳更多内容
#define RULER_CANVAS_WIDTH 220 // 直尺画布宽度
#define RULER_CANVAS_HEIGHT 30 // 增加高度以容纳度数、刻度和方向文字
#define RULER_BOTTOM_Y (RULER_CANVAS_HEIGHT - 5)
#define RULER_CENTER_X (RULER_CANVAS_WIDTH / 2)  // 直尺中点X坐标
#define RULER_CENTER_Y (RULER_CANVAS_HEIGHT / 2) // 调整中点Y坐标，使布局更合理
#define RULER_LENGTH 200                         // 有效刻度长度
#define MAX_ANGLE 90                             // 最大显示角度（±180°）
#define ANGLE_STEP 5                             // 刻度间隔（5°，每小格5度）
#define UPDATE_INTERVAL 1000                     // 角度更新间隔（ms）

// 刻度线长度定义
#define SHORT_LINE_LENGTH 10  // 短刻度（5°）
#define MEDIUM_LINE_LENGTH 14 // 中刻度（15°）
#define LONG_LINE_LENGTH 17   // 长刻度（30°）

// 四舍五入到最近的5的倍数
#define ALIGN_TO_5(angle) (((angle) + 2) / 5 * 5)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
// static void draw_ruler_scale(lv_obj_t *canvas, int current_angle);
static void angle_update_timer(lv_timer_t *timer);
static const char *get_direction_text(int angle); // 获取方向汉字

static void custom_task(void *pvParameters);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *ruler_canvas = NULL; // 直尺画布组件指针
static int current_angle = 0;         // 当前角度（0~360°）
// 绘制描述符（适配LVGL的draw_dsc接口）
static lv_draw_line_dsc_t line_dsc;       // 刻度线描述符
static lv_draw_label_dsc_t label_dsc;     // 度数文字描述符
static lv_draw_label_dsc_t dir_label_dsc; // 方向文字描述符
static lv_draw_line_dsc_t midline_dsc;    // 中线描述符

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void custom_init(lv_ui *ui)
{
    /* 获取直尺画布组件 */
    ruler_canvas = ui->screen_main_canvas_direct;

    /* 初始化线条描述符（刻度线） */
    lv_draw_line_dsc_init(&line_dsc);
    line_dsc.width = 1;
    line_dsc.color = lv_color_hex(0xffffff); // 白色刻度线

    /* 初始化度数文字描述符 */
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.font = &lv_font_montserratMedium_12; // 度数字体
    label_dsc.color = lv_color_hex(0xffffff);      // 白色文字（与背景对比）
    label_dsc.align = LV_TEXT_ALIGN_CENTER;        // 文字居中

    /* 初始化方向文字描述符（汉字可能需要更大字体） */
    lv_draw_label_dsc_init(&dir_label_dsc);
    dir_label_dsc.font = &lv_font_sun_14;         // 使用支持汉字的字体
    dir_label_dsc.color = lv_color_hex(0x00FF00); // 绿色方向文字，更醒目
    dir_label_dsc.align = LV_TEXT_ALIGN_CENTER;   // 文字居中

    /* 初始化中线描述符 */
    lv_draw_line_dsc_init(&midline_dsc);
    midline_dsc.width = 2;
    midline_dsc.color = lv_color_hex(0xFF0000); // 红色中线，更粗一些

    // /* 启动角度更新定时器 */
    lv_timer_create(angle_update_timer, UPDATE_INTERVAL, ui);

    // /* 初始绘制一次刻度 */
    draw_ruler_scale(ruler_canvas, current_angle);

    // 创建任务
    //  xTaskCreatePinnedToCore();
    // 创建刷新任务
    // xTaskCreatePinnedToCore((TaskFunction_t)custom_task, "custom_task", 3072, NULL, 5, NULL, 0);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * 根据角度获取方向汉字
 */
static const char *get_direction_text(int angle)
{
    // 归一化角度到0-360°
    angle = angle % 360;
    if (angle < 0)
        angle += 360;

    // 定义方向角度范围
    if ((angle >= 337.5 || angle < 22.5))
        return "北";
    if (angle >= 22.5 && angle < 67.5)
        return "东北";
    if (angle >= 67.5 && angle < 112.5)
        return "东";
    if (angle >= 112.5 && angle < 157.5)
        return "东南";
    if (angle >= 157.5 && angle < 202.5)
        return "南";
    if (angle >= 202.5 && angle < 247.5)
        return "西南";
    if (angle >= 247.5 && angle < 292.5)
        return "西";
    if (angle >= 292.5 && angle < 337.5)
        return "西北";

    return ""; // 默认返回空
}

/**
 * 绘制直尺刻度
 * @param canvas 直尺画布组件
 * @param current_angle 当前角度（0~360°）
 */

// void draw_ruler_scale(lv_obj_t *canvas, int target_angle)
// {
//     if (canvas == NULL)
//         return;

//     // 静态变量保存当前显示的角度（用于动画过渡）
//     static int display_angle = 0;
//     // 动画步长，控制过渡速度（值越小过渡越平滑）
//     const int ANIMATION_STEP = 5;

//     // 1. 计算需要移动的方向和步长，实现平滑过渡
//     if (display_angle != target_angle)
//     {
//         int diff = target_angle - display_angle;
        
//         // 根据角度差决定每次移动的步长和方向
//         if (abs(diff) <= ANIMATION_STEP)
//         {
//             display_angle = target_angle; // 到达目标值
//         }
//         else
//         {
//             // 向目标角度靠近一步（保留方向）
//             display_angle += (diff > 0) ? ANIMATION_STEP : -ANIMATION_STEP;
//         }
//     }

//     // 2. 清除画布（用黑色背景覆盖）
//     lv_canvas_fill_bg(canvas, lv_color_hex(0x000000), LV_OPA_COVER);

//     // 3. 计算刻度起始角度（使用当前显示的角度）
//     int start_angle = display_angle - MAX_ANGLE;

//     // 4. 绘制刻度线、度数和方向
//     for (int angle = start_angle; angle <= start_angle + 2 * MAX_ANGLE; angle += ANGLE_STEP)
//     {
//         // 关键修改：调整X坐标计算方向，使角度变化与视觉移动一致
//         // 角度增加时刻度向左移，角度减少时刻度向右移
//         float ratio = (display_angle - angle) / (float)MAX_ANGLE; // 反转比例计算
//         int x = RULER_CENTER_X + (int)(ratio * (RULER_LENGTH / 2));

//         // 跳过超出画布范围的刻度
//         if (x < 5 || x >= RULER_CANVAS_WIDTH - 5)
//             continue;

//         // 5. 确定刻度线长度（5°短，15°中，30°长）
//         int line_length;
//         if (angle % 30 == 0)
//         {
//             line_length = LONG_LINE_LENGTH; // 30°长刻度
//         }
//         else if (angle % 15 == 0)
//         {
//             line_length = MEDIUM_LINE_LENGTH; // 15°中刻度
//         }
//         else
//         {
//             line_length = SHORT_LINE_LENGTH; // 5°短刻度
//         }

//         // 绘制刻度线
//         lv_point_t line_points[2] = {
//             {x, RULER_CANVAS_HEIGHT - line_length},
//             {x, RULER_BOTTOM_Y}};
//         lv_canvas_draw_line(canvas, line_points, 2, &line_dsc);

//         // 6. 绘制30°整数倍的度数和方向
//         if (angle % 30 == 0)
//         {
//             // 绘制度数（在刻度上方）
//             char text[16] = {0};
//             int show_angle = angle % 360;
//             if (show_angle > 180)
//                 show_angle -= 360; // 转换为±180°显示
//             sprintf(text, "%d", show_angle);

//             lv_canvas_draw_text(canvas,
//                                 x - 15,                               // X坐标（居中显示）
//                                 RULER_CENTER_Y - line_length / 2 - 8, // 刻度上方
//                                 30,                                   // 最大宽度
//                                 &label_dsc,
//                                 text);
//         }
//     }

//     // 7. 如果还没到达目标角度，请求再次绘制以继续动画
//     if (display_angle != target_angle)
//     {
//         lv_obj_invalidate(canvas); // 触发重绘，持续动画
//     }
// }


void draw_ruler_scale(lv_obj_t *canvas, int current_angle)
{
    if (canvas == NULL)
        return;

    // 1. 清除画布（用黑色背景覆盖）
    lv_canvas_fill_bg(canvas, lv_color_hex(0x000000), LV_OPA_COVER);

    // 2. 计算刻度起始角度
    int start_angle = current_angle - MAX_ANGLE;

    // 3. 绘制刻度线、度数和方向
    for (int angle = start_angle; angle <= start_angle + 2 * MAX_ANGLE; angle += ANGLE_STEP)
    {
        // 计算刻度在直尺上的X坐标
        float ratio = (angle - current_angle) / (float)MAX_ANGLE; // -1.0 ~ 1.0
        int x = RULER_CENTER_X + (int)(ratio * (RULER_LENGTH / 2));

        // 跳过超出画布范围的刻度
        if (x < 5 || x >= RULER_CANVAS_WIDTH - 5)
            continue;

        // 4. 确定刻度线长度（5°短，15°中，30°长）
        int line_length;
        if (angle % 30 == 0)
        {
            line_length = LONG_LINE_LENGTH; // 30°长刻度
        }
        else if (angle % 15 == 0)
        {
            line_length = MEDIUM_LINE_LENGTH; // 15°中刻度
        }
        else
        {
            line_length = SHORT_LINE_LENGTH; // 5°短刻度
        }

        // 绘制刻度线
        lv_point_t line_points[2] = {
            {x, RULER_CANVAS_HEIGHT - line_length},
            {x, RULER_BOTTOM_Y}};
        lv_canvas_draw_line(canvas, line_points, 2, &line_dsc);

        // 5. 绘制30°整数倍的度数和方向
        if (angle % 30 == 0)
        {
            // 绘制度数（在刻度上方）
            char text[16] = {0};
            int display_angle = angle % 360;
            if (display_angle > 180)
                display_angle -= 360; // 转换为±180°显示
            sprintf(text, "%d", display_angle);

            lv_canvas_draw_text(canvas,
                                x - 15,                               // X坐标
                                RULER_CENTER_Y - line_length / 2 - 8, // 刻度上方
                                30,                                   // 最大宽度
                                &label_dsc,
                                text);
        }
    }
}

/**
 * 定时器回调：更新角度并重绘刻度
 */
static void angle_update_timer(lv_timer_t *timer)
{
    static int mlast_angle = 0;
    lv_ui *ui = (lv_ui *)timer->user_data;
    if (ui == NULL)
        return;

    // 角度递增（每1000ms增加5°，模拟角度变化）
    // current_angle = (current_angle + 5) % 360;
    if (xSemaphoreTake(g_data_mutex, pdMS_TO_TICKS(800)) == pdTRUE)
    {
        current_angle = (int)g_qmc5883l_data.angle;
        xSemaphoreGive(g_data_mutex);
    }
    current_angle = ALIGN_TO_5(current_angle);
    if (mlast_angle != current_angle)
    {
        // 重绘刻度
        draw_ruler_scale(ruler_canvas, current_angle);
    }
    mlast_angle = current_angle;
}

static void custom_task(void *pvParameters)
{
    // static int mlast_angle = 0;
    // while (1)
    // {
    //     if (xSemaphoreTake(g_data_mutex, pdMS_TO_TICKS(800)) == pdTRUE)
    //     {
    //         current_angle = (int)g_qmc5883l_data.angle;
    //         xSemaphoreGive(g_data_mutex);
    //     }
    //     current_angle = ALIGN_TO_5(current_angle);
    //     if (mlast_angle != current_angle)
    //     {
    //         // 重绘刻度
    //         draw_ruler_scale(ruler_canvas, current_angle);
    //     }
    //     mlast_angle = current_angle;
    //     vTaskDelay(pdMS_TO_TICKS(500));
    // }
}