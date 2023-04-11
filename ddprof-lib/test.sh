#!/usr/bin/env bash

set -e

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

CMAKE=$(which cmake)
if [ -z "$CMAKE" ]; then
  echo "[ERROR] Please, install cmake"
  exit 1
fi

TARGET=${HERE}/build/cmake
cd ${HERE}/src/test
cmake -Wno-dev -S . -B ${TARGET}
cmake --build ${TARGET}
cd ${TARGET} && ctest