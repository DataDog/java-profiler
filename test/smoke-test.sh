#!/bin/bash

set -e  # exit on any failure
set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

(
  cd $(dirname $0)
  source include.sh

  if [ "Target.class" -ot "Target.java" ]; then
     ${JAVA_HOME}/bin/javac -cp ../build/java-profiler.jar Target.java
  fi

  FILENAME=/tmp/java-smoke.jfr
  COLLAPSED_OUT=/tmp/smoke-test.txt

  # cleanup first
  rm -f $FILENAME
  rm -f $COLLAPSED_OUT

  ${JAVA_HOME}/bin/java -agentpath:../build/libjavaProfiler.so=start,cpu=1ms,jfr,cstack=no,file=$FILENAME Target &

  JAVAPID=$!

  function cleanup {
    kill $JAVAPID 2>/dev/null || true
  }

  trap cleanup EXIT

  sleep 1     # allow the Java runtime to initialize
  kill $JAVAPID
  
  collapseJfr datadog.ExecutionSample $FILENAME $COLLAPSED_OUT
  
  assert_string "Target.main;Target.method1 " $COLLAPSED_OUT
  assert_string "Target.main;Target.method2 " $COLLAPSED_OUT
  assert_string "Target.main;Target.method3;java/io/File" $COLLAPSED_OUT
)
