/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSUPPORT_H
#define _HOTSPOT_HOTSPOTSUPPORT_H

#include "guards.h"
#include "hotspot/hotspotStackFrame.h"
#include "hotspot/jitCodeCache.h"
#include "hotspot/klassRegistry.h"
#include "frame.h"
#include "stackFrame.h"
#include "stackWalker.h"
#include "threadLocalData.inline.h"

#include <jni.h>
#include <jvmti.h>

class VMMethod;
class VMSymbol;

// What HotspotSupport::resolve() extracts from a raw Method*: the holder's
// internal class name, the method name and signature, and the decoded line
// number table. Everything is copied out of the VM metadata, so the result
// stays valid after the class has been unloaded.
//
// Each name has a fixed-size inline buffer for the common case, with a
// malloc'd fallback (up to MAX_SYMBOL_LEN) for names that don't fit. The line
// number table is always malloc'd. resolve() can siglongjmp out of a fault
// after any of these allocations, bypassing ~ResolvedMethod(), which is why
// its fault-recovery path calls release() explicitly.
class ResolvedMethod {
  // Hard ceiling for the malloc fallback in setName(). Not a JVM/class-file
  // limit (Symbol::length() is a u2, so up to 65535 is legal).
  static constexpr size_t MAX_SYMBOL_LEN = 64 * 1024;

  // Fast-path buffer sizes, deliberately small enough that the malloc
  // fallback in setName() still gets exercised occasionally. A name that does
  // not fit even the fallback serializes as "unknown";
  // METHOD_RESOLVE_SYMBOL_UNREADABLE makes that visible.
  static constexpr size_t MAX_KLASS_NAME_LEN  = 1024;  // internal names; realistically < 256
  static constexpr size_t MAX_METHOD_NAME_LEN =  512;  // realistically < 64
  static constexpr size_t MAX_SIGNATURE_LEN   = 1024;

  // volatile: resolve() mutates these between sigsetjmp() and a possible
  // siglongjmp() out of a fault, and release() reads them back at the landing
  // pad. Per C11 7.13.2.1p3 a non-volatile automatic modified in that window
  // has an indeterminate value after longjmp.
  char* volatile _long_method_name;
  char* volatile _long_method_signature;
  char* volatile _long_klass_name;
  jvmtiLineNumberEntry* volatile _line_number_table;
  volatile int _line_number_table_size;
  volatile bool _is_thread_run;

  char _method_name[MAX_METHOD_NAME_LEN];
  char _method_signature[MAX_SIGNATURE_LEN];
  char _klass_name[MAX_KLASS_NAME_LEN];

  bool setName(char* short_name, char* volatile& long_name, size_t short_limit, VMSymbol* sym);

  friend class HotspotSupport;

public:
  // Upper bound on decoded line number table entries; mirrors the u2
  // code_length limit of JVMS 4.7.3.
  static constexpr int MAX_LINE_NUMBER_TABLE_ENTRIES = 65535;

  ResolvedMethod(const ResolvedMethod&) = delete;
  ResolvedMethod& operator=(const ResolvedMethod&) = delete;

  ResolvedMethod();
  ~ResolvedMethod() { release(); }

  // Frees everything still owned. Idempotent.
  void release();

  bool setMethodName(VMSymbol* sym);
  bool setMethodSignature(VMSymbol* sym);
  bool setKlassName(VMSymbol* sym);

  // Internal (slash-separated) class name, e.g. "java/lang/Thread".
  const char* klassName() const {
    return _long_klass_name != nullptr ? _long_klass_name : _klass_name;
  }

  const char* methodName() const {
    return _long_method_name != nullptr ? _long_method_name : _method_name;
  }

  const char* methodSignature() const {
    return _long_method_signature != nullptr ? _long_method_signature : _method_signature;
  }

  // True for run()V declared by java.lang.Thread or one of its subclasses.
  bool isThreadRun() const { return _is_thread_run; }

  // Decoded line number table, sorted by bci as HotSpot stores it, or
  // nullptr if the method has none. Allocated with malloc().
  const jvmtiLineNumberEntry* lineNumberTable() const { return _line_number_table; }
  int lineNumberTableSize() const { return _line_number_table_size; }

  // Hands ownership of the line number table to the caller, who must free()
  // it. Returns nullptr if there is none.
  jvmtiLineNumberEntry* takeLineNumberTable(int* size) {
    jvmtiLineNumberEntry* table = _line_number_table;
    *size = _line_number_table_size;
    _line_number_table = nullptr;
    _line_number_table_size = 0;
    return table;
  }
};

class HotspotSupport {
    friend class JVMSupport;
    friend class HotspotSupportTestAccessor;

private:
    // pc_is_return_address describes the seed pc: a ucontext pc is the exact
    // interrupted address, while callerPC() is a real return address on every
    // architecture except the one where CALLER_PC_IS_RETURN_ADDRESS is false.
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      const void* pc, bool pc_is_return_address,
                      uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      int lock_index, bool* truncated = nullptr);

    // ctx_snapshot is owned by the caller's withUcontextFaultRecovery() scope
    // (hotspotSupport.cpp), not constructed locally: getJavaTraceAsync() must
    // record the JavaThread anchor mutation it's about to make (see
    // saveJavaAnchor() below) on the exact same RegisterSnapshot instance
    // whose restore() runs on a recovered SIGSEGV, or the anchor never gets
    // restored -- a fault siglongjmps past this whole function's frame,
    // skipping any local snapshot it might otherwise have owned.
    static int getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                 int max_depth, StackContext *java_ctx,
                                 bool *truncated, HotspotStackFrame::RegisterSnapshot& ctx_snapshot);

    static bool loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all);

    // fjmethodid=lazy: liveness registry for every loaded class, consulted by
    // resolve() before it touches a raw Method*. See klassRegistry.h.
    static KlassRegistry _klass_registry;

    // Raw frame tags (frame.h). fjmethodid=lazy frames set the top tag bit
    // and keep the low 25 bits of the holder's JFR trace ID (KlassTraceId) in
    // the rest, unique per load of a class. Partial-mode (fjmethodid=false)
    // frames carry no tag: their method field is the plain Method*, whose top
    // bit is never set for a user-space address. resolve() goes by each
    // frame's own kind, never by the current mode.
    static const uint32_t TRACE_ID_TAG = 1u << (FrameType::RAW_TAG_BITS - 1);
    static const uint32_t TAG_VALUE_MASK = TRACE_ID_TAG - 1;

    // The tag to store with a lazy-mode raw frame of `method`; false if the
    // holder's trace ID is unreadable. Signal safe.
    static bool lazyFrameTag(const VMMethod* method, uint32_t* tag, const void** holder = nullptr);

    // fjmethodid=lazy: records `klass` in _klass_registry instead of
    // allocating its jmethodIDs. Called wherever the other modes preload.
    static bool registerClass(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);

    // Around every RedefineClasses/RetransformClasses call, in every mode
    // once _klass_registry has entries (raw frames of a lazy session can
    // outlive it): marks `klass` while the call runs and for good if it
    // succeeds (see klassRegistry.h for why its raw frames are refused), and in
    // lazy mode preloads its jmethodIDs after a successful call. `klass` comes
    // straight from the caller, so anything that is not an instance class is
    // ignored, as JVMTI itself rejects it.
    static void beforeClassRedefinition(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);
    static void afterClassRedefinition(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool succeeded);

    // True if JVMTI accepts `klass` as a class that is neither an array nor a
    // primitive, i.e. one with a Klass* that has methods.
    static bool isInstanceClass(jvmtiEnv *jvmti, jclass klass);

    // fjmethodid=lazy half of resolve(): pins the class registered under
    // `holder`, refuses it if its trace ID does not match `trace_id_bits` (the
    // frame came from another load of a class whose memory this one reuses),
    // checks that `vm_method` is still one of its methods, and only then reads
    // its names and line number table into `result`, with the class still
    // pinned. `holder` and `idnum` were read from the unverified Method* and
    // are only used as lookup keys.
    static bool resolveViaRegistry(ProfiledThread* prof_thread, VMMethod* vm_method,
                                   const void* holder, int idnum, uint32_t trace_id_bits,
                                   ResolvedMethod& result, bool count = true);

    // The raw metadata walk behind resolve(): names, signature, Thread.run
    // detection and line number table of `method`. Must run with crash
    // protection installed; uses no JNI or JVMTI.
    static bool readMethod(const void* method, ResolvedMethod* result);

    // Runs getJavaTraceAsync() under withUcontextFaultRecovery(), then layers
    // on its two post-processing steps: resolving frame types for the top
    // Java frame via fillFrameTypes(), and appending a synthetic "JVM
    // Continuation" frame when the sampled thread is carrying a virtual
    // thread. Called from walkJavaStack()'s single dispatch branch that
    // reaches getJavaTraceAsync() (the hook-prefixed/BCI_CPU/BCI_WALL arm
    // with cstack < CSTACK_VM) -- previously duplicated verbatim in each
    // of the two dispatch arms.
    static int asyncJavaTraceWithPostProcessing(void* ucontext, ASGCT_CallFrame* frames,
                                                int max_depth, StackContext* java_ctx,
                                                bool* truncated, ProfiledThread* prof_thread);
public:
    static void initClassloaderInfo(JNIEnv* jni);

    // Runs `work` under the ucontext-fault-recovery protocol walkJavaStack()
    // needs around getJavaTraceAsync(): installs a sigsetjmp/siglongjmp
    // crash-protection scope chained on prof_thread (JmpCtxScope, guards.h),
    // and if a SIGSEGV strikes and is recovered by Profiler::checkFault(),
    // restores ucontext's pc/sp/fp to what they were before `work` ran.
    // getJavaTraceAsync() mutates those registers in place (its pc()/sp()/
    // fp() are references into uc_mcontext) and normally restores them
    // itself, but a fault mid-mutation (e.g. the PROBE_SP retry loop, or
    // inside unwindStub()/unwindCompiled()) skips that restore -- and this
    // ucontext is the exact one the kernel uses to resume the sampled
    // thread when the signal handler returns.
    //
    // `partial_result` is the caller's own accumulator for whatever `work`
    // has already committed to the output buffer (e.g. walkJavaStack's
    // java_frames): getJavaTraceAsync() can fault *after* already returning a
    // valid frame count and filling `frames` (e.g. inside
    // fillFrameTypes()/isCarryingVirtualThread()'s follow-up work). `work` is
    // void-returning and writes only into `partial_result` (by capturing it,
    // not by a return value) -- the wrapper reads `partial_result` back on
    // both the normal-completion path and the recovery path, so there is a
    // single channel for the result rather than two that a caller could wire
    // to different objects, or forget to wire at all (a plain return value
    // whose default became 0 on a recovered fault was exactly the
    // "recovered fault discards an already-valid partial trace" shape this
    // wrapper exists to avoid). The caller must initialize `partial_result`
    // itself before the call (normally to 0); before this recovery logic was
    // extracted into a shared helper, walkJavaStack() already reported the
    // fault-after-partial-progress case as a truncated-but-valid count by
    // reading back its own `volatile int java_frames` local from the recovery
    // branch -- this parameter is how that pre-existing behavior is preserved
    // now that the branch lives here instead, not a new fix on top of it.
    //
    // `work` receives ctx_snapshot by reference so that getJavaTraceAsync()
    // (via its own saveJavaAnchor() call, above) can record a JavaThread
    // anchor mutation on this exact instance -- the one whose restore()
    // actually runs below on a recovered fault. A local snapshot inside
    // getJavaTraceAsync() would be useless: a siglongjmp from a fault there
    // jumps straight back to this sigsetjmp, skipping getJavaTraceAsync's
    // entire stack frame (and anything it owned) without running any of its
    // code.
    //
    // Extracted into one place, rather than hand-rolled separately in
    // walkJavaStack(), so production and its regression test invoke the
    // identical recovery branch -- see hotspot_crash_protection_ut.cpp's
    // WalkJavaStackUcontextRestoreTest. A template rather than
    // std::function<void()> so the hot sample path pays no allocation for
    // captures. Must stay defined here (not in hotspotSupport.cpp): as a
    // template, its body needs to be visible wherever it's instantiated --
    // both walkJavaStack() and the regression test's own call sites, which
    // each pass a distinct closure type.
    template <typename Fn>
    static int withUcontextFaultRecovery(void* ucontext, ProfiledThread* prof_thread, bool* truncated, volatile int& partial_result, Fn&& work) {
        const bool prev_unwinding_java = prof_thread->is_unwinding_Java();
        HotspotStackFrame::RegisterSnapshot ctx_snapshot(ucontext);

        sigjmp_buf crash_protection_ctx;
        JmpCtxScope jmp_scope(prof_thread);

        if (sigsetjmp(crash_protection_ctx, 1) != 0) {
            // checkFault() does a siglongjmp from inside segvHandler, bypassing
            // segvHandler's SignalHandlerScope destructor. Compensate.
            SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
            jmp_scope.restore();
            // Backstop for template callers whose work() acquires the
            // AsyncSampleMutex itself (a recovered siglongjmp bypasses its
            // destructor). The production caller constructs the mutex above
            // this scope (see asyncJavaTraceWithPostProcessing), where this
            // restore is a no-op and the mutex destructor clears the flag
            // on return.
            prof_thread->set_unwinding_Java(prev_unwinding_java);
            ctx_snapshot.restore();
            if (truncated) {
                *truncated = true;
            }
            return partial_result;
        }
        jmp_scope.install(&crash_protection_ctx);
        work(ctx_snapshot);
        return partial_result;
    }

    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const StackFrame& frame, const void*& pc) {
        return HotspotStackFrame::unwindAtomicStub(frame, pc);
    }

    static inline bool isJitCode(const void* p) {
        return JitCodeCache::isJitCode(p);
    }

    static inline long long runtimeStubsMemoryUsage() {
        return JitCodeCache::runtimeStubsMemoryUsage();
    }

    // If should load all jmethodIDs. Raw Method* frames only come from walkVM,
    // so anything but the resolved stack walker mode `cstack` == CSTACK_VM --
    // including CSTACK_DEFAULT, which resolves to DWARF where the VM walker is
    // unavailable -- needs every jmethodID preloaded.
    static inline bool shouldPreloadJmethodIDs(const Arguments& args, CStack cstack) {
        return args._force_jmethodID || cstack != CSTACK_VM;
    }

    // The Method* a raw frame stands for: untagged for a lazy-mode frame,
    // as stored for a partial-mode one.
    static inline const void* rawFrameMethod(int bci, const void* method) {
        return (FrameType::rawTag(bci, method) & TRACE_ID_TAG) != 0 ? FrameType::untagPointer(method) : method;
    }

    // fjmethodid=lazy needs the Klass*/methods-array structs on top of the
    // ones the raw Method* walk already uses; without them, the caller falls
    // back to the partial preload mode.
    static bool canResolveLazily();

    // fjmethodid=lazy setup that needs JNI: locates Klass::_trace_id
    // (KlassTraceId::calibrate). Returns false if it cannot be found; lazy
    // mode then does not run, since nothing else can tell a stale raw frame
    // from one of a class that took over its memory.
    static bool initLazyResolution(JNIEnv* jni);

    // Resolves a raw-pointer frame at dump time into its class name, method
    // name, signature and line number table, read from VM metadata. Takes the
    // frame's method field and encoded bci as stored, tag bits included.
    // Returns false, leaving `result` empty, if the frame must be treated as
    // unknown: the JMETHODID_NOT_WALKABLE sentinel, metadata that is stale or
    // unreadable, or a lazy-mode frame the class registry refuses.
    static bool resolve(const void* tagged_method, int bci, ResolvedMethod& result);

    // PROTOTYPE (UnloadCapture): reads `method`'s names under crash protection
    // if its holder's trace ID still matches `tag` and it is one of the
    // holder's current methods. No JNI, no JVMTI, no locks: callable from a
    // GarbageCollectionStart callback.
    static bool captureMethod(ProfiledThread* prof_thread, const void* method, uint32_t tag,
                              ResolvedMethod& result);

    // PROTOTYPE (UnloadCapture background drain): resolve() for a lazy
    // (Method*, tag) pair, pinning the class through the registry, without
    // touching the method_resolve_lazy_* counters. Needs an attached thread.
    static bool capturePinned(ProfiledThread* prof_thread, const void* method, uint32_t tag,
                              ResolvedMethod& result);

    // Store a Java frame captured from HotSpot metadata. A null jmethodID
    // triggers the raw Method* fallback only when fjmethodid=false; with
    // fjmethodid=true the sentinel is used instead to avoid deferring a
    // raw Method* dereference to the dump thread. The rejected-ID sentinel
    // is always stored as an ordinary frame, resolved to the shared unknown
    // method at dump time.
    static void fillJavaFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci,
                              jmethodID method_id, const VMMethod* method);
};

#endif // _HOTSPOT_HOTSPOTSUPPORT_H
