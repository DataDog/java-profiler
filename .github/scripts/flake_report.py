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
import re
import sys
import xml.etree.ElementTree as ET

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quarantine  # noqa: E402


def _attempt_number(path):
    return int(path.rsplit("-", 1)[1])


def _numbered_attempt_dirs(evidence_dir):
    """attempt-<n> directories, numeric suffixes only.

    A stray `attempt-tmp` left by a tool must not raise out of sorted() and
    take the whole classification -- and with it the job -- down with it.
    """
    found = []
    for path in glob.glob(os.path.join(evidence_dir, "attempt-*")):
        suffix = path.rsplit("-", 1)[1]
        if suffix.isdigit():
            found.append(path)
    return sorted(found, key=_attempt_number)


def attempt_results(root_dir):
    """(observed test ids, {failed test id: message}) from JUnit XML under root_dir.

    `observed` is every testcase the attempt recorded a result for, pass or
    fail. Knowing a test ran and passed is what distinguishes a flake from a
    test that simply never got reached on the retry.
    """
    observed = set()
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
            name = case.get("name")
            classname = case.get("classname")
            if not name or not classname:
                # A testcase element missing either half of its id cannot be
                # attributed to any real test; "Class." and ".method" are
                # equally unusable as a test id worth counting, tabling, or
                # proposing for quarantine.
                continue
            test_id = "{}.{}".format(classname, name)
            if case.find("skipped") is None:
                observed.add(test_id)
            problem = case.find("failure")
            if problem is None:
                problem = case.find("error")
            if problem is None:
                continue
            message = (problem.get("message") or problem.get("type") or "").strip()
            failures[test_id] = message.splitlines()[0][:200] if message else "failed"
    return observed, failures


def failed_tests(root_dir):
    """Just the failures, for callers that do not care what else ran."""
    return attempt_results(root_dir)[1]


def collect_attempts(evidence_dir):
    """[(attempt number, observed, failures)] ordered by attempt.

    An attempt that recorded no testcase at all is dropped: it tells us nothing
    about any individual test, and counting it would make every failure from
    the other attempts look as though it had passed somewhere.
    """
    attempts = []
    for path in _numbered_attempt_dirs(evidence_dir):
        observed, failures = attempt_results(path)
        if observed:
            attempts.append((_attempt_number(path), observed, failures))
    return attempts


def cmd_count(args):
    print(len(failed_tests(args.dir)))
    return 0


_NON_TEST_TASK_FAILURE_RE = re.compile(r"Execution failed for task '([^']+)'")


def non_test_task_failures(log_path, test_task_pattern):
    """Gradle task names blamed for a failure, other than the test task itself.

    Quarantine excuses the tests it names; it does not excuse the build. If
    this invocation's log also blames a compile, a native gtest, or a
    verification task, that failure has nothing to do with the list.
    """
    if not log_path or not os.path.isfile(log_path):
        return []
    found = set()
    with open(log_path, errors="replace") as handle:
        for line in handle:
            m = _NON_TEST_TASK_FAILURE_RE.search(line)
            if m and test_task_pattern not in m.group(1):
                found.add(m.group(1))
    return sorted(found)


def cmd_report(args):
    attempts = collect_attempts(args.evidence_dir)
    ran = len(attempts)
    entries = quarantine.load(args.list)

    results = []
    for test_id in sorted({t for _, _, f in attempts for t in f}):
        failed_in = [n for n, _, f in attempts if test_id in f]
        # Flaky means seen both ways: failed here, ran and passed there. A test
        # that is merely missing from the retry never re-ran -- an attempt that
        # aborted early, a filtered suite -- and claiming that as a pass would
        # hand out quarantine proposals for tests nobody has cleared.
        passed_in = [n for n, seen, f in attempts if test_id in seen and test_id not in f]
        hit = quarantine.find_entry(entries, test_id, args.cell)
        results.append({
            "test": test_id,
            "failed_attempts": failed_in,
            "message": next(f[test_id] for _, _, f in attempts if test_id in f),
            "flaky": bool(passed_in),
            "quarantined": hit is not None,
            "ticket": hit.get("ticket") if hit else None,
        })

    gating = [r for r in results if not r["quarantined"]]

    # The caller's exit-code decision must never be made from failures
    # aggregated across every attempt: those can all be quarantined while the
    # final attempt itself failed for a reason that named no test at all (a
    # docker or Gradle configuration failure, an OOM-killed daemon, an ASan
    # init abort). Report the final attempt's own standing separately so the
    # caller can require it to have actually produced test results, with every
    # one of its own named failures quarantined, before trusting the list.
    final = attempts[-1] if attempts else None
    final_attempt_ran = final is not None and final[0] == args.final_attempt
    final_attempt_gating_count = None
    final_attempt_failure_count = None
    if final_attempt_ran:
        _, _, final_failures = final
        final_attempt_failure_count = len(final_failures)
        final_attempt_gating_count = sum(
            1 for test_id in final_failures
            if quarantine.find_entry(entries, test_id, args.cell) is None
        )

    other_task_failures = non_test_task_failures(args.attempt_log, args.test_task_pattern)

    # The gating verdict, owned here rather than re-derived by the caller from
    # raw counts: three independent readers of this file re-deciding the same
    # thing is how a schema change turns into shotgun surgery.
    #
    #   any un-quarantined failure  -> gate, even if a retry passed. A flake
    #                                  nobody has quarantined is still a
    #                                  failure.
    #   every failure quarantined   -> excuse, but only when the *final*
    #                                  attempt itself ran and recorded results
    #                                  (final_attempt_ran), and every failure
    #                                  it did name is quarantined. A final
    #                                  attempt that crashed before recording a
    #                                  single testcase drops out of `attempts`
    #                                  entirely, so final_attempt_ran is False
    #                                  and it is never waved through just
    #                                  because an *earlier* attempt's failures
    #                                  all happen to be quarantined. A final
    #                                  attempt that ran and simply passed
    #                                  outright (zero failures of its own) is
    #                                  the ordinary flaky-then-fixed case and
    #                                  must not gate.
    #   final attempt exited        -> gate. It ran, recorded results, and
    #   non-zero having named          named no failure of its own, yet the
    #   no failure of its own          command still failed: the JVM aborted
    #                                  part-way through, so the tests it never
    #                                  reached are absent from the XML rather
    #                                  than passing. Gradle blames the crash on
    #                                  the test task itself, so the non-test
    #                                  task check above cannot see it.
    #   no failure named            -> no opinion; the caller keeps its own
    #                                  exit code (a compile error or a dead
    #                                  runner is nothing to do with
    #                                  quarantine).
    if args.evidence_suspect:
        gates = True
        gate_reason = (
            "flake evidence for this cell is suspect (the results directory "
            "could not be reliably cleared between attempts), so a prior "
            "attempt's results may be mistaken for the final attempt's own"
        )
    elif gating:
        gates = True
        gate_reason = "{} un-quarantined failure(s)".format(len(gating))
    elif results:
        if not final_attempt_ran or final_attempt_gating_count != 0:
            gates = True
            gate_reason = (
                "the final attempt did not itself pass with only quarantined "
                "failures (ran={}, its own named failures={}, its own "
                "unquarantined count={}); failures from an earlier attempt "
                "cannot be trusted instead"
            ).format(final_attempt_ran, final_attempt_failure_count, final_attempt_gating_count)
        elif other_task_failures:
            gates = True
            gate_reason = "all failing tests are quarantined, but the build also failed in {}".format(
                ", ".join(other_task_failures))
        elif args.final_attempt_exit_code not in (None, 0) and not final_attempt_failure_count:
            gates = True
            gate_reason = (
                "the final attempt named no failure of its own yet exited {}; "
                "the run was cut short rather than passing, so the tests missing "
                "from its results cannot be read as quarantined"
            ).format(args.final_attempt_exit_code)
        else:
            gates = False
            gate_reason = "all {} failing test(s) are quarantined".format(len(results))
    else:
        gates = None
        gate_reason = None

    report = {
        "cell": args.cell,
        "attempts": ran,
        "attempts_run": args.final_attempt,
        "flaky": [r for r in results if r["flaky"] and not r["quarantined"]],
        "persistent": [r for r in results if not r["flaky"] and not r["quarantined"]],
        "quarantined": [r for r in results if r["quarantined"]],
        "gating_count": len(gating),
        "failure_count": len(results),
        "final_attempt_ran": final_attempt_ran,
        "final_attempt_gating_count": final_attempt_gating_count,
        "final_attempt_failure_count": final_attempt_failure_count,
        "other_task_failures": other_task_failures,
        "final_attempt_exit_code": args.final_attempt_exit_code,
        "gates": gates,
        "gate_reason": gate_reason,
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
    report.add_argument("--final-attempt", required=True, type=int,
                         help="the attempt number the caller actually ran last")
    report.add_argument("--out", required=True)
    report.add_argument("--final-attempt-exit-code", default=None, type=int,
                         help="the exit status of the final attempt's command; a non-zero "
                              "status with no named failure of its own means the run was "
                              "cut short and must not be excused by the list")
    report.add_argument("--attempt-log", default=None,
                         help="the final attempt's raw log, to check for non-test task failures")
    report.add_argument("--test-task-pattern", default=":ddprof-test:test",
                         help="Gradle task name the quarantine list is entitled to excuse")
    report.add_argument("--evidence-suspect", action="store_true",
                         help="the caller could not reliably isolate this attempt's own "
                              "results (e.g. a stale results directory it could not clear); "
                              "never let the quarantine list excuse the exit code")
    report.set_defaults(func=cmd_report)

    args = parser.parse_args()
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
