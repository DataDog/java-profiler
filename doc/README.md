# Java Profiler Documentation

## Directory Structure

| Directory | Purpose |
|-----------|---------|
| `architecture/` | Profiler internal architecture and design documents |
| `build/` | Build system documentation (Gradle, native compilation) |
| `reference/` | Reference documentation for profiler features |
| `temp/` | Work logs, session state, and analysis reports |

## Naming Convention

All documentation files use **PascalCase** naming (e.g., `BuildSystemGuide.md`).

## Quick Navigation

### Architecture
- [CallTraceStorage](architecture/CallTraceStorage.md) - Triple-buffer architecture for call traces
- [RefCountGuard](architecture/RefCountGuard.md) - Lock-free RAII reference-counting primitive used to drain readers before resource reclamation
- [StringDictionary](architecture/StringDictionary.md) - Concurrency model: RefCountGuard, clearAll, and rotation protocols
- [TLSContext](architecture/TLSContext.md) - Thread-local context for distributed tracing
- [TLSPriming](architecture/TLSPriming.md) - Signal-safe TLS initialization

### Build System
- [BuildSystemGuide](build/BuildSystemGuide.md) - Comprehensive build system documentation
- [GradleTasks](build/GradleTasks.md) - Available Gradle tasks reference
- [NativeBuildPlugin](build/NativeBuildPlugin.md) - Native C++ compilation plugin
- [TestingGuide](build/TestingGuide.md) - Test strategy: tiers, sanitizers, CI layout, and local workflows

### Reference
- [ProfilerMemoryRequirements](reference/ProfilerMemoryRequirements.md) - Memory usage and limits
- [EventTypeSystem](reference/EventTypeSystem.md) - Profiler event types
- [RemoteSymbolication](reference/RemoteSymbolication.md) - Symbol resolution
- [RemoteSymbolicationFrameTypes](reference/RemoteSymbolicationFrameTypes.md) - Frame type design for symbolication
- [TestFlakinessAnalysis](reference/TestFlakinessAnalysis.md) - Test flakiness investigation results

### Work State (temp/)
Session logs and analysis reports for ongoing work. Not considered permanent documentation.
