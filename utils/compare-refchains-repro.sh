#!/usr/bin/env bash
#
# Runs the reference-chains repro app (run-refchains-repro.sh) twice, back to
# back, over an identical bounded window - once with referencechains=true and
# once with referencechains=false - and diffs the two runs' throughput,
# safepoint/GC pause times, and heap growth, to answer:
#   - is it slower overall (throughput/round latency)?
#   - is it imposing lengthy STW safepoints (safepoint/GC log)?
#   - is it increasing memory usage significantly (heap growth, peak RSS)?
#
# Prints a markdown comparison table plus explicit answers to those three
# questions, and saves the same content as report.md in the run's temp
# working directory alongside the raw stdout/safepoint logs.
#
# Usage: compare-refchains-repro.sh [duration-seconds]
#
# Env vars: same REFCHAINS_SO/REFCHAINS_JAR/REFCHAINS_ARGS/REFCHAINS_JAVA_HOME/
# REFCHAINS_GC as run-refchains-repro.sh - passed through unchanged to both
# variants so the two runs stay comparable (REFCHAINS_ENABLED is set by this
# script itself, per run - don't set it yourself).

set -euo pipefail

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DURATION_SECONDS="${1:-120}"
WORKDIR="$(mktemp -d /tmp/refchains_compare.XXXXXX)"

JDK_DESC="${REFCHAINS_JAVA_HOME:-java on PATH}"
GC_DESC="${REFCHAINS_GC:-JVM ergonomic default}"

echo "Comparing referencechains=true vs. false over ${DURATION_SECONDS}s each"
echo "JDK: ${JDK_DESC}"
echo "GC: ${GC_DESC}"
echo "Working directory: ${WORKDIR}"

run_variant() {
  local label="$1" enabled="$2" jfr="${WORKDIR}/${1}.jfr"
  echo
  echo "=== running variant '${label}' (referencechains=${enabled}) ==="
  REFCHAINS_ENABLED="${enabled}" "${HERE}/run-refchains-repro.sh" "${jfr}" "${DURATION_SECONDS}" \
    > "${WORKDIR}/${label}.stdout.log" 2>&1 &
  local pid=$!

  # Peak RSS while the JVM runs - the -Xlog heap numbers only cover Java heap,
  # not native/off-heap growth (e.g. the tracker's own chain-storage arena).
  local peak_rss_kb=0
  while kill -0 "${pid}" 2>/dev/null; do
    local rss
    rss=$(ps -o rss= -p "${pid}" 2>/dev/null | tr -d ' ' || true)
    if [ -n "${rss}" ] && [ "${rss}" -gt "${peak_rss_kb}" ]; then
      peak_rss_kb="${rss}"
    fi
    sleep 1
  done
  wait "${pid}" || echo "WARN: variant '${label}' exited non-zero"
  echo "${peak_rss_kb}" > "${WORKDIR}/${label}.peak_rss_kb"
}

run_variant "on" "true"
run_variant "off" "false"

# Parses one variant's logs and echoes a single space-separated line of
# metrics (entriesPerSec avgRoundMs maxRoundMs heapGrowthMb stwCount stwTotalSec
# stwAvgSec stwMaxSec peakRssKb wallSeconds), so both variants can be captured
# into shell variables and diffed numerically rather than eyeballed as text.
parse_variant() {
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

  # Unified-logging safepoint format (JDK 17+, -Xlog:safepoint*): one line per
  # safepoint event, e.g. `[safepoint] Safepoint "G1CollectFull", Time since
  # last: ... ns, ..., Total: 11011880 ns`. "Total" is the full STW window for
  # that safepoint (sync + cleanup + vmop), which includes GC pauses since GC
  # itself runs at a safepoint. Sum + max (converted ns -> s) across the run
  # gives total/longest STW time.
  local stw_stats
  stw_stats=$(grep -oE 'Safepoint "[^"]+".*Total: [0-9]+ ns' "${safepoint_log}" 2>/dev/null \
    | grep -oE 'Total: [0-9]+ ns' \
    | grep -oE '[0-9]+' \
    | awk '{sec=$1/1e9; sum+=sec; if(sec>max) max=sec; n+=1} END {printf "%d %.4f %.4f %.4f", n, sum, (n>0?sum/n:0), max}')
  read -r stw_count stw_total stw_avg stw_max <<< "${stw_stats:-0 0 0 0}"

  echo "${entries_per_sec:-0} ${avg_round_ms:-0} ${max_round_ms:-0} ${heap_growth_mb:-0} ${stw_count} ${stw_total} ${stw_avg} ${stw_max} ${peak_rss_kb} ${wall_seconds:-0}"
}

read -r on_entries on_avg_round on_max_round on_heap_growth on_stw_count on_stw_total on_stw_avg on_stw_max on_rss on_wall \
  <<< "$(parse_variant "on")"
read -r off_entries off_avg_round off_max_round off_heap_growth off_stw_count off_stw_total off_stw_avg off_stw_max off_rss off_wall \
  <<< "$(parse_variant "off")"

# Percentage delta of "on" relative to "off": positive means "on" is worse
# (slower/longer-paused/more memory). Guards div-by-zero by falling back to 0.
pct_delta() {
  awk -v on="$1" -v off="$2" 'BEGIN {
    if (off == 0) { printf "n/a"; exit }
    printf "%+.1f%%", ((on - off) / off) * 100.0
  }'
}

throughput_delta_pct=$(pct_delta "${off_entries}" "${on_entries}")   # off/on: lower throughput with refchains on is the "cost"
avg_round_delta_pct=$(pct_delta "${on_avg_round}" "${off_avg_round}")
stw_total_delta_pct=$(pct_delta "${on_stw_total}" "${off_stw_total}")
stw_max_delta_pct=$(pct_delta "${on_stw_max}" "${off_stw_max}")
heap_growth_delta_mb=$((on_heap_growth - off_heap_growth))
rss_delta_kb=$((on_rss - off_rss))
rss_delta_pct=$(pct_delta "${on_rss}" "${off_rss}")

REPORT="${WORKDIR}/report.md"
{
  echo "# reference-chains overhead comparison"
  echo
  echo "referencechains=true vs. false, ${DURATION_SECONDS}s each. Raw logs: \`${WORKDIR}\`"
  echo
  echo "JDK: ${JDK_DESC} | GC: ${GC_DESC}"
  echo
  echo "| metric | on (refchains=true) | off (refchains=false) | delta (on vs. off) |"
  echo "|---|---|---|---|"
  echo "| entries/sec (throughput) | ${on_entries} | ${off_entries} | ${throughput_delta_pct} |"
  echo "| avg round latency (ms) | ${on_avg_round} | ${off_avg_round} | ${avg_round_delta_pct} |"
  echo "| max round latency (ms) | ${on_max_round} | ${off_max_round} | - |"
  echo "| safepoint count | ${on_stw_count} | ${off_stw_count} | - |"
  echo "| total STW stop time (s) | ${on_stw_total} | ${off_stw_total} | ${stw_total_delta_pct} |"
  echo "| longest single STW pause (s) | ${on_stw_max} | ${off_stw_max} | ${stw_max_delta_pct} |"
  echo "| heap growth (MB) | ${on_heap_growth} | ${off_heap_growth} | ${heap_growth_delta_mb} MB |"
  echo "| peak RSS (KB) | ${on_rss} | ${off_rss} | ${rss_delta_pct} (${rss_delta_kb} KB) |"
  echo
  echo "## Answers"
  echo
  echo "- **Slower overall?** throughput ${throughput_delta_pct}, avg round latency ${avg_round_delta_pct} with referencechains on."
  echo "- **Lengthy STW safepoints?** total stop time ${stw_total_delta_pct}, longest single pause ${on_stw_max}s (vs. ${off_stw_max}s off)."
  echo "- **Memory usage up significantly?** heap grew ${heap_growth_delta_mb} MB more, peak RSS ${rss_delta_pct} (${rss_delta_kb} KB) with referencechains on."
} > "${REPORT}"

echo
echo "===================== results ====================="
cat "${REPORT}"
echo
echo "Report saved to: ${REPORT}"
echo "Raw logs kept in: ${WORKDIR}"
