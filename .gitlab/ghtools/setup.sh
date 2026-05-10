#! /bin/bash

set -eou pipefail

CI_JOB_TOKEN=$1

if [ -z "$CI_JOB_TOKEN" ]; then
  echo "Skip installation of Github tools."
  exit 0
fi

#apt update && apt install -y hwinfo procps git curl software-properties-common build-essential libnss3-dev zlib1g-dev libgdbm-dev libncurses5-dev libssl-dev libffi-dev libreadline-dev libsqlite3-dev libbz2-dev openjdk-11-jdk
#git clone -q --depth 1 https://github.com/pyenv/pyenv.git --branch "v2.0.4" --single-branch /pyenv
#export PYENV_ROOT="/pyenv"
#export PATH="/pyenv/shims:/pyenv/bin:$PATH"
#eval "$(pyenv init -)"
#pyenv install 3.9.6 && pyenv global 3.9.6
#
#pip3 install awscli virtualenv setuptools

git clone https://gitlab-ci-token:${CI_JOB_TOKEN}@gitlab.ddbuild.io/DataDog/benchmarking-platform-tools.git benchmarking-tools

cd benchmarking-tools/github-tools
./install.sh

echo "GITHUB_TOOLS_HOME=$(pwd)" >> ~/.bashrc
echo 'PATH=${GITHUB_TOOLS_HOME}:$PATH' >> ~/.bashrc