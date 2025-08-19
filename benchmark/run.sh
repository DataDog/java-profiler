#!/usr/bin/env bash
set -eu

readonly SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
readonly INITIAL_DIR="$(pwd)"
export PROFILER="${SCRIPT_DIR}/profiler/libjavaProfiler.so"

cd "${SCRIPT_DIR}"

# Build container image
echo "Building base image ..."
docker build \
  -t profiler-java/benchmark \
  .

# Find or rebuild profiler to be used in the benchmarks
if [[ ! -f "${PROFILER}" ]]; then
  mkdir -p "${SCRIPT_DIR}/tracer"
  cd "${SCRIPT_DIR}/.."
  readonly PROFILER_VERSION=$(./gradlew properties -q | grep "version:" | awk '{print $2}')
  readonly PROFILER_COMPILED="${SCRIPT_DIR}/../java-profiler//ddprof-lib/build/lib/main/release/linux/x64/libjavaProfiler.so"
  if [ ! -f "${TRACER_COMPILED}" ]; then
    echo "Profiler not found, starting gradle compile ..."
    ./gradlew assemble
  fi
  cp "${PROFILER_COMPILED}" "${PROFILER}"
  cd "${SCRIPT_DIR}"
fi

# Trigger benchmarks
echo "Running benchmarks ..."
docker run --rm \
  -v "${HOME}/.gradle":/home/benchmark/.gradle:delegated \
  -v "${PWD}/..":/tracer:delegated \
  -w /profiler/benchmark \
  -e GRADLE_OPTS="-Dorg.gradle.daemon=false" \
  --entrypoint=./benchmarks.sh \
  --name java-profiler-benchmark \
  --cap-add SYS_ADMIN \
  java-profiler/benchmark \
  "$@"

cd "${INITIAL_DIR}"
