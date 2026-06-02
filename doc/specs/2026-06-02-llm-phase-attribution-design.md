# LLM Phase Attribution — Foundation + F1 Pilot

**Status:** Approved design, pending implementation plan
**Date:** 2026-06-02
**Branch:** `jb/llm`
**Scope source:** `doc/temp/llm-profiling-design.md` (15-feature roadmap)

## Problem

LLM pipeline state is invisible to the profiler. A CPU flamegraph from an
LLM-based JVM service shows undifferentiated work with no way to tell context
assembly from inference wait from tool execution. This spec covers the shared
*foundation* for LLM phase attribution plus the first feature (F1, "AI Phase
Tagging (CPU)"), proven end-to-end and demonstrated with real recorded data.

This is one slice of a larger roadmap. The other 14 features are explicitly out
of scope here (see Non-Goals).

## Goals

1. Define a per-thread *agent phase* contract owned by `java-profiler`.
2. Let `dd-trace-java` set the phase from instrumentation, async-signal-safe to
   read.
3. CPU samples carry the phase so flamegraphs become phase-keyed.
4. Ship a real, runnable LangChain4j scenario that produces a JFR recording
   suitable for the profiling backend.

## Key architectural decision: Hybrid representation

The roadmap doc proposes a new ~24-byte typed struct in the per-thread native
context (`agentPhase` uint8, etc.). **For this pilot we do not do that.**

Evidence from the codebase:

- The per-thread context already has **10 attribute slots** (`DD_TAGS_CAPACITY`),
  each a `u32` dictionary-encoded ID, read async-signal-safe in the signal
  handler via `getOtelTagEncoding(i)` (`ddprof-lib/src/main/cpp/thread.h:250`).
- `writeCurrentContext()` already emits those tag encodings into **CPU execution
  samples** — not only wall-clock — via `recordExecutionSample`
  (`ddprof-lib/src/main/cpp/flightRecorder.cpp:1700-1713`).
- `dd-trace-java` already has the full attribute path: `ContextSetter`,
  `Profiling.get().setContextValue(...)`, `ProfilingContextAttribute`, and
  `DD_PROFILING_CONTEXT_ATTRIBUTES` slot registration
  (`DatadogProfiler.java:153`, `DatadogProfilerConfig.getContextAttributes`).

`agentPhase` is an enum with 9 values — ideal for dictionary encoding (tiny,
stable cardinality). For F1 the dedicated struct buys nothing over the existing
attribute path and costs native struct churn, new JFR metadata, new JNI setters,
and a wider blast radius.

**Decision:** Expose a typed `AgentPhase` enum as the public contract, but back
it with the existing dictionary-encoded attribute slot. No native changes.

The dedicated typed fields *are* justified later — for high-cardinality numeric
fields (`contextTokenCount`, `requestContextId`, `requestStartNs`) that would
explode a string dictionary, and because string-encoding the full roadmap would
exhaust the 10 slots. That work is deferred to the first Phase-2 feature that
needs it.

## Constraints (carried from the roadmap)

- No malloc / no heap access in signal handlers — reads stay plain field /
  dictionary-id accesses on pre-allocated per-thread state.
- No O(N) work in any sampler hot path.
- The phase contract is owned by `java-profiler`; instrumentation lives in
  `dd-trace-java`.

## Component design

### java-profiler

1. **`AgentPhase` enum** in `com.datadoghq.profiler` — the layout contract. The
   9 phases from the roadmap (`IDLE`, `INFERENCE_WAIT`, `TOOL_EXECUTION`,
   `CONTEXT_BUILD`, `TOKENIZING`, `EMBEDDING`, `AWAITING_INFERENCE`, `RETRYING`,
   `SERIALIZING`), each with a stable lowercase string token (e.g.
   `AWAITING_INFERENCE` → `"awaiting_inference"`). The profiling backend keys on
   these tokens.
2. **Enum→token helper** for use with the existing
   `ContextSetter.setContextValue(attribute, value)`. No JNI, no native code, no
   new JFR metadata.
3. **Well-known attribute name constant** (`llm.agent.phase`) so both sides agree
   on the slot name.

### dd-trace-java

1. **Startup registration.** Ensure `llm.agent.phase` is in the registered
   attribute set returned by `getContextAttributes`, gated by a config flag
   (working name `DD_PROFILING_LLM_PHASE_ENABLED`, default-on for the pilot),
   mirroring the existing `PROFILING_CONTEXT_ATTRIBUTES_SPAN_NAME_ENABLED`
   pattern. Consumes 1 of 10 slots. This is mandatory: `ContextSetter` is built
   once at startup and `offsetOf()` returns `-1` (setter no-ops) for any name not
   registered then.
2. **Typed setter.** Add `setAgentPhase(AgentPhase)` to the profiling API
   surface, implemented in `DatadogProfilingIntegration` / `DatadogProfiler` by
   mapping the enum to its token and calling `setContextValue(offset, token)`.
   Use scoped set/restore (`Profiling.get().newScope()`) so nested phases restore
   the previous value on exit — satisfying the roadmap's "zeroed at exit"
   requirement without leaving a stale phase on the slot.
3. **New LangChain4j instrumentation module.** Tags three phases at LC4j
   orchestration boundaries:
   - **CONTEXT_BUILD** — AiServices prompt / message assembly (incl. RAG
     retrieval if present).
   - **AWAITING_INFERENCE** — the model call (`ChatModel.chat`, streaming
     variant noted during implementation).
   - **TOOL_EXECUTION** — tool executor dispatch.
   loopIteration and other numeric counters are out (F3/deferred). Exact LC4j
   version and class/method signatures are pinned during implementation
   (LC4j renamed `ChatLanguageModel`→`ChatModel` at 1.0, so version matters).

### JFR output

No new event type. The phase rides as an existing context **tag encoding**
emitted on every `T_EXECUTION_SAMPLE`. Downstream, each CPU sample carries an
`llm.agent.phase` label → phase-keyed flamegraph.

**Open verification (implementation-time, not assumed):** confirm the
`llm.agent.phase` label surfaces *by name* in the emitted JFR via the existing
attribute machinery.

## Testing strategy

1. **java-profiler unit (`ddprof-test`).** Caller-simulated, no dd-trace-java
   dependency: register `llm.agent.phase`, set a phase from a worker thread, run
   CPU load, assert the JFR execution samples carry the phase tag encoding. Runs
   under `testRelease` / `testDebug` (the `:test` task is disabled).
2. **dd-trace-java instrumentation/muzzle test.** Assert the LangChain4j call
   path drives the phase attribute (set on enter, restored on exit) across the
   three boundaries.
3. **Demo — mock path (CI-safe).** A canned `ChatModel` returning fixed
   responses with an artificial delay; a small AiServices agent with one tool, so
   all three phases appear. Deterministic; exercises full instrumentation + JFR
   path.
4. **Demo — Ollama path (manual).** Same agent app against a local Ollama model
   (e.g. llama3) for realistic inference latency, producing a JFR recording for
   the profiling backend. No API key, offline-reproducible.

## Non-goals / explicit deferrals

- No dedicated native typed fields; no new JNI setters; no new JFR event type.
- Numeric fields (`contextTokenCount`, `requestContextId`, `requestStartNs`)
  deferred to their first consuming Phase-2 feature.
- Roadmap features F2–F15 deferred.
- Other framework modules (Spring AI, OpenAI Java SDK, DJL, HuggingFace) and the
  real-OpenAI demo backend deferred.

## Integration reference (grounding)

| Concern | Location |
|---|---|
| Attribute slots, async-signal-safe read | `ddprof-lib/.../cpp/thread.h:250` (`getOtelTagEncoding`) |
| Tag encodings emitted on CPU samples | `ddprof-lib/.../cpp/flightRecorder.cpp:1700-1713` |
| Java attribute setter | `ddprof-lib/.../java/com/datadoghq/profiler/ContextSetter.java` |
| Startup attribute set | dd-trace-java `DatadogProfilerConfig.getContextAttributes` |
| ContextSetter wiring | dd-trace-java `DatadogProfiler.java:153` |
| Profiler context bridge | dd-trace-java `DatadogProfilingIntegration.java` |
| Profiling API surface | dd-trace-java `dd-trace-api/.../profiling/ProfilingContext.java` |
| Existing OpenAI instrumentation (pattern reference) | dd-trace-java `dd-java-agent/instrumentation/openai-java/` |
