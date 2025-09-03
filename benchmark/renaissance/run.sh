#!/usr/bin/env bash
set -eu

source "${UTILS_DIR}/update-java-version.sh" 17

function message() {
  echo "$(date +"%T"): $1"
}

run_benchmark() {
  local type=$1

  message "renaissance benchmark: ${type} started"

  # export the benchmark
  export BENCHMARK="${type}"

  # create output folder for the test
  export OUTPUT_DIR="${REPORTS_DIR}/renaissance/${type}"
  mkdir -p "${OUTPUT_DIR}"

  # substitute environment variables in the json file
  benchmark=$(mktemp)
  # shellcheck disable=SC2016
  envsubst "$(printf '${%s} ' $(env | cut -d'=' -f1))" <benchmark.json >"${benchmark}"

  # run the sirun test
  sirun "${benchmark}" &>"${OUTPUT_DIR}/${type}.json"

  message "renaissance benchmark: ${type} finished"
}

if [ "$#" == '2' ]; then
  run_benchmark "$2"
else
  for benchmark in akka-uct neo4j-analytics ; do
    run_benchmark "${benchmark}"
  done
fi

