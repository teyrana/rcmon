cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# =======================================================================
project(blink)
# basically just a hello world for the RP2040-One board:
# https://www.waveshare.com/product/rp2040-one.htm

add_executable(blink
        src/led_ws2812b.c
        src/main.c
        )

# pull in common dependencies
target_link_libraries(blink pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)

# add url via pico_set_program_url
example_auto_set_url(blink)