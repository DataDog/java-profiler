#!/usr/bin/env bash
# Reproducer harness for the java-profiler + wasmtime crash.
#
# Run under nohup on an x86_64 Linux machine:
#   nohup ./run-reproducer.sh > reproducer.log 2>&1 &
#
# Stops on the first JVM crash (non-zero exit code).
# Artifacts: hs_err_<pid>.log and core.<pid> in the working directory.

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JAR="$SCRIPT_DIR/build/libs/wasmtime-reproducer.jar"

# Java 26 — override with JAVA_HOME if needed.
JAVA="${JAVA_HOME:-/usr/lib/jvm/java-26-openjdk-amd64}/bin/java"

if [[ ! -f "$JAR" ]]; then
  echo "ERROR: $JAR not found. Build first: ./gradlew :wasmtime-reproducer:jar" >&2
  exit 1
fi

if [[ ! -x "$JAVA" ]]; then
  echo "ERROR: Java executable not found at $JAVA. Set JAVA_HOME to a Java 26 installation." >&2
  exit 1
fi

# Enable core dumps in this shell. Fail fast if the kernel disallows it
# (e.g. container with hard limit 0) so we don't silently lose core files.
ulimit -c unlimited || { echo "ERROR: ulimit -c unlimited failed — core dumps will not be generated." >&2; exit 1; }

attempt=0
start_epoch=$(date +%s)

while true; do
  attempt=$((attempt + 1))
  now=$(date +%s)
  elapsed=$((now - start_epoch))
  echo "[run $attempt | ${elapsed}s] launching JVM"

  "$JAVA" \
    -XX:+CreateCoredumpOnCrash \
    "-XX:ErrorFile=$SCRIPT_DIR/hs_err_%p.log" \
    -jar "$JAR"

  exit_code=$?

  if [[ $exit_code -ne 0 ]]; then
    echo "[run $attempt] JVM exited with code $exit_code — crash detected. Stopping."
    echo "Check $SCRIPT_DIR/hs_err_*.log and core.* for diagnostics."
    exit 0
  fi

  echo "[run $attempt] JVM exited cleanly — retrying."
done
