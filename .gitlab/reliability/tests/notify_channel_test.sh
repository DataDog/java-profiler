#! /bin/bash
# Copyright 2026, Datadog, Inc.
#
# Network-free tests for .gitlab/reliability/notify_channel.sh: the REASON_
# failure post, the INCONCLUSIVE_ post, the green-pipeline no-op and the
# CANCELLED early exit. postmessage is replaced by a stub that records every
# call, so no network and no Slack are involved.
# Run with: bash .gitlab/reliability/tests/notify_channel_test.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
SCRIPT="${HERE}/../notify_channel.sh"

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

VERSION=2.1.0
CI_PROJECT_URL=https://gitlab.example.com/datadog/java-profiler
CI_PIPELINE_ID=42
PIPELINE_LINK="<${CI_PROJECT_URL}/pipelines/${CI_PIPELINE_ID}|pipeline #${CI_PIPELINE_ID}>"

# Recorded against the pre-change script run with a stubbed postmessage; the
# REASON_ branch text must stay identical to it.
FAIL_REASON="Memory usage is trending up"
FAIL_MSG=":bomb: Reliability test failed for ${VERSION} (pipeline=${PIPELINE_LINK}, reason=\"${FAIL_REASON}\", config=\"profiler_gmalloc_amd64\", variant=\"memory\")"
FAIL_POST="#java-profiler-lib|${FAIL_MSG}|alert"

INCONCLUSIVE_REASON="Only 4 memory samples were recorded, at least 5 are needed"
INCONCLUSIVE_MSG="Reliability memory check inconclusive for ${VERSION} (pipeline=${PIPELINE_LINK}, reason=\"${INCONCLUSIVE_REASON}\", config=\"profiler_tracer_jemalloc_aarch64\", variant=\"memory\")"
INCONCLUSIVE_POST="#java-profiler-lib|${INCONCLUSIVE_MSG}|alert"

# Runs the script in a clean environment with only the given variables, a
# postmessage stub on PATH and its output at <dir>/posts.txt; prints the exit
# code. env -i keeps inherited REASON_/INCONCLUSIVE_ vars out of the run.
run_notify() { # $1 dir, then VAR=VALUE pairs for the clean environment
  local dir=$1
  shift
  mkdir -p "${dir}/bin"
  cat > "${dir}/bin/postmessage" <<'STUB'
#!/bin/bash
printf '%s|%s|%s\n' "$1" "$2" "$3" >> "$NOTIFY_POSTS"
STUB
  chmod +x "${dir}/bin/postmessage"
  : > "${dir}/posts.txt"
  env -i \
    PATH="${dir}/bin:/usr/bin:/bin" \
    HOME="${dir}" \
    CI_PROJECT_URL="${CI_PROJECT_URL}" \
    CI_PIPELINE_ID="${CI_PIPELINE_ID}" \
    NOTIFY_POSTS="${dir}/posts.txt" \
    "$@" bash "${SCRIPT}" "${VERSION}" \
    > "${dir}/out.log" 2> "${dir}/trace.log"
  echo $?
}

post_count() { # $1 dir
  wc -l < "${1}/posts.txt" | tr -d ' '
}

# --- a REASON_ key posts the unchanged failure message --------------------------

CASE="${WORK}/fail"
rc=$(run_notify "${CASE}" "REASON_profiler_gmalloc_amd64Xmemory=${FAIL_REASON}")
assert_eq "a REASON_ run exits 0" "0" "${rc}"
assert_eq "a REASON_ key posts exactly once" "1" "$(post_count "${CASE}")"
assert_eq "the failure post is byte-identical to the recorded expectation" \
  "${FAIL_POST}" "$(sed -n '1p' "${CASE}/posts.txt")"

# --- an INCONCLUSIVE_ key posts the distinct non-bomb message ---------------------

CASE="${WORK}/inconclusive"
rc=$(run_notify "${CASE}" "INCONCLUSIVE_profiler_tracer_jemalloc_aarch64Xmemory=${INCONCLUSIVE_REASON}")
assert_eq "an INCONCLUSIVE_ run exits 0" "0" "${rc}"
assert_eq "an INCONCLUSIVE_ key posts exactly once" "1" "$(post_count "${CASE}")"
assert_eq "the inconclusive post carries version, pipeline, config and variant" \
  "${INCONCLUSIVE_POST}" "$(sed -n '1p' "${CASE}/posts.txt")"
if grep -q ':bomb:' "${CASE}/posts.txt"; then
  fail_case "the inconclusive message uses :bomb:"
else
  pass "the inconclusive message does not use :bomb:"
fi

# --- both keys post both messages ------------------------------------------------

CASE="${WORK}/mixed"
rc=$(run_notify "${CASE}" \
  "REASON_profiler_gmalloc_amd64Xmemory=${FAIL_REASON}" \
  "INCONCLUSIVE_profiler_tracer_jemalloc_aarch64Xmemory=${INCONCLUSIVE_REASON}")
assert_eq "a mixed run exits 0" "0" "${rc}"
assert_eq "a mixed run posts exactly twice" "2" "$(post_count "${CASE}")"
assert_eq "the failure message is posted in the mixed run" "1" \
  "$(grep -cF "${FAIL_MSG}" "${CASE}/posts.txt")"
assert_eq "the inconclusive message is posted in the mixed run" "1" \
  "$(grep -cF "${INCONCLUSIVE_MSG}" "${CASE}/posts.txt")"

# --- a fully green pipeline posts nothing and exits 0 -----------------------------

CASE="${WORK}/green"
rc=$(run_notify "${CASE}" "UNRELATED=1")
assert_eq "a green run exits 0" "0" "${rc}"
assert_eq "a green run posts nothing" "0" "$(post_count "${CASE}")"

# --- CANCELLED exits before posting ----------------------------------------------

CASE="${WORK}/cancelled"
rc=$(run_notify "${CASE}" \
  "CANCELLED=1" \
  "REASON_profiler_gmalloc_amd64Xmemory=${FAIL_REASON}")
assert_eq "a cancelled run exits 0" "0" "${rc}"
assert_eq "a cancelled run posts nothing" "0" "$(post_count "${CASE}")"

if [ "${FAILED}" -eq 0 ]; then
  echo "All notify_channel tests passed"
  exit 0
fi
echo "notify_channel tests failed"
exit 1
