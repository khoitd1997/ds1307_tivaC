add_library(ds3231 src/ds3231.c src/ds3231_i2c.c)
target_include_directories(ds3231 PUBLIC include PRIVATE src)
target_link_libraries(ds3231 PRIVATE tiva_utils)
