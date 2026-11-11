#! /bin/bash

# Copyright 2026, Datadog, Inc

# Run every gtest binary of one build configuration and gate the outcome on
# the flaky-test quarantine list (ddprof-test/quarantine.txt) — the same list
# the GitHub Actions Java jobs gate on. Quarantined failures still report
# (every binary runs to completion, failures are printed); they just do not
# turn the job red. Un-quarantined failures, or a binary that exited non-zero
# without naming any test (crash, harness error), fail the job.
#
# Usage: [EXTRA_ENV=... ...] run-gtests.sh <release|asan|tsan|debug>
#
# The quarantine cell is glibc-gtest-<config>-<arch>: the gtest binaries do
# not run under a target JDK, so the jdk slot of the usual
# <libc>-<jdk>-<config>-<arch> cell shape names the runner kind instead.

set -uo pipefail

case "${1:-}" in
  release|asan|tsan|debug) CONFIG_LC="$1" ;;
  *) echo "usage: $0 <release|asan|tsan|debug>" >&2; exit 2 ;;
esac

EVIDENCE="ddprof-lib/build/gtest-results/${CONFIG_LC}"
# Stale results must never excuse a failing binary (the same reason
# flake_report.py's caller clears the evidence dir between attempts).
rm -rf "$EVIDENCE"
mkdir -p "${EVIDENCE}/rc"

find ddprof-lib/build/bin/gtest -mindepth 2 -maxdepth 2 -type f -executable \
  | grep "/${CONFIG_LC}_" \
  | sort \
  | while read -r binary; do
      name=$(basename "$binary")
      echo ""
      echo "=== ${name} ==="
      # The loop must keep running past a failing binary so every suite
      # reports; the gate below, not this loop's exit code, owns the verdict.
      "$binary" --gtest_output="xml:${EVIDENCE}/TEST-${name}.xml"
      rc=$?
      echo "$rc" > "${EVIDENCE}/rc/${name}"
      if [ "$rc" -ne 0 ]; then
        echo "FAILED: ${name} exited ${rc}"
      fi
    done

# A matching but non-executable binary is skipped by find -executable above;
# running a subset of the suites must not read as a complete passing run.
missing=$(find ddprof-lib/build/bin/gtest -mindepth 2 -maxdepth 2 -type f ! -executable \
  2>/dev/null | grep "/${CONFIG_LC}_" || true)
if [ -n "$missing" ]; then
  echo "GATE: matching gtest binaries are not executable, refusing to run a subset:"
  echo "$missing"
  exit 1
fi

# pipefail: a non-zero pipeline status here means the binary set was empty
# (grep matched nothing) or find itself failed — that is a broken job, not a
# passing one; it must not reach the gate and read as a clean run.
pipeline_rc=$?
if [ "$pipeline_rc" -ne 0 ]; then
  echo "GATE: no gtest binaries found for ${CONFIG_LC} (pipeline exited ${pipeline_rc})"
  exit 1
fi

python3 "$(cd "$(dirname "$0")" && pwd)/gtest_quarantine_gate.py" \
  --evidence "$EVIDENCE" --cell "glibc-gtest-${CONFIG_LC}-$(uname -m | sed 's/^x86_64$/amd64/')"
