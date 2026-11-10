#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc
"""Exercise launcher parsing/argv with inert runtime and Git fixtures only.
This suite executes no containers, JVMs, Gradle, network or native tests.
"""
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile
import unittest

SCRIPT = Path(__file__).with_name("run-containers-tests.sh")


class ContainerLauncherTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="launcher-control-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.project = self.root / "launcher"
        (self.project / "utils").mkdir(parents=True)
        self.script = self.project / "utils" / SCRIPT.name
        shutil.copy2(SCRIPT, self.script)
        self.source = self.root / "source 'with spaces $literal"
        self.metadata = self.root / "actual-common.git"
        self.metadata.mkdir()
        for project in (self.project, self.source):
            (project / "gradle").mkdir(parents=True)
            (project / "gradlew").write_text("INERT WRAPPER FIXTURE\n")
        self.bin = self.root / "bin"
        self.bin.mkdir()
        self.log = self.root / "argv.jsonl"
        self.env = dict(os.environ, PATH=str(self.bin) + os.pathsep + os.environ["PATH"],
                        CALL_LOG=str(self.log), FIXTURE_METADATA=str(self.metadata),
                        CONTAINER_RUNTIME="podman", MISSING_IMAGE="", RUN_EXIT="0")
        stub = "#!" + sys.executable + "\n" + '''import json, os, pathlib, sys
name = pathlib.Path(sys.argv[0]).name
args = sys.argv[1:]
with open(os.environ['CALL_LOG'], 'a') as f:
    f.write(json.dumps([name] + args) + '\\n')
if name == 'git':
    if '--git-common-dir' in args:
        print(os.environ['FIXTURE_METADATA'])
    elif '--show-toplevel' in args:
        print(args[args.index('-C') + 1])
    else:
        sys.exit(99)
elif name == 'getenforce':
    print(os.environ.get('SELINUX', 'Disabled'))
elif name == 'uname':
    print(os.environ.get('MACHINE', 'arm64'))
elif args[:2] == ['image', 'inspect']:
    sys.exit(1 if os.environ.get('MISSING_IMAGE') in ('all', args[2]) else 0)
elif args and args[0] == 'build':
    pass
elif args and args[0] == 'run':
    sys.exit(int(os.environ.get('RUN_EXIT', '0')))
else:
    sys.exit(98)
'''
        for name in ("podman", "docker", "git", "getenforce", "uname"):
            path = self.bin / name
            path.write_text(stub)
            path.chmod(0o755)

    def invoke(self, *args, success=True):
        self.log.write_text("")
        result = subprocess.run(["/bin/bash", str(self.script), *args], env=self.env,
                                stdin=subprocess.DEVNULL, capture_output=True, text=True)
        self.calls = [json.loads(line) for line in self.log.read_text().splitlines()]
        if success:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        else:
            self.assertNotEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    def runs(self):
        return [c for c in self.calls if c[0] in ("podman", "docker") and c[1] == "run"]

    def safe_args(self):
        return ("--libc=glibc", "--arch=aarch64", "--jdk=17", "--config=debug",
                "--mount", "--source-root=" + str(self.source), "--offline", "--max-workers=1",
                "--gtest-task=nativeSocketInterposer_ut")

    def test_exact_local_offline_serialized_argv(self):
        self.invoke(*self.safe_args())
        self.assertEqual(len(self.runs()), 1, "supported source/offline/worker flags must construct one run")
        run, = self.runs()
        self.assertIn("--pull=never", run)
        self.assertIn("--network=none", run)
        self.assertIn(str(self.source) + ":/workspace", run)
        self.assertIn(str(self.metadata) + ":" + str(self.metadata) + ":ro", run)
        gradle = shlex.split(run[-1])
        for arg in ("--offline", "--no-parallel", "--max-workers=1",
                    ":ddprof-lib:gtestDebug_nativeSocketInterposer_ut"):
            self.assertIn(arg, gradle)
        self.assertNotIn("--parallel", gradle)
        self.assertNotIn("safe.directory", " ".join(run))
        self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_offline_missing_each_image_fails_before_build_or_run(self):
        for image in ("java-profiler-base:glibc-aarch64", "java-profiler-test:glibc-jdk17-aarch64"):
            with self.subTest(image=image):
                self.env["MISSING_IMAGE"] = image
                result = self.invoke(*self.safe_args(), success=False)
                self.assertIn("offline", (result.stdout + result.stderr).lower())
                self.assertFalse(self.runs())
                self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_offline_rejects_rebuild_and_shell(self):
        for arg in ("--rebuild", "--rebuild-base", "--shell"):
            with self.subTest(arg=arg):
                self.invoke(*self.safe_args(), arg, success=False)
                self.assertFalse(self.runs())

    def test_offline_requires_mount(self):
        self.invoke("--offline", success=False)
        self.assertFalse(self.runs())

    def test_source_requires_mount(self):
        self.invoke("--source-root=" + str(self.source), success=False)
        self.assertFalse(self.runs())

    def test_invalid_source(self):
        for source in ("", "relative", str(self.root / "missing")):
            with self.subTest(source=source):
                self.invoke("--mount", "--source-root=" + source, success=False)
                self.assertFalse(self.runs())

    def source_fixture(self, name):
        """Make an independently mountable source for the inert Git/runtime fixtures."""
        source = self.root / name
        (source / "gradle").mkdir(parents=True)
        (source / "gradlew").write_text("INERT WRAPPER FIXTURE\n")
        return source

    def test_source_rejects_raw_trailing_newline_without_selecting_sibling(self):
        sibling = self.source_fixture("selected-source")
        source = self.source_fixture("selected-source\n")
        self.invoke("--mount", "--source-root=" + str(sibling))
        self.assertIn(str(sibling) + ":/workspace", self.runs()[0])
        self.invoke("--mount", "--source-root=" + str(source), success=False)
        self.assertFalse(self.runs())
        self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_source_rejects_resolved_trailing_newline_without_selecting_sibling(self):
        sibling = self.source_fixture("resolved-source")
        source = self.source_fixture("resolved-source\n")
        link = self.root / "ordinary-source-link"
        link.symlink_to(source, target_is_directory=True)
        self.invoke("--mount", "--source-root=" + str(sibling))
        self.assertIn(str(sibling) + ":/workspace", self.runs()[0])
        self.invoke("--mount", "--source-root=" + str(link), success=False)
        self.assertFalse(self.runs())
        self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_source_rejects_other_raw_volume_delimiters(self):
        for name in ("source:volume", "source\nline"):
            with self.subTest(name=name):
                source = self.source_fixture(name)
                self.invoke("--mount", "--source-root=" + str(source), success=False)
                self.assertFalse(self.runs())
                self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_source_rejects_other_resolved_volume_delimiters(self):
        for i, name in enumerate(("resolved:volume", "resolved\nline")):
            with self.subTest(name=name):
                source = self.source_fixture(name)
                link = self.root / ("ordinary-source-link-" + str(i))
                link.symlink_to(source, target_is_directory=True)
                self.invoke("--mount", "--source-root=" + str(link), success=False)
                self.assertFalse(self.runs())
                self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_invalid_worker_limits(self):
        for count in ("", "0", "-1", "1;echo BAD", "two", "1.5"):
            with self.subTest(count=count):
                self.invoke("--max-workers=" + count, success=False)
                self.assertFalse(self.runs())

    def test_artifacts_preserve_xml_and_recording_paths_literally(self):
        artifacts = self.source / "build" / "logs" / "evidence 'quoted'; $(not-a-command)"
        artifacts.mkdir(parents=True)
        self.invoke(*self.safe_args(), "--artifacts-dir=" + str(artifacts))
        self.assertEqual(len(self.runs()), 1, "artifact support must construct one run")
        run, = self.runs()
        cell = artifacts / "glibc-jdk17-aarch64-debug"
        self.assertIn(str(cell / "gtest") + ":/qualification-gtest", run)
        self.assertIn(str(cell / "jfr") + ":/tmp/recordings", run)
        self.assertIn("GTEST_OUTPUT=xml:/qualification-gtest/", run)
        self.assertTrue((cell / "gtest").is_dir())
        self.assertTrue((cell / "jfr").is_dir())
        self.assertIn("--network=none", run, "offline policy must remain unchanged")

    def test_artifacts_require_mount_and_reject_shell(self):
        artifacts = self.source / "build" / "logs" / "evidence"
        artifacts.mkdir(parents=True)
        for args in ((), ("--mount", "--shell")):
            with self.subTest(args=args):
                self.invoke(*args, "--artifacts-dir=" + str(artifacts), success=False)
                self.assertFalse(self.runs())

    def test_artifacts_reject_invalid_roots_before_runtime(self):
        file = self.root / "not-a-directory"
        file.write_text("not a directory")
        for suffix in ("bad:volume", "bad\nline", "trailing\n"):
            (self.root / suffix).mkdir()
        link = self.root / "ordinary-symlink"
        link.symlink_to(self.root / "trailing\n", target_is_directory=True)
        for root in ("", "relative", str(self.root / "missing"), str(file),
                     str(self.root / "bad:volume"), str(self.root / "bad\nline"),
                     str(self.root / "trailing\n"), str(link)):
            with self.subTest(root=root):
                self.invoke("--mount", "--artifacts-dir=" + root, success=False)
                self.assertFalse(self.runs())
                self.assertFalse(any(c[1:2] == ["build"] for c in self.calls))

    def test_artifacts_use_runtime_selinux_conventions(self):
        artifacts = self.source / "build" / "logs" / "evidence"
        artifacts.mkdir(parents=True)
        self.env["SELINUX"] = "Enforcing"
        for runtime, suffix in (("podman", ":z"), ("docker", "")):
            with self.subTest(runtime=runtime):
                self.invoke("--mount", "--container=" + runtime,
                            "--artifacts-dir=" + str(artifacts), "--jdk=17")
                self.assertEqual(len(self.runs()), 1)
                run, = self.runs()
                cell = artifacts / "glibc-jdk17-aarch64-debug"
                self.assertIn(str(cell / "gtest") + ":/qualification-gtest" + suffix, run)
                self.assertIn(str(cell / "jfr") + ":/tmp/recordings" + suffix, run)

    def test_artifacts_matrix_forwards_separate_cell_paths(self):
        artifacts = self.source / "build" / "logs" / "evidence"
        artifacts.mkdir(parents=True)
        self.invoke(*self.safe_args(), "--artifacts-dir=" + str(artifacts),
                    "--config=debug,release", "--run")
        self.assertEqual(len(self.runs()), 2, "artifact option must propagate to both cells")
        for run, config in zip(self.runs(), ("debug", "release")):
            cell = artifacts / ("glibc-jdk17-aarch64-" + config)
            self.assertIn(str(cell / "gtest") + ":/qualification-gtest", run)
            self.assertIn(str(cell / "jfr") + ":/tmp/recordings", run)
            self.assertIn("GTEST_OUTPUT=xml:/qualification-gtest/", run)

    def test_default_clone_unchanged(self):
        self.invoke()
        run, = self.runs()
        self.assertIn(str(self.project) + ":/source:ro", run)
        self.assertIn("java-profiler-test:glibc-jdk21-aarch64", run)
        self.assertIn("git clone --depth 1 file:///source /workspace", run[-1])
        self.assertIn("--parallel", run[-1])
        self.assertIn("-Pskip-gtest", run[-1])
        self.assertNotIn("--network=none", run)
        self.assertNotIn("--pull=never", run)
        self.assertFalse(any("qualification-gtest" in arg or "/tmp/recordings" in arg or
                             "GTEST_OUTPUT=" in arg for arg in run))

    def test_legacy_cache_miss_and_rebuild_paths(self):
        for flag, missing, builds in ((None, "all", 2), ("--rebuild", "", 2),
                                      ("--rebuild-base", "", 1)):
            with self.subTest(flag=flag, missing=missing):
                self.env["MISSING_IMAGE"] = missing
                self.invoke(*([flag] if flag else []))
                self.assertEqual(sum(c[1:2] == ["build"] for c in self.calls), builds)
                self.assertEqual(len(self.runs()), 1)

    def test_docker_musl_and_tests_pattern(self):
        self.invoke("--container=docker", "--libc=musl", "--arch=x64", "--jdk=8",
                    "--tests=SomeTest.*", "--gtest")
        run, = self.runs()
        self.assertEqual(run[0], "docker")
        self.assertIn("linux/amd64", run)
        self.assertIn("java-profiler-test:musl-jdk8-x64", run)
        self.assertIn("-Ptests=SomeTest.*", shlex.split(run[-1].split(" && ")[-1]))
        self.assertNotIn("-Pskip-gtest", run[-1])

    def test_shell_and_tsan_legacy_flags(self):
        self.invoke("--mount", "--shell", "--config=tsan", "--arch=aarch64")
        run, = self.runs()
        for arg in ("-it", "--init", "--ulimit", "core=-1", "--cap-add=SYS_PTRACE", "--privileged"):
            self.assertIn(arg, run)
        self.assertEqual(run[-1], "/bin/bash")
        self.invoke("--config=tsan", "--arch=aarch64")
        run, = self.runs()
        self.assertIn("sysctl -w vm.mmap_rnd_bits=28", run[-1])
        self.assertIn("-Pnative.forceCompiler=clang++-17", run[-1])

    def test_selinux_volume_options(self):
        self.env["SELINUX"] = "Enforcing"
        self.invoke("--mount")
        self.assertIn(str(self.project) + ":/workspace:z", self.runs()[0])
        self.invoke("--container=docker")
        self.assertIn(str(self.project) + ":/source:ro", self.runs()[0])

    def test_arch_detection_fallback_and_runtime_environment(self):
        for machine, arch in (("amd64", "x64"), ("unknown", "x64"), ("arm64", "aarch64")):
            with self.subTest(machine=machine):
                self.env.update(MACHINE=machine, CONTAINER_RUNTIME="docker")
                self.invoke()
                self.assertEqual(self.runs()[0][0], "docker")
                self.assertIn("java-profiler-test:glibc-jdk21-" + arch, self.runs()[0])

    def test_matrix_preview_and_skip_branches(self):
        result = self.invoke("--matrix")
        self.assertIn("Generated cells: 192", result.stdout)
        self.assertIn("Preview only", result.stdout)
        self.assertFalse(self.runs())
        for args in (("--libc=musl", "--jdk=17-j9"), ("--libc=musl", "--jdk=21-graal"),
                     ("--jdk=17-graal", "--config=asan"),
                     ("--jdk=8", "--arch=aarch64"), ("--libc=musl", "--config=tsan")):
            with self.subTest(args=args):
                self.invoke(*args, success=False)
                self.assertFalse(self.runs())

    def test_matrix_forwards_new_options(self):
        self.invoke(*self.safe_args(), "--config=debug,release", "--run")
        self.assertEqual(len(self.runs()), 2)
        for run in self.runs():
            self.assertIn("--network=none", run)
            self.assertIn("--max-workers=1", run[-1])
            self.assertIn(str(self.source) + ":/workspace", run)

    def test_fail_fast_and_exit_propagation(self):
        self.env["RUN_EXIT"] = "7"
        result = self.invoke("--config=debug,release", "--run", "--fail-fast", success=False)
        self.assertEqual(len(self.runs()), 1)
        self.assertIn("Cancelled: 1", result.stdout)
        result = self.invoke(success=False)
        self.assertEqual(result.returncode, 7)

    def test_existing_validation_exits(self):
        for args in (("--container=other",), ("--tests=X", "--gtest-task=Y"),
                     ("--libc=glibc,",), ("--jdk=unknown",), ("--arch=unknown",),
                     ("--config=unknown",), ("--fail-fast",),
                     ("--config=debug,release", "--shell"),
                     ("--matrix", "--gtest-task=:ddprof-lib:gtestDebug_x")):
            with self.subTest(args=args):
                self.invoke(*args, success=False)
                self.assertFalse(self.runs())

    def test_full_task_and_quoted_pattern_not_argument_injection(self):
        self.invoke("--gtest-task=:ddprof-lib:gtestDebug_libraryPatcher_ut")
        self.assertIn(":ddprof-lib:gtestDebug_libraryPatcher_ut", self.runs()[0][-1])
        pattern = "Test 'quoted'; $(not-a-command)"
        self.invoke("--tests=" + pattern)
        command = self.runs()[0][-1].split(" && ")[-1]
        self.assertIn("-Ptests=" + pattern, shlex.split(command))


if __name__ == "__main__":
    unittest.main(verbosity=2)
