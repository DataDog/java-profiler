#!/bin/bash
# Paired allocation-ledger capture on the dd-trace-doe workload, to attribute
# the +22.56 MiB of mmap-served malloc address space (`hblkhd`) that enabling
# the profiler adds.
#
# WHY: hblkhd's fitted residency is ~0, so it is the term that explains why the
# committed-basis accounting over-states resident anon. Only ~7.7 MiB of it is
# profiler-instrumented allocation (see alloc_size_histogram.py on the memsweep
# dumps), so most of it is induced JVM or tracer allocation and is currently
# unattributed. This locates it.
#
# WHY NOT run_ledger_capture.sh: that runs the *memsweep* workload (N classes in
# a bare JVM). The term being attributed was measured on dd-trace-doe, and the
# earlier histogram's main caveat was exactly that the two workloads differ. So
# the ledger has to run on the same workload the number came from.
#
# WHY BOTH ARMS: the profiler's own counters ride its JFR, so the tracing-only
# arm emits nothing and no paired delta can be formed from them. LD_PRELOAD does
# not care whether the profiler is attached, so the probe runs in both arms and
# the *difference* of the two caller tables is what attributes the delta.
#
# ATTRIBUTION WITHOUT SYMBOLS: the probe emits no module table, but its dump
# includes the process's own smaps, which carries a pathname per mapping. Joining
# caller addresses against that gives a per-library split (libjvm / libc /
# libjavaProfiler / tracer natives) with no debug info required -- which is
# enough to answer "whose allocation is this?". Finer attribution inside libjvm
# would need HotSpot symbols the container image does not carry.
#
# The probe dumps on SIGRTMIN+10 (= 44), delivered to PID 1 in the container.
# HotSpot claims SIGUSR2 for thread suspend/resume, which is why the probe does
# not use it.
#
# Usage: run_ledger_doe.sh <out_dir> [pairs]
set -u
OUT="$1"
PAIRS="${2:-3}"
DOE_REPO="${DOE_REPO:-/home/bits/go/src/github.com/DataDog/dd-trace-doe}"
DOE_BIN="${DOE_BIN:-/tmp/doe}"
# DURATION MUST STAY 300. doe derives the image tag from a hash of the input
# parameters, and `duration` is one of them -- raising it to 360 produced tag
# doe/java:4c2c61b3, which does not exist, and --no-build then failed with
# "No such image" before any container started. 300 also keeps this batch
# comparable to every prior one.
#
# The margin against the exit deadline therefore comes from DUMP_AT instead.
# 250 s is inside the plateau (t >= 240) and leaves 50 s; the smaps batch
# successfully snapshotted these same containers at t=285, so the container is
# comfortably alive here, and the dump is only a few hundred KB to write.
DURATION="${DURATION:-300}"
DUMP_AT="${DUMP_AT:-250}"
PROBE_SO="${PROBE_SO:-/tmp/ledger_doe.so}"
SIGNUM="${SIGNUM:-44}"             # SIGRTMIN+10

[ -f "$PROBE_SO" ] || { echo "ERROR: $PROBE_SO missing (build it first)" >&2; exit 1; }

mkdir -p "$OUT/logs" "$OUT/anon"

COMMON="archetype=enterprise language=java library_version=local agent=false \
duration=${DURATION} loops_cpu=0 allocs_cpu=0 loops_num=1712244 allocs_num=408773"

sample_anon() {
  local cid="$1" outfile="$2"
  local stat="/sys/fs/cgroup/docker/${cid}/memory.stat"
  while [ -r "$stat" ]; do
    local v
    v=$(awk '/^anon /{print $2; exit}' "$stat" 2>/dev/null) || break
    [ -n "$v" ] && printf '%s %s\n' "$(date +%s%3N)" "$v" >> "$outfile"
    sleep 0.5
  done
}

run_one() {
  local prof="$1" pair="$2"
  local tag="pair$(printf '%02d' "$pair")_prof${prof}"
  local log="$OUT/logs/${tag}.log"
  local anonfile="$OUT/anon/${tag}.txt"
  local ldir="$OUT/ledger/${tag}"
  : > "$anonfile"
  mkdir -p "$ldir"
  cp "$PROBE_SO" "$ldir/probe.so"
  chmod 755 "$ldir/probe.so"

  local jto="-XX:NativeMemoryTracking=summary -XX:+AlwaysPreTouch"
  [ "$prof" = "true" ] && jto="-Ddd.profiling.debug.jfr.disabled=true $jto"

  local -a envs=()
  envs+=(DOE_DEBUG_JAVA_TOOL_OPTIONS="$jto")
  envs+=(DOE_DEBUG_EXTRA_MOUNT_SRC="$ldir")
  envs+=(DOE_DEBUG_EXTRA_MOUNT_DST=/ledger)
  # PROBE_TRACK_RAW is deliberately OFF. It would catch OS::safeAlloc's naked
  # syscall, but that arena is NM_CALLTRACE, which mallinfo cannot see at all
  # (hence `uordblks + fordblks = arena` holding exactly) -- so it is not part
  # of hblkhd and tracking it only adds probe footprint and event volume.
  envs+=(DOE_DEBUG_EXTRA_ENV="LD_PRELOAD=/ledger/probe.so;PROBE_OUTDIR=/ledger;PROBE_TRACK_REQ=1")

  ( cd "$DOE_REPO" && env "${envs[@]}" "$DOE_BIN" run $COMMON --no-build \
      tracing=true profiling="$prof" -n 1 -f > "$log" 2>&1 ) &
  local pid=$!

  local cid=""
  while kill -0 "$pid" 2>/dev/null; do
    cid=$(grep -oP 'app container started.*container_id=\K[a-f0-9]+' "$log" 2>/dev/null | head -1)
    [ -n "$cid" ] && break
    sleep 2
  done
  if [ -z "$cid" ]; then echo "  WARN: no container id for $tag"; wait "$pid"; return; fi

  sample_anon "$cid" "$anonfile" &
  local sampler_pid=$!

  ( sleep "$DUMP_AT"
    v=$(awk '/^anon /{print $2; exit}' "/sys/fs/cgroup/docker/${cid}/memory.stat" 2>/dev/null)
    printf '%s %s DUMP\n' "$(date +%s%3N)" "${v:-0}" >> "$anonfile"
    # Do NOT swallow this: if docker rejects the numeric signal the run
    # produces no dump and the cause would otherwise be invisible.
    if ! docker kill --signal="$SIGNUM" "$cid" 2>"$OUT/logs/${tag}.signal.err"; then
      echo "    SIGNAL FAILED: $(cat "$OUT/logs/${tag}.signal.err")"
    fi
    # The handler only sets a flag; a helper thread does the writing. Give it
    # room before the workload's own exit deadline takes the process away.
    sleep 15 ) &
  local dump_pid=$!

  wait "$pid"
  kill "$sampler_pid" 2>/dev/null
  wait "$dump_pid" 2>/dev/null
  wait 2>/dev/null

  local n; n=$(ls "$ldir"/*.callers.txt 2>/dev/null | wc -l)
  echo "  $tag  dumps=${n}  anon_samples=$(wc -l < "$anonfile")"
  [ "$n" -eq 0 ] && echo "    WARN: no dump -- check the signal arrived before JVM exit"
}

for p in $(seq 1 "$PAIRS"); do
  if [ $(( p % 2 )) -eq 1 ]; then order="true false"; else order="false true"; fi
  echo "=== pair $p (order: $order) ==="
  for prof in $order; do
    run_one "$prof" "$p"
  done
done
echo "ALLDONE"
