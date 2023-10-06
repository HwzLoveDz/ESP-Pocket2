
# set(COMPONENT_SRCS "./DRV2605/src/Adafruit_DRV2605.cpp")
# set(COMPONENT_ADD_INCLUDEDIRS "./DRV2605/src")
# register_component()

idf_component_register(SRCS "src/drv2605.cpp"
                    INCLUDE_DIRS "src"
                    )