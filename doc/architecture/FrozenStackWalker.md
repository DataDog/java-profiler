<!-- Copyright 2026, Datadog, Inc. -->

# Frozen Stack Walker

`HotspotSupport::walkVM` walks the mounted part of a virtual thread on its carrier
stack. After a partial thaw, older Java callers can remain in heap `StackChunk`
objects. At a verified continuation return barrier, `FrozenStackWalker::append`
adds those callers to the existing trace buffer before the walker emits the
`JVM Continuation` root (`cstack=vm`) or resumes carrier walking (`cstack=vmx`).

## Eligibility and lifetime

`VMStructs::ready()` discovers the layout before readers can use it. Recovery
requires HotSpot JDK 21–27, x86_64 or aarch64, G1/Serial/Parallel, and all required
object and chunk offsets. Compressed oops use the exported base and shift;
uncompressed oops are loaded directly. Missing symbols or an unsupported
collector leave recovery disabled.

`VM::ready()` serializes initializers. A successful layout is published once with
release semantics, and availability checks acquire that publication. Repeated
agent/API initialization leaves the published offsets and oop width unchanged.
Initialization that has not yet found all required metadata remains retryable.

The sampled thread must be in Java, and the interrupted PC must not lie inside
the continuation freeze/thaw runtime (marked at library initialization:
`FreezeBase`, `ThawBase`, every function instantiated for
`Config<oop_kind, BarrierSet>`, and the freeze/thaw entry symbols), because an
in-progress freeze/thaw runs without a Java-to-VM transition and copied frames
can sit on the carrier and in the chunk at once. An unmarked callee of that
runtime is covered too: an in-progress freeze/thaw keeps its runtime frames on
the stack between the interrupted PC and the continuation boundary, so the walk
detects the crossing, while a completed transition has already returned past
them. Freeze/thaw transitions do not always change the thread's Java state, so
the state check alone is insufficient. The mark only annotates these frames:
they keep their symbols, and native stack walks continue through them.

For a native interrupted PC outside that runtime, the chunk is quiescent. An
example is a native call that keeps the thread in the Java state, such as
compiled `System.nanoTime`; JNI calls change the state and stay rejected. Recovery is
then gated on the first mounted Java frame the walk verified and emitted instead
of the interrupted PC; a frame that an anchor redirect replaces does not count.
That substitution requires positive proof: every native frame between the
interrupted PC and that Java frame was walked and resolved (no anchor-mediated
jump skipped them), and library initialization recognized both executable
freeze and thaw entry symbol families. When the prefix was skipped, the entry
families were not recognized, or no mounted Java frame was verified, the
interrupted PC keeps the conservative rejection.

The carrier's `Thread.cont` must identify a single outermost continuation.
Nested continuations are rejected because publication before native entry and
restoration after native exit can expose a different continuation from the
physical boundary. Recovery is attempted only at the first continuation boundary
crossed by the physical walk.

The walk runs inside `walkVM`'s existing `JmpCtxScope` fault recovery. It allocates
no memory, takes no locks, invokes no JNI/JVMTI functions and modifies neither heap
objects nor JVM frames. Concurrently relocating collectors require load barriers
that this reader does not provide and are excluded.

## Chunk and frame traversal

The walker follows `Continuation.tail` and chunk parent links, bounded to 256
chunks and the caller's remaining output-frame capacity. Each chunk's size,
current SP and bottom offset are checked before use. A non-forward frame step,
invalid method, unsupported frame kind or invalid relative pointer ends recovery.

Compiled frames use nmethod frame sizes. Scope decoding restores inlined methods
in Java call order. For a deoptimized frame, `VMNMethod::originalPC` recognizes
the exported deoptimization handler layout and reads the saved original PC only
inside the validated physical frame. JDK 21–22 use handler addresses, JDK 23–25
use handler offsets, and JDK 26+ use the shared handler-entry offset. A changed
PC must resolve to the same nmethod and provide a decodable scope.

Interpreted frames hold relative FP, locals and sender-SP values inside the
chunk. The walker validates and converts those values before advancing. These
representations follow OpenJDK's
[StackChunkFrameStream](https://github.com/openjdk/jdk21u/blob/master/src/hotspot/share/runtime/stackChunkFrameStream.inline.hpp)
and the stack layout described in
[continuationFreezeThaw.cpp](https://github.com/openjdk/jdk21u/blob/master/src/hotspot/share/runtime/continuationFreezeThaw.cpp).

## Completeness and diagnostics

Before appending any frozen caller, `walkVM` marks the trace truncated. It restores
the prior truncation state only when every reachable chunk and inline scope was
consumed successfully. Partial output remains useful when recovery fails, but its
trace stays truncated. Carrier recovery has its own validation and can still fail
after complete Java caller recovery.

Debug counters report successful and failed recovery attempts, interpreted and
compiled frames, and parent chunks. `walkvm_cont_barrier_hit` establishes that the
workload exercised a frozen continuation boundary independently of whether its
older callers were recovered.

## Regression coverage

- `FrozenVirtualThreadStackTest` compares recovered caller counts and order with
  the JVM's logical stack, including CPU/wall sampling, parent chunks, collection,
  depth limits, native-state fallback and fully thawed controls.
- `FrozenDeoptimizationTest` proves that a mounted compiled caller was invalidated
  before freezing and requires its physical and inlined callers to be restored.
- `frozenDeoptimization_ut.cpp` checks original-PC recovery across the supported
  handler layouts, frame bounds and invalid saved-PC slots.
- `frozenStackWalker_ut.cpp` exercises the production layout initialization,
  immutable successful publication and retry after incomplete metadata discovery.
- `originAnchorFrozen_ut.cpp` classifies the freeze/thaw runtime symbols,
  including the internal-linkage (`_ZL`) entry names in libjvm's symbol table, and
  walks with anchor-verified Java frames: an ordinary native call recovers the
  frozen callers, a freeze/thaw-runtime origin or an anchor-replaced compiled
  frame keeps the rejection, and without an anchor no Java frames are
  manufactured. It also drives `append` directly through its state, origin,
  nesting, geometry, depth and chunk-chain guards.
- `walkVmAttribution_ut.cpp` checks that freeze/thaw-marked frames keep their
  symbols in walkVM and in the FP/DWARF native-trace conversion.
- `NestedContinuationTransitionTest` holds real child-publication and child-return
  intervals open and rejects suspended child frames in sampled parent stacks.
