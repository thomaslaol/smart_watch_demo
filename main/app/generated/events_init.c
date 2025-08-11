/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void screen_main_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_PRESSED:
    {
        break;
    }
    default:
        break;
    }
}

static void screen_main_canvas_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void screen_main_img_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // printf("img1 Clicked\n");
        // static int crurent = 0;
        // const void *img_src = NULL;

        // if (crurent == 0)
        // {
        //     lv_label_set_text(guider_ui.screen_main_label_cnt, "< 1/3 >");
        //     img_src = &_5555_240x135;
        // }
        // else if (crurent == 1)
        // {
        //     lv_label_set_text(guider_ui.screen_main_label_cnt, "< 2/3 >");
        //     img_src = &_222_240x135;
        // }
        // else
        // {
        //     lv_label_set_text(guider_ui.screen_main_label_cnt, "< 3/3 >");
        //     img_src = &_333_240x135;
        // }

        // crurent++;
        // crurent %= 3;
        // lv_img_set_src(guider_ui.screen_main_img_1, img_src);
        break;
    }
    default:
        break;
    }
}


static void screen_main_carousel_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        // printf("carousel_2 scroll end\n");
        // static int indix_crurent = 0;
        // switch (indix_crurent)
        // {
        // case 0:
        //     break;
        // case 1:
        //     lv_label_set_text(guider_ui.screen_main_label_cnt, "< 2/3 >");
        //     break;
        // case 2:
        //     break;
        // case 3:
        //     lv_label_set_text(guider_ui.screen_main_label_cnt, "< 3/3 >");
        //     break;
        // case 4:
        //     break;
        // case 5:

        //     break;
        // case 6:
        //     break;
        // default:
        //     break;
        // }
        // indix_crurent++;
        // indix_crurent %= 7;

        break;
    }
    default:
        break;
    }
}

void events_init_screen_main(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_main, screen_main_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_main_canvas_2, screen_main_canvas_2_event_handler, LV_EVENT_ALL, ui);

    lv_obj_add_event_cb(ui->screen_main_carousel_2, screen_main_carousel_2_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{
}
