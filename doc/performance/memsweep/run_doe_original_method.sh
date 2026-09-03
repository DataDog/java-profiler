#!/bin/bash
# Reproduce the ORIGINAL dd-trace-doe overhead measurement with the CURRENT
# profiler build, to answer one question:
#
#   Does the profiler's share still come out near ~104 MB under the old method?
#
# The August 2026 reproduction measured, against a 1514 MB no-APM baseline:
# tracer +136.1 MB, profiler +104.3 MB, total ~240 MB (original claim ~250).
# This investigation later measured the profiler at 59-74 MiB -- but by a
# different method AND a different scope. If the old method still yields ~104 MB
# on today's build, the entire gap is measurement. If it yields less, part of it
# is a genuine footprint improvement and can be claimed as one.
#
# DELIBERATELY THE OLD METHOD. None of this investigation's improvements are
# applied: no AlwaysPreTouch, no plateau sampling, no custom anon sampler, no
# interleaved pairing. duration=90 as originally run, and the metric is doe's own
# `memory=` field -- a maximum over the whole load+stop phase. That estimator is
# the thing under test and must not be replaced.
#
# THREE CONDITIONS, because the old figure and the new one differ in scope as
# well as method. The old number is baseline -> tracer+profiler, so it contains
# the tracer's ~136 MB; the new number is tracing-only -> tracing+profiling, where
# the tracer runs in both arms and cancels. Measuring all three recovers the split:
#
#   total    = both     - baseline
#   tracer   = tracer   - baseline
#   profiler = both     - tracer      <- the figure to compare against ~104 MB
#
# TWO DEVIATIONS FROM "PLAIN", both stated rather than hidden:
#
#  * Calibration is pinned to the same values used throughout this investigation.
#    Left unpinned, each condition calibrates independently and can end up running
#    a slightly different workload -- a confound in the comparison, not a property
#    of the estimator. Pinning removes it without touching what is being tested.
#  * Conditions rotate within each repetition rather than running blocked. Blocked
#    ordering would let machine drift land preferentially on one condition and
#    masquerade as an effect. This is not "plateau sampling by the back door" --
#    the estimator is untouched.
#
# Usage: run_doe_original_method.sh <out_dir> [reps]
set -u
OUT="$1"
REPS="${2:-5}"
DOE_REPO="${DOE_REPO:-/home/bits/go/src/github.com/DataDog/dd-trace-doe}"
DOE_BIN="${DOE_BIN:-/tmp/doe}"
DURATION="${DURATION:-90}"

mkdir -p "$OUT/logs"
: > "$OUT/results.txt"

COMMON="archetype=enterprise language=java library_version=local agent=false \
duration=${DURATION} loops_cpu=0 allocs_cpu=0 loops_num=1712244 allocs_num=408773"

run_one() {
  local cond="$1" tracing="$2" profiling="$3" rep="$4"
  local tag="rep$(printf '%02d' "$rep")_${cond}"
  local log="$OUT/logs/${tag}.log"

  ( cd "$DOE_REPO" && "$DOE_BIN" run $COMMON \
      tracing="$tracing" profiling="$profiling" -n 1 -f > "$log" 2>&1 )

  local mem
  mem=$(grep -oP 'memory=\K[0-9]+' "$log" | tail -1)
  if [ -z "$mem" ]; then
    echo "  $tag  MISSING  (see $log)"
    grep -iE "^.*(ERR|error response|failed)" "$log" | tail -2 | sed 's/^/      /'
    return
  fi
  printf '%s %s %s\n' "$rep" "$cond" "$mem" >> "$OUT/results.txt"
  printf '  %-22s memory=%s MB\n' "$tag" "$(( mem / 1048576 ))"
}

for r in $(seq 1 "$REPS"); do
  echo "=== rep $r ==="
  run_one baseline false false "$r"
  run_one tracer   true  false "$r"
  run_one both     true  true  "$r"
done
echo "ALLDONE"
