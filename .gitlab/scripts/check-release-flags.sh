#! /bin/bash
#
# Checks that a release-build shared object carries no trace of the opt-in
# -PenableFaultInjection / -PenableSamplerPerf build flags (see
# ConfigurationPresets.kt). Both are additive: they append -D__FAULT_INJECTION__
# / -D__SAMPLER_PERF__ on top of the normal release config, so a build with
# either one active still passes every other check -- it links, it runs, it
# looks like a release build. Fault injection deliberately corrupts memory
# reads on a random sample of calls, and the sampler-perf probes add a timing
# report at Profiler::stop(); shipping either to customers would be a silent
# correctness/perf regression that nothing else here would catch.
#
# Rather than diffing against a golden symbol list (which the additive nature
# of the flags would make brittle), this looks for markers that exist only
# because a flag was on: mangled symbols from the flag-only code (faultInjection.h
# / samplerPerf.h), plus the counter names those flags add to counters.h, which
# survive as plain strings in .rodata even if the symbols themselves get
# inlined away.
#
# Usage: check-release-flags.sh <shared-object>
#   e.g. check-release-flags.sh libs/linux-x64/libjavaProfiler.so
#
# Relies on the release .so still carrying its symbol table: build.sh strips
# only debug sections (--strip-debug), not the symbol table itself, before
# this runs.
#
# Set NM / STRINGS to point at different binutils tools; the unit tests use
# them to feed canned output in.

set -eo pipefail

SO="$1"
NM="${NM:-nm}"
STRINGS="${STRINGS:-strings}"

die() {
  echo "ERROR: $*" >&2
  exit 1
}

if [ -z "${SO}" ]; then
  echo "usage: $(basename "$0") <shared-object>" >&2
  exit 2
fi

[ -f "${SO}" ] || die "no such file: ${SO}"
command -v "${NM}" >/dev/null 2>&1 || die "${NM} not found"
command -v "${STRINGS}" >/dev/null 2>&1 || die "${STRINGS} not found"

# "<marker>::<flag>::<description>". Symbol markers are substrings of the
# Itanium mangling nm prints by default, so they match every overload,
# constructor and destructor without needing c++filt.
SYMBOL_MARKERS=(
  '_ZN8faultinj::-PenableFaultInjection::the faultinj:: namespace (faultInjection.h)'
  '_Z8crashNowv::-PenableFaultInjection::crashNow() (faultInjection.h)'
  '_ZN16SamplerPerfProbe::-PenableSamplerPerf::the SamplerPerfProbe class (samplerPerf.h)'
)

STRING_MARKERS=(
  'faults_injected::-PenableFaultInjection::the "faults_injected" counter (counters.h)'
  'sampler_ticks.::-PenableSamplerPerf::the "sampler_ticks.*" counters (counters.h)'
  'sampler_count.::-PenableSamplerPerf::the "sampler_count.*" counters (counters.h)'
)

SYMTAB=$("${NM}" "${SO}" 2>/dev/null) || die "${NM} failed on ${SO}"
if [ -z "${SYMTAB}" ]; then
  echo "ERROR: ${NM} found no symbols in ${SO}." >&2
  echo "       A release build's symbol table survives strip --strip-debug (see" >&2
  echo "       build.sh), so this is far more likely to mean the wrong file was" >&2
  echo "       passed than that the library is clean. Refusing to report a pass." >&2
  exit 1
fi

STRTAB=$("${STRINGS}" "${SO}") || die "${STRINGS} failed on ${SO}"

STATUS=0

for entry in "${SYMBOL_MARKERS[@]}"; do
  marker="${entry%%::*}"
  rest="${entry#*::}"
  flag="${rest%%::*}"
  desc="${rest#*::}"
  # A here-string, not a pipe: `printf ... | grep -q` would let grep's early
  # exit on the first match send SIGPIPE back to printf, and pipefail would
  # then report that SIGPIPE as the pipeline's failure -- turning a match
  # into a false "not found".
  if grep -qF -- "${marker}" <<< "${SYMTAB}"; then
    echo "FAIL: ${SO} contains ${desc}, built only under ${flag}." >&2
    STATUS=1
  fi
done

for entry in "${STRING_MARKERS[@]}"; do
  marker="${entry%%::*}"
  rest="${entry#*::}"
  flag="${rest%%::*}"
  desc="${rest#*::}"
  if grep -qF -- "${marker}" <<< "${STRTAB}"; then
    echo "FAIL: ${SO} contains ${desc}, built only under ${flag}." >&2
    STATUS=1
  fi
done

if [ "${STATUS}" -eq 0 ]; then
  echo "OK: ${SO} carries no -PenableFaultInjection / -PenableSamplerPerf markers"
else
  echo "      Rebuild the release artifact without these -P flags." >&2
fi

exit "${STATUS}"
