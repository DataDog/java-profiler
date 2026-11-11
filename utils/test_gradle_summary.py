#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
"""Exercise the actual Gradle wrapper with inert launchers, including owned shutdown."""

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

    def test_failure_status_preserved_with_reports(self):
        self.launcher("import sys\nprint('> Task :test FAILED')\nprint('3 tests completed, 1 failed, 1 skipped')\nprint('Could not resolve artifact')\nprint('BUILD FAILED in 1s')\nsys.exit(7)\n")
        result, report = self.run_wrapper()
        self.assertEqual(7, result.returncode)
        self.assertEqual(7, report["exitCode"])
        self.assertEqual(["> Task :test FAILED"], report["failedTasks"])
        self.assertTrue(report["depIssues"])
        self.assertTrue(report["tests"]["observedSummaryLines"])
        self.assertTrue((self.root / "build/reports/claude/gradle-summary.md").exists())

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
