#!/usr/bin/env bash
set -eu

echo "Running benchmarks ..."

readonly SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
export PROFILER_DIR="${SCRIPT_DIR}/.."
export REPORTS_DIR="${SCRIPT_DIR}/reports"
export UTILS_DIR="${SCRIPT_DIR}/utils"
export SHELL_UTILS_DIR="${UTILS_DIR}/shell"
export K6_UTILS_DIR="${UTILS_DIR}/k6"
export PROFILER="${SCRIPT_DIR}/profiler/libjavaProfiler.so"

run_benchmarks() {
  local type=$1
  if [[ -d "${type}" ]] && [[ -f "${type}/run.sh" ]]; then
    cd "${type}"
    ./run.sh "$@"
    cd "${SCRIPT_DIR}"
  fi
}

# Find or rebuild profiler to be used in the benchmarks
if [[ ! -f "${PROFILER}" ]]; then
  mkdir -p "${SCRIPT_DIR}/profiler"
  cd "${PROFILER_DIR}"
  ARCH=$(uname -p)
  if [ $ARCH eq "x86_64" ]; then
    ARCH="x64"
  fi

  readonly PROFILER_VERSION=$(./gradlew properties -q | grep "version:" | awk '{print $2}')
  readonly PROFILER_COMPILED="${SCRIPT_DIR}/../ddprof-lib/build/lib/main/release/linux/${ARCH}/libjavaProfiler.so"
  if [[ ! -f "${PROFILER_COMPILED}" ]]; then
    echo "Profiler not found, starting gradle compile ..."
    ./gradlew assemble
  fi
  cp "${PROFILER_COMPILED}" "${PROFILER}"
  cd "${SCRIPT_DIR}"
fi

if [[ "$#" == '0' ]]; then
  for type in 'dacapo'; do
    run_benchmarks "$type"
  done
else
  run_benchmarks "$@"
fi
