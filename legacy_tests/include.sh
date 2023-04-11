#! /bin/bash

function collapseJfr() {
    local event=$1
    local input=$2
    local output=$3

    local json_out="${input}.json"
    $JAVA_HOME/bin/jfr print --events $1 --stack-depth 10 --json $input > $json_out
    jq -r '[.recording.events[]?.values.stackTrace | select(.truncated == false) | .frames | map("\(.method.type.name).\(.method.name)") | reverse | join(";")]' $json_out | grep -v '.no_Java_frame' | sed 's/"//g' | sed 's/,/ /g' > $output
}

  function assert_string() {
    if ! grep -q "$1" $2; then
      echo "Required text "$1" was not found in $2"
      exit 1
    fi
  }
