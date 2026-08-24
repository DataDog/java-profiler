#!/bin/bash
# Single with/without-agent pair, fixed-heap classes workload, both LD_PRELOADing
# malloc_info_probe.so (built from malloc_info_probe.c in this directory). At
# the same ~1s-before-deadline sample point used by run_repeated_sweep_fixedheap.sh,
# sends SIGRTMIN+10 to each JVM, which dumps malloc_info() before and after
# malloc_trim(0) -- see "Ruling out arena-level fragmentation as the residual's
# mechanism" in memory-sweep-results-linux.md for what this was built to test
# and what it found.
#
# Usage: run_mallocinfo_capture.sh [N] [duration_ms]
# Environment overrides: DDPROF_LIB/DDPROF_JAVA_API/JAVA_BIN/WORKDIR/OUTDIR,
# same conventions as run_repeated_sweep_fixedheap.sh. WORKDIR must already
# contain compiled classes (reuse an existing memsweep_fixedheap_<N> dir, or
# run run_repeated_sweep_fixedheap.sh once first to generate one).
set -u
N="${1:-150000}"
DURATION_MS="${2:-180000}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
HEAP_FLAGS="${HEAP_FLAGS:--Xms512m -Xmx512m -XX:+AlwaysPreTouch}"
WORKDIR="${WORKDIR:-/tmp/memsweep_fixedheap_${N}}"
CLASSDIR="$WORKDIR/classes"
GENDIR="$WORKDIR/gen"
OUTDIR="${OUTDIR:-/tmp/memsweep_mallocinfo}"
PROBE_SO="${PROBE_SO:-/tmp/malloc_info_probe.so}"

if [ -z "$DDPROF_LIB" ] || [ ! -f "$DDPROF_LIB" ]; then
  echo "ERROR: could not find libjavaProfiler under $REPO_ROOT/ddprof-lib/build/lib/main/release." >&2
  exit 1
fi
if [ ! -d "$GENDIR" ]; then
  echo "ERROR: $GENDIR does not exist -- run run_repeated_sweep_fixedheap.sh $N once first to generate+compile the classes." >&2
  exit 1
fi
if [ ! -f "$PROBE_SO" ]; then
  echo "[$(date +%T)] compiling $PROBE_SO from $SCRIPT_DIR/malloc_info_probe.c ..."
  gcc -shared -fPIC -O2 -o "$PROBE_SO" "$SCRIPT_DIR/malloc_info_probe.c" || exit 1
fi

mkdir -p "$OUTDIR"
rm -f "$OUTDIR"/*.xml

run_one() {
  local cond="$1"
  local out="$OUTDIR/$cond"
  if [ "$cond" = "with" ]; then
    LD_PRELOAD="$PROBE_SO" "$JAVA_BIN" $HEAP_FLAGS -XX:NativeMemoryTracking=summary \
      -agentpath:${DDPROF_LIB}=start,wall=~1ms,jfr,file=${out}.jfr,cstack=fp \
      -Dmemsweep.libpath="$DDPROF_LIB" \
      -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classes "$N" "$DURATION_MS" "$GENDIR" \
      > "${out}.stdout" 2>&1 &
  else
    LD_PRELOAD="$PROBE_SO" "$JAVA_BIN" $HEAP_FLAGS -XX:NativeMemoryTracking=summary \
      -Dmemsweep.libpath="$DDPROF_LIB" \
      -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classes "$N" "$DURATION_MS" "$GENDIR" \
      > "${out}.stdout" 2>&1 &
  fi
  local pid=$!
  echo "$pid" > "${out}.pid"
  local launch_epoch
  launch_epoch=$(date +%s.%N)
  local sample_at
  sample_at=$(python3 -c "
import time
target = $launch_epoch + max(0.1, ($DURATION_MS - 1000) / 1000)
print(max(0.1, target - time.time()))
")
  sleep "$sample_at"
  kill -RTMIN+10 "$pid" 2>/dev/null
  sleep 0.5
  cp "$OUTDIR/$pid.before.xml" "${out}.before.xml" 2>/dev/null
  cp "$OUTDIR/$pid.after.xml" "${out}.after.xml" 2>/dev/null
  ps -o rss= -p "$pid" > "${out}.rss.txt" 2>/dev/null
  wait "$pid" 2>/dev/null
  echo "[$(date +%T)] done: $cond (pid $pid)"
}

run_one with &
run_one without &
wait
echo "[$(date +%T)] ALL DONE -- see $OUTDIR/{with,without}.{before,after}.xml"
