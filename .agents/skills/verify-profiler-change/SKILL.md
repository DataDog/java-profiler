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
| Signal-handler paths, atomics, crash protection, thread lifecycle | The C++ row, plus `gtestAsan`, `gtestTsan` and `testAsan` where the sanitizers are available (Linux glibc), plus the aarch64 container (`./utils/run-containers-tests.sh --arch=aarch64 ...`) when there is no arm64 host: memory-ordering bugs show only there |
| JVM-implementation code (`hotspot/`, `j9/`, `zing/`, or shared code that branches on `VM::isHotspot()`, `VM::isOpenJ9()` or `VM::isZing()`) | `testDebug` against each affected JVM: `JAVA_TEST_HOME` set to it, or the container with the matching `--jdk` (for example `17-j9`). The containers have no Zing JDK; check the JDK matrix in `.github/workflows/test_workflow.yml` for a `-zing` entry before claiming CI coverage |
| libc-sensitive code (allocation hooks, `dlopen`, symbol lookup, TLS) | The matching row, plus the musl container (`--libc=musl`) |
| Java code or the Java API | `:ddprof-test:testDebug`, or the narrowest `-Ptests=` filter that covers the change, then the full suite before review |
| `build-logic/` or Gradle files | `assembleAll`, and the tasks the change affects |
| Scripts and hooks (`utils/`, `.github/scripts/`, `.gitlab/**`, `.claude/`, `.pi/`, `.githooks/`) | The test suites in the `tests/` directories next to them (`git ls-files '*/tests/*'`). The Pi adapter cases need Node.js 22.6 or newer (`--experimental-strip-types`); older versions skip them, which is not a pass. Scripts that CI, Gradle or hooks run also follow the `ci-script-change` skill. |
| Docs, skills, `AGENTS.md` | `:ddprof-lib:qualityChecks`. Running its `utils/check-*.py` scripts directly skips the signal-reachability check, which needs the debug build. |

- **Flaky failures:** re-run once. If the retry passes, record the first failure and the
  retry. If it fails again, treat it as a real failure until shown otherwise.
- **When a check cannot run here** (no sanitizer runtime, no container runtime, no arm64
  host, no Zing), report it as `blocked` with the reason. Name the CI job that covers it,
  found in `.github/workflows/` or `.gitlab-ci.yml`, or state that none does. Never
  report it as passed.
