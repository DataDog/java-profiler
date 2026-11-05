#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check that every tracked .knowledgebase/memories file carries cairn's memory frontmatter.

Only the cairn skills write .knowledgebase/ (`cairn memorize` validates the full memory
contract). An agent hook blocks file-tool edits there, but not shell writes; this check is
the backstop. It mirrors cairn's stable required subset, not the whole contract:
- the file is `<id>.md` and starts with a `---` frontmatter block;
- `id`, `title`, `kind`, `tags` and `source` are present and non-empty;
- `id` is a lowercase slug equal to the file name; `kind` is `finding` or `dead-end`.

Exit codes: 0 clean, 1 violations, 2 environment error.
"""

import argparse
import os
import re
import subprocess
import sys

MEMORIES = ".knowledgebase/memories/"
REQUIRED = ("id", "title", "kind", "tags", "source")
KINDS = ("finding", "dead-end")
SLUG = re.compile(r"[a-z0-9][a-z0-9-]*")
FIELD = re.compile(r"([A-Za-z_]+):(.*)")


class EnvError(Exception):
    pass


def tracked_memories(root):
    res = subprocess.run(["git", "-C", root, "ls-files", "-z", "--", MEMORIES],
                         capture_output=True, text=True, errors="surrogateescape")
    if res.returncode != 0:
        raise EnvError("git ls-files failed: %s" % res.stderr.strip())
    return [p for p in res.stdout.split("\0") if p]


def frontmatter(text):
    """Top-level `key: value` fields of the leading `---` block, or None without one."""
    lines = text.splitlines()
    if not lines or lines[0].strip() != "---":
        return None
    fields = {}
    for line in lines[1:]:
        if line.strip() == "---":
            return fields
        m = FIELD.match(line)
        if m:
            fields[m.group(1)] = m.group(2).strip()
    return None  # no closing marker


def problems(root, path):
    name = os.path.basename(path)
    if not name.endswith(".md"):
        return ["not a memory file (`<id>.md`)"]
    with open(os.path.join(root, path), errors="replace") as f:
        fm = frontmatter(f.read())
    if fm is None:
        return ["no `---` frontmatter block; write memories with `cairn memorize`"]
    found = ["frontmatter '%s' is required" % k for k in REQUIRED if not fm.get(k)]
    mid, kind = fm.get("id", ""), fm.get("kind", "")
    if mid and not SLUG.fullmatch(mid):
        found.append("id '%s' is not a lowercase slug" % mid)
    if mid and mid != name[:-3]:
        found.append("id '%s' does not match the file name" % mid)
    if kind and kind not in KINDS:
        found.append("kind '%s' is not one of %s" % (kind, ", ".join(KINDS)))
    return found


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=None,
                    help="repository root (default: the checkout containing this script)")
    args = ap.parse_args(argv)
    root = args.root or os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    try:
        paths = tracked_memories(root)
    except EnvError as e:
        print("error: %s" % e, file=sys.stderr)
        return 2
    errors = ["%s: %s" % (p, msg) for p in paths for msg in problems(root, p)]
    for e in errors:
        print(e)
    print("knowledgebase: %s" % ("%d problem(s)" % len(errors) if errors else
                                 "OK (%d memories)" % len(paths)))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
