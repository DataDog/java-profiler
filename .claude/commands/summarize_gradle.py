#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Capture Gradle output and status locally, including on failure or interruption."""

import ctypes
import datetime
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time


def adopt_gradle_descendants(args):
    """Own detached single-use daemons on Linux, not just the launcher session."""
    if sys.platform != "linux" or "--no-daemon" not in args:
        return False
    libc = ctypes.CDLL(None, use_errno=True)
    # PR_SET_CHILD_SUBREAPER: orphaned descendants reparent here rather than PID 1.
    if libc.prctl(36, 1, 0, 0, 0) != 0:
        raise OSError(ctypes.get_errno(), "cannot own Gradle descendant processes")
    return True


def reap_adopted_children():
    """Terminate and reap only children adopted by this wrapper's subreaper."""
    children_file = Path("/proc/self/task") / str(os.getpid()) / "children"
    started = time.monotonic()
    signalled = set()
    while True:
        while True:
            try:
                pid, _ = os.waitpid(-1, os.WNOHANG)
            except ChildProcessError:
                return
            if pid == 0:
                break
        children = [int(pid) for pid in children_file.read_text().split()]
        for pid in children:
            sig = signal.SIGKILL if time.monotonic() - started >= 10 else signal.SIGTERM
            if (pid, sig) not in signalled:
                try:
                    os.kill(pid, sig)
                except ProcessLookupError:
                    pass
                signalled.add((pid, sig))
        time.sleep(0.02)


def main(args):
    """Forward arguments unchanged and publish evidence, not inferred test passes."""
    args = args or ["build"]
    for directory in ("build/logs", "build/reports/claude", ".claude/out"):
        Path(directory).mkdir(parents=True, exist_ok=True)
    stamp = datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%d-%H%M%S-%f")
    label = args[0].replace("/", "_").replace(":", "_")
    log = Path("build/logs") / (stamp + "-" + label + ".log")
    command = ["./gradlew"] + args
    if not any(arg in ("-i", "--info", "-d", "--debug") for arg in args):
        command.append("-i")
    if not any(arg == "--console" or arg.startswith("--console=") for arg in args):
        command.append("--console=plain")
    interrupted = []
    process = None
    subreaper = False

    def interrupt(signum, frame):
        interrupted.append(signum)
        if process is not None:
            try:
                os.killpg(process.pid, signal.SIGTERM)
            except ProcessLookupError:
                pass

    previous = {sig: signal.signal(sig, interrupt) for sig in (signal.SIGINT, signal.SIGTERM)}
    print("Logging full Gradle output to: " + str(log), flush=True)
    try:
        with log.open("wb") as output:
            try:
                subreaper = adopt_gradle_descendants(args)
                process = subprocess.Popen(command, stdout=output, stderr=subprocess.STDOUT,
                                           start_new_session=True)
                termination_started = None
                while True:
                    try:
                        status = process.wait(timeout=0.2)
                        break
                    except subprocess.TimeoutExpired:
                        if interrupted:
                            if termination_started is None:
                                termination_started = time.monotonic()
                            elif time.monotonic() - termination_started >= 10:
                                os.killpg(process.pid, signal.SIGKILL)
                if status < 0:
                    status = 128 - status
            except OSError as error:
                output.write((str(error) + "\n").encode())
                status = 127
            finally:
                # Gradle is run without a persistent daemon by qualification callers.
                # Reap any still-owned descendants after their launcher exits.
                if process is not None:
                    try:
                        os.killpg(process.pid, signal.SIGKILL)
                    except ProcessLookupError:
                        pass
                if subreaper:
                    reap_adopted_children()
        if interrupted:
            status = 128 + interrupted[0]
        lines = log.read_text(errors="replace").splitlines()
        build = next((line for line in reversed(lines) if line.startswith("BUILD ")), "No BUILD status")
        report = {"command": command, "log": str(log), "exitCode": status,
                  "buildStatus": build, "testAcceptance": "not evaluated; inspect fresh XML populations"}
        root = Path("build/reports/claude/gradle-summary")
        root.with_suffix(".json").write_text(json.dumps(report, indent=2) + "\n")
        root.with_suffix(".md").write_text(
            "# Gradle summary\n\n" + build + "\n\nExit status: " + str(status)
            + "\n\nFull log: `" + str(log) + "`\n\nTest acceptance requires fresh XML counts and skips.\n")
        print(build + " (exit " + str(status) + ")", flush=True)
        print(str(root.with_suffix(".md")))
        print(str(root.with_suffix(".json")))
        return status
    finally:
        for sig, handler in previous.items():
            signal.signal(sig, handler)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
