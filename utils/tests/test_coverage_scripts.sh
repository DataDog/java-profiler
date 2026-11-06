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
# podman: every image exists; the base image ID is "base-1" and a JDK image's base-id
# label is $STUB_LABEL. `run` records one argument per line, `build` appends its tags.
cat > "$STUB_BIN/podman" <<'EOF'
#!/usr/bin/env bash
case "$1 $2" in
  "run "*)
    printf '%s\n' "$@" > "$STUB_LOG"
    exit "${STUB_RUN_RC:-0}" ;;
  "build "*)
    echo "$*" >> "$STUB_LOG.build" ;;
  "image inspect")
    case "$*" in
      *'{{.Id}}'*) echo "base-1" ;;
      *java-profiler.base-id*) echo "${STUB_LABEL:-}" ;;
    esac ;;
esac
exit 0
EOF
# gcovr and java record their arguments; java's `report` writes a minimal jacoco.xml.
cat > "$STUB_BIN/gcovr" <<'EOF'
#!/usr/bin/env bash
printf '%s\n' "$@" > "$STUB_LOG.gcovr"
echo "lines: 50.0% (1 out of 2)"
EOF
cat > "$STUB_BIN/java" <<'EOF'
#!/usr/bin/env bash
printf '%s\n' "$@" >> "$STUB_LOG.java"
if [[ "$3" == "report" ]]; then
  while [[ $# -gt 0 ]]; do
    if [[ "$1" == "--xml" ]]; then
      printf '<report name="r"><counter type="LINE" missed="1" covered="3"/></report>\n' > "$2"
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
touch "$REPO/gradlew" "$REPO/gradle/wrapper.properties"
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
expect_contains "cell properties" "$log" "glibc aarch64 21 \$(git rev-parse HEAD) \$rc > /coverage-out/cell.properties"
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
expect_contains "summary cells" "$summary" "| glibc | aarch64 | 25-graal | 0 |"
expect_contains "summary cpp" "$summary" "lines: 50.0% (1 out of 2)"
expect_contains "summary java" "$summary" "line: 75.0% (3 out of 4)"
expect_not_contains "identical classes do not warn" "$output" "differ from"

make_cell "$TEMP_DIR/c3" "$SRC_COMMIT" 17 other
output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged3" "$TEMP_DIR/c1" "$TEMP_DIR/c3" 2>&1)
expect_contains "differing classes warn" "$output" "classes in $TEMP_DIR/c3 differ"

rm -f "$TEMP_DIR/c3/reports/cpp/coverage.json"
output=$("$MERGE" --source-root="$SRC" --out="$TEMP_DIR/merged4" "$TEMP_DIR/c1" "$TEMP_DIR/c3" 2>&1)
expect_contains "missing tracefile warns" "$output" "$TEMP_DIR/c3 has no C++ tracefile"

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

echo "$TESTS tests, $FAILED failed"
[[ $FAILED -eq 0 ]]
