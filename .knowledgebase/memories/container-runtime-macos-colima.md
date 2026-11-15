---
id: container-runtime-macos-colima
title: Container tests on macOS: podman is broken locally, use colima+docker
kind: finding
tags: []
applies_to: []
source: implement-github-issue-sphinx/container-runtime-macos-colima
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# Container tests on macOS: podman is broken locally, use colima+docker

**Observed symptom (verified on this machine):** every `podman run` command aborts with
`error getting credentials` before the container starts. Cause: podman resolves the Datadog
registry credentials via the `ddtool` credHelper declared in ~/.docker/config.json
(credHelpers for registry-staging.ddbuild.io / registry.ddbuild.io / registry.us1-build.fed.dog);
ddtool fetches an identity JWT from vault.us1-build.fed.dog, which /etc/hosts blackholes to
127.0.0.1 ("Explicitely fail probe to fed vault"). Fatal because podman treats helper failure
as an error.

**Working path:** colima (docker runtime) + docker CLI client (`brew install docker`,
`brew link --overwrite docker` if a Docker.app bash-completion symlink blocks linking).
Colima context already set in ~/.docker/config.json (currentContext: colima).
`./utils/run-containers-tests.sh --container=docker ...` works; Docker Hub pulls
(debian/eclipse-temurin base images) do not touch the ddtool helpers.

Docs updated: AGENTS.md, README.md, utils/README.md (commit b412cd098). Script default
(podman, for Linux CI) intentionally unchanged.
