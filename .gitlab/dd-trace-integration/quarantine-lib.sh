#!/bin/bash
# quarantine-lib.sh - shared quarantine logic for the dd-trace-integration pipeline.
#
# Sourced by post-pr-comment.sh (the gate) and validate-quarantine.sh (the CI
# validator) so the format and matching rules the two apply cannot drift.
#
# List format (.gitlab/dd-trace-integration/quarantine.txt), five fields
# separated by "|", whitespace around each field ignored; blank lines and
# lines starting with "#" are ignored:
#
#   <cell-glob>/<scenario> | PROF-<n> | added | review_by | reason
#
#   cell-glob   Bash glob against a known matrix cell <libc>-<arch>-<jvm>-jdk<version>.
#   scenario    Exactly "profiler-only" or "tracer-profiler" (the validation-log
#               filename prefixes post-pr-comment.sh reads).
#   ticket      PROF-<number>. Required - a quarantine without a ticket is just
#               a test nobody runs.
#   added       YYYY-MM-DD, the day the entry went in.
#   review_by   YYYY-MM-DD. CI fails on and after this date, so staying
#               quarantined is a decision somebody renews rather than the
#               default. 90 days is the usual span.
#   reason      Free text; last field, so it may contain "|".
#
# A quarantined scenario STILL RUNS and still reports; only the gating is
# suspended. The intended exit from the file is a fix and a deleted line.
#
# QUARANTINE_LIST overrides the list path (default: quarantine.txt next to
# this file); the gate's unit tests use it to inject temporary lists. An
# expired entry never matches (the failure gates again); the validator is what
# turns an expired entry into a red job.

# The matrix this pipeline is expected to cover. Declared once: it drives the
# completeness check in post-pr-comment.sh and the cell-glob validation here,
# so the two cannot drift.
QUARANTINE_PLATFORMS=(
  glibc-x64-hotspot glibc-x64-openj9 glibc-arm64-hotspot glibc-arm64-openj9
  musl-x64-hotspot musl-x64-openj9 musl-arm64-hotspot musl-arm64-openj9
)
QUARANTINE_JDKS=(8 11 17 21 25)

# Consumed by validate-quarantine.sh, which sources this lib.
# shellcheck disable=SC2034
QUARANTINE_SCENARIOS=("profiler-only" "tracer-profiler")

# 90 days is the usual span; padded by 30 so a proposal dated `added` at write
# time is not rejected before it is appended (same rule as quarantine.py's
# MAX_REVIEW_DAYS).
# Consumed by validate-quarantine.sh, which sources this lib.
# shellcheck disable=SC2034
QUARANTINE_MAX_REVIEW_DAYS=$((90 + 30))

# Parallel arrays describing each parsed entry.
QUARANTINE_IDS=()
QUARANTINE_CELL_GLOBS=()
QUARANTINE_SCENARIO_IDS=()
QUARANTINE_TICKETS=()
QUARANTINE_ADDED=()
QUARANTINE_REVIEW_BY=()
QUARANTINE_REASONS=()
QUARANTINE_LINES=()

quarantine_trim() {
  local s="$1"
  s="${s#"${s%%[![:space:]]*}"}"
  s="${s%"${s##*[![:space:]]}"}"
  printf '%s' "${s}"
}

quarantine_default_list() {
  local here
  here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  printf '%s' "${here}/quarantine.txt"
}

# Splits "<cell-glob>/<scenario>" into QUARANTINE_CELL_GLOB / QUARANTINE_SCENARIO_ID.
# Returns 1 when the id carries no "/" or the scenario part is empty. The cell
# glob may itself contain "/"-free globs only; a second "/" is a format error.
quarantine_split_id() {
  local id="$1"
  local glob="${id%/*}" scenario="${id##*/}"
  if [ "${glob}" = "${id}" ] || [ -z "${scenario}" ] || [ -z "${glob}" ]; then
    return 1
  fi
  case "${glob}" in */*) return 1 ;; esac
  QUARANTINE_CELL_GLOB="${glob}"
  QUARANTINE_SCENARIO_ID="${scenario}"
}

# Parses the list into the QUARANTINE_* arrays. Returns 0 even when the file
# is missing (matching tolerates absence); malformed lines are recorded in
# QUARANTINE_PARSE_ERRORS as "<line>:<message>" and skipped. Validation is the
# validator's job; the gate only refuses to excuse what it cannot parse.
quarantine_load() {
  local file="$1"
  QUARANTINE_IDS=()
  QUARANTINE_CELL_GLOBS=()
  QUARANTINE_SCENARIO_IDS=()
  QUARANTINE_TICKETS=()
  QUARANTINE_ADDED=()
  QUARANTINE_REVIEW_BY=()
  QUARANTINE_REASONS=()
  QUARANTINE_LINES=()
  QUARANTINE_PARSE_ERRORS=()
  [ -f "${file}" ] || return 0

  local line number id ticket added review_by reason
  number=0
  while IFS= read -r line || [ -n "${line}" ]; do
    number=$((number + 1))
    line="$(quarantine_trim "${line}")"
    case "${line}" in
      "" | "#"*) continue ;;
    esac
    local pipes="${line//[!|]/}"
    if [ "${#pipes}" -lt 4 ]; then
      QUARANTINE_PARSE_ERRORS+=("${number}:expected 5 '|'-separated fields, found $(( ${#pipes} + 1 ))")
      continue
    fi
    IFS='|' read -r id ticket added review_by reason <<< "${line}"
    id="$(quarantine_trim "${id}")"
    ticket="$(quarantine_trim "${ticket}")"
    added="$(quarantine_trim "${added}")"
    review_by="$(quarantine_trim "${review_by}")"
    reason="$(quarantine_trim "${reason}")"
    if ! quarantine_split_id "${id}"; then
      QUARANTINE_PARSE_ERRORS+=("${number}:id '${id}' is not <cell-glob>/<scenario>")
      continue
    fi
    QUARANTINE_IDS+=("${id}")
    QUARANTINE_CELL_GLOBS+=("${QUARANTINE_CELL_GLOB}")
    QUARANTINE_SCENARIO_IDS+=("${QUARANTINE_SCENARIO_ID}")
    QUARANTINE_TICKETS+=("${ticket}")
    QUARANTINE_ADDED+=("${added}")
    QUARANTINE_REVIEW_BY+=("${review_by}")
    QUARANTINE_REASONS+=("${reason}")
    QUARANTINE_LINES+=("${number}")
  done < "${file}"
  return 0
}

# YYYY-MM-DD is chronologically ordered as a string, so the comparison needs
# no date arithmetic and no GNU/BSD date divergence.
quarantine_date_lte() {
  [ "$1" \< "$2" ] || [ "$1" = "$2" ]
}

# Today in UTC as YYYY-MM-DD, without relying on GNU/BSD-specific date flags.
quarantine_today() {
  printf '%s' "$(TZ=UTC date '+%Y-%m-%d')"
}

# Is $1 a syntactically valid, real calendar date? Pure bash (incl. leap
# years) so the validator behaves identically on GNU and BSD hosts.
quarantine_date_valid() {
  local d="$1" year month day max_day
  case "${d}" in
    [0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]) ;;
    *) return 1 ;;
  esac
  year=$((10#${d%%-*}))
  month=$((10#${d:5:2}))
  day=$((10#${d:8:2}))
  [ "${month}" -ge 1 ] && [ "${month}" -le 12 ] || return 1
  [ "${day}" -ge 1 ] || return 1
  case "${month}" in
    2)
      max_day=28
      if [ $((year % 4)) -eq 0 ] && { [ $((year % 100)) -ne 0 ] || [ $((year % 400)) -eq 0 ]; }; then
        max_day=29
      fi
      ;;
    4 | 6 | 9 | 11) max_day=30 ;;
    *) max_day=31 ;;
  esac
  [ "${day}" -le "${max_day}" ]
}

# Enumerates the known matrix cells, one per line.
quarantine_known_cells() {
  local platform jdk
  for platform in "${QUARANTINE_PLATFORMS[@]}"; do
    for jdk in "${QUARANTINE_JDKS[@]}"; do
      printf '%s-jdk%s\n' "${platform}" "${jdk}"
    done
  done
}

# Days since 1970-01-01 for a YYYY-MM-DD date, pure bash (civil-days formula,
# leap-year aware) so the validator's 120-day review window behaves
# identically on GNU and BSD hosts; leap days count as cumulative L(yy) - L(1969).
quarantine_days_since_epoch() {
  local d="$1"
  local y=${d%%-*} m=$((10#${d:5:2})) day=$((10#${d:8:2}))
  local yy=$((y - 1))
  local -a cum=(0 31 59 90 120 151 181 212 243 273 304 334)
  local dm=${cum[m - 1]}
  if [ "${m}" -gt 2 ] && [ $((y % 4)) -eq 0 ] && { [ $((y % 100)) -ne 0 ] || [ $((y % 400)) -eq 0 ]; }; then
    dm=$((dm + 1))
  fi
  printf '%d\n' $(( (yy - 1969) * 365 + (yy / 4 - yy / 100 + yy / 400) - (1969 / 4 - 1969 / 100 + 1969 / 400) + dm + day - 1 ))
}

# Can one known cell match both globs? Two entries that share a reachable
# cell shadow each other, since quarantine_find only ever returns the first
# match.
globs_overlap() {
  local g1="$1" g2="$2" cell
  while IFS= read -r cell; do
    # shellcheck disable=SC2254  # the globs are intentionally unquoted
    case "${cell}" in
      ${g1})
        case "${cell}" in
          ${g2}) return 0 ;;
        esac
        ;;
    esac
  done < <(quarantine_known_cells)
  return 1
}

# Does the cell glob match at least one known matrix cell?
quarantine_glob_matches_known_cell() {
  local glob="$1" cell
  while IFS= read -r cell; do
    # shellcheck disable=SC2254  # the glob is intentionally unquoted
    case "${cell}" in
      ${glob}) return 0 ;;
    esac
  done < <(quarantine_known_cells)
  return 1
}

# Index of the first unexpired entry covering <cell> <scenario>, or 1 when
# none. An expired entry is treated as absent: the failure gates again, and
# the validator is what turns the stale entry into a red job. Unparsable
# entries never loaded, so they cannot excuse anything either.
quarantine_find() {
  local cell="$1" scenario="$2" today
  today="$(quarantine_today)"
  if [ "${#QUARANTINE_IDS[@]}" -eq 0 ]; then
    return 1
  fi
  local i
  for i in "${!QUARANTINE_IDS[@]}"; do
    [ "${QUARANTINE_SCENARIO_IDS[${i}]}" = "${scenario}" ] || continue
    # shellcheck disable=SC2254  # the glob is intentionally unquoted
    case "${cell}" in
      ${QUARANTINE_CELL_GLOBS[${i}]}) ;;
      *) continue ;;
    esac
    if quarantine_date_lte "${QUARANTINE_REVIEW_BY[${i}]}" "${today}"; then
      continue
    fi
    printf '%s\n' "${i}"
    return 0
  done
  return 1
}
