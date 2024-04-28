cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(cmake/pico_sdk_import.cmake)

# =============================
project(revmon C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)


# TODO: setup board type
# # Add my_pico_w.h
# set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR} )
# # Add my_pico_w.cmake
# set(PICO_BOARD_CMAKE_DIRS ${CMAKE_CURRENT_LIST_DIR} )
# # Add my_pico_w
# set(PICO_BOARD my_pico_w)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()


# =============================
add_subdirectory(src/blink)
# add_subdirectory(src/mon)
# add_subdirectory(src/scan)


# include_directories( ${CMAKE_CURRENT_LIST_DIR}/src/ )
# message( STATUS "::INCLUDE:: ${CMAKE_CURRENT_LIST_DIR}/src/" )


