#!/usr/bin/env bash

set -e
mkdir -p test-reports
mkdir -p unwinding-reports
cp /tmp/hs_err* test-reports/ || true
cp ddprof-test/javacore*.txt test-reports/ || true
cp ddprof-test/build/hs_err* test-reports/ || true
cp -r ddprof-lib/build/tmp test-reports/native_build || true
cp -r ddprof-test/build/reports/tests test-reports/tests || true
cp -r /tmp/recordings test-reports/recordings || true
find ddprof-lib/build -name 'libjavaProfiler.*' -exec cp {} test-reports/ \; || true

cp -r ddprof-test/build/reports/unwinding-summary.md unwinding-reports/ || true
cp -r /tmp/unwinding-recordings/* unwinding-reports/ || true
