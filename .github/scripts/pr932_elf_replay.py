#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.

import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import signal
import stat
import subprocess
import sys
import time
import xml.etree.ElementTree as ET
import zipfile

from pr932_elf_diagnostic import validate_xml


BRANCH = "paul.fournillon/diagnose-pr932-regression"
PRODUCER_HEAD = "d79319a95671484be44cc2ec377911710d2cac0f"
ARTIFACT_ID = 13965627960
PRODUCER_RUN = 43265852389
ARTIFACT_NAME = "pr932-native-elf-tsan-43265852389"
ARCHIVE_SHA256 = "acf2ed570928e02856073c24d50580e2b9ebcf6c6ad1f30a2897f0a631992b14"
SOURCE_PINS = {"base": "66f01812f2acfbe9d2f48aae80fad43cf924815e",
               "candidate": "152d939c395a37142202e407e2860efc4515ef04"}
BINARY = "bin/gtest/tsan_elfparser_ut/elfparser_ut"
HELPER = "test/resources/native-libs/unresolved-functions/main"
FIXTURES = {
    HELPER: "1a5b2ed0d025bd47653c994fd3d4716c69ed00f59136403afde763d1fca1797f",
    "test/resources/native-libs/reladyn-lib/libreladyn.so":
        "17862fd7e71ab1dba1feca85af9df08538b60284bcfb7a97852f6862b14c9642",
    "test/resources/native-libs/small-lib/libsmall-lib.so":
        "17381065fe11e484f7b16383a6dd50679cbe8f8a7ac556d8cb89c3983916db9b",
}
PAYLOAD_HASHES = {
    label: {BINARY: digest, **FIXTURES} for label, digest in (
        ("base", "8b5068aa23e000206e6b5b6cbca3c08e697ff31a76038a51bb2751927af88fd0"),
        ("candidate", "33cda2a3160c538f7d6005dac85294222a226ed8bd65731dcc4fad13278137c1"))
}
SUPPRESSION_SHA256 = "8c03642fa1ad1f83b7a1b179fc7b3bd2cdab49486e2eb4a0a864f65fafa30378"
TSAN_PREFIX = ("handle_segv=0:handle_sigbus=0:use_sigaltstack=0:halt_on_error=1:"
               "abort_on_error=1:io_sync=0:suppressions=")
SCHEDULE = ("base", "candidate", "candidate", "base") * 5
TSAN_REPORT = re.compile(r"ThreadSanitizer:|WARNING:.*[Tt]hread[Ss]anitizer")


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2) + "\n")


def ordinary_path(path, directory=False):
    # Reject symlink ancestors as well as a symlink leaf; resolve() would hide them.
    path = Path(os.path.abspath(path))
    for component in [*reversed(path.parents), path]:
        info = component.lstat()
        if stat.S_ISLNK(info.st_mode):
            raise ValueError(f"Symlink is not allowed: {component}")
    info = path.stat()
    expected_type = stat.S_ISDIR if directory else stat.S_ISREG
    if not expected_type(info.st_mode):
        raise ValueError(f"Not an ordinary {'directory' if directory else 'file'}: {path}")
    return info


def snapshot(path):
    info = ordinary_path(path)
    if info.st_uid != os.getuid() or info.st_mode & 0o7000:
        raise ValueError(f"Payload must be owned and have no special mode bits: {path}")
    return {"path": str(path), "inode": info.st_ino, "device": info.st_dev,
            "mode": oct(stat.S_IMODE(info.st_mode)), "uid": info.st_uid,
            "size": info.st_size, "sha256": hashlib.sha256(path.read_bytes()).hexdigest()}


def verify_metadata(metadata):
    if not isinstance(metadata, dict) or not isinstance(metadata.get("workflow_run"), dict):
        raise ValueError("Missing artifact/producer metadata")
    expected = {"id": ARTIFACT_ID, "name": ARTIFACT_NAME, "expired": False,
                "digest": "sha256:" + ARCHIVE_SHA256}
    run = {"id": PRODUCER_RUN, "repository_id": 585532470,
           "head_repository_id": 585532470, "head_branch": BRANCH, "head_sha": PRODUCER_HEAD}
    if any(metadata.get(key) != value for key, value in expected.items()):
        raise ValueError("Artifact identity/digest/expiry does not match the pinned producer")
    if any(metadata.get("workflow_run", {}).get(key) != value for key, value in run.items()):
        raise ValueError("Artifact producer run/source does not match the pinned producer")


def extract_archive(archive, destination):
    destination.mkdir()
    with zipfile.ZipFile(archive) as bundle:
        seen = set()
        for member in bundle.infolist():
            name = PurePosixPath(member.filename)
            mode = member.external_attr >> 16
            if (name.is_absolute() or ".." in name.parts or "\\" in member.filename
                    or not name.parts or name in seen
                    or stat.S_IFMT(mode) not in (0, stat.S_IFREG, stat.S_IFDIR)):
                raise ValueError(f"Unsafe or duplicate artifact entry: {member.filename}")
            seen.add(name)
            target = destination.joinpath(*name.parts)
            if member.is_dir():
                target.mkdir(parents=True, exist_ok=True)
            else:
                target.parent.mkdir(parents=True, exist_ok=True)
                with bundle.open(member) as source, target.open("xb") as output:
                    while chunk := source.read(1024 * 1024):
                        output.write(chunk)


def check_unchanged(records):
    for path, expected in records.items():
        if snapshot(path) != expected:
            raise ValueError(f"Input mutation: {path}")


def run_suite(binary, build, attempt, environment, timeout, record):
    xml = attempt / "elfparser.xml"
    command = [str(binary), f"--gtest_output=xml:{xml}"]
    record.update(command=command, working_directory=str(build),
                  native_environment={key: environment[key] for key in
                                      ("TEST_COMMIT", "TSAN_OPTIONS", "GTEST_DEATH_TEST_STYLE")},
                  started_unix_ns=time.time_ns(), started_monotonic_ns=time.monotonic_ns())
    write_json(attempt / "launch.json", record)
    timed_out = False
    leftover = False
    with (attempt / "stdout.txt").open("xb") as stdout, (attempt / "stderr.txt").open("xb") as stderr:
        with subprocess.Popen(command, cwd=build, env=environment, stdout=stdout, stderr=stderr,
                              start_new_session=True) as process:
            record["pid"] = process.pid
            try:
                process.wait(timeout=timeout)
            except subprocess.TimeoutExpired:
                timed_out = True
            finally:
                # Kill the whole session on timeout, and reject surviving suite children on exit.
                try:
                    os.killpg(process.pid, signal.SIGKILL)
                    leftover = not timed_out
                except ProcessLookupError:
                    pass
                process.wait()
    record.update(returncode=process.returncode,
                  shell_exit_code=128 - process.returncode if process.returncode < 0 else process.returncode,
                  signal=-process.returncode if process.returncode < 0 else None,
                  ended_unix_ns=time.time_ns(), ended_monotonic_ns=time.monotonic_ns(),
                  timed_out=timed_out, leftover_processes=leftover, xml_present=xml.exists(), errors=[])
    if process.returncode:
        record["errors"].append(f"Native exit {record['shell_exit_code']}")
    write_json(attempt / "process.json", record)
    for name in ("stdout.txt", "stderr.txt"):
        ordinary_path(attempt / name)
        if TSAN_REPORT.search((attempt / name).read_text(errors="replace")):
            record["errors"].append(f"TSan report in {name}")
    if xml.exists() or xml.is_symlink():
        ordinary_path(xml)
    try:
        record["tests_passed"] = validate_xml(xml)
    except (FileNotFoundError, ValueError, ET.ParseError) as error:
        # Native missing/invalid XML is an observation, not permission to omit its counterparts.
        record["errors"].append(f"Invalid XML: {error}")
    if timed_out or leftover:
        record["errors"].append("Bounded timeout" if timed_out else "Surviving suite children")
    record["status"] = "failed" if record["errors"] else "passed"


def replay(archive, metadata_path, output, suppression, *, payload_hashes=PAYLOAD_HASHES,
           archive_sha256=ARCHIVE_SHA256, suppression_sha256=SUPPRESSION_SHA256, timeout=60):
    archive, metadata_path, output, suppression = map(
        lambda path: Path(os.path.abspath(path)), (archive, metadata_path, output, suppression))
    result = {"status": "failed", "stage": "initialization", "producer_run": PRODUCER_RUN,
              "producer_head": PRODUCER_HEAD, "artifact_id": ARTIFACT_ID,
              "source_pins": SOURCE_PINS, "suite_timeout_seconds": timeout,
              "attempts": [{"index": index, "control": label, "status": "not_attempted",
                            "scheduled_unix_ns": time.time_ns()}
                           for index, label in enumerate(SCHEDULE, 1)]}
    output_created = False
    try:
        ordinary_path(output.parent, directory=True)
        output.mkdir()
        output_created = True
        write_json(output / "result.json", result)
        result["stage"] = "integrity"
        inputs = {path: snapshot(path) for path in (archive, metadata_path, suppression)}
        verify_metadata(json.loads(metadata_path.read_text()))
        if inputs[archive]["sha256"] != archive_sha256:
            raise ValueError("Downloaded artifact ZIP hash mismatch")
        if inputs[suppression]["sha256"] != suppression_sha256:
            raise ValueError("Frozen suppression hash mismatch")
        producer = output / "producer"
        extract_archive(archive, producer)
        payloads = {}
        for label, pin in SOURCE_PINS.items():
            manifest_path = producer / label / "result.json"
            inputs[manifest_path] = snapshot(manifest_path)
            manifest = json.loads(manifest_path.read_text())
            if (not isinstance(manifest, dict)
                    or manifest.get("expected_sha") != pin or manifest.get("actual_sha") != pin
                    or type(manifest.get("build_exit_code")) is not int
                    or manifest["build_exit_code"] != 0
                    or manifest.get("binary_sha256") != payload_hashes[label][BINARY]):
                raise ValueError(f"Invalid retained source/build manifest: {label}")
            build = producer / label / "native"
            actual_paths = {str(path.relative_to(build)) for path in build.rglob("*") if not path.is_dir()}
            if actual_paths != set(payload_hashes[label]):
                raise ValueError(f"Missing or unexpected native payload: {label}")
            for name, digest in payload_hashes[label].items():
                path = build / name
                payloads[path] = snapshot(path)
                if payloads[path]["sha256"] != digest:
                    raise ValueError(f"Payload hash mismatch: {path}")
        result["verified_inputs"] = list(inputs.values()) + list(payloads.values())
        write_json(output / "verified-inputs.json", result["verified_inputs"])
        check_unchanged(inputs | payloads)
        result["mode_restorations"] = []
        # ZIP loses executable modes; only these hash-verified, workspace-owned files may gain x bits.
        for label in SOURCE_PINS:
            for name in (BINARY, HELPER):
                path = producer / label / "native" / name
                before = payloads[path]
                path.chmod(int(before["mode"], 8) | 0o111)
                after = snapshot(path)
                if after != dict(before, mode=oct(int(before["mode"], 8) | 0o111)):
                    raise ValueError(f"Input mutation during mode restoration: {path}")
                result["mode_restorations"].append({"before": before, "after": after})
                payloads[path] = after
        inputs.update(payloads)
        result["stage"] = "native"
        write_json(output / "result.json", result)
        for scheduled in result["attempts"]:
            check_unchanged(inputs)
            attempt = output / f"attempt-{scheduled['index']:02d}-{scheduled['control']}"
            attempt.mkdir()
            scheduled.update(status="launching", payloads=list(payloads.values()))
            write_json(output / "result.json", result)
            label = scheduled["control"]
            build = producer / label / "native"
            environment = {key: value for key, value in os.environ.items() if not key.startswith("GTEST_")}
            environment.update(TEST_COMMIT=SOURCE_PINS[label], TSAN_OPTIONS=TSAN_PREFIX + str(suppression),
                               GTEST_DEATH_TEST_STYLE="threadsafe", GTEST_FILTER="*", GTEST_REPEAT="1")
            run_suite(build / BINARY, build, attempt, environment, timeout, scheduled)
            write_json(attempt / "result.json", scheduled)
            write_json(output / "result.json", result)
            check_unchanged(inputs)
            if scheduled["timed_out"] or scheduled["leftover_processes"]:
                raise RuntimeError("Experiment stopped after timeout/process cleanup")
        result.update(stage="complete", status="failed" if any(
            attempt["status"] != "passed" for attempt in result["attempts"]) else "passed")
    except (OSError, ValueError, RuntimeError, zipfile.BadZipFile) as error:
        result.update(status="failed", error=str(error))
        for attempt in result["attempts"]:
            if attempt["status"] == "launching":
                attempt.update(status="failed", harness_error=str(error))
        print(f"ELF replay stopped at {result['stage']}: {error}", file=sys.stderr)
    finally:
        if not output_created:
            return 1
        try:
            for attempt in result["attempts"]:
                if attempt["status"] == "not_attempted":
                    attempt["reason"] = result.get("error", "Experiment did not reach this launch")
            write_json(output / "result.json", result)
        except OSError as error:
            print(f"Required replay result write failed: {error}", file=sys.stderr)
            return 1
    return int(result["status"] != "passed")


def main():
    if (os.environ.get("GITHUB_ACTIONS") != "true"
            or os.environ.get("GITHUB_REPOSITORY") != "DataDog/java-profiler"
            or os.environ.get("GITHUB_REF") != "refs/heads/" + BRANCH):
        print("Retained native payload execution is restricted to the diagnostic CI branch", file=sys.stderr)
        return 1
    if len(sys.argv) != 4:
        print("Usage: pr932_elf_replay.py ARTIFACT.zip METADATA.json OUTPUT", file=sys.stderr)
        return 1
    suppression = Path(__file__).resolve().parents[2] / "gradle/sanitizers/tsan.supp"
    return replay(*sys.argv[1:], suppression)


if __name__ == "__main__":
    sys.exit(main())
