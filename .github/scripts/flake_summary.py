#!/usr/bin/env python3
"""Turn the per-cell reports written by flake_report.py into PR-comment markdown.

The matrix runs the same suite across dozens of cells, so the useful unit is the
test, not the cell: one flaky test shows up as eight red cells, and eight
unrelated breakages also show up as eight red cells. Grouping by test tells
those apart.

For anything that looks flaky, this also prints the quarantine entry to paste
and what to do with it. The judgement -- is this really flaky, is it worth a
ticket -- stays with a person; the typing does not.
"""

import argparse
import datetime
import glob
import json
import os
import sys
from collections import OrderedDict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quarantine  # noqa: E402

DEFAULT_REVIEW_DAYS = quarantine.DEFAULT_REVIEW_DAYS


def load_reports(root_dir):
    reports = []
    for path in sorted(glob.glob(os.path.join(root_dir, "**", "*.json"), recursive=True)):
        try:
            with open(path) as handle:
                data = json.load(handle)
        except (OSError, ValueError):
            continue
        if isinstance(data, dict) and "cell" in data:
            reports.append(data)
    return reports


def group_by_test(reports, key):
    """OrderedDict of test id -> {cells, message, ticket}."""
    grouped = OrderedDict()
    for report in reports:
        for entry in report.get(key, []):
            slot = grouped.setdefault(entry["test"], {
                "cells": [],
                "message": entry.get("message", ""),
                "ticket": entry.get("ticket"),
            })
            slot["cells"].append(report["cell"])
    return grouped


def short_name(test_id):
    """com.datadoghq.profiler.FooTest.bar -> FooTest.bar"""
    parts = test_id.rsplit(".", 2)
    return ".".join(parts[-2:]) if len(parts) >= 2 else test_id


def render_table(grouped, cell_limit=4, row_limit=25, ticket_column=False):
    header = "| Test | Cells | " + ("Ticket | " if ticket_column else "") + "Message |"
    rule = "|------|-------|" + ("--------|" if ticket_column else "") + "---------|"
    lines = [header, rule]
    for test_id, info in list(grouped.items())[:row_limit]:
        cells = info["cells"]
        shown = ", ".join("`{}`".format(c) for c in cells[:cell_limit])
        if len(cells) > cell_limit:
            shown += " _+{} more_".format(len(cells) - cell_limit)
        message = (info["message"] or "").replace("|", "\\|")[:120]
        ticket = "{} | ".format(info.get("ticket") or "—") if ticket_column else ""
        lines.append("| `{}` | {} | {}{} |".format(short_name(test_id), shown, ticket, message))
    if len(grouped) > row_limit:
        lines.append("")
        lines.append("_...and {} more. See the job logs._".format(len(grouped) - row_limit))
    return lines


def cells_glob(cells):
    """A glob covering these cells, when they share an obvious axis.

    Suggesting `*arm64*` for something that only ever failed on arm64 is more
    useful than listing four cell names, and narrower than quarantining
    everywhere -- which would hide the same test breaking on x64 tomorrow.
    """
    for axis in ("arm64", "aarch64", "musl", "asan", "tsan"):
        if all(axis in c for c in cells):
            return ["*{}*".format(axis)]
    return None


def render_proposals(flaky):
    today = datetime.date.today()
    review_by = (today + datetime.timedelta(days=DEFAULT_REVIEW_DAYS)).isoformat()
    out = [
        "<details>",
        "<summary><b>Consider quarantining these — click for ready-made entries</b></summary>",
        "",
        "A quarantined test still runs and still reports; its failures just stop",
        "turning CI red. To quarantine one:",
        "",
        "1. Open a **PROF** ticket for the test, linking the failing job.",
        "2. Append the line below to `ddprof-test/quarantine.txt`, replacing",
        "   `PROF-XXXXX` with the ticket number.",
        "3. Check the `cells` and `reason` columns — the proposal only knows what",
        "   failed in this run, and a narrower `cells` glob keeps the same test",
        "   gating everywhere it has not misbehaved.",
        "",
        "CI fails once `review_by` passes, so an entry expires instead of piling up.",
        "",
        "```",
        "# test | ticket | added | review_by | cells | reason",
    ]
    for test_id, info in flaky.items():
        reason = "{} (seen in: {})".format(
            info["message"] or "intermittent failure",
            ", ".join(sorted(set(info["cells"]))[:4]),
        ).replace("|", "/")
        out.append(quarantine.format_entry(
            test_id,
            "PROF-XXXXX",
            today.isoformat(),
            review_by,
            cells_glob(info["cells"]) or [],
            reason,
        ))
    out.append("```")
    out.append("")
    out.append("</details>")
    out.append("")
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dir", required=True, help="directory of downloaded ci-outcome artifacts")
    args = parser.parse_args()

    reports = load_reports(args.dir)
    if not reports:
        return 0

    flaky = group_by_test(reports, "flaky")
    persistent = group_by_test(reports, "persistent")
    quarantined = group_by_test(reports, "quarantined")

    out = []
    if flaky:
        out.append("### :warning: Flaky tests — failed, then passed on retry")
        out.append("")
        out.extend(render_table(flaky))
        out.append("")
        out.append(
            "**These fail the build.** Passing on a second run makes a test flaky, "
            "not passing. Fix it, or quarantine it against a ticket so the debt is "
            "tracked rather than forgotten."
        )
        out.append("")
        out.extend(render_proposals(flaky))
    if persistent:
        out.append("### :x: Failing tests")
        out.append("")
        out.extend(render_table(persistent))
        out.append("")
    if quarantined:
        out.append("### :mute: Quarantined failures — not gating")
        out.append("")
        out.extend(render_table(quarantined, ticket_column=True))
        out.append("")

    retried = [r for r in reports if r.get("attempts", 1) > 1]
    if retried:
        out.append("_Retried {} of {} cells._".format(len(retried), len(reports)))
        out.append("")

    sys.stdout.write("\n".join(out))
    if out:
        sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
