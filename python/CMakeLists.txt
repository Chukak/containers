cmake_minimum_required(VERSION 3.0)

project(containers LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(ENABLE_PYTHON3 ON)
set(PYTHON_EXECUTABLE_PATH)

#TODO
#fix for travis

find_package(PythonInterp 3.5 REQUIRED)
find_package(PythonLibs 3.5 REQUIRED)
if (PythonLibs_FOUND AND PythonIterp_FOUND)
    find_package(Boost 1.52.0 COMPONENTS python-py35 REQUIRED)
else(PythonLibs_FOUND AND PythonIterp_FOUND)
    find_package(PythonInterp 3.4 REQUIRED)
    find_package(PythonLibs 3.4 REQUIRED)
    find_package(Boost 1.52.0 COMPONENTS python-py34 REQUIRED)
endif()

add_definitions("-g -O -Wall -Werror -fPIC")

include_directories("../src")

file(GLOB_RECURSE sources "src/*.cpp")

python_add_module(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
