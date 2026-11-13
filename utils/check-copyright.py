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
With --head the check reads that commit instead of the working tree (pre-push).

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
    # surrogateescape: a file name that is not valid UTF-8 must not abort the check.
    res = subprocess.run(["git", "-C", root, *args], capture_output=True, text=True,
                         errors="surrogateescape")
    if res.returncode != 0:
        raise EnvError("git %s failed: %s" % (" ".join(args), res.stderr.strip()))
    return res.stdout


def changed_files(root, base, head):
    """(added, path) for files added, modified or renamed since the merge base, up to
    commit `head`, or up to the working tree when head is None."""
    ref = "refs/remotes/" + base if base.startswith("origin/") else base
    mb = git(root, "merge-base", ref, head or "HEAD").strip()
    # -z: NUL-separated and unquoted, so names with non-ASCII bytes or tabs stay intact.
    out = git(root, "diff", "--name-status", "-z", "-M", "--diff-filter=AMR", "--no-relative", mb,
              *([head] if head else []))
    fields = iter(out.split("\0")[:-1])
    for status in fields:
        path = next(fields)
        if status.startswith("R"):  # a rename lists the old path, then the new one
            path = next(fields)
        yield status == "A", path


def change_year(root, path, head):
    if not head and git(root, "status", "--porcelain", "--", path).strip():
        return datetime.date.today().year
    year = git(root, "log", "-1", "--format=%cd", "--date=format:%Y", head or "HEAD", "--",
               path).strip()
    return int(year) if year else datetime.date.today().year


def header_lines(root, path, head):
    if head:
        return git(root, "show", "%s:%s" % (head, path)).splitlines()[:HEADER_LINES]
    with open(os.path.join(root, path), errors="replace") as f:
        return [line for _, line in zip(range(HEADER_LINES), f)]


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


def is_regular_file(root, path, head):
    """False for symlinks, directories and submodule entries, in commit `head` or the
    working tree."""
    if head:
        return git(root, "ls-tree", head, "--", path).split(" ", 1)[0] in ("100644", "100755")
    full = os.path.join(root, path)
    return not os.path.islink(full) and os.path.isfile(full)


def problem(root, added, path, head):
    # Only regular files with a code extension or none are read.
    if (path.startswith(EXCLUDED) or not path.endswith(SOURCE) and os.path.splitext(path)[1]
            or not is_regular_file(root, path, head)):
        return None
    header = header_lines(root, path, head)
    # Extensionless scripts (git hooks, .claude/commands) count as source by their shebang.
    if not path.endswith(SOURCE) and not (header and header[0].startswith("#!")):
        return None
    end = datadog_end_year(header)
    if added and end is None:
        return "new file has no 'Copyright <year>, Datadog, Inc.' line"
    if end is None:
        if path.endswith(NEEDS_LINE_WHEN_MISSING) and not any(COPYRIGHT.search(l) for l in header):
            return "modified file has no copyright line; add 'Copyright <year>, Datadog, Inc.'"
        return None
    year = change_year(root, path, head)
    if end < year:
        return "Datadog copyright ends in %d; changed in %d, update the end year" % (end, year)
    return None


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    # No eager __file__ default: the git hooks run this source with `python3 -I -c`.
    ap.add_argument("--root", help="repository root (default: the checkout containing this script)")
    ap.add_argument("--base", help="base branch (default: origin/$GITHUB_BASE_REF in a pull "
                                   "request, else origin/main)")
    ap.add_argument("--head", help="check this commit instead of the working tree (pre-push)")
    args = ap.parse_args(argv)
    sys.stdout.reconfigure(errors="backslashreplace")  # non-UTF-8 file names print escaped
    args.root = args.root or os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    args.base = args.base or "origin/" + (os.environ.get("GITHUB_BASE_REF") or "main")
    try:
        errors = ["%s: %s" % (path, p)
                  for added, path in changed_files(args.root, args.base, args.head)
                  for p in [problem(args.root, added, path, args.head)] if p]
    except EnvError as e:
        print("error: %s" % e, file=sys.stderr)
        return 2
    for e in errors:
        print(e)
    print("copyright: %s" % ("%d problem(s)" % len(errors) if errors else "OK"))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
