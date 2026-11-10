#! /bin/bash
# Copyright 2026, Datadog, Inc.
#
# Network-free tests for the release probe and the verdict mapping in
# .gitlab/reliability/memory_trend_check.sh. The gate is sourced (its main
# body runs only when executed), the probe is driven against fake proc and
# cgroup trees with a stub jcmd, and the verdict mapping is asserted on the
# stderr lines it emits.
# Run with: bash .gitlab/reliability/tests/memory_probe_test.sh
# PYTHON_BIN can point at an interpreter that has numpy and matplotlib.

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
CHECK="${HERE}/../memory_trend_check.sh"
# the sourced gate redefines HERE for its own helpers, so sibling paths are
# captured before the source line
STEPS="${HERE}/../../benchmarks/steps"
MEMWATCH="${STEPS}/mem_watch.sh"
PYTHON_BIN="${PYTHON_BIN:-python3}"

FAILED=0
WORK=$(mktemp -d)
JPID=
SPID=
JPID2=
SPID2=

# shellcheck disable=SC2329  # cleanup runs through the EXIT trap
cleanup() {
  kill "${JPID:-}" "${SPID:-}" "${JPID2:-}" "${SPID2:-}" 2>/dev/null
  rm -rf "${WORK}"
}
trap cleanup EXIT

pass() { echo "PASS: $1"; }
fail_case() { echo "FAIL: $1"; FAILED=1; }

assert_eq() { # $1 what, $2 expected, $3 actual
  if [ "$2" = "$3" ]; then
    pass "$1"
  else
    fail_case "$1: expected [$2] got [$3]"
  fi
}

# pid discovery inside mem_watch.sh drops lines containing 'grep' or 'time'
case "$WORK" in
  *time*|*grep*)
    echo "FAIL: temp dir path is excluded by pid discovery: $WORK"
    exit 1
    ;;
esac

# shellcheck disable=SC1090  # sourcing defines the helpers without running the gate
. "${CHECK}"

# --- constants and main-body wiring -------------------------------------------

assert_eq "PROBE_TAIL_SECONDS" "30" "${PROBE_TAIL_SECONDS}"
assert_eq "PROBE_TIMEOUT_SECONDS" "20" "${PROBE_TIMEOUT_SECONDS}"
if [ "${PROBE_TIMEOUT_SECONDS}" -lt "${PROBE_TAIL_SECONDS}" ]; then
  pass "the probe timeout stays below the tail"
else
  fail_case "the probe timeout must stay below the tail"
fi

check_provisional_comment() { # $1 constant name
  if awk -v name="$1" '
    $0 ~ "^" name "=" {
      c = 0; prov = 0
      for (i = NR - 1; i >= 1 && index(lines[i], "#") == 1; i--) {
        c++
        if (lines[i] ~ /[Pp]rovisional/) prov = 1
      }
      exit !(c >= 1 && c <= 3 && prov)
    }
    { lines[NR] = $0 }
  ' "${CHECK}"; then
    pass "$1 carries a provisional comment of at most 3 lines"
  else
    fail_case "$1 lacks a provisional comment of at most 3 lines"
  fi
}

check_provisional_comment PROBE_TAIL_SECONDS
check_provisional_comment PROBE_TIMEOUT_SECONDS

assert_wiring() { # $1 description, $2 fixed string that must appear in the gate
  if grep -qF -- "$2" "${CHECK}"; then
    pass "$1"
  else
    fail_case "$1: [$2] is missing from ${CHECK}"
  fi
}

# shellcheck disable=SC2016  # the checked strings must stay literal
wiring_checks() {
  assert_wiring "the JVM runs the window plus the probe tail" 'akka-uct -t $((RUNTIME + PROBE_TAIL_SECONDS)) &'
  assert_wiring "the JVM runs in the background" 'JVM_PID=$!'
  assert_wiring "the sampler pid is kept" 'SAMPLER_PID=$!'
  assert_wiring "the window closes before the probe" 'close_measurement_window "${RUNTIME}" "${JVM_PID}" "${SAMPLER_PID}" "${CONTROL_FILE}"'
  assert_wiring "the probe records go to memwatch.log" 'release_probe_records "$ALLOCATOR" "${JVM_PID}" "${HERE}/../../memwatch.log"'
  assert_wiring "RC comes from waiting for the JVM" 'wait "${JVM_PID}"'
  assert_wiring "the crash failure is preserved" 'FAIL:Benchmark crashed'
  assert_wiring "the verdict runs through the allocator-aware check" 'run_trend_check "${HERE}/../../memwatch.log" "${HERE}/../../memwatch-trend.png" "$ALLOCATOR"'

  local sampler_line preload_line
  sampler_line=$(grep -nF 'sh ${HERE}/../benchmarks/steps/mem_watch.sh' "${CHECK}" | head -1 | cut -d: -f1)
  preload_line=$(grep -nF 'case $ALLOCATOR in' "${CHECK}" | head -1 | cut -d: -f1)
  if [ -n "${sampler_line}" ] && [ -n "${preload_line}" ] && [ "${sampler_line}" -lt "${preload_line}" ]; then
    pass "the sampler starts before LD_PRELOAD is exported"
  else
    fail_case "the sampler no longer starts before LD_PRELOAD is exported"
  fi
}

wiring_checks

# --- fake trees and stubs -----------------------------------------------------

write_stat() { # $1 proc root, $2 pid, $3 comm, $4 state, $5 ppid
  mkdir -p "$1/$2"
  printf '%s (%s) %s %s 1 1 1 0 -1 0\n' "$2" "$3" "$4" "$5" > "$1/$2/stat"
}

write_smaps() { # $1 proc root, $2 pid, $3 rss kB
  mkdir -p "$1/$2"
  printf 'Rss:        %s kB\n' "$3" > "$1/$2/smaps_rollup"
}

build_roots() { # $1 proc root, $2 cgroup root
  mkdir -p "$1/pressure" "$2"
  printf 'some avg10=0.15 avg60=1.25 avg300=1.75 total=100\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$1/pressure/cpu"
  printf 'some avg10=0.25 avg60=1.50 avg300=2.00 total=200\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$1/pressure/memory"
  printf '0.80 0.90 1.00 2/400 4321\n' > "$1/loadavg"
  printf 'cpu io memory\n' > "$2/cgroup.controllers"
  printf 'usage_usec 1000\nnr_periods 100\nnr_throttled 4\nthrottled_usec 0\n' > "$2/cpu.stat"
}

PROC="${WORK}/proc"
CG="${WORK}/cgroup"
BIN="${WORK}/bin"
mkdir -p "${BIN}"
build_roots "${PROC}" "${CG}"
write_stat "${PROC}" 4242 java S 1
write_stat "${PROC}" 500 cotenant R 1
write_stat "${PROC}" 501 idle S 1
write_smaps "${PROC}" 4242 23456

EXP_TOKENS="psi_cpu_some_avg10=0.15 psi_memory_some_avg10=0.25 loadavg_1m=0.80 cpu_nr_throttled=4 cotenant_runnable=1"

cat > "${WORK}/jcmd-ok" <<'EOF'
#!/bin/sh
echo "$1:"
echo "Trim native heap: 4096 kB trimmed"
EOF
cat > "${WORK}/jcmd-exit3" <<'EOF'
#!/bin/sh
echo "$1: attach failed"
exit 3
EOF
cat > "${WORK}/jcmd-nomatch" <<'EOF'
#!/bin/sh
echo "$1: unknown diagnostic"
exit 0
EOF
cat > "${WORK}/jcmd-slow" <<'EOF'
#!/bin/sh
exec sleep 30
EOF
chmod +x "${WORK}"/jcmd-*

if ! command -v timeout > /dev/null 2>&1; then
  cat > "${BIN}/timeout" <<'EOF'
#!/bin/sh
# Test shim for hosts without coreutils timeout: exit 124 when the command
# is killed at the deadline, else pass its own status through.
secs=$1
shift
"$@" &
cmd=$!
( sleep "$secs" && kill -9 "$cmd" ) > /dev/null 2>&1 &
killer=$!
wait "$cmd"
status=$?
kill "$killer" 2>/dev/null
wait "$killer" 2>/dev/null
[ "$status" -lt 128 ] || status=124
exit "$status"
EOF
  chmod +x "${BIN}/timeout"
fi

# run_trend_check invokes python3 by name, so it must resolve to PYTHON_BIN;
# a wrapper (not a symlink) keeps the interpreter's own activation working
cat > "${BIN}/python3" <<EOF
#!/bin/sh
exec $(command -v "${PYTHON_BIN}") "\$@"
EOF
chmod +x "${BIN}/python3"
export PATH="${BIN}:${PATH}"

# --- probe records with a stub jcmd -------------------------------------------

MEMWATCH_PROC_ROOT="${PROC}"
MEMWATCH_CGROUP_ROOT="${CG}"

run_probe() { # $1 log, $2 allocator, $3 pid, $4 jcmd stub
  : > "$1"
  MEM_TREND_JCMD="$4" release_probe_records "$2" "$3" "$1"
}

LOG="${WORK}/probe-ok.log"
run_probe "$LOG" gmalloc 4242 "${WORK}/jcmd-ok"
assert_eq "ok probe_before line" "probe_before: rss_kb=23456 ${EXP_TOKENS}" "$(sed -n '1p' "${LOG}")"
assert_eq "ok release_probe line" "release_probe=jcmd status=ok" "$(sed -n '2p' "${LOG}")"
assert_eq "ok probe_after line" "probe_after: rss_kb=23456 ${EXP_TOKENS}" "$(sed -n '3p' "${LOG}")"
assert_eq "ok probe writes no mem line" "0" "$(grep -c '^mem:' "${LOG}")"
assert_eq "ok probe writes exactly three records" "3" "$(sed -n '$=' "${LOG}")"

LOG="${WORK}/probe-exit3.log"
run_probe "$LOG" gmalloc 4242 "${WORK}/jcmd-exit3"
assert_eq "non-zero jcmd exit maps to failed" "release_probe=jcmd status=failed" "$(grep -m1 '^release_probe=' "${LOG}")"
assert_eq "non-zero exit still records both rss probes" "2" "$(grep -c '^probe_' "${LOG}")"

LOG="${WORK}/probe-nomatch.log"
run_probe "$LOG" gmalloc 4242 "${WORK}/jcmd-nomatch"
assert_eq "jcmd output without the trim marker maps to failed" "release_probe=jcmd status=failed" "$(grep -m1 '^release_probe=' "${LOG}")"

LOG="${WORK}/probe-timeout.log"
PROBE_TIMEOUT_SECONDS=3
probe_start=$(date +%s)
run_probe "$LOG" gmalloc 4242 "${WORK}/jcmd-slow"
probe_elapsed=$(( $(date +%s) - probe_start ))
PROBE_TIMEOUT_SECONDS=20
assert_eq "a jcmd killed at the timeout maps to failed" "release_probe=jcmd status=failed" "$(grep -m1 '^release_probe=' "${LOG}")"
if [ "${probe_elapsed}" -lt 25 ]; then
  pass "the timeout fired instead of waiting out the stub"
else
  fail_case "the probe waited ${probe_elapsed}s; the timeout did not fire"
fi

LOG="${WORK}/probe-na-rss.log"
write_stat "${PROC}" 4343 java S 1
run_probe "$LOG" gmalloc 4343 "${WORK}/jcmd-ok"
assert_eq "unreadable smaps yields the literal NA" "probe_before: rss_kb=NA ${EXP_TOKENS}" "$(grep -m1 '^probe_before:' "${LOG}")"
assert_eq "unreadable smaps yields NA after the probe too" "probe_after: rss_kb=NA ${EXP_TOKENS}" "$(grep -m1 '^probe_after:' "${LOG}")"

for allocator in jemalloc tcmalloc; do
  LOG="${WORK}/probe-${allocator}.log"
  run_probe "$LOG" "$allocator" 4242 "${WORK}/jcmd-ok"
  assert_eq "${allocator} is not applicable" "release_probe=not-applicable allocator=${allocator}" "$(sed -n '1p' "${LOG}")"
  assert_eq "${allocator} writes exactly one record" "1" "$(sed -n '$=' "${LOG}")"
done

# Without MEM_TREND_JCMD the gate must pick the jcmd that sits next to the
# resolved java binary; the stubs live only in that dir so a bare PATH
# lookup cannot satisfy them.
if [ -n "${MEM_TREND_JCMD:-}" ]; then
  fail_case "MEM_TREND_JCMD leaked out of a scoped case"
else
  pass "MEM_TREND_JCMD stays unset outside its cases"
fi
JDKBIN="${WORK}/jdkbin"
JDKFAIL="${WORK}/jdkfail"
mkdir -p "${JDKBIN}" "${JDKFAIL}"
printf '#!/bin/sh\n: # stub so jcmd resolution finds its sibling\n' > "${JDKBIN}/java"
chmod +x "${JDKBIN}/java"
cat > "${JDKBIN}/jcmd" <<'EOF'
#!/bin/sh
echo "$1:"
echo "Trim native heap: 8 kB trimmed"
EOF
chmod +x "${JDKBIN}/jcmd"
# Sits before JDKBIN on PATH, so a bare `jcmd` lookup stops here and fails
cat > "${JDKFAIL}/jcmd" <<'EOF'
#!/bin/sh
exit 9
EOF
chmod +x "${JDKFAIL}/jcmd"
PATH="${JDKFAIL}:${JDKBIN}:${PATH}"
LOG="${WORK}/probe-default-jcmd.log"
: > "${LOG}"
release_probe_records gmalloc 4242 "${LOG}"
assert_eq "jcmd resolves next to the resolved java by default" "release_probe=jcmd status=ok" "$(grep -m1 '^release_probe=' "${LOG}")"

# --- window close against the real sampler ------------------------------------

CASE="${WORK}/window"
PROC2="${CASE}/proc"
CG2="${CASE}/cgroup"
OUT="${CASE}/out.log"
CTL="${CASE}/.running"
mkdir -p "${CASE}"
build_roots "${PROC2}" "${CG2}"
write_stat "${PROC2}" 700 cotenant R 1
write_stat "${PROC2}" 701 idle S 1
cat > "${CASE}/javawatch" <<'EOF'
#!/bin/sh
trap 'kill "$c" 2>/dev/null' EXIT
sleep 600 &
c=$!
wait $c
EOF
( cd "${CASE}" && exec sh ./javawatch "${CTL}" ) & JPID=$!
write_stat "${PROC2}" "${JPID}" javawatch S 1
write_smaps "${PROC2}" "${JPID}" 34567
: > "${OUT}"
: > "${CTL}"
# the sampler must not be launched by its repo path: the worktree name
# contains "java", which pid discovery would match
ln -sf "${MEMWATCH}" "${CASE}/memsampler.sh"
ln -sf "${STEPS}/collect_markers.sh" "${CASE}/collect_markers.sh"
# shellcheck disable=SC2030  # the override is local to the sampler's subshell
( cd "${CASE}" && export MEMWATCH_PROC_ROOT="${PROC2}" MEMWATCH_CGROUP_ROOT="${CG2}" && exec sh ./memsampler.sh "${CTL}" "${OUT}" ) > "${CASE}/sampler.stdout" 2>&1 & SPID=$!

wait_mem_lines() { # $1 wanted count, $2 timeout seconds
  local count deadline
  deadline=$(( $(date +%s) + $2 ))
  while :; do
    count=$(grep -c '^mem:' "${OUT}" 2>/dev/null)
    count=${count:-0}
    [ "${count}" -ge "$1" ] && return 0
    [ "$(date +%s)" -ge "${deadline}" ] && return 1
    sleep 0.5
  done
}

if wait_mem_lines 1 15; then
  pass "the sampler records the JVM before the window closes"
else
  fail_case "the sampler wrote no mem line before the window closed"
fi

# The sampler's own discovery pipeline, replayed from the test: the fake JVM
# must be its only match, or pid would hold two ids and no sample is recorded.
# shellcheck disable=SC2009  # replays the sampler's discovery pipeline verbatim
discovered=$(ps ax | grep 'java' | grep "${CTL}" | grep -v 'grep' | grep -v 'time' | sed -e 's/^[[:space:]]*//' | cut -f1 -d' ')
assert_eq "pid discovery matches exactly the fake JVM" "${JPID}" "${discovered}"

close_measurement_window 2 "${JPID}" "${SPID}" "${CTL}"
if [ ! -f "${CTL}" ]; then
  pass "the control file is removed when the window ends"
else
  fail_case "the control file survived the window close"
fi
if kill -0 "${SPID}" 2>/dev/null; then
  fail_case "the sampler was not waited for before the probe"
else
  pass "the sampler is waited for before the probe"
fi

MEMWATCH_PROC_ROOT="${PROC2}"
MEMWATCH_CGROUP_ROOT="${CG2}"
MEM_TREND_JCMD="${WORK}/jcmd-ok" release_probe_records gmalloc "${JPID}" "${OUT}"
first_probe=$(grep -n '^probe_before:' "${OUT}" | head -1 | cut -d: -f1)
last_mem=$(grep -n '^mem:' "${OUT}" | tail -1 | cut -d: -f1)
if [ -n "${first_probe}" ] && [ -n "${last_mem}" ] && [ "${last_mem}" -lt "${first_probe}" ]; then
  pass "every mem line precedes the probe"
else
  fail_case "a mem line follows the probe (mem ${last_mem}, probe ${first_probe})"
fi
assert_eq "no mem line is written after the probe" "0" "$(sed -n "${first_probe},\$p" "${OUT}" | grep -c '^mem:')"
assert_eq "the probe reads the JVM rss" "probe_before: rss_kb=34567 ${EXP_TOKENS}" "$(grep -m1 '^probe_before:' "${OUT}")"
assert_eq "the probe succeeds on the stubbed jcmd" "release_probe=jcmd status=ok" "$(grep -m1 '^release_probe=' "${OUT}")"
kill "${JPID}" 2>/dev/null
wait "${JPID}" 2>/dev/null

# --- window closes early when the JVM exits ----------------------------------

CASE2="${WORK}/early"
CTL2="${CASE2}/.running"
OUT2="${CASE2}/out.log"
EMPTY_PROC="${CASE2}/empty"
mkdir -p "${CASE2}" "${EMPTY_PROC}"
: > "${CTL2}"
: > "${OUT2}"
cat > "${CASE2}/javawatch" <<'EOF'
#!/bin/sh
sleep 1
EOF
ln -sf "${MEMWATCH}" "${CASE2}/memsampler.sh"
ln -sf "${STEPS}/collect_markers.sh" "${CASE2}/collect_markers.sh"
( cd "${CASE2}" && exec sh ./javawatch "${CTL2}" ) & JPID2=$!
# shellcheck disable=SC2031  # the override is local to the sampler's subshell
( cd "${CASE2}" && export MEMWATCH_PROC_ROOT="${EMPTY_PROC}" MEMWATCH_CGROUP_ROOT="${EMPTY_PROC}" && exec sh ./memsampler.sh "${CTL2}" "${OUT2}" ) > "${CASE2}/sampler.stdout" 2>&1 & SPID2=$!
early_start=$(date +%s)
close_measurement_window 30 "${JPID2}" "${SPID2}" "${CTL2}"
early_elapsed=$(( $(date +%s) - early_start ))
if [ "${early_elapsed}" -lt 15 ]; then
  pass "an early JVM exit closes the window before the full runtime"
else
  fail_case "the window waited ${early_elapsed}s despite the JVM exiting early"
fi
if [ ! -f "${CTL2}" ]; then
  pass "the control file is removed on early exit"
else
  fail_case "the control file survived an early JVM exit"
fi

# --- verdict mapping on fixture logs ------------------------------------------

if "${PYTHON_BIN}" -c "import numpy, matplotlib" > /dev/null 2>&1; then
  export MPLBACKEND=Agg

  TOKENS="psi_cpu_some_avg10=0.1 psi_memory_some_avg10=0.05 loadavg_1m=1.5 cpu_nr_throttled=4 cotenant_runnable=2"

  growth_series() { # $1 log: 24 rising samples with clean markers
    local v=100000 i
    : > "$1"
    for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24; do
      echo "mem: ${v}" >> "$1"
      echo "markers: ${TOKENS}" >> "$1"
      v=$((v * 105 / 100))
    done
  }

  probe_lines() { # $1 log, $2 before rss, $3 after rss
    {
      echo "probe_before: rss_kb=$2 ${TOKENS}"
      echo "release_probe=jcmd status=ok"
      echo "probe_after: rss_kb=$3 ${TOKENS}"
    } >> "$1"
  }

  run_verdict() { # $1 log, $2 allocator, $3 err file
    : > "$3"
    OUT_TEXT=$(run_trend_check "$1" "${1%.log}.png" "$2" 2> "$3")
  }

  assert_trend_up() { # $1 description
    if printf '%s\n' "${OUT_TEXT}" | grep -q '^TREND:up$'; then
      pass "$1"
    else
      fail_case "$1: no TREND:up line in the check output"
    fi
  }

  assert_gmalloc_fail() { # $1 description, $2 err file
    local line
    line=$(grep -m1 '^FAIL:' "$2")
    case "${line}" in
      "FAIL:Memory usage is trending up"*) pass "$1 starts with the trend text" ;;
      *) fail_case "$1 does not start with the trend text: [${line}]" ;;
    esac
    case "${line}" in
      *thread-arena*) pass "$1 carries the thread-arena caveat" ;;
      *) fail_case "$1 lacks the thread-arena caveat: [${line}]" ;;
    esac
    assert_eq "$1 is a single verdict line" "1" "$(grep -cE '^(FAIL|INCONCLUSIVE):' "$2")"
  }

  LOG="${WORK}/v-fail-gmalloc.log"
  ERR="${WORK}/v-fail-gmalloc.err"
  growth_series "${LOG}"
  probe_lines "${LOG}" 400000 400000
  run_verdict "${LOG}" gmalloc "${ERR}"
  assert_trend_up "a growing series still reports TREND:up"
  assert_gmalloc_fail "a non-reducing gmalloc probe fails" "${ERR}"

  LOG="${WORK}/v-fail-jemalloc.log"
  ERR="${WORK}/v-fail-jemalloc.err"
  growth_series "${LOG}"
  echo "release_probe=not-applicable allocator=jemalloc" >> "${LOG}"
  run_verdict "${LOG}" jemalloc "${ERR}"
  assert_eq "a non-glibc fail line is exact" "FAIL:Memory usage is trending up" "$(grep -m1 '^FAIL:' "${ERR}")"
  assert_eq "a non-glibc fail is a single verdict line" "1" "$(grep -cE '^(FAIL|INCONCLUSIVE):' "${ERR}")"

  LOG="${WORK}/v-pass-gmalloc.log"
  ERR="${WORK}/v-pass-gmalloc.err"
  growth_series "${LOG}"
  probe_lines "${LOG}" 400000 250000
  run_verdict "${LOG}" gmalloc "${ERR}"
  assert_eq "grow-then-release emits no verdict line" "0" "$(grep -cE '^(FAIL|INCONCLUSIVE):' "${ERR}")"
  assert_trend_up "grow-then-release still reports the trend"

  LOG="${WORK}/v-growth-zero.log"
  ERR="${WORK}/v-growth-zero.err"
  growth_series "${LOG}"
  probe_lines "${LOG}" 100000 90000
  run_verdict "${LOG}" gmalloc "${ERR}"
  assert_gmalloc_fail "zero growth_kb with TREND:up still fails" "${ERR}"

  LOG="${WORK}/v-short.log"
  ERR="${WORK}/v-short.err"
  : > "${LOG}"
  for i in 1 2 3 4; do
    echo "mem: $((100000 + i))" >> "${LOG}"
    echo "markers: ${TOKENS}" >> "${LOG}"
  done
  run_verdict "${LOG}" gmalloc "${ERR}"
  assert_eq "an inconclusive reason is relayed verbatim" \
    "INCONCLUSIVE:Only 4 memory samples were recorded, at least 5 are needed" \
    "$(grep -m1 '^INCONCLUSIVE:' "${ERR}")"
  assert_eq "an inconclusive verdict is a single line" "1" "$(grep -cE '^(FAIL|INCONCLUSIVE):' "${ERR}")"

  NOOUT="${WORK}/noout"
  mkdir -p "${NOOUT}"
  printf '#!/bin/sh\nexit 0\n' > "${NOOUT}/python3"
  chmod +x "${NOOUT}/python3"
  ERR="${WORK}/v-noverdict.err"
  : > "${ERR}"
  saved_path="${PATH}"
  PATH="${NOOUT}:${PATH}"
  run_trend_check "${WORK}/v-short.log" "${NOOUT}/trend.png" gmalloc 2> "${ERR}"
  PATH="${saved_path}"
  assert_eq "a missing verdict maps to inconclusive" \
    "INCONCLUSIVE:trend check produced no verdict" \
    "$(grep -m1 '^INCONCLUSIVE:' "${ERR}")"
  assert_eq "a missing verdict is a single line" "1" "$(grep -cE '^(FAIL|INCONCLUSIVE):' "${ERR}")"
else
  fail_case "${PYTHON_BIN} cannot import numpy and matplotlib; the verdict mapping tests need both"
fi

if [ "${FAILED}" -eq 0 ]; then
  echo "All memory probe tests passed"
  exit 0
fi
echo "memory probe tests failed"
exit 1
