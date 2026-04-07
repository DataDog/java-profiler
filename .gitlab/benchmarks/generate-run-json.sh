#!/bin/bash

# generate-run-json.sh - Generate run JSON for benchmark tests
#
# Usage: generate-run-json.sh [reports-dir]
#
# Parses benchmark report files and outputs a JSON object
# suitable for update-history.sh. Reads CI environment variables for metadata.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="${SCRIPT_DIR}/../.."
REPORTS_DIR="${1:-${PROJECT_ROOT}/reports}"

# Read metadata from environment or defaults
TIMESTAMP=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
PIPELINE_ID="${CI_PIPELINE_ID:-0}"
PIPELINE_URL="${CI_PIPELINE_URL:-#}"
DDPROF_BRANCH="${DDPROF_COMMIT_BRANCH:-main}"
DDPROF_SHA="${DDPROF_COMMIT_SHA:-unknown}"

# Read version from environment or version.txt
LIB_VERSION="${CURRENT_VERSION:-unknown}"
if [ "${LIB_VERSION}" = "unknown" ] && [ -f "${PROJECT_ROOT}/version.txt" ]; then
  LIB_VERSION=$(awk -F: '{print $NF}' "${PROJECT_ROOT}/version.txt" | tr -d ' ')
fi

# Lookup PR for branch
PR_JSON="{}"
if [ -x "${SCRIPT_DIR}/../common/lookup-pr.sh" ]; then
  PR_JSON=$("${SCRIPT_DIR}/../common/lookup-pr.sh" "${DDPROF_BRANCH}" 2>/dev/null) || PR_JSON="{}"
fi

# Parse benchmark results
python3 <<EOF
import json
import os
import re
from pathlib import Path

reports_dir = "${REPORTS_DIR}"
timestamp = "${TIMESTAMP}"
pipeline_id = "${PIPELINE_ID}"
pipeline_url = "${PIPELINE_URL}"
ddprof_branch = "${DDPROF_BRANCH}"
ddprof_sha = "${DDPROF_SHA}"
lib_version = "${LIB_VERSION}"

# Parse PR JSON (may be empty {})
try:
    pr_info = json.loads('''${PR_JSON}''')
except json.JSONDecodeError:
    pr_info = {}

def analyze_benchmarks(base_dir):
    """Analyze benchmark results."""
    results = {
        "architectures": [],
        "modes_tested": [],
        "regression_detected": False,
        "regression_details": [],
        "total_benchmarks": 0,
        "comparison_files": 0
    }

    if not os.path.isdir(base_dir):
        return results

    architectures = set()
    modes = set()

    # Look for result files
    for entry in os.listdir(base_dir):
        file_path = os.path.join(base_dir, entry)
        if not os.path.isfile(file_path):
            continue

        # Parse architecture from filename (e.g., candidate-amd64_cpu,wall.json)
        if entry.endswith('.json'):
            results["total_benchmarks"] += 1

            # Extract architecture
            if 'amd64' in entry.lower() or 'x64' in entry.lower():
                architectures.add('amd64')
            if 'aarch64' in entry.lower() or 'arm64' in entry.lower():
                architectures.add('aarch64')

            # Extract modes from filename
            mode_match = re.search(r'_([a-z,]+)\.json$', entry)
            if mode_match:
                for mode in mode_match.group(1).split(','):
                    modes.add(mode)

        # Count comparison files
        if 'comparison' in entry.lower():
            results["comparison_files"] += 1

        # Check for regression markers in markdown files
        if entry.endswith('.md') and 'comparison' in entry.lower():
            try:
                with open(file_path, 'r') as f:
                    content = f.read().lower()
                    if 'regression' in content or 'worse' in content:
                        results["regression_detected"] = True
                        # Extract regression details (first few lines mentioning regression)
                        for line in content.split('\n'):
                            if 'regression' in line or 'worse' in line:
                                detail = line.strip()[:100]
                                if detail and detail not in results["regression_details"]:
                                    results["regression_details"].append(detail)
                                    if len(results["regression_details"]) >= 5:
                                        break
            except Exception:
                pass

    results["architectures"] = sorted(architectures)
    results["modes_tested"] = sorted(modes)

    return results

# Analyze results
summary = analyze_benchmarks(reports_dir)

# Determine overall status
if summary["regression_detected"]:
    status = "failed"
elif summary["total_benchmarks"] > 0:
    status = "passed"
else:
    status = "unknown"

# Build run JSON
run = {
    "id": pipeline_id,
    "timestamp": timestamp,
    "ddprof_branch": ddprof_branch,
    "ddprof_sha": ddprof_sha,
    "ddprof_pr": pr_info if pr_info.get("number") else None,
    "pipeline": {
        "id": pipeline_id,
        "url": pipeline_url
    },
    "lib_version": lib_version,
    "status": status,
    "summary": summary
}

# Output JSON
print(json.dumps(run, indent=2))
EOF
