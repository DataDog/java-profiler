#!/usr/bin/env bash

if [ -z "${UPSTREAM_PROJECT_NAME}" ]; then
    echo "No upstream project defined. Skipping."
    exit 0
fi

# Append $SUFFIX for unique names to match the configurations
ARCH=`uname -m`
SUFFIX=$(echo "$RUN_MODE" | tr ',' '_')
SUFFIX=${ARCH}_${SUFFIX}

cat "$ARTIFACTS_DIR/comparison-baseline-vs-candidate_${SUFFIX}.md" | pr-commenter --for-repo="$UPSTREAM_PROJECT_NAME" --for-pr="$UPSTREAM_BRANCH" --header="Benchmarks [$ARCH $RUN_MODE]" --on-duplicate=replace
