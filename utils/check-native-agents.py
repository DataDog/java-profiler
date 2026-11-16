#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check that the native-code instruction file reaches Claude Code and Pi from the same
directory list.

`.pi/native-agents.json` names the instruction file and the covered directories; the Pi
extension `.pi/extensions/native-agents.ts` reads it. Claude Code loads the file through a
`CLAUDE.md` stub in each covered directory. Rules, over the tracked files:
- the instruction file is tracked;
- each listed directory is listed once and has a tracked `CLAUDE.md` that holds only the
  line `@<path>`, where <path>, relative to the stub, resolves to the instruction file;
- every tracked `CLAUDE.md` below the repository root is in the list;
- the root `AGENTS.md` names the instruction file and every listed directory (its
  fallback line for sessions that load neither).

Exit codes: 0 clean, 1 violations, 2 environment error.
"""

import argparse
import json
import os
import posixpath
import subprocess
import sys

LIST = ".pi/native-agents.json"
STUB = "CLAUDE.md"


class EnvError(Exception):
    pass


def read(root, path):
    try:
        with open(os.path.join(root, path), encoding="utf-8") as f:
            return f.read()
    except (OSError, UnicodeDecodeError) as e:
        raise EnvError("cannot read %s: %s" % (path, e))


def load_list(root):
    try:
        data = json.loads(read(root, LIST))
    except ValueError as e:
        raise EnvError("%s: not valid JSON: %s" % (LIST, e))
    instructions, dirs = (data.get("instructions"), data.get("dirs")) if isinstance(data, dict) else (None, None)
    if not isinstance(instructions, str) or not isinstance(dirs, list) \
            or not all(isinstance(d, str) for d in dirs):
        raise EnvError('%s: expected {"instructions": <path>, "dirs": [<path>, ...]}' % LIST)
    return instructions, dirs


def check(root):
    instructions, dirs = load_list(root)
    res = subprocess.run(["git", "-C", root, "ls-files"], capture_output=True, text=True)
    if res.returncode != 0:
        raise EnvError("git ls-files failed: %s" % res.stderr.strip())
    tracked = set(res.stdout.splitlines())

    errors = []
    if instructions not in tracked:
        errors.append("%s: instruction file %s is not tracked" % (LIST, instructions))
    seen = set()
    for d in dirs:
        if d in seen:
            errors.append("%s: %s is listed twice" % (LIST, d))
        seen.add(d)
        stub = posixpath.join(d, STUB)
        if stub not in tracked:
            errors.append("%s: missing; it must hold only the line @<path to %s>" % (stub, instructions))
            continue
        try:
            lines = read(root, stub).splitlines()
        except EnvError as e:
            errors.append("%s: %s" % (stub, e))
            continue
        if len(lines) != 1 or not lines[0].startswith("@"):
            errors.append("%s: must hold only the line @<path to %s>" % (stub, instructions))
            continue
        target = posixpath.normpath(posixpath.join(d, lines[0][1:]))
        if target != instructions:
            errors.append("%s: imports %s, expected %s" % (stub, target, instructions))
    for stub in sorted(tracked):
        if posixpath.basename(stub) == STUB and stub != STUB and posixpath.dirname(stub) not in seen:
            errors.append("%s: not in %s, so Pi does not cover this directory" % (stub, LIST))
    agents = read(root, "AGENTS.md")
    for name in [instructions] + sorted(seen):
        if "`%s`" % name not in agents and "(%s)" % name not in agents:
            errors.append("AGENTS.md: does not name %s in its native-code line" % name)
    return errors


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    root = ap.parse_args(argv).root
    try:
        errors = check(root)
    except EnvError as e:
        print("error: %s" % e, file=sys.stderr)
        return 2
    for e in errors:
        print(e)
    print("native agents: %s" % ("%d problem(s)" % len(errors) if errors else "OK"))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
