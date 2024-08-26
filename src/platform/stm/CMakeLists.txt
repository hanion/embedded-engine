# ##############################################################################
# file:  CMakeLists.txt brief: Template "CMakeLists.txt" for building of
# executables and static libraries.
#
# usage: Edit "VARIABLES"-section to suit project requirements. For debug build:
# cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -G"Unix
# Makefiles" -DCMAKE_BUILD_TYPE=Debug make -C Debug VERBOSE=1 -j For release
# build: cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release
# -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release make -C Release VERBOSE=1 -j
# ##############################################################################
cmake_minimum_required(VERSION 3.20)

# ##################### CONSTANTS ######################################
set(PROJECT_TYPE_EXECUTABLE "exe")
set(PROJECT_TYPE_STATIC_LIBRARY "static-lib")
set(MCPU_CORTEX_M0 "-mcpu=cortex-m0")
set(MCPU_CORTEX_M0PLUS "-mcpu=cortex-m0plus")
set(MCPU_CORTEX_M3 "-mcpu=cortex-m3")
set(MCPU_CORTEX_M4 "-mcpu=cortex-m4")
set(MCPU_CORTEX_M7 "-mcpu=cortex-m7")
set(MCPU_CORTEX_M33 "-mcpu=cortex-m33")
set(MCPU_CORTEX_M55 "-mcpu=cortex-m55")
set(MCPU_CORTEX_M85 "-mcpu=cortex-m85")
set(MFPU_FPV4_SP_D16 "-mfpu=fpv4-sp-d16")
set(MFPU_FPV5_D16 "-mfpu=fpv5-d16")
set(RUNTIME_LIBRARY_STD_C "")
set(RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set(RUNTIME_LIBRARY_SYSCALLS_NONE "")
set(MFLOAT_ABI_SOFTWARE "-mfloat-abi=soft")
set(MFLOAT_ABI_HARDWARE "-mfloat-abi=hard")
set(MFLOAT_ABI_MIX "-mfloat-abi=softfp")
# ##############################################################################

# ##################### VARIABLES ######################################
set(PROJECT_NAME "ee-stm")
set(PROJECT_TYPE "exe")
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103R8TX_FLASH.ld")
set(MCPU "-mcpu=Cortex-M3")
set(MFLOAT_ABI "")
# set (RUNTIME_LIBRARY          "--specs=nosys.specs") set
# (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wno-unsupported-option)

# Recursively include all source files
file(
  GLOB_RECURSE
  PROJECT_SOURCES
  "${CMAKE_SOURCE_DIR}/../../engine/*.cpp"
  "${CMAKE_SOURCE_DIR}/../../app/*.cpp"
  "${CMAKE_SOURCE_DIR}/../../engine/*.c"
  "${CMAKE_SOURCE_DIR}/../../app/*.c"
  "${CMAKE_SOURCE_DIR}/*.c"
  "${CMAKE_SOURCE_DIR}/*.cpp"
  "${CMAKE_SOURCE_DIR}/*.s"
  "${CMAKE_SOURCE_DIR}/Drivers/*.c"
  "${CMAKE_SOURCE_DIR}/Drivers/*.cpp")

# Recursively include all header files
# file(
#   GLOB_RECURSE
#   PROJECT_INCLUDES
#   # "/usr/include"
#   # "/usr/local/include"
#   # "/usr/lib/clang/18/include"
#   "${CMAKE_SOURCE_DIR}"
#   "${CMAKE_SOURCE_DIR}/src/platform/stm/"
#   "${CMAKE_SOURCE_DIR}/../../engine/"
#   "${CMAKE_SOURCE_DIR}/../../app/"
#   "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include"
#   "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include"
#   "${CMAKE_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc"
#   "${CMAKE_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy")

set(PROJECT_DEFINES # LIST COMPILER DEFINITIONS HERE
)

# ########### MODIFY ACCORDING TO REQUIREMENTS) ########################

# ##############################################################################

# ################# PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(ASM)
if(${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_EXECUTABLE})
  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
  add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
elseif(${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
  add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

add_compile_definitions(${PROJECT_DEFINES})

# Define the target STM32 device
add_definitions(-DSTM32F103R8)

include_directories(
  "${CMAKE_SOURCE_DIR}/../../engine"
  "${CMAKE_SOURCE_DIR}/../../app"
  "${CMAKE_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include"
  "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include"
  "${CMAKE_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc"
  "${CMAKE_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy")

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")

set(CMAKE_C_FLAGS
    "${MTUNE} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -Wall -Werror"
)
set(CMAKE_EXE_LINKER_FLAGS
    "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group"
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -mcpu=cortex-m3 -mthumb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -mcpu=cortex-m3 -mthumb")

set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -Wall -fstack-usage -mfloat-abi=soft"
)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -mfloat-abi=soft"
)

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs -Wl,-Map=\"${BuildArtifactFileBaseName}.map\" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group"
)
