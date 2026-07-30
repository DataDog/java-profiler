#!/bin/bash
# Measures NM_THREAD_LOCAL while N threads are actually alive (see
# LiveThreadLocalSweep.java for why the normal threads sweep in run_sweep.sh
# can't measure this correctly). Prints one CSV line: n,thread_local_bytes
#
# Usage: run_threadlocal_live.sh <N> [hold_duration_ms]
#
# Environment overrides (auto-detected if unset): same as run_sweep.sh.
set -u
N="$1"
HOLD_MS="${2:-8000}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"

DDPROF_LIB="${DDPROF_LIB:-$(find "$REPO_ROOT/ddprof-lib/build/lib/main/release" -name 'libjavaProfiler.*' -not -name '*.debug' 2>/dev/null | head -1)}"
DDPROF_JAVA_API="${DDPROF_JAVA_API:-$REPO_ROOT/ddprof-lib/build/classes/java/main}"
JAVA_BIN="${JAVA_BIN:-java}"
JAVA_HOME_DIR="$("$JAVA_BIN" -XshowSettings:properties -version 2>&1 | awk -F'= ' '/java.home/{print $2}')"
JAVAC_BIN="${JAVAC_BIN:-$(command -v javac || echo "$JAVA_HOME_DIR/bin/javac")}"
JFR_BIN="${JFR_BIN:-$(command -v jfr || echo "$JAVA_HOME_DIR/bin/jfr")}"
WORKDIR="${WORKDIR:-/tmp/memsweep}"

if [ -z "$DDPROF_LIB" ] || [ ! -f "$DDPROF_LIB" ]; then
  echo "ERROR: could not find libjavaProfiler under $REPO_ROOT/ddprof-lib/build/lib/main/release." >&2
  exit 1
fi

CLASSDIR="$WORKDIR/classes"
mkdir -p "$CLASSDIR" "$WORKDIR/out"
if [ ! -f "$CLASSDIR/LiveThreadLocalSweep.class" ]; then
  "$JAVAC_BIN" -cp "$DDPROF_JAVA_API" -d "$CLASSDIR" "$SCRIPT_DIR/src/LiveThreadLocalSweep.java"
fi

TAG="livethreadlocal_${N}"
DUMPJFR="$WORKDIR/out/${TAG}.jfr"

"$JAVA_BIN" -agentpath:${DDPROF_LIB}=start,wall=~5ms,jfr,file=${WORKDIR}/out/${TAG}.final.jfr,cstack=fp \
  -Dmemsweep.libpath="$DDPROF_LIB" \
  -cp "$CLASSDIR:$DDPROF_JAVA_API" LiveThreadLocalSweep "$N" "$HOLD_MS" "$DUMPJFR" \
  > "$WORKDIR/out/${TAG}.stdout" 2>&1

if [ -f "$DUMPJFR" ]; then
  "$JFR_BIN" print --json --events datadog.ProfilerCounter "$DUMPJFR" > "${DUMPJFR}.json" 2>/dev/null
  # extract.py's field order is fixed -- thread_local is the 8th column.
  THREAD_LOCAL=$(python3 "$SCRIPT_DIR/extract.py" "${DUMPJFR}.json" | cut -d, -f8)
else
  THREAD_LOCAL="NO_JFR"
fi
echo "${N},${THREAD_LOCAL}"
