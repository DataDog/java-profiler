#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Agent-hook policy: deny file-tool writes into .knowledgebase/, which only the cairn
skills write (through `cairn memorize`, not the agent's file tools). Reads the target
path, relative to its checkout's top level, on stdin; exit 2 with the reason on stderr
denies the write, exit 0 allows it."""

import posixpath
import sys

KB_DIR = ".knowledgebase"


def main():
    rel = posixpath.normpath(sys.stdin.read().strip())
    # Case-blind, as on macOS's default file system; on Linux this also blocks a distinct
    # `.KnowledgeBase/`, an accepted false block.
    folded = rel.lower()
    if folded != KB_DIR and not folded.startswith(KB_DIR + "/"):
        return 0
    print("Blocked write to `%s`: .knowledgebase/ is written only by the cairn skills.\n"
          "Record findings with cairn (`cairn memorize`); never edit memory files by hand."
          % rel, file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main())
