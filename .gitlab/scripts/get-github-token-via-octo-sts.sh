#!/bin/bash

# Exchange GitLab CI OIDC Token for GitHub Token via Datadog Octo-STS
# This script uses GitLab's OIDC provider to obtain a short-lived GitHub token
# without requiring any stored secrets in the GitLab project.

set -euo pipefail

# Configuration
OCTO_STS_DOMAIN="${OCTO_STS_DOMAIN:-octo-sts.chainguard.dev}"
OCTO_STS_AUDIENCE="${OCTO_STS_AUDIENCE:-dd-octo-sts}"
OCTO_STS_SCOPE="${OCTO_STS_SCOPE:-DataDog/java-profiler}"
OCTO_STS_POLICY="${OCTO_STS_POLICY:-gist-update}"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

function log_info() {
  echo -e "${GREEN}[INFO]${NC} $*" >&2
}

function log_warn() {
  echo -e "${YELLOW}[WARN]${NC} $*" >&2
}

function log_error() {
  echo -e "${RED}[ERROR]${NC} $*" >&2
}

# Validate GitLab CI environment
if [ -z "${CI:-}" ]; then
  log_error "This script must run in GitLab CI environment"
  log_error "CI environment variable not set"
  exit 1
fi

# Check for GitLab OIDC token
if [ -z "${CI_JOB_JWT_V2:-}" ]; then
  log_error "GitLab OIDC token (CI_JOB_JWT_V2) not available"
  log_error "Ensure the CI job has 'id_tokens:' configured"
  exit 1
fi

log_info "Exchanging GitLab OIDC token for GitHub token via Octo-STS..."
log_info "Scope: ${OCTO_STS_SCOPE}"
log_info "Policy: ${OCTO_STS_POLICY}"

# Build Octo-STS exchange URL
EXCHANGE_URL="https://${OCTO_STS_DOMAIN}/sts/exchange?scope=${OCTO_STS_SCOPE}&identity=${OCTO_STS_POLICY}"

log_info "Exchange URL: ${EXCHANGE_URL}"

# Exchange OIDC token for GitHub token
response=$(curl -s -w "\n%{http_code}" \
  -X POST \
  -H "Authorization: Bearer ${CI_JOB_JWT_V2}" \
  -H "Accept: application/json" \
  "${EXCHANGE_URL}")

# Split response into body and status code
http_code=$(echo "${response}" | tail -n1)
body=$(echo "${response}" | sed '$d')

log_info "HTTP status: ${http_code}"
log_info "Response body: ${body}"

# Check HTTP status code
if [ "${http_code}" -ne 200 ]; then
  log_error "Octo-STS token exchange failed (HTTP ${http_code})"
  log_error "Response: ${body}"

  if [ "${http_code}" -eq 401 ]; then
    log_error "Authentication failed - OIDC token was rejected"
    log_error "Possible causes:"
    log_error "  1. Trust policy not configured for this repository"
    log_error "  2. Trust policy doesn't match GitLab CI claims"
    log_error "  3. Octo-STS configuration issue"
  elif [ "${http_code}" -eq 404 ]; then
    log_error "Trust policy not found"
    log_error "Expected location: https://github.com/${OCTO_STS_SCOPE}/.github/chainguard/${OCTO_STS_POLICY}.sts.yaml"
  fi

  exit 1
fi

# Extract token from response (expecting JSON: {"token": "ghs_..."})
github_token=$(echo "${body}" | grep -o '"token":"[^"]*"' | cut -d'"' -f4)

if [ -z "${github_token}" ]; then
  log_error "Failed to extract GitHub token from response"
  log_error "Response: ${body}"
  exit 1
fi

log_info "✅ Successfully obtained GitHub token (expires in 1 hour)"

# Output token to stdout (caller can capture with TOKEN=$(./get-github-token-via-octo-sts.sh))
echo "${github_token}"
