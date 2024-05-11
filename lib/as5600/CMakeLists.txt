
add_library( as5600 STATIC
    ${CMAKE_SOURCE_DIR}/lib/as5600/AS5600.cpp
    ${CMAKE_SOURCE_DIR}/lib/as5600/AS5600.h
)

# pull in common dependencies
target_link_libraries( as5600 pico_stdlib)

# Add any user requested libraries
target_link_libraries( as5600 hardware_pio hardware_i2c )