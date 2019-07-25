#!/bin/bash

if [[ "$(docker images -q docker-containers-test 2> /dev/null)" == "" ]]; then
    docker build -t docker-containers-test .
fi
docker-compose build
docker-compose up > /dev/null
docker-compose logs containers-tests
docker-compose logs containers-tests-coverage
docker-compose logs containers-performance
docker-compose logs containers-python-module
docker-compose logs containers-build-library
