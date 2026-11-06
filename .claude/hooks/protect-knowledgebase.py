#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse hook: block Edit/Write/NotebookEdit into .knowledgebase/, which
only the cairn skills write. The policy is utils/knowledgebase-write-policy.py."""

import json
import os
import subprocess
import sys

TRUSTED_REF = "refs/remotes/origin/main"  # qualified: a tag named origin/main must not win
# git_out and the trusted-ref loading are copied in require-fresh-review.py,
# require-gradle-wrapper.py and protect-knowledgebase.py; change all three together.
# Only this hook falls back to the checkout's policy: it guards accidents, not a branch.
POLICY = "utils/knowledgebase-write-policy.py"
PATH_FIELDS = ("file_path", "notebook_path")


def read(top, rel):
    try:
        with open(os.path.join(top, rel), encoding="utf-8") as f:
            return f.read()
    except (OSError, ValueError):  # ValueError: not UTF-8
        return None


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


def repo_relative(path, top):
    """`path` relative to checkout `top`. On a case-insensitive file system `path` may spell
    the checkout root in another case than git reports; compare case-blind then."""
    rel = os.path.relpath(path, top)
    if rel.startswith(os.pardir):
        folded = os.path.relpath(path.lower(), top.lower())
        if not folded.startswith(os.pardir):
            return folded
    return rel


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
        # The rule comes from origin/main, so a branch cannot change it; this hook itself runs
        # from the checkout under Claude Code's workspace trust. A stale fork as origin falls
        # back to the checkout's policy rather than allowing every write.
        source = git_out(["show", TRUSTED_REF + ":" + POLICY], top) or read(top, POLICY)
        if source is None:
            return 0  # neither has the policy yet
        # -I keeps the checkout root off sys.path, so planted stdlib-named files are not imported.
        res = subprocess.run([sys.executable, "-I", "-c", source], cwd=top,
                             input=repo_relative(candidate, top).encode(),
                             stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
        if res.returncode == 2:
            print(res.stderr.decode(errors="replace").strip(), file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
