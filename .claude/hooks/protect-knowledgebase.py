#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse hook: block Edit/Write/NotebookEdit into .knowledgebase/, which
only the cairn skills write. The policy is utils/knowledgebase-write-policy.py."""

import json
import os
import subprocess
import sys

TRUSTED_REF = "refs/remotes/origin/main"  # qualified: a tag named origin/main must not win
# git_out and the trusted-ref loading mirror require-gradle-wrapper.py; change both together.
PATH_FIELDS = ("file_path", "notebook_path")


def git_out(args, cwd):
    res = subprocess.run(["git", *args], cwd=cwd, stdout=subprocess.PIPE,
                         stderr=subprocess.DEVNULL)
    return res.stdout.decode().strip() if res.returncode == 0 else None


def common_dir(path):
    return git_out(["rev-parse", "--path-format=absolute", "--git-common-dir"], path)


def checkout_of(path):
    """Top level of the checkout holding `path`, which need not exist yet."""
    d = path
    while not os.path.isdir(d):
        parent = os.path.dirname(d)
        if parent == d:
            return None
        d = parent
    return git_out(["rev-parse", "--show-toplevel"], d)


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    tool_input = payload.get("tool_input") or {}
    target = next((tool_input[f] for f in PATH_FIELDS if isinstance(tool_input.get(f), str)), "")
    if not target:
        return 0
    path = os.path.join(payload.get("cwd") or os.getcwd(), os.path.expanduser(target))
    # The literal path and the one behind any symlink: either may lead into .knowledgebase/.
    candidates = {os.path.normpath(path), os.path.realpath(path)}
    # Case-blind: on macOS's default file system `.KnowledgeBase/` is the same directory.
    if not any(".knowledgebase" in c.lower() for c in candidates):
        return 0  # most writes: skip the git calls below
    project = common_dir(os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd())
    for candidate in sorted(candidates):
        top = checkout_of(candidate)
        if not top or common_dir(top) != project:
            continue  # another repository, or not a git checkout: not this repo's policy
        # origin/main's policy, never the checkout's: the branch may be untrusted (a fork PR).
        source = git_out(["show", TRUSTED_REF + ":utils/knowledgebase-write-policy.py"], top)
        if source is None:
            return 0  # the policy is not on the default branch yet
        # -I keeps the checkout root off sys.path, so planted stdlib-named files are not imported.
        res = subprocess.run([sys.executable, "-I", "-c", source], cwd=top,
                             input=os.path.relpath(candidate, top).encode(),
                             stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
        if res.returncode == 2:
            print(res.stderr.decode(errors="replace").strip(), file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
