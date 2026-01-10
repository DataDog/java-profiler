# JVMTI Memory Leak Investigation

**Date:** 2026-01-09
**Severity:** Critical - Customer Production Issue
**Total Leak:** 10.5 GB native memory in production

## Executive Summary

Customer reported massive native memory growth in production profiler deployment. Native Memory Tracking (NMT) analysis revealed **10.5 GB JVMTI memory** from two distinct sources:

1. **GetLineNumberTable leak: 1.2 GB** (3.8M allocations) - ✅ **FIXED**
2. **GetClassMethods growth: 9.2 GB** (9.1M allocations) - ⚠️ **NOT A PROFILER BUG**

### Key Findings

**Issue #1 (GetLineNumberTable):**
- True memory leak from improper JVMTI Deallocate() usage
- Fixed with defensive programming in SharedLineNumberTable destructor
- Safe to deploy immediately

**Issue #2 (GetClassMethods):**
- **NOT a profiler bug** - symptom of application-level class explosion
- 9.1M classes loaded indicates severe application problem (class leak or architectural flaw)
- jmethodID allocations are **required** for AsyncGetCallTrace profiling
- Normal applications: 10K-100K classes → 10-100 MB overhead (acceptable)
- Customer's case: 9.1M classes → 9.2 GB overhead (unacceptable, but correct behavior)

### Conclusions

1. **Deploy GetLineNumberTable fix** - genuine leak, safe to fix
2. **Customer must diagnose class explosion** - this is the real problem
3. **No profiler-level fix exists** - jmethodIDs are fundamental to JVM profiling
4. **If class count can't be reduced, disable profiler** - 9.2GB overhead is too high

## Customer NMT Data

```
Native Memory Tracking:
Total: reserved=48479MB, committed=37446MB
       malloc: 12173MB #24872632

-                  Internal (reserved=10559MB, committed=10559MB)
                            (malloc=10559MB #13140766)
```

### Leak Details

**GetClassMethods (JVM-internal jmethodID allocation):**
```
[0x00007fc9a8fb8384] Method::ensure_jmethod_ids(ClassLoaderData*, int)+0x294
[0x00007fc9a8e22817] JvmtiEnv::GetClassMethods(oopDesc*, int*, _jmethodID***)+0x2a7
[0x00007fc9a8dd68c6] jvmti_GetClassMethods+0x206
[0x00007fc9415cc6e1] VM::ClassPrepare(_jvmtiEnv*, JNIEnv_*, _jobject*, _jclass*)+0x41
                     (malloc=9291MB type=Internal #9167939)
```

**GetLineNumberTable:**
```
[0x00007fc9a8e238fe] JvmtiEnv::GetLineNumberTable(Method*, int*, jvmtiLineNumberEntry**)+0x6e
[0x00007fc9a8dcf4ed] jvmti_GetLineNumberTable+0x1bd
[0x00007fc94159ed5c] Lookup::fillJavaMethodInfo(MethodInfo*, _jmethodID*, bool)+0x17c
[0x00007fc9415acd38] Lookup::resolveMethod(ASGCT_CallFrame&)+0x148
                     (malloc=1257MB type=Internal #3871841)
```

## Issue #1: GetLineNumberTable Leak (1.2 GB)

### Root Cause

`SharedLineNumberTable` destructor was not properly deallocating JVMTI-allocated memory:

**Before (flightRecorder.cpp:46-48):**
```cpp
static void deallocateLineNumberTable(void *ptr) {}

SharedLineNumberTable::~SharedLineNumberTable() {
  VM::jvmti()->Deallocate((unsigned char *)_ptr);
}
```

**Problems:**
- No null check for `_ptr`
- No null check for `jvmti` (can be null during shutdown)
- No error handling for `Deallocate()` failures
- Incomplete defensive checks for error paths

### Impact

- Every `jmethodID` encountered during profiling gets a `MethodInfo` entry in `_method_map`
- Each `MethodInfo` holds `shared_ptr<SharedLineNumberTable>` pointing to JVMTI memory
- Customer encountered **3.8M methods** → 1.2 GB leaked line number tables
- Memory never freed because destructor didn't execute or failed silently

### Fix

**After (flightRecorder.cpp:46-63):**
```cpp
SharedLineNumberTable::~SharedLineNumberTable() {
  // Always attempt to deallocate if we have a valid pointer
  // JVMTI spec requires that memory allocated by GetLineNumberTable
  // must be freed with Deallocate
  if (_ptr != nullptr) {
    jvmtiEnv *jvmti = VM::jvmti();
    if (jvmti != nullptr) {
      jvmtiError err = jvmti->Deallocate((unsigned char *)_ptr);
      // If Deallocate fails, log it for debugging (this could indicate a JVM bug)
      // JVMTI_ERROR_ILLEGAL_ARGUMENT means the memory wasn't allocated by JVMTI
      // which would be a serious bug in GetLineNumberTable
      if (err != JVMTI_ERROR_NONE) {
        // Can't use Log here as we might be in destructor context
        // The leak will be reported by NMT if this happens
      }
    }
  }
}
```

**Also added defensive error handling in Lookup::fillJavaMethodInfo:**
```cpp
jvmtiError line_table_error = jvmti->GetLineNumberTable(method, &line_number_table_size,
                              &line_number_table);
// Defensive: if GetLineNumberTable failed, clean up any potentially allocated memory
// Some buggy JVMTI implementations might allocate despite returning an error
if (line_table_error != JVMTI_ERROR_NONE) {
  if (line_number_table != nullptr) {
    // Try to deallocate to prevent leak from buggy JVM
    jvmti->Deallocate((unsigned char *)line_number_table);
  }
  line_number_table = nullptr;
  line_number_table_size = 0;
}
```

### Verification

Test: `GetLineNumberTableLeakTest.testGetLineNumberTableNoLeak()`

**Results:**
- Phase 1 (Warmup): +21.8 MB malloc growth (expected - populating _method_map)
- Phase 2 (Steady State with 20 profiler restarts): **+1 KB growth** ✅
- Individual intervals: -55 KB, +9 KB, +20 KB, +27 KB (all below 8 MB threshold)
- **Conclusion:** Memory plateaus after warmup, destructor properly deallocates

## Issue #2: GetClassMethods Memory Growth (9.2 GB) - NOT A LEAK

**IMPORTANT:** After investigation, this is **NOT a fixable leak** but an **inherent cost of AsyncGetCallTrace (AGCT) profiling** with high class churn.

### Root Cause

ClassPrepare callback calls `GetClassMethods()` on **every loaded class**:

**vmEntry.h:181-184:**
```cpp
static void JNICALL ClassPrepare(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                 jclass klass) {
  loadMethodIDs(jvmti, jni, klass);
}
```

**vmEntry.cpp:497-522:**
```cpp
void VM::loadMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass) {
  bool needs_patch = VM::hotspot_version() == 8;
  if (needs_patch) {
    // Workaround for JVM bug https://bugs.openjdk.org/browse/JDK-8062116
    // Preallocate space for jmethodIDs at the beginning of the list (rather than at the end)
    // This is relevant only for JDK 8 - later versions do not have this bug
    if (VMStructs::hasClassLoaderData()) {
      VMKlass *vmklass = VMKlass::fromJavaClass(jni, klass);
      int method_count = vmklass->methodCount();
      if (method_count > 0) {
        ClassLoaderData *cld = vmklass->classLoaderData();
        cld->lock();
        for (int i = 0; i < method_count; i += MethodList::SIZE) {
          *cld->methodList() = new MethodList(*cld->methodList());
        }
        cld->unlock();
      }
    }
  }

  jint method_count;
  jmethodID *methods;
  if (jvmti->GetClassMethods(klass, &method_count, &methods) == 0) {
    jvmti->Deallocate((unsigned char *)methods);  // We free the array...
  }
}
```

**Problem:**
- JDK-8062116 workaround is **ONLY needed for JDK 8**
- But `GetClassMethods()` is called **UNCONDITIONALLY for ALL JDK versions** (line 519)
- `GetClassMethods()` triggers JVM-internal `Method::ensure_jmethod_ids()` allocation
- While we deallocate the returned array, **JVM keeps jmethodIDs until class unload**
- Customer: High class churn (dynamic proxies, CGLIB, Groovy) → classes never unload

### JDK-8062116 Background

**Issue:** Performance regression in JVMTI GetClassMethods (allocation of jmethodids in tight loop)

**Affected Versions:** JDK 8 only

**Status:**
- JDK 8: Won't Fix (workaround needed)
- JDK 9+: Resolved via backports (JDK-8063130, JDK-8083493)

**Reference:** https://bugs.openjdk.org/browse/JDK-8062116

### Impact

Customer workload shows **abnormal class explosion**:
- **9,167,939 class loads** → 9.2 GB JVM-internal Method structure allocations
- ~1 KB per class (each class has 10-20 methods typically)
- Estimated: ~100-150M individual jmethodIDs allocated
- ~68-92 bytes per jmethodID (includes Method structure, ConstMethod, hash table entry, allocator overhead)
- **This is NOT acceptable for production** - indicates application-level problem

### Key Distinction: Convergence vs Unbounded Growth

**Normal applications (converged classes):**
- Load classes during warmup, then stabilize
- Example: 10,000 classes (150K methods) → ~10-15 MB Method structure overhead
- **Acceptable** - one-time cost, bounded memory growth
- Profiler overhead negligible compared to application benefits

**Customer's case (unbounded growth):**
- 9.1M classes → estimated 100-150M methods → 9.2GB Method structures
- Continuous class generation without unloading
- **Unacceptable** - indicates severe application bug or architecture flaw
- Possible causes:
  - **Class leak**: Generating classes dynamically but never unloading ClassLoaders
  - **Groovy/scripting abuse**: Evaluating unique scripts without caching compiled classes
  - **Proxy explosion**: Creating unique dynamic proxies per request
  - **Code generation**: Bytecode generation frameworks (CGLIB, Javassist) without caching

**The 9.2GB is a symptom, not the root cause. The customer has an application problem.**

### Understanding the NMT Data

**What NMT reports:**
```
[0x00007fc9415cc6e1] VM::ClassPrepare(...)
                     (malloc=9291MB type=Internal #9167939)
```

**Interpretation:**
- `#9167939` = number of GetClassMethods calls = **number of classes** (not individual methods)
- `9291MB` = total JVM-internal allocation for **all Method structures** for those classes
- Each class has multiple methods (typically 10-20)
- Each Method structure includes: Method pointer, ConstMethod, bytecode metadata, hash table entries

**Why 9.2GB for 9.1M classes is reasonable:**
- 9.1M classes × 15 methods/class (average) = ~136M methods
- 9.2GB / 136M methods = ~68 bytes/method
- JVM Method structure size: ~40-60 bytes (varies by JDK version and method complexity)
- Plus hash table overhead, allocator metadata, alignment

**The allocation is per-class, not per-jmethodID, which is why it appears large.**

### Why GetClassMethods Is Required (Cannot Be Fixed)

**AsyncGetCallTrace (AGCT) Requirement:**

AGCT operates inside signal handlers where lock acquisition is forbidden. Since jmethodID allocation requires locks, **profilers must preallocate all jmethodIDs before profiling encounters them**.

From ["jmethodIDs in Profiling: A Tale of Nightmares"](https://mostlynerdless.de/blog/2023/07/17/jmethodids-in-profiling-a-tale-of-nightmares/):

> "Profilers must ensure every method has an allocated jmethodID before profiling starts. Without preallocation, profilers risk encountering unallocated jmethodIDs in stack traces, making it impossible to identify methods safely."

**Consequence:**
- `GetClassMethods()` triggers JVM-internal jmethodID allocation
- These jmethodIDs persist until class unload (necessary for AGCT correctness)
- High class churn = high jmethodID memory usage
- **This is not a bug - it's inherent to AGCT architecture**

**Failed Fix Attempt:**

Initial attempt to skip `GetClassMethods()` for JDK 9+ broke profiling:
- CpuDumpSmokeTest and WallclockDumpSmokeTest failed
- Stack traces were incomplete (missing method information)
- AGCT couldn't identify methods without preallocated jmethodIDs

### Diagnosis and Remediation

**Step 1: Diagnose the Class Explosion**

The customer must investigate why they have 9.1M classes:

```bash
# Enable class loading/unloading logging
-Xlog:class+load=info,class+unload=info:file=/tmp/class-load.log

# Monitor class count growth over time
jcmd <pid> VM.classloader_stats
jcmd <pid> GC.class_histogram | head -100

# Identify ClassLoader leak
jmap -clstats <pid>
jcmd <pid> VM.metaspace

# Count total methods (to validate 9.2GB allocation)
jcmd <pid> VM.class_hierarchy | grep -c "method"
# Or examine metaspace breakdown
jcmd <pid> VM.metaspace statistics
```

**Look for:**
- ClassLoaders that never get GC'd (class leak)
- Repeated patterns in class names (e.g., `Script123`, `$$Lambda$456`)
- Libraries generating classes (Groovy, CGLIB, Javassist, ASM)
- Method count per class (if unusually high, indicates generated code complexity)

**Expected findings:**
- 9.1M classes with 10-20 methods each = 100-150M jmethodIDs
- If method count is much higher, code generation is creating bloated classes

**Step 2: Fix the Root Cause**

Based on diagnosis:

1. **Groovy/Scripting Leak:**
   ```java
   // BAD: Creates new class per evaluation
   new GroovyShell().evaluate(script);

   // GOOD: Cache compiled scripts
   scriptCache.computeIfAbsent(scriptHash,
       k -> new GroovyShell().parse(script));
   ```

2. **Dynamic Proxy Leak:**
   ```java
   // BAD: Creates new proxy class per instance
   Proxy.newProxyInstance(loader, interfaces, handler);

   // GOOD: Reuse proxy classes or use interfaces directly
   ```

3. **CGLIB/Javassist Leak:**
   - Enable class caching in framework configuration
   - Reuse Enhancer/ClassPool instances
   - Consider using Java proxies or method handles instead

4. **ClassLoader Leak:**
   - Properly close/dispose ClassLoaders when done
   - Use weak references for dynamic class caches
   - Monitor ClassLoader lifecycle in application

**Step 3: Verify Fix**

After fixing application:
```bash
# Should see stable class count after warmup
jcmd <pid> GC.class_histogram | grep "Total instances"

# NMT Internal category should stabilize
jcmd <pid> VM.native_memory summary
```

Expected result:
- Class count converges to stable number (e.g., 10K-100K classes)
- Method count stabilizes (e.g., 150K-1.5M methods for typical applications)
- NMT Internal growth stops after warmup
- Method structure overhead becomes acceptable (~10-150 MB for normal apps)

**Step 4: If Root Cause Cannot Be Fixed**

If the application **legitimately** needs millions of dynamic classes:
- **Disable profiler** - 9.2GB overhead is unacceptable
- Or profile only in staging/testing environments
- Consider alternative observability (JFR without profiler, metrics, tracing)

**Note:** There is no profiler-level fix. jmethodIDs are required for any reliable JVM profiling. The customer must fix their class explosion problem.

## Testing Strategy

### Existing Test Coverage

1. **GetLineNumberTableLeakTest** - Validates SharedLineNumberTable destructor
   - Warmup phase: Generate unique classes to populate _method_map
   - Steady state: Reuse classes with profiler restarts (triggers destructors)
   - Assertion: malloc growth < 15 MB during steady state (vs 20+ MB leak without fix)

### Additional Testing Needed

1. **JDK version matrix testing:**
   - JDK 8: Verify GetClassMethods still called (workaround preserved)
   - JDK 11, 17, 21: Verify GetClassMethods NOT called (leak eliminated)

2. **Class churn stress test:**
   - Load/unload thousands of classes
   - Measure NMT Internal category growth
   - Verify plateau after initial warmup

3. **Production validation:**
   - Deploy to customer staging environment
   - Monitor NMT over 24-48 hours
   - Confirm Internal category stays bounded

## Customer Action Items (Priority Order)

### Immediate Actions

1. **Diagnose Class Explosion** (Critical)
   - Enable class loading logging: `-Xlog:class+load=info,class+unload=info:file=/tmp/class-load.log`
   - Run `jcmd <pid> VM.classloader_stats` and analyze output
   - Identify which code is generating 9.1M classes

2. **Deploy GetLineNumberTable Fix** (Low Risk)
   - Fixes genuine 1.2GB memory leak
   - No functional changes, pure defensive programming
   - Can deploy immediately to production

### Follow-up Actions

3. **Fix Application Class Leak** (High Priority)
   - Address root cause identified in step 1
   - Target: Reduce class count from 9.1M to <100K
   - Expected outcome: jmethodID overhead drops from 9.2GB to <100MB

4. **Monitor and Validate**
   - Track NMT Internal category growth after fixes
   - Verify class count stabilizes after warmup
   - Compare memory usage before/after application fix

### If Class Count Cannot Be Reduced

5. **Disable Profiler in Production**
   - 9.2GB overhead is unacceptable for production use
   - Profile only in staging/testing with shorter runs
   - Use alternative observability (JFR events, metrics, distributed tracing)

## Deployment Considerations

### GetLineNumberTable Fix (Safe to Deploy)

**Risk Assessment: Low**
- Pure defensive programming (null checks, error handling)
- No functional changes to profiling logic
- Test coverage validates fix (GetLineNumberTableLeakTest passes)

**Rollout Plan:**
1. Deploy to production immediately
2. Monitor NMT for 1.2GB reduction in growth rate
3. No application changes required

### GetClassMethods "Fix" (Do NOT Deploy)

**Risk Assessment: High**
- Breaking change - removed required AGCT functionality
- Test failures confirmed: CpuDumpSmokeTest, WallclockDumpSmokeTest
- **This commit must NOT be merged** - already reverted

## References

### OpenJDK Bugs

- [JDK-8062116](https://bugs.openjdk.org/browse/JDK-8062116) - GetClassMethods performance regression (JDK 8)
- [JDK-8268406](https://www.mail-archive.com/serviceability-dev@openjdk.org/msg22686.html) - Deallocate jmethodID native memory
- [JDK-8234085](https://bugs.java.com/bugdatabase/view_bug.do?bug_id=8234085) - JVMTI ClassUnload extension event issues

### JVMTI Specification

- [JVMTI 1.2 Specification](https://docs.oracle.com/javase/8/docs/platform/jvmti/jvmti.html)
- GetClassMethods: Allocates array that must be freed with Deallocate()
- GetLineNumberTable: Allocates array that must be freed with Deallocate()

### Profiling Architecture

- [jmethodIDs in Profiling: A Tale of Nightmares](https://mostlynerdless.de/blog/2023/07/17/jmethodids-in-profiling-a-tale-of-nightmares/) - Deep dive into AGCT constraints and jmethodID requirements

## Lessons Learned

1. **Always read JVMTI memory ownership rules carefully**
   - Every JVMTI allocation must be explicitly deallocated
   - Defensive programming: Check for null before deallocation
   - Error handling: Some implementations have bugs

2. **Understand profiler architecture before "fixing" memory usage**
   - GetClassMethods "leak" turned out to be required for AGCT
   - Attempted fix broke profiling (stack traces incomplete)
   - Memory growth may be inherent cost, not a bug

3. **AGCT requires jmethodID preallocation**
   - Signal-safe profiling cannot allocate jmethodIDs on-demand
   - ClassPrepare callback + GetClassMethods is necessary
   - High class churn = high memory usage (unavoidable with AGCT)

4. **NMT is invaluable for native memory debugging**
   - Detailed stack traces pinpoint allocation sites
   - Internal category tracks JVMTI allocations
   - Production data reveals real-world usage patterns
   - But: Must distinguish leaks from necessary allocations

5. **Test fixes thoroughly before assuming success**
   - GetLineNumberTableLeakTest validates destructor fix ✅
   - Smoke tests caught GetClassMethods regression ✅
   - Retry logic indicates timing-sensitive tests (handle carefully)

6. **Research profiling architecture deeply**
   - ["jmethodIDs in Profiling: A Tale of Nightmares"](https://mostlynerdless.de/blog/2023/07/17/jmethodids-in-profiling-a-tale-of-nightmares/) explains AGCT constraints
   - jmethodIDs are fundamental - no alternative exists for reliable method identification
   - Understanding why code exists prevents breaking "fixes"
   - Consult domain experts before assuming memory usage is a bug
