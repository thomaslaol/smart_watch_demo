set(srcs 
    "src/inv_mpu_dmp_motion_driver.c" 
    "src/inv_mpu.c" 
    "src/mpu6050.c" 
)

set(include_dirs "include")

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES iic_bus freertos
)

component_compile_options(-ffast-math -O1 -Wno-error=format)
# component_compile_options(-ffast-math -O0 -g -Wno-error=format)
