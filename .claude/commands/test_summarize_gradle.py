# Copyright 2026, Datadog, Inc.
"""Hermetic tests of local capture/status/owned-process wrapper behavior."""

import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import tempfile
import time
import unittest

WRAPPER = Path(__file__).with_name("build-and-summarize").resolve()


class GradleSummaryTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)

    def launcher(self, body):
        path = self.root / "gradlew"
        path.write_text("#!/usr/bin/env python3\n" + body)
        path.chmod(0o755)

    def report(self):
        return json.loads((self.root / "build/reports/claude/gradle-summary.json").read_text())

    def run_wrapper(self, *args):
        return subprocess.run([str(WRAPPER), *args], cwd=self.root,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=20)

    def test_default_success_and_complete_stream_capture(self):
        self.launcher("import sys\nprint('BUILD SUCCESSFUL')\nprint('stderr marker', file=sys.stderr)\n")
        result = self.run_wrapper()
        self.assertEqual(0, result.returncode, result.stderr)
        report = self.report()
        self.assertEqual(["./gradlew", "build", "-i", "--console=plain"], report["command"])
        self.assertIn("stderr marker", (self.root / report["log"]).read_text())
        self.assertIn("not evaluated", report["testAcceptance"])

    def test_failure_status_and_arguments_are_preserved(self):
        self.launcher("import sys\nprint('BUILD FAILED')\nsys.exit(23)\n")
        result = self.run_wrapper(":module:test", "--console=plain", "-d", "-Ptests=a b")
        self.assertEqual(23, result.returncode, result.stderr)
        self.assertEqual(["./gradlew", ":module:test", "--console=plain", "-d", "-Ptests=a b"],
                         self.report()["command"])
        self.assertEqual(23, self.report()["exitCode"])

    def test_missing_launcher_still_produces_failure_evidence(self):
        self.assertEqual(127, self.run_wrapper().returncode)
        self.assertEqual(127, self.report()["exitCode"])

    @unittest.skipUnless(sys.platform == "linux", "Linux subreaper ownership requires Linux")
    def test_no_daemon_reaps_detached_descendant(self):
        self.launcher("import os, time\nchild = os.fork()\nif child == 0:\n"
                      "    os.setsid()\n    open('detached.pid', 'w').write(str(os.getpid()))\n"
                      "    time.sleep(60)\nelse:\n"
                      "    while not os.path.exists('detached.pid'): time.sleep(0.01)\n"
                      "    print('BUILD SUCCESSFUL')\n")
        result = self.run_wrapper("--no-daemon")
        self.assertEqual(0, result.returncode, result.stderr)
        child = int((self.root / "detached.pid").read_text())
        with self.assertRaises(ProcessLookupError):
            os.kill(child, 0)

    def test_sigterm_reaps_owned_group_and_reports_signal(self):
        self.launcher("import os, time\nopen('launcher.pid', 'w').write(str(os.getpid()))\n"
                      "time.sleep(60)\n")
        process = subprocess.Popen([str(WRAPPER), "--no-daemon"], cwd=self.root,
                                   stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        self.addCleanup(lambda: process.poll() is None and process.kill())
        for _ in range(200):
            if (self.root / "launcher.pid").exists():
                break
            time.sleep(0.01)
        self.assertTrue((self.root / "launcher.pid").exists())
        child = int((self.root / "launcher.pid").read_text())
        process.send_signal(signal.SIGTERM)
        process.communicate(timeout=15)
        self.assertEqual(143, process.returncode)
        self.assertEqual(143, self.report()["exitCode"])
        with self.assertRaises(ProcessLookupError):
            os.kill(child, 0)


if __name__ == "__main__":
    unittest.main()
