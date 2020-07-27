FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y gcc-7 g++-7 build-essential cmake lcov libboost-all-dev python3 python3-dev

ADD . /containers

RUN mkdir /containers/build-containers && \
    cd /containers/build-containers && \
    cmake -DBUILD_TESTS=1 -DBUILD_ASAN=1 -DBUILD_PYTHON=1 -DPY_MODULE_WRAP_METHODS=1 -DCMAKE_BUILD_TYPE="Coverage" ../ && \
    make

RUN mkdir /containers/build-containers-lib
