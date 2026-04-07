#!/bin/bash

# publish-gh-pages.sh - Publish benchmark reports to GitHub Pages
#
# Usage: publish-gh-pages.sh [reports-dir]
#
# Updates benchmark history and regenerates GitHub Pages site.
# Reports are available at: https://datadog.github.io/async-profiler-build/benchmarks/
#
# In CI: Uses Octo-STS for secure, short-lived GitHub tokens (no secrets needed)
# Locally: Use 'devflow gitlab auth' for Octo-STS, or set GITHUB_TOKEN env var

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="${SCRIPT_DIR}/../.."
REPORTS_DIR="${1:-${PROJECT_ROOT}/reports}"
export MAX_HISTORY=10

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
RUN_JSON_FILE=$(mktemp)
# shellcheck disable=SC2064  # Intentional: capture values at setup time
trap "rm -rf ${WORK_DIR} ${RUN_JSON_FILE}" EXIT

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

# Create Jekyll config if not exists
if [ ! -f "_config.yml" ]; then
  cat > "_config.yml" <<EOF
title: Java Profiler Build - Test Dashboard
description: Test reports for dd-trace-java integration, benchmarks, and reliability
theme: jekyll-theme-minimal
EOF
fi

# Ensure directory structure for history
mkdir -p _data integration benchmarks reliability

# ============================================
# HISTORY TRACKING
# ============================================
log_info "Updating benchmark test history..."

# Generate run JSON for this pipeline
if "${SCRIPT_DIR}/generate-run-json.sh" "${REPORTS_DIR}" > "${RUN_JSON_FILE}" 2>/dev/null; then
  log_info "Generated run JSON"

  # Update history (prepend new run, keep last MAX_HISTORY)
  if "${SCRIPT_DIR}/../common/update-history.sh" benchmarks "${RUN_JSON_FILE}" "." 2>/dev/null; then
    log_info "Updated benchmark history"
  else
    log_warn "Failed to update history"
  fi
else
  log_warn "Failed to generate run JSON"
fi

# Generate dashboard and index pages
log_info "Generating dashboard..."
if "${SCRIPT_DIR}/../common/generate-dashboard.sh" "." 2>&1; then
  log_info "Generated dashboard index.md"
else
  log_warn "Failed to generate dashboard"
fi

log_info "Generating benchmark index..."
if "${SCRIPT_DIR}/../common/generate-index.sh" benchmarks "." 2>/dev/null; then
  log_info "Generated benchmarks/index.md"
else
  log_warn "Failed to generate benchmark index"
fi

# Commit and push
TIMESTAMP=$(date -u +"%Y-%m-%d %H:%M UTC")
log_info "Committing changes..."
git add -A
if git diff --staged --quiet; then
  log_info "No changes to commit"
else
  git config user.email "ci@datadoghq.com"
  git config user.name "CI Bot"
  git commit -m "Update benchmark reports - ${TIMESTAMP}"

  log_info "Pushing to gh-pages..."
  git push origin gh-pages --force

  log_info "Reports published successfully!"
  log_info "View at: ${PAGES_URL}/benchmarks/"
fi

echo ""
echo "PAGES_URL=${PAGES_URL}/benchmarks/"
