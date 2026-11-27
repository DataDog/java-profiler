# Copyright 2026, Datadog, Inc.
"""Exercise the main-only producer with real quarantine validation and aggregation."""

import datetime
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[3]
SOURCE_DIR = ROOT / ".gitlab/dd-trace-integration"
PLATFORMS = (
    "glibc-x64-hotspot", "glibc-x64-openj9", "glibc-arm64-hotspot", "glibc-arm64-openj9",
    "musl-x64-hotspot", "musl-x64-openj9", "musl-arm64-hotspot", "musl-arm64-openj9",
)
JDKS = (8, 11, 17, 21, 25)


class MainIntegrationGateTest(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory(prefix="main-integration-gate-")
        self.addCleanup(directory.cleanup)
        self.work = Path(directory.name)
        self.gate = self.work / ".gitlab/dd-trace-integration"
        self.gate.mkdir(parents=True)
        for name in ("certify-main.sh", "validate-quarantine.sh",
                     "post-pr-comment.sh", "quarantine-lib.sh"):
            shutil.copy(SOURCE_DIR / name, self.gate / name)
        # post-pr-comment.sh resolves its comment poster relative to the copied
        # tree, so the poster must be copied at the same relative depth.
        (self.gate.parent / "scripts").mkdir()
        shutil.copy(SOURCE_DIR.parent / "scripts/upsert-github-pr-comment.sh",
                    self.gate.parent / "scripts/upsert-github-pr-comment.sh")
        self.results = self.work / "integration-test-results"
        for platform in PLATFORMS:
            for jdk in JDKS:
                config = f"{platform}-jdk{jdk}"
                cell = self.results / config
                cell.mkdir(parents=True)
                for scenario in ("profiler-only", "tracer-profiler"):
                    (cell / f"{scenario}-{config}.log").write_text("SUCCESS: validated\n")
        self.prepared = self.work / "ddprof-commit-sha.txt"
        self.quarantine = self.gate / "quarantine.txt"
        self.quarantine.write_text("")
        self.body = self.work / "body.md"
        self.network = self.work / "network-attempt"
        binary = self.work / "bin"
        binary.mkdir()
        for command in ("curl", "wget", "gh", "dd-octo-sts"):
            stub = binary / command
            stub.write_text('#!/bin/sh\nprintf "%s\\n" "$0 $*" >> "$NETWORK_ATTEMPT_MARKER"\nexit 97\n')
            stub.chmod(0o700)
        self.env = dict(os.environ, PATH=str(binary) + os.pathsep + os.defpath,
                        CI_PIPELINE_SOURCE="push", CI_COMMIT_BRANCH="main",
                        CANCELLED="", QUARANTINE_LIST=str(self.work / "attacker-quarantine-list"),
                        COMMENT_BODY_FILE=str(self.body), NETWORK_ATTEMPT_MARKER=str(self.network),
                        DDPROF_COMMIT_BRANCH="incorrect-inherited-branch", DDPROF_COMMIT_SHA="f" * 40)
        for token in ("GITHUB_TOKEN", "GH_TOKEN", "DDOCTOSTS_ID_TOKEN"):
            self.env.pop(token, None)
        self.git("init", "-q")
        self.commit_policy()

    def git(self, *args):
        env = dict(self.env, GIT_CONFIG_GLOBAL=os.devnull, GIT_CONFIG_NOSYSTEM="1")
        return subprocess.check_output(["git", "-c", "user.name=Test", "-c", "user.email=test@example.invalid",
                                        *args], cwd=self.work, env=env, text=True).strip()

    def commit_policy(self):
        self.git("add", "-A", "--", str(self.quarantine))
        self.git("commit", "-qm", "fixture policy")
        self.sha = self.git("rev-parse", "HEAD")
        self.env["CI_COMMIT_SHA"] = self.sha
        self.prepared.write_text(self.sha + "\n")

    def run_gate(self, **changes):
        env = dict(self.env)
        for key, value in changes.items():
            if value is None:
                env.pop(key, None)
            else:
                env[key] = value
        result = subprocess.run(["bash", str(self.gate / "certify-main.sh")], cwd=self.work, env=env,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                text=True, timeout=30)
        self.assertFalse(self.network.exists(), "Certification attempted a network operation")
        return result

    def assert_blocked(self, message, **changes):
        result = self.run_gate(**changes)
        self.assertNotEqual(result.returncode, 0, result.stdout)
        self.assertIn(message, result.stdout)
        return result

    def fail_scenario(self):
        config = "glibc-x64-openj9-jdk25"
        path = self.results / config / f"profiler-only-{config}.log"
        path.write_text("VALIDATION_FAILED\n")
        return config

    def write_quarantine(self, config, *, expired=False):
        today = datetime.datetime.now(datetime.timezone.utc).date()
        added = today - datetime.timedelta(days=7)
        review = today + datetime.timedelta(days=-1 if expired else 7)
        self.quarantine.write_text(
            f"{config}/profiler-only | PROF-16810 | {added} | {review} | confirmed flake\n")
        self.commit_policy()

    def test_main_push_with_real_complete_results_succeeds_without_posting(self):
        result = self.run_gate()
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertIn("All 30 integration tests passed", self.body.read_text())
        self.assertIn("10 not applicable", self.body.read_text())
        self.assertIn("`" + self.sha[:8] + "`", self.body.read_text())
        self.assertNotIn("`" + "f" * 8 + "`", self.body.read_text())
        self.assertIn("Skipping PR comment for branch: main", result.stdout)
        self.assertIn("0 quarantined scenario(s), all valid", result.stdout)

    def test_non_main_branches_cannot_attest_even_with_valid_artifacts(self):
        for branch in ("topic-with-no-pr", "main-other", "release/1.2._", "", None):
            with self.subTest(branch=branch):
                self.assert_blocked("requires a main push pipeline", CI_COMMIT_BRANCH=branch)
        self.assertFalse(self.body.exists())

    def test_non_push_sources_cannot_attest(self):
        for source in ("schedule", "web", "trigger", "pipeline", "merge_request_event", "", None):
            with self.subTest(source=source):
                self.assert_blocked("requires a main push pipeline", CI_PIPELINE_SOURCE=source)
        self.assertFalse(self.body.exists())

    def test_cancelled_main_must_fail_instead_of_returning_noop_success(self):
        self.assert_blocked("Cancelled integration", CANCELLED="true")
        self.assertFalse(self.body.exists())

    def test_non_cancelled_marker_does_not_skip_execution(self):
        result = self.run_gate(CANCELLED="false")
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertTrue(self.body.exists())

    def test_candidate_sha_is_required_and_must_be_complete(self):
        for candidate in ("", None, "main", "a" * 39, "a" * 41, "g" * 40):
            with self.subTest(candidate=candidate):
                self.assert_blocked("requires a full candidate SHA", CI_COMMIT_SHA=candidate)
        self.assertFalse(self.body.exists())

    def test_missing_or_mismatched_preparation_cannot_attest(self):
        self.prepared.unlink()
        self.assert_blocked("Prepared agent evidence is missing")
        for artifact in ("", "b" * 40, self.sha + "\nother-pipeline\n"):
            with self.subTest(artifact=artifact):
                self.prepared.write_text(artifact)
                self.assert_blocked("Prepared agent evidence is missing")
        self.assertFalse(self.body.exists())

    def test_incomplete_matrix_blocks_the_producer(self):
        config = "musl-arm64-hotspot-jdk25"
        (self.results / config / f"tracer-profiler-{config}.log").unlink()
        result = self.assert_blocked("configuration(s) produced no result")
        self.assertIn(config, result.stdout)

    def test_empty_results_cannot_attest(self):
        shutil.rmtree(self.results)
        self.assert_blocked("configuration(s) produced no result")

    def test_unquarantined_validation_failure_blocks_the_producer(self):
        config = self.fail_scenario()
        self.assert_blocked("integration test(s) failed")
        self.assertIn(config, self.body.read_text())

    def test_valid_quarantined_failure_preserves_existing_policy(self):
        config = self.fail_scenario()
        self.write_quarantine(config)
        result = self.run_gate()
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertIn("Quarantined failures", self.body.read_text())
        self.assertIn(config, self.body.read_text())

    def test_worktree_cannot_replace_the_committed_policy(self):
        self.quarantine.write_text("malformed working-tree entry\n")
        result = self.run_gate()
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertIn("0 quarantined scenario(s), all valid", result.stdout)

    def test_expired_quarantine_is_validated_even_when_all_results_pass(self):
        self.write_quarantine("glibc-x64-openj9-jdk25", expired=True)
        self.assert_blocked("review was due")
        self.assertFalse(self.body.exists())

    def test_malformed_quarantine_cannot_be_bypassed_by_passing_results(self):
        self.quarantine.write_text("not a valid quarantine entry\n")
        self.commit_policy()
        self.assert_blocked("problem(s)")
        self.assertFalse(self.body.exists())

    def test_missing_quarantine_file_cannot_attest(self):
        self.quarantine.unlink()
        self.commit_policy()
        self.assert_blocked("Cannot read the quarantine list from the candidate commit")
        self.assertFalse(self.body.exists())


if __name__ == "__main__":
    unittest.main()
