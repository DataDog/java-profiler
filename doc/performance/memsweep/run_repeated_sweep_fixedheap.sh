#!/bin/bash
# Fixed-heap variant of run_repeated_sweep.sh -- adds -Xms/-Xmx/-XX:+AlwaysPreTouch
# to remove GC/heap-resize timing noise as a confound. The original sweep ran
# under default JVM heap ergonomics and showed ~89 MB of per-condition RSS
# stdev at N=150,000 (10 reps) -- large enough that the reported delta was
# only a ~2.5-sigma signal. Forcing both conditions to commit and fully touch
# an identical, fixed-size heap up front removes that timing variable
# entirely; see memory-sweep-results-linux.md's "Tightening the residual: a
# fixed-heap re-measurement" for the derivation this was built for (cut
# per-condition stdev ~10x, from ~89 MB to ~6-11 MB, at N=150,000/12 reps).
#
# Otherwise identical to run_repeated_sweep.sh: compiles N classes once,
# interleaves with/without-agent runs in same-size batches, appends one CSV
# line per run to $RESULTS_FILE:
#   n,condition,rep,rss_kb,nmt_thread_committed_kb,nmt_total_committed_kb
#
# Usage: run_repeated_sweep_fixedheap.sh <N> <duration_ms> <reps> <concurrency> <results_file>
#
# Environment overrides: HEAP_FLAGS (default "-Xms512m -Xmx512m
# -XX:+AlwaysPreTouch"), plus the same DDPROF_LIB/DDPROF_JAVA_API/JAVA_BIN/
# JAVAC_BIN/JCMD_BIN/WORKDIR overrides as run_repeated_sweep.sh.
set -u
N="$1"
DURATION_MS="$2"
REPS="$3"
CONCURRENCY="$4"
RESULTS="$5"
HEAP_FLAGS="${HEAP_FLAGS:--Xms512m -Xmx512m -XX:+AlwaysPreTouch}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
JAVA_HOME_DIR="$("$JAVA_BIN" -XshowSettings:properties -version 2>&1 | awk -F'= ' '/java.home/{print $2}')"
JAVAC_BIN="${JAVAC_BIN:-$(command -v javac || echo "$JAVA_HOME_DIR/bin/javac")}"
JCMD_BIN="${JCMD_BIN:-$(command -v jcmd || echo "$JAVA_HOME_DIR/bin/jcmd")}"
WORKDIR="${WORKDIR:-/tmp/memsweep_fixedheap_${N}}"

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

echo "[$(date +%T)] generating+compiling $N classes (once, reused for all reps)..."
"$JAVA_BIN" -cp "$CLASSDIR" GenSources classes "$N" "$GENDIR" > "$OUTDIR/gen.log" 2>&1
find "$GENDIR" -name "*.java" > "$GENDIR.filelist"
"$JAVAC_BIN" -d "$GENDIR" "@${GENDIR}.filelist" >> "$OUTDIR/gen.log" 2>&1
echo "[$(date +%T)] compile done, starting $((REPS*2)) runs (concurrency=$CONCURRENCY), HEAP_FLAGS='$HEAP_FLAGS'"

run_one() {
  local cond="$1" rep="$2"
  local tag="${cond}_rep${rep}"
  local out="$OUTDIR/$tag"
  if [ "$cond" = "with" ]; then
    "$JAVA_BIN" $HEAP_FLAGS -XX:NativeMemoryTracking=summary \
      -agentpath:${DDPROF_LIB}=start,wall=~1ms,jfr,file=${out}.jfr,cstack=fp \
      -Dmemsweep.libpath="$DDPROF_LIB" \
      -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classes "$N" "$DURATION_MS" "$GENDIR" \
      > "${out}.stdout" 2>&1 &
  else
    "$JAVA_BIN" $HEAP_FLAGS -XX:NativeMemoryTracking=summary \
      -Dmemsweep.libpath="$DDPROF_LIB" \
      -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classes "$N" "$DURATION_MS" "$GENDIR" \
      > "${out}.stdout" 2>&1 &
  fi
  local pid=$!
  local launch_epoch
  launch_epoch=$(date +%s.%N)

  # See run_nmt.sh for why this loop + the launch-epoch-relative sleep below
  # are both needed: a fixed post-baseline sleep can push the sample past the
  # workload's own deadline, especially once several concurrent reps are
  # competing for CPU.
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
  echo "${N},${cond},${rep},${maxrss:-NA},${nmt_thread:-NA},${nmt_total:-NA}" >> "$RESULTS"
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

echo "[$(date +%T)] ALL DONE for N=$N"
