# Eclipse OpenJ9 Profiling Limitations

This document describes the architectural limitations of Eclipse OpenJ9 (IBM Semeru Runtime) that affect profiling capabilities in the Datadog Java Profiler, particularly for native stack unwinding and remote symbolication.

## Overview

OpenJ9 uses a fundamentally different architecture from HotSpot for managing execution stacks. This architectural difference makes certain profiling features impossible or unreliable on OpenJ9.

## Dual-Stack Architecture

### The Core Difference

**Official OpenJ9 Documentation** ([`-Xmso` option](https://eclipse.dev/openj9/docs/xmso/)):

> "Java methods and native methods run on two different stacks and the VM handles switching between them for JNI calls."

This is the root cause of most profiling limitations on OpenJ9.

### Stack Configuration

OpenJ9 maintains two separate stacks per thread:

- **Java Stack** (`-Xss`): Managed by the JVM
  - Contains Java method frames
  - Tracked by J9VMThread structure
  - Used by bytecode interpreter and JIT-compiled code

- **Native Stack** (`-Xmso`): Operating system thread stack
  - Contains C/C++ function frames
  - Standard OS stack with frame pointers
  - Used for native method execution and JNI calls

### Contrast with HotSpot

| Aspect | HotSpot | OpenJ9 |
|--------|---------|---------|
| **Stack Model** | Unified stack | Dual stack (Java + Native) |
| **JNI Transition** | Push frame on same stack | Switch to different stack |
| **Frame Pointer Chain** | Continuous across JNI | Broken at JNI boundary |
| **Memory Layout** | Java frames ↔ Native frames in same region | Separate memory regions |

### Visual Representation

**HotSpot (Unified Stack)**:
```
┌──────────────────┐ High addresses
│  Native Frame 3  │ ← FP chain continues
├──────────────────┤
│  Native Frame 2  │
├──────────────────┤
│  JNI Transition  │
├──────────────────┤
│  Java Frame B    │
├──────────────────┤
│  Java Frame A    │
└──────────────────┘ Low addresses
    Single stack
```

**OpenJ9 (Dual Stack)**:
```
Java Stack:              Native Stack:
┌──────────────────┐    ┌──────────────────┐
│  Java Frame B    │    │  Native Frame 3  │
├──────────────────┤    ├──────────────────┤
│  Java Frame A    │    │  Native Frame 2  │
└──────────────────┘    └──────────────────┘
  (suspended)             (active)
       ↕ VM switches stacks ↕
  No frame pointer connection!
```

## Impact on Profiling Features

### 1. Remote Symbolication (DWARF Unwinding)

**Status**: ❌ **Not supported on any OpenJ9 version**

**Why it fails**:

1. **DWARF unwinding operates on a single stack**
   - When a profiling signal fires in native code, DWARF unwinder starts from the signal context (PC, SP, FP)
   - It follows frame pointers backwards through the native stack
   - It successfully unwinds native frames... until it reaches the JNI entry point
   - **Then it stops** - there's no frame pointer linking to the Java stack

2. **The frames we capture are VM internals, not JNI library code**
   - Test logs show frames like `VM_BytecodeInterpreterCompressed::run()`, `TR_BitVector`, `OMR::LocalCSE`
   - These are J9's interpreter/JIT frames from the **Java stack**
   - The actual JNI library frames (e.g., `libddproftest.so`) executed on the **native stack**
   - DWARF unwinder never reaches them because it can't jump stacks

3. **Non-standard frame layout**
   - From [OpenJ9 Issue #3497](https://github.com/eclipse-openj9/openj9/issues/3497):
     - "OpenJ9 doesn't produce ABI-compliant stack frames, making them unwalkable by standard profiling tools"
   - Even with frame pointers preserved, frames may not follow x86-64/ARM calling conventions

**Evidence from profiler logs** (J9 17.0.17-sem):
```
[TEST::INFO] walkDwarf returned 6 frames
[TEST::INFO] resolveNativeFrame: PC 0x... -> symbol: _ZN32VM_BytecodeInterpreterCompressed3runEP10J9VMThread
[TEST::INFO] resolveNativeFrame: PC 0x... -> symbol: _ZN12TR_BitVector12setChunkSizeEi
[TEST::INFO] resolveNativeFrame: PC 0x... -> symbol: returnFromJITL
[TEST::INFO] No frames from libddproftest found in any samples
```

All captured frames are VM internals. The JNI library frames are missing because they're on the separate native stack.

**Affected Tests**:
- `RemoteSymbolicationTest` - Skipped on all J9 versions

### 2. ASGCT (AsyncGetCallTrace) Limitations

**File**: `ddprof-lib/src/main/cpp/j9Ext.h:58-65`

```cpp
static bool can_use_ASGCT() {
  // as of 21.0.6 the use of ASGCT will lead to almost immediate crash or livelock on J9
  return (VM::java_version() == 8 && VM::java_update_version() >= 361) ||
         (VM::java_version() == 11 && VM::java_update_version() >= 18) ||
         (VM::java_version() == 17 && VM::java_update_version() >= 6) ||
         (VM::java_version() >= 18 && VM::java_version() < 21);
}
```

**Version-specific behavior**:

- **J9 < 8u361, 11u18, 17u6**: ASGCT unsafe - causes crashes or livelocks
- **J9 8u361+, 11u18+, 17u6+, 18-20**: ASGCT supported with limitations
- **J9 >= 21**: ASGCT completely disabled - must use JVMTI extensions

**Why J9 >= 21 uses JVMTI mode**:
```cpp
// profiler.cpp:1118-1127
if (VM::isOpenJ9()) {
  if (!J9Ext::shouldUseAsgct() || !J9Ext::can_use_ASGCT()) {
    TEST_LOG("J9[cpu]=jvmti");
    return &j9_engine;  // Uses JVMTI, no signal-based profiling
  }
  TEST_LOG("J9[cpu]=asgct");
}
```

JVMTI mode:
- Uses `com.ibm.GetStackTraceExtended` JVMTI extension
- Polling-based, not signal-based
- No DWARF unwinding invoked
- Cannot capture native frames via DWARF

### 3. SafeFetch Implementation

**Status**: ❌ **Not implemented for J9**

**File**: `ddprof-test/src/test/java/com/datadoghq/profiler/classgc/ClassGCTest.java:46-47`

```java
// TODO temporarily skip this for J9 as it is crashing due to missing safe fetch impl
Assumptions.assumeFalse(Platform.isJ9());
```

Safe fetch allows protected memory access without crashing. Missing implementation causes crashes during class GC operations.

### 4. JVMTI GetClassSignature Issues

**Status**: ⚠️ **Crashes on J9 17+ and J9 8**

**File**: `ddprof-test/src/test/java/com/datadoghq/profiler/metadata/BoundMethodHandleMetadataSizeTest.java:24-26`

```java
assumeFalse(Platform.isJ9() && isAsan()); // running this test on j9 and asan is weirdly crashy
assumeFalse(Platform.isJ9() && Platform.isJavaVersion(8)); // getting crash-failure in CI reliably
assumeFalse(Platform.isJ9() && Platform.isJavaVersion(17)); // JVMTI::GetClassSignature() reliably crashing
```

### 5. jmethodID Safety

**File**: `ddprof-lib/src/main/cpp/j9Ext.h:67-71`

```cpp
static bool is_jvmti_jmethodid_safe() {
  // only JDK 8 is safe to use jmethodID in JVMTI for deferred resolution
  //   unless -XX:+KeepJNIIDs=true is provided
  return VM::java_version() == 8;
}
```

**Workaround for J9 > 8**: Use JVM flag `-XX:+KeepJNIIDs=true` to prevent jmethodID invalidation.

Without this flag, the profiler issues warnings:
```
[ddprof] [WARN] Safe jmethodID access is not available on this JVM.
Using CPU profiler on your own risk. Use -XX:+KeepJNIIDs=true JVM flag...
```

## Why These Cannot Be Fixed in the Profiler

### 1. DWARF Unwinding Limitation

The profiler's DWARF unwinder (`stackWalker.cpp:walkDwarf()`) is fundamentally constrained by:

- **DWARF operates on a single stack**: The `.eh_frame` exception handling information describes frame unwinding within a contiguous stack region
- **No cross-stack metadata**: OpenJ9 doesn't provide DWARF debug info linking Java stack ↔ Native stack
- **Signal context limitation**: When the profiling signal fires, CPU registers (PC, SP, FP) point to ONE stack only
- **Missing cross-references**: HotSpot uses `JavaFrameAnchor` structures at JNI entry points to link stacks; OpenJ9's mechanism is VM-internal

### 2. Architectural Differences

From [OpenJ9 Issue #3497](https://github.com/eclipse-openj9/openj9/issues/3497), three fundamental issues:

1. **Dual Stack Architecture**: "OpenJ9 maintains separate Java and native stacks with execution weaving between them"
2. **Non-Standard Linkage**: "OpenJ9 doesn't produce ABI-compliant stack frames"
3. **GC Safety Constraints**: "Stack walking is only reliably safe at garbage collection points"

## Recommended Profiling Approach for OpenJ9

### Option 1: Use OpenJ9 JVMTI Extensions (Future Work)

OpenJ9 provides custom JVMTI extensions (`j9Ext.cpp:34-59`):

- `com.ibm.GetOSThreadID` - Get OS thread ID
- `com.ibm.GetJ9vmThread` - Get J9 VM thread pointer
- `com.ibm.GetStackTraceExtended` - Extended stack trace with frame types
- `com.ibm.GetAllStackTracesExtended` - Batch stack traces

These could be used for J9-specific profiling, but would require:
- Polling-based sampling (not signal-based)
- Separate code path for J9
- Different performance characteristics

### Option 2: Use HotSpot-Based JDKs

For profiling with native code and remote symbolication:
- **Temurin (Eclipse Adoptium)** - HotSpot-based, fully supported
- **Oracle JDK** - HotSpot-based, fully supported
- **Zulu** - HotSpot-based, fully supported
- **Corretto** - HotSpot-based, fully supported

### Option 3: Linux perf with DWARF

For performance analysis on OpenJ9, use Linux perf directly:

```bash
perf record --call-graph dwarf -F 99 java -jar app.jar
perf report
```

Note: This provides better results than frame pointer chaining, but still limited by dual-stack architecture.

## Tests Skipped for J9

Complete list of tests that skip on OpenJ9:

| Test | Location | Reason |
|------|----------|--------|
| `RemoteSymbolicationTest` | cpu/ | DWARF unwinding fails across JNI boundaries |
| `ClassGCTest` | classgc/ | Missing SafeFetch implementation |
| `LoadLibraryTest` | nativelibs/ | Library handling differs |
| `NativeLibrariesTest` | nativelibs/ | Combined with Zing skip |
| `ContextCpuTest` | cpu/ | Context tracking incompatible |
| `LightweightContextCpuTest` | cpu/ | Context tracking incompatible |
| `TagContextTest` | context/ | Context tag handling |
| `JfrDumpTest` | jfr/ | JFR dump issues |
| `CollapsingSleepTest` | wallclock/ | Sleep collapsing incompatible |
| `MegamorphicCallTest` | wallclock/ | Combined with Zing skip |
| `WallClockThreadFilterTest` | wallclock/ | Thread filtering differences |
| `BaseContextWallClockTest` | wallclock/ | Combined with Zing skip |
| `BoundMethodHandleMetadataSizeTest` | metadata/ | GetClassSignature crashes |

## Platform Detection

```java
// Platform.java:304-306
public static boolean isJ9() {
  return System.getProperty("java.vm.name").contains("J9");
}
```

## References

- [OpenJ9 Issue #3497 - Frame Pointer Preservation](https://github.com/eclipse-openj9/openj9/issues/3497)
- [OpenJ9 Documentation - Native Stack (`-Xmso`)](https://eclipse.dev/openj9/docs/xmso/)
- [OpenJ9 Documentation - Java Dump (Thread Structure)](https://eclipse-openj9.github.io/openj9-docs/dump_javadump/)
- [OpenJ9 Issue #3676 - Compilation Flags](https://github.com/eclipse-openj9/openj9/issues/3676)

## Conclusion

The limitations described in this document are **architectural** - they stem from OpenJ9's fundamental design decisions around stack management and execution model. These are not bugs in the profiler or missing features that can be added. The profiler correctly detects OpenJ9 and falls back to supported profiling modes (JVMTI for J9 >= 21, limited ASGCT for older versions).

For production profiling with native code analysis and remote symbolication, **HotSpot-based JDKs are required**.
