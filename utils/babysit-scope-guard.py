#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Babysit scope guard, invoked by .githooks/pre-push: when a running babysit-pr marker
in this worktree (build/babysit-pr-*.json, gitignored) matches the pushed branch, every
file in the outgoing delta must be inside the source/test allowlist AND inside the scope
the marker declares. Non-babysit pushes are never restricted: no matching running marker
means exit 0. A git failure or a matching marker without a scope array fails closed.

Accepted limit: the marker is worker-side bookkeeping, so a worker that rewrites it —
including corrupting it to unreadable JSON, which this guard skips with a warning — can
disable this check. The guard is defense-in-depth against accidental scope drift, not
against a malicious agent (which has shell access regardless); a stale marker (a dead
run) is likewise ignored after STALE_AFTER_S so it cannot gate a branch forever."""

import glob
import json
import os
import re
import subprocess
import sys
import time

# The fix universe: production source and tests. Everything else — skills, hooks, agent
# personas, CI, build system, docs — is banned by omission.
ALLOWLIST = re.compile(r"^(ddprof-lib/src/(main|test)/|ddprof-test/src/|ddprof-stresstest/src/)")
ZERO = set("0")


def git_out(*args):
    res = subprocess.run(["git", *args], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    return res.stdout.decode(errors="replace").strip() if res.returncode == 0 else None


def delta_files(local_sha, remote_sha):
    """Files changed by the push. Against the replaced remote tip: the babysit run's own
    commits, not the branch's whole PR diff. A branch creation (all-zero remote) falls
    back to the merge-base with origin/main."""
    base = remote_sha if set(remote_sha) != ZERO else git_out(
        "merge-base", "refs/remotes/origin/main", local_sha)
    if base is None:
        return None
    out = git_out("diff", "--name-only", base, local_sha)
    return None if out is None else [f for f in out.splitlines() if f]


# mtime is the marker's creation time (the file is never rewritten during a run), so
# the age-out must exceed the two-hour run cap by a wide margin to be safe for a long
# final push; a dead run must not gate its branch forever.
STALE_AFTER_S = 26 * 3600


def matching_marker(branch):
    """The running marker for this branch, or None. An unreadable or stale marker is
    skipped with a warning — an unrelated corrupt file must not block a human push,
    and the loop continues so a valid marker later in the glob order still gates.
    Old-format markers without a `branch` field cannot match (transition fail-open)."""
    for path in sorted(glob.glob("build/babysit-pr-*.json")):
        try:
            with open(path, errors="replace") as f:
                marker = json.load(f)
        except (OSError, ValueError) as err:
            print("pre-push: skipping unreadable babysit marker %s: %s" % (path, err),
                  file=sys.stderr)
            continue
        try:
            age = time.time() - os.path.getmtime(path)
        except OSError:
            age = 0
        if age > STALE_AFTER_S:
            print("pre-push: ignoring stale babysit marker %s (age %dh; a dead run must "
                  "not gate this branch forever)" % (path, age // 3600), file=sys.stderr)
            continue
        if not isinstance(marker, dict) or marker.get("status") != "running":
            continue
        if marker.get("branch") == branch:
            return marker
    return None


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--branch", required=True,
                        help="the push's local branch; markers name the babysat local branch")
    parser.add_argument("--local-sha", required=True)
    parser.add_argument("--remote-sha", required=True)
    args = parser.parse_args()

    marker = matching_marker(args.branch)
    if marker is None:
        return 0

    files = delta_files(args.local_sha, args.remote_sha)
    if files is None:
        print("pre-push: cannot compute the babysit push delta (git failed), refusing "
              "the push of %s" % args.branch, file=sys.stderr)
        return 1

    outside = [f for f in files if not ALLOWLIST.match(f)]
    if outside:
        print("pre-push: babysit push of %s changes files outside the source/test "
              "allowlist (skills, hooks, agents, CI, build system and docs are the "
              "parent session's, never the worker's): %s" % (args.branch, ", ".join(outside)),
              file=sys.stderr)
        return 1

    declared = marker.get("scope")
    if not isinstance(declared, list):
        print("pre-push: the running babysit marker for %s declares no scope array; "
              "the worker must declare the files its findings justify before editing"
              % args.branch, file=sys.stderr)
        return 1
    undeclared = [f for f in files if f not in declared]
    if undeclared:
        print("pre-push: babysit push of %s changes files the marker never declared: %s"
              % (args.branch, ", ".join(undeclared)), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
