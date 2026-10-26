# Header-only until the bus implementation is written.
idf_component_register(
    INCLUDE_DIRS "."
    REQUIRES bsp esp_driver_gpio
)
