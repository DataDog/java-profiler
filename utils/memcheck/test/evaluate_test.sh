#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Tests for utils/memcheck/src/Evaluate.java: builds small run records and
# budget files, runs the evaluator, and checks its exit status and report.
# Needs JDK 11+ on the PATH (single-file source launch).
#
# Usage: evaluate_test.sh
set -uo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EVALUATE="$HERE/../src/Evaluate.java"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
failures=0

# record <dir> <scenario> <arm> <rep> <counters-json> <nmt_kb-json> [proc_kb-json]
record() {
  mkdir -p "$1/runs"
  printf '{"scenario":"%s","arm":"%s","rep":%s,"counters":%s,"counters_middump":{},"nmt_kb":%s,"proc_kb":%s}\n' \
    "$2" "$3" "$4" "$5" "$6" "${7:-{\}}" > "$1/runs/$2-$3-$4.json"
}

# check <name> <expected-exit> <budget-text> <grep-pattern>...   (records from $RUN)
check() {
  local name=$1 want=$2 budget=$3 rc pattern
  shift 3
  printf '%s\n' "$budget" > "$TMP/budget.txt"
  java "$EVALUATE" "$TMP/budget.txt" "$TMP/report.md" "$RUN" > "$TMP/stdout.txt" 2>&1
  rc=$?
  if [ "$rc" -ne "$want" ]; then
    echo "FAIL $name: exit $rc, want $want"; cat "$TMP/stdout.txt"; failures=$((failures + 1)); return
  fi
  for pattern in "$@"; do
    if ! grep -qF -- "$pattern" "$TMP/report.md"; then
      echo "FAIL $name: report lacks '$pattern'"; cat "$TMP/report.md"; failures=$((failures + 1)); return
    fi
  done
  echo "ok   $name"
}

R="$TMP/run"
# Two profiled runs and one no-profiler run of "alpha", one of each of "beta".
record "$R" alpha nmt 1 '{"native_mem_max_bytes":1048576,"line_number_tables":105}' '{"class":3000,"internal":500}' '{"VmRSS":200000}'
record "$R" alpha nmt 2 '{"native_mem_max_bytes":1153434,"line_number_tables":115}' '{"class":3010,"internal":520}' '{"VmRSS":202000}'
record "$R" alpha noprof 1 '{}' '{"class":1000,"internal":400}' '{"VmRSS":180000}'
record "$R" beta nmt 1 '{"native_mem_max_bytes":2097152,"line_number_tables":7}' '{"class":10}'
record "$R" beta noprof 1 '{}' '{"class":10}'
echo "deadbeefcafe" > "$R/profiler-commit.txt"
RUN="$R"

# alpha native_mem_max_bytes: mean of 1 MiB and 1.1 MiB = 1.05 MiB.
check "counter within budget" 0 "alpha native_mem_max_bytes 2MiB 1MiB" \
  "within budget" "| alpha | \`native_mem_max_bytes\` | 1.05 MiB | +51 KiB | 2.00 MiB | 973 KiB | ok |" "Profiler \`deadbeefc\`"
check "counter over budget" 1 "alpha native_mem_max_bytes 1MiB 1MiB" \
  "over budget" "❌ OVER" "raise the limit"
# NMT class: (3000 + 3010) / 2 - 1000 = 2005 KiB = 1.96 MiB; internal: 510 - 400 = 110 KiB.
check "nmt delta" 0 $'alpha nmt.class 3MiB -\nalpha nmt.internal 200KiB 100KiB' \
  "| alpha | \`nmt.class\` | 1.96 MiB |  | 3.00 MiB |" "| alpha | \`nmt.internal\` | 110 KiB | +10 KiB | 200 KiB | 90 KiB | ok |"
# proc: (200000 + 202000) / 2 - 180000 = 21000 KiB.
check "proc delta, report only" 0 "alpha proc.VmRSS - -" "| scenario | \`proc.VmRSS\` |" "| alpha | 20.51 MiB |"
# Coverage: mean methods 110, ref 100, 1 KiB each: 1.05 MiB - 10 KiB = 1065 KiB = 1.04 MiB.
check "coverage correction" 0 "alpha native_mem_max_bytes 1.1MiB - per_method=1024 ref_methods=100" \
  "(coverage-corrected) | 1.04 MiB |"
check "wildcard covers each scenario" 0 "* nmt.class 3MiB -" "| alpha | \`nmt.class\`" "| beta | \`nmt.class\` | 0 KiB |"
check "tripwire absent" 0 "* nmt.tracing absent -" "✅ \`nmt.tracing\` absent in every scenario."

# A profiled run in which the Tracing category appeared.
R2="$TMP/run2"
cp -r "$R" "$R2"
record "$R2" beta nmt 2 '{"native_mem_max_bytes":2097152}' '{"class":10,"tracing":64}'
RUN="$R2"
check "tripwire present" 1 "* nmt.tracing absent -" "❌ \`nmt.tracing\` must be absent but appeared in: beta."
RUN="$R"

check "no records for a budgeted scenario" 2 "gamma native_mem_max_bytes 1MiB -" \
  "incomplete" "no profiled runs for scenario gamma (budget line 1)"
check "unknown counter" 2 "alpha native_mem_bogus 1MiB -" "no counter native_mem_bogus in scenario alpha"
check "bad size" 2 "alpha native_mem_max_bytes 1MB -" "budget line 1: '1MB' is not a size"
check "missing measured column" 2 "alpha native_mem_max_bytes 1MiB" "budget line 1: expected"
check "half of the coverage options" 2 "alpha native_mem_max_bytes 1MiB - per_method=1" "per_method and ref_methods go together"
check "absent on a counter" 2 "alpha native_mem_max_bytes absent -" "'absent' only applies to nmt.<category>"
check "comments and blank lines" 0 $'# header\n\nalpha native_mem_max_bytes 2MiB -   # trailing' "| alpha | \`native_mem_max_bytes\` | 1.05 MiB |"

# calibrate <name> <expected-exit> <budget-text> <grep-pattern>...   (job dirs from $JOBS)
# Patterns are checked in the written budget on success, in stderr on failure.
calibrate() {
  local name=$1 want=$2 budget=$3 rc pattern out
  shift 3
  printf '%s\n' "$budget" > "$TMP/budget.txt"
  rm -f "$TMP/new-budget.txt"
  # shellcheck disable=SC2086
  java "$EVALUATE" --calibrate "$TMP/budget.txt" "$TMP/new-budget.txt" $JOBS > "$TMP/stdout.txt" 2> "$TMP/stderr.txt"
  rc=$?
  if [ "$rc" -ne "$want" ]; then
    echo "FAIL $name: exit $rc, want $want"; cat "$TMP/stdout.txt" "$TMP/stderr.txt"; failures=$((failures + 1)); return
  fi
  out="$TMP/new-budget.txt"
  if [ "$want" -ne 0 ]; then
    out="$TMP/stderr.txt"
    if [ -e "$TMP/new-budget.txt" ]; then
      echo "FAIL $name: wrote a budget despite errors"; failures=$((failures + 1)); return
    fi
  fi
  for pattern in "$@"; do
    if ! grep -qF -- "$pattern" "$out"; then
      echo "FAIL $name: output lacks '$pattern'"; cat "$out"; failures=$((failures + 1)); return
    fi
  done
  echo "ok   $name"
}

MIB=1048576
# Two calibration jobs. flat: 10 MiB in every run. noisy: job 1 runs 10 MiB -/+ 100 KiB.
# cov: native_mem_max_bytes = 1 MiB + 500 B per method above 1000; methods 1000/1020
# (profiled) and 1100/1300 (counters-only) in both jobs, mean 1105 over both arms. NMT class:
# job 1 3000 KiB, job 2 3100 KiB profiled, 1000 KiB no-profiler in both.
C1="$TMP/cal/memcheck-1"
C2="$TMP/cal/memcheck-2"
for j in 1 2; do
  dir="$TMP/cal/memcheck-$j"
  class=$((2900 + 100 * j))
  for rep in 1 2; do
    noisy=$((10 * MIB + (2 * rep - 3) * 102400 * (2 - j)))
    m=$((980 + 20 * rep))
    record "$dir" flat nmt "$rep" "{\"native_mem_max_bytes\":$((10 * MIB))}" "{\"class\":$class}"
    record "$dir" noisy nmt "$rep" "{\"native_mem_max_bytes\":$noisy}" '{}'
    record "$dir" cov nmt "$rep" "{\"native_mem_max_bytes\":$((MIB + 500 * (m - 1000))),\"line_number_tables\":$m}" '{}'
    cm=$((900 + 200 * rep))
    record "$dir" cov counters "$rep" "{\"native_mem_max_bytes\":$((MIB + 500 * (cm - 1000))),\"line_number_tables\":$cm}" '{}'
  done
  record "$dir" flat noprof 1 '{}' '{"class":1000}'
  record "$dir" single nmt 1 "{\"native_mem_max_bytes\":$MIB}" '{}'
done
JOBS="$C1 $C2"

# SD 0: limit = 10 MiB + the 256 KiB floor = 10.25 MiB exactly, which must not round up to 10.30.
calibrate "floor, exact multiple kept" 0 "flat native_mem_max_bytes 1MiB 1MiB" \
  "flat      native_mem_max_bytes   10.25MiB  10.00MiB   # SD 0 KiB, per-job spread 0 KiB"
# Job 1 SD = 141 KiB, 4 * SD = 566 KiB > floor: 10 MiB + 566 KiB = 10.55 MiB, rounded up to 10.60.
calibrate "4 SD term, rounded up" 0 "noisy native_mem_max_bytes 1MiB 1MiB" \
  "noisy     native_mem_max_bytes   10.60MiB  10.00MiB   # SD 141 KiB"
# Per-job deltas 2000 and 2100 KiB: measured 2050 KiB = 2.00 MiB, limit 2306 KiB = 2.25 -> 2.30.
calibrate "nmt per-job delta and spread" 0 "flat nmt.class 1MiB 1MiB" \
  "flat      nmt.class              2.30MiB  2.00MiB   # SD 0 KiB, per-job spread 100 KiB"
# Slope 500 B, ref = mean 1105 over both arms rounded to 1100 (profiled runs alone: 1000);
# corrected value 1 MiB + 500 * (1100 - 1000) B = 1.05 MiB, limit 1.30 MiB.
calibrate "coverage slope over both arms" 0 "cov native_mem_max_bytes 1MiB 1MiB per_method=1 ref_methods=1" \
  "1.30MiB  1.05MiB  per_method=500 ref_methods=1100"
calibrate "kept lines" 0 $'# header comment\nflat native_mem_max_bytes 1MiB 1MiB\n* nmt.tracing absent -\nflat nmt.code - -' \
  "# header comment" "* nmt.tracing absent -" "flat nmt.code - -"
calibrate "calibrated budget accepts its own data" 0 "flat native_mem_max_bytes 1MiB 1MiB"
if java "$EVALUATE" "$TMP/new-budget.txt" "$TMP/report.md" $JOBS > /dev/null 2>&1; then
  echo "ok   calibrated budget passes evaluation"
else
  echo "FAIL calibrated budget passes evaluation"; cat "$TMP/report.md"; failures=$((failures + 1))
fi

calibrate "one profiled run per job" 2 "single native_mem_max_bytes 1MiB 1MiB" \
  "budget line 1: every job needs at least 2 profiled runs of single"
calibrate "no no-profiler runs" 2 "noisy nmt.class 1MiB 1MiB" "a job has no no-profiler runs of noisy"
calibrate "missing counter" 2 "flat native_mem_bogus 1MiB 1MiB" "lacks counter native_mem_bogus"
calibrate "no coverage variation" 2 "flat native_mem_max_bytes 1MiB 1MiB per_method=1 ref_methods=1" \
  "line_number_tables does not vary in flat"
# NMT class 100 KiB profiled, 200 KiB without the profiler: a delta of -100 KiB.
NEG="$TMP/neg"
for j in 1 2; do
  for rep in 1 2; do record "$NEG/memcheck-$j" low nmt "$rep" '{}' '{"class":100}'; done
  record "$NEG/memcheck-$j" low noprof 1 '{}' '{"class":200}'
done
JOBS="$NEG/memcheck-1 $NEG/memcheck-2"
calibrate "negative measured" 2 "low nmt.class 1MiB 1MiB" "is negative"

if [ "$failures" -ne 0 ]; then
  echo "$failures test(s) failed"
  exit 1
fi
echo "all evaluate tests passed"
