#!/bin/bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

source "${PROJECT_ROOT}/.gitlab/config.env"
[ -n "${AWS_REGION:-}" ]  || { echo "[ERROR] AWS_REGION not set in config.env"; exit 1; }
[ -n "${SSM_PREFIX:-}" ]  || { echo "[ERROR] SSM_PREFIX not set in config.env"; exit 1; }

# URL used for metadata queries and snapshot downloads (Steps 2 and 3).
CENTRAL_SNAPSHOTS_URL="https://central.sonatype.com/repository/maven-snapshots/"
MAVEN_CENTRAL_URL="https://repo1.maven.org/maven2/"
# URL used for publishing (Step 5) — legacy s01 endpoint required for deploy:deploy-file.
OSSRH_SNAPSHOTS_URL="https://s01.oss.sonatype.org/content/repositories/snapshots/"

# State file used by the nightly job to skip publishing when the version pair
# (ddprof release + dd-trace snapshot) is unchanged since the last successful run.
# Written at the end of a successful publish; restored from GitLab cache on re-runs.
STATE_FILE="${PROJECT_ROOT}/.profiler-snapshot-state"

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

# detect_latest_release_version <group_id> <artifact_id>
# Queries Maven Central and prints the latest non-snapshot release version to stdout.
detect_latest_release_version() {
  local group_id="$1" artifact_id="$2"
  local group_path metadata release_version
  group_path=$(echo "${group_id}" | tr '.' '/')
  local metadata_url="${MAVEN_CENTRAL_URL}${group_path}/${artifact_id}/maven-metadata.xml"
  log_info "Querying ${artifact_id} release metadata from ${metadata_url}" >&2
  metadata=$(curl -fsSL "${metadata_url}") || {
    log_error "Could not fetch metadata from ${metadata_url}" >&2
    return 1
  }
  # Prefer <release> tag; fall back to the highest semver-looking non-snapshot version.
  release_version=$(echo "${metadata}" | sed -n 's/.*<release>\(.*\)<\/release>.*/\1/p')
  if [ -n "${release_version}" ] && \
     echo "${release_version}" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+$'; then
    log_info "Latest ${artifact_id} release: ${release_version}" >&2
    echo "${release_version}"
    return 0
  fi
  release_version=$(echo "${metadata}" | \
    sed -n 's/.*<version>\(.*\)<\/version>.*/\1/p' | \
    grep -E '^[0-9]+\.[0-9]+\.[0-9]+$' | \
    sort -V | tail -1 || true)
  if [ -z "${release_version}" ]; then
    log_error "Could not detect latest release version for ${artifact_id}" >&2
    return 1
  fi
  log_info "Latest ${artifact_id} release: ${release_version}" >&2
  echo "${release_version}"
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

# Prefer the build artifact; fall back to Maven Central (explicit version or auto-detected latest).
DDPROF_JAR=$(find "${PROJECT_ROOT}/ddprof-lib/build/libs" -name "ddprof-lib-*.jar" \
               2>/dev/null | sort -V | tail -1 || true)
if [ -n "${DDPROF_JAR}" ] && [ -f "${DDPROF_JAR}" ]; then
  DDPROF_SOURCE="build artifact (${DDPROF_JAR##*/})"
  # Extract the version from the JAR filename (ddprof-lib-X.Y.Z[-qualifier].jar)
  DDPROF_VERSION=$(basename "${DDPROF_JAR}" .jar | sed 's/^ddprof-lib-//')
  log_info "Using build artifact — inferred DDPROF_VERSION=${DDPROF_VERSION}"
else
  if [ -z "${DDPROF_VERSION:-}" ]; then
    log_info "No build artifact and DDPROF_VERSION not set — detecting latest ddprof-lib release..."
    if ! DDPROF_VERSION=$(detect_latest_release_version "com.datadoghq" "ddprof-lib"); then
      log_error "Could not determine latest ddprof-lib release from Maven Central."
      exit 1
    fi
  fi
  log_info "No build artifact found — downloading com.datadoghq:ddprof-lib:${DDPROF_VERSION} from Maven Central"
  MVN_WORK_DIR_DDPROF=$(mktemp -d /tmp/mvn-workdir-XXXXXX)
  MVN_LOG1=$(mktemp /tmp/mvn-log-XXXXXX)
  if ! (cd "${MVN_WORK_DIR_DDPROF}" && mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
      -DrepoUrl="${MAVEN_CENTRAL_URL}" \
      -Dartifact="com.datadoghq:ddprof-lib:${DDPROF_VERSION}" \
      -q > "${MVN_LOG1}" 2>&1); then
    log_error "Failed to download com.datadoghq:ddprof-lib:${DDPROF_VERSION}"
    cat "${MVN_LOG1}"
    exit 1
  fi
  DDPROF_JAR="${HOME}/.m2/repository/com/datadoghq/ddprof-lib/${DDPROF_VERSION}/ddprof-lib-${DDPROF_VERSION}.jar"
  DDPROF_SOURCE="Maven Central (ddprof-lib ${DDPROF_VERSION})"
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

# ── Step 2b: Deduplication check (nightly only) ───────────────────────────────
#
# When NIGHTLY_PROFILER_SNAPSHOT=true and NIGHTLY_FORCE_PUBLISH is not set,
# compare the resolved version pair against the last successful publish recorded
# in STATE_FILE. Skip if unchanged to avoid redundant OSSRH uploads.

if [ "${NIGHTLY_PROFILER_SNAPSHOT:-}" = "true" ] && \
   [ "${NIGHTLY_FORCE_PUBLISH:-}" != "true" ]; then
  if [ -f "${STATE_FILE}" ]; then
    # shellcheck source=/dev/null
    source "${STATE_FILE}"
    LAST_DDPROF="${LAST_PUBLISHED_DDPROF_VERSION:-}"
    LAST_TRACE="${LAST_PUBLISHED_DD_TRACE_VERSION:-}"
    if [ "${LAST_DDPROF}" = "${DDPROF_VERSION}" ] && \
       [ "${LAST_TRACE}" = "${DD_TRACE_VERSION}" ]; then
      log_info "Versions unchanged since last publish (ddprof=${DDPROF_VERSION}, dd-trace=${DD_TRACE_VERSION}) — skipping."
      log_info "Set NIGHTLY_FORCE_PUBLISH=true to override."
      exit 0
    fi
    log_info "Version changed (ddprof: ${LAST_DDPROF:-none}→${DDPROF_VERSION}, dd-trace: ${LAST_TRACE:-none}→${DD_TRACE_VERSION}) — publishing."
  else
    log_info "No prior state found — publishing."
  fi
fi

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
  --with-decryption --query "Parameter.Value" --out text | tr -d '\n\r') \
  || { log_error "Failed to fetch Sonatype username from SSM"; exit 1; }
SONATYPE_PASSWORD=$(aws ssm get-parameter \
  --region "${AWS_REGION}" \
  --name "${SSM_PREFIX}.sonatype_token" \
  --with-decryption --query "Parameter.Value" --out text | tr -d '\n\r') \
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

# ── Step 7: Update state (nightly deduplication) ──────────────────────────────

if [ "${NIGHTLY_PROFILER_SNAPSHOT:-}" = "true" ]; then
  {
    echo "LAST_PUBLISHED_DDPROF_VERSION=${DDPROF_VERSION}"
    echo "LAST_PUBLISHED_DD_TRACE_VERSION=${DD_TRACE_VERSION}"
  } > "${STATE_FILE}"
  log_info "State written to ${STATE_FILE}"
fi
