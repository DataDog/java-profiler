#!/bin/bash
# Interleaved paired doe runs for the profiler memory reconciliation.
#
# WHY INTERLEAVED: measuring the two conditions in separate windows let
# machine-level drift land preferentially on one arm, which left the memory
# delta ambiguous between 74.6 and 84.3 MiB. Alternating within one window
# removes that. The within-pair order is also counterbalanced (pair 1:
# profiling first; pair 2: tracing-only first; ...) because the first run in a
# pair carries ~7.1 MiB more anon memory regardless of which arm it is;
# counterbalancing cancels that bias instead of letting it pick a side.
#
# WHY WE SAMPLE ANON OURSELVES: doe's own `memory=` output is
# max(cgroup anon) over the whole load+stop phase -- an extreme-value
# statistic. A maximum is upward-biased, high-variance, and permanently
# latches any transient (JIT compiler arenas, GC bursts), which is most of why
# per-pair deltas span 26-112 MiB. It is also temporally incoherent with the
# other instruments: doe's figure is a max over 0-90 s, the NMT snapshot is a
# point at t=30 s, and NativeMem is read at JFR flush -- three different
# moments, so JIT arena memory cannot be validly subtracted from both sides.
#
# This harness therefore samples cgroup anon directly, on a timestamped
# schedule, and records the value at the exact instant of the NMT snapshot.
# That yields max (comparable to doe's), mean/median (low variance), and a
# synchronous point value that CAN be differenced against NMT coherently.
#
# Read from the host cgroup path rather than `docker exec ... cat`, because
# exec spawns a process inside the target's own cgroup and inflates the very
# number being measured (observed: 1519616 vs 1257472 bytes).
#
# WHY CALIBRATION IS PINNED: loops_num/allocs_num are fixed to the values
# calibration produced, with loops_cpu/allocs_cpu=0, so NeedsCalibration() is
# false. This drops one calibration container per invocation AND removes a
# confound -- each arm previously calibrated independently and could end up
# running a slightly different workload. All other archetype parameters are
# unchanged.
#
# Usage: run_doe_interleaved.sh <out_dir> [pairs]
set -u
OUT="$1"
PAIRS="${2:-12}"
DOE_REPO="${DOE_REPO:-/home/bits/go/src/github.com/DataDog/dd-trace-doe}"
DOE_BIN="${DOE_BIN:-/tmp/doe}"
SAMPLE_INTERVAL="${SAMPLE_INTERVAL:-0.5}"
# Two NMT snapshots per run. t=30 s matches the earlier batches so those numbers
# stay comparable; t=70 s lands in steady state, since anon is still climbing its
# startup ramp at 30 s (measured: whole-run median 1657 MiB vs steady-state
# median 1682 MiB on the same run). The steady-state snapshot is the one whose
# Arena Chunk value can be meaningfully differenced against a steady-state anon
# reading.
NMT_DELAYS="${NMT_DELAYS:-30 70}"

mkdir -p "$OUT/nmt" "$OUT/jfr" "$OUT/logs" "$OUT/anon"

DURATION="${DURATION:-90}"
# DOE_ARGS exists so a long-running experiment can pass --no-build. The agent jar
# is baked into the image (`COPY binaries/ /binaries/`), so a running container is
# unaffected by host-side rebuilds -- but without --no-build a later invocation
# would rebuild the image and silently swap the profiler mid-experiment. Pass
# --no-build for anything running alongside profiler development work.
DOE_ARGS="${DOE_ARGS:-}"

COMMON="archetype=enterprise language=java library_version=local agent=false \
duration=${DURATION} loops_cpu=0 allocs_cpu=0 loops_num=1712244 allocs_num=408773"

# Timestamped cgroup-anon sampler. Emits "<epoch_ms> <bytes>" per line, plus a
# "<epoch_ms> <bytes> NMT" marked line at the NMT snapshot instant.
sample_anon() {
  local cid="$1" outfile="$2"
  local stat="/sys/fs/cgroup/docker/${cid}/memory.stat"
  while [ -r "$stat" ]; do
    local v
    v=$(awk '/^anon /{print $2; exit}' "$stat" 2>/dev/null) || break
    [ -n "$v" ] && printf '%s %s\n' "$(date +%s%3N)" "$v" >> "$outfile"
    sleep "$SAMPLE_INTERVAL"
  done
}

run_one() {
  local prof="$1" pair="$2"
  local tag="pair$(printf '%02d' "$pair")_prof${prof}"
  local log="$OUT/logs/${tag}.log"
  local jfrdir="$OUT/jfr/${tag}"
  local anonfile="$OUT/anon/${tag}.txt"
  : > "$anonfile"

  # EXTRA_JVM_FLAGS is how -XX:+AlwaysPreTouch is applied. Pre-touching pins
  # touched heap pages at the full -Xmx from startup, so GC can no longer move
  # them. That matters because cgroup anon is ~92% touched heap here (2048 MiB
  # committed vs ~1580 MiB anon), and its GC-driven swing (+/-72 MiB within a
  # run) is the dominant noise term -- far larger than the ~25 MiB being
  # measured. NOTE: pre-touching inflates a max-based estimator via its startup
  # page-fault storm, so it must be paired with a steady-state estimator, not
  # with doe's own max(anon) figure.
  local jto="-XX:NativeMemoryTracking=summary ${EXTRA_JVM_FLAGS:-}"
  local -a envs=()
  if [ "$prof" = "true" ]; then
    jto="-Ddd.profiling.debug.jfr.disabled=true $jto"
    mkdir -p "$jfrdir"
    envs+=(DOE_DEBUG_PROFILE_DIR="$jfrdir")
  fi
  envs+=(DOE_DEBUG_JAVA_TOOL_OPTIONS="$jto")

  # MALLINFO_SO, when set, LD_PRELOADs the passive arena sampler
  # (memsweep/mallinfo_sampler.c) into BOTH arms. The profiler reports
  # mallinfo2 itself, but only through its own JFR -- so the tracing-only arm
  # emits nothing and arena waste cannot be attributed. This can, because
  # LD_PRELOAD does not care whether the profiler is attached.
  if [ -n "${MALLINFO_SO:-}" ]; then
    mkdir -p "$OUT/mallinfo/${tag}"
    envs+=(DOE_DEBUG_EXTRA_MOUNT_SRC="$OUT/mallinfo/${tag}")
    envs+=(DOE_DEBUG_EXTRA_MOUNT_DST=/mallinfo)
    envs+=(DOE_DEBUG_EXTRA_ENV="LD_PRELOAD=${MALLINFO_SO_IN_CONTAINER:-/mallinfo/sampler.so};MALLINFO_OUT=/mallinfo;MALLINFO_INTERVAL_MS=${MALLINFO_INTERVAL_MS:-1000}")
    cp "$MALLINFO_SO" "$OUT/mallinfo/${tag}/sampler.so"
    chmod 755 "$OUT/mallinfo/${tag}/sampler.so"
  fi

  ( cd "$DOE_REPO" && env "${envs[@]}" "$DOE_BIN" run $COMMON $DOE_ARGS \
      tracing=true profiling="$prof" -n 1 -f > "$log" 2>&1 ) &
  local pid=$!

  # With calibration pinned there is exactly one app container per invocation,
  # so no calibration container has to be skipped.
  local cid=""
  while kill -0 "$pid" 2>/dev/null; do
    cid=$(grep -oP 'app container started.*container_id=\K[a-f0-9]+' "$log" 2>/dev/null | head -1)
    [ -n "$cid" ] && break
    sleep 2
  done

  local sampler_pid=""
  if [ -n "$cid" ]; then
    sample_anon "$cid" "$anonfile" &
    sampler_pid=$!
    for d in $NMT_DELAYS; do
      ( sleep "$d"
        # Mark the synchronous anon reading FIRST, so it is as close as possible
        # to the NMT snapshot that follows.
        local stat="/sys/fs/cgroup/docker/${cid}/memory.stat"
        local v
        v=$(awk '/^anon /{print $2; exit}' "$stat" 2>/dev/null)
        [ -n "$v" ] && printf '%s %s NMT%s\n' "$(date +%s%3N)" "$v" "$d" >> "$anonfile"
        docker run --rm --pid=container:"$cid" eclipse-temurin:21-jdk \
          jcmd 1 VM.native_memory summary > "$OUT/nmt/${tag}_t${d}.txt" 2>&1 ) &
    done
  else
    echo "  WARN: no container id for $tag"
  fi

  wait "$pid"
  [ -n "$sampler_pid" ] && kill "$sampler_pid" 2>/dev/null
  wait 2>/dev/null

  local mem
  mem=$(grep -oP 'memory=\K[0-9]+' "$log" | tail -1)
  local n_samples
  n_samples=$(wc -l < "$anonfile")
  echo "  $tag doe_max=${mem:-MISSING} anon_samples=${n_samples}"
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
