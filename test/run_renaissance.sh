#!/bin/bash

set -e  # exit on any failure
set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

WGET=$(which wget)
if [ -z "$WGET" ]; then
  echo "Missing wget"
  exit 1
fi

function help() {
  echo "Usage: run_renaissance.sh -pa <profiler arguments> <benchmark arguments>"
}

if [ $# -eq 0 ]; then
  help
  exit 1
fi

while [ $# -gt 1 ]; do
  KEY=$1
  case "$KEY" in
    "-pa")
      shift
      PROFILER_ARGS=$1
      ;;
    *)
      if [ -z "$PROFILER_ARGS" ]; then
         help
         exit 1
      fi
      BENCHMARK_ARGS=("$@")
      break
      ;;
  esac
  shift
done

mkdir -p .resources
(cd .resources && if [ ! -e renaissance.jar ]; then wget https://github.com/renaissance-benchmarks/renaissance/releases/download/v0.14.0/renaissance-mit-0.14.0.jar -nv -O renaissance.jar; fi)

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BASEDIR="${HERE}/.."

AGENT_PATH=${BASEDIR}/build/libjavaProfiler.so
if [ ! -f "$AGENT_PATH" ]; then
  # we are running in CI - the library will be in a different place
  AGENT_PATH=${BASEDIR}/target/classes/META-INF/native/linux-x64/libjavaProfiler.so
fi
echo "${JAVA_HOME}/bin/java -agentpath:${AGENT_PATH}=start,${PROFILER_ARGS} -jar .resources/renaissance.jar ${BENCHMARK_ARGS[@]}"
${JAVA_HOME}/bin/java -agentpath:${AGENT_PATH}=start,${PROFILER_ARGS} -jar .resources/renaissance.jar "${BENCHMARK_ARGS[@]}"