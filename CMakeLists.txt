cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

# =============================
project(irmon C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
# basically just a hello world for the RP2040-One board:
# https://www.waveshare.com/product/rp2040-one.htm

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(src/receive)

# =============================
add_executable(irmon
        # ${CMAKE_CURRENT_LIST_DIR}/src/led.c
        # ${CMAKE_CURRENT_LIST_DIR}/src/led.h
        ${CMAKE_CURRENT_LIST_DIR}/src/irmon/main.c
)

# # generate the header file into the source tree as it is included in the RP2040 datasheet
# pico_generate_pio_header(irmon ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/build )

# =============================

# enable usb output, disable uart output
pico_enable_stdio_usb(irmon 1)
pico_enable_stdio_uart(irmon 0)

pico_set_program_name(irmon "InfraredMonitor")
pico_set_program_version(irmon "0.0.1")

# pull in common dependencies
target_link_libraries(irmon pico_stdlib)

# Add any user requested libraries
target_link_libraries(irmon hardware_pio )

target_link_libraries(irmon nec_receive_library )

pico_add_extra_outputs(irmon)

