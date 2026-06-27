#!/bin/bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

source "${PROJECT_ROOT}/.gitlab/config.env"
[ -n "${AWS_REGION:-}" ]  || { echo "[ERROR] AWS_REGION not set in config.env"; exit 1; }
[ -n "${SSM_PREFIX:-}" ]  || { echo "[ERROR] SSM_PREFIX not set in config.env"; exit 1; }

# URL used for metadata queries and snapshot downloads (Steps 2 and 3).
CENTRAL_SNAPSHOTS_URL="https://central.sonatype.com/repository/maven-snapshots/"
# URL used for publishing (Step 5) — legacy s01 endpoint required for deploy:deploy-file.
OSSRH_SNAPSHOTS_URL="https://s01.oss.sonatype.org/content/repositories/snapshots/"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

log_info()  { echo -e "${GREEN}[INFO]${NC} $*"; }
log_warn()  { echo -e "${YELLOW}[WARN]${NC} $*"; }
log_error() { echo -e "${RED}[ERROR]${NC} $*"; }

MAVEN_SETTINGS=""
MVN_WORK_DIR_DDPROF=""
MVN_WORK_DIR_AGENT=""
MVN_LOG1=""
MVN_LOG2=""
OUTPUT_JAR=""
cleanup() {
  [ -n "${MAVEN_SETTINGS}" ] && rm -f "${MAVEN_SETTINGS}"
  [ -n "${MVN_WORK_DIR_DDPROF}" ] && rm -rf "${MVN_WORK_DIR_DDPROF}"
  [ -n "${MVN_WORK_DIR_AGENT}" ] && rm -rf "${MVN_WORK_DIR_AGENT}"
  [ -n "${MVN_LOG1}" ] && rm -f "${MVN_LOG1}"
  [ -n "${MVN_LOG2}" ] && rm -f "${MVN_LOG2}"
  # OUTPUT_JAR and publish-report.txt are GitLab artifacts — do NOT delete them here;
  # GitLab collects artifacts after the script exits.
}
trap cleanup EXIT
trap 'cleanup; exit 143' TERM
trap 'cleanup; exit 130' INT
trap 'cleanup; exit 129' HUP

# detect_latest_snapshot_version <group_id> <artifact_id> <repo_url>
# Prints the latest vanilla snapshot version to stdout; all logging goes to stderr.
detect_latest_snapshot_version() {
  local group_id="$1" artifact_id="$2" repo_url="$3"
  local group_path metadata latest_version
  group_path=$(echo "${group_id}" | tr '.' '/')
  local metadata_url="${repo_url}${group_path}/${artifact_id}/maven-metadata.xml"
  log_info "Querying ${artifact_id} metadata from ${metadata_url}" >&2
  metadata=$(curl -fsSL "${metadata_url}") || {
    log_error "Could not fetch metadata from ${metadata_url}" >&2
    return 1
  }
  latest_version=$(echo "${metadata}" | sed -n 's/.*<latest>\(.*\)<\/latest>.*/\1/p')
  if [ -n "${latest_version}" ] && \
     ! echo "${latest_version}" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+(-DD)?-SNAPSHOT$'; then
    log_warn "Latest tag '${latest_version}' looks branch-qualified; scanning versions list" >&2
    latest_version=""
  fi
  if [ -z "${latest_version}" ]; then
    latest_version=$(echo "${metadata}" | \
      sed -n 's/.*<version>\(.*\)<\/version>.*/\1/p' | \
      grep -E '^[0-9]+\.[0-9]+\.[0-9]+(-DD)?-SNAPSHOT$' | \
      sort -V | tail -1 || true)
  fi
  if [ -z "${latest_version}" ]; then
    log_error "Could not detect latest version for ${artifact_id}" >&2
    return 1
  fi
  log_info "Latest ${artifact_id}: ${latest_version}" >&2
  echo "${latest_version}"
}

# ── Input validation ──────────────────────────────────────────────────────────

if [ -n "${DDPROF_VERSION:-}" ] && \
   ! echo "${DDPROF_VERSION}" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+$'; then
  log_error "DDPROF_VERSION '${DDPROF_VERSION}' is not a valid semver (expected X.Y.Z)"
  exit 1
fi
if [ -n "${DD_TRACE_VERSION:-}" ] && \
   ! echo "${DD_TRACE_VERSION}" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+(-DD)?-SNAPSHOT$'; then
  log_error "DD_TRACE_VERSION '${DD_TRACE_VERSION}' does not match expected pattern X.Y.Z[-DD]-SNAPSHOT"
  exit 1
fi

# ── Step 1: Resolve ddprof JAR ────────────────────────────────────────────────

DDPROF_JAR=""
DDPROF_SOURCE=""

# Prefer the build artifact; only fall back to Maven Central when absent and DDPROF_VERSION is set.
DDPROF_JAR=$(find "${PROJECT_ROOT}/ddprof-lib/build/libs" -name "ddprof-lib-*.jar" \
               2>/dev/null | sort -V | tail -1 || true)
if [ -n "${DDPROF_JAR}" ] && [ -f "${DDPROF_JAR}" ]; then
  DDPROF_SOURCE="build artifact (${DDPROF_JAR##*/})"
elif [ -n "${DDPROF_VERSION:-}" ]; then
  log_info "No build artifact found — downloading com.datadoghq:ddprof:${DDPROF_VERSION} from Maven Central"
  MVN_WORK_DIR_DDPROF=$(mktemp -d /tmp/mvn-workdir-XXXXXX)
  MVN_LOG1=$(mktemp /tmp/mvn-log-XXXXXX)
  if ! (cd "${MVN_WORK_DIR_DDPROF}" && mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
      -DrepoUrl=https://repo1.maven.org/maven2/ \
      -Dartifact="com.datadoghq:ddprof:${DDPROF_VERSION}" \
      -q > "${MVN_LOG1}" 2>&1); then
    log_error "Failed to download com.datadoghq:ddprof:${DDPROF_VERSION}"
    cat "${MVN_LOG1}"
    exit 1
  fi
  DDPROF_JAR="${HOME}/.m2/repository/com/datadoghq/ddprof/${DDPROF_VERSION}/ddprof-${DDPROF_VERSION}.jar"
  DDPROF_SOURCE="Maven Central (${DDPROF_VERSION})"
else
  log_error "No build artifact found and DDPROF_VERSION is not set."
  log_error "Set DDPROF_VERSION to a released version (e.g. 1.47.0) for manual runs."
  exit 1
fi

if [ ! -f "${DDPROF_JAR}" ]; then
  log_error "ddprof JAR not found: ${DDPROF_JAR}"
  exit 1
fi
log_info "ddprof JAR: ${DDPROF_JAR} [${DDPROF_SOURCE}]"

# ── Step 2: Resolve dd-trace-java snapshot version ────────────────────────────

if [ -n "${DD_TRACE_VERSION:-}" ]; then
  log_info "DD_TRACE_VERSION=${DD_TRACE_VERSION} (explicit)"
else
  log_info "Detecting latest dd-java-agent snapshot version..."
  if ! DD_TRACE_VERSION=$(detect_latest_snapshot_version \
        "com.datadoghq" "dd-java-agent" "${CENTRAL_SNAPSHOTS_URL}"); then
    log_error "Could not determine dd-java-agent version from Maven metadata."
    exit 1
  fi
fi

# Strip -SNAPSHOT / -DD-SNAPSHOT suffix to get the numeric base (e.g. 1.63.0)
DD_TRACE_BASE_VERSION=$(echo "${DD_TRACE_VERSION}" | sed -E 's/-(DD-)?SNAPSHOT$//')
PROFILER_VERSION="${DD_TRACE_BASE_VERSION}-PROFILER-SNAPSHOT"

log_info "dd-trace source version:  ${DD_TRACE_VERSION}"
log_info "Published version:        com.datadoghq:dd-java-agent:${PROFILER_VERSION}"

# ── Step 3: Download dd-java-agent snapshot ───────────────────────────────────

log_info "Downloading dd-java-agent:${DD_TRACE_VERSION}..."
MVN_WORK_DIR_AGENT=$(mktemp -d /tmp/mvn-workdir-XXXXXX)
MVN_LOG2=$(mktemp /tmp/mvn-log-XXXXXX)
if ! (cd "${MVN_WORK_DIR_AGENT}" && mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
    -DrepoUrl="${CENTRAL_SNAPSHOTS_URL}" \
    -Dartifact="com.datadoghq:dd-java-agent:${DD_TRACE_VERSION}" \
    -q > "${MVN_LOG2}" 2>&1); then
  log_error "Failed to download dd-java-agent:${DD_TRACE_VERSION}"
  cat "${MVN_LOG2}"
  exit 1
fi

DD_AGENT_JAR="${HOME}/.m2/repository/com/datadoghq/dd-java-agent/${DD_TRACE_VERSION}/dd-java-agent-${DD_TRACE_VERSION}.jar"
if [ ! -f "${DD_AGENT_JAR}" ]; then
  log_error "Downloaded JAR not found at expected path: ${DD_AGENT_JAR}"
  exit 1
fi
log_info "Downloaded: ${DD_AGENT_JAR}"

# ── Step 4: Patch ─────────────────────────────────────────────────────────────

OUTPUT_JAR="${PROJECT_ROOT}/dd-java-agent-profiler-snapshot.jar"  # intentionally NOT cleaned up — GitLab artifact
log_info "Patching dd-java-agent with ddprof..."
DD_AGENT_JAR="${DD_AGENT_JAR}" \
DDPROF_JAR="${DDPROF_JAR}" \
OUTPUT_JAR="${OUTPUT_JAR}" \
  "${PROJECT_ROOT}/utils/patch-dd-java-agent.sh"
log_info "Patched JAR: ${OUTPUT_JAR}"

# ── Step 5: Publish ───────────────────────────────────────────────────────────

log_info "Fetching Sonatype credentials from AWS SSM..."
# Suppress xtrace to prevent credentials appearing in logs
case $- in *x*) _xtrace=1;; *) _xtrace=0;; esac
set +x
SONATYPE_USERNAME=$(aws ssm get-parameter \
  --region "${AWS_REGION}" \
  --name "${SSM_PREFIX}.sonatype_token_user" \
  --with-decryption --query "Parameter.Value" --out text) \
  || { log_error "Failed to fetch Sonatype username from SSM"; exit 1; }
SONATYPE_PASSWORD=$(aws ssm get-parameter \
  --region "${AWS_REGION}" \
  --name "${SSM_PREFIX}.sonatype_token" \
  --with-decryption --query "Parameter.Value" --out text) \
  || { log_error "Failed to fetch Sonatype password from SSM"; exit 1; }
[ -z "${SONATYPE_USERNAME}" ] && { log_error "Sonatype username is empty — check SSM parameter"; exit 1; }
[ -z "${SONATYPE_PASSWORD}" ] && { log_error "Sonatype password is empty — check SSM parameter"; exit 1; }

# Validate credentials contain no XML-special characters.
# Use POSIX extended regex (no grep -P) for portability across Linux and macOS.
# Single-quote is checked by splitting the shell quoting; newline/CR are checked via $'...' literals.
_check_cred() {
  local name="$1" val="$2"
  printf '%s' "${val}" | grep -qE '[<>&"'"'"']'   && { log_error "${name} contains XML-special characters — cannot embed safely"; exit 1; }
  printf '%s' "${val}" | grep -qF $'\n'            && { log_error "${name} contains a newline — cannot embed safely"; exit 1; }
  printf '%s' "${val}" | grep -qF $'\r'            && { log_error "${name} contains a carriage return — cannot embed safely"; exit 1; }
}
_check_cred SONATYPE_USERNAME "${SONATYPE_USERNAME}"
_check_cred SONATYPE_PASSWORD "${SONATYPE_PASSWORD}"

MAVEN_SETTINGS=$(umask 077; mktemp /tmp/maven-settings-XXXXXX) \
  || { log_error "Failed to create temporary Maven settings file"; exit 1; }
# NOTE: delimiter is intentionally unquoted so $SONATYPE_USERNAME / $SONATYPE_PASSWORD expand at runtime
cat > "${MAVEN_SETTINGS}" << XML
<settings>
  <servers>
    <server>
      <id>ossrh</id>
      <username>${SONATYPE_USERNAME}</username>
      <password>${SONATYPE_PASSWORD}</password>
    </server>
  </servers>
</settings>
XML
log_info "Publishing com.datadoghq:dd-java-agent:${PROFILER_VERSION}..."
if ! mvn --batch-mode -q deploy:deploy-file \
    --settings "${MAVEN_SETTINGS}" \
    -Durl="${OSSRH_SNAPSHOTS_URL}" \
    -DrepositoryId=ossrh \
    -Dfile="${OUTPUT_JAR}" \
    -DgroupId=com.datadoghq \
    -DartifactId=dd-java-agent \
    -Dversion="${PROFILER_VERSION}" \
    -Dpackaging=jar; then
  log_error "Failed to publish com.datadoghq:dd-java-agent:${PROFILER_VERSION}"
  exit 1
fi
# Restore xtrace after deploy — keeps both the settings file path and credentials out of CI trace
[ "${_xtrace}" = 1 ] && set -x
log_info "Published successfully"

# ── Step 6: Report ────────────────────────────────────────────────────────────

REPORT="${PROJECT_ROOT}/publish-report.txt"
{
  echo "Published:      com.datadoghq:dd-java-agent:${PROFILER_VERSION}"
  echo "Repository:     ${OSSRH_SNAPSHOTS_URL}"
  echo "ddprof source:  ${DDPROF_SOURCE}"
  echo "dd-trace input: ${DD_TRACE_VERSION}"
} > "${REPORT}"
cat "${REPORT}"
