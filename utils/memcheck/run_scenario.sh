#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Runs one memcheck scenario once and writes one JSON record (see CollectRun).
#
# Usage: run_scenario.sh <scenario> <arm> <rep>
#   scenario: threads | traces | classesM | allocs | mixed
#   arm:      counters  profiler attached, NMT off
#             nmt       profiler attached, -XX:NativeMemoryTracking=summary
#             noprof    no profiler, NMT on (control for the nmt arm)
#
# NMT and RSS are sampled once per run, SAMPLE_DELAY_S after the mid-run
# recording rotation completes, so every arm is sampled at the same point of
# the workload's lifecycle.
#
# Required environment:
#   DDPROF_LIB      the profiler library (libjavaProfiler.so)
#   DDPROF_CLASSES  ddprof-lib's compiled Java classes
#   MEMCHECK_CLASSES  compiled MemCheckMain/GenSources/CollectRun
#   WORKDIR         scratch directory (generated sources are cached here)
#   OUTDIR          where the per-run JSON record goes
# Optional: JAVA_HOME, STEADY_MS (40000), DUMP_AFTER_MS (20000), SAMPLE_DELAY_S (5)
set -euo pipefail

SCENARIO="$1"
ARM="$2"
REP="$3"
STEADY_MS="${STEADY_MS:-40000}"
DUMP_AFTER_MS="${DUMP_AFTER_MS:-20000}"
SAMPLE_DELAY_S="${SAMPLE_DELAY_S:-5}"
JAVA="${JAVA_HOME:+$JAVA_HOME/bin/}java"
JAVAC="${JAVA_HOME:+$JAVA_HOME/bin/}javac"
JCMD="${JAVA_HOME:+$JAVA_HOME/bin/}jcmd"

case "$SCENARIO" in
  threads)  MODE=threads;  ARGS=(200);        ENGINES="wall=~5ms" ;;
  traces)   MODE=traces;   ARGS=(5000);       ENGINES="wall=~5ms" ;;
  classesM) MODE=classesM; ARGS=(2000 20);    ENGINES="wall=~5ms" ;;
  allocs)   MODE=allocs;   ARGS=(2000);       ENGINES="memory=1024:a" ;;
  mixed)    MODE=allocs;   ARGS=(2000);       ENGINES="cpu=10ms,wall=~5ms,memory=262144:al" ;;
  *) echo "unknown scenario: $SCENARIO" >&2; exit 2 ;;
esac

GENDIR="$WORKDIR/gen/${MODE}_$(IFS=_; echo "${ARGS[*]}")"
if [ "$MODE" != threads ] && [ ! -f "$GENDIR/.done" ]; then
  mkdir -p "$GENDIR"
  "$JAVA" -cp "$MEMCHECK_CLASSES" GenSources "$MODE" "${ARGS[0]}" "$GENDIR" "${ARGS[@]:1}"
  find "$GENDIR" -name '*.java' > "$GENDIR.files"
  "$JAVAC" -d "$GENDIR" "@$GENDIR.files"
  touch "$GENDIR/.done"
fi

TAG="${SCENARIO}-${ARM}-${REP}"
RUNDIR="$WORKDIR/runs/$TAG"
rm -rf "$RUNDIR"
mkdir -p "$RUNDIR" "$OUTDIR"

JVM_ARGS=(-Xms512m -Xmx512m -XX:+AlwaysPreTouch "-Dmemcheck.dumpAfterMs=$DUMP_AFTER_MS" "-Dmemcheck.dumpPath=$RUNDIR/middump.jfr")
case "$ARM" in
  counters) JVM_ARGS+=("-agentpath:$DDPROF_LIB=start,$ENGINES,jfr,file=$RUNDIR/final.jfr" "-Dmemcheck.libpath=$DDPROF_LIB") ;;
  nmt)      JVM_ARGS+=(-XX:NativeMemoryTracking=summary "-agentpath:$DDPROF_LIB=start,$ENGINES,jfr,file=$RUNDIR/final.jfr" "-Dmemcheck.libpath=$DDPROF_LIB") ;;
  noprof)   JVM_ARGS+=(-XX:NativeMemoryTracking=summary -Dmemcheck.noProfiler=true) ;;
  *) echo "unknown arm: $ARM" >&2; exit 2 ;;
esac

"$JAVA" "${JVM_ARGS[@]}" -cp "$MEMCHECK_CLASSES:$DDPROF_CLASSES" \
  MemCheckMain "$MODE" "${ARGS[0]}" "$STEADY_MS" "$GENDIR" "${ARGS[@]:1}" \
  > "$RUNDIR/stdout.log" 2>&1 &
PID=$!

# Wait for the rotation; give up if the JVM dies or it takes far too long.
deadline=$(( $(date +%s) + 300 ))
until grep -qE 'MEMCHECK_DUMP_(END|FAILED)' "$RUNDIR/stdout.log" 2>/dev/null; do
  if ! kill -0 "$PID" 2>/dev/null || [ "$(date +%s)" -gt "$deadline" ]; then
    echo "FAIL: $TAG never reached the rotation; see $RUNDIR/stdout.log" >&2
    kill "$PID" 2>/dev/null || true
    exit 1
  fi
  sleep 0.2
done
if grep -q MEMCHECK_DUMP_FAILED "$RUNDIR/stdout.log"; then
  echo "FAIL: $TAG rotation failed: $(grep MEMCHECK_DUMP_FAILED "$RUNDIR/stdout.log")" >&2
  kill "$PID" 2>/dev/null || true
  exit 1
fi

sleep "$SAMPLE_DELAY_S"
cp "/proc/$PID/status" "$RUNDIR/status.txt"
if [ "$ARM" != counters ]; then
  "$JCMD" "$PID" VM.native_memory summary > "$RUNDIR/nmt.txt" 2>&1
fi

if ! wait "$PID"; then
  echo "FAIL: $TAG JVM exited non-zero; see $RUNDIR/stdout.log" >&2
  exit 1
fi

"$JAVA" -cp "$MEMCHECK_CLASSES" CollectRun scenario="$SCENARIO" arm="$ARM" rep="$REP" \
  jfr="$RUNDIR/final.jfr" middump="$RUNDIR/middump.jfr" nmt="$RUNDIR/nmt.txt" \
  status="$RUNDIR/status.txt" out="$OUTDIR/$TAG.json"
echo "ok: $TAG"
