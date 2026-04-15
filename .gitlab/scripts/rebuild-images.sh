#!/bin/bash
# rebuild-images.sh - Build and push CI images, then create a GitHub PR with updated references
#
# Usage: REBUILD_IMAGES="x64,arm64" ./scripts/rebuild-images.sh
#        REBUILD_IMAGES="" ./scripts/rebuild-images.sh   # builds all images
#
# Required environment (auto-set in GitLab CI):
#   CI_PIPELINE_ID  - Pipeline ID used as image tag prefix
#   CI_JOB_URL      - URL of the CI job (included in PR comment)
#
# Optional environment:
#   REBUILD_IMAGES  - Comma/space-separated short names; empty = all
#   DRY_RUN         - Set to 'true' to print plan and exit without building
#   REGISTRY        - Override registry (default: registry.ddbuild.io)
#
# Base image variables come from .gitlab/build-deploy/images.yml which is
# included in the root pipeline and available as CI variables:
#   OPENJDK_BASE_IMAGE, OPENJDK_BASE_IMAGE_ARM64, OPENJDK_BASE_IMAGE_MUSL,
#   OPENJDK_BASE_IMAGE_ARM64_MUSL, BASE_IMAGE_LIBC_2_17, BASE_BENCHMARK_IMAGE_NAME,
#   DOCKER_IMAGE

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

REGISTRY="${REGISTRY:-registry.ddbuild.io}"

# Colors for stderr
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

log_info()  { echo -e "${GREEN}[INFO]${NC} $*" >&2; }
log_warn()  { echo -e "${YELLOW}[WARN]${NC} $*" >&2; }
log_error() { echo -e "${RED}[ERROR]${NC} $*" >&2; }

usage() {
    echo "Usage: REBUILD_IMAGES=\"<names>\" $0" >&2
    echo "" >&2
    echo "Valid short names:" >&2
    echo "  x64            glibc x86_64 build image" >&2
    echo "  x64-2.17       glibc 2.17 (centos7) x86_64 build image" >&2
    echo "  x64-musl       musl x86_64 build image" >&2
    echo "  arm64          glibc arm64 build image" >&2
    echo "  arm64-musl     musl arm64 build image" >&2
    echo "  datadog-ci     datadog-ci utility image" >&2
    echo "  benchmarks-amd64  benchmark runner image for amd64" >&2
    echo "  benchmarks-arm64  benchmark runner image for arm64" >&2
    echo "" >&2
    echo "Leave REBUILD_IMAGES empty to rebuild all images." >&2
}

# IMAGE_DEFS format (pipe-delimited):
#   short_name | VAR_NAME | yaml_file | tag_suffix | dockerfile | platform | registry_path | base_image_var
#
# base_image_var is the name of the env var holding the base image (empty if none needed).
IMAGE_DEFS=(
    "x64|BUILD_IMAGE_X64|.gitlab/build-deploy/.gitlab-ci.yml|x64-base|.gitlab/base/Dockerfile|linux/amd64|async-profiler-build|OPENJDK_BASE_IMAGE"
    "x64-2.17|BUILD_IMAGE_X64_2_17|.gitlab/build-deploy/.gitlab-ci.yml|x64-2.17-base|.gitlab/base/centos7/Dockerfile|linux/amd64|async-profiler-build|BASE_IMAGE_LIBC_2_17"
    "x64-musl|BUILD_IMAGE_X64_MUSL|.gitlab/build-deploy/.gitlab-ci.yml|x64-musl-base|.gitlab/base/Dockerfile|linux/amd64|async-profiler-build|OPENJDK_BASE_IMAGE_MUSL"
    "arm64|BUILD_IMAGE_ARM64|.gitlab/build-deploy/.gitlab-ci.yml|arm64-base|.gitlab/base/Dockerfile|linux/arm64|async-profiler-build|OPENJDK_BASE_IMAGE_ARM64"
    "arm64-musl|BUILD_IMAGE_ARM64_MUSL|.gitlab/build-deploy/.gitlab-ci.yml|arm64-musl-base|.gitlab/base/Dockerfile|linux/arm64|async-profiler-build|OPENJDK_BASE_IMAGE_ARM64_MUSL"
    "datadog-ci|DATADOG_CI_IMAGE|.gitlab/build-deploy/.gitlab-ci.yml|datadog-ci|.gitlab/Dockerfile.datadog-ci|linux/amd64|async-profiler-build|"
    "benchmarks-amd64|BENCHMARK_IMAGE_AMD64|.gitlab/benchmarks/images.yml|amd64-benchmarks|.gitlab/benchmarks/docker/Dockerfile|linux/amd64|async-profiler-build-amd64|BASE_BENCHMARK_IMAGE_NAME"
    "benchmarks-arm64|BENCHMARK_IMAGE_ARM64|.gitlab/benchmarks/images.yml|arm64-benchmarks|.gitlab/benchmarks/docker/Dockerfile|linux/arm64|async-profiler-build-arm64|BASE_BENCHMARK_IMAGE_NAME"
)

# Extract current image reference from YAML file (reused from check-image-updates.sh)
get_current_ref() {
    local var_name="$1"
    local yaml_file="$2"
    local full_path="${PROJECT_ROOT}/${yaml_file}"

    if [[ ! -f "$full_path" ]]; then
        log_error "YAML file not found: $full_path"
        return 1
    fi

    grep -E "^\s*${var_name}:" "$full_path" | \
        sed "s/^[[:space:]]*${var_name}:[[:space:]]*//" | \
        tr -d ' "'"'" | \
        head -1
}

# Extract tag from full image reference (reused from check-image-updates.sh)
extract_tag() {
    local ref="$1"
    echo "$ref" | sed 's/@sha256:.*//' | rev | cut -d':' -f1 | rev
}

# Build one image and return its digest.
# Arguments: short_name tag dockerfile platform registry_path base_image
# Prints the sha256 digest to stdout on success.
build_image() {
    local short_name="$1"
    local tag="$2"
    local dockerfile="$3"
    local platform="$4"
    local registry_path="$5"
    local base_image="$6"

    local full_tag="${REGISTRY}/ci/${registry_path}:${tag}"
    local meta_file
    meta_file=$(mktemp)

    local build_args=()
    [[ -n "$base_image" ]] && build_args+=(--build-arg "BASE_IMAGE=${base_image}")
    [[ -n "${CI_JOB_TOKEN:-}" ]] && build_args+=(--build-arg "CI_JOB_TOKEN=${CI_JOB_TOKEN}")

    # benchmarks images change into the docker sub-directory before building
    local build_context="."
    local dockerfile_flag="-f ${PROJECT_ROOT}/${dockerfile}"
    if [[ "$short_name" == benchmarks-* ]]; then
        build_context="${PROJECT_ROOT}/.gitlab/benchmarks/docker"
        dockerfile_flag="-f ${PROJECT_ROOT}/${dockerfile}"
    elif [[ "$dockerfile" == */ ]]; then
        # dockerfile is a directory (build context)
        build_context="${PROJECT_ROOT}/${dockerfile}"
        dockerfile_flag=""
    fi

    log_info "  Running: docker buildx build --platform=${platform} --tag=${full_tag} ... --push"

    # shellcheck disable=SC2086
    docker buildx build \
        --platform "${platform}" \
        --tag "${full_tag}" \
        "${build_args[@]}" \
        --push \
        --metadata-file "${meta_file}" \
        ${dockerfile_flag} \
        "${build_context}"

    ddsign sign "${full_tag}" --docker-metadata-file "${meta_file}" >&2

    # Get manifest digest from registry: more reliable than --metadata-file
    # which ddsign corrupts for some image types.
    docker buildx imagetools inspect "${full_tag}" 2>/dev/null \
        | awk '/Digest:/{print $NF; exit}'
}

find_def() {
    local target_name="$1"
    for def in "${IMAGE_DEFS[@]}"; do
        local short_name
        short_name=$(cut -d'|' -f1 <<< "$def")
        if [[ "$short_name" == "$target_name" ]]; then
            echo "$def"
            return 0
        fi
    done
    return 1
}

main() {
    cd "$PROJECT_ROOT"

    # Build list of all valid short names
    local all_names=()
    for def in "${IMAGE_DEFS[@]}"; do
        all_names+=("$(cut -d'|' -f1 <<< "$def")")
    done

    # Parse REBUILD_IMAGES (split on comma and/or whitespace)
    local selected=()
    if [[ -n "${REBUILD_IMAGES:-}" ]]; then
        IFS=', ' read -r -a selected <<< "${REBUILD_IMAGES}"
        # Validate
        for name in "${selected[@]}"; do
            if ! find_def "$name" > /dev/null 2>&1; then
                log_error "Unknown image name: '${name}'"
                usage
                exit 1
            fi
        done
    else
        selected=("${all_names[@]}")
    fi

    log_info "Images to build: ${selected[*]}"

    if [[ "${DRY_RUN:-}" == "true" ]]; then
        log_info "DRY RUN: would build the following images:"
        for name in "${selected[@]}"; do
            local def
            def=$(find_def "$name")
            IFS='|' read -r s_name var_name yaml_file tag_suffix dockerfile platform registry_path base_image_var <<< "$def"
            local tag="v${CI_PIPELINE_ID:-DRY_RUN}-${tag_suffix}"
            log_info "  ${name}: ${REGISTRY}/ci/${registry_path}:${tag} (${platform})"
        done
        exit 0
    fi

    local updates="[]"
    local failed=0

    for name in "${selected[@]}"; do
        local def
        def=$(find_def "$name")
        IFS='|' read -r s_name var_name yaml_file tag_suffix dockerfile platform registry_path base_image_var <<< "$def"

        local base_image=""
        if [[ -n "$base_image_var" ]]; then
            base_image="${!base_image_var:-}"
            if [[ -z "$base_image" ]]; then
                log_warn "Base image variable ${base_image_var} is not set for ${name}, building without BASE_IMAGE arg"
            fi
        fi

        local new_tag="v${CI_PIPELINE_ID}-${tag_suffix}"
        log_info "Building ${name} (${new_tag})..."

        local digest
        if ! digest=$(build_image "$name" "$new_tag" "$dockerfile" "$platform" "$registry_path" "$base_image"); then
            log_error "Build failed for: ${name}"
            (( failed++ )) || true
            continue
        fi

        if [[ -z "$digest" || "$digest" == "null" ]]; then
            log_error "Build succeeded but digest is empty for ${name} (ddsign may have corrupted metadata)"
            (( failed++ )) || true
            continue
        fi

        local new_full_ref="${REGISTRY}/ci/${registry_path}:${new_tag}@${digest}"
        local current_ref
        current_ref=$(get_current_ref "$var_name" "$yaml_file" || echo "")
        local current_tag=""
        [[ -n "$current_ref" ]] && current_tag=$(extract_tag "$current_ref")
        local current_digest
        current_digest=$(echo "$current_ref" | grep -oE 'sha256:[a-f0-9]+' || echo "")
        local job_url="${CI_JOB_URL:-}"

        updates=$(echo "$updates" | jq \
            --arg var_name "$var_name" \
            --arg yaml_file "$yaml_file" \
            --arg current_tag "$current_tag" \
            --arg current_digest "$current_digest" \
            --arg new_tag "$new_tag" \
            --arg new_digest "$digest" \
            --arg new_full_ref "$new_full_ref" \
            --arg job_url "$job_url" \
            --arg job_name "rebuild-images" \
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

    done

    local update_count
    update_count=$(echo "$updates" | jq 'length')

    # Always write updates.json before exiting so the PR job always has valid JSON
    echo "$updates" | jq . > "${PROJECT_ROOT}/updates.json"
    log_info "Wrote ${update_count} update(s) to updates.json"

    if [[ "$update_count" -eq 0 ]]; then
        log_error "No successful builds; nothing to create a PR for"
        exit 1
    fi

    exit $failed
}

main "$@"
