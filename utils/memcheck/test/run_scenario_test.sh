#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Hermetic tests for utils/memcheck/run_scenario.sh and the failure branch of
# ci-run.sh. Stub java/javac/jcmd (and gradlew) stand in for the JVM, so no
# profiler build is needed. Linux only: run_scenario.sh reads /proc/<pid>/status.
#
# Usage: run_scenario_test.sh
set -uo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
failures=0

fail() {
  echo "FAIL $1"; [ -f "$TMP/out.txt" ] && cat "$TMP/out.txt"; failures=$((failures + 1))
}

# The stub JVM: STUB_JVM selects ok (rotation, then exit), slow (rotation, then
# stays alive), dumpfail (reports a failed rotation) or die (exits at once).
STUB="$TMP/jdk/bin"
mkdir -p "$STUB"
cat > "$STUB/java" <<'JAVA'
#!/bin/bash
for a in "$@"; do case "$a" in MemCheckMain) role=main ;; CollectRun) role=collect ;; esac; done
case "${role:-}" in
  main)
    echo $$ > "$STUB_DIR/jvm.pid"
    printf '%s\n' "$@" > "$STUB_DIR/jvm.args"
    case "$STUB_JVM" in
      ok) echo MEMCHECK_LOADED; echo "MEMCHECK_DUMP_END 1"; sleep 1; exit 0 ;;
      slow) echo MEMCHECK_LOADED; echo "MEMCHECK_DUMP_END 1"; exec sleep 30 ;;
      dumpfail) echo "MEMCHECK_DUMP_FAILED boom"; exec sleep 30 ;;
      die) exit 3 ;;
    esac ;;
  collect)
    for a in "$@"; do case "$a" in out=*) echo '{}' > "${a#out=}" ;; esac; done ;;
esac
JAVA
cat > "$STUB/jcmd" <<'JCMD'
#!/bin/bash
echo "$*" >> "$STUB_DIR/jcmd.calls"
[ "${STUB_JCMD:-ok}" = ok ] || exit 1
echo "Total: reserved=2KB, committed=1KB"
JCMD
printf '#!/bin/bash\nexit 0\n' > "$STUB/javac"
chmod +x "$STUB"/*

# scenario <name> <arm> <STUB_JVM> <STUB_JCMD>: runs run_scenario.sh in a fresh dir, sets $rc.
scenario() {
  export STUB_DIR="$TMP/case-$1"
  mkdir -p "$STUB_DIR"
  JAVA_HOME="$TMP/jdk" STUB_JVM=$3 STUB_JCMD=$4 SAMPLE_DELAY_S=0 DDPROF_LIB=/stub/libjavaProfiler.so \
    DDPROF_CLASSES=/stub/classes MEMCHECK_CLASSES=/stub/memcheck WORKDIR="$STUB_DIR/work" \
    OUTDIR="$STUB_DIR/out" "$HERE/../run_scenario.sh" threads "$2" 1 > "$TMP/out.txt" 2>&1
  rc=$?
}

jvm_gone() {
  sleep 0.2
  ! kill -0 "$(cat "$STUB_DIR/jvm.pid")" 2>/dev/null
}

scenario counters counters ok ok
if [ "$rc" -ne 0 ] || [ ! -f "$STUB_DIR/out/threads-counters-1.json" ]; then fail "counters arm runs"
elif [ -e "$STUB_DIR/jcmd.calls" ]; then fail "counters arm must not sample NMT"
elif ! grep -q '^-agentpath:/stub/libjavaProfiler.so=start,wall=~5ms' "$STUB_DIR/jvm.args" \
    || grep -q NativeMemoryTracking "$STUB_DIR/jvm.args"; then fail "counters arm JVM flags"
else echo "ok   counters arm: profiler, no NMT"; fi

scenario nmt nmt ok ok
if [ "$rc" -ne 0 ] || ! grep -qx "$(cat "$STUB_DIR/jvm.pid") VM.native_memory summary" "$STUB_DIR/jcmd.calls"; then
  fail "nmt arm samples NMT"
elif ! grep -q '^-agentpath:' "$STUB_DIR/jvm.args" || ! grep -qx -- '-XX:NativeMemoryTracking=summary' "$STUB_DIR/jvm.args"; then
  fail "nmt arm JVM flags"
elif ! grep -q committed=1KB "$STUB_DIR/work/runs/threads-nmt-1/nmt.txt" \
    || ! grep -q '^VmRSS:' "$STUB_DIR/work/runs/threads-nmt-1/status.txt"; then fail "nmt arm sample files"
else echo "ok   nmt arm: profiler and NMT sampled"; fi

scenario noprof noprof ok ok
if [ "$rc" -ne 0 ] || [ ! -s "$STUB_DIR/jcmd.calls" ]; then fail "noprof arm samples NMT"
elif grep -q '^-agentpath:' "$STUB_DIR/jvm.args" || ! grep -qx -- '-Dmemcheck.noProfiler=true' "$STUB_DIR/jvm.args"; then
  fail "noprof arm JVM flags"
else echo "ok   noprof arm: NMT, no profiler"; fi

scenario jcmdfail nmt slow fail
if [ "$rc" -eq 0 ]; then fail "failed jcmd fails the run"
elif ! jvm_gone; then fail "failed jcmd leaves the JVM running"
else echo "ok   failed jcmd fails the run and kills the JVM"; fi

scenario dumpfail nmt dumpfail ok
if [ "$rc" -ne 1 ] || ! grep -q 'rotation failed: MEMCHECK_DUMP_FAILED boom' "$TMP/out.txt"; then fail "failed rotation"
elif ! jvm_gone; then fail "failed rotation leaves the JVM running"
else echo "ok   failed rotation fails the run and kills the JVM"; fi

# The run must notice the exit at once, not only at its 300 s deadline.
start=$SECONDS
scenario die nmt die ok
if [ "$rc" -ne 1 ] || ! grep -q 'never reached the rotation' "$TMP/out.txt"; then fail "JVM exiting before the rotation"
elif [ $((SECONDS - start)) -gt 30 ]; then fail "JVM exit noticed only after $((SECONDS - start)) s"
else echo "ok   JVM exiting before the rotation fails the run at once"; fi

scenario badarm bogus ok ok
if [ "$rc" -ne 2 ] || ! grep -q 'unknown arm: bogus' "$TMP/out.txt"; then fail "unknown arm"
else echo "ok   unknown arm"; fi

# MemCheckMain against a stub JavaProfiler whose dump() writes no file, an empty file or a
# recording (memcheck.stubWrites): only the last may report a completed rotation.
PROF="$TMP/stubprof"
mkdir -p "$PROF/src/com/datadoghq/profiler" "$PROF/classes"
cat > "$PROF/src/com/datadoghq/profiler/JavaProfiler.java" <<'PROFILER'
package com.datadoghq.profiler;

public class JavaProfiler {
    public static JavaProfiler getInstance(String lib, String scratch) { return new JavaProfiler(); }
    public void addThread() {}
    public void dump(java.nio.file.Path p) {
        try {
            String w = System.getProperty("memcheck.stubWrites");
            if (!w.equals("none")) java.nio.file.Files.write(p, w.equals("data") ? new byte[] {1} : new byte[0]);
        } catch (java.io.IOException e) { throw new java.io.UncheckedIOException(e); }
    }
}
PROFILER
javac -d "$PROF/classes" "$PROF/src/com/datadoghq/profiler/JavaProfiler.java" "$HERE/../src/MemCheckMain.java"
for writes in none empty data; do
  java -cp "$PROF/classes" -Dmemcheck.libpath=/stub -Dmemcheck.dumpAfterMs=100 \
    -Dmemcheck.dumpPath="$PROF/middump-$writes.jfr" -Dmemcheck.stubWrites=$writes \
    MemCheckMain threads 1 1500 > "$TMP/out.txt" 2>&1
  want=$([ "$writes" = data ] && echo MEMCHECK_DUMP_END || echo "MEMCHECK_DUMP_FAILED .*wrote no recording")
  if grep -q "^$want" "$TMP/out.txt"; then echo "ok   rotation that writes=$writes reports ${want%% *}"
  else fail "rotation that writes=$writes"; fi
done

# ci-run.sh in a scratch tree: a stub gradlew and a stub run_all.sh that writes a run log.
ci_run() {
  local root="$TMP/ci-$1"
  mkdir -p "$root/utils/memcheck" "$root/ddprof-lib/build/lib/main/release/linux/x64"
  cp "$HERE/../ci-run.sh" "$root/utils/memcheck/"
  touch "$root/ddprof-lib/build/lib/main/release/linux/x64/libjavaProfiler.so"
  printf '#!/bin/bash\nexit 0\n' > "$root/gradlew"
  printf '#!/bin/bash\nmkdir -p "$WORKDIR/runs/threads-nmt-1"\necho jvm-said-this > "$WORKDIR/runs/threads-nmt-1/stdout.log"\nexit %s\n' \
    "$2" > "$root/utils/memcheck/run_all.sh"
  chmod +x "$root/gradlew" "$root/utils/memcheck/"*.sh
  git -C "$root" init -q && git -C "$root" -c user.name=t -c user.email=t -c commit.gpgsign=false \
    commit -q --allow-empty -m init
  "$root/utils/memcheck/ci-run.sh" "$root/build/memcheck-out" > "$TMP/out.txt" 2>&1
  rc=$?
  DIAG="$root/build/memcheck-out/diagnostics"
}

ci_run failed 1
if [ "$rc" -eq 0 ]; then fail "ci-run.sh fails with run_all.sh"
elif ! grep -qx jvm-said-this "$DIAG/threads-nmt-1/stdout.log"; then fail "ci-run.sh keeps failed run logs"
else echo "ok   ci-run.sh keeps the run logs of a failed job"; fi

ci_run passed 0
if [ "$rc" -ne 0 ] || [ -e "$DIAG" ]; then fail "ci-run.sh without failures"
else echo "ok   ci-run.sh copies no logs when every run passes"; fi

if [ "$failures" -ne 0 ]; then
  echo "$failures test(s) failed"
  exit 1
fi
echo "all run_scenario tests passed"
