
add_library( monoled STATIC
    ${CMAKE_SOURCE_DIR}/lib/led/monoled.c
    ${CMAKE_SOURCE_DIR}/lib/led/monoled.h
)
target_link_libraries( monoled pico_stdlib)

add_library( rgbled STATIC
    ${CMAKE_SOURCE_DIR}/lib/led/ws2812.c
    ${CMAKE_SOURCE_DIR}/lib/led/ws2812.h
)

# pull in common dependencies
target_link_libraries( rgbled pico_stdlib)

# Add any user requested libraries
target_link_libraries( rgbled hardware_pio )


# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header( rgbled
    ${CMAKE_SOURCE_DIR}/lib/led/ws2812.pio
    OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib/led/
)
