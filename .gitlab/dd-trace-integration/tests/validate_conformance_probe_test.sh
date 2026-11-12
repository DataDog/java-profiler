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

# Installs a fake jbang that answers the probe with the given lines (one per
# HAS line, plus PROBE_COMPLETE) and reports the validation as passed.
install_stub_jbang() {
  local probe_out="$1"
  mkdir -p "${WORK}/bin"
  cat > "${WORK}/bin/jbang" <<STUB
#! /bin/bash
for arg in "\$@"; do
  case "\${arg}" in
    *probe-event-types.jfrs*)
      printf '%b\n' '${probe_out}'
      exit 0
      ;;
    *validate-jfr.jfrs*)
      echo '"SUCCESS: All validations passed"'
      exit 0
      ;;
  esac
done
echo "unexpected jbang invocation: \$*" >&2
exit 97
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
#    the PROF-16618 shape -- 674 CPU events that the degraded `metadata`
#    command could not see.
install_stub_jbang 'HAS jdk.ExecutionSample 0\nHAS datadog.ExecutionSample 674\nHAS jdk.ObjectAllocationSample 0\nHAS datadog.ObjectSample 378\nHAS jdk.ThreadAllocationStatistics 45\nHAS datadog.Endpoint 0\nPROBE_COMPLETE'
if run_validate; then
  pass "a complete probe with datadog.ExecutionSample present validates"
else
  fail "a complete probe with datadog.ExecutionSample present should validate (exit $?)"
fi

# 2. A probe that omits datadog.ExecutionSample must NOT abort the validation:
#    the absent type is treated as zero events and the remaining checks decide.
install_stub_jbang 'HAS jdk.ExecutionSample 0\nHAS jdk.ObjectAllocationSample 0\nHAS jdk.ThreadAllocationStatistics 45\nPROBE_COMPLETE'
if run_validate; then
  pass "an absent-type probe does not abort the validation"
else
  fail "an absent-type probe should not abort the validation (exit $?)"
fi

# 3. An incomplete probe (PROBE_COMPLETE missing) must fall back to "all types
#    present" so the real queries still run -- the degraded-metadata case must
#    never silently gate the validation off.
install_stub_jbang 'HAS jdk.ExecutionSample 0'
if run_validate; then
  pass "an incomplete probe falls back to all-present and validates"
else
  fail "an incomplete probe should fall back to all-present (exit $?)"
fi

# 4. The flag log must reflect the probe, not the backend: datadog types the
#    probe lists are "true" even though a degraded metadata view would say
#    "false".
grep -q "datadog.ExecutionSample: true" "${WORK}/stdout.log" \
  || fail "the flag log should take datadog.ExecutionSample from the probe"
pass "the flag log reflects the probe output"

[ "${FAILED}" -eq 0 ] || exit 1
echo "All validate-jfr-conformance probe tests passed."
