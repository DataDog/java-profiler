#!/bin/bash
set -euxo pipefail

if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

# Source centralized configuration
HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source "${HERE}/../../.gitlab/config.env"

VERSION=${1:-"unknown"}
PIPELINE_URL="$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID"
PIPELINE_LINK="<$PIPELINE_URL|pipeline #$CI_PIPELINE_ID>"

MESSAGE_TEXT=":better-siren: dd-trace-java integration tests failed for ${VERSION} (pipeline=$PIPELINE_LINK)

Some integration tests failed across the test matrix.
Please review the pipeline artifacts for details."

postmessage "$SLACK_CHANNEL" "$MESSAGE_TEXT" "alert"
