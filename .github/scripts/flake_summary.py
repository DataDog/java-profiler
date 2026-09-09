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
import re
import sys
from collections import OrderedDict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quarantine  # noqa: E402

DEFAULT_REVIEW_DAYS = quarantine.DEFAULT_REVIEW_DAYS

# Test ids and failure messages come from the PR's own test code, not from
# anything CI controls, and this comment is rendered as markdown and offered
# up as a ready-to-paste quarantine entry. Neither may carry markdown, HTML, or
# a fence-breaking ``` sequence into that render.
_SAFE_TEST_ID_RE = re.compile(r"[^A-Za-z0-9_.$-]")

# The one place a failure message is truncated for display. flake_report.py
# stores messages at a wider cap (200 chars) for anyone reading the raw JSON;
# every renderer of this data (this module's tables, generate-test-summary.sh's
# per-job table) uses this same, narrower display width so the same failure
# does not render at two different lengths in one PR comment.
MESSAGE_DISPLAY_WIDTH = 120


def sanitize_test_id(test_id):
    return _SAFE_TEST_ID_RE.sub("_", test_id)


def sanitize_quarantine_test_pattern(test_id):
    """Sanitize a test id for the *paste-ready quarantine entry*, not display.

    sanitize_test_id() is safe for markdown but rewrites JUnit's parameterized-
    and dynamic-test punctuation (brackets, parens, commas) to '_', producing a
    pattern quarantine.covers() (exact string equality, or a trailing '.*')
    can never match against the real id. When the method name would need that
    rewriting to render safely, fall back to the class-wide '.*' pattern
    instead, which is still an exact, matchable pattern and rendering-safe as
    is (it contains no character _SAFE_TEST_ID_RE would touch).
    """
    if not _SAFE_TEST_ID_RE.search(test_id):
        return test_id
    classname = test_id.rsplit(".", 1)[0]
    if classname and not _SAFE_TEST_ID_RE.search(classname):
        return classname + ".*"
    return sanitize_test_id(test_id)


def sanitize_inline(text):
    """Strip newlines and backticks so text can't break a table row, a code
    span, or the ``` fence around the quarantine proposals."""
    return text.replace("`", "'").replace("\n", " ").replace("\r", " ")


def load_reports(root_dir):
    """(reports, files found, files skipped).

    Skipped covers anything that looked like a report but wasn't usable: JSON
    that failed to parse, or parsed into something that isn't a report at all.
    Distinguishing "found nothing" from "found reports, all clean" from "found
    reports, some unreadable" is the point -- a total artifact-download failure
    must not render the same as a spotless run.
    """
    reports = []
    skipped = 0
    paths = sorted(glob.glob(os.path.join(root_dir, "**", "*.json"), recursive=True))
    for path in paths:
        try:
            with open(path) as handle:
                data = json.load(handle)
        except (OSError, ValueError):
            skipped += 1
            continue
        if isinstance(data, dict) and "cell" in data:
            reports.append(data)
        else:
            skipped += 1
    return reports, len(paths), skipped


def group_by_test(reports, key):
    """OrderedDict of test id -> {cells, message, ticket, tickets}.

    quarantine.py deliberately allows the same test to carry different
    tickets on disjoint cell globs, so this keeps every ticket seen (not just
    the first report's) and every message, rather than collapsing them to
    whichever report happened to load first.
    """
    grouped = OrderedDict()
    for report in reports:
        for entry in report.get(key, []):
            slot = grouped.setdefault(entry["test"], {
                "cells": [],
                "message": entry.get("message", ""),
                "ticket": entry.get("ticket"),
                "tickets": [],
                "messages": [],
            })
            slot["cells"].append(report["cell"])
            ticket = entry.get("ticket")
            if ticket and ticket not in slot["tickets"]:
                slot["tickets"].append(ticket)
            message = entry.get("message", "")
            if message and message not in slot["messages"]:
                slot["messages"].append(message)
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
        # cell names come from this PR's own workflow file and must go
        # through the same sanitizer as everything else rendered here.
        shown = ", ".join("`{}`".format(sanitize_test_id(c)) for c in cells[:cell_limit])
        if len(cells) > cell_limit:
            shown += " _+{} more_".format(len(cells) - cell_limit)
        message = sanitize_inline((info["message"] or "").replace("|", "\\|"))[:MESSAGE_DISPLAY_WIDTH]
        message_cell = "`{}`".format(message) if message else ""
        if ticket_column:
            # ticket comes from this PR's own quarantine.txt line and is
            # rendered into the same PR comment -- it must not be trusted
            # unescaped any more than the test id or the message are.
            tickets = info.get("tickets") or ([info["ticket"]] if info.get("ticket") else [])
            ticket_text = ", ".join(sanitize_test_id(t) for t in tickets) or "—"
            ticket = "{} | ".format(ticket_text)
        else:
            ticket = ""
        lines.append("| `{}` | {} | {}{} |".format(
            sanitize_test_id(short_name(test_id)), shown, ticket, message_cell))
    if len(grouped) > row_limit:
        lines.append("")
        lines.append("_...and {} more. See the job logs._".format(len(grouped) - row_limit))
    return lines


def cells_glob(cells):
    """A glob covering these cells, when they share one or more obvious axes.

    Suggesting `*aarch64*` for something that only ever failed on aarch64 is more
    useful than listing four cell names, and narrower than quarantining
    everywhere -- which would hide the same test breaking on x64 tomorrow.
    Every shared axis narrows the glob further: a test failing only on
    musl+aarch64 gets `*musl*aarch64*` rather than the wider `*aarch64*`
    (which would also cover glibc aarch64).
    """
    axes = ["aarch64", "amd64", "musl", "glibc", "asan", "tsan", "slow"]
    shared = [axis for axis in axes if all(axis in c for c in cells)]
    if not shared:
        return None
    return ["*" + "*".join(shared) + "*"]


def render_proposals(flaky, proposal_limit=25):
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
    items = list(flaky.items())
    for test_id, info in items[:proposal_limit]:
        reason = sanitize_inline("{} (seen in: {})".format(
            info["message"] or "intermittent failure",
            ", ".join(sorted(set(info["cells"]))[:4]),
        )).replace("|", "/")
        out.append(quarantine.format_entry(
            sanitize_quarantine_test_pattern(test_id),
            "PROF-XXXXX",
            today.isoformat(),
            review_by,
            cells_glob(info["cells"]) or [],
            reason,
        ))
    if len(items) > proposal_limit:
        out.append("# ...and {} more. See the job logs.".format(len(items) - proposal_limit))
    out.append("```")
    out.append("")
    out.append("</details>")
    out.append("")
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dir", required=True, help="directory of downloaded ci-outcome artifacts")
    args = parser.parse_args()

    reports, files_found, files_skipped = load_reports(args.dir)
    if not files_found:
        # Distinct from "reports loaded, all clean": this is what a total
        # ci-outcome artifact-download failure looks like, and it must not
        # render as a silent, spotless run.
        sys.stdout.write("_No CI outcome reports were found for this run._\n")
        return 0
    if not reports:
        if files_skipped:
            sys.stdout.write(
                "_{} CI outcome report(s) were found but could not be parsed._\n"
                .format(files_skipped))
        return 0

    flaky = group_by_test(reports, "flaky")
    persistent = group_by_test(reports, "persistent")
    quarantined = group_by_test(reports, "quarantined")

    out = []
    if files_skipped:
        out.append("_{} of {} CI outcome report(s) could not be parsed and were skipped._".format(
            files_skipped, files_found))
        out.append("")
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

    # attempts_run counts every attempt the runner actually executed;
    # `attempts` counts only attempts that produced JUnit results, which
    # undercounts a cell whose first attempt aborted before writing any XML
    # (e.g. an ASan init abort) and only produced results on the retry.
    retried = [r for r in reports if r.get("attempts_run", r.get("attempts", 1)) > 1]
    if retried:
        out.append("_Retried {} of {} cells._".format(len(retried), len(reports)))
        out.append("")

    sys.stdout.write("\n".join(out))
    if out:
        sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
