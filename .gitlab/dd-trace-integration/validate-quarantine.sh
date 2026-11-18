#!/bin/bash
# validate-quarantine.sh - validate the dd-trace-integration quarantine list.
#
# Enforces what the gate (post-pr-comment.sh via quarantine-lib.sh) relies on:
# format, ticket reference, real calendar dates, an unexpired review_by, a
# known scenario token, and cell globs that match the known matrix. Fails the
# job on any problem - a stale or malformed entry must turn CI red, not
# silently stop gating. QUARANTINE_LIST overrides the list path (the unit
# tests use this).
#
# Errors are emitted as GitHub workflow commands (::error file=,line=) so the
# validate-quarantine job annotates the offending lines in the PR, matching
# .github/scripts/quarantine.py's format.

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Path is computed at runtime, so shellcheck cannot follow it; the lib's
# variables and functions are what this script consumes.
# shellcheck disable=SC1091
. "${HERE}/quarantine-lib.sh"

LIST="${QUARANTINE_LIST:-$(quarantine_default_list)}"
PROBLEMS=0

error() {
  local line="$1" message="$2"
  printf '::error file=%s,line=%s::%s\n' "${LIST}" "${line}" "${message}" >&2
  PROBLEMS=$((PROBLEMS + 1))
}

# parse() tolerates a missing file so that matching still works before the
# first entry lands. Validation must not: "0 quarantined scenario(s), all
# valid" for a list that has been renamed or deleted would report success at
# the exact moment gating silently stopped applying everywhere.
if [ ! -f "${LIST}" ]; then
  # No line number to anchor: the file itself is missing (quarantine.py uses
  # the same bare form — GitHub drops annotations whose line is 0).
  printf '::error::quarantine list %s does not exist\n' "'${LIST}'" >&2
  exit 1
fi

quarantine_load "${LIST}"
if [ "${#QUARANTINE_PARSE_ERRORS[@]}" -gt 0 ]; then
  for e in "${QUARANTINE_PARSE_ERRORS[@]}"; do
    error "${e%%:*}" "${e#*:}"
  done
fi

TICKET_RE='^PROF-[0-9]+$'
TODAY="$(quarantine_today)"

# Ids are exact per (scenario, cell-glob); two entries whose globs can match
# the same known cell for the same scenario shadow each other - quarantine_find
# only ever returns the first match, so the second entry's ticket and expiry
# would silently never take effect.
# Id -> first line, kept as parallel indexed arrays: macOS /bin/bash is 3.2,
# which has no associative arrays (no 'declare -A').
SEEN_ID_KEYS=()
SEEN_ID_LINES=()

if [ "${#QUARANTINE_IDS[@]}" -gt 0 ]; then
for i in "${!QUARANTINE_IDS[@]}"; do
  line="${QUARANTINE_LINES[${i}]}"
  id="${QUARANTINE_IDS[${i}]}"
  glob="${QUARANTINE_CELL_GLOBS[${i}]}"
  scenario="${QUARANTINE_SCENARIO_IDS[${i}]}"
  ticket="${QUARANTINE_TICKETS[${i}]}"
  added="${QUARANTINE_ADDED[${i}]}"
  review_by="${QUARANTINE_REVIEW_BY[${i}]}"

  [ -n "${ticket}" ] || error "${line}" "field 'ticket' is empty - no ticket, no quarantine"
  if [ -n "${ticket}" ] && ! [[ "${ticket}" =~ ${TICKET_RE} ]]; then
    error "${line}" "ticket '${ticket}' is not a PROF-<number>"
  fi

  [ -n "${added}" ] || error "${line}" "field 'added' is empty"
  [ -n "${review_by}" ] || error "${line}" "field 'review_by' is empty - an expiry that cannot be read has passed"
  [ -n "${QUARANTINE_REASONS[${i}]}" ] || error "${line}" "field 'reason' is empty"

  if [ -n "${added}" ] && ! quarantine_date_valid "${added}"; then
    error "${line}" "added '${added}' is not a real calendar date (YYYY-MM-DD)"
  fi

  if [ -n "${review_by}" ]; then
    if ! quarantine_date_valid "${review_by}"; then
      error "${line}" "review_by '${review_by}' is not a real calendar date (YYYY-MM-DD)"
    elif quarantine_date_lte "${review_by}" "${TODAY}"; then
      error "${line}" "'${id}' has been quarantined since ${added} and its review was due ${review_by}. Fix the scenario and delete this line, or renew review_by with a note on ${ticket:-the ticket}."
    else
      # A review_by further out than QUARANTINE_MAX_REVIEW_DAYS is not a review
      # date, it is a way to write "never" without saying so. Compare via the
      # pure-bash day serials (no GNU/BSD date divergence).
      due_serial=$(quarantine_days_since_epoch "${review_by}")
      today_serial=$(quarantine_days_since_epoch "${TODAY}")
      if [ $((due_serial - today_serial)) -gt "${QUARANTINE_MAX_REVIEW_DAYS}" ]; then
        error "${line}" "review_by '${review_by}' is more than ${QUARANTINE_MAX_REVIEW_DAYS} days out; that is not a review date, it defeats the point of an expiring quarantine"
      fi
    fi
  fi

  known_scenario=0
  for s in "${QUARANTINE_SCENARIOS[@]}"; do
    [ "${scenario}" = "${s}" ] && known_scenario=1
  done
  if [ "${known_scenario}" -eq 0 ]; then
    error "${line}" "scenario '${scenario}' is not one of ${QUARANTINE_SCENARIOS[*]}; entries are written <cell-glob>/<scenario> and this one would never match"
  fi

  if ! quarantine_glob_matches_known_cell "${glob}"; then
    error "${line}" "cell glob '${glob}' matches no known matrix cell (<libc>-<arch>-<jvm>-jdk<version>, e.g. glibc-x64-openj9-jdk25); it would quarantine nothing"
  fi

  seen_line=""
  if [ "${#SEEN_ID_KEYS[@]}" -gt 0 ]; then
    for k in "${!SEEN_ID_KEYS[@]}"; do
      if [ "${SEEN_ID_KEYS[${k}]}" = "${id}" ]; then
        seen_line="${SEEN_ID_LINES[${k}]}"
        break
      fi
    done
  fi
  if [ -n "${seen_line}" ]; then
    error "${line}" "'${id}' is already quarantined on line ${seen_line}; only the first entry would ever take effect"
  else
    SEEN_ID_KEYS+=("${id}")
    SEEN_ID_LINES+=("${line}")
  fi
done
fi

# Overlap across different globs for the same scenario: two entries whose
# cell globs both match some common known cell shadow each other the same way.
if [ "${#QUARANTINE_IDS[@]}" -gt 0 ]; then
for i in "${!QUARANTINE_IDS[@]}"; do
  for j in "${!QUARANTINE_IDS[@]}"; do
    [ "${i}" -lt "${j}" ] || continue
    [ "${QUARANTINE_SCENARIO_IDS[${i}]}" = "${QUARANTINE_SCENARIO_IDS[${j}]}" ] || continue
    # Identical ids are already reported by the duplicate check above.
    if [ "${QUARANTINE_IDS[${i}]}" = "${QUARANTINE_IDS[${j}]}" ]; then
      continue
    fi
    if globs_overlap "${QUARANTINE_CELL_GLOBS[${i}]}" "${QUARANTINE_CELL_GLOBS[${j}]}"; then
      error "${QUARANTINE_LINES[${j}]}" "'${QUARANTINE_IDS[${j}]}' overlaps '${QUARANTINE_IDS[${i}]}' (line ${QUARANTINE_LINES[${i}]}) on at least one known cell; only the first entry would ever take effect"
    fi
  done
done
fi

if [ "${PROBLEMS}" -gt 0 ]; then
  printf '\n%s problem(s) in %s\n' "${PROBLEMS}" "${LIST}" >&2
  exit 1
fi

printf '%s: %d quarantined scenario(s), all valid\n' "${LIST}" "${#QUARANTINE_IDS[@]}"
