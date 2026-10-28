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

The sampled thread must be in Java, and its original interrupted PC must resolve
to an interpreted or compiled Java body. Freeze/thaw transitions do not always
change the thread's Java state, so the state check alone is insufficient. Native,
runtime and generated transition PCs do not permit heap recovery.

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
- `NestedContinuationTransitionTest` holds real child-publication and child-return
  intervals open and rejects suspended child frames in sampled parent stacks.
