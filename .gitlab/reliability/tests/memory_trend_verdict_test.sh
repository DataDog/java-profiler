#! /bin/bash
# Copyright 2026, Datadog, Inc.
# Fixture tests for the pass/fail/inconclusive verdict in
# .gitlab/reliability/memory_trend_check.py, plus a byte-compatibility proof
# that the pre-allocator output is unchanged.
# Run with: bash .gitlab/reliability/tests/memory_trend_verdict_test.sh
# PYTHON_BIN can point at an interpreter that has numpy and matplotlib.

# shellcheck disable=SC2317  # the run_* helpers are invoked via expect_* helpers

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${SCRIPT:-${HERE}/../memory_trend_check.py}"
PYTHON_BIN="${PYTHON_BIN:-python3}"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

pass() { echo "PASS: $1"; }
fail_case() {
  echo "FAIL: $1"
  [ -f "${WORK}/run/stdout" ] && sed 's/^/      /' "${WORK}/run/stdout"
  [ -f "${WORK}/run/stderr" ] && sed 's/^/      /' "${WORK}/run/stderr" | tail -5
  FAILED=1
}

if ! "${PYTHON_BIN}" -c "import numpy, matplotlib" > /dev/null 2>&1; then
  echo "FAIL: ${PYTHON_BIN} cannot import numpy and matplotlib; the verdict tests need both"
  exit 1
fi

# Recorded pre-change stdout for a growth and for a flat series; the
# post-change script must keep producing these bytes, with and without
# --allocator.
EXPECTED_GROWTH_STDOUT=$(cat <<'EOF'
Arguments:  Namespace(filename='memwatch.log', plot=False, output='trend.png')
Persistent and significant memory growth detected.
TREND:up
Plotting memory log to trend.png
EOF
)
EXPECTED_FLAT_STDOUT=$(cat <<'EOF'
Arguments:  Namespace(filename='memwatch.log', plot=False, output='trend.png')
No persistent and significant memory growth detected.
Plotting memory log to trend.png
EOF
)

# --- fixtures ----------------------------------------------------------------

# Every verdict fixture is generated here: a growth series rises 5% per
# sample, so every sliding window grows and the series is a reliable TREND:up.
"${PYTHON_BIN}" - "${WORK}" <<'PYEOF'
import sys

work = sys.argv[1]


def growth(count, start=100000):
    values, v = [], start
    for _ in range(count):
        values.append(v)
        v = v * 105 // 100
    return values


def markers(psi_cpu="0.1", psi_mem="0.05", throttled="4"):
    return (f"markers: psi_cpu_some_avg10={psi_cpu} psi_memory_some_avg10={psi_mem} "
            f"loadavg_1m=1.5 cpu_nr_throttled={throttled} cotenant_runnable=2")


def emit(values, psi_cpu="0.1", psi_mem="0.05", throttled="4", na_psi=0, na_thr=0, missing=()):
    lines = []
    for i, v in enumerate(values):
        lines.append(f"mem: {v}")
        if i in missing:
            continue
        p = "NA" if i < na_psi else psi_mem
        t = "NA" if i < na_thr else throttled
        lines.append(markers(psi_cpu, p, t))
    return lines


def write(name, lines):
    with open(f"{work}/{name}", "w") as f:
        f.write("\n".join(lines) + "\n")


def probe(before, after, status="ok"):
    return [f"probe_before: rss_kb={before} {markers()}",
            f"release_probe=jcmd status={status}",
            f"probe_after: rss_kb={after} {markers()}"]


g24, g10, flat = growth(24), growth(10), [500000] * 24

# Byte-compatibility fixtures: current format, and the same series with
# markers and probe records interleaved.
write("plain-growth.log", [f"mem: {v}" for v in g24])
write("plain-flat.log", [f"mem: {v}" for v in flat])
interleaved = []
for v in g24:
    interleaved.append(f"mem: {v}")
    interleaved.append(markers())
# Released equals half the growth, so this is also the at-bound release pass.
write("interleaved.log", interleaved + probe(400000, 250000))

# Fewer than 5 samples.
write("short.log", emit(growth(4)))

# Exact window boundary: 5 samples reach the trend window, 4 stay short.
write("boundary-5.log", emit(growth(5)) + ["release_probe=not-applicable allocator=jemalloc"])
write("boundary-4.log", emit(growth(4)))

# NA share: exactly half the samples lack a markers record, and more than
# half carry NA in either gated field.
write("na-at.log", emit(g10, missing=range(0, 10, 2)) + ["release_probe=not-applicable allocator=jemalloc"])
write("na-above-psi.log", emit(g10, na_psi=6))
write("na-above-throttle.log", emit(g10, na_thr=6))

# psi_memory median, exactly at the bound and one step past it; psi_cpu is
# recorded only, so a high psi_cpu never turns a quiet row inconclusive.
write("psi-at.log", emit(g24, psi_mem="5.0") + ["release_probe=not-applicable allocator=jemalloc"])
write("psi-above.log", emit(g24, psi_mem="5.5"))
write("psi-cpu-high.log", emit(flat, psi_cpu="40.0", psi_mem="0.0") + ["release_probe=not-applicable allocator=jemalloc"])
thr_at = emit(g24)
thr_at[-1] = markers("0.1", "0.05", "12")
write("throttle-at.log", thr_at + ["release_probe=not-applicable allocator=jemalloc"])
thr_above = emit(g24)
thr_above[-1] = markers("0.1", "0.05", "13")
write("throttle-above.log", thr_above)

# gmalloc probe shape: missing, failed, and NA RSS on either probe record.
write("probe-missing.log", emit(g24))
write("probe-failed.log", emit(g24) + ["release_probe=jcmd status=failed"])
write("probe-na-before.log", emit(g24) + probe("NA", 120000))
write("probe-na-after.log", emit(g24) + probe(160000, "NA"))

# Growth verdicts for gmalloc and the non-glibc rows.
write("grow-jemalloc.log", emit(g24) + ["release_probe=not-applicable allocator=jemalloc"])
write("flat-jemalloc.log", emit(flat) + ["release_probe=not-applicable allocator=jemalloc"])
write("flat-tcmalloc.log", emit(flat) + ["release_probe=not-applicable allocator=tcmalloc"])
write("flat-gmalloc.log", emit(flat) + probe(500000, 480000))

# Release recovery, exactly at the share and one kB short of it, plus the
# growth_kb bounds: zero, negative, and one kB past zero.
write("release-at.log", emit(g24) + probe(160000, 130000))
write("release-below.log", emit(g24) + probe(160000, 130001))
write("growth-zero.log", emit(g24) + probe(100000, 90000))
write("growth-negative.log", emit(g24) + probe(90000, 80000))
write("growth-one.log", emit(g24) + probe(100001, 100000))
PYEOF

# --- runner and assertions ---------------------------------------------------

RUN_RC=0
run_out() { # log-file [allocator]
  mkdir -p "${WORK}/run"
  cp "${WORK}/$1" "${WORK}/run/memwatch.log"
  rm -f "${WORK}/run/trend.png"
  local args=()
  if [ "$#" -ge 2 ]; then args=(--allocator "$2"); fi
  ( cd "${WORK}/run" && MPLBACKEND=Agg "${PYTHON_BIN}" "${SCRIPT}" --output trend.png \
      ${args[@]+"${args[@]}"} memwatch.log > stdout 2> stderr )
  RUN_RC=$?
}

verdict() { grep -m1 '^VERDICT:' "${WORK}/run/stdout" | cut -f2 -d':'; }
reason() { grep -m1 '^VERDICT_REASON:' "${WORK}/run/stdout" | sed 's/^VERDICT_REASON://'; }

expect_verdict() { # description expected-verdict log-file allocator
  local desc=$1 expected=$2
  run_out "$3" "$4"
  if [ "${RUN_RC}" -ne 0 ]; then
    fail_case "${desc} — the check exited ${RUN_RC}"
    return
  fi
  if [ "$(verdict)" = "${expected}" ]; then
    pass "${desc}"
  else
    fail_case "${desc} — expected verdict ${expected}, got '$(verdict)'"
    return
  fi
  local why
  why=$(reason)
  case "${why}" in
    *:*) fail_case "${desc} — reason contains a colon" ;;
    *'`'*) fail_case "${desc} — reason contains a backtick" ;;
    "") fail_case "${desc} — reason is empty" ;;
  esac
}

expect_trend_up() { # description
  if grep -q '^TREND:up$' "${WORK}/run/stdout"; then
    pass "$1"
  else
    fail_case "$1 — no TREND:up line in the output"
  fi
}

expect_no_trend() { # description
  if grep -q '^TREND:' "${WORK}/run/stdout"; then
    fail_case "$1 — a TREND line was printed"
  else
    pass "$1"
  fi
}

expect_reason() { # description substring
  if grep -qF "$2" <(reason); then
    pass "$1"
  else
    fail_case "$1 — reason '$(reason)' does not contain '$2'"
  fi
}

expect_reason_is() { # description exact-text
  if [ "$(reason)" = "$2" ]; then
    pass "$1"
  else
    fail_case "$1 — reason is '$(reason)', expected '$2'"
  fi
}

expect_gmalloc_fail_reason() { # description
  local why
  why=$(reason)
  if [[ "${why}" == "Memory usage is trending up"* ]] && [[ "${why}" == *"thread-arena"* ]]; then
    pass "$1"
  else
    fail_case "$1 — reason '$(reason)' does not start with the trend text or carry the caveat"
  fi
}

expect_stdout_is() { # description expected-text-file
  # Verdict lines are additive, so they are stripped before the comparison.
  grep -v '^VERDICT' "${WORK}/run/stdout" > "${WORK}/run/stripped"
  if diff -u "$2" "${WORK}/run/stripped" > "${WORK}/run/diff" 2>&1; then
    pass "$1"
  else
    fail_case "$1 — output differs from the recorded expectation"
    sed 's/^/      /' "${WORK}/run/diff"
  fi
}

printf '%s\n' "${EXPECTED_GROWTH_STDOUT}" > "${WORK}/expected-growth"
printf '%s\n' "${EXPECTED_FLAT_STDOUT}" > "${WORK}/expected-flat"

# --- byte compatibility ------------------------------------------------------

run_out plain-growth.log
expect_stdout_is "growth log without --allocator is byte-identical" "${WORK}/expected-growth"

run_out plain-growth.log jemalloc
expect_stdout_is "growth log with --allocator keeps the TREND output" "${WORK}/expected-growth"
expect_trend_up "growth log with --allocator still reports TREND:up"

run_out plain-flat.log
expect_stdout_is "flat log without --allocator is byte-identical" "${WORK}/expected-flat"

run_out plain-flat.log tcmalloc
expect_stdout_is "flat log with --allocator keeps the TREND output" "${WORK}/expected-flat"

run_out interleaved.log
expect_stdout_is "interleaved log without --allocator is byte-identical" "${WORK}/expected-growth"

run_out interleaved.log gmalloc
expect_stdout_is "interleaved log with --allocator keeps the TREND output" "${WORK}/expected-growth"

# The markers and probe records must not change the parsed RSS series.
if "${PYTHON_BIN}" - "${SCRIPT}" "${WORK}/plain-growth.log" "${WORK}/interleaved.log" <<'PYEOF'
import importlib.util, sys
spec = importlib.util.spec_from_file_location("memory_trend_check", sys.argv[1])
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
plain = module.read_memory_log(sys.argv[2])
interleaved = module.read_memory_log(sys.argv[3])
sys.exit(0 if plain == interleaved and len(plain) == 24 else 1)
PYEOF
then
  pass "interleaved log parses to the identical RSS series"
else
  fail_case "interleaved log parses to a different RSS series"
fi

# --- verdict rules and boundaries ---------------------------------------------

expect_verdict "fewer than 5 samples is inconclusive" inconclusive short.log gmalloc
expect_no_trend "fewer than 5 samples prints no TREND line"

expect_verdict "exactly window_size samples still get a trend verdict" fail boundary-5.log jemalloc
expect_reason_is "window-size fail reason is the trend text" "Memory usage is trending up"
expect_trend_up "exactly window_size samples run the trend window"
expect_verdict "one sample below window_size stays inconclusive" inconclusive boundary-4.log gmalloc
expect_reason_is "the short-window reason names the sample count" "Only 4 memory samples were recorded, at least 5 are needed"

expect_verdict "NA share at the bound still gets a verdict" fail na-at.log jemalloc
expect_reason_is "NA share at the bound is not an NA verdict" "Memory usage is trending up"
expect_verdict "NA share above the bound is inconclusive (NA psi_memory)" inconclusive na-above-psi.log gmalloc
expect_reason "NA share above the bound names the count" "missing for 6 of 10"
expect_verdict "NA share above the bound is inconclusive (NA throttle)" inconclusive na-above-throttle.log gmalloc

expect_verdict "psi_memory median at the bound still gets a verdict" fail psi-at.log jemalloc
expect_verdict "psi_memory median above the bound is inconclusive" inconclusive psi-above.log gmalloc
expect_reason "psi_memory verdict names the median" "Median host memory pressure 5.5"
expect_verdict "high psi_cpu with quiet memory pressure still passes" pass psi-cpu-high.log jemalloc

expect_verdict "throttle delta at the bound still gets a verdict" fail throttle-at.log jemalloc
expect_verdict "throttle delta above the bound is inconclusive" inconclusive throttle-above.log gmalloc
expect_reason "throttle verdict names the delta" "rose by 9 events"

expect_verdict "missing probe record is inconclusive" inconclusive probe-missing.log gmalloc
expect_reason "missing probe verdict names the probe" "No jcmd release probe record"
expect_verdict "failed probe status is inconclusive" inconclusive probe-failed.log gmalloc
expect_reason "failed probe verdict names the status" "reported status failed"
expect_verdict "NA rss on the before probe is inconclusive" inconclusive probe-na-before.log gmalloc
expect_verdict "NA rss on the after probe is inconclusive" inconclusive probe-na-after.log gmalloc
expect_reason "NA rss verdict names the cause" "did not record a usable RSS value"

expect_verdict "non-glibc growth fails" fail grow-jemalloc.log jemalloc
expect_reason_is "non-glibc fail reason is exact" "Memory usage is trending up"
expect_verdict "jemalloc flat passes" pass flat-jemalloc.log jemalloc
expect_verdict "tcmalloc flat passes" pass flat-tcmalloc.log tcmalloc
expect_verdict "gmalloc flat with a healthy probe passes" pass flat-gmalloc.log gmalloc

expect_verdict "grow-then-release at the recovery share passes" pass release-at.log gmalloc
expect_reason "release pass reason says the probe released the growth" "released 30000 kB of the 60000 kB growth"
expect_verdict "grow-then-release just below the share fails" fail release-below.log gmalloc
expect_gmalloc_fail_reason "unreleased growth carries the caveat"

expect_verdict "growth_kb of zero still fails" fail growth-zero.log gmalloc
expect_gmalloc_fail_reason "growth_kb of zero carries the caveat"
expect_verdict "negative growth_kb still fails" fail growth-negative.log gmalloc
expect_verdict "growth_kb of one kB passes when released" pass growth-one.log gmalloc

expect_verdict "interleaved grow-then-release passes" pass interleaved.log gmalloc

# --- constants and forbidden inputs -------------------------------------------

if "${PYTHON_BIN}" - "${SCRIPT}" <<'PYEOF'
import sys
names = ["NA_SHARE_MAX", "PSI_MEMORY_SOME_AVG10_MAX", "THROTTLE_EVENTS_MAX", "RELEASE_RECOVERY_SHARE"]
lines = open(sys.argv[1]).read().splitlines()
problems = []
for name in names:
    hits = [i for i, line in enumerate(lines) if line.startswith(name + " =")]
    if len(hits) != 1:
        problems.append(f"{name} is not defined exactly once at module level")
        continue
    comment, i = [], hits[0] - 1
    while i >= 0 and lines[i].lstrip().startswith("#"):
        comment.insert(0, lines[i])
        i -= 1
    if not comment or len(comment) > 3 or not any("provisional" in c.lower() for c in comment):
        problems.append(f"{name} lacks a provisional-basis comment of at most 3 lines")
for problem in problems:
    print(problem)
sys.exit(1 if problems else 0)
PYEOF
then
  pass "every verdict bound is a named constant with a provisional-basis comment"
else
  fail_case "a verdict bound is not a commented module-level constant"
fi

if grep -nE '(^|[^A-Za-z_])MALLOC_|mallinfo|malloc_info|malloc_stats' "${SCRIPT}"; then
  fail_case "the check reads a forbidden allocator counter"
else
  pass "the check reads no allocator counters"
fi

exit "${FAILED}"
