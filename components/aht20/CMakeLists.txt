set(srcs "src/aht20.c")
set(include_dirs "include")

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES iic_bus freertos
)

component_compile_options(-ffast-math -O3 -Wno-error=format)
# component_compile_options(-ffast-math -O0 -g -Wno-error=format)