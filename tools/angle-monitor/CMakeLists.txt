set( EXE_NAME angle-monitor )

add_executable( ${EXE_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


target_link_libraries( ${EXE_NAME}
        # Common libraries
        pico_stdlib

        # Pico Hardware libraries
        hardware_pio
        hardware_i2c
)

# Project internal libraries
target_link_libraries( ${EXE_NAME}
        as5600
        led
)

pico_set_program_name(${EXE_NAME} "AngleMon")
pico_set_program_version(${EXE_NAME} "0.1.0")

# enable usb output
pico_enable_stdio_usb(${EXE_NAME} 1)

# disable uart output
pico_enable_stdio_uart(${EXE_NAME} 0)

# create map,bin,hex,uf2 files in addition to ELF.
pico_add_extra_outputs(${EXE_NAME})

