# Investigation Index

## Findings (confirmed)

### F-CONT-UNWIND: Continuation unwind version-gate bug (FIXED in PR #664)
`hotspotSupport.cpp:381` branch checked only `VMContinuationEntry::type_size() > 0`
to decide between the JDK 27+ path (contEntry() linked-list walk) and the JDK 21-26
fallback (fp-derivation). On Corretto JDK 26, `ContinuationEntry` IS exported in
`gHotSpotVMTypes` (type_size() > 0) but `JavaThread::_cont_entry_offset` is gated
`field_with_version(..., 27, MAX_VERSION)` so it stays `-1`. `contEntry()` returns
null (guard: `_cont_entry_offset < 0`), the branch aborts with `cont_entry_null`,
and carrier frames are never reached.

**Evidence:** counters from failing run on macOS arm64 + Corretto JDK 26:
`enter_special_hit: 493, cont_entry_null: 493` (unwind attempted, aborted).
After fix: `enter_special_hit: 510, cont_entry_null: 0`.

**Not macOS-specific** — would fail on Linux too with Corretto JDK 26. CI passes
because it runs JDK 21 (`JAVA_TEST_VERSION=21.0.3-tem`) where `type_size() == 0`
takes the working fallback branch.

**Fix:** added `VMStructs::hasContEntryOffset()` (`_cont_entry_offset >= 0`);
changed branch to `type_size() > 0 && hasContEntryOffset()`. When the offset is
unavailable, falls through to fp-derivation. Committed in PR #664.

### F-FLAKY-SLEEP: UnfilteredWallPrecheckTest sample-count boundary (FIXED in PR #664)
`unownedSleepAfterOwnedBlockUsesNormalSampling` asserts `sampleCount >= 10`. The
wall clock uses reservoir sampling (16 threads/tick); the test thread is 1 of many.
With the unowned-blocked fallback ratio of 1/10, 300ms produced ~9-16 samples —
right at the boundary. `waitForProfilerReady` did not help (profiler ready in 0ms;
issue was signal frequency, not startup race).

**Fix:** `SLEEP_MILLIS` 300 → 1000. Gives ~30+ expected samples. Safe for
suppression tests (once-per-run suppression keeps them `< 10` regardless of
duration). Committed in PR #664.

## Open bugs (not fixed — out of scope for PR #664)

### B-VTABLE-RECEIVER-MACOS: vtable receiver VMSymbol* resolution fails on macOS arm64 + JDK 26
**JIRA:** [PROF-15828](https://datadoghq.atlassian.net/browse/PROF-15828)
`VtableReceiverFrameTest`: vtable stubs ARE detected (`.vtable stub()` appears in
~20 traces) but the `vtable_receiver` synthetic frame is NEVER emitted. The
signal-handler capture path (`hotspotSupport.cpp:667`) reads `frame.jarg0()` as
the receiver oop, calls `VMKlass::fromOop(receiver)` then `klass->name()` to get
the `VMSymbol*`. One of these fails on macOS arm64 + Corretto JDK 26.

**Suspected area:** oop→klass resolution depends on `_has_class_names`, which
requires `_klass_name_offset >= 0` AND (`_compact_object_headers` ?
(`_markWord_klass_shift >= 0` && `_markWord_monitor_value == MONITOR_BIT`) :
`_oop_klass_offset >= 0`) AND `_symbol_length_offset >= 0` AND
`_symbol_body_offset >= 0` AND `_klass != NULL` (vmStructs.cpp:362). Compact
object headers (JDK 19+) use the mark word klass shift; classic uses the oop
klass offset. One of these offsets is likely wrong or unavailable on this
platform/JDK combination.

**Test skipped** with `Assumptions.assumeFalse(Platform.isMac())` in PR #664
(pre-existing test from PR #719). Root cause NOT determined — needs deep
investigation of mark-word / compact-object-header resolution on macOS arm64.

### B-NATIVE-THREAD-MACOS: native thread CPU profiling fails on macOS (platform limitation)
`NativeThreadTest`, `ThreadEntryDetectionTest`, `DynamicNativeThread` produce
0-6 total ExecutionSamples, none from native threads.

**Verified mechanism:** Linux `CTimer` registers all OS threads (including native
pthreads) with per-thread `timer_create(CLOCK_THREAD_CPUTIME_ID, SIGEV_THREAD_ID)`.
macOS `CTimer::check` fails (`timer_create(CLOCK_THREAD_CPUTIME_ID)` not supported),
falls back to `ITimer` (process-wide `setitimer(ITIMER_PROF)`). No per-thread
timers. SIGPROF lands on an arbitrary thread; the handler resolves
`ProfiledThread` via `acquireCurrent()`, and native threads have no
`ProfiledThread` TLS entry, so the sample is dropped.

**Tests skipped** with `Assumptions.assumeTrue(Platform.isLinux())` in PR #664.
This is a genuine platform limitation, not a bug — skip is the correct fix.

## Hypotheses

## Dead ends

## Evidence

## Questions
