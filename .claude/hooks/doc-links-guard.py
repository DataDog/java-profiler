#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse adapter for the doc-links write guard.

Reads the hook payload from stdin, reconstructs the document a Write/Edit/MultiEdit
would produce, and runs utils/check-doc-links.py --check-file on it. Exit 2 blocks
the tool call with the checker's violations as feedback; exit 0 allows. A floor, not
a sandbox: bash rewrites bypass it, and a checker environment error must not wedge
the agent, so it allows.
"""
import json
import os
import subprocess
import sys

_MD_EXTS = (".md", ".markdown")


def _resulting_content(tool_name, tool_input, incoming_path):
    """The document the tool call would produce, or None when it cannot be determined."""
    if tool_name == "Write":
        return tool_input.get("content")
    # Edit/MultiEdit: check the resulting file, never just the introduced fragment —
    # a fragment's code fences balance against the surrounding file, so fragment-only
    # checking false-blocks valid edits and misses breaks formed by the combination.
    try:
        with open(incoming_path, encoding="utf-8") as fh:
            content = fh.read()
    except OSError:
        return None  # unreadable target: allow, the edit call itself will fail
    if tool_name == "Edit":
        edits = [tool_input]
    else:
        edits = tool_input.get("edits") or []
    for edit in edits:
        old = edit.get("old_string")
        if not isinstance(old, str) or old not in content:
            return None  # cannot reconstruct the result: allow, the edit call will fail
        # Claude Code's Edit replaces every occurrence under replace_all; otherwise
        # only the first (the tool contracts require a unique match).
        count = content.count(old) if edit.get("replace_all") else 1
        content = content.replace(old, edit.get("new_string", ""), count)
    return content


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    tool_input = payload.get("tool_input") or {}
    path = tool_input.get("file_path") or tool_input.get("path")
    if not path or not str(path).lower().endswith(_MD_EXTS):
        return 0
    root = os.environ.get("CLAUDE_PROJECT_DIR") or os.path.dirname(
        os.path.dirname(os.path.abspath(__file__)))
    incoming_path = str(path)
    if not os.path.isabs(incoming_path):
        base = os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd()
        incoming_path = os.path.join(base, incoming_path)
    rel = os.path.relpath(incoming_path, root)
    if rel.startswith("..") or os.path.isabs(rel):
        return 0  # outside the checkout
    content = _resulting_content(payload.get("tool_name"), tool_input, incoming_path)
    if not content:
        return 0
    try:
        res = subprocess.run(
            ["python3", "utils/check-doc-links.py", "--check-file", rel],
            cwd=root, input=content, text=True, capture_output=True, timeout=15)
    except (OSError, subprocess.TimeoutExpired):
        return 0
    if res.returncode == 1:
        sys.stderr.write("Blocked: the write would introduce broken doc links.\n" + res.stdout)
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
