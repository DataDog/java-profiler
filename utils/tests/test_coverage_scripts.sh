#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for the coverage paths of utils/run-containers-tests.sh
# (--coverage-out, worktree sources, JDK image reuse) and for utils/merge-coverage.sh.
# The container runtime, gcovr and java are stubs that record their arguments.
# Run with: bash utils/tests/test_coverage_scripts.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
UTILS_DIR="$SCRIPT_DIR/.."
TESTS=0
FAILED=0

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() { TESTS=$((TESTS + 1)); }
fail() {
  TESTS=$((TESTS + 1))
  FAILED=$((FAILED + 1))
  echo "FAIL: $*" >&2
}

# Usage: expect_contains <name> <haystack> <needle>
expect_contains() {
  if [[ "$2" == *"$3"* ]]; then pass; else fail "$1: expected to contain [$3], got: $2"; fi
}
expect_not_contains() {
  if [[ "$2" != *"$3"* ]]; then pass; else fail "$1: expected not to contain [$3], got: $2"; fi
}

# ---- Stubs ----
STUB_BIN="$TEMP_DIR/bin"
mkdir -p "$STUB_BIN"
# podman: every image exists; the base image ID is ${STUB_BASE_ID-base-1} and a JDK image's
# base-id label is $STUB_LABEL. `run` records one argument per line; with $STUB_EXEC it runs
# the container command on the host, /source, /workspace, /coverage-out mapped to $STUB_*.
cat > "$STUB_BIN/podman" <<'EOF'
#!/usr/bin/env bash
case "$1 $2" in
  "run "*)
    printf '%s\n' "$@" > "$STUB_LOG"
    if [[ -n "${STUB_EXEC:-}" ]]; then
      cmd=${*: -1}
      cmd=${cmd//file:\/\/\/source/file://$STUB_SRC}
      cmd=${cmd//\/workspace/$STUB_WS}
      cmd=${cmd//\/coverage-out/$STUB_OUT}
      HOME="$STUB_HOME" bash -c "$cmd"
      exit $?
    fi
    exit "${STUB_RUN_RC:-0}" ;;
  "build "*)
    echo "$*" >> "$STUB_LOG.build" ;;
  "image inspect")
    case "$*" in
      *'{{.Id}}'*) echo "${STUB_BASE_ID-base-1}" ;;
      *java-profiler.base-id*) echo "${STUB_LABEL:-}" ;;
    esac ;;
esac
exit 0
EOF
# gcovr and java record their arguments; java's `report` writes a minimal jacoco.xml.
cat > "$STUB_BIN/gcovr" <<'EOF'
#!/usr/bin/env bash
printf '%s\n' "$@" > "$STUB_LOG.gcovr"
while [[ $# -gt 0 ]]; do
  if [[ "$1" == "-o" ]]; then touch "$2"; fi
  shift
done
echo "lines: 50.0% (1 out of 2)"
EOF
cat > "$STUB_BIN/java" <<'EOF'
#!/usr/bin/env bash
printf '%s\n' "$@" >> "$STUB_LOG.java"
if [[ "$3" == "report" ]]; then
  while [[ $# -gt 0 ]]; do
    if [[ "$1" == "--html" ]]; then mkdir -p "$2"; touch "$2/index.html"; fi
    if [[ "$1" == "--xml" ]]; then
      printf '%s\n' "${STUB_XML:-<report name=\"r\"><counter type=\"LINE\" missed=\"1\" covered=\"3\"/></report>}" > "$2"
    fi
    shift
  done
fi
EOF
chmod +x "$STUB_BIN"/*
export PATH="$STUB_BIN:$PATH"
export STUB_LOG="$TEMP_DIR/stub.log"

# ---- Fake repository with a worktree ----
# run-containers-tests.sh derives the mounted source from its own location.
REPO="$TEMP_DIR/repo"
mkdir -p "$REPO/utils" "$REPO/gradle"
cp "$UTILS_DIR/run-containers-tests.sh" "$REPO/utils/"
touch "$REPO/gradle/wrapper.properties"
# Gradle stand-in for executed container commands: writes the outputs the export copies.
cat > "$REPO/gradlew" <<'EOF'
#!/usr/bin/env bash
mkdir -p ddprof-lib/build/reports/coverage/cpp ddprof-test/build/jacoco ddprof-lib/build/classes/java/main
echo '{}' > ddprof-lib/build/reports/coverage/cpp/coverage.json
touch ddprof-test/build/jacoco/testCoverage.exec ddprof-lib/build/classes/java/main/A.class
exit "${STUB_GRADLE_RC:-0}"
EOF
chmod +x "$REPO/gradlew"
git init --quiet "$REPO"
git -C "$REPO" -c user.name=T -c user.email=t@t.invalid -c commit.gpgsign=false \
  commit --quiet --allow-empty -m init
git -C "$REPO" add -A
git -C "$REPO" -c user.name=T -c user.email=t@t.invalid -c commit.gpgsign=false \
  commit --quiet -m files
WORKTREE="$TEMP_DIR/wt"
git -C "$REPO" worktree add --quiet --detach "$WORKTREE"
COMMON_DIR=$(git -C "$WORKTREE" rev-parse --path-format=absolute --git-common-dir)

run_script() {
  local root=$1
  shift
  rm -f "$STUB_LOG"
  "$root/utils/run-containers-tests.sh" --container=podman --arch=aarch64 "$@" 2>&1
}

# ---- run-containers-tests.sh: coverage command and export ----
out_dir="$TEMP_DIR/cell-out"
output=$(run_script "$REPO" --libc=glibc --jdk=21 --coverage-out="$out_dir")
log=$(cat "$STUB_LOG")
expect_contains "coverage task" "$log" "./gradlew -PCI -PenableCoverage :ddprof-lib:coverageReport --no-daemon"
expect_not_contains "coverage skips no gtests" "$log" "-Pskip-gtest"
expect_contains "coverage out mount" "$log" "$out_dir:/coverage-out"
expect_contains "coverage env" "$log" "SANITIZER=coverage"
expect_contains "export reports" "$log" "cp -r ddprof-lib/build/reports/coverage /coverage-out/reports"
expect_contains "export jacoco" "$log" "cp -r ddprof-test/build/jacoco /coverage-out/jacoco"
expect_contains "export classes" "$log" "cp -r ddprof-lib/build/classes/java/main /coverage-out/classes"
expect_contains "gradle exit preserved" "$log" "|| rc=\$?;"
expect_contains "export clears previous data" "$log" "rm -rf /coverage-out/reports /coverage-out/jacoco /coverage-out/classes /coverage-out/cell.properties"
expect_not_contains "plain repo has no common-dir mount" "$log" "$COMMON_DIR:$COMMON_DIR"
expect_contains "plain repo keeps narrow safe.directory" "$log" "safe.directory /source/.git"
[[ -d "$out_dir" ]] && pass || fail "--coverage-out directory was not created"

output=$(run_script "$REPO" --libc=glibc --jdk=21 --coverage-out="$out_dir" --tests=FooTest)
expect_contains "coverage honours --tests" "$(cat "$STUB_LOG")" ":ddprof-lib:coverageReport -Ptests=FooTest"

if STUB_RUN_RC=7 run_script "$REPO" --libc=glibc --jdk=21 --coverage-out="$out_dir" >/dev/null; then
  fail "container failure exit code was swallowed"
else
  pass
fi

# ---- run-containers-tests.sh: the container command itself ----
export STUB_SRC="$REPO" STUB_HOME="$TEMP_DIR/home"
mkdir -p "$STUB_HOME"
exec_out="$TEMP_DIR/exec-out"
exec_cell() {
  rm -rf "$TEMP_DIR/ws"
  STUB_EXEC=1 STUB_WS="$TEMP_DIR/ws" STUB_OUT="$exec_out" run_script "$REPO" --libc=glibc --jdk=21 \
    --coverage-out="$exec_out" "$@" >/dev/null
}
mkdir -p "$exec_out/reports/stale"
rc=0
STUB_GRADLE_RC=3 exec_cell --tests=FooTest || rc=$?
[[ $rc -eq 3 ]] && pass || fail "cell exit code $rc is not Gradle's 3"
props=$(cat "$exec_out/cell.properties" 2>/dev/null || true)
expect_contains "properties fields" "$props" $'libc=glibc\narch=aarch64\njdk=21\ntests=FooTest\n'
expect_contains "properties commit" "$props" "commit=$(git -C "$REPO" rev-parse HEAD)"
expect_contains "properties gradle exit" "$props" "gradle_exit=3"
[[ -f "$exec_out/reports/cpp/coverage.json" && -f "$exec_out/jacoco/testCoverage.exec" && -f "$exec_out/classes/A.class" ]] \
  && pass || fail "export did not copy reports, jacoco and classes: $(find "$exec_out" | sort)"
[[ ! -e "$exec_out/reports/stale" && ! -e "$exec_out/reports/coverage" ]] \
  && pass || fail "export kept or nested the previous export: $(find "$exec_out" | sort)"
rc=0
exec_cell || rc=$?
[[ $rc -eq 0 ]] && pass || fail "clean cell exited $rc"
expect_contains "unfiltered tests" "$(cat "$exec_out/cell.properties")" $'tests=\n'
# The export fails when its target vanished (a missing parent fails for root too).
rc=0
rm -rf "$TEMP_DIR/ws"
STUB_EXEC=1 STUB_WS="$TEMP_DIR/ws" STUB_OUT="$TEMP_DIR/missing/out" run_script "$REPO" \
  --libc=glibc --jdk=21 --coverage-out="$exec_out" >/dev/null || rc=$?
[[ $rc -eq 70 ]] && pass || fail "failed export exited $rc, expected 70"
# A run that fails before the export leaves no earlier export behind.
STUB_RUN_RC=125 run_script "$REPO" --libc=glibc --jdk=21 --coverage-out="$exec_out" >/dev/null || true
[[ ! -e "$exec_out/cell.properties" && ! -e "$exec_out/reports" ]] \
  && pass || fail "a failed run left the previous export: $(find "$exec_out" | sort)"
for bad in 'A$B' 'A"B' "A'B" 'A`B' 'A\B' 'A;B' 'A B' 'A|B' $'A\nB'; do
  for mode in --coverage-out="$exec_out" --gtest; do
    if output=$(run_script "$REPO" --libc=glibc --jdk=21 "$mode" --tests="$bad"); then
      fail "--tests=$bad was accepted ($mode)"
    else
      expect_contains "--tests=$bad rejected ($mode)" "$output" "--tests may contain only"
    fi
  done
done
output=$(run_script "$REPO" --libc=glibc --jdk=21 --tests='com.Foo*Test#run,Bar-1_x')
expect_contains "test pattern characters accepted" "$(cat "$STUB_LOG")" "-Ptests=com.Foo*Test#run,Bar-1_x"

# The non-coverage command is unchanged.
output=$(run_script "$REPO" --libc=glibc --jdk=21)
log=$(cat "$STUB_LOG")
expect_contains "default task" "$log" "./gradlew -PCI -PkeepJFRs :ddprof-test:testDebug -Pskip-gtest"
expect_not_contains "default has no export" "$log" "/coverage-out"

# ---- run-containers-tests.sh: worktree sources ----
output=$(run_script "$WORKTREE" --libc=musl --jdk=17 --coverage-out="$out_dir")
log=$(cat "$STUB_LOG")
expect_contains "worktree common-dir mount" "$log" "$COMMON_DIR:$COMMON_DIR:ro"
expect_contains "worktree safe.directory" "$log" "safe.directory \"*\""

# ---- run-containers-tests.sh: rejected combinations ----
for bad in "--shell" "--mount" "--matrix" "--config=debug" "--gtest-task=foo_ut"; do
  if output=$(run_script "$REPO" --libc=glibc --jdk=21 --coverage-out="$out_dir" "$bad"); then
    fail "--coverage-out with $bad was accepted"
  else
    expect_contains "--coverage-out with $bad" "$output" "--coverage-out cannot be combined"
  fi
done
if output=$(run_script "$REPO" --libc=glibc --jdk=21 --coverage-out=); then
  fail "empty --coverage-out was accepted"
else
  expect_contains "empty --coverage-out" "$output" "--coverage-out needs a directory"
fi
if run_script "$REPO" --libc=glibc,musl --jdk=21 --coverage-out="$TEMP_DIR/never" >/dev/null; then
  fail "--coverage-out with two cells was accepted"
else
  [[ ! -e "$TEMP_DIR/never" ]] && pass || fail "rejected run created its --coverage-out directory"
fi
if output=$(run_script "$REPO" --libc=glibc,musl --jdk=21 --coverage-out="$out_dir"); then
  fail "--coverage-out with two cells was accepted"
else
  expect_contains "--coverage-out multi-cell" "$output" "--coverage-out runs a single cell"
fi
if output=$(run_script "$REPO" --libc=musl --jdk=21-j9 --coverage-out="$out_dir"); then
  fail "musl J9 coverage cell was accepted"
else
  expect_contains "musl J9 skipped" "$output" "no runnable cells"
fi

# ---- run-containers-tests.sh: JDK image reuse follows the base image ID ----
rm -f "$STUB_LOG.build"
STUB_LABEL=base-1 run_script "$REPO" --libc=glibc --jdk=21 >/dev/null
if [[ -f "$STUB_LOG.build" ]]; then
  fail "JDK image built on the current base was rebuilt: $(cat "$STUB_LOG.build")"
else
  pass
fi
output=$(STUB_LABEL=base-0 run_script "$REPO" --libc=glibc --jdk=21)
expect_contains "stale JDK image rebuilt" "$(cat "$STUB_LOG.build")" "--label java-profiler.base-id=base-1 -t java-profiler-test:glibc-jdk21-aarch64"
expect_contains "stale JDK image message" "$output" "was not built on the current java-profiler-base:glibc-aarch64"
rm -f "$STUB_LOG.build"
STUB_LABEL= run_script "$REPO" --libc=glibc --jdk=21 >/dev/null
expect_contains "unlabeled JDK image rebuilt" "$(cat "$STUB_LOG.build")" "-t java-profiler-test:glibc-jdk21-aarch64"

rm -f "$STUB_LOG.build"
STUB_LABEL=base-1 run_script "$REPO" --libc=glibc --jdk=21 --rebuild-base >/dev/null
expect_contains "--rebuild-base rebuilds the JDK image" "$(cat "$STUB_LOG.build" 2>/dev/null)" "-t java-profiler-test:glibc-jdk21-aarch64"
rm -f "$STUB_LOG.build"
STUB_BASE_ID= STUB_LABEL= run_script "$REPO" --libc=glibc --jdk=21 >/dev/null
expect_contains "unknown base ID rebuilds the JDK image" "$(cat "$STUB_LOG.build" 2>/dev/null)" "-t java-profiler-test:glibc-jdk21-aarch64"

# ---- run-containers-tests.sh: CI-matched cells the test-coverage skill runs ----
output=$(run_script "$REPO" --libc=glibc --jdk=21-graal --coverage-out="$out_dir")
expect_contains "graal coverage image" "$(cat "$STUB_LOG")" "java-profiler-test:glibc-jdk21-graal-aarch64"
if output=$(run_script "$REPO" --libc=glibc --jdk=8 --coverage-out="$out_dir"); then
  fail "glibc aarch64 HotSpot 8 coverage cell was accepted"
else
  expect_contains "glibc aarch64 HotSpot 8 skipped" "$output" "no runnable cells"
fi

# ---- merge-coverage.sh ----
MERGE="$UTILS_DIR/merge-coverage.sh"
SRC="$TEMP_DIR/src"
mkdir -p "$SRC/ddprof-lib/src/main/cpp" "$SRC/ddprof-lib/src/main/java"
git init --quiet "$SRC"
git -C "$SRC" -c user.name=T -c user.email=t@t.invalid -c commit.gpgsign=false \
  commit --quiet --allow-empty -m src
SRC_COMMIT=$(git -C "$SRC" rev-parse HEAD)

# Usage: make_cell <dir> <commit> <jdk> [classes-content]
make_cell() {
  mkdir -p "$1/reports/cpp" "$1/jacoco/children" "$1/classes"
  printf 'libc=glibc\narch=aarch64\njdk=%s\ncommit=%s\ngradle_exit=0\n' "$3" "$2" > "$1/cell.properties"
  echo '{}' > "$1/reports/cpp/coverage.json"
  touch "$1/jacoco/testCoverage.exec" "$1/jacoco/children/child-1.exec"
  echo "${4:-same}" > "$1/classes/A.class"
}
make_cell "$TEMP_DIR/c1" "$SRC_COMMIT" 21
make_cell "$TEMP_DIR/c2" "$SRC_COMMIT" 25-graal
export JACOCO_CLI="$TEMP_DIR/jacococli.jar"
touch "$JACOCO_CLI"

rm -f "$STUB_LOG.gcovr" "$STUB_LOG.java"
output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged" "$TEMP_DIR/c1" "$TEMP_DIR/c2" 2>&1)
gcovr_args=$(cat "$STUB_LOG.gcovr")
java_args=$(cat "$STUB_LOG.java")
expect_contains "gcovr tracefile 1" "$gcovr_args" "$TEMP_DIR/c1/reports/cpp/coverage.json"
expect_contains "gcovr tracefile 2" "$gcovr_args" "$TEMP_DIR/c2/reports/cpp/coverage.json"
expect_contains "gcovr root" "$gcovr_args" "$SRC/ddprof-lib/src/main/cpp"
expect_contains "gcovr merge mode" "$gcovr_args" "--merge-mode-functions=separate"
expect_contains "jacoco merges child exec" "$java_args" "$TEMP_DIR/c2/jacoco/children/child-1.exec"
expect_contains "jacoco merges task exec" "$java_args" "$TEMP_DIR/c1/jacoco/testCoverage.exec"
expect_contains "jacoco report classes" "$java_args" "$TEMP_DIR/c1/classes"
summary=$(cat "$TEMP_DIR/merged/summary.md")
expect_contains "summary cells" "$summary" "| glibc | aarch64 | 25-graal |  | 0 | yes | yes |"
expect_not_contains "unfiltered run has no banner" "$summary" "Filtered run"
expect_contains "summary cpp" "$summary" "lines: 50.0% (1 out of 2)"
expect_contains "summary java" "$summary" "line: 75.0% (3 out of 4)"
expect_not_contains "identical classes do not warn" "$output" "differ from"

make_cell "$TEMP_DIR/c3" "$SRC_COMMIT" 17 other
output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged3" "$TEMP_DIR/c1" "$TEMP_DIR/c3" 2>&1)
expect_contains "differing classes warn" "$output" "classes in $TEMP_DIR/c3 differ"
expect_contains "differing classes in summary" "$(cat "$TEMP_DIR/merged3/summary.md")" "| 17 |  | 0 | yes | partial (classes differ) |"

rm -f "$TEMP_DIR/c3/reports/cpp/coverage.json"
output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged4" "$TEMP_DIR/c1" "$TEMP_DIR/c3" 2>&1)
expect_contains "missing tracefile warns" "$output" "$TEMP_DIR/c3 has no C++ tracefile"
expect_contains "missing tracefile in summary" "$(cat "$TEMP_DIR/merged4/summary.md")" "| 0 | no (no tracefile) |"

make_cell "$TEMP_DIR/c4" "0000000000000000000000000000000000000000" 11
if output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/m" "$TEMP_DIR/c1" "$TEMP_DIR/c4" 2>&1); then
  fail "cells from different commits were merged"
else
  expect_contains "commit mismatch" "$output" "other cells from $SRC_COMMIT"
fi
if output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/m" "$TEMP_DIR/c4" 2>&1); then
  fail "source root at another commit was accepted"
else
  expect_contains "source mismatch" "$output" "--source-root is at $SRC_COMMIT"
fi
mkdir -p "$TEMP_DIR/empty"
if output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/m" "$TEMP_DIR/empty" 2>&1); then
  fail "cell without cell.properties was accepted"
else
  expect_contains "missing properties" "$output" "has no cell.properties"
fi
if output=$("$MERGE" --source-root="$TEMP_DIR" --out="$TEMP_DIR/m" "$TEMP_DIR/c1" 2>&1); then
  fail "non-checkout source root was accepted"
else
  expect_contains "bad source root" "$output" "is not a java-profiler checkout"
fi

# Filtered cells, stale output, empty commit, zero counters, zero cells.
make_cell "$TEMP_DIR/c5" "$SRC_COMMIT" 21
echo "tests=FooTest" >> "$TEMP_DIR/c5/cell.properties"
mkdir -p "$TEMP_DIR/merged5/cpp"
touch "$TEMP_DIR/merged5/cpp/stale.html" "$TEMP_DIR/merged5/.merge-coverage-output"
"$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged5" "$TEMP_DIR/c5" >/dev/null 2>&1
summary=$(cat "$TEMP_DIR/merged5/summary.md")
expect_contains "filtered banner" "$summary" "Filtered run"
expect_contains "filter column" "$summary" "| 21 | FooTest |"
[[ ! -e "$TEMP_DIR/merged5/cpp/stale.html" ]] && pass || fail "--out kept an earlier merge's report"

# Java column: no .exec files, and .exec files but no classes in any cell.
make_cell "$TEMP_DIR/c9" "$SRC_COMMIT" 11
rm -f "$TEMP_DIR/c9/jacoco/testCoverage.exec" "$TEMP_DIR/c9/jacoco/children/child-1.exec"
"$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged9" "$TEMP_DIR/c1" "$TEMP_DIR/c9" >/dev/null 2>&1
expect_contains "no exec column" "$(cat "$TEMP_DIR/merged9/summary.md")" "| 11 |  | 0 | yes | no (no JaCoCo data) |"
rm -rf "$TEMP_DIR/c10"
make_cell "$TEMP_DIR/c10" "$SRC_COMMIT" 8
rm -rf "$TEMP_DIR/c10/classes"
"$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged10" "$TEMP_DIR/c10" >/dev/null 2>&1
summary=$(cat "$TEMP_DIR/merged10/summary.md")
expect_contains "no classes column" "$summary" "| 8 |  | 0 | yes | no (no classes in any cell) |"
expect_contains "no classes summary" "$summary" "(no cell exported classes)"

# --out must be empty or an earlier merge output.
mkdir -p "$TEMP_DIR/notmerge/cpp"
touch "$TEMP_DIR/notmerge/cpp/keep.cpp"
if output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/notmerge" "$TEMP_DIR/c1" 2>&1); then
  fail "a non-merge --out was accepted"
else
  expect_contains "non-merge out" "$output" "neither empty nor an earlier merge output"
fi
[[ -f "$TEMP_DIR/notmerge/cpp/keep.cpp" ]] && pass || fail "a rejected --out lost its files"

make_cell "$TEMP_DIR/c6" "" 21
if output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/m" "$TEMP_DIR/c6" "$TEMP_DIR/c1" 2>&1); then
  fail "cell without a commit was merged"
else
  expect_contains "empty commit" "$output" "$TEMP_DIR/c6 has no commit in cell.properties"
fi

if output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/m" 2>&1); then
  fail "merge without cells was accepted"
else
  expect_contains "no cells" "$output" "no cell directories given"
fi

STUB_XML='<report name="r"><counter type="BRANCH" missed="0" covered="0"/></report>' \
  "$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged7" "$TEMP_DIR/c1" >/dev/null 2>&1
expect_contains "zero-total counter" "$(cat "$TEMP_DIR/merged7/summary.md")" "branch: 0.0% (0 out of 0)"

# JaCoCo CLI download: the jar must match the pinned SHA-256.
cat > "$STUB_BIN/curl" <<'EOF'
#!/usr/bin/env bash
while [[ $# -gt 0 ]]; do
  if [[ "$1" == "-o" ]]; then printf '%s' "${STUB_JAR:-jar}" > "$2"; fi
  shift
done
EOF
chmod +x "$STUB_BIN/curl"
pinned=$(sed -n 's/^JACOCO_CLI_SHA256="\(.*\)"$/\1/p' "$MERGE")
if output=$(env -u JACOCO_CLI "$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged8" "$TEMP_DIR/c1" 2>&1); then
  fail "JaCoCo CLI with a wrong checksum was used"
else
  expect_contains "checksum mismatch" "$output" "SHA-256 mismatch"
  [[ ! -e "$TEMP_DIR/merged8/tools/org.jacoco.cli-0.8.14-nodeps.jar" ]] && pass || fail "mismatched jar was kept"
fi
[[ ${#pinned} -eq 64 ]] && pass || fail "merge-coverage.sh has no pinned SHA-256"
# A merge that failed midway (merged8, checksum mismatch) can be rerun into the same --out.
if "$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged8" "$TEMP_DIR/c1" >/dev/null 2>&1; then
  pass
else
  fail "rerun into a failed merge's --out was rejected"
fi
summary=$(cat "$TEMP_DIR/merged8/summary.md" 2>/dev/null || true)
expect_contains "cpp link when written" "$summary" "- C++ report:"
expect_contains "java link when written" "$summary" "- Java report:"
expect_not_contains "no java link without report" "$(cat "$TEMP_DIR/merged10/summary.md")" "- Java report:"
merge_version=$(sed -n 's/^JACOCO_VERSION="\(.*\)"$/\1/p' "$MERGE")
build_version=$(sed -n 's/^ *toolVersion = "\(.*\)"$/\1/p' "$UTILS_DIR/../ddprof-test/build.gradle.kts")
[[ -n "$merge_version" && "$merge_version" == "$build_version" ]] \
  && pass || fail "JACOCO_VERSION $merge_version differs from ddprof-test toolVersion $build_version"

echo "$TESTS tests, $FAILED failed"
[[ $FAILED -eq 0 ]]
