#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for .github/scripts/check_pr_ticket.py.
# Run with: .github/scripts/tests/test_check_pr_ticket.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
CHECK="$SCRIPT_DIR/../check_pr_ticket.py"
TESTS=0
FAILED=0

# expect <name> <expected-exit> <title> <body> <author>
expect() {
  local name=$1 want=$2 rc=0
  PR_TITLE=$3 PR_BODY=$4 PR_AUTHOR=$5 python3 "$CHECK" >/dev/null 2>&1 || rc=$?
  TESTS=$((TESTS + 1))
  if [ "$rc" -ne "$want" ]; then
    FAILED=$((FAILED + 1))
    echo "FAIL: $name: exit $rc, want $want" >&2
  fi
}

expect "Jira key in title" 0 "Fix the thing (PROF-123)" "" alice
expect "Jira key in body" 0 "Fix the thing" $'Notes\n- [x] JIRA: [PROF-42](https://x/PROF-42)' alice
expect "GitHub issue in body" 0 "Fix the thing" "Fixes #77" alice
expect "issue at start of title" 0 "#12 follow-up" "" alice
expect "no reference" 1 "Fix the thing" "Some description" alice
expect "template placeholder only" 1 "Fix the thing" "- [ ] JIRA: [JIRA-XXXX]" alice
expect "other Jira project" 1 "Fix the thing (ABC-12)" "" alice
expect "key without number" 1 "PROF- cleanup" "" alice
expect "key embedded in a word" 1 "XPROF-12 cleanup" "" alice
expect "HTML entity is not an issue" 1 "Fix" "a &#39;quoted&#39; word" alice
expect "anchor is not an issue" 1 "Fix" "see doc/README.md#section" alice
expect "bot author exempt" 0 "Bump foo from 1 to 2" "" "dependabot[bot]"
expect "bot suffix only at the end" 1 "Fix" "" "bot[bot]-impostor"
expect "empty environment" 1 "" "" ""

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
