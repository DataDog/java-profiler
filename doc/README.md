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
- [CallTraceStorage](architecture/CallTraceStorage.md) - Triple-buffer architecture for call traces
- [JfrIntegration](architecture/JfrIntegration.md) - Native JFR writer: recordings, buffers, metadata, constant pools
- [LiveHeapReferenceChainsImplementation](architecture/LiveHeapReferenceChainsImplementation.md) - Current reference-chain implementation
- [NativeMemoryProfiling](architecture/NativeMemoryProfiling.md) - malloc interception and allocation sampling
- [ProfilingEngines](architecture/ProfilingEngines.md) - CPU, wall-clock, allocation, native-memory and liveness engines
- [RefCountGuard](architecture/RefCountGuard.md) - Lock-free RAII reference-counting primitive used to drain readers before resource reclamation
- [ReferenceChainsSignalsExplained](architecture/ReferenceChainsSignalsExplained.md) - Reference-chain scheduling and cost control
- [JvmSupportLayer](architecture/JvmSupportLayer.md) - JVM-implementation abstraction (HotSpot, J9, Zing), compiled/interpreted continuation entries, arm64 exception phases, and return-barrier entry/interior recovery
- [SanityChecks](architecture/SanityChecks.md) - Startup sanity checks
- [SigsegvPatching](architecture/SigsegvPatching.md) - SIGSEGV-safe library patching
- [StringDictionary](architecture/StringDictionary.md) - Concurrency model: RefCountGuard, clearAll, and rotation protocols
- [TLSContext](architecture/TLSContext.md) - Thread-local context for distributed tracing

### Build System
- [BuildSystemGuide](building/BuildSystemGuide.md) - Comprehensive build system documentation
- [GradleTasks](building/GradleTasks.md) - Available Gradle tasks reference
- [JdkUpgrades](building/JdkUpgrades.md) - Two-JDK pattern and JDK upgrade touchpoints
- [NativeBuildPlugin](building/NativeBuildPlugin.md) - Native C++ compilation plugin
- [TestingGuide](building/TestingGuide.md) - Test strategy: tiers, sanitizers, CI layout, shared virtual-thread chaos coverage, and local workflows
- [Versioning](building/Versioning.md) - Version computation from git tags

### Reference
- [ProfilerMemoryRequirements](reference/ProfilerMemoryRequirements.md) - Memory usage and limits
- [EventTypeSystem](reference/EventTypeSystem.md) - Profiler event types
- [RemoteSymbolication](reference/RemoteSymbolication.md) - Symbol resolution
- [RemoteSymbolicationFrameTypes](reference/RemoteSymbolicationFrameTypes.md) - Frame type design for symbolication
- [SamplerPerfCounters](reference/SamplerPerfCounters.md) - Opt-in per-sampler timing counters and the stop-time report
- [TestFlakinessAnalysis](reference/TestFlakinessAnalysis.md) - Test flakiness investigation results

### Design

- [ReferenceChainsCollectionSummary](ReferenceChainsCollectionSummary.md) - Short reference-chain overview and limits
- [ReferenceChainsDesign](ReferenceChainsDesign.md) - Reference-chain design decision and trade-offs
- [WorkTracking](WorkTracking.md) - Work-tracking phases: Intent, Design, Build and Test, Deploy

### Reports

- [ThreadContextBenchmark](performance/reports/ThreadContextBenchmark.md) - Thread-context tracking benchmark results
