  #!/usr/bin/env bash

set -e
mkdir -p test-reports
mkdir -p unwinding-reports
cp build/test-raw.log test-reports/ || true
cp /tmp/hs_err* test-reports/ || true
cp /tmp/asan_*.log test-reports/ || true
cp /tmp/ubsan_*.log test-reports/ || true
cp /tmp/tsan_*.log test-reports/ || true
cp ddprof-test/javacore*.txt test-reports/ || true
cp ddprof-test/build/hs_err* test-reports/ || true
cp -r ddprof-lib/build/tmp test-reports/native_build || true
cp -r ddprof-test/build/reports/tests test-reports/tests || true
# The JUnit XML of every attempt, for reading by hand, normally comes from
# flake-evidence/ alone (copied below): run_tests_with_retry.sh snapshots
# each attempt's build/test-results there, and flake-evidence/attempt-<final>
# holds exactly what build/test-results itself holds once the run is over.
# The one case that snapshots nothing at all is a suite that passed outright
# on its first attempt (skipped as a needless copy with no other attempt to
# compare against) -- copy build/test-results directly only then, so a green
# run still ships its JUnit XML.
# Keyed on real evidence rather than on the attempt-* directory: snapshot()
# creates that with mkdir -p *before* the copy that may fail, so an empty or
# partial snapshot would otherwise skip this fallback and ship an artifact with
# no JUnit XML in it at all.
if [ -z "$(find flake-evidence -name 'TEST-*.xml' 2>/dev/null | head -1)" ]; then
  cp -r ddprof-test/build/test-results test-reports/test-results || true
fi
cp -r flake-evidence test-reports/flake-evidence || true
cp build/logs/gdb-watchdog.log test-reports/ || true
cp -r /tmp/recordings test-reports/recordings || true
find ddprof-lib/build -name 'libjavaProfiler.*' -exec cp {} test-reports/ \; || true

cp -r ddprof-test/build/reports/unwinding-summary.md unwinding-reports/ || true
cp -r /tmp/unwinding-recordings/* unwinding-reports/ || true
