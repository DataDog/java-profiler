/*
 * Copyright 2026, Datadog, Inc.
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
#ifndef _FRAMES_H
#define _FRAMES_H

#include <jni.h>
#include <jvmti.h>
#include "vmEntry.h"

inline void copyJvmtiFrames(ASGCT_CallFrame *frames,
                            const jvmtiFrameInfo *jvmti_frames,
                            jint num_frames) {
  // The source and destination commonly refer to the two views of the same
  // CallTraceBuffer union. Read both source fields before either write.
  for (jint i = 0; i < num_frames; ++i) {
    jmethodID method = jvmti_frames[i].method;
    jlocation location = jvmti_frames[i].location;
    frames[i].method_id = method;
    frames[i].bci = static_cast<jint>(location);
    LP64_ONLY(frames[i].padding = 0;)
  }
}

inline int makeFrame(ASGCT_CallFrame *frames, jint type, jmethodID id) {
  frames[0].bci = type;
  frames[0].method_id = id;
  return 1;
}

inline int makeFrame(ASGCT_CallFrame *frames, jint type,
                            const char *id) {
  return makeFrame(frames, type, (jmethodID)id);
}

#endif // _FRAMES_H
