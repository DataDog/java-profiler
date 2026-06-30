/*
 * Copyright 2025, 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "profilerVmStructsExt.h"
#include "codeCache.h"
#include "hotspot/vmStructs.h"
#include "jniHelper.h"
#include "safeAccess.h"
#include "spinLock.h"
#include "vmEntry.h"
#include <stdlib.h>
#include <string.h>

// Static field definitions for ProfilerVMStructsExt
ProfilerVMStructsExt::HeapUsageFunc ProfilerVMStructsExt::_heap_usage_func = NULL;
ProfilerVMStructsExt::MemoryUsageFunc ProfilerVMStructsExt::_memory_usage_func = NULL;
ProfilerVMStructsExt::GCHeapSummaryFunc ProfilerVMStructsExt::_gc_heap_summary_func = NULL;
// Static field definitions for HeapUsage
bool HeapUsage::is_jmx_attempted = false;
bool HeapUsage::is_jmx_supported = false;

void ProfilerVMStructsExt::init() {
    CodeCache* libjvm = VMStructs::libjvm();
    if (libjvm == NULL) {
        return;
    }
    _heap_usage_func = (HeapUsageFunc)findHeapUsageFunc();
    _gc_heap_summary_func = (GCHeapSummaryFunc)libjvm->findSymbol(
        "_ZN13CollectedHeap19create_heap_summaryEv");
}

void ProfilerVMStructsExt::patchSafeFetch() {
    // Workarounds for JDK-8307549 and JDK-8321116
    CodeCache* libjvm = VMStructs::libjvm();
    if (libjvm == NULL) {
        return;
    }
    if (WX_MEMORY && VM::hotspot_version() == 17) {
        void** entry = (void**)libjvm->findSymbol("_ZN12StubRoutines18_safefetch32_entryE");
        if (entry != NULL) {
            *entry = (void*)SafeAccess::load32;
        }
    } else if (WX_MEMORY && VM::hotspot_version() == 11) {
        void** entry = (void**)libjvm->findSymbol("_ZN12StubRoutines17_safefetchN_entryE");
        if (entry != NULL) {
            *entry = (void*)SafeAccess::load;
        }
    }
}

void ProfilerVMStructsExt::initCriticalJNINatives() {
#ifdef __aarch64__
    // aarch64 does not support CriticalJNINatives
    VMFlag* flag = VMFlag::find("CriticalJNINatives", {VMFlag::Type::Bool});
    if (flag != nullptr && flag->get()) {
        flag->set(0);
    }
#endif // __aarch64__
}

const void* ProfilerVMStructsExt::findHeapUsageFunc() {
    CodeCache* libjvm = VMStructs::libjvm();
    if (libjvm == NULL) {
        return nullptr;
    }
    if (VM::hotspot_version() < 17) {
        // For JDK 11 it is really unreliable to find the memory_usage function -
        // just disable it
        return nullptr;
    } else {
        VMFlag* flag = VMFlag::find("UseG1GC", {VMFlag::Type::Bool});
        if (flag != NULL && flag->get()) {
            // The CollectedHeap::memory_usage function is a virtual one -
            // G1, Shenandoah and ZGC are overriding it and calling the base class
            // method results in asserts triggering. Therefore, we try to locate the
            // concrete overridden method form.
            return libjvm->findSymbol("_ZN15G1CollectedHeap12memory_usageEv");
        }
        flag = VMFlag::find("UseShenandoahGC", {VMFlag::Type::Bool});
        if (flag != NULL && flag->get()) {
            return libjvm->findSymbol("_ZN14ShenandoahHeap12memory_usageEv");
        }
        flag = VMFlag::find("UseZGC", {VMFlag::Type::Bool});
        if (flag != NULL && flag->get() && VM::hotspot_version() < 21) {
            // accessing this method in JDK 21 (generational ZGC) will cause SIGSEGV
            return libjvm->findSymbol("_ZN14ZCollectedHeap12memory_usageEv");
        }
        return libjvm->findSymbol("_ZN13CollectedHeap12memory_usageEv");
    }
}

bool ProfilerVMStructsExt::isSafeToWalk(uintptr_t pc) {
    return !VMStructs::unsafeToWalkCache().contains((const void*)pc);
}

void JNICALL ProfilerVMStructsExt::NativeMethodBind(jvmtiEnv* jvmti, JNIEnv* jni,
                                                     jthread thread, jmethodID method,
                                                     void* address, void** new_address_ptr) {
    static SpinLock _lock;
    static int delayedCounter = 0;
    static void** delayed = (void**)malloc(512 * sizeof(void*) * 2);

    if (_memory_usage_func == NULL) {
        if (jvmti != NULL && jni != NULL) {
            checkNativeBinding(jvmti, jni, method, address);
            void** tmpDelayed = NULL;
            int tmpCounter = 0;
            _lock.lock();
            if (delayed != NULL && delayedCounter > 0) {
                // in order to minimize the lock time, we copy the delayed list, free it
                // and release the lock
                tmpCounter = delayedCounter;
                tmpDelayed = (void**)malloc(tmpCounter * sizeof(void*) * 2);
                memcpy(tmpDelayed, delayed, tmpCounter * sizeof(void*) * 2);
                delayedCounter = 0;
                free(delayed);
                delayed = NULL;
            }
            _lock.unlock();
            // if there was a delayed list, we check it now, not blocking on the lock
            if (tmpDelayed != NULL) {
                for (int i = 0; i < tmpCounter; i += 2) {
                    checkNativeBinding(jvmti, jni, (jmethodID)tmpDelayed[i],
                                      tmpDelayed[i + 1]);
                }
                // don't forget to free the tmp list
                free(tmpDelayed);
            }
        } else {
            _lock.lock();
            if (delayed != NULL) {
                delayed[delayedCounter] = method;
                delayed[delayedCounter + 1] = address;
                delayedCounter += 2;
            }
            _lock.unlock();
        }
    }
}

void ProfilerVMStructsExt::checkNativeBinding(jvmtiEnv* jvmti, JNIEnv* jni,
                                               jmethodID method, void* address) {
    char* method_name;
    char* method_sig;
    int error = jvmti->GetMethodName(method, &method_name, &method_sig, NULL);
    if (error == 0) {
        if (strcmp(method_name, "getMemoryUsage0") == 0 &&
            strcmp(method_sig, "(Z)Ljava/lang/management/MemoryUsage;") == 0) {
            _memory_usage_func = (MemoryUsageFunc)address;
        }
    }
    jvmti->Deallocate((unsigned char*)method_sig);
    jvmti->Deallocate((unsigned char*)method_name);
}

// ===== HeapUsage implementation =====

bool HeapUsage::isJMXSupported() {
    initJMXUsage(VM::jni());
    return is_jmx_supported;
}

void HeapUsage::initJMXUsage(JNIEnv* env) {
    if (is_jmx_attempted) {
        // do not re-run the initialization
        return;
    }
    is_jmx_attempted = true;
    if (env == nullptr) {
        return;
    }
    jclass factory = env->FindClass("java/lang/management/ManagementFactory");
    if (!jniExceptionCheck(env) || factory == nullptr) {
        return;
    }
    jclass memoryBeanClass = env->FindClass("java/lang/management/MemoryMXBean");
    if (!jniExceptionCheck(env) || memoryBeanClass == nullptr) {
        return;
    }
    jmethodID get_memory = env->GetStaticMethodID(
        factory, "getMemoryMXBean", "()Ljava/lang/management/MemoryMXBean;");
    if (!jniExceptionCheck(env) || get_memory == nullptr) {
        return;
    }
    jobject memoryBean = env->CallStaticObjectMethod(factory, get_memory);
    if (!jniExceptionCheck(env) || memoryBean == nullptr) {
        return;
    }
    jmethodID get_heap = env->GetMethodID(memoryBeanClass, "getHeapMemoryUsage",
                                          "()Ljava/lang/management/MemoryUsage;");
    if (!jniExceptionCheck(env) || get_heap == nullptr) {
        return;
    }
    env->CallObjectMethod(memoryBean, get_heap);
    if (!jniExceptionCheck(env)) {
        return;
    }
    // mark JMX as supported only after we were able to retrieve the memory usage
    is_jmx_supported = true;
}

bool HeapUsage::isLastGCUsageSupported() {
    // only supported for JDK 17+
    // the CollectedHeap structure is vastly different in JDK 11 and earlier so
    // we can't support it
    return VMStructs::collected_heap_addr() != NULL &&
           ProfilerVMStructsExt::_heap_usage_func != NULL;
}

bool HeapUsage::needsNativeBindingInterception() {
    return VMStructs::collected_heap_addr() == NULL ||
           (ProfilerVMStructsExt::_heap_usage_func == NULL &&
            ProfilerVMStructsExt::_gc_heap_summary_func == NULL);
}

jlong HeapUsage::getMaxHeap(JNIEnv* env) {
    static jclass _rt;
    static jmethodID _get_rt;
    static jmethodID _max_memory;

    if (!(_rt = env->FindClass("java/lang/Runtime"))) {
        jniExceptionCheck(env);
        return -1;
    }

    if (!(_get_rt = env->GetStaticMethodID(_rt, "getRuntime",
                                          "()Ljava/lang/Runtime;"))) {
        jniExceptionCheck(env);
        return -1;
    }

    if (!(_max_memory = env->GetMethodID(_rt, "maxMemory", "()J"))) {
        jniExceptionCheck(env);
        return -1;
    }

    jobject rt = (jobject)env->CallStaticObjectMethod(_rt, _get_rt);
    jlong ret = (jlong)env->CallLongMethod(rt, _max_memory);
    if (jniExceptionCheck(env)) {
        return -1;
    }
    return ret;
}

HeapUsage HeapUsage::get() {
    return get(true);
}

HeapUsage HeapUsage::get(bool allow_jmx) {
    HeapUsage usage;
    const void* collected_heap_addr = VMStructs::collected_heap_addr();
    if (collected_heap_addr != NULL) {
        if (ProfilerVMStructsExt::_heap_usage_func != NULL) {
            // this is the JDK 17+ path
            usage = ProfilerVMStructsExt::_heap_usage_func(*(char**)collected_heap_addr);
            usage._used_at_last_gc =
                ((CollectedHeapWrapper*)*(char**)collected_heap_addr)->_used_at_last_gc;
        } else if (ProfilerVMStructsExt::_gc_heap_summary_func != NULL) {
            // this is the JDK 11 path
            // we need to collect GCHeapSummary information first
            GCHeapSummary summary =
                ProfilerVMStructsExt::_gc_heap_summary_func(*(char**)collected_heap_addr);
            usage._initSize = -1;
            usage._used = summary.used();
            usage._committed = -1;
            usage._maxSize = summary.maxSize();
        }
    }
    if (usage._maxSize == size_t(-1) && ProfilerVMStructsExt::_memory_usage_func != NULL &&
        allow_jmx && isJMXSupported()) {
        // this path is for non-hotspot JVMs
        // we need to patch the native method binding for JMX GetMemoryUsage to
        // capture the native method pointer first also, it requires JMX and
        // allocating new objects so it really should not be used in a GC callback
        JNIEnv* env = VM::jni();
        if (env == NULL) {
            return usage;
        }
        jobject m_usage =
            (jobject)ProfilerVMStructsExt::_memory_usage_func(env, (jobject)NULL, (jboolean)true);
        jclass cls = env->GetObjectClass(m_usage);
        jfieldID init_fid = env->GetFieldID(cls, "init", "J");
        jfieldID max_fid = env->GetFieldID(cls, "max", "J");
        jfieldID used_fid = env->GetFieldID(cls, "used", "J");
        jfieldID committed_fid = env->GetFieldID(cls, "committed", "J");
        if (init_fid == NULL || max_fid == NULL || used_fid == NULL ||
            committed_fid == NULL) {
            return usage;
        }
        usage._initSize = env->GetLongField(m_usage, init_fid);
        usage._maxSize = env->GetLongField(m_usage, max_fid);
        usage._used = env->GetLongField(m_usage, used_fid);
        usage._committed = env->GetLongField(m_usage, committed_fid);
    }
    return usage;
}
