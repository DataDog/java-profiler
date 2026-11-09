#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
#
# Writes the memory gate's candidate, this pipeline's published snapshot build
# pinned by its timestamp, as a dotenv file for the speedlab trigger job:
#   MEMORY_GATE_CANDIDATE=snapshot:1.54.0-my_branch-20261109.101500-3
# A branch selector would be resolved again in speedlab and could pick a newer
# push; the timestamped build cannot change.
#
# Usage: resolve-candidate.sh <version.txt> <dotenv out> [maven-metadata.xml]
# version.txt is deploy-artifact's ("com.datadoghq:ddprof:<version>"). The
# metadata file defaults to the snapshot repository's for that version.
set -euo pipefail

# The main jar's timestamped build in a snapshot's maven-metadata.xml (stdin):
# the last <snapshotVersion> with no classifier and extension jar.
latest_jar_build() {
  awk '
    /<snapshotVersion>/ { classifier=""; extension=""; value="" }
    /<classifier>/ { classifier=$0; gsub(/.*<classifier>|<\/classifier>.*/, "", classifier) }
    /<extension>/ { extension=$0; gsub(/.*<extension>|<\/extension>.*/, "", extension) }
    /<value>/ { value=$0; gsub(/.*<value>|<\/value>.*/, "", value) }
    /<\/snapshotVersion>/ { if (classifier == "" && extension == "jar") last=value }
    END { print last }
  '
}

main() {
  local version_file=$1 out=$2 metadata=${3:-}
  local version
  version=$(sed -n 's/^com\.datadoghq:ddprof://p' "$version_file")
  if [[ "$version" != *-SNAPSHOT ]]; then
    echo "ERROR: '${version}' from ${version_file} is not a snapshot version" >&2
    return 1
  fi
  local build
  if [ -n "$metadata" ]; then
    build=$(latest_jar_build < "$metadata")
  else
    build=$(curl -fsSL --connect-timeout 10 --max-time 30 \
      "https://central.sonatype.com/repository/maven-snapshots/com/datadoghq/ddprof/${version}/maven-metadata.xml" \
      | latest_jar_build)
  fi
  # The build is the version with -SNAPSHOT replaced by <date>.<time>-<n>.
  if [[ ! "$build" =~ ^${version%-SNAPSHOT}-[0-9]{8}\.[0-9]{6}-[0-9]+$ ]]; then
    echo "ERROR: no timestamped jar build of ${version} in the snapshot metadata (got '${build}')" >&2
    return 1
  fi
  echo "MEMORY_GATE_CANDIDATE=snapshot:${build}" > "$out"
  echo "Memory gate candidate: snapshot:${build}"
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
