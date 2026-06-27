#!/usr/bin/env bash
# Downloads result JSONs from the BP downstream pipeline via the GitLab CI API.
#
# Requires only curl and python3 (stdlib) — no aws CLI, pip, or boto3 needed.
# BP jobs already store artifacts in GitLab; this fetches them directly from
# the downstream pipeline triggered by benchmarks-trigger.
set -uo pipefail   # intentionally no -e: we handle errors explicitly

DEST="${1:-reports}"
mkdir -p "${DEST}"

TMPDIR_LOCAL=$(mktemp -d)
trap 'rm -rf "${TMPDIR_LOCAL}"' EXIT

# ── helper: curl with explicit HTTP status checking ──────────────────────────
# Usage: api_get <url> <output_file>
# Returns 0 on 2xx, prints diagnostics and returns 1 otherwise.
api_get() {
  local url="$1" out="$2"
  local http_code
  http_code=$(curl -s -o "${out}" -w "%{http_code}" \
    --header "JOB-TOKEN: ${CI_JOB_TOKEN}" "${url}")
  if [[ "${http_code}" != 2* ]]; then
    echo "  API ${url##*/}: HTTP ${http_code} — $(cat "${out}" | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('message','?'))" 2>/dev/null || echo 'see above')"
    return 1
  fi
  return 0
}

# ── 1. find the benchmarks-trigger bridge ────────────────────────────────────
BRIDGES_FILE="${TMPDIR_LOCAL}/bridges.json"
echo "Querying bridges for pipeline ${CI_PIPELINE_ID}…"
if ! api_get \
  "${CI_API_V4_URL}/projects/${CI_PROJECT_ID}/pipelines/${CI_PIPELINE_ID}/bridges" \
  "${BRIDGES_FILE}"; then
  echo "Cannot read pipeline bridges (job token may lack Reporter access) — skipping download"
  exit 0
fi

read -r BP_PROJECT_ID DOWNSTREAM_PIPELINE_ID < <(python3 - "${BRIDGES_FILE}" <<'PYEOF'
import json, sys
with open(sys.argv[1]) as f:
    bridges = json.load(f)
for b in bridges:
    if b.get("name") == "benchmarks-trigger":
        dp = b.get("downstream_pipeline") or {}
        if dp.get("id") and dp.get("project_id") and dp.get("status") == "success":
            print(dp["project_id"], dp["id"])
            sys.exit(0)
print("", "")
PYEOF
)

if [ -z "${DOWNSTREAM_PIPELINE_ID:-}" ]; then
  echo "benchmarks-trigger bridge not found or did not run — skipping download"
  exit 0
fi
echo "BP downstream pipeline: project=${BP_PROJECT_ID}  pipeline=${DOWNSTREAM_PIPELINE_ID}"

# ── 2. list jobs in the downstream pipeline ──────────────────────────────────
JOBS_FILE="${TMPDIR_LOCAL}/jobs.json"
echo "Listing BP pipeline jobs…"
if ! api_get \
  "${CI_API_V4_URL}/projects/${BP_PROJECT_ID}/pipelines/${DOWNSTREAM_PIPELINE_ID}/jobs?per_page=100" \
  "${JOBS_FILE}"; then
  echo "Cannot list BP pipeline jobs — skipping download"
  exit 0
fi

JOB_IDS=$(python3 -c "
import json
with open('${JOBS_FILE}') as f:
    print(' '.join(str(j['id']) for j in json.load(f)))
")

# ── 3. download result_*.json from each job's artifact zip ───────────────────
DOWNLOADED=0
for JOB_ID in ${JOB_IDS}; do
  ART_ZIP="${TMPDIR_LOCAL}/art_${JOB_ID}.zip"
  ART_STATUS=$(curl -s -o "${ART_ZIP}" -w "%{http_code}" \
    --header "JOB-TOKEN: ${CI_JOB_TOKEN}" \
    "${CI_API_V4_URL}/projects/${BP_PROJECT_ID}/jobs/${JOB_ID}/artifacts" 2>/dev/null)
  if [[ "${ART_STATUS}" == 2* ]]; then
    # -j: junk paths (strip artifacts/ prefix), -q: quiet, -o: overwrite
    if unzip -q -j "${ART_ZIP}" "artifacts/result_*.json" -d "${DEST}/" 2>/dev/null; then
      DOWNLOADED=$((DOWNLOADED + 1))
    fi
  fi
done

RESULT_COUNT=$(find "${DEST}" -name "result_*.json" | wc -l)
echo "result_*.json files: ${RESULT_COUNT} (from ${DOWNLOADED} BP job(s))"

if [ "${RESULT_COUNT}" -eq 0 ]; then
  echo "WARNING: no result JSONs found — BP jobs may not have run or produced artifacts yet"
  exit 1
fi
