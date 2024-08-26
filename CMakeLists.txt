cmake_minimum_required(VERSION 3.10)

project(embedded-engine)

option(TARGET_PLATFORM "Select the target platform: stm or sim" "stm")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(TARGET_PLATFORM STREQUAL "stm")
    message(STATUS "Building for STM32 platform")
    include(src/platform/stm/CMakeLists.txt)
elseif(TARGET_PLATFORM STREQUAL "sim")
    message(STATUS "Building for Raylib (Simulator) platform")
    include(src/platform/sim/CMakeLists.txt)
else()
    message(FATAL_ERROR "Unknown TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()
