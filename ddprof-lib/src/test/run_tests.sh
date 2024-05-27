#!/usr/bin/env bash

PROJECT_DIR=$1
CONFIG_NAME=$2
GTEST_DIR=$3

function build_test() {
  NAME=$1
  echo "Building test ${NAME}..."
  # shellcheck disable=SC2038
  find ${PROJECT_DIR}/build/obj/main/${CONFIG_NAME} -name "*.o" |
    xargs g++ -std=c++11 -o ${TMPDIR}/${NAME} ${PROJECT_DIR}/src/test/cpp/${NAME}.cpp \
              -I${GTEST_DIR}/googletest/include -I${GTEST_DIR}/googlemock/include \
              -I${PROJECT_DIR}/src/main/cpp ${GTEST_DIR}/lib/libgtest.a \
              ${GTEST_DIR}/lib/libgtest_main.a ${GTEST_DIR}/lib/libgmock.a \
              ${GTEST_DIR}/lib/libgmock_main.a -pthread
}

function build_and_run() {
    NAME=$1
    build_test ${NAME}
    echo "Running test ${NAME}..."
    ${TMPDIR}/${NAME}
}

build_and_run ddprof_ut
build_and_run demangle_ut

