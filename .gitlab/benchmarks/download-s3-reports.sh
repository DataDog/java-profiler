#!/usr/bin/env bash
# Downloads benchmark reports uploaded by the BP pipeline for this pipeline run.
#
# The BP upload key is:
#   s3://relenv-benchmarking-data/java-profiler/${CI_PIPELINE_ID}/${BP_JOB_ID}/
# We pass UPSTREAM_PIPELINE_ID=${CI_PIPELINE_ID} and UPSTREAM_BRANCH=${CI_PIPELINE_ID}
# to BP; each BP job uploads to its own CI_JOB_ID leaf under that prefix, so
# syncing the whole prefix captures all arch+mode results.
#
# Uses boto3 (Python) rather than the aws CLI — the post-benchmark jobs run in
# dd-octo-sts-ci-base which ships Python but not the aws CLI binary.
set -euo pipefail

DEST="${1:-reports}"
S3_BUCKET="relenv-benchmarking-data"
S3_PREFIX="java-profiler/${CI_PIPELINE_ID}"

mkdir -p "${DEST}"

# Ensure boto3 is available; install quietly if missing.
python3 -c "import boto3" 2>/dev/null || pip3 install --quiet boto3

python3 - "${DEST}" "${S3_BUCKET}" "${S3_PREFIX}" <<'PYEOF'
import boto3, os, sys

dest, bucket, prefix = sys.argv[1], sys.argv[2], sys.argv[3]

INCLUDE_PATTERNS = (".json", "-vs-candidate.md", "-vs-candidate.html")

s3 = boto3.client("s3")
paginator = s3.get_paginator("list_objects_v2")

downloaded = 0
for page in paginator.paginate(Bucket=bucket, Prefix=prefix):
    for obj in page.get("Contents", []):
        key = obj["Key"]
        name = os.path.basename(key)
        if not any(name.endswith(p) for p in INCLUDE_PATTERNS):
            continue
        local_path = os.path.join(dest, name)
        print(f"  {key} → {name}")
        s3.download_file(bucket, key, local_path)
        downloaded += 1

print(f"Downloaded {downloaded} file(s) from s3://{bucket}/{prefix}/")
if downloaded == 0:
    print("ERROR: no benchmark reports found — BP pipeline may not have uploaded yet",
          file=sys.stderr)
    sys.exit(1)
PYEOF
