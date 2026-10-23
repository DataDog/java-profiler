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

if [ "$failures" -ne 0 ]; then
  echo "$failures test(s) failed"
  exit 1
fi
echo "all evaluate tests passed"
