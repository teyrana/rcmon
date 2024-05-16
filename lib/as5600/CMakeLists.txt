
add_library( as5600 STATIC
    ${CMAKE_SOURCE_DIR}/lib/as5600/AS5600.cpp
    ${CMAKE_SOURCE_DIR}/lib/as5600/AS5600.h
)

target_link_libraries( as5600 
    # pull in common dependencies
    pico_stdlib

    # Add any user requested libraries
    hardware_pio 
    hardware_i2c
)