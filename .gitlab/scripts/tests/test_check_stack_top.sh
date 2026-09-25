#! /bin/bash
# Minimal, dependency-free unit tests for .gitlab/benchmarks/check-stack-top.sh.
# Run with: bash .gitlab/scripts/tests/test_check_stack_top.sh
#
# The decision script is exercised through a fake `curl` (and, for the
# jq-absent fallback, a PATH without `jq`), so no network access happens.

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT_UNDER_TEST="${HERE}/../../benchmarks/check-stack-top.sh"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT
# resolved up front: the test runs the script with a PATH restricted to the
# fake-tool bin dir, which does not contain bash
BASH_BIN=$(command -v bash)

fail() { echo "FAIL: $*"; FAILED=1; }
pass() { echo "PASS: $*"; }

# Build an isolated bin dir: fake curl, optional real jq, and symlinks for
# every external tool the script needs — PATH is restricted to this dir so
# the host's jq cannot leak into the jq-absent case.
setup_bin() {
  local with_jq="$1"
  local bin="$WORK/bin"
  rm -rf "$bin"
  mkdir -p "$bin"
  local tool
  for tool in sed tr grep mktemp chmod cat rm cp stat; do
    ln -s "$(command -v "$tool")" "$bin/$tool"
  done
  cat > "$bin/curl" << 'FAKE'
#! /bin/bash
# fake curl: records argv, snapshots any -H @file header (the script under
# test deletes that file on exit, so the snapshot must be taken during the
# request), writes $FAKE_BODY to the -o target, prints the HTTP code
printf '%s\n' "$@" >> "$FAKE_CURL_ARGS"
out=""
while [ $# -gt 0 ]; do
  case "$1" in
    -o) out="$2"; shift 2 ;;
    -w) shift 2 ;;
    -H) if [ -f "${2#@}" ]; then
          cp "${2#@}" "$FAKE_HDR_SNAPSHOT" 2>/dev/null
          stat -f '%Lp' "${2#@}" > "$FAKE_HDR_MODE" 2>/dev/null || \
            stat -c '%a' "${2#@}" > "$FAKE_HDR_MODE" 2>/dev/null
        fi
        shift 2 ;;
    *) shift ;;
  esac
done
if [ -n "$out" ]; then
  printf '%s' "${FAKE_BODY:-[]}" > "$out"
fi
printf '%s' "${FAKE_HTTP_CODE:-200}"
exit "${FAKE_CURL_EXIT:-0}"
FAKE
  chmod +x "$bin/curl"
  if [ "$with_jq" = "yes" ]; then
    ln -s "$(command -v jq)" "$bin/jq"
  fi
}

# run_check <branch> [KEY=VALUE env assignments...]
# Sets RESULT (decision line), URL_LINE (API URL the fake curl saw),
# HDR_CONTENT and HDR_MODE (snapshot of the Authorization header file).
run_check() {
  local branch="$1"; shift
  setup_bin "${WITH_JQ:-yes}"
  : > "$WORK/curl_args"
  rm -f "$WORK/hdr_snapshot" "$WORK/hdr_mode"
  RESULT=$(env "$@" PATH="$WORK/bin" CI_COMMIT_BRANCH="$branch" \
    FAKE_CURL_ARGS="$WORK/curl_args" FAKE_HDR_SNAPSHOT="$WORK/hdr_snapshot" \
    FAKE_HDR_MODE="$WORK/hdr_mode" \
    "$BASH_BIN" "$SCRIPT_UNDER_TEST" 2>"$WORK/stderr")
  URL_LINE=$(grep -F 'base=' "$WORK/curl_args" 2>/dev/null | head -1 || true)
  HDR_CONTENT=$(cat "$WORK/hdr_snapshot" 2>/dev/null || true)
  HDR_MODE=$(cat "$WORK/hdr_mode" 2>/dev/null || true)
}

expect_decision() {
  local desc="$1" expected="$2"
  if [ "$RESULT" = "RUN_BENCHMARKS=$expected" ]; then
    pass "$desc"
  else
    fail "$desc — expected RUN_BENCHMARKS=$expected, got '${RESULT}'"
  fi
}

# main/master and empty branches never query the API
run_check "main"
expect_decision "main branch runs benchmarks" true
if [ -n "$URL_LINE" ]; then fail "main branch must not query the API"; else pass "main branch skips the API"; fi

run_check ""
expect_decision "empty branch runs benchmarks" true

# a stacked branch (open PR uses it as base) is skipped
FAKE_BODY='[{"number":1}]' run_check "jb/feature"
expect_decision "branch with a stacked PR is skipped" false

# top of the stack / independent branch runs
FAKE_BODY='[]' run_check "jb/feature"
expect_decision "branch without a stacked PR runs benchmarks" true

# API error bodies are JSON objects, not arrays — fail open
FAKE_BODY='{"message":"API rate limit exceeded"}' run_check "jb/feature"
expect_decision "non-array rate-limit response fails open" true

# transport failures fail open
FAKE_CURL_EXIT=7 run_check "jb/feature"
expect_decision "curl transport failure fails open" true

# non-200 HTTP status (e.g. 403 rate limit) fails open
FAKE_HTTP_CODE=403 FAKE_BODY='{"message":"API rate limit exceeded"}' run_check "jb/feature"
expect_decision "HTTP 403 fails open" true

# branch names with reserved characters must be percent-encoded
FAKE_BODY='[]' run_check "fix-50%off&a b"
case "$URL_LINE" in
  *base=fix-50%25off%26a%20b*) pass "reserved characters are percent-encoded" ;;
  *) fail "reserved characters are percent-encoded — got URL: $URL_LINE" ;;
esac

# the sed fallback path (jq absent) must encode % first
WITH_JQ=no FAKE_BODY='[]' run_check "fix-50%off"
expect_decision "jq-absent fallback still decides" true
case "$URL_LINE" in
  *base=fix-50%25off*) pass "sed fallback encodes % before other characters" ;;
  *) fail "sed fallback encodes % first — got URL: $URL_LINE" ;;
esac

# a token with trailing newline is normalized, not injected raw into headers
FAKE_BODY='[]' run_check "jb/feature" "GITHUB_TOKEN=$(printf 'tok123\n')"
expect_decision "normalized token still authenticates" true
if [ -n "$HDR_CONTENT" ]; then
  if [ "$HDR_CONTENT" = "Authorization: token tok123" ]; then
    pass "token passed via header file with single-line value"
  else
    fail "token header file content — got '$HDR_CONTENT'"
  fi
  if [ "$HDR_MODE" = "600" ]; then
    pass "header file is mode 0600"
  else
    fail "header file must be mode 0600 — got '$HDR_MODE'"
  fi
else
  fail "token was not passed via a header file"
fi

# a multi-line token value is rejected instead of becoming injected headers
FAKE_BODY='[]' run_check "jb/feature" "GITHUB_TOKEN=$(printf 'tok\nX-Injected: yes')"
if [ -z "$HDR_CONTENT" ]; then
  pass "malformed token is dropped (anonymous request)"
else
  fail "malformed token must be dropped — header content: $HDR_CONTENT"
fi

if [ "$FAILED" -eq 0 ]; then
  echo "test_check_stack_top: all tests passed"
else
  echo "test_check_stack_top: FAILURES detected"
fi
exit "$FAILED"
