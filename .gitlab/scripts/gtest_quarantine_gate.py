#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc
"""Gate for the GitLab gtest jobs: apply the quarantine list to gtest results.

Mirrors flake_report.py's verdict philosophy for the simpler single-attempt
gtest runner:

  - any un-quarantined named failure gates, whether or not the binary's other
    tests passed;
  - every named failure quarantined is excused -- the point of the list -- but
    a binary that exited non-zero without naming any test (a crash, a harness
    error, truncated XML) still gates: with no named failure there is nothing
    the list can excuse, and an unreadable report must never read as a pass.

The XML reports are only ever needed to excuse a failure, never to pass a
run: a failing test makes gtest exit non-zero on its own, so a broken or
missing report degrades to rc-based gating (fail-closed), not to silent
green.
"""

import argparse
import glob
import os
import sys
import xml.etree.ElementTree as ET

sys.path.insert(0, os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..", "..", ".github", "scripts"))
import quarantine  # noqa: E402


def named_failures(xml_path):
    """{test id: message} from one gtest JUnit XML file, None when unreadable.

    Same id shape as flake_report.py's attempt_results(): classname.name,
    which is what quarantine covers() matches entries against. A missing file
    (a binary that died before gtest wrote anything) is as unreadable as a
    truncated one: neither is evidence any test passed.
    """
    try:
        tree = ET.parse(xml_path)
    except (ET.ParseError, OSError):
        return None
    failures = {}
    for case in tree.iter("testcase"):
        name = case.get("name")
        classname = case.get("classname")
        if not name or not classname:
            continue
        problem = case.find("failure")
        if problem is None:
            problem = case.find("error")
        if problem is None:
            continue
        message = (problem.get("message") or problem.get("type") or "").strip()
        failures["{}.{}".format(classname, name)] = (
            message.splitlines()[0][:200] if message else "failed")
    return failures


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--evidence", required=True,
                        help="run-gtests.sh's evidence dir (TEST-*.xml + rc/)")
    parser.add_argument("--cell", required=True,
                        help="quarantine cell, glibc-gtest-<config>-<arch>")
    parser.add_argument("--list", default=quarantine.DEFAULT_LIST)
    args = parser.parse_args()

    entries = quarantine.load(args.list)
    if not entries:
        print("::error::quarantine list '{}' is empty or missing; refusing to "
              "gate on nothing".format(args.list))
        return 1

    unquarantined = []
    excused = []
    for xml_path in sorted(glob.glob(os.path.join(args.evidence, "TEST-*.xml"))):
        binary = os.path.basename(xml_path)[len("TEST-"):-len(".xml")]
        failures = named_failures(xml_path)
        if failures is None:
            print("GATE: {} wrote no readable report; treating it as a "
                  "failure the list cannot excuse".format(binary))
            unquarantined.append((binary, "no readable report"))
            continue
        for test_id in sorted(failures):
            hit = quarantine.find_entry(entries, test_id, args.cell)
            if hit is None:
                unquarantined.append((binary, test_id))
            else:
                excused.append((binary, test_id, hit["ticket"]))

    for binary, test_id in unquarantined:
        print("GATE: {} gates: {} is not quarantined for cell {}".format(
            binary, test_id, args.cell))
    for binary, test_id, ticket in excused:
        print("GATE: {} excused by quarantine ({}): {}".format(
            binary, ticket, test_id))

    # A binary that exited non-zero without naming a test gates regardless of
    # the XML verdicts above: the list excuses named tests, not crashes.
    for rc_path in sorted(glob.glob(os.path.join(args.evidence, "rc", "*"))):
        binary = os.path.basename(rc_path)
        with open(rc_path) as handle:
            rc = handle.read().strip()
        if rc.isdigit() and int(rc) == 0:
            continue
        xml_path = os.path.join(args.evidence, "TEST-{}.xml".format(binary))
        failures = named_failures(xml_path)
        if not failures:
            print("GATE: {} exited {} without naming a failing test; the "
                  "quarantine list has nothing to excuse".format(binary, rc or "?"))
            unquarantined.append((binary, "exited {} with no named failure".format(rc or "?")))

    if unquarantined:
        print("GATE: {} un-quarantined failure(s) for cell {}".format(
            len(unquarantined), args.cell))
        return 1
    if excused:
        print("GATE: all {} failure(s) for cell {} are quarantined; job passes".format(
            len(excused), args.cell))
    else:
        print("GATE: no failures for cell {}".format(args.cell))
    return 0


if __name__ == "__main__":
    sys.exit(main())
