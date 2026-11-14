#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
"""Run Gradle with retained output and deterministic, non-LLM summary reports."""

import datetime
import json
import os
from pathlib import Path
import re
import signal
import subprocess
import sys
import threading
import time
from urllib.parse import urlsplit, urlunsplit


PROGRESS = re.compile(r"^(> Task |BUILD (SUCCESSFUL|FAILED))|\d+ tests? (successful|failed|skipped)")


def public_line(line):
    """Do not propagate URL credentials or signed query strings into summary artifacts."""
    def clean(match):
        try:
            url = urlsplit(match.group())
            host = url.hostname or ""
            if url.port is not None:
                host += ":" + str(url.port)
            return urlunsplit((url.scheme, host, url.path, "", ""))
        except ValueError:
            return "[invalid URL omitted]"
    return re.sub(r"https?://[^\s\"'<>]+", clean, line)


def summarize(log, status, elapsed, command, launcher_pid, interrupted_by):
    """Extract observed log facts only; absent test counts/timings remain unknown."""
    lines = [public_line(line) for line in log.read_text(errors="replace").splitlines()]
    builds = [line for line in lines if re.match(r"^BUILD (SUCCESSFUL|FAILED)", line)]
    failed = [line for line in lines if re.match(r"^> Task .* FAILED$", line)]
    tests = [line for line in lines if re.search(r"\d+ tests? (completed|successful|failed|skipped)", line)]
    warnings = [line for line in lines if re.search(r"deprecated|deprecation|configuration cache|cache miss", line, re.I)]
    dependencies = [line for line in lines if re.search(r"Could not (resolve|GET|HEAD)|timed out|HTTP.*(401|403|404)|artifact.*not found", line, re.I)]
    headlines = []
    in_failure = False
    for line in lines:
        if line == "* What went wrong:":
            in_failure = True
        elif line.startswith("* "):
            in_failure = False
        elif in_failure and line.strip():
            headlines.append(line)
    report = {
        "status": "FAILED" if status else ("SUCCESS" if builds and builds[-1].startswith("BUILD SUCCESSFUL") else "UNKNOWN"),
        "exitCode": status,
        "launcherPid": launcher_pid,
        "launcherProcessGroup": launcher_pid,
        "interruptedBy": interrupted_by,
        "totalTime": elapsed,
        "log": str(log),
        "command": [public_line(arg) for arg in command],
        "failedTasks": failed,
        "failedTests": [line for line in lines if re.search(r"[A-Za-z0-9_.$]+ > [A-Za-z0-9_.$()]+ FAILED$", line)],
        "exceptionHeadlines": headlines[:20],
        "warnings": warnings[:30],
        "tests": {"total": None, "failed": None, "skipped": None, "modules": [], "observedSummaryLines": tests},
        "slowTasks": [],
        "depIssues": dependencies[:20],
        "actions": ["Inspect retained XML/JFR for exact test populations; build success alone is not coverage."],
    }
    directory = Path("build/reports/claude")
    directory.mkdir(parents=True, exist_ok=True)
    (directory / "gradle-summary.json").write_text(json.dumps(report, indent=2) + "\n")
    summary = ["# Gradle summary", "", "Status: {} (exit {})".format(report["status"], status),
               "Elapsed: {:.2f}s".format(elapsed), "Log: `{}`".format(log), "",
               "Counts and task timings not present in the log are unknown, not zero.",
               "Retained XML/JFR must be inspected separately for nonzero cases, failures and skips."]
    for title, entries in [("Build", builds[-1:]), ("Failed tasks", failed), ("Exceptions", headlines[:10]),
                           ("Test summaries", tests[-15:]), ("Warnings/cache", warnings[:15]),
                           ("Dependency/network", dependencies[:10])]:
        summary.extend(["", "## " + title] + ["- " + line for line in entries])
    (directory / "gradle-summary.md").write_text("\n".join(summary) + "\n")
    return report


def signal_process_group(group, sig):
    """Ignore Darwin's EPERM for an exited group, but never hide a live cleanup failure."""
    try:
        os.killpg(group, sig)
    except ProcessLookupError:
        # The owned process group already exited; no signal remains to deliver.
        pass
    except PermissionError:
        # XNU's killpg1 filters zombies and returns EPERM when no eligible member remains.
        states = subprocess.check_output(["ps", "-ax", "-o", "pgid=,stat="], text=True)
        for line in states.splitlines():
            fields = line.split()
            if len(fields) >= 2 and int(fields[0]) == group and not fields[1].startswith("Z"):
                raise


def main(args):
    """Own the Gradle process group, preserve its exit status, and report even on failure."""
    for directory in ("build/logs", "build/reports/claude", ".claude/out"):
        Path(directory).mkdir(parents=True, exist_ok=True)
    args = args or ["build"]
    label = re.sub(r"[^A-Za-z0-9_.-]", "_", args[0])
    stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S-%f")
    log = Path("build/logs/{}-{}-{}.log".format(stamp, label, os.getpid()))
    command = ["./gradlew"] + args + ["-i", "--console=plain"]
    print("Logging full Gradle output to: {}".format(log), flush=True)
    started = time.monotonic()
    child = None
    timer = None
    interrupted = None

    def kill_group(sig):
        if child is not None:
            signal_process_group(child.pid, sig)

    def stop(signum, frame):
        nonlocal interrupted, timer
        if interrupted is None:
            interrupted = signum
            kill_group(signal.SIGTERM)
            timer = threading.Timer(10, kill_group, args=(signal.SIGKILL,))
            timer.daemon = True
            timer.start()

    previous = {sig: signal.signal(sig, stop) for sig in (signal.SIGINT, signal.SIGTERM)}
    status = 1
    completed = False
    stage = "Log sink"
    try:
        with os.fdopen(os.open(str(log), os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o600), "w") as output:
            stage = "Gradle launcher"
            child = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                     start_new_session=True, text=True, errors="replace", bufsize=1)
            if interrupted is not None:
                kill_group(signal.SIGTERM)
            stream = iter(child.stdout)
            while True:
                stage = "Gradle stream"
                try:
                    line = next(stream)
                except StopIteration:
                    break
                stage = "Log sink"
                output.write(line)
                output.flush()
                if PROGRESS.search(line) and not re.search(r" (SKIPPED|UP-TO-DATE|NO-SOURCE)\s*$", line):
                    stage = "Progress sink"
                    print(line, end="", flush=True)
            stage = "Gradle wait"
            wait_status = child.wait()
            status = 128 - wait_status if wait_status < 0 else wait_status
            stage = "Log sink"
        completed = True
    except OSError as error:
        # A failed sink cannot be used to report its own failure.
        print("{} failed: {}".format(stage, error), file=sys.stderr)
        status = 127 if child is None and stage == "Gradle launcher" else 1
    finally:
        try:
            if child is not None:
                # Exceptional exits also own descendants after their launcher exits.
                try:
                    if not completed or interrupted is not None:
                        kill_group(signal.SIGKILL)
                finally:
                    try:
                        child.stdout.close()
                    except OSError as error:
                        print("Gradle pipe close failed: {}".format(error), file=sys.stderr)
                        status = status or 1
                    finally:
                        child.wait()
        finally:
            if timer is not None:
                timer.cancel()
            for sig, handler in previous.items():
                signal.signal(sig, handler)
    if interrupted is not None:
        status = 128 + interrupted
    try:
        report = summarize(log, status, time.monotonic() - started, command,
                           child.pid if child is not None else None, interrupted)
    except OSError as error:
        print("Summary failed: {}".format(error), file=sys.stderr)
        return status or 1
    print("Gradle exit: {}. Full log at: {}".format(status, log))
    if status:
        print("=== What went wrong ===")
        print("\n".join(report["exceptionHeadlines"][:20]))
        print("=== Failing tasks/tests ===")
        print("\n".join(report["failedTasks"][:10] +
                        report["tests"]["observedSummaryLines"][:5] +
                        report["failedTests"][:20]))
    print("build/reports/claude/gradle-summary.md\nbuild/reports/claude/gradle-summary.json")
    return status


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
