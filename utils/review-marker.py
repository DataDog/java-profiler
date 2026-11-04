#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Record and validate the agentic-review marker of a branch (see utils/README.md).

Exit codes: 0 fresh or written, 1 missing or stale, 2 usage or environment error.
"""

import argparse
import datetime
import hashlib
import json
import os
import subprocess
import sys

DEFAULT_BASE = "origin/main"


class EnvError(Exception):
    pass


def git_bytes(*args, input_bytes=None):
    try:
        res = subprocess.run(["git", *args], input=input_bytes,
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                             check=True)
    except subprocess.CalledProcessError as e:
        raise EnvError("git %s failed: %s" % (" ".join(args),
                                              e.stderr.decode(errors="replace").strip()))
    return res.stdout


def git(*args, input_bytes=None):
    return git_bytes(*args, input_bytes=input_bytes).decode(errors="replace").strip()


def marker_path(branch):
    # The common dir is shared by all worktrees, so a marker written in one is visible to
    # a push or PR made from another. Hashed names cannot collide on case-insensitive disks.
    common = os.path.abspath(git("rev-parse", "--git-common-dir"))
    name = hashlib.sha256(branch.encode()).hexdigest()[:32]
    return os.path.join(common, "review-markers", name + ".json")


def current_branch():
    try:
        return git("symbolic-ref", "--quiet", "--short", "HEAD")
    except EnvError:
        raise EnvError("HEAD is detached; check out the branch under review")


def require_git_version():
    version = git("version").split()[2]
    parts = [int(p) for p in version.split(".")[:2] if p.isdigit()]
    if parts < [2, 39]:
        raise EnvError("git 2.39 or newer is required (patch-id --verbatim); found %s"
                       % version)


def resolve_commit(commit):
    try:
        return git("rev-parse", "--verify", "--quiet", commit + "^{commit}")
    except EnvError:
        raise EnvError("%s is not available locally; fetch or check it out first" % commit)


def change_digest(base, commit):
    # patch-id drops line numbers, so context lines are what anchor each hunk's position;
    # a base change next to a hunk therefore errs toward stale. --verbatim keeps whitespace.
    mb = git("merge-base", base, commit)
    diff = git_bytes("diff", "--no-relative", "--no-ext-diff", "--no-color", mb, commit)
    pid = git("patch-id", "--verbatim", input_bytes=diff)
    return pid.split()[0] if pid else "empty"


def cmd_write(args):
    branch = current_branch()
    if git("status", "--porcelain", "--untracked-files=no"):
        raise EnvError("uncommitted changes to tracked files: commit the reviewed "
                       "change set, then write the marker")
    base = args.base or DEFAULT_BASE
    state = {
        "branch": branch,
        "base": base,
        "head": git("rev-parse", "HEAD"),
        "digest": change_digest(base, "HEAD"),
        "tool": args.tool,
        "session": args.session or "",
        "date": datetime.datetime.now(datetime.timezone.utc)
                .strftime("%Y-%m-%dT%H:%M:%SZ"),
    }
    path = marker_path(branch)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        json.dump(state, f, indent=2)
        f.write("\n")
    print("review marker written for %s (tool=%s, base=%s)" % (branch, args.tool, base))
    return 0


def cmd_check(args):
    branch = args.branch or current_branch()
    path = marker_path(branch)
    try:
        with open(path) as f:
            marker = json.load(f)
    except FileNotFoundError:
        print("no review marker for branch %s" % branch, file=sys.stderr)
        return 1
    except ValueError:
        print("review marker for %s is not valid JSON (%s)" % (branch, path),
              file=sys.stderr)
        return 1
    if marker.get("branch") != branch:
        print("no review marker for branch %s" % branch, file=sys.stderr)
        return 1
    base = args.base or marker.get("base", DEFAULT_BASE)
    if marker.get("base") != base:
        print("review of %s covered base %s, not %s" % (branch, marker.get("base"), base),
              file=sys.stderr)
        return 1
    commit = resolve_commit(args.commit or "refs/heads/" + branch)
    if change_digest(base, commit) != marker.get("digest"):
        print("review marker for %s is stale: the commits changed since the %s review "
              "on %s" % (branch, marker.get("tool", "?"), marker.get("date", "?")),
              file=sys.stderr)
        return 1
    print("review marker for %s is fresh (%s review on %s, base %s)"
          % (branch, marker.get("tool", "?"), marker.get("date", "?"), base))
    return 0


SHIM_TAG = "# Installed by utils/review-marker.py install-hook"
HOOK_SHIM = "#!/bin/sh\n" + SHIM_TAG + """; runs the checkout's own hook.
hook="$(git rev-parse --show-toplevel)/.githooks/pre-push"
[ -x "$hook" ] || { cat >/dev/null; exit 0; }
exec "$hook" "$@"
"""


def cmd_install_hook(args):
    # A shim in the common dir, not core.hooksPath: a repo-local hooksPath would
    # replace a global one (Datadog's runs the secret scanner, then .git/hooks).
    path = os.path.join(os.path.abspath(git("rev-parse", "--git-common-dir")),
                        "hooks", "pre-push")
    if os.path.exists(path):
        with open(path, errors="replace") as f:
            current = f.read()
        if current == HOOK_SHIM:
            print("pre-push hook already installed (%s)" % path)
            return 0
        if SHIM_TAG not in current:  # an older shim of ours is upgraded in place
            raise EnvError("%s exists and is not this repo's shim; merge it by hand" % path)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        f.write(HOOK_SHIM)
    os.chmod(path, 0o755)
    print("pre-push hook installed (%s)" % path)
    try:
        hooks_path = git("config", "--get", "core.hooksPath")
    except EnvError:
        return 0  # unset: git runs the shim directly
    print("note: core.hooksPath is %s; the shim runs only if those hooks chain to "
          ".git/hooks (Datadog's global hooks do)" % hooks_path)
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = p.add_subparsers(dest="cmd", required=True)
    w = sub.add_parser("write", help="record a completed review of the current branch")
    w.add_argument("--tool", required=True)
    w.add_argument("--session")
    w.add_argument("--base")
    c = sub.add_parser("check", help="check a branch (default: current) against its marker")
    c.add_argument("--branch")
    c.add_argument("--commit", help="tip to check instead of the branch head")
    c.add_argument("--base")
    sub.add_parser("install-hook", help="install the pre-push shim into the common git dir")
    args = p.parse_args()
    try:
        if args.cmd == "install-hook":
            return cmd_install_hook(args)
        require_git_version()
        return cmd_write(args) if args.cmd == "write" else cmd_check(args)
    except EnvError as e:
        print("review-marker: %s" % e, file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
