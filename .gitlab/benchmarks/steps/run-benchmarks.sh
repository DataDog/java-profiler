#!/usr/bin/env bash

set -euo pipefail
HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir -p "${ARTIFACTS_DIR}" || :

LATEST_VERSION="" # initially empty
retries=0
if [ -z "$CANDIDATE_VERSION" ] || [ -z "$BASELINE_VERSION" ]; then
    echo "Retrieving the latest released version ..."
    while [ -z "$LATEST_VERSION" ] && [ $retries -lt 5 ]; do
        # default to the latest released version
        LATEST_VERSION=$(curl -s https://api.github.com/repos/DataDog/java-profiler/releases/latest | grep "tag_name" | cut -f2 -d: | sed -e "s#\"v_##g" | sed -e "s#\",##g" | sed -e "s# ##g")
        if [ -z "$LATEST_VERSION" ]; then
            echo "Can not retrieve the baseline version from Github. Waiting 10s ..."
            sleep 10
        fi
        retries=$((retries+1))
    done
    if [ -z "$LATEST_VERSION" ]; then
        echo "Unable to resolve the latest released version!"
        exit 1
    fi
fi
CANDIDATE_VERSION=${CANDIDATE_VERSION:=$LATEST_VERSION}
BASELINE_VERSION=${BASELINE_VERSION:=$LATEST_VERSION}
RUN_MODE=${RUN_MODE:=cpu,wall}
MODES=${RUN_MODE}

SUFFIX=$(echo "$MODES" | tr ',' '_')

echo "Setting baseline to: $BASELINE_VERSION"
echo "Setting candidate version to: $CANDIDATE_VERSION"

"${HERE}"/run_benchmark.sh --iterations ${BENCHMARK_ITERATIONS:-5} --version $CANDIDATE_VERSION --output $ARTIFACTS_DIR/candidate-$SUFFIX.json --modes "${RUN_MODE}" --config candidate

if [ "$BASELINE_VERSION" != "$CANDIDATE_VERSION" ]; then
    # run comparison against the baseline version, same profiling modes
    "${HERE}"/run_benchmark.sh --iterations ${BENCHMARK_ITERATIONS:-5} --version $BASELINE_VERSION --output $ARTIFACTS_DIR/baseline-$SUFFIX.json --modes "${RUN_MODE}" --config baseline
else
    # run comparison against the same version but with profiling disabled
    "${HERE}"/run_benchmark.sh --iterations ${BENCHMARK_ITERATIONS:-5} --version $CANDIDATE_VERSION --output $ARTIFACTS_DIR/baseline-$SUFFIX.json --modes "" --config baseline
fi

