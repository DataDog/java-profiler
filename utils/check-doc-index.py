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
"""Check that every tracked doc/**/*.md is linked from doc/README.md and named in PascalCase.

doc/README.md itself is the only exception to both rules.

Exit codes: 0 clean, 1 violations, 2 environment error.
"""

import argparse
import os
import posixpath
import re
import subprocess
import sys

INDEX = "doc/README.md"
_LINK = re.compile(r"\]\(([^)\s]+)")
_PASCAL = re.compile(r"^[A-Z][A-Za-z0-9]*\.md$")


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    root = ap.parse_args(argv).root

    try:
        docs = subprocess.run(["git", "-C", root, "ls-files", "--", "doc/*.md", "doc/**/*.md"],
                              capture_output=True, text=True, check=True).stdout.splitlines()
        with open(os.path.join(root, INDEX), encoding="utf-8") as f:
            index = f.read()
    except (OSError, subprocess.CalledProcessError) as e:
        print("error: %s" % e, file=sys.stderr)
        return 2

    linked = set()
    for target in _LINK.findall(index):
        target = target.split("#", 1)[0]
        if target and "://" not in target:
            linked.add(posixpath.normpath(posixpath.join("doc", target)))

    errors = []
    for doc in sorted(set(docs) - {INDEX}):
        if doc not in linked:
            errors.append("%s: not linked from %s" % (doc, INDEX))
        if not _PASCAL.match(posixpath.basename(doc)):
            errors.append("%s: file name is not PascalCase (e.g. BuildSystemGuide.md)" % doc)
    for e in errors:
        print(e)
    print("doc index: %s" % ("%d problem(s)" % len(errors) if errors else "OK (%d docs)" % (len(docs) - 1)))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
