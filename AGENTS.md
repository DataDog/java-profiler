<!-- cairn:knowledgebase begin (managed by cairn; do not edit manually) -->
## Cairn knowledgebase (optional)

If `.knowledgebase/memories/` exists, this repo carries distilled
institutional memory from past cairn investigations (confirmed findings
and refuted dead ends); if your harness also provides the cairn-memory
skill, consult it before design, implementation, or review work here.
If cairn is not available in your environment, skip this section —
nothing else in this file depends on it.
<!-- cairn:knowledgebase end -->

**`.knowledgebase/` is written only by the cairn skills** (a hook blocks file-tool edits;
`qualityChecks` checks the memory frontmatter). New memories travel with the change they
came from, in its PR or a stacked one. Reviews skip their content: no threads, findings
or suggested edits on memory files.

# AGENTS.md

This file provides guidance to AI coding assistants when working with code in this
repository. It is deliberately a thin index: rules that must always be in context live
here; subsystem details live in `doc/` (start at the [doc/README.md](doc/README.md)
index).

> **⛔ MANDATORY — KEEP THIS FILE CURRENT.** Any change to the architecture — a new
> subsystem, a removed or disabled subsystem, a changed subsystem contract (buffering
> scheme, engine, storage layout, build system, module list, JDK pattern, CI layout) —
> REQUIRES updating this file in the same change set: the affected section here or in
> `ddprof-lib/src/main/cpp/AGENTS.md` (native code), the linked `doc/` detail page,
> and the [doc/README.md](doc/README.md) index entry (add or remove). An architecture
> change that lands without its AGENTS.md/doc update is an incomplete change — treat it
> as a failing check, not a nice-to-have.

**What stays inline vs. what moves to `doc/`** — apply this test when updating this
file. Inline (this file, or `ddprof-lib/src/main/cpp/AGENTS.md` for rules that bind
only native code): rules that must shape behavior at unpredictable moments —
invariants whose violation causes crashes/leaks/lockups, rules for writing code and code
comments. Externalized (`doc/`): reference material read only when
working on a specific subsystem — architecture pages, build/task references,
analyses. Procedures run at a known moment go in skills (`.agents/skills/`, which
load fresh when invoked); enforcement goes in scripts, hooks and CI — text here is
advisory and cannot gate anything. A skill's `description` carries the obligation to
run it; this file points to a skill only when a test drive shows that the description
alone does not load it. Rules stay inline even when needed only once per
task if that moment is end-of-task and no skill carries them.
This layering and the work-tracking process follow the Datadog AI Native SDLC Playbook,
a Datadog-internal Confluence page. Read it only when planning tracked work, changing
the process, or changing the agent configuration (`AGENTS.md`, `.agents/skills/`,
`.claude/`, `.pi/`, `.githooks/`). Agents find it with the Atlassian Confluence tools
by its title; without Datadog access, skip it.
Skipping a linked page silently is forbidden: if you touched code covered by a
`doc/` page you did not read (context pressure, time), you MUST disclose it in the
task summary with an explicit `SUBSYSTEM DOC NOT READ: <path>` line — the user,
not you, decides whether to compact and redo the work with the rules in context,
or accept the risk. The same applies to any instruction in this file you could not
follow: surface it, never absorb it.
Hoist a section only when it grows with examples or scope. Leave a one-line mandatory
pointer behind when it moves to `doc/`; a section that moves into a skill follows the
skill-pointer rule above.
Update this file from repeated failures: when an agent repeats a mistake or needs
the same undocumented explanation twice, it proposes a concise correction here
(or to the affected `doc/` page or skill); the responsible team reviews it, and
stale instructions are removed.

## Project Overview

The Datadog Java Profiler Library — a profiler derived from async-profiler but tailored
for Datadog's needs. Java 8+ API, C++17 native engine, custom Gradle native-build plugin,
JNI integration, Google Test for C++ units.

**Modules** (`settings.gradle.kts`): `ddprof-lib` (main library, plus `:ddprof-lib:fuzz`
and `:ddprof-lib:benchmarks`), `ddprof-test` (Java integration tests), `ddprof-test-tracer`
(tracing-context tests), `ddprof-test-native`, `ddprof-stresstest` (JMH + chaos),
`malloc-shim` (Linux allocation interceptor), `demo-java-leak` (deployable
dependency-free leak-demo app; not published).

**Supported JVMs:** HotSpot, J9, Zing; HotSpot continuation recovery uses instruction phases (compiled/interpreted entries and x64/arm64 exception exits, including recognized resolver returns), validated metadata for return-barrier entries and interiors (positive-argument OSR layouts use validated entries, not guessed padding), and retires consumed Java anchors — see [doc/architecture/JvmSupportLayer.md](doc/architecture/JvmSupportLayer.md).
**Platforms:** Linux x64/arm64 (primary), macOS arm64/x64; musl libc handled automatically.
Frozen virtual-thread caller recovery uses bounded, read-only heap chunk traversal
on supported HotSpot layouts and collectors; see [doc/architecture/FrozenStackWalker.md](doc/architecture/FrozenStackWalker.md).

## Operating Rules for Agent Sessions

- Never run `./gradlew` directly. Always invoke the wrapper:
  `./.claude/commands/build-and-summarize <gradle-task...>`. It runs Gradle with
  `--console=plain -i`, captures the full output into `build/logs/<timestamp>-<task>.log`,
  and prints only the status line. On failure, read the wrapper's extracted
  "What went wrong" section and the failing task/test lines; grep the log for anything
  rarer. If no log path is given, use the newest `build/logs/*.log`. In Claude Code and
  Pi the `require-gradle-wrapper` hook denies direct `gradlew` calls, except
  `--stop` and `--version`.
- Never paste large log chunks into chat. If more than ~30 lines are needed, write to a
  file and point at it.
- If a step fails, print the failing command and a one-line hint, then stop.
- "build assembleDebugJar" means `./.claude/commands/build-and-summarize assembleDebugJar`.
- When renaming a symbol or concept, grep for the old name and update function names, comments and the PR title/description to the new name before requesting review.

## Build & Test Quick Reference

Configurations: `release`, `debug`, plus `asan`/`tsan`/`fuzzer` when the sanitizer runtime
is found for the selected compiler (inactive on macOS and musl), plus opt-in `coverage`
with `-PenableCoverage` (`:ddprof-lib:coverageReport`; the C++ report covers only the
`-O0 -DDEBUG` build — see [doc/building/CodeCoverage.md](doc/building/CodeCoverage.md)).

```bash
./.claude/commands/build-and-summarize buildRelease      # release library + JAR
./.claude/commands/build-and-summarize assembleAll       # all active configurations
./.claude/commands/build-and-summarize :ddprof-test:testDebug -Ptests=ClassName.methodName
./.claude/commands/build-and-summarize :ddprof-lib:gtestDebug            # all C++ tests (debug)
./.claude/commands/build-and-summarize :ddprof-lib:gtestDebug_test_callTraceStorage
JAVA_TEST_HOME=/path/to/test/jdk ./.claude/commands/build-and-summarize :ddprof-test:testDebug
```

- `buildRelease`/`buildDebug`/`buildAsan`/`buildTsan` are Gradle base-plugin
  rule-resolved aliases (`build<ConfigurationName>`) for
  `compile{Config} → link{Config} → assemble{Config}Jar`. They do not appear in
  `tasks --all`. Do not use the bare `assemble` task.
- Single Java test: `-Ptests=ClassName` / `-Ptests=ClassName.methodName` / `-Ptests="*.Pattern"`
  — unified across glibc, macOS and musl platforms.
- CStack templates with no safe declared mode are disabled before per-test callbacks and
  profiler setup; constructor injection still runs. See [TestingGuide.md](doc/building/TestingGuide.md).
- Flaky native gtests: the Tier 1 GitLab jobs gate through `ddprof-test/quarantine.txt`
  with cell `glibc-<config>-<arch>` (see [doc/building/TestingGuide.md](doc/building/TestingGuide.md),
  Tier 1) — a flaky gtest gets an entry with a PROF ticket, same as the Java cells.
- Flaky dd-trace-integration cells: the Tier 3 GitLab jobs gate through
  `post-pr-comment.sh`, and a flaky cell+scenario is quarantined in
  `.gitlab/dd-trace-integration/quarantine.txt` with a PROF ticket and an expiry
  (see [doc/building/TestingGuide.md](doc/building/TestingGuide.md), Tier 3).
- Useful properties: `-Pskip-native`, `-Pskip-tests`, `-Pskip-gtest`, `-PkeepJFRs`,
  `-PenableFaultInjection`, `-PenableSamplerPerf` (the last two only affect
  release/debug builds). There is **no** `-Pskip-debug-extraction` property: debug-symbol
  extraction and stripping happen unconditionally inside `linkRelease`.
- Code quality: `spotlessApply` before committing (CI fails on `spotlessCheck`),
  `qualityChecks` (source invariants, copyright headers, `CLAUDE.md` and the native-code
  stubs), `scanBuild` (Linux only), `:ddprof-stresstest:runStressTests`,
  `:ddprof-lib:runBenchmarks`.
- Container-based testing (ASan, aarch64, musl, CI repro): `./utils/run-containers-tests.sh`
  — defaults to podman; on macOS use either podman or Docker through colima
  (`--container=docker` after `colima start` — check availability with
  `podman info` / `docker info` and pick the runtime whose daemon answers).
  Full flags in
  [doc/building/TestingGuide.md](doc/building/TestingGuide.md).

Full task reference: [doc/building/GradleTasks.md](doc/building/GradleTasks.md). Native issues:
debug symbols via `buildDebug`, memory errors via ASan, suppressions in
`gradle/sanitizers/*.supp`, and `sudo sysctl vm.mmap_rnd_bits=28` if ASan crashes occur.

## Build System Architecture

Custom Kotlin-based native build plugin (`build-logic/`) instead of Gradle's
`cpp-library`/`cpp-application` plugins; it invokes `clang++`/`g++` directly. Build
configurations are discovered dynamically from `ConfigurationPresets.kt`, never hardcoded.
Google Test entry-point archives precede their dependencies so architecture-gated
test files also link on hosts where they register no cases.
Two-JDK pattern: `JAVA_HOME` (build, JDK 17+, Gradle runs on 21 LTS) runs Gradle;
`JAVA_TEST_HOME` runs tests against the target JDK; target bytecode is Java 8 via
`--release 8`.

The `ddprof-stresstest:chaosElements` outgoing configuration shares the chaos JAR
with `ddprof-test` stack-correctness tests. See
[TestingGuide.md](doc/building/TestingGuide.md#virtual-thread-remount-correctness).

Details and troubleshooting:
[build-logic/README.md](build-logic/README.md),
[doc/building/NativeBuildPlugin.md](doc/building/NativeBuildPlugin.md) (task DSL, debug-symbol
extraction, artifact layout),
[doc/building/BuildSystemGuide.md](doc/building/BuildSystemGuide.md) (Java formatting and convention-test CI),
[doc/building/Versioning.md](doc/building/Versioning.md) (version from git tags),
[doc/building/JdkUpgrades.md](doc/building/JdkUpgrades.md) (JDK upgrade touchpoints).

## Architecture

[doc/README.md](doc/README.md) indexes the detail page of every subsystem. Read the page
before you change its subsystem.

**Native code.** Before you change code in `ddprof-lib/src/main/cpp`,
`ddprof-lib/src/test/cpp`, `ddprof-lib/src/test/fuzz` or `malloc-shim/src`, read
[ddprof-lib/src/main/cpp/AGENTS.md](ddprof-lib/src/main/cpp/AGENTS.md) unless it is
already in your context. It holds the Critical Invariants and the index of the native
subsystems.

Key source locations: Java API `ddprof-lib/src/main/java/com/datadoghq/profiler/JavaProfiler.java`;
C++ engine `ddprof-lib/src/main/cpp/` (implementation-specific code under `hotspot/`, `j9/`,
`zing/`); native libraries `ddprof-lib/build/lib/main/{config}/{os}/{arch}/`; gtest tests
`ddprof-lib/src/test/cpp/`; Java tests `ddprof-test/src/test/java/`.

## Development Guidelines

- Never replace the code you work on with stubs. Never "fix" tests by testing constants
  against constants. Never claim success until all affected tests pass.
  `assert()` is compiled out of release builds (`-DNDEBUG`): never rely on it for safety
  and never put side effects in it.
- Platform-specific code goes in per-OS implementation files (`os_linux.cpp`,
  `os_macos.cpp`, `libraryPatcher_linux.cpp`, etc.), never in a single shared file guarded
  by `#ifdef`. Name new files `<module>_<os>.cpp`.
- Provide javadoc for public classes and methods, and for non-trivial private/package-private
  code, including C++ algorithms (probing/compaction loops, index management,
  randomization): state the invariant and why the approach is needed. Verify every javadoc
  claim (thread safety, ownership, nullability, return values, clearing semantics, failure
  modes) against the implementation; public Javadoc must not reference private symbols.
- Provide comprehensive tests for new functionality: every branch, marker and error path
  (including CI and shell scripts) needs a test that fails when that branch is removed or
  mistyped — every new guard and boundary branch (null inputs, exact size/index limits,
  first value rejected past a capacity), counter label and RAII guard contract, and every
  new branch in concurrency, eviction, overflow and aging logic. Tests that exercise only
  an empty or trivial state, and manual runs, do not count. Each test must assert its
  claim (no print-only checks), fail if the behavior it names is removed, and not
  duplicate another test's assertions. Tests must fail fast on missing data: assert that
  JFR fields and accessors the event requires are non-null before any loop, and cover
  every event field and code path the feature writes.
- Bug fixes need a test in the same PR, not a follow-up: it fails before the fix and
  passes after. Native-only fixes need a gtest in `ddprof-lib/src/test/cpp`. Assert that
  the scenario was actually reached (e.g. threshold crossed, signals suppressed), not just
  that some result exists.
- Treat caller contract violations (null arguments, mismatched array lengths, an operation
  that must never fail in a test) as bugs: throw instead of returning false or
  incrementing a failure counter, and do not add validation that duplicates what the loop
  already checks.
- Explain in a comment why a non-obvious call, init-order assumption, sentinel return value
  (e.g. 0 meaning miss/full), omitted lock, unsynchronized access or read of a specific
  buffer (e.g. standby) is safe, and why a workaround or test exclusion exists.
- Keep code lean and easy to follow; factor self-contained code into short functions with
  explicit names. Datadog-specific extensions are integrated directly into base files (e.g.
  `stackWalker.h`); exclude `ddprof-lib/build/async-profiler` from usage searches.
- Java code on context and sampling paths (e.g. `ContextValueCache`, `ContextSetter`)
  minimizes allocations: no string concatenation, boxing or varargs there, also when
  building error or label strings.
- Copyright: new source files (including tests) start with the short header
  `Copyright <current year>, Datadog, Inc.` — no full license text block. When modifying
  an existing Datadog copyright, update the end year (e.g. `2025, 2026, Datadog`) in every
  file the change touches, including test, moved and refactored files. Preserve all other
  copyrights. Add a copyright line to modified C/C++/Java/Kotlin files missing one; CI and
  config files (Dockerfiles, `.gitlab/**`) are exempt. Enforced in CI:
  `utils/check-copyright.py` (part of `qualityChecks`) checks the files a branch adds or
  modifies.
- Commits: logical chunks. Never commit files from other projects or scratch files.
  **Never commit design artifacts automatically** — plans, specs, review reports, audit
  findings, session notes, analysis dumps — even when they live in the repo tree. Always
  ask for permission first and commit them only if the user explicitly says so.
- Scope: keep each PR scoped to its stated purpose. Put unrelated production changes
  (e.g. a separate bug fix found while working), renames and cleanups in their own PR, do
  not add code with no production caller (stage it in the PR that needs it), and do not
  delete passing tests without stating why. When a change alters behavior described in
  `doc/` or in comments, update those in the same PR.
- C/C++ style: match the surrounding indentation and spacing exactly; don't split inline
  logic into helpers unless reused or genuinely hard to follow; extract code that appears a
  second time (e.g. in copy constructors, assignment operators) into one shared helper; use
  `static_cast`/`reinterpret_cast`, not C-style casts; give file-local helpers internal
  linkage (`static`); no commented-out code, redundant `inline` on in-class or constexpr
  definitions, redundant access specifiers, or redundant conditions — a disjunct equivalent
  to an adjacent check is dead; remove it, or keep it only as a deliberate defensive guard
  whose comment does not claim it catches a distinct case; add duplicated fast-path variants
  (e.g. `JavaCritical_*`) only for demonstrably performance-critical methods.
- **Comment budget.** Before finishing any change, prune every comment and javadoc you
  wrote: each comment ≤3 lines, each line a distinct constraint (a non-obvious
  mechanism, invariant, or consequence) the reader could not get from the code. A
  longer comment needs a reason a reviewer would accept; prefer cutting — a verbose
  comment is review surface, not safety. The same cut applies to `doc/` paragraphs and
  PR descriptions. No tool enforces this, because it takes judgment; the `pre-pr-review`
  skill checks it.
- Comments: "why" comments must reference concrete mechanisms (e.g. "ASAN's allocator
  lock is reentrant"), never speculative claims about HotSpot/glibc/ASAN/ISA internals — if
  unsure, describe the observable symptom. Describe current behavior, not history; cite no
  tickets, plan documents, design docs, review reports, "phase N" or line numbers (refer
  to symbols) — in comments and in `doc/` alike. Name each
  thread or actor explicitly. Scope words ("only", "every", "never blocks", "single-threaded",
  "no lock needed") and invariants (e.g. "always leaves a terminator") must hold on every
  branch and for every caller thread, including early returns, timeouts and `siglongjmp`.
  Check the actual callers before claiming a context (signal handler vs JNI). Prefer a
  named `constexpr` over a comment restating a magic number. Comments on workarounds state
  what breaks without them (symptom, JDK/arch/libc) and when they can be removed. State
  each fact once, and omit comments that restate an obvious bounds check. After any
  change, refactor or API rename, re-read the nearby comments against the final diff and
  grep for the old name or behavior (including headers, tests and callers' comments).
  Proofread comments, javadoc and exception messages. Hold user-facing operational
  messages (error/warning logs, script and CLI output) to the same standard of accuracy:
  state only what is known to be true, and recommend only next steps that can actually
  succeed — never advise a retry that cannot clear the condition, never report a pending
  state (e.g. a run awaiting approval) as failed, and never warn that something may still
  be running when it is known to be terminal.
- **RAII for every acquire/release pair** (C/C++). A lock, a heap allocation, or a flag
  that must be restored is released by a guard or owner destructor, not by a manual call
  at each exit. Reuse `SharedLockGuard`, `ExclusiveLockGuard`, `OptionalSharedLockGuard`,
  `MutexLocker`, `CriticalSection` before you add a type. A new owner type is non-copyable
  and hands over ownership explicitly (the receiver sets the owner's pointer to `nullptr`).
  A manual pair needs a comment that says why a guard scope cannot express it. In code that
  shares a lock with signal handlers, end an owner that frees memory outside the exclusive
  critical section, because its destructor frees at scope end.
- Always challenge proposals with deep analysis when you have hard evidence.

## Work Tracking

Work runs in four phases — Intent → Design → Build and Test → Deploy — with the
tracker ticket as the system of record: Jira (`PROF-<n>`) for Datadog engineers,
GitHub issues for external contributors. **Read [doc/WorkTracking.md](doc/WorkTracking.md)
before starting tracked work** — it is the phase-by-phase process reference; skipping
it must be disclosed per the rule at the top of this file. These rules always apply:

- **Verification first.** No transition happens on claims: acceptance criteria before
  code, tests and review before merge, production verification before closure. **Fix
  the code, not the expectation**; a criterion changes only with the engineer's sign-off.
  Agents own execution; humans approve the intent, the criteria, the merge and any
  rollout.
- **Evidence states.** Every check is reported as `passed` / `failed` / `blocked` /
  `inconclusive` — never prose summaries; observed results are kept separate from
  their interpretation; missing evidence means unverified. Evidence binds to the
  exact candidate — a changed candidate invalidates it. "It merged" is not done:
  closure requires the acceptance criteria demonstrably met and, for user-facing
  changes, verified in production.
- **Never weaken a gate.** The agent fixes failures — it never disables a required
  check, weakens an agreed expectation, or changes a tolerance to pass. Hooks,
  CI, and access control are authoritative even when a local hook does not fire;
  `AGENTS.md` and skills are advisory guidance.
- **A ticket on every PR.** The PR title or body references a Jira `PROF-<n>` key or
  a GitHub issue `#<n>`. Enforced in CI: the `PR ticket reference` workflow
  (`.github/workflows/pr-ticket.yml`) fails the PR otherwise; bot PRs are exempt.

The `bits-review-gate` workflow publishes the `bits-review/head` commit status
for PR heads targeting `main`; see [doc/BitsReviewMergeGateDesign.md](doc/BitsReviewMergeGateDesign.md)
for the design and its current activation status.

Isolation, parallel sessions and the rest of the tracking contract are in
[doc/WorkTracking.md](doc/WorkTracking.md) and enforced by review discipline. Existing
production-change guidelines and review rules still apply in full.
