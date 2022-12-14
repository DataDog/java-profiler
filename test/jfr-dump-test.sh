#!/bin/bash

set -e  # exit on any failure
# set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

function assert_string() {
    if ! echo $1 | grep -q "$2"; then
        exit 1
    fi
}

# test in-process API
(
    echo "=== dump [internal API]"
    cd $(dirname $0)

    if [ "Target.class" -ot "Target.java" ]; then
        ${JAVA_HOME}/bin/javac -cp ../build/java-profiler.jar Target.java
    fi

    FILENAME=/tmp/dump_test.jfr
    DUMP_1=/tmp/dump_test_1.jfr
    DUMP_1_SECS=1

    rm -f $FILENAME
    rm -f $DUMP_1

    ${JAVA_HOME}/bin/java -cp .:../build/java-profiler.jar -agentpath:../build/libjavaProfiler.so=start,wall=500ms,jfr,file=$FILENAME Target $DUMP_1 $DUMP_1_SECS &
    JAVAPID=$!

    function cleanup {
        kill $JAVAPID 2>/dev/null || true
    }

    trap cleanup EXIT

    sleep $DUMP_1_SECS
    # wait for the internal dump

    if [ -z "$(${JAVA_HOME}/bin/jps | grep $PID)" ]; then
        echo "Test application died. Check the output."
        exit 1
    fi

    kill $JAVAPID

    assert_string "$(jfr summary $DUMP_1 | grep Duration)" "Duration: $DUMP_1_SECS s"

)
