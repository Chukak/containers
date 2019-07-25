FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y gcc-7 g++-7 build-essential cmake lcov libboost-all-dev python3 python3-dev

ADD . /containers

RUN mkdir /containers/build-containers-tests && \
    cd /containers/build-containers-tests && \
    cmake ../tests/ && \
    make

RUN mkdir /containers/build-containers-tests-coverage && \
    cd /containers/build-containers-tests-coverage && \
    cmake -DCMAKE_BUILD_TYPE='Coverage' ../tests/ && \
    make

RUN mkdir /containers/build-containers-performance && \
    cd /containers/build-containers-performance && \
    cmake ../tests/performance && \
    make

RUN mkdir /containers/build-containers-python-module && \
    cd /containers/build-containers-python-module && \
    cmake -DPY_MODULE_WRAP_METHODS=1 ../python/ && \
    make && \
    cp ./containers.so ../python/tests/containers.so

RUN mkdir /containers/build-containers-lib
