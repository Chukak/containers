cmake_minimum_required(VERSION 3.0)

project(containers_tests LANGUAGES CXX)

set(COVERAGE_COMPILE_FLAGS "-coverage -fprofile-arcs -ftest-coverage --coverage")
set(COVERAGE_LINK_FLAGS "-coverage -lgcov")

if (NOT DEFINED BUILD_TESTS)
    message(FATAL_ERROR "Please, go to top level project directory and run cmake with '-DBUILD_TESTS=1' option.")
endif()

set(CATCH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodules/Catch2")
if (EXISTS ${CATCH_DIR})
    add_subdirectory(${CATCH_DIR})
    include_directories("${CATCH_DIR}/single_include/catch2/")
    add_library(Catch INTERFACE)
    target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
else()
    message(FATAL_ERROR "The directory ${CATCH_DIR} doesn't exists!")
endif()

file(GLOB main_source "${CMAKE_CURRENT_SOURCE_DIR}/unit/main.cpp")
file(GLOB unittests_sources "${CMAKE_CURRENT_SOURCE_DIR}/unit/tst_*.cpp")
file(GLOB catch2_headers "${CATCH_DIR}/single_include/catch2/*.hpp")

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")
endif()

add_executable(${PROJECT_NAME} ${catch2_headers} ${unittests_sources} ${main_source})
target_link_libraries(${PROJECT_NAME} containers Catch2 ${COVERAGE_LINK_FLAGS})
add_test(NAME "${PROJECT_NAME}" COMMAND ${PROJECT_NAME})
