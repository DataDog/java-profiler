#! /bin/bash
# Copyright 2026, Datadog, Inc.
#
# Network-free tests for the run JSON produced by
# .gitlab/reliability/generate-run-json.sh. REASON_ rows must keep landing in
# failures and memory_trend_warnings, INCONCLUSIVE_ rows must land in their own
# fields and never in failures, passed must subtract both kinds, and the
# status must never be passed while any row is inconclusive.
# Run with: bash .gitlab/reliability/tests/generate_run_json_test.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
SCRIPT="${HERE}/../generate-run-json.sh"

FAILED=0
WORK=$(mktemp -d)

# shellcheck disable=SC2329  # cleanup runs through the EXIT trap
cleanup() {
  rm -rf "${WORK}"
}
trap cleanup EXIT

pass() { echo "PASS: $1"; }
fail_case() { echo "FAIL: $1"; FAILED=1; }

assert_eq() { # $1 what, $2 expected, $3 actual
  if [ "$2" = "$3" ]; then
    pass "$1"
  else
    fail_case "$1: expected [$2] got [$3]"
  fi
}

# Runs the generator on $1 with fixed metadata. The branch 'main' makes
# lookup-pr.sh skip its GitHub query, keeping the test network-free.
run_json() { # $1 artifacts dir
  CI_PIPELINE_ID=42 CI_PIPELINE_URL='https://example.invalid/42' \
    DDPROF_COMMIT_BRANCH=main DDPROF_COMMIT_SHA=deadbeef CURRENT_VERSION=1.2.3 \
    bash "${SCRIPT}" "$1"
}

# Extracts a field from run JSON $1 through the python expression $2, which is
# evaluated over the parsed run as the variable r.
field() { # $1 run json, $2 python expression
  printf '%s' "$1" | python3 -c "import json,sys; r = json.load(sys.stdin); print($2)"
}

summary_field() { # $1 run json, $2 python expression over the summary dict s
  printf '%s' "$1" | python3 -c "import json,sys; s = json.load(sys.stdin)['summary']; print($2)"
}

# Runs the generator on $1 and fails the case if it exits non-zero or prints
# unparseable JSON.
case_run() { # $1 dir, sets JSON and leaves the exit status in CASE_RC
  JSON=$(run_json "$1")
  CASE_RC=$?
  if [ "${CASE_RC}" -ne 0 ] || [ -z "${JSON}" ]; then
    fail_case "the generator exits 0 and prints JSON for $(basename "$1")"
    JSON='{}'
  fi
}

assert_not_passed_with_inconclusive() { # $1 run json, $2 description
  local status
  status=$(field "$1" "r['status']")
  if [ "${status}" = "passed" ]; then
    fail_case "$2: status must not be passed while rows are inconclusive"
  else
    pass "$2: status [${status}] is not the success-implying passed"
  fi
}

# --- fail-only run: every config failed ----------------------------------------

CASE="${WORK}/failonly"
mkdir -p "${CASE}"
{
  i=1
  while [ "${i}" -le 36 ]; do
    printf 'REASON_profiler%d_gmalloc_amd64Xmemory=Memory usage is trending up\n' "${i}"
    i=$((i + 1))
  done
} > "${CASE}/build.env"
case_run "${CASE}"
assert_eq "fail-only status is failed" "failed" "$(field "${JSON}" "r['status']")"
assert_eq "fail-only counts every row as failed" "36" \
  "$(summary_field "${JSON}" "s['failed']")"
assert_eq "fail-only leaves no passed configs" "0" \
  "$(summary_field "${JSON}" "s['passed']")"
assert_eq "fail-only records no inconclusive rows" "0" \
  "$(summary_field "${JSON}" "s['inconclusive']")"
assert_eq "fail-only formats every failure" "36" \
  "$(summary_field "${JSON}" "len(s['failures'])")"
assert_eq "the trending reason lands in failures" \
  "profiler1-gmalloc-amd64-memory: Memory usage is trending up" \
  "$(summary_field "${JSON}" "s['failures'][0]")"
assert_eq "the trending reason lands in memory_trend_warnings" \
  "profiler1-gmalloc-amd64-memory" \
  "$(summary_field "${JSON}" "s['memory_trend_warnings'][0]")"
assert_eq "memory_trend_warnings tracks all 36 rows" "36" \
  "$(summary_field "${JSON}" "len(s['memory_trend_warnings'])")"

# --- inconclusive-only run: nothing failed, nothing counted as failure ---------

CASE="${WORK}/inconclusive"
mkdir -p "${CASE}"
{
  echo 'INCONCLUSIVE_profiler_jemalloc_aarch64Xmemory=Only 4 memory samples were recorded, at least 5 are needed'
  echo 'INCONCLUSIVE_profiler_tracer_gmalloc_amd64Xmemory=cpu PSI too high'
} > "${CASE}/build.env"
case_run "${CASE}"
assert_eq "inconclusive-only status is partial" "partial" "$(field "${JSON}" "r['status']")"
assert_not_passed_with_inconclusive "${JSON}" "inconclusive-only"
assert_eq "inconclusive-only counts the rows" "2" \
  "$(summary_field "${JSON}" "s['inconclusive']")"
assert_eq "inconclusive-only reduces passed by the same count" "34" \
  "$(summary_field "${JSON}" "s['passed']")"
assert_eq "inconclusive-only counts no failures" "0" \
  "$(summary_field "${JSON}" "s['failed']")"
assert_eq "nothing lands in failures" "0" \
  "$(summary_field "${JSON}" "len(s['failures'])")"
assert_eq "nothing lands in memory_trend_warnings" "0" \
  "$(summary_field "${JSON}" "len(s['memory_trend_warnings'])")"
assert_eq "inconclusive_configs lists the labels in file order" \
  "['profiler-jemalloc-aarch64-memory', 'profiler-tracer-gmalloc_amd64-memory']" \
  "$(summary_field "${JSON}" "s['inconclusive_configs']")"

# An unparsable INCONCLUSIVE_ key is reported, never dropped into failures.
CASE="${WORK}/unknownkey"
mkdir -p "${CASE}"
echo 'INCONCLUSIVE_garbage=odd key' > "${CASE}/build.env"
case_run "${CASE}"
assert_eq "an unparsable inconclusive key keeps the run partial" "partial" \
  "$(field "${JSON}" "r['status']")"
assert_not_passed_with_inconclusive "${JSON}" "unknown inconclusive key"
assert_eq "the unparsable key is counted as inconclusive" "1" \
  "$(summary_field "${JSON}" "s['inconclusive']")"
assert_eq "the unparsable key is reported through its raw text" \
  "['INCONCLUSIVE_garbage=odd key']" \
  "$(summary_field "${JSON}" "s['inconclusive_configs']")"
assert_eq "the unparsable key never lands in failures" "0" \
  "$(summary_field "${JSON}" "len(s['failures'])")"

# Every row inconclusive: passed reaches 0 without any failure, so the run
# must still not take the failed status reserved for failed-only runs.
CASE="${WORK}/allinconclusive"
mkdir -p "${CASE}"
{
  i=1
  while [ "${i}" -le 36 ]; do
    printf 'INCONCLUSIVE_profiler%d_jemalloc_amd64Xmemory=few samples\n' "${i}"
    i=$((i + 1))
  done
} > "${CASE}/build.env"
case_run "${CASE}"
assert_eq "an all-inconclusive run with no passed configs is partial" "partial" \
  "$(field "${JSON}" "r['status']")"
assert_not_passed_with_inconclusive "${JSON}" "all-inconclusive"
assert_eq "an all-inconclusive run has no passed configs" "0" \
  "$(summary_field "${JSON}" "s['passed']")"
assert_eq "an all-inconclusive run counts no failures" "0" \
  "$(summary_field "${JSON}" "s['failed']")"

# --- mixed run: failures and inconclusive rows coexist -------------------------

CASE="${WORK}/mixed"
mkdir -p "${CASE}"
{
  echo 'REASON_profiler_gmalloc_amd64Xmemory=Memory usage is trending up'
  echo 'INCONCLUSIVE_profiler_jemalloc_aarch64Xmemory=few samples'
} > "${CASE}/build.env"
case_run "${CASE}"
assert_eq "a mixed run is partial" "partial" "$(field "${JSON}" "r['status']")"
assert_not_passed_with_inconclusive "${JSON}" "mixed"
assert_eq "a mixed run counts one failure" "1" \
  "$(summary_field "${JSON}" "s['failed']")"
assert_eq "a mixed run counts one inconclusive row" "1" \
  "$(summary_field "${JSON}" "s['inconclusive']")"
assert_eq "passed subtracts failures and inconclusive rows" "34" \
  "$(summary_field "${JSON}" "s['passed']")"
assert_eq "the failure keeps its label and reason" \
  "profiler-gmalloc-amd64-memory: Memory usage is trending up" \
  "$(summary_field "${JSON}" "s['failures'][0]")"
assert_eq "the mixed-run failure still lands in memory_trend_warnings" \
  "['profiler-gmalloc-amd64-memory']" \
  "$(summary_field "${JSON}" "s['memory_trend_warnings']")"
assert_eq "the mixed run reports the inconclusive label" \
  "['profiler-jemalloc-aarch64-memory']" \
  "$(summary_field "${JSON}" "s['inconclusive_configs']")"

# --- green run: no reason rows at all ------------------------------------------

CASE="${WORK}/green"
mkdir -p "${CASE}"
echo 'SOME_UNRELATED_KEY=some value' > "${CASE}/build.env"
case_run "${CASE}"
assert_eq "a run without reason rows is passed" "passed" "$(field "${JSON}" "r['status']")"
assert_eq "a green run passes every expected config" "36" \
  "$(summary_field "${JSON}" "s['passed']")"
assert_eq "a green run reports no failures" "0" \
  "$(summary_field "${JSON}" "s['failed']")"
assert_eq "a green run reports no inconclusive rows" "0" \
  "$(summary_field "${JSON}" "s['inconclusive']")"

# --- REASON_ parsing stays byte-identical, including the tracer mis-split -----

# Recorded against the generator before inconclusive support was added; the
# fixture mixes REASON_ and INCONCLUSIVE_ rows across nested build.env files so
# the check also proves the new parsing never perturbs the old one.
CASE="${WORK}/recorded"
mkdir -p "${CASE}/profiler/gmalloc" "${CASE}/profiler/jemalloc"
{
  echo 'REASON_profiler_tcmalloc_amd64Xjit=Some unrelated crash'
  echo 'REASON_profiler_tracer_gmalloc_amd64Xmemory=Memory usage is trending up'
  echo 'REASON_profiler_jemalloc_aarch64Xchaos=weird failure with = equals in reason'
  echo 'REASON_garbage=unparsable key'
} > "${CASE}/profiler/gmalloc/build.env"
echo 'INCONCLUSIVE_profiler_jemalloc_amd64Xmemory=few samples' \
  > "${CASE}/profiler/jemalloc/build.env"
case_run "${CASE}"

# shellcheck disable=SC2016  # the recorded expectation is a fixed literal
RECORDED_FAILURES="['profiler-tcmalloc-amd64-jit: Some unrelated crash', 'profiler-tracer-gmalloc_amd64-memory: Memory usage is trending up', 'profiler-jemalloc-aarch64-chaos: weird failure with = equals in reason', 'REASON_garbage=unparsable key: REASON_garbage=unparsable key']"
assert_eq "failures match the recorded pre-change expectation" \
  "${RECORDED_FAILURES}" "$(summary_field "${JSON}" "s['failures']")"
assert_eq "memory_trend_warnings match the recorded pre-change expectation" \
  "['profiler-tracer-gmalloc_amd64-memory']" \
  "$(summary_field "${JSON}" "s['memory_trend_warnings']")"
assert_eq "the failed count is unchanged by the inconclusive row" "4" \
  "$(summary_field "${JSON}" "s['failed']")"
assert_eq "the nested inconclusive row is counted separately" "1" \
  "$(summary_field "${JSON}" "s['inconclusive']")"
assert_eq "the nested inconclusive row never lands in failures" "4" \
  "$(summary_field "${JSON}" "len(s['failures'])")"
assert_eq "passed subtracts both kinds from the expected total" "31" \
  "$(summary_field "${JSON}" "s['passed']")"

# --- YAML wiring: build.env must be downloadable as a regular artifact -------

# The generator parses build.env files from the artifact download. GitLab only
# makes a dotenv report available as a file to later jobs when it is also
# listed in artifacts:paths, so each reliability template must list it in every
# artifacts block it defines.
SCHEDULED_YAML="${HERE}/../.gitlab-ci.yml"
PR_YAML="${HERE}/../pr-child.gitlab-ci.yml"

build_env_path_count() { # $1 yaml
  sed -n '/^  artifacts:/,/^    reports:/p' "$1" | grep -cF -- 'build.env'
}

assert_eq "scheduled pipeline lists build.env in both artifacts paths" "2" \
  "$(build_env_path_count "${SCHEDULED_YAML}")"
assert_eq "PR child pipeline lists build.env in both artifacts paths" "2" \
  "$(build_env_path_count "${PR_YAML}")"

if [ "${FAILED}" -eq 0 ]; then
  echo "All generate_run_json tests passed"
  exit 0
fi
echo "generate_run_json tests failed"
exit 1
