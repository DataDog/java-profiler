#!/bin/bash

set -euo pipefail

# Patch dd-java-agent.jar with ddprof contents

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

# Input JARs
DD_AGENT_JAR="${DD_AGENT_JAR:-${PROJECT_ROOT}/dd-java-agent-original.jar}"
DDPROF_JAR="${DDPROF_JAR:-${PROJECT_ROOT}/ddprof.jar}"

# Output JAR
OUTPUT_JAR="${OUTPUT_JAR:-${PROJECT_ROOT}/dd-java-agent-patched.jar}"

# Working directory for extraction
# Use mktemp for guaranteed unique directory, fall back to PID-based if mktemp unavailable
WORK_DIR="${WORK_DIR:-$(mktemp -d 2>/dev/null || echo "/tmp/jar-patch-$$")}"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
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

function log_debug() {
  if [ "${DEBUG:-false}" = "true" ]; then
    echo -e "${BLUE}[DEBUG]${NC} $*"
  fi
}

function cleanup() {
  if [ -d "${WORK_DIR}" ]; then
    log_debug "Cleaning up work directory: ${WORK_DIR}"
    rm -rf "${WORK_DIR}"
  fi
}

trap cleanup EXIT

# Validate required tools are available
for tool in unzip zip dirname basename; do
  if ! command -v "$tool" &> /dev/null; then
    log_error "Required tool not found: $tool"
    log_error "Please install $tool to continue"
    exit 1
  fi
done

function usage() {
  cat << EOF
Usage: $0 [OPTIONS]

Patch dd-java-agent.jar with ddprof contents.

Mapping rules:
  - Native libraries: ddprof.jar:META-INF/native-libs/** → dd-java-agent.jar:shared/META-INF/native-libs/**
  - Class files: ddprof.jar:**/*.class → dd-java-agent.jar:shared/**/*.classdata (same package structure)

OPTIONS:
  --dd-agent-jar <path>   Path to dd-java-agent-original.jar (default: ${DD_AGENT_JAR})
  --ddprof-jar <path>     Path to ddprof.jar (default: ${DDPROF_JAR})
  --output-jar <path>     Path to output patched jar (default: ${OUTPUT_JAR})
  --work-dir <path>       Working directory for extraction (default: /tmp/jar-patch-\$\$)
  --debug                 Enable debug output
  --help                  Show this help message

ENVIRONMENT VARIABLES:
  DD_AGENT_JAR            Path to dd-java-agent-original.jar
  DDPROF_JAR              Path to ddprof.jar
  OUTPUT_JAR              Path to output patched jar
  WORK_DIR                Working directory for extraction
  DEBUG                   Enable debug output (true/false)

EXAMPLES:
  # Patch with default paths
  $0

  # Patch with custom paths
  $0 --dd-agent-jar /path/to/agent.jar --ddprof-jar /path/to/ddprof.jar

  # Enable debug output
  DEBUG=true $0
EOF
}

# Parse command line arguments
while [ $# -gt 0 ]; do
  case "$1" in
    --dd-agent-jar)
      DD_AGENT_JAR="$2"
      shift 2
      ;;
    --ddprof-jar)
      DDPROF_JAR="$2"
      shift 2
      ;;
    --output-jar)
      OUTPUT_JAR="$2"
      shift 2
      ;;
    --work-dir)
      WORK_DIR="$2"
      shift 2
      ;;
    --debug)
      DEBUG=true
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

# Validate input JARs exist
if [ ! -f "${DD_AGENT_JAR}" ]; then
  log_error "dd-java-agent JAR not found: ${DD_AGENT_JAR}"
  exit 1
fi

if [ ! -f "${DDPROF_JAR}" ]; then
  log_error "ddprof JAR not found: ${DDPROF_JAR}"
  exit 1
fi

log_info "Starting JAR patching process"
log_info "  dd-java-agent: ${DD_AGENT_JAR}"
log_info "  ddprof:        ${DDPROF_JAR}"
log_info "  output:        ${OUTPUT_JAR}"
log_info "  work dir:      ${WORK_DIR}"

# Create working directories
if ! mkdir -p "${WORK_DIR}/agent" "${WORK_DIR}/ddprof"; then
  log_error "Failed to create working directories in: ${WORK_DIR}"
  log_error "Check disk space and permissions"
  exit 1
fi

# Extract dd-java-agent
log_info "Extracting dd-java-agent..."
if ! unzip -q "${DD_AGENT_JAR}" -d "${WORK_DIR}/agent/"; then
  log_error "Failed to extract dd-java-agent: ${DD_AGENT_JAR}"
  log_error "Check if file is corrupted or disk is full"
  exit 1
fi
log_info "✓ Extracted dd-java-agent"

# Extract ddprof
log_info "Extracting ddprof..."
if ! unzip -q "${DDPROF_JAR}" -d "${WORK_DIR}/ddprof/"; then
  log_error "Failed to extract ddprof: ${DDPROF_JAR}"
  log_error "Check if file is corrupted or disk is full"
  exit 1
fi
log_info "✓ Extracted ddprof"

# Create shared directory structure in agent
mkdir -p "${WORK_DIR}/agent/shared/META-INF"

# Copy native libraries
log_info "Copying native libraries..."
if [ -d "${WORK_DIR}/ddprof/META-INF/native-libs" ]; then
  cp -r "${WORK_DIR}/ddprof/META-INF/native-libs" "${WORK_DIR}/agent/shared/META-INF/"

  # Count native libraries
  NATIVE_COUNT=$(find "${WORK_DIR}/agent/shared/META-INF/native-libs" -type f -name "*.so" | wc -l | tr -d ' ')
  log_info "✓ Copied ${NATIVE_COUNT} native libraries"

  # List platforms
  if [ "${DEBUG:-false}" = "true" ]; then
    log_debug "Native library platforms:"
    find "${WORK_DIR}/agent/shared/META-INF/native-libs" -type d -mindepth 1 -maxdepth 1 -exec basename {} \; | while read -r platform; do
      log_debug "  - ${platform}"
    done
  fi
else
  log_warn "No native libraries found in ddprof (META-INF/native-libs missing)"
fi

# Copy and rename class files
log_info "Copying and renaming class files..."
CLASS_COUNT=0
SKIPPED_COUNT=0

# Count total class files first for progress tracking
TOTAL_CLASSES=$(find "${WORK_DIR}/ddprof" -name "*.class" -type f | wc -l | tr -d ' ')

# Validate TOTAL_CLASSES is a number
if ! [[ "${TOTAL_CLASSES}" =~ ^[0-9]+$ ]]; then
  log_error "Failed to count class files, got: '${TOTAL_CLASSES}'"
  exit 1
fi

log_info "Found ${TOTAL_CLASSES} class files to process"

# Verify ddprof extraction directory exists and has content
if [ ! -d "${WORK_DIR}/ddprof" ]; then
  log_error "ddprof extraction directory not found: ${WORK_DIR}/ddprof"
  exit 1
fi

# Exit early if no files to process
if [ "${TOTAL_CLASSES}" -eq 0 ]; then
  log_warn "No class files found to process"
  # Skip loop but don't fail - might be expected for some builds
fi

log_info "Starting class file copy loop..."

# Use find to locate all .class files, excluding META-INF
while IFS= read -r -d '' classfile; do
  log_debug "Processing: ${classfile}"

  # Get relative path from ddprof root
  relpath="${classfile#"${WORK_DIR}"/ddprof/}"

  # Skip META-INF directory
  if [[ "$relpath" == META-INF/* ]]; then
    log_debug "Skipping META-INF class: ${relpath}"
    SKIPPED_COUNT=$((SKIPPED_COUNT + 1))
    continue
  fi

  # Convert path: foo/bar/Baz.class → shared/foo/bar/Baz.classdata
  targetpath="${WORK_DIR}/agent/shared/${relpath%.class}.classdata"
  targetdir=$(dirname "$targetpath")

  # Create target directory if needed
  if ! mkdir -p "$targetdir"; then
    log_error "Failed to create directory: $targetdir"
    log_error "Check disk space and permissions"
    df -h "${WORK_DIR}" >&2
    exit 1
  fi

  # Copy file
  if ! cp "$classfile" "$targetpath"; then
    log_error "Failed to copy class file: $classfile"
    log_error "Target: $targetpath"
    log_error "Check disk space and permissions"
    df -h "${WORK_DIR}" >&2
    exit 1
  fi
  CLASS_COUNT=$((CLASS_COUNT + 1))

  # Show progress every 100 files
  if [ $((CLASS_COUNT % 100)) -eq 0 ]; then
    log_debug "Progress: ${CLASS_COUNT}/${TOTAL_CLASSES} files copied"
  fi

  log_debug "Copied: ${relpath} → shared/${relpath%.class}.classdata"
done < <(find "${WORK_DIR}/ddprof" -name "*.class" -type f -print0)

# Verify loop completed successfully
if [ "${CLASS_COUNT}" -eq 0 ] && [ "${TOTAL_CLASSES}" -gt 0 ]; then
  log_error "Class file loop failed - no files were copied despite ${TOTAL_CLASSES} files found"
  exit 1
fi

log_info "✓ Copied and renamed ${CLASS_COUNT} class files (${SKIPPED_COUNT} skipped from META-INF)"

# List some sample class files for verification
if [ "${DEBUG:-false}" = "true" ]; then
  log_debug "Sample classdata files:"
  # Use process substitution to avoid SIGPIPE from head in pipeline
  count=0
  while IFS= read -r f && [ "$count" -lt 5 ]; do
    relpath="${f#"${WORK_DIR}"/agent/}"
    log_debug "  - ${relpath}"
    count=$((count + 1))
  done < <(find "${WORK_DIR}/agent/shared" -name "*.classdata" -type f)
fi

# Repackage JAR
log_info "Repackaging JAR..."

# Save original directory and change to agent directory
ORIG_DIR=$(pwd)
if ! cd "${WORK_DIR}/agent"; then
  log_error "Failed to change directory to ${WORK_DIR}/agent"
  log_error "Check if directory exists and is accessible"
  exit 1
fi

if ! zip -r -q "${OUTPUT_JAR}" .; then
  log_error "Failed to repackage JAR"
  log_error "Check disk space and write permissions for: ${OUTPUT_JAR}"
  cd "$ORIG_DIR" || true
  exit 1
fi

# Restore original directory
cd "$ORIG_DIR" || log_warn "Failed to return to original directory"

log_info "✓ Created patched JAR: ${OUTPUT_JAR}"

# Validate patched JAR
log_info "Validating patched JAR..."

if ! unzip -t "${OUTPUT_JAR}" > /dev/null 2>&1; then
  log_error "Patched JAR is corrupted"
  exit 1
fi
log_info "✓ JAR integrity check passed"

# Verify shared directory structure
log_info "Verifying structure..."
SHARED_NATIVE_COUNT=$(unzip -l "${OUTPUT_JAR}" | grep -c "shared/META-INF/native-libs/.*\.so$" || echo "0")
TOTAL_CLASSDATA_COUNT=$(unzip -l "${OUTPUT_JAR}" | grep -c "shared/.*\.classdata$" || echo "0")

if [ "${SHARED_NATIVE_COUNT}" -eq 0 ] && [ "${NATIVE_COUNT}" -gt 0 ]; then
  log_error "Native libraries missing in patched JAR"
  exit 1
fi

# Diagnostic: Check for unexpected classes in ddprof-owned package namespaces
# Only check com/datadoghq/profiler - this is the actual ddprof package
log_debug "Checking for unexpected classes in com/datadoghq/profiler package..."
DDPROF_CLASSES=$(unzip -l "${DDPROF_JAR}" '*.class' 2>/dev/null | \
  awk '{print $NF}' | \
  grep "^com/datadoghq/profiler/" | \
  grep "\.class$" | \
  sed 's/\.class$//' | \
  sort || true)

# Get classes from patched JAR in the ddprof package
PATCHED_CLASSES=$(unzip -l "${OUTPUT_JAR}" 2>/dev/null | \
  grep "shared/com/datadoghq/profiler/.*\.classdata$" | \
  awk '{print $NF}' | \
  sed 's|^shared/||' | \
  sed 's/\.classdata$//' | \
  sort || true)

# Find classes in patched JAR that weren't in original ddprof.jar
UNEXPECTED_CLASSES=$(comm -13 <(echo "${DDPROF_CLASSES}") <(echo "${PATCHED_CLASSES}") || true)

if [ -n "${UNEXPECTED_CLASSES}" ]; then
  UNEXPECTED_COUNT=$(echo "${UNEXPECTED_CLASSES}" | grep -c . || echo "0")
  log_warn "Found ${UNEXPECTED_COUNT} unexpected classes in com/datadoghq/profiler:"
  log_warn "These classes exist in dd-java-agent but not in ddprof.jar:"
  echo "${UNEXPECTED_CLASSES}" | while IFS= read -r cls; do
    log_debug "  - ${cls}"
  done | head -10
  if [ "${UNEXPECTED_COUNT}" -gt 10 ]; then
    log_debug "  ... and $((UNEXPECTED_COUNT - 10)) more"
  fi
  log_warn "This may indicate:"
  log_warn "  - Package namespace overlap between dd-java-agent and ddprof"
  log_warn "  - Classes added to ddprof.jar (valid scenario)"
fi

log_info "✓ Structure verification passed"
log_info "  - ${SHARED_NATIVE_COUNT} native libraries in shared/META-INF/native-libs/"
log_info "  - ${CLASS_COUNT} ddprof classes added to patched JAR"
log_info "  - ${TOTAL_CLASSDATA_COUNT} total classdata files in patched JAR"

# Print summary
JAR_SIZE=$(du -h "${OUTPUT_JAR}" | cut -f1)
log_info ""
log_info "Patching complete!"
log_info "  Output: ${OUTPUT_JAR} (${JAR_SIZE})"
log_info ""
log_info "To inspect the patched JAR structure:"
log_info "  unzip -l ${OUTPUT_JAR} | grep shared/"
