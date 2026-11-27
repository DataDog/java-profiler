#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# fetchAndExtract <url> <target_path> <strip_components> [sudo]
# Streams the archive into tar like a plain `curl | tar`, but reports the
# HTTP status and fails on a curl error: without pipefail the pipeline exits
# with tar's status, so a 404 would surface only as a gzip error.
function fetchAndExtract() {
  local url=$1
  local target_path=$2
  local strip=$3
  local tar_cmd=(tar)
  if [[ "${4:-}" == "sudo" ]]; then
    tar_cmd=(sudo tar)
  fi
  curl -L --fail -w '%{stderr}HTTP status: %{http_code}\n' "${url}" | "${tar_cmd[@]}" -xvzf - -C "${target_path}" --strip-components "${strip}"
  local statuses=("${PIPESTATUS[@]}")
  if [[ ${statuses[0]} -ne 0 ]]; then
    echo "Download failed (curl exit ${statuses[0]}, HTTP status above): ${url}" >&2
    return 1
  fi
  if [[ ${statuses[1]} -ne 0 ]]; then
    echo "Extraction failed (tar exit ${statuses[1]}): ${url}" >&2
    return 1
  fi
}

function prepareJdk() {
  local variant=$1
  local arch=$2
  local version=${variant%%-*}
  local qualifier=${variant#*-}

  local target_path="${GITHUB_WORKSPACE}/${JDKS_DIR}/jdk${variant}"

  mkdir -p ${target_path}

  if [[ ${qualifier} == "librca" ]] && [[ "${arch}" =~ "-musl" ]]; then
    local osarch="${arch%-musl}"
    local suffix=
    if [[ "${osarch}" == "aarch64" ]]; then
      suffix="AARCH64_"
    fi
    URL_VAR="JAVA_${version}_MUSL_${suffix}URL"
    URL="${!URL_VAR}"
    if [[ -z "${URL}" ]]; then
      echo "Musl/Liberica JDK URL not found for ${arch}/${variant}"
      exit 1
    fi
    fetchAndExtract "${URL}" "${target_path}" 1 || exit 1
    return
  fi

  if [[ ${qualifier} == "orcl" ]]; then
    if [[ ${version} == "8" ]]; then
      mkdir -p "${target_path}"
      fetchAndExtract "${JAVA_8_ORACLE_URL}" "${target_path}" 1 sudo || exit 1
      return
    else
      echo "Oracle JDK 8 only!"
      exit 1
    fi
  fi

  if [[ ${qualifier} == "ibm" ]]; then
    if [[ ${version} == "8" ]]; then
      mkdir -p "${target_path}"
      fetchAndExtract "${JAVA_8_IBM_URL}" "${target_path}" 2 sudo || exit 1
      return
    else
      echo "IBM JDK 8 only!"
      exit 1
    fi
  fi

  if [[ ${qualifier} == "zing" ]]; then
    URL_VAR="JAVA_${version}_ZING_URL"
    if [[ "${arch}" == "aarch64" ]]; then
      URL_VAR="JAVA_${version}_ZING_AARCH64_URL"
    fi

    URL="${!URL_VAR}"
    if [[ -z "${URL}" ]]; then
      echo "Zing JDK URL not found for ${variant}"
      exit 1
    fi
    fetchAndExtract "${URL}" "${target_path}" 1 sudo || exit 1
    if [[ "${arch}" != "aarch64" ]]; then
      # rename the bundled libstdc++.so to avoid conflicts with the system one
      sudo mv ${target_path}/etc/libc++/libstdc++.so.6 ${target_path}/etc/libc++/libstdc++.so.6.bak
    fi
    return
  fi

  # below the installation of the SDKMAN-managed JDK
  source ~/.sdkman/bin/sdkman-init.sh

  local suffix="tem"
  local versionVar="JAVA_${version}_VERSION"
  if [[ "${qualifier}" == "j9" ]]; then
    suffix="sem"
    versionVar="JAVA_${version}_J9_VERSION"
  elif [[ "${qualifier}" == "graal" ]]; then
    suffix="graal"
    versionVar="JAVA_${version}_GRAAL_VERSION"
  fi

  local distro_base
  distro_base="${!versionVar}"
  local jdk_distro="${distro_base}-${suffix}"

  echo 'n' | sdk install java ${jdk_distro} > /dev/null

  rm -rf ${target_path}
  mkdir -p "$(dirname ${target_path})"
  mv ${SDKMAN_DIR}/candidates/java/${jdk_distro} ${target_path}
}
