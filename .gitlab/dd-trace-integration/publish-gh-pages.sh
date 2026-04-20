#!/bin/bash

# publish-gh-pages.sh - Publish integration test reports to GitHub Pages
#
# Usage: publish-gh-pages.sh [results-dir]
#
# Generates reports for all test configurations and publishes to gh-pages branch.
# Reports are available at: https://datadog.github.io/async-profiler-build/
#
# In CI: Uses Octo-STS for secure, short-lived GitHub tokens (no secrets needed)
# Locally: Use 'devflow gitlab auth' for Octo-STS, or set GITHUB_TOKEN env var

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="${SCRIPT_DIR}/../.."
RESULTS_BASE="${1:-${PROJECT_ROOT}/integration-test-results}"
MAX_HISTORY=10

# GitHub repo for Pages
GITHUB_REPO="DataDog/java-profiler"
PAGES_URL="https://datadog.github.io/java-profiler"

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

log_info() { echo -e "${GREEN}[INFO]${NC} $*"; }
log_warn() { echo -e "${YELLOW}[WARN]${NC} $*"; }
log_error() { echo -e "${RED}[ERROR]${NC} $*"; }

# Obtain GitHub token
obtain_github_token() {
  # Try dd-octo-sts CLI (works in CI with DDOCTOSTS_ID_TOKEN)
  if command -v dd-octo-sts >/dev/null 2>&1 && [ -n "${DDOCTOSTS_ID_TOKEN:-}" ]; then
    log_info "Obtaining GitHub token via dd-octo-sts CLI..."
    # Policy name matches the .sts.yaml filename (without extension)

    # Run dd-octo-sts and capture only stdout (don't capture stderr to avoid error messages in token)
    local TOKEN_OUTPUT
    local TOKEN_EXIT_CODE
    TOKEN_OUTPUT=$(dd-octo-sts token --scope DataDog/java-profiler --policy async-profiler-build.ci 2>/tmp/dd-octo-sts-error.log)
    TOKEN_EXIT_CODE=$?

    if [ $TOKEN_EXIT_CODE -eq 0 ] && [ -n "${TOKEN_OUTPUT}" ]; then
      # Validate token format (GitHub tokens start with ghs_, ghp_, or look like JWT)
      if [[ "${TOKEN_OUTPUT}" =~ ^(ghs_|ghp_|v1\.|[A-Za-z0-9_-]+\.[A-Za-z0-9_-]+\.) ]]; then
        GITHUB_TOKEN="${TOKEN_OUTPUT}"
        log_info "GitHub token obtained via dd-octo-sts (expires in 1 hour)"
        return 0
      else
        log_warn "dd-octo-sts returned invalid token format (first 50 chars): ${TOKEN_OUTPUT:0:50}"
      fi
    else
      log_warn "dd-octo-sts token exchange failed (exit code: ${TOKEN_EXIT_CODE})"
      if [ -s /tmp/dd-octo-sts-error.log ]; then
        log_warn "dd-octo-sts error output:"
        cat /tmp/dd-octo-sts-error.log | head -10 >&2
      fi
    fi
  fi

  # Fall back to GITHUB_TOKEN environment variable
  if [ -n "${GITHUB_TOKEN:-}" ]; then
    log_info "Using GITHUB_TOKEN from environment"
    return 0
  fi

  return 1
}

if ! obtain_github_token; then
  log_error "Failed to obtain GitHub token"
  log_error "Options:"
  log_error "  1. Run in GitLab CI with dd-octo-sts-ci-base image and DDOCTOSTS_ID_TOKEN"
  log_error "  2. Set GITHUB_TOKEN env var (PAT with 'repo' scope)"
  exit 1
fi

# Create temporary directory for gh-pages content
WORK_DIR=$(mktemp -d)
trap "rm -rf ${WORK_DIR}" EXIT

log_info "Preparing gh-pages content in: ${WORK_DIR}"

# Clone gh-pages branch (or create if doesn't exist)
log_info "Cloning gh-pages branch..."
cd "${WORK_DIR}"

if git clone --depth 1 --branch gh-pages "https://x-access-token:${GITHUB_TOKEN}@github.com/${GITHUB_REPO}.git" pages 2>/dev/null; then
  cd pages
  log_info "Cloned existing gh-pages branch"
else
  log_info "Creating new gh-pages branch..."
  mkdir pages && cd pages
  git init
  git remote add origin "https://x-access-token:${GITHUB_TOKEN}@github.com/${GITHUB_REPO}.git"
  git checkout -b gh-pages
fi

# Create/update Jekyll config with baseurl for subpath deployment
cat > "_config.yml" <<EOF
title: Java Profiler Build - Test Dashboard
description: Test reports for dd-trace-java integration, benchmarks, and reliability
theme: jekyll-theme-minimal
baseurl: /java-profiler
EOF

# Ensure directory structure for history
mkdir -p _data integration benchmarks reliability

# ============================================
# HISTORY TRACKING
# ============================================
log_info "Updating integration test history..."
log_info "Results directory: ${RESULTS_BASE}"

# Check if results exist
if [ -d "${RESULTS_BASE}" ]; then
  log_info "Results directory exists, listing contents:"
  ls -la "${RESULTS_BASE}" || true
  log_info "Number of test configs: $(ls -1 "${RESULTS_BASE}" 2>/dev/null | wc -l)"
else
  log_warn "Results directory does not exist: ${RESULTS_BASE}"
fi

# Generate run JSON for this pipeline
RUN_JSON_FILE=$(mktemp)
trap "rm -rf ${WORK_DIR} ${RUN_JSON_FILE}" EXIT

log_info "Running generate-run-json.sh..."
if "${SCRIPT_DIR}/generate-run-json.sh" "${RESULTS_BASE}" > "${RUN_JSON_FILE}"; then
  log_info "Generated run JSON successfully"
  log_info "Run JSON size: $(wc -c < "${RUN_JSON_FILE}") bytes"
  log_info "Run JSON preview:"
  head -20 "${RUN_JSON_FILE}" || true

  # Update history (prepend new run, keep last MAX_HISTORY)
  log_info "Running update-history.sh..."
  if "${SCRIPT_DIR}/../common/update-history.sh" integration "${RUN_JSON_FILE}" "."; then
    log_info "Updated integration history"
  else
    log_warn "Failed to update history, error output above"
  fi
else
  log_warn "Failed to generate run JSON, error output:"
  log_warn "Showing last 100 lines of output:"
  tail -100 "${RUN_JSON_FILE}" || true

  log_warn ""
  log_warn "Checking first config directory for debugging:"
  first_config=$(find "${RESULTS_BASE}" -maxdepth 1 -type d ! -path "${RESULTS_BASE}" | head -1)
  if [ -n "$first_config" ]; then
    log_warn "Contents of $(basename "$first_config"):"
    ls -la "$first_config" || true
    log_warn ""
    log_warn "Sample log file content (if exists):"
    find "$first_config" -name "*.log" -type f | head -1 | xargs head -20 2>/dev/null || log_warn "No log files found"
  fi
fi

# Generate dashboard and index pages
log_info "Generating dashboard..."
if "${SCRIPT_DIR}/../common/generate-dashboard.sh" "." 2>&1; then
  log_info "Generated dashboard index.md"
  if [ -f "index.md" ]; then
    log_info "Dashboard size: $(wc -c < "index.md") bytes"
  fi
else
  log_warn "Failed to generate dashboard, error output above"
fi

log_info "Generating integration index..."
if "${SCRIPT_DIR}/../common/generate-index.sh" integration "." 2>&1; then
  log_info "Generated integration/index.md"
  if [ -f "integration/index.md" ]; then
    log_info "Integration index size: $(wc -c < "integration/index.md") bytes"
  fi
else
  log_warn "Failed to generate integration index, error output above"
fi

# ============================================
# DETAILED REPORTS (per-config reports for current run)
# ============================================
log_info "Generating detailed reports..."

TIMESTAMP=$(date -u +"%Y-%m-%d %H:%M UTC")

# Find all test result directories
RESULT_DIRS=()
while IFS= read -r -d '' dir; do
  if [[ "${dir}" == *"/history"* ]]; then
    continue
  fi
  if ls "${dir}"/*.log &>/dev/null 2>&1; then
    RESULT_DIRS+=("${dir}")
  fi
done < <(find "${RESULTS_BASE}" -mindepth 1 -maxdepth 1 -type d -print0 2>/dev/null | sort -z)

if [ ${#RESULT_DIRS[@]} -eq 0 ]; then
  log_warn "No test results found in ${RESULTS_BASE}"
fi

log_info "Found ${#RESULT_DIRS[@]} test configuration(s)"

# Create reports directory for detailed per-config reports
mkdir -p reports

# Process each configuration
for dir in "${RESULT_DIRS[@]}"; do
  config_name=$(basename "${dir}")
  log_info "Processing: ${config_name}"

  # Generate detailed report
  report_file="reports/${config_name}.md"
  if "${SCRIPT_DIR}/generate-report.sh" "${dir}" "${WORK_DIR}/pages/${report_file}" 2>/dev/null; then
    # Add front matter for Jekyll
    tmp_file=$(mktemp)
    cat > "${tmp_file}" <<EOF
---
layout: default
title: ${config_name}
---

EOF
    cat "${WORK_DIR}/pages/${report_file}" >> "${tmp_file}"
    mv "${tmp_file}" "${WORK_DIR}/pages/${report_file}"
  else
    log_warn "Failed to generate report for ${config_name}"
  fi
done

# Commit and push
log_info "Committing changes..."
git add -A
if git diff --staged --quiet; then
  log_info "No changes to commit"
else
  git config user.email "ci@datadoghq.com"
  git config user.name "CI Bot"
  git commit -m "Update integration test reports - ${TIMESTAMP}"

  log_info "Pushing to gh-pages..."
  git push origin gh-pages --force

  log_info "✅ Reports published successfully!"
  log_info "View at: ${PAGES_URL}"
fi

echo ""
echo "PAGES_URL=${PAGES_URL}"
