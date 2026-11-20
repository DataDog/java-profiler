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

Flags the `throw`, `try` and `catch` keywords and the throwing std helpers
(`std::rethrow_exception`, `std::rethrow_if_nested`, `std::throw_with_nested`,
`__cxa_throw`, `__cxa_rethrow`, `__cxa_begin_catch`, `__cxa_end_catch`,
`__throw_*`) after blanking comments and string literals. An uncaught
exception crossing a JVMTI callback or a signal handler terminates the JVM,
and exception unwinding is incompatible with the allocation and signal
disciplines; see AGENTS.md ("C++ exceptions"). Known exceptions are listed
explicitly below; a listed site that disappears fails the check.

Known blanking limitations, both fail loud (a stray false positive, never a
silent miss): digit separators (`1'000'000ULL`) look like character literals
to the blanking regex, and raw string literals (R"(...)") are not parsed, so
their bodies are scanned as code.

Exit codes: 0 clean, 1 violations or stale exceptions, 2 environment error.
"""

import argparse
import os
import re
import subprocess
import sys

SRC = "ddprof-lib/src/main/cpp"
SOURCES = (".c", ".cc", ".cpp", ".h", ".hpp")

# Sanctioned exception sites, as (relative path, stripped source snippet).
# The snippet is the exact keyword-bearing text the check found; each entry
# exempts one occurrence, counted in order of appearance within the file.
# An entry whose snippet no longer appears fails the check. Keep this list
# empty: a new exception site needs an engineer-approved reason in AGENTS.md.
KNOWN_EXCEPTIONS = set()

_CALL = re.compile(
    r"\b(?:throw|try|catch|rethrow_exception|rethrow_if_nested|throw_with_nested"
    r"|__cxa_throw|__cxa_rethrow|__cxa_begin_catch|__cxa_end_catch|__throw_\w+)\b")
_COMMENT_OR_STRING = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def blank(m):
    # Keep offsets and line numbers; keep string quotes so code shape is intact.
    t = m.group(0)
    if t[0] in "\"'":
        return t[0] + " " * (len(t) - 2) + t[-1]
    return re.sub(r"[^\n]", " ", t)


def check_file(path, text):
    code = _COMMENT_OR_STRING.sub(blank, text)
    rel = path[len(SRC) + 1:]
    errors, exceptions = [], []
    for m in _CALL.finditer(code):
        line = code.count("\n", 0, m.start()) + 1
        snippet = re.sub(r"\s+", " ", m.group(0))
        key = (rel, snippet)
        if key in KNOWN_EXCEPTIONS:
            exceptions.append(key)
            continue
        errors.append("%s:%d: C++ exceptions are forbidden in native code (%s); "
                      "bugs are assert/abort, expected failures are error codes"
                      % (path, line, snippet))
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

    errors, seen, calls = [], set(), 0
    for path in files:
        try:
            with open(os.path.join(root, path), encoding="utf-8", errors="replace") as f:
                text = f.read()
        except OSError as e:
            print("error: %s" % e, file=sys.stderr)
            return 2
        code = _COMMENT_OR_STRING.sub(blank, text)
        calls += len(_CALL.findall(code))
        e, s = check_file(path, text)
        errors += e
        seen |= set(s)
    if not args.files:
        for rel, snippet in sorted(KNOWN_EXCEPTIONS - seen):
            errors.append("%s/%s: known exception %s no longer found; remove it from "
                          "KNOWN_EXCEPTIONS" % (SRC, rel, snippet))
    for e in errors:
        print(e)
    print("native exceptions: %s" % ("%d problem(s)" % len(errors) if errors
                                     else "OK (%d calls, %d known exception(s))" % (calls, len(seen))))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
