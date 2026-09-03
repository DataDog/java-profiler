#!/bin/bash
# The customer-facing measurement: naked workload vs full APM, measured with
# this investigation's methodology rather than the original one.
#
# WHY THIS EXISTS. Everything else in this investigation measures the profiler's
# *marginal* cost on top of a tracer that is already running -- the right scope
# for profiler engineering, and the wrong scope for "what does APM cost a
# customer". That question compares a bare workload against tracer+profiler
# together, and nobody has measured it with an estimator that reproduces.
#
# It also completes a three-way set:
#
#   run_doe_original_method.sh   old method,  old scope   -> compare to ~240 MB
#   this script                  new method,  old scope   -> what customers pay
#   the paired plateau batches   new method,  new scope   -> 59-74 MiB profiler
#
# METHOD: everything this investigation established, unlike the sibling script
# which deliberately preserves the original. duration=300 with sampling at
# t >= 240 s (anon does not plateau until t ~ 180 s, so the original 90 s runs
# never reached steady state at all); AlwaysPreTouch, so the heap's contribution
# is constant by construction rather than assumed small; conditions rotated
# within each round so drift cannot land preferentially on one; pinned
# calibration so all three run an identical workload.
#
# BOTH ESTIMATORS, SAME RUNS. Records doe's own `memory=` (a maximum over the
# whole load+stop phase) alongside a 2 Hz cgroup-anon trace summarised as a
# plateau median. Because both come from identical runs, the difference between
# them isolates the estimator exactly -- which is the single largest suspected
# reason the old figure ran high.
#
# THREE CONDITIONS, so the split is recoverable rather than conflated:
#   full APM  = both   - baseline     <- the customer-facing number
#   tracer    = tracer - baseline
#   profiler  = both   - tracer
#
# NO --no-build. doe folds `tracing=` and `profiling=` into the input hash it
# derives the image tag from, so each of the three conditions needs its own
# image and the baseline (tracing=false profiling=false) has never been built.
# With --no-build the run dies with "No such image" before a container starts --
# it produced "no container id" on the first attempt here. Building is safe: the
# agent jar is fixed on disk (chmod 444) and its profiler .so was verified
# byte-identical to the build under test, so a rebuild cannot swap the profiler.
#
# Usage: run_doe_full_apm.sh <out_dir> [rounds]
set -u
OUT="$1"
ROUNDS="${2:-6}"
DOE_REPO="${DOE_REPO:-/home/bits/go/src/github.com/DataDog/dd-trace-doe}"
DOE_BIN="${DOE_BIN:-/tmp/doe}"
DURATION="${DURATION:-300}"
PLATEAU_FROM="${PLATEAU_FROM:-240}"

mkdir -p "$OUT/logs" "$OUT/anon"
: > "$OUT/results.txt"

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
  local cond="$1" tracing="$2" profiling="$3" round="$4"
  local tag="r$(printf '%02d' "$round")_${cond}"
  local log="$OUT/logs/${tag}.log"
  local anonfile="$OUT/anon/${tag}.txt"
  : > "$anonfile"

  ( cd "$DOE_REPO" && env DOE_DEBUG_JAVA_TOOL_OPTIONS="-XX:+AlwaysPreTouch" \
      "$DOE_BIN" run $COMMON \
      tracing="$tracing" profiling="$profiling" -n 1 -f > "$log" 2>&1 ) &
  local pid=$!

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
  else
    echo "  WARN: no container id for $tag"
  fi

  wait "$pid"
  [ -n "$sampler_pid" ] && kill "$sampler_pid" 2>/dev/null
  wait 2>/dev/null

  local mem; mem=$(grep -oP 'memory=\K[0-9]+' "$log" | tail -1)
  printf '%s %s %s %s\n' "$round" "$cond" "${mem:-0}" "$anonfile" >> "$OUT/results.txt"
  printf '  %-18s doe_max=%s MB  anon_samples=%s\n' \
    "$tag" "$(( ${mem:-0} / 1048576 ))" "$(wc -l < "$anonfile")"
}

for r in $(seq 1 "$ROUNDS"); do
  case $(( r % 3 )) in
    1) order="baseline tracer both" ;;
    2) order="tracer both baseline" ;;
    0) order="both baseline tracer" ;;
  esac
  echo "=== round $r (order: $order) ==="
  for c in $order; do
    case "$c" in
      baseline) run_one baseline false false "$r" ;;
      tracer)   run_one tracer   true  false "$r" ;;
      both)     run_one both     true  true  "$r" ;;
    esac
  done
done
echo "ALLDONE"
