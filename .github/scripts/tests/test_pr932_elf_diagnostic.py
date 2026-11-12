#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.

import importlib.util
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch


SCRIPT = Path(__file__).resolve().parents[1] / "pr932_elf_diagnostic.py"
SPEC = importlib.util.spec_from_file_location("diagnostic", SCRIPT)
DIAGNOSTIC = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(DIAGNOSTIC)
SHA = "a" * 40

WRAPPER = r'''
import os
from pathlib import Path
import sys
root = Path.cwd()
(root / "wrapper-arguments.json").write_text(__import__("json").dumps(sys.argv[1:]))
(root / "build/logs").mkdir(parents=True, exist_ok=True)
(root / "build/logs/elf-build.log").write_text("narrow build log\n")
daemon = Path(os.environ["GRADLE_USER_HOME"]) / "daemon/9/daemon-1.out.log"
daemon.parent.mkdir(parents=True, exist_ok=True)
daemon.write_text("secret-context must not ship\nThreadSanitizer: selected\nsingle-use Daemon\n")
old = daemon.with_name("daemon-0.out.log")
old.write_text("FATAL: unrelated old build\n")
os.utime(old, (0, 0))
print("build stdout")
print("build stderr", file=sys.stderr)
build = root / "ddprof-lib/build"
for name in ["test/resources/native-libs/unresolved-functions/main",
             "test/resources/native-libs/reladyn-lib/libreladyn.so",
             "test/resources/native-libs/small-lib/libsmall-lib.so"]:
    path = build / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("fixture debug metadata")
if os.environ.get("MODE") == "missing_resource":
    path.unlink()
if os.environ.get("MODE") != "missing_binary":
    binary = build / "bin/gtest/tsan_elfparser_ut/elfparser_ut"
    binary.parent.mkdir(parents=True, exist_ok=True)
    binary.write_text(os.environ["FAKE_BINARY"])
    binary.chmod(0o755)
sys.exit(17 if os.environ.get("MODE") == "build_failure" else 0)
'''

BINARY = r'''
import json
import os
from pathlib import Path
import signal
import sys
root = Path.cwd().parents[1]
count = root / "native-count"
index = int(count.read_text()) + 1 if count.exists() else 1
count.write_text(str(index))
print("native stdout " + str(index))
print("native stderr " + str(index), file=sys.stderr, flush=True)
print(json.dumps({key: os.environ[key] for key in
                  ("TEST_COMMIT", "TSAN_OPTIONS", "GTEST_DEATH_TEST_STYLE")}))
xml = Path(sys.argv[1].split("xml:", 1)[1])
mode = os.environ.get("MODE", "")
if mode == "signal":
    os.kill(os.getpid(), signal.SIGTERM)
if mode == "missing_xml":
    sys.exit(0)
if mode == "malformed_xml":
    xml.write_text("<broken>")
    sys.exit(0)
if mode == "empty_xml":
    xml.touch()
    sys.exit(0)
cases = 30 if mode == "partial_xml" else 32 if mode == "extra_xml" else 31
marker = {"failed_xml": "<failure/>", "error_xml": "<error/>",
          "skipped_xml": "<skipped/>"}.get(mode, "")
status = ' status="notrun"' if mode == "notrun_xml" else ''
root_tag = 'wrong' if mode == 'wrong_root_xml' else 'testsuites'
xml.write_text('<' + root_tag + '><testsuite tests="31">' +
               ''.join('<testcase name="case' + str(i) + '"' + status + '>' +
                       (marker if i == 0 else '') + '</testcase>' for i in range(cases)) +
               '</testsuite></' + root_tag + '>')
if mode == "native_failure" or (mode == "second_failure" and index == 2):
    sys.exit(134)
'''


class ElfDiagnosticTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="elf diagnostic ")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.source = self.root / "source"
        self.source.mkdir()
        self.output = self.root / "evidence"
        tools = self.root / "tools"
        tools.mkdir()
        self.executable(tools / "git", '''
import os
import sys
from pathlib import Path
if sys.argv[1] == "rev-parse":
    print(os.environ.get("ACTUAL_SHA", "a" * 40))
else:
    counter = Path("diff-count")
    count = int(counter.read_text()) + 1 if counter.exists() else 1
    counter.write_text(str(count))
    mode = os.environ.get("MODE")
    sys.exit(1 if mode == "dirty_source" or (mode == "modified_source" and count == 2)
             or (mode == "modified_during_native" and count == 3) else 0)
''')
        self.executable(tools / "readelf", '''
import os
import sys
print("ELF build-id and embedded debug sections")
sys.exit(1 if os.environ.get("MODE") == "readelf_failure" else 0)
''')
        self.executable(self.source / ".claude/commands/build-and-summarize", WRAPPER)
        self.environment = dict(os.environ, PATH=str(tools) + os.pathsep + os.environ["PATH"],
                                GRADLE_USER_HOME=str(self.root / "gradle"),
                                FAKE_BINARY=f"#!{sys.executable}\n" + BINARY)

    @staticmethod
    def executable(path, content):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(f"#!{sys.executable}\n" + content)
        path.chmod(0o755)

    def run_diagnostic(self, mode="", repetitions=3, actual_sha=SHA):
        environment = dict(self.environment, MODE=mode, ACTUAL_SHA=actual_sha)
        completed = subprocess.run([sys.executable, str(SCRIPT), str(self.source), SHA,
                                    str(self.output), str(repetitions)], env=environment,
                                   text=True, capture_output=True)
        self.result = json.loads((self.output / "result.json").read_text())
        return completed

    def assert_failure(self, completed, stage, attempts):
        self.assertEqual(completed.returncode, 1, completed.stderr)
        self.assertEqual(self.result["status"], "failed")
        self.assertEqual(self.result["stage"], stage)
        self.assertEqual(len(self.result["attempts"]), attempts)
        self.assertIn("ELF diagnostic failed", completed.stderr)

    def test_success_captures_all_repetitions_artifacts_environment_and_logs(self):
        completed = self.run_diagnostic()
        self.assertEqual(completed.returncode, 0, completed.stderr)
        self.assertEqual(self.result["status"], "passed")
        self.assertEqual(self.result["actual_sha"], SHA)
        self.assertEqual(self.result["repetitions_planned"], 3)
        self.assertEqual([a["tests_passed"] for a in self.result["attempts"]], [31, 31, 31])
        arguments = json.loads((self.source / "wrapper-arguments.json").read_text())
        self.assertEqual(arguments, [":ddprof-lib:linkGtestTsan_elfparser_ut", ":ddprof-lib:buildNativeLibs",
                                     "-PCI", "-PkeepJFRs", "--no-daemon", "--parallel", "--build-cache", "--no-watch-fs"])
        for index in range(1, 4):
            attempt = self.output / f"attempt-{index}"
            self.assertIn(f"native stdout {index}", (attempt / "stdout.txt").read_text())
            self.assertEqual((attempt / "stderr.txt").read_text(), f"native stderr {index}\n")
            self.assertTrue((attempt / "elfparser.xml").is_file())
        stdout = (self.output / "attempt-1/stdout.txt").read_text().splitlines()
        environment = json.loads(stdout[1])
        self.assertEqual(environment["TEST_COMMIT"], SHA)
        self.assertEqual(environment["GTEST_DEATH_TEST_STYLE"], "threadsafe")
        self.assertEqual(environment["TSAN_OPTIONS"],
                         "handle_segv=0:handle_sigbus=0:use_sigaltstack=0:halt_on_error=1:"
                         f"abort_on_error=1:io_sync=0:suppressions={self.source}/gradle/sanitizers/tsan.supp")
        binary = self.output / "native/bin/gtest/tsan_elfparser_ut/elfparser_ut"
        self.assertEqual(self.result["binary_sha256"], __import__("hashlib").sha256(binary.read_bytes()).hexdigest())
        self.assertTrue((self.output / "native/test/resources/native-libs/unresolved-functions/main").is_file())
        self.assertTrue((self.output / "native/test/resources/native-libs/reladyn-lib/libreladyn.so").is_file())
        small_library = Path("test/resources/native-libs/small-lib/libsmall-lib.so")
        self.assertEqual((self.output / "native" / small_library).read_bytes(),
                         (self.source / "ddprof-lib/build" / small_library).read_bytes())
        self.assertIn("embedded debug", (self.output / "elf-metadata.txt").read_text())
        self.assertEqual((self.output / "build-logs/elf-build.log").read_text(), "narrow build log\n")
        daemon = (self.output / "build-logs/single-use-daemon-diagnostics.txt").read_text()
        self.assertIn("ThreadSanitizer: selected", daemon)
        self.assertIn("single-use Daemon", daemon)
        self.assertNotIn("secret-context", daemon)
        self.assertNotIn("unrelated old build", daemon)
        self.assertIn("build stderr", (self.output / "build-driver.log").read_text())

    def test_repetition_limits(self):
        for count in (0, 11):
            with self.subTest(count=count):
                self.assert_failure(self.run_diagnostic(repetitions=count), "preflight", 0)
                self.assertFalse((self.source / "wrapper-arguments.json").exists())

    def test_maximum_repetitions_complete_without_retry(self):
        completed = self.run_diagnostic(repetitions=10)
        self.assertEqual(completed.returncode, 0, completed.stderr)
        self.assertEqual(len(self.result["attempts"]), 10)
        self.assertEqual(self.result["attempts"][-1]["tests_passed"], 31)

    def test_sha_mismatch_prevents_build(self):
        self.assert_failure(self.run_diagnostic(actual_sha="b" * 40), "preflight", 0)
        self.assertFalse((self.source / "wrapper-arguments.json").exists())

    def test_dirty_source_prevents_build(self):
        self.assert_failure(self.run_diagnostic("dirty_source"), "preflight", 0)
        self.assertFalse((self.source / "wrapper-arguments.json").exists())

    def test_build_failure_retains_logs_without_native_execution(self):
        self.assert_failure(self.run_diagnostic("build_failure"), "build", 0)
        self.assertEqual(self.result["build_exit_code"], 17)
        self.assertIn("build stdout", (self.output / "build-driver.log").read_text())
        self.assertTrue((self.output / "build-logs/elf-build.log").exists())
        self.assertFalse((self.source / "native-count").exists())

    def test_missing_binary_stops_before_native(self):
        self.assert_failure(self.run_diagnostic("missing_binary"), "artifacts", 0)

    def test_missing_resource_stops_before_native(self):
        self.assert_failure(self.run_diagnostic("missing_resource"), "artifacts", 0)
        self.assertTrue((self.output / "native/bin/gtest/tsan_elfparser_ut/elfparser_ut").exists())

    def test_readelf_failure_is_gating(self):
        self.assert_failure(self.run_diagnostic("readelf_failure"), "artifacts", 0)
        self.assertTrue((self.output / "elf-metadata.txt").exists())

    def test_native_exit134_is_not_excused_by_passing_xml(self):
        self.assert_failure(self.run_diagnostic("native_failure"), "native", 1)
        self.assertEqual(self.result["attempts"][0]["shell_exit_code"], 134)
        self.assertTrue(self.result["attempts"][0]["xml_present"])
        self.assertEqual((self.output / "attempt-1/stderr.txt").read_text(), "native stderr 1\n")
        self.assertFalse((self.output / "attempt-2").exists())
        self.assertTrue((self.output / "native/bin/gtest/tsan_elfparser_ut/elfparser_ut").exists())

    def test_later_failure_stops_remaining_repetitions(self):
        self.assert_failure(self.run_diagnostic("second_failure"), "native", 2)
        self.assertEqual(self.result["attempts"][0]["tests_passed"], 31)
        self.assertFalse((self.output / "attempt-3").exists())

    def test_signal_exit_is_recorded_without_xml(self):
        self.assert_failure(self.run_diagnostic("signal"), "native", 1)
        self.assertEqual(self.result["attempts"][0]["returncode"], -15)
        self.assertEqual(self.result["attempts"][0]["shell_exit_code"], 143)
        self.assertFalse(self.result["attempts"][0]["xml_present"])

    def test_zero_exit_with_missing_xml_is_gating(self):
        self.assert_failure(self.run_diagnostic("missing_xml"), "native", 1)
        self.assertFalse(self.result["attempts"][0]["xml_present"])
        self.assertFalse((self.output / "attempt-2").exists())

    def test_invalid_or_incomplete_xml_is_gating(self):
        for mode in ("malformed_xml", "empty_xml", "partial_xml", "extra_xml", "failed_xml",
                     "error_xml", "skipped_xml", "notrun_xml", "wrong_root_xml"):
            with self.subTest(mode=mode):
                # Each case owns fresh artifacts, so a stale XML cannot satisfy a later run.
                self.output = self.root / mode
                self.assert_failure(self.run_diagnostic(mode), "native", 1)
                self.assertFalse((self.output / "attempt-2").exists())

    def test_source_modified_during_build_prevents_native_execution(self):
        self.assert_failure(self.run_diagnostic("modified_source"), "source_verification", 0)
        self.assertFalse((self.source / "native-count").exists())

    def test_source_modified_during_native_is_gating(self):
        self.assert_failure(self.run_diagnostic("modified_during_native"), "native", 3)

    def test_failed_control_does_not_prevent_separate_control(self):
        self.assert_failure(self.run_diagnostic("build_failure"), "build", 0)
        failed_output = self.output
        self.source = self.root / "candidate"
        self.source.mkdir()
        self.executable(self.source / ".claude/commands/build-and-summarize", WRAPPER)
        self.output = self.root / "candidate-evidence"
        completed = self.run_diagnostic(repetitions=1)
        self.assertEqual(completed.returncode, 0, completed.stderr)
        self.assertEqual(self.result["attempts"][0]["tests_passed"], 31)
        self.assertEqual(json.loads((failed_output / "result.json").read_text())["build_exit_code"], 17)

    def test_log_collection_failure_cannot_pass(self):
        stderr = io.StringIO()
        with patch.dict(os.environ, self.environment), patch.object(DIAGNOSTIC, "collect_logs", side_effect=OSError("log copy failed")), patch("sys.stderr", stderr):
            status = DIAGNOSTIC.diagnose(self.source, SHA, self.output, 1)
        self.assertEqual(status, 1)
        self.assertIn("Failed to retain build/daemon logs: log copy failed", stderr.getvalue())
        result = json.loads((self.output / "result.json").read_text())
        self.assertEqual(result["status"], "failed")
        self.assertEqual(result["log_collection_error"], "log copy failed")
        self.assertEqual(result["attempts"][0]["tests_passed"], 31)


if __name__ == "__main__":
    unittest.main()
