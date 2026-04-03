#!/bin/bash

set -euo pipefail

# Download dd-java-agent and ddprof snapshot artifacts from Maven

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

# Maven snapshot repository
SNAPSHOT_REPO="https://central.sonatype.com/repository/maven-snapshots/"

# Default versions (can be overridden via environment)
DEFAULT_DD_TRACE_VERSION="1.50.0-SNAPSHOT"

# Output directory for downloaded artifacts
OUTPUT_DIR="${OUTPUT_DIR:-${PROJECT_ROOT}}"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

function log_info() {
  echo -e "${GREEN}[INFO]${NC} $*"
}

function log_warn() {
  echo -e "${YELLOW}[WARN]${NC} $*"
}

function log_error() {
  echo -e "${RED}[ERROR]${NC} $*"
}

function detect_latest_snapshot_version() {
  local group_id=$1
  local artifact_id=$2
  local repo_url=$3

  # Convert group_id to path (com.datadoghq -> com/datadoghq)
  local group_path=$(echo "${group_id}" | tr '.' '/')

  # Construct metadata URL
  local metadata_url="${repo_url}${group_path}/${artifact_id}/maven-metadata.xml"

  # Log to stderr so it doesn't interfere with return value
  echo -e "${GREEN}[INFO]${NC} Querying for latest ${artifact_id} version from metadata" >&2

  # Fetch metadata
  local metadata=$(curl -fsSL "${metadata_url}" 2>/dev/null || echo "")

  if [ -z "${metadata}" ]; then
    echo -e "${RED}[ERROR]${NC} Could not fetch metadata from ${metadata_url}" >&2
    return 1
  fi

  # Extract latest version using sed (portable across macOS and Linux)
  local latest_version=$(echo "${metadata}" | sed -n 's/.*<latest>\(.*\)<\/latest>.*/\1/p')

  # Validate that latest version is vanilla (no branch name)
  # Vanilla patterns: X.Y.Z-SNAPSHOT or X.Y.Z-DD-SNAPSHOT
  if [ -n "${latest_version}" ]; then
    if ! echo "${latest_version}" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+(-DD)?-SNAPSHOT$'; then
      echo -e "${YELLOW}[WARN]${NC} Latest version '${latest_version}' contains branch name, searching for vanilla snapshot..." >&2
      latest_version=""
    fi
  fi

  if [ -z "${latest_version}" ]; then
    # Fallback: try to find latest from versions list
    # Extract all versions, filter for vanilla SNAPSHOT (no branch names)
    # Vanilla patterns: X.Y.Z-SNAPSHOT or X.Y.Z-DD-SNAPSHOT
    # Reject patterns with branch names: X.Y.Z-branch_name-SNAPSHOT
    latest_version=$(echo "${metadata}" | \
      sed -n 's/.*<version>\(.*\)<\/version>.*/\1/p' | \
      grep -E '^[0-9]+\.[0-9]+\.[0-9]+(-DD)?-SNAPSHOT$' | \
      sort -V | \
      tail -1 || echo "")
  fi

  if [ -z "${latest_version}" ]; then
    echo -e "${RED}[ERROR]${NC} Could not detect latest version for ${artifact_id}" >&2
    return 1
  fi

  echo -e "${GREEN}[INFO]${NC} Detected latest version: ${latest_version}" >&2
  echo "${latest_version}"
}

function usage() {
  cat << EOF
Usage: $0 [OPTIONS]

Download dd-java-agent and ddprof snapshot artifacts from Maven.

OPTIONS:
  --dd-trace-version <version>  dd-java-agent version (default: auto-detect from Maven)
  --ddprof-version <version>    ddprof version (auto-detected from build.env, CURRENT_VERSION, or Maven)
  --output-dir <dir>            Output directory (default: ${OUTPUT_DIR})
  --skip-ddprof                 Skip ddprof download (use when ddprof.jar already available)
  --auto-detect                 Force auto-detection even if versions are set
  --help                        Show this help message

ENVIRONMENT VARIABLES:
  DD_TRACE_VERSION              Override dd-java-agent version
  DDPROF_VERSION                Override ddprof version
  CURRENT_VERSION               Auto-detected ddprof version from CI (build.env)
  OUTPUT_DIR                    Output directory for artifacts

OUTPUTS:
  dd-java-agent-original.jar    Downloaded dd-java-agent artifact
  ddprof.jar                    Downloaded ddprof artifact

NOTES:
  - If no version is specified, the script will attempt to auto-detect
    the latest SNAPSHOT version from the Maven repository
  - Auto-detection queries maven-metadata.xml from OSSRH
  - For CI/production use, explicit versions are recommended

EXAMPLES:
  # Download with auto-detected versions
  $0

  # Force auto-detection (ignore environment variables)
  $0 --auto-detect

  # Download specific versions
  $0 --dd-trace-version 1.49.0-SNAPSHOT --ddprof-version 1.35.0-DD-SNAPSHOT

  # Download to specific directory
  $0 --output-dir /tmp/artifacts
EOF
}

# Parse command line arguments
AUTO_DETECT=false
SKIP_DDPROF=false
DD_TRACE_VERSION_ARG=""
DDPROF_VERSION_ARG=""
while [ $# -gt 0 ]; do
  case "$1" in
    --dd-trace-version)
      DD_TRACE_VERSION_ARG="$2"
      shift 2
      ;;
    --ddprof-version)
      DDPROF_VERSION_ARG="$2"
      shift 2
      ;;
    --output-dir)
      OUTPUT_DIR="$2"
      shift 2
      ;;
    --skip-ddprof)
      SKIP_DDPROF=true
      shift
      ;;
    --auto-detect)
      AUTO_DETECT=true
      shift
      ;;
    --help)
      usage
      exit 0
      ;;
    *)
      log_error "Unknown option: $1"
      usage
      exit 1
      ;;
  esac
done

# Determine dd-trace-java version
if [ "${AUTO_DETECT}" = "true" ]; then
  log_info "Auto-detect flag set, detecting latest dd-java-agent version..."
  if ! DD_TRACE_VERSION=$(detect_latest_snapshot_version "com.datadoghq" "dd-java-agent" "${SNAPSHOT_REPO}"); then
    log_warn "Auto-detection failed, using default: ${DEFAULT_DD_TRACE_VERSION}"
    DD_TRACE_VERSION="${DEFAULT_DD_TRACE_VERSION}"
  fi
elif [ -n "${DD_TRACE_VERSION_ARG}" ]; then
  DD_TRACE_VERSION="${DD_TRACE_VERSION_ARG}"
elif [ -n "${DD_TRACE_VERSION:-}" ]; then
  DD_TRACE_VERSION="${DD_TRACE_VERSION}"
else
  # Auto-detect latest
  log_info "No dd-java-agent version specified, detecting latest..."
  if ! DD_TRACE_VERSION=$(detect_latest_snapshot_version "com.datadoghq" "dd-java-agent" "${SNAPSHOT_REPO}"); then
    log_warn "Auto-detection failed, using default: ${DEFAULT_DD_TRACE_VERSION}"
    DD_TRACE_VERSION="${DEFAULT_DD_TRACE_VERSION}"
  fi
fi

# Determine ddprof version (skip if --skip-ddprof flag is set)
if [ "${SKIP_DDPROF}" = "false" ]; then
  if [ "${AUTO_DETECT}" = "true" ]; then
    log_info "Auto-detect flag set, detecting latest ddprof version..."
    if ! DDPROF_VERSION=$(detect_latest_snapshot_version "com.datadoghq" "ddprof" "${SNAPSHOT_REPO}"); then
      log_error "Could not determine ddprof version (auto-detection failed)"
      exit 1
    fi
  elif [ -n "${DDPROF_VERSION_ARG}" ]; then
    DDPROF_VERSION="${DDPROF_VERSION_ARG}"
  elif [ -n "${DDPROF_VERSION:-}" ]; then
    DDPROF_VERSION="${DDPROF_VERSION}"
  elif [ -n "${CURRENT_VERSION:-}" ]; then
    DDPROF_VERSION="${CURRENT_VERSION}"
  elif [ -f "${PROJECT_ROOT}/build.env" ]; then
    # Try to source build.env to get CURRENT_VERSION
    log_info "Detecting ddprof version from build.env"
    # shellcheck disable=SC1091
    source "${PROJECT_ROOT}/build.env" 2>/dev/null || true
    DDPROF_VERSION="${CURRENT_VERSION:-}"
  fi

  if [ -z "${DDPROF_VERSION:-}" ]; then
    # Auto-detect latest
    log_info "No ddprof version specified, detecting latest..."
    if ! DDPROF_VERSION=$(detect_latest_snapshot_version "com.datadoghq" "ddprof" "${SNAPSHOT_REPO}"); then
      log_error "Could not determine ddprof version (auto-detection failed and no fallback available)"
      exit 1
    fi
  fi
else
  log_info "Skipping ddprof download (--skip-ddprof flag set)"
fi

# Validate Maven is available
if ! command -v mvn &> /dev/null; then
  log_error "Maven (mvn) is not installed or not in PATH"
  log_error "Please install Maven to download artifacts"
  exit 1
fi

# Create output directory
mkdir -p "${OUTPUT_DIR}"

log_info "Downloading artifacts to: ${OUTPUT_DIR}"
log_info "dd-java-agent version: ${DD_TRACE_VERSION}"
if [ "${SKIP_DDPROF}" = "false" ]; then
  log_info "ddprof version: ${DDPROF_VERSION}"
else
  log_info "ddprof: skipping (using existing artifact)"
fi

# Download dd-java-agent
log_info "Downloading dd-java-agent:${DD_TRACE_VERSION}..."
if mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
    -DrepoUrl="${SNAPSHOT_REPO}" \
    -Dartifact="com.datadoghq:dd-java-agent:${DD_TRACE_VERSION}" \
    -q > /tmp/mvn-dd-trace.log 2>&1; then
  log_info "Successfully downloaded dd-java-agent"
else
  log_error "Failed to download dd-java-agent"
  log_error "Maven output:"
  cat /tmp/mvn-dd-trace.log
  exit 1
fi

# Download ddprof (skip if --skip-ddprof flag is set)
if [ "${SKIP_DDPROF}" = "false" ]; then
  log_info "Downloading ddprof:${DDPROF_VERSION}..."
  if mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
      -DrepoUrl="${SNAPSHOT_REPO}" \
      -Dartifact="com.datadoghq:ddprof:${DDPROF_VERSION}" \
      -q > /tmp/mvn-ddprof.log 2>&1; then
    log_info "Successfully downloaded ddprof"
  else
    log_error "Failed to download ddprof"
    log_error "Maven output:"
    cat /tmp/mvn-ddprof.log
    exit 1
  fi
fi

# Determine Maven local repository path (default: ~/.m2/repository)
MVN_REPO="${HOME}/.m2/repository"
if [ -n "${MAVEN_CONFIG:-}" ]; then
  # Check if custom Maven settings specify different local repo
  log_warn "Custom MAVEN_CONFIG detected, using default ~/.m2/repository"
fi

# Copy artifacts to output directory
DD_AGENT_JAR="${MVN_REPO}/com/datadoghq/dd-java-agent/${DD_TRACE_VERSION}/dd-java-agent-${DD_TRACE_VERSION}.jar"

if [ ! -f "${DD_AGENT_JAR}" ]; then
  log_error "dd-java-agent JAR not found at: ${DD_AGENT_JAR}"
  exit 1
fi

log_info "Copying dd-java-agent to ${OUTPUT_DIR}/dd-java-agent-original.jar"
cp "${DD_AGENT_JAR}" "${OUTPUT_DIR}/dd-java-agent-original.jar"

if [ "${SKIP_DDPROF}" = "false" ]; then
  DDPROF_JAR="${MVN_REPO}/com/datadoghq/ddprof/${DDPROF_VERSION}/ddprof-${DDPROF_VERSION}.jar"

  if [ ! -f "${DDPROF_JAR}" ]; then
    log_error "ddprof JAR not found at: ${DDPROF_JAR}"
    exit 1
  fi

  log_info "Copying ddprof to ${OUTPUT_DIR}/ddprof.jar"
  cp "${DDPROF_JAR}" "${OUTPUT_DIR}/ddprof.jar"
fi

# Validate JAR integrity
log_info "Validating JAR integrity..."

if unzip -t "${OUTPUT_DIR}/dd-java-agent-original.jar" > /dev/null 2>&1; then
  log_info "✓ dd-java-agent-original.jar is valid"
else
  log_error "✗ dd-java-agent-original.jar is corrupted"
  exit 1
fi

if [ "${SKIP_DDPROF}" = "false" ]; then
  if unzip -t "${OUTPUT_DIR}/ddprof.jar" > /dev/null 2>&1; then
    log_info "✓ ddprof.jar is valid"
  else
    log_error "✗ ddprof.jar is corrupted"
    exit 1
  fi
fi

# Print summary
log_info "Download complete!"
log_info "Artifacts:"
log_info "  dd-java-agent: $(du -h "${OUTPUT_DIR}/dd-java-agent-original.jar" | cut -f1)"
if [ "${SKIP_DDPROF}" = "false" ]; then
  log_info "  ddprof:        $(du -h "${OUTPUT_DIR}/ddprof.jar" | cut -f1)"
fi
