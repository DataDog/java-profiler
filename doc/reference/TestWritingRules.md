# Copyright 2026, Datadog, Inc.
# Test-writing rules

AGENTS.md ("Provide comprehensive tests", "Bug fixes need a test in the same PR")
points here for the mechanics. Every rule below is a constraint a reviewer
enforces; a test that violates one does not count as covering the behavior it
names.

## A test must fail when the behavior is removed

- Before review, delete or invert each new guard, alternative and boundary
  comparison, or replace the code under test with a no-op or `return true`, and
  confirm that every test naming the behavior fails. Restore afterwards. A test
  that still passes is a print-only check, not coverage.
- A memory-ordering or fence claim needs a multi-threaded or stress test: a
  single-threaded write-then-read passes with or without the fence.
- Delete any test whose assertions another test already makes.

## A stub or fake must test the code, not itself

- A stub or fake (a `gh` stub, a fake test binary) answers only the exact
  query, selector or environment the code must send, and runs the code's own
  parsing (e.g. its `--jq` expression), so a wrong target or a broken parse
  fails the test.
- A test calls the production function it covers (give it a test-visible
  declaration if needed), never a copy of that function's mechanism
  re-implemented in the test file.
- Never "fix" tests by testing constants against constants.

## Pin derived constants independently of the code under test

- Instruction-decoder opcode/mask constants are derived from the ISA encoding
  diagrams (A64: ARM ARM DDI 0487) by bit arithmetic; each match is pinned by a
  gtest using encodings obtained independently of the decoder (assembler output
  or the manual), including sibling forms the mask must accept or reject
  (e.g. STP vs STNP, CBZ vs CBNZ).

## Gate capability-dependent tests on the exact preconditions

- Gate a test of a capability-dependent path (VM type, platform-thread
  classification, engine support) with `assumeTrue(<probe>)`, where the probe
  checks exactly the native preconditions that path checks: a broader gate
  skips working coverage, a narrower one fails on unsupported JVMs.
- Tests of date- or expiry-dependent logic freeze the clock (a shim exported to
  every child process) with fixture dates on both sides of the frozen date, and
  fail fast when the freeze does not hold.
- Test harnesses and CI scripts verify their own setup the same way: gate on a
  tool's exit status, not on its output file existing, and fail setup when a
  requested checker or mode is not active (e.g. `MALLOC_CHECK_` on glibc ≥ 2.34
  needs `libc_malloc_debug` preloaded; a profiler fallback WARN means the mode
  under test is off).

## Coverage counts only from the build that exercises the branch

- A test compiled only under `__FAULT_INJECTION__` (`-PenableFaultInjection`)
  covers a branch only if the PR names the CI job that builds with that flag;
  otherwise the branch also needs a default-build test.
- Set the flag that gates a branch (e.g. `use_debug=true`) and pair each
  rejected input with an accepted one, because a result such as `count() == 0`
  holds for any early exit.
- A CI script that scans sources for declarations (e.g. gtest
  `TEST`/`TEST_F`/`TEST_P`/`GTEST_TEST`) matches every declaration macro and
  every file extension the build compiles (including `.inc`), with one hermetic
  test case per form.
- Tests that exercise only an empty or trivial state, manual runs, and fuzz
  targets (nightly or `test:fuzz` label only) do not count.

## Concurrent and handoff results

- A test that runs work on helper threads or executors drains every `Future`,
  collects each worker `Throwable`, and fails once with all of them attached
  (`addSuppressed`) — never only the first.
- In tests and scenarios, check every boolean or nullable handoff result
  (`offer()`, `poll()`, a published value or tid) and throw with its context
  (round, attempt).
- Tests must fail fast on missing data: assert that JFR fields and accessors
  the event requires are non-null before any loop, and cover every event field
  and code path the feature writes.
- Report a setup failure with its own marker, never the marker of the result
  under test. Every runtime skip, drop, saturation or invalid-configuration
  path increments a counter named for that one cause; never reuse a counter
  documented for another.
