# Virtual Thread Continuation Unwind Fix Implementation Plan

> **Status: IMPLEMENTED** — All tasks complete as of 2026-03-30. See "Implementation Divergences" section below for how the final code differs from the original design.

**Goal:** Enable `walkVM` to traverse through `jdk.internal.vm.Continuation.enterSpecial` frames when profiling mounted virtual threads, covering both VTs that have never yielded (all frames thawed) and VTs that have yielded and remounted with frozen frames remaining.

**Architecture:** Two complementary paths, both navigating via `ContinuationEntry`:

1. **CPU-bound VT (never yielded, all frames thawed):** Profiler walks up through continuation body frames → `Continuation.enter` (normal JIT nmethod) → reaches `enterSpecial`. On JDK 27+ `enterSpecial` is an nmethod detected by identity (`nm == VMStructs::enterSpecialNMethod()`). On JDK 21-26 `enterSpecial` is a `RuntimeBlob`, so `findNMethod()` returns `NULL`; this is detected in the `nm == NULL` handler by combining three guards: `VMContinuationEntry::type_size() == 0` (JDK 21-26 marker), `VMStructs::hasContReturnBarrier()` (JDK 21+ proxy), and `vm_thread->hasActiveContinuation()`. In both cases the walker jumps to the carrier thread via `walkThroughContinuation(/*path_a=*/true)`.

2. **Yielded VT (partial thaw, frozen frames remain):** The bottommost thawed compiled frame has its return PC patched to `StubRoutines::_cont_returnBarrier`. Detected by PC comparison before `findNMethod`. Same `walkThroughContinuation(/*path_a=*/false)` navigation to the carrier.

Both paths use the same `walkThroughContinuation` lambda which computes `{carrier_fp, carrier_pc, carrier_sp}` from `entry_fp`. On JDK 21-26 (no `type_size()`) `entry_fp` is derived from the current `fp` register via fp-based fallback. The `isEntryFrame` / `JavaCallWrapper` path is never reached for either case.

### Implementation Divergences from Original Plan

| Aspect | Original plan | Actual implementation |
|--------|--------------|----------------------|
| Path A detection | `nm == enterSpecialNMethod()` inside `isNMethod()` block | JDK 27+: same. JDK 21-26: `nm == NULL` handler + `type_size()==0` + `hasContReturnBarrier()` + `hasActiveContinuation()` |
| Carrier navigation | `entry->entryFP()` via `contEntry()` | `walkThroughContinuation` lambda; `entry_fp` derived from `fp` on JDK 21-26 |
| `CONT_UNWIND_DISABLED` | Not modelled in plan | Handled: when disabled at continuation boundary, emit `BCI_NATIVE_FRAME, "JVM Continuation"` and break cleanly |
| New vmStructs helpers | `contEntry()` only | Also added `hasContReturnBarrier()` and `hasActiveContinuation()` (bypasses `type_size()` guard) |
| Test assertions | No walk-error sentinels | Carrier frames (`ForkJoinWorkerThread`) visible in stack traces |
| Test modes | `vm`, `fp` | `vm`, `vmx` only — fp/dwarf use ASGCT which cannot cross continuation boundary |
| Test profiler args | `wall=1ms` | `wall=1ms,filter=,wextend=vt_carrier` |

**Tech Stack:** C++ (C++14), JVM vmStructs introspection, GTest (C++ unit tests), JUnit 5 + JMC (Java integration tests), JDK 21+.

---

## File Map

| File | Change |
|---|---|
| `ddprof-lib/src/main/cpp/vmStructs.h` | Add `VMContinuationEntry` type; add `_cont_return_barrier`, `_cont_entry_return_pc`, `_enter_special_nm` static fields; `contEntry()` on VMThread; `isContReturnBarrier()` and `enterSpecialNMethod()` helpers |
| `ddprof-lib/src/main/cpp/vmStructs.cpp` | Initialise the three new static fields; find `_enter_special_nm` from CodeHeap after `_cont_entry_return_pc` is set |
| `ddprof-lib/src/main/cpp/counters.h` | Add `WALKVM_CONT_BARRIER_HIT`, `WALKVM_ENTER_SPECIAL_HIT`, `WALKVM_CONT_ENTRY_NULL` |
| `ddprof-lib/src/main/cpp/stackWalker.cpp` | (a) Add `enterSpecial` detection inside the `isNMethod()` block; (b) Add `cont_returnBarrier` branch before `isEntryFrame`; both branches share the same `contEntry()` navigation logic |
| `ddprof-test/src/test/java/com/datadoghq/profiler/wallclock/VirtualThreadWallClockTest.java` | New integration test covering both paths: CPU-bound VT (never-yield path) and I/O-blocking VT (cont_returnBarrier path) |

---

## Task 1: Add counters

**Files:**
- Modify: `ddprof-lib/src/main/cpp/counters.h:95-98`

- [x] **Step 1: Add three new counters before `NATIVE_LIBS_DROPPED`**

  In `counters.h`, the relevant lines are:
  ```cpp
    X(WALKVM_ANCHOR_NOT_IN_JAVA, "walkvm_anchor_not_in_java")                    \
    X(NATIVE_LIBS_DROPPED, "native_libs_dropped")                                \
  ```
  Change to:
  ```cpp
    X(WALKVM_ANCHOR_NOT_IN_JAVA,  "walkvm_anchor_not_in_java")                   \
    X(WALKVM_CONT_BARRIER_HIT,    "walkvm_cont_barrier_hit")                     \
    X(WALKVM_ENTER_SPECIAL_HIT,   "walkvm_enter_special_hit")                    \
    X(WALKVM_CONT_ENTRY_NULL,     "walkvm_cont_entry_null")                      \
    X(NATIVE_LIBS_DROPPED, "native_libs_dropped")                                \
  ```

- [x] **Step 2: Build**

  ```bash
  cd /Users/jaroslav.bachorik/go/src/github.com/DataDog/java-profiler
  ./gradlew :ddprof-lib:assemble -Pbuild_profile=debug 2>&1 | tail -20
  ```
  Expected: `BUILD SUCCESSFUL`

- [x] **Step 3: Commit**

  ```bash
  git add ddprof-lib/src/main/cpp/counters.h
  git commit -m "feat(walkvm): add continuation walk counters"
  ```

---

## Task 2: Expose `ContinuationEntry` and `enterSpecial` nmethod in vmStructs

**Files:**
- Modify: `ddprof-lib/src/main/cpp/vmStructs.h`
- Modify: `ddprof-lib/src/main/cpp/vmStructs.cpp`

### Background

`ContinuationEntry` is embedded on the carrier thread's stack immediately below the `enterSpecial` frame's saved-fp slot. `JavaThread::_cont_entry` points to the innermost active entry (a linked list for nested virtual threads).

On-stack layout (identical on x86-64 and aarch64 — the JVM standardises FP to point at the `{saved_fp, lr}` pair):

```
[high addresses]
  return_addr_to_carrier   <- caller of enterSpecial (in Continuation.run())
  saved_fp                 <- entryFP() == (uintptr_t)entry + ContinuationEntry::size()
  ContinuationEntry {
    _parent                <- enclosing ContinuationEntry* or null
    ...                    <- other fields not needed by profiler
  }                        <- entry == vm_thread->_cont_entry
  [argsize padding]
  bottommost thawed frame  <- return PC = cont_returnBarrier (if frozen frames exist)
                                       OR real caller PC (if fully thawed)
[low addresses]
```

Given `entry_fp = entry->entryFP()`:
- `*(uintptr_t*)entry_fp` = carrier FP
- `((const void**)entry_fp)[1]` = carrier PC (return addr back to Continuation.run())
- `entry_fp + 2*sizeof(void*)` = carrier SP

`ContinuationEntry::_return_pc` is a static address baked into the `enterSpecial` nmethod's code at the point after the thaw call. The profiler caches it as `_cont_entry_return_pc` and then uses it to locate the `enterSpecial` nmethod itself via `CodeHeap::findNMethod(_cont_entry_return_pc)`, stored as `_enter_special_nm`. This is the same pattern used to find `_interpreter_nm` from `_interpreter_start`.

### Steps

- [x] **Step 1: Add `VMContinuationEntry` to `DECLARE_TYPES_DO`**

  In `vmStructs.h`, `DECLARE_TYPES_DO` currently is:
  ```cpp
  #define DECLARE_TYPES_DO(f) \
      f(VMClassLoaderData,    MATCH_SYMBOLS("ClassLoaderData"))   \
      f(VMConstantPool,       MATCH_SYMBOLS("ConstantPool"))      \
      f(VMConstMethod,        MATCH_SYMBOLS("ConstMethod"))       \
      f(VMFlag,               MATCH_SYMBOLS("JVMFlag", "Flag"))   \
      f(VMJavaFrameAnchor,    MATCH_SYMBOLS("JavaFrameAnchor"))   \
      f(VMKlass,              MATCH_SYMBOLS("Klass"))             \
      f(VMMethod,             MATCH_SYMBOLS("Method"))            \
      f(VMNMethod,            MATCH_SYMBOLS("nmethod"))           \
      f(VMSymbol,             MATCH_SYMBOLS("Symbol"))            \
      f(VMThread,             MATCH_SYMBOLS("Thread"))
  ```
  Change to:
  ```cpp
  #define DECLARE_TYPES_DO(f) \
      f(VMClassLoaderData,      MATCH_SYMBOLS("ClassLoaderData"))   \
      f(VMConstantPool,         MATCH_SYMBOLS("ConstantPool"))      \
      f(VMConstMethod,          MATCH_SYMBOLS("ConstMethod"))       \
      f(VMContinuationEntry,    MATCH_SYMBOLS("ContinuationEntry")) \
      f(VMFlag,                 MATCH_SYMBOLS("JVMFlag", "Flag"))   \
      f(VMJavaFrameAnchor,      MATCH_SYMBOLS("JavaFrameAnchor"))   \
      f(VMKlass,                MATCH_SYMBOLS("Klass"))             \
      f(VMMethod,               MATCH_SYMBOLS("Method"))            \
      f(VMNMethod,              MATCH_SYMBOLS("nmethod"))           \
      f(VMSymbol,               MATCH_SYMBOLS("Symbol"))            \
      f(VMThread,               MATCH_SYMBOLS("Thread"))
  ```

- [x] **Step 2: Add field declarations in `DECLARE_TYPE_FIELD_DO`**

  2a. Add `_cont_entry_offset` to the `VMJavaThread` block (around line 190):
  ```cpp
      type_begin(VMJavaThread, MATCH_SYMBOLS("JavaThread", "Thread"))
          field(_thread_osthread_offset, offset, MATCH_SYMBOLS("_osthread"))
          field(_thread_anchor_offset, offset, MATCH_SYMBOLS("_anchor"))
          field(_thread_state_offset, offset, MATCH_SYMBOLS("_thread_state"))
          field(_thread_vframe_offset, offset, MATCH_SYMBOLS("_vframe_array_head"))
          field_with_version(_cont_entry_offset, offset, 21, MAX_VERSION, MATCH_SYMBOLS("_cont_entry"))
      type_end()
  ```

  2b. Add `_cont_return_barrier_addr` to the `VMStubRoutine` block (around line 250):
  ```cpp
      type_begin(VMStubRoutine, MATCH_SYMBOLS("StubRoutines"))
          field(_call_stub_return_addr, address, MATCH_SYMBOLS("_call_stub_return_address"))
          field_with_version(_cont_return_barrier_addr, address, 21, MAX_VERSION, MATCH_SYMBOLS("_cont_returnBarrier"))
      type_end()
  ```

  2c. Add a new `VMContinuationEntry` type block after the `VMJavaFrameAnchor` block:
  ```cpp
      type_begin(VMContinuationEntry, MATCH_SYMBOLS("ContinuationEntry"))
          field_with_version(_cont_entry_parent_offset, offset, 21, MAX_VERSION, MATCH_SYMBOLS("_parent"))
          field_with_version(_cont_entry_return_pc_addr, address, 21, MAX_VERSION, MATCH_SYMBOLS("_return_pc"))
      type_end()
  ```

- [x] **Step 3: Add three static variables to the `VMStructs` class body**

  In `vmStructs.h`, add these three lines directly after `static const void* _call_stub_return;` (around line 313):
  ```cpp
      static const void* _cont_return_barrier;
      static const void* _cont_entry_return_pc;
      static VMNMethod*  _enter_special_nm;
  ```

- [x] **Step 4: Add static helpers to `VMStructs`**

  In `vmStructs.h`, add these two static methods inside the `VMStructs` class, near `isEntryFrame` in `VMNMethod` or after the static variable declarations:
  ```cpp
      static bool isContReturnBarrier(const void* pc) {
          return _cont_return_barrier != nullptr && pc == _cont_return_barrier;
      }

      static VMNMethod* enterSpecialNMethod() {
          return _enter_special_nm;
      }
  ```

- [x] **Step 5: Add the `VMContinuationEntry` DECLARE class**

  Add this new class after the `DECLARE_END` of `VMJavaFrameAnchor` (around line 680):
  ```cpp
  DECLARE(VMContinuationEntry)
    public:
      static bool isAvailable() {
          return _cont_entry_parent_offset >= 0;
      }

      VMContinuationEntry* parent() {
          assert(_cont_entry_parent_offset >= 0);
          return (VMContinuationEntry*) SafeAccess::loadPtr((void**) at(_cont_entry_parent_offset), nullptr);
      }

      // Address of the enterSpecial frame's {saved_fp, return_addr} pair.
      // Layout above this address: [saved_fp][return_addr_to_carrier][carrier_sp...]
      uintptr_t entryFP() const {
          return (uintptr_t)this + type_size();
      }
  DECLARE_END
  ```

- [x] **Step 6: Add `contEntry()` to `VMThread`**

  Inside the `VMThread` `DECLARE` block, add after `anchor()`:
  ```cpp
      VMContinuationEntry* contEntry() {
          if (_cont_entry_offset < 0) return nullptr;
          void* ptr = SafeAccess::loadPtr((void**) at(_cont_entry_offset), nullptr);
          return ptr != nullptr ? VMContinuationEntry::cast(ptr) : nullptr;
      }
  ```

- [x] **Step 7: Add static-variable definitions in `vmStructs.cpp`**

  Add three lines after `const void* VMStructs::_call_stub_return = nullptr;` (around line 36):
  ```cpp
  const void* VMStructs::_cont_return_barrier   = nullptr;
  const void* VMStructs::_cont_entry_return_pc  = nullptr;
  VMNMethod*  VMStructs::_enter_special_nm       = nullptr;
  ```

- [x] **Step 8: Initialise the new fields in `vmStructs.cpp`**

  In `vmStructs.cpp`, after the existing `_call_stub_return` init block (around line 394), add:
  ```cpp
      if (_cont_return_barrier_addr != NULL) {
          _cont_return_barrier = *(const void**)_cont_return_barrier_addr;
      }
      if (_cont_entry_return_pc_addr != NULL) {
          _cont_entry_return_pc = *(const void**)_cont_entry_return_pc_addr;
      }
  ```

  Then, after the existing `_interpreter_nm` lookup (around line 443):
  ```cpp
      if (_enter_special_nm == NULL && _cont_entry_return_pc != NULL) {
          _enter_special_nm = CodeHeap::findNMethod(_cont_entry_return_pc);
      }
  ```

  This mirrors the existing pattern `_interpreter_nm = CodeHeap::findNMethod(_interpreter_start)`.

- [x] **Step 9: Build**

  ```bash
  ./gradlew :ddprof-lib:assemble -Pbuild_profile=debug 2>&1 | tail -20
  ```
  Expected: `BUILD SUCCESSFUL`

- [x] **Step 10: Commit**

  ```bash
  git add ddprof-lib/src/main/cpp/vmStructs.h ddprof-lib/src/main/cpp/vmStructs.cpp
  git commit -m "feat(vmstructs): expose ContinuationEntry and enterSpecial nmethod"
  ```

---

## Task 3: Add continuation unwind paths in `walkVM`

**Files:**
- Modify: `ddprof-lib/src/main/cpp/stackWalker.cpp`

### What to implement

Both paths produce the same carrier-thread `{sp, fp, pc}` triple from `entry->entryFP()` and `continue` the walk loop. The computation:

```
entry_fp   = entry->entryFP()            // = (uintptr_t)entry + ContinuationEntry::type_size()
carrier_fp = *(uintptr_t*)entry_fp       // saved FP from enterSpecial's frame prologue
carrier_pc = ((const void**)entry_fp)[1] // return address baked into enterSpecial → Continuation.run()
carrier_sp = entry_fp + 2*sizeof(void*)  // SP of the Continuation.run() call site
```

**Path A — `enterSpecial` nmethod detection** (CPU-bound VT, all frames thawed):
Placed at the *top* of the `isNMethod()` block, before the frame is emitted or `frameSize()` is used. When `nm == VMStructs::enterSpecialNMethod()`, skip directly to carrier via `contEntry()`. This prevents incorrect `frameSize()` usage on the `enterSpecial` frame and avoids emitting a profiler-internal stub as a user-visible frame.

**Path B — `cont_returnBarrier` detection** (yielded VT, frozen frames remain):
New `else if` branch between the `isNMethod()` and `isEntryFrame()` blocks. Triggered when the current PC equals `StubRoutines::_cont_returnBarrier`.

### Steps

- [x] **Step 1: Add Path A — `enterSpecial` detection inside `isNMethod()`**

  Locate the opening of the `isNMethod()` block (around line 443):
  ```cpp
              } else if (nm->isNMethod()) {
                  // Check if deoptimization is in progress before walking compiled frames
                  if (vm_thread != NULL && vm_thread->inDeopt()) {
  ```
  Insert the enterSpecial check at the very beginning of this block:
  ```cpp
              } else if (nm->isNMethod()) {
                  // enterSpecial is a generated native nmethod that acts as the
                  // continuation entry stub. It has no JavaCallWrapper, so
                  // isEntryFrame() will not fire for it. Detect it by identity
                  // and navigate to the carrier thread via ContinuationEntry.
                  if (nm == VMStructs::enterSpecialNMethod()) {
                      Counters::increment(WALKVM_ENTER_SPECIAL_HIT);
                      VMContinuationEntry* entry = vm_thread != nullptr ? vm_thread->contEntry() : nullptr;
                      if (entry == nullptr) {
                          Counters::increment(WALKVM_CONT_ENTRY_NULL);
                          fillFrame(frames[depth++], BCI_ERROR, "break_cont_entry_null");
                          break;
                      }
                      uintptr_t entry_fp = entry->entryFP();
                      if (!goodPtr((void*)entry_fp) || !aligned(entry_fp)) {
                          fillFrame(frames[depth++], BCI_ERROR, "break_cont_entry_fp");
                          break;
                      }
                      uintptr_t carrier_fp = *(uintptr_t*)entry_fp;
                      const void* carrier_pc = ((const void**)entry_fp)[1];
                      uintptr_t carrier_sp = entry_fp + 2 * sizeof(void*);
                      if (!sameStack(sp, carrier_sp, bottom) || !aligned(carrier_sp)) {
                          fillFrame(frames[depth++], BCI_ERROR, "break_cont_carrier_sp");
                          break;
                      }
                      sp = carrier_sp;
                      fp = carrier_fp;
                      pc = carrier_pc;
                      continue;
                  }
                  // Check if deoptimization is in progress before walking compiled frames
                  if (vm_thread != NULL && vm_thread->inDeopt()) {
  ```

- [x] **Step 2: Add Path B — `cont_returnBarrier` branch**

  Locate the `isEntryFrame` branch (around line 502):
  ```cpp
              } else if (nm->isEntryFrame(pc) && !features.mixed) {
  ```
  Insert a new `else if` immediately before it:
  ```cpp
              } else if (VMStructs::isContReturnBarrier(pc)) {
                  // The bottommost thawed compiled frame's return PC has been
                  // patched to cont_returnBarrier, meaning frozen frames remain
                  // in the StackChunk. Navigate via ContinuationEntry to the
                  // carrier thread frames above the enterSpecial stub.
                  Counters::increment(WALKVM_CONT_BARRIER_HIT);
                  VMContinuationEntry* entry = vm_thread != nullptr ? vm_thread->contEntry() : nullptr;
                  if (entry == nullptr) {
                      Counters::increment(WALKVM_CONT_ENTRY_NULL);
                      fillFrame(frames[depth++], BCI_ERROR, "break_cont_entry_null");
                      break;
                  }
                  uintptr_t entry_fp = entry->entryFP();
                  if (!goodPtr((void*)entry_fp) || !aligned(entry_fp)) {
                      fillFrame(frames[depth++], BCI_ERROR, "break_cont_entry_fp");
                      break;
                  }
                  uintptr_t carrier_fp = *(uintptr_t*)entry_fp;
                  const void* carrier_pc = ((const void**)entry_fp)[1];
                  uintptr_t carrier_sp = entry_fp + 2 * sizeof(void*);
                  if (!sameStack(sp, carrier_sp, bottom) || !aligned(carrier_sp)) {
                      fillFrame(frames[depth++], BCI_ERROR, "break_cont_carrier_sp");
                      break;
                  }
                  sp = carrier_sp;
                  fp = carrier_fp;
                  pc = carrier_pc;
                  continue;
              } else if (nm->isEntryFrame(pc) && !features.mixed) {
  ```

- [x] **Step 3: Build**

  ```bash
  ./gradlew :ddprof-lib:assemble -Pbuild_profile=debug 2>&1 | tail -20
  ```
  Expected: `BUILD SUCCESSFUL`

- [x] **Step 4: Commit**

  ```bash
  git add ddprof-lib/src/main/cpp/stackWalker.cpp ddprof-lib/src/main/cpp/vmStructs.h
  git commit -m "fix(walkvm): unwind through enterSpecial and cont_returnBarrier"
  ```

---

## Task 4: Integration tests — both VT unwind paths

**Files:**
- Create: `ddprof-test/src/test/java/com/datadoghq/profiler/wallclock/VirtualThreadWallClockTest.java`

### What to test

Two test methods, one per path:

**`samplesCarrierFramesFromCpuBoundVT`** — Path A (enterSpecial detection).
A VT that never blocks (CPU-only spin loop) is never suspended, so all frames are always thawed and `cont_returnBarrier` never appears. The profiler must traverse `enterSpecial` via the nmethod-identity check to reach carrier frames.

**`samplesCarrierFramesFromBlockingVT`** — Path B (cont_returnBarrier).
A VT that repeatedly parks and unparks will have its frames frozen and thawed. When remounted with frozen frames still in the StackChunk, `cont_returnBarrier` is the return PC of the bottommost thawed frame.

Both methods assert:
1. At least one sample from the VT's lambda is captured.
2. No sample contains any `break_cont_*` or `break_entry_frame` sentinel in the stack trace string.

The test class is skipped entirely on JDK < 21.

- [x] **Step 1: Write the test**

  ```java
  package com.datadoghq.profiler.wallclock;

  import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
  import com.datadoghq.profiler.Platform;
  import com.datadoghq.profiler.junit.CStack;
  import com.datadoghq.profiler.junit.RetryTest;
  import org.junit.jupiter.api.TestTemplate;
  import org.junit.jupiter.params.provider.ValueSource;
  import org.openjdk.jmc.common.item.IItem;
  import org.openjdk.jmc.common.item.IItemCollection;
  import org.openjdk.jmc.common.item.IItemIterable;
  import org.openjdk.jmc.common.item.IMemberAccessor;
  import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

  import java.util.concurrent.CountDownLatch;
  import java.util.concurrent.locks.LockSupport;

  import static org.junit.jupiter.api.Assertions.assertFalse;
  import static org.junit.jupiter.api.Assertions.assertTrue;

  public class VirtualThreadWallClockTest extends CStackAwareAbstractProfilerTest {

      private volatile long sink;

      public VirtualThreadWallClockTest(@CStack String cstack) {
          super(cstack);
      }

      @Override
      protected boolean isPlatformSupported() {
          // Virtual threads require JDK 21+
          return Platform.isJavaVersionAtLeast(21);
      }

      /**
       * Path A: enterSpecial nmethod detection.
       * A CPU-bound VT never yields, so all frames stay thawed and cont_returnBarrier
       * never appears. The profiler must unwind through enterSpecial directly.
       */
      @RetryTest(3)
      @TestTemplate
      @ValueSource(strings = {"vm", "fp"})
      public void samplesCarrierFramesFromCpuBoundVT(@CStack String cstack) throws Exception {
          CountDownLatch started = new CountDownLatch(1);
          Thread vt = Thread.ofVirtual().start(() -> {
              started.countDown();
              long sum = 0;
              for (long i = 0; i < 600_000_000L; i++) {
                  sum += i;
              }
              sink = sum;
          });
          started.await();
          vt.join(15_000);
          stopProfiler();

          assertNoWalkErrors("VirtualThreadWallClockTest");
      }

      /**
       * Path B: cont_returnBarrier detection.
       * A VT that parks and unparks repeatedly will have frames frozen into a StackChunk.
       * On remount with frozen frames remaining, the bottommost thawed frame has
       * cont_returnBarrier as its return PC.
       */
      @RetryTest(3)
      @TestTemplate
      @ValueSource(strings = {"vm", "fp"})
      public void samplesCarrierFramesFromBlockingVT(@CStack String cstack) throws Exception {
          Thread[] carrier = new Thread[1];
          CountDownLatch started = new CountDownLatch(1);
          Thread vt = Thread.ofVirtual().start(() -> {
              carrier[0] = Thread.currentThread();
              started.countDown();
              // Park/unpark 200 times to exercise freeze/thaw cycle
              for (int i = 0; i < 200; i++) {
                  LockSupport.park();
              }
          });
          started.await();
          for (int i = 0; i < 200; i++) {
              Thread.sleep(5);   // give wall-clock sampler time to fire during freeze/thaw
              LockSupport.unpark(vt);
          }
          vt.join(10_000);
          stopProfiler();

          assertNoWalkErrors("VirtualThreadWallClockTest");
      }

      /** Verifies at least one sample from this test class with no walk-error sentinels. */
      private void assertNoWalkErrors(String markerClass) throws Exception {
          IItemCollection events = verifyEvents("datadog.MethodSample");
          boolean sawSample = false;
          for (IItemIterable samples : events) {
              IMemberAccessor<String, IItem> traceAcc =
                      JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());
              if (traceAcc == null) continue;
              for (IItem sample : samples) {
                  String trace = traceAcc.getMember(sample);
                  if (trace == null || !trace.contains(markerClass)) continue;
                  sawSample = true;
                  assertFalse(trace.contains("break_cont_entry_null"),
                          "cont_entry null walk error in: " + trace);
                  assertFalse(trace.contains("break_cont_entry_fp"),
                          "cont_entry fp walk error in: " + trace);
                  assertFalse(trace.contains("break_cont_carrier_sp"),
                          "cont carrier sp walk error in: " + trace);
                  assertFalse(trace.contains("break_entry_frame"),
                          "entry frame walk error in: " + trace);
              }
          }
          assertTrue(sawSample, "No wall-clock samples captured from the virtual thread");
      }

      @Override
      protected void after() {}

      @Override
      protected String getProfilerCommand() {
          return "wall=1ms";
      }
  }
  ```

- [x] **Step 2: Build**

  ```bash
  ./gradlew :ddprof-test:compileTestJava 2>&1 | tail -20
  ```
  Expected: `BUILD SUCCESSFUL`

- [x] **Step 3: Run on JDK 21+**

  ```bash
  ./gradlew :ddprof-test:testRelease \
    --tests "com.datadoghq.profiler.wallclock.VirtualThreadWallClockTest" 2>&1 | tail -40
  ```
  Expected: both test methods pass. On JDK < 21 the entire class is skipped via `isPlatformSupported()`.

- [x] **Step 4: Commit**

  ```bash
  git add ddprof-test/src/test/java/com/datadoghq/profiler/wallclock/VirtualThreadWallClockTest.java
  git commit -m "test(wallclock): virtual thread continuation unwind smoke tests"
  ```

---

## Self-Review

### Spec coverage

| Hypothesis | Task that addresses it |
|---|---|
| H1: `cont_returnBarrier` not recognised | Task 3 Path B |
| H2: No `JavaCallWrapper` for `enterSpecial` | Task 3 Path A (enterSpecial is bypassed, `isEntryFrame` never reached) |
| H3: Wrong blob-type classification for `enterSpecial` | Task 3 Path A (detection is by nmethod identity, not name/type) |
| H4: Broken FP chain at ContinuationEntry boundary | Task 3 both paths (use `entryFP()` instead of raw FP chain) |
| H5: `@Hidden` / non-standard frame at yield point | Resolved: `Continuation.enter` is a normal JIT nmethod; H5 was a misidentification of the real problem (the `enterSpecial` frame above it, now covered by Path A) |

**H5 closure:** The `@Hidden` annotation and the non-local yield-return path do not affect the physical JIT frame layout or OopMap coverage of `Continuation.enter`. The profiler walks it correctly via the standard `isNMethod()` path. The actual difficulty was always the `enterSpecial` frame above it, which is now addressed by Path A.

### Placeholder scan

None found.

### Type consistency

- `VMContinuationEntry` is defined in Task 2 Steps 1–5, used in Task 3 Steps 1–2. `entryFP()` defined in Step 5, called in Steps 1 and 2 of Task 3. Consistent.
- `WALKVM_CONT_BARRIER_HIT`, `WALKVM_ENTER_SPECIAL_HIT`, `WALKVM_CONT_ENTRY_NULL` defined in Task 1, used in Task 3. Consistent.
- `isContReturnBarrier()` and `enterSpecialNMethod()` defined in Task 2 Step 4, called in Task 3 Steps 1 and 2. Consistent.
- `_enter_special_nm` declared in Task 2 Step 3, defined in Task 2 Step 7, initialised in Task 2 Step 8, returned by `enterSpecialNMethod()` in Step 4. Consistent.
