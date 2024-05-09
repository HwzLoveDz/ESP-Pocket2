# set(src_dirs ./src)
# set(include_dirs ./src)
# idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs})
idf_component_register(SRCS "src/max31856.c"
                    REQUIRES driver
                    INCLUDE_DIRS "src"
                    )
