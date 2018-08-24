#!/bin/bash

CC=""
CXX=""
MAKE=""
PLACE=""
COMMONDIR="containers"
CONTAINERS=(queue stack sorted_list bst counter)
declare -A SOURCES
SOURCES=([queue]=queue [stack]=stack [sorted_list]=sorted_list [bst]=bst [counter]=counter)
CC_FLAGS="-lstd++ -g -Wall -Werror -std=c++14"
CXX_FLAGS="-g -Wall -Werror -std=c++14"
FLAGS=""


config_gxx() {
    echo "Checking g++."
    dpkg -s g++ &> /dev/null
    if [[ $? -ne 0 ]]; then
        echo "Package `g++` not found."
        exit 1;
    else
        gxx_version="$(g++ -dumpversion)"
        regex='^[5-9]{1}\.[0-9]+\.[0-9]+$'
        if [[ $gxx_version =~ $regex ]]; then
            CXX="g++"
        else
            echo "You need 'g++' 5 version and newer."
            exit 1
        fi
        unset gxx_version
        unset regex
    fi
}

config_make() {
    echo "Checking make."
    dpkg -s make &> /dev/null
    if [[ $? -ne 0 ]]; then
        echo "Package `make` not found."
        exit 1;
    else
        make_version="$(make -v | grep "^GNU Make [4-9]\.[0-9]*")"
        if [[ $make_version ]]; then
            MAKE="make"
        else
            echo "You need 'make' 4 version and newer."
            exit 1
        fi
        unset make_version
    fi
}

build_library() {
    if ! [[ $CXX ]] && ! [[ $CC ]]; then
        config_gxx
    fi

    if ! [[ $MAKE ]]; then
        config_make
    fi
    
    compiler=""
    if [[ $CC ]]; then
        compiler=$CC
    elif [[ $CXX ]]; then
       compiler=$CXX
    fi
    
    if ! [[ $FLAGS ]]; then
        if [[ $compiler == $CXX ]]; then
            FLAGS=$CXX_FLAGS
        else
            FLAGS=$CC_FLAGS
        fi
    fi

    if [[ $MAKE ]] && [[ $compiler ]]; then
        if [[ $PLACE ]]; then 
            COMMONDIR=$PLACE/$COMMONDIR
        fi
        if [[ -d $COMMONDIR ]]; then
            rm -rf $COMMONDIR
            if [[ $? -ne 0 ]]; then
                echo "Can not delete an existing directory $COMMONDIR."
                exit 1
            fi
        fi
        mkdir $COMMONDIR
        if [[ $? -ne 0 ]]; then
            echo "Can not create $COMMONDIR."
            exit 1
        fi
        echo "Current compiler: $compiler ."
        echo "Flags: $FLAGS ."
        if [[ $compiler ]]; then
            for lib in ${CONTAINERS[@]}; do
                echo "Create $lib directory."
                mkdir $COMMONDIR/$lib
                if [[ $? -ne 0 ]]; then
                    echo "Can not create $COMMONDIR/$lib."
                    exit 1
                fi
                echo "Building a ${SOURCES[$lib]} library."
                $compiler $FLAGS -fPIC -c -o $COMMONDIR/$lib/${SOURCES[$lib]}.o src/${SOURCES[$lib]}.cpp
                $compiler $FLAGS -fPIC -o $COMMONDIR/$lib/${SOURCES[$lib]}.so $COMMONDIR/$lib/${SOURCES[$lib]}.o -shared 
                rm $COMMONDIR/$lib/${SOURCES[$lib]}.o   
                cp src/${SOURCES[$lib]}.h $COMMONDIR/$lib/
            done
        else
            echo "The compiler was not found. Check your -gcc or -g++ options."
        fi
    else
        echo "Unknown error."
        exit 128
    fi
    unset compiler
}

usage() {
    echo "Usage: ./build_library.sh [options] /path/to/library
Options:
  --help            Display this information.

Build options:
  -make             Make special path.
  -gcc              A special path to the C compiler.
  -g++              A special path to the C++ compiler.
  -flags            Flags of compiler, for example: \" -g -Werror \".
                    Also if you compile with gcc, use \" -lstdc++ -std=c++xx \"
                    flags.
  --inplace         Create a library in the same directory.
  /path/to/library  Create a library in the special directory."
}


if [[ $# -eq 1 ]]; then
    if [[ $1 == "--help" ]]; then
        usage
        exit 0
    fi
    
    if ! [[ $1 =~ ^-[a-zA-Z\+]+=* ]]; then
        if [[ $1 == "--inplace" ]]; then
            PLACE=$PWD
        elif [[ $1 ]] && [[ -d $1 ]]; then
            PLACE=$1
        else
            echo "The $1 directory does not exists."
            exit 1;
        fi

        build_library
    else
        echo "You need to the path to the library or --inplace option."
        exit 1;
    fi

elif [[ $# -ge 1 ]]; then
    for arg in "$@"; do
        case $arg in
            -make=*)
                MAKE="${arg#*=}"
                shift
                ;;
            -g++=*)
                CXX="${arg#*=}"
                shift
                ;;
            -gcc=*)
                CC="${arg#*=}"
                shift
                ;;
            -flags=*)
                FLAGS="${arg#*=}"
                shift
                ;;
            --inplace)
                PLACE=$PWD
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
    if ! [[ $PLACE=="" ]]; then 
        if [[ $arg =~ --* ]] || [[ $arg =~ -*=* ]]; then
            echo "You need to the path to the library or --inplace option."
            exit 1
        elif ! [[ -d $arg ]]; then
            echo "The $arg directory does not exists."
            exit 1
        else
            PLACE=$arg
        fi
    fi

    build_library

else
    echo "No options found. --help - for help."
fi

unset CC
unset CXX
unset MAKE
unset PLACE
unset COMMONDIR
unset CONTAINERS
unset SOURCES
unset CXX_FLAGS
unset CC_FLAGS
unset FLAGS
