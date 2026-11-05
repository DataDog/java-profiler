#! /bin/bash
# Selects the JDK under test inside the openjdk-build CI image and prints its
# home directory. The image layout is not fixed across JDK_VERSION values, so
# every java executable under the search root is located and mapped back to
# its JDK home; the result is what the job exports as JAVA_TEST_HOME, which is
# the variable the profiler-test Gradle plugin resolves the test JVM from.
#
# Usage: select_test_jdk.sh [search-root]   (default: /usr/lib/jvm)
#
# With several JDKs installed, the one whose path contains $JDK_VERSION is
# preferred; failing that, the script exits non-zero instead of guessing.

set -euo pipefail

root="${1:-/usr/lib/jvm}"

if [ ! -d "${root}" ]; then
  echo "select_test_jdk: search root does not exist: ${root}" >&2
  exit 1
fi

homes=()
while IFS= read -r java_bin; do
  if [ -x "${java_bin}" ]; then
    homes+=("${java_bin%/bin/java}")
  fi
done < <(find "${root}" -name java -path '*/bin/java' | sort -u)

if [ "${#homes[@]}" -eq 0 ]; then
  echo "select_test_jdk: no JDK with an executable bin/java found under ${root}" >&2
  exit 1
fi

if [ "${#homes[@]}" -eq 1 ]; then
  echo "${homes[0]}"
  exit 0
fi

matches=()
if [ -n "${JDK_VERSION:-}" ]; then
  for home in "${homes[@]}"; do
    case "${home}" in
      *"${JDK_VERSION}"*)
        matches+=("${home}")
        ;;
    esac
  done
  if [ "${#matches[@]}" -eq 1 ]; then
    echo "${matches[0]}"
    exit 0
  fi
  if [ "${#matches[@]}" -gt 1 ]; then
    echo "select_test_jdk: ${#matches[@]} JDKs under ${root} match JDK_VERSION='${JDK_VERSION}':" >&2
    printf '  %s\n' "${matches[@]}" >&2
    exit 1
  fi
fi

echo "select_test_jdk: ${#homes[@]} JDKs under ${root} and none matches JDK_VERSION='${JDK_VERSION:-}':" >&2
printf '  %s\n' "${homes[@]}" >&2
exit 1
