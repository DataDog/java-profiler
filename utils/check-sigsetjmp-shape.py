#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc
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
"""Check that every crash-protection sigsetjmp() follows the JmpCtxScope pattern (guards.h).

For each sigsetjmp( / __sigsetjmp( call in tracked files under ddprof-lib/src/main/cpp:
  1. a JmpCtxScope is declared before it, in the same or an enclosing block;
  2. savemask is the literal 1;
  3. the landing pad `if (sigsetjmp(...) != 0) {` starts with
     SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP(); followed by <scope>.restore();

Exit codes: 0 clean, 1 violations or stale exceptions, 2 environment error.
"""

import argparse
import os
import re
import subprocess
import sys

SRC = "ddprof-lib/src/main/cpp"

# (file, first argument) of calls that are not crash protection.
# libraryPatcher_linux.cpp: glibc pthread cancellation buffer. glibc's unwinder
# siglongjmps here on pthread_exit/cancel (not checkFault() from segvHandler),
# so there is no signal-handler state to unwind and no signal mask to restore.
KNOWN_EXCEPTIONS = {
    ("libraryPatcher_linux.cpp", "(struct __jmp_buf_tag*)(void*)cancel_buf.__cancel_jmp_buf"),
}

_CALL = re.compile(r"\b(?:__)?sigsetjmp\s*\(")
_SCOPE = re.compile(r"\bJmpCtxScope\s+(\w+)\s*[({]")
_PAD = re.compile(r"\s*!=\s*0\s*\)\s*\{\s*SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP\s*\(\s*\)\s*;\s*(\w+)\s*\.\s*restore\s*\(\s*\)\s*;")
_COMMENT_OR_STRING = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def blank(m):
    # Keep offsets and line numbers; keep string quotes so code shape is intact.
    t = m.group(0)
    if t[0] in "\"'":
        return t[0] + " " * (len(t) - 2) + t[-1]
    return re.sub(r"[^\n]", " ", t)


def split_args(code, open_paren):
    """Top-level arguments of the call whose '(' is at open_paren; returns (args, end)."""
    depth, start, args = 0, open_paren + 1, []
    for i in range(open_paren, len(code)):
        c = code[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
            if depth == 0:
                args.append(code[start:i].strip())
                return args, i + 1
        elif c == "," and depth == 1:
            args.append(code[start:i].strip())
            start = i + 1
    return None, len(code)


def scope_in_effect(code, pos):
    """Name of the nearest JmpCtxScope declared before pos in the same or an enclosing block."""
    depth = 0
    visible = []  # code ranges at the call's block nesting
    end = pos
    for i in range(pos - 1, -1, -1):
        c = code[i]
        if c == "}":
            if depth == 0:
                visible.append((i + 1, end))
            depth += 1
        elif c == "{":
            if depth == 0:
                visible.append((i + 1, end))
                end = i
            else:
                depth -= 1
                if depth == 0:
                    end = i + 1
    if depth == 0:
        visible.append((0, end))
    for a, b in visible:
        names = _SCOPE.findall(code[a:b])
        if names:
            return names[-1]
    return None


def check_file(path, text):
    code = _COMMENT_OR_STRING.sub(blank, text)
    rel = path[len(SRC) + 1:]
    errors, exceptions = [], set()
    for m in _CALL.finditer(code):
        line = code.count("\n", 0, m.start()) + 1
        where = "%s:%d" % (path, line)
        args, end = split_args(code, m.end() - 1)
        if args is None or len(args) != 2:
            errors.append("%s: cannot parse the sigsetjmp() arguments" % where)
            continue
        first = " ".join(args[0].split())
        key = (rel, first)
        if key in KNOWN_EXCEPTIONS:
            exceptions.add(key)
            continue
        scope = scope_in_effect(code, m.start())
        if scope is None:
            errors.append("%s: no JmpCtxScope declared before sigsetjmp(%s, ...); see guards.h" % (where, first))
        if args[1] != "1":
            errors.append("%s: savemask is '%s', must be 1 (SIGSEGV stays blocked after siglongjmp otherwise)"
                          % (where, args[1]))
        pad = _PAD.match(code, end)
        if pad is None:
            errors.append("%s: landing pad must be `if (sigsetjmp(...) != 0) {` starting with "
                          "SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP(); then <scope>.restore();" % where)
        elif scope is not None and pad.group(1) != scope:
            errors.append("%s: landing pad restores '%s' but the JmpCtxScope in effect is '%s'"
                          % (where, pad.group(1), scope))
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
        calls += len(_CALL.findall(_COMMENT_OR_STRING.sub(blank, text)))
        e, s = check_file(path, text)
        errors += e
        seen |= s
    if not args.files:
        for rel, arg in sorted(KNOWN_EXCEPTIONS - seen):
            errors.append("%s/%s: known exception __sigsetjmp(%s, ...) no longer found; remove it from "
                          "KNOWN_EXCEPTIONS" % (SRC, rel, arg))
    for e in errors:
        print(e)
    print("sigsetjmp shape: %s" % ("%d problem(s)" % len(errors) if errors
                                   else "OK (%d calls, %d known exception(s))" % (calls, len(seen))))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
