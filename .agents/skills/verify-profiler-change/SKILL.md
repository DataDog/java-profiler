---
name: verify-profiler-change
description: Which builds and tests a java-profiler change must pass before it is called done, by kind of change (C++, signal handlers and atomics, JVM-specific code, libc-sensitive code, Java, build logic, scripts and hooks, docs and skills). Use before claiming that a change works, is fixed or is done, and when planning acceptance criteria.
---

# Verify a profiler change

Run the checks for every kind of change the diff contains, and report each as `passed`,
`failed`, `blocked` or `inconclusive`. Run Gradle only through
`./.claude/commands/build-and-summarize <task>`. Commands, container flags and the CI
tiers that run later are in `doc/building/TestingGuide.md`.

| The change touches | Run locally before calling it done |
| --- | --- |
| C++ under `ddprof-lib/src/main/cpp/` | `:ddprof-lib:gtestDebug`; add `:ddprof-test:testDebug` when Java-visible behavior can change |
| Signal-handler paths, atomics, crash protection, thread lifecycle | The C++ row, plus `gtestAsan` and `testAsan` where the sanitizer is available (Linux glibc), plus the aarch64 container (`./utils/run-containers-tests.sh --arch=aarch64 ...`) when there is no arm64 host: memory-ordering bugs show only there |
| JVM-implementation code (`hotspot/`, `j9/`, `zing/`) | `testDebug` against that JVM: `JAVA_TEST_HOME` set to it, or the container with the matching `--jdk` (for example `17-j9`) |
| libc-sensitive code (allocation hooks, `dlopen`, symbol lookup, TLS) | The matching row, plus the musl container (`--libc=musl`) |
| Java code or the Java API | `:ddprof-test:testDebug`, or the narrowest `-Ptests=` filter that covers the change, then the full suite before review |
| `build-logic/` or Gradle files | `assembleAll`, and the tasks the change affects |
| Scripts and hooks under `utils/`, `.claude/`, `.pi/`, `.githooks/` | The matching `utils/tests/*.sh` suites. Run the Pi adapter cases with Node.js 22 or newer: older Node.js skips them. CI scripts also follow the `ci-script-change` skill. |
| Docs, skills, `AGENTS.md` | `:ddprof-lib:qualityChecks`, or its `utils/check-*.py` scripts directly |

- **A test you add must fail without the change.** For a bug fix, show it fail before the
  fix and pass after. Assert that the scenario was reached, not only that some result
  exists.
- **Flaky failures:** re-run once. If the retry passes, record the first failure and the
  retry. If it fails again, treat it as a real failure until shown otherwise.
- **When a check cannot run here** (no sanitizer runtime, no container runtime, no arm64),
  report it as `blocked` with the reason, and name the CI job that covers it. Never report
  it as passed.
