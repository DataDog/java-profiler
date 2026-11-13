#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PostToolUse hook: on a successful `gh pr create|new` in this repo's
checkout, trigger the babysit-pr skill by naming the created PR. Exit 2 feeds the stderr
message to Claude after the successful call (no block). Success is read from the tool
response: a `gh pr create` success prints the created PR's URL, so a URL matching the
protected repository in the response text counts, wherever it appears. Attribution does
not come from the URL's shape (response formatting is not part of any contract) but from
the command gate: only `gh pr create|new` invocations reach this check, so a URL printed
by `gh pr view` or `gh pr ready` is never attributed to the create, and no URL at all
means the create failed or never ran. Residual: a later segment of a compound command
that mentions `gh pr create` and prints a URL itself can still be misattributed to the
create — accepted, backstopped by the skill's trigger-context resolve. A PR in another
repository is not this repo's policy; only datadog/java-profiler PRs trigger.
Pushes and PR readiness stay gated by require-fresh-review.py and .githooks/pre-push;
this hook only injects an instruction."""

import json
import os
import re
import subprocess
import sys

# Matched on raw text, as in require-fresh-review.py: subshells, `bash -c`, if/then and
# multi-line commands cannot hide it. The cost is a false trigger when the text is only
# quoted; a false trigger only injects an instruction, so it is accepted. The Pi adapter
# (.pi/extensions/babysit-pr.ts) applies a looser TS pre-filter before spawning this
# hook; this regex remains authoritative.
PR_CMD = re.compile(r"\bgh\b[^\n]*?\bpr\s+(create|new)\b")
PR_URL = re.compile(r"https://github\.com/([\w.-]+/[\w.-]+)/pull/(\d+)")
# The repository this trigger protects, whatever the checkout's remotes point at.
PROTECTED_REPO = "datadog/java-profiler"
# git_out joins the copy group of require-fresh-review.py, require-gradle-wrapper.py
# and protect-knowledgebase.py; change all four together. This hook copies git_out
# only: it runs no origin/main script and loads no trusted ref.


def git_out(args, cwd):
    res = subprocess.run(["git", *args], cwd=cwd, stdout=subprocess.PIPE,
                         stderr=subprocess.DEVNULL)
    return res.stdout.decode(errors="replace").strip() if res.returncode == 0 else None


def strings(value):
    """Every string nested in the parsed tool_response, recursively: the Bash response
    shape (stdout/stderr fields) is not part of any contract."""
    if isinstance(value, str):
        yield value
    elif isinstance(value, dict):
        for child in value.values():
            yield from strings(child)
    elif isinstance(value, list):
        for child in value:
            yield from strings(child)


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    if not isinstance(payload, dict):
        return 0  # non-object JSON: fail open like malformed JSON
    tool_input = payload.get("tool_input")
    if not isinstance(tool_input, dict):
        return 0  # missing/null/non-dict tool_input: fail open
    typed = tool_input.get("command")
    if not isinstance(typed, str):
        return 0  # non-string command: fail open
    # Join backslash-continued lines so `gh pr \<newline> create` is one line to the regex.
    if not PR_CMD.search(typed.replace("\\\n", " ")):
        return 0
    project = os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd()
    cwd = payload.get("cwd")
    if not isinstance(cwd, str) or not cwd:
        cwd = os.getcwd()  # missing/non-string/empty: use the hook's own cwd
    top = git_out(["rev-parse", "--show-toplevel"], cwd)
    common = top and git_out(["rev-parse", "--path-format=absolute", "--git-common-dir"], top)
    if not common or common != git_out(["rev-parse", "--path-format=absolute",
                                        "--git-common-dir"], project):
        return 0  # another repository, or not a git checkout: not this repo's policy
    response = "\n".join(strings(payload.get("tool_response") or {}))
    # A trigger URL must be the sole content of its line: `gh pr create` prints the
    # created PR's URL alone on a line, while any other gh output that mentions a PR
    # URL (e.g. `gh pr view --json url`) embeds it in JSON or prose and must not
    # hijack the trigger when the create failed in a compound command.
    urls = [m for line in response.splitlines()
            for m in PR_URL.finditer(line) if line.strip() == m.group(0)]
    if not urls:
        return 0  # no bare PR URL in the response: the create failed, or gh printed none
    # The last protected bare-URL line wins: gh pr create prints the just-created PR
    # of this repository as a bare line, and a later foreign-repo bare line must not
    # hide it.
    selected = next((m for m in reversed(urls)
                     if m.group(1).lower() == PROTECTED_REPO), None)
    if not selected:
        return 0  # no PR in this repository: not this repo's policy
    number = selected.group(2)
    print("Babysit-pr trigger: pull request #%s was created (%s).\n"
          "Invoke the babysit-pr skill now and follow it exactly: launch the background "
          "babysitter for PR #%s as the skill specifies." % (number, selected.group(0),
                                                             number),
          file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main())
