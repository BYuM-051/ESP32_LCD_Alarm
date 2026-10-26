cmake_minimum_required(VERSION 3.16)

# ESP-IDF discovers immediate children of components/ automatically.
# Register the BSP's nested bus and device directories as separate components.
file(GLOB_RECURSE BSP_COMPONENT_CMAKES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/components/bsp/*/CMakeLists.txt"
)
foreach(BSP_COMPONENT_CMAKE IN LISTS BSP_COMPONENT_CMAKES)
    get_filename_component(BSP_COMPONENT_DIR "${BSP_COMPONENT_CMAKE}" DIRECTORY)
    list(APPEND EXTRA_COMPONENT_DIRS "${BSP_COMPONENT_DIR}")
endforeach()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(10_LVGL_V9_Test)
