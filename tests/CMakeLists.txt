cmake_minimum_required(VERSION 3.0)

project(containers_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COVERAGE_COMPILE_FLAGS "-coverage -fprofile-arcs -ftest-coverage --coverage")
set(COVERAGE_LINK_FLAGS "-coverage -lgcov")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -g -Werror -g -O -Wall -Weffc++ \
        -pedantic-errors -Wextra -Wcast-align -Wno-attributes \
        -Wcast-qual -Wconversion -Wdisabled-optimization \
        -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security \
        -Wformat-y2k -Wimport  -Winit-self  -Winline \
        -Winvalid-pch -Wlong-long -Wmissing-field-initializers \
        -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn \
        -Wpacked -Wpointer-arith -Wredundant-decls \
        -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wswitch-default \
        -Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter \
        -Wvariadic-macros -Wwrite-strings -Wno-unknown-pragmas \
        -Wno-uninitialized  -Wno-inline -Wno-long-long")

# disabled flags
#  -Wpadded  -Waggregate-return

set(SAVED_COMPILER_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS "")

if (EXISTS "../CMakeLists.txt")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../" "${CMAKE_CURRENT_BINARY_DIR}/libcontainers")
    file(COPY "../include/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/libcontainers/include/")
    include_directories("${CMAKE_CURRENT_BINARY_DIR}/libcontainers/include/")
    link_directories("${CMAKE_CURRENT_BINARY_DIR}/libcontainers/")
endif()

set(CMAKE_CXX_FLAGS ${SAVED_COMPILER_FLAGS})
#file(GLOB_RECURSE sources "../src/*.cpp")
#file(GLOB_RECURSE headers "../src/*.h")

#include_directories("../src/")

set(CATCH_DIR "submodules/Catch2")
add_subdirectory(${CATCH_DIR})

include_directories("${CATCH_DIR}/single_include/catch2/")
if (EXISTS ${CATCH_DIR})
    message(${CATCH_DIR})
endif()
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})


file(GLOB unittests_sources "${CMAKE_CURRENT_SOURCE_DIR}/tst_*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
file(GLOB catch2_headers "${CATCH_DIR}/single_include/catch2/*.hpp")

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")
endif()

add_executable(${PROJECT_NAME} ${catch2_headers} ${unittests_sources})
target_link_libraries(${PROJECT_NAME} containers Catch2)
