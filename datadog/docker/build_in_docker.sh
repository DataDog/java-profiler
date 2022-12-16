#! /bin/bash
set -euo pipefail

export PROFILER_VERSION=$1
FORCE_TESTS=$2
FORCE_CPPCHECK=$3

cd /data/src/java-profiler
# make sure all previously compiled classes are gone to prevent any bytecode incompatibility
find . -name '*.class' | xargs -I {} rm -f {} || true
# build the library

find . -name '*.class' | xargs -I {} rm -f {}
CMD=""

if [ "yes" = "$FORCE_CPPCHECK" ]; then
  CMD="cppcheck"
fi
if [ "yes" = "$FORCE_TESTS" ]; then
  CMD+=" test"
fi
if [ -z "$CMD" ]; then
  CMD="all"
fi
make clean $CMD
cp build/libjavaProfiler.so /data/libs/libjavaProfiler.so