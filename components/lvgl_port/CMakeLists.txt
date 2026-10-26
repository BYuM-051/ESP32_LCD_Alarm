# The existing port files are unfinished; register the public headers only.
idf_component_register(
    INCLUDE_DIRS "."
    REQUIRES lvgl__lvgl
)
