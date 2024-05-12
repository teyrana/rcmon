
add_library( led STATIC
    # Monochrome LED
    ${CMAKE_SOURCE_DIR}/lib/led/monoled.c
    ${CMAKE_SOURCE_DIR}/lib/led/monoled.h

    # RGB LED
    ${CMAKE_SOURCE_DIR}/lib/led/ws2812.c
    ${CMAKE_SOURCE_DIR}/lib/led/ws2812.h
)

# pull in common dependencies
target_link_libraries( led
    pico_stdlib
    hardware_pio
)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header( led
    ${CMAKE_SOURCE_DIR}/lib/led/ws2812.pio
    OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib/led/
)
