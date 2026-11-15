#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
# CI discovers shell entry points; these suites use inert process/runtime fixtures.
set -euo pipefail
ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
cd "$ROOT"
python3 -m unittest utils/test_gradle_summary.py utils/test_run_containers_tests.py
python3 .github/scripts/tests/test_assert_vm_qualification.py
