  #!/usr/bin/env bash

set -e
mkdir -p reports
cp /tmp/hs_err* reports/ || true
cp ddprof-test/javacore*.txt reports/ || true
cp ddprof-test/build/hs_err* reports/ || true
cp -r ddprof-lib/build/tmp reports/native_build || true
cp -r ddprof-test/build/reports/tests reports/tests || true
cp -r /tmp/recordings reports/recordings || true
find ddprof-lib/build -name 'libjavaProfiler.*' -exec cp {} reports/ \; || true
