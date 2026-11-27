#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Hermetic tests for utils/babysit-pr.py and utils/babysit_pr_policy.py: GitHub is a
# fake gh (fake_gh.py), git runs on temporary repositories.
# Run with: bash utils/tests/test_babysit_pr.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
python3 -m py_compile "$SCRIPT_DIR/../babysit-pr.py" "$SCRIPT_DIR/../babysit_pr_policy.py"
chmod +x "$SCRIPT_DIR/fake_gh.py"
exec python3 "$SCRIPT_DIR/test_babysit_pr.py" -v
