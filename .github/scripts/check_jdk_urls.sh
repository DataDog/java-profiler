#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc.

# Checks the JDK download URLs pinned in cache_java.yml, and whether IBM lists
# an SDK 8 release newer than the pinned one. Run by jdk-url-check.yml.
#
# Usage:
#   check_jdk_urls.sh check --out <dir> [--workflow <path>]
#   check_jdk_urls.sh alert --out <dir> [--force-issue] [--dry-run]
#
# check: probes every env key JAVA_*_URL and classifies it OK (2xx), STALE
#   (404/410) or INCONCLUSIVE (anything else; warning only). Probes share one
#   deadline (PROBE_DEADLINE_SECONDS, default 1200): past it, unprobed pins
#   are INCONCLUSIVE without a probe and the IBM newer-release check is
#   skipped. Writes
#   results.tsv, table.md and ibm.txt to <dir> and appends the table to
#   $GITHUB_STEP_SUMMARY. Exits 1 when a URL is STALE, 2 on usage or parse error.
# alert: reads <dir> and, per STALE URL, files a PROF Jira ticket; per OK URL,
#   resolves a ticket an earlier run filed; for a verified newer IBM release,
#   files a ticket. Slack is told when a ticket is new, could not be filed, or
#   a pin recovers.
#   Resolves newer-release tickets once the pin reaches their version.
#   --force-issue reports JAVA_8_IBM_URL as stale to test this path;
#   --dry-run prints the actions instead of calling Jira or Slack.
#   Jira and Slack failures are warnings in the job log; they do not fail it.
#
# Environment (alert): SLACK_WEBHOOK, ATLASSIAN_* (see file-jira-issue.sh),
# RUN_URL (defaults to the GitHub Actions run URL).

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT_DIR=$(cd "$SCRIPT_DIR/../.." && pwd)
IBM_JAVA_INDEX_URL="https://public.dhe.ibm.com/ibmdl/export/pub/systems/cloud/runtimes/java/"
IBM_URL_VAR="JAVA_8_IBM_URL"
# retry 1 / max-time 30 / retry-max-time 30 bound each transfer and the total
# retry window, so a server-sent Retry-After cannot stall one probe past the
# deadline; the daily cadence re-checks INCONCLUSIVE pins.
CURL_OPTS=(-sS -L --retry 1 --retry-all-errors --connect-timeout 15 --max-time 30 --retry-max-time 30)
# Probes share one budget: past it, unprobed pins are INCONCLUSIVE instead of
# the job being killed at timeout-minutes before any alert. Overridable for
# the hermetic tests.
PROBE_DEADLINE_SECONDS="${PROBE_DEADLINE_SECONDS:-1200}"

# True once the shared probe budget is exhausted; $1 is the budget's origin
# (SECONDS at the start of the check).
deadline_expired() {
  (( SECONDS - $1 >= PROBE_DEADLINE_SECONDS ))
}
JIRA_COMPONENT="library-java"
JIRA_LABEL="ci"

usage() {
  echo "Usage: $0 check --out <dir> [--workflow <path>]" >&2
  echo "       $0 alert --out <dir> [--force-issue] [--dry-run]" >&2
  exit 2
}

# Prints "VAR URL" for every env key matching ^JAVA_.*_URL$. Commented-out
# pins are YAML comments, so yq never sees them.
extract_urls() {
  local workflow=$1
  yq -r '.env // {} | to_entries | .[] | select(.key | test("^JAVA_.*_URL$")) | .key + " " + .value' "$workflow"
}

classify() {
  case "$1" in
    2[0-9][0-9]) echo OK ;;
    404|410) echo STALE ;;
    *) echo INCONCLUSIVE ;;
  esac
}

# Prints "<http_code> <final_url>"; code 000 means no HTTP response, and
# curl's last error line goes to stderr for the job log.
probe_once() {
  local out err
  err=$(mktemp)
  out=$(curl "${CURL_OPTS[@]}" -o /dev/null -w '%{http_code} %{url_effective}' "$@" 2>"$err" </dev/null) || true
  if [ -z "$out" ]; then
    out="000 ${*: -1}"
  fi
  if [ "${out%% *}" = 000 ] && [ -s "$err" ]; then
    tail -n 1 "$err" >&2
  fi
  rm -f "$err"
  echo "$out"
}

# HEAD first. Some servers reject or mishandle HEAD on downloads, so a
# rejection (403/405/501) or a stale answer (404/410) is confirmed with a
# 1-byte range GET before it is reported.
probe_url() {
  local url=$1 out
  out=$(probe_once -I "$url")
  case "${out%% *}" in
    403|404|405|410|501) out=$(probe_once -r 0-0 "$url") ;;
  esac
  echo "$out"
}

# The release directory, e.g. 8.0.8.75 in .../java/8.0.8.75/linux/...
pinned_ibm_version() {
  sed -nE 's#.*/java/(8\.0\.[0-9]+\.[0-9]+)/.*#\1#p' <<<"$1"
}

# Directory listing HTML on stdin; prints each 8.0.x.y release once, ascending.
parse_ibm_listing() {
  grep -oE '(^|[^0-9.])8\.0\.[0-9]+\.[0-9]+/' | grep -oE '8\.0\.[0-9]+\.[0-9]+' | sort -uV || true
}

# True when $1 sorts strictly after $2 as a version.
version_gt() {
  [ "$1" != "$2" ] && [ "$(printf '%s\n%s\n' "$1" "$2" | sort -V | tail -n 1)" = "$1" ]
}

ibm_candidate_url() {
  local version=$1
  echo "${IBM_JAVA_INDEX_URL}${version}/linux/x86_64/ibm-java-jre-8.0-${version#8.0.}-linux-x86_64.tgz"
}

write_kv() {
  printf '%s=%s\n' "$2" "$3" >> "$1"
}

read_kv() {
  sed -n "s/^$2=//p" "$1" 2>/dev/null | tail -n 1
}

# Writes ibm.txt. Every failure here is a warning: the newer-release check
# must never fail the job.
check_ibm_release() {
  local out=$1 pinned_url=$2 ibm="$1/ibm.txt" pinned listing versions latest candidate code v newer_count=0
  : > "$ibm"
  pinned=$(pinned_ibm_version "$pinned_url")
  if [ -z "$pinned" ]; then
    echo "::warning::Cannot parse the IBM SDK 8 version from $IBM_URL_VAR: $pinned_url"
    return 0
  fi
  write_kv "$ibm" pinned "$pinned"
  if ! listing=$(curl "${CURL_OPTS[@]}" --fail "$IBM_JAVA_INDEX_URL" 2>/dev/null </dev/null); then
    echo "::warning::IBM release listing unreachable: $IBM_JAVA_INDEX_URL"
    return 0
  fi
  versions=$(parse_ibm_listing <<<"$listing")
  if [ -z "$versions" ]; then
    echo "::warning::No 8.0.x.y releases found in the IBM listing: $IBM_JAVA_INDEX_URL"
    return 0
  fi
  write_kv "$ibm" listed "$(tr '\n' ' ' <<<"$versions" | sed 's/ $//')"
  latest=$(tail -n 1 <<<"$versions")
  write_kv "$ibm" latest "$latest"
  if [ "$latest" = "$pinned" ]; then
    echo "IBM SDK 8: the pinned $pinned is the newest listed release"
    return 0
  fi
  if ! version_gt "$latest" "$pinned"; then
    echo "::warning::IBM listing tops out at $latest, older than the pinned $pinned"
    return 0
  fi
  candidate=$(ibm_candidate_url "$latest")
  code=$(probe_url "$candidate")
  code=${code%% *}
  if [ "$(classify "$code")" != OK ]; then
    echo "::warning::IBM lists $latest but its archive returned HTTP $code: $candidate"
    return 0
  fi
  write_kv "$ibm" newer "$latest"
  write_kv "$ibm" candidate_url "$candidate"
  while read -r v; do
    if version_gt "$v" "$pinned"; then
      newer_count=$((newer_count + 1))
    fi
  done <<<"$versions"
  write_kv "$ibm" newer_count "$newer_count"
  echo "::notice::IBM SDK 8 $latest is available (pinned: $pinned): $candidate"
}

cmd_check() {
  local out="" workflow="$ROOT_DIR/.github/workflows/cache_java.yml"
  while [ $# -gt 0 ]; do
    case "$1" in
      --out) out="$2"; shift 2 ;;
      --workflow) workflow="$2"; shift 2 ;;
      *) echo "ERROR: unknown argument: $1" >&2; usage ;;
    esac
  done
  [ -n "$out" ] || usage
  mkdir -p "$out"
  local pins
  if ! pins=$(extract_urls "$workflow"); then
    echo "::error::Cannot parse $workflow with yq"
    exit 2
  fi
  # An empty list would pass every day while checking nothing.
  if [ -z "$pins" ]; then
    echo "::error::No env JAVA_*_URL keys found in $workflow"
    exit 2
  fi

  local results="$out/results.tsv" table="$out/table.md" stale=0 ibm_url=""
  : > "$results"
  {
    echo "| Variable | URL | HTTP status | Final URL |"
    echo "| --- | --- | --- | --- |"
  } > "$table"
  local var url probe code final class
  local deadline_start=$SECONDS deadline_hit=0
  while read -r var url; do
    if deadline_expired "$deadline_start"; then
      if [ "$deadline_hit" = 0 ]; then
        echo "::warning::Probe deadline (${PROBE_DEADLINE_SECONDS}s) reached; marking the remaining pins INCONCLUSIVE without probing"
        deadline_hit=1
      fi
      probe="000 $url"
    else
      probe=$(probe_url "$url")
    fi
    code=${probe%% *}
    final=${probe#* }
    class=$(classify "$code")
    printf '%s\t%s\t%s\t%s\t%s\n' "$var" "$url" "$class" "$code" "$final" >> "$results"
    # shellcheck disable=SC2016 # the backticks are a Markdown code span
    printf '| `%s` | %s | %s %s | %s |\n' "$var" "$url" "$code" "$class" "$final" >> "$table"
    case "$class" in
      OK) echo "OK: $var HTTP $code" ;;
      STALE) echo "::error::Stale JDK download URL: $var returned HTTP $code: $url"; stale=1 ;;
      *) echo "::warning::Inconclusive check of $var (HTTP $code): $url" ;;
    esac
    if [ "$var" = "$IBM_URL_VAR" ]; then
      ibm_url=$url
    fi
  done <<<"$pins"

  if [ -n "$ibm_url" ]; then
    if deadline_expired "$deadline_start"; then
      : > "$out/ibm.txt"
      echo "::warning::Probe deadline reached; skipping the IBM newer-release check"
    else
      check_ibm_release "$out" "$ibm_url"
    fi
  else
    : > "$out/ibm.txt"
    echo "::warning::$IBM_URL_VAR is not pinned; skipping the IBM newer-release check"
  fi

  if [ -n "${GITHUB_STEP_SUMMARY:-}" ]; then
    {
      echo "## JDK download URL check"
      echo
      cat "$table"
    } >> "$GITHUB_STEP_SUMMARY"
  fi
  return "$stale"
}

stale_summary() {
  echo "Stale JDK download URL: $1 (jdk-url-check)"
}

newer_summary() {
  echo "Newer IBM SDK 8 release available: $1 (jdk-url-check)"
}

bump_procedure() {
  cat <<'EOF'
Bump procedure (as in PR #1043):
1. In .github/workflows/cache_java.yml, set the pin to the new release. For JAVA_8_IBM_URL, both the directory and the archive name carry the version.
2. Update any comment that names the pinned version. Change .github/scripts/java_setup.sh only when the archive layout changed (the ibm branch strips 2 path components).
3. Open the PR. The edit changes the JDK cache key, so the PR's cache job downloads the new archive, and the jdk-url-check PR run verifies every pin.
EOF
}

# Runs a Jira command; under --dry-run prints it to stderr, leaving stdout
# (the issue key) empty.
run_action() {
  if [ "$DRY_RUN" = 1 ]; then
    echo "DRY-RUN: would run: $*" >&2
    return 0
  fi
  "$@" </dev/null
}

# file_alert <summary> <body file> <priority>: sets FILED_KEY and FILED_STATUS
# (created, existing, failed or dry-run). An open ticket is left as is, so
# each alert notifies once.
file_alert() {
  local status_file="$OUT_DIR/status.txt" rc=0
  rm -f "$status_file"
  FILED_KEY=$(run_action "$SCRIPT_DIR/file-jira-issue.sh" --summary "$1" --body-file "$2" \
    --priority "$3" --label "$JIRA_LABEL" --component "$JIRA_COMPONENT" \
    --on-duplicate skip --status-file "$status_file") || rc=$?
  if [ "$DRY_RUN" = 1 ]; then
    FILED_STATUS=dry-run
  elif [ "$rc" -ne 0 ]; then
    echo "::warning::Jira ticket '$1' could not be filed (exit $rc)"
    FILED_KEY=""
    FILED_STATUS=failed
  else
    FILED_STATUS=$(cat "$status_file" 2>/dev/null || echo created)
  fi
}

# try_resolve <summary> <comment file>: sets RESOLVED_KEY when a ticket was
# closed. A lookup or credentials failure would repeat for every summary, so
# it stops the remaining attempts of this run.
try_resolve() {
  local rc=0
  RESOLVED_KEY=""
  if [ "$RESOLVE_DISABLED" = 1 ]; then
    return 0
  fi
  RESOLVED_KEY=$(run_action "$SCRIPT_DIR/resolve-jira-issue.sh" --summary "$1" --comment-file "$2") || rc=$?
  case "$rc" in
    0) ;;
    3) echo "::warning::Jira credentials missing; skipping auto-resolve"; RESOLVE_DISABLED=1 ;;
    4) echo "::warning::$RESOLVED_KEY has no transition to done; resolve it by hand" ;;
    5) echo "::warning::$RESOLVED_KEY could not be resolved (exit 5); resolve it by hand" ;;
    *) echo "::warning::Auto-resolve lookup failed (exit $rc); skipping auto-resolve"; RESOLVE_DISABLED=1 ;;
  esac
  if [ "$rc" -ne 0 ]; then
    RESOLVED_KEY=""
  fi
}

post_slack() {
  local text_file=$1
  if [ "$DRY_RUN" = 1 ]; then
    echo "DRY-RUN: would post to Slack:"
    cat "$text_file"
    return 0
  fi
  if [ -z "${SLACK_WEBHOOK:-}" ]; then
    echo "SLACK_WEBHOOK not configured, skipping notification"
    return 0
  fi
  # Same fields as certification.yml: one webhook receiver serves both, and
  # a plain incoming webhook ignores the extras.
  local payload
  payload=$(jq -n --rawfile text "$text_file" --arg run "$RUN_URL" \
    '{text: $text, scenarios: $text, failed_run_url: $run}')
  if ! curl -fsS -X POST -H 'Content-Type: application/json' --data "$payload" "$SLACK_WEBHOOK" >/dev/null; then
    echo "::warning::Slack notification failed"
  fi
}

write_stale_body() {
  local body=$1 var=$2 url=$3 code=$4 forced=$5
  {
    if [ "$forced" = 1 ]; then
      echo "FORCED TEST ALERT (workflow_dispatch force_issue=true). This URL is not necessarily stale; the next scheduled or manual run resolves this ticket if it answers 2xx."
      echo
    fi
    echo "$var in .github/workflows/cache_java.yml returned HTTP $code: $url"
    echo
    echo "Until it is fixed, every cache_java.yml cache miss fails, which blocks the Linux test matrix."
    echo
    echo "Run: $RUN_URL"
    echo
    cat "$OUT_DIR/table.md"
    echo
    bump_procedure
  } > "$body"
}

write_newer_body() {
  local body=$1 ibm=$2 newer=$3 pinned=$4
  {
    echo "IBM lists IBM SDK 8 $newer; .github/workflows/cache_java.yml pins $pinned."
    echo
    echo "Releases listed by IBM: $(read_kv "$ibm" listed). Releases newer than the pin: $(read_kv "$ibm" newer_count). IBM keeps only a few releases, so the pin returns 404 once enough newer ones ship."
    echo
    echo "Verified archive: $(read_kv "$ibm" candidate_url)"
    echo
    echo "This check does not change the pin. A new IBM SDK carries a new OpenJ9 level; review it before the bump."
    echo
    echo "Run: $RUN_URL"
    echo
    cat "$OUT_DIR/table.md"
    echo
    bump_procedure
  } > "$body"
}

cmd_alert() {
  local force=0
  OUT_DIR=""
  DRY_RUN=0
  RESOLVE_DISABLED=0
  while [ $# -gt 0 ]; do
    case "$1" in
      --out) OUT_DIR="$2"; shift 2 ;;
      --force-issue) force=1; shift ;;
      --dry-run) DRY_RUN=1; shift ;;
      *) echo "ERROR: unknown argument: $1" >&2; usage ;;
    esac
  done
  [ -n "$OUT_DIR" ] || usage
  local results="$OUT_DIR/results.tsv" ibm="$OUT_DIR/ibm.txt"
  if [ ! -s "$results" ]; then
    echo "::warning::No check results in $OUT_DIR; nothing to alert on"
    return 0
  fi
  if [ -z "${RUN_URL:-}" ]; then
    RUN_URL="${GITHUB_SERVER_URL:-https://github.com}/${GITHUB_REPOSITORY:-DataDog/java-profiler}/actions/runs/${GITHUB_RUN_ID:-0}"
  fi
  local slack="$OUT_DIR/slack.txt" summary_lines="$OUT_DIR/actions.md"
  : > "$slack"
  : > "$summary_lines"

  # A forced alert reuses the real summary, so the next scheduled run, which
  # sees the URL resolve, also exercises the auto-resolve path.
  local force_var=""
  if [ "$force" = 1 ]; then
    force_var=$(awk -F '\t' -v v="$IBM_URL_VAR" '$1 == v { print $1 }' "$results")
    if [ -z "$force_var" ]; then
      force_var=$(head -n 1 "$results" | cut -f 1)
    fi
  fi

  local var url class code final body forced label
  while IFS=$'\t' read -r var url class code final; do
    forced=0
    if [ "$var" = "$force_var" ]; then
      forced=1
      class=STALE
    fi
    case "$class" in
      STALE)
        body="$OUT_DIR/stale-$var.txt"
        write_stale_body "$body" "$var" "$url" "$code" "$forced"
        file_alert "$(stale_summary "$var")" "$body" High
        label="Stale: $var (HTTP $code) $url"
        if [ "$forced" = 1 ]; then
          label="Stale (forced test via force_issue): $var"
        fi
        if [ "$FILED_STATUS" != existing ]; then
          echo "$label${FILED_KEY:+ -> $FILED_KEY}" >> "$slack"
        fi
        echo "- $label ($FILED_STATUS${FILED_KEY:+: $FILED_KEY})" >> "$summary_lines"
        ;;
      OK)
        body="$OUT_DIR/resolved-$var.txt"
        printf '%s resolves again (HTTP %s) in %s; closing this alert.\n' "$var" "$code" "$RUN_URL" > "$body"
        try_resolve "$(stale_summary "$var")" "$body"
        if [ -n "$RESOLVED_KEY" ]; then
          echo "Recovered: $var resolves again (HTTP $code); resolved $RESOLVED_KEY" >> "$slack"
          echo "- Recovered $var: resolved $RESOLVED_KEY" >> "$summary_lines"
        fi
        ;;
      *) ;;
    esac
  done < "$results"

  local newer pinned v
  newer=$(read_kv "$ibm" newer)
  pinned=$(read_kv "$ibm" pinned)
  if [ -n "$newer" ]; then
    body="$OUT_DIR/newer-ibm.txt"
    write_newer_body "$body" "$ibm" "$newer" "$pinned"
    file_alert "$(newer_summary "$newer")" "$body" Medium
    if [ "$FILED_STATUS" != existing ]; then
      echo "Newer IBM SDK 8 release: $newer (pinned: $pinned)${FILED_KEY:+ -> $FILED_KEY}" >> "$slack"
    fi
    echo "- Newer IBM SDK 8 release $newer, pinned $pinned ($FILED_STATUS${FILED_KEY:+: $FILED_KEY})" >> "$summary_lines"
  fi
  # A newer-release ticket is done once the pin reaches its version.
  if [ -n "$pinned" ]; then
    for v in $(read_kv "$ibm" listed); do
      if version_gt "$v" "$pinned"; then
        continue
      fi
      body="$OUT_DIR/resolved-ibm-$v.txt"
      printf 'JAVA_8_IBM_URL pins IBM SDK %s in %s; closing this alert.\n' "$pinned" "$RUN_URL" > "$body"
      try_resolve "$(newer_summary "$v")" "$body"
      if [ -n "$RESOLVED_KEY" ]; then
        echo "- IBM SDK 8 $v is pinned: resolved $RESOLVED_KEY" >> "$summary_lines"
      fi
    done
  fi

  if [ -s "$slack" ]; then
    {
      echo "java-profiler JDK download URL check ($RUN_URL):"
      cat "$slack"
    } > "$slack.msg"
    post_slack "$slack.msg"
  fi
  if [ -n "${GITHUB_STEP_SUMMARY:-}" ] && [ -s "$summary_lines" ]; then
    {
      echo
      echo "### Alerts"
      cat "$summary_lines"
    } >> "$GITHUB_STEP_SUMMARY"
  fi
}

main() {
  local cmd=${1:-}
  [ $# -gt 0 ] && shift
  case "$cmd" in
    check) cmd_check "$@" ;;
    alert) cmd_alert "$@" ;;
    *) usage ;;
  esac
}

# Sourcing exposes the helpers to the hermetic tests without running a command.
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
