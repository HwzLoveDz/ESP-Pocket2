#Add sources from ui directory
file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c")
file(GLOB UI_C_SOURCES src/lv_dependent/*.c)
file(GLOB UI_CPP_SOURCES src/lv_dependent/*.cpp)
# file(GLOB SQ_SOURCES src/lv_squarline/*.c)
# file(GLOB SQ_SOURCES src/lv_squarline/screens/*.c)
# file(GLOB SQ_SOURCES src/lv_squarline/images/*.c)
# file(GLOB PNG_SOURCES src/lv_assets/png/*.c)
# file(GLOB FONTS_SOURCES src/lv_assets/fonts/*.c)
file(GLOB I2C_PER_C_SOURCES src/i2c_peripheral/*.c)
file(GLOB I2C_PER_CPP_SOURCES src/i2c_peripheral/*.cpp)
# file(GLOB UART_PER_CPP_SOURCES src/uart_peripheral/*.c)

idf_component_register(SRCS     
                                ${SRC_UI}
                                # ${SQ_SOURCES}
                                # ${PNG_SOURCES}
                                # ${FONTS_SOURCES}
                                ${UI_C_SOURCES}
                                ${UI_CPP_SOURCES}
                                ${I2C_PER_C_SOURCES}
                                ${I2C_PER_CPP_SOURCES}
                                # ${UART_PER_CPP_SOURCES}
                                "max31856_task.c"
                                "main.cpp"

                        INCLUDE_DIRS 
                                "."
                                "ui"
                                "./include"
                                "./include/lv_dependent"
                                # "./include/lv_squarline"
                                # "./include/lv_assets"
                                "./include/i2c_peripheral"
                                # "./include/uart_peripheral"
                        )
