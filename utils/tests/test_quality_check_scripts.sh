#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for the utils/check-*.py quality-check scripts run by
# `./gradlew :ddprof-lib:qualityChecks`.
# Run with: bash utils/tests/test_quality_check_scripts.sh
#
# Linux-only cases (they compile the signal-reachability fixture and need GNU
# objdump) print "SKIP: <case> (not Linux)" elsewhere; a skip counts as a pass.

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
SIGSETJMP="$ROOT/utils/check-sigsetjmp-shape.py"
BOUNDARY="$ROOT/utils/check-jvm-boundary-includes.py"
REACHABILITY="$ROOT/utils/check-signal-reachability.py"
FIXTURE="$ROOT/utils/tests/signal-reachability-fixture.cpp"
SRC=ddprof-lib/src/main/cpp
TESTS=0
FAILED=0

# Importing the scripts as modules must not leave __pycache__ in the tree.
export PYTHONDONTWRITEBYTECODE=1

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

skip() {
  TESTS=$((TESTS + 1))
  echo "SKIP: $*"
}

on_linux() {
  [ "$(uname -s)" = "Linux" ]
}

# expect <case> <expected rc> <actual rc> <output> [<substring that must appear>]
expect() {
  local name=$1 want_rc=$2 rc=$3 out=$4 want_out=${5:-}
  if [ "$rc" -ne "$want_rc" ]; then
    fail "$name: exit $rc, expected $want_rc; output:"$'\n'"$out"
  elif [ -n "$want_out" ] && [[ "$out" != *"$want_out"* ]]; then
    fail "$name: output lacks '$want_out'; output:"$'\n'"$out"
  else
    pass
  fi
}

# --- T1: check-sigsetjmp-shape.py scope recognition ---------------------------

SJ_ROOT="$TEMP_DIR/sigsetjmp"
mkdir -p "$SJ_ROOT/$SRC"
PAD_A='if (sigsetjmp(ctx, 1) != 0) { SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP(); jmp_scope.restore(); return; }'

# sigsetjmp_case <case> <file body>; prints output, returns the checker's exit code.
sigsetjmp_case() {
  local name=$1 body=$2
  printf 'void f(ProfiledThread* pt, bool x) {\n%s\n}\n' "$body" > "$SJ_ROOT/$SRC/$name.cpp"
  python3 "$SIGSETJMP" --root "$SJ_ROOT" "$SRC/$name.cpp" 2>&1
}

rc=0; out=$(sigsetjmp_case brace_init "  JmpCtxScope jmp_scope{pt};
  $PAD_A") || rc=$?
expect "T1a brace-init guard" 0 "$rc" "$out" "OK (1 calls"

rc=0; out=$(sigsetjmp_case paren_init "  JmpCtxScope jmp_scope(pt);
  $PAD_A") || rc=$?
expect "T1b paren-init guard" 0 "$rc" "$out" "OK (1 calls"

rc=0; out=$(sigsetjmp_case block_paren "  { JmpCtxScope jmp_scope(pt); }
  $PAD_A") || rc=$?
expect "T1c paren-init guard in completed block" 1 "$rc" "$out" "no JmpCtxScope declared"

rc=0; out=$(sigsetjmp_case block_brace "  { JmpCtxScope jmp_scope{pt}; }
  $PAD_A") || rc=$?
expect "T1d brace-init guard in completed block" 1 "$rc" "$out" "no JmpCtxScope declared"

rc=0; out=$(sigsetjmp_case enclosing_brace "  JmpCtxScope jmp_scope{pt};
  if (x) {
    $PAD_A
  }") || rc=$?
expect "T1e brace-init guard in enclosing block" 0 "$rc" "$out" "OK (1 calls"

rc=0; out=$(sigsetjmp_case pad_mismatch "  JmpCtxScope a{pt};
  if (sigsetjmp(ctx, 1) != 0) { SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP(); b.restore(); return; }") || rc=$?
expect "T1f brace-init guard, pad name mismatch" 1 "$rc" "$out" \
  "restores 'b' but the JmpCtxScope in effect is 'a'"

rc=0; out=$(python3 "$SIGSETJMP" 2>&1) || rc=$?
expect "T1g tracked tree" 0 "$rc" "$out" "OK (7 calls, 1 known exception(s))"

# --- T2: check-jvm-boundary-includes.py include forms --------------------------

# boundary_repo <name> <file> <include line> [<file> <include line> ...]; prints the repo dir.
boundary_repo() {
  local repo="$TEMP_DIR/boundary/$1"
  shift
  mkdir -p "$repo/$SRC"
  git -C "$repo" init -q
  while [ $# -gt 0 ]; do
    mkdir -p "$(dirname "$repo/$SRC/$1")"
    printf '%s\nvoid f() {}\n' "$2" > "$repo/$SRC/$1"
    git -C "$repo" add "$SRC/$1"
    shift 2
  done
  echo "$repo"
}

# run_boundary <repo> <KNOWN_EXCEPTIONS as a Python literal>
run_boundary() {
  python3 - "$BOUNDARY" "$1" "$2" <<'EOF' 2>&1
import ast, importlib.util, sys
spec = importlib.util.spec_from_file_location("check_jvm_boundary_includes", sys.argv[1])
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
mod.KNOWN_EXCEPTIONS = ast.literal_eval(sys.argv[3])
sys.exit(mod.main(["--root", sys.argv[2]]))
EOF
}

repo=$(boundary_repo angle shared.cpp '#include <hotspot/vmStructs.h>')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2a angle-bracket include" 1 "$rc" "$out" "shared.cpp:1: shared code includes \"hotspot/vmStructs.h\""

repo=$(boundary_repo quoted shared.cpp '#include "hotspot/vmStructs.h"')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2b quoted include" 1 "$rc" "$out" "shared.cpp:1: shared code includes \"hotspot/vmStructs.h\""

repo=$(boundary_repo j9zing a.cpp '#include <j9/j9Support.h>' b.cpp '#  include <zing/x.h>')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2c j9 angle include" 1 "$rc" "$out" "a.cpp:1: shared code includes \"j9/j9Support.h\""
expect "T2c zing angle include" 1 "$rc" "$out" "b.cpp:1: shared code includes \"zing/x.h\""

repo=$(boundary_repo mixed1 shared.cpp '#include "hotspot/vmStructs.h>')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2d mixed \"...> delimiters not matched" 0 "$rc" "$out" "jvm boundary includes: OK"

repo=$(boundary_repo mixed2 shared.cpp '#include <hotspot/vmStructs.h"')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2e mixed <...\" delimiters not matched" 0 "$rc" "$out" "jvm boundary includes: OK"

repo=$(boundary_repo known_angle shared.cpp '#include <hotspot/vmStructs.h>')
rc=0; out=$(run_boundary "$repo" '{"shared.cpp": {"hotspot/vmStructs.h"}}') || rc=$?
expect "T2f known exception via angle include" 0 "$rc" "$out" "jvm boundary includes: OK"

repo=$(boundary_repo stale shared.cpp '#include <stdio.h>')
rc=0; out=$(run_boundary "$repo" '{"shared.cpp": {"hotspot/vmStructs.h"}}') || rc=$?
expect "T2g stale known exception" 1 "$rc" "$out" "no longer included"

repo=$(boundary_repo boundary_file jvmSupport.cpp '#include <hotspot/vmStructs.h>')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2h boundary file exempt" 0 "$rc" "$out" "jvm boundary includes: OK"

repo=$(boundary_repo impl_dir hotspot/x.cpp '#include <hotspot/vmStructs.h>')
rc=0; out=$(run_boundary "$repo" '{}') || rc=$?
expect "T2i implementation dir exempt" 0 "$rc" "$out" "jvm boundary includes: OK"

rc=0; out=$(python3 "$BOUNDARY" 2>&1) || rc=$?
expect "T2j tracked tree" 0 "$rc" "$out" "jvm boundary includes: OK"

# --- T3: check-signal-reachability.py --self-test (Linux) ----------------------

# self_test_copy <case> [<line appended to the fixture copy>]; prints stdout,
# stderr goes to $TEMP_DIR/sr-<case>.err, returns the self-test's exit code.
self_test_copy() {
  local dir="$TEMP_DIR/sr-$1"
  mkdir -p "$dir/tests"
  cp "$REACHABILITY" "$dir/"
  cp "$FIXTURE" "$dir/tests/"
  if [ -n "${2:-}" ]; then
    printf '%s\n' "$2" >> "$dir/tests/signal-reachability-fixture.cpp"
  fi
  python3 "$dir/check-signal-reachability.py" --self-test 2> "$TEMP_DIR/sr-$1.err"
}

if on_linux; then
  rc=0; out=$(self_test_copy healthy) || rc=$?
  expect "T3a healthy self-test" 0 "$rc" "$out" "self-test PASSED"
  if [[ "$out" == *MISSED* ]]; then fail "T3a healthy self-test reports MISSED:"$'\n'"$out"; else pass; fi

  rc=0; out=$(self_test_copy missed '// EXPECT: CTimer::signalHandler -> fopen') || rc=$?
  expect "T3b missed expectation" 1 "$rc" "$out" "MISSED CTimer::signalHandler -> fopen"

  rc=0; out=$(self_test_copy stale '// EXPECT-ALLOWLISTED: CTimer::signalHandler -> dlopen') || rc=$?
  expect "T3c unused allowlist entry" 1 "$rc" "$out" "NOT FOUND (allowlisted) CTimer::signalHandler -> dlopen"
  if grep -q 'not enough values to unpack' "$TEMP_DIR/sr-stale.err"; then
    fail "T3c unused allowlist entry crashed: $(cat "$TEMP_DIR/sr-stale.err")"
  else
    pass
  fi

  rc=0; out=$(self_test_copy false_positive '// EXPECT-NOT: CTimer::signalHandler -> malloc') || rc=$?
  expect "T3d false positive" 1 "$rc" "$out" "FALSE POSITIVE CTimer::signalHandler -> malloc"
else
  skip "T3a-T3d fixture self-test (not Linux)"
fi

# --- T3h: self_test() evaluates the real findings (every host) ----------------
#
# Stubs the compiler run and the object analysis so self_test()'s own logic is
# exercised without an ELF toolchain: findings must come from
# find_violations(*build_graph([obj])) inside the temp dir, and check()'s
# stale-entry list must never be treated as findings.

run_self_test_harness() {
  python3 - "$REACHABILITY" "$1" <<'EOF' 2>&1
import contextlib, importlib.util, io, os, re, sys, types

path, case = sys.argv[1], sys.argv[2]
spec = importlib.util.spec_from_file_location("check_signal_reachability", path)
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)

with open(mod.SELF_TEST_FIXTURE) as f:
    src = f.read()

def pairs(tag):
    return set(re.findall(r"^// %s: (.+?) -> (.+?)\s*$" % tag, src, re.M))

E, A, N = pairs("EXPECT"), pairs("EXPECT-ALLOWLISTED"), pairs("EXPECT-NOT")
FP = ("Profiler::instance", "malloc")
MISS = ("CTimer::signalHandler", "malloc")
if not (E and A and N) or (E & A) or (E & N) or (A & N) or FP not in N or MISS not in E:
    print("FAIL: %s: fixture precondition broken (E=%r A=%r N=%r)" % (case, E, A, N))
    sys.exit(1)

cases = {
    #  name                 findings              stale                                          new findings
    "healthy":            (E | A,                 [],                                            E),
    "stale":              (E | A,                 [(("NoSuch::caller",), "malloc", "SELFTEST-1")], E),
    "allowlisted_absent": (E,                     [],                                            E),
    "false_positive":     (E | A | {FP},          [],                                            E | {FP}),
    "missed":             ((E - {MISS}) | A,      [],                                            E - {MISS}),
}
F, stale, E_new = cases[case]

DEFINED, GRAPH = object(), object()
state = {"obj": None, "fv_calls": 0, "problems": []}

def fake_run(cmd, **kw):
    state["obj"] = cmd[cmd.index("-o") + 1]
    return types.SimpleNamespace(returncode=0, stdout="", stderr="")

def fake_check(obj_dir, allowlist):
    return ["x:%s -> %s (via y)" % p for p in sorted(E_new)], stale

def fake_build_graph(objs):
    if objs != [state["obj"]]:
        state["problems"].append("build_graph(%r), expected [%r]" % (objs, state["obj"]))
    if not os.path.isdir(os.path.dirname(objs[0])):
        state["problems"].append("build_graph called after the temp dir was removed")
    return DEFINED, GRAPH

def fake_find_violations(defined, graph):
    if defined is not DEFINED or graph is not GRAPH:
        state["problems"].append("find_violations not called with build_graph's result")
    state["fv_calls"] += 1
    return {"root"}, [("fixture.o", c, s, "path") for c, s in sorted(F)]

mod._run, mod.check = fake_run, fake_check
mod.build_graph, mod.find_violations = fake_build_graph, fake_find_violations

buf = io.StringIO()
try:
    with contextlib.redirect_stdout(buf):
        rc = mod.self_test()
except Exception as e:
    print("FAIL: %s: self_test raised %s: %s" % (case, type(e).__name__, e))
    sys.exit(1)
if state["fv_calls"] != 1:
    state["problems"].append("find_violations called %d times, expected 1" % state["fv_calls"])
print(buf.getvalue(), end="")
for p in state["problems"]:
    print("FAIL: %s: %s" % (case, p))
print("rc=%d" % rc)
sys.exit(1 if state["problems"] else 0)
EOF
}

# self_test_harness_case <case> <expected self_test() rc> [<substring>]
self_test_harness_case() {
  local name=$1 want=$2 want_out=${3:-}
  local rc=0 out
  out=$(run_self_test_harness "$name") || rc=$?
  if [ "$rc" -ne 0 ]; then
    fail "T3h-$name: harness failed:"$'\n'"$out"
  elif [[ "$out" != *"rc=$want"* ]]; then
    fail "T3h-$name: self_test() did not return $want:"$'\n'"$out"
  elif [ -n "$want_out" ] && [[ "$out" != *"$want_out"* ]]; then
    fail "T3h-$name: output lacks '$want_out':"$'\n'"$out"
  else
    pass
  fi
}

self_test_harness_case healthy 0 "self-test PASSED"
self_test_harness_case stale 0 "self-test PASSED"
self_test_harness_case allowlisted_absent 1 "NOT FOUND (allowlisted) wakeupHandler -> Log::warn"
self_test_harness_case false_positive 1 "FALSE POSITIVE Profiler::instance -> malloc"
self_test_harness_case missed 1 "MISSED CTimer::signalHandler -> malloc"

# --- T4: tree-level script health and doc/build wiring ------------------------

rc=0; out=$(python3 "$ROOT/utils/check-doc-index.py" 2>&1) || rc=$?
expect "T4 check-doc-index.py" 0 "$rc" "$out"

rc=0; out=$(python3 "$ROOT/utils/check-tracked-artifacts.py" 2>&1) || rc=$?
expect "T4 check-tracked-artifacts.py" 0 "$rc" "$out"

# Built without the literal so this file never matches itself.
pat=s_nested_overflow; pat="${pat}_warned"
if out=$(git -C "$ROOT" grep -n "$pat" -- doc ddprof-lib AGENTS.md README.md utils/README.md); then
  fail "T4 removed overflow-warning latch still documented:"$'\n'"$out"
else
  pass
fi

if grep -q 'opt-in; checkSignalReachability plus all four' "$ROOT/utils/README.md"; then
  fail "T4 utils/README.md still calls qualityChecks opt-in"
else
  pass
fi

if grep -n 'Opt-in' "$ROOT/ddprof-lib/build.gradle.kts"; then
  fail "T4 ddprof-lib/build.gradle.kts still says Opt-in"
else
  pass
fi

GRADLE="$ROOT/ddprof-lib/build.gradle.kts"
n=$(grep -c 'hasElfObjects(debugObjDir)' "$GRADLE" || true)
if [ "$n" -ne 2 ]; then fail "T4 hasElfObjects(debugObjDir) used $n times, expected 2"; else pass; fi
n=$(grep -c '0x7f' "$GRADLE" || true)
fun_line=$(grep -n '^fun hasElfObjects' "$GRADLE" | head -1 | cut -d: -f1 || true)
magic_line=$(grep -n '0x7f' "$GRADLE" | head -1 | cut -d: -f1 || true)
if [ "$n" -ne 1 ] || [ -z "$fun_line" ] || [ -z "$magic_line" ] ||
   [ "$magic_line" -le "$fun_line" ] || [ $((magic_line - fun_line)) -gt 6 ]; then
  fail "T4 ELF magic must appear once, inside fun hasElfObjects (count=$n, fun=$fun_line, magic=$magic_line)"
else
  pass
fi

n=$(grep -cxF './gradlew :ddprof-lib:checkSignalReachability      # opt-in; SKIPPED when the debug objects are not ELF' \
  "$ROOT/utils/README.md" || true)
if [ "$n" -ne 1 ]; then fail "T4 utils/README.md standalone checkSignalReachability line changed"; else pass; fi

n=$(grep -c 'REFCOUNT_NESTED_OVERFLOW' "$ROOT/doc/architecture/RefCountGuard.md" || true)
if [ "$n" -lt 2 ]; then fail "T4 RefCountGuard.md mentions REFCOUNT_NESTED_OVERFLOW $n times, expected >= 2"; else pass; fi

# --- Summary -----------------------------------------------------------------

if [ "$FAILED" -gt 0 ]; then
  echo "FAIL: $FAILED/$TESTS test groups failed" >&2
  exit 1
fi
echo "PASS: $TESTS test groups"
