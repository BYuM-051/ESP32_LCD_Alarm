idf_component_register(
    SRCS "i2cBSP.c"
    INCLUDE_DIRS "."
    REQUIRES bsp esp_driver_i2c
)
