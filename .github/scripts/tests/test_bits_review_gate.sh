#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Hermetic runner for the Bits review gate suite: byte-compiles both gate
# scripts, then runs only this gate's Python test family.
# Run with: bash .github/scripts/tests/test_bits_review_gate.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

# Hermetic: the suite never needs credentials, so unset both tokens; a stray
# value in the environment cannot change any test outcome.
unset GITHUB_TOKEN STATUS_TOKEN

# Byte-compile first: a missing or syntactically broken gate script fails
# before any test runs.
python3 -m py_compile "$SCRIPT_DIR/../bits_review_gate.py" \
  "$SCRIPT_DIR/../bits_review_gate_policy.py"

# The discover pattern runs only this gate's family; the shared helper
# bits_review_gate_testlib.py is its one allowed non-family import.
cd "$SCRIPT_DIR/../../.."
exec python3 -m unittest discover -s .github/scripts/tests -p 'test_bits_review_gate_*.py'
