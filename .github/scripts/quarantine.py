#!/usr/bin/env python3
"""The quarantine list: which failing tests do not turn CI red.

Its `validate` subcommand enforces the format, the ticket, and the review_by
date. The gating decision itself (find_entry(), covers(), applies_to()) is a
library used in-process by flake_report.py -- there is no CLI for it, so the
rule CI actually runs cannot drift from a separate CLI wrapper.

The paste-ready entry a PR comment proposes for a flaky test is rendered by
flake_summary.py's own call to format_entry() below, not by this module's CLI.

The list is a plain text table (see ddprof-test/quarantine.txt) rather than
JSON or YAML: it is edited by hand far more often than by machine, so real
comments, one-line diffs and clean `git blame` matter more than a schema. It
also has to parse inside the Alpine test containers, where PyYAML cannot be
assumed -- this needs nothing but str.split.
"""

import argparse
import datetime
import fnmatch
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
# A review_by further out than this is not a review date, it is a way to write
# "never" without saying so. Padded above DEFAULT_REVIEW_DAYS since a proposal
# is dated `added` at the moment it is written, and review_by is measured from
# whenever the entry is actually appended -- which is not the same day.
MAX_REVIEW_DAYS = DEFAULT_REVIEW_DAYS + 30
# The `test` field is an exact test id, optionally ending in a class-wide
# ".*" -- that is all covers() understands. Anything else (a bare "*", a "?",
# or a wildcard anywhere but as the final two characters) passes validate()
# today and then silently quarantines nothing at runtime.
BAD_TEST_WILDCARD_RE = re.compile(r"[*?]")

# Cell names are <libc>-<jdk>-<config>-<arch>. Only libc and arch are a closed
# set -- jdk and config come from the workflow inputs and grow without warning
# -- so those two are the only axes worth checking a glob against.
KNOWN_ARCHES = ("amd64", "aarch64")
KNOWN_LIBCS = ("glibc", "musl")
# Anything that reads like an architecture. A glob naming one that CI never
# builds silently quarantines nothing, which is how "*arm64*" shipped in this
# file's own example: the arch is spelled aarch64.
ARCH_LIKE_RE = re.compile(r"(?:x86|x64|amd|arm|aarch|i386|ppc|s390)[\w_]*")

# A synthetic universe of cell names, used only to ask whether two entries'
# cell globs could both match the same real cell. Wide enough to catch a glob
# written against any axis (jdk, config, the libc/arch pair, or the slow/regular
# suite suffix) without having to enumerate the workflow's actual, ever-growing
# matrix. Deliberately over-inclusive (e.g. jdk variants like "8-j9" beyond the
# base list below): a synthetic cell that never occurs for real only makes
# overlap detection more conservative, never less.
_SYNTHETIC_JDKS = ("8", "8-graal", "11", "17", "17-graal", "21", "25")
_SYNTHETIC_CONFIGS = ("debug", "release", "asan", "tsan")
_SYNTHETIC_SUITE_SUFFIXES = ("", "-slow")
SYNTHETIC_CELLS = tuple(
    "{}-{}-{}-{}{}".format(libc, jdk, config, arch, suffix)
    for libc in KNOWN_LIBCS
    for jdk in _SYNTHETIC_JDKS
    for config in _SYNTHETIC_CONFIGS
    for arch in KNOWN_ARCHES
    for suffix in _SYNTHETIC_SUITE_SUFFIXES
)


def _matches_any_synthetic_cell(globs):
    return any(any(fnmatch.fnmatch(cell, g) for g in globs) for cell in SYNTHETIC_CELLS)


def cells_overlap(globs_a, globs_b):
    """Could some real cell match both sets of globs? No globs means every cell.

    Equal glob lists always overlap without needing the synthetic universe,
    which matters when a glob names an axis (like a jdk or config) that
    SYNTHETIC_CELLS does not model. And when a glob's axis is genuinely
    unmodelled -- it matches nothing in the synthetic universe at all -- this
    fails closed (treats it as overlapping) rather than open: a duplicate that
    cells_overlap cannot evaluate is exactly the case validate() must not wave
    through, since find_entry() would still only honour the first entry.
    """
    if not globs_a or not globs_b:
        return True
    if sorted(globs_a) == sorted(globs_b):
        return True
    if not _matches_any_synthetic_cell(globs_a) or not _matches_any_synthetic_cell(globs_b):
        return True
    return any(
        any(fnmatch.fnmatch(cell, g) for g in globs_a)
        and any(fnmatch.fnmatch(cell, g) for g in globs_b)
        for cell in SYNTHETIC_CELLS
    )


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


def find_entry(entries, test_id, cell):
    """The first entry quarantining this test on this cell, or None.

    Every caller that decides whether a failure gates goes through here, so the
    matching rule cannot drift between the subcommand and flake_report.py.
    """
    return next(
        (e for e in entries if covers(e, test_id) and applies_to(e, cell)),
        None,
    )


def format_entry(test, ticket, added, review_by, cells, reason):
    return " | ".join([test, ticket, added, review_by, ",".join(cells) or "-", reason])


def cmd_validate(args):
    # parse() tolerates a missing file so that matching still works before the
    # first entry lands. Validation must not: "0 quarantined test(s), all
    # valid" for a list that has been renamed or deleted would report success
    # at the exact moment gating silently stopped applying everywhere.
    if not os.path.exists(args.list):
        print("::error::quarantine list '{}' does not exist".format(args.list))
        return 1

    entries, problems = parse(args.list)
    today = datetime.date.today()
    seen_by_name = []

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

        # Two entries shadow each other on cells where they overlap when either
        # pattern covers() the other -- not just when the `test` strings are
        # identical. A trailing ".*" entry covers individual methods too, and
        # find_entry() only ever returns the first match, so the second
        # entry's ticket and review_by silently never take effect on the
        # cells the two share.
        for prior in seen_by_name:
            if not (covers(prior, entry["test"]) or covers(entry, prior["test"])):
                continue
            if cells_overlap(prior["cells"], entry["cells"]):
                where = ", ".join(entry["cells"]) or "every cell"
                complain(line, "'{}' is already quarantined (as '{}') for {} on line {}".format(
                    name, prior["test"], where, prior["_line"]))
                break
        seen_by_name.append(entry)

        if entry["ticket"] and not TICKET_RE.match(entry["ticket"]):
            complain(line, "ticket '{}' is not a PROF-<number>".format(entry["ticket"]))

        for field in ("added", "review_by"):
            if entry[field] and not DATE_RE.match(entry[field]):
                complain(line, "{} '{}' is not YYYY-MM-DD".format(field, entry[field]))

        if entry["test"] and BAD_TEST_WILDCARD_RE.search(
            entry["test"][:-2] if entry["test"].endswith(".*") else entry["test"]
        ):
            complain(line, (
                "test pattern '{}' has a wildcard outside a single trailing "
                "'.*'; covers() only understands an exact id or a class-wide "
                "'.*', so this would silently quarantine nothing"
            ).format(entry["test"]))

        if entry["added"] and DATE_RE.match(entry["added"]):
            try:
                datetime.date.fromisoformat(entry["added"])
            except ValueError:
                complain(line, "added '{}' is not a real calendar date".format(entry["added"]))

        for pattern in entry["cells"]:
            unknown_arch_tokens = [
                t for t in ARCH_LIKE_RE.findall(pattern) if t not in KNOWN_ARCHES
            ]
            # A token like "amd" or "aarch" (from "*amd*"/"*aarch*") is a
            # legitimate abbreviation of a real arch and matches real cells;
            # only complain when the glob, as actually evaluated by fnmatch,
            # matches nothing in the synthetic universe -- that is what
            # distinguishes a working glob from one like "*arm64*" that
            # genuinely names an architecture CI never builds.
            if unknown_arch_tokens and not _matches_any_synthetic_cell([pattern]):
                complain(line, (
                    "cell glob '{}' names architecture '{}', which CI never "
                    "builds (cells end in {}); it would quarantine nothing"
                ).format(pattern, unknown_arch_tokens[0], " or ".join(KNOWN_ARCHES)))
            head = pattern.split("-", 1)[0]
            if head and "*" not in head and "?" not in head and head not in KNOWN_LIBCS:
                complain(line, (
                    "cell glob '{}' starts with '{}'; cell names start with {}"
                ).format(pattern, head, " or ".join(KNOWN_LIBCS)))

        if DATE_RE.match(entry["review_by"]):
            try:
                due = datetime.date.fromisoformat(entry["review_by"])
            except ValueError:
                complain(line, "review_by '{}' is not a real calendar date".format(
                    entry["review_by"]))
            else:
                if due < today:
                    complain(line, (
                        "'{}' has been quarantined since {} and its review was due {} "
                        "({} days ago). Fix the test and delete this line, or renew "
                        "review_by with a note on {}."
                    ).format(name, entry["added"], entry["review_by"],
                             (today - due).days, entry["ticket"] or "the ticket"))
                elif due > today + datetime.timedelta(days=MAX_REVIEW_DAYS):
                    complain(line, (
                        "review_by '{}' is more than {} days out; that is not a "
                        "review date, it defeats the point of an expiring quarantine"
                    ).format(entry["review_by"], MAX_REVIEW_DAYS))

    for line, message in sorted(problems):
        print("::error file={},line={}::{}".format(args.list, line, message))

    if problems:
        print("\n{} problem(s) in {}".format(len(problems), args.list), file=sys.stderr)
        return 1

    print("{}: {} quarantined test(s), all valid".format(args.list, len(entries)))
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--list", default=DEFAULT_LIST)
    sub = parser.add_subparsers(dest="command", required=True)

    validate = sub.add_parser("validate", help="check the list's format and review dates")
    validate.set_defaults(func=cmd_validate)

    args = parser.parse_args()
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
