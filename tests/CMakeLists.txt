cmake_minimum_required(VERSION 3.0)
include(CheckCXXCompilerFlag)

project(containers_tests)

CHECK_CXX_COMPILER_FLAG(-std=c++14 COMPILER_SUPPORTS_CXX14)

add_compile_options("-g")
add_compile_options("-Wall")
add_compile_options("-Werror")

if(COMPILER_SUPPORTS_CXX14)
    add_compile_options("-std=c++14")
endif()

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(SOURCES_DIR ../src)

set(
    TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tst_queue.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/tst_queue_c.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/tst_stack.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/tst_stack_c.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/tst_sorted_list.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/tst_bst.cpp
                 ${SOURCES_DIR}/queue.cpp
                 ${SOURCES_DIR}/stack.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )

include_directories(${SOURCES_DIR})
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch)
