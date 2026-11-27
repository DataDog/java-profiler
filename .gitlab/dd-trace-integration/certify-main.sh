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
# Both gate scripts accept a list path. Ignore inherited paths and working-tree
# contents: validate and aggregate with the same bytes from the candidate commit.
unset QUARANTINE_LIST
policy_dir=$(mktemp -d)
trap 'rm -rf "$policy_dir"' EXIT
export QUARANTINE_LIST="$policy_dir/quarantine.txt"
if ! git --no-replace-objects -C "$HERE" cat-file blob "$CI_COMMIT_SHA:.gitlab/dd-trace-integration/quarantine.txt" > "$QUARANTINE_LIST"; then
  echo '::error::Cannot read the quarantine list from the candidate commit' >&2
  exit 1
fi
bash "${HERE}/validate-quarantine.sh"
# The existing aggregator skips PR posting for main, before obtaining any token.
# Pin its legacy metadata to this pipeline rather than an inherited environment.
export DDPROF_COMMIT_BRANCH=main
export DDPROF_COMMIT_SHA="${CI_COMMIT_SHA}"
bash "${HERE}/post-pr-comment.sh" integration-test-results
