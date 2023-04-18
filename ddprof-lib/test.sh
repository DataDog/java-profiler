#!/usr/bin/env bash

set -e

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

CMAKE=$(which cmake)
if [ -z "$CMAKE" ]; then
  echo "[ERROR] Please, install cmake"
  exit 1
fi

function build_and_test() {
  BUILD_TYPE=$1
  TARGET=${HERE}/build_${BUILD_TYPE}
  cd ${HERE}/src/test
  cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -Wno-dev -S . -B ${TARGET}
  cmake --build ${TARGET}
  cd ${TARGET} && ctest
}

if [ -z "${BUILD_TYPE}" ]; then
  BUILD_TYPE="Debug"
fi

build_and_test ${BUILD_TYPE}
