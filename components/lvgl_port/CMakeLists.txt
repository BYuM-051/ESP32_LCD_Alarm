# The existing port draft is unchanged and is not yet registered as a source.
idf_component_register(
    INCLUDE_DIRS "."
    REQUIRES lvgl__lvgl lcd lcd_bl_pwm_bsp touch esp_timer
)
