idf_component_register(
    SRCS "lcd_bl_pwm_bsp.c"
    INCLUDE_DIRS "."
    REQUIRES pwm gpio
    PRIV_REQUIRES main esp_driver_ledc esp_driver_gpio
)
