#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Exercise the GitLab integration selector without installing packages or JDKs."""

import hashlib
import io
import os
from pathlib import Path
import re
import subprocess
import tarfile
import tempfile
import textwrap
import unittest


ROOT = Path(__file__).resolve().parents[3]
SCRIPTS = ROOT / ".gitlab/dd-trace-integration"
VERSIONS = {8: "8.0.512.0", 11: "11.0.33.0", 17: "17.0.21.0", 21: "21.0.13.0", 25: "25.0.5.0"}

# Published release assets, independent of the installer's tag/archive selection.
SEMERU_URLS = {
    (8, "x64"): "https://github.com/ibmruntimes/semeru8-binaries/releases/download/jdk-8.0.512.0/ibm-semeru-open-jdk_x64_linux_8.0.512.0.tar.gz",
    (8, "arm64"): "https://github.com/ibmruntimes/semeru8-binaries/releases/download/jdk-8.0.512.0/ibm-semeru-open-jdk_aarch64_linux_8.0.512.0.tar.gz",
    (11, "x64"): "https://github.com/ibmruntimes/semeru11-binaries/releases/download/jdk-11.0.33.0/ibm-semeru-open-jdk_x64_linux_11.0.33.0.tar.gz",
    (11, "arm64"): "https://github.com/ibmruntimes/semeru11-binaries/releases/download/jdk-11.0.33.0/ibm-semeru-open-jdk_aarch64_linux_11.0.33.0.tar.gz",
    (17, "x64"): "https://github.com/ibmruntimes/semeru17-binaries/releases/download/jdk-17.0.21.0/ibm-semeru-open-jdk_x64_linux_17.0.21.0.tar.gz",
    (17, "arm64"): "https://github.com/ibmruntimes/semeru17-binaries/releases/download/jdk-17.0.21.0/ibm-semeru-open-jdk_aarch64_linux_17.0.21.0.tar.gz",
    (21, "x64"): "https://github.com/ibmruntimes/semeru21-binaries/releases/download/jdk-21.0.13.0/ibm-semeru-open-jdk_x64_linux_21.0.13.0.tar.gz",
    (21, "arm64"): "https://github.com/ibmruntimes/semeru21-binaries/releases/download/jdk-21.0.13.0/ibm-semeru-open-jdk_aarch64_linux_21.0.13.0.tar.gz",
    (25, "x64"): "https://github.com/ibmruntimes/semeru25-binaries/releases/download/jdk-25.0.5.0/ibm-semeru-open-jdk_x64_linux_25.0.5.0.tar.gz",
    (25, "arm64"): "https://github.com/ibmruntimes/semeru25-binaries/releases/download/jdk-25.0.5.0/ibm-semeru-open-jdk_aarch64_linux_25.0.5.0.tar.gz",
}

# Upstream <archive>.sha256.txt for each asset above.
SEMERU_SHA256 = {
    (8, "x64"): "bd45587130f56feb746056e30d1fa1ebe5dd0ef44ec7b496e8aa072201981f8e",
    (8, "arm64"): "2090ee80f0a05889c62dae44c0479687bff9ad606ead0e367cde496c9ffcadb2",
    (11, "x64"): "dc4c3d88a1e2d64152e5c14109b5fbf35a1654d45b92b3419a2325c91ab15013",
    (11, "arm64"): "25947aef6c52a1ada2f53d73d8e71ee2e79398977f2f6f46e9f95886a917b085",
    (17, "x64"): "854268feba1ebddcad42cf97915b3c48e44a543bbbe8f43e587a722921a16c42",
    (17, "arm64"): "9e92ab55b5088d6f8f9170b4f4e70baff7d39416e454583306e6b576c2262e67",
    (21, "x64"): "0c92b61ea02efe73a7b6d346f1d8324efd50fe1fb848bf3a031a577dc1181d45",
    (21, "arm64"): "c8730b3746f3c2e5eb5ce7cc4415d4b86260cf7e9b12de469607c0c9c3c32dfb",
    (25, "x64"): "cb52686cd841bb76b55b66dabcbf890a303169158aa4bb10fa61040bf462f9b1",
    (25, "arm64"): "0d011789093c1e5e4da6843a8f40947a36c2f0af0199e6be64590d279e37e7cc",
}


def integration_script():
    config = (SCRIPTS / ".gitlab-ci.yml").read_text()
    base = config.split(".integration_test_base:\n", 1)[1].split("\n  artifacts:", 1)[0]
    script = textwrap.dedent(base.split("  script:\n    - |\n", 1)[1])
    # Stop before networked agent prerequisites, after the real selection and assertion.
    return script.split(".gitlab/dd-trace-integration/install-prerequisites.sh", 1)[0]


class JvmSelectionTest(unittest.TestCase):
    def setUp(self):
        self.work = tempfile.TemporaryDirectory()
        self.addCleanup(self.work.cleanup)
        self.path = Path(self.work.name)
        self.bin = self.path / "bin"
        self.bin.mkdir()
        self.calls = self.path / "calls"
        self.calls.touch()
        self.jdk = self.path / "fixture-jdk"
        (self.jdk / "bin").mkdir(parents=True)
        self.java = self.executable(
            self.jdk / "bin/java",
            'echo "java $*" >> "$CALLS"\n'
            'printf "    java.vm.name = %s\\n    java.version = %s\\n" '
            '"$FIXTURE_VM_NAME" "$FIXTURE_JAVA_VERSION" >&2\n'
            'exit "${JAVA_EXIT:-0}"\n',
        )
        self.executable(self.jdk / "bin/javac", "exit 0\n")
        self.archive = self.path / "jdk.tar.gz"
        with tarfile.open(self.archive, "w:gz") as archive:
            archive.add(self.jdk, arcname="semeru-jdk")
        # The first BAD_BODIES requests succeed with a non-gzip body, like an egress error page.
        self.executable(
            self.bin / "curl",
            'echo "curl $*" >> "$CALLS"\n'
            '[ "${CURL_EXIT:-0}" = 0 ] || exit "$CURL_EXIT"\n'
            'served=$(grep -c "^curl " "$CALLS")\n'
            'if [ "$served" -le "${BAD_BODIES:-0}" ]; then echo "<html>proxy error</html>"; exit 0; fi\n'
            'cat "$ARCHIVE"\n',
        )
        self.executable(self.bin / "sleep", 'echo "sleep $*" >> "$CALLS"\n')
        # The fixture archive cannot match a pinned digest: record the digest checked, exit SHA_EXIT.
        self.executable(
            self.bin / "sha256sum",
            'read -r digest file\n'
            'echo "sha256sum $* $digest" >> "$CALLS"\n'
            '[ -f "$file" ] || exit 1\n'
            'exit "${SHA_EXIT:-0}"\n',
        )
        self.tmp = self.path / "tmp"
        self.tmp.mkdir()
        self.executable(self.bin / "apt-get", 'echo "apt-get $*" >> "$CALLS"\n')
        self.executable(self.bin / "find", 'printf "%s\\n" "$FIXTURE_JDK"\n')
        self.env = dict(
            os.environ,
            PATH=f"{self.bin}:{os.environ['PATH']}",
            CALLS=str(self.calls),
            ARCHIVE=str(self.archive),
            FIXTURE_JDK=str(self.jdk),
            FIXTURE_VM_NAME="Eclipse OpenJ9 VM",
            FIXTURE_JAVA_VERSION="17.0.21",
            JAVA_HOME=str(self.jdk),
            JVM_TYPE="openj9",
            JAVA_VERSION="17",
            ARCH="x64",
            LIBC_VARIANT="glibc",
            INSTALL_ROOT=str(self.path / "installed"),
            TMPDIR=str(self.tmp),
        )

    def executable(self, path, body):
        path.write_text("#!/bin/bash\nset -eu\n" + body)
        path.chmod(0o755)
        return path

    def run_bash(self, script, **env):
        return subprocess.run(
            ["bash", "-euo", "pipefail", "-c", script],
            cwd=ROOT,
            env=dict(self.env, **env),
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

    def run_cell(self, **env):
        # Redirect only the install destination; execute the checked-in CI script body.
        prefix = 'source() { builtin source "$1" "$INSTALL_ROOT"; }\n'
        return self.run_bash(prefix + integration_script(), **env)

    def checked_digests(self):
        return [line.split()[-1] for line in self.calls.read_text().splitlines() if line.startswith("sha256sum ")]

    def curl_urls(self):
        return [line.split()[-1] for line in self.calls.read_text().splitlines() if line.startswith("curl ")]

    def assert_failed(self, result, message):
        self.assertNotEqual(result.returncode, 0, result.stdout)
        self.assertIn(message, result.stdout)
        self.assertNotIn("Verified integration JVM:", result.stdout)

    def test_all_glibc_openj9_cells_download_semeru_not_apt_hotspot(self):
        for arch in ("x64", "arm64"):
            for major, version in VERSIONS.items():
                with self.subTest(arch=arch, major=major):
                    self.calls.write_text("")
                    runtime_version = "1.8.0_512" if major == 8 else version
                    result = self.run_cell(ARCH=arch, JAVA_VERSION=str(major), FIXTURE_JAVA_VERSION=runtime_version)
                    self.assertEqual(result.returncode, 0, result.stdout)
                    calls = self.calls.read_text()
                    self.assertEqual(self.curl_urls(), [SEMERU_URLS[major, arch]])
                    self.assertEqual(self.checked_digests(), [SEMERU_SHA256[major, arch]])
                    self.assertNotIn("openjdk-", calls)
                    self.assertIn(f"Using JAVA_HOME: {self.path}/installed/openj9-{major}", result.stdout)
                    self.assertIn("Verified integration JVM:", result.stdout)
                    self.assertIn("java.vm.name=Eclipse OpenJ9 VM", result.stdout)

    def test_hotspot_cells_keep_apt_selection_and_are_verified(self):
        for major in VERSIONS:
            with self.subTest(major=major):
                self.calls.write_text("")
                result = self.run_cell(
                    JVM_TYPE="hotspot", JAVA_VERSION=str(major), FIXTURE_VM_NAME="OpenJDK 64-Bit Server VM",
                    FIXTURE_JAVA_VERSION="1.8.0_512" if major == 8 else f"{major}.0.1",
                )
                self.assertEqual(result.returncode, 0, result.stdout)
                self.assertIn(f"openjdk-{major}-jdk", self.calls.read_text())
                self.assertNotIn("\ncurl ", self.calls.read_text())
                self.assertIn("Verified integration JVM: JVM_TYPE=hotspot", result.stdout)

    def test_direct_musl_openj9_provisioning_still_fails_closed_without_downloading(self):
        for arch in ("x64", "arm64"):
            for major in VERSIONS:
                with self.subTest(arch=arch, major=major):
                    self.calls.write_text("")
                    result = self.run_cell(ARCH=arch, JAVA_VERSION=str(major), LIBC_VARIANT="musl")
                    self.assert_failed(result, "no OpenJ9 musl runtime is configured")
                    self.assertNotIn("\ncurl ", self.calls.read_text())
                    self.assertNotIn("java ", self.calls.read_text())

    def test_unknown_jvm_type_fails_without_jdk_selection(self):
        result = self.run_cell(JVM_TYPE="unknown")
        self.assert_failed(result, "Unsupported JVM_TYPE: unknown")
        self.assertNotIn("\ncurl ", self.calls.read_text())

    def test_unsupported_openj9_architecture_and_version_fail_before_download(self):
        for env, message in (({"ARCH": "sparc"}, "Unsupported OpenJ9 architecture"),
                             ({"JAVA_VERSION": "7"}, "Unsupported OpenJ9 JDK version")):
            with self.subTest(env=env):
                result = self.run_cell(**env)
                self.assert_failed(result, message)
                self.assertNotIn("\ncurl ", self.calls.read_text())

    def test_failed_download_fails_closed_without_another_attempt(self):
        result = self.run_cell(CURL_EXIT="22")
        self.assertNotEqual(result.returncode, 0, result.stdout)
        self.assertNotIn("Verified integration JVM:", result.stdout)
        self.assertNotIn("java ", self.calls.read_text())
        self.assertEqual(len(self.curl_urls()), 1, "curl handles transport retries itself")

    def test_invalid_archive_body_is_downloaded_again(self):
        result = self.run_cell(BAD_BODIES="1")
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertIn("attempt 1/3 is not a gzip tar archive", result.stdout)
        self.assertEqual(self.curl_urls(), [SEMERU_URLS[17, "x64"]] * 2)
        self.assertEqual(self.calls.read_text().count("sleep 5\n"), 1)
        self.assertIn("Verified integration JVM:", result.stdout)
        self.assertEqual(list(self.tmp.iterdir()), [])

    def test_digest_mismatch_fails_closed_without_retry_or_extraction(self):
        result = self.run_cell(SHA_EXIT="1")
        self.assert_failed(result, "ERROR: Semeru archive SHA-256 does not match the pinned "
                           + SEMERU_SHA256[17, "x64"])
        self.assertEqual(len(self.curl_urls()), 1, "a wrong digest is not retried")
        self.assertNotIn("sleep ", self.calls.read_text())
        self.assertNotIn("java ", self.calls.read_text())
        self.assertFalse((self.path / "installed/openj9-17/bin").exists())
        self.assertEqual(list(self.tmp.iterdir()), [])

    def test_installer_digest_check_line_accepts_match_and_rejects_mismatch(self):
        # Runs the installer's own check line with the real sha256sum, not the stub.
        line = next(l.strip() for l in (SCRIPTS / "install-openj9.sh").read_text().splitlines()
                    if "sha256sum -c" in l)
        check = re.fullmatch(r"if ! (.+); then", line)
        self.assertIsNotNone(check, line)
        digest = hashlib.sha256(self.archive.read_bytes()).hexdigest()
        env = dict(os.environ, archive=str(self.archive))
        for pinned, expected in ((digest, 0), ("0" * 64, 1)):
            with self.subTest(pinned=pinned):
                result = subprocess.run(["bash", "-c", check[1]], env=dict(env, SEMERU_SHA256=pinned))
                self.assertEqual(result.returncode, expected)

    def test_three_invalid_archive_bodies_fail_closed(self):
        result = self.run_cell(BAD_BODIES="3")
        self.assert_failed(result, "ERROR: Could not download a valid Semeru archive after 3 attempts")
        self.assertEqual(len(self.curl_urls()), 3)
        self.assertEqual(self.calls.read_text().count("sleep 5\n"), 2)
        self.assertNotIn("java ", self.calls.read_text())
        self.assertFalse((self.path / "installed/openj9-17/bin").exists())
        self.assertEqual(list(self.tmp.iterdir()), [])

    def test_sourced_installer_leaves_no_trap_and_keeps_caller_shell(self):
        prefix = 'source() { builtin source "$1" "$INSTALL_ROOT"; }\n'
        result = self.run_bash(prefix + "source .gitlab/dd-trace-integration/install-openj9.sh\n"
                               'echo "after-source JAVA_HOME=$JAVA_HOME trap=[$(trap -p EXIT)]"')
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertIn(f"after-source JAVA_HOME={self.path}/installed/openj9-17 trap=[]", result.stdout)

    def test_archive_requires_both_executable_java_and_javac(self):
        for missing in ("java", "javac"):
            with self.subTest(missing=missing):
                archive_path = self.path / f"no-{missing}.tar.gz"
                with tarfile.open(archive_path, "w:gz") as archive:
                    for name in ("java", "javac"):
                        entry = tarfile.TarInfo(f"jdk/bin/{name}")
                        entry.mode = 0o644 if name == missing else 0o755
                        content = b"#!/bin/bash\nexit 0\n"
                        entry.size = len(content)
                        archive.addfile(entry, io.BytesIO(content))
                result = self.run_cell(ARCHIVE=str(archive_path))
                self.assert_failed(result, "Semeru archive does not contain an executable JDK")

    def test_identity_rejects_wrong_vm_in_both_directions(self):
        for expected, actual in (("openj9", "OpenJDK 64-Bit Server VM"),
                                 ("openj9", "Java HotSpot(TM) 64-Bit Server VM"),
                                 ("hotspot", "Eclipse OpenJ9 VM"),
                                 ("openj9", ""), ("hotspot", "unknown")):
            with self.subTest(expected=expected, actual=actual):
                result = self.run_bash("bash .gitlab/dd-trace-integration/verify-jvm.sh",
                                       JVM_TYPE=expected, FIXTURE_VM_NAME=actual)
                self.assert_failed(result, "JVM identity mismatch")

    def test_identity_accepts_hotspot_vendor_name(self):
        result = self.run_bash("bash .gitlab/dd-trace-integration/verify-jvm.sh",
                               JVM_TYPE="hotspot", FIXTURE_VM_NAME="Java HotSpot(TM) 64-Bit Server VM")
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertIn("Verified integration JVM:", result.stdout)

    def test_identity_accepts_bare_major_ga_version(self):
        for major in ("17", "25"):
            with self.subTest(major=major):
                result = self.run_bash("bash .gitlab/dd-trace-integration/verify-jvm.sh",
                                       JAVA_VERSION=major, FIXTURE_JAVA_VERSION=major)
                self.assertEqual(result.returncode, 0, result.stdout)
                self.assertIn(f"java.version={major}\n", result.stdout + "\n")

    def test_identity_rejects_wrong_major_missing_version_and_failed_query(self):
        for version in ("11.0.33", "11", "170.0.1", "1", "", "1.8.0_512"):
            with self.subTest(version=version):
                result = self.run_bash("bash .gitlab/dd-trace-integration/verify-jvm.sh",
                                       FIXTURE_JAVA_VERSION=version)
                self.assert_failed(result, "JDK version mismatch")
        result = self.run_bash("bash .gitlab/dd-trace-integration/verify-jvm.sh", JAVA_EXIT="1")
        self.assert_failed(result, "Could not query integration JVM identity")

    def test_runner_rejects_mislabeled_jvm_before_artifacts_or_prerequisites(self):
        result = self.run_bash("bash .gitlab/dd-trace-integration/run-integration-test.sh",
                               FIXTURE_VM_NAME="OpenJDK 64-Bit Server VM", CI_PROJECT_DIR=str(self.path))
        self.assert_failed(result, "JVM identity mismatch")
        self.assertFalse((self.path / "integration-test-results").exists())
        self.assertNotIn("Installing prerequisites", result.stdout)

    def test_openj9_musl_cells_are_not_applicable_by_effective_ci_rules(self):
        config = (SCRIPTS / ".gitlab-ci.yml").read_text()
        base = config.split(".integration_test_base:\n", 1)[1].split("\n  script:", 1)[0]
        rule = re.search(
            r"    - if: '([^'\n]+)'\n      when: (never)\n    - when: on_success\n",
            base,
        )
        self.assertIsNotNone(rule, "Require a not-applicable skip rule before the terminal rule")
        terms = re.fullmatch(r'\$(\w+) == "(\w+)" && \$(\w+) == "(\w+)"', rule[1])
        self.assertIsNotNone(terms, "Expected a conjunction of matrix-variable equalities")
        condition = ((terms[1], terms[2]), (terms[3], terms[4]))
        skipped = 0
        scheduled = 0
        for arch in ("x64", "arm64"):
            for libc in ("glibc", "musl"):
                job = config.split(f"\nintegration-test-{arch}-{libc}:\n", 1)[1].split("\n\n", 1)[0]
                self.assertNotIn("rules:", job, "Cell override must not bypass the base applicability rule")
                self.assertIn("extends: .integration_test_base", job)
                for vm in ("hotspot", "openj9"):
                    for major in VERSIONS:
                        with self.subTest(arch=arch, libc=libc, vm=vm, major=major):
                            variables = {"JVM_TYPE": vm, "LIBC_VARIANT": libc}
                            matches = all(variables.get(key) == value for key, value in condition)
                            effective = rule[2] if matches else "on_success"
                            self.assertEqual(effective, "never" if vm == "openj9" and libc == "musl"
                                             else "on_success")
                            skipped += effective == "never"
                            scheduled += effective == "on_success"
        self.assertEqual(skipped, 10)
        self.assertEqual(scheduled, 30)

    def test_applicability_keeps_existing_pipeline_exclusions_and_failure_policy(self):
        config = (SCRIPTS / ".gitlab-ci.yml").read_text()
        base = config.split(".integration_test_base:\n", 1)[1].split("\n  script:", 1)[0]
        exclusions = [
            "    - !reference [.skip-on-release, rules]",
            "    - if: '$JDK_VERSION != null || $DEBUG_LEVEL != null || $HASH != null || $DOWNSTREAM != null'\n      when: never",
            '    - if: \'$CI_PIPELINE_SOURCE == "merge_request_event"\'\n      when: never',
        ]
        positions = [base.index(exclusion) for exclusion in exclusions]
        self.assertEqual(positions, sorted(positions))
        self.assertLess(positions[-1], base.index('$JVM_TYPE == "openj9"'))
        self.assertRegex(base, r"(?m)^  allow_failure: true$")
        self.assertNotIn("allow_failure: false", base)

    def test_ci_keeps_all_labeled_cells_and_runs_regression_tests(self):
        config = (SCRIPTS / ".gitlab-ci.yml").read_text()
        for platform in ("x64-glibc", "x64-musl", "arm64-glibc", "arm64-musl"):
            job = config.split(f"\nintegration-test-{platform}:\n", 1)[1].split("\n\n", 1)[0]
            self.assertEqual(re.findall(r"JVM_TYPE: (\w+)", job), ["hotspot", "openj9"])
            self.assertEqual(job.count("JAVA_VERSION: [8, 11, 17, 21, 25]"), 2)
        self.assertIn("python3 .gitlab/dd-trace-integration/tests/test_jvm_selection.py",
                      (ROOT / ".gitlab-ci.yml").read_text())
        self.assertIn("bash .gitlab/dd-trace-integration/verify-jvm.sh", integration_script())


if __name__ == "__main__":
    unittest.main(verbosity=2)
