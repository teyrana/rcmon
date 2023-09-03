cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

# =============================
project(blink C CXX ASM)
# basically just a hello world for the RP2040-One board:
# https://www.waveshare.com/product/rp2040-one.htm

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# =============================
add_executable(rp2040-1-blink
        ${CMAKE_CURRENT_LIST_DIR}/src/led.c
        ${CMAKE_CURRENT_LIST_DIR}/src/led.h
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(rp2040-1-blink ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/build )

# =============================

pico_enable_stdio_usb(hello_world 1)

pico_set_program_name(rp2040-1-blink "RP2040_One_Blink")
pico_set_program_version(rp2040-1-blink "0.1")

# pull in common dependencies
target_link_libraries(rp2040-1-blink pico_stdlib)

# pico_enable_stdio_uart(blink 0)
# pico_enable_stdio_usb(blink 0)

# Add the standard library to the build
target_link_libraries(rp2040-1-blink pico_stdlib )

# Add any user requested libraries
target_link_libraries(rp2040-1-blink hardware_pio )

pico_add_extra_outputs(rp2040-1-blink)

