#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc

"""Run the release CLI, optionally answering prompts through a real terminal."""

import errno
import os
import pty
import select
import signal
import sys
import time


def main():
    """Forward the CLI exit status and script terminal replies when requested."""
    command = ["bash", *sys.argv[1:]]
    if "CLI_PTY_REPLIES" not in os.environ:
        os.execvp(command[0], command)

    replies = iter(os.environ["CLI_PTY_REPLIES"].split("\n"))
    prompt = b"[y/N]: "
    pending = b""
    child_pid, terminal = pty.fork()
    if child_pid == 0:
        os.execvp(command[0], command)

    try:
        deadline = time.monotonic() + 30
        while True:
            if time.monotonic() >= deadline:
                raise RuntimeError("interactive release test timed out")
            readable, _, _ = select.select([terminal], [], [], 0.1)
            if not readable:
                continue
            try:
                output = os.read(terminal, 4096)
            except OSError as error:
                if error.errno == errno.EIO:
                    break
                raise
            if not output:
                break
            sys.stdout.buffer.write(output)
            sys.stdout.buffer.flush()
            pending += output
            while prompt in pending:
                pending = pending.split(prompt, 1)[1]
                reply = next(replies).encode()
                # Ctrl-C and Ctrl-D exercise terminal interrupt and EOF handling.
                os.write(terminal, reply if reply in (b"\x03", b"\x04") else reply + b"\n")
        _, status = os.waitpid(child_pid, 0)
    except BaseException:
        try:
            os.killpg(child_pid, signal.SIGKILL)
        except ProcessLookupError:
            # The child may have exited and its process group disappeared before cleanup.
            pass
        os.waitpid(child_pid, 0)
        raise
    finally:
        os.close(terminal)

    result = os.waitstatus_to_exitcode(status)
    return result if result >= 0 else 128 - result


if __name__ == "__main__":
    sys.exit(main())
