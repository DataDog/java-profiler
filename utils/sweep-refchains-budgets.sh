#!/usr/bin/env bash
#
# Sweeps referencechains=... budget-related sub-options (budget,
# firstpassbudget, pausetarget, painbudget) across a matrix of values and
# runs the repro app (run-refchains-repro.sh) once per combination, to
# answer: how does each budget knob trade off throughput/round-latency,
# STW pause time, and heap/RSS growth?
#
# This is the multi-point sibling of compare-refchains-repro.sh (which only
# ever does one on/off comparison at a single fixed set of sub-options).
# Reuses the same repro app and the same metric sources (stdout
# "[metrics]" line + -Xlog safepoint/GC log + peak RSS sampling), but drives
# N runs instead of 2 and writes them to a CSV plus a self-contained HTML
# report with charts (see refchains-report.py).
#
# Usage: sweep-refchains-budgets.sh [duration-seconds]
#
# Env vars:
#   REFCHAINS_SWEEP_PARAM   which sub-option to sweep: "budget" (default),
#                           "firstpassbudget", "pausetarget", or "painbudget".
#   REFCHAINS_SWEEP_VALUES  comma-separated values for that sub-option
#                           (default depends on REFCHAINS_SWEEP_PARAM - see
#                           below).
#   REFCHAINS_SO/REFCHAINS_JAR/REFCHAINS_JAVA_HOME/REFCHAINS_GC same as
#                           run-refchains-repro.sh - passed through unchanged
#                           to every run so they stay comparable.
#   REFCHAINS_ARGS          extra referencechains=... sub-options held fixed
#                           across the whole sweep (in addition to the
#                           defaults baked into run-refchains-repro.sh).

set -euo pipefail

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DURATION_SECONDS="${1:-120}"
SWEEP_PARAM="${REFCHAINS_SWEEP_PARAM:-budget}"

case "${SWEEP_PARAM}" in
  budget)          DEFAULT_VALUES="1000,4000,10000,40000,100000" ;;
  firstpassbudget) DEFAULT_VALUES="2000,10000,50000,200000" ;;
  pausetarget)     DEFAULT_VALUES="50,100,250,500,1000" ;;
  painbudget)      DEFAULT_VALUES="10,50,100,500,1000" ;;
  *)
    echo "FAIL: unknown REFCHAINS_SWEEP_PARAM=${SWEEP_PARAM} (expected: budget, firstpassbudget, pausetarget, painbudget)" >&2
    exit 1
    ;;
esac
IFS=',' read -r -a SWEEP_VALUES <<< "${REFCHAINS_SWEEP_VALUES:-${DEFAULT_VALUES}}"

WORKDIR="$(mktemp -d /tmp/refchains_sweep.XXXXXX)"
CSV="${WORKDIR}/sweep.csv"

JDK_DESC="${REFCHAINS_JAVA_HOME:-java on PATH}"
GC_DESC="${REFCHAINS_GC:-JVM ergonomic default}"

echo "Sweeping referencechains ${SWEEP_PARAM} over: ${SWEEP_VALUES[*]}"
echo "JDK: ${JDK_DESC}"
echo "GC: ${GC_DESC}"
echo "Duration per point: ${DURATION_SECONDS}s"
echo "Working directory: ${WORKDIR}"

echo "param_value,entries_per_sec,avg_round_ms,max_round_ms,heap_growth_mb,stw_count,stw_total_s,stw_avg_s,stw_max_s,peak_rss_kb,wall_seconds" > "${CSV}"

# Parses one run's logs into a single space-separated metrics line - same
# fields/sources as compare-refchains-repro.sh's parse_variant, factored out
# here since this script iterates N runs instead of a fixed on/off pair.
parse_run() {
  local label="$1"
  local stdout="${WORKDIR}/${label}.stdout.log"
  local safepoint_log="${WORKDIR}/${label}.jfr.safepoint.log"
  local peak_rss_kb
  peak_rss_kb=$(cat "${WORKDIR}/${label}.peak_rss_kb" 2>/dev/null || echo 0)

  local metrics_line
  metrics_line=$(grep '^\[metrics\]' "${stdout}" || true)
  local wall_seconds entries_per_sec avg_round_ms max_round_ms heap_growth_mb
  wall_seconds=$(echo "${metrics_line}" | grep -oE 'wallSeconds=[0-9.]+' | cut -d= -f2)
  entries_per_sec=$(echo "${metrics_line}" | grep -oE 'entriesPerSec=[0-9.]+' | cut -d= -f2)
  avg_round_ms=$(echo "${metrics_line}" | grep -oE 'avgRoundMs=[0-9.]+' | cut -d= -f2)
  max_round_ms=$(echo "${metrics_line}" | grep -oE 'maxRoundMs=[0-9.]+' | cut -d= -f2)
  heap_growth_mb=$(echo "${metrics_line}" | grep -oE 'heapGrowthMb=-?[0-9]+' | cut -d= -f2)

  # Two -Xlog safepoint line shapes across JDK versions:
  #  - JDK 17+: `Safepoint "name", ... Total: N ns` (one line, everything on it)
  #  - JDK <=16 (e.g. 11): `Total time for which application threads were
  #    stopped: N seconds, Stopping threads took: ...` (separate summary line,
  #    no per-name "Safepoint" prefix, value already in seconds not ns)
  # Try the ns-based JDK17+ shape first; fall back to the seconds-based one.
  local stw_stats
  stw_stats=$(grep -oE 'Safepoint "[^"]+".*Total: [0-9]+ ns' "${safepoint_log}" 2>/dev/null \
    | grep -oE 'Total: [0-9]+ ns' \
    | grep -oE '[0-9]+' \
    | awk '{sec=$1/1e9; sum+=sec; if(sec>max) max=sec; n+=1} END {if(n>0) printf "%d %.4f %.4f %.4f", n, sum, sum/n, max}')
  if [ -z "${stw_stats}" ]; then
    stw_stats=$(grep -oE 'Total time for which application threads were stopped: [0-9.]+ seconds' "${safepoint_log}" 2>/dev/null \
      | grep -oE '[0-9.]+' \
      | awk '{sec=$1; sum+=sec; if(sec>max) max=sec; n+=1} END {if(n>0) printf "%d %.4f %.4f %.4f", n, sum, sum/n, max}')
  fi
  read -r stw_count stw_total stw_avg stw_max <<< "${stw_stats:-0 0 0 0}"

  echo "${entries_per_sec:-0} ${avg_round_ms:-0} ${max_round_ms:-0} ${heap_growth_mb:-0} ${stw_count} ${stw_total} ${stw_avg} ${stw_max} ${peak_rss_kb} ${wall_seconds:-0}"
}

for value in "${SWEEP_VALUES[@]}"; do
  label="${SWEEP_PARAM}_${value}"
  jfr="${WORKDIR}/${label}.jfr"
  echo
  echo "=== running ${SWEEP_PARAM}=${value} ==="

  REFCHAINS_ENABLED="true" REFCHAINS_ARGS="${SWEEP_PARAM}=${value}${REFCHAINS_ARGS:+:${REFCHAINS_ARGS}}" \
    "${HERE}/run-refchains-repro.sh" "${jfr}" "${DURATION_SECONDS}" \
    > "${WORKDIR}/${label}.stdout.log" 2>&1 &
  pid=$!

  peak_rss_kb=0
  while kill -0 "${pid}" 2>/dev/null; do
    rss=$(ps -o rss= -p "${pid}" 2>/dev/null | tr -d ' ' || true)
    if [ -n "${rss}" ] && [ "${rss}" -gt "${peak_rss_kb}" ]; then
      peak_rss_kb="${rss}"
    fi
    sleep 1
  done
  wait "${pid}" || echo "WARN: run ${SWEEP_PARAM}=${value} exited non-zero"
  echo "${peak_rss_kb}" > "${WORKDIR}/${label}.peak_rss_kb"

  read -r entries avg_round max_round heap_growth stw_count stw_total stw_avg stw_max rss wall \
    <<< "$(parse_run "${label}")"
  echo "${value},${entries},${avg_round},${max_round},${heap_growth},${stw_count},${stw_total},${stw_avg},${stw_max},${rss},${wall}" >> "${CSV}"
done

echo
echo "CSV written to: ${CSV}"

REPORT_HTML="${WORKDIR}/report.html"
python3 "${HERE}/refchains-report.py" "${CSV}" "${REPORT_HTML}" \
  --param "${SWEEP_PARAM}" --jdk "${JDK_DESC}" --gc "${GC_DESC}" --duration "${DURATION_SECONDS}"

echo "HTML report written to: ${REPORT_HTML}"
echo "Raw logs kept in: ${WORKDIR}"
