/*
 * Copyright 2021, 2025 Datadog, Inc
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

#ifndef _STACKWALKER_DD_H
#define _STACKWALKER_DD_H

#include "stackWalker.h"


namespace ddprof {
  class StackWalker : public ::StackWalker {
    public:
      inline static int walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated) {
        int walked = ::StackWalker::walkFP(ucontext, callchain, max_depth + 1, java_ctx);
        if (walked > max_depth) {
          *truncated = true;
          walked = max_depth;
        }
        return walked;
      }
      inline static int walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated) {
        int walked = ::StackWalker::walkDwarf(ucontext, callchain, max_depth + 1, java_ctx);
        if (walked > max_depth) {
          *truncated = true;
          walked = max_depth;
        }
        return walked;
      }
      inline static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, StackDetail detail, bool* truncated) {
        int walked = ::StackWalker::walkVM(ucontext, frames, max_depth + 1, detail);
        if (walked > max_depth) {
          *truncated = true;
          walked = max_depth;
        } else if (walked > 0) {
          if (frames[walked - 1].bci == BCI_ERROR) {
            // root frame is error; best guess is that the trace is truncated
            *truncated = true;
          }
        }
        return walked;
      }

      inline static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, JavaFrameAnchor* anchor, bool* truncated) {
        int walked = ::StackWalker::walkVM(ucontext, frames, max_depth + 1, anchor);
        if (walked > max_depth) {
          *truncated = true;
          walked = max_depth;
        } else if (walked > 0) {
          if (frames[walked - 1].bci == BCI_ERROR) {
            // root frame is error; best guess is that the trace is truncated
            *truncated = true;
          }
        }
        return walked;
      }
  };
}

#endif // _STACKWALKER_H