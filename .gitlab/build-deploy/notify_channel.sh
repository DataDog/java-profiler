#!/bin/bash
set -euxo pipefail

if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

# Source centralized configuration
HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source "${HERE}/../../.gitlab/config.env"

COMMIT_SHA=${CI_COMMIT_SHA}
PIPELINE_URL="$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID"
PIPELINE_LINK="<$PIPELINE_URL|pipeline #$CI_PIPELINE_ID>"

COMMIT_URL="https://github.com/DataDog/java-profiler/commit/$COMMIT_SHA"
COMMIT_LINK="<$COMMIT_URL|${COMMIT_SHA:0:8}>"

BRANCH="${CI_COMMIT_BRANCH:-${CI_COMMIT_REF_NAME:-unknown}}"
BRANCH_URL="https://github.com/DataDog/java-profiler/tree/$BRANCH"
BRANCH_LINK="<$BRANCH_URL|$BRANCH>"

# get status from argument
STATUS=$1
VERSION=$2

if [[ $STATUS == "success" ]]; then
  if [[ ! $VERSION =~ .*?-SNAPSHOT ]]; then
    MESSAGE_TEXT=":tada: Release succeeded for ${VERSION} (branch=$BRANCH_LINK, commit=$COMMIT_LINK, pipeline=$PIPELINE_LINK)

:point_up: Now you can publish the artifacts from <https://oss.sonatype.org/#stagingRepositories|OSS Sonatype>"
  else
    MESSAGE_TEXT=":done: Build succeeded for ${VERSION} (branch=$BRANCH_LINK, commit=$COMMIT_LINK, pipeline=$PIPELINE_LINK)"
  fi
else
  MESSAGE_TEXT=":better-siren: Build failed for ${VERSION} (branch=$BRANCH_LINK, commit=$COMMIT_LINK, pipeline=$PIPELINE_LINK)"
fi

postmessage "$SLACK_CHANNEL" "$MESSAGE_TEXT" "$STATUS"
