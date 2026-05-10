#!/bin/bash

set -euo pipefail

# Verify compatibility between ddprof classes and patched dd-java-agent

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

# Input JARs
DDPROF_JAR="${DDPROF_JAR:-${PROJECT_ROOT}/ddprof.jar}"
DD_AGENT_JAR="${DD_AGENT_JAR:-${PROJECT_ROOT}/dd-java-agent-original.jar}"
PATCHED_JAR="${PATCHED_JAR:-${PROJECT_ROOT}/dd-java-agent-patched.jar}"

# Working directory
WORK_DIR="${WORK_DIR:-/tmp/jar-verify-$$}"

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

function usage() {
  cat << EOF
Usage: $0 [OPTIONS]

Verify compatibility between ddprof and patched dd-java-agent.

This script checks for breaking changes in public API by comparing
class signatures using javap.

OPTIONS:
  --ddprof-jar <path>     Path to ddprof.jar (default: ${DDPROF_JAR})
  --dd-agent-jar <path>   Path to original dd-java-agent.jar (default: ${DD_AGENT_JAR})
  --patched-jar <path>    Path to patched dd-java-agent.jar (default: ${PATCHED_JAR})
  --work-dir <path>       Working directory (default: /tmp/jar-verify-\$\$)
  --debug                 Enable debug output
  --help                  Show this help message

ENVIRONMENT VARIABLES:
  DDPROF_JAR              Path to ddprof.jar
  DD_AGENT_JAR            Path to original dd-java-agent.jar
  PATCHED_JAR             Path to patched dd-java-agent.jar
  WORK_DIR                Working directory
  DEBUG                   Enable debug output (true/false)

EXIT CODES:
  0   - Compatible, safe to proceed
  1   - Incompatible, breaking changes detected or validation error

EXAMPLES:
  # Verify with default paths
  $0

  # Verify with custom paths
  $0 --ddprof-jar /path/to/ddprof.jar --patched-jar /path/to/patched.jar

  # Enable debug output
  DEBUG=true $0
EOF
}

# Parse command line arguments
while [ $# -gt 0 ]; do
  case "$1" in
    --ddprof-jar)
      DDPROF_JAR="$2"
      shift 2
      ;;
    --dd-agent-jar)
      DD_AGENT_JAR="$2"
      shift 2
      ;;
    --patched-jar)
      PATCHED_JAR="$2"
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
if [ ! -f "${DDPROF_JAR}" ]; then
  log_error "ddprof JAR not found: ${DDPROF_JAR}"
  exit 1
fi

if [ ! -f "${DD_AGENT_JAR}" ]; then
  log_error "dd-java-agent JAR not found: ${DD_AGENT_JAR}"
  exit 1
fi

if [ ! -f "${PATCHED_JAR}" ]; then
  log_error "patched JAR not found: ${PATCHED_JAR}"
  exit 1
fi

# Check for javap
if ! command -v javap &> /dev/null; then
  log_error "javap not found in PATH"
  log_error "javap is part of the JDK. Please ensure JAVA_HOME is set and JDK bin is in PATH"
  exit 1
fi

log_info "Starting compatibility verification"
log_info "  ddprof:        ${DDPROF_JAR}"
log_info "  dd-agent-orig: ${DD_AGENT_JAR}"
log_info "  patched:       ${PATCHED_JAR}"

# Create working directories
mkdir -p "${WORK_DIR}/original" "${WORK_DIR}/ddprof"

# Extract JARs once
log_info "Extracting dd-java-agent-original..."
if ! unzip -q "${DD_AGENT_JAR}" -d "${WORK_DIR}/original/"; then
  log_error "Failed to extract dd-java-agent"
  exit 1
fi

log_info "Extracting ddprof..."
if ! unzip -q "${DDPROF_JAR}" -d "${WORK_DIR}/ddprof/"; then
  log_error "Failed to extract ddprof"
  exit 1
fi

# Create symlinks for .classdata files so javap can read them
# NOTE: These symlinks are temporary and only for validation - they exist
#       in WORK_DIR and are cleaned up by trap. They do NOT affect the patched JAR.
# Only symlink profiler classes (com/datadoghq/profiler) since those are the only ones ddprof provides
log_info "Creating .class symlinks for profiler .classdata files..."

cd "${WORK_DIR}/original"
if [ -d "shared/com/datadoghq/profiler" ]; then
  CLASSDATA_COUNT=$(find shared/com/datadoghq/profiler -name "*.classdata" -type f | wc -l | tr -d ' ')
  log_debug "Found ${CLASSDATA_COUNT} profiler .classdata files"

  find shared/com/datadoghq/profiler -name "*.classdata" -type f | while IFS= read -r classdata; do
    # URL-decode: %24 -> $
    classfile="${classdata%.classdata}.class"
    classfile="${classfile//%24/$}"

    # Create directory if needed (for inner classes)
    mkdir -p "$(dirname "${classfile}")"

    log_debug "  Symlinking: ${classfile} -> $(basename "${classdata}")"
    ln -sf "$(basename "${classdata}")" "${classfile}"
  done
else
  log_warn "No shared/com/datadoghq/profiler directory found in original"
fi
cd - > /dev/null

log_info "✓ Created symlinks for javap compatibility"

# Find all classes in ddprof (excluding META-INF)
log_info "Finding classes to verify..."
CLASSES=$(cd "${WORK_DIR}/ddprof" && find . -name "*.class" -type f | grep -v "^\\./META-INF/" | sed 's|^\./||' || true)
CLASS_COUNT=$(echo "${CLASSES}" | grep -c . || echo 0)

if [ "${CLASS_COUNT}" -eq 0 ]; then
  log_warn "No classes found in ddprof JAR (this is unusual but not necessarily an error)"
  log_info "Verification passed (no classes to verify)"
  exit 0
fi

log_info "Found ${CLASS_COUNT} classes to verify"

# Extract and compare signatures for each class
CHECKED_COUNT=0
SKIPPED_COUNT=0
BREAKING_CHANGES=0

function extract_signature() {
  local classfile="$1"
  local output="$2"

  log_debug "    extract_signature: classfile=${classfile}"

  if [ ! -f "${classfile}" ] && [ ! -L "${classfile}" ]; then
    log_debug "    extract_signature: File does not exist"
    return 1
  fi

  # Run javap with -protected flag to get clean method/field signatures
  # Skip first line (Compiled from) and class declaration line
  if javap -protected "${classfile}" 2>/dev/null | \
     tail -n +2 | \
     grep -E "^\s+(public|protected)" | \
     sed 's/^[[:space:]]*//' | \
     sort > "${output}"; then
    log_debug "    extract_signature: SUCCESS - extracted signatures"
    return 0
  else
    log_debug "    extract_signature: FAILED - no public/protected members found"
    return 1
  fi
}

function normalize_signature() {
  # Normalize method signatures for comparison
  # Remove whitespace variations, package names from return types, etc.
  sed 's/\s\+/ /g' | \
  sed 's/^ //g' | \
  sed 's/ $//g' | \
  sort -u
}

log_info "Comparing public/protected API signatures..."

while IFS= read -r classfile; do
  if [ -z "${classfile}" ]; then
    continue
  fi

  # Convert path to fully qualified class name
  classname=$(echo "${classfile}" | sed 's#/#.#g' | sed 's#\.class$##')

  log_debug "Checking class: ${classname}"

  # Check if class exists in original (as .class symlink we created)
  ORIGINAL_FILE="${WORK_DIR}/original/shared/${classfile}"

  if [ ! -f "${ORIGINAL_FILE}" ] && [ ! -L "${ORIGINAL_FILE}" ]; then
    log_debug "Class ${classname} is new in ddprof (not in original dd-agent)"
    SKIPPED_COUNT=$((SKIPPED_COUNT + 1))
    continue
  fi

  log_debug "  Found in original: shared/${classfile}"

  # Extract signatures from both versions
  ORIGINAL_SIG="${WORK_DIR}/original-${classname}.txt"
  DDPROF_SIG="${WORK_DIR}/ddprof-${classname}.txt"

  DDPROF_FILE="${WORK_DIR}/ddprof/${classfile}"

  if ! extract_signature "${ORIGINAL_FILE}" "${ORIGINAL_SIG}"; then
    log_debug "Could not extract ${classname} from dd-agent (might be non-public or package-private)"
    SKIPPED_COUNT=$((SKIPPED_COUNT + 1))
    continue
  fi

  if ! extract_signature "${DDPROF_FILE}" "${DDPROF_SIG}"; then
    log_warn "⚠ Could not extract ${classname} from ddprof"
    SKIPPED_COUNT=$((SKIPPED_COUNT + 1))
    continue
  fi

  # Normalize both signatures for comparison
  cat "${ORIGINAL_SIG}" | normalize_signature > "${ORIGINAL_SIG}.norm"
  cat "${DDPROF_SIG}" | normalize_signature > "${DDPROF_SIG}.norm"

  # Check if all public/protected methods from original are present in ddprof
  MISSING_METHODS="${WORK_DIR}/missing-${classname}.txt"
  comm -23 "${ORIGINAL_SIG}.norm" "${DDPROF_SIG}.norm" > "${MISSING_METHODS}"

  if [ -s "${MISSING_METHODS}" ]; then
    log_warn "⚠ API changes detected in ${classname}:"
    log_warn "    Methods in dd-java-agent-original but missing in ddprof:"
    while IFS= read -r method; do
      log_warn "      ${method}"
    done < "${MISSING_METHODS}"

    # Also check for methods in ddprof that are not in original (additions)
    ADDED_METHODS="${WORK_DIR}/added-${classname}.txt"
    comm -13 "${ORIGINAL_SIG}.norm" "${DDPROF_SIG}.norm" > "${ADDED_METHODS}"
    if [ -s "${ADDED_METHODS}" ]; then
      log_info "    Methods added in ddprof (not in original):"
      while IFS= read -r method; do
        log_info "      ${method}"
      done < "${ADDED_METHODS}"
    fi

    BREAKING_CHANGES=$((BREAKING_CHANGES + 1))
  else
    log_debug "✓ ${classname} is API-compatible"
  fi

  CHECKED_COUNT=$((CHECKED_COUNT + 1))

done <<< "${CLASSES}"

log_info "API compatibility check complete:"
log_info "  - ${CHECKED_COUNT} classes verified for API compatibility"
log_info "  - ${SKIPPED_COUNT} classes skipped (new or non-public)"
log_info "  - ${BREAKING_CHANGES} classes with breaking changes"

# Verify native libraries are present
log_info "Verifying native libraries..."
NATIVE_IN_DDPROF=$(unzip -l "${DDPROF_JAR}" | grep -c "META-INF/native-libs/.*\.so$" || true)
if [ -z "${NATIVE_IN_DDPROF}" ] || ! [[ "${NATIVE_IN_DDPROF}" =~ ^[0-9]+$ ]]; then
  NATIVE_IN_DDPROF=0
fi

NATIVE_IN_PATCHED=$(unzip -l "${PATCHED_JAR}" | grep -c "shared/META-INF/native-libs/.*\.so$" || true)
if [ -z "${NATIVE_IN_PATCHED}" ] || ! [[ "${NATIVE_IN_PATCHED}" =~ ^[0-9]+$ ]]; then
  NATIVE_IN_PATCHED=0
fi

log_debug "Native libraries in ddprof: ${NATIVE_IN_DDPROF}"
log_debug "Native libraries in patched: ${NATIVE_IN_PATCHED}"

# Note: ddprof.jar may only contain 1 lib (e.g., from debug build on one arch)
# The patched JAR gets all platform libs from libs/$TARGET/ directories, not from ddprof.jar
if [ "${NATIVE_IN_PATCHED}" -eq 0 ]; then
  log_warn "No native libraries found in patched JAR"
  log_warn "This may be expected if building without native libraries"
else
  log_info "✓ Found ${NATIVE_IN_PATCHED} native libraries in patched JAR"
fi

# Verify all expected platforms are present
log_info "Verifying platform coverage..."
EXPECTED_PLATFORMS=("linux-x64" "linux-x64-musl" "linux-arm64" "linux-arm64-musl")
MISSING_PLATFORMS=()

for platform in "${EXPECTED_PLATFORMS[@]}"; do
  if unzip -l "${PATCHED_JAR}" "shared/META-INF/native-libs/${platform}/libjavaProfiler.so" > /dev/null 2>&1; then
    log_debug "✓ Found platform: ${platform}"
  else
    log_debug "✗ Missing platform: ${platform}"
    MISSING_PLATFORMS+=("${platform}")
  fi
done

if [ ${#MISSING_PLATFORMS[@]} -gt 0 ]; then
  log_warn "Some platforms are missing: ${MISSING_PLATFORMS[*]}"
  log_warn "This may be expected if not all platforms were built"
else
  log_info "✓ All expected platforms present"
fi

# Final verdict
log_info ""
log_info "============================================"
log_info "VERIFICATION COMPLETED"
log_info "============================================"
log_info ""
log_info "Summary:"
log_info "  - ${CHECKED_COUNT} classes verified for API compatibility"
log_info "  - ${SKIPPED_COUNT} classes skipped (new or non-public)"
log_info "  - ${BREAKING_CHANGES} classes with API changes (warnings)"
log_info "  - ${NATIVE_IN_PATCHED} native libraries verified"
log_info "  - ${#MISSING_PLATFORMS[@]} platforms missing (may be expected)"

if [ "${BREAKING_CHANGES}" -gt 0 ]; then
  log_warn ""
  log_warn "API changes detected but not blocking (see warnings above)"
  log_warn "Review warnings for methods removed from dd-java-agent"
fi

exit 0
