cmake_minimum_required(VERSION 3.0)
include(CheckCXXCompilerFlag)

project(containers_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall -g -Werror")
#-g -O -Wall -fPIC -Weffc++ -pedantic  \
#	-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
#	-Wcast-qual -Wconversion -Wdisabled-optimization -Werror \
#	-Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security  \
#	-Wformat-y2k -Wimport  -Winit-self  -Winline \
#	-Winvalid-pch -Wlong-long -Wmissing-field-initializers \
#	-Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn \
#	-Wpacked  -Wpadded -Wpointer-arith -Wredundant-decls \
#	-Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wswitch-default \
#	-Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter \
#	-Wvariadic-macros -Wwrite-strings")


file(GLOB_RECURSE sources "../src/*.cpp")
file(GLOB_RECURSE headers "../src/*.h")

include_directories("../src/")

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

add_executable(${PROJECT_NAME} ${headers} ${sources} ${catch2_headers} ${unittests_sources})
target_link_libraries(${PROJECT_NAME}  Catch2)
