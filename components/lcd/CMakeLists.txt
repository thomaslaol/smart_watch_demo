set(srcs 
"src/ui.c"
"src/lvgl_init.c"
# "src/lcd.c"
"src/st7789v.c"
"src/cst816t.c"
)
set(include_dirs "include")

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES freertos esp_timer driver lvgl iic_bus
)

component_compile_options(-ffast-math -O3 -Wno-error=format)
# component_compile_options(-ffast-math -O0 -g -Wno-error=format)