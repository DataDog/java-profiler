#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.

# Exercise the wrapper without Gradle, including the documented *.log discovery.
set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT
mkdir -p "$TEMP_DIR/build/logs" "$TEMP_DIR/bin" "$TEMP_DIR/.claude/commands" "$TEMP_DIR/utils"
cp "$ROOT/.claude/commands/build-and-summarize" "$TEMP_DIR/.claude/commands/build-and-summarize"
cp "$ROOT/utils/gradle_summary.py" "$TEMP_DIR/utils/gradle_summary.py"
run_wrapper() { bash .claude/commands/build-and-summarize "$@"; }
cd "$TEMP_DIR"

cat > gradlew <<'EOF'
#!/usr/bin/env bash
printf '%s\n' "$@" > "$CAPTURE"
echo 'full build output'
if [ "${FAKE_STATUS:-0}" -ne 0 ]; then
  echo '* What went wrong:'
  echo 'fixture build failed'
  echo '* Try:'
  echo '> Task :fixture:test FAILED'
  echo '2 tests completed, 1 failed'
  echo 'Fixture > fails() FAILED'
fi
exit "${FAKE_STATUS:-0}"
EOF
chmod +x gradlew
export PATH="$TEMP_DIR/bin:$PATH" CAPTURE="$TEMP_DIR/args"

for i in $(seq 1 25); do
  echo "retained evidence $i" > "build/logs/old-$i.log"
  touch -t 202001010000 "build/logs/old-$i.log"
done

run_wrapper > success.out
printf '%s\n' build -i --console=plain > expected.args
cmp expected.args args
log=$(sed -n 's/^.*Full log at: //p' success.out)
latest=$(ls -t build/logs/*.log | head -1)
[ "$latest" = "$log" ] || { echo "FAIL: *.log discovery found $latest, not $log" >&2; exit 1; }
grep -q 'full build output' "$latest"
! grep -q 'full build output' success.out

status=0
FAKE_STATUS=37 run_wrapper :fixture:test '-Ptests=Fixture with spaces' > failure.out || status=$?
[ "$status" -eq 37 ]
printf '%s\n' :fixture:test '-Ptests=Fixture with spaces' -i --console=plain > expected.args
cmp expected.args args
for text in 'fixture build failed' '> Task :fixture:test FAILED' '2 tests completed, 1 failed' 'Fixture > fails() FAILED'; do
  grep -qF "$text" failure.out
done
failure_log=$(sed -n 's/^.*Full log at: //p' failure.out)
case "$failure_log" in build/logs/*-_fixture_test-*.log) ;; *) exit 1 ;; esac
[ "$failure_log" != "$log" ]

CAPTURE="$TEMP_DIR/args-1" run_wrapper sameTask > concurrent-1.out &
pid1=$!
CAPTURE="$TEMP_DIR/args-2" run_wrapper sameTask > concurrent-2.out &
pid2=$!
wait "$pid1"
wait "$pid2"
log1=$(sed -n 's/^.*Full log at: //p' concurrent-1.out)
log2=$(sed -n 's/^.*Full log at: //p' concurrent-2.out)
[ "$log1" != "$log2" ]
[ -f "$log1" ] && [ -f "$log2" ]
[ "$(find build/logs -name '*.log' | wc -l | tr -d ' ')" -eq 29 ]
for i in $(seq 1 25); do grep -q "retained evidence $i" "build/logs/old-$i.log"; done

mkdir no-logs
: > no-logs/build
status=0
(cd no-logs && bash ../.claude/commands/build-and-summarize) > mkdir.out 2>&1 || status=$?
[ "$status" -eq 1 ]
cmp expected.args args

echo 'PASS: wrapper log discovery, default/explicit arguments, exit status, failure summary, concurrent uniqueness, evidence retention and setup errors'
