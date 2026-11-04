#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse hook: block commands that mention `gh pr create|new|ready`
while the branch's review marker is stale. Pushes are gated by .githooks/pre-push."""

import json
import os
import re
import shlex
import subprocess
import sys

# Matched on raw text, not parsed: subshells, `bash -c`, if/then and multi-line
# commands cannot hide it. The cost is a false block when the text is only quoted.
PR_CMD = re.compile(r"\bgh\b[^\n]*?\bpr\s+(create|new|ready)\b([^\n;&|)]*)")
# Anything that can point gh or git at another checkout than the payload cwd.
DIR_CHANGE = re.compile(r"(^|[\s;&|(){}])(cd|pushd|popd)(\s|$)|\bGIT_(DIR|WORK_TREE)="
                        r"|\benv\b[^\n;&|]*\s(-C|--chdir)\b", re.M)
# The hook runs before the command, so a git step that moves HEAD in the same command
# would be judged on the pre-command state.
GIT_STATE_CHANGE = re.compile(r"\bgit\b[^\n;&|]*?\s(commit|switch|checkout|rebase|reset|"
                              r"merge|cherry-pick|am|pull|revert|stash|restore)\b")
HEAD_FLAG = re.compile(r"(^|\s)(--head\b|-H)")
BASE_FLAG = re.compile(r"(?:^|\s)(?:--base[= ]\s*|-B\s*)(['\"]?)([^\s'\"]+)\1")


def git_out(args, cwd):
    res = subprocess.run(["git", *args], cwd=cwd, stdout=subprocess.PIPE,
                         stderr=subprocess.DEVNULL)
    return res.stdout.decode().strip() if res.returncode == 0 else None


def words(text):
    try:
        return shlex.split(text)
    except ValueError:
        return text.split()


def gh_query(args, cwd):
    """stdout of a gh query, or None when gh, network or auth fails."""
    try:
        res = subprocess.run(["gh", *args], cwd=cwd, stdout=subprocess.PIPE,
                             stderr=subprocess.DEVNULL, timeout=10)
    except (OSError, subprocess.TimeoutExpired):
        return None
    out = res.stdout.decode().strip()
    return out if res.returncode == 0 and out else None


def origin(name):
    return name if name.startswith("origin/") else "origin/" + name


def ready_target(args, cwd):
    """Check arguments for the PR `gh pr ready` targets, from GitHub so the commits the
    PR holds are checked; [] means the current branch, None that it cannot be resolved."""
    repo = next((args[i + 1] for i, a in enumerate(args[:-1]) if a in ("-R", "--repo")), None)
    selector = [a for i, a in enumerate(args)
                if not a.startswith("-") and (i == 0 or args[i - 1] not in ("-R", "--repo"))]
    out = gh_query(["pr", "view", *selector[:1], *(["-R", repo] if repo else []), "--json",
                    "headRefName,headRefOid,baseRefName", "-q",
                    '.headRefName + " " + .headRefOid + " " + .baseRefName'], cwd)
    if not out or len(out.split()) != 3:
        return None if selector else []
    head, oid, base = out.split()
    return ["--branch", head, "--commit", oid, "--base", origin(base)]


def run_check(script, cwd, extra):
    return subprocess.run([sys.executable, script, "check", *extra], cwd=cwd,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def evaluate(script, cwd, sub, args, command):
    """Return None to allow, else the reason to block."""
    if sub == "ready":
        extra = ready_target(args, cwd)
        if extra is None:
            return "cannot resolve the PR's head commit (gh failed); retry when gh works."
    else:
        if HEAD_FLAG.search(command):
            return "--head names a branch other than the checkout's.\n" \
                   "Run `gh pr create` from that branch's worktree without --head."
        bases = {origin(m.group(2)) for m in BASE_FLAG.finditer(command)}
        if len(bases) > 1:
            return "the command names several bases (%s)." % ", ".join(sorted(bases))
        extra = ["--base", bases.pop()] if bases else []
    res = run_check(script, cwd, extra)
    if res.returncode == 0 and sub == "create" and not extra:
        # Only a passing check pays for the default-branch lookup.
        default = gh_query(["repo", "view", "--json", "defaultBranchRef", "-q",
                            ".defaultBranchRef.name"], cwd)
        if default:
            res = run_check(script, cwd, ["--base", origin(default)])
    if res.returncode == 0:
        return None
    reason = res.stderr.decode(errors="replace").strip()
    if res.returncode == 1:
        return "%s\nRun the pre-pr-review skill, then retry." % reason
    return "cannot check the review marker: %s\nRerunning the review will not help." % reason


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    # Join backslash-continued lines so `gh pr \<newline> create` is one line to the regexes.
    command = payload.get("tool_input", {}).get("command", "").replace("\\\n", " ")
    matches = list(PR_CMD.finditer(command))
    if not matches:
        return 0
    project = os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd()
    top = git_out(["rev-parse", "--show-toplevel"], payload.get("cwd") or os.getcwd())
    common = top and git_out(["rev-parse", "--path-format=absolute", "--git-common-dir"], top)
    if not common or common != git_out(["rev-parse", "--path-format=absolute",
                                        "--git-common-dir"], project):
        return 0  # another repository, or not a git checkout: not this repo's policy
    # Prefer the checkout's own script: the session's checkout may be on an older branch.
    script = next((s for s in (os.path.join(top, "utils", "review-marker.py"),
                               os.path.join(project, "utils", "review-marker.py"))
                   if os.path.exists(s)), None)
    if script is None:
        return 0
    for m in matches:
        sub = "create" if m.group(1) == "new" else m.group(1)
        args = words(m.group(2))
        if sub == "ready" and "--undo" in args:
            continue
        if DIR_CHANGE.search(command):
            reason = "the command may act on another checkout (cd, pushd, env -C or " \
                     "GIT_DIR).\nRun `gh pr %s` from the branch's worktree without it." % sub
        elif GIT_STATE_CHANGE.search(command):
            reason = "the command also changes git state (commit, switch, rebase, ...), " \
                     "which the check cannot see beforehand.\nRun `gh pr %s` as its own " \
                     "command." % sub
        else:
            reason = evaluate(script, top, sub, args, command)
        if reason:
            print("Blocked `gh pr %s`: %s" % (sub, reason), file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
