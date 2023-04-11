#!/usr/bin/env bash

set -e

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

CMAKE=$(which cmake)
if [ -z "$CMAKE" ]; then
  echo "[ERROR] Please, install cmake"
  exit 1
fi

cd ${HERE}/src/test
cmake -Wno-dev -S . -B build
cmake --build build
cd build && ctest