cmake_minimum_required(VERSION 3.0)

project(containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -g -Werror -O -fPIC -Weffc++ -pedantic \
    -pedantic-errors -Wextra -Wcast-align \
    -Wcast-qual -Wconversion -Wdisabled-optimization \
    -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security \
    -Wformat-y2k -Wimport  -Winit-self  -Winline \
    -Winvalid-pch -Wlong-long -Wmissing-field-initializers \
    -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn \
    -Wpacked -Wpointer-arith -Wredundant-decls \
    -Wshadow -Wstack-protector -Wstrict-aliasing=2 \
    -Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter \
    -Wvariadic-macros -Wwrite-strings -Wno-unknown-pragmas \
    -Wno-uninitialized  -Wno-inline -Wno-long-long")

#  -Wswitch-default

find_program(HAS_CPPCHECK "cppcheck")
if (HAS_CPPCHECK)
    # cppcheck section
    set(CPPCHECK_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src")
    set(CPPCHECK_TESTS_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/tests/unit")
    set(CPPCHECK_SRC_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src")
    set(CPPCHECK_TEMPLATE "--template=\"[{severity}][{id}] {message} {callstack} (On {file}:{line})\"")
    set(CPPCHECK_COMMAND cppcheck)
    set(CPPCHECK_ARGUMENTS --enable=all ${CPPCHECK_TEMPLATE}
        --inconclusive -I ${CPPCHECK_INCLUDE_DIRECTORIES} -I ${CPPCHECK_TESTS_DIRECTORIES}
        -i googletest
        --suppress=missingIncludeSystem
        ${CPPCHECK_SRC_DIRECTORIES} ${CPPCHECK_TESTS_DIRECTORIES})
    set(CPPCHECK_LOG_FILE "${CMAKE_CURRENT_BINARY_DIR}/cppcheck.txt")
    execute_process(COMMAND ${CPPCHECK_COMMAND} ${CPPCHECK_ARGUMENTS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        RESULT_VARIABLE rv
        ERROR_FILE ${CPPCHECK_LOG_FILE})
endif()

if (BUILD_TESTS AND BUILD_ASAN)
    if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER "4.7.4")
        set(SANITIZE_FLAG "address")
        set(ASAN_Libraries asan)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=${SANITIZE_FLAG} -fno-omit-frame-pointer")
    endif()
endif()

file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "src/*.h")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(${PROJECT_NAME} SHARED ${headers} ${sources})

if (BUILD_TESTS)
    enable_testing()
    link_directories("${CMAKE_BINARY_DIR}")

    add_subdirectory(tests)
    add_subdirectory(tests/performance)
endif()

if (BUILD_PYTHON)
    if (DEFINED PY_MODULE_WRAP_METHODS)
        add_definitions("-DPY_MODULE_WRAP_METHODS")
    endif()
    add_subdirectory(python)
endif()
