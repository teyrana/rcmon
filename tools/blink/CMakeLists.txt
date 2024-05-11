set( EXE_NAME blink )

add_executable( ${EXE_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

# pull in common dependencies
target_link_libraries( ${EXE_NAME} pico_stdlib)

# Add any user requested libraries
target_link_libraries( ${EXE_NAME} hardware_pio )

# Add any project internal libraries
target_link_libraries( ${EXE_NAME} 
        monoled
        rgbled )

pico_set_program_name(${EXE_NAME} "Blink")
pico_set_program_version(${EXE_NAME} "0.1.0")

# enable usb output
pico_enable_stdio_usb(${EXE_NAME} 1)

# disable uart output
pico_enable_stdio_uart(${EXE_NAME} 0)

# need this to generate the .uf2 binariy output
pico_add_extra_outputs(${EXE_NAME})
