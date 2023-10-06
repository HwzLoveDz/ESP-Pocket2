# if(ESP_PLATFORM)

#     file(GLOB_RECURSE SOURCES src/*.c test/*.c)

#     idf_build_get_property(LV_MICROPYTHON LV_MICROPYTHON)

#     if (LV_MICROPYTHON)
#         idf_component_register(SRCS ${SOURCES}
#                                INCLUDE_DIRS . src test ../
#                                REQUIRES lv_lib_100ask)
#     else()
#         idf_component_register(SRCS ${SOURCES}
#                                INCLUDE_DIRS . src test
#                                REQUIRES lv_lib_100ask)
#     endif()

#     target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_LIB_100ASK_ESP_PLATFORM")

# else()

#     file(GLOB_RECURSE SOURCES src/*.c test/*.c)
#     add_library(lv_lib_100ask STATIC ${SOURCES})

# endif()


cmake_minimum_required(VERSION 3.12.4)

# Option to define LV_LIB_100ASK_CONF_INCLUDE_SIMPLE, default: ON
option(LV_LIB_100ASK_CONF_INCLUDE_SIMPLE "Simple include of \"lv_lib_100ask_conf.h\"" ON)

# Option to set LV_LIB_100ASK_CONF_PATH, if set parent path LV_LIB_100ASK_CONF_DIR is added
# to includes
option(LV_LIB_100ASK_CONF_PATH "Path defined for lv_lib_100ask_conf.h")
get_filename_component(LV_LIB_100ASK_CONF_DIR ${LV_LIB_100ASK_CONF_PATH} DIRECTORY)

# idf_component_register(SRCS ${SOURCES}
#                         INCLUDE_DIRS . src test
#                         REQUIRES lv_lib_100ask)

file(GLOB_RECURSE SOURCES src/*.c)
add_library(lv_lib_100ask STATIC ${SOURCES})

target_include_directories(lv_lib_100ask SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                  ${LV_LIB_100ASK_CONF_DIR})

target_link_libraries(lv_lib_100ask PUBLIC lvgl)

