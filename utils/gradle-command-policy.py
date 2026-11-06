#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Agent-hook policy: deny shell commands that run gradlew directly instead of through
.claude/commands/build-and-summarize. Reads the command text on stdin; exit 2 with the
reason on stderr denies the command, exit 0 allows it."""

import itertools
import os
import re
import shlex
import sys

# Deny by default: every simple command that names gradlew is denied unless it starts
# with a read-only tool, so new prefixes (`if`, `env -u X`, `> log`) cannot slip through.
SEPARATOR = re.compile(r"[;&|(){}`\n]")
READERS = frozenset({"cat", "less", "more", "head", "tail", "grep", "egrep", "fgrep", "rg",
                     "ls", "find", "file", "stat", "wc", "diff", "git", "sed", "awk", "echo",
                     "printf", "chmod", "which", "type"})
# Daemon housekeeping that builds nothing, so the wrapper's log capture adds nothing.
ALLOWED_ARGS = ({"--stop"}, {"--version"})
REDIRECT = re.compile(r"^\d*[<>]")
REDIRECT_OP = re.compile(r"^\d*[<>]+$")  # operator alone: its target is the next word
ASSIGNMENT = re.compile(r"^\w+=")


def words(segment):
    """Words of one simple command, redirections dropped. A quote that the separator split
    left open (`bash -c "cd x; ./gradlew build"`) falls back to whitespace splitting."""
    try:
        raw = iter(shlex.split(segment))
    except ValueError:
        raw = iter(segment.split())
    kept = []
    for w in raw:
        if REDIRECT_OP.match(w):
            next(raw, None)
        elif not REDIRECT.match(w):
            kept.append(w)
    return kept


def direct_call(command):
    """The first denied gradlew call in command, or None."""
    for segment in SEPARATOR.split(command):
        ws = list(itertools.dropwhile(ASSIGNMENT.match, words(segment)))
        if not ws or os.path.basename(ws[0]) in READERS:
            continue
        for i, w in enumerate(ws):
            if os.path.basename(w.strip("'\"")) in ("gradlew", "gradlew.bat"):
                if set(ws[i + 1:]) in ALLOWED_ARGS:
                    break
                return " ".join(ws[i:]).strip("'\"")
            if any(c.isspace() for c in w):  # a quoted script, as in `bash -c '...'`
                nested = direct_call(w)
                if nested:
                    return nested
    return None


def main():
    # Join backslash-continued lines so `./gradlew \<newline> build` is one command.
    call = direct_call(sys.stdin.read().replace("\\\n", " "))
    if call:
        print("Blocked `%s`: run Gradle through `./.claude/commands/build-and-summarize "
              "<task...>`, which keeps the full log in build/logs/ (AGENTS.md, Operating "
              "Rules). Only `gradlew --stop` and `gradlew --version` may run directly."
              % call, file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
