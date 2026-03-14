/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cassert>
#include "threadState.inline.h"
#include "vmStructs.h"

ThreadStateResolver* ThreadStateResolver::INSTANCE = nullptr;

void ThreadStateResolver::initialize() {
    if (VM::isHotspot()) {
        INSTANCE = new VMStructsThreadStateResolver();
    } else {
        INSTANCE = new JNIThreadStateResolver();
    }
}

VMStructsThreadStateResolver::VMStructsThreadStateResolver() {
    assert(VM::isHotspot());
}

OSThreadState VMStructsThreadStateResolver::resolveThreadState(jthread thread) {
    JNIEnv* jni = VM::jni();
    VMThread* vm_thread = VMThread::fromJavaThread(jni, thread);
    // Thread no longer reachable
    if (vm_thread == nullptr) {
        return  OSThreadState::TERMINATED;
    }

    int raw_thread_state = vm_thread->state();
    bool is_initialized = raw_thread_state >= JVMJavaThreadState::_thread_in_native &&
                          raw_thread_state < JVMJavaThreadState::_thread_max_state;
    if (!is_initialized) {
        return OSThreadState::UNKNOWN;
    }

    OSThreadState state = OSThreadState::UNKNOWN;
    OSThreadState os_state = vm_thread->osThreadState();
    if (os_state == OSThreadState::UNKNOWN) {
      state = OSThreadState::RUNNABLE;
    } else {
      state = os_state;
    }
    return state;
}

ExecutionMode VMStructsThreadStateResolver::resolveThreadExecutionMode(jthread thread) {
    JNIEnv* jni = VM::jni();
    VMThread* vm_thread = VMThread::fromJavaThread(jni, thread);
    return getThreadExecutionMode(vm_thread);
}


JNIThreadStateResolver::JNIThreadStateResolver() {
    assert(VM::isOpenJ9() || VM::isZing());

    JNIEnv* jni = VM::jni();
    jclass thread_class = jni->FindClass("java/lang/Thread");
    jclass thread_state_class = jni->FindClass("java/lang/Thread$State");
    assert(thread_class != nullptr);
    assert(thread_state_class != nullptr);

    _thread_get_state_id = jni->GetMethodID(thread_class, "getState", "()Ljava/lang/Thread$State;");
    assert(_thread_get_state_id != nullptr);
    _state_ordinal_id = jni->GetMethodID(thread_state_class, "ordinal", "()I");
    assert(_state_ordinal_id != nullptr);
}

OSThreadState JNIThreadStateResolver::resolveThreadState(jthread thread) {
    JNIEnv* jni = VM::jni();
    jobject state = jni->CallObjectMethod(thread, _thread_get_state_id);
    int ordinal = jni->CallIntMethod(state, _state_ordinal_id);
    return ordinal2ThreadState(ordinal);
}

ExecutionMode JNIThreadStateResolver::resolveThreadExecutionMode(jthread thread) {
    return ExecutionMode::JAVA;
}

OSThreadState JNIThreadStateResolver::ordinal2ThreadState(int ordinal) {
    switch(ordinal) {
        case 0: return OSThreadState::NEW;
        case 1: return OSThreadState::RUNNABLE;
        case 2: return OSThreadState::MONITOR_WAIT;
        case 3:
        case 4: return OSThreadState::OBJECT_WAIT;
        case 5: return OSThreadState::TERMINATED;
        default: assert(false);
    }
    return OSThreadState::UNKNOWN;
}
