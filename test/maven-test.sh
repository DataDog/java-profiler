#!/bin/bash

set -e  # exit on any failure
set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

(
  cd $HERE/..

  if [ -f build/libjavaProfiler.so ]; then
    SKIP_ARG="-Dskip-native"
  fi
  mvn $SKIP_ARG -B test
)
