function get_version() {
  if [[ "${CI_COMMIT_TAG}" =~ ^v_[0-9.]+(-SNAPSHOT)?$ ]]; then
    echo "${CI_COMMIT_TAG//v_/}"
    return
  fi

  local branch="${CI_COMMIT_BRANCH:-${CI_COMMIT_REF_NAME:-}}"
  local version
  if [ -n "${branch}" ] && [ "${branch}" != "${CI_DEFAULT_BRANCH:-main}" ] && [ "${branch}" != "main" ] && [[ ! "${branch}" =~ ^release/ ]]; then
    version=$(utils/compute-version.sh --branch-suffix "${branch}")
  else
    version=$(utils/compute-version.sh)
  fi

  if [ -z "$version" ]; then
    echo "ERROR: Failed to determine version from compute-version.sh" >&2
    return 1
  fi
  echo "$version"
}

function get_current_version() {
  get_version
}

function get_previous_version() {
  CURRENT=$(get_current_version)
  LOOKBACK=1
  if [[ ! $CURRENT =~ ^.*?-SNAPSHOT$ ]]; then
    # current version is not a snapshot; need to look at the previous tag
    LOOKBACK=2
  fi
  git tag | grep v_ | sort -t_ -k2,2V | tail -n ${LOOKBACK} | head -n 1 | sed -e "s#v_##g"
}

function setup_java_home() {
  if [ -z "${JAVA_HOME}" ] || [ ! -x "${JAVA_HOME}/bin/java" ]; then
    if [ -x ~/.sdkman/candidates/java/current/bin/java ]; then
      export JAVA_HOME=~/.sdkman/candidates/java/current
    else
      echo "ERROR: JAVA_HOME=${JAVA_HOME:-<unset>} does not point to a valid Java installation."
      exit 1
    fi
  fi

  echo "Using Java @ ${JAVA_HOME}"
}

function is_new_snapshot_version() {
  local candidate="$1"
  local baseline="$2"
  [ -n "${candidate}" ] && [ "${candidate}" != "${baseline}" ]
}

function collect_artifacts() {
  local target=$1
  local artifact_type=$2  # "test" or "stresstest"
  local source_dir=$3
  local base_dir=${4:-${HERE:-$(pwd)}}

  mkdir -p "${base_dir}/${artifact_type}/${target}/reports"
  mkdir -p "${base_dir}/${artifact_type}/${target}/logs"

  # Collect reports
  if [ -d "${source_dir}/build/reports" ]; then
    cp -r "${source_dir}/build/reports" "${base_dir}/${artifact_type}/${target}/" || echo "WARNING: No reports found"
  fi

  # Collect logs from /tmp
  find /tmp -maxdepth 1 \( -name "*.jfr" -o -name "*.json" -o -name "*.txt" \) -exec cp {} "${base_dir}/${artifact_type}/${target}/logs/" \; 2>/dev/null || true

  # Collect crash logs (limit search depth to avoid long searches)
  find . -maxdepth 2 -name 'hs_err*' -exec cp {} "${base_dir}/${artifact_type}/${target}/logs/" \; 2>/dev/null || true
}
