#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Fail a pull request whose title and body reference no tracker ticket.

A reference is a Jira key `PROF-<n>` or a GitHub issue `#<n>`. Bot accounts
(login ending in `[bot]`, e.g. dependabot) are exempt. Reads PR_TITLE, PR_BODY
and PR_AUTHOR from the environment, so workflow expressions never reach a shell.

Exit codes: 0 referenced or exempt, 1 no reference.
"""

import os
import re
import sys

# The PR template's placeholder `JIRA-XXXX` must not count.
TICKET = re.compile(r"\bPROF-\d+\b|(?<![\w&])#\d+\b")


def main():
    title = os.environ.get("PR_TITLE", "")
    body = os.environ.get("PR_BODY", "")
    author = os.environ.get("PR_AUTHOR", "")
    if author.endswith("[bot]"):
        print("ticket reference: exempt (%s)" % author)
        return 0
    m = TICKET.search(title + "\n" + body)
    if m:
        print("ticket reference: %s" % m.group(0))
        return 0
    print("error: no tracker ticket in the PR title or body. Add a Jira key (PROF-<n>) "
          "or a GitHub issue (#<n>), e.g. in the template's JIRA line.", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
