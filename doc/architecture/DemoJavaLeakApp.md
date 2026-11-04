<!-- Copyright 2026, Datadog, Inc. -->

# DemoJavaLeakApp

The `demo-java-leak` module is a self-contained demo web application with a steadily
growing memory leak. It is the Java counterpart of the `prof-dotnet-leak` demo service:
a continuously running, always-leaking workload that gives the Datadog Profiling UI a
steady, easy-to-find source of Java live-heap and reference-chain profile data in staging
and production. The deployed service (`prof-java-leak`, owned by profiling-backend) runs
this app under the released Datadog Java tracer.

## No profiler dependency

The module has zero third-party dependencies and no dependency on the profiler itself:
no `:ddprof-lib` project or `com.datadoghq.profiler` dependency, no `JavaProfiler` API
calls, no `-agentpath`. The app is plain JDK Java (`java.base`, `jdk.httpserver`,
`java.management`) and is oblivious to profiling. In the deployed service, profiling
comes solely from dd-trace-java attached with `-javaagent`. The module is not published
to any Maven repository; it exists only as a deployable demo artifact.

## Architecture

The app is built from a small set of plain-JDK components:

| Component | Role |
|---|---|
| `com.datadoghq.demo.leak.Main` | Entry point: starts the HTTP server on an ephemeral port and runs the self-traffic loop; never exits on its own |
| `HttpLeakHandler` | Serves each request by creating a request-scoped state object and handing it to the cache; always returns a small fixed response |
| `RequestCache` | The leak: an unbounded `HashMap` that strongly retains every recorded request state; retention is removed only by `flush()` |
| `RequestState` | Request-scoped object: a key string plus long fields sized to clear the allocation sampler's floor, plus a registered listener closure that captures the instance |
| `HeapWatermark` | Samples post-GC heap usage (via `MemoryPoolMXBean`, falling back to `Runtime.maxMemory()` when the max is undefined) and reports when occupancy crosses the flush threshold |

### Leak shape

Every handled HTTP request creates one request-scoped state object. The cache retains
each object by a direct strong reference (the map entry) and additionally through a
registered listener closure that captures the instance — a Java analog of a cache
misconfiguration where per-request callbacks outlive the request. There is no eviction
and no size cap: the retained population only grows, so the per-klass population trend
the reference-chain tracker relies on keeps rising across GC epochs.

### Self-traffic

The app generates its own request traffic over the real HTTP handler path: `Main` runs
a loop that issues requests to its own server using the JDK HTTP client. No external
client or load generator is needed. Each round forces a `System.gc()` so GC epochs
advance on a predictable schedule even though a quiet 512 MiB heap may not collect on
its own often enough.

### Watermark-flush cycle

The JVM runs with `-Xmx512m`. An unbounded cache under a bounded heap would eventually
OOM, and a throttled-growth plateau would flatten the population trend the leak
detectors need. Instead the app paces growth and flushes on a high watermark:

1. The cache grows at a rate sized so one growth phase fills most of the heap over a
   long window (far more than the ~10 GC epochs the leak-trend gates need to qualify).
2. Each round, `HeapWatermark` checks post-GC occupancy. Below the high watermark
   (75% of max heap), growth continues.
3. When occupancy crosses the watermark, `RequestCache.flush()` drops the entire cache
   in one step (logging one `flushed N retained entries` line), and growth resumes from
   an empty cache.

The result is a sawtooth occupancy: long monotonic growth phases — each long enough for
the reference-chain trend gates to qualify and emit chains — followed by a single-step
drop and regrowth, with no `OutOfMemoryError` and no container restart.

## Build

The module compiles with `--release 21` (configured in `demo-java-leak/build.gradle.kts`),
not the repo-wide `--release 8`: it builds under the repo's JDK 21 Gradle and runs on the
JDK 27 container image. Build with the repo wrapper:

```bash
./.claude/commands/build-and-summarize :demo-java-leak:build
```

The Gradle `application` plugin writes `Main-Class: com.datadoghq.demo.leak.Main` into the
jar manifest, so the jar is directly runnable (`java -jar`). The module's test JVM runs
with the same `-Xmx512m` heap as the deployed app, so tests observe the same watermark
behavior as production.

## How the container image consumes it

The `prof-java-leak` service image (in the profiling-backend repository) does not use
Gradle. Its Dockerfile clones the public `java-profiler` repository at a pinned,
immutable commit, compiles the module's sources with plain
`javac --release 21`, and packages them with `jar --main-class`. The image records the
source commit (`APP_REPOSITORY_URL` / `APP_COMMIT_SHA` → `DD_GIT_REPOSITORY_URL` /
`DD_GIT_COMMIT_SHA`). Because the module has no third-party dependencies, the two build
paths (this Gradle module and the image's `javac`) compile the same plain-JDK sources and
cannot drift apart in dependencies. At runtime the image starts the app with
`-javaagent:dd-java-agent` and `-Xmx512m`, with heap, live-heap and reference-chain
profiling enabled through the tracer's `DD_PROFILING_*` configuration.
