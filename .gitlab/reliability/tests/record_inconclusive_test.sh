#! /bin/bash
# Copyright 2026, Datadog, Inc.
#
# Network-free tests for .gitlab/reliability/record_inconclusive.sh and for
# the wiring of its step into both reliability YAML templates. The script is
# run in a scratch job directory with fixture err.log files; no network and
# no JVM are involved.
# Run with: bash .gitlab/reliability/tests/record_inconclusive_test.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
SCRIPT="${HERE}/../record_inconclusive.sh"
SCHEDULED_YAML="${HERE}/../.gitlab-ci.yml"
PR_YAML="${HERE}/../pr-child.gitlab-ci.yml"

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

# Runs the recorder with the CI matrix variables set and the job directory
# at $1; $2..$5 are CONFIG, ALLOCATOR, ARCH, VARIANT.
run_case() { # $1 dir, $2 config, $3 allocator, $4 arch, $5 variant
  (
    cd "$1" || exit 1
    export CONFIG="$2" ALLOCATOR="$3" ARCH="$4" VARIANT="$5"
    exec bash "${SCRIPT}"
  )
}

REASON="Only 4 memory samples were recorded, at least 5 are needed"

# --- records the first inconclusive line --------------------------------------

CASE="${WORK}/one"
mkdir -p "${CASE}"
printf 'INCONCLUSIVE:%s\n' "${REASON}" > "${CASE}/err.log"
run_case "${CASE}" 'profiler+tracer' gmalloc amd64 memory
assert_eq "an inconclusive line records and exits 0" "0" "$?"
assert_eq "the key maps + to _ and carries the variant" \
  "INCONCLUSIVE_profiler_tracer_gmalloc_amd64Xmemory=${REASON}" \
  "$(sed -n '1p' "${CASE}/build.env")"

CASE="${WORK}/first"
mkdir -p "${CASE}"
{
  printf 'INCONCLUSIVE:first reason\n'
  printf 'INCONCLUSIVE:second reason\n'
} > "${CASE}/err.log"
run_case "${CASE}" profiler jemalloc aarch64 memory
assert_eq "only the first inconclusive line is used" \
  "INCONCLUSIVE_profiler_jemalloc_aarch64Xmemory=first reason" \
  "$(sed -n '1p' "${CASE}/build.env")"

CASE="${WORK}/mixed"
mkdir -p "${CASE}"
{
  echo "some noise captured in err.log"
  printf 'INCONCLUSIVE:%s\n' "${REASON}"
} > "${CASE}/err.log"
run_case "${CASE}" profiler gmalloc amd64 memory
assert_eq "noise before the verdict line is skipped" \
  "INCONCLUSIVE_profiler_gmalloc_amd64Xmemory=${REASON}" \
  "$(sed -n '1p' "${CASE}/build.env")"

# --- writes nothing without an inconclusive line -------------------------------

CASE="${WORK}/nofail"
mkdir -p "${CASE}"
echo "FAIL:Memory usage is trending up" > "${CASE}/err.log"
run_case "${CASE}" profiler gmalloc amd64 memory
assert_eq "a fail-only err.log exits 0" "0" "$?"
if [ ! -e "${CASE}/build.env" ]; then
  pass "no INCONCLUSIVE_ key is written for a confirmed fail"
else
  fail_case "a fail-only run wrote to build.env: $(cat "${CASE}/build.env")"
fi

CASE="${WORK}/empty"
mkdir -p "${CASE}"
: > "${CASE}/err.log"
run_case "${CASE}" profiler gmalloc amd64 memory
assert_eq "an empty err.log exits 0" "0" "$?"
if [ ! -e "${CASE}/build.env" ]; then
  pass "an empty err.log writes nothing"
else
  fail_case "an empty err.log wrote to build.env"
fi

CASE="${WORK}/nolog"
mkdir -p "${CASE}"
run_case "${CASE}" profiler gmalloc amd64 memory
assert_eq "a missing err.log exits 0" "0" "$?"
if [ ! -e "${CASE}/build.env" ]; then
  pass "a missing err.log writes nothing"
else
  fail_case "a missing err.log wrote to build.env"
fi

# --- appends instead of truncating ---------------------------------------------

CASE="${WORK}/append"
mkdir -p "${CASE}"
printf 'REASON_profiler_gmalloc_amd64Xjit=some failure\n' > "${CASE}/build.env"
printf 'INCONCLUSIVE:%s\n' "${REASON}" > "${CASE}/err.log"
run_case "${CASE}" 'profiler+tracer' gmalloc amd64 memory
assert_eq "a pre-existing build.env line is kept" \
  "REASON_profiler_gmalloc_amd64Xjit=some failure" \
  "$(sed -n '1p' "${CASE}/build.env")"
assert_eq "the inconclusive key is appended" \
  "INCONCLUSIVE_profiler_tracer_gmalloc_amd64Xmemory=${REASON}" \
  "$(sed -n '2p' "${CASE}/build.env")"
assert_eq "build.env keeps exactly two lines" "2" "$(sed -n '$=' "${CASE}/build.env")"

# --- the reason survives both REASON parsers -----------------------------------

# The scheduled job cuts values at the first colon and the PR child cuts
# from it, so a reason with a colon would be truncated by one of them; a
# backtick would break shell word splitting downstream.
scheduled_value=$(grep -m1 'INCONCLUSIVE:' "${CASE}/err.log" | cut -f2 -d':')
assert_eq "the scheduled cut -f2 -d':' parser reads the reason whole" \
  "${REASON}" "${scheduled_value}"
pr_value=$(grep -m1 'INCONCLUSIVE:' "${CASE}/err.log" | cut -f2- -d':' | tr -d '\n')
assert_eq "the PR child cut -f2- parser reads the reason whole" \
  "${REASON}" "${pr_value}"

if printf '%s' "${REASON}" | grep -q '[:`]'; then
  fail_case "the fixture reason carries a colon or backtick"
else
  pass "the reason is single-line with no colon and no backtick"
fi

# --- YAML wiring: both templates gain the step after the fail path --------------

assert_wiring() { # $1 description, $2 yaml, $3 fixed string that must appear
  if grep -qF -- "$3" "$2"; then
    pass "$1"
  else
    fail_case "$1: [$3] is missing from $2"
  fi
}

# shellcheck disable=SC2016  # the checked strings must stay literal
SCHED_PARSER="REASON=\$(cat err.log | grep \"FAIL:\" | cut -f2 -d':') || true"
# shellcheck disable=SC2016  # the PR parser fixture must not be expanded by this test script
PR_PARSER="REASON=\$(grep -m1 'FAIL:' err.log | cut -f2- -d':' | tr -d '\n') || true"
# shellcheck disable=SC2016  # the fail-exit fixture vars must stay literal for grep
SCHED_FAIL_EXIT="if [ -n \"\${REASON}\" ]; then echo \"REASON_\${CONFIG}_\${ALLOCATOR}_\${ARCH}X\${VARIANT}=\${REASON}\" | tr '+' '_' >> build.env; exit 1; fi"
# shellcheck disable=SC2016  # the PR fail-exit fixture vars must stay literal for grep
PR_FAIL_EXIT="if [ -n \"\${REASON}\" ]; then _key=\$(printf 'REASON_%s_%s_%sX%s' \"\${CONFIG}\" \"\${ALLOCATOR}\" \"\${ARCH}\" \"\${VARIANT}\" | tr '+' '_'); echo \"\${_key}=\${REASON}\" >> build.env; exit 1; fi"

assert_wiring "the scheduled REASON parser is unchanged" "${SCHEDULED_YAML}" "${SCHED_PARSER}"
assert_wiring "the PR child REASON parser is unchanged" "${PR_YAML}" "${PR_PARSER}"
assert_wiring "the scheduled fail exit is unchanged" "${SCHEDULED_YAML}" "${SCHED_FAIL_EXIT}"
assert_wiring "the PR child fail exit is unchanged" "${PR_YAML}" "${PR_FAIL_EXIT}"
assert_wiring "the scheduled timeout fallback stays" "${SCHEDULED_YAML}" 'Unknown failure, perhaps timeout'
assert_wiring "the PR child timeout fallback stays" "${PR_YAML}" 'Unknown failure, perhaps timeout'

# The recorder step must sit after the fail exit line, so it runs only when
# the confirmed-fail path has not fired.
step_after_fail_exit() { # $1 yaml, $2 fail-exit line, $3 description
  local fail_line step_line
  fail_line=$(grep -nF -- "$2" "$1" | head -1 | cut -d: -f1)
  step_line=$(grep -nF '.gitlab/reliability/record_inconclusive.sh' "$1" | head -1 | cut -d: -f1)
  if [ -n "${fail_line}" ] && [ -n "${step_line}" ] && [ "${step_line}" -gt "${fail_line}" ]; then
    pass "$3"
  else
    fail_case "$3: recorder step at ${step_line}, fail exit at ${fail_line}"
  fi
}

step_after_fail_exit "${SCHEDULED_YAML}" "${SCHED_FAIL_EXIT}" \
  "the scheduled recorder step follows the unchanged fail exit"
step_after_fail_exit "${PR_YAML}" "${PR_FAIL_EXIT}" \
  "the PR child recorder step follows the unchanged fail exit"

# The notify step runs on every scheduled pipeline; staying silent on a green
# one is notify_channel.sh's duty, not a rule change here.
notify_rules=$(sed -n '/^notify-slack:/,/^publish-reliability-gh-pages:/p' "${SCHEDULED_YAML}")
if printf '%s' "${notify_rules}" | grep -q 'when: always' && \
   ! printf '%s' "${notify_rules}" | grep -q 'when: on_failure'; then
  pass "the notify-slack rule runs on every scheduled pipeline"
else
  fail_case "the notify-slack rule is not when: always"
fi

if [ "${FAILED}" -eq 0 ]; then
  echo "All record_inconclusive tests passed"
  exit 0
fi
echo "record_inconclusive tests failed"
exit 1
