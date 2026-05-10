#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

source ${DIR}/config-benchmark-analyzer.sh

BASELINE_JSON=$(find $ARTIFACTS_DIR -name 'baseline*.json' 2>/dev/null)
CANDIDATE_JSON=$(find $ARTIFACTS_DIR -name 'candidate*.json' 2>/dev/null)

# Append $SUFFIX for unique names to match the configurations
ARCH=`uname -m`
SUFFIX=$(echo "$RUN_MODE" | tr ',' '_')
SUFFIX=${ARCH}_${SUFFIX}

benchmark_analyzer analyze \
    --format=html \
    --outpath="$ARTIFACTS_DIR/baseline-analysis_${SUFFIX}.html" \
   "${BASELINE_JSON}"

benchmark_analyzer analyze \
    --format=html \
    --outpath="$ARTIFACTS_DIR/candidate-analysis_${SUFFIX}.html" \
   "${CANDIDATE_JSON}"

benchmark_analyzer compare pairwise \
    --baseline='{"config":"baseline"}' \
    --candidate='{"config":"candidate"}' \
    --format=html \
    --outpath="$ARTIFACTS_DIR/comparison-baseline-vs-candidate_${SUFFIX}.html" \
   "${BASELINE_JSON}" "${CANDIDATE_JSON}"

benchmark_analyzer compare pairwise \
    --baseline='{"config":"baseline"}' \
    --candidate='{"config":"candidate"}' \
    --format=md \
    --outpath="$ARTIFACTS_DIR/comparison-baseline-vs-candidate_${SUFFIX}.md" \
   "${BASELINE_JSON}" "${CANDIDATE_JSON}"
