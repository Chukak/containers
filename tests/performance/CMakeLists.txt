cmake_minimum_required(VERSION 3.0)
include(CheckCXXCompilerFlag)

project(containers_performance)

file(GLOB_RECURSE perf_sources "./*.cpp")
file(GLOB_RECURSE perf_headers "./*h")

add_executable(${PROJECT_NAME} ${perf_sources} ${perf_headers})
target_link_libraries(${PROJECT_NAME} containers)
#add_test(NAME "${PROJECT_NAME}" COMMAND ${PROJECT_NAME})
