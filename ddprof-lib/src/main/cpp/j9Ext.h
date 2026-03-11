/*
 * Copyright 2022 Andrei Pangin
 * Copyright 2024, 2025 Datadog, Inc
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

#ifndef _J9EXT_H
#define _J9EXT_H

#include <jvmti.h>

#include "log.h"
#include "vmEntry.h"
#include "vmStructs.h"

#define JVMTI_EXT(f, ...) ((jvmtiError(*)(jvmtiEnv *, __VA_ARGS__))f)

struct jvmtiFrameInfoExtended {
  jmethodID method;
  jlocation location;
  jlocation machinepc;
  jint type;
  void *native_frame_address;
};

struct jvmtiStackInfoExtended {
  jthread thread;
  jint state;
  jvmtiFrameInfoExtended *frame_buffer;
  jint frame_count;
};

enum { SHOW_COMPILED_FRAMES = 4, SHOW_INLINED_FRAMES = 8 };

/**
 * J9 frame type constants from ibmjvmti.h.
 * These are the expected values returned in jvmtiFrameInfoExtended.type.
 */
enum J9FrameType {
  J9_FRAME_NOT_JITTED = 0,  // COM_IBM_STACK_FRAME_EXTENDED_NOT_JITTED
  J9_FRAME_JITTED = 1,      // COM_IBM_STACK_FRAME_EXTENDED_JITTED
  J9_FRAME_INLINED = 2      // COM_IBM_STACK_FRAME_EXTENDED_INLINED
};

/**
 * Validates and maps J9 frame type to FrameTypeId.
 * J9's JVMTI extension may return unexpected values in the type field.
 * This function ensures we only pass valid values to FrameType::encode().
 *
 * @param j9_type The frame type value from jvmtiFrameInfoExtended.type
 * @return A valid FrameTypeId (FRAME_INTERPRETED, FRAME_JIT_COMPILED, or FRAME_INLINED)
 */
static inline int sanitizeJ9FrameType(jint j9_type) {
  // J9 should only return 0, 1, or 2 for the frame type.
  // Any other value is unexpected and we default to JIT compiled.
  if (j9_type >= J9_FRAME_NOT_JITTED && j9_type <= J9_FRAME_INLINED) {
    return j9_type;  // Direct mapping: J9 values match our FrameTypeId values
  }
  // Unexpected value - default to JIT compiled as the safest assumption
  return FRAME_JIT_COMPILED;
}

class J9Ext {
private:
  static jvmtiEnv *_jvmti;

  static void *(*_j9thread_self)();

  static jvmtiExtensionFunction _GetOSThreadID;
  static jvmtiExtensionFunction _GetJ9vmThread;
  static jvmtiExtensionFunction _GetStackTraceExtended;
  static jvmtiExtensionFunction _GetAllStackTracesExtended;

public:
  static bool can_use_ASGCT() {
    // as of 21.0.6 the use of ASGCT will lead to almost immediate crash
    //   or livelock on J9
    return (VM::java_version() == 8 && VM::java_update_version() >= 361) ||
           (VM::java_version() == 11 && VM::java_update_version() >= 18) ||
           (VM::java_version() == 17 && VM::java_update_version() >= 6) ||
           (VM::java_version() >= 18 && VM::java_version() < 21);
  }

  static bool is_jvmti_jmethodid_safe() {
    // only JDK 8 is safe to use jmethodID in JVMTI for deferred resolution
    //   unless -XX:+KeepJNIIDs=true is provided
    return VM::java_version() == 8;
  }

  static bool shouldUseAsgct() {
    char *sampler = NULL;

    jvmtiEnv *jvmti = VM::jvmti();
    jvmti->GetSystemProperty("dd.profiling.ddprof.j9.sampler", &sampler);

    bool asgct = true;
    if (sampler != nullptr) {
      if (!strncmp("asgct", sampler, 5)) {
        asgct = true;
      } else if (!strncmp("jvmti", sampler, 5)) {
        asgct = false;
      } else {
        fprintf(stdout, "[ddprof] [WARN] Invalid J9 sampler: %s, supported values are [jvmti, asgct]", sampler);
      }
    }
    jvmti->Deallocate((unsigned char *)sampler);
    return asgct;
  }

  static bool initialize(jvmtiEnv *jvmti, const void *j9thread_self);

  static int GetOSThreadID(jthread thread) {
    jlong thread_id;
    return JVMTI_EXT(_GetOSThreadID, jthread, jlong *)(_jvmti, thread,
                                                       &thread_id) == 0
               ? (int)thread_id
               : -1;
  }

  static JNIEnv *GetJ9vmThread(jthread thread) {
    JNIEnv *result;
    return JVMTI_EXT(_GetJ9vmThread, jthread, JNIEnv **)(_jvmti, thread,
                                                         &result) == 0
               ? result
               : NULL;
  }

  static jvmtiError GetStackTraceExtended(jthread thread, jint start_depth,
                                          jint max_frame_count,
                                          void *frame_buffer, jint *count_ptr) {
    return JVMTI_EXT(_GetStackTraceExtended, jint, jthread, jint, jint, void *,
                     jint *)(_jvmti, SHOW_COMPILED_FRAMES | SHOW_INLINED_FRAMES,
                             thread, start_depth, max_frame_count, frame_buffer,
                             count_ptr);
  }

  static jvmtiError GetAllStackTracesExtended(jint max_frame_count,
                                              void **stack_info_ptr,
                                              jint *thread_count_ptr) {
    return JVMTI_EXT(_GetAllStackTracesExtended, jint, jint, void **,
                     jint *)(_jvmti, SHOW_COMPILED_FRAMES | SHOW_INLINED_FRAMES,
                             max_frame_count, stack_info_ptr, thread_count_ptr);
  }

  static jvmtiError GetStackTrace(jthread thread, jint start_depth,
                                  jint max_frame_count,
                                  ASGCT_CallFrame *frame_buffer,
                                  jint *count_ptr) {
    jvmtiFrameInfoExtended buffer[max_frame_count];

    jvmtiError err = GetStackTraceExtended(thread, start_depth, max_frame_count,
                                           buffer, count_ptr);
    if (err) {
      return err;
    }
    for (int j = 0; j < *count_ptr; j++) {
      jvmtiFrameInfoExtended *fi = &buffer[j];
      frame_buffer[j].method_id = fi->method;
      frame_buffer[j].bci = FrameType::encode(sanitizeJ9FrameType(fi->type), fi->location);
    }
    return JVMTI_ERROR_NONE;
  }

  static void *j9thread_self() {
    return _j9thread_self != NULL ? _j9thread_self() : NULL;
  }

  static int InstrumentableObjectAlloc_id;
};

#endif // _J9EXT_H
