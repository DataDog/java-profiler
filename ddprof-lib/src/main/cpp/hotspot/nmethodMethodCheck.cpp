/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nmethodMethodCheck.h"

#include "hotspot/vmStructs.inline.h"
#include "threadLocalData.h"

#include <jvmti.h>

static constexpr int MAX_READS = 16;

struct ReadContext {
    jmethodID target;
    // Slots are claimed with a fetch_add on count. live counts each poster
    // from just before its claim to just after its last write, so the
    // counters can only be reset for a new batch once no poster can still
    // reach a slot.
    int count;
    int live;
    jlong reads[MAX_READS * 3];
};

// Static storage: JVMTI's disable does not join a post that entered before
// it, so a stalled poster can still write after readsForTest returns; every
// such write lands in this buffer at a bounded slot instead of dead stack.
// Single caller (the test child's main thread); concurrent readsForTest
// calls are not supported.
static ReadContext readContext;

// Disposes the JVMTI environment on every exit path, including the early
// returns after a failed JVMTI call.
class JvmtiEnvOwner {
  public:
    explicit JvmtiEnvOwner(jvmtiEnv* env) : _env(env) {}
    ~JvmtiEnvOwner() {
        if (_env != nullptr) {
            _env->DisposeEnvironment();
        }
    }
    JvmtiEnvOwner(const JvmtiEnvOwner&) = delete;
    JvmtiEnvOwner& operator=(const JvmtiEnvOwner&) = delete;

  private:
    jvmtiEnv* _env;
};

static void throwIllegalState(JNIEnv* jni, const char* what) {
    jclass ex = jni->FindClass("java/lang/IllegalStateException");
    if (ex != nullptr) {
        jni->ThrowNew(ex, what);
    }
}

static void JNICALL onCompiledMethodLoad(jvmtiEnv* jvmti, jmethodID method, jint code_size,
                                         const void* code_addr, jint map_length,
                                         const jvmtiAddrLocationMap* map, const void* compile_info) {
    // Never touches the env after entry: a post that survives past the
    // env's disposal must not call back into freed JVMTI state.
    ReadContext* ctx = &readContext;
    // Acquire pairs with readsForTest's release store of target, so a
    // poster that entered the callback sees the current call's target.
    if (method != __atomic_load_n(&ctx->target, __ATOMIC_ACQUIRE)) {
        return;
    }

    // The callback can land on a compiler or ServiceThread that never went
    // through the profiler's thread hooks; the code-heap read below needs
    // the profiler TLS those threads otherwise lack. Events filtered out by
    // the target compare above return without touching VM structures, so
    // they skip the initialization cost. The initialization itself must stay
    // before the live claim: it can allocate on first use for a thread, and
    // a poster holding a live slot while doing it could outlast the reader's
    // bounded drain wait and get its batch discarded.
    ProfiledThread::initCurrentThreadSignalSafe();

    // The count precedes the claim so a reset that observes no live poster
    // can never race one that is about to claim a slot it would reuse; a
    // poster entering during a reset (live < 0) backs off instead.
    if (__atomic_fetch_add(&ctx->live, 1, __ATOMIC_ACQ_REL) < 0) {
        return;
    }

    // While the event is enabled, the ServiceThread can also post to this env
    // for a compile on another thread; the atomic claim with rollback keeps
    // concurrent posters on distinct, bounded slots. The claim must be a
    // RELEASE RMW: readsForTest snapshots count with an acquire load, and a
    // relaxed increment publishes no prior writes, so that snapshot could
    // observe the claim without the preceding live registration (arm64 is
    // weakly ordered) — the reader would then pass its live == 0 drain wait
    // and copy the slot while this poster is still writing it. The count
    // rollback below stays relaxed: it publishes nothing, and its RMW reads
    // the claim's own written value, keeping it in the claim's release
    // sequence. The live decrements stay release: the drain wait pairs its
    // acquire loads of live with them.
    int slot = __atomic_fetch_add(&ctx->count, 1, __ATOMIC_RELEASE);
    if (slot < 0) {
        // A rollback racing the reset's store of count can drive it negative:
        // such a slot was never claimed, so it must be neither written nor
        // rolled back (a rollback would push count lower still).
        __atomic_fetch_sub(&ctx->live, 1, __ATOMIC_RELEASE);
        return;
    }
    if (slot >= MAX_READS) {
        __atomic_fetch_sub(&ctx->count, 1, __ATOMIC_RELAXED);
        __atomic_fetch_sub(&ctx->live, 1, __ATOMIC_RELEASE);
        return;
    }

    VMNMethod* nm = CodeHeap::findNMethod(code_addr);
    jlong status = 1;
    jlong read = 0;
    if (nm != nullptr && nm->isNMethod()) {
        // The raw id(): nullptr and JMETHODID_NOT_WALKABLE are reported as-is,
        // the caller distinguishes them from a real jmethodID.
        VMMethod* m = nm->method();
        status = 0;
        read = m == nullptr ? 0 : reinterpret_cast<jlong>(m->id());
    }
    ctx->reads[slot * 3] = reinterpret_cast<jlong>(code_addr);
    ctx->reads[slot * 3 + 1] = status;
    ctx->reads[slot * 3 + 2] = read;
    // Release publishes the writes above to the reset and to the reader that
    // acquires live.
    __atomic_fetch_sub(&ctx->live, 1, __ATOMIC_RELEASE);
}

// For CI only: NMethodMethodJvmtiValidationTest compares this with JVMTI's
// CompiledMethodLoad.
jlongArray NMethodMethodCheck::readsForTest(JNIEnv* jni, jobject method) {
    if (!CodeHeap::available()) {
        return nullptr;
    }

    jmethodID target = jni->FromReflectedMethod(method);
    if (target == nullptr) {
        jclass ex = jni->FindClass("java/lang/IllegalArgumentException");
        if (ex != nullptr) {
            jni->ThrowNew(ex, "compiledMethodReadsForTest: not a Method object");
        }
        return nullptr;
    }

    JavaVM* vm = nullptr;
    if (jni->GetJavaVM(&vm) != JNI_OK) {
        throwIllegalState(jni, "compiledMethodReadsForTest: GetJavaVM failed");
        return nullptr;
    }
    jvmtiEnv* jvmti = nullptr;
    if (vm->GetEnv(reinterpret_cast<void**>(&jvmti), JVMTI_VERSION_1_0) != JNI_OK || jvmti == nullptr) {
        throwIllegalState(jni, "compiledMethodReadsForTest: GetEnv failed");
        return nullptr;
    }
    JvmtiEnvOwner owner(jvmti);

    jvmtiCapabilities capabilities = {0};
    capabilities.can_generate_compiled_method_load_events = 1;
    if (jvmti->AddCapabilities(&capabilities) != JVMTI_ERROR_NONE) {
        throwIllegalState(jni, "compiledMethodReadsForTest: AddCapabilities failed");
        return nullptr;
    }

    jvmtiEventCallbacks callbacks = {0};
    callbacks.CompiledMethodLoad = onCompiledMethodLoad;
    if (jvmti->SetEventCallbacks(&callbacks, sizeof(callbacks)) != JVMTI_ERROR_NONE) {
        throwIllegalState(jni, "compiledMethodReadsForTest: SetEventCallbacks failed");
        return nullptr;
    }

    __atomic_store_n(&readContext.target, target, __ATOMIC_RELEASE);
    // Slots are reused only once no poster can still reach them: the CAS
    // claims the reset exclusively, a poster racing in backs off on the
    // negative live, and a call that finds survivors keeps claiming fresh
    // slots past the undrained ones instead of reusing theirs.
    int live = __atomic_load_n(&readContext.live, __ATOMIC_ACQUIRE);
    if (live == 0 && __atomic_compare_exchange_n(&readContext.live, &live, -1, false,
                                                 __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
        __atomic_store_n(&readContext.count, 0, __ATOMIC_RELAXED);
        __atomic_store_n(&readContext.live, 0, __ATOMIC_RELEASE);
    }
    // The batch owns the claims from here to the next reset; slots below the
    // base belong to an earlier batch whose poster may still be writing.
    int base = __atomic_load_n(&readContext.count, __ATOMIC_ACQUIRE);
    // The slot<0 back-off leaves count at -1 until the next claim heals it;
    // clamp so a transient negative count cannot reach the copy below.
    if (base < 0) {
        base = 0;
    } else if (base > MAX_READS) {
        base = MAX_READS;
    }

    // HotSpot queues these events only while some env has them enabled, and
    // posts them per env: enabled here only around GenerateEvents and disabled
    // before returning; async posts in that window race the ctx (atomic slot).
    if (jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_COMPILED_METHOD_LOAD, nullptr) != JVMTI_ERROR_NONE) {
        throwIllegalState(jni, "compiledMethodReadsForTest: SetEventNotificationMode enable failed");
        return nullptr;
    }
    jvmtiError err = jvmti->GenerateEvents(JVMTI_EVENT_COMPILED_METHOD_LOAD);
    // Disable before the result is built and the env disposed, so late
    // ServiceThread posts cannot reach this env after the seam returns.
    if (jvmti->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_COMPILED_METHOD_LOAD, nullptr) != JVMTI_ERROR_NONE) {
        throwIllegalState(jni, "compiledMethodReadsForTest: SetEventNotificationMode disable failed");
        return nullptr;
    }
    if (err != JVMTI_ERROR_NONE) {
        throwIllegalState(jni, "compiledMethodReadsForTest: GenerateEvents failed");
        return nullptr;
    }

    // JVMTI's disable does not join a post that entered before it: the
    // callback can still be claiming a slot. Snapshot the batch's claim bound
    // first, so a poster claiming afterwards lands outside the copied range,
    // then wait for every live poster to finish before reading the slots.
    int claimed = __atomic_load_n(&readContext.count, __ATOMIC_ACQUIRE) - base;
    int spin = 0;
    while (spin < 1000000 && __atomic_load_n(&readContext.live, __ATOMIC_ACQUIRE) != 0) {
        spin++;
    }
    // A completion bound does not identify a completed prefix: a timeout
    // leaves a claimed slot unfinished, so discard the batch and let the
    // caller retry instead of copying a slot that can still be written.
    if (__atomic_load_n(&readContext.live, __ATOMIC_ACQUIRE) != 0) {
        claimed = 0;
    } else if (claimed < 0) {
        claimed = 0;
    } else if (claimed > MAX_READS - base) {
        // Claims past the capacity rolled back and never wrote a slot.
        claimed = MAX_READS - base;
    }

    jlongArray result = jni->NewLongArray(1 + claimed * 3);
    if (result == nullptr) {
        // A null here means NewLongArray failed (pending OutOfMemoryError), not
        // "seam unavailable": the Java caller's null handling treats null as a
        // permanent unsupported case, so the transient OOM must surface as an
        // exception instead, or the validation test would silently skip.
        jni->ExceptionClear();
        throwIllegalState(jni, "compiledMethodReadsForTest: NewLongArray failed");
        return nullptr;
    }
    jlong targetValue = reinterpret_cast<jlong>(target);
    jni->SetLongArrayRegion(result, 0, 1, &targetValue);
    if (claimed > 0) {
        jni->SetLongArrayRegion(result, 1, claimed * 3, readContext.reads + base * 3);
    }
    return result;
}
