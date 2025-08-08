idf_component_register(
    SRCS
    "main.c"
    INCLUDE_DIRS
    "."
    REQUIRES aht20 qmc5883l bmp280 mpu6050 jfh142 lcd
)
