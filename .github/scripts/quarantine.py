#!/usr/bin/env python3
"""The quarantine list: which failing tests do not turn CI red.

Its `validate` subcommand enforces the format, the ticket, the review_by
date, and -- for the GitLab gtest jobs -- that every bare-suite entry's id
matches a TEST(...) declaration in the gtest sources, so a mistyped or
stale mute fails the PR instead of quarantining nothing. The gating decision
itself (find_entry(), covers(), applies_to()) is a library used in-process by
flake_report.py -- there is no CLI for it, so the rule CI actually runs cannot
drift from a separate CLI wrapper.

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
#
# "el7" names the GitLab functional job's Oracle Linux 7 runtime, which is
# technically glibc but must not share the "glibc" token: that job runs a
# different environment (container, kernel, network stack) than the GitHub
# Actions "glibc" matrix (Ubuntu), and the two can fail the same test for
# unrelated reasons. Sharing a cell string would let an entry meant to excuse
# one silently excuse the other.
KNOWN_ARCHES = ("amd64", "aarch64")
KNOWN_LIBCS = ("glibc", "musl", "el7")
# Anything that reads like an architecture. A glob naming one that CI never
# builds silently quarantines nothing, which is how "*arm64*" shipped in this
# file's own example: the arch is spelled aarch64.
ARCH_LIKE_RE = re.compile(r"(?:x86|x64|amd|arm|aarch|i386|ppc|s390)[\w_]*")

# A synthetic universe of cell names, used only to ask whether two entries'
# cell globs could both match the same real cell. Wide enough to catch a glob
# written against any axis (jdk, config, the libc/arch pair, or the slow/regular
# suite suffix) without having to enumerate the workflow's actual, ever-growing
# matrix. Over-inclusive on purpose: a synthetic cell that never occurs for
# real only makes overlap detection more conservative, never less. Under-
# inclusive is the dangerous direction -- cells_overlap() fails closed for a
# glob matching nothing synthetic, so a JDK variant missing from here makes two
# genuinely disjoint entries look like duplicates and fail validation.
_SYNTHETIC_JDK_BASES = ("8", "11", "17", "21", "25")
_SYNTHETIC_JDK_SUFFIXES = ("", "-orcl", "-j9", "-ibm", "-graal")
_SYNTHETIC_JDKS = tuple(
    base + suffix
    for base in _SYNTHETIC_JDK_BASES
    for suffix in _SYNTHETIC_JDK_SUFFIXES
)
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

# The GitLab sanitizer gtest jobs run native binaries that never link a JDK,
# so their cells carry no jdk axis and no slow-suite suffix -- three tokens
# only (the quarantine.txt gtest section documents the shape). Without these
# in the universe, cells_overlap() fails closed for every gtest glob and two
# genuinely disjoint entries (asan vs tsan) read as duplicates.
SYNTHETIC_CELLS += tuple(
    "glibc-{}-{}".format(config, arch)
    for config in _SYNTHETIC_CONFIGS
    for arch in KNOWN_ARCHES
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


_INVOCATION_INDEX_RE = re.compile(r"^\[\d+\]$")


def normalise_test_id(test_id):
    """A JUnit XML test id reduced to the shape entries are written in.

    Gradle writes a JUnit 5 @Test method as `name="method()"`, so the id built
    from the report is `Class.method()`, while quarantine.txt documents -- and
    a human writes -- `Class.method`. Stripping the parentheses here, in the
    one function every caller's match goes through, keeps the documented shape
    matching the id JUnit actually produces while reports and annotations go
    on showing the real name.
    """
    return test_id[:-2] if test_id.endswith("()") else test_id


def covers(entry, test_id):
    pattern = entry["test"]
    test_id = normalise_test_id(test_id)
    if pattern.endswith(".*"):
        # "covers every method in the class", per quarantine.txt -- so the
        # remainder after the class name must be a single method segment. An
        # unbounded prefix match would make "com.datadoghq.profiler.*" suspend
        # the merge gate for the entire repository from one validate-clean
        # line.
        prefix = pattern[:-1]
        if test_id.startswith(prefix):
            # The remainder may carry a trailing "/0"-style suffix: Java
            # writes none, but gtest value-parameterized cases are named
            # "Case/0", and the Java rule's only real constraint is that the
            # remainder holds no further class/case separator dot.
            return "." not in test_id[len(prefix):]
        # GoogleTest bakes its suite decorations into the XML classname, not
        # into the entry: value-parameterized suites are "<inst>/<suite>"
        # (the "/0" lands on the case name), typed suites "<suite>/<typeidx>",
        # and combinations "<inst>/<suite>/<typeidx>". Reduce the classname to
        # its bare suite -- drop a trailing all-digits segment, then take the
        # last "/" segment -- and compare that. Java classnames never contain
        # "/", so this branch is unreachable for a Java id.
        cls, _, _ = test_id.rpartition(".")
        if not cls or "/" not in cls:
            return False
        segments = cls.split("/")
        if len(segments) > 1 and segments[-1].isdigit():
            segments.pop()
        if segments[-1] + "." == prefix:
            return True
        # A decorated entry ("MyInst/WobblySuite.*") also covers the typed
        # variants of its own instantiation ("MyInst/WobblySuite/0.case"):
        # the full undecorated classname must equal the prefix's suite too.
        return "/".join(segments) + "." == prefix
    return test_id == pattern


def _parse_date(s):
    """A YYYY-MM-DD string as a date, or raises ValueError.

    date.fromisoformat() needs Python 3.7+; this also has to run under
    Python 3.6 (EL7's base-repo python3).
    """
    return datetime.datetime.strptime(s, "%Y-%m-%d").date()


def is_expired(entry, today=None):
    """True once this entry's review_by date has passed.

    validate-quarantine (quarantine.py's own CLI) only runs from ci.yml, but
    find_entry() is called from every workflow that reuses run_tests_with_retry.sh
    (nightly.yml, release-validated.yml included). Enforcing expiry here, at
    match time, means a stale mute cannot keep quarantining a failure just
    because the workflow that hit it never runs the separate validator.
    """
    review_by = entry.get("review_by", "")
    if not DATE_RE.match(review_by):
        # Blank or not a date at all. parse() accepts both, and validate()
        # only runs in PR CI, so treating an unreadable expiry as "never
        # expires" would let the one entry nobody can review outlive every
        # entry that can be. An expiry that cannot be read has passed.
        return True
    try:
        due = _parse_date(review_by)
    except ValueError:
        return True
    return due < (today or datetime.date.today())


def find_entry(entries, test_id, cell):
    """The first entry quarantining this test on this cell, or None.

    Every caller that decides whether a failure gates goes through here, so the
    matching rule cannot drift between the subcommand and flake_report.py. An
    expired entry is treated as absent rather than as a hit, so it can never
    excuse a failure outside the PR CI that happens to run validate-quarantine.
    """
    return next(
        (e for e in entries
         if covers(e, test_id) and applies_to(e, cell) and not is_expired(e)),
        None,
    )


def format_entry(test, ticket, added, review_by, cells, reason):
    return " | ".join([test, ticket, added, review_by, ",".join(cells) or "-", reason])


def _declared_gtest_ids(src_dir):
    """({Suite.Case: kind}, {Suite}) from the gtest sources.

    A textual whole-file scan on purpose: validate() runs before any build,
    and the declarations sit behind platform #ifdefs (nativeThreadNameRace_ut
    is Linux-only) that a compile-time check cannot see. A false positive
    from a comment over-permits one id; a missed declaration would wrongly
    reject a real entry, so the scan errs towards finding MORE declarations,
    not fewer -- hence the whole-file scan (a TEST( wrapped across lines is
    still a declaration) and errors='replace' (a stray non-UTF-8 byte in a
    comment must not crash the validator).

    The kind records whether the case's report id carries instantiation
    decoration: TEST_P and TYPED_TEST cases report as
    '<inst>/<Suite>.<case>/<idx>' and '<Suite>/<idx>.<case>', while TEST and
    TEST_F cases report under the bare suite name.
    """
    decl_re = re.compile(
        r"\b(GTEST_TEST|TYPED_TEST_P|TYPED_TEST|TEST_P|TEST_F|TEST)\s*\(\s*"
        r"(\w+)\s*,\s*(\w+)\s*\)")
    ids, suites = {}, set()
    for dirpath, _, filenames in os.walk(src_dir):
        for filename in filenames:
            # .h/.hpp too: a fixture's case list can live in a shared header.
            # GTEST_TEST is the macro the others expand to; wrapper macros a
            # project defines on top of it stay invisible -- a false 'matches
            # no declaration' on one of those is the scan's known limit.
            if not filename.endswith((".cpp", ".cc", ".h", ".hpp")):
                continue
            with open(os.path.join(dirpath, filename),
                      encoding="utf-8", errors="replace") as handle:
                text = handle.read()
            for match in decl_re.finditer(text):
                ids["{}.{}".format(match.group(2), match.group(3))] = match.group(1)
                suites.add(match.group(2))
    return ids, suites


def _bare_gtest_suite(class_part):
    """A gtest classname reduced to its declared suite name.

    Mirrors covers(): value-parameterized suites are '<inst>/<Suite>' (a
    trailing all-digits segment is an instantiation index), typed suites
    '<Suite>/<typeidx>'. The declared name is the last non-index segment.
    """
    segments = class_part.split("/")
    if len(segments) > 1 and segments[-1].isdigit():
        segments.pop()
    return segments[-1]


def _gtest_decl_problems(entry, declared_ids, declared_suites):
    """Complaints for a gtest entry whose id no source file can produce.

    A Java id always carries a package, so the class part contains a dot; a
    bare gtest suite's does not. Java ids are out of scope here -- their
    lifecycle (rename, delete) is invisible to a C++ source scan.

    The check mirrors covers(), not wishes: an exact entry matches the report
    id verbatim, so a bare id for a value-parameterized suite (whose runtime
    id is '<inst>/<Suite>.<case>/<idx>') or any id carrying instantiation
    decoration can never fire -- only the class-wide '<Suite>.*' form
    survives covers()'s classname reduction for those.
    """
    test = entry["test"]
    class_wide = test.endswith(".*")
    stem = test[:-2] if class_wide else test
    cls, sep, case = stem.rpartition(".")
    if sep and "." in cls:
        return []  # Java-shaped: the class part carries a package
    if not sep:
        if not class_wide:
            return [
                "test '{}' has no case segment -- it is neither an exact id "
                "nor a class-wide '<Suite>.*', so it matches nothing".format(test)
            ]
        cls, case = stem, ""
    if not class_wide:
        # Only covers()'s class-wide path reduces a decorated classname; an
        # exact entry is compared verbatim and a report id always carries the
        # '/<idx>' suffix an entry cannot predict.
        if "/" in cls or "/" in case:
            return [
                "gtest id '{}' carries instantiation decoration, which an exact "
                "entry can never match -- quarantine the suite with '{}.*' "
                "instead".format(test, _bare_gtest_suite(cls) if "/" in cls else cls)
            ]
        if not case or _INVOCATION_INDEX_RE.match(case):
            return [
                "test '{}' has no case segment after the last dot -- it is "
                "neither an exact id nor a class-wide '<Suite>.*', so it "
                "matches nothing".format(test)
            ]
        kind = declared_ids.get("{}.{}".format(cls, case))
        if kind is None:
            return [
                "gtest id '{}' matches no TEST declaration in the gtest "
                "sources -- the mute would never fire; fix the id or delete "
                "the entry. If this is a Java id in the default package, "
                "spell its package explicitly".format(test)
            ]
        if kind != "TEST" and kind != "TEST_F":
            return [
                "gtest case '{}' is declared with {}: its report id carries "
                "instantiation decoration ('<inst>/<Suite>.<case>/<idx>' or "
                "'<Suite>/<idx>.<case>'), which the exact id '{}' never "
                "equals -- quarantine the suite with '{}.*' instead"
                .format("{}.{}".format(cls, case), kind, test, cls)
            ]
    elif "/" in cls:
        cls = _bare_gtest_suite(cls)
    if cls not in declared_suites:
        return [
            "gtest suite '{}' is declared in no gtest source -- the entry "
            "quarantines nothing; fix the suite name or delete the entry"
            .format(cls)
        ]
    return []


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

    # Where the gtest sources live: explicit --gtest-src wins; otherwise
    # derive the repo root from the list path (the list is <root>/ddprof-test/
    # quarantine.txt) and scan from there. A missing tree skips the check:
    # hermetic callers pass scratch lists with no source tree beside them, and
    # CI always runs validate from the repo root, where the tree exists.
    if args.gtest_src:
        gtest_src = args.gtest_src
    else:
        list_dir = os.path.dirname(os.path.abspath(args.list))
        gtest_src = os.path.join(os.path.dirname(list_dir), "ddprof-lib", "src", "test", "cpp")
    if os.path.isdir(gtest_src):
        declared_ids, declared_suites = _declared_gtest_ids(gtest_src)
    else:
        if not args.gtest_src:
            # Hermetic callers pass --gtest-src with a fixture and expect the
            # skip; the derived default vanishing under CI is a silent
            # no-op of the whole check and must be visible in the log.
            print("::warning::gtest sources not found at '{}'; skipping the "
                  "gtest declaration cross-check".format(gtest_src))
        declared_ids, declared_suites = None, None

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

        if declared_ids is not None:
            for message in _gtest_decl_problems(entry, declared_ids, declared_suites):
                complain(line, message)

        stem = entry["test"][:-2] if entry["test"].endswith(".*") else entry["test"]
        if entry["test"] and (not stem or BAD_TEST_WILDCARD_RE.search(stem)):
            complain(line, (
                "test pattern '{}' is not an exact id or a class-wide '<class>.*'; "
                "covers() understands nothing else, so this would silently "
                "quarantine nothing"
            ).format(entry["test"]))

        # "<package>.*" is not a class. covers() scopes a trailing '.*' to one
        # class's methods, so a package-level pattern quarantines nothing --
        # while looking like it quarantines a great deal.
        if entry["test"].endswith(".*") and stem:
            last = stem.rsplit(".", 1)[-1]
            if last and not last[:1].isupper():
                complain(line, (
                    "test pattern '{}' reads as a package, not a class: a "
                    "trailing '.*' covers the methods of one class, so this "
                    "matches nothing. Name the class, or list its tests"
                ).format(entry["test"]))

        if entry["test"].endswith("()"):
            complain(line, (
                "test '{}' carries the parentheses JUnit puts in its XML; "
                "entries are written as <class>.<method>, and covers() "
                "normalises the report's id to that shape -- drop the '()'"
            ).format(entry["test"]))

        # A decorated gtest suite name ("<inst>/<Suite>.*") in a class-wide
        # entry is valid and narrower than the bare-suite form: covers()
        # matches it directly against the decorated classname, muting only
        # that instantiation. No complaint - just do not claim it matches
        # nothing.

        if _INVOCATION_INDEX_RE.match(entry["test"].rsplit(".", 1)[-1]):
            complain(line, (
                "test '{}' names an invocation index. @ParameterizedTest and "
                "@RetryingTest invocations appear in the XML as '[1]', '[2]' "
                "with no method name at all, so the index identifies neither "
                "the method nor a stable case -- quarantine the class with "
                "'<class>.*' instead"
            ).format(entry["test"]))

        if entry["added"] and DATE_RE.match(entry["added"]):
            try:
                _parse_date(entry["added"])
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
                due = _parse_date(entry["review_by"])
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
    # required=True on add_subparsers() needs Python 3.7+; this also has to run
    # under Python 3.6 (EL7's base-repo python3), so the check is manual.
    sub = parser.add_subparsers(dest="command")

    validate = sub.add_parser("validate", help="check the list's format and review dates")
    validate.add_argument(
        "--gtest-src", metavar="DIR", default=None,
        help="gtest source tree to cross-check bare-suite ids against "
             "(default: ddprof-lib/src/test/cpp beside the list's repo root)")
    validate.set_defaults(func=cmd_validate)

    args = parser.parse_args()
    if args.command is None:
        parser.error("a command is required")
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
