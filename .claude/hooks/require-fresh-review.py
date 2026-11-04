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
TRUSTED_REF = "refs/remotes/origin/main"  # qualified: a tag named origin/main must not win
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


def repo_flag(tokens):
    """Value of -R/--repo in any of gh's spellings (`-R x`, `-Rx`, `--repo x`, `--repo=x`)."""
    for i, t in enumerate(tokens):
        if t in ("-R", "--repo"):
            return tokens[i + 1] if i + 1 < len(tokens) else None
        if t.startswith("--repo="):
            return t[len("--repo="):]
        if t.startswith("-R") and len(t) > 2:
            return t[2:]
    return None


def ready_target(args, repo, cwd):
    """Check arguments for the PR `gh pr ready` targets, from GitHub so the commits the
    PR holds are checked; [] means the current branch, None that it cannot be resolved."""
    selector = [a for i, a in enumerate(args)
                if not a.startswith("-") and (i == 0 or args[i - 1] not in ("-R", "--repo"))]
    out = gh_query(["pr", "view", *selector[:1], *(["-R", repo] if repo else []), "--json",
                    "headRefName,headRefOid,baseRefName", "-q",
                    '.headRefName + " " + .headRefOid + " " + .baseRefName'], cwd)
    if not out or len(out.split()) != 3:
        return None if selector else []
    head, oid, base = out.split()
    return ["--branch", head, "--commit", oid, "--base", origin(base)]


def run_check(source, cwd, extra):
    # -I keeps the checkout root off sys.path, so planted stdlib-named files are not imported.
    return subprocess.run([sys.executable, "-I", "-c", source, "check", *extra], cwd=cwd,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def configured_base(cwd):
    """`branch.<current>.gh-merge-base`, which bare `gh pr create` prefers to the repo default."""
    ref = git_out(["symbolic-ref", "--quiet", "HEAD"], cwd)
    if not ref:
        return None
    return git_out(["config", "--get", "branch.%s.gh-merge-base" % ref[len("refs/heads/"):]], cwd)


def evaluate(source, cwd, sub, args, command, match_text):
    """Return None to allow, else the reason to block."""
    if sub == "ready":
        # The repo flag may sit before `pr` (`gh -R o/r pr ready`), so read it from the whole match.
        extra = ready_target(args, repo_flag(words(match_text)), cwd)
        if extra is None:
            return "cannot resolve the PR's head commit (gh failed); retry when gh works."
    else:
        if HEAD_FLAG.search(command):
            return "--head names a branch other than the checkout's.\n" \
                   "Run `gh pr create` from that branch's worktree without --head."
        bases = {origin(m.group(2)) for m in BASE_FLAG.finditer(command)}
        if len(bases) > 1:
            return "the command names several bases (%s)." % ", ".join(sorted(bases))
        base = bases.pop() if bases else configured_base(cwd)
        extra = ["--base", origin(base)] if base else []
    res = run_check(source, cwd, extra)
    if res.returncode == 0 and sub == "create" and not extra:
        # Only a passing check pays for the default-branch lookup.
        default = gh_query(["repo", "view", "--json", "defaultBranchRef", "-q",
                            ".defaultBranchRef.name"], cwd)
        if default:
            res = run_check(source, cwd, ["--base", origin(default)])
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
    # origin/main's script, never the checkout's: the branch may be untrusted (a fork PR).
    source = git_out(["show", TRUSTED_REF + ":utils/review-marker.py"], top)
    if source is None:
        return 0  # the gate is not on the default branch yet
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
            reason = evaluate(source, top, sub, args, command, m.group(0))
        if reason:
            print("Blocked `gh pr %s`: %s" % (sub, reason), file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
