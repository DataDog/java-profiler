function get_version() {
  rm -f .version

  if [[ "${CI_COMMIT_TAG}" =~ ^v_[0-9.]+(-SNAPSHOT)?$ ]]; then
    echo "${CI_COMMIT_TAG//v_/}"
    return
  fi

  local gradlecmd=$GRADLE_CMD
  if [ -z "$gradlecmd" ]; then
    gradlecmd="./gradlew"
  fi
  ${gradlecmd} printVersion --max-workers=1 --build-cache --stacktrace --info --no-watch-fs --no-daemon | grep 'Version:' | cut -f2 -d' ' > .version
  local version=$(cat .version)
  if [ -z "$version" ]; then
    echo "ERROR: Failed to determine version from Gradle printVersion task" >&2
    return 1
  fi

  local branch="${CI_COMMIT_BRANCH:-${CI_COMMIT_REF_NAME:-}}"
  local default_branch="${CI_DEFAULT_BRANCH:-main}"
  if [ -n "${branch}" ] && [ "${branch}" != "${default_branch}" ] && [ "${branch}" != "main" ]; then
    local suffix=$(echo "$branch" | tr '/' '_')
    version=$(echo "$version" | sed "s#-SNAPSHOT#-${suffix}-SNAPSHOT#g")
  fi
  echo "${version}"
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
  if [ -z "${JAVA_HOME}" ]; then
    export JAVA_HOME=~/.sdkman/candidates/java/current
  fi

  if [ ! -d "$JAVA_HOME" ]; then
    echo "ERROR: JAVA_HOME does not exist: $JAVA_HOME"
    exit 1
  fi

  echo "Using Java @ ${JAVA_HOME}"
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
