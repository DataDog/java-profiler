#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Check that native sources under ddprof-lib/src/main/cpp never use C++ exceptions.

Flags the `throw`, `try` and `catch` keywords and the listed throwing std
helpers (`std::rethrow_exception`, `std::rethrow_if_nested`,
`std::throw_with_nested`, `__cxa_throw`, `__cxa_rethrow`, `__cxa_begin_catch`,
`__cxa_end_catch`, `__throw_*`) after blanking comments and string literals.
An uncaught exception crossing a JVMTI callback or a signal handler terminates
the JVM; see AGENTS.md ("C++ exceptions"). Known exceptions are listed
explicitly below; a listed site that disappears fails the check.

Blanking is heuristic. Raw string literals (R"delim(...)delim") are parsed and
their bodies blanked; character literals match only the single-character form,
so digit separators (1'000'000) stay code and cannot swallow a keyword between
them. An unbalanced quote or comment opener still blanks the rest of the file
and can hide keywords behind it — the same limitation as
check-sigsetjmp-shape.py.

Exit codes: 0 clean, 1 violations or stale exceptions, 2 environment error.
"""

import argparse
import os
import re
import subprocess
import sys

SRC = "ddprof-lib/src/main/cpp"
SOURCES = (".c", ".cc", ".cpp", ".h", ".hpp")

# Sanctioned exception sites, as (relative path, keyword, occurrence) where
# occurrence is the 1-based index of that exact keyword text within the file,
# counted in order of appearance. One entry exempts exactly one occurrence; a
# new occurrence inserted before it shifts the indexes and fails the check
# (the real site is flagged). An entry whose occurrence no longer exists fails
# as stale. Keep this list empty: a new exception site needs an
# engineer-approved reason in AGENTS.md.
KNOWN_EXCEPTIONS = set()

_CALL = re.compile(
    r"\b(?:throw|try|catch|rethrow_exception|rethrow_if_nested|throw_with_nested"
    r"|__cxa_throw|__cxa_rethrow|__cxa_begin_catch|__cxa_end_catch|__throw_\w+)\b")
_RAW_STRING = r'R"([^()\\\s]*)\(.*?\)\1"'
_COMMENT_OR_STRING = re.compile(
    r'//[^\n]*|/\*.*?\*/|' + _RAW_STRING + r'|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])\'', re.S)


def blank(m):
    # Keep offsets and line numbers; keep string quotes so code shape is intact.
    t = m.group(0)
    if t[0] in "\"'":
        return t[0] + " " * (len(t) - 2) + t[-1]
    return re.sub(r"[^\n]", " ", t)


def blank_comments_and_strings(text):
    return _COMMENT_OR_STRING.sub(blank, text)


def check_file(path, rel, code):
    errors, exceptions = [], []
    seen_counts = {}
    for m in _CALL.finditer(code):
        line = code.count("\n", 0, m.start()) + 1
        keyword = re.sub(r"\s+", " ", m.group(0))
        occurrence = seen_counts.get((rel, keyword), 0) + 1
        seen_counts[(rel, keyword)] = occurrence
        key = (rel, keyword, occurrence)
        if key in KNOWN_EXCEPTIONS:
            exceptions.append(key)
            continue
        errors.append("%s:%d: C++ exceptions are forbidden in native code (%s); "
                      "bugs are assert/abort, expected failures are error codes"
                      % (path, line, keyword))
    return errors, exceptions


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    ap.add_argument("files", nargs="*", help="check these files instead of the tracked sources")
    args = ap.parse_args(argv)
    root = args.root
    files = args.files
    if not files:
        try:
            files = subprocess.run(["git", "-C", root, "ls-files", "--", SRC],
                                   capture_output=True, text=True, check=True).stdout.splitlines()
            files = [f for f in files if f.endswith(SOURCES)]
        except (OSError, subprocess.CalledProcessError) as e:
            print("error: git ls-files failed: %s" % e, file=sys.stderr)
            return 2

    errors, seen, keywords = [], set(), 0
    for path in files:
        try:
            with open(os.path.join(root, path), encoding="utf-8", errors="replace") as f:
                text = f.read()
        except OSError as e:
            print("error: %s" % e, file=sys.stderr)
            return 2
        rel = path[len(SRC) + 1:] if path.startswith(SRC + os.sep) else path
        code = blank_comments_and_strings(text)
        keywords += len(_CALL.findall(code))
        e, s = check_file(path, rel, code)
        errors += e
        seen |= set(s)
    if not args.files:
        for rel, keyword, occurrence in sorted(KNOWN_EXCEPTIONS - seen):
            errors.append("%s/%s: known exception %s #%d no longer found; remove it from "
                          "KNOWN_EXCEPTIONS" % (SRC, rel, keyword, occurrence))
    for e in errors:
        print(e)
    print("native exceptions: %s" % ("%d problem(s)" % len(errors) if errors
                                     else "OK (%d keywords, %d known exception(s))" % (keywords, len(seen))))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
