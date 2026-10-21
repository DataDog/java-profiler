#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Runs Phase 0 directly on a CI runner, without a container: records the
# runner's shape, builds the release library from the checked-out tree, then
# runs phase0.sh. The JSON records land in OUT/runs, and OUT gets the same
# metadata files as phase0-container.sh, so analyze_phase0.py reads it as is.
#
# The shared GitLab amd64 runners give a pod a different set of CPUs per job
# (52 to 93 of them in the first CI run) and no CPU quota, so the JVM sizes
# its GC and compiler threads differently in every job. The scenarios
# therefore run under taskset on the first CPUS of the CPUs the pod is allowed,
# so the JVM, nproc and the profiler all see CPUS cores, as with the pinned
# container runs. runner.txt records the pod's own shape (CPU count and quota,
# CPU model, memory limit) and the pinned set.
#
# Usage: ci-phase0.sh [OUT]   (default OUT: build/memcheck)
#   CPUS (4), REPS, NOPROF_REPS, SCENARIOS, STEADY_MS, DUMP_AFTER_MS, SAMPLE_DELAY_S
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
OUT="$(mkdir -p "${1:-$ROOT/build/memcheck}" && cd "${1:-$ROOT/build/memcheck}" && pwd)"
CPUS="${CPUS:-4}"

# Prints the first $1 CPUs of this process's affinity list (e.g. "0-3,8,10-12")
# as a taskset list, or fails if fewer are allowed.
first_allowed_cpus() {
  local want=$1 part lo hi c
  local -a parts picked=()
  IFS=, read -ra parts <<< "$(awk '/^Cpus_allowed_list/ {print $2}' /proc/self/status)"
  for part in "${parts[@]}"; do
    lo=${part%-*}
    hi=${part#*-}
    for ((c = lo; c <= hi && ${#picked[@]} < want; c++)); do
      picked+=("$c")
    done
  done
  if [ "${#picked[@]}" -lt "$want" ]; then
    echo "only ${#picked[@]} CPUs allowed, need $want" >&2
    return 1
  fi
  (IFS=,; echo "${picked[*]}")
}
PIN_CPUS="$(first_allowed_cpus "$CPUS")"

# Best effort: a missing file must not fail the job.
{
  echo "ci_job: ${CI_JOB_ID:-} node ${CI_NODE_INDEX:-}/${CI_NODE_TOTAL:-}"
  echo "ci_runner: ${CI_RUNNER_ID:-} ${CI_RUNNER_DESCRIPTION:-}"
  echo "hostname: $(hostname)"
  echo "kernel: $(uname -r)"
  echo "nproc: $(nproc)"
  echo "cpu.max: $(cat /sys/fs/cgroup/cpu.max 2>/dev/null \
    || echo "v1 $(cat /sys/fs/cgroup/cpu/cpu.cfs_quota_us 2>/dev/null) $(cat /sys/fs/cgroup/cpu/cpu.cfs_period_us 2>/dev/null)")"
  echo "cpu_model: $(grep -m1 'model name' /proc/cpuinfo | cut -d: -f2-)"
  echo "mem_total: $(grep MemTotal /proc/meminfo | awk '{print $2, $3}')"
  echo "memory.max: $(cat /sys/fs/cgroup/memory.max 2>/dev/null \
    || cat /sys/fs/cgroup/memory/memory.limit_in_bytes 2>/dev/null)"
  echo "pid_max: $(cat /proc/sys/kernel/pid_max)"
  echo "perf_event_paranoid: $(cat /proc/sys/kernel/perf_event_paranoid)"
  # CI's JAVA_TOOL_OPTIONS (proxy settings, internal host lists) stays out.
  java -XshowSettings:system -version 2>&1 | grep -v '^Picked up JAVA_TOOL_OPTIONS'
  echo "pinned_cpus: $PIN_CPUS"
  echo "pinned_nproc: $(taskset -c "$PIN_CPUS" nproc)"
} > "$OUT/runner.txt" 2>&1 || true

git -C "$ROOT" rev-parse HEAD > "$OUT/profiler-commit.txt"
# grep, not head -1: CI sets JAVA_TOOL_OPTIONS, which java reports first.
java -version 2>&1 | grep -m1 ' version ' > "$OUT/jdk.txt"
taskset -c "$PIN_CPUS" nproc > "$OUT/cpus.txt"

cd "$ROOT"
./gradlew -q --console=plain --no-daemon :ddprof-lib:assembleReleaseJar \
  -Pskip-tests -Pskip-gtest -Pskip-debug-extraction=true > "$OUT/build.log" 2>&1 \
  || { echo "build failed, see $OUT/build.log"; tail -50 "$OUT/build.log"; exit 1; }

export DDPROF_LIB
DDPROF_LIB="$(find "$ROOT/ddprof-lib/build/lib/main/release" -name libjavaProfiler.so | head -1)"
export DDPROF_CLASSES="$ROOT/ddprof-lib/build/classes/java/main"
# Scratch space (generated classes, JFR files) outside the job's artifact
# paths, which match build/memcheck-*.
export MEMCHECK_CLASSES="$ROOT/build/mc-scratch/classes"
export WORKDIR="$ROOT/build/mc-scratch"
export OUTDIR="$OUT/runs"
taskset -c "$PIN_CPUS" "$HERE/phase0.sh" 2>&1 | tee "$OUT/phase0.log"
