#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Hermetic tests for check_jdk_urls.sh, the Jira helpers it drives and
# fetchAndExtract in java_setup.sh; a fake curl answers from fixtures.
# Run with: .github/scripts/tests/test_check_jdk_urls.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
SCRIPTS=$(cd "$SCRIPT_DIR/.." && pwd)
CHECK="$SCRIPTS/check_jdk_urls.sh"
FILE_JIRA="$SCRIPTS/file-jira-issue.sh"
RESOLVE_JIRA="$SCRIPTS/resolve-jira-issue.sh"
CACHE_JAVA="$SCRIPTS/../workflows/cache_java.yml"
SETUP="$SCRIPTS/java_setup.sh"
TEMP_DIR=$(mktemp -d)
TESTS=0
IBM_BASE="https://public.dhe.ibm.com/ibmdl/export/pub/systems/cloud/runtimes/java/"
IBM_PIN="${IBM_BASE}8.0.8.75/linux/x86_64/ibm-java-jre-8.0-8.75-linux-x86_64.tgz"
IBM_NEXT="${IBM_BASE}8.0.8.80/linux/x86_64/ibm-java-jre-8.0-8.80-linux-x86_64.tgz"

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
}

assert_eq() {
  [ "$1" = "$2" ] || fail "$3: expected '$1', got '$2'"
  pass
}

assert_contains() {
  case "$1" in
    *"$2"*) pass ;;
    *) fail "$3: output does not contain '$2'. Output: $1" ;;
  esac
}

assert_not_contains() {
  case "$1" in
    *"$2"*) fail "$3: output contains '$2'. Output: $1" ;;
    *) pass ;;
  esac
}

command -v yq >/dev/null || fail "yq (mikefarah v4) is required"
command -v jq >/dev/null || fail "jq is required"

# --- Fake network --------------------------------------------------------------
# FAKE_URLS lines: "<url> <head_code> [<range_code>] [<final_url>]"; an unlisted
# URL behaves like an unreachable host. FAKE_OPEN lines: "<key>|<summary>" for
# unresolved Jira issues. Every call is logged to FAKE_CURL_LOG.

FAKE_BIN="$TEMP_DIR/bin"
mkdir -p "$FAKE_BIN"
cat > "$FAKE_BIN/curl" <<'EOF'
#!/usr/bin/env bash
url="" method="" data="" head=0 range=0 wfmt="" out=""
while [ $# -gt 0 ]; do
  case "$1" in
    -I) head=1 ;;
    -r) range=1; shift ;;
    -w) wfmt=$2; shift ;;
    -o) out=$2; shift ;;
    -X) method=$2; shift ;;
    --data) data=$2; shift ;;
    -u|-H|--retry|--connect-timeout|--max-time) shift ;;
    http://*|https://*) url=$1 ;;
  esac
  shift
done
[ -n "${FAKE_CURL_DELAY:-}" ] && sleep "$FAKE_CURL_DELAY"
[ -z "$method" ] && { [ -n "$data" ] && method=POST || method=GET; }
[ "$head" = 1 ] && method=HEAD
[ "$range" = 1 ] && method=RANGE
compact=""
[ -n "$data" ] && compact=$(jq -c . <<<"$data")
printf '%s %s %s\n' "$method" "$url" "$compact" >> "$FAKE_CURL_LOG"

if [ -n "${FAKE_SLACK_URL:-}" ] && [ "$url" = "$FAKE_SLACK_URL" ]; then
  [ "${FAKE_SLACK_FAIL:-0}" = 1 ] && exit 22
  exit 0
fi
case "$url" in
  */rest/api/3/*)
    [ "${FAKE_JIRA_FAIL:-0}" = 1 ] && exit 22
    case "$url" in
      */search/jql)
        [ "${FAKE_SEARCH_FAIL:-0}" = 1 ] && exit 22
        summary=$(jq -r .jql <<<"$data" | sed -E 's/.*summary ~ "\\"(.*)\\"" AND resolution.*/\1/')
        # Jira phrase matching also hits longer summaries: every open issue
        # whose summary contains the phrase is returned, with its summary.
        hits=$(awk -F '|' -v s="$summary" 'index(tolower($2), tolower(s)) { print }' "${FAKE_OPEN:-/dev/null}")
        printf '%s\n' "$hits" | jq -Rn --arg s "$summary" '[inputs | split("|")
          | select(length == 2 and (.[1] | ascii_downcase | contains($s | ascii_downcase)))
          | {key: .[0], fields: {summary: .[1]}}] | {issues: .}' ;;
      */transitions)
        if [ "$method" = GET ]; then
          [ "${FAKE_TRANSITIONS_GET_FAIL:-0}" = 1 ] && exit 22
          if [ "${FAKE_NO_DONE:-0}" = 1 ]; then
            echo '{"transitions":[{"id":"11","name":"In Progress","to":{"statusCategory":{"key":"indeterminate"}}}]}'
          else
            echo '{"transitions":[{"id":"41","name":"Won'"'"'t Do","to":{"statusCategory":{"key":"done"}}},{"id":"11","name":"In Progress","to":{"statusCategory":{"key":"indeterminate"}}},{"id":"31","name":"Done","to":{"statusCategory":{"key":"done"}}}]}'
          fi
        elif [ "${FAKE_TRANSITION_FAIL:-0}" = 1 ]; then
          exit 22
        fi ;;
      */comment)
        [ "${FAKE_COMMENT_FAIL:-0}" = 1 ] && exit 22
        echo '{}' ;;
      */issue) echo '{"key":"PROF-9001"}' ;;
    esac
    exit 0 ;;
esac
if [ "$url" = "${IBM_INDEX:-}" ]; then
  [ -f "${FAKE_IBM_LISTING:-}" ] || exit 22
  cat "$FAKE_IBM_LISTING"
  exit 0
fi
line=$(awk -v u="$url" '$1 == u { print; exit }' "${FAKE_URLS:-/dev/null}")
if [ -z "$line" ]; then
  [ -n "$wfmt" ] && printf '000 %s' "$url"
  echo "curl: (6) Could not resolve host: fake" >&2
  exit 6
fi
read -r _ head_code range_code final <<<"$line"
code=$head_code
[ "$method" = RANGE ] && code=${range_code:-$head_code}
if [ -n "$wfmt" ] && [ "$wfmt" = "${wfmt#%\{stderr\}}" ]; then
  printf '%s %s' "$code" "${final:-$url}"
  exit 0
fi
# Download mode, as java_setup.sh calls it (body on stdout, status on stderr).
echo "HTTP status: $code" >&2
case "$code" in
  2??) cat "${FAKE_DOWNLOAD:-/dev/null}" ;;
  *) echo "curl: (22) The requested URL returned error: $code" >&2; exit 22 ;;
esac
EOF
cat > "$FAKE_BIN/tar" <<'EOF'
#!/usr/bin/env bash
echo "tar $*" >> "$FAKE_CURL_LOG"
cat > /dev/null
exit "${FAKE_TAR_RC:-0}"
EOF
cat > "$FAKE_BIN/sudo" <<'EOF'
#!/usr/bin/env bash
echo "sudo" >> "$FAKE_CURL_LOG"
exec "$@"
EOF
chmod +x "$FAKE_BIN"/*
PATH="$FAKE_BIN:$PATH"
export PATH FAKE_CURL_LOG="$TEMP_DIR/curl.log" IBM_INDEX="$IBM_BASE"
unset GITHUB_STEP_SUMMARY SLACK_WEBHOOK ATLASSIAN_BASE_URL ATLASSIAN_USER_EMAIL ATLASSIAN_API_TOKEN RUN_URL

reset_fakes() {
  : > "$FAKE_CURL_LOG"
  unset FAKE_URLS FAKE_OPEN FAKE_IBM_LISTING FAKE_NO_DONE FAKE_JIRA_FAIL FAKE_SLACK_URL FAKE_SLACK_FAIL \
    FAKE_TRANSITION_FAIL FAKE_TRANSITIONS_GET_FAIL FAKE_COMMENT_FAIL FAKE_SEARCH_FAIL FAKE_DOWNLOAD FAKE_TAR_RC \
    FAKE_CURL_DELAY
}

with_jira() {
  export ATLASSIAN_BASE_URL="https://jira.example.invalid" ATLASSIAN_USER_EMAIL="bot@example.invalid" ATLASSIAN_API_TOKEN="token"
}

without_jira() {
  unset ATLASSIAN_BASE_URL ATLASSIAN_USER_EMAIL ATLASSIAN_API_TOKEN
}

# --- Pure helpers ----------------------------------------------------------------
# Sourcing defines the helpers only; main runs when the script is executed.
# shellcheck disable=SC1090,SC1091 # path resolved at run time
source "$CHECK"
for code in 200 204 299; do
  assert_eq OK "$(classify "$code")" "classify $code"
done
for code in 404 410; do
  assert_eq STALE "$(classify "$code")" "classify $code"
done
for code in 000 301 401 403 429 500 503; do
  assert_eq INCONCLUSIVE "$(classify "$code")" "classify $code"
done

# sort -V, not lexical: 8.0.8.10 is newer than 8.0.8.9.
version_gt 8.0.8.10 8.0.8.9 || fail "version_gt 8.0.8.10 8.0.8.9"
version_gt 8.0.9.0 8.0.8.75 || fail "version_gt 8.0.9.0 8.0.8.75"
! version_gt 8.0.8.75 8.0.8.75 || fail "version_gt equal"
! version_gt 8.0.8.9 8.0.8.10 || fail "version_gt lower"
TESTS=$((TESTS + 4))

assert_eq 8.0.8.75 "$(pinned_ibm_version "$IBM_PIN")" "pinned_ibm_version"
assert_eq "" "$(pinned_ibm_version "https://example.invalid/jdk.tgz")" "pinned_ibm_version without a release directory"
assert_eq "$IBM_NEXT" "$(ibm_candidate_url 8.0.8.80)" "ibm_candidate_url"

listing='<a href="8.0.8.45/">8.0.8.45/</a> <a href="8.0.8.9/">8.0.8.9/</a>
<a href="8.0.8.75/">8.0.8.75/</a> <a href="18.0.1.2/">18.0.1.2/</a>
8.0.8.70/ <a href="8.0.8.75/">dup</a> ibm-8.0.8.99.tgz readme.txt'
assert_eq "8.0.8.9 8.0.8.45 8.0.8.70 8.0.8.75 " "$(parse_ibm_listing <<<"$listing" | tr '\n' ' ')" "parse_ibm_listing"
assert_eq "" "$(parse_ibm_listing <<<"<html>no releases</html>")" "parse_ibm_listing without releases"

cat > "$TEMP_DIR/fixture.yml" <<EOF
env:
  JDKS_DIR: jdks
  JAVA_8_VERSION: 8.0.462
  JAVA_8_IBM_URL: "$IBM_PIN"
  # JAVA_8_ZING_URL: "https://cdn.example.invalid/zing.tar.gz"
  JAVA_11_MUSL_URL : "https://ok.example.invalid/musl11.tar.gz"
  JAVA_11_URL_NOTE: "https://example.invalid/not-a-pin"
jobs:
  build:
    env:
      JAVA_17_JOB_URL: "https://example.invalid/job-level"
EOF
assert_eq "JAVA_8_IBM_URL $IBM_PIN
JAVA_11_MUSL_URL https://ok.example.invalid/musl11.tar.gz" "$(extract_urls "$TEMP_DIR/fixture.yml")" "extract_urls: top-level env JAVA_*_URL keys only"

# The real workflow: the IBM pin is checked, the commented-out Zing pins are not.
real=$(extract_urls "$CACHE_JAVA")
assert_contains "$real" "JAVA_8_IBM_URL https://" "extract_urls cache_java.yml: IBM pin"
assert_not_contains "$real" "ZING" "extract_urls cache_java.yml: commented-out Zing pins"

# --- check ---------------------------------------------------------------------
reset_fakes
cat > "$TEMP_DIR/urls.txt" <<EOF
$IBM_PIN 200
$IBM_NEXT 200
https://ok.example.invalid/musl11.tar.gz 200 200 https://cdn.example.invalid/musl11.tar.gz
https://gone.example.invalid/jdk.tgz 404
https://busy.example.invalid/jdk.tgz 503
https://nohead.example.invalid/jdk.tgz 405 206
https://forbidden.example.invalid/jdk.tgz 403 200
https://notimpl.example.invalid/jdk.tgz 501 206
https://headlies.example.invalid/jdk.tgz 404 206
EOF
cat > "$TEMP_DIR/mixed.yml" <<EOF
env:
  JAVA_8_IBM_URL: "$IBM_PIN"
  JAVA_11_MUSL_URL: "https://ok.example.invalid/musl11.tar.gz"
  JAVA_17_MUSL_URL: "https://gone.example.invalid/jdk.tgz"
  JAVA_21_MUSL_URL: "https://busy.example.invalid/jdk.tgz"
  JAVA_8_ORACLE_URL: "https://nohead.example.invalid/jdk.tgz"
  JAVA_25_MUSL_URL: "https://down.example.invalid/jdk.tgz"
  JAVA_8_MUSL_URL: "https://forbidden.example.invalid/jdk.tgz"
  JAVA_8_MUSL_AARCH64_URL: "https://notimpl.example.invalid/jdk.tgz"
  JAVA_11_MUSL_AARCH64_URL: "https://headlies.example.invalid/jdk.tgz"
EOF
printf '<a href="8.0.8.70/">x</a><a href="8.0.8.75/">x</a><a href="8.0.8.80/">x</a>' > "$TEMP_DIR/listing.html"
export FAKE_URLS="$TEMP_DIR/urls.txt" FAKE_IBM_LISTING="$TEMP_DIR/listing.html"
export GITHUB_STEP_SUMMARY="$TEMP_DIR/step-summary.md"
: > "$GITHUB_STEP_SUMMARY"
OUT="$TEMP_DIR/mixed"
rc=0
output=$("$CHECK" check --out "$OUT" --workflow "$TEMP_DIR/mixed.yml" 2>&1) || rc=$?
assert_eq 1 "$rc" "check exits 1 when a URL is stale"
assert_eq "JAVA_8_IBM_URL:OK JAVA_11_MUSL_URL:OK JAVA_17_MUSL_URL:STALE JAVA_21_MUSL_URL:INCONCLUSIVE JAVA_8_ORACLE_URL:OK JAVA_25_MUSL_URL:INCONCLUSIVE JAVA_8_MUSL_URL:OK JAVA_8_MUSL_AARCH64_URL:OK JAVA_11_MUSL_AARCH64_URL:OK " \
  "$(awk -F '\t' '{ printf "%s:%s ", $1, $3 }' "$OUT/results.tsv")" "check classifies every pin"
assert_contains "$output" "::error::Stale JDK download URL: JAVA_17_MUSL_URL returned HTTP 404" "stale is an error"
assert_contains "$output" "::warning::Inconclusive check of JAVA_21_MUSL_URL (HTTP 503)" "5xx is a warning"
assert_contains "$output" "::warning::Inconclusive check of JAVA_25_MUSL_URL (HTTP 000)" "no response is a warning"
assert_contains "$output" "curl: (6) Could not resolve host" "curl's error reaches the log when there is no response"
log=$(cat "$FAKE_CURL_LOG")
assert_contains "$log" "RANGE https://nohead.example.invalid/jdk.tgz" "HEAD 405 falls back to a range GET"
assert_contains "$log" "RANGE https://forbidden.example.invalid/jdk.tgz" "HEAD 403 falls back to a range GET"
assert_contains "$log" "RANGE https://notimpl.example.invalid/jdk.tgz" "HEAD 501 falls back to a range GET"
assert_contains "$log" "RANGE https://gone.example.invalid/jdk.tgz" "HEAD 404 is confirmed with a range GET"
assert_eq "JAVA_11_MUSL_AARCH64_URL 206" "$(awk -F '\t' '$1 == "JAVA_11_MUSL_AARCH64_URL" { print $1, $4 }' "$OUT/results.tsv")" "a HEAD-only 404 is not stale"
assert_eq "JAVA_8_ORACLE_URL 206" "$(awk -F '\t' '$1 == "JAVA_8_ORACLE_URL" { print $1, $4 }' "$OUT/results.tsv")" "range GET status is reported"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "RANGE https://busy.example.invalid" "503 does not fall back"
assert_eq "https://cdn.example.invalid/musl11.tar.gz" "$(awk -F '\t' '$1 == "JAVA_11_MUSL_URL" { print $5 }' "$OUT/results.tsv")" "final URL after redirects"
# shellcheck disable=SC2016 # the backticks are a Markdown code span
assert_contains "$(cat "$GITHUB_STEP_SUMMARY")" '| `JAVA_17_MUSL_URL` | https://gone.example.invalid/jdk.tgz | 404 STALE | https://gone.example.invalid/jdk.tgz |' "step summary table row"
assert_eq "8.0.8.80" "$(sed -n 's/^newer=//p' "$OUT/ibm.txt")" "newer IBM release detected"
assert_eq "$IBM_NEXT" "$(sed -n 's/^candidate_url=//p' "$OUT/ibm.txt")" "newer IBM archive verified"
assert_eq "1" "$(sed -n 's/^newer_count=//p' "$OUT/ibm.txt")" "count of releases newer than the pin"
assert_contains "$(cat "$FAKE_CURL_LOG")" "HEAD $IBM_NEXT" "candidate archive is probed before reporting"
assert_contains "$output" "::notice::IBM SDK 8 8.0.8.80 is available" "newer release is a notice"

# IBM newer-release branches: each is a warning or a no-op, never a failure.
cat > "$TEMP_DIR/ibm-only.yml" <<EOF
env:
  JAVA_8_IBM_URL: "$IBM_PIN"
EOF
ibm_case() {
  # ibm_case <name> <listing or -> <expected ibm.txt newer> <expected output fragment>
  local name=$1 listing=$2 want_newer=$3 want_output=$4 out="$TEMP_DIR/ibm-$1" rc=0 output
  if [ "$listing" = - ]; then
    rm -f "$TEMP_DIR/listing.html"
  else
    printf '%s' "$listing" > "$TEMP_DIR/listing.html"
  fi
  output=$("$CHECK" check --out "$out" --workflow "$TEMP_DIR/ibm-only.yml" 2>&1) || rc=$?
  assert_eq 0 "$rc" "ibm $name: check passes"
  assert_eq "$want_newer" "$(sed -n 's/^newer=//p' "$out/ibm.txt")" "ibm $name: newer"
  assert_contains "$output" "$want_output" "ibm $name: message"
}
ibm_case unreachable - "" "::warning::IBM release listing unreachable"
ibm_case unparseable "<html>maintenance</html>" "" "::warning::No 8.0.x.y releases found"
ibm_case current '<a href="8.0.8.70/">x</a><a href="8.0.8.75/">x</a>' "" "the pinned 8.0.8.75 is the newest listed release"
ibm_case older '<a href="8.0.8.70/">x</a>' "" "::warning::IBM listing tops out at 8.0.8.70"
ibm_case missing-archive '<a href="8.0.8.75/">x</a><a href="8.0.8.99/">x</a>' "" "::warning::IBM lists 8.0.8.99 but its archive returned HTTP 000"

cat > "$TEMP_DIR/bad-ibm.yml" <<EOF
env:
  JAVA_8_IBM_URL: "https://ok.example.invalid/musl11.tar.gz"
EOF
output=$("$CHECK" check --out "$TEMP_DIR/bad-ibm" --workflow "$TEMP_DIR/bad-ibm.yml" 2>&1)
assert_contains "$output" "::warning::Cannot parse the IBM SDK 8 version" "unparseable IBM pin warns"

echo "https://gone410.example.invalid/jdk.tgz 410" >> "$TEMP_DIR/urls.txt"
printf 'env:\n  JAVA_11_MUSL_URL: "https://gone410.example.invalid/jdk.tgz"\n' > "$TEMP_DIR/gone410.yml"
: > "$FAKE_CURL_LOG"
rc=0
"$CHECK" check --out "$TEMP_DIR/gone410" --workflow "$TEMP_DIR/gone410.yml" >/dev/null 2>&1 || rc=$?
assert_eq 1 "$rc" "HTTP 410 is stale"
assert_contains "$(cat "$FAKE_CURL_LOG")" "RANGE https://gone410.example.invalid/jdk.tgz" "HEAD 410 is confirmed with a range GET"

# Probe deadline: pins past the budget are INCONCLUSIVE without a probe, the
# IBM newer-release check is skipped, and earlier STALE pins still fail.
reset_fakes
cat > "$TEMP_DIR/deadline.yml" <<EOF
env:
  JAVA_8_IBM_URL: "$IBM_PIN"
  JAVA_17_MUSL_URL: "https://gone.example.invalid/jdk.tgz"
  JAVA_11_MUSL_URL: "https://ok.example.invalid/musl11.tar.gz"
EOF
export FAKE_URLS="$TEMP_DIR/urls.txt" FAKE_CURL_DELAY=1 PROBE_DEADLINE_SECONDS=2
rc=0
output=$("$CHECK" check --out "$TEMP_DIR/deadline" --workflow "$TEMP_DIR/deadline.yml" 2>&1) || rc=$?
unset FAKE_CURL_DELAY PROBE_DEADLINE_SECONDS
assert_eq 1 "$rc" "deadline: an earlier STALE pin still fails the check"
assert_eq "JAVA_8_IBM_URL:OK JAVA_17_MUSL_URL:STALE JAVA_11_MUSL_URL:INCONCLUSIVE " \
  "$(awk -F '\t' '{ printf "%s:%s ", $1, $3 }' "$TEMP_DIR/deadline/results.tsv")" "deadline: probed pins keep their class, the rest is INCONCLUSIVE"
assert_eq "000" "$(awk -F '\t' '$1 == "JAVA_11_MUSL_URL" { print $4 }' "$TEMP_DIR/deadline/results.tsv")" "deadline: an unprobed pin reports no HTTP status"
assert_contains "$output" "::warning::Probe deadline (2s) reached" "deadline expiry warns"
assert_contains "$output" "::warning::Probe deadline reached; skipping the IBM newer-release check" "deadline skips the IBM check"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "GET $IBM_BASE" "deadline: no IBM listing fetch after the deadline"

cat > "$TEMP_DIR/no-ibm.yml" <<EOF
env:
  JAVA_11_MUSL_URL: "https://ok.example.invalid/musl11.tar.gz"
EOF
output=$("$CHECK" check --out "$TEMP_DIR/no-ibm" --workflow "$TEMP_DIR/no-ibm.yml" 2>&1)
assert_contains "$output" "JAVA_8_IBM_URL is not pinned" "missing IBM pin skips the newer-release check"

printf 'env:\n  JAVA_8_VERSION: 8.0.462\n' > "$TEMP_DIR/empty.yml"
rc=0
output=$("$CHECK" check --out "$TEMP_DIR/empty" --workflow "$TEMP_DIR/empty.yml" 2>&1) || rc=$?
assert_eq 2 "$rc" "no pins is an error, not a pass"
assert_contains "$output" "No env JAVA_*_URL keys found" "no pins message"
rc=0
"$CHECK" check --out "$TEMP_DIR/missing" --workflow "$TEMP_DIR/does-not-exist.yml" >/dev/null 2>&1 || rc=$?
assert_eq 2 "$rc" "unreadable workflow is an error"
rc=0
"$CHECK" check >/dev/null 2>&1 || rc=$?
assert_eq 2 "$rc" "check without --out is a usage error"
rc=0
"$CHECK" bogus >/dev/null 2>&1 || rc=$?
assert_eq 2 "$rc" "unknown command is a usage error"

# --- alert --dry-run -----------------------------------------------------------
reset_fakes
export RUN_URL="https://github.example.invalid/run/1"
: > "$GITHUB_STEP_SUMMARY"
output=$("$CHECK" alert --out "$OUT" --dry-run 2>&1)
assert_contains "$output" "DRY-RUN: would run: $FILE_JIRA --summary Stale JDK download URL: JAVA_17_MUSL_URL (jdk-url-check) --body-file $OUT/stale-JAVA_17_MUSL_URL.txt --priority High --label ci --component library-java" "dry-run files the stale ticket"
assert_contains "$output" "DRY-RUN: would run: $RESOLVE_JIRA --summary Stale JDK download URL: JAVA_8_IBM_URL (jdk-url-check)" "dry-run resolves a recovered pin"
assert_not_contains "$output" "JAVA_21_MUSL_URL (jdk-url-check)" "inconclusive pins raise nothing"
assert_contains "$output" "--summary Newer IBM SDK 8 release available: 8.0.8.80 (jdk-url-check)" "dry-run files the newer-release ticket"
assert_contains "$output" "--priority Medium --label ci --component library-java --on-duplicate skip" "newer-release ticket is not re-commented"
assert_contains "$output" "DRY-RUN: would post to Slack:" "dry-run prints the Slack message"
assert_contains "$output" "Stale: JAVA_17_MUSL_URL (HTTP 404)" "Slack message lists the stale pin"
assert_contains "$output" "Newer IBM SDK 8 release: 8.0.8.80 (pinned: 8.0.8.75)" "Slack message lists the newer release"
assert_eq "" "$(cat "$FAKE_CURL_LOG")" "dry-run makes no network call"
stale_body=$(cat "$OUT/stale-JAVA_17_MUSL_URL.txt")
assert_contains "$stale_body" "Run: $RUN_URL" "stale body carries the run URL"
assert_contains "$stale_body" "| Variable | URL | HTTP status | Final URL |" "stale body carries the table"
assert_contains "$stale_body" "Bump procedure" "stale body carries the bump procedure"
assert_not_contains "$stale_body" "FORCED TEST ALERT" "real stale body is not marked forced"
newer_body=$(cat "$OUT/newer-ibm.txt")
assert_contains "$newer_body" "Releases listed by IBM: 8.0.8.70 8.0.8.75 8.0.8.80. Releases newer than the pin: 1." "newer body lists the retained releases"
assert_contains "$newer_body" "Verified archive: $IBM_NEXT" "newer body carries the verified archive"
assert_contains "$(cat "$GITHUB_STEP_SUMMARY")" "- Stale: JAVA_17_MUSL_URL (HTTP 404)" "alert actions go to the step summary"

# force_issue on a healthy run reports the IBM pin, and does not resolve it.
OK_OUT="$TEMP_DIR/ok"
mkdir -p "$OK_OUT"
printf 'JAVA_11_MUSL_URL\thttps://ok.example.invalid/m.tgz\tOK\t200\thttps://ok.example.invalid/m.tgz\n' > "$OK_OUT/results.tsv"
printf 'JAVA_8_IBM_URL\t%s\tOK\t200\t%s\n' "$IBM_PIN" "$IBM_PIN" >> "$OK_OUT/results.tsv"
echo "| Variable | URL | HTTP status | Final URL |" > "$OK_OUT/table.md"
: > "$OK_OUT/ibm.txt"
output=$("$CHECK" alert --out "$OK_OUT" --dry-run 2>&1)
assert_not_contains "$output" "file-jira-issue.sh" "healthy run files nothing"
assert_not_contains "$output" "would post to Slack" "healthy run with nothing resolved posts nothing"
output=$("$CHECK" alert --out "$OK_OUT" --dry-run --force-issue 2>&1)
assert_contains "$output" "--summary Stale JDK download URL: JAVA_8_IBM_URL (jdk-url-check)" "force_issue reports the IBM pin as stale"
assert_not_contains "$output" "$RESOLVE_JIRA --summary Stale JDK download URL: JAVA_8_IBM_URL" "forced pin is not auto-resolved"
assert_contains "$output" "$RESOLVE_JIRA --summary Stale JDK download URL: JAVA_11_MUSL_URL" "other pins still auto-resolve"
assert_contains "$(cat "$OK_OUT/stale-JAVA_8_IBM_URL.txt")" "FORCED TEST ALERT" "forced body is marked"
assert_contains "$output" "Stale (forced test via force_issue): JAVA_8_IBM_URL" "forced Slack line is marked"
grep -v JAVA_8_IBM_URL "$OK_OUT/results.tsv" > "$OK_OUT/results.tmp" && mv "$OK_OUT/results.tmp" "$OK_OUT/results.tsv"
output=$("$CHECK" alert --out "$OK_OUT" --dry-run --force-issue 2>&1)
assert_contains "$output" "--summary Stale JDK download URL: JAVA_11_MUSL_URL (jdk-url-check) --body-file" "force_issue without an IBM pin reports the first pin"
output=$("$CHECK" alert --out "$TEMP_DIR/nothing" --dry-run 2>&1)
assert_contains "$output" "::warning::No check results" "alert without results warns"

# --- alert against the fake Jira and Slack -----------------------------------------
slack_text() {
  grep "^POST $FAKE_SLACK_URL " "$FAKE_CURL_LOG" | cut -d ' ' -f 3- | jq -r .text
}

reset_fakes
with_jira
export FAKE_SLACK_URL="https://hooks.slack.example.invalid/T/B/x" SLACK_WEBHOOK="https://hooks.slack.example.invalid/T/B/x"
printf '%s\n' 'PROF-7|Stale JDK download URL: JAVA_8_IBM_URL (jdk-url-check)' \
  'PROF-8|Newer IBM SDK 8 release available: 8.0.8.80 (jdk-url-check)' \
  'PROF-6|Newer IBM SDK 8 release available: 8.0.8.75 (jdk-url-check)' > "$TEMP_DIR/open.txt"
export FAKE_OPEN="$TEMP_DIR/open.txt"
: > "$GITHUB_STEP_SUMMARY"
output=$("$CHECK" alert --out "$OUT" 2>&1)
log=$(cat "$FAKE_CURL_LOG")
create=$(grep '^POST https://jira.example.invalid/rest/api/3/issue ' "$FAKE_CURL_LOG" | cut -d ' ' -f 3-)
assert_eq "1" "$(grep -c '^POST https://jira.example.invalid/rest/api/3/issue ' "$FAKE_CURL_LOG")" "one new ticket: the stale pin"
assert_eq '"Stale JDK download URL: JAVA_17_MUSL_URL (jdk-url-check)" [{"name":"library-java"}] ["ci"] "High"' \
  "$(jq -c '.fields.summary, .fields.components, .fields.labels, .fields.priority.name' <<<"$create" | tr '\n' ' ' | sed 's/ $//')" "stale ticket fields"
assert_contains "$log" 'POST https://jira.example.invalid/rest/api/3/issue/PROF-7/transitions {"transition":{"id":"31"}}' "recovered pin moves to Done, not Won't Do"
assert_contains "$log" "POST https://jira.example.invalid/rest/api/3/issue/PROF-7/comment" "recovered pin gets a comment"
assert_not_contains "$log" "PROF-8/" "open newer-release ticket above the pin is left alone"
assert_contains "$log" 'POST https://jira.example.invalid/rest/api/3/issue/PROF-6/transitions {"transition":{"id":"31"}}' "newer-release ticket at the pinned version is resolved"
assert_contains "$log" 'statusCategory != Done' "auto-resolve skips done tickets whose resolution is unset"
slack=$(grep "^POST $FAKE_SLACK_URL " "$FAKE_CURL_LOG" | cut -d ' ' -f 3-)
assert_eq '["text","scenarios","failed_run_url"]' "$(jq -c 'keys_unsorted' <<<"$slack")" "Slack payload follows certification.yml"
assert_contains "$(slack_text)" "Stale: JAVA_17_MUSL_URL (HTTP 404) https://gone.example.invalid/jdk.tgz -> PROF-9001" "Slack names the new stale ticket"
assert_contains "$(slack_text)" "Recovered: JAVA_8_IBM_URL resolves again (HTTP 200); resolved PROF-7" "Slack notes the recovery"
assert_not_contains "$(slack_text)" "Newer IBM SDK 8" "known newer release is not re-announced"
assert_eq "$RUN_URL" "$(jq -r .failed_run_url <<<"$slack")" "Slack payload carries the run URL"
assert_contains "$(cat "$GITHUB_STEP_SUMMARY")" "- IBM SDK 8 8.0.8.75 is pinned: resolved PROF-6" "newer-release resolution goes to the step summary"
assert_contains "$(cat "$GITHUB_STEP_SUMMARY")" "(created: PROF-9001)" "step summary says the ticket is new"
assert_not_contains "$output" "::warning::" "healthy Jira and Slack raise no warning"

# A stale pin whose ticket is already open: no comment, no Slack repeat.
reset_fakes
with_jira
export FAKE_SLACK_URL="$SLACK_WEBHOOK"
printf 'PROF-3|Stale JDK download URL: JAVA_17_MUSL_URL (jdk-url-check)\n' > "$TEMP_DIR/open-stale.txt"
export FAKE_OPEN="$TEMP_DIR/open-stale.txt"
: > "$GITHUB_STEP_SUMMARY"
output=$("$CHECK" alert --out "$OUT" 2>&1)
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "PROF-3/comment" "an open stale ticket is not re-commented"
assert_not_contains "$(slack_text)" "Stale: JAVA_17_MUSL_URL" "an open stale ticket is not re-announced"
assert_contains "$(cat "$GITHUB_STEP_SUMMARY")" "(existing: PROF-3)" "step summary says the ticket was already open"
assert_contains "$(slack_text)" "Newer IBM SDK 8 release: 8.0.8.80 (pinned: 8.0.8.75) -> PROF-9001" "a new newer-release ticket is announced"

# No done transition: leave the ticket untouched, warn, keep going.
reset_fakes
with_jira
export FAKE_SLACK_URL="$SLACK_WEBHOOK" FAKE_OPEN="$TEMP_DIR/open.txt" FAKE_NO_DONE=1
output=$("$CHECK" alert --out "$OUT" 2>&1)
assert_contains "$output" "::warning::PROF-7 has no transition to done; resolve it by hand" "missing done transition warns"
assert_contains "$output" "::warning::PROF-6 has no transition to done" "the next ticket is still tried"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "/comment" "an issue that cannot close gets no comment"
assert_not_contains "$(slack_text)" "resolved PROF-7" "an unresolved ticket is not reported as resolved"

# A failing transition is per issue: warn, do not stop the other attempts.
reset_fakes
with_jira
export FAKE_SLACK_URL="$SLACK_WEBHOOK" FAKE_OPEN="$TEMP_DIR/open.txt" FAKE_TRANSITION_FAIL=1
output=$("$CHECK" alert --out "$OUT" 2>&1)
assert_contains "$output" "::warning::PROF-7 could not be resolved (exit 5)" "a failed transition warns"
assert_contains "$output" "::warning::PROF-6 could not be resolved (exit 5)" "a failed transition does not stop auto-resolve"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "PROF-7/comment" "no comment without a transition"

# Slack rejects the post: warn only.
reset_fakes
with_jira
export FAKE_SLACK_URL="$SLACK_WEBHOOK" FAKE_SLACK_FAIL=1
output=$("$CHECK" alert --out "$OUT" 2>&1)
assert_contains "$output" "::warning::Slack notification failed" "Slack failure warns"

# No credentials: Slack still goes out, the resolve warning appears once.
reset_fakes
without_jira
: > "$GITHUB_STEP_SUMMARY"
export FAKE_SLACK_URL="$SLACK_WEBHOOK"
output=$("$CHECK" alert --out "$OUT" 2>&1)
assert_contains "$output" "::warning::Jira ticket 'Stale JDK download URL: JAVA_17_MUSL_URL (jdk-url-check)' could not be filed (exit 3)" "missing credentials warn on filing"
assert_contains "$output" "::warning::Jira ticket 'Newer IBM SDK 8 release available: 8.0.8.80 (jdk-url-check)' could not be filed (exit 3)" "missing credentials warn on the newer-release ticket"
assert_contains "$(cat "$GITHUB_STEP_SUMMARY")" "- Stale: JAVA_17_MUSL_URL (HTTP 404) https://gone.example.invalid/jdk.tgz (failed)" "step summary shows a failed filing"
assert_eq "1" "$(grep -c 'Jira credentials missing; skipping auto-resolve' <<<"$output")" "auto-resolve warns once"
assert_contains "$(slack_text)" "Stale: JAVA_17_MUSL_URL (HTTP 404)" "without a ticket the stale pin is announced"
assert_contains "$(slack_text)" "Newer IBM SDK 8 release: 8.0.8.80" "without a ticket the newer release is announced"
assert_eq "0" "$(grep -c 'rest/api' "$FAKE_CURL_LOG" || true)" "no Jira call without credentials"

# Jira API down: filing warns, and one auto-resolve warning covers every pin.
reset_fakes
with_jira
export FAKE_JIRA_FAIL=1
unset SLACK_WEBHOOK
output=$("$CHECK" alert --out "$OUT" 2>&1)
assert_contains "$output" "::warning::Jira ticket 'Stale JDK download URL: JAVA_17_MUSL_URL (jdk-url-check)' could not be filed (exit 1)" "a Jira outage blocks filing, not the run"
assert_eq "1" "$(grep -c 'Auto-resolve lookup failed' <<<"$output")" "failed lookups stop after the first"
# Two filing lookups (stale, newer) and the first resolve lookup.
assert_eq "3" "$(grep -c 'search/jql' "$FAKE_CURL_LOG")" "no resolve lookup after the first failure"
assert_contains "$output" "SLACK_WEBHOOK not configured, skipping notification" "missing webhook is skipped"
export SLACK_WEBHOOK="https://hooks.slack.example.invalid/T/B/x"

# Outside GitHub Actions RUN_URL falls back to the run coordinates.
reset_fakes
unset RUN_URL
output=$(GITHUB_SERVER_URL=https://gh.example.invalid GITHUB_REPOSITORY=o/r GITHUB_RUN_ID=42 "$CHECK" alert --out "$OUT" --dry-run 2>&1)
assert_contains "$(cat "$OUT/stale-JAVA_17_MUSL_URL.txt")" "Run: https://gh.example.invalid/o/r/actions/runs/42" "default RUN_URL"
export RUN_URL="https://github.example.invalid/run/1"

# --- file-jira-issue.sh options ------------------------------------------------------
reset_fakes
with_jira
echo "body" > "$TEMP_DIR/body.txt"
"$FILE_JIRA" --summary "no component" --body-file "$TEMP_DIR/body.txt" --label x >/dev/null
assert_eq "false" "$(grep '/rest/api/3/issue ' "$FAKE_CURL_LOG" | cut -d ' ' -f 3- | jq '.fields | has("components")')" "no --component keeps the old payload"
"$FILE_JIRA" --summary "two components" --body-file "$TEMP_DIR/body.txt" --component a --component b --status-file "$TEMP_DIR/status" >/dev/null
assert_eq '[{"name":"a"},{"name":"b"}]' "$(grep '/rest/api/3/issue ' "$FAKE_CURL_LOG" | tail -n 1 | cut -d ' ' -f 3- | jq -c '.fields.components')" "--component is repeatable"
assert_eq "created" "$(cat "$TEMP_DIR/status")" "--status-file reports created"
printf 'PROF-5|dup\n' > "$TEMP_DIR/open-dup.txt"
export FAKE_OPEN="$TEMP_DIR/open-dup.txt"
: > "$FAKE_CURL_LOG"
assert_eq "PROF-5" "$("$FILE_JIRA" --summary dup --body-file "$TEMP_DIR/body.txt" --on-duplicate skip --status-file "$TEMP_DIR/status")" "skip prints the existing key"
assert_eq "existing" "$(cat "$TEMP_DIR/status")" "--status-file reports existing"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "PROF-5/comment" "--on-duplicate skip does not comment"
"$FILE_JIRA" --summary dup --body-file "$TEMP_DIR/body.txt" >/dev/null
assert_contains "$(cat "$FAKE_CURL_LOG")" "POST https://jira.example.invalid/rest/api/3/issue/PROF-5/comment" "default still comments on a duplicate"
export FAKE_JIRA_FAIL=1
: > "$FAKE_CURL_LOG"
rc=0
"$FILE_JIRA" --summary fresh --body-file "$TEMP_DIR/body.txt" --on-duplicate skip >/dev/null 2>&1 || rc=$?
assert_eq 1 "$rc" "skip files nothing when the dedupe lookup fails"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "/rest/api/3/issue " "no issue POST after a failed skip lookup"
unset FAKE_JIRA_FAIL
rc=0
"$FILE_JIRA" --summary dup --body-file "$TEMP_DIR/body.txt" --on-duplicate bogus >/dev/null 2>&1 || rc=$?
assert_eq 2 "$rc" "invalid --on-duplicate is a usage error"
export FAKE_SEARCH_FAIL=1
: > "$FAKE_CURL_LOG"
assert_eq "PROF-9001" "$("$FILE_JIRA" --summary fresh --body-file "$TEMP_DIR/body.txt" 2>/dev/null)" "comment mode still files when the dedupe lookup fails"
unset FAKE_SEARCH_FAIL
: > "$FAKE_CURL_LOG"
"$FILE_JIRA" --summary fresh --body-file "$TEMP_DIR/body.txt" >/dev/null
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "statusCategory" "comment mode keeps the old dedupe query"
: > "$FAKE_CURL_LOG"
"$FILE_JIRA" --summary fresh --body-file "$TEMP_DIR/body.txt" --on-duplicate skip >/dev/null
assert_contains "$(cat "$FAKE_CURL_LOG")" "Unresolved AND statusCategory != Done" "skip ignores done tickets with an unset resolution"

# --- resolve-jira-issue.sh -------------------------------------------------------------
reset_fakes
with_jira
assert_eq "" "$("$RESOLVE_JIRA" --summary "nothing open" --comment-file "$TEMP_DIR/body.txt")" "nothing open resolves nothing"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "/comment" "nothing open adds no comment"
rc=0
"$RESOLVE_JIRA" --summary x >/dev/null 2>&1 || rc=$?
assert_eq 2 "$rc" "resolve without --comment-file is a usage error"
rc=0
"$RESOLVE_JIRA" --summary x --comment-file "$TEMP_DIR/missing.txt" >/dev/null 2>&1 || rc=$?
assert_eq 2 "$rc" "resolve with a missing comment file is a usage error"
without_jira
rc=0
"$RESOLVE_JIRA" --summary x --comment-file "$TEMP_DIR/body.txt" >/dev/null 2>&1 || rc=$?
assert_eq 3 "$rc" "resolve without credentials exits 3"
with_jira
export FAKE_JIRA_FAIL=1
rc=0
"$RESOLVE_JIRA" --summary x --comment-file "$TEMP_DIR/body.txt" >/dev/null 2>&1 || rc=$?
assert_eq 1 "$rc" "resolve API failure exits 1"
unset FAKE_JIRA_FAIL
printf 'PROF-4|open one\n' > "$TEMP_DIR/open-one.txt"
export FAKE_OPEN="$TEMP_DIR/open-one.txt" FAKE_TRANSITIONS_GET_FAIL=1
rc=0
key=$("$RESOLVE_JIRA" --summary "open one" --comment-file "$TEMP_DIR/body.txt" 2>/dev/null) || rc=$?
assert_eq "5 PROF-4" "$rc $key" "a failed transition lookup exits 5 and names the issue"
unset FAKE_TRANSITIONS_GET_FAIL
export FAKE_COMMENT_FAIL=1
rc=0
key=$("$RESOLVE_JIRA" --summary "open one" --comment-file "$TEMP_DIR/body.txt" 2>"$TEMP_DIR/resolve.err") || rc=$?
assert_eq "0 PROF-4" "$rc $key" "a failed comment after the transition still reports the resolution"
assert_contains "$(cat "$TEMP_DIR/resolve.err")" "PROF-4 resolved, but the comment failed" "a failed comment warns"
unset FAKE_COMMENT_FAIL FAKE_OPEN

# A phrase hit whose summary merely contains the phrase is never closed.
printf '%s\n' 'PROF-10|Stale JDK download URL: JAVA_9_MUSL_URL (jdk-url-check) build-4521' \
  'PROF-11|Stale JDK download URL: JAVA_9_MUSL_URL (jdk-url-check)' > "$TEMP_DIR/open-long.txt"
export FAKE_OPEN="$TEMP_DIR/open-long.txt"
assert_eq "PROF-11" "$("$RESOLVE_JIRA" --summary "Stale JDK download URL: JAVA_9_MUSL_URL (jdk-url-check)" --comment-file "$TEMP_DIR/body.txt")" "the exact summary match is resolved"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "PROF-10/" "a longer phrase hit is left open"
assert_eq "PROF-11" "$("$RESOLVE_JIRA" --summary "stale jdk download url: java_9_musl_url (jdk-url-check)" --comment-file "$TEMP_DIR/body.txt")" "the summary comparison is case-insensitive"
printf 'PROF-10|Stale JDK download URL: JAVA_9_MUSL_URL (jdk-url-check) build-4521\n' > "$TEMP_DIR/open-only-long.txt"
reset_fakes
with_jira
export FAKE_OPEN="$TEMP_DIR/open-only-long.txt"
rc=0
output=$("$RESOLVE_JIRA" --summary "Stale JDK download URL: JAVA_9_MUSL_URL (jdk-url-check)" --comment-file "$TEMP_DIR/body.txt" 2>"$TEMP_DIR/resolve-long.err") || rc=$?
assert_eq 0 "$rc" "a non-exact phrase hit resolves nothing and exits 0"
assert_contains "$(cat "$TEMP_DIR/resolve-long.err")" "none with the exact summary" "a non-exact phrase hit warns"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "/transitions" "no transition without an exact summary match"
unset FAKE_OPEN

# --- java_setup.sh fetchAndExtract ---------------------------------------------------
# GitHub's default run shell is bash -e without pipefail; each case runs so.
# run_setup <variant> <arch>: runs prepareJdk in a subshell, output in setup.out.
run_setup() {
  (
    set +o pipefail
    # shellcheck disable=SC1090,SC1091 # path resolved at run time
    source "$SETUP"
    prepareJdk "$1" "$2"
    echo "not reached"
  ) > "$TEMP_DIR/setup.out" 2>&1
}

reset_fakes
echo "archive" > "$TEMP_DIR/archive.tgz"
printf '%s 200\nhttps://gone.example.invalid/jdk.tgz 404\n' "$IBM_PIN" > "$TEMP_DIR/dl.txt"
export FAKE_URLS="$TEMP_DIR/dl.txt" FAKE_DOWNLOAD="$TEMP_DIR/archive.tgz"
export GITHUB_WORKSPACE="$TEMP_DIR/ws" JDKS_DIR=jdks
setup_case() {
  # setup_case <variant> <arch> <url var> <expected tar line> <sudo 0|1>
  reset_fakes
  export FAKE_URLS="$TEMP_DIR/dl.txt" FAKE_DOWNLOAD="$TEMP_DIR/archive.tgz"
  export "$3=$IBM_PIN"
  run_setup "$1" "$2" || true
  local log
  log=$(cat "$FAKE_CURL_LOG")
  assert_contains "$log" "$4" "prepareJdk $1 $2: tar arguments"
  if [ "$5" = 1 ]; then
    assert_contains "$log" "sudo" "prepareJdk $1 $2: extracts with sudo"
  else
    assert_not_contains "$log" "sudo" "prepareJdk $1 $2: extracts without sudo"
  fi
  assert_contains "$(cat "$TEMP_DIR/setup.out")" "HTTP status: 200" "prepareJdk $1 $2: prints the HTTP status"
  unset "$3"
}
setup_case 8-ibm amd64 JAVA_8_IBM_URL "tar -xvzf - -C $GITHUB_WORKSPACE/jdks/jdk8-ibm --strip-components 2" 1
setup_case 8-orcl amd64 JAVA_8_ORACLE_URL "tar -xvzf - -C $GITHUB_WORKSPACE/jdks/jdk8-orcl --strip-components 1" 1
setup_case 17-librca amd64-musl JAVA_17_MUSL_URL "tar -xvzf - -C $GITHUB_WORKSPACE/jdks/jdk17-librca --strip-components 1" 0
setup_case 21-librca aarch64-musl JAVA_21_MUSL_AARCH64_URL "tar -xvzf - -C $GITHUB_WORKSPACE/jdks/jdk21-librca --strip-components 1" 0
setup_case 21-zing aarch64 JAVA_21_ZING_AARCH64_URL "tar -xvzf - -C $GITHUB_WORKSPACE/jdks/jdk21-zing --strip-components 1" 1

reset_fakes
export FAKE_URLS="$TEMP_DIR/dl.txt" FAKE_DOWNLOAD="$TEMP_DIR/archive.tgz" JAVA_8_IBM_URL="https://gone.example.invalid/jdk.tgz"
rc=0
run_setup 8-ibm amd64 || rc=$?
assert_eq 1 "$rc" "a 404 fails prepareJdk without pipefail"
assert_contains "$(cat "$TEMP_DIR/setup.out")" "HTTP status: 404" "a 404 prints its HTTP status"
assert_contains "$(cat "$TEMP_DIR/setup.out")" "Download failed (curl exit 22, HTTP status above): https://gone.example.invalid/jdk.tgz" "404 is reported as a download failure"
assert_not_contains "$(cat "$TEMP_DIR/setup.out")" "not reached" "prepareJdk stops on a failed download"

reset_fakes
export FAKE_URLS="$TEMP_DIR/dl.txt" FAKE_DOWNLOAD="$TEMP_DIR/archive.tgz" FAKE_TAR_RC=2
rc=0
(
  set +o pipefail
  # shellcheck disable=SC1090,SC1091 # path resolved at run time
  source "$SETUP"
  fetchAndExtract "$IBM_PIN" "$TEMP_DIR/ws/x" 1
) > "$TEMP_DIR/setup.out" 2>&1 || rc=$?
assert_eq 1 "$rc" "a tar failure fails fetchAndExtract"
assert_contains "$(cat "$TEMP_DIR/setup.out")" "Extraction failed (tar exit 2)" "tar failure is reported"
assert_not_contains "$(cat "$FAKE_CURL_LOG")" "sudo" "plain tar without the sudo argument"

echo "test_check_jdk_urls.sh: $TESTS checks passed"
