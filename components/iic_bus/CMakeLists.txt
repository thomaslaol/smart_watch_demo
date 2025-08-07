set(srcs "src/iic_bus.c")
set(include_dirs "include")

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES driver
)

component_compile_options(-ffast-math -O1 -Wno-error=format)