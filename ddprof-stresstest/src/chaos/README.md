<!-- Copyright 2026, Datadog, Inc. -->

# Chaos harness

Long-running antagonist workload driving the reliability CI cell. Runs as a
black-box application under a `dd-java-agent.jar` patched with the locally
built `ddprof.jar` (see `utils/patch-dd-java-agent.sh`). Native crashes and
workload failures produce a non-zero exit. Native crashes also leave an
`hs_err_pid*.log` captured by the runner script.

The profiler-aware workloads bind method handles through the attached agent's
isolated class loader. The application jar does not contain a second copy of
`JavaProfiler`. Standalone native tests resolve the profiler on their test classpath.
To also check the packaged harness with a real patched agent in both profiler-only
and profiler-plus-tracer modes, pass its path to the test task:

```bash
./.claude/commands/build-and-summarize :ddprof-stresstest:testOwnedBlockPrecheck -PchaosAgentJar=/path/to/dd-java-agent-patched.jar
```

## Antagonist roster

| Name              | Targets                                                                  |
| ----------------- | ------------------------------------------------------------------------ |
| `thread-churn`    | signal-vs-teardown races, slot reuse, calltrace storage put/get          |
| `vthread-churn`   | virtual thread mount/unmount, carrier-thread context, `ProfiledThread`   |
| `classloader-churn` | class unload racing stack walk, `CodeCache`/`Symbols` invalidation     |
| `alloc-storm`     | Java alloc engine + GOT-patched libc malloc/free                         |
| `trace-context`   | `setTraceContext`/`clearTraceContext` racing signals, span ID propagation |
| `reapply-context-value` | concurrent per-slot `setContextValue`/`clearContextValue` churn interleaved with span activation, racing the all-native record's write/read window |
| `park-block-churn` | `ThreadFilter`/`WallClockBlockTracker` registry+block-run races: sleep/park/wait/contended-monitor blocking (some interrupted mid-block) on short-lived threads, racing slot reuse and teardown against the owned/unowned block-run suppression path |

## Owned-block precheck coverage

`park-block-churn` explicitly invokes the native sleep and park hooks through
method handles bound to the runtime `JavaProfiler` instance. It does not rely on
the downloaded tracer to instrument blocking APIs. Object waits and contended
monitor acquisition remain unowned observations. Background hook failures fail
the harness, and shutdown prints armed-sleep and park-call counts.

The existing agent-driven runner keeps the agent's profiler configuration. To
verify the unfiltered suppression path independently, run on HotSpot with a
COUNTERS-enabled build (including the standard debug build):

```bash
./.claude/commands/build-and-summarize :ddprof-stresstest:testOwnedBlockPrecheck
```

The tests start standalone recordings and fail unless owned sleeps, park hooks,
unfiltered registry lookups, and timer-side suppression occur with
`wall=1ms,filter=,wallprecheck=true`. Disabled-precheck controls must fail the
coverage check. This task is also part of the module's `check` lifecycle. It does
not inject a Java agent; each test stops its
recording and removes the temporary JFR file on exit.

## Deferred

- **`dlopen`/`dlclose` churn** — load and unload throwaway native libraries to
  exercise the profiler's `CodeCache`/`Symbols` modules during library
  teardown. Deferred because it requires shipping a dummy `.so` per supported
  architecture; the simplest path is to build those libraries per-arch as a
  preparation step in the same reliability CI run. Largely overlaps with
  `classloader-churn` for the symbol-resolution race surface, so revisit only
  if that antagonist proves insufficient.

## Multi-engine signal pressure

Not an antagonist — applied at the runner level via launch flags
(`-Ddd.profiling.ddprof.alloc.enabled=true`, `...wall.enabled=true`,
nativemem, aggressive sampling intervals).
