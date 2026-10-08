#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Phase 0 noise measurement: runs every scenario REPS times in the counters and
# nmt arms, and NOPROF_REPS times in the noprof control arm. Repetitions are
# interleaved (rep 1 of everything, then rep 2, ...) so slow machine drift is
# spread across all scenarios and arms instead of landing on one of them.
# A failed run is logged and skipped; the loop carries on.
#
# Usage: phase0.sh   (environment as for run_scenario.sh, plus)
#   REPS (10), NOPROF_REPS (3), SCENARIOS ("threads traces classesM allocs mixed")
set -uo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPS="${REPS:-10}"
NOPROF_REPS="${NOPROF_REPS:-3}"
SCENARIOS="${SCENARIOS:-threads traces classesM allocs mixed}"
JAVAC="${JAVA_HOME:+$JAVA_HOME/bin/}javac"

mkdir -p "$MEMCHECK_CLASSES" "$OUTDIR"
"$JAVAC" -cp "$DDPROF_CLASSES" -d "$MEMCHECK_CLASSES" "$HERE"/src/*.java || exit 1

failures=0
for rep in $(seq 1 "$REPS"); do
  for scenario in $SCENARIOS; do
    arms="counters nmt"
    [ "$rep" -le "$NOPROF_REPS" ] && arms="$arms noprof"
    for arm in $arms; do
      if ! "$HERE/run_scenario.sh" "$scenario" "$arm" "$rep"; then
        failures=$((failures + 1))
      fi
    done
  done
done
echo "phase0 done: $failures failed run(s)"
