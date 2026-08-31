#!/bin/bash
# 8 interleaved counterbalanced pairs with a per-mapping residency snapshot.
#
# WHY PAIRS AND NOT ONE SNAPSHOT: the single pair in run_smaps_snapshot.sh
# settled the ABSOLUTE question (free-but-held arena pages are resident: arena
# regions held 214.9 MiB Rss against 78.7 MiB of in-use arena bytes) but drew
# d_fordblks = +1.6 MiB against a 12-pair mean of +22.86, so it could not size
# the profiler-ATTRIBUTABLE free-held cost. Per-pair anon SD is 29.56 MiB, so
# that term needs replication, not one draw.
#
# Interleaved and counterbalanced for the same reasons as
# run_doe_interleaved.sh: machine drift otherwise lands preferentially on one
# arm, and the first run in a pair carries ~7.1 MiB more anon regardless of
# which arm it is.
#
# Differences from run_smaps_snapshot.sh:
#   - 8 pairs, order alternating per pair
#   - DOE_DEBUG_PROFILE_DIR set, so profiler NativeMem counters are available
#     per run (the single-pair capture omitted it and had none)
#   - two snapshots per run (t=250, t=285) so within-plateau stability of the
#     per-mapping breakdown is measurable, not assumed
#
# Usage: run_smaps_paired.sh <out_dir> [pairs]
set -u
OUT="$1"
PAIRS="${2:-8}"
DOE_REPO="${DOE_REPO:-/home/bits/go/src/github.com/DataDog/dd-trace-doe}"
DOE_BIN="${DOE_BIN:-/tmp/doe}"
DURATION="${DURATION:-300}"
SNAP_AT="${SNAP_AT:-250 285}"
SIDECAR="${SIDECAR:-eclipse-temurin:21-jdk}"
MALLINFO_SO="${MALLINFO_SO:-/tmp/arena12/mallinfo/pair01_proftrue/sampler.so}"

mkdir -p "$OUT/smaps" "$OUT/mallinfo" "$OUT/logs" "$OUT/anon" "$OUT/jfr" "$OUT/nmt"

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
  : > "$anonfile"

  local jto="-XX:NativeMemoryTracking=summary -XX:+AlwaysPreTouch"
  local -a envs=()
  if [ "$prof" = "true" ]; then
    jto="-Ddd.profiling.debug.jfr.disabled=true $jto"
    mkdir -p "$OUT/jfr/${tag}"
    envs+=(DOE_DEBUG_PROFILE_DIR="$OUT/jfr/${tag}")
  fi

  mkdir -p "$OUT/mallinfo/${tag}"
  cp "$MALLINFO_SO" "$OUT/mallinfo/${tag}/sampler.so"
  chmod 755 "$OUT/mallinfo/${tag}/sampler.so"
  envs+=(DOE_DEBUG_JAVA_TOOL_OPTIONS="$jto")
  envs+=(DOE_DEBUG_EXTRA_MOUNT_SRC="$OUT/mallinfo/${tag}")
  envs+=(DOE_DEBUG_EXTRA_MOUNT_DST=/mallinfo)
  envs+=(DOE_DEBUG_EXTRA_ENV="LD_PRELOAD=/mallinfo/sampler.so;MALLINFO_OUT=/mallinfo;MALLINFO_INTERVAL_MS=1000")

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

  for d in $SNAP_AT; do
    ( sleep "$d"
      ts=$(date +%s%3N)
      v=$(awk '/^anon /{print $2; exit}' "/sys/fs/cgroup/docker/${cid}/memory.stat" 2>/dev/null)
      printf '%s %s SNAP%s\n' "$ts" "${v:-0}" "$d" >> "$anonfile"
      echo "$ts ${v:-0}" > "$OUT/smaps/${tag}_t${d}.snapmeta"
      docker run --rm --pid=container:"$cid" --cap-add=SYS_PTRACE -u 0 "$SIDECAR" \
        cat /proc/1/smaps > "$OUT/smaps/${tag}_t${d}.smaps" 2>/dev/null
      docker run --rm --pid=container:"$cid" --cap-add=SYS_PTRACE -u 0 "$SIDECAR" \
        jcmd 1 VM.native_memory summary > "$OUT/nmt/${tag}_t${d}.txt" 2>/dev/null ) &
  done

  wait "$pid"
  kill "$sampler_pid" 2>/dev/null
  wait 2>/dev/null

  local n=0
  for d in $SNAP_AT; do
    local sz; sz=$(wc -c < "$OUT/smaps/${tag}_t${d}.smaps" 2>/dev/null || echo 0)
    [ "$sz" -gt 1000 ] && n=$((n+1))
  done
  echo "  $tag  smaps_ok=${n}/$(echo $SNAP_AT | wc -w)  anon_samples=$(wc -l < "$anonfile")"
}

for p in $(seq 1 "$PAIRS"); do
  if [ $(( p % 2 )) -eq 1 ]; then order="true false"; else order="false true"; fi
  echo "=== pair $p (order: $order) ==="
  for prof in $order; do
    run_one "$prof" "$p"
  done
done
echo "ALLDONE"
