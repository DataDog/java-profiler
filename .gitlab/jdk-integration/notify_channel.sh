#!/bin/bash
set -euxo pipefail

if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

# Source centralized configuration
HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source "${HERE}/../../.gitlab/config.env"

PIPELINE_URL="$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID"
PIPELINE_LINK="<$PIPELINE_URL|pipeline #$CI_PIPELINE_ID>"

# get the JDK build args
JDK_VERSION=$1
DEBUG_LEVEL=$2
HASH=$3

JDK_IMAGE="registry.ddbuild.io/ci/openjdk-build:${JDK_VERSION}-${DEBUG_LEVEL}-${HASH}"

MESSAGE_TEXT=":nuke: JDK Integration tests failed (image=\"${JDK_IMAGE}\", pipeline=$PIPELINE_LINK)"

postmessage "$SLACK_CHANNEL" "$MESSAGE_TEXT" "alert"
