#! /bin/bash
# Copyright 2026, Datadog, Inc.
#
# Network-free tests for the memory sampler's load markers. The sampler is
# driven against fake proc and cgroup trees through MEMWATCH_PROC_ROOT and
# MEMWATCH_CGROUP_ROOT; the pid it discovers is a helper process whose
# command line carries the control-file name, as the production JVM does.
# Run with: bash .gitlab/reliability/tests/mem_watch_markers_test.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
STEPS="${HERE}/../../benchmarks/steps"

FAILED=0
WORK=$(mktemp -d)
JPID=
SPID=
XPID=
CTL=".running"

# shellcheck disable=SC2329  # cleanup runs through the EXIT trap
cleanup() {
  kill "${JPID:-}" "${SPID:-}" "${XPID:-}" 2>/dev/null
  rm -rf "$WORK"
}
trap cleanup EXIT

# pid discovery drops lines containing 'grep' or 'time', so the temp tree
# must not contain either string
case "$WORK" in
  *time*|*grep*)
    echo "FAIL: temp dir path is excluded by pid discovery: $WORK"
    exit 1
    ;;
esac

pass() { echo "PASS: $1"; }
fail() { echo "FAIL: $1"; FAILED=1; }

assert_eq() { # $1 what, $2 expected, $3 actual
  if [ "$2" = "$3" ]; then
    pass "$1"
  else
    fail "$1: expected [$2] got [$3]"
  fi
}

write_stat() { # $1 proc root, $2 pid, $3 comm, $4 state, $5 ppid
  mkdir -p "$1/$2"
  printf '%s (%s) %s %s 1 1 1 0 -1 0\n' "$2" "$3" "$4" "$5" > "$1/$2/stat"
}

write_smaps() { # $1 proc root, $2 pid, $3 rss kB
  mkdir -p "$1/$2"
  printf 'Rss:        %s kB\n' "$3" > "$1/$2/smaps_rollup"
}

start_fake_java() {
  cat > "$WORK/javawatch" <<'EOF'
#!/bin/sh
trap 'kill "$c" 2>/dev/null' EXIT
sleep 600 &
c=$!
wait $c
EOF
  ( cd "$WORK" && exec sh ./javawatch "$CTL" ) & JPID=$!
}

# A sibling whose command line carries the same discovery tokens as the
# fake JVM, so the ps text match alone cannot tell them apart.
start_fake_sibling() {
  cat > "$WORK/javasibling" <<'EOF'
#!/bin/sh
trap 'kill "$c" 2>/dev/null' EXIT
sleep 600 &
c=$!
wait $c
EOF
  ( cd "$WORK" && exec sh ./javasibling "$CTL" ) & XPID=$!
}

start_sampler() { # $1 = shell to run the sampler with
  mkdir -p "$CASE_DIR"
  ln -sf "$STEPS/mem_watch.sh" "$CASE_DIR/memsampler.sh"
  ln -sf "$STEPS/collect_markers.sh" "$CASE_DIR/collect_markers.sh"
  : > "$OUT"
  : > "$CASE_DIR/$CTL"
  : > "$CASE_DIR/sampler.stdout"
  (
    cd "$CASE_DIR" || exit 1
    # shellcheck disable=SC2030  # the roots are local to the sampler's subshell
    export MEMWATCH_PROC_ROOT="$PROC" MEMWATCH_CGROUP_ROOT="$CG"
    exec "$1" ./memsampler.sh "$CTL" out.log
  ) > "$CASE_DIR/sampler.stdout" 2>&1 & SPID=$!
}

wait_markers() { # $1 = markers records to wait for; 25 s timeout
  local count deadline
  deadline=$(( $(date +%s) + 25 ))
  while :; do
    count=$(grep -c '^markers:' "$OUT" 2>/dev/null)
    count=${count:-0}
    [ "$count" -ge "$1" ] && return 0
    if [ "$(date +%s)" -ge "$deadline" ]; then
      return 1
    fi
    sleep 0.2
  done
}

stop_sampler() {
  rm -f "$CASE_DIR/$CTL"
  wait "$SPID" 2>/dev/null
  kill "${JPID:-}" 2>/dev/null
  wait "${JPID:-}" 2>/dev/null
}

line_n() { # $1 = 1-based line number of the sampler output
  sed -n "$1p" "$OUT"
}

no_markers() { # $1 = case name
  fail "$1: no markers record was written"
  sed -n '1,10p' "$CASE_DIR/sampler.stdout" 2>/dev/null
  stop_sampler
}

case_v2() {
  CASE_DIR="$WORK/v2"; PROC="$WORK/v2/proc"; CG="$WORK/v2/cgroup"
  OUT="$CASE_DIR/out.log"
  mkdir -p "$PROC/pressure" "$CG"
  printf 'some avg10=1.25 avg60=2.50 avg300=3.75 total=123\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$PROC/pressure/cpu"
  printf 'some avg10=4.75 avg60=5.00 avg300=5.25 total=500\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$PROC/pressure/memory"
  printf '0.52 0.58 0.59 1/500 12345\n' > "$PROC/loadavg"
  printf 'cpu io memory\n' > "$CG/cgroup.controllers"
  printf 'usage_usec 1000\nnr_periods 100\nnr_throttled 42\nthrottled_usec 0\n' > "$CG/cpu.stat"
  start_fake_java
  write_stat "$PROC" "$JPID" javawatch R 1
  write_stat "$PROC" 901 cotenant R 1
  write_stat "$PROC" 902 cotenant R 1
  write_stat "$PROC" 903 sleeper S 1
  write_smaps "$PROC" "$JPID" 12345
  start_sampler sh
  wait_markers 1 || { no_markers v2; return; }
  # changed sources between ticks prove each markers record is read in the
  # same tick as the mem record that precedes it
  printf '1.75 1.80 1.85 2/600 999\n' > "$PROC/loadavg"
  printf 'usage_usec 2000\nnr_periods 200\nnr_throttled 43\nthrottled_usec 0\n' > "$CG/cpu.stat"
  write_smaps "$PROC" "$JPID" 13000
  write_stat "$PROC" 905 samplerchild R "$SPID"
  write_stat "$PROC" 906 otherchild R 424242
  # grandchildren of the sampler (as the census's own cat|awk collectors are,
  # through the command-substitution subshell) must not be counted: the
  # exclusion walks the ancestor chain, not just the direct parent
  write_stat "$PROC" 907 collector R 905
  write_stat "$PROC" 908 collector2 R 907
  wait_markers 2 || { no_markers v2; return; }
  stop_sampler
  assert_eq "v2 mem line format" "mem: 12345" "$(line_n 1)"
  assert_eq "v2 tick1 markers (JVM pid excluded from census)" \
    "markers: psi_cpu_some_avg10=1.25 psi_memory_some_avg10=4.75 loadavg_1m=0.52 cpu_nr_throttled=42 cotenant_runnable=2" \
    "$(line_n 2)"
  assert_eq "v2 tick2 mem line" "mem: 13000" "$(line_n 3)"
  assert_eq "v2 tick2 markers (same tick, sampler descendants excluded, foreign child counted)" \
    "markers: psi_cpu_some_avg10=1.25 psi_memory_some_avg10=4.75 loadavg_1m=1.75 cpu_nr_throttled=43 cotenant_runnable=3" \
    "$(line_n 4)"
  assert_eq "v2 mem record count" 2 "$(grep -c '^mem:' "$OUT")"
  assert_eq "v2 markers record count" 2 "$(grep -c '^markers:' "$OUT")"
  assert_eq "v2 no other output lines" 4 "$(sed -n '$=' "$OUT")"
}

case_v1() {
  CASE_DIR="$WORK/v1"; PROC="$WORK/v1/proc"; CG="$WORK/v1/cgroup"
  OUT="$CASE_DIR/out.log"
  mkdir -p "$PROC/pressure" "$CG/cpu,cpuacct" "$CG/cpu"
  printf 'some avg10=2.25 avg60=2.00 avg300=1.75 total=10\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$PROC/pressure/cpu"
  printf 'some avg10=3.50 avg60=3.00 avg300=2.50 total=20\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$PROC/pressure/memory"
  printf '1.10 1.20 1.30 2/300 777\n' > "$PROC/loadavg"
  printf 'nr_periods 50\nnr_throttled 7\nthrottled_time 0\n' > "$CG/cpu,cpuacct/cpu.stat"
  printf 'nr_periods 60\nnr_throttled 9\nthrottled_time 0\n' > "$CG/cpu/cpu.stat"
  start_fake_java
  write_stat "$PROC" "$JPID" javawatch R 1
  write_stat "$PROC" 510 cotenant R 1
  write_stat "$PROC" 511 idle S 1
  write_smaps "$PROC" "$JPID" 23456
  start_sampler sh
  wait_markers 1 || { no_markers v1; return; }
  rm -rf "$CG/cpu,cpuacct"
  wait_markers 2 || { no_markers v1; return; }
  stop_sampler
  assert_eq "v1 mem line format" "mem: 23456" "$(line_n 1)"
  assert_eq "v1 tick1 markers (cpu,cpuacct root preferred)" \
    "markers: psi_cpu_some_avg10=2.25 psi_memory_some_avg10=3.50 loadavg_1m=1.10 cpu_nr_throttled=7 cotenant_runnable=1" \
    "$(line_n 2)"
  assert_eq "v1 tick2 markers (fallback to cpu root)" \
    "markers: psi_cpu_some_avg10=2.25 psi_memory_some_avg10=3.50 loadavg_1m=1.10 cpu_nr_throttled=9 cotenant_runnable=1" \
    "$(line_n 4)"
  assert_eq "v1 one markers record per mem record" \
    "$(grep -c '^mem:' "$OUT")" "$(grep -c '^markers:' "$OUT")"
}

case_missing() {
  CASE_DIR="$WORK/missing"; PROC="$WORK/missing/proc"; CG="$WORK/missing/cgroup"
  OUT="$CASE_DIR/out.log"
  mkdir -p "$PROC" "$CG"
  printf '0.25 0.35 0.45 3/400 555\n' > "$PROC/loadavg"
  printf 'cpu\n' > "$CG/cgroup.controllers"
  printf 'nr_periods 80\nnr_throttled 4\nthrottled_usec 0\n' > "$CG/cpu.stat"
  start_fake_java
  write_stat "$PROC" "$JPID" javawatch R 1
  write_stat "$PROC" 610 cotenant R 1
  write_stat "$PROC" 611 idle S 1
  write_smaps "$PROC" "$JPID" 34567
  start_sampler "$POSIX_SH"
  wait_markers 1 || { no_markers missing; return; }
  rm -rf "$CG"
  rm -f "$PROC/loadavg"
  wait_markers 2 || { no_markers missing; return; }
  stop_sampler
  assert_eq "missing tick1 markers (PSI files absent yield NA)" \
    "markers: psi_cpu_some_avg10=NA psi_memory_some_avg10=NA loadavg_1m=0.25 cpu_nr_throttled=4 cotenant_runnable=1" \
    "$(line_n 2)"
  assert_eq "missing tick2 markers (cgroup and loadavg absent yield NA)" \
    "markers: psi_cpu_some_avg10=NA psi_memory_some_avg10=NA loadavg_1m=NA cpu_nr_throttled=NA cotenant_runnable=1" \
    "$(line_n 4)"
  assert_eq "missing mem line format" "mem: 34567" "$(line_n 1)"
}

POSIX_SH='sh'
if [ -x /bin/dash ]; then
  POSIX_SH=/bin/dash
fi

# A cgroup root that exists but holds no cpu.stat at any known mount: the
# sampler must emit NA for the throttle token, not read its stdin through
# an empty sed filename.
case_no_stat() {
  CASE_DIR="$WORK/nostat"; PROC="$WORK/nostat/proc"; CG="$WORK/nostat/cgroup"
  OUT="$CASE_DIR/out.log"
  mkdir -p "$PROC" "$CG"
  printf '0.25 0.35 0.45 3/400 555\n' > "$PROC/loadavg"
  start_fake_java
  write_stat "$PROC" "$JPID" javawatch R 1
  write_stat "$PROC" 610 cotenant R 1
  write_smaps "$PROC" "$JPID" 34567
  start_sampler "$POSIX_SH"
  wait_markers 1 || { no_markers nostat; return; }
  stop_sampler
  assert_eq "no-stat markers yield NA for the throttle token" \
    "markers: psi_cpu_some_avg10=NA psi_memory_some_avg10=NA loadavg_1m=0.25 cpu_nr_throttled=NA cotenant_runnable=1" \
    "$(line_n 2)"
  assert_eq "no-stat mem line format" "mem: 34567" "$(line_n 1)"
}

case_v2
case_v1
case_missing
case_no_stat

# MEMWATCH_TARGET_PID selects the launched JVM even when a sibling matches
# the ps text discovery; unset, the discovery loop runs unchanged (the
# cases above never set the override).
case_override() {
  CASE_DIR="$WORK/override"; PROC="$WORK/override/proc"; CG="$WORK/override/cgroup"
  OUT="$CASE_DIR/out.log"
  mkdir -p "$PROC/pressure" "$CG"
  printf 'some avg10=0.50 avg60=0.50 avg300=0.50 total=10\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$PROC/pressure/cpu"
  printf 'some avg10=0.75 avg60=0.75 avg300=0.75 total=20\nfull avg10=0.00 avg60=0.00 avg300=0.00 total=0\n' > "$PROC/pressure/memory"
  printf '0.40 0.41 0.42 1/100 111\n' > "$PROC/loadavg"
  printf 'cpu io memory\n' > "$CG/cgroup.controllers"
  printf 'usage_usec 1\nnr_periods 10\nnr_throttled 1\nthrottled_usec 0\n' > "$CG/cpu.stat"
  start_fake_java
  start_fake_sibling
  write_stat "$PROC" "$JPID" javawatch R 1
  write_stat "$PROC" "$XPID" javasibling R 1
  write_smaps "$PROC" "$JPID" 12345
  write_smaps "$PROC" "$XPID" 54321
  # shellcheck disable=SC2009  # replays the sampler's discovery pipeline verbatim
  discovered=$(ps ax | grep 'java' | grep "$CTL" | grep -v 'grep' | grep -v 'time' | sed -e 's/^[[:space:]]*//' | cut -f1 -d' ')
  if printf '%s\n' "$discovered" | grep -qx "$JPID" && printf '%s\n' "$discovered" | grep -qx "$XPID"; then
    pass "the fixture's discovery matches both the JVM and the sibling"
  else
    fail "override: discovery does not see both processes [$discovered]"
  fi
  mkdir -p "$CASE_DIR"
  ln -sf "$STEPS/mem_watch.sh" "$CASE_DIR/memsampler.sh"
  ln -sf "$STEPS/collect_markers.sh" "$CASE_DIR/collect_markers.sh"
  : > "$OUT"
  : > "$CASE_DIR/$CTL"
  : > "$CASE_DIR/sampler.stdout"
  (
    cd "$CASE_DIR" || exit 1
    # shellcheck disable=SC2031  # the roots and override are local to the sampler's subshell
    export MEMWATCH_PROC_ROOT="$PROC" MEMWATCH_CGROUP_ROOT="$CG"
    export MEMWATCH_TARGET_PID="$JPID"
    exec sh ./memsampler.sh "$CTL" out.log
  ) > "$CASE_DIR/sampler.stdout" 2>&1 & SPID=$!
  if ! wait_markers 1; then
    fail "override: no markers record was written"
    sed -n '1,10p' "$CASE_DIR/sampler.stdout" 2>/dev/null
  fi
  stop_sampler
  kill "$XPID" 2>/dev/null
  wait "$XPID" 2>/dev/null
  assert_eq "override mem line reads the target JVM rss" "mem: 12345" "$(line_n 1)"
  assert_eq "override markers exclude the target JVM from the census" \
    "markers: psi_cpu_some_avg10=0.50 psi_memory_some_avg10=0.75 loadavg_1m=0.40 cpu_nr_throttled=1 cotenant_runnable=1" \
    "$(line_n 2)"
}

case_override

# Direct helper call against a nonexistent proc root: every source is
# unavailable, so no token may fall back to 0 or empty
# shellcheck disable=SC2016  # $1/$2 are sh -c positional args, not expansions
absent=$(cd "$STEPS" && "$POSIX_SH" -c '. ./collect_markers.sh; collect_markers "$1" "$2" 1 2' sh "$WORK/noroot" "$WORK/noroot")
assert_eq "absent roots yield NA in every token" \
  "psi_cpu_some_avg10=NA psi_memory_some_avg10=NA loadavg_1m=NA cpu_nr_throttled=NA cotenant_runnable=NA" \
  "$absent"

# A pid whose stat entry cannot be opened must not kill the census: cat
# skips it and the count still covers the readable entries. The unreadable
# entry is a stat-shaped directory, so open fails with EISDIR for every uid,
# root included. Read directly through the helper; the sampler replays it.
UNREADABLE="$WORK/unreadable"
mkdir -p "$UNREADABLE/801" "$UNREADABLE/802" "$UNREADABLE/803" "$UNREADABLE/804"
printf '801 (cotenant) R 1 1 1 1 0 -1 0\n' > "$UNREADABLE/801/stat"
printf '802 (idle) S 1 1 1 1 0 -1 0\n' > "$UNREADABLE/802/stat"
printf '804 (cotenant) R 1 1 1 1 0 -1 0\n' > "$UNREADABLE/804/stat"
mkdir "$UNREADABLE/803/stat"
UNRE_ERR="$WORK/unreadable.err"
: > "$UNRE_ERR"
# shellcheck disable=SC2016  # $1 is a sh -c positional arg, not an expansion
unre=$(cd "$STEPS" && "$POSIX_SH" -c '. ./collect_markers.sh; markers_cotenant_runnable "$1" 999' sh "$UNREADABLE" 2> "$UNRE_ERR")
assert_eq "an unreadable stat entry does not zero the census" "2" "$unre"
if [ ! -s "$UNRE_ERR" ]; then
  pass "the unreadable entry leaves the census stderr empty"
else
  fail "the census leaked stderr for the unreadable entry: $(cat "$UNRE_ERR")"
fi

# A ppid cycle (pid reuse can pair two entries) must not hang the census:
# the ancestor walk is step-bounded and counts the unresolvable entries.
# The direct call runs under a poll watchdog; a hang fails the case.
CYCLE="$WORK/cycle"
CYC_OUT="$WORK/cycle.out"
mkdir -p "$CYCLE/960" "$CYCLE/961"
printf '960 (cotenant) R 961 1 1 1 0 -1 0\n' > "$CYCLE/960/stat"
printf '961 (cotenant) R 960 1 1 1 0 -1 0\n' > "$CYCLE/961/stat"
# shellcheck disable=SC2016  # $1 is a sh -c positional arg, not an expansion
(cd "$STEPS" && "$POSIX_SH" -c '. ./collect_markers.sh; markers_cotenant_runnable "$1" 999' sh "$CYCLE" > "$CYC_OUT" 2>/dev/null) &
CYC_PID=$!
CYC_TICKS=0
# integer sleep: POSIX sh (musl/Alpine) rejects fractional operands
while kill -0 "$CYC_PID" 2>/dev/null && [ "$CYC_TICKS" -lt 10 ]; do
  sleep 1
  CYC_TICKS=$((CYC_TICKS + 1))
done
if kill -0 "$CYC_PID" 2>/dev/null; then
  kill -9 "$CYC_PID"
  fail "the census hung on a ppid cycle (watchdog kill after 10s)"
else
  wait "$CYC_PID"
  assert_eq "a ppid cycle terminates and counts both entries" "2" "$(cat "$CYC_OUT")"
fi

if [ "$FAILED" -eq 0 ]; then
  echo "All mem_watch markers tests passed"
  exit 0
fi
echo "mem_watch markers tests failed"
exit 1
