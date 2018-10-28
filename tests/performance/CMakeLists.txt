cmake_minimum_required(VERSION 3.0)
include(CheckCXXCompilerFlag)

project(performance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall -g -Werror -g -O -Wall -Weffc++ -pedantic
        -pedantic-errors -Wextra -Wcast-align -Wno-attributes
	-Wcast-qual -Wconversion -Wdisabled-optimization
	-Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security
	-Wformat-y2k -Wimport  -Winit-self  -Winline
	-Winvalid-pch -Wlong-long -Wmissing-field-initializers
	-Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn
	-Wpacked -Wpointer-arith -Wredundant-decls
	-Wshadow -Wstack-protector -Wstrict-aliasing=2
	-Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter
	-Wvariadic-macros -Wwrite-strings -Wno-unknown-pragmas
	-Wno-uninitialized  -Wno-inline")


file(GLOB_RECURSE sources "../../src/*.cpp")
file(GLOB_RECURSE headers "../../src/*.h")

include_directories("../../src/")


file(GLOB_RECURSE perf_sources "./*.cpp")
file(GLOB_RECURSE perf_headers "./*h")

add_executable(performance ${perf_sources} ${perf_headers} ${sources} ${headers})
