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
| `classloader-churn` | class unload racing stack walk, `CodeCache`/`Symbols` invalidation     |
| `alloc-storm`     | Java alloc engine + GOT-patched libc malloc/free                         |
| `trace-context`   | `setContext`/`clearContext` racing signals, span ID propagation          |

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
