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

VERSION=$1

FOUND=
env | while IFS='=' read -r name value; do
    # Check if the variable name starts with 'REASON_'
    if [[ $name == REASON_* ]]; then
        STRIPPED="${name#REASON_}"
        CONFIG="${STRIPPED%%X*}"
        VARIANT="${STRIPPED#*X}"
        REASON=$value
        MESSAGE_TEXT=":bomb: Reliability test failed for ${VERSION} (pipeline=$PIPELINE_LINK, reason=\"$REASON\", config=\"$CONFIG\", variant=\"$VARIANT\")"
        postmessage "$SLACK_CHANNEL" "$MESSAGE_TEXT" "alert"
        found="true"
    fi
done
