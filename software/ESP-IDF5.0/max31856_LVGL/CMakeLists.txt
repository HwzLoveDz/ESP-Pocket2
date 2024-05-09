cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_FLAGS "-O3")
set(--compile-no-warning-as-error)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ST7789_GT911_LVGL_8.3.5)
