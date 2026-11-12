#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.

import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import signal
import stat
import subprocess
import sys
import tempfile
import textwrap
import time
import unittest
from unittest.mock import patch
import zipfile


SCRIPT = Path(__file__).resolve().parents[1] / "pr932_elf_replay.py"
SPEC = importlib.util.spec_from_file_location("replay", SCRIPT)
REPLAY = importlib.util.module_from_spec(SPEC)
with patch.object(sys, "path", [str(SCRIPT.parent), *sys.path]):
    SPEC.loader.exec_module(REPLAY)

FAKE_SUITE = r'''
import hashlib
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time
build = Path.cwd()
actions = Path(os.environ["REPLAY_ACTIONS"])
previous = actions.read_text().splitlines() if actions.exists() else []
index = len(previous) + 1
fixtures = [build / "test/resources/native-libs" / name for name in
            ("unresolved-functions/main", "reladyn-lib/libreladyn.so", "small-lib/libsmall-lib.so")]
observation = {"index": index, "control": build.parent.name, "cwd": str(build), "pid": os.getpid(),
               "arguments": sys.argv[1:], "helper_executable": os.access(fixtures[0], os.X_OK),
               "fixture_hashes": [hashlib.sha256(path.read_bytes()).hexdigest() for path in fixtures],
               "environment": {key: os.environ[key] for key in
                               ("TEST_COMMIT", "TSAN_OPTIONS", "GTEST_DEATH_TEST_STYLE",
                                "GTEST_FILTER", "GTEST_REPEAT")}}
with actions.open("a") as log:
    log.write(json.dumps(observation) + "\n")
print("fake stdout " + str(index), flush=True)
print("fake stderr " + str(index), file=sys.stderr, flush=True)
xml = Path(sys.argv[1].split("xml:", 1)[1])
mode = os.environ.get("REPLAY_MODE", "") if index == 1 else ""
if mode == "signal":
    os.kill(os.getpid(), signal.SIGTERM)
if mode in ("timeout", "leftover"):
    child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(60)"])
    Path(os.environ["CHILD_PID"]).write_text(str(child.pid))
    if mode == "timeout":
        time.sleep(60)
if mode == "no_xml":
    sys.exit(0)
if mode == "bad_xml":
    xml.write_text("<broken>")
    sys.exit(0)
if mode == "xml_symlink":
    xml.symlink_to(fixtures[0])
    sys.exit(0)
if mode == "output_missing":
    xml.with_name("stdout.txt").unlink()
count = 30 if mode == "partial_xml" else 32 if mode == "extra_xml" else 31
marker = {"failed_xml": "<failure/>", "error_xml": "<error/>", "skipped_xml": "<skipped/>"}.get(mode, "")
status = ' status="notrun"' if mode == "notrun_xml" else ''
xml.write_text('<testsuites><testsuite>' + ''.join(
    '<testcase name="case' + str(i) + '"' + status + '>' + (marker if i == 0 else '') + '</testcase>'
    for i in range(count)) + '</testsuite></testsuites>')
if mode == "warning":
    print("WARNING: ThreadSanitizer: data race", file=sys.stderr)
if mode == "mutation":
    fixtures[2].write_text("changed after execution")
if mode == "inode_mutation":
    saved = fixtures[2].read_bytes()
    replacement = fixtures[2].with_suffix(".replacement")
    replacement.write_bytes(saved)
    replacement.replace(fixtures[2])
if mode == "nonzero":
    sys.exit(134)
'''


def digest(content):
    return hashlib.sha256(content).hexdigest()


class ElfReplayTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="elf replay ")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.archive = self.root / "producer.zip"
        self.metadata = self.root / "metadata.json"
        self.suppression = self.root / "tsan.supp"
        self.output = self.root / "evidence"
        self.suppression.write_text("unchanged suppression fixture\n")
        self.actions = self.root / "actions.jsonl"
        self.environment = dict(os.environ, REPLAY_ACTIONS=str(self.actions),
                                CHILD_PID=str(self.root / "child.pid"),
                                GTEST_FILTER="must be replaced", GTEST_REPEAT="7")
        self.files = {}
        self.hashes = {}
        for label, pin in REPLAY.SOURCE_PINS.items():
            payloads = {REPLAY.BINARY: (f"#!{sys.executable}\n" + FAKE_SUITE).encode(),
                        **{name: (name + " fixture\n").encode() for name in REPLAY.FIXTURES}}
            self.hashes[label] = {name: digest(content) for name, content in payloads.items()}
            for name, content in payloads.items():
                self.files[f"{label}/native/{name}"] = content
            manifest = {"actual_sha": pin, "expected_sha": pin, "build_exit_code": 0,
                        "binary_sha256": self.hashes[label][REPLAY.BINARY],
                        "status": "failed" if label == "candidate" else "passed"}
            self.files[f"{label}/result.json"] = json.dumps(manifest).encode()
        self.metadata_value = {"id": REPLAY.ARTIFACT_ID, "name": REPLAY.ARTIFACT_NAME, "expired": False,
                               "digest": "sha256:" + REPLAY.ARCHIVE_SHA256,
                               "workflow_run": {"id": REPLAY.PRODUCER_RUN, "repository_id": 585532470,
                                                "head_repository_id": 585532470,
                                                "head_branch": REPLAY.BRANCH, "head_sha": REPLAY.PRODUCER_HEAD}}
        self.save_inputs()

    def save_inputs(self, special=None):
        self.metadata.write_text(json.dumps(self.metadata_value))
        with zipfile.ZipFile(self.archive, "w") as bundle:
            for name, content in self.files.items():
                member = zipfile.ZipInfo(name)
                member.external_attr = (stat.S_IFREG | 0o644) << 16
                if special and name == special[0]:
                    member.external_attr = special[1] << 16
                bundle.writestr(member, content)
        self.archive_hash = digest(self.archive.read_bytes())

    def run_replay(self, mode="", timeout=3, **kwargs):
        stderr = io.StringIO()
        with patch.dict(os.environ, dict(self.environment, REPLAY_MODE=mode), clear=True), patch("sys.stderr", stderr):
            status = REPLAY.replay(self.archive, self.metadata, self.output, self.suppression,
                                   payload_hashes=self.hashes, archive_sha256=self.archive_hash,
                                   suppression_sha256=digest(b"unchanged suppression fixture\n"),
                                   timeout=timeout, **kwargs)
        self.stderr = stderr.getvalue()
        result_path = self.output / "result.json"
        self.result = json.loads(result_path.read_text()) if result_path.is_file() else None
        self.observed = [json.loads(line) for line in self.actions.read_text().splitlines()] if self.actions.exists() else []
        return status

    def assert_stopped(self, status, launches=0):
        self.assertEqual(status, 1)
        self.assertEqual(self.result["status"], "failed")
        self.assertEqual(len(self.observed), launches)
        self.assertIn("ELF replay stopped", self.stderr)
        self.assertTrue(all(attempt["status"] == "not_attempted"
                            for attempt in self.result["attempts"][launches:]))
        self.assertTrue(all(attempt.get("reason") for attempt in self.result["attempts"][launches:]))

    def test_exact_twenty_counterbalanced_launches_cwd_environment_and_artifacts(self):
        self.assertEqual(self.run_replay(), 0, self.stderr)
        self.assertEqual(self.result["status"], "passed")
        expected_order = ["base", "candidate", "candidate", "base"] * 5
        self.assertEqual([action["control"] for action in self.observed], expected_order)
        self.assertEqual(len(self.observed), 20)
        self.assertEqual(sum(action["control"] == "base" for action in self.observed), 10)
        for action, attempt in zip(self.observed, self.result["attempts"]):
            label = action["control"]
            build = self.output / "producer" / label / "native"
            self.assertEqual(action["cwd"], str(build))
            self.assertEqual(action["environment"], {
                "TEST_COMMIT": REPLAY.SOURCE_PINS[label], "TSAN_OPTIONS": REPLAY.TSAN_PREFIX + str(self.suppression),
                "GTEST_DEATH_TEST_STYLE": "threadsafe", "GTEST_FILTER": "*", "GTEST_REPEAT": "1"})
            self.assertTrue(action["helper_executable"])
            self.assertEqual(action["fixture_hashes"], [self.hashes[label][name] for name in REPLAY.FIXTURES])
            attempt_dir = self.output / f"attempt-{action['index']:02d}-{label}"
            self.assertEqual(action["arguments"], [f"--gtest_output=xml:{attempt_dir}/elfparser.xml"])
            self.assertEqual(attempt["command"][0], str(build / REPLAY.BINARY))
            self.assertEqual((attempt_dir / "stdout.txt").read_text(), f"fake stdout {action['index']}\n")
            self.assertEqual((attempt_dir / "stderr.txt").read_text(), f"fake stderr {action['index']}\n")
            self.assertEqual(json.loads((attempt_dir / "result.json").read_text()), attempt)
            self.assertEqual(attempt["tests_passed"], 31)
            self.assertEqual(attempt["status"], "passed")
            self.assertEqual(attempt["pid"], action["pid"])
            self.assertLessEqual(attempt["scheduled_unix_ns"], attempt["started_unix_ns"])
            self.assertLess(attempt["started_monotonic_ns"], attempt["ended_monotonic_ns"])
            self.assertEqual(attempt["shell_exit_code"], 0)
            for payload in attempt["payloads"]:
                self.assertEqual(payload["sha256"], digest(Path(payload["path"]).read_bytes()))
                self.assertEqual(payload["inode"], Path(payload["path"]).stat().st_ino)
        verified = json.loads((self.output / "verified-inputs.json").read_text())
        self.assertTrue(all(item["mode"] == "0o644" for item in verified if "/native/" in item["path"]))
        restored = self.result["mode_restorations"]
        self.assertEqual(len(restored), 4)
        self.assertTrue(all(item["after"]["mode"] == "0o755" for item in restored))
        for label in REPLAY.SOURCE_PINS:
            library = self.output / "producer" / label / "native/test/resources/native-libs/reladyn-lib/libreladyn.so"
            self.assertEqual(stat.S_IMODE(library.stat().st_mode), 0o644)
        self.assertNotIn("build_exit_code", self.result)

    def test_native_failures_continue_all_scheduled_counterparts_and_never_pass(self):
        for mode in ("nonzero", "signal", "no_xml", "bad_xml", "partial_xml", "extra_xml",
                     "failed_xml", "error_xml", "skipped_xml", "notrun_xml", "warning"):
            with self.subTest(mode=mode):
                self.output = self.root / mode
                self.actions = self.root / (mode + ".jsonl")
                self.environment["REPLAY_ACTIONS"] = str(self.actions)
                self.assertEqual(self.run_replay(mode), 1)
                self.assertEqual(self.result["stage"], "complete")
                self.assertEqual(self.result["status"], "failed")
                self.assertEqual([action["control"] for action in self.observed],
                                 ["base", "candidate", "candidate", "base"] * 5)
                first = self.result["attempts"][0]
                self.assertEqual(first["status"], "failed")
                self.assertTrue(first["errors"])
                self.assertTrue(all(attempt["status"] == "passed" for attempt in self.result["attempts"][1:]))
                self.assertTrue((self.output / "attempt-01-base/stderr.txt").is_file())
                if mode == "nonzero":
                    self.assertEqual(first["tests_passed"], 31)
                    self.assertEqual(first["shell_exit_code"], 134)
                elif mode == "signal":
                    self.assertEqual(first["returncode"], -signal.SIGTERM)
                    self.assertEqual(first["signal"], signal.SIGTERM)
                    self.assertEqual(first["shell_exit_code"], 143)
                    self.assertFalse(first["xml_present"])
                elif mode == "warning":
                    self.assertEqual(first["tests_passed"], 31)
                    self.assertIn("TSan report in stderr.txt", first["errors"])

    def test_provenance_fields_reject_mismatch_before_modes_or_execution(self):
        mutations = (("id", 0), ("name", "other"), ("expired", True), ("digest", "sha256:wrong"),
                     ("workflow_run.id", 0), ("workflow_run.repository_id", 0),
                     ("workflow_run.head_repository_id", 0), ("workflow_run.head_branch", "other"),
                     ("workflow_run.head_sha", "0" * 40))
        original = json.dumps(self.metadata_value)
        for index, (field, value) in enumerate(mutations):
            with self.subTest(field=field):
                self.output = self.root / f"provenance-{index}"
                self.metadata_value = json.loads(original)
                container = self.metadata_value
                parts = field.split(".")
                for key in parts[:-1]:
                    container = container[key]
                container[parts[-1]] = value
                self.save_inputs()
                with patch.object(Path, "chmod", side_effect=AssertionError("chmod before verification")):
                    self.assert_stopped(self.run_replay())
                self.assertIn("pinned producer", self.result["error"])

    def test_missing_or_malformed_metadata_is_integrity_failure(self):
        for index, content in enumerate(("[]", "{}", "{")):
            with self.subTest(content=content):
                self.output = self.root / f"metadata-{index}"
                self.metadata.write_text(content)
                self.assert_stopped(self.run_replay())

    def test_actual_downloaded_zip_and_suppression_bytes_are_verified(self):
        self.archive.write_bytes(self.archive.read_bytes() + b"changed")
        self.assert_stopped(self.run_replay())
        self.assertIn("ZIP hash mismatch", self.result["error"])
        self.save_inputs()
        self.output = self.root / "suppression-error"
        self.suppression.write_text("tampered")
        self.assert_stopped(self.run_replay())
        self.assertIn("suppression hash mismatch", self.result["error"])

    def test_every_binary_and_fixture_hash_is_checked_before_any_mode_restoration(self):
        for label in REPLAY.SOURCE_PINS:
            for name in self.hashes[label]:
                with self.subTest(label=label, name=name):
                    key = f"{label}/native/{name}"
                    saved = self.files[key]
                    self.files[key] = saved + b"tampered"
                    self.output = self.root / (label + "-" + Path(name).name)
                    self.save_inputs()
                    with patch.object(Path, "chmod", side_effect=AssertionError("chmod before verification")):
                        self.assert_stopped(self.run_replay())
                    self.assertIn("Payload hash mismatch", self.result["error"])
                    self.files[key] = saved

    def test_retained_manifests_require_both_source_pins_build_zero_and_binary_hash(self):
        for label in REPLAY.SOURCE_PINS:
            for field, value in (("expected_sha", "wrong"), ("actual_sha", "wrong"),
                                 ("build_exit_code", 3), ("build_exit_code", False),
                                 ("binary_sha256", "wrong")):
                with self.subTest(label=label, field=field, value=value):
                    key = f"{label}/result.json"
                    saved = self.files[key]
                    manifest = json.loads(saved)
                    manifest[field] = value
                    self.files[key] = json.dumps(manifest).encode()
                    self.output = self.root / (label + field + str(value))
                    self.save_inputs()
                    self.assert_stopped(self.run_replay())
                    self.assertIn("source/build manifest", self.result["error"])
                    self.files[key] = saved

    def test_missing_and_unexpected_payloads_are_integrity_failures(self):
        for index, name in enumerate(list(self.files)):
            with self.subTest(name=name):
                saved = self.files.pop(name)
                self.save_inputs()
                self.output = self.root / f"missing-{index}"
                self.assert_stopped(self.run_replay())
                self.files[name] = saved
        self.files["base/native/unexpected.so"] = b"unverified"
        self.save_inputs()
        self.output = self.root / "unexpected"
        self.assert_stopped(self.run_replay())
        self.assertIn("unexpected native payload", self.result["error"])

    def test_symlink_archive_metadata_suppression_and_ancestor_are_rejected(self):
        for attribute in ("archive", "metadata", "suppression"):
            with self.subTest(attribute=attribute):
                saved = getattr(self, attribute)
                alias = self.root / (attribute + "-symlink")
                alias.symlink_to(saved)
                setattr(self, attribute, alias)
                self.output = self.root / (attribute + "-result")
                self.assert_stopped(self.run_replay())
                self.assertIn("Symlink", self.result["error"])
                setattr(self, attribute, saved)
        alias = self.root / "ancestor"
        alias.symlink_to(self.root, target_is_directory=True)
        self.archive = alias / self.archive.name
        self.output = self.root / "ancestor-result"
        self.assert_stopped(self.run_replay())

    def test_unsafe_zip_symlink_traversal_and_special_members_are_rejected(self):
        for index, special in enumerate((stat.S_IFLNK | 0o777, stat.S_IFIFO | 0o644)):
            with self.subTest(special=special):
                self.output = self.root / f"unsafe-{index}"
                self.save_inputs((f"base/native/{REPLAY.BINARY}", special))
                self.assert_stopped(self.run_replay())
                self.assertIn("Unsafe", self.result["error"])
        for index, name in enumerate(("../escape", "/absolute", "base\\escape")):
            with self.subTest(name=name):
                self.files[name] = b"escape"
                self.save_inputs()
                self.output = self.root / f"traversal-{index}"
                self.assert_stopped(self.run_replay())
                self.files.pop(name)
        self.assertFalse((self.root / "escape").exists())

    def test_payload_content_or_inode_mutation_stops_remaining_launches(self):
        for mode in ("mutation", "inode_mutation"):
            with self.subTest(mode=mode):
                self.output = self.root / mode
                self.actions = self.root / (mode + ".jsonl")
                self.environment["REPLAY_ACTIONS"] = str(self.actions)
                self.assert_stopped(self.run_replay(mode), launches=1)
                self.assertIn("Input mutation", self.result["error"])
                self.assertTrue((self.output / "attempt-01-base/elfparser.xml").exists())

    def test_foreign_owned_or_special_mode_inputs_are_not_executed(self):
        with patch.object(REPLAY.os, "getuid", return_value=os.getuid() + 1):
            self.assert_stopped(self.run_replay())
        self.assertIn("must be owned", self.result["error"])
        original_stat = Path.stat
        def special_stat(path, *args, **kwargs):
            info = original_stat(path, *args, **kwargs)
            if path == self.suppression:
                fields = list(info)
                fields[0] |= stat.S_ISUID
                return os.stat_result(fields)
            return info
        self.output = self.root / "special-mode"
        with patch.object(Path, "stat", special_stat):
            self.assert_stopped(self.run_replay())
        self.assertIn("no special mode bits", self.result["error"])

    def test_broken_zip_and_duplicate_paths_are_rejected_without_execution(self):
        self.archive.write_bytes(b"not a ZIP")
        self.archive_hash = digest(self.archive.read_bytes())
        self.assert_stopped(self.run_replay())
        self.assertIn("not a zip file", self.result["error"])
        self.save_inputs()
        with self.assertWarns(UserWarning), zipfile.ZipFile(self.archive, "a") as bundle:
            bundle.writestr("base/result.json", self.files["base/result.json"])
        self.archive_hash = digest(self.archive.read_bytes())
        self.output = self.root / "duplicate-path"
        self.assert_stopped(self.run_replay())
        self.assertIn("duplicate artifact entry", self.result["error"])

    def test_mutation_during_mode_restoration_cannot_become_the_new_expected_hash(self):
        chmod = Path.chmod
        def mutate_after_chmod(path, mode):
            chmod(path, mode)
            if str(path).endswith(REPLAY.BINARY):
                path.write_bytes(path.read_bytes() + b"changed during chmod")
        with patch.object(Path, "chmod", mutate_after_chmod):
            self.assert_stopped(self.run_replay())
        self.assertIn("mutation during mode restoration", self.result["error"])

    def test_required_output_loss_or_symlink_stops_remaining_launches(self):
        for mode in ("output_missing", "xml_symlink"):
            with self.subTest(mode=mode):
                self.output = self.root / mode
                self.actions = self.root / (mode + ".jsonl")
                self.environment["REPLAY_ACTIONS"] = str(self.actions)
                self.assert_stopped(self.run_replay(mode), launches=1)
                first = self.result["attempts"][0]
                self.assertEqual(first["returncode"], 0)
                self.assertEqual(first["status"], "failed")
                process = json.loads((self.output / "attempt-01-base/process.json").read_text())
                self.assertEqual(process["returncode"], 0)

    def test_required_initial_and_verified_input_writes_gate_before_execution(self):
        writer = REPLAY.write_json
        for name in ("result.json", "verified-inputs.json"):
            with self.subTest(name=name):
                self.output = self.root / name
                def blocked_write(path, value):
                    if path == self.output / name and not path.exists():
                        path.mkdir()
                    writer(path, value)
                with patch.object(REPLAY, "write_json", side_effect=blocked_write):
                    self.assertEqual(self.run_replay(), 1)
                self.assertEqual(self.observed, [])
                self.assertFalse((self.output / "attempt-01-base").exists())

    def test_required_per_attempt_result_write_stops_before_next_counterpart(self):
        writer = REPLAY.write_json
        def blocked_write(path, value):
            if path == self.output / "attempt-01-base/result.json":
                path.mkdir()
            writer(path, value)
        with patch.object(REPLAY, "write_json", side_effect=blocked_write):
            self.assert_stopped(self.run_replay(), launches=1)
        self.assertIn("Is a directory", self.result["error"])

    def assert_processes_stopped(self, pids):
        for pid in pids:
            deadline = time.monotonic() + 3
            while time.monotonic() < deadline:
                status = subprocess.run(["ps", "-o", "stat=", "-p", str(pid)], text=True, capture_output=True)
                if status.returncode or status.stdout.strip().startswith("Z"):
                    break
                time.sleep(0.02)
            else:
                self.fail(f"Process survived cleanup: {pid}")

    def test_timeout_kills_suite_and_child_and_labels_rest_unattempted(self):
        self.assert_stopped(self.run_replay("timeout", timeout=0.5), launches=1)
        first = self.result["attempts"][0]
        self.assertTrue(first["timed_out"])
        self.assertEqual(first["returncode"], -signal.SIGKILL)
        self.assertFalse(first["xml_present"])
        self.assertIn("timeout", self.result["error"])
        self.assert_processes_stopped((first["pid"], int((self.root / "child.pid").read_text())))

    def test_surviving_child_is_killed_and_stops_experiment_without_retry(self):
        self.assert_stopped(self.run_replay("leftover"), launches=1)
        first = self.result["attempts"][0]
        self.assertFalse(first["timed_out"])
        self.assertTrue(first["leftover_processes"])
        self.assertIn("Surviving suite children", first["errors"])
        self.assert_processes_stopped((int((self.root / "child.pid").read_text()),))

    def test_existing_output_is_not_overwritten_or_reused(self):
        self.output.mkdir()
        saved = self.output / "result.json"
        saved.write_text('{"status":"prior evidence"}')
        self.assertEqual(self.run_replay(), 1)
        self.assertEqual(self.result, {"status": "prior evidence"})
        self.assertEqual(self.observed, [])

    def test_production_cli_rejects_local_execution_and_has_no_hash_override(self):
        environment = {key: value for key, value in os.environ.items() if not key.startswith("GITHUB_")}
        completed = subprocess.run([sys.executable, str(SCRIPT), str(self.archive), str(self.metadata),
                                    str(self.output)], env=environment, text=True, capture_output=True)
        self.assertEqual(completed.returncode, 1)
        self.assertIn("restricted to the diagnostic CI branch", completed.stderr)
        self.assertFalse(self.output.exists())
        environment.update(GITHUB_ACTIONS="true", GITHUB_REPOSITORY="DataDog/java-profiler",
                           GITHUB_REF="refs/heads/" + REPLAY.BRANCH)
        completed = subprocess.run([sys.executable, str(SCRIPT), "--skip-hash", str(self.archive),
                                    str(self.metadata), str(self.output)], env=environment,
                                   text=True, capture_output=True)
        self.assertEqual(completed.returncode, 1)
        self.assertIn("Usage:", completed.stderr)
        self.assertFalse(self.output.exists())


class ReplayWorkflowTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="replay workflow ")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.tools = self.root / "tools"
        self.tools.mkdir()
        self.workflow = (SCRIPT.parents[1] / "workflows/pr932-regression-diagnostic.yml").read_text()
        self.environment = dict(os.environ, PATH=str(self.tools) + os.pathsep + os.environ["PATH"],
                                GH_TOKEN="hermetic-token-not-for-output")
        for command in ("gh", "python3"):
            path = self.tools / command
            path.write_text(f"#!{sys.executable}\n" + r'''
import json
import os
from pathlib import Path
import sys
command = Path(sys.argv[0]).name
arguments = sys.argv[1:]
with Path("calls.jsonl").open("a") as log:
    log.write(json.dumps({"command": command, "arguments": arguments,
                          "token_present": "GH_TOKEN" in os.environ}) + "\n")
if command == "gh":
    is_zip = arguments[-1].endswith("/zip")
    sys.stdout.buffer.write(b"fake ZIP bytes" if is_zip else b'{"producer":"metadata"}')
    sys.exit(9 if os.environ.get("FAIL_DOWNLOAD") == ("zip" if is_zip else "metadata") else 0)
sys.exit(int(os.environ.get("REPLAY_EXIT", "0")))
''')
            path.chmod(0o755)

    def block(self, name):
        block = self.workflow.split("      - name: " + name + "\n", 1)[1].split("\n      - name:", 1)[0]
        return textwrap.dedent(block.split("        run: |\n", 1)[1])

    def run_block(self, block, **environment):
        return subprocess.run(["bash", "--noprofile", "--norc", "-e", "-o", "pipefail", "-c", block],
                              cwd=self.work, env=dict(self.environment, **environment), text=True,
                              capture_output=True)

    def test_download_uses_only_pinned_artifact_endpoints_and_required_writes(self):
        block = self.block("Download immutable producer artifact")
        for mode in ("success", "metadata", "zip", "blocked-metadata", "blocked-zip"):
            with self.subTest(mode=mode):
                self.work = self.root / mode
                (self.work / "diagnostic").mkdir(parents=True)
                if mode.startswith("blocked-"):
                    (self.work / "diagnostic" / ("producer.zip" if mode.endswith("zip")
                                                 else "producer-metadata.json")).mkdir()
                completed = self.run_block(block + "\nprintf reached > reached\n", FAIL_DOWNLOAD=mode)
                calls_path = self.work / "calls.jsonl"
                calls = [json.loads(line) for line in calls_path.read_text().splitlines()] if calls_path.exists() else []
                expected_count = 0 if mode == "blocked-metadata" else 1 if mode in ("metadata", "blocked-zip") else 2
                self.assertEqual(len(calls), expected_count)
                for index, call in enumerate(calls):
                    endpoint = "repos/DataDog/java-profiler/actions/artifacts/13965627960" + ("/zip" if index else "")
                    self.assertEqual(call, {"command": "gh", "arguments": ["api", endpoint], "token_present": True})
                self.assertEqual((self.work / "reached").exists(), mode == "success")
                self.assertEqual(completed.returncode == 0, mode == "success", completed.stderr)
                self.assertNotIn("hermetic-token", completed.stdout + completed.stderr)
                if mode == "success":
                    self.assertEqual((self.work / "diagnostic/producer.zip").read_bytes(), b"fake ZIP bytes")
                    self.assertEqual(json.loads((self.work / "diagnostic/producer-metadata.json").read_text()),
                                     {"producer": "metadata"})

    def runtime_block(self):
        name = "Record current replay runtime"
        marker = "      - name: " + name + "\n"
        self.assertIn(marker, self.workflow, "Current-runtime evidence step is required")
        self.assertLess(self.workflow.index("      - name: Setup ordinary glibc debug dependencies\n"),
                        self.workflow.index(marker))
        self.assertLess(self.workflow.index(marker), self.workflow.index(
            "      - name: Replay retained ELF suites in fixed counterbalanced order\n"))
        return self.block(name)

    def runtime_tools(self):
        self.environment.pop("GH_TOKEN")
        for command in ("dpkg-query", "ldd", "readelf", "sha256sum"):
            path = self.tools / command
            path.write_text(f"#!{sys.executable}\n" + r'''
import json
import os
from pathlib import Path
import sys
command = Path(sys.argv[0]).name
subject = sys.argv[-1] if command == "dpkg-query" else command
with Path("calls.jsonl").open("a") as log:
    log.write(json.dumps({"command": command, "arguments": sys.argv[1:],
                          "subject": subject, "token_present": "GH_TOKEN" in os.environ}) + "\n")
if subject in os.environ.get("FAIL_RUNTIME", "").split(","):
    print(subject + ": probe failed", file=sys.stderr)
    sys.exit(7)
if command == "dpkg-query":
    versions = {"libc6": "2.43-test.7", "libc6-dbg": "2.43-test.7",
                "libstdc++6": "15.3-test.2", "libgcc-s1": "15.3-test.2"}
    print(subject + "=" + versions[subject] + " architecture=amd64")
elif command == "ldd":
    print("ldd (Ubuntu GLIBC) 2.43-test.7")
elif command == "readelf":
    print("Build ID: fake-current-loader-identity")
else:
    print("fake-current-loader-digest  /lib64/ld-linux-x86-64.so.2")
''')
            path.chmod(0o755)

    def test_current_runtime_records_actual_post_setup_observations(self):
        block = self.runtime_block()
        self.runtime_tools()
        self.work = self.root / "runtime-readable"
        (self.work / "diagnostic").mkdir(parents=True)
        completed = self.run_block(block)
        self.assertEqual(completed.returncode, 0, completed.stderr)
        metadata = (self.work / "diagnostic/replay-runtime.txt").read_text()
        self.assertIn("observation=current replay runtime after dependency setup", metadata)
        for value in ("libc6=2.43-test.7", "libc6-dbg=2.43-test.7", "libstdc++6=15.3-test.2",
                      "libgcc-s1=15.3-test.2", "ldd (Ubuntu GLIBC) 2.43-test.7",
                      "Build ID: fake-current-loader-identity", "fake-current-loader-digest"):
            self.assertIn(value, metadata)
        self.assertNotIn("unavailable/unverified", metadata)
        calls = [json.loads(line) for line in (self.work / "calls.jsonl").read_text().splitlines()]
        self.assertEqual([call["subject"] for call in calls],
                         ["libc6", "libc6-dbg", "libstdc++6", "libgcc-s1", "ldd", "readelf", "sha256sum"])
        for call in calls[:4]:
            self.assertEqual(call["arguments"], ["-W", "-f=${binary:Package}=${Version} "
                "architecture=${Architecture} source=${source:Package} source-version=${source:Version}\\n",
                call["subject"]])
        self.assertEqual(calls[4]["arguments"], ["--version"])
        self.assertEqual(calls[5]["arguments"], ["-n", "/lib64/ld-linux-x86-64.so.2"])
        self.assertEqual(calls[6]["arguments"], ["/lib64/ld-linux-x86-64.so.2"])
        self.assertTrue(all(not call["token_present"] for call in calls))
        self.assertEqual(completed.stdout + completed.stderr, "")

    def test_current_runtime_unavailable_probes_are_explicit_and_do_not_skip_later_probes(self):
        block = self.runtime_block()
        self.runtime_tools()
        markers = {package: "package " + package for package in
                   ("libc6", "libc6-dbg", "libstdc++6", "libgcc-s1")}
        markers.update(ldd="ldd version", readelf="loader notes/build ID", sha256sum="loader SHA256")
        for index, failures in enumerate(("libc6-dbg,readelf", ",".join(markers))):
            with self.subTest(failures=failures):
                self.work = self.root / f"runtime-unavailable-{index}"
                (self.work / "diagnostic").mkdir(parents=True)
                completed = self.run_block(block + "\nprintf reached > reached\n", FAIL_RUNTIME=failures)
                self.assertEqual(completed.returncode, 0, completed.stderr)
                self.assertTrue((self.work / "reached").exists())
                metadata = (self.work / "diagnostic/replay-runtime.txt").read_text()
                for probe, marker in markers.items():
                    self.assertEqual(marker + ": unavailable/unverified" in metadata, probe in failures.split(","))
                calls = [json.loads(line) for line in (self.work / "calls.jsonl").read_text().splitlines()]
                self.assertEqual([call["subject"] for call in calls], list(markers))
                self.assertEqual(completed.stdout + completed.stderr, "")

    def test_current_runtime_required_artifact_write_failure_stops_before_probes(self):
        block = self.runtime_block()
        self.runtime_tools()
        self.work = self.root / "runtime-blocked-write"
        self.work.mkdir()
        (self.work / "diagnostic").write_text("not a directory")
        completed = self.run_block(block + "\nprintf reached > reached\n")
        self.assertNotEqual(completed.returncode, 0)
        self.assertIn("diagnostic/replay-runtime.txt", completed.stderr)
        self.assertFalse((self.work / "reached").exists())
        self.assertFalse((self.work / "calls.jsonl").exists())

    def test_current_runtime_failed_evidence_output_is_gating_not_optional(self):
        block = self.runtime_block()
        self.runtime_tools()
        formats = [("", "observation=current replay runtime after dependency setup; producer metadata is separate\\n")]
        formats += [(package, "package %s: unavailable/unverified\\n") for package in
                    ("libc6", "libc6-dbg", "libstdc++6", "libgcc-s1")]
        formats += [("ldd", "ldd version: unavailable/unverified\\n"),
                    ("readelf", "loader notes/build ID: unavailable/unverified\\n"),
                    ("sha256sum", "loader SHA256: unavailable/unverified\\n")]
        for index, (probe, output_format) in enumerate(formats):
            with self.subTest(probe=probe or "observation label"):
                self.work = self.root / f"runtime-output-failure-{index}"
                (self.work / "diagnostic").mkdir(parents=True)
                printf = 'printf() { if [ "$1" = "$FAIL_FORMAT" ]; then return 7; fi; builtin printf "$@"; }\n'
                completed = self.run_block(printf + block + "\nprintf reached > reached\n",
                                           FAIL_RUNTIME=probe, FAIL_FORMAT=output_format)
                self.assertEqual(completed.returncode, 7)
                self.assertFalse((self.work / "reached").exists())
                if not probe:
                    self.assertFalse((self.work / "calls.jsonl").exists())
                else:
                    calls = [json.loads(line) for line in (self.work / "calls.jsonl").read_text().splitlines()]
                    self.assertEqual(calls[-1]["subject"], probe)

    def test_replay_step_propagates_failure_without_token_or_build_tasks(self):
        block = self.block("Replay retained ELF suites in fixed counterbalanced order")
        self.environment.pop("GH_TOKEN")
        for code in (0, 1, 134):
            with self.subTest(code=code):
                self.work = self.root / f"exit-{code}"
                self.work.mkdir()
                completed = self.run_block(block + "\nprintf reached > reached\n", REPLAY_EXIT=str(code))
                self.assertEqual(completed.returncode, code)
                self.assertEqual((self.work / "reached").exists(), code == 0)
                call = json.loads((self.work / "calls.jsonl").read_text())
                self.assertEqual(call, {"command": "python3", "arguments": [".github/scripts/pr932_elf_replay.py",
                                  "diagnostic/producer.zip", "diagnostic/producer-metadata.json", "diagnostic/replay"],
                                  "token_present": False})
        self.assertNotIn("continue-on-error", self.workflow)
        self.assertNotIn("gradlew", self.workflow)
        self.assertNotIn("build-and-summarize", self.workflow)
        self.assertNotIn("setup_cached_java", self.workflow)
        self.assertEqual(self.workflow.count("GH_TOKEN:"), 1)
        self.assertIn("          path: diagnostic/\n", self.workflow)
        self.assertIn("        if: always()\n", self.workflow)


if __name__ == "__main__":
    unittest.main()
