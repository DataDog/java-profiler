#!/usr/bin/env bash

function prepareJdk() {
  local jdk_distro=$1
  local target_path=$2

  if [ -e "$target_path/bin/java" ]; then
    echo "JDK $jdk_distro already installed at $jdk_path"
    return
  fi

  echo 'n' | sdk install java ${jdk_distro}
  ln -s ~/.sdkman/candidates/java/${jdk_distro} ${target_path}
}