#!/usr/bin/env bash
# Downloads result JSONs from the BP downstream pipeline via the GitLab CI API.
#
# Requires only curl and python3 (stdlib) — no aws CLI, pip, or boto3 needed.
# BP jobs already store artifacts in GitLab; this fetches them directly from
# the downstream pipeline triggered by benchmarks-trigger.
set -euo pipefail

DEST="${1:-reports}"
mkdir -p "${DEST}"

TMPDIR_LOCAL=$(mktemp -d)
trap 'rm -rf "${TMPDIR_LOCAL}"' EXIT

# ── 1. find the benchmarks-trigger bridge to get downstream project + pipeline ──
BRIDGES_FILE="${TMPDIR_LOCAL}/bridges.json"
curl -sf \
  --header "JOB-TOKEN: ${CI_JOB_TOKEN}" \
  "${CI_API_V4_URL}/projects/${CI_PROJECT_ID}/pipelines/${CI_PIPELINE_ID}/bridges" \
  > "${BRIDGES_FILE}"

read -r BP_PROJECT_ID DOWNSTREAM_PIPELINE_ID < <(python3 - "${BRIDGES_FILE}" <<'PYEOF'
import json, sys
with open(sys.argv[1]) as f:
    bridges = json.load(f)
for b in bridges:
    if b.get("name") == "benchmarks-trigger":
        dp = b.get("downstream_pipeline") or {}
        if dp.get("id") and dp.get("project_id"):
            print(dp["project_id"], dp["id"])
            sys.exit(0)
print("", "")
PYEOF
)

if [ -z "${DOWNSTREAM_PIPELINE_ID:-}" ]; then
  echo "No downstream BP pipeline found for benchmarks-trigger — skipping download"
  exit 0
fi
echo "BP downstream pipeline: project=${BP_PROJECT_ID}  pipeline=${DOWNSTREAM_PIPELINE_ID}"

# ── 2. list jobs in the downstream pipeline ──
JOBS_FILE="${TMPDIR_LOCAL}/jobs.json"
curl -sf \
  --header "JOB-TOKEN: ${CI_JOB_TOKEN}" \
  "${CI_API_V4_URL}/projects/${BP_PROJECT_ID}/pipelines/${DOWNSTREAM_PIPELINE_ID}/jobs?per_page=100" \
  > "${JOBS_FILE}"

JOB_IDS=$(python3 -c "
import json
with open('${JOBS_FILE}') as f:
    print(' '.join(str(j['id']) for j in json.load(f)))
")

# ── 3. download result_*.json from each job's artifact zip ──
DOWNLOADED=0
for JOB_ID in ${JOB_IDS}; do
  ART_ZIP="${TMPDIR_LOCAL}/art_${JOB_ID}.zip"
  if curl -sf \
    --header "JOB-TOKEN: ${CI_JOB_TOKEN}" \
    "${CI_API_V4_URL}/projects/${BP_PROJECT_ID}/jobs/${JOB_ID}/artifacts" \
    --output "${ART_ZIP}" 2>/dev/null; then
    # -j: junk paths (strip the artifacts/ prefix), quiet, overwrite
    if unzip -q -j "${ART_ZIP}" "artifacts/result_*.json" -d "${DEST}/" 2>/dev/null; then
      DOWNLOADED=$((DOWNLOADED + 1))
    fi
  fi
done

RESULT_COUNT=$(find "${DEST}" -name "result_*.json" | wc -l)
echo "result_*.json files downloaded: ${RESULT_COUNT} (from ${DOWNLOADED} BP job(s))"

if [ "${RESULT_COUNT}" -eq 0 ]; then
  echo "WARNING: no result JSONs found — BP jobs may not have run yet" >&2
  exit 1
fi
