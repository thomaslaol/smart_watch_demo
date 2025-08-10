set(srcs "src/ble_time_sync.c")
set(include_dirs "include")

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES iic_bus freertos bt nvs_flash
    PRIV_REQUIRES mrtc
    # PRIV_REQUIRES esp_timer mrtc
)

component_compile_options(-ffast-math -O3 -Wno-error=format)
# component_compile_options(-ffast-math -O0 -g -Wno-error=format)