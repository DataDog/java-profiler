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
  if [ -z "${GPG_PRIVATE_KEY:-}" ]; then
    echo "ERROR: GPG_PRIVATE_KEY is not set — run the create_key CI job first to provision the signing key in SSM (ci.java-profiler.signing.gpg_private_key)"
    exit 1
  fi
  ./gradlew -Pskip-native -Pskip-tests -Pddprof_version="${LIB_VERSION}" -PbuildInfo.build.number=$CI_JOB_ID -Pwith-libs="$(pwd)/libs" publishToSonatype closeAndReleaseSonatypeStagingRepository --exclude-task compileFuzzer --max-workers=1 --no-build-cache --stacktrace --info --no-watch-fs --no-daemon

  # Downstream consumers (e.g. benchmarking-platform's run-benchmarks.sh)
  # resolve the real timestamped filename via maven-metadata.xml right after
  # this job finishes. Sonatype needs a little time to index a freshly
  # published snapshot, so wait until the metadata (and the jar it points to)
  # are actually resolvable before this job reports success.
  if [[ "${LIB_VERSION}" == *-SNAPSHOT ]]; then
    echo "=== Waiting for snapshot artifact to become resolvable on Sonatype ==="
    META_URL="https://central.sonatype.com/repository/maven-snapshots/com/datadoghq/ddprof/${LIB_VERSION}/maven-metadata.xml"
    RESOLVED=0
    for attempt in $(seq 1 20); do
      SNAPSHOT_VER=$(curl -fsSL "${META_URL}" 2>/dev/null | grep -o '<value>[^<]*</value>' | tail -1 | sed 's/<[^>]*>//g' || true)
      if [ -n "${SNAPSHOT_VER}" ]; then
        JAR_URL="https://central.sonatype.com/repository/maven-snapshots/com/datadoghq/ddprof/${LIB_VERSION}/ddprof-${SNAPSHOT_VER}-debug.jar"
        if curl -fsSL -o /dev/null "${JAR_URL}"; then
          echo "Snapshot artifact resolvable: ${JAR_URL}"
          RESOLVED=1
          break
        fi
      fi
      echo "Attempt ${attempt}/20: snapshot not yet resolvable, retrying in 15s..."
      sleep 15
    done
    if [ "${RESOLVED}" -ne 1 ]; then
      echo "ERROR: snapshot artifact still not resolvable after 20 attempts" >&2
      exit 1
    fi
  fi
fi
