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
# The Alpine aarch64 suite runs as root inside Docker while this script runs as
# the host user, so the XML it writes is root-owned. Without this the snapshot
# and the next attempt's cleanup both fail, and the cell loses flake
# classification entirely -- silently, since both used to discard their errors.
make_results_readable() {
  [ -d "$RESULTS_DIR" ] || return 0
  # The permission problem this exists to fix is per-file (Docker writes the
  # XML as root while the directory it lands in stays host-owned), so a
  # directory-level writability check would miss it. Probe by ownership rather
  # than with find's -writable, which busybox does not implement -- there the
  # test would fail open into a silent no-op, which is the failure this whole
  # function exists to stop. A probe that cannot decide takes ownership anyway.
  if foreign=$(find "$RESULTS_DIR" ! -user "$(id -u)" -print 2>/dev/null | head -n 1); then
    [ -n "$foreign" ] || { [ -w "$RESULTS_DIR" ] && [ -w "$(dirname "$RESULTS_DIR")" ] && return 0; }
  fi
  command -v sudo >/dev/null 2>&1 || return 0
  # Include the parent so the pre-attempt `rm -rf "$RESULTS_DIR"` below (which
  # needs to unlink the directory itself, not just its contents) can succeed.
  sudo chmod -R a+rwX "$(dirname "$RESULTS_DIR")" 2>/dev/null \
    || echo "::warning::Could not take ownership of ${RESULTS_DIR}; flake evidence may be incomplete"
}

snapshot() {
  local attempt="$1"
  local dest="${EVIDENCE_DIR}/attempt-${attempt}"
  make_results_readable
  rm -rf "$dest" || echo "::warning::Could not clear ${dest}; attempt ${attempt} evidence may be stale"
  mkdir -p "$dest"
  if [ -d "$RESULTS_DIR" ]; then
    cp -r "$RESULTS_DIR"/. "$dest"/ \
      || echo "::warning::Could not snapshot ${RESULTS_DIR} for attempt ${attempt}; flake classification for this cell will be incomplete"
  fi
}

# Which Gradle tasks are the tests. A failure in anything else is not something
# the quarantine list has any business excusing.
TEST_TASK_PATTERN="${TEST_TASK_PATTERN:-:ddprof-test:test}"

# Task failures the quarantine list must never wave through.
non_test_task_failures() {
  local log="$1"
  [ -f "$log" ] || return 0
  grep -oE "Execution failed for task '[^']+'" "$log" 2>/dev/null \
    | sed -E "s/^Execution failed for task '//; s/'$//" \
    | grep -v -F "$TEST_TASK_PATTERN" \
    | sort -u
}

# Self-contained state: a leftover attempt-2 from an earlier run on a reused
# workspace would be read back as this run's evidence, inflating the attempt
# count and importing failures that never happened here.
rm -rf "$EVIDENCE_DIR" "$(dirname "$OUTCOME_FILE")"

EXIT_CODE=1
ATTEMPT_LOG=""
for attempt in $(seq 1 "$MAX_ATTEMPTS"); do
  mkdir -p build/logs
  make_results_readable
  rm -rf "$RESULTS_DIR" \
    || echo "::warning::Could not clear ${RESULTS_DIR} before attempt ${attempt}; it may inherit the previous attempt's results and a flake will look persistent"
  ATTEMPT_LOG="build/logs/attempt-${attempt}.log"

  "$@" 2>&1 \
    | tee -a build/test-raw.log \
    | tee "$ATTEMPT_LOG" \
    | python3 -u "${HERE}/filter_gradle_log.py"
  EXIT_CODE=${PIPESTATUS[0]}

  snapshot "$attempt"

  if [ "$EXIT_CODE" -eq 0 ]; then
    break
  fi

  if [ "$attempt" -ge "$MAX_ATTEMPTS" ]; then
    break
  fi

  failed=$(python3 "${HERE}/flake_report.py" count --dir "${EVIDENCE_DIR}/attempt-${attempt}") || failed=""
  case "$failed" in
    ''|*[!0-9]*)
      # Every guard below is a numeric comparison; on a non-number they would
      # all quietly evaluate false and retry the very failures meant to be
      # taken at face value.
      echo "::warning::Could not count test failures for attempt ${attempt}; not retrying"
      break
      ;;
  esac
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

python3 "${HERE}/flake_report.py" --list "$QUARANTINE_LIST" report \
  --cell "$CELL" \
  --evidence-dir "$EVIDENCE_DIR" \
  --final-attempt "$attempt" \
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
#   every failure quarantined   -> green, but only when the *final* attempt is
#                                  the one vouching for that: failures
#                                  aggregated across every attempt can all be
#                                  quarantined while the final attempt itself
#                                  failed for a reason that named no test at
#                                  all (a docker or Gradle failure, an
#                                  OOM-killed daemon, an ASan init abort), and
#                                  the list has no business excusing that.
#   no test named               -> keep the command's own exit code: a compile
#                                  error or a dead runner is nothing to do with
#                                  quarantine.
if [ -f "$OUTCOME_FILE" ]; then
  summary=$(python3 -c "
import json, sys
d = json.load(open(sys.argv[1]))
final_gating = d['final_attempt_gating_count']
print(d['gating_count'], d['failure_count'], int(d['final_attempt_ran']),
      final_gating if final_gating is not None else -1)
" "$OUTCOME_FILE") || {
    echo "::error::Could not read ${OUTCOME_FILE}; failing the job rather than guessing whether its failures gate"
    exit 1
  }
  read -r gating failures final_ran final_gating <<< "$summary"
  case "${gating}:${failures}:${final_ran}" in
    *[!0-9:]*|:*|*:|*::*)
      echo "::error::${OUTCOME_FILE} did not yield usable counts (got '${summary}'); failing the job"
      exit 1
      ;;
  esac
  case "$final_gating" in
    -1|*[!0-9]*)
      [ "$final_gating" = "-1" ] || {
        echo "::error::${OUTCOME_FILE} did not yield a usable final-attempt gating count (got '${summary}'); failing the job"
        exit 1
      }
      ;;
  esac

  if [ "$gating" -gt 0 ]; then
    EXIT_CODE=1
  elif [ "$failures" -gt 0 ]; then
    if [ "$final_ran" -ne 1 ] || [ "$final_gating" -ne 0 ]; then
      # The final attempt either produced no test results of its own (a
      # build or infrastructure failure, not something quarantine speaks to)
      # or still has its own named failures unquarantined -- either way the
      # list has nothing to say about why this attempt is red.
      echo "::error::${CELL}'s final attempt did not itself pass with only quarantined failures (ran=${final_ran}, its own gating count=${final_gating}); failing the job rather than trusting failures from an earlier attempt"
      EXIT_CODE=1
    else
      # Quarantine excuses the tests it names. It does not excuse the build:
      # if this same invocation also failed a compile, a native gtest or a
      # verification task, that failure has nothing to do with the list and
      # zeroing the exit code here would bury it.
      other=$(non_test_task_failures "$ATTEMPT_LOG")
      if [ -n "$other" ]; then
        echo "::error::All ${failures} failing test(s) in ${CELL} are quarantined, but the build also failed in $(echo "$other" | tr '\n' ' ')— failing the job"
        EXIT_CODE=1
      else
        echo "::warning::All ${failures} failing test(s) in ${CELL} are quarantined; not failing the job"
        EXIT_CODE=0
      fi
    fi
  fi
fi

exit "$EXIT_CODE"
