# version requirements
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# initialization
include(${CMAKE_SOURCE_DIR}/src/Dependency/pico-sdk/pico_sdk_init.cmake)

# project definition
project(sdcard)

pico_sdk_init()

add_subdirectory(${CMAKE_SOURCE_DIR}/src/Dependency/no-OS-FatFS/src build)

add_executable(${PROJECT_NAME} src/main.cpp)

# target configuration
set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    pico_stdlib
    FatFs_SPI)

pico_enable_stdio_usb(${PROJECT_NAME} 1) # enable usb output
pico_enable_stdio_uart(${PROJECT_NAME} 0) # disable uart output
pico_add_extra_outputs(${PROJECT_NAME}) # create map/bin/hex/uf2 files in addition to elf