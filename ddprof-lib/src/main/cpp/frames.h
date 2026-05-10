#ifndef _FRAMES_H
#define _FRAMES_H

#include <jni.h>
#include "vmEntry.h"

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
