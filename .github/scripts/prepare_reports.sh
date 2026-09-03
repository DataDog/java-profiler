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
# The JUnit XML of the final attempt, not just the rendered HTML, for reading
# by hand. Each attempt starts by deleting this directory, so the per-attempt
# evidence flake_report.py compares lives in flake-evidence/ (copied below).
cp -r ddprof-test/build/test-results test-reports/test-results || true
cp -r flake-evidence test-reports/flake-evidence || true
cp build/logs/gdb-watchdog.log test-reports/ || true
cp -r /tmp/recordings test-reports/recordings || true
find ddprof-lib/build -name 'libjavaProfiler.*' -exec cp {} test-reports/ \; || true

cp -r ddprof-test/build/reports/unwinding-summary.md unwinding-reports/ || true
cp -r /tmp/unwinding-recordings/* unwinding-reports/ || true
