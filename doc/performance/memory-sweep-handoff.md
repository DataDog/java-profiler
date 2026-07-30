# Native Memory Sweep — Handoff for Linux Follow-up

This hands off an in-progress investigation into what workload properties
drive java-profiler's native memory usage, so it can continue on a Linux
machine. Read in this order:

1. [memory-usage-model.md](memory-usage-model.md) — static-analysis model
   (baseline footprint + per-dimension scaling), built from reading the
   source before any experiment was run.
2. [memory-sweep-results.md](memory-sweep-results.md) — empirical results
   from running the harness in `memsweep/` on macOS arm64, including several
   rounds of debugging null results, and the NMT/JFR-architecture follow-up.
3. This document — what's unresolved, what Linux specifically should answer,
   and how to run the harness there.

## Why Linux, specifically

Everything so far was run on macOS arm64 (Corretto 25) because that's what
was available. Several results are platform-specific or suspected to be:

- **`NM_PERF` is Linux-only by construction** (`perfEvents_linux.cpp`,
  `#ifdef __linux__`) — it read 0 in every macOS run, not because nothing
  happened, but because there's no macOS implementation at all. This is the
  single biggest reason to rerun on Linux: it's a whole category of
  native-memory accounting this investigation hasn't touched yet.
- **The CPU-time engine (`cpu=<interval>`) fails to initialize at all on this
  macOS build** (`Agent_OnLoad` error, JVM refuses to start). It's unknown
  whether this is a macOS-specific gap or would also fail on Linux — worth
  checking early, since CPU sampling doesn't need the `addThread()`
  workaround (see below) and would make the trace/class sweeps much cheaper
  to run at scale.
- **Wall-clock sampling required an undocumented workaround**: on this
  build, `-agentpath:...=start,wall=~5ms,...` alone produced **zero**
  `datadog.MethodSample` events, for any thread, including the main thread —
  despite `datadog.WallClockSamplingEpoch` events showing the sampler was
  running on schedule. Samples only appeared once every sampled thread
  explicitly called `JavaProfiler.getInstance(...).addThread()`. It is not
  known whether this is:
  - the intended design (auto-registration was never supposed to happen,
    and every test/production integration is expected to call `addThread()`
    itself — check how dd-trace-java integrates this), or
  - a macOS-specific gap in whatever installs the JVMTI `ThreadStart`
    callback (or signal-based registration) that should auto-register new
    threads, or
  - specific to attaching via `-agentpath` rather than the in-process JNI
    API (both were tested here and both needed `addThread()`, but both were
    on the same macOS build).

  **First thing to check on Linux: does wall-clock sampling work without
  `addThread()`?** If it does, that confirms a macOS-specific gap and
  changes how much of the earlier "harness bug" debugging even applies
  there. The harness's `MemSweepMain` already calls `addThread()`
  unconditionally, so it will work either way — but it's worth temporarily
  removing that call on Linux to check.
- **`jcmd` attach became unreliable at higher thread counts specifically
  when this profiler's agent was also attached** (256+ threads, "state is
  not ready to participate in attach handshake"). This wasn't root-caused —
  plausible cause is the profiler's own signal handling (needed for
  wall-clock sampling) interfering with HotSpot's attach listener. The NMT
  numbers in memory-sweep-results.md were measured on **agent-free control
  runs** to work around this. Worth checking whether this reproduces on
  Linux; if it doesn't, NMT can be measured directly alongside the agent
  there, which is a strictly better experiment (same-process comparison
  instead of two separate runs).

## Open questions to resolve on Linux

In priority order:

1. **Does `NM_THREAD_LOCAL` actually scale with thread count?** It read
   exactly 4,120 bytes from 1 thread to 1,000 threads on macOS, which
   contradicts the source-level model (`ProfiledThread` is a per-OS-thread
   TLS structure, see memory-usage-model.md). Rerun the `threads` sweep
   (1, 4, 16, 64, 256, 1000) and watch this counter specifically. If it's
   still flat on Linux, this is very likely a real instrumentation gap
   worth reporting/fixing upstream, not a macOS artifact.
2. **Does the class-name dictionary (`NM_DICTIONARY`) ever grow?** On macOS,
   even 40,000 distinct classes with 97,661 real samples landing across them
   didn't move it (see the "was 2,000 too small" follow-up in
   memory-sweep-results.md — the calltrace counter *did* show a clean ~16 MB
   jump under the same methodology, so the harness itself is validated; only
   the dictionary counter stayed flat). Two hypotheses, neither confirmed:
   - the per-name threshold to fill one 512 KB `StringArena` chunk
     (`stringDictionary.h:67`) is higher than the back-of-envelope estimate
     (~35–40K names at ~13 bytes each), or
   - the per-thread `StringDictionaryBuffer` batches entries locally and
     hadn't flushed enough into the shared global arena within the run.

   To disambiguate: try (a) an even larger N (e.g. 150,000 classes) and/or
   much longer duration to rule out "just needs more", and (b) if source
   reading turns up a flush trigger/threshold for `StringDictionaryBuffer`,
   check whether the run's duration/sample count crosses it.
3. **`NM_PERF` categorization.** Once on Linux, enable `cpu=` (assuming it
   works there) and check whether `NM_PERF` moves with sample rate / thread
   count. This is entirely unexplored territory — no macOS data exists for
   it at all.
4. **Allocation profiling (`memory=<interval>[:a]`) and native-malloc tracing
   (`nativemem=<bytes>`) were never exercised** in any run so far — only
   wall-clock. These populate different call-trace/dictionary insertion
   paths (allocation sample stacks vs. malloc-hook stacks vs. wall-clock
   stacks) and might behave differently. Worth adding as a fourth sweep
   dimension alongside threads/traces/classes: e.g. an `allocs` mode that
   allocates N distinct short-lived object shapes to see whether allocation
   sampling drives calltrace/dictionary growth differently than wall-clock
   reflection calls did.
5. **Reconcile RSS with NMT + `NM_*` more precisely.** On macOS, NMT's own
   "Thread" bucket explained only ~17–20% of measured per-thread RSS growth,
   even on an agent-free control run — meaning most of it is OS-level
   thread bookkeeping invisible to both NMT and the profiler's own counters.
   On Linux, `-XX:NativeMemoryTracking=detail` plus `pmap`/`smaps` on the
   process can attribute resident pages far more precisely than macOS's
   coarser tooling. If `jcmd` attach turns out to be reliable there even
   with the agent attached (see above), get a same-process NMT diff +
   `/proc/<pid>/smaps_rollup` comparison across the thread sweep, instead of
   the macOS workaround of two separate agent-free/agent-attached runs.

## Running the harness

Everything needed is under `doc/performance/memsweep/` in this checkout:

```
memsweep/
├── src/
│   ├── MemSweepMain.java   # the three sweep workloads (threads/traces/classes)
│   └── GenSources.java     # writes .java sources for traces/classes, compiled externally
├── run_sweep.sh            # one sweep point -> CSV line with RSS + NM_* counters
├── run_nmt.sh              # one sweep point with JVM Native Memory Tracking
└── extract.py              # parses `jfr print --json` output for native_mem_* counters
```

Build the agent first if not already built (from repo root):

```
./gradlew :ddprof-lib:assembleRelease
```

Then, from repo root:

```
# threads / traces / classes sweep, prints one CSV line per point
doc/performance/memsweep/run_sweep.sh threads 256 3000
doc/performance/memsweep/run_sweep.sh traces 60000 90000 ~1ms   # 4th arg overrides wall interval
doc/performance/memsweep/run_sweep.sh classes 40000 120000 ~1ms

# NMT-enabled run (jcmd attach + agent both active -- try this first on Linux;
# if it fails like it did on macOS, add --no-agent as a 5th arg for a
# control-only run and compare against a separate run_sweep.sh run)
doc/performance/memsweep/run_nmt.sh threads 256 9000
doc/performance/memsweep/run_nmt.sh threads 256 9000 ~5ms --no-agent
```

The scripts auto-detect `DDPROF_LIB` (globs
`ddprof-lib/build/lib/main/release/**/libjavaProfiler.*`), `javac`/`jfr`/`jcmd`
via `java.home` if not already on `PATH`, and default to `/tmp/memsweep` as a
scratch dir (override with `WORKDIR=...`). All of this was written and
tested against a macOS layout; the auto-detection glob should work unchanged
for a Linux build's `.so`, but hasn't actually been run on Linux yet — if
`DDPROF_LIB` resolution fails, set it explicitly:

```
DDPROF_LIB=/path/to/ddprof-lib/build/lib/main/release/linux/<arch>/libjavaProfiler.so \
  doc/performance/memsweep/run_sweep.sh threads 256 3000
```

**Important methodology notes carried over from the macOS runs** (see
memory-sweep-results.md for the full reasoning):

- For `traces`/`classes` sweeps at meaningful N, you need enough *samples*,
  not just enough classes/methods, to cross the growth thresholds computed
  above (49,152 distinct call-trace shapes; ~35–40K distinct class names).
  Sample count ≈ duration / wall_interval, and coverage of N candidates
  follows a coupon-collector curve — plan durations accordingly (the macOS
  confirmation run used `wall=~1ms` for 90–120s to get 76K–98K samples).
- `NM_*` counters only refresh at JFR chunk finish (profiler stop / process
  exit for a short single-chunk run), so read the *last* occurrence of each
  counter name from the JFR file, not an average across the run.
- The `traces`/`classes` sources must be compiled by an **external** `javac`
  process, not `javax.tools.JavaCompiler` in-process — otherwise the
  in-process compiler's own ~3,000 classes swamp the intended N-classes
  signal (already handled by `run_sweep.sh`/`GenSources.java`, just don't
  reintroduce in-process compilation if modifying the harness).
- If wall-clock produces zero samples again, check `jfr summary <file>`
  for `datadog.MethodSample` count before assuming a null result means "no
  growth" — it might mean "nothing was ever sampled." This exact mistake
  cost significant time during the macOS investigation.
