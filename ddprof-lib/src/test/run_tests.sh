#!/usr/bin/env bash

set -euo pipefail
set -x

CONFIG_NAME=$1
PROJECT_DIR=$2
GTEST_DIR=$3
shift
shift
shift
ARGS=$@

TMPDIR="${TMPDIR:-$(dirname $(mktemp))}"

function build_test() {
  NAME=$1
  echo "Building test ${NAME}..."
  # shellcheck disable=SC2038
  files=$(find ${PROJECT_DIR}/build/obj/main/${CONFIG_NAME} -name "*.o" -print | tr '\n' ' ')
  libdir=${GTEST_DIR}/configs/${CONFIG_NAME}/lib
  g++ -std=c++11 -o ${TMPDIR}/${NAME}_${CONFIG_NAME} ${PROJECT_DIR}/src/test/cpp/${NAME}.cpp \
        -I${GTEST_DIR}/googletest/include -I${GTEST_DIR}/googlemock/include \
        -I${PROJECT_DIR}/src/main/cpp ${libdir}/libgtest.a \
        ${libdir}/libgtest_main.a ${libdir}/libgmock.a \
        ${libdir}/libgmock_main.a $files -lpthread -lm -ldl ${ARGS[@]}  -pthread
}

function build_and_run() {
    NAME=$1
    build_test ${NAME}
    echo "Running test ${NAME}..."
    ${TMPDIR}/${NAME}_${CONFIG_NAME}
}

build_test ddprof_ut
build_test demangle_ut

