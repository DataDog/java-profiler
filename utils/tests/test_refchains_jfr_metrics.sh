#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic unit tests for utils/refchains-jfr-metrics.py. A fake `jfr` serves
# canned `print --events <name> --json` / `summary` output from sidecar files
# next to each (empty) snapshot path; a "poison" `jfr` first on PATH proves
# which tool the script picked.
# Run with: bash utils/tests/test_refchains_jfr_metrics.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
METRICS="$SCRIPT_DIR/../refchains-jfr-metrics.py"
TESTS=0
FAILED=0

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() {
  TESTS=$((TESTS + 1))
}

fail() {
  TESTS=$((TESTS + 1))
  FAILED=$((FAILED + 1))
  echo "FAIL: $*" >&2
}

expect_eq() {
  if [ "$2" = "$3" ]; then pass; else fail "$1: expected '$3', got '$2'"; fi
}

expect_contains() {
  case "$2" in
    *"$3"*) pass ;;
    *) fail "$1: expected to contain '$3', got '$2'" ;;
  esac
}

expect_absent() {
  if [ ! -e "$2" ]; then pass; else fail "$1: '$2' should not exist"; fi
}

# T1.17: every success line has the exact output shape.
expect_shape() {
  if printf '%s\n' "$2" | grep -Eq '^[0-9]+ [0-9]+ -?[0-9]+\.[0-9]{3}$' \
      && [ "$(printf '%s\n' "$2" | wc -l | tr -d ' ')" = "1" ]; then
    pass
  else
    fail "$1 (T1.17 shape): '$2'"
  fi
}

# --- fixtures --------------------------------------------------------------

# Both fake tools append to "<tool-root>.calls" (e.g. $TEMP_DIR/jdk.calls).
mkdir -p "$TEMP_DIR/jdk/bin" "$TEMP_DIR/poison/bin"
cat > "$TEMP_DIR/jdk/bin/jfr" <<'EOF'
#!/usr/bin/env bash
root=$(cd "$(dirname "$0")/.." && pwd)
echo "$*" >> "${root}.calls"
for path in "$@"; do :; done
if [ -e "${path}.fail" ]; then
  echo "fake jfr failure for ${path}" >&2
  exit 1
fi
case "$1" in
  summary)
    if [ -f "${path}.summary" ]; then cat "${path}.summary"; fi
    ;;
  print)
    if [ -e "${path}.badjson" ]; then
      echo "this is not json"
    elif [ -f "${path}.$3.json" ]; then
      cat "${path}.$3.json"
    else
      echo '{"recording":{"events":[]}}'
    fi
    ;;
esac
exit 0
EOF
cat > "$TEMP_DIR/poison/bin/jfr" <<'EOF'
#!/usr/bin/env bash
root=$(cd "$(dirname "$0")/.." && pwd)
echo "$*" >> "${root}.calls"
exit 99
EOF
chmod +x "$TEMP_DIR/jdk/bin/jfr" "$TEMP_DIR/poison/bin/jfr"

JDK="$TEMP_DIR/jdk"
POISON_PATH="$TEMP_DIR/poison/bin:$PATH"

T0="2026-10-20T10:00:00.000+00:00"
# ts <seconds after T0, 0..59>
ts() {
  printf '2026-10-20T10:00:%02d.000+00:00' "$1"
}

# events <snapshot path> <event name> <values-json>...
events() {
  local path=$1 name=$2 body="" v
  shift 2
  for v in "$@"; do
    body="${body:+${body},}{\"type\":\"${name}\",\"values\":${v}}"
  done
  printf '{"recording":{"events":[%s]}}\n' "${body}" > "${path}.${name}.json"
}

# summary <snapshot path> <HH:MM:SS> - exactly one leading space, like real jfr.
summary() {
  printf ' Start: 2026-10-20 %s (UTC)\n' "$2" > "$1.summary"
}

CASE_N=0
new_case() {
  CASE_N=$((CASE_N + 1))
  CASE_DIR="$TEMP_DIR/case$CASE_N"
  mkdir -p "$CASE_DIR"
  rm -f "$TEMP_DIR/jdk.calls" "$TEMP_DIR/poison.calls"
}

snap() {
  : > "$CASE_DIR/$1"
  printf '%s' "$CASE_DIR/$1"
}

# run_m <command...> - sets RC, OUT, ERR
run_m() {
  RC=0
  "$@" > "$TEMP_DIR/out" 2> "$TEMP_DIR/err" || RC=$?
  OUT=$(cat "$TEMP_DIR/out")
  ERR=$(cat "$TEMP_DIR/err")
}

# metrics <files...>: the default invocation (java home = fake jdk, poison on PATH)
metrics() {
  run_m env REFCHAINS_JAVA_HOME="$JDK" PATH="$POISON_PATH" python3 "$METRICS" "$@"
}

# --- T1.1 java-home jfr is used --------------------------------------------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 5)\"}"
metrics "$f"
expect_eq "T1.1 rc" "$RC" "0"
expect_eq "T1.1 out" "$OUT" "1 0 5.000"
expect_shape "T1.1" "$OUT"
expect_absent "T1.1 poison not called" "$TEMP_DIR/poison.calls"
if [ -s "$TEMP_DIR/jdk.calls" ]; then pass; else fail "T1.1: java-home jfr was not called"; fi

# --- T1.2 bad java home is fatal, no fallback -------------------------------
new_case
f=$(snap t12.jfr)
run_m env REFCHAINS_JAVA_HOME="$TEMP_DIR/nope" PATH="$POISON_PATH" python3 "$METRICS" "$f"
expect_eq "T1.2 rc" "$RC" "1"
expect_contains "T1.2 stderr names the tool" "$ERR" "$TEMP_DIR/nope/bin/jfr"
expect_absent "T1.2 poison not called" "$TEMP_DIR/poison.calls"
expect_eq "T1.2 stdout" "$OUT" ""

# --- T1.3 unset / empty java home uses PATH ---------------------------------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 5)\"}"
run_m env -u REFCHAINS_JAVA_HOME PATH="$JDK/bin:$PATH" python3 "$METRICS" "$f"
expect_eq "T1.3 unset rc" "$RC" "0"
expect_eq "T1.3 unset out" "$OUT" "1 0 5.000"
expect_shape "T1.3 unset" "$OUT"
run_m env REFCHAINS_JAVA_HOME="" PATH="$JDK/bin:$PATH" python3 "$METRICS" "$f"
expect_eq "T1.3 empty rc" "$RC" "0"
expect_eq "T1.3 empty out" "$OUT" "1 0 5.000"

# --- T1.4 multi-chunk origin -------------------------------------------------
new_case
f1=$(snap s1.jfr)
f2=$(snap s2.jfr)
events "$f1" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
summary "$f1" "10:00:00"
events "$f1" datadog.ReferenceChain "{\"startTime\":\"$(ts 12)\"}"
events "$f1" datadog.ReferenceChainAbandoned "{\"startTime\":\"$(ts 13)\"}"
events "$f2" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
summary "$f2" "10:00:20"
events "$f2" datadog.ReferenceChain "{\"startTime\":\"$(ts 21)\"}" "{\"startTime\":\"$(ts 40)\"}"
events "$f2" datadog.ReferenceChainAbandoned "{\"startTime\":\"$(ts 22)\"}"
metrics "$f1" "$f2"
expect_eq "T1.4 rc" "$RC" "0"
expect_eq "T1.4 out" "$OUT" "3 2 12.000"
expect_shape "T1.4" "$OUT"

# --- T1.5 origin precedence: ActiveRecording startTime ----------------------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"startTime\":\"$T0\"}"
summary "$f" "10:00:20"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 30)\"}"
metrics "$f"
expect_eq "T1.5 out" "$OUT" "1 0 30.000"
expect_shape "T1.5" "$OUT"

# --- T1.6 origin precedence: summary Start -----------------------------------
new_case
f=$(snap a.jfr)
summary "$f" "10:00:00"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 7)\"}"
metrics "$f"
expect_eq "T1.6 out" "$OUT" "1 0 7.000"
expect_shape "T1.6" "$OUT"

# --- T1.7 ActiveRecording beats summary --------------------------------------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
summary "$f" "10:00:20"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 25)\"}"
metrics "$f"
expect_eq "T1.7 out" "$OUT" "1 0 25.000"

# --- T1.8 epoch-millis origin -------------------------------------------------
new_case
f=$(snap a.jfr)
T0_MS=$(python3 -c 'from datetime import datetime, timezone; print(int(datetime(2026, 10, 20, 10, tzinfo=timezone.utc).timestamp() * 1000))')
events "$f" jdk.ActiveRecording "{\"recordingStart\":${T0_MS}}"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 3)\"}"
metrics "$f"
expect_eq "T1.8 out" "$OUT" "1 0 3.000"
expect_shape "T1.8" "$OUT"

# --- T1.9 ISO variants (9 fraction digits + Z, offset without fraction) ------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
events "$f" datadog.ReferenceChain \
  '{"startTime":"2026-10-20T10:00:04.123456789Z"}' \
  '{"startTime":"2026-10-20T12:00:02+02:00"}'
metrics "$f"
expect_eq "T1.9 rc" "$RC" "0"
expect_eq "T1.9 out" "$OUT" "2 0 2.000"

# --- T1.10 no chain -----------------------------------------------------------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
events "$f" datadog.ReferenceChainAbandoned "{\"startTime\":\"$(ts 1)\"}" "{\"startTime\":\"$(ts 2)\"}"
metrics "$f"
expect_eq "T1.10 out" "$OUT" "0 2 -1.000"
expect_shape "T1.10" "$OUT"

# --- T1.11 no origin ----------------------------------------------------------
new_case
f=$(snap a.jfr)
events "$f" datadog.ReferenceChain "{\"startTime\":\"$(ts 5)\"}"
metrics "$f"
expect_eq "T1.11 out" "$OUT" "1 0 -1.000"

# --- T1.12 clamp to >= 0 -----------------------------------------------------
new_case
f=$(snap a.jfr)
events "$f" jdk.ActiveRecording "{\"recordingStart\":\"$(ts 1)\"}"
events "$f" datadog.ReferenceChain "{\"startTime\":\"$T0\"}"
metrics "$f"
expect_eq "T1.12 out" "$OUT" "1 0 0.000"

# --- T1.13 one unreadable file is skipped -----------------------------------
new_case
f1=$(snap bad.jfr)
f2=$(snap good.jfr)
: > "$f1.fail"
events "$f2" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
events "$f2" datadog.ReferenceChain "{\"startTime\":\"$(ts 4)\"}"
metrics "$f1" "$f2"
expect_eq "T1.13 rc" "$RC" "0"
expect_eq "T1.13 out" "$OUT" "1 0 4.000"
expect_contains "T1.13 stderr names the skipped file" "$ERR" "$f1"

# --- T1.14 bad JSON is skipped -----------------------------------------------
new_case
f1=$(snap bad.jfr)
f2=$(snap good.jfr)
: > "$f1.badjson"
events "$f2" jdk.ActiveRecording "{\"recordingStart\":\"$T0\"}"
events "$f2" datadog.ReferenceChain "{\"startTime\":\"$(ts 4)\"}"
metrics "$f1" "$f2"
expect_eq "T1.14 rc" "$RC" "0"
expect_eq "T1.14 out" "$OUT" "1 0 4.000"

# --- T1.15 all unreadable ----------------------------------------------------
new_case
f1=$(snap a.jfr)
f2=$(snap b.jfr)
: > "$f1.fail"
: > "$f2.fail"
metrics "$f1" "$f2"
if [ "$RC" -ne 0 ]; then pass; else fail "T1.15: expected non-zero exit"; fi
expect_eq "T1.15 stdout" "$OUT" ""

# --- T1.16 usage -------------------------------------------------------------
new_case
run_m env REFCHAINS_JAVA_HOME="$JDK" python3 "$METRICS"
expect_eq "T1.16 rc" "$RC" "1"
expect_contains "T1.16 usage" "$ERR" "Usage"

echo "$TESTS checks, $FAILED failed"
if [ "$FAILED" -gt 0 ]; then
  exit 1
fi
