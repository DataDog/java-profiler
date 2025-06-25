#!/usr/bin/env bash
set -x

# This script is used to initialize the cherry-pick repo from async-profiler

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

PATH_REPO="$1"

if [ -z "$PATH_REPO" ]; then
  mkdir -p .tmp
  PATH_REPO="$HERE/../.tmp/async-profiler-cherry"
fi

if [ ! -d "$PATH_REPO" ]; then
  git clone https://github.com/async-profiler/async-profiler.git $PATH_REPO

  cd "$PATH_REPO" || exit 1

  git remote add upstream https://github.com/async-profiler/async-profiler.git
fi

cd "$HERE" || exit 1

git remote add cherry file://"$PATH_REPO" || true
