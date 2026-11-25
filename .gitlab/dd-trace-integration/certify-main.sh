#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.

set -euo pipefail

# This job's mirrored success must mean main's integration check executed.
# Cancellation and missing artifacts must fail, never produce a green no-op.
if [ "${CI_PIPELINE_SOURCE:-}" != "push" ] || [ "${CI_COMMIT_BRANCH:-}" != "main" ]; then
  echo "::error::Integration certification requires a main push pipeline" >&2
  exit 1
fi
if [ "${CANCELLED:-}" = "true" ]; then
  echo "::error::Cancelled integration cannot certify a candidate" >&2
  exit 1
fi
if ! [[ "${CI_COMMIT_SHA:-}" =~ ^[0-9a-f]{40}$ ]]; then
  echo "::error::Integration certification requires a full candidate SHA" >&2
  exit 1
fi
if [ ! -f ddprof-commit-sha.txt ] || [ "$(<ddprof-commit-sha.txt)" != "${CI_COMMIT_SHA}" ]; then
  echo "::error::Prepared agent evidence is missing or belongs to another SHA" >&2
  exit 1
fi

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
bash "${HERE}/validate-quarantine.sh"
# The existing aggregator skips PR posting for main, before obtaining any token.
# Pin its legacy metadata to this pipeline rather than an inherited environment.
export DDPROF_COMMIT_BRANCH=main
export DDPROF_COMMIT_SHA="${CI_COMMIT_SHA}"
exec bash "${HERE}/post-pr-comment.sh" integration-test-results
