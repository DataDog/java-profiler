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

# Two translation units: the C probe, plus a C++ one defining the replaceable
# global operator new/delete. The latter is not optional -- without it every
# `new`/STL/CountingAllocator byte is attributed to libstdc++ instead of to the
# profiler, because that is where the return address lands.
if [ ! -f "$PROBE_SO" ] \
   || [ "$SCRIPT_DIR/alloc_ledger_probe.c" -nt "$PROBE_SO" ] \
   || [ "$SCRIPT_DIR/alloc_ledger_newops.cpp" -nt "$PROBE_SO" ]; then
  echo "[$(date +%T)] building $PROBE_SO"
  tmpd=$(mktemp -d)
  gcc -c -fPIC -O2 -o "$tmpd/probe.o" "$SCRIPT_DIR/alloc_ledger_probe.c" || exit 1
  g++ -c -fPIC -O2 -std=c++17 -o "$tmpd/newops.o" "$SCRIPT_DIR/alloc_ledger_newops.cpp" || exit 1
  g++ -shared -o "$PROBE_SO" "$tmpd/probe.o" "$tmpd/newops.o" -ldl || exit 1
  rm -rf "$tmpd"
fi

# NativeMem::_live[] is a file-local static, so it cannot be dlsym'd. Recover
# its link-time offset from the debug object's symbol table and hand it to the
# probe, which adds the runtime load base. Recomputed every run so it cannot go
# stale against a rebuilt library.
DDPROF_DEBUG="${DDPROF_DEBUG:-$(dirname "$DDPROF_LIB")/debug/$(basename "$DDPROF_LIB").debug}"
NMLIVE_OFF=""
if [ -f "$DDPROF_DEBUG" ]; then
  NMLIVE_OFF=$(nm --defined-only "$DDPROF_DEBUG" 2>/dev/null \
    | awk '$3=="_ZN9NativeMem5_liveE"{print "0x"$1}')
fi
NMLIVE_NCAT=$(awk '/define DD_NATIVE_MEM_CATEGORY_TABLE/,/MISC/' \
  "$REPO_ROOT/ddprof-lib/src/main/cpp/nativeMem.h" | grep -c '^  X(')
# libjavaProfiler.so statically links libstdc++ and does not export operator
# new, so its internal `new` calls bind to its own private copy and the probe's
# LD_PRELOAD override never sees them -- every such allocation would be
# attributed to one opaque frame. Hand the probe that copy's address range so it
# can unwind out of it to the real call site.
OPNEW_LO=""; OPNEW_SIZE=""
if [ -f "$DDPROF_DEBUG" ]; then
  # Portable hex arithmetic: mawk has no strtonum(), so fold in bash instead.
  lo=0; hi=0
  while read -r a sz _t _n; do
    ai=$((16#$a)); hi_i=$((ai + 16#$sz))
    [ "$lo" -eq 0 ] || [ "$ai" -lt "$lo" ] && lo=$ai
    [ "$hi_i" -gt "$hi" ] && hi=$hi_i
    # .cold fragments live far away in a separate section; including them would
    # stretch the span across hundreds of KB of unrelated code and cause real
    # call sites to be mistaken for operator new.
  done < <(nm -S --defined-only "$DDPROF_DEBUG" 2>/dev/null \
           | grep -E ' _Zn[wa]m' | grep -v '\.cold')
  if [ "$lo" -ne 0 ]; then
    OPNEW_LO=$(printf "0x%x" "$lo")
    OPNEW_SIZE=$(printf "0x%x" $((hi - lo)))
  fi
  [ -n "$OPNEW_LO" ] && echo "[$(date +%T)] private operator new range $OPNEW_LO +$OPNEW_SIZE"
fi

if [ -z "$NMLIVE_OFF" ]; then
  echo "WARNING: could not find _ZN9NativeMem5_liveE in $DDPROF_DEBUG -- the" >&2
  echo "         profiler's own counters will not be captured." >&2
else
  echo "[$(date +%T)] NativeMem::_live offset $NMLIVE_OFF, $NMLIVE_NCAT categories"
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
    PROBE_NMLIVE_OFF="$NMLIVE_OFF" PROBE_NMLIVE_NCAT="$NMLIVE_NCAT" \
    PROBE_OPNEW_OFF="$OPNEW_LO" PROBE_OPNEW_SIZE="$OPNEW_SIZE" \
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
