cmake_minimum_required(VERSION 3.0)
include(CheckCXXCompilerFlag)

project(performance)

CHECK_CXX_COMPILER_FLAG(-std=c++14 COMPILER_SUPPORTS_CXX14)

add_compile_options("-g")
add_compile_options("-Wall")
add_compile_options("-Werror")

if(COMPILER_SUPPORTS_CXX14)
    add_compile_options("-std=c++14")
endif()

set(SOURCES_DIR ../../src)

set(
    SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

include_directories(${SOURCES_DIR})
add_executable(performance ${SRC_FILES})
