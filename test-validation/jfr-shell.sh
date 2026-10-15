#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.

set -euo pipefail

# Pin a Java 25 release and resolve its backend through JBang too. Otherwise
# jfr-shell auto-installs the backend with its own hardcoded public repositories.
JAFAR_VERSION="0.26.2"
jbang_args=(--java 25 --ignore-transitive-repositories
  --deps "io.btrace:jfr-shell-jafar:${JAFAR_VERSION}")
if [ -n "${MAVEN_REPOSITORY_PROXY:-}" ]; then
  jbang_args+=(--repos "central=${MAVEN_REPOSITORY_PROXY}")
fi

# Use Maven coordinates directly: the remote catalog launcher declares its own
# public repository, which can be added alongside JBang's --repos option.
exec jbang "${jbang_args[@]}" "io.btrace:jafar-shell:${JAFAR_VERSION}" "$@"
