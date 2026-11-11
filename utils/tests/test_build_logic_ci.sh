#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.

set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
python3 - "${1:-$ROOT/.github/workflows/ci.yml}" <<'PY'
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

workflow = Path(sys.argv[1]).read_text()


def job(name):
    matches = re.findall(
        rf"^  {re.escape(name)}:\n(.*?)(?=^  [\w-]+:|\Z)", workflow, re.M | re.S
    )
    assert len(matches) == 1, f"expected one {name} job, found {len(matches)}"
    return matches[0]


def field(block, key, indent):
    matches = re.findall(rf"^{' ' * indent}{re.escape(key)}: (.+)$", block, re.M)
    assert len(matches) == 1, f"expected one {key} field, found {len(matches)}"
    return matches[0]


build_logic = job("build-logic-tests")
assert field(build_logic, "runs-on", 4) == "ubuntu-22.04"
assert 1 <= int(field(build_logic, "timeout-minutes", 4)) <= 30
assert field(build_logic, "needs", 4) == "check-for-pr", "must not depend on formatting"
assert field(build_logic, "if", 4) == field(job("check-formatting"), "if", 4)
assert field(build_logic, "if", 4) == "needs.check-for-pr.outputs.skip != 'true'"
assert "    permissions:\n      contents: read\n    steps:\n" in build_logic
assert "continue-on-error:" not in build_logic

# The workflow uses six-space step headers and literal, ten-space run blocks.
steps = re.split(r"^      - ", build_logic, flags=re.M)[1:]
assert len(steps) == 4, "expected checkout, Java setup, tests and failure artifacts"
checkout, java, tests, artifacts = steps
for step, action, reference in (
    (checkout, "checkout", job("check-formatting")),
    (java, "setup-java", job("check-formatting")),
    (artifacts, "upload-artifact", job("fuzz")),
):
    pin = rf"actions/{action}@[0-9a-f]{{40}}"
    actual = re.findall(pin, step)
    assert len(actual) == 1 and actual == re.findall(pin, reference), f"reuse pinned {action}"
assert field(checkout, "persist-credentials", 10) == "false"
assert field(java, "distribution", 10) == "'zulu'"
assert field(java, "java-version", 10) == "'21'"
assert field(artifacts, "if", 8) == "failure()"
assert field(artifacts, "if-no-files-found", 10) == "warn"
assert field(artifacts, "name", 10) == "build-logic-test-failures"
assert "          path: |\n            build/logs/\n            build-logic/conventions/build/test-results/test/*.xml\n" in artifacts
assert not re.search(r"^        (if|working-directory|env):", tests, re.M)
print("PASS: build-logic-tests job, JDK, guard, permissions and failure artifacts")

blocks = re.findall(r"^        run: \|\n((?:          .*\n)+)", tests, re.M)
assert len(blocks) == 1, "expected one literal test run block"
run = "\n".join(line[10:] for line in blocks[0].splitlines()) + "\n"
expected_args = [
    "-p", "build-logic", ":conventions:test", "--max-workers=2",
    "--no-build-cache", "--no-daemon", "--no-watch-fs",
]
assert run.strip() == "./.claude/commands/build-and-summarize " + " ".join(expected_args)
assert "for t in utils/tests/*.sh " in job("script-tests"), "contract test must run in CI"

with tempfile.TemporaryDirectory() as tmp:
    root = Path(tmp)
    wrapper = root / ".claude/commands/build-and-summarize"
    wrapper.parent.mkdir(parents=True)
    wrapper.write_text('#!/usr/bin/env bash\nprintf "%s\\n" "$@" > "$CAPTURE"\nexit "$FAKE_STATUS"\n')
    wrapper.chmod(0o755)
    capture = root / "args"
    for status in (0, 37):
        capture.unlink(missing_ok=True)
        result = subprocess.run(
            ["bash", "--noprofile", "--norc", "-e", "-o", "pipefail", "-c", run],
            cwd=root, env={**os.environ, "CAPTURE": str(capture), "FAKE_STATUS": str(status)},
            capture_output=True, text=True,
        )
        assert result.returncode == status, f"wrapper exit {status} lost: {result}"
        assert capture.read_text().splitlines() == expected_args, "wrong Gradle task or arguments"
        print(f"PASS: workflow run block invokes exact wrapper arguments and propagates exit {status}")
PY
