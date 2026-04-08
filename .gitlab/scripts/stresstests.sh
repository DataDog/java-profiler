#! /bin/bash

set -eo pipefail  # exit on any failure, including mid-pipeline
set -x

if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

if [ -z "$TARGET" ]; then
  echo "Expecting the TARGET variable to be set"
  exit 1
fi

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_ROOT=$( cd "${HERE}/../.." && pwd )

if [ -z "${JAVA_HOME}" ]; then
  # workaround for CI when JAVA_HOME is not properly defined
  export JAVA_HOME=~/.sdkman/candidates/java/current
fi

echo "Using Java @ ${JAVA_HOME}"

source .gitlab/scripts/includes.sh

function onexit {
  mkdir -p "${REPO_ROOT}/stresstest/${TARGET}/logs"
  mkdir -p "${REPO_ROOT}/stresstest/${TARGET}/results"
  mv "${REPO_ROOT}/ddprof-stresstest/jmh-result.html" "${REPO_ROOT}/stresstest/${TARGET}/results" 2>/dev/null || true
  find . -name 'hs_err*' | xargs -I {} cp {} "${REPO_ROOT}/stresstest/${TARGET}/logs" 2>/dev/null || true
}

trap onexit EXIT

./gradlew -Pddprof_version="$(get_version)" -Pskip-native -Pskip-tests -Pwith-libs="$(pwd)/libs" assembleDebugJar --max-workers=1 --build-cache --stacktrace --info --no-watch-fs --no-daemon
./gradlew -Pddprof_version="$(get_version)" -Pskip-native -Pwith-libs="$(pwd)/libs" -x gtestDebug runStressTests --max-workers=1 --build-cache --stacktrace --info --no-watch-fs --no-daemon
