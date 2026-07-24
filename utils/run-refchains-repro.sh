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
# Usage: run-refchains-repro.sh [jfr-output-path] [duration-seconds]
#
# duration-seconds (optional) bounds the run and makes the app print a single
# "[metrics]" summary line (throughput/round-latency/heap growth) at exit
# instead of running forever - see ReferenceChainLeakDemo.reportMetrics(). Also
# enables -Xlog safepoint+GC logging to <jfr-output-path>.safepoint.log and
# .gc.log for STW-pause analysis. Used by compare-refchains-repro.sh to A/B
# referencechains=true vs. false over an identical bounded window.
#
# Env vars:
#   REFCHAINS_SO      path to libjavaProfiler.so/.dylib (default: locate the
#                      locally built debug artifact under ddprof-lib/build/lib)
#   REFCHAINS_JAR      path to refchains_repro.jar (default: build/rebuild via
#                      ./gradlew :ddprof-stresstest:reproJar)
#   REFCHAINS_ENABLED  "true" (default) or "false" - toggles the
#                      referencechains=... agent sub-option itself, for A/B
#                      comparison against a baseline with the feature off.
#   REFCHAINS_ARGS     extra referencechains=... sub-options appended after the
#                      baked-in defaults below (e.g. "hops=32")
#   REFCHAINS_JAVA_HOME  JDK home to launch the repro with (default: "java" on
#                      PATH). Lets you A/B a specific JDK, e.g. to reproduce a
#                      version-specific VMStructs bug: REFCHAINS_JAVA_HOME=/usr/local/sdkman/candidates/java/25.0.3-tem
#   REFCHAINS_GC       GC to force via -XX:+Use<name>GC (default: JVM's own
#                      ergonomic default - no flag added). Accepts either the
#                      bare name ("Serial", "G1", "Parallel", "Shenandoah",
#                      "Z", "Epsilon") or the full flag name ("SerialGC").
#                      e.g. REFCHAINS_GC=Serial or REFCHAINS_GC=ZGC

set -euo pipefail

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ROOT="$( cd "${HERE}/.." >/dev/null 2>&1 && pwd )"

JFR_OUT="${1:-/tmp/refchains_repro.jfr}"
DURATION_SECONDS="${2:-}"

JAVA_BIN="java"
if [ -n "${REFCHAINS_JAVA_HOME:-}" ]; then
  JAVA_BIN="${REFCHAINS_JAVA_HOME}/bin/java"
  if [ ! -x "${JAVA_BIN}" ]; then
    echo "FAIL: ${JAVA_BIN} not found/executable - check REFCHAINS_JAVA_HOME" >&2
    exit 1
  fi
fi
echo "Using JDK: $("${JAVA_BIN}" -version 2>&1 | head -1)"

GC_JVM_OPTS=()
if [ -n "${REFCHAINS_GC:-}" ]; then
  case "${REFCHAINS_GC}" in
    *GC) GC_FLAG="-XX:+Use${REFCHAINS_GC}" ;;
    *)   GC_FLAG="-XX:+Use${REFCHAINS_GC}GC" ;;
  esac
  GC_JVM_OPTS=("${GC_FLAG}")
  echo "Forcing GC: ${GC_FLAG}"
else
  echo "GC: JVM ergonomic default"
fi

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
REFCHAINS_ENABLED="${REFCHAINS_ENABLED:-true}"
REFERENCECHAINS_OPTS="${REFCHAINS_ENABLED}:hops=64:budget=10000:ttl=120000:framecap=2000000:pausetarget=500:painbudget=100"
if [ -n "${REFCHAINS_ARGS:-}" ]; then
  REFERENCECHAINS_OPTS="${REFERENCECHAINS_OPTS}:${REFCHAINS_ARGS}"
fi

echo "JFR output: ${JFR_OUT}"
echo "referencechains enabled: ${REFCHAINS_ENABLED}"
rm -f "${JFR_OUT}"

JAVA_LOG_OPTS=()
if [ -n "${DURATION_SECONDS}" ]; then
  # Unified-logging safepoint+GC pause detail, kept per-run alongside the JFR file so
  # compare-refchains-repro.sh can parse "Total time for which application threads were
  # stopped" (STW safepoint pauses, includes GC) and per-GC pause times out of one file.
  SAFEPOINT_LOG="${JFR_OUT}.safepoint.log"
  rm -f "${SAFEPOINT_LOG}"
  JAVA_LOG_OPTS=(-Xlog:safepoint*=info,gc*=info:file="${SAFEPOINT_LOG}":time,uptime,level,tags)
  echo "Safepoint/GC log: ${SAFEPOINT_LOG}"
fi

exec "${JAVA_BIN}" \
  "${JAVA_LOG_OPTS[@]}" \
  "${GC_JVM_OPTS[@]}" \
  -agentpath:"${REFCHAINS_SO}"=start,memory=64:l,generations=true,referencechains=${REFERENCECHAINS_OPTS},jfr,file="${JFR_OUT}" \
  -jar "${REFCHAINS_JAR}" "${JFR_OUT}" "${REFCHAINS_SO}" ${DURATION_SECONDS}
