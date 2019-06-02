#!/bin/bash

CXX_LIB=""
PLACE_LIB=""
PLACE_HEADERS=""
COMMONDIR="containers"
CONTAINERS=(queue stack sorted_list bst counter)
declare -A SOURCES
SOURCES=([queue]=queue [stack]=stack [sorted_list]=sorted_list [bst]=bst [counter]=counter)

check_return_code() {
    until eval $1;
    do
        exit 1
    done
}

config_gxx() {
    echo "Checking g++."
    gxx_version="$(g++ -dumpversion)"
    if [[ $? -ne 0 ]]; then
        echo "Package `g++` not found."
        exit 1
    fi
    regex='^[7-9]{1}.*$'
    if ! [[ $gxx_version =~ $regex ]]; then
        echo "You need 'g++' 7 version and newer."
        exit 1
    fi
    unset gxx_version
    unset regex
}

config_cmake() {
    echo "Checking cmake."
    check_cmake=$(cmake --version)
    if [[ $? -ne 0 ]]; then
        echo "Package `cmake` not found."
        exit 1;
    fi
    cmake_version="$(cmake --version | grep -E "^cmake version [3-9]\.([7-9]|10)\.[0-9]")"
    if ! [[ $cmake_version ]]; then
        echo "You need 'cmake' 3.7.2 version and newer."
        exit 1
    fi
    unset cmake_version
    unset check_cmake
}



build_library() {
    config_cmake
    
    if ! [[ $CXX ]]; then
        config_gxx
    fi
    
    if [[ -d $PWD/build_lib ]]; then
        check_return_code "rm -rf build_lib"
    fi
    check_return_code "mkdir build_lib"
    check_return_code "cd build_lib"
    if [[ -x $CXX ]]; then
        check_return_code "cmake -DCMAKE_CXX_COMPILER=$CXX_LIB ../"
    else
        check_return_code "cmake ../"
    fi
    check_return_code "make"
    check_return_code  "cp $PWD/libcontainers.so  $PLACE_LIB/libcontainers.so"
    if [[ -d $PLACE_HEADERS/$COMMONDIR ]]; then
        check_return_code "rm -rf $PLACE_HEADERS/$COMMONDIR"
    fi
    check_return_code "mkdir $PLACE_HEADERS/$COMMONDIR"
    for lib in ${CONTAINERS[@]}; do
        echo "Create $lib directory."
        check_return_code "mkdir $PLACE_HEADERS/$COMMONDIR/$lib"
        check_return_code "cp ../include/${SOURCES[$lib]}.h $PLACE_HEADERS/$COMMONDIR/$lib/"
    done
    check_return_code "cd ../"
    check_return_code "rm -rf build_lib"
}

usage() {
    echo "Usage: ./build_library.sh /path/to/library /path/to/includes
Options:
  --help            Display this information.

Build options:
  -g++              A special path to the C++ compiler.
  --inplace/-inp        Create a library in the same directory.
Paths:
  /path/to/library  Create a library in the special directory.
  /path/to/includes  Create headers in the special directory."
}


if [[ $# -eq 1 ]]; then
    if [[ $1 == "--help" ]]; then
        usage
        exit 0 
    elif [[ $1 == "--inplace" ]]; then
        PLACE_LIB=$(realpath $PWD)
        PLACE_HEADERS=$(realpath $PWD)
        
        build_library
    else 
        echo "$1: unknown option."
    fi
elif [[ $# -ge 2 ]]; then
    if ! [[ $1 =~ ^-[a-zA-Z\+]+=* ]]; then
        if [[ $1 ]] && [[ -d $1 ]]; then
            PLACE_LIB=$(realpath $1)
        else
            echo "The $1 directory does not exists."
            exit 1;
        fi
        if [[ $2 ]] && [[ -d $2 ]]; then
            PLACE_HEADERS=$(realpath $2)
        else
            echo "The $2 directory does not exists."
            exit 1;
        fi
        if [[ $# -eq 2 ]]; then
            build_library
        else
            for arg in "$@"; do
            case $arg in
                -g++=*)
                    CXX_LIB="${arg#*=}"
                    shift
                    ;;
                -inp)
                    PLACE_LIB=$(realpath $PWD)
                    PLACE_HEADERS=$(realpath $PWD)
                    shift
                    ;;
                --help)
                    usage
                    exit 0
                    ;;
                -*)
                    echo "Unknown option."
                    exit 128
                    ;;
                *)
                    ;;
            esac
            done

            build_library
        fi
    else
        echo "You need set the path to the library and set the path to the headers."
        exit 1;
    fi
else
    echo "No options found. --help - for help."
fi

unset CXX_LIB
unset PLACE_LIB
unset PLACE_HEADERS
unset SOURCES
unset COMMONDIR
unset CONTAINERS

