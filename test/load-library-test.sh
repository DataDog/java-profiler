#!/bin/bash

set -e  # exit on any failure
set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

(
  cd $(dirname $0)

  if [ "LoadLibraryTest.class" -ot "LoadLibraryTest.java" ]; then
     ${JAVA_HOME}/bin/javac LoadLibraryTest.java
  fi

  JFR_FILENAME=/tmp/java-load-library.jfr
  JSON_FILENAME="${JFR_FILENAME}.json"
  ${JAVA_HOME}/bin/java -agentpath:../build/libjavaProfiler.so=start,cpu=1ms,jfr,file=$JFR_FILENAME LoadLibraryTest &

  JAVAPID=$!

  function cleanup {
    kill $JAVAPID 2>/dev/null || true
  }

  trap cleanup EXIT

  sleep 5     # allow the Java runtime to initialize
  kill $JAVAPID

  $JAVA_HOME/bin/jfr print --stack-depth 32 --json $JFR_FILENAME | grep 'Java_sun_management' > $JSON_FILENAME
  if [ ! -s "$JSON_FILENAME" ]; then
    echo "Expecting datadog.ExecutionSample events with frames pointing to Java_sun_management function!"
    exit 1
  fi
)
