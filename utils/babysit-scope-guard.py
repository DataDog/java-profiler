#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Babysit scope guard, invoked by .githooks/pre-push: when a running babysit-pr marker
in this worktree (build/babysit-pr-*.json, gitignored) matches the pushed branch, every
file in the outgoing delta must be inside the source/test allowlist AND inside the scope
the marker declares. Non-babysit pushes are never restricted: no matching running marker
means exit 0. A matching marker that cannot be verified fails closed — the guard exists
because agent-made pushes need a machine-checked scope, not judgment."""

import glob
import json
import os
import re
import subprocess
import sys

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


def matching_marker(branch):
    """The running marker for this branch, or None. Old-format markers without a
    `branch` field cannot match and are not enforced (transition fail-open)."""
    for path in sorted(glob.glob("build/babysit-pr-*.json")):
        try:
            with open(path, errors="replace") as f:
                marker = json.load(f)
        except (OSError, ValueError) as err:
            return {"error": "cannot read %s: %s" % (path, err)}
        if not isinstance(marker, dict) or marker.get("status") != "running":
            continue
        if marker.get("branch") == branch:
            return marker
    return None


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--branch", required=True, help="the pushed remote branch")
    parser.add_argument("--local-sha", required=True)
    parser.add_argument("--remote-sha", required=True)
    args = parser.parse_args()

    marker = matching_marker(args.branch)
    if marker is None:
        return 0
    if "error" in marker:
        print("pre-push: babysit marker is unreadable, refusing the push: %s" % marker["error"],
              file=sys.stderr)
        return 1

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
