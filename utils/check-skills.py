#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check that every agent skill under .agents/skills/ loads, and that AGENTS.md names only
existing skills.

Pi silently skips a SKILL.md with malformed frontmatter or without a description, so a
broken skill would otherwise go unnoticed. Rules, per tracked `.agents/skills/<dir>/`:
a SKILL.md with a leading `---` block; a single-line `name` equal to <dir>, made of
lowercase letters, digits and single hyphens, at most 64 characters; a non-empty
single-line `description` of at most 1024 characters. Block scalars (`>`, `|`) are
rejected because the line parser here cannot read them. `.claude/skills` must be the
symlink to `../.agents/skills` that Claude Code reads them through. Every "`<name>` skill"
mention in AGENTS.md must name a skill directory.

Exit codes: 0 clean, 1 violations, 2 environment error.
"""

import argparse
import os
import re
import subprocess
import sys

SKILLS = ".agents/skills/"
LINK, LINK_TARGET = ".claude/skills", "../.agents/skills"
NAME = re.compile(r"[a-z0-9]+(-[a-z0-9]+)*")
MAX_NAME, MAX_DESCRIPTION = 64, 1024
POINTER = re.compile(r"`([^`\s]+)` skill\b")


class EnvError(Exception):
    pass


def git(root, *args):
    res = subprocess.run(["git", "-C", root, *args], capture_output=True, text=True,
                         errors="surrogateescape")
    if res.returncode != 0:
        raise EnvError("git %s failed: %s" % (args[0], res.stderr.strip()))
    return res.stdout


def skill_dirs(root):
    """{dir name: tracked file names directly in it} for each tracked skill directory."""
    dirs = {}
    for path in git(root, "ls-files", "-z", "--", SKILLS).split("\0"):
        parts = path[len(SKILLS):].split("/") if path else []
        if len(parts) >= 2:
            dirs.setdefault(parts[0], set()).add(parts[1])
    return dirs


def frontmatter(text):
    """The leading `---` block's `key: value` lines, or None without a closed block."""
    lines = [l.rstrip() for l in text.splitlines()]
    if not lines or lines[0] != "---" or "---" not in lines[1:]:
        return None
    fields = {}
    for line in lines[1:lines.index("---", 1)]:
        if line and not line[0].isspace() and not line.startswith("#") and ":" in line:
            key, _, value = line.partition(":")
            value = value.strip()
            if len(value) >= 2 and value[0] == value[-1] and value[0] in "'\"":
                value = value[1:-1]
            fields[key.strip()] = value
    return fields


def skill_problems(root, name, files):
    path = SKILLS + name + "/SKILL.md"
    if "SKILL.md" not in files:
        return ["%s: missing" % path]
    try:
        with open(os.path.join(root, path), encoding="utf-8", errors="replace") as f:
            fm = frontmatter(f.read())
    except OSError as e:
        return ["%s: cannot read: %s" % (path, e.strerror)]
    if fm is None:
        return ["%s: no `---` frontmatter block" % path]
    found = []
    declared, description = fm.get("name", ""), fm.get("description", "")
    if declared in (">", "|", ">-", "|-") or description[:1] in (">", "|"):
        found.append("%s: use single-line values, not YAML block scalars" % path)
    elif not declared:
        found.append("%s: frontmatter 'name' is required" % path)
    elif declared != name:
        found.append("%s: name '%s' differs from its directory '%s'" % (path, declared, name))
    elif not NAME.fullmatch(declared) or len(declared) > MAX_NAME:
        found.append("%s: name '%s' must be lowercase letters, digits and single hyphens, "
                     "at most %d characters" % (path, declared, MAX_NAME))
    if not description:
        found.append("%s: frontmatter 'description' is required; without one the skill "
                     "never loads" % path)
    elif len(description) > MAX_DESCRIPTION:
        found.append("%s: description has %d characters, at most %d load"
                     % (path, len(description), MAX_DESCRIPTION))
    return found


def link_problems(root):
    entry = git(root, "ls-files", "-s", "--", LINK).split()
    if not entry or entry[0] != "120000":
        return ["%s: must be a tracked symlink to %s" % (LINK, LINK_TARGET)]
    target = git(root, "cat-file", "-p", entry[1])
    if target != LINK_TARGET:
        return ["%s: points to '%s', expected %s" % (LINK, target, LINK_TARGET)]
    return []


def pointer_problems(root, names):
    try:
        with open(os.path.join(root, "AGENTS.md"), encoding="utf-8", errors="replace") as f:
            text = f.read()
    except OSError as e:
        raise EnvError("cannot read AGENTS.md: %s" % e.strerror)
    missing = sorted({m for m in POINTER.findall(text) if m not in names})
    return ["AGENTS.md: names the `%s` skill, but %s%s/ does not exist" % (m, SKILLS, m)
            for m in missing]


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=None,
                    help="repository root (default: the checkout containing this script)")
    args = ap.parse_args(argv)
    root = args.root or os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    try:
        dirs = skill_dirs(root)
        errors = [e for name in sorted(dirs) for e in skill_problems(root, name, dirs[name])]
        errors += link_problems(root) + pointer_problems(root, dirs)
    except EnvError as e:
        print("error: %s" % e, file=sys.stderr)
        return 2
    for e in errors:
        print(e)
    print("skills: %s" % ("%d problem(s)" % len(errors) if errors else
                          "OK (%d skills)" % len(dirs)))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
