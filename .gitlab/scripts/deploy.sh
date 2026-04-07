#! /bin/bash

set -eo pipefail  # exit on any failure, including mid-pipeline
set +x

if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

# NEW: Mode parameter
MODE="${1:-all}"  # Options: all, assemble, publish

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Load centralized configuration
source "${HERE}/../../.gitlab/config.env"

# debug the CI env
echo "CI_COMMIT_TAG=${CI_COMMIT_TAG}"
echo "CI_COMMIT_BRANCH=${CI_COMMIT_BRANCH}"
echo "CI_DEFAULT_BRANCH=${CI_DEFAULT_BRANCH}"
echo "MODE=${MODE}"

# Only fetch AWS SSM secrets when publishing
if [ "$MODE" = "publish" ] || [ "$MODE" = "all" ]; then
  export SONATYPE_USERNAME=$(aws ssm get-parameter --region ${AWS_REGION} --name ${SSM_PREFIX}.sonatype_token_user --with-decryption --query "Parameter.Value" --out text)
  export SONATYPE_PASSWORD=$(aws ssm get-parameter --region ${AWS_REGION} --name ${SSM_PREFIX}.sonatype_token --with-decryption --query "Parameter.Value" --out text)
  export GPG_PRIVATE_KEY=$(aws ssm get-parameter --region ${AWS_REGION} --name ${SSM_PREFIX}.signing.gpg_private_key --with-decryption --query "Parameter.Value" --out text)
  export GPG_PASSWORD=$(aws ssm get-parameter --region ${AWS_REGION} --name ${SSM_PREFIX}.signing.gpg_passphrase --with-decryption --query "Parameter.Value" --out text)
fi

source .gitlab/scripts/includes.sh

LIB_VERSION=$(get_version)
echo "com.datadoghq:ddprof:${LIB_VERSION}" > version.txt

# Assemble task (always needed for artifact creation)
if [ "$MODE" = "assemble" ] || [ "$MODE" = "all" ]; then
  echo "=== Assembling artifact ==="
  ./gradlew -Pskip-native -Pskip-tests -Pddprof_version="${LIB_VERSION}" -PbuildInfo.build.number=$CI_JOB_ID -Pwith-libs="$(pwd)/libs" :ddprof-lib:jar assembleAll --exclude-task compileFuzzer --exclude-task sign --max-workers=1 --no-build-cache --stacktrace --info --no-watch-fs --no-daemon
fi

# Publish task (only when publishing to Maven Central)
if [ "$MODE" = "publish" ] || [ "$MODE" = "all" ]; then
  echo "=== Publishing to Sonatype ==="
  ./gradlew -Pskip-native -Pskip-tests -Pddprof_version="${LIB_VERSION}" -PbuildInfo.build.number=$CI_JOB_ID -Pwith-libs="$(pwd)/libs" publishToSonatype closeAndReleaseSonatypeStagingRepository --exclude-task compileFuzzer --max-workers=1 --no-build-cache --stacktrace --info --no-watch-fs --no-daemon
fi
