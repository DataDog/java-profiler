#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse adapter for the doc-links write guard.

Reads the hook payload from stdin, extracts the markdown content a Write/Edit/MultiEdit
would introduce, and runs utils/check-doc-links.py --check-file on it as the doc the
path names. Exit 2 blocks the tool call with the checker's violations as feedback;
exit 0 allows. A floor, not a sandbox: bash rewrites bypass it, and a checker
environment error (exit 2) must not wedge the agent, so it allows.
"""
import json
import os
import subprocess
import sys

_MD_EXTS = (".md", ".markdown")


def _incoming_content(tool_name, tool_input):
    """The markdown content the tool call would introduce, or None when not applicable."""
    if tool_name == "Write":
        return tool_input.get("content")
    if tool_name == "Edit":
        return tool_input.get("new_string")
    if tool_name == "MultiEdit":
        return "\n".join(e.get("new_string", "") for e in tool_input.get("edits") or [])
    return None


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    tool_input = payload.get("tool_input") or {}
    content = _incoming_content(payload.get("tool_name"), tool_input)
    path = tool_input.get("file_path") or tool_input.get("path")
    if not content or not path or not str(path).lower().endswith(_MD_EXTS):
        return 0
    root = os.environ.get("CLAUDE_PROJECT_DIR") or os.path.dirname(
        os.path.dirname(os.path.abspath(__file__)))
    rel = os.path.relpath(str(path), root)
    if rel.startswith("..") or os.path.isabs(rel):
        return 0  # outside the checkout
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
