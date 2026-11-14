#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc
#
# One-factor-at-a-time (OFAT) sweep across all four referencechains budget
# knobs (budget, firstpassbudget, pausetarget, painbudget): for each knob,
# sweeps its own value list while holding the other three at
# run-refchains-repro.sh's baked baseline (BAKED_REFCHAINS_OPTS there:
# budget=10000, pausetarget=500, painbudget=100 - NOT the tracker's built-in
# arguments.h defaults; firstpassbudget is not baked, so it stays auto-scaled
# from budget - see referenceChains.h's AUTO_FIRST_PASS_BUDGET_*). The swept
# knob replaces its baked value (run-refchains-repro.sh drops a baked key that
# REFCHAINS_ARGS also sets), so each point runs exactly one occurrence of it.
# A full cartesian product across all four knobs is combinatorially far more
# runs for little extra insight over OFAT at this stage, so this is
# deliberately OFAT, not a grid search.
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
#                           across every run (in addition to the baseline
#                           baked into run-refchains-repro.sh). A key here
#                           that is also the knob being swept is dropped (with
#                           a WARN) for that knob's runs, so the swept value is
#                           never shadowed by, or duplicated with, a fixed one.

set -euo pipefail

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DURATION_SECONDS="${1:-60}"

# Caller's fixed sub-options, captured once: REFCHAINS_ARGS itself is rebuilt
# per run below (swept knob + these).
FIXED_REFCHAINS_ARGS="${REFCHAINS_ARGS:-}"

# Prints FIXED_REFCHAINS_ARGS minus any "<knob>=..." entry (key matched
# case-insensitively, like arguments.cpp), warning on stderr for each one
# dropped - stdout is the result, captured by the caller.
fixed_args_without() {
  local drop="$1" out="" kv key
  local parts=()
  if [ -n "${FIXED_REFCHAINS_ARGS}" ]; then
    IFS=':' read -r -a parts <<< "${FIXED_REFCHAINS_ARGS}"
  fi
  for kv in ${parts[@]+"${parts[@]}"}; do
    key=$(printf '%s' "${kv%%=*}" | tr '[:upper:]' '[:lower:]')
    if [ "${key}" = "${drop}" ]; then
      echo "WARN: ignoring REFCHAINS_ARGS entry '${kv}' while sweeping ${drop}" >&2
      continue
    fi
    out="${out:+${out}:}${kv}"
  done
  printf '%s' "${out}"
}

KNOBS=(budget firstpassbudget pausetarget painbudget)

# Per-knob sweep value lists (env-overridable). A function + case instead of an
# associative array: macOS ships /bin/bash 3.2, which has no `declare -A`, and
# run-refchains-repro.sh (which this script drives) deliberately supports it -
# same ${var,,}-free, ${arr[@]+...}-guarded discipline as the sibling scripts.
knob_values() {
  case "$1" in
    budget)          printf '%s' "${REFCHAINS_SWEEP_BUDGET_VALUES:-1000,4000,10000,40000,100000}" ;;
    firstpassbudget) printf '%s' "${REFCHAINS_SWEEP_FIRSTPASSBUDGET_VALUES:-2000,10000,50000,200000}" ;;
    pausetarget)     printf '%s' "${REFCHAINS_SWEEP_PAUSETARGET_VALUES:-50,100,250,500,1000}" ;;
    painbudget)      printf '%s' "${REFCHAINS_SWEEP_PAINBUDGET_VALUES:-10,50,100,500,1000}" ;;
    *) return 1 ;;
  esac
}

WORKDIR="$(mktemp -d /tmp/refchains_sweep_all.XXXXXX)"
CSV="${WORKDIR}/sweep.csv"

JDK_DESC="${REFCHAINS_JAVA_HOME:-java on PATH}"
GC_DESC="${REFCHAINS_GC:-JVM ergonomic default}"

TOTAL_RUNS=0
for k in "${KNOBS[@]}"; do
  IFS=',' read -r -a vals <<< "$(knob_values "${k}")"
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
  # Every extraction below tolerates "no match" (`|| true`): under set -euo
  # pipefail one crashed/truncated run would otherwise abort the whole OFAT
  # sweep instead of recording that point as 0 and moving on.
  local wall_seconds entries_per_sec avg_round_ms max_round_ms heap_growth_mb
  wall_seconds=$(echo "${metrics_line}" | grep -oE 'wallSeconds=[0-9.]+' | cut -d= -f2 || true)
  entries_per_sec=$(echo "${metrics_line}" | grep -oE 'entriesPerSec=[0-9.]+' | cut -d= -f2 || true)
  avg_round_ms=$(echo "${metrics_line}" | grep -oE 'avgRoundMs=[0-9.]+' | cut -d= -f2 || true)
  max_round_ms=$(echo "${metrics_line}" | grep -oE 'maxRoundMs=[0-9.]+' | cut -d= -f2 || true)
  heap_growth_mb=$(echo "${metrics_line}" | grep -oE 'heapGrowthMb=-?[0-9]+' | cut -d= -f2 || true)

  local stw_stats
  stw_stats=$(grep -oE 'Safepoint "[^"]+".*Total: [0-9]+ ns' "${safepoint_log}" 2>/dev/null \
    | grep -oE 'Total: [0-9]+ ns' \
    | grep -oE '[0-9]+' \
    | awk '{sec=$1/1e9; sum+=sec; if(sec>max) max=sec; n+=1} END {if(n>0) printf "%d %.4f %.4f %.4f", n, sum, sum/n, max}' \
    || true)
  if [ -z "${stw_stats}" ]; then
    # JDK <=16 shape. One sed capture of exactly the "stopped: N seconds"
    # value per line (only matching lines are printed), rather than every
    # numeric token on the line.
    stw_stats=$(sed -nE 's/.*Total time for which application threads were stopped: ([0-9.]+) seconds.*/\1/p' "${safepoint_log}" 2>/dev/null \
      | awk '{sec=$1; sum+=sec; if(sec>max) max=sec; n+=1} END {if(n>0) printf "%d %.4f %.4f %.4f", n, sum, sum/n, max}' \
      || true)
  fi
  read -r stw_count stw_total stw_avg stw_max <<< "${stw_stats:-0 0 0 0}"

  # jfr print/summary require a ".jfr" extension - the repro app's periodic
  # dump targets ("<jfr>.snapshot" and "<jfr>.snapshot.<round>", see
  # ReferenceChainLeakDemo's own header comment on SNAPSHOT_SUFFIX) don't have
  # one, so copy each under a distinct .jfr name before handing them to
  # refchains-jfr-metrics.py.
  #
  # Every dump() finishes one chunk, so each snapshot file holds exactly one
  # chunk whose own start is the previous dump - and the tracker re-stamps every
  # cached chain into every dump. Per-file "chain time - chunk start" therefore
  # collapses to ~one dump interval. Instead, all of this run's snapshots go to
  # ONE refchains-jfr-metrics.py call, which sums the counts and measures
  # time-to-first-chain against the ORIGINAL recording start
  # (jdk.ActiveRecording). Resolution is one dump interval.
  local snapshot_base="${WORKDIR}/${label}.jfr.snapshot"
  local chain_count abandoned_count time_to_first_chain_s
  local jfr_stats="0 0 -1" snap n_snaps=0
  local tmp_jfrs=()
  for snap in "${snapshot_base}" "${snapshot_base}".*; do
    [ -f "${snap}" ] || continue
    n_snaps=$((n_snaps + 1))
    tmp_jfrs+=("${WORKDIR}/${label}.metrics.${n_snaps}.jfr")
    cp "${snap}" "${WORKDIR}/${label}.metrics.${n_snaps}.jfr"
  done
  if [ "${n_snaps}" -gt 0 ]; then
    # stderr is NOT discarded: a jfr/REFCHAINS_JAVA_HOME problem must be visible
    # rather than silently recorded as "no chains" (parse_run runs under $(...),
    # which captures stdout only, so the 13-field echo below stays clean).
    jfr_stats=$(python3 "${HERE}/refchains-jfr-metrics.py" "${tmp_jfrs[@]}") \
      || { echo "WARN: refchains-jfr-metrics failed for '${label}'; recording 0 0 -1" >&2; jfr_stats="0 0 -1"; }
    rm -f "${tmp_jfrs[@]}"
  fi
  read -r chain_count abandoned_count time_to_first_chain_s <<< "${jfr_stats:-0 0 -1}"

  echo "${entries_per_sec:-0} ${avg_round_ms:-0} ${max_round_ms:-0} ${heap_growth_mb:-0} ${stw_count} ${stw_total} ${stw_avg} ${stw_max} ${peak_rss_kb} ${wall_seconds:-0} ${chain_count} ${abandoned_count} ${time_to_first_chain_s}"
}

run_idx=0
for knob in "${KNOBS[@]}"; do
  IFS=',' read -r -a vals <<< "$(knob_values "${knob}")"
  for value in "${vals[@]}"; do
    run_idx=$((run_idx + 1))
    label="${knob}_${value}"
    jfr="${WORKDIR}/${label}.jfr"
    echo
    echo "=== [${run_idx}/${TOTAL_RUNS}] ${knob}=${value} ==="

    fixed_args="$(fixed_args_without "${knob}")"
    REFCHAINS_ENABLED="true" REFCHAINS_ARGS="${knob}=${value}${fixed_args:+:${fixed_args}}" \
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
