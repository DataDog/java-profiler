#!/usr/bin/env python3
"""
Streaming filter for Gradle test output.

Compresses verbose test logs:
  - PASSED tests:  single summary line; all buffered output (including [TEST::INFO]) discarded
  - FAILED tests:  full context emitted: STARTED line + buffered stdout/stderr + FAILED line
                   followed by exception/stack trace that comes after the FAILED marker
  - SKIPPED tests: single summary line
  - CRASHED tests: if the stream ends mid-test (JVM kill, OOM, sanitizer abort), the full
                   buffer is emitted with a warning header

Designed for inline use with `tee` so the unfiltered raw log is preserved:

    ./gradlew ... 2>&1 \\
      | tee -a "${RAW_LOG}" \\
      | python3 -u .github/scripts/filter_gradle_log.py

Exit code and PIPESTATUS:
    The filter always exits 0 regardless of test outcomes; use ${PIPESTATUS[0]} in bash
    to capture the Gradle exit code:

        ./gradlew ... 2>&1 | tee -a raw.log | python3 -u filter_gradle_log.py
        GRADLE_EXIT=${PIPESTATUS[0]}

Limitations:
  - [TEST::INFO] lines emitted from class-level lifecycle methods (@BeforeAll, static
    initializers) appear before any STARTED marker and are suppressed in OUTSIDE state.
    They remain visible in the raw log preserved by tee.
"""

import re
import sys

# Matches Gradle per-test event lines emitted by the Test task:
#
#   com.example.FooTest > testBar STARTED
#   com.example.FooTest > testBar[1] PASSED (0.456s)
#   com.example.FooTest > testBar(int) FAILED
#   com.example.FooTest > testBar SKIPPED
#
# The class name starts with a word character (not '>'), which prevents matching
# "> Task :project:taskName FAILED" build-level lines.
_TEST_EVENT = re.compile(
    r'^([\w.$][\w.$ ]* > \S.*?) (STARTED|PASSED|FAILED|SKIPPED)(\s+\([^)]+\))?\s*$'
)


def emit(line: str) -> None:
    print(line, flush=True)


def main() -> None:
    # --- States ---
    OUTSIDE = 0    # between tests: pass lines through directly
    BUFFERING = 1  # inside a running test: accumulate output
    FAILING = 2    # after FAILED marker: pass lines through until next test

    state = OUTSIDE
    buf: list = []

    for raw in sys.stdin:
        line = raw.rstrip('\n')
        m = _TEST_EVENT.match(line)

        if m:
            event = m.group(2)

            if event == 'STARTED':
                if state == BUFFERING:
                    # Previous test had no outcome line (shouldn't normally happen).
                    # Emit the buffer so we don't silently discard output.
                    for buffered_line in buf:
                        emit(buffered_line)
                elif state == FAILING:
                    emit('')  # blank line to visually separate failure blocks

                # Include the STARTED line in the buffer so it appears in failure output.
                buf = [line]
                state = BUFFERING

            elif event == 'PASSED':
                buf = []
                emit(line)
                state = OUTSIDE

            elif event == 'FAILED':
                # Emit everything collected since STARTED (includes [TEST::INFO] lines).
                for buffered_line in buf:
                    emit(buffered_line)
                buf = []
                emit(line)
                state = FAILING

            elif event == 'SKIPPED':
                buf = []
                emit(line)
                state = OUTSIDE

        elif state == BUFFERING:
            buf.append(line)

        else:
            # OUTSIDE or FAILING: pass through directly.
            # In FAILING state this captures exception lines, stack traces, etc.
            # In OUTSIDE state, suppress [TEST::INFO] lines: they originate from
            # class-level init (@BeforeAll, static blocks) and are noise when no
            # test has failed; the raw log still contains them for reference.
            if state == FAILING or not line.startswith('[TEST::INFO]'):
                emit(line)

    # EOF handling: if still inside a test the JVM likely crashed (SIGABRT from sanitizer,
    # OOM kill, etc.).  Emit everything so the failure is visible in the filtered log.
    if state == BUFFERING and buf:
        emit('# WARNING: stream ended inside a test (crash / OOM / sanitizer abort?)')
        for buffered_line in buf:
            emit(buffered_line)


if __name__ == '__main__':
    main()
