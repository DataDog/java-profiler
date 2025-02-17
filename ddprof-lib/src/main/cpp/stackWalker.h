/*
 * Copyright 2021 Andrei Pangin
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

#ifndef _STACKWALKER_H
#define _STACKWALKER_H

#include "thread.h"
#include "vmEntry.h"
#include <functional>
#include <stdint.h>

class JavaFrameAnchor;

struct StackContext {
  const void *pc;
  uintptr_t sp;
  uintptr_t fp;

  void set(const void *pc, uintptr_t sp, uintptr_t fp) {
    this->pc = pc;
    this->sp = sp;
    this->fp = fp;
  }
};

// Detail level of VMStructs stack walking
enum StackDetail {
    VM_BASIC,   // only basic Java frames similar to what AsyncGetCallTrace provides
    VM_NORMAL,  // include frame types and runtime stubs
    VM_EXPERT   // all features: frame types, runtime stubs, and intermediate native frames
};

class StackWalker {
private:
  static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                    StackDetail detail, const void* pc, uintptr_t sp, uintptr_t fp, bool *truncated);

public:
  static int walkFP(void *ucontext, const void **callchain, int max_depth,
                    StackContext *java_ctx, bool *truncated);
  static int walkDwarf(void *ucontext, const void **callchain, int max_depth,
                       StackContext *java_ctx, bool *truncated);
  static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, StackDetail detail, bool *truncated);
  static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, JavaFrameAnchor* anchor, bool *truncated);

  static void checkFault(ProfiledThread* thrd);
};

#endif // _STACKWALKER_H
