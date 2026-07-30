#!/bin/bash
# Runs one native-memory sweep point: mode, N, duration(ms).
#
# Usage: run_sweep.sh <threads|traces|classes|allocs> <N> <duration_ms> [interval]
#
# threads/traces/classes drive the wall-clock engine (interval is the wall=
# sampling period, e.g. ~5ms). allocs drives the allocation-sampling engine
# instead (interval is the memory= sampling period in bytes, e.g. 1024) --
# it isolates allocation-sampler-driven calltrace/dictionary growth from the
# wall-clock reflection calls the other three modes use.
#
# For traces/classes/allocs, pre-generates and compiles sources with an
# EXTERNAL (unprofiled) javac process first, so the profiled JVM only ever
# loads precompiled .class files -- doing this in-process would load the
# compiler's own classes into the profiled JVM and swamp the intended
# N-classes signal.
#
# Samples RSS while the JVM runs, then extracts native_mem_* counters from
# the resulting JFR file. Prints one CSV line to stdout:
#   mode,n,maxrss_kb,live_total,avg_total,max_total,max_observed_total,
#   calltrace,dictionary,thread_filter,thread_local,native_symbols,
#   line_tables,jfr_buffers,perf,misc
#
# Environment overrides (auto-detected if unset):
#   DDPROF_LIB       path to the built libjavaProfiler.so/.dylib
#   DDPROF_JAVA_API  path to ddprof-lib's compiled java classes (JavaProfiler.class)
#   JAVA_BIN, JAVAC_BIN, JFR_BIN  default to `java`/`javac`/`jfr` on PATH
#   WORKDIR          scratch directory, default /tmp/memsweep
set -u
MODE="$1"
N="$2"
DURATION_MS="$3"
if [ "$MODE" = "allocs" ]; then
  INTERVAL="${4:-1024}"
  ENGINE_ARG="memory=${INTERVAL}:a"
else
  INTERVAL="${4:-~5ms}"
  ENGINE_ARG="wall=${INTERVAL}"
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
# `javac`/`jfr` aren't always on PATH even when `java` is (e.g. macOS's
# /usr/bin/java shim); fall back to deriving them from java.home.
JAVA_HOME_DIR="$("$JAVA_BIN" -XshowSettings:properties -version 2>&1 | awk -F'= ' '/java.home/{print $2}')"
JAVAC_BIN="${JAVAC_BIN:-$(command -v javac || echo "$JAVA_HOME_DIR/bin/javac")}"
JFR_BIN="${JFR_BIN:-$(command -v jfr || echo "$JAVA_HOME_DIR/bin/jfr")}"
WORKDIR="${WORKDIR:-/tmp/memsweep}"

if [ -z "$DDPROF_LIB" ] || [ ! -f "$DDPROF_LIB" ]; then
  echo "ERROR: could not find libjavaProfiler under $REPO_ROOT/ddprof-lib/build/lib/main/release." >&2
  echo "Build it first (./gradlew assembleRelease) or set DDPROF_LIB explicitly." >&2
  exit 1
fi

CLASSDIR="$WORKDIR/classes"
mkdir -p "$CLASSDIR" "$WORKDIR/gen" "$WORKDIR/out"
if [ ! -f "$CLASSDIR/MemSweepMain.class" ]; then
  "$JAVAC_BIN" -cp "$DDPROF_JAVA_API" -d "$CLASSDIR" "$SCRIPT_DIR/src/MemSweepMain.java" "$SCRIPT_DIR/src/GenSources.java"
fi

TAG="${MODE}_${N}"
GENDIR="$WORKDIR/gen/${TAG}"
OUTJFR="$WORKDIR/out/${TAG}.jfr"
mkdir -p "$GENDIR"

if [ "$MODE" = "traces" ] || [ "$MODE" = "classes" ] || [ "$MODE" = "allocs" ]; then
  "$JAVA_BIN" -cp "$CLASSDIR" GenSources "$MODE" "$N" "$GENDIR" >"$WORKDIR/out/${TAG}.gen.log" 2>&1
  find "$GENDIR" -name "*.java" > "$GENDIR.filelist"
  "$JAVAC_BIN" -d "$GENDIR" "@${GENDIR}.filelist" >>"$WORKDIR/out/${TAG}.gen.log" 2>&1
fi

"$JAVA_BIN" -agentpath:${DDPROF_LIB}=start,${ENGINE_ARG},jfr,file=${OUTJFR},cstack=fp \
  -Dmemsweep.libpath="$DDPROF_LIB" \
  -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain "$MODE" "$N" "$DURATION_MS" "$GENDIR" \
  > "$WORKDIR/out/${TAG}.stdout" 2>&1 &
PID=$!

MAXRSS=0
while kill -0 "$PID" 2>/dev/null; do
  RSS=$(ps -o rss= -p "$PID" 2>/dev/null | tr -d ' ')
  if [ -n "$RSS" ] && [ "$RSS" -gt "$MAXRSS" ] 2>/dev/null; then
    MAXRSS=$RSS
  fi
  sleep 0.2
done
wait "$PID"

if [ -f "$OUTJFR" ]; then
  "$JFR_BIN" print --json --events datadog.ProfilerCounter "$OUTJFR" > "${OUTJFR}.json" 2>/dev/null
  EXTRACTED=$(python3 "$SCRIPT_DIR/extract.py" "${OUTJFR}.json")
else
  EXTRACTED="NO_JFR"
fi
echo "${MODE},${N},${MAXRSS},${EXTRACTED}"
