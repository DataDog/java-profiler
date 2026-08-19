#!/usr/bin/env bash
#
# One-factor-at-a-time (OFAT) sweep across all four referencechains budget
# knobs (budget, firstpassbudget, pausetarget, painbudget): for each knob,
# sweeps its own value list while holding the other three at their built-in
# defaults (i.e. omitted from the sub-option string, letting the tracker's
# own defaults/auto-scaling apply - see referenceChains.h). A full cartesian
# product across all four knobs is combinatorially far more runs for little
# extra insight over OFAT at this stage, so this is deliberately OFAT, not a
# grid search.
#
# Writes one combined CSV (knob,param_value,<metrics...>) covering all four
# sweeps, then renders it via refchains-report-multi.py into a single
# Chart.js-based HTML report with one tab per knob.
#
# Usage: sweep-refchains-all.sh [duration-seconds]
#
# Env vars:
#   REFCHAINS_SO/REFCHAINS_JAR/REFCHAINS_JAVA_HOME/REFCHAINS_GC   same as
#                           run-refchains-repro.sh - passed through unchanged
#                           to every run so all sweeps stay comparable.
#   REFCHAINS_ARGS          extra referencechains=... sub-options held fixed
#                           across every run (in addition to the defaults
#                           baked into run-refchains-repro.sh).

set -euo pipefail

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DURATION_SECONDS="${1:-60}"

KNOBS=(budget firstpassbudget pausetarget painbudget)
declare -A KNOB_VALUES=(
  [budget]="${REFCHAINS_SWEEP_BUDGET_VALUES:-1000,4000,10000,40000,100000}"
  [firstpassbudget]="${REFCHAINS_SWEEP_FIRSTPASSBUDGET_VALUES:-2000,10000,50000,200000}"
  [pausetarget]="${REFCHAINS_SWEEP_PAUSETARGET_VALUES:-50,100,250,500,1000}"
  [painbudget]="${REFCHAINS_SWEEP_PAINBUDGET_VALUES:-10,50,100,500,1000}"
)

WORKDIR="$(mktemp -d /tmp/refchains_sweep_all.XXXXXX)"
CSV="${WORKDIR}/sweep.csv"

JDK_DESC="${REFCHAINS_JAVA_HOME:-java on PATH}"
GC_DESC="${REFCHAINS_GC:-JVM ergonomic default}"

TOTAL_RUNS=0
for k in "${KNOBS[@]}"; do
  IFS=',' read -r -a vals <<< "${KNOB_VALUES[${k}]}"
  TOTAL_RUNS=$((TOTAL_RUNS + ${#vals[@]}))
done

echo "OFAT sweep across knobs: ${KNOBS[*]}"
echo "JDK: ${JDK_DESC}"
echo "GC: ${GC_DESC}"
echo "Duration per point: ${DURATION_SECONDS}s, total runs: ${TOTAL_RUNS} (~$((TOTAL_RUNS * DURATION_SECONDS / 60)) min)"
echo "Working directory: ${WORKDIR}"

echo "knob,param_value,entries_per_sec,avg_round_ms,max_round_ms,heap_growth_mb,stw_count,stw_total_s,stw_avg_s,stw_max_s,peak_rss_kb,wall_seconds,chain_count,abandoned_count,time_to_first_chain_s" > "${CSV}"

# Same metrics extraction as sweep-refchains-budgets.sh/compare-refchains-repro.sh -
# kept in sync across all three since they read the same stdout/-Xlog sources.
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

  # jfr print/summary require a ".jfr" extension - the repro app's periodic
  # dump target ("<jfr>.snapshot", see ReferenceChainLeakDemo's own header
  # comment on SNAPSHOT_SUFFIX) doesn't have one, so copy it under a .jfr
  # name before handing it to refchains-jfr-metrics.py.
  local snapshot="${WORKDIR}/${label}.jfr.snapshot"
  local chain_count=0 abandoned_count=0 time_to_first_chain_s=-1
  if [ -f "${snapshot}" ]; then
    local tmp_jfr="${WORKDIR}/${label}.metrics.jfr"
    cp "${snapshot}" "${tmp_jfr}"
    local chain_stats
    chain_stats=$(python3 "${HERE}/refchains-jfr-metrics.py" "${tmp_jfr}" 2>/dev/null || echo "0 0 -1")
    read -r chain_count abandoned_count time_to_first_chain_s <<< "${chain_stats}"
    rm -f "${tmp_jfr}"
  fi

  echo "${entries_per_sec:-0} ${avg_round_ms:-0} ${max_round_ms:-0} ${heap_growth_mb:-0} ${stw_count} ${stw_total} ${stw_avg} ${stw_max} ${peak_rss_kb} ${wall_seconds:-0} ${chain_count} ${abandoned_count} ${time_to_first_chain_s}"
}

run_idx=0
for knob in "${KNOBS[@]}"; do
  IFS=',' read -r -a vals <<< "${KNOB_VALUES[${knob}]}"
  for value in "${vals[@]}"; do
    run_idx=$((run_idx + 1))
    label="${knob}_${value}"
    jfr="${WORKDIR}/${label}.jfr"
    echo
    echo "=== [${run_idx}/${TOTAL_RUNS}] ${knob}=${value} ==="

    REFCHAINS_ENABLED="true" REFCHAINS_ARGS="${knob}=${value}${REFCHAINS_ARGS:+:${REFCHAINS_ARGS}}" \
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
    wait "${pid}" || echo "WARN: run ${knob}=${value} exited non-zero"
    echo "${peak_rss_kb}" > "${WORKDIR}/${label}.peak_rss_kb"

    read -r entries avg_round max_round heap_growth stw_count stw_total stw_avg stw_max rss wall \
      chain_count abandoned_count time_to_first_chain \
      <<< "$(parse_run "${label}")"
    echo "${knob},${value},${entries},${avg_round},${max_round},${heap_growth},${stw_count},${stw_total},${stw_avg},${stw_max},${rss},${wall},${chain_count},${abandoned_count},${time_to_first_chain}" >> "${CSV}"
  done
done

echo
echo "CSV written to: ${CSV}"

REPORT_HTML="${WORKDIR}/report.html"
python3 "${HERE}/refchains-report-multi.py" "${CSV}" "${REPORT_HTML}" \
  --jdk "${JDK_DESC}" --gc "${GC_DESC}" --duration "${DURATION_SECONDS}"

echo "HTML report written to: ${REPORT_HTML}"
echo "Raw logs kept in: ${WORKDIR}"
