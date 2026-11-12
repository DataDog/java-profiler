#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.

import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time
import xml.etree.ElementTree as ET


EXPECTED_TESTS = 31
DAEMON_DIAGNOSTIC = re.compile(
    r"Daemon will be stopped|single-use Daemon|daemon has disappeared|"
    r"FAILURE:|What went wrong|Execution failed for task|BUILD FAILED|"
    r"ThreadSanitizer:|CHECK failed:|FATAL:|^> Task .*FAILED"
)


def validate_xml(path):
    root = ET.parse(path).getroot()
    cases = list(root.iter("testcase"))
    if root.tag != "testsuites" or len(cases) != EXPECTED_TESTS:
        raise ValueError(f"Expected {EXPECTED_TESTS} ELF test cases in {path}")
    for case in cases:
        if (case.find("failure") is not None or case.find("error") is not None
                or case.find("skipped") is not None or case.get("status") == "notrun"):
            raise ValueError(f"Failed or skipped ELF case in {path}: {case.get('name')}")
    return len(cases)


def collect_logs(source, output, started):
    logs = output / "build-logs"
    logs.mkdir(exist_ok=True)
    for path in (source / "build/logs").glob("*.log"):
        shutil.copy2(path, logs / path.name)
    # Keep only diagnostics from this invocation's daemon logs, not daemon environment/context dumps.
    daemon_home = Path(os.environ.get("GRADLE_USER_HOME", str(Path.home() / ".gradle")))
    with (logs / "single-use-daemon-diagnostics.txt").open("w") as dest:
        for path in sorted((daemon_home / "daemon").glob("*/daemon-*.out.log")):
            if path.stat().st_mtime >= started:
                lines = [line for line in path.read_text(errors="replace").splitlines()
                         if DAEMON_DIAGNOSTIC.search(line)]
                dest.write(f"{path.name}: {len(lines)} selected diagnostic lines\n")
                dest.write("\n".join(lines) + "\n")


def diagnose(source, expected_sha, output, repetitions):
    source, output = Path(source).resolve(), Path(output).resolve()
    output.mkdir(parents=True, exist_ok=True)
    result = {"expected_sha": expected_sha, "status": "failed", "stage": "preflight",
              "repetitions_planned": repetitions, "attempts": []}
    started = time.time()
    status = 1
    try:
        if not 1 <= repetitions <= 10:
            raise ValueError("Repetitions must be between 1 and 10")
        result["actual_sha"] = subprocess.check_output(
            ["git", "rev-parse", "HEAD"], cwd=source, text=True).strip()
        if result["actual_sha"] != expected_sha:
            raise ValueError("Source SHA does not match the pinned control")
        subprocess.run(["git", "diff", "--exit-code", "HEAD"], cwd=source, check=True)
        environment = dict(os.environ, TEST_COMMIT=expected_sha)
        result["stage"] = "build"
        command = ["./.claude/commands/build-and-summarize",
                   ":ddprof-lib:linkGtestTsan_elfparser_ut", ":ddprof-lib:buildNativeLibs",
                   "-PCI", "-PkeepJFRs", "--no-daemon", "--parallel", "--build-cache", "--no-watch-fs"]
        result["build_command"] = command
        with (output / "build-driver.log").open("wb") as log:
            completed = subprocess.run(command, cwd=source, env=environment, stdout=log,
                                       stderr=subprocess.STDOUT)
        result["build_exit_code"] = completed.returncode
        if completed.returncode:
            raise RuntimeError(f"Build failed with exit {completed.returncode}; see build-driver.log")
        result["stage"] = "source_verification"
        subprocess.run(["git", "diff", "--exit-code", "HEAD"], cwd=source, check=True)
        result["stage"] = "artifacts"
        build = source / "ddprof-lib/build"
        binary = build / "bin/gtest/tsan_elfparser_ut/elfparser_ut"
        resources = [build / "test/resources/native-libs/unresolved-functions/main",
                     build / "test/resources/native-libs/reladyn-lib/libreladyn.so",
                     build / "test/resources/native-libs/small-lib/libsmall-lib.so"]
        for path in [binary] + resources:
            destination = output / "native" / path.relative_to(build)
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(path, destination)
        result["binary_sha256"] = hashlib.sha256(binary.read_bytes()).hexdigest()
        with (output / "elf-metadata.txt").open("wb") as log:
            subprocess.run(["readelf", "-n", "-S", "-l", str(binary)], check=True,
                           stdout=log, stderr=subprocess.STDOUT)
        # Match ConfigurationPresets.configureTsan plus GtestTaskBuilder hardening; do not preload TSan.
        environment["TSAN_OPTIONS"] = (
            "handle_segv=0:handle_sigbus=0:use_sigaltstack=0:halt_on_error=1:"
            f"abort_on_error=1:io_sync=0:suppressions={source}/gradle/sanitizers/tsan.supp")
        environment["GTEST_DEATH_TEST_STYLE"] = "threadsafe"
        result["native_environment"] = {key: environment[key] for key in
                                        ("TSAN_OPTIONS", "GTEST_DEATH_TEST_STYLE")}
        result["working_directory"] = str(build)
        result["stage"] = "native"
        for index in range(1, repetitions + 1):
            attempt = output / f"attempt-{index}"
            attempt.mkdir()
            xml = attempt / "elfparser.xml"
            command = [str(binary), f"--gtest_output=xml:{xml}"]
            with (attempt / "stdout.txt").open("wb") as stdout, (attempt / "stderr.txt").open("wb") as stderr:
                completed = subprocess.run(command, cwd=build, env=environment, stdout=stdout, stderr=stderr)
            code = completed.returncode
            attempt_result = {"index": index, "command": command, "returncode": code,
                              "shell_exit_code": 128 - code if code < 0 else code,
                              "xml_present": xml.is_file()}
            result["attempts"].append(attempt_result)
            if code:
                raise RuntimeError(f"Native ELF failed with exit {attempt_result['shell_exit_code']}; see {attempt.name}")
            attempt_result["tests_passed"] = validate_xml(xml)
        subprocess.run(["git", "diff", "--exit-code", "HEAD"], cwd=source, check=True)
        result.update(status="passed", stage="complete")
        status = 0
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError, ET.ParseError) as error:
        result["error"] = str(error)
        print(f"ELF diagnostic failed at {result['stage']}: {error}", file=sys.stderr)
    finally:
        try:
            collect_logs(source, output, started)
        except OSError as error:
            result.update(status="failed", log_collection_error=str(error))
            print(f"Failed to retain build/daemon logs: {error}", file=sys.stderr)
            status = 1
        (output / "result.json").write_text(json.dumps(result, indent=2) + "\n")
    return status


if __name__ == "__main__":
    source, expected_sha, output, repetitions = sys.argv[1:]
    sys.exit(diagnose(source, expected_sha, output, int(repetitions)))
