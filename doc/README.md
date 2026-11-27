<!-- Copyright 2026, Datadog, Inc. -->

# Java Profiler Documentation

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
- [CallTraceStorage](architecture/CallTraceStorage.md) - Triple-buffer architecture for call traces; recording-scoped (release/acquire)
- [DemoJavaLeakApp](architecture/DemoJavaLeakApp.md) - Self-contained leak-demo app (`demo-java-leak`): unbounded strong-ref cache, self-traffic, watermark flush, no profiler dependency
- [JfrIntegration](architecture/JfrIntegration.md) - Native JFR writer: recordings, buffers, metadata, constant pools
- [LiveHeapReferenceChainsImplementation](architecture/LiveHeapReferenceChainsImplementation.md) - Current reference-chain implementation, including root-anchor indexing and rotation, and deferred updates after JVMTI traversal
- [MallocArenaWarning](architecture/MallocArenaWarning.md) - glibc malloc arena detector: arena walk, rule, and JFR events
- [NativeMemoryProfiling](architecture/NativeMemoryProfiling.md) - malloc interception, startup admission, per-recording restoration, reuse-aware exit admission and allocation sampling
- [ProfilingEngines](architecture/ProfilingEngines.md) - CPU, wall-clock, allocation, native-memory and liveness engines; gated thread registration; the persistent `pthread_create` hook (loader-binding rule, pending entries, foreign wrappers left alone); recording-scoped liveness; filtered wall reservoir and epoch accounting; bounded timer TID prechecks; lazy wall-block backing; allocation/liveness stack capture, JVMTI retry, depth-limit truncation and verification scratch (`allocstack`)
- [RefCountGuard](architecture/RefCountGuard.md) - Lock-free RAII reference-counting primitive used to drain readers before resource reclamation
- [ReferenceChainsSignalsExplained](architecture/ReferenceChainsSignalsExplained.md) - Reference-chain scheduling and cost control
- [JvmSupportLayer](architecture/JvmSupportLayer.md) - JVM-implementation abstraction (HotSpot, J9, Zing), continuation completeness and vtable receiver frames
- [SanityChecks](architecture/SanityChecks.md) - Startup sanity checks
- [SigsegvPatching](architecture/SigsegvPatching.md) - SIGSEGV-safe library patching (persistent sigaction/pthread_create hooks); crash-handler bootstrap (fault-PC prefilter, raw-identity thread-exit registry, Linux-only fault/profiling-mask fence)
- [StringDictionary](architecture/StringDictionary.md) - Concurrency model: RefCountGuard, clearAll, release, and rotation protocols; lazy storage
- [TLSContext](architecture/TLSContext.md) - Thread-local context for distributed tracing

### Build System
- [BuildSystemGuide](building/BuildSystemGuide.md) - Build conventions, Java formatting, TestKit verification and independent JDK 21 build-logic CI
- [CodeCoverage](building/CodeCoverage.md) - Opt-in C++ (gcovr) and Java (JaCoCo) coverage reports, prerequisites, debug-only scope
- [GradleTasks](building/GradleTasks.md) - Available Gradle tasks reference
- [JdkUpgrades](building/JdkUpgrades.md) - Two-JDK pattern and JDK upgrade touchpoints
- [MemoryOverheadCheck](building/MemoryOverheadCheck.md) - Per-PR native-memory budget check on GitLab and how to recalibrate it
- [NativeBuildPlugin](building/NativeBuildPlugin.md) - Native C++ compilation plugin
- [ReleaseTrain](building/ReleaseTrain.md) - Automated release train: nightly certification, Friday minor release, dd-trace-java bump
- [TestingGuide](building/TestingGuide.md) - Test strategy: tiers, sanitizers, CI layout, integration runtime applicability and JVM identity checks, and local workflows
- [Versioning](building/Versioning.md) - Version computation from git tags

### Reference
- [ProfilerMemoryRequirements](reference/ProfilerMemoryRequirements.md) - Memory usage and limits, including what an idle profiler holds
- [EventTypeSystem](reference/EventTypeSystem.md) - Profiler event types
- [RemoteSymbolication](reference/RemoteSymbolication.md) - Symbol resolution
- [RemoteSymbolicationFrameTypes](reference/RemoteSymbolicationFrameTypes.md) - Frame type design for symbolication
- [SamplerPerfCounters](reference/SamplerPerfCounters.md) - Opt-in per-sampler timing counters and the stop-time report
- [TestFlakinessAnalysis](reference/TestFlakinessAnalysis.md) - Test flakiness investigation results

### Design

- [BitsReviewMergeGateDesign](BitsReviewMergeGateDesign.md) - Bits PASS merge gate: policy, implementation, trusted status publisher, and enforcement proposal pending separate approval
- [BitsReviewRedReviewRunbook](BitsReviewRedReviewRunbook.md) - Developer procedure for a red Bits review: what clears FAIL, what does not, and how to get a fresh review
- [NativeMemoryProfilerExclusionDesign](NativeMemoryProfilerExclusionDesign.md) - Admission check design for conflicting native-memory profilers: decision, rationale and lifecycle limits
- [ReferenceChainsCollectionSummary](ReferenceChainsCollectionSummary.md) - Short reference-chain overview and limits
- [ReferenceChainsDesign](ReferenceChainsDesign.md) - Reference-chain design decision and trade-offs
- [WorkTracking](WorkTracking.md) - Work-tracking phases: Intent, Design, Build and Test, Deploy

### Reports

- [ThreadContextBenchmark](performance/reports/ThreadContextBenchmark.md) - Thread-context tracking benchmark results
