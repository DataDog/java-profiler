/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nmethodMethodCheck.h"

#include "hotspot/vmStructs.inline.h"

#include <jvmti.h>

static constexpr int MAX_READS = 16;

struct ReadContext {
    jmethodID target;
    // Slots are claimed with a fetch_add on count; done counts the claims
    // that wrote a triple (published with release, so the entries are
    // visible to an acquire reader once done catches up with count).
    int count;
    int done;
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

    // While the event is enabled, the ServiceThread can also post to this env
    // for a compile on another thread; the atomic claim with rollback keeps
    // concurrent posters on distinct, bounded slots. A reset racing an
    // in-flight claim can drive count negative: such a slot is never written
    // and must not be rolled back (that would push count lower still).
    int slot = __atomic_fetch_add(&ctx->count, 1, __ATOMIC_RELAXED);
    if (slot < 0) {
        return;
    }
    if (slot >= MAX_READS) {
        __atomic_fetch_sub(&ctx->count, 1, __ATOMIC_RELAXED);
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
    __atomic_fetch_add(&ctx->done, 1, __ATOMIC_RELEASE);
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
    // Atomic stores: a stalled poster from an earlier call can still be
    // running; a plain reset racing its RMW on the same field is UB.
    __atomic_store_n(&readContext.count, 0, __ATOMIC_RELAXED);
    __atomic_store_n(&readContext.done, 0, __ATOMIC_RELAXED);

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
    // callback can still be claiming a slot, and transient claims exceed
    // MAX_READS until their rollback lands. Wait for the claim and write
    // phases to drain before reading count and the entries it bounds.
    int count = __atomic_load_n(&readContext.count, __ATOMIC_ACQUIRE);
    for (int spin = 0; spin < 1000000 &&
                    __atomic_load_n(&readContext.done, __ATOMIC_ACQUIRE) < count; spin++) {
        count = __atomic_load_n(&readContext.count, __ATOMIC_ACQUIRE);
    }
    // Only reachable if a post wedged between its claim and its write;
    // done bounds the completed writes, so an entry past a wedged writer
    // can still be stale from an earlier call and the retry absorbs it.
    int done = __atomic_load_n(&readContext.done, __ATOMIC_ACQUIRE);
    if (done < 0 || done > MAX_READS) {
        done = done < 0 ? 0 : MAX_READS;
    }
    if (count < 0 || count > done) {
        count = count < 0 ? 0 : done;
    }

    jlongArray result = jni->NewLongArray(1 + count * 3);
    if (result == nullptr) {
        return nullptr;  // pending OutOfMemoryError
    }
    jlong targetValue = reinterpret_cast<jlong>(target);
    jni->SetLongArrayRegion(result, 0, 1, &targetValue);
    if (count > 0) {
        jni->SetLongArrayRegion(result, 1, count * 3, readContext.reads);
    }
    return result;
}
