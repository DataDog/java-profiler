#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
"""Exercise the actual Gradle wrapper with inert launchers, including owned shutdown."""

import contextlib
import io
import importlib.util
import json
import os
from pathlib import Path
import shutil
import signal
import subprocess
import tempfile
import time
import unittest
import unittest.mock


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("gradle_summary", ROOT / "utils/gradle_summary.py")
SUMMARY = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SUMMARY)


class GradleSummaryTest(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        (self.root / ".claude/commands").mkdir(parents=True)
        (self.root / "utils").mkdir()
        for relative in (".claude/commands/build-and-summarize", "utils/gradle_summary.py"):
            shutil.copy2(ROOT / relative, self.root / relative)
        # If an external coding runner is ever invoked, the test must fail.
        runner = self.root / "claude"
        runner.write_text("#!/bin/sh\ntouch external-runner-called\nexit 99\n")
        runner.chmod(0o755)
        self.env = dict(os.environ, PATH=str(self.root) + os.pathsep + os.environ["PATH"])

    def launcher(self, body):
        file = self.root / "gradlew"
        file.write_text("#!/usr/bin/env python3\n" + body)
        file.chmod(0o755)

    def run_wrapper(self, *args):
        result = subprocess.run([".claude/commands/build-and-summarize", *args], cwd=self.root,
                                env=self.env, capture_output=True, text=True)
        self.assertFalse((self.root / "external-runner-called").exists())
        return result, json.loads((self.root / "build/reports/claude/gradle-summary.json").read_text())

    def test_defaults_argument_fidelity_and_full_stream_capture(self):
        self.launcher("import sys,json\nprint(json.dumps(sys.argv[1:]))\nprint('stderr-witness',file=sys.stderr)\nprint('BUILD SUCCESSFUL in 1s')\n")
        result, report = self.run_wrapper()
        self.assertEqual(0, result.returncode)
        self.assertEqual(["./gradlew", "build", "-i", "--console=plain"], report["command"])
        result, report = self.run_wrapper(":ddprof-test:testDebug", "-Ptests=Class.method with spaces", "--offline")
        self.assertEqual(0, result.returncode)
        log = (self.root / report["log"]).read_text()
        self.assertIn("stderr-witness", log)
        self.assertEqual([":ddprof-test:testDebug", "-Ptests=Class.method with spaces", "--offline", "-i", "--console=plain"], json.loads(log.splitlines()[1]))
        self.assertEqual("SUCCESS", report["status"])
        self.assertGreater(report["launcherPid"], 0)
        self.assertEqual(report["launcherPid"], report["launcherProcessGroup"])
        self.assertIsNone(report["interruptedBy"])
        self.assertIsNone(report["tests"]["total"])
        self.assertEqual(2, len(list((self.root / "build/logs").glob("*.log"))))

    def test_log_collision_never_overwrites_retained_evidence(self):
        class FixedDateTime:
            @staticmethod
            def now():
                return FixedDateTime()

            def strftime(self, pattern):
                return "20261113-200000-000001"

        log = self.root / "build/logs/20261113-200000-000001-build-{}.log".format(os.getpid())
        log.parent.mkdir(parents=True)
        log.write_text("retained evidence\n")
        previous = os.getcwd()
        try:
            os.chdir(self.root)
            with unittest.mock.patch.object(SUMMARY.datetime, "datetime", FixedDateTime), \
                 contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(1, SUMMARY.main([]))
            self.assertEqual("retained evidence\n", log.read_text())
        finally:
            os.chdir(previous)

    def test_failure_status_preserved_with_reports(self):
        lines = ["> Task :test FAILED", "Fixture > fails() FAILED", "3 tests completed, 1 failed, 1 skipped",
                 "* What went wrong:", "Execution failed for task ':test'.",
                 "> A controlled failure", "", "* Try:", "Not an exception headline",
                 "Deprecated feature", "configuration cache miss", "Could not resolve artifact",
                 "BUILD FAILED in 1s"]
        self.launcher("import sys\n" + "\n".join("print({!r})".format(line) for line in lines) + "\nsys.exit(7)\n")
        result, report = self.run_wrapper()
        self.assertEqual(7, result.returncode)
        self.assertEqual(7, report["exitCode"])
        self.assertEqual(["> Task :test FAILED"], report["failedTasks"])
        for expected in ("=== What went wrong ===", "> A controlled failure",
                         "=== Failing tasks/tests ===", "Fixture > fails() FAILED"):
            self.assertIn(expected, result.stdout)
        self.assertEqual(["Execution failed for task ':test'.", "> A controlled failure"], report["exceptionHeadlines"])
        self.assertEqual(["Deprecated feature", "configuration cache miss"], report["warnings"])
        self.assertEqual(["Could not resolve artifact"], report["depIssues"])
        self.assertEqual(["3 tests completed, 1 failed, 1 skipped"], report["tests"]["observedSummaryLines"])
        markdown = (self.root / "build/reports/claude/gradle-summary.md").read_text()
        self.assertIn("- > A controlled failure", markdown)
        self.assertNotIn("Not an exception headline", markdown)

    def test_summary_extraction_truncates_at_exact_boundaries(self):
        headlines = ["failure-{}".format(i) for i in range(21)]
        warnings = ["cache miss-{}".format(i) for i in range(31)]
        dependencies = ["Could not GET artifact-{}".format(i) for i in range(21)]
        lines = ["* What went wrong:"] + headlines + ["* Try:", "excluded"] + warnings + dependencies
        self.launcher("\n".join("print({!r})".format(line) for line in lines) + "\n")
        result, report = self.run_wrapper()
        self.assertEqual(0, result.returncode)
        self.assertEqual(headlines[:20], report["exceptionHeadlines"])
        self.assertEqual(warnings[:30], report["warnings"])
        self.assertEqual(dependencies[:20], report["depIssues"])
        markdown = (self.root / "build/reports/claude/gradle-summary.md").read_text()
        for entries, limit in [(headlines, 10), (warnings, 15), (dependencies, 10)]:
            self.assertIn("- " + entries[limit - 1] + "\n", markdown)
            self.assertNotIn("- " + entries[limit] + "\n", markdown)

    def test_summary_write_failure_preserves_child_failure_and_fails_success(self):
        for exit_code in (0, 7):
            for filename in ("gradle-summary.json", "gradle-summary.md"):
                with self.subTest(exit_code=exit_code, filename=filename):
                    self.launcher("import sys\nprint('BUILD SUCCESSFUL in 1s')\nsys.exit({})\n".format(exit_code))
                    path = self.root / "build/reports/claude" / filename
                    path.parent.mkdir(parents=True, exist_ok=True)
                    if path.is_file():
                        path.unlink()
                    path.mkdir()
                    try:
                        result = subprocess.run([".claude/commands/build-and-summarize"], cwd=self.root,
                                                env=self.env, capture_output=True, text=True)
                        self.assertEqual(exit_code or 1, result.returncode)
                        self.assertIn("Summary failed:", result.stderr)
                    finally:
                        path.rmdir()

    def test_streaming_errors_close_pipe_kill_group_and_reap_launcher(self):
        for stage in ("Gradle stream", "Log sink", "Progress sink", "pipe close"):
            with self.subTest(stage=stage):
                self.launcher("import subprocess,time,pathlib\np=subprocess.Popen(['sleep','120'])\npathlib.Path('child.pid').write_text(str(p.pid))\nprint('> Task :inert',flush=True)\ntime.sleep(120)\n")
                real_popen = subprocess.Popen
                owned = []

                class BrokenPipe:
                    def __init__(self, pipe):
                        self.pipe = pipe
                    def __iter__(self):
                        return self
                    def __next__(self):
                        line = next(self.pipe)
                        if stage == "Gradle stream":
                            raise OSError("injected stream failure")
                        return line
                    def close(self):
                        self.pipe.close()
                        if stage == "pipe close":
                            raise OSError("injected close failure")

                def launch(*args, **kwargs):
                    process = real_popen(*args, **kwargs)
                    owned.append(process)
                    process.stdout = BrokenPipe(process.stdout)
                    return process

                real_print = print
                def print_line(*args, **kwargs):
                    if args and str(args[0]).startswith("> Task") and stage in ("Progress sink", "pipe close"):
                        raise OSError("injected progress failure")
                    real_print(*args, **kwargs)

                real_fdopen = os.fdopen
                class BrokenSink:
                    def __init__(self, *args, **kwargs):
                        self.file = real_fdopen(*args, **kwargs)
                    def __enter__(self):
                        return self
                    def __exit__(self, *args):
                        self.file.close()
                    def write(self, line):
                        raise OSError("injected sink failure")

                errors = io.StringIO()
                previous = os.getcwd()
                handlers = {sig: signal.getsignal(sig) for sig in (signal.SIGINT, signal.SIGTERM)}
                try:
                    os.chdir(self.root)
                    with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(errors), \
                         unittest.mock.patch.object(SUMMARY.subprocess, "Popen", side_effect=launch), \
                         unittest.mock.patch("builtins.print", side_effect=print_line), \
                         unittest.mock.patch.object(SUMMARY.os, "fdopen", side_effect=BrokenSink if stage == "Log sink" else real_fdopen):
                        status = SUMMARY.main([])
                    self.assertEqual(1, status)
                    self.assertIn(("Progress sink" if stage == "pipe close" else stage) + " failed:", errors.getvalue())
                    if stage == "pipe close":
                        self.assertIn("Gradle pipe close failed:", errors.getvalue())
                    self.assertEqual(1, len(owned))
                    child = owned[0]
                    self.assertIsNotNone(child.returncode)
                    self.assertTrue(child.stdout.pipe.closed)
                    with self.assertRaises(ChildProcessError):
                        os.waitpid(child.pid, os.WNOHANG)
                    # Zombies have no executable lifetime; no owned group member may remain live.
                    states = subprocess.check_output(["ps", "-ax", "-o", "pgid=,stat="], text=True)
                    self.assertFalse(any(int(parts[0]) == child.pid and not parts[1].startswith("Z")
                                         for line in states.splitlines() if len(parts := line.split()) >= 2))
                    self.assertEqual(handlers, {sig: signal.getsignal(sig) for sig in handlers})
                    report = json.loads(Path("build/reports/claude/gradle-summary.json").read_text())
                    self.assertEqual(1, report["exitCode"])
                finally:
                    os.chdir(previous)
                    for child in owned:
                        if child.poll() is None:
                            os.killpg(child.pid, signal.SIGKILL)
                            child.wait(timeout=5)

    def test_summaries_omit_signed_queries_and_url_credentials(self):
        self.launcher("print('Could not GET https://user:password@example.org/artifact?sig=private#fragment')\nprint('Could not resolve https://[invalid')\n")
        result, report = self.run_wrapper()
        self.assertEqual(0, result.returncode)
        raw = (self.root / report["log"]).read_text()
        self.assertIn("sig=private", raw)
        self.assertEqual(0o600, (self.root / report["log"]).stat().st_mode & 0o777)
        for name in ("gradle-summary.md", "gradle-summary.json"):
            summary = (self.root / "build/reports/claude" / name).read_text()
            self.assertNotIn("private", summary)
            self.assertNotIn("password", summary)
            self.assertNotIn("fragment", summary)
            self.assertIn("https://example.org/artifact", summary)
            self.assertIn("[invalid URL omitted]", summary)

    def test_missing_launcher_is_not_success(self):
        result, report = self.run_wrapper()
        self.assertEqual(127, result.returncode)
        self.assertEqual("FAILED", report["status"])
        self.assertIsNone(report["launcherPid"])
        self.assertIsNone(report["launcherProcessGroup"])

    def test_empty_output_does_not_claim_build_or_tests(self):
        self.launcher("pass\n")
        result, report = self.run_wrapper()
        self.assertEqual(0, result.returncode)
        self.assertEqual("UNKNOWN", report["status"])
        self.assertIsNone(report["tests"]["total"])

    def test_signal_permission_error_requires_no_live_group_members(self):
        process = subprocess.Popen(["sleep", "120"], start_new_session=True)
        try:
            with unittest.mock.patch.object(SUMMARY.os, "killpg", side_effect=PermissionError):
                with self.assertRaises(PermissionError):
                    SUMMARY.signal_process_group(process.pid, signal.SIGKILL)
            process.terminate()
            process.wait(timeout=5)
            with unittest.mock.patch.object(SUMMARY.os, "killpg", side_effect=PermissionError):
                SUMMARY.signal_process_group(process.pid, signal.SIGKILL)
        finally:
            if process.poll() is None:
                process.kill()
                process.wait(timeout=5)

    def test_signal_terminates_owned_process_and_descendant(self):
        self.launcher("import subprocess,time,pathlib\np=subprocess.Popen(['sleep','120'])\npathlib.Path('child.pid').write_text(str(p.pid))\ntry:\n time.sleep(120)\nfinally:\n p.terminate()\n p.wait()\n")
        process = subprocess.Popen([".claude/commands/build-and-summarize"], cwd=self.root,
                                   env=self.env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        try:
            deadline = time.monotonic() + 5
            while not (self.root / "child.pid").exists() and time.monotonic() < deadline:
                time.sleep(0.02)
            self.assertTrue((self.root / "child.pid").exists())
            pid = int((self.root / "child.pid").read_text())
            process.send_signal(signal.SIGTERM)
            output, _ = process.communicate(timeout=15)
            self.assertEqual(143, process.returncode, output)
            deadline = time.monotonic() + 5
            while time.monotonic() < deadline:
                try:
                    os.kill(pid, 0)
                except ProcessLookupError:
                    break
                time.sleep(0.02)
            else:
                self.fail("owned descendant still exists")
            report = json.loads((self.root / "build/reports/claude/gradle-summary.json").read_text())
            self.assertEqual(143, report["exitCode"])
            self.assertEqual(signal.SIGTERM, report["interruptedBy"])
            self.assertGreater(report["launcherProcessGroup"], 0)
        finally:
            if process.poll() is None:
                process.terminate()
                process.communicate(timeout=15)


if __name__ == "__main__":
    unittest.main()
