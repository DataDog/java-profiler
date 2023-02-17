/*
 * Copyright 2022 Andrei Pangin
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

#include "j9ObjectSampler.h"
#include "j9Ext.h"
#include "vmEntry.h"


// !!! This class is not used currently and as such all the implementation is commented out !!!

void J9ObjectSampler::JavaObjectAlloc(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread,
                                      jobject object, jclass object_klass, jlong size) {
    #ifdef NEVER
    if (_interval > 0  && updateCounter(_allocated_bytes, size, _interval)) {
        recordAllocation(jvmti, BCI_ALLOC, object_klass, size);
    }
    #endif
}

void J9ObjectSampler::VMObjectAlloc(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread,
                                    jobject object, jclass object_klass, jlong size) {
    #ifdef NEVER
    if (_interval > 0  && updateCounter(_allocated_bytes, size, _interval)) {
        recordAllocation(jvmti, BCI_ALLOC_OUTSIDE_TLAB, object_klass, size);
    }
    #endif
}

Error J9ObjectSampler::check(Arguments& args) {
    #ifdef NEVER
    if (J9Ext::InstrumentableObjectAlloc_id < 0) {
        return Error("InstrumentableObjectAlloc is not supported on this JVM");
    }
    #endif
    return Error::OK;
}

Error J9ObjectSampler::start(Arguments& args) {
    #ifdef NEVER
    Error error = check(args);
    if (error) {
        return error;
    }

    _interval = args._memory > 0 ? args._memory : DEFAULT_ALLOC_INTERVAL;
    _allocated_bytes = 0;

    jvmtiEnv* jvmti = VM::jvmti();
    if (jvmti->SetExtensionEventCallback(J9Ext::InstrumentableObjectAlloc_id, (jvmtiExtensionEvent)JavaObjectAlloc) != 0) {
        return Error("Could not enable InstrumentableObjectAlloc callback");
    }
    jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, NULL);
    #endif

    return Error::OK;
}

void J9ObjectSampler::stop() {
    #ifdef NEVER
    jvmtiEnv* jvmti = VM::jvmti();
    jvmti->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, NULL);
    jvmti->SetExtensionEventCallback(J9Ext::InstrumentableObjectAlloc_id, NULL);
    #endif
}
