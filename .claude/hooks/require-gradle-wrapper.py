#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse hook: block commands that run gradlew directly instead of
through .claude/commands/build-and-summarize. The policy is utils/gradle-command-policy.py."""

import json
import os
import subprocess
import sys

TRUSTED_REF = "refs/remotes/origin/main"  # qualified: a tag named origin/main must not win
# git_out and the trusted-ref loading mirror require-fresh-review.py; change both together.


def git_out(args, cwd):
    res = subprocess.run(["git", *args], cwd=cwd, stdout=subprocess.PIPE,
                         stderr=subprocess.DEVNULL)
    return res.stdout.decode().strip() if res.returncode == 0 else None


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    command = payload.get("tool_input", {}).get("command", "")
    if "gradlew" not in command:
        return 0  # most commands: skip the git calls below
    project = os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd()
    top = git_out(["rev-parse", "--show-toplevel"], payload.get("cwd") or os.getcwd())
    common = top and git_out(["rev-parse", "--path-format=absolute", "--git-common-dir"], top)
    if not common or common != git_out(["rev-parse", "--path-format=absolute",
                                        "--git-common-dir"], project):
        return 0  # another repository, or not a git checkout: not this repo's policy
    # origin/main's policy, never the checkout's: the branch may be untrusted (a fork PR).
    source = git_out(["show", TRUSTED_REF + ":utils/gradle-command-policy.py"], top)
    if source is None:
        return 0  # the policy is not on the default branch yet
    # -I keeps the checkout root off sys.path, so planted stdlib-named files are not imported.
    res = subprocess.run([sys.executable, "-I", "-c", source], cwd=top, input=command.encode(),
                         stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    if res.returncode != 2:
        return 0
    print(res.stderr.decode(errors="replace").strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main())
