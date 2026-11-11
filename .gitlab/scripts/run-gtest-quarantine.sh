#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

# Run one GitLab sanitizer gtest configuration through the flake/quarantine
# machinery shared with the Java cells (.github/scripts/run_tests_with_retry.sh
# -> flake_report.py -> ddprof-test/quarantine.txt).
#
# Invoked from .gitlab/sanitizer-tests/.gitlab-ci.yml after
# buildGtest${SANITIZER_CONFIG}. With --attempt it runs one attempt (every
# binary of the configuration); that is the command the retry wrapper
# re-executes, so the retry is a full re-run of the suite, never a filtered
# replay of the failures.
#
# Required environment:
#   SANITIZER_LC   binary selector and cell config token (asan, tsan, release)
#   GTEST_ARCH     cell arch token: amd64 or aarch64 -- the quarantine cell
#                  universe's spelling (KNOWN_ARCHES), not the GitLab runner
#                  tag's "arm64"; a glob naming an arch CI never builds
#                  quarantines nothing.
#
# Recognized environment:
#   GTEST_DEATH_TEST_STYLE     inherited by the binaries (the tsan jobs set
#                              threadsafe in their job definition)
#   MAX_ATTEMPTS               retry budget (run_tests_with_retry.sh default: 2)
#
# Cell: glibc-<config>-<arch>. The gtest binaries never link a JDK, so the
# Java cell's jdk axis is genuinely absent (see the gtest section of
# ddprof-test/quarantine.txt).

set -uo pipefail

if [ -z "${SANITIZER_LC:-}" ] || [ -z "${GTEST_ARCH:-}" ]; then
  echo "SANITIZER_LC and GTEST_ARCH must both be set (e.g. asan / aarch64)" >&2
  exit 1
fi

HERE=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
REPO_ROOT=$(cd "${HERE}/../.." && pwd)
cd "${REPO_ROOT}" || exit 1

RESULTS_DIR="ddprof-lib/build/test-results/gtest/${SANITIZER_LC}"

# Config-specific environment, set before the --attempt branch so it holds on
# every path: the wrapper re-executes this script, and the attempt subprocess
# must not depend on the main invocation having exported these.
if [ "${SANITIZER_LC}" = "asan" ]; then
  # ASan init can nondeterministically collide with the process's
  # ASLR-influenced mmap layout (google/sanitizers#856): the binary aborts
  # before any test runs, naming no test. Same setting the GitHub asan matrix
  # uses for the same reason. Consumed by run_tests_with_retry.sh.
  export RETRY_ON_NO_TEST_FAILURES=1
fi

if [ "${SANITIZER_LC}" = "tsan" ]; then
  # TSan's defaults (halt_on_error=0, exitcode=66) report every race and
  # exit 66 at process exit -- after gtest has written a passing JUnit XML,
  # so neither the abort marker nor the >128 exit check would fire. Halting
  # on the first race kills the binary before the XML is written and routes
  # the failure through the ABORTED path; the race report itself still goes
  # to the log first.
  export TSAN_OPTIONS="${TSAN_OPTIONS:+${TSAN_OPTIONS}:}halt_on_error=1"
fi

if [ "${1:-}" = "--attempt" ]; then
  # A stale TEST-*.xml from a reused workspace or a failed earlier clear
  # would satisfy the -s check below and defeat the ABORTED detection --
  # the exact false-green this marker exists to prevent. The wrapper clears
  # RESULTS_DIR between attempts; this also covers direct --attempt runs.
  rm -rf "${RESULTS_DIR}" || {
    echo "cannot clear ${RESULTS_DIR}; attempt evidence would not be this attempt's own" >&2
    exit 3
  }
  mkdir -p "${RESULTS_DIR}"
  # Run EVERY binary and aggregate instead of exiting at the first failure:
  # a single quarantined failure must not hide the rest of the suite from the
  # evidence (and the old first-failure exit did exactly that).
  # find's status is taken alone, before filtering: with pipefail a pipeline
  # status cannot tell a failed find from grep's zero-match exit 1.
  # -perm -u+x, not GNU's -executable: both GNU and BSD find support the
  # former, so the script also runs on macOS/BSD hosts.
  all_binaries=$(find ddprof-lib/build/bin/gtest -mindepth 2 -maxdepth 2 -type f -perm -u+x) || {
    echo "find over ddprof-lib/build/bin/gtest failed (status $?); check the build output directory" >&2
    exit 2
  }
  binaries=$(printf '%s\n' "${all_binaries}" | grep "/${SANITIZER_LC}_" | sort)
  if [ -z "${binaries}" ]; then
    echo "no gtest binaries matching /${SANITIZER_LC}_ under ddprof-lib/build/bin/gtest; the build produced nothing runnable"
    exit 1
  fi
  first_rc=0
  hard_rc=0
  while IFS= read -r binary; do
    echo ""
    echo "=== $(basename "$binary") ==="
    # One XML per binary, named TEST-*.xml: the name flake_report.py globs.
    xml_path="${RESULTS_DIR}/TEST-$(basename "$binary").xml"
    "$binary" --gtest_output="xml:${xml_path}"
    bin_rc=$?
    if [ "${bin_rc}" -ne 0 ]; then
      echo "FAILED: $(basename "$binary") exited ${bin_rc}"
      if ! [ -s "${xml_path}" ]; then
        # gtest writes the XML at exit, so a binary aborted by a sanitizer
        # diagnostic (ASan exit 1, TSan exit 66 -- no signal involved) leaves
        # none. flake_report.py greps this marker from the attempt log and
        # reads the run as cut short: the aborted binary's unrecorded tests
        # must not be excused by another binary's quarantined failures.
        echo "ABORTED: $(basename "$binary") exited ${bin_rc} without producing test results"
        if [ "${hard_rc}" -eq 0 ]; then hard_rc=${bin_rc}; fi
      elif [ "${bin_rc}" -gt 128 ]; then
        # A signal death (128+N) is the same cut-short evidence, visible
        # from the exit code alone; rc 128 counts as plain, matching
        # flake_report.py's strict >128 check.
        if [ "${hard_rc}" -eq 0 ]; then hard_rc=${bin_rc}; fi
      elif [ "${first_rc}" -eq 0 ]; then
        first_rc=${bin_rc}
      fi
    fi
  done <<< "${binaries}"
  if [ "${hard_rc}" -ne 0 ]; then
    exit "${hard_rc}"
  fi
  exit "${first_rc}"
fi

CELL="glibc-${SANITIZER_LC}-${GTEST_ARCH}"
RESULTS_DIR="${RESULTS_DIR}" \
  .github/scripts/run_tests_with_retry.sh \
  --list ddprof-test/quarantine.txt \
  "${CELL}" -- \
  bash .gitlab/scripts/run-gtest-quarantine.sh --attempt
