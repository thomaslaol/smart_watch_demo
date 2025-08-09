idf_component_register(
    SRCS
    "main.c"

    "custom/custom.c" # 你的自定义逻辑

    "generated/widgets_init.c" # UI组件初始化
    "generated/events_init.c" # 事件回调
    "generated/gui_guider.c" # UI全局逻辑（若存在）
    "generated/setup_scr_screen_main.c"

    "fonts/lv_font_sun_14.c" # 中文字体
    "fonts/lv_font_sun_16.c"
    "fonts/lv_font_sun_32.c"
    "fonts/lv_font_arial_16.c"
    "fonts/lv_font_montserratMedium_12.c" # 度数字体
    "fonts/lv_font_montserratMedium_16.c"




    "images/_111_240x135.c"
    "images/_222_240x135.c"
    "images/_333_240x135.c"
    "images/_3304542_20230221171348882211_0_58x2.c"
    "images/_3304542_20230221171348882211_0_100x2.c"
    "images/_3304542_20230221171348882211_0_alpha_236x1.c"
    "images/_3304542_20230221171348882211_0_alpha_238x1.c"
    "images/_date_15x15.c"
    "images/_heat_25x25.c"
    "images/_hum_15x14.c"
    # "images/_hum_18x18.c"
    # "images/_icon_wx_alpha_20x20.c"
    "images/_icon_wx_25x25.c"
    # "images/_o2_18x18.c"
    # "images/_pointer_alpha_15x15.c"
    # "images/_pointer1_alpha_15x15.c"
    "images/_pointer2_15x15.c"
    # "images/_pressure_25x25.c"
    "images/_step_20x20.c"
    "images/_temp_15x15.c"
    # "images/_temp_alpha_20x20.c"
    "images/_week_25x25.c"
    "images/_FF0000_240x135.c"
    "images/_5555_240x135.c"
    






    INCLUDE_DIRS
    "."
    "custom" # 自定义逻辑头文件路径
    "generated" # UI结构体/组件头文件路径
    "fonts" # 字体头文件路径
    "images" # 图片头文件路径（如有）


    REQUIRES aht20 qmc5883l bmp280 mpu6050 jfh142 lcd lvgl
)
