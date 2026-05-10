#!/bin/bash

# generate-run-json.sh - Generate run JSON for reliability tests
#
# Usage: generate-run-json.sh [artifacts-dir]
#
# Parses build.env files for failure reasons and outputs a JSON object
# suitable for update-history.sh. Reads CI environment variables for metadata.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="${SCRIPT_DIR}/../.."
ARTIFACTS_DIR="${1:-${PROJECT_ROOT}}"

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

# Expected configs: 2 configs x 2 variants x 3 allocators x 2 architectures = 24
EXPECTED_CONFIGS=24

# Parse reliability results
python3 <<EOF
import json
import os
import re

artifacts_dir = "${ARTIFACTS_DIR}"
timestamp = "${TIMESTAMP}"
pipeline_id = "${PIPELINE_ID}"
pipeline_url = "${PIPELINE_URL}"
ddprof_branch = "${DDPROF_BRANCH}"
ddprof_sha = "${DDPROF_SHA}"
lib_version = "${LIB_VERSION}"
expected_configs = ${EXPECTED_CONFIGS}

# Parse PR JSON (may be empty {})
try:
    pr_info = json.loads('''${PR_JSON}''')
except json.JSONDecodeError:
    pr_info = {}

def parse_build_env(base_dir):
    """Parse build.env files for failure reasons."""
    failures = []

    # Look for build.env in base directory and subdirectories
    for root, dirs, files in os.walk(base_dir):
        if 'build.env' in files:
            env_path = os.path.join(root, 'build.env')
            try:
                with open(env_path, 'r') as f:
                    for line in f:
                        line = line.strip()
                        if line.startswith('REASON_') and '=' in line:
                            # Parse: REASON_profiler_tcmalloc_amd64Xjit=Memory usage is trending up
                            key, value = line.split('=', 1)
                            # Extract config details from key
                            # Format: REASON_{config}_{allocator}_{arch}X{variant}
                            match = re.match(r'REASON_([^_]+)_([^_]+)_(\w+)X(\w+)', key)
                            if match:
                                config, allocator, arch, variant = match.groups()
                                failures.append({
                                    "config": config,
                                    "allocator": allocator,
                                    "arch": arch,
                                    "variant": variant,
                                    "reason": value
                                })
                            else:
                                failures.append({
                                    "config": "unknown",
                                    "reason": f"{key}={value}"
                                })
            except Exception:
                pass

    return failures

def analyze_results(base_dir):
    """Analyze reliability test results."""
    failures = parse_build_env(base_dir)

    results = {
        "total_configs": expected_configs,
        "passed": expected_configs - len(failures),
        "failed": len(failures),
        "failures": [],
        "memory_trend_warnings": []
    }

    # Format failures for display
    for f in failures:
        if f.get("config") != "unknown":
            label = f"{f['config']}-{f['allocator']}-{f['arch']}-{f['variant']}"
        else:
            label = f.get("reason", "Unknown")

        results["failures"].append(f"{label}: {f.get('reason', 'Unknown')}")

        # Track memory trend issues separately
        if 'memory' in f.get('reason', '').lower() or 'trending' in f.get('reason', '').lower():
            results["memory_trend_warnings"].append(label)

    return results

# Analyze results
summary = analyze_results(artifacts_dir)

# Determine overall status
if summary["failed"] == 0:
    status = "passed"
elif summary["passed"] == 0:
    status = "failed"
else:
    status = "partial"

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
