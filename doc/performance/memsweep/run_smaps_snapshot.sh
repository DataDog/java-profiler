#!/bin/bash
# Per-mapping residency snapshot, to settle whether glibc's free-but-held arena
# space is resident.
#
# WHY THIS EXISTS: mallinfo alone cannot answer it. Two models both fit the
# 12-pair means and disagree by 25.6 MiB:
#   report:  anon = uordblks + hblkhd + calltrace = 61.6  (matches mean, but its
#            SD is 0.16 MiB against anon's 29.56 and corr is -0.005, so it cannot
#            explain why anon moves between pairs at all)
#   arena:   anon = arena    + hblkhd + calltrace = 84.5  (matches the variance,
#            corr 0.998, but overshoots the mean by +25.6)
# Both are inferences from cross-run correlation. smaps reports Rss per mapping
# directly, which discriminates them.
#
# malloc_trim is NOT a valid alternative test here: keepcost = 0.13 MiB, so
# nothing is trimmable regardless of whether those pages are resident.
#
# Workload parameters are identical to the arena12 12-pair run so the mallinfo
# terms are directly comparable. The mallinfo sampler is preloaded into BOTH arms
# so `arena`/`uordblks`/`fordblks` are known at the snapshot instant.
#
# Timing skew between the three instruments is tolerable: plateau anon is stable
# to an IQR of 0.55-0.82 MiB over a whole 60 s window (measured), so the ~2 s
# cost of starting the sidecar is immaterial.
#
# Usage: run_smaps_snapshot.sh <out_dir>
set -u
OUT="$1"
DOE_REPO="${DOE_REPO:-/home/bits/go/src/github.com/DataDog/dd-trace-doe}"
DOE_BIN="${DOE_BIN:-/tmp/doe}"
DURATION="${DURATION:-300}"
SNAP_AT="${SNAP_AT:-270}"          # inside the plateau (t >= 240 s)
SIDECAR="${SIDECAR:-eclipse-temurin:21-jdk}"
MALLINFO_SO="${MALLINFO_SO:-/tmp/arena12/mallinfo/pair01_proftrue/sampler.so}"

mkdir -p "$OUT/smaps" "$OUT/mallinfo" "$OUT/logs" "$OUT/anon"

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
  local prof="$1"
  local tag="prof${prof}"
  local log="$OUT/logs/${tag}.log"
  local anonfile="$OUT/anon/${tag}.txt"
  : > "$anonfile"

  local jto="-XX:NativeMemoryTracking=summary -XX:+AlwaysPreTouch"
  local -a envs=()
  [ "$prof" = "true" ] && jto="-Ddd.profiling.debug.jfr.disabled=true $jto"

  mkdir -p "$OUT/mallinfo/${tag}"
  cp "$MALLINFO_SO" "$OUT/mallinfo/${tag}/sampler.so"
  chmod 755 "$OUT/mallinfo/${tag}/sampler.so"
  envs+=(DOE_DEBUG_JAVA_TOOL_OPTIONS="$jto")
  envs+=(DOE_DEBUG_EXTRA_MOUNT_SRC="$OUT/mallinfo/${tag}")
  envs+=(DOE_DEBUG_EXTRA_MOUNT_DST=/mallinfo)
  envs+=(DOE_DEBUG_EXTRA_ENV="LD_PRELOAD=/mallinfo/sampler.so;MALLINFO_OUT=/mallinfo;MALLINFO_INTERVAL_MS=1000")

  echo "=== arm profiling=$prof ==="
  ( cd "$DOE_REPO" && env "${envs[@]}" "$DOE_BIN" run $COMMON --no-build \
      tracing=true profiling="$prof" -n 1 -f > "$log" 2>&1 ) &
  local pid=$!

  local cid=""
  while kill -0 "$pid" 2>/dev/null; do
    cid=$(grep -oP 'app container started.*container_id=\K[a-f0-9]+' "$log" 2>/dev/null | head -1)
    [ -n "$cid" ] && break
    sleep 2
  done
  if [ -z "$cid" ]; then echo "  WARN: no container id"; wait "$pid"; return; fi
  echo "  container ${cid:0:12}"

  sample_anon "$cid" "$anonfile" &
  local sampler_pid=$!

  ( sleep "$SNAP_AT"
    ts=$(date +%s%3N)
    # cgroup anon FIRST, closest to the smaps read that follows
    v=$(awk '/^anon /{print $2; exit}' "/sys/fs/cgroup/docker/${cid}/memory.stat" 2>/dev/null)
    printf '%s %s SNAP\n' "$ts" "${v:-0}" >> "$anonfile"
    echo "$ts ${v:-0}" > "$OUT/smaps/${tag}.snapmeta"
    # Full smaps plus the cheap rollup total, from a sidecar sharing the PID ns.
    # SYS_PTRACE + uid 0 are needed to read another process's smaps.
    docker run --rm --pid=container:"$cid" --cap-add=SYS_PTRACE -u 0 "$SIDECAR" \
      cat /proc/1/smaps > "$OUT/smaps/${tag}.smaps" 2>"$OUT/smaps/${tag}.smaps.err"
    docker run --rm --pid=container:"$cid" --cap-add=SYS_PTRACE -u 0 "$SIDECAR" \
      cat /proc/1/smaps_rollup > "$OUT/smaps/${tag}.rollup" 2>/dev/null
    docker run --rm --pid=container:"$cid" --cap-add=SYS_PTRACE -u 0 "$SIDECAR" \
      jcmd 1 VM.native_memory summary > "$OUT/smaps/${tag}.nmt" 2>/dev/null
  ) &
  local snap_pid=$!

  wait "$pid"
  kill "$sampler_pid" 2>/dev/null
  wait "$snap_pid" 2>/dev/null
  wait 2>/dev/null

  local sz; sz=$(wc -c < "$OUT/smaps/${tag}.smaps" 2>/dev/null || echo 0)
  echo "  smaps bytes=${sz}  anon_samples=$(wc -l < "$anonfile")"
  [ "$sz" -lt 1000 ] && { echo "  --- smaps stderr ---"; sed 's/^/    /' "$OUT/smaps/${tag}.smaps.err" 2>/dev/null | head -5; }
}

run_one true
run_one false
echo "ALLDONE"
