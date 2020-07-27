cmake_minimum_required(VERSION 3.0)

project(containers_py LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

if (NOT DEFINED BUILD_PYTHON)
    message(FATAL_ERROR "Please, go to top level project directory and run cmake with '-DBUILD_PYTHON=1' option.")
endif()

set(ENABLE_PYTHON3 ON)
set(PYTHON_EXECUTABLE_PATH)

find_package(Boost 1.52.0 COMPONENTS python-py36 QUIET)
if (NOT Boost_FOUND)
    find_package(Boost 1.52.0 COMPONENTS python-py35 QUIET)
    if (NOT Boost_FOUND)
        find_package(Boost 1.52.0 COMPONENTS python-py34 QUIET)
        if (NOT Boost_FOUND)
            find_package(Boost 1.52.0 COMPONENTS python REQUIRED)
            find_package(PythonInterp 3 REQUIRED)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(PythonInterp 3.4 REQUIRED)
            find_package(PythonLibs 3.4 REQUIRED)
        endif()
    else()
        find_package(PythonInterp 3.5 REQUIRED)
        find_package(PythonLibs 3.5 REQUIRED)
    endif()
else()
    find_package(PythonInterp 3.6 REQUIRED)
    find_package(PythonLibs 3.6 REQUIRED)
endif()


add_definitions("-g -O -Wall -Werror -fPIC")

include_directories("../src")

file(GLOB_RECURSE sources "src/*.cpp")

add_definitions("-DLIBRARY_NAME=${PROJECT_NAME}")

python_add_module(${PROJECT_NAME} ${sources})

if (BUILD_ASAN)
    set(ASAN_SUPPRESSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/asan.supp")
    set(LEAK_SUPPRESSIONS "leak:*boost::python*\n
        leak:*PyUnicode_*\n
        leak:*PyType_*\n
        leak:*PyBytes_*\n
        leak:*PyObject_*\n
        leak:*python*\n
        leak:*bash*\n") # CI leaks
    file(WRITE "${ASAN_SUPPRESSION_FILE}" "${LEAK_SUPPRESSIONS}")
    set(ASAN_PRELOAD "LD_PRELOAD=\"$(gcc -print-file-name=libasan.so) $(gcc -print-file-name=libstdc++.so)\"")
    set(ASAN_OPTIONS "LSAN_OPTIONS=suppressions=${ASAN_SUPPRESSION_FILE}:verbosity=1")
else()
    set(ASAN_PRELOAD "")
endif()

set(RUN_TEST_COMMAND "mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/tests &&
    cp ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.py ${CMAKE_CURRENT_BINARY_DIR}/tests &&
    cp ${CMAKE_CURRENT_BINARY_DIR}/containers_py.so ${CMAKE_CURRENT_BINARY_DIR}/tests/ &&
    cd ${CMAKE_CURRENT_BINARY_DIR}/tests &&
    ${ASAN_PRELOAD} ${ASAN_OPTIONS} python3 -m unittest discover -s ./ -p \"tst_*.py\"")

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
add_test(NAME "${PROJECT_NAME}" COMMAND sh -c "${RUN_TEST_COMMAND}")
