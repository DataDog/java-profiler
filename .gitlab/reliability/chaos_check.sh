#!/usr/bin/env bash
#
# CI entry point for the chaos harness. Thin wrapper around
# utils/run-chaos-harness.sh — this file only supplies the CI-specific
# caching paths (so repeated scheduled runs on the same runner reuse the
# downloaded JDK/agent jar) and the fixed hs_err.log location the pipeline's
# `artifacts:` block expects at the repo root. All the actual build/run logic
# lives in the standalone script, which is also runnable by hand.

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ROOT="$( cd "${HERE}/../.." >/dev/null 2>&1 && pwd )"

export CHAOS_JDK_DIR="${CHAOS_JDK_DIR:-/opt/jdk-${CHAOS_JDK}}"
export CHAOS_WORK_DIR="${CHAOS_WORK_DIR:-/var/lib/datadog}"
export CHAOS_ERROR_FILE="${ROOT}/hs_err.log"

exec "${ROOT}/utils/run-chaos-harness.sh" "$@"
