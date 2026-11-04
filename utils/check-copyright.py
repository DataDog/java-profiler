#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check copyright headers on the files a branch adds or modifies (AGENTS.md rule).

- An added source file carries a Datadog copyright line.
- A modified file with a Datadog copyright has an end year of at least its change year.
- A modified C/C++/Java/Kotlin file without any copyright line gets a Datadog one.

The change year is the year of the file's last commit, or the current year when it
has uncommitted changes, so a December change still passes when checked in January.
In a GitHub pull request the default base is the PR's base branch (GITHUB_BASE_REF),
so a backport into release/* is compared with that branch, not with main.

Exit codes: 0 clean, 1 violations, 2 environment error.
"""

import argparse
import datetime
import os
import re
import subprocess
import sys

SOURCE = (".c", ".cc", ".cpp", ".h", ".hpp", ".inc", ".java", ".kt", ".kts", ".groovy", ".py",
          ".sh", ".ts", ".js")
NEEDS_LINE_WHEN_MISSING = (".c", ".cc", ".cpp", ".h", ".hpp", ".inc", ".java", ".kt", ".kts")
EXCLUDED = ("utils/vendor/", "ddprof-lib/build/", ".gitlab/")
HEADER_LINES = 25
COPYRIGHT = re.compile(r"copyright", re.I)
DATADOG_LINE = re.compile(r"copyright\b(?P<years>.*?)\bdatadog", re.I)
YEAR = re.compile(r"\b(\d{4})\b")


class EnvError(Exception):
    pass


def git(root, *args):
    res = subprocess.run(["git", "-C", root, *args], capture_output=True, text=True)
    if res.returncode != 0:
        raise EnvError("git %s failed: %s" % (" ".join(args), res.stderr.strip()))
    return res.stdout


def changed_files(root, base):
    """(added, path) for files added, modified or renamed since the merge base."""
    ref = "refs/remotes/" + base if base.startswith("origin/") else base
    mb = git(root, "merge-base", ref, "HEAD").strip()
    # -z: NUL-separated and unquoted, so names with non-ASCII bytes or tabs stay intact.
    out = git(root, "diff", "--name-status", "-z", "-M", "--diff-filter=AMR", "--no-relative", mb)
    fields = iter(out.split("\0")[:-1])
    for status in fields:
        path = next(fields)
        if status.startswith("R"):  # a rename lists the old path, then the new one
            path = next(fields)
        yield status == "A", path


def change_year(root, path):
    if git(root, "status", "--porcelain", "--", path).strip():
        return datetime.date.today().year
    year = git(root, "log", "-1", "--format=%cd", "--date=format:%Y", "HEAD", "--", path).strip()
    return int(year) if year else datetime.date.today().year


def datadog_end_year(header):
    """Latest year on the Datadog copyright line; None without one, 9999 for 'Present'."""
    for line in header:
        m = DATADOG_LINE.search(line)
        if m:
            if "present" in m.group("years").lower():
                return 9999
            years = [int(y) for y in YEAR.findall(m.group("years"))]
            return max(years) if years else 0
    return None


def problem(root, added, path):
    if path.startswith(EXCLUDED):
        return None
    full = os.path.join(root, path)
    with open(full, errors="replace") as f:
        header = [next(f, "") for _ in range(HEADER_LINES)]
    # Extensionless scripts (git hooks, .claude/commands) count as source by their shebang.
    if not path.endswith(SOURCE) and (os.path.splitext(path)[1] or not header[0].startswith("#!")):
        return None
    end = datadog_end_year(header)
    if added and end is None:
        return "new file has no 'Copyright <year>, Datadog, Inc.' line"
    if end is None:
        if path.endswith(NEEDS_LINE_WHEN_MISSING) and not any(COPYRIGHT.search(l) for l in header):
            return "modified file has no copyright line; add 'Copyright <year>, Datadog, Inc.'"
        return None
    year = change_year(root, path)
    if end < year:
        return "Datadog copyright ends in %d; changed in %d, update the end year" % (end, year)
    return None


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    ap.add_argument("--base", help="base branch (default: origin/$GITHUB_BASE_REF in a pull "
                                   "request, else origin/main)")
    args = ap.parse_args(argv)
    args.base = args.base or "origin/" + (os.environ.get("GITHUB_BASE_REF") or "main")
    try:
        errors = ["%s: %s" % (path, p) for added, path in changed_files(args.root, args.base)
                  for p in [problem(args.root, added, path)] if p]
    except EnvError as e:
        print("error: %s" % e, file=sys.stderr)
        return 2
    for e in errors:
        print(e)
    print("copyright: %s" % ("%d problem(s)" % len(errors) if errors else "OK"))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
