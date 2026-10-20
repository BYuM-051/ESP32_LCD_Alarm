file(GLOB_RECURSE UISrcs CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
)

idf_component_register(
    SRCS
        ${UISrcs}
    INCLUDE_DIRS
        "./"
    REQUIRES 
        lvgl
)