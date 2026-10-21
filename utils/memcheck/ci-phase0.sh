#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Runs Phase 0 directly on a CI runner, without a container: records the
# runner's shape, builds the release library from the checked-out tree, then
# runs phase0.sh. The JSON records land in OUT/runs, and OUT gets the same
# metadata files as phase0-container.sh, so analyze_phase0.py reads it as is.
#
# It cannot pin cores: on the shared GitLab amd64 runners a pod's CPU set
# differs between jobs (52 to 93 CPUs in the first CI run) and changes during
# a job. Pinning to fixed CPU IDs with taskset made the JVM fall back to
# Serial GC in most runs, as it does when it sees a single CPU.
# run_scenario.sh instead sets -XX:ActiveProcessorCount=$CPUS and the
# collector, so the JVM sizes itself for CPUS cores on any pod. runner.txt
# records the pod's shape (CPU count and quota, CPU model, memory limit).
#
# Usage: ci-phase0.sh [OUT]   (default OUT: build/memcheck)
#   CPUS (4), REPS, NOPROF_REPS, SCENARIOS, STEADY_MS, DUMP_AFTER_MS, SAMPLE_DELAY_S
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
OUT="$(mkdir -p "${1:-$ROOT/build/memcheck}" && cd "${1:-$ROOT/build/memcheck}" && pwd)"
export CPUS="${CPUS:-4}"

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
} > "$OUT/runner.txt" 2>&1 || true

git -C "$ROOT" rev-parse HEAD > "$OUT/profiler-commit.txt"
# grep, not head -1: CI sets JAVA_TOOL_OPTIONS, which java reports first.
java -version 2>&1 | grep -m1 ' version ' > "$OUT/jdk.txt"
# The CPU count the JVMs are sized for (-XX:ActiveProcessorCount).
echo "$CPUS" > "$OUT/cpus.txt"

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
"$HERE/phase0.sh" 2>&1 | tee "$OUT/phase0.log"
