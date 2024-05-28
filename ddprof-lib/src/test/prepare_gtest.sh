#!/usr/bin/env bash
set -eo pipefail

CONFIG_NAME=$1
GTEST_DIR=$2

CFG_DIR="${GTEST_DIR}/configs/${CONFIG_NAME}"

echo "Starting script with CONFIG_NAME=${CONFIG_NAME} and GTEST_DIR=${GTEST_DIR}"

if [ ! -d "${CFG_DIR}" ]; then
    mkdir -p "${CFG_DIR}"
fi
cd "${CFG_DIR}"
echo "Running cmake in ${CFG_DIR}"
cmake ${GTEST_DIR}/../../../src/test -DCMAKE_BUILD_TYPE=${CONFIG_NAME}
if [ $? -ne 0 ]; then
    echo "cmake failed"
    exit 1
fi
echo "Running make in ${CFG_DIR}"
make
if [ $? -ne 0 ]; then
    echo "make failed"
    exit 1
fi
echo "Build completed successfully."
