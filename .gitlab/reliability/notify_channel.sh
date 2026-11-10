#!/bin/bash
set -euxo pipefail

# shellcheck disable=SC2236  # pre-existing style; ! -z and -n are equivalent here
if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

# Source centralized configuration
HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# shellcheck disable=SC1091  # config.env lives in the checkout; the path is computed at runtime
source "${HERE}/../../.gitlab/config.env"

PIPELINE_URL="$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID"
PIPELINE_LINK="<$PIPELINE_URL|pipeline #$CI_PIPELINE_ID>"

VERSION=$1

# shellcheck disable=SC2034  # FOUND is never read; preserved unchanged
FOUND=
env | while IFS='=' read -r name value; do
    # Check if the variable name starts with 'REASON_' or 'INCONCLUSIVE_'
    if [[ $name == REASON_* ]]; then
        STRIPPED="${name#REASON_}"
        CONFIG="${STRIPPED%%X*}"
        VARIANT="${STRIPPED#*X}"
        REASON=$value
        MESSAGE_TEXT=":bomb: Reliability test failed for ${VERSION} (pipeline=$PIPELINE_LINK, reason=\"$REASON\", config=\"$CONFIG\", variant=\"$VARIANT\")"
        postmessage "$SLACK_CHANNEL" "$MESSAGE_TEXT" "alert"
        # shellcheck disable=SC2034  # found cannot escape the pipeline subshell; preserved unchanged
        found="true"
    elif [[ $name == INCONCLUSIVE_* ]]; then
        STRIPPED="${name#INCONCLUSIVE_}"
        CONFIG="${STRIPPED%%X*}"
        VARIANT="${STRIPPED#*X}"
        REASON=$value
        MESSAGE_TEXT="Reliability memory check inconclusive for ${VERSION} (pipeline=$PIPELINE_LINK, reason=\"$REASON\", config=\"$CONFIG\", variant=\"$VARIANT\")"
        postmessage "$SLACK_CHANNEL" "$MESSAGE_TEXT" "alert"
    fi
done
