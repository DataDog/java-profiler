#!/bin/bash
# Runs one sweep point with JVM Native Memory Tracking enabled, to separate
# JVM-internal native memory (thread stacks, JFR engine, code cache, etc.)
# from the profiler agent's own allocations (measured by NM_* via run_sweep.sh).
#
# On macOS, attaching jcmd while this agent is also attached became
# unreliable at higher thread counts (attach handshake failures), so that
# pass used --no-agent control runs instead of measuring alongside the
# agent. On Linux, jcmd attach is reliable even with the agent attached at
# 1000 threads (see memory-sweep-results-linux.md) -- --no-agent is kept
# for cross-platform parity and as a control, not because it's required here.
#
# Usage: run_nmt.sh <threads|traces|classes|allocs> <N> <duration_ms> [interval] [--no-agent]
set -u
MODE="$1"
N="$2"
DURATION_MS="$3"
WALL="${4:-~5ms}"
NO_AGENT="${5:-}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
JAVA_HOME_DIR="$("$JAVA_BIN" -XshowSettings:properties -version 2>&1 | awk -F'= ' '/java.home/{print $2}')"
JAVAC_BIN="${JAVAC_BIN:-$(command -v javac || echo "$JAVA_HOME_DIR/bin/javac")}"
JCMD_BIN="${JCMD_BIN:-$(command -v jcmd || echo "$JAVA_HOME_DIR/bin/jcmd")}"
WORKDIR="${WORKDIR:-/tmp/memsweep}"

CLASSDIR="$WORKDIR/classes"
mkdir -p "$CLASSDIR" "$WORKDIR/gen" "$WORKDIR/out"
if [ ! -f "$CLASSDIR/MemSweepMain.class" ]; then
  "$JAVAC_BIN" -cp "$DDPROF_JAVA_API" -d "$CLASSDIR" "$SCRIPT_DIR/src/MemSweepMain.java" "$SCRIPT_DIR/src/GenSources.java"
fi

TAG="nmt_${MODE}_${N}"
GENDIR="$WORKDIR/gen/${TAG}"
OUTJFR="$WORKDIR/out/${TAG}.jfr"
mkdir -p "$GENDIR"

if [ "$MODE" = "traces" ] || [ "$MODE" = "classes" ]; then
  "$JAVA_BIN" -cp "$CLASSDIR" GenSources "$MODE" "$N" "$GENDIR" >"$WORKDIR/out/${TAG}.gen.log" 2>&1
  find "$GENDIR" -name "*.java" > "$GENDIR.filelist"
  "$JAVAC_BIN" -d "$GENDIR" "@${GENDIR}.filelist" >>"$WORKDIR/out/${TAG}.gen.log" 2>&1
fi

if [ "$NO_AGENT" = "--no-agent" ]; then
  "$JAVA_BIN" -XX:NativeMemoryTracking=summary \
    -Dmemsweep.libpath="$DDPROF_LIB" \
    -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain "$MODE" "$N" "$DURATION_MS" "$GENDIR" \
    > "$WORKDIR/out/${TAG}.stdout" 2>&1 &
else
  "$JAVA_BIN" -XX:NativeMemoryTracking=summary \
    -agentpath:${DDPROF_LIB}=start,wall=${WALL},jfr,file=${OUTJFR},cstack=fp \
    -Dmemsweep.libpath="$DDPROF_LIB" \
    -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain "$MODE" "$N" "$DURATION_MS" "$GENDIR" \
    > "$WORKDIR/out/${TAG}.stdout" 2>&1 &
fi
PID=$!
LAUNCH_EPOCH=$(date +%s.%N)

# Give the JVM a moment to initialize before baselining; retry attach a few
# times since high thread counts can delay readiness for the attach handshake.
for i in 1 2 3 4 5 6; do
  sleep 1
  "$JCMD_BIN" "$PID" VM.native_memory baseline > "$WORKDIR/out/${TAG}.nmt_baseline.txt" 2>&1
  # Wording is JDK-version-dependent: some print "Baseline succeeded", others
  # (this JDK 21 build) print "Baseline taken" -- match either.
  grep -qE "Baseline (succeeded|taken)" "$WORKDIR/out/${TAG}.nmt_baseline.txt" && break
done

# Sample near the end of the run, while the workload is still active. Target
# time is relative to when the JVM was actually launched, not to "now" --
# the baseline retry loop above already burned real wall-clock time, and not
# accounting for it here means this sleep alone can push us past the
# workload's own deadline, causing the process to have already exited by the
# time the diff/summary jcmd calls below run (seen in practice as jcmd
# failing with "No such process" despite the workload having run for the
# full requested duration).
SAMPLE_AT=$(python3 -c "
import time
target = $LAUNCH_EPOCH + max(0.1, ($DURATION_MS - 1000) / 1000)
print(max(0.1, target - time.time()))
")
sleep "$SAMPLE_AT"
"$JCMD_BIN" "$PID" VM.native_memory summary.diff > "$WORKDIR/out/${TAG}.nmt_diff.txt" 2>&1
"$JCMD_BIN" "$PID" VM.native_memory summary > "$WORKDIR/out/${TAG}.nmt_summary.txt" 2>&1

MAXRSS=$(ps -o rss= -p "$PID" 2>/dev/null | tr -d ' ')
wait "$PID"

echo "TAG=${TAG} RSS_AT_SAMPLE_KB=${MAXRSS}"
echo "--- diff ---"
cat "$WORKDIR/out/${TAG}.nmt_diff.txt"
