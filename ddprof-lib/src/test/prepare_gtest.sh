#!/usr/bin/env bash
# set -x
CONFIG_NAME=$1
GTEST_DIR=$2

CFG_DIR="${GTEST_DIR}"/configs/"${CONFIG_NAME}"
if [ ! -d "${CFG_DIR}/lib" ]; then
    mkdir -p $CFG_DIR
    cd "${GTEST_DIR}"/configs/"${CONFIG_NAME}"
    cmake ../.. 
    make
fi
