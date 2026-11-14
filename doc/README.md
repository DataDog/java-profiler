<!-- Copyright 2026, Datadog, Inc. -->

# Java Profiler Documentation

<!-- Copyright 2026, Datadog, Inc -->

## Directory Structure

| Directory | Purpose |
|-----------|---------|
| `architecture/` | Profiler internal architecture and design documents |
| `building/` | Build system documentation (Gradle, native compilation) |
| `reference/` | Reference documentation for profiler features |
| `performance/` | Benchmark and performance reports |

## Naming Convention

All documentation files use **PascalCase** naming (e.g., `BuildSystemGuide.md`).

## Quick Navigation

### Architecture
- [CallTraceStorage](architecture/CallTraceStorage.md) - Triple-buffer rotation, isolated liveness collectors, reusable unowned wall-stack roots and exact-copy failure handling
- [DemoJavaLeakApp](architecture/DemoJavaLeakApp.md) - Self-contained leak-demo app (`demo-java-leak`): unbounded strong-ref cache, self-traffic, watermark flush, no profiler dependency
- [JfrIntegration](architecture/JfrIntegration.md) - Native JFR writer: stripe-owned deferred wall tails, recordings, buffers, metadata, constant pools and [delivery custody](architecture/JfrIntegration.md#delivery-custody)
- [LiveHeapReferenceChainsImplementation](architecture/LiveHeapReferenceChainsImplementation.md) - Current reference-chain implementation
- [Native I/O Hooks](architecture/NativeIoHooks.md) — shared import ownership, FD reuse and synchronous native TaskBlocks.
- [NativeMemoryProfiling](architecture/NativeMemoryProfiling.md) - malloc interception and allocation sampling
- [ProfilingEngines](architecture/ProfilingEngines.md) - CPU, monotonic wall-clock cadence, allocation, native-memory and liveness engines; wall reservoir and retained-weight epoch provenance; lazy wall-block backing; [TaskBlock producer contract](architecture/ProfilingEngines.md#taskblock-producer-contract); allocation/liveness stack capture, JVMTI retry, depth-limit truncation and verification scratch (`allocstack`)
- [RefCountGuard](architecture/RefCountGuard.md) - Lock-free RAII reference-counting primitive used to drain readers before resource reclamation
- [ReferenceChainsSignalsExplained](architecture/ReferenceChainsSignalsExplained.md) - Reference-chain scheduling and cost control
- [JvmSupportLayer](architecture/JvmSupportLayer.md) - JVM-implementation abstraction (HotSpot, J9, Zing), continuation completeness
- [SanityChecks](architecture/SanityChecks.md) - Startup sanity checks
- [SigsegvPatching](architecture/SigsegvPatching.md) - SIGSEGV-safe library patching
- [StringDictionary](architecture/StringDictionary.md) - Concurrency model: RefCountGuard, clearAll, and rotation protocols
- [TLSContext](architecture/TLSContext.md) - Thread-local tracing, owner context-window membership and retained filtered/unfiltered unowned wall context

### Build System
- [BuildSystemGuide](building/BuildSystemGuide.md) - Build conventions, Java formatting, TestKit verification and independent JDK 21 build-logic CI
- [CodeCoverage](building/CodeCoverage.md) - Opt-in C++ (gcovr) and Java (JaCoCo) coverage reports, prerequisites, debug-only scope
- [GradleTasks](building/GradleTasks.md) - Available Gradle tasks reference
- [JdkUpgrades](building/JdkUpgrades.md) - Two-JDK pattern and JDK upgrade touchpoints
- [NativeBuildPlugin](building/NativeBuildPlugin.md) - Native C++ compilation plugin
- [TestingGuide](building/TestingGuide.md) - Test strategy: tiers, sanitizers, CI layout, and local workflows
- [Versioning](building/Versioning.md) - Version computation from git tags
  - [Bounded local container runs](building/TestingGuide.md#bounded-local-container-runs) - Exact Git worktrees, offline cache-only execution, worker limits, and retained test artifacts

### Reference
- [ProfilerMemoryRequirements](reference/ProfilerMemoryRequirements.md) - Memory usage and limits
- [EventTypeSystem](reference/EventTypeSystem.md) - Profiler event types
- [RemoteSymbolication](reference/RemoteSymbolication.md) - Symbol resolution
- [RemoteSymbolicationFrameTypes](reference/RemoteSymbolicationFrameTypes.md) - Frame type design for symbolication
- [SamplerPerfCounters](reference/SamplerPerfCounters.md) - Wall-timer cadence/phase diagnostics and opt-in per-sampler timing counters and the stop-time report
- [TestFlakinessAnalysis](reference/TestFlakinessAnalysis.md) - Test flakiness investigation results

### Design

- [ReferenceChainsCollectionSummary](ReferenceChainsCollectionSummary.md) - Short reference-chain overview and limits
- [ReferenceChainsDesign](ReferenceChainsDesign.md) - Reference-chain design decision and trade-offs
- [WorkTracking](WorkTracking.md) - Work-tracking phases: Intent, Design, Build and Test, Deploy

### Reports

- [ThreadContextBenchmark](performance/reports/ThreadContextBenchmark.md) - Thread-context tracking benchmark results
