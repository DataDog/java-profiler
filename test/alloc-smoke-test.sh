#!/bin/bash

set -e  # exit on any failure
set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

(
  cd $(dirname $0)

  if [ "AllocatingTarget.class" -ot "AllocatingTarget.java" ]; then
     ${JAVA_HOME}/bin/javac AllocatingTarget.java
  fi

  FILENAME=/tmp/alloc-smoke-test.jfr
  ${JAVA_HOME}/bin/java -cp .:../build/java-profiler.jar -agentpath:../build/debug/libjavaProfiler.so=start,filter,alloc,context,jfr,file=$FILENAME AllocatingTarget &

  JAVAPID=$!

  function cleanup {
    kill $JAVAPID 2>/dev/null || true
  }

  trap cleanup EXIT

  sleep 5
  kill $JAVAPID

  if [ -f $FILENAME ]; then
    if [ -z "$($JAVA_HOME/bin/jfr summary $FILENAME | grep 'datadog.ObjectAllocationInNewTLAB')" ]; then
      echo "Expecting 'datadog.ObjectAllocationInNewTLAB' events!"
      exit 1
    fi
  else
    echo "Missing JFR recording!"
    exit 1
  fi
)
