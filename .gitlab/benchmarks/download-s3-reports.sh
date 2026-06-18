#!/usr/bin/env bash
# Downloads benchmark reports uploaded by the BP pipeline for this pipeline run.
#
# The BP upload key is:
#   s3://relenv-benchmarking-data/java-profiler/${CI_PIPELINE_ID}/${BP_JOB_ID}/
# We pass UPSTREAM_PIPELINE_ID=${CI_PIPELINE_ID} and UPSTREAM_BRANCH=${CI_PIPELINE_ID}
# to BP; each BP job uploads to its own CI_JOB_ID leaf under that prefix, so
# syncing the whole prefix captures all arch+mode results.
set -euo pipefail

DEST="${1:-reports}"
S3_BUCKET="relenv-benchmarking-data"
S3_PREFIX="java-profiler/${CI_PIPELINE_ID}"

mkdir -p "${DEST}"
aws s3 sync "s3://${S3_BUCKET}/${S3_PREFIX}/" "${DEST}/" \
  --exclude "*" \
  --include "comparison-baseline-vs-candidate_*.md" \
  --include "comparison-baseline-vs-candidate_*.html" \
  --include "*.json"

echo "Downloaded from s3://${S3_BUCKET}/${S3_PREFIX}/ → ${DEST}/"
FILE_COUNT=$(find "${DEST}" -type f | wc -l)
echo "Files downloaded: ${FILE_COUNT}"
if [ "${FILE_COUNT}" -eq 0 ]; then
  echo "ERROR: no benchmark reports found — BP pipeline may not have uploaded yet" >&2
  exit 1
fi
