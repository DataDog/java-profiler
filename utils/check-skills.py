#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check that every agent skill under .agents/skills/ loads, and that AGENTS.md names only
existing skills.

Pi silently skips a SKILL.md whose frontmatter does not parse as YAML or has no
description, so a broken skill would otherwise go unnoticed. Rules, per tracked
`.agents/skills/<dir>/`:
- SKILL.md starts with a `---` block;
- every line in the block is blank, a column-0 `#` comment, or `key: value` with a unique
  key, and every value is empty or a one-line string accepted by scalar(). This subset
  needs no YAML library and is stricter than YAML: it has no nested mappings, lists or
  multi-line values;
- `name` equals <dir> and uses lowercase letters, digits and single hyphens, at most 64
  characters; `description` is non-empty, at most 1024 characters.
`.claude/skills` must be the symlink to `../.agents/skills` that Claude Code reads the
skills through. Every "`<name>` skill" mention in AGENTS.md must name a skill directory.

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
KEY_LINE = re.compile(r"([A-Za-z][A-Za-z0-9_-]*):(?: (.*))?")
# YAML's printable non-ASCII range, minus U+2028/U+2029 (line breaks to some tools), the
# byte-order mark and U+FFFD (the decode-error replacement character).
TEXT = "\u00a0-\u2027\u202a-\ud7ff\ue000-\ufefe\uff00-\ufffc\U00010000-\U0010ffff"
PLAIN_PUNCTUATION = ".,;:()'\"/_+=?!#*&%@<>~^$`-"
PLAIN = re.compile("[A-Za-z%s][A-Za-z0-9 %s%s]*" % (TEXT, TEXT, re.escape(PLAIN_PUNCTUATION)))
PRINTABLE = re.compile("[\t\x20-\x7e%s]*" % TEXT)
TAB_AFTER_KEY = re.compile(r"[A-Za-z][A-Za-z0-9_-]*:\t")
DOUBLE_QUOTED = re.compile(r'"((?:[^"\\]|\\["\\])*)"(?:\s+#.*)?')
SINGLE_QUOTED = re.compile(r"'((?:[^']|'')*)'(?:\s+#.*)?")
NON_STRING_WORDS = {"null", "true", "false", "yes", "no", "on", "off", "y", "n"}


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


def scalar(raw):
    """(value, None) for a non-empty raw value in the accepted one-line string subset, else
    (None, reason). Accepted: a plain value that starts with a letter, uses only letters,
    digits, spaces, non-ASCII text and PLAIN_PUNCTUATION, has no `: `, ` #` or trailing
    `:` and is not a YAML null or boolean word; or a double-quoted string whose only
    escapes are \\" and \\\\, or a single-quoted string with '' doubling, either optionally
    followed by a comment."""
    if raw[:1] in ("|", ">"):
        return None, "block scalars are not supported; put the value on one line"
    double, single = DOUBLE_QUOTED.fullmatch(raw), SINGLE_QUOTED.fullmatch(raw)
    if double or single:
        value = (re.sub(r'\\(["\\])', r"\1", double.group(1)) if double
                 else single.group(1).replace("''", "'"))
        if not PRINTABLE.fullmatch(value):
            return None, "it contains a control or non-printable character"
        return value, None
    if raw[:1] in ("'", '"'):
        return None, ("the quoted string is unterminated, has an unescaped quote, or uses "
                      "an escape other than \\\" and \\\\")
    if not PLAIN.fullmatch(raw):
        return None, ("a plain value must start with a letter and contain only letters, "
                      "digits, spaces, non-ASCII text and %s; quote it" % PLAIN_PUNCTUATION)
    if ": " in raw or " #" in raw or raw.endswith(":"):
        return None, "it contains ': ' or ' #' or ends with ':', which YAML parses differently; quote it"
    if raw.lower() in NON_STRING_WORDS:
        return None, "YAML reads it as a null or boolean, not a string; quote it"
    return raw, None


def frontmatter(text):
    """(fields, problems) for the leading `---` block, or None without a closed block.

    fields maps each key to its decoded value, "" when empty, or None when the value was
    rejected; problems lists every line outside the accepted subset."""
    lines = [l.rstrip() for l in text.split("\n")]
    if not lines or lines[0] != "---" or "---" not in lines[1:]:
        return None
    fields, problems = {}, []
    for number, line in enumerate(lines[1:lines.index("---", 1)], start=2):
        if not line or line.startswith("#"):
            continue
        match = KEY_LINE.fullmatch(line)
        if not match and TAB_AFTER_KEY.match(line):
            problems.append("line %d: use a space, not a tab, after the colon" % number)
            continue
        if not match:
            problems.append("line %d: expected `key: value` at column 0; indented, list and "
                            "continuation lines are not supported" % number)
            continue
        key, raw = match.group(1), (match.group(2) or "").strip()
        if key in fields:
            problems.append("line %d: duplicate key '%s'" % (number, key))
        value, why = scalar(raw) if raw else ("", None)
        if why:
            problems.append("line %d: '%s' must be a one-line string: %s" % (number, key, why))
        fields[key] = value
    return fields, problems


def name_problems(path, directory, declared):
    if not declared:
        return ["%s: frontmatter 'name' is required" % path]
    if declared != directory:
        return ["%s: name '%s' differs from its directory '%s'" % (path, declared, directory)]
    if not NAME.fullmatch(declared) or len(declared) > MAX_NAME:
        return ["%s: name '%s' must be lowercase letters, digits and single hyphens, "
                "at most %d characters" % (path, declared, MAX_NAME)]
    return []


def description_problems(path, description):
    if not description:
        return ["%s: frontmatter 'description' is required; without one the skill never "
                "loads" % path]
    if len(description) > MAX_DESCRIPTION:
        return ["%s: description has %d characters, at most %d load"
                % (path, len(description), MAX_DESCRIPTION)]
    return []


def skill_problems(root, name, files):
    path = SKILLS + name + "/SKILL.md"
    if "SKILL.md" not in files:
        return ["%s: missing" % path]
    try:
        with open(os.path.join(root, path), encoding="utf-8") as f:
            parsed = frontmatter(f.read())
    except OSError as e:
        return ["%s: cannot read: %s" % (path, e.strerror)]
    except UnicodeDecodeError as e:
        return ["%s: not valid UTF-8 at byte %d" % (path, e.start)]
    if parsed is None:
        return ["%s: no `---` frontmatter block" % path]
    fields, problems = parsed
    found = ["%s: %s" % (path, p) for p in problems]
    # A None value was rejected by scalar() and is already in problems.
    declared, description = fields.get("name", ""), fields.get("description", "")
    if declared is not None:
        found += name_problems(path, name, declared)
    if description is not None:
        found += description_problems(path, description)
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
