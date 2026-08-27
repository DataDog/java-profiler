#!/bin/bash
# Interleaved paired doe runs: alternates tracing-only and tracing+profiling
# within a single window, so machine-level drift cannot land preferentially on
# one condition. Replaces the previous design (12 reps of one condition, then 12
# of the other, hours apart), which left the RSS delta ambiguous between
# 74.6 and 84.3 MiB.
#
# Two deliberate changes from run_batch.sh:
#   * loops_num/allocs_num are pinned to the values calibration produced, with
#     loops_cpu/allocs_cpu=0, so NeedsCalibration() is false. This removes 24
#     calibration containers AND removes a confound -- previously each condition
#     calibrated independently, so the two arms could run slightly different
#     workloads. Every other archetype parameter is unchanged.
#   * Within-pair order is counterbalanced (pair 1: prof,base; pair 2:
#     base,prof; ...) so any linear drift across a pair cancels rather than
#     always favouring whichever arm goes first.
#
# With calibration off there is exactly ONE "app container started" per
# invocation, so no calibration container has to be skipped.
#
# Usage: run_interleaved.sh <out_dir> [pairs]
set -u
OUT="$1"
PAIRS="${2:-12}"
DOE_REPO=/home/bits/go/src/github.com/DataDog/dd-trace-doe

mkdir -p "$OUT/nmt" "$OUT/jfr" "$OUT/logs"

COMMON="archetype=enterprise language=java library_version=local agent=false \
duration=90 loops_cpu=0 allocs_cpu=0 loops_num=1712244 allocs_num=408773"

run_one() {
  local prof="$1" pair="$2"
  local tag="pair$(printf '%02d' "$pair")_prof${prof}"
  local log="$OUT/logs/${tag}.log"
  local jfrdir="$OUT/jfr/${tag}"

  local jto="-XX:NativeMemoryTracking=summary"
  local -a envs=()
  if [ "$prof" = "true" ]; then
    jto="-Ddd.profiling.debug.jfr.disabled=true $jto"
    mkdir -p "$jfrdir"
    envs+=(DOE_DEBUG_PROFILE_DIR="$jfrdir")
  fi
  envs+=(DOE_DEBUG_JAVA_TOOL_OPTIONS="$jto")

  ( cd "$DOE_REPO" && env "${envs[@]}" /tmp/doe run $COMMON \
      tracing=true profiling="$prof" -n 1 -f > "$log" 2>&1 ) &
  local pid=$!

  # Wait for the app container, then snapshot NMT 30 s in (matches the timing
  # used by the earlier batches, so the numbers stay comparable).
  local cid=""
  while kill -0 "$pid" 2>/dev/null; do
    cid=$(grep -oP 'app container started.*container_id=\K[a-f0-9]+' "$log" 2>/dev/null | head -1)
    [ -n "$cid" ] && break
    sleep 2
  done
  if [ -n "$cid" ]; then
    ( sleep 30
      docker run --rm --pid=container:"$cid" eclipse-temurin:21-jdk \
        jcmd 1 VM.native_memory summary > "$OUT/nmt/${tag}.txt" 2>&1 ) &
  else
    echo "  WARN: no container id for $tag"
  fi

  wait "$pid"
  wait                      # let the NMT sidecar finish
  local mem
  mem=$(grep -oP 'memory=\K[0-9]+' "$log" | tail -1)
  echo "  $tag memory=${mem:-MISSING}"
  echo "${tag} ${mem:-MISSING}" >> "$OUT/rss.txt"
}

: > "$OUT/rss.txt"
for p in $(seq 1 "$PAIRS"); do
  if [ $(( p % 2 )) -eq 1 ]; then order="true false"; else order="false true"; fi
  echo "=== pair $p (order: $order) ==="
  for prof in $order; do
    run_one "$prof" "$p"
  done
done
echo "ALLDONE $(wc -l < "$OUT/rss.txt") runs"
