#! /bin/bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for the event-type probe wiring in
# test-validation/validate-jfr-conformance.sh.
# Run with: bash .gitlab/dd-trace-integration/tests/validate_conformance_probe_test.sh
#
# jfr-shell is stubbed through a fake `jbang` on PATH: the probe script's
# canned output drives the HAS_* flags, and the validation script's stubbed
# output drives the pass/fail verdict. No real recording or JFR parsing runs;
# the real probe execution is covered by probe_event_types_real_test.sh.

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${HERE}/../../../test-validation/validate-jfr-conformance.sh"

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

# Installs a fake jbang. The probe answers with the given lines; the validation
# stub derives its verdict from the HAS flags the conformance script passes
# (arg 15 = datadog.ExecutionSample registered), so a regression in
# has_event_type flips the validation verdict instead of hiding behind SUCCESS.
install_stub_jbang() {
  local probe_out="$1"
  mkdir -p "${WORK}/bin"
  cat > "${WORK}/bin/jbang" <<STUB
#! /bin/bash
args=("\$@")
for arg in "\${args[@]}"; do
  case "\${arg}" in
    *probe-event-types.jfrs*)
      printf '%b\n' '${probe_out}'
      exit 0
      ;;
  esac
done
for i in "\${!args[@]}"; do
  case "\${args[\$i]}" in
    *validate-jfr.jfrs*) fidx=\$((i + 1)); break ;;
  esac
done
# After the .jfrs path: 1=recording, 2=scenario, 3-5=min counts, 6=expected
# CPU type, ...; the datadog.ExecutionSample HAS flag is argument 15.
expected_cpu="\${args[\$((fidx + 5))]}"
dd_exec_flag="\${args[\$((fidx + 14))]}"
if [ "\${expected_cpu}" = "datadog" ] && [ "\${dd_exec_flag}" != "true" ]; then
  echo '"VALIDATION_FAILED: required CPU events absent"'
  exit 1
fi
echo '"SUCCESS: All validations passed"'
exit 0
STUB
  chmod +x "${WORK}/bin/jbang"
  echo "dummy recording" > "${WORK}/recording.jfr"
}

# The HAS flag log is the last block that prints "<type>: <value>"; earlier
# blocks print other flags under the same type names.
flag_of() {
  { grep -F "${1}: " "${WORK}/stdout.log" || true; } | tail -1 | sed 's/.*: //'
}

# SC2030/SC2031: the subshell PATH scope is the mechanism — each run sees
# only the stub jbang, and the parent shell keeps its real PATH.
run_validate() {
  # shellcheck disable=SC2030,SC2031
  ( export PATH="${WORK}/bin:${PATH}"
    bash "${SCRIPT}" "${WORK}/recording.jfr" \
      --ddprof-enabled=true --tracer-enabled=false --test-duration=60 \
      --arch=x64 --libc=musl --jvm-type=hotspot \
      --output="${WORK}/validation-out.log" ) > "${WORK}/stdout.log" 2>&1
}

# 1. A complete probe listing datadog.ExecutionSample must validate: this is
#    the shape of the failed integration run -- hundreds of CPU events that the
#    degraded `metadata` command could not see. The flag-driven stub makes the
#    verdict depend on the HAS flag actually reaching the validation script.
install_stub_jbang 'HAS jdk.ExecutionSample 0\nHAS datadog.ExecutionSample 674\nHAS jdk.ObjectAllocationSample 0\nHAS datadog.ObjectSample 378\nHAS jdk.ThreadAllocationStatistics 45\nHAS datadog.Endpoint 0\nPROBE_COMPLETE'
if run_validate; then
  pass "a complete probe with datadog.ExecutionSample present validates"
else
  fail "a complete probe with datadog.ExecutionSample present should validate (exit $?)"
fi
[ "$(flag_of datadog.ExecutionSample)" = "true" ] \
  || fail "the flag log should report datadog.ExecutionSample as true when the probe lists it"
pass "a probed type is flagged true in the flag log"

# 2. A probe that omits datadog.ExecutionSample flags it false; the flag-driven
#    stub then fails the validation, proving the false actually flows through.
#    What must NOT happen is a fallback-to-present: that is the degraded
#    metadata behavior this change removes.
install_stub_jbang 'HAS jdk.ExecutionSample 0\nHAS jdk.ObjectAllocationSample 0\nHAS jdk.ThreadAllocationStatistics 45\nPROBE_COMPLETE'
if run_validate; then
  fail "an absent required type should fail the flag-driven validation"
else
  pass "an absent required type fails the validation"
fi
[ "$(flag_of datadog.ExecutionSample)" = "false" ] \
  || fail "the flag log should report datadog.ExecutionSample as false when the probe omits it"
pass "an absent type is flagged false in the flag log"

# 3. An incomplete probe (PROBE_COMPLETE missing) must fall back to "all types
#    present" so the real queries still run -- the degraded-metadata case must
#    never silently gate the validation off.
install_stub_jbang 'HAS jdk.ExecutionSample 0'
if run_validate; then
  pass "an incomplete probe falls back to all-present and validates"
else
  fail "an incomplete probe should fall back to all-present (exit $?)"
fi

# 4. The absent type must be flagged true again by the fallback, even though
#    the probe output carried no line for it.
[ "$(flag_of datadog.ExecutionSample)" = "true" ] \
  || fail "the fallback should flag datadog.ExecutionSample as present"
pass "the fallback flags all types present"

# 5. A type that is only a prefix of a probed name must not count as present:
#    has_event_type matches "HAS <type> " including the trailing space.
install_stub_jbang 'HAS datadog.ExecutionSampleExtra 5\nPROBE_COMPLETE'
run_validate || true
[ "$(flag_of datadog.ExecutionSample)" = "false" ] \
  || fail "a probe listing only datadog.ExecutionSampleExtra must not flag datadog.ExecutionSample"
pass "a type name that is a prefix of a probed type is not matched"

# 6. Without the probe script next to it, the conformance script falls back to
#    all-present rather than gating the queries off.
NOPROBE="${WORK}/noprobe"
mkdir -p "${NOPROBE}"
cp "${SCRIPT}" "${HERE}/../../../test-validation/validate-jfr.jfrs" "${NOPROBE}/"
install_stub_jbang 'HAS jdk.ExecutionSample 0\nPROBE_COMPLETE'
# shellcheck disable=SC2030,SC2031  # deliberate: the stub PATH must not leak past this run
( export PATH="${WORK}/bin:${PATH}"
  bash "${NOPROBE}/validate-jfr-conformance.sh" "${WORK}/recording.jfr" \
    --ddprof-enabled=true --tracer-enabled=false --test-duration=60 \
    --arch=x64 --libc=musl --jvm-type=hotspot \
    --output="${WORK}/validation-out.log" ) > "${WORK}/stdout.log" 2>&1 \
  || fail "a missing probe script should fall back to all-present and validate"
grep -q "Probe script not found" "${WORK}/stdout.log" \
  || fail "a missing probe script should log a warning"
[ "$(flag_of datadog.ExecutionSample)" = "true" ] \
  || fail "a missing probe script should flag all types present"
pass "a missing probe script falls back to all-present"

# 7. The probe script queries and reports every type the conformance script
#    asks about: one events/<type> query and one HAS line per has_event_type.
PROBE="${HERE}/../../../test-validation/probe-event-types.jfrs"
TYPES=$(grep -o 'has_event_type "[^"]*"' "${SCRIPT}" | sed 's/has_event_type "//; s/"$//')
[ -n "${TYPES}" ] || fail "no has_event_type calls found in the conformance script"
for t in ${TYPES}; do
  grep -qF "events/${t} |" "${PROBE}" || fail "probe script has no events/${t} query"
  grep -qF "echo \"HAS ${t} " "${PROBE}" || fail "probe script has no HAS line for ${t}"
done
pass "the probe script covers every type the conformance script checks"

# 8. JAVA_HOME from the JVM under test (e.g., OpenJ9 JDK 25) must not leak to
#    jbang, which needs its managed HotSpot JDK 25 for tooling.
mkdir -p "${WORK}/bin-env"
cat > "${WORK}/bin-env/jbang" <<'STUB'
#! /bin/bash
if [ -n "${JAVA_HOME:-}" ]; then
  echo "ERROR: JAVA_HOME leaked to jbang: ${JAVA_HOME}" >&2
  exit 99
fi
for arg in "$@"; do
  case "${arg}" in
    *probe-event-types.jfrs*)
      printf 'HAS jdk.ExecutionSample 0\nHAS datadog.ExecutionSample 10\nHAS jdk.ObjectAllocationSample 0\nHAS datadog.ObjectSample 5\nHAS jdk.ThreadAllocationStatistics 1\nHAS datadog.Endpoint 0\nPROBE_COMPLETE\n'
      exit 0
      ;;
  esac
done
echo '"SUCCESS: All validations passed"'
exit 0
STUB
chmod +x "${WORK}/bin-env/jbang"
# shellcheck disable=SC2031  # prior subshell PATH overrides are deliberately isolated
PATH="${WORK}/bin-env:${PATH}" JAVA_HOME="/opt/java/openj9-25" \
  bash "${SCRIPT}" "${WORK}/recording.jfr" \
    --ddprof-enabled=true --tracer-enabled=false --test-duration=60 \
    --arch=x64 --libc=glibc --jvm-type=openj9 \
    --output="${WORK}/validation-out.log" > "${WORK}/stdout.log" 2>&1 \
  || fail "JAVA_HOME leaked to jbang during conformance validation"
pass "conformance validation unsets JAVA_HOME before invoking jbang"

[ "${FAILED}" -eq 0 ] || exit 1
echo "All validate-jfr-conformance probe tests passed."
