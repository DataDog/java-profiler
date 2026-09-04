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

case "$MAX_ATTEMPTS" in
  ''|*[!0-9]*|0)
    echo "::error::MAX_ATTEMPTS must be a positive integer, got '${MAX_ATTEMPTS}'"
    exit 1
    ;;
esac

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Overridable so a caller outside :ddprof-test's own Gradle layout can point
# this at its own results directory instead of silently classifying an empty,
# never-populated evidence set as "no observed tests".
RESULTS_DIR="${RESULTS_DIR:-ddprof-test/build/test-results}"
EVIDENCE_DIR="flake-evidence"
OUTCOME_FILE="ci-outcome/${CELL}.json"
# Set when an attempt's evidence cannot be trusted as belonging to that
# attempt alone (e.g. a stale RESULTS_DIR that could not be cleared) -- the
# quarantine excuse must never fire on suspect evidence, no matter what the
# counts say.
EVIDENCE_SUSPECT=0

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
  # Returning non-zero here is the whole contract: the tree holds files this
  # user cannot read, so any snapshot taken from it is partial, and a partial
  # snapshot is exactly what lets a final attempt's missing failures read back
  # as a quarantined pass. The caller turns that into EVIDENCE_SUSPECT.
  if ! command -v sudo >/dev/null 2>&1; then
    echo "::warning::${RESULTS_DIR} has files not owned by $(id -un) and sudo is unavailable to fix that; flake evidence may be incomplete"
    return 1
  fi
  # Non-recursive on the parent: it only needs its own write bit so the
  # pre-attempt `rm -rf "$RESULTS_DIR"` below can unlink the directory itself.
  # Recursing over the whole module build tree (classes, jars, native libs,
  # kept JFRs) would be orders of magnitude more inodes than needed and makes
  # unrelated build output world-writable.
  local ok=0
  sudo chmod a+rwX "$(dirname "$RESULTS_DIR")" 2>/dev/null \
    || { ok=1; echo "::warning::Could not make $(dirname "$RESULTS_DIR") writable; flake evidence may be incomplete"; }
  sudo chmod -R a+rwX "$RESULTS_DIR" 2>/dev/null \
    || { ok=1; echo "::warning::Could not take ownership of ${RESULTS_DIR}; flake evidence may be incomplete"; }
  return "$ok"
}

snapshot() {
  local attempt="$1"
  local dest="${EVIDENCE_DIR}/attempt-${attempt}"
  # The XML being snapshotted was written by the command that just ran, after
  # the loop-top make_results_readable() -- under Docker it lands root-owned,
  # so read access has to be taken again here or the cp below fails and the
  # cell silently loses its flake evidence.
  make_results_readable || EVIDENCE_SUSPECT=1
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

# Self-contained state: a leftover attempt-2 from an earlier run on a reused
# workspace would be read back as this run's evidence, inflating the attempt
# count and importing failures that never happened here.
rm -rf "$EVIDENCE_DIR" "$(dirname "$OUTCOME_FILE")"

EXIT_CODE=1
# A single, per-attempt-truncated log: only the final attempt's is ever read
# (by flake_report.py's non-test-task-failure check below), and keeping one
# copy per attempt on disk earned nothing but wasted space.
ATTEMPT_LOG="build/logs/attempt.log"
for attempt in $(seq 1 "$MAX_ATTEMPTS"); do
  mkdir -p build/logs
  make_results_readable || EVIDENCE_SUSPECT=1
  if ! rm -rf "$RESULTS_DIR"; then
    echo "::warning::Could not clear ${RESULTS_DIR} before attempt ${attempt}; it may inherit the previous attempt's results and a flake will look persistent"
    # A stale RESULTS_DIR here means this attempt's snapshot can end up being
    # the *previous* attempt's JUnit XML, which would let a final attempt that
    # actually crashed without running a single test be read back as having
    # "passed with only quarantined failures". Never let the quarantine excuse
    # fire on evidence that might not be this attempt's own.
    EVIDENCE_SUSPECT=1
  fi
  : > "$ATTEMPT_LOG"

  "$@" 2>&1 \
    | tee -a build/test-raw.log \
    | tee "$ATTEMPT_LOG" \
    | python3 -u "${HERE}/filter_gradle_log.py"
  EXIT_CODE=${PIPESTATUS[0]}

  # A first-attempt pass has no prior attempt to compare against, so its
  # snapshot could only ever yield an empty flake report; skip the find
  # traversal, possible sudo chmod, and recursive copy that nobody will read.
  # A later-attempt pass still needs its snapshot -- that is the evidence that
  # proves the earlier failure was a flake.
  if [ "$EXIT_CODE" -ne 0 ] || [ "$attempt" -gt 1 ]; then
    snapshot "$attempt"
  fi

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

REPORT_ARGS=(--list "$QUARANTINE_LIST" report
  --cell "$CELL"
  --evidence-dir "$EVIDENCE_DIR"
  --final-attempt "$attempt"
  --out "$OUTCOME_FILE"
  --attempt-log "$ATTEMPT_LOG"
  --final-attempt-exit-code "$EXIT_CODE"
  --test-task-pattern "$TEST_TASK_PATTERN")
[ "$EVIDENCE_SUSPECT" = "1" ] && REPORT_ARGS+=(--evidence-suspect)

python3 "${HERE}/flake_report.py" "${REPORT_ARGS[@]}"
REPORT_STATUS=$?

# A classifier that did not run cannot vouch for a green suite: it is the only
# thing that would have noticed a test failing on the first attempt and passing
# on the second. Fail loudly rather than inherit a pass we cannot justify.
if [ "$REPORT_STATUS" -ne 0 ]; then
  echo "::error::Could not classify results for ${CELL} (flake_report.py exited ${REPORT_STATUS}); failing the job rather than trusting an unexamined pass"
  exit 1
fi

# flake_report.py owns the gating verdict -- it has every count and the
# quarantine list in hand, so re-deriving the decision here (as this script
# used to, with an inline python, two case sanity checks, and a bash
# if/elif chain) is one more independent reader of the outcome-JSON schema
# for no benefit. "gates" is true/false to override EXIT_CODE, or the string
# "none" when there is no failure to have an opinion about, in which case the
# command's own exit code stands (a compile error or a dead runner is nothing
# to do with quarantine).
if [ -f "$OUTCOME_FILE" ]; then
  decision=$(python3 -c "
import json, sys
try:
    d = json.load(open(sys.argv[1]))
    if 'gates' not in d:
        sys.exit('missing key: gates')
except Exception as e:
    sys.exit(str(e))
gates = d['gates']
print('none' if gates is None else ('true' if gates else 'false'))
print(d.get('gate_reason') or '')
" "$OUTCOME_FILE") || {
    echo "::error::Could not read ${OUTCOME_FILE} (${decision:-no output}); failing the job rather than guessing whether its failures gate"
    exit 1
  }
  gates=$(echo "$decision" | sed -n '1p')
  reason=$(echo "$decision" | sed -n '2p')
  case "$gates" in
    true)
      echo "::error::${CELL} fails: ${reason}"
      EXIT_CODE=1
      ;;
    false)
      echo "::warning::${CELL} is not failing the job: ${reason}"
      EXIT_CODE=0
      ;;
    none) ;;
    *)
      echo "::error::${OUTCOME_FILE} did not yield a usable gating decision (got '${gates}'); failing the job"
      exit 1
      ;;
  esac
fi

exit "$EXIT_CODE"
