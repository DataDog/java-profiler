#!/usr/bin/env python3
"""The quarantine list: which failing tests do not turn CI red.

Three jobs, one per subcommand:

  match     split a cell's failures into gating and quarantined
  validate  enforce the format, the ticket, and the review_by date
  propose   print an entry ready to paste for a test CI thinks is flaky

The list is a plain text table (see ddprof-test/quarantine.txt) rather than
JSON or YAML: it is edited by hand far more often than by machine, so real
comments, one-line diffs and clean `git blame` matter more than a schema. It
also has to parse inside the Alpine test containers, where PyYAML cannot be
assumed -- this needs nothing but str.split.
"""

import argparse
import datetime
import fnmatch
import json
import os
import re
import sys

DEFAULT_LIST = os.path.join("ddprof-test", "quarantine.txt")
TICKET_RE = re.compile(r"^PROF-\d+$")
DATE_RE = re.compile(r"^\d{4}-\d{2}-\d{2}$")
FIELDS = ("test", "ticket", "added", "review_by", "cells", "reason")
# Long enough not to be busywork, short enough that a quarantine outlives
# neither the release it was added in nor the memory of why.
DEFAULT_REVIEW_DAYS = 90


def parse(path):
    """([entry], [(line number, message)]) — entries and malformed lines.

    Each entry carries `_line` so validate() can point at the offender.
    """
    entries, errors = [], []
    if not os.path.exists(path):
        return entries, errors

    with open(path) as handle:
        for number, raw in enumerate(handle, start=1):
            line = raw.strip()
            if not line or line.startswith("#"):
                continue

            parts = [p.strip() for p in line.split("|")]
            if len(parts) != len(FIELDS):
                errors.append((number, "expected {} fields separated by '|', found {}".format(
                    len(FIELDS), len(parts))))
                continue

            entry = dict(zip(FIELDS, parts))
            entry["cells"] = [c.strip() for c in entry["cells"].split(",")
                              if c.strip() and c.strip() != "-"]
            entry["_line"] = number
            entries.append(entry)

    return entries, errors


def load(path):
    """Entries only, for callers that just need to match against the list."""
    return parse(path)[0]


def applies_to(entry, cell):
    """Does this entry cover the given cell? No globs means everywhere."""
    globs = entry.get("cells")
    if not globs:
        return True
    return any(fnmatch.fnmatch(cell, g) for g in globs)


def covers(entry, test_id):
    pattern = entry["test"]
    if pattern.endswith(".*"):
        return test_id.startswith(pattern[:-1])
    return test_id == pattern


def format_entry(test, ticket, added, review_by, cells, reason):
    return " | ".join([test, ticket, added, review_by, ",".join(cells) or "-", reason])


def cmd_match(args):
    entries = load(args.list)
    failures = [line.strip() for line in sys.stdin if line.strip()]

    gating, quarantined = [], []
    for test_id in failures:
        hit = next(
            (e for e in entries if covers(e, test_id) and applies_to(e, args.cell)),
            None,
        )
        (quarantined if hit else gating).append(test_id)

    json.dump({"gating": gating, "quarantined": quarantined}, sys.stdout)
    sys.stdout.write("\n")
    return 0


def cmd_validate(args):
    entries, problems = parse(args.list)
    today = datetime.date.today()
    seen = {}

    def complain(line, message):
        problems.append((line, message))

    for entry in entries:
        line = entry["_line"]
        name = entry["test"]

        for field in FIELDS:
            if field == "cells":
                continue  # optional, normalised to [] above
            if not entry[field]:
                complain(line, "field '{}' is empty".format(field))

        if name in seen:
            complain(line, "'{}' is already quarantined on line {}".format(name, seen[name]))
        seen[name] = line

        if entry["ticket"] and not TICKET_RE.match(entry["ticket"]):
            complain(line, "ticket '{}' is not a PROF-<number>".format(entry["ticket"]))

        for field in ("added", "review_by"):
            if entry[field] and not DATE_RE.match(entry[field]):
                complain(line, "{} '{}' is not YYYY-MM-DD".format(field, entry[field]))

        if DATE_RE.match(entry["review_by"]):
            due = datetime.date.fromisoformat(entry["review_by"])
            if due < today:
                complain(line, (
                    "'{}' has been quarantined since {} and its review was due {} "
                    "({} days ago). Fix the test and delete this line, or renew "
                    "review_by with a note on {}."
                ).format(name, entry["added"], entry["review_by"],
                         (today - due).days, entry["ticket"] or "the ticket"))

    for line, message in sorted(problems):
        print("::error file={},line={}::{}".format(args.list, line, message))

    if problems:
        print("\n{} problem(s) in {}".format(len(problems), args.list), file=sys.stderr)
        return 1

    print("{}: {} quarantined test(s), all valid".format(args.list, len(entries)))
    return 0


def cmd_propose(args):
    today = datetime.date.today()
    print(format_entry(
        args.test,
        "PROF-XXXXX",
        today.isoformat(),
        (today + datetime.timedelta(days=DEFAULT_REVIEW_DAYS)).isoformat(),
        args.cells or [],
        args.reason,
    ))
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--list", default=DEFAULT_LIST)
    sub = parser.add_subparsers(dest="command", required=True)

    match = sub.add_parser("match", help="split stdin's failed test ids by quarantine status")
    match.add_argument("--cell", required=True)
    match.set_defaults(func=cmd_match)

    validate = sub.add_parser("validate", help="check the list's format and review dates")
    validate.set_defaults(func=cmd_validate)

    propose = sub.add_parser("propose", help="print a paste-ready entry")
    propose.add_argument("--test", required=True)
    propose.add_argument("--reason", required=True)
    propose.add_argument("--cells", nargs="*")
    propose.set_defaults(func=cmd_propose)

    args = parser.parse_args()
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
