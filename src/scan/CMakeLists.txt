set( EXE_NAME i2c_scan )
add_executable( ${EXE_NAME}
        ${CMAKE_CURRENT_LIST_DIR}/src/scan/main.c
)
# pull in common dependencies and additional i2c hardware support
target_link_libraries(i2c_scan pico_stdlib hardware_i2c)

# # create map/bin/hex file etc.
# pico_add_extra_outputs(i2c_bus_scan)


