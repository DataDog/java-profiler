#!/usr/bin/env bash

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
    curl -L --fail "${URL}" | tar -xvzf - -C ${target_path} --strip-components 1
    return
  fi

  if [[ ${qualifier} == "orcl" ]]; then
    if [[ ${version} == "8" ]]; then
      mkdir -p "${target_path}"
      curl -L --fail "${JAVA_8_ORACLE_URL}" | sudo tar -xvzf - -C ${target_path} --strip-components 1
      return
    else
      echo "Oracle JDK 8 only!"
      exit 1
    fi
  fi

  if [[ ${qualifier} == "ibm" ]]; then
    if [[ ${version} == "8" ]]; then
      mkdir -p "${target_path}"
      curl -L --fail "${JAVA_8_IBM_URL}" | sudo tar -xvzf - -C ${target_path} --strip-components 2
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
    curl -L --fail "${URL}" | sudo tar -xvzf - -C ${target_path} --strip-components 1
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
