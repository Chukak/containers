cmake_minimum_required(VERSION 3.0)

project(containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall -g -Werror -O -fPIC -Weffc++ -pedantic
    -pedantic-errors -Wextra -Wcast-align
    -Wcast-qual -Wconversion -Wdisabled-optimization
    -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security
    -Wformat-y2k -Wimport  -Winit-self  -Winline
    -Winvalid-pch -Wlong-long -Wmissing-field-initializers
    -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn
    -Wpacked -Wpointer-arith -Wredundant-decls
    -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wswitch-default
    -Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter
    -Wvariadic-macros -Wwrite-strings -Wno-unknown-pragmas
    -Wno-uninitialized  -Wno-inline")

file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "src/*.h")

include_directories("src/")

add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
