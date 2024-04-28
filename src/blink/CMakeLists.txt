set( EXE_NAME blink )

add_executable( ${EXE_NAME}
        ws2812.pio.h
        main.c
)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(${EXE_NAME} 
        ${CMAKE_CURRENT_SOURCE_DIR}/ws2812.pio 
        OUTPUT_DIR . )

# enable usb output
pico_enable_stdio_usb(${EXE_NAME} 1)
# disable uart output
pico_enable_stdio_uart(${EXE_NAME} 0)

pico_set_program_name(${EXE_NAME} "Blink")
pico_set_program_version(${EXE_NAME} "0.1.0")

# pull in common dependencies
target_link_libraries(${EXE_NAME} pico_stdlib)

# Add any user requested libraries
target_link_libraries(${EXE_NAME} hardware_pio )

pico_add_extra_outputs(${EXE_NAME})

