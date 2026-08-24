#!/bin/bash
# Paired with/without-agent capture using alloc_ledger_probe.so, for the Step 0
# question in memory-sweep-results-linux.md: is the unexplained residual
# (a) malloc chunk overhead our logical NativeMem counters cannot see,
# (b) malloc allocations at sites we never instrumented, or
# (c) not malloc at all, but mmap-backed?
#
# Deliberate differences from run_mallocinfo_capture.sh, do not "fix" them back:
#
#  * SEQUENTIAL, not concurrent. That script backgrounds both conditions at
#    once. A prior batch in this investigation had to be discarded because CPU
#    contention produced a physically impossible negative with-vs-without
#    delta, so the conditions are run one at a time here.
#
#  * Sampling is relative to the workload's MEMSWEEP_LOADED marker, not to
#    launch. runClasses loads all N classes to completion *before* entering its
#    timed loop, and the agent makes loading measurably slower; a
#    launch-relative sample can therefore catch the two conditions at different
#    lifecycle stages. We wait for the marker, then let the run settle for
#    STEADY_S seconds of steady-state loop before sampling.
#
#  * NMT is OFF by default. NMT's per-allocation tracking header scales with
#    the number of JVM allocations, and the agent causes many more of them, so
#    leaving NMT on biases the with-agent condition upward. Run with NMT=on to
#    measure that bias term explicitly as a separate comparison.
#
# Usage: run_ledger_capture.sh [N] [duration_ms] [reps] [nmt(on|off)]
# Env:   WORKDIR must already contain compiled classes (see run_repeated_sweep_fixedheap.sh).
set -u
N="${1:-150000}"
DURATION_MS="${2:-300000}"
REPS="${3:-3}"
NMT="${4:-off}"
STEADY_S="${STEADY_S:-60}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
HEAP_FLAGS="${HEAP_FLAGS:--Xms512m -Xmx512m -XX:+AlwaysPreTouch}"
WORKDIR="${WORKDIR:-/tmp/memsweep_fixedheap_${N}}"
CLASSDIR="$WORKDIR/classes"
GENDIR="$WORKDIR/gen"
OUTDIR="${OUTDIR:-/tmp/memsweep_ledger_run}"
PROBE_SO="${PROBE_SO:-/tmp/alloc_ledger_probe.so}"

[ -n "$DDPROF_LIB" ] && [ -f "$DDPROF_LIB" ] || { echo "ERROR: no libjavaProfiler under $REPO_ROOT/ddprof-lib/build/lib/main/release" >&2; exit 1; }
[ -d "$GENDIR" ] || { echo "ERROR: $GENDIR missing -- generate the classes first" >&2; exit 1; }

if [ ! -f "$PROBE_SO" ] || [ "$SCRIPT_DIR/alloc_ledger_probe.c" -nt "$PROBE_SO" ]; then
  echo "[$(date +%T)] building $PROBE_SO"
  gcc -shared -fPIC -O2 -o "$PROBE_SO" "$SCRIPT_DIR/alloc_ledger_probe.c" -ldl || exit 1
fi

NMT_FLAG=""
[ "$NMT" = "on" ] && NMT_FLAG="-XX:NativeMemoryTracking=summary"

mkdir -p "$OUTDIR"

run_one() {
  local cond="$1" rep="$2"
  local tag="${cond}_nmt${NMT}_rep${rep}"
  local out="$OUTDIR/$tag"
  local dumpdir="$OUTDIR/dump_$tag"
  mkdir -p "$dumpdir"

  local agent=()
  if [ "$cond" = "with" ]; then
    agent=(-agentpath:${DDPROF_LIB}=start,wall=~1ms,jfr,file=${out}.jfr,cstack=fp)
  fi

  LD_PRELOAD="$PROBE_SO" PROBE_OUTDIR="$dumpdir" \
    "$JAVA_BIN" $HEAP_FLAGS $NMT_FLAG "${agent[@]}" \
    -Dmemsweep.libpath="$DDPROF_LIB" \
    -cp "$CLASSDIR:$DDPROF_JAVA_API" MemSweepMain classes "$N" "$DURATION_MS" "$GENDIR" \
    > "${out}.stdout" 2>&1 &
  local pid=$!

  # Wait for the steady-state marker rather than a fixed offset from launch.
  local waited=0
  while ! grep -q MEMSWEEP_LOADED "${out}.stdout" 2>/dev/null; do
    sleep 2
    waited=$((waited + 2))
    if ! kill -0 "$pid" 2>/dev/null; then
      echo "[$(date +%T)] $tag: JVM exited before reaching steady state" >&2
      wait "$pid" 2>/dev/null
      return 1
    fi
    if [ "$waited" -gt 900 ]; then
      echo "[$(date +%T)] $tag: timed out waiting for MEMSWEEP_LOADED" >&2
      kill "$pid" 2>/dev/null
      return 1
    fi
  done
  echo "[$(date +%T)] $tag: loaded after ${waited}s, settling ${STEADY_S}s"
  sleep "$STEADY_S"

  kill -s SIGRTMIN+10 "$pid" 2>/dev/null || /bin/kill -s RTMIN+10 "$pid"
  sleep 3
  echo "$pid" > "${out}.pid"
  kill "$pid" 2>/dev/null
  wait "$pid" 2>/dev/null
  echo "[$(date +%T)] done: $tag (pid $pid, dump in $dumpdir)"
}

echo "[$(date +%T)] N=$N duration=${DURATION_MS}ms reps=$REPS nmt=$NMT steady=${STEADY_S}s"
for rep in $(seq 1 "$REPS"); do
  run_one without "$rep"
  run_one with "$rep"
done
echo "[$(date +%T)] ALL DONE -- $OUTDIR"
