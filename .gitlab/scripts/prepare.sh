#! /bin/bash

set -eo pipefail  # exit on any failure, including mid-pipeline

# Normalize CI_COMMIT_BRANCH — it may be empty for trigger/pipeline sources;
# fall back to CI_COMMIT_REF_NAME which is always populated by GitLab.
CI_COMMIT_BRANCH="${CI_COMMIT_BRANCH:-${CI_COMMIT_REF_NAME:-}}"
export CI_COMMIT_BRANCH

# Check if we should skip non-PR branch builds
# Allow: default branch pushes, scheduled runs, and web (manual) triggers
# Gate: push/trigger/pipeline sources on non-default branches must have an open GitHub PR
if [ "${CI_PIPELINE_SOURCE}" == "push" ] || [ "${CI_PIPELINE_SOURCE}" == "trigger" ] || [ "${CI_PIPELINE_SOURCE}" == "pipeline" ]; then
  if [ -n "${CI_COMMIT_BRANCH}" ] && [ "${CI_COMMIT_BRANCH}" != "${CI_DEFAULT_BRANCH:-main}" ] && [[ ! ${CI_COMMIT_TAG} =~ ^v_[0-9]+(-SNAPSHOT)?$ ]]; then
    # Check if the branch has an open PR in DataDog/java-profiler
    API_RESPONSE=$(curl -sf "https://api.github.com/repos/DataDog/java-profiler/pulls?head=DataDog:${CI_COMMIT_BRANCH}&state=open&per_page=1" 2>/dev/null || echo "")
    if [ -n "${API_RESPONSE}" ] && ! echo "${API_RESPONSE}" | grep -q '"number"'; then
      echo "No open PR for branch ${CI_COMMIT_BRANCH}, skipping pipeline"
      echo "CANCELLED=true" >> build.env
      exit 0
    fi
  fi
fi

apt-get update -qq && apt-get install -y -qq openjdk-21-jdk-headless

source .gitlab/scripts/includes.sh

LIB_VERSION=$(get_version)
echo "com.datadoghq:ddprof:${LIB_VERSION}" > version.txt

# Export CI_COMMIT_BRANCH so downstream jobs inherit the resolved value
echo "CI_COMMIT_BRANCH=${CI_COMMIT_BRANCH}" >> build.env
# Export DDPROF_COMMIT_BRANCH/SHA for integration test scripts (legacy variable names)
echo "DDPROF_COMMIT_BRANCH=${CI_COMMIT_BRANCH}" >> build.env
echo "DDPROF_COMMIT_SHA=${CI_COMMIT_SHA}" >> build.env
