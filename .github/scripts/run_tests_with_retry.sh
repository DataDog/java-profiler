#!/usr/bin/env bash
# Run a test suite, retry once to find out whether a failure reproduces, and
# let the quarantine list -- not the retry -- decide whether the job goes red.
#
# Usage: run_tests_with_retry.sh [--list <quarantine file>] <cell> -- <command...>
#
# The command is passed through verbatim, so a caller can hand over a plain
# ./gradlew invocation, one wrapped in setarch, or the docker run that drives
# the Alpine aarch64 suite.
#
# Environment:
#   MAX_ATTEMPTS               attempts to allow (default 2; 1 disables retry)
#   MAX_FAILURES_TO_RETRY      don't retry past this many failed tests (default 3)
#   RETRY_ON_NO_TEST_FAILURES  retry a failure that named no test (default 0)
#
# The retry buys a label, not a pass. A test that fails then passes is flaky; a
# test that fails twice is broken. Both still fail the build unless quarantined
# -- the difference decides what the PR comment advises, not whether CI is green.
#
# A retry is spent only when the shape of the failure suggests it might not
# reproduce: a handful of failed tests. A suite where fifty tests went red, or
# where none did (a compile error, an OOM-killed runner, a JVM that never
# started), is not flakiness and a second run only doubles the wait.
#
# The retry is a full re-run rather than a `--tests` filter over the failures.
# Re-running a test alone would clear any failure that only happens in company
# -- an ordering or shared-state bug -- and a test mislabelled "flaky" invites a
# quarantine entry that buries a real defect.

set -uo pipefail

QUARANTINE_LIST="ddprof-test/quarantine.txt"
if [ "${1:-}" = "--list" ]; then
  QUARANTINE_LIST="$2"
  shift 2
fi

CELL="${1:?usage: run_tests_with_retry.sh [--list <file>] <cell> -- <command...>}"
shift
[ "${1:-}" = "--" ] && shift

MAX_ATTEMPTS="${MAX_ATTEMPTS:-2}"
MAX_FAILURES_TO_RETRY="${MAX_FAILURES_TO_RETRY:-3}"
RETRY_ON_NO_TEST_FAILURES="${RETRY_ON_NO_TEST_FAILURES:-0}"

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RESULTS_DIR="ddprof-test/build/test-results"
EVIDENCE_DIR="flake-evidence"
OUTCOME_FILE="ci-outcome/${CELL}.json"

# Snapshot this attempt's JUnit XML before the next one overwrites it -- the
# whole point is to compare attempts, and Gradle reuses the same directory.
snapshot() {
  local attempt="$1"
  local dest="${EVIDENCE_DIR}/attempt-${attempt}"
  rm -rf "$dest"
  mkdir -p "$dest"
  if [ -d "$RESULTS_DIR" ]; then
    cp -r "$RESULTS_DIR"/. "$dest"/ 2>/dev/null || true
  fi
}

EXIT_CODE=1
for attempt in $(seq 1 "$MAX_ATTEMPTS"); do
  mkdir -p build/logs
  rm -rf "$RESULTS_DIR"

  "$@" 2>&1 \
    | tee -a build/test-raw.log \
    | python3 -u "${HERE}/filter_gradle_log.py"
  EXIT_CODE=${PIPESTATUS[0]}

  snapshot "$attempt"

  if [ "$EXIT_CODE" -eq 0 ]; then
    break
  fi

  if [ "$attempt" -ge "$MAX_ATTEMPTS" ]; then
    break
  fi

  failed=$(python3 "${HERE}/flake_report.py" count --dir "${EVIDENCE_DIR}/attempt-${attempt}")
  if [ "$failed" -eq 0 ] && [ "$RETRY_ON_NO_TEST_FAILURES" != "1" ]; then
    # No test was named, so the suite did not get far enough to have one fail:
    # a compile error, a missing toolchain, a runner that ran out of disk. None
    # of those get better on a second run.
    echo "::notice::Attempt ${attempt} failed with no named test failures (build or infrastructure); not retrying"
    break
  fi
  if [ "$failed" -gt "$MAX_FAILURES_TO_RETRY" ]; then
    echo "::notice::Attempt ${attempt} failed ${failed} tests (> ${MAX_FAILURES_TO_RETRY}); a break, not a flake — not retrying"
    break
  fi

  if [ "$failed" -eq 0 ]; then
    echo "::warning::Attempt ${attempt} failed before any test ran, retrying once"
  else
    echo "::warning::Attempt ${attempt} failed ${failed} test(s), retrying once to tell a flake from a break"
  fi
  ./gradlew --stop 2>/dev/null || true
done

if [ "$EXIT_CODE" -eq 0 ]; then
  FINAL_STATUS=pass
else
  FINAL_STATUS=fail
fi

python3 "${HERE}/flake_report.py" --list "$QUARANTINE_LIST" report \
  --cell "$CELL" \
  --evidence-dir "$EVIDENCE_DIR" \
  --final-status "$FINAL_STATUS" \
  --out "$OUTCOME_FILE"
REPORT_STATUS=$?

# A classifier that did not run cannot vouch for a green suite: it is the only
# thing that would have noticed a test failing on the first attempt and passing
# on the second. Fail loudly rather than inherit a pass we cannot justify.
if [ "$REPORT_STATUS" -ne 0 ]; then
  echo "::error::Could not classify results for ${CELL} (flake_report.py exited ${REPORT_STATUS}); failing the job rather than trusting an unexamined pass"
  exit 1
fi

# The quarantine list, not the retry, decides whether the job goes red.
#
#   any un-quarantined failure  -> red, even if the retry passed. A flake that
#                                  nobody has quarantined is still a failure;
#                                  letting the retry excuse it is how flakes get
#                                  tolerated for years.
#   every failure quarantined   -> green. That is what the list is for, and the
#                                  entry behind it carries a ticket and a date.
#   no test named               -> keep the command's own exit code: a compile
#                                  error or a dead runner is nothing to do with
#                                  quarantine.
if [ -f "$OUTCOME_FILE" ]; then
  read -r gating failures <<< "$(python3 -c "
import json, sys
d = json.load(open(sys.argv[1]))
print(d['gating_count'], d['failure_count'])
" "$OUTCOME_FILE")"

  if [ "${gating:-0}" -gt 0 ]; then
    EXIT_CODE=1
  elif [ "${failures:-0}" -gt 0 ]; then
    echo "::warning::All ${failures} failing test(s) in ${CELL} are quarantined; not failing the job"
    EXIT_CODE=0
  fi
fi

exit "$EXIT_CODE"
