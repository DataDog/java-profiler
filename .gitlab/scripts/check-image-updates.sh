#!/bin/bash
# check-image-updates.sh - Detect available image updates in registry
#
# Compares current image references in YAML files against the registry
# and outputs a JSON array of needed updates.
#
# Usage: ./scripts/check-image-updates.sh
# Output: JSON array to stdout
#
# Required environment:
#   CI_JOB_TOKEN - GitLab CI job token (for API access)
#   CI_PROJECT_ID - GitLab project ID (auto-set in CI)
#
# Optional environment:
#   GITLAB_URL - GitLab instance URL (default: https://gitlab.ddbuild.io)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Configuration
REGISTRY="registry.ddbuild.io"
GITLAB_URL="${GITLAB_URL:-https://gitlab.ddbuild.io}"
GITLAB_PROJECT_PATH="DataDog/java-profiler"

# Colors for stderr output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

log_info() { echo -e "${GREEN}[INFO]${NC} $*" >&2; }
log_warn() { echo -e "${YELLOW}[WARN]${NC} $*" >&2; }
log_error() { echo -e "${RED}[ERROR]${NC} $*" >&2; }

# Image definitions: var_name|yaml_file|tag_suffix|job_name|registry_path
# registry_path is relative to REGISTRY/ci/
IMAGE_DEFS=(
    "BUILD_IMAGE_X64|.gitlab/build-deploy/.gitlab-ci.yml|x64-base|image-base-build-x64|async-profiler-build"
    "BUILD_IMAGE_X64_2_17|.gitlab/build-deploy/.gitlab-ci.yml|x64-2.17-base|image-base-build-x64-2.17|async-profiler-build"
    "BUILD_IMAGE_X64_MUSL|.gitlab/build-deploy/.gitlab-ci.yml|x64-musl-base|image-base-build-x64-musl|async-profiler-build"
    "BUILD_IMAGE_ARM64|.gitlab/build-deploy/.gitlab-ci.yml|arm64-base|image-base-build-arm64|async-profiler-build"
    "BUILD_IMAGE_ARM64_MUSL|.gitlab/build-deploy/.gitlab-ci.yml|arm64-musl-base|image-base-build-arm64-musl|async-profiler-build"
    "DATADOG_CI_IMAGE|.gitlab/build-deploy/.gitlab-ci.yml|datadog-ci|image-datadog-ci|async-profiler-build"
    "BENCHMARK_IMAGE_AMD64|.gitlab/benchmarks/images.yml|amd64-benchmarks|image-benchmarks-amd64|async-profiler-build-amd64"
    "BENCHMARK_IMAGE_ARM64|.gitlab/benchmarks/images.yml|arm64-benchmarks|image-benchmarks-arm64|async-profiler-build-arm64"
)

# Extract current image reference from YAML file
# Returns: full image reference (e.g., registry.../v12345-x64-base@sha256:abc...)
get_current_ref() {
    local var_name="$1"
    local yaml_file="$2"
    local full_path="${PROJECT_ROOT}/${yaml_file}"

    if [[ ! -f "$full_path" ]]; then
        log_error "YAML file not found: $full_path"
        return 1
    fi

    # Match lines like: BUILD_IMAGE_X64: registry.../...
    # Handle both with and without quotes
    # Use awk to split on first colon after variable name
    grep -E "^\s*${var_name}:" "$full_path" | \
        sed "s/^[[:space:]]*${var_name}:[[:space:]]*//" | \
        tr -d ' "'"'" | \
        head -1
}

# Extract pipeline ID from image tag
# Input: v95799584-x64-base or registry.../v95799584-x64-base@sha256:...
# Output: 95799584
extract_pipeline_id() {
    local ref="$1"
    echo "$ref" | grep -oE 'v[0-9]+' | head -1 | sed 's/^v//'
}

# Extract tag from full image reference
# Input: registry.../v95799584-x64-base@sha256:abc...
# Output: v95799584-x64-base
extract_tag() {
    local ref="$1"
    echo "$ref" | sed 's/@sha256:.*//' | rev | cut -d':' -f1 | rev
}

# Query registry for latest tag matching pattern
# Returns the tag with highest pipeline ID
get_latest_tag() {
    local registry_path="$1"
    local tag_suffix="$2"
    local full_registry="${REGISTRY}/ci/${registry_path}"

    log_info "Querying registry: ${full_registry} for *-${tag_suffix}"

    # List all tags, filter by suffix, sort by pipeline ID (numeric), get latest
    local tags
    tags=$(crane ls "${full_registry}" 2>/dev/null || echo "")

    if [[ -z "$tags" ]]; then
        log_warn "No tags found in ${full_registry}"
        return 1
    fi

    # Filter tags matching pattern v<number>-<suffix>
    local matching_tags
    matching_tags=$(echo "$tags" | grep -E "^v[0-9]+-${tag_suffix}$" || true)

    if [[ -z "$matching_tags" ]]; then
        log_warn "No tags matching pattern *-${tag_suffix}"
        return 1
    fi

    # Sort by pipeline ID (extract number after 'v', sort numerically)
    echo "$matching_tags" | \
        awk -F'-' '{print $1}' | \
        sed 's/^v//' | \
        sort -n | \
        tail -1 | \
        xargs -I{} echo "v{}-${tag_suffix}"
}

# Get SHA256 digest for an image tag
get_digest() {
    local registry_path="$1"
    local tag="$2"
    local full_image="${REGISTRY}/ci/${registry_path}:${tag}"

    crane digest "${full_image}" 2>/dev/null
}

# Query GitLab API to find job URL within a pipeline
get_job_url() {
    local pipeline_id="$1"
    local job_name="$2"

    if [[ -z "${CI_JOB_TOKEN:-}" ]]; then
        log_warn "CI_JOB_TOKEN not set, cannot query GitLab API for job URL"
        echo ""
        return 0
    fi

    # URL-encode the project path
    local encoded_project
    encoded_project=$(echo -n "${GITLAB_PROJECT_PATH}" | jq -sRr @uri)

    local api_url="${GITLAB_URL}/api/v4/projects/${encoded_project}/pipelines/${pipeline_id}/jobs"

    log_info "Querying GitLab API for job '${job_name}' in pipeline ${pipeline_id}"

    local response
    response=$(curl -s --fail \
        -H "JOB-TOKEN: ${CI_JOB_TOKEN}" \
        "${api_url}" 2>/dev/null || echo "[]")

    # Find the job with matching name and extract web_url
    local job_url
    job_url=$(echo "$response" | jq -r ".[] | select(.name == \"${job_name}\") | .web_url" 2>/dev/null | head -1)

    if [[ -n "$job_url" && "$job_url" != "null" ]]; then
        echo "$job_url"
    else
        log_warn "Job '${job_name}' not found in pipeline ${pipeline_id}"
        # Fallback to pipeline URL
        echo "${GITLAB_URL}/${GITLAB_PROJECT_PATH}/-/pipelines/${pipeline_id}"
    fi
}

# Main detection logic
main() {
    log_info "Starting image update detection..."

    # Verify crane is available
    if ! command -v crane &>/dev/null; then
        log_error "crane command not found. Please install google/go-containerregistry"
        exit 1
    fi

    # Verify jq is available
    if ! command -v jq &>/dev/null; then
        log_error "jq command not found. Please install jq"
        exit 1
    fi

    cd "$PROJECT_ROOT"

    local updates="[]"
    local checked=0
    local found=0

    for def in "${IMAGE_DEFS[@]}"; do
        IFS='|' read -r var_name yaml_file tag_suffix job_name registry_path <<< "$def"
        ((checked++))

        log_info "Checking ${var_name}..."

        # Get current reference from YAML
        local current_ref
        current_ref=$(get_current_ref "$var_name" "$yaml_file" || echo "")
        if [[ -z "$current_ref" ]]; then
            log_warn "Could not find ${var_name} in ${yaml_file}, skipping"
            continue
        fi

        local current_tag
        current_tag=$(extract_tag "$current_ref")
        local current_pipeline_id
        current_pipeline_id=$(extract_pipeline_id "$current_ref")

        log_info "  Current: ${current_tag} (pipeline ${current_pipeline_id})"

        # Get latest tag from registry
        local latest_tag
        latest_tag=$(get_latest_tag "$registry_path" "$tag_suffix" || echo "")
        if [[ -z "$latest_tag" ]]; then
            log_warn "  Could not determine latest tag, skipping"
            continue
        fi

        local latest_pipeline_id
        latest_pipeline_id=$(extract_pipeline_id "$latest_tag")

        log_info "  Latest:  ${latest_tag} (pipeline ${latest_pipeline_id})"

        # Compare pipeline IDs
        if [[ "$latest_pipeline_id" -gt "$current_pipeline_id" ]]; then
            log_info "  UPDATE AVAILABLE: ${current_tag} -> ${latest_tag}"
            ((found++))

            # Get digest for new image
            local new_digest
            new_digest=$(get_digest "$registry_path" "$latest_tag" || echo "")
            if [[ -z "$new_digest" ]]; then
                log_warn "  Could not get digest for ${latest_tag}, skipping"
                continue
            fi

            # Get job URL from GitLab API
            local job_url
            job_url=$(get_job_url "$latest_pipeline_id" "$job_name")

            # Build full image reference
            local new_full_ref="${REGISTRY}/ci/${registry_path}:${latest_tag}@${new_digest}"

            # Extract current digest for comparison
            local current_digest
            current_digest=$(echo "$current_ref" | grep -oE 'sha256:[a-f0-9]+' || echo "")

            # Add to updates array
            updates=$(echo "$updates" | jq \
                --arg var_name "$var_name" \
                --arg yaml_file "$yaml_file" \
                --arg current_tag "$current_tag" \
                --arg current_digest "$current_digest" \
                --arg new_tag "$latest_tag" \
                --arg new_digest "$new_digest" \
                --arg new_full_ref "$new_full_ref" \
                --arg job_url "$job_url" \
                --arg job_name "$job_name" \
                '. + [{
                    var_name: $var_name,
                    yaml_file: $yaml_file,
                    current_tag: $current_tag,
                    current_digest: $current_digest,
                    new_tag: $new_tag,
                    new_digest: $new_digest,
                    new_full_ref: $new_full_ref,
                    job_url: $job_url,
                    job_name: $job_name
                }]')
        else
            log_info "  Up to date"
        fi
    done

    log_info "Detection complete: checked ${checked} images, found ${found} updates"

    # Output JSON to stdout
    echo "$updates" | jq .
}

main "$@"
