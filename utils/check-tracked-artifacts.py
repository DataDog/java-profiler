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
"""Check that no session/tool artifacts are tracked by git.

Rejected paths: anything under docs/sphinx/ or a .sphinx/ directory, and any
path component matching *.scratch* (e.g. .scratch/, notes.scratch.md).

Exit codes: 0 clean, 1 violations, 2 environment error.
"""

import argparse
import fnmatch
import os
import subprocess
import sys


def reason(path):
    parts = path.split("/")
    for i, part in enumerate(parts):
        if part == "docs" and i + 1 < len(parts) - 1 and parts[i + 1] == "sphinx":
            return "docs/sphinx/ holds review-session artifacts"
        if part == ".sphinx" and i < len(parts) - 1:
            return ".sphinx/ holds review-session state"
        if fnmatch.fnmatchcase(part, "*.scratch*"):
            return "*.scratch* paths are local scratch files"
    return None


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    root = ap.parse_args(argv).root
    try:
        files = subprocess.run(["git", "-C", root, "ls-files"],
                               capture_output=True, text=True, check=True).stdout.splitlines()
    except (OSError, subprocess.CalledProcessError) as e:
        print("error: git ls-files failed: %s" % e, file=sys.stderr)
        return 2

    errors = ["%s: tracked artifact (%s); git rm it" % (f, r) for f in files for r in [reason(f)] if r]
    for e in errors:
        print(e)
    print("tracked artifacts: %s" % ("%d problem(s)" % len(errors) if errors else "OK"))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
