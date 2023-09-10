cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(cmake/pico_sdk_import.cmake)

# =============================
project(irmon C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
# basically just a hello world for the RP2040-One board:
# https://www.waveshare.com/product/rp2040-one.htm

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(src/nec/receive)

# =============================
set( EXE_NAME irmon )
add_executable( ${EXE_NAME}
        # ${CMAKE_CURRENT_LIST_DIR}/src/led.c
        # ${CMAKE_CURRENT_LIST_DIR}/src/led.h
        ${CMAKE_CURRENT_LIST_DIR}/src/irmon/main.c
)

include_directories( ${EXE_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/ )
message( STATUS "::INCLUDE:: ${CMAKE_CURRENT_LIST_DIR}/src/" )

# =============================

# enable usb output, disable uart output
pico_enable_stdio_usb(${EXE_NAME} 1)
pico_enable_stdio_uart(${EXE_NAME} 0)

pico_set_program_name(${EXE_NAME} "InfraredMonitor")
pico_set_program_version(${EXE_NAME} "0.0.1")

# pull in common dependencies
target_link_libraries(${EXE_NAME} pico_stdlib)

# Add any user requested libraries
target_link_libraries(${EXE_NAME} hardware_pio )

target_link_libraries(${EXE_NAME} nec_receive_library )

pico_add_extra_outputs(${EXE_NAME})

