#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Agent-hook policy: deny shell commands that run gradlew directly instead of through
.claude/commands/build-and-summarize. Reads the command text on stdin; exit 2 with the
reason on stderr denies the command, exit 0 allows it."""

import re
import shlex
import sys

# gradlew in command position: at the start, after a separator or an opening quote
# (`bash -c "./gradlew ..."`), behind optional prefixes such as `env`, `timeout 60` or `sh`.
# Matched on raw text like require-fresh-review.py, so a quoted mention is a false block.
PREFIX = (r"(?:\w+=\S*|env|exec|time|nohup|command|xargs|then|do|else|!"
          r"|timeout\s+\S+|(?:ba|z|da)?sh(?:\s+-\w+)*)")
GRADLEW = re.compile(r"(?:^|[;&|(){}`\n\"']|\$\()\s*(?:" + PREFIX + r"\s+)*"
                     r"((?:[^\s;&|(){}'\"`]*/)?gradlew(?:\.bat)?)(?![\w.-])"
                     r"([^;&|)}\n]*)", re.M)
# Daemon housekeeping that builds nothing, so the wrapper's log capture adds nothing.
ALLOWED_ARGS = ({"--stop"}, {"--version"})
REDIRECT = re.compile(r"^\d*[<>]")
REDIRECT_OP = re.compile(r"^\d*[<>]+&?$")  # operator alone: its target is the next token


def allowed(args):
    """Args include any quoted text, so `--stop "build"` is denied; an unbalanced quote
    (the end of `bash -c "./gradlew ..."`) makes shlex fail, which denies too."""
    try:
        tokens = iter(shlex.split(args))
    except ValueError:
        return False
    kept = set()
    for t in tokens:
        if REDIRECT_OP.match(t):
            next(tokens, None)
        elif not REDIRECT.match(t):
            kept.add(t)
    return kept in ALLOWED_ARGS


def main():
    # Join backslash-continued lines so `./gradlew \<newline> build` is one line to the regex.
    command = sys.stdin.read().replace("\\\n", " ")
    for m in GRADLEW.finditer(command):
        if not allowed(m.group(2)):
            print("Blocked `%s`: run Gradle through `./.claude/commands/build-and-summarize "
                  "<task...>`, which keeps the full log in build/logs/ (AGENTS.md, Operating "
                  "Rules). Only `gradlew --stop` and `gradlew --version` may run directly."
                  % (m.group(1) + m.group(2)).strip().rstrip("'\""), file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
