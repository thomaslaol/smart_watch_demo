idf_component_register(
    SRCS
    "main.c"

    "app/app.c"
    "app/custom/custom.c"

    "app/generated/widgets_init.c" # UI组件初始化
    "app/generated/events_init.c" # 事件回调
    "app/generated/gui_guider.c" # UI全局逻辑（若存在）
    "app/generated/setup_scr_screen_main.c"

    "app/fonts/lv_font_sun_14.c" # 中文字体
    "app/fonts/lv_font_sun_16.c"
    "app/fonts/lv_font_sun_22.c"
    "app/fonts/lv_font_sun_32.c"
    "app/fonts/lv_font_arial_16.c"
    "app/fonts/lv_font_montserratMedium_12.c" # 度数字体
    "app/fonts/lv_font_montserratMedium_16.c"

    "app/images/_5555_240x135.c"
    "app/images/_222_240x135.c"
    "app/images/_333_240x135.c"
    "app/images/_3304542_20230221171348882211_0_58x2.c"
    "app/images/_3304542_20230221171348882211_0_100x2.c"
    "app/images/_3304542_20230221171348882211_0_alpha_236x1.c"
    "app/images/_3304542_20230221171348882211_0_alpha_238x1.c"
    "app/images/_date_15x15.c"
    "app/images/_heart2_25x25.c"
    "app/images/_hum_23x23.c"
    "app/images/_pointer2_15x15.c"
    "app/images/_step_23x20.c"
    "app/images/_temp_23x23.c"
    "app/images/_tired_25x25.c"
    "app/images/_week_25x25.c"

    "app/images/_temp_25x25.c"
    "app/images/_bt_20x20.c"
    "app/images/_o2_21x20.c"
    "app/images/_power2_20x20.c"
    "app/images/_wei_22x22.c"


    INCLUDE_DIRS
    "."
    "app"
    "app/custom" # 自定义逻辑头文件路径
    "app/generated" # UI结构体/组件头文件路径
    "app/fonts" # 字体头文件路径
    "app/images" # 图片头文件路径

    REQUIRES aht20 qmc5883l bmp280 mpu6050 jfh142 lcd lvgl ble mrtc
)
