#!/bin/bash

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

(
    cd $HERE/..
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
        arm64) ARCH+="-arm64";;
        *) echo "Unsupported CPU: $CPU"; exit 1;;
    esac

    if [[ $(ldd /bin/ls) =~ .*musl.* ]]; then
        ARCH+="-musl"
    fi
    
    make clean all

    TARGET_DIR=src/main/resources/native-libs/$ARCH
    mkdir -p $TARGET_DIR
    cp build/libjavaProfiler.so ${TARGET_DIR}/
)
