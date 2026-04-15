#!/usr/bin/env bash
# Reproducer harness for the java-profiler + wasmtime hang.
#
# Run on an x86_64 Linux machine (with or without nohup):
#   nohup ./run-reproducer.sh > reproducer.log 2>&1 &
#
# Exit codes from the JVM:
#   42  — hang detected (worker thread stalled); thread dump printed to stdout.
#   0   — clean run (all workers made progress); retried automatically.
#   other — unexpected crash; stopped immediately.

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

attempt=0
start_epoch=$(date +%s)

while true; do
  attempt=$((attempt + 1))
  now=$(date +%s)
  elapsed=$((now - start_epoch))
  echo "[run $attempt | ${elapsed}s] launching JVM"

  "$JAVA" -jar "$JAR"

  exit_code=$?

  if [[ $exit_code -eq 42 ]]; then
    echo "[run $attempt] HANG DETECTED (exit 42). Stopping."
    echo "Thread dump was printed to stdout above."
    exit 0
  elif [[ $exit_code -ne 0 ]]; then
    echo "[run $attempt] JVM exited with unexpected code $exit_code. Stopping."
    exit 0
  fi

  echo "[run $attempt] JVM exited cleanly — retrying."
done
