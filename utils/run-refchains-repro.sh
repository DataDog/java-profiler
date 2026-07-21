#!/usr/bin/env bash
#
# Runs the standalone reference-chains repro app (ddprof-stresstest/src/repro)
# with -agentpath and a set of referencechains sub-options known to actually
# reach the app's leaking CachedEntry population - see ReferenceChainLeakDemo's
# own class comment for why the tracker's auto-scaled first-pass budget
# (referenceChains.h's AUTO_FIRST_PASS_BUDGET_MULTIPLIER/_CAP) matters here.
#
# The jar takes the JFR output path as its own arg and periodically calls
# JavaProfiler.dump() on it - also load-bearing, per ReferenceChainLeakDemo's
# comment: without a dump() call nothing ever drains the tracker's pending
# chain-event queue, so datadog.ReferenceChain never actually lands in the file.
#
# Usage: run-refchains-repro.sh [jfr-output-path]
#
# Env vars:
#   REFCHAINS_SO   path to libjavaProfiler.so/.dylib (default: locate the
#                   locally built debug artifact under ddprof-lib/build/lib)
#   REFCHAINS_JAR  path to refchains_repro.jar (default: build/rebuild via
#                   ./gradlew :ddprof-stresstest:reproJar)
#   REFCHAINS_ARGS extra referencechains=... sub-options appended after the
#                   baked-in defaults below (e.g. "hops=32")

set -euo pipefail

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ROOT="$( cd "${HERE}/.." >/dev/null 2>&1 && pwd )"

JFR_OUT="${1:-/tmp/refchains_repro.jfr}"

if [ -z "${REFCHAINS_SO:-}" ]; then
  REFCHAINS_SO=$(find "${ROOT}/ddprof-lib/build/lib" -name 'libjavaProfiler.so' -o -name 'libjavaProfiler.dylib' 2>/dev/null | head -1)
fi
if [ -z "${REFCHAINS_SO}" ] || [ ! -f "${REFCHAINS_SO}" ]; then
  echo "FAIL:libjavaProfiler.so/.dylib not found - build one first: ./gradlew :ddprof-lib:debugSharedLibrary" >&2
  exit 1
fi
echo "Using agent: ${REFCHAINS_SO}"

if [ -z "${REFCHAINS_JAR:-}" ]; then
  REFCHAINS_JAR="${ROOT}/ddprof-stresstest/build/libs/refchains_repro.jar"
  if [ ! -f "${REFCHAINS_JAR}" ]; then
    echo "refchains_repro.jar not present - building it"
    ( cd "${ROOT}" && ./gradlew :ddprof-stresstest:reproJar -q --no-daemon )
  fi
fi
if [ ! -f "${REFCHAINS_JAR}" ]; then
  echo "FAIL:refchains_repro.jar unavailable" >&2
  exit 1
fi
echo "Using jar: ${REFCHAINS_JAR}"

# No firstpassbudget here: the tracker auto-scales the first pass's budget
# from budget=4000 (currently x50, capped at 200000 - referenceChains.h) so
# it can actually reach this app's leaking population. Pass
# REFCHAINS_ARGS="firstpassbudget=N" to override that auto-scaled default.
REFERENCECHAINS_OPTS="true:hops=64:budget=10000:ttl=120000:framecap=2000000:pausetarget=500:painbudget=100"
if [ -n "${REFCHAINS_ARGS:-}" ]; then
  REFERENCECHAINS_OPTS="${REFERENCECHAINS_OPTS}:${REFCHAINS_ARGS}"
fi

echo "JFR output: ${JFR_OUT}"
rm -f "${JFR_OUT}"

exec java \
  -agentpath:"${REFCHAINS_SO}"=start,memory=64:l,generations=true,referencechains=${REFERENCECHAINS_OPTS},jfr,file="${JFR_OUT}" \
  -jar "${REFCHAINS_JAR}" "${JFR_OUT}" "${REFCHAINS_SO}"
