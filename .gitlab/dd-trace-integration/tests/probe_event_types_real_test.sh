#! /bin/bash

# Copyright 2026, Datadog, Inc

# Executes the real probe-event-types.jfrs through jbang/jfr-shell against a
# deterministic synthetic recording (probe_event_types_fixture.java): two
# tracked types present, four absent. This covers what the hermetic
# validate_conformance_probe_test.sh cannot: variable interpolation in the
# HAS lines, the absent-type line suppression, and PROBE_COMPLETE surviving
# failed queries. Requires jbang on PATH; the dd-trace-integration CI job
# runs install-prerequisites.sh before this script.
#
# Run with: bash .gitlab/dd-trace-integration/tests/probe_event_types_real_test.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_ROOT=$(cd "${HERE}/../../.." && pwd)
PROBE="${REPO_ROOT}/test-validation/probe-event-types.jfrs"
FIXTURE="${HERE}/probe_event_types_fixture.java"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

fail() {
  echo "FAIL: $*" >&2
  FAILED=1
}

pass() {
  echo "  ok: $*"
}

if ! command -v jbang &> /dev/null; then
  fail "jbang not found on PATH; install-prerequisites.sh must run first"
  exit 1
fi
[ -f "${PROBE}" ] || { fail "probe script not found: ${PROBE}"; exit 1; }
[ -f "${FIXTURE}" ] || { fail "fixture not found: ${FIXTURE}"; exit 1; }

# Same Maven routing as validate-jfr-conformance.sh: jfr-shell resolves from
# Maven Central, unreachable directly from CI runners.
JBANG_REPOS_OPT=""
if [ -n "${MAVEN_REPOSITORY_PROXY:-}" ]; then
  JBANG_REPOS_OPT="--repos=central=${MAVEN_REPOSITORY_PROXY}"
fi

RECORDING="${WORK}/synthetic.jfr"
# shellcheck disable=SC2086  # empty or one --repos option
if ! jbang run --java 25 ${JBANG_REPOS_OPT} "${FIXTURE}" "${RECORDING}" > "${WORK}/gen.log" 2>&1; then
  cat "${WORK}/gen.log" >&2
  fail "fixture recording generation failed"
  exit 1
fi
[ -s "${RECORDING}" ] || { fail "generated recording is empty"; exit 1; }

# stderr is not silenced: the absent-type queries print "Event type ... not
# found" there by design; only stdout drives the HAS contract.
# shellcheck disable=SC2086  # empty or one --repos option
jbang --java 25 ${JBANG_REPOS_OPT} jfr-shell@btraceio script "${PROBE}" "${RECORDING}" \
  > "${WORK}/probe-stdout.log" 2> "${WORK}/probe-stderr.log"
PROBE_EXIT=$?

[ "${PROBE_EXIT}" -eq 0 ] \
  || fail "the probe exited ${PROBE_EXIT}; it must exit 0 when tracked types are absent"
pass "the probe exits 0 when tracked types are absent"

grep -qF "HAS jdk.ExecutionSample 2" "${WORK}/probe-stdout.log" \
  || fail "expected HAS jdk.ExecutionSample 2 in the probe output"
grep -qF "HAS datadog.ExecutionSample 3" "${WORK}/probe-stdout.log" \
  || fail "expected HAS datadog.ExecutionSample 3 in the probe output"
pass "present types report their exact event counts (interpolation works)"

for t in datadog.ObjectSample datadog.Endpoint; do
  if grep -qF "HAS ${t} " "${WORK}/probe-stdout.log"; then
    fail "absent custom type ${t} must not produce a HAS line"
  fi
done
pass "absent custom types produce no HAS line"

# JDK built-in types resolve through the engine's schema even when the
# recording has none of them, so their HAS line is emitted with count 0 --
# observed on this fixture (observed on JDK 25 recordings; the line-present
# signal then means resolvable, and the validation thresholds read the count).
grep -qF "HAS jdk.ObjectAllocationSample 0" "${WORK}/probe-stdout.log" \
  || fail "expected HAS jdk.ObjectAllocationSample 0 for an absent JDK built-in type"
pass "absent JDK built-in types report count 0"

HAS_LINES=$(grep -cE '"HAS [^ ]+ [0-9]+"' "${WORK}/probe-stdout.log" || true)
[ "${HAS_LINES}" -eq 4 ] \
  || fail "expected 4 HAS lines with numeric counts, got ${HAS_LINES}"
pass "every HAS line carries a numeric count"

grep -qF "PROBE_COMPLETE" "${WORK}/probe-stdout.log" \
  || fail "PROBE_COMPLETE missing from the probe output"
LAST_EMIT=$(grep '^"\?\(HAS \|PROBE_COMPLETE\)' "${WORK}/probe-stdout.log" | tail -1)
[ "${LAST_EMIT}" = '"PROBE_COMPLETE"' ] \
  || fail "expected PROBE_COMPLETE as the last script-emitted line, got: ${LAST_EMIT}"
pass "PROBE_COMPLETE is emitted last, after the failed queries"

# Same grep as has_event_type in validate-jfr-conformance.sh: the flags it
# derives from the real output must agree with the recording's actual content.
has_event_type() {
  grep -qF -- "HAS ${1} " "${WORK}/probe-stdout.log" && echo true || echo false
}
[ "$(has_event_type datadog.ExecutionSample)" = "true" ] \
  || fail "has_event_type semantics must flag a present type true"
[ "$(has_event_type datadog.Endpoint)" = "false" ] \
  || fail "has_event_type semantics must flag an absent type false"
pass "has_event_type's grep semantics agree with the real probe output"

[ "${FAILED}" -eq 0 ] || exit 1
echo "probe-event-types real-probe tests passed."
