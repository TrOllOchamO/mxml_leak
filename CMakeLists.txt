cmake_minimum_required(VERSION 3.22.1)
project(mxml-leak-test C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wno-error=unused-function -Wno-error=unused-parameter -Wno-error=unused-variable")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("src/")
add_subdirectory("mxml/")

