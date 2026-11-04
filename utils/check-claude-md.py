#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check that CLAUDE.md is the canonical redirect stub to AGENTS.md.

Claude Code reads CLAUDE.md for its Compact Instructions; everything else lives in
AGENTS.md so that every coding agent reads the same instructions. This script holds
the canonical text; `--write` restores it.

Exit codes: 0 canonical (or written), 1 missing or different, 2 environment error.
"""

import argparse
import difflib
import os
import sys

CANONICAL = """\
# CLAUDE.md

**This file redirects to AGENTS.md for tooling-agnostic project instructions.**

Read and follow all instructions in [AGENTS.md](AGENTS.md) in this directory.

All project guidance, build commands, architecture details, and development guidelines
are maintained in AGENTS.md to support multiple AI coding tools.

## Compact Instructions

When compacting this conversation, prioritize keeping: decisions made, code/config diffs,
open questions, and file:line references. Drop raw tool output that can be re-fetched on
demand — full file contents, grep/search dumps, build/test logs — summarize these to a
one-line pointer (what was read/run and the conclusion) instead of retaining them verbatim.
"""


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    ap.add_argument("--write", action="store_true", help="write the canonical CLAUDE.md")
    args = ap.parse_args(argv)
    path = os.path.join(args.root, "CLAUDE.md")
    try:
        if args.write:
            with open(path, "w", encoding="utf-8") as f:
                f.write(CANONICAL)
            print("CLAUDE.md: written")
            return 0
        if not os.path.exists(path):
            print("CLAUDE.md: missing; run utils/check-claude-md.py --write")
            return 1
        with open(path, encoding="utf-8") as f:
            actual = f.read()
    except OSError as e:
        print("error: %s" % e, file=sys.stderr)
        return 2
    if actual == CANONICAL:
        print("CLAUDE.md: OK")
        return 0
    sys.stdout.writelines(difflib.unified_diff(actual.splitlines(True), CANONICAL.splitlines(True),
                                               "CLAUDE.md", "canonical"))
    print("CLAUDE.md: differs from the canonical stub; keep project guidance in AGENTS.md "
          "and run utils/check-claude-md.py --write")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
