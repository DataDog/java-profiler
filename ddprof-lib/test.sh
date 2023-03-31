#!/usr/bin/env bash

set -e

CMAKE=$(which cmake)
if [ -z "$CMAKE" ]; then
  echo "[ERROR] Please, install cmake"
  exit 1
fi

cd src/test
cmake  -Wno-dev -S . -B build
cmake --build build
cd build && ctest