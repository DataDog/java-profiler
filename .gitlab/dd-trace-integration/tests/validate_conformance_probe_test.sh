#! /bin/bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for the event-type probe wiring in
# test-validation/validate-jfr-conformance.sh.
# Run with: bash .gitlab/dd-trace-integration/tests/validate_conformance_probe_test.sh
#
# jfr-shell is stubbed through a fake `jbang` on PATH: the probe script's
# canned output drives the HAS_* flags, and the validation script's stubbed
# output drives the pass/fail verdict. No real recording or JFR parsing runs.

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

run_validate() {
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
grep -q "datadog.ExecutionSample: true" "${WORK}/stdout.log" \
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
grep -q "datadog.ExecutionSample: false" "${WORK}/stdout.log" \
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
grep -q "datadog.ExecutionSample: true" "${WORK}/stdout.log" \
  || fail "the fallback should flag datadog.ExecutionSample as present"
pass "the fallback flags all types present"

[ "${FAILED}" -eq 0 ] || exit 1
echo "All validate-jfr-conformance probe tests passed."
