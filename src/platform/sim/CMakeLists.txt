cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "ee-sim")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

file(
  GLOB_RECURSE
  PROJECT_SOURCES
  "${CMAKE_SOURCE_DIR}/../../engine/*.cpp"
  "${CMAKE_SOURCE_DIR}/../../app/*.cpp"
  "${CMAKE_SOURCE_DIR}/../../engine/*.c"
  "${CMAKE_SOURCE_DIR}/../../app/*.c"
  "${CMAKE_SOURCE_DIR}/*.c"
  "${CMAKE_SOURCE_DIR}/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/../../engine"
                    "${CMAKE_SOURCE_DIR}/../../app" "${CMAKE_SOURCE_DIR}")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
