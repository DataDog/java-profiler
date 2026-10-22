#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for utils/sweep-refchains-all.sh's per-run metrics
# aggregation (parse_run). The sweep is copied next to stub sibling scripts
# (repro runner, refchains-jfr-metrics.py, report renderer) so no JVM or jfr
# is needed.
# Run with: bash utils/tests/test_sweep_refchains_parse_run.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
SWEEP="$SCRIPT_DIR/../sweep-refchains-all.sh"
TESTS=0
FAILED=0

TEMP_DIR=$(mktemp -d)
SWEEP_WORKDIRS=()
cleanup() {
  rm -rf "$TEMP_DIR"
  local d
  for d in ${SWEEP_WORKDIRS[@]+"${SWEEP_WORKDIRS[@]}"}; do
    rm -rf "$d"
  done
}
trap cleanup EXIT

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

expect_not_contains() {
  case "$2" in
    *"$3"*) fail "$1: should not contain '$3'" ;;
    *) pass ;;
  esac
}

HERE_DIR="$TEMP_DIR/here"
mkdir -p "$HERE_DIR"
cp "$SWEEP" "$HERE_DIR/sweep-refchains-all.sh"
chmod +x "$HERE_DIR/sweep-refchains-all.sh"

cat > "$HERE_DIR/run-refchains-repro.sh" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
jfr="$1"
if [ -z "${STUB_NO_SNAPSHOTS:-}" ]; then
  echo "snap-base" > "${jfr}.snapshot"
  echo "snap-10" > "${jfr}.snapshot.10"
  echo "snap-20" > "${jfr}.snapshot.20"
fi
echo "[metrics] wallSeconds=1.0 entriesPerSec=100.0 avgRoundMs=1.0 maxRoundMs=2.0 heapGrowthMb=3"
exit 0
EOF

cat > "$HERE_DIR/refchains-jfr-metrics.py" <<'EOF'
#!/usr/bin/env python3
import os
import sys

log = os.environ.get("STUB_LOG")
if log:
    parts = [f"argc={len(sys.argv) - 1}"]
    for a in sys.argv[1:]:
        parts.append(f"{a}:exists={int(os.path.exists(a))}:ends_jfr={int(a.endswith('.jfr'))}")
    with open(log, "a") as f:
        f.write(" ".join(parts) + "\n")
if os.environ.get("STUB_JFR_FAIL") == "1":
    print("boom-diagnostic", file=sys.stderr)
    sys.exit(1)
print(os.environ.get("STUB_JFR_OUT", "5 2 12.345"))
EOF

cat > "$HERE_DIR/refchains-report-multi.py" <<'EOF'
#!/usr/bin/env python3
EOF

chmod +x "$HERE_DIR/run-refchains-repro.sh" "$HERE_DIR/refchains-jfr-metrics.py" \
  "$HERE_DIR/refchains-report-multi.py"

EXPECTED_HEADER="knob,param_value,entries_per_sec,avg_round_ms,max_round_ms,heap_growth_mb,stw_count,stw_total_s,stw_avg_s,stw_max_s,peak_rss_kb,wall_seconds,chain_count,abandoned_count,time_to_first_chain_s"

# run_sweep <bash binary> [env=val ...] - sets RC, OUT, ERR, CSV_PATH, WD
run_sweep() {
  local bash_bin=$1
  shift
  RC=0
  rm -f "$TEMP_DIR/stub.log"
  env REFCHAINS_SWEEP_BUDGET_VALUES=1 \
    REFCHAINS_SWEEP_FIRSTPASSBUDGET_VALUES=2 \
    REFCHAINS_SWEEP_PAUSETARGET_VALUES=3 \
    REFCHAINS_SWEEP_PAINBUDGET_VALUES=4 \
    STUB_LOG="$TEMP_DIR/stub.log" \
    "$@" \
    "$bash_bin" "$HERE_DIR/sweep-refchains-all.sh" 1 \
    > "$TEMP_DIR/sweep.out" 2> "$TEMP_DIR/sweep.err" || RC=$?
  OUT=$(cat "$TEMP_DIR/sweep.out")
  ERR=$(cat "$TEMP_DIR/sweep.err")
  CSV_PATH=$(sed -n 's/^CSV written to: //p' "$TEMP_DIR/sweep.out")
  WD=""
  if [ -n "$CSV_PATH" ]; then
    WD=$(dirname "$CSV_PATH")
    SWEEP_WORKDIRS+=("$WD")
  fi
}

# rows_ending <suffix regex> - number of CSV data rows matching
rows_ending() {
  if [ -z "$CSV_PATH" ] || [ ! -f "$CSV_PATH" ]; then
    echo 0
    return
  fi
  tail -n +2 "$CSV_PATH" | grep -c -- "$1\$" || true
}

run_suite() {
  local bash_bin=$1 tag=$2

  # --- T2.1 one aggregate call per run --------------------------------------
  run_sweep "$bash_bin"
  expect_eq "$tag T2.1 rc" "$RC" "0"
  local lines=0
  if [ -f "$TEMP_DIR/stub.log" ]; then
    lines=$(wc -l < "$TEMP_DIR/stub.log" | tr -d ' ')
  fi
  expect_eq "$tag T2.1 metrics calls" "$lines" "4"
  if [ -f "$TEMP_DIR/stub.log" ]; then
    local line n_args distinct
    while IFS= read -r line; do
      expect_contains "$tag T2.1 argc" "$line" "argc=3 "
      n_args=$(printf '%s\n' "$line" | tr ' ' '\n' | grep -c ':exists=1:ends_jfr=1$' || true)
      expect_eq "$tag T2.1 args exist and end in .jfr" "$n_args" "3"
      distinct=$(printf '%s\n' "$line" | tr ' ' '\n' | grep ':exists=' | cut -d: -f1 | sort -u | wc -l | tr -d ' ')
      expect_eq "$tag T2.1 distinct paths" "$distinct" "3"
    done < "$TEMP_DIR/stub.log"
  fi
  if [ -n "$WD" ]; then
    local leftovers
    leftovers=$(find "$WD" -name '*.metrics*.jfr' | wc -l | tr -d ' ')
    expect_eq "$tag T2.1 temp copies removed" "$leftovers" "0"
  else
    fail "$tag T2.1: no 'CSV written to:' line"
  fi

  # --- T2.2 float ttf reaches the CSV ---------------------------------------
  expect_eq "$tag T2.2 rows with 5,2,12.345" "$(rows_ending ',5,2,12\.345')" "4"

  # --- T2.3 CSV contract -------------------------------------------------------
  if [ -n "$CSV_PATH" ] && [ -f "$CSV_PATH" ]; then
    expect_eq "$tag T2.3 header" "$(head -n 1 "$CSV_PATH")" "$EXPECTED_HEADER"
    if awk -F, 'NF != 15 { bad = 1 } END { exit bad }' "$CSV_PATH"; then
      pass
    else
      fail "$tag T2.3: a CSV row does not have 15 fields"
    fi
  else
    fail "$tag T2.3: CSV missing"
  fi

  # --- T2.4 failure is visible ----------------------------------------------
  run_sweep "$bash_bin" STUB_JFR_FAIL=1
  expect_eq "$tag T2.4 rc" "$RC" "0"
  expect_eq "$tag T2.4 rows with 0,0,-1" "$(rows_ending ',0,0,-1')" "4"
  expect_contains "$tag T2.4 diagnostic" "$ERR" "boom-diagnostic"
  expect_contains "$tag T2.4 warn" "$ERR" "WARN: refchains-jfr-metrics failed for 'budget_1'"

  # --- T2.5 no snapshots --------------------------------------------------------
  run_sweep "$bash_bin" STUB_NO_SNAPSHOTS=1
  expect_eq "$tag T2.5 rc" "$RC" "0"
  if [ ! -s "$TEMP_DIR/stub.log" ]; then pass; else fail "$tag T2.5: metrics script was called"; fi
  expect_eq "$tag T2.5 rows with 0,0,-1" "$(rows_ending ',0,0,-1')" "4"
  expect_not_contains "$tag T2.5 stderr" "$ERR" "unbound variable"
}

run_suite bash "bash"

# --- T2.6 bash 3.2 ------------------------------------------------------------
if [ -x /bin/bash ] && case "$(/bin/bash --version 2>/dev/null)" in *"version 3."*) true ;; *) false ;; esac; then
  run_suite /bin/bash "bash3.2"
else
  echo "SKIP: T2.6 (bash 3.2 unavailable)"
fi

echo "$TESTS checks, $FAILED failed"
if [ "$FAILED" -gt 0 ]; then
  exit 1
fi
