#!/usr/bin/env python3
"""Classify a cell's test failures and decide whether they should gate.

Two questions, answered separately:

  Is it flaky?    Failed on one attempt and passed on another. This is what the
                  retry exists to establish -- it does NOT excuse the failure.
  Does it gate?   Only the quarantine list answers that. A failure not on the
                  list turns the job red whether it is flaky or broken, which is
                  what keeps a flake from being quietly tolerated forever.

So a flaky test still fails CI until somebody quarantines it with a ticket. To
make that cheap, `report` prints a filled-in quarantine entry to paste.
"""

import argparse
import glob
import json
import os
import sys
import xml.etree.ElementTree as ET

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quarantine  # noqa: E402


def _attempt_number(path):
    return int(path.rsplit("-", 1)[1])


def failed_tests(root_dir):
    """Map of "class.test" -> first line of the failure message, for JUnit XML
    anywhere under root_dir."""
    failures = {}
    pattern = os.path.join(root_dir, "**", "TEST-*.xml")
    for path in glob.glob(pattern, recursive=True):
        try:
            tree = ET.parse(path)
        except ET.ParseError:
            # A JVM that died mid-suite leaves a truncated report. That is not
            # evidence the tests in it passed, but it is not attributable to a
            # named test either, so it is left to the exit code to report.
            continue
        for case in tree.iter("testcase"):
            problem = case.find("failure")
            if problem is None:
                problem = case.find("error")
            if problem is None:
                continue
            test_id = "{}.{}".format(case.get("classname") or "", case.get("name") or "")
            message = (problem.get("message") or problem.get("type") or "").strip()
            failures[test_id] = message.splitlines()[0][:200] if message else "failed"
    return failures


def collect_attempts(evidence_dir):
    """[(attempt number, failures)] ordered by attempt."""
    dirs = glob.glob(os.path.join(evidence_dir, "attempt-*"))
    return [(_attempt_number(d), failed_tests(d)) for d in sorted(dirs, key=_attempt_number)]


def cmd_count(args):
    print(len(failed_tests(args.dir)))
    return 0


def cmd_report(args):
    attempts = collect_attempts(args.evidence_dir)
    ran = len(attempts)
    entries = quarantine.load(args.list)

    results = []
    for test_id in sorted({t for _, f in attempts for t in f}):
        failed_in = [n for n, f in attempts if test_id in f]
        hit = next(
            (e for e in entries if quarantine.covers(e, test_id) and quarantine.applies_to(e, args.cell)),
            None,
        )
        results.append({
            "test": test_id,
            "failed_attempts": failed_in,
            "message": next(f[test_id] for _, f in attempts if test_id in f),
            # Passing on any attempt is what makes it flaky, so a test that
            # failed in fewer attempts than were run has passed at least once.
            "flaky": len(failed_in) < ran,
            "quarantined": hit is not None,
            "ticket": hit.get("ticket") if hit else None,
        })

    gating = [r for r in results if not r["quarantined"]]

    report = {
        "cell": args.cell,
        "attempts": ran,
        "status": args.final_status,
        "flaky": [r for r in results if r["flaky"] and not r["quarantined"]],
        "persistent": [r for r in results if not r["flaky"] and not r["quarantined"]],
        "quarantined": [r for r in results if r["quarantined"]],
        "gating_count": len(gating),
        "failure_count": len(results),
    }

    os.makedirs(os.path.dirname(args.out) or ".", exist_ok=True)
    with open(args.out, "w") as handle:
        json.dump(report, handle, indent=2)
        handle.write("\n")

    for entry in report["quarantined"]:
        print("::notice title=Quarantined test failed::{}: {} ({}) — not gating".format(
            args.cell, entry["test"], entry["ticket"]))

    for entry in report["flaky"]:
        attempts_desc = ", ".join(str(n) for n in entry["failed_attempts"])
        print("::error title=Flaky test::{}: {} failed on attempt {} and passed on retry. "
              "It is not quarantined, so it fails the build. See the PR comment for a "
              "quarantine entry to paste.".format(args.cell, entry["test"], attempts_desc))

    print("[flake-report] {}: {} flaky, {} persistent, {} quarantined; {} gating".format(
        args.cell, len(report["flaky"]), len(report["persistent"]),
        len(report["quarantined"]), report["gating_count"]), file=sys.stderr)
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--list", default=quarantine.DEFAULT_LIST)
    sub = parser.add_subparsers(dest="command", required=True)

    count = sub.add_parser("count", help="print the number of distinct failed tests")
    count.add_argument("--dir", required=True)
    count.set_defaults(func=cmd_count)

    report = sub.add_parser("report", help="classify failures and decide gating")
    report.add_argument("--cell", required=True)
    report.add_argument("--evidence-dir", required=True)
    report.add_argument("--final-status", required=True, choices=["pass", "fail"])
    report.add_argument("--out", required=True)
    report.set_defaults(func=cmd_report)

    args = parser.parse_args()
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
