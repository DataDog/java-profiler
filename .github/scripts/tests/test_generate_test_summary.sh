#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Hermetic tests for generate-test-summary.sh's handling of downloaded
# ci-outcome reports.
# Run with: .github/scripts/tests/test_generate_test_summary.sh
#
# `gh` is the only external dependency this script has that can't run inside a
# sandbox, so it is the only thing stubbed out below; everything else (jq,
# the report-parsing logic) runs for real against fixture data.

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
SCRIPT="$ROOT/.github/scripts/generate-test-summary.sh"
TEMP_DIR=$(mktemp -d)
TESTS=0

cleanup() {
  rm -rf "$TEMP_DIR"
}
trap cleanup EXIT

fail() {
  echo "FAIL: $*" >&2
  exit 1
}

pass() {
  TESTS=$((TESTS + 1))
  echo "  ok: $*"
}

# A stub `gh` good enough for this script's two call sites: the jobs listing
# and the ci-outcome artifact download. Real GitHub is never reached.
STUB_BIN="$TEMP_DIR/stub-bin"
mkdir -p "$STUB_BIN"
cat > "$STUB_BIN/gh" <<'EOS'
#!/usr/bin/env bash
if [ "$1" = "api" ]; then
  cat "$GH_JOBS_FIXTURE"
  exit 0
fi
if [ "$1" = "run" ] && [ "$2" = "download" ]; then
  dir=""
  prev=""
  for arg in "$@"; do
    if [ "$prev" = "--dir" ]; then dir="$arg"; fi
    prev="$arg"
  done
  mkdir -p "$dir"
  cp "$GH_OUTCOME_FIXTURE_DIR"/*.json "$dir/" 2>/dev/null || true
  exit 0
fi
echo "stub gh: unexpected invocation: $*" >&2
exit 1
EOS
chmod +x "$STUB_BIN/gh"
PATH="$STUB_BIN:$PATH"
export PATH

write_jobs_fixture() {
  # write_jobs_fixture <path> <conclusion>
  cat > "$1" <<EOJ
[
  {
    "name": "test-matrix / test-linux-glibc-amd64 (17, debug, regular)",
    "conclusion": "$2",
    "html_url": "https://example.invalid/job/1",
    "started_at": "2026-01-01T00:00:00Z",
    "completed_at": "2026-01-01T00:05:00Z"
  }
]
EOJ
}

echo "== generate-test-summary.sh: outcome report parsing =="

# A well-formed, failing outcome report must be rendered as a real failure
# row -- not swallowed into the "unreadable outcome report" fallback. This is
# the path a mutated `if ! rows=$(jq ...)` (dropping the `!`) would break: jq
# succeeding on valid JSON would then take the branch meant for jq failing.
CASE="$TEMP_DIR/case-valid-report"
mkdir -p "$CASE/jobs" "$CASE/outcomes" "$CASE/work"
write_jobs_fixture "$CASE/jobs/jobs.json" failure
cat > "$CASE/outcomes/glibc-17-debug-amd64.json" <<'EOJ'
{"cell": "glibc-17-debug-amd64", "attempts": 1, "persistent":
 [{"test": "com.dd.FooTest.bar", "message": "assertion failed: boom"}],
 "flaky": [], "quarantined": [], "gating_count": 1, "failure_count": 1,
 "final_attempt_ran": true, "final_attempt_gating_count": 1}
EOJ
(
  cd "$CASE/work"
  export GH_JOBS_FIXTURE="$CASE/jobs/jobs.json" GH_OUTCOME_FIXTURE_DIR="$CASE/outcomes"
  export GITHUB_REPOSITORY="DataDog/java-profiler" GITHUB_SHA="deadbeefcafef00dfeedfacebeefcafebeefcafe"
  "$SCRIPT" 12345 "$CASE/work/summary.md"
) || fail "generate-test-summary.sh exited non-zero on a valid outcome report"
summary=$(cat "$CASE/work/summary.md")
echo "$summary" | grep -q "FooTest.bar" \
  || fail "expected the real failing test in the summary, got: $summary"
echo "$summary" | grep -q "assertion failed: boom" \
  || fail "expected the real failure message in the summary, got: $summary"
if echo "$summary" | grep -q "_unreadable outcome report_"; then
  fail "a valid outcome report was rendered as unreadable, got: $summary"
fi
pass "a valid outcome report renders its real failure, not the unreadable fallback"

# A malformed outcome report (invalid JSON) must be rendered as unreadable,
# not silently dropped or fed further down the pipeline as if it were rows.
CASE="$TEMP_DIR/case-malformed-report"
mkdir -p "$CASE/jobs" "$CASE/outcomes" "$CASE/work"
write_jobs_fixture "$CASE/jobs/jobs.json" failure
printf 'this is not json\n' > "$CASE/outcomes/glibc-17-debug-amd64.json"
(
  cd "$CASE/work"
  export GH_JOBS_FIXTURE="$CASE/jobs/jobs.json" GH_OUTCOME_FIXTURE_DIR="$CASE/outcomes"
  export GITHUB_REPOSITORY="DataDog/java-profiler" GITHUB_SHA="deadbeefcafef00dfeedfacebeefcafebeefcafe"
  "$SCRIPT" 12345 "$CASE/work/summary.md"
) || fail "generate-test-summary.sh exited non-zero on a malformed outcome report"
summary=$(cat "$CASE/work/summary.md")
echo "$summary" | grep -q "_unreadable outcome report_" \
  || fail "expected a malformed outcome report to be flagged unreadable, got: $summary"
pass "a malformed outcome report is flagged unreadable rather than silently ignored"

echo
echo "All $TESTS generate-test-summary tests passed."
