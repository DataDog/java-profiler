# Chaos harness

Long-running antagonist workload driving the reliability CI cell. Runs as a
black-box application under a `dd-java-agent.jar` patched with the locally
built `ddprof.jar` (see `utils/patch-dd-java-agent.sh`). The only failure
signal is a JVM crash — non-zero exit code plus `hs_err_pid*.log` captured by
the runner script.

## Antagonist roster

| Name              | Targets                                                                  |
| ----------------- | ------------------------------------------------------------------------ |
| `thread-churn`    | signal-vs-teardown races, slot reuse, calltrace storage put/get          |
| `vthread-churn`   | virtual thread mount/unmount, carrier-thread context, `ProfiledThread`   |
| `vthread-remount` | bounded workers parking under deep callers, post-remount CPU work, stack arguments and JIT transitions |
| `classloader-churn` | class unload racing stack walk, `CodeCache`/`Symbols` invalidation     |
| `alloc-storm`     | Java alloc engine + GOT-patched libc malloc/free                         |
| `trace-context`   | `setTraceContext`/`clearTraceContext` racing signals, span ID propagation |
| `reapply-context-value` | concurrent per-slot `setContextValue`/`clearContextValue` churn interleaved with span activation, racing the all-native record's write/read window |

## Virtual-thread carrier recovery

`vthread-remount` keeps four virtual threads alive and alternates register-only
and stack-passed arguments under 128–224 recursive callers. Each leaf parks,
then burns CPU after remounting. Worker failures and shutdown timeouts propagate
to the harness. It can be selected by name through `run-chaos-harness.sh`'s
fourth argument, including alongside other antagonists.

`VirtualThreadCarrierChaosTest` profiles this same workload with native CPU and
wall sampling in both `cstack=vmx` and `cstack=vm`. It requires return-barrier
hits, progress in both argument layouts, and enough eligible samples from each
engine. It checks carrier presence, uniqueness and ordering, and requires
missing outer callers to remain marked truncated. Samples that stop before a
continuation boundary are counted separately; continuation-pointer errors fail
the check. Profile events are streamed rather than retained for the whole run.

The ordinary `testDebug` suite runs six seconds per mode on supported HotSpot
JDK 21+ runtimes. For a longer run, select the build and test JDKs with
`JAVA_HOME` and `JAVA_TEST_HOME`, then run:

```sh
DDPROF_VTHREAD_STRESS_SECONDS=120 JAVA_TOOL_OPTIONS=-XX:-PreserveFramePointer \
  ./.claude/commands/build-and-summarize :ddprof-test:testDebug \
  -Ptests=VirtualThreadCarrierChaosTest -Pskip-gtest -PkeepJFRs
```

Repeat with `JAVA_TOOL_OPTIONS=-XX:+PreserveFramePointer` as a control.
The duration accepts 2–3600 seconds. Test XML and retained JFR recordings include
both the CPU and wall-clock checks; inspect the logged eligible-sample and
pre-boundary-stop counts when comparing runs. Passing process survival in the
agent chaos harness alone does not establish stack correctness.

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
