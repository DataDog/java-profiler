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

  if [ "MemLeakTarget.class" -ot "MemLeakTarget.java" ]; then
     ${JAVA_HOME}/bin/javac MemLeakTarget.java
  fi

  JFR_FILENAME=/tmp/java-memleak-smoke.jfr
  JSON_FILENAME="${JFR_FILENAME}.json"
  COLLAPSED_OUT="${JFR_FILENAME}.txt"

  # cleanup first
  rm -f $JFR_FILENAME
  rm -f $JSON_FILENAME
  rm -f $COLLAPSED_OUT

  ${JAVA_HOME}/bin/java -agentpath:../build/libjavaProfiler.so=start,memleak=524288,cstack=no,jfr,file=$JFR_FILENAME MemLeakTarget &

  JAVAPID=$!

  function cleanup {
    kill $JAVAPID 2>/dev/null || true
  }

  trap cleanup EXIT

  sleep 5     # allow the Java runtime to initialize
  kill $JAVAPID
  $JAVA_HOME/bin/jfr print --events datadog.HeapLiveObject --json $JFR_FILENAME > $JSON_FILENAME
  jq '.recording | try .events[]?.values | select((.objectClass.name == "[Ljava.lang.Integer;") or (.objectClass.name == "[I")) | .stackTrace.frames[]? | select((.method.type.name == "MemLeakTarget") and (.method.name == "allocate"))' $JSON_FILENAME > $COLLAPSED_OUT

  if [ ! -s "$COLLAPSED_OUT" ]; then
    echo "No live samples for Integer[] and int[] were found!"
    exit 1
  fi
)
