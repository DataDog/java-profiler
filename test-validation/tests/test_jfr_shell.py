#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Regression tests for repository routing and conformance orchestration."""

import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class JfrShellTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.directory = Path(self.tmp.name)
        self.calls = self.directory / "calls.jsonl"
        self.recording = self.directory / 'recording with spaces; $name.jfr'
        self.recording.touch()
        jbang = self.directory / "jbang"
        jbang.write_text("""#!/usr/bin/env python3
import json, os, sys
args = sys.argv[1:]
with open(os.environ['JBANG_CALLS'], 'a') as log:
    log.write(json.dumps(args) + '\\n')
command = 'metadata' if 'metadata' in args else 'script'
if os.environ.get('JBANG_FAIL') == command:
    sys.exit(1)
if command == 'metadata':
    print('- datadog.ExecutionSample\\n- datadog.ObjectSample')
else:
    print('SUCCESS: All validations passed')
""")
        jbang.chmod(0o755)
        self.env = dict(os.environ, PATH=f"{self.directory}:{os.environ['PATH']}", JBANG_CALLS=str(self.calls))
        self.env.pop("MAVEN_REPOSITORY_PROXY", None)

    def run_script(self, path, *args):
        return subprocess.run(["bash", str(ROOT / path), *map(str, args)], env=self.env, capture_output=True, text=True)

    def read_calls(self):
        return [json.loads(line) for line in self.calls.read_text().splitlines()]

    def test_proxy_routes_shell_and_backend_together(self):
        self.env["MAVEN_REPOSITORY_PROXY"] = "https://depot.example/mirror/@current/"
        result = self.run_script("test-validation/jfr-shell.sh", "metadata", self.recording)
        self.assertEqual(result.returncode, 0, result.stderr)
        args, = self.read_calls()
        self.assertEqual(args[args.index("--repos") + 1], "central=" + self.env["MAVEN_REPOSITORY_PROXY"])
        self.assertIn("--ignore-transitive-repositories", args)
        shell = next(arg for arg in args if arg.startswith("io.btrace:jafar-shell:"))
        self.assertEqual(args[args.index("--deps") + 1], shell.replace(":jafar-shell:", ":jfr-shell-jafar:"))
        self.assertFalse(any("@btraceio" in arg for arg in args))
        self.assertEqual(args[-2:], ["metadata", str(self.recording)])

    def test_unconfigured_local_build_keeps_default_repository(self):
        for value in (None, ""):
            with self.subTest(value=value):
                if value is not None:
                    self.env["MAVEN_REPOSITORY_PROXY"] = value
                result = self.run_script("test-validation/jfr-shell.sh", "script", "/dev/null")
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertNotIn("--repos", self.read_calls()[-1])

    def test_conformance_preserves_arguments_and_output_modes(self):
        for use_output in (False, True):
            with self.subTest(use_output=use_output):
                self.calls.unlink(missing_ok=True)
                self.env["MAVEN_REPOSITORY_PROXY"] = "https://depot.example/mirror/@current/"
                output = self.directory / "validation output.log"
                options = [f"--output={output}"] if use_output else []
                result = self.run_script("test-validation/validate-jfr-conformance.sh", self.recording, "--ddprof-enabled=true", *options)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                metadata, validation = self.read_calls()
                self.assertEqual(metadata[:metadata.index("metadata")], validation[:validation.index("script")])
                script_args = validation[validation.index("script") + 1:]
                self.assertEqual(script_args[1], str(self.recording))
                self.assertEqual(script_args[2], "ddprof_only")
                self.assertEqual(len(script_args), 20)
                self.assertEqual(script_args[-6:], ["false", "true", "false", "true", "false", "false"])
                if use_output:
                    self.assertIn("SUCCESS:", output.read_text())

    def test_metadata_failure_preserves_fallback(self):
        self.env["JBANG_FAIL"] = "metadata"
        result = self.run_script("test-validation/validate-jfr-conformance.sh", self.recording)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(self.read_calls()[-1][-6:], ["true"] * 6)

    def test_validation_failure_is_not_a_pass(self):
        self.env["JBANG_FAIL"] = "script"
        output = self.directory / "failed validation.log"
        result = self.run_script("test-validation/validate-jfr-conformance.sh", self.recording, f"--output={output}")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("VALIDATION_FAILED", output.read_text())

    def test_missing_recording_is_a_configuration_error(self):
        result = self.run_script("test-validation/validate-jfr-conformance.sh", self.directory / "missing.jfr")
        self.assertEqual(result.returncode, 2)
        self.assertFalse(self.calls.exists())


if __name__ == "__main__":
    unittest.main()
