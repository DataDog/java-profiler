#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
set -euo pipefail

if [[ $# != 1 || ! $1 =~ ^[0-9a-f]{40}$ ]]; then
  echo 'Expected a full release commit SHA' >&2
  exit 2
fi

# Reconstruct the signed bytes from the resolved release target, not the note.
# The source digest independently binds the signing run to that same commit.
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
printf '%s\n' "$1" > "$work/certified-commit.txt"
gh attestation verify "$work/certified-commit.txt" --repo DataDog/java-profiler \
  --signer-workflow DataDog/java-profiler/.github/workflows/certification.yml \
  --source-ref refs/heads/main --source-digest "$1" --deny-self-hosted-runners
