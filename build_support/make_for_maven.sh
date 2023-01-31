#!/bin/bash

set -e

ARG=$1
if [ "${ARG:-no}" != "no" ]; then
    echo "Skipping native build"
    exit 0
fi

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $HERE/..
pwd
OS=$(uname)
CPU=$(uname -m)
ARCH=
case $OS in
    Linux) ARCH=linux;;
    Darwin) ARCH=macos;;
    *) echo "Unsupported OS: $OS"; exit 1;;
esac

case $CPU in
    x86_64) ARCH+="-x64";;
    arm64|aarch64) ARCH+="-arm64";;
    *) echo "Unsupported CPU: $CPU"; exit 1;;
esac

if [[ $(ldd /bin/ls) =~ .*musl.* ]]; then
    ARCH+="-musl"
fi

rm -rf build

make all

TARGET_DIR=${HERE}/../target/classes/META-INF/native/$ARCH
mkdir -p $TARGET_DIR
cp build/libjavaProfiler.so ${TARGET_DIR}/
