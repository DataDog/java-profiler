#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
#
# Records an inconclusive memory verdict in build.env without failing the
# job. Runs only after the FAIL path (which exits 1) has not fired, so a
# confirmed fail keeps its REASON_ key and exit 1.

set -u

ERR_LOG=${ERR_LOG:-err.log}
BUILD_ENV=${BUILD_ENV:-build.env}

reason=$(grep -m1 '^INCONCLUSIVE:' "${ERR_LOG}" 2>/dev/null | cut -f2- -d':' | tr -d '\n')
if [ -z "${reason}" ]; then
  exit 0
fi
key=$(printf 'INCONCLUSIVE_%s_%s_%sX%s' "${CONFIG:-}" "${ALLOCATOR:-}" "${ARCH:-}" "${VARIANT:-}" | tr '+' '_')
echo "${key}=${reason}" >> "${BUILD_ENV}"
exit 0
