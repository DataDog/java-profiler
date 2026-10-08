#!/bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Runs Phase 0 inside the java-profiler test image (see
# utils/run-containers-tests.sh, which builds it). The profiler is built from a
# clean clone of the committed HEAD, so local uncommitted changes to the
# profiler do not leak in; the memcheck scripts themselves are mounted from
# the working tree. The built library is kept in OUT/lib, so a re-run with
# SKIP_BUILD=1 reuses it.
#
# Usage: phase0-container.sh [OUT]   (default OUT: build/memcheck)
#   IMAGE (java-profiler-test:glibc-jdk21-<arch>), CPUS (4), REPS, NOPROF_REPS,
#   SCENARIOS, SKIP_BUILD, STEADY_MS, DUMP_AFTER_MS, SAMPLE_DELAY_S
#   DOCKER_EXTRA_ARGS  extra `docker run` flags, e.g. to let the profiler open
#                      perf events (needed for the NM_PERF category):
#                      "--cap-add=PERFMON --security-opt seccomp=unconfined"
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
OUT="$(mkdir -p "${1:-$ROOT/build/memcheck}" && cd "${1:-$ROOT/build/memcheck}" && pwd)"
case "$(uname -m)" in arm64|aarch64) ARCH=aarch64 ;; *) ARCH=x64 ;; esac
IMAGE="${IMAGE:-java-profiler-test:glibc-jdk21-$ARCH}"

# shellcheck disable=SC2086  # DOCKER_EXTRA_ARGS is a list of flags
docker run --rm --cpus="${CPUS:-4}" ${DOCKER_EXTRA_ARGS:-} \
  -v "$ROOT":/source:ro -v "$HERE":/memcheck:ro -v "$OUT":/out \
  -e REPS -e NOPROF_REPS -e SCENARIOS -e SKIP_BUILD -e STEADY_MS -e DUMP_AFTER_MS -e SAMPLE_DELAY_S \
  -e GRADLE_USER_HOME=/gradle-cache \
  "$IMAGE" /bin/bash -c '
set -euo pipefail
if [ -z "${SKIP_BUILD:-}" ]; then
  git clone -q --depth 1 file:///source /workspace
  cd /workspace
  git rev-parse HEAD > /out/profiler-commit.txt
  ./gradlew -q --console=plain :ddprof-lib:assembleReleaseJar \
    -Pskip-tests -Pskip-gtest -Pskip-debug-extraction=true > /out/build.log 2>&1 \
    || { echo "build failed, see /out/build.log"; exit 1; }
  rm -rf /out/lib && mkdir -p /out/lib
  cp "$(find ddprof-lib/build/lib/main/release -name libjavaProfiler.so | head -1)" /out/lib/
  cp -r ddprof-lib/build/classes/java/main /out/lib/classes
fi
export DDPROF_LIB=/out/lib/libjavaProfiler.so DDPROF_CLASSES=/out/lib/classes
export MEMCHECK_CLASSES=/tmp/memcheck-classes WORKDIR=/tmp/memcheck OUTDIR=/out/runs
java -version 2>&1 | head -1 > /out/jdk.txt
nproc > /out/cpus.txt
/memcheck/phase0.sh 2>&1 | tee /out/phase0.log
'
