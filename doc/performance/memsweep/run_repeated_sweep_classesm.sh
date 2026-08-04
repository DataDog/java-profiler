#!/bin/bash
# Repeated-measures with/without-agent comparison for classesM mode (N
# classes, M methods each, all invoked every cycle) at a single (N, M) pair.
# Same structure as run_repeated_sweep.sh, adapted to carry the extra
# methods-per-class parameter through GenSources/MemSweepMain -- built to
# test whether class-diversity overhead (see memory-sweep-results-linux.md)
# actually tracks distinct classes touched, or distinct methods touched,
# which the plain `classes` mode can't distinguish since every class there
# has exactly one method.
#
# Appends one CSV line per run to $RESULTS_FILE:
#   n,methods_per_class,condition,rep,rss_kb,nmt_thread_committed_kb,nmt_total_committed_kb
#
# Usage: run_repeated_sweep_classesm.sh <N> <M> <duration_ms> <reps> <concurrency> <results_file>
set -u
N="$1"
M="$2"
DURATION_MS="$3"
REPS="$4"
CONCURRENCY="$5"
RESULTS="$6"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
JAVA_HOME_DIR="$("$JAVA_BIN" -XshowSettings:properties -version 2>&1 | awk -F'= ' '/java.home/{print $2}')"
JAVAC_BIN="${JAVAC_BIN:-$(command -v javac || echo "$JAVA_HOME_DIR/bin/javac")}"
JCMD_BIN="${JCMD_BIN:-$(command -v jcmd || echo "$JAVA_HOME_DIR/bin/jcmd")}"
WORKDIR="${WORKDIR:-/tmp/memsweep_repeated_classesm_${N}_${M}}"

if [ -z "$DDPROF_LIB" ] || [ ! -f "$DDPROF_LIB" ]; then
  echo "ERROR: could not find libjavaProfiler under $REPO_ROOT/ddprof-lib/build/lib/main/release." >&2
  exit 1
fi

CLASSDIR="$WORKDIR/classes"
GENDIR="$WORKDIR/gen"
OUTDIR="$WORKDIR/out"
mkdir -p "$CLASSDIR" "$GENDIR" "$OUTDIR"

echo "[$(date +%T)] compiling MemSweepMain/GenSources..."
"$JAVAC_BIN" -cp "$DDPROF_JAVA_API" -d "$CLASSDIR" \
  "$SCRIPT_DIR/src/MemSweepMain.java" "$SCRIPT_DIR/src/GenSources.java"

echo "[$(date +%T)] generating+compiling $N classes x $M methods (once, reused for all reps)..."
"$JAVA_BIN" -cp "$CLASSDIR" GenSources classesM "$N" "$GENDIR" "$M" > "$OUTDIR/gen.log" 2>&1
find "$GENDIR" -name "*.java" > "$GENDIR.filelist"
"$JAVAC_BIN" -d "$GENDIR" "@${GENDIR}.filelist" >> "$OUTDIR/gen.log" 2>&1
echo "[$(date +%T)] compile done, starting $((REPS*2)) runs (concurrency=$CONCURRENCY)"

run_one() {
  local cond="$1" rep="$2"
  local tag="${cond}_rep${rep}"
  local out="$OUTDIR/$tag"
  if [ "$cond" = "with" ]; then
    "$JAVA_BIN" -XX:NativeMemoryTracking=summary \
      -agentpath:${DDPROF_LIB}=start,wall=~1ms,jfr,file=${out}.jfr,cstack=fp \
      -Dmemsweep.libpath="$DDPROF_LIB" \
      -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classesM "$N" "$DURATION_MS" "$GENDIR" "$M" \
      > "${out}.stdout" 2>&1 &
  else
    "$JAVA_BIN" -XX:NativeMemoryTracking=summary \
      -Dmemsweep.libpath="$DDPROF_LIB" \
      -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classesM "$N" "$DURATION_MS" "$GENDIR" "$M" \
      > "${out}.stdout" 2>&1 &
  fi
  local pid=$!
  local launch_epoch
  launch_epoch=$(date +%s.%N)

  for i in 1 2 3 4 5 6; do
    sleep 1
    "$JCMD_BIN" "$pid" VM.native_memory baseline > "${out}.baseline.txt" 2>&1
    grep -qE "Baseline (succeeded|taken)" "${out}.baseline.txt" && break
  done

  local sample_at
  sample_at=$(python3 -c "
import time
target = $launch_epoch + max(0.1, ($DURATION_MS - 1000) / 1000)
print(max(0.1, target - time.time()))
")
  sleep "$sample_at"
  "$JCMD_BIN" "$pid" VM.native_memory summary.diff > "${out}.diff.txt" 2>&1
  "$JCMD_BIN" "$pid" VM.native_memory summary > "${out}.summary.txt" 2>&1
  local maxrss
  maxrss=$(ps -o rss= -p "$pid" 2>/dev/null | tr -d ' ')
  wait "$pid" 2>/dev/null

  local nmt_thread nmt_total
  nmt_thread=$(grep -A1 "^-\s*Thread " "${out}.summary.txt" | head -1 | grep -oP 'committed=\K[0-9]+')
  nmt_total=$(grep "^Total:" "${out}.summary.txt" | grep -oP 'committed=\K[0-9]+')
  echo "${N},${M},${cond},${rep},${maxrss:-NA},${nmt_thread:-NA},${nmt_total:-NA}" >> "$RESULTS"
  echo "[$(date +%T)] done: $tag rss=${maxrss:-NA}KB"
}

rep=1
while [ "$rep" -le "$REPS" ]; do
  batch_end=$((rep + CONCURRENCY/2 - 1))
  [ "$batch_end" -gt "$REPS" ] && batch_end=$REPS
  for r in $(seq "$rep" "$batch_end"); do
    run_one with "$r" &
    run_one without "$r" &
  done
  wait
  rep=$((batch_end + 1))
done

echo "[$(date +%T)] ALL DONE for N=$N M=$M"
