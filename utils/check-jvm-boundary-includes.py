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
"""Check that shared native code reaches JVM implementations only through the boundary.

Shared files under ddprof-lib/src/main/cpp must not #include "hotspot/...",
"j9/..." or "zing/..." headers. Allowed: the implementation directories
themselves, the boundary files, and the known exceptions listed below.

Exit codes: 0 clean, 1 violations or stale exceptions, 2 environment error.
"""

import argparse
import os
import re
import subprocess
import sys

SRC = "ddprof-lib/src/main/cpp"
IMPLEMENTATION_DIRS = ("hotspot/", "j9/", "zing/")

# The abstraction files that dispatch on the detected VM.
BOUNDARY_FILES = {
    "jvmSupport.h", "jvmSupport.inline.h", "jvmSupport.cpp",
    "jvmThread.h", "jvmThread.cpp",
    "vmEntry.h", "vmEntry.cpp",
    "javaApi.cpp",
}

# MUST match doc/architecture/JvmSupportLayer.md#known-boundary-exceptions;
# update both together. New code should not add to this list.
KNOWN_EXCEPTIONS = {
    "profiler.cpp": {"hotspot/vmStructs.inline.h", "hotspot/hotspotSupport.h",
                     "j9/j9Support.h", "j9/j9WallClock.h"},
    "flightRecorder.cpp": {"hotspot/vmStructs.h"},
    "livenessTracker.cpp": {"hotspot/vmStructs.h", "hotspot/vmStructs.inline.h"},
    "sanityCheck.cpp": {"hotspot/vmStructs.h", "hotspot/vmStructs.inline.h"},
    "threadState.inline.h": {"hotspot/vmStructs.h"},
}

_INCLUDE = re.compile(r'^\s*#\s*include\s+"((?:hotspot|j9|zing)/[^"]+)"')


def tracked_files(root, path):
    try:
        out = subprocess.run(["git", "-C", root, "ls-files", "--", path],
                             capture_output=True, text=True, check=True).stdout
    except (OSError, subprocess.CalledProcessError) as e:
        print("error: git ls-files failed: %s" % e, file=sys.stderr)
        return None
    return out.splitlines()


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    root = ap.parse_args(argv).root

    files = tracked_files(root, SRC)
    if files is None:
        return 2
    errors, seen = [], set()
    for path in files:
        rel = path[len(SRC) + 1:]
        if rel.startswith(IMPLEMENTATION_DIRS) or rel in BOUNDARY_FILES:
            continue
        with open(os.path.join(root, path), encoding="utf-8", errors="replace") as f:
            for n, line in enumerate(f, 1):
                m = _INCLUDE.match(line)
                if not m:
                    continue
                header = m.group(1)
                if header in KNOWN_EXCEPTIONS.get(rel, ()):
                    seen.add((rel, header))
                else:
                    errors.append('%s:%d: shared code includes "%s"; call JVMSupport/JVMThread/VM instead '
                                  "(see doc/architecture/JvmSupportLayer.md)" % (path, n, header))
    for rel, headers in sorted(KNOWN_EXCEPTIONS.items()):
        for header in sorted(headers - {h for r, h in seen if r == rel}):
            errors.append('%s/%s: known exception "%s" is no longer included; remove it from '
                          "KNOWN_EXCEPTIONS and doc/architecture/JvmSupportLayer.md" % (SRC, rel, header))
    for e in errors:
        print(e)
    print("jvm boundary includes: %s" % ("%d problem(s)" % len(errors) if errors else "OK"))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
