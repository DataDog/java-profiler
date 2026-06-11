#!/usr/bin/env bash

set -e

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

RUNTIME=${1}
CONFIG=${2:-profiler}
VARIANT=${3:-jit}
ALLOCATOR=${4:-gmalloc}
ARCH=${5:-AMD64}

echo "Running with runtime: ${RUNTIME} seconds, config=${CONFIG}, variant=${VARIANT}, allocator=${ALLOCATOR}, arch=${ARCH}"

case $VARIANT in
  jit)
    # Short variant
    ${HERE}/jit_stability_check.sh $RUNTIME $CONFIG $ALLOCATOR
    ;;
  memory)
    # Long variant
    ${HERE}/memory_trend_check.sh $RUNTIME $CONFIG $ALLOCATOR
    ;;
  chaos)
    # Reliability chaos harness — runs antagonists under a patched dd-java-agent
    ${HERE}/chaos_check.sh $RUNTIME $CONFIG $ALLOCATOR
    ;;
  *)
    echo "Unknown variant: $VARIANT"
    exit 1
    ;;
esac