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

#include "stackWalker.h"
#include "common.h"
#include "dwarf.h"
#include "libraries.h"
#include "profiler.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "symbols.h"
#include "vmStructs.h"

#include <ucontext.h>
#include <setjmp.h>

const uintptr_t SAME_STACK_DISTANCE = 8192;
const uintptr_t MAX_WALK_SIZE = 0x100000;
const intptr_t MAX_FRAME_SIZE = 0x40000;
const intptr_t MAX_INTERPRETER_FRAME_SIZE = 0x1000;
const intptr_t DEAD_ZONE = 0x1000;

static inline bool aligned(uintptr_t ptr) {
  return (ptr & (sizeof(uintptr_t) - 1)) == 0;
}

static inline bool inDeadZone(const void *ptr) {
  return ptr < (const void *)DEAD_ZONE || ptr > (const void *)-DEAD_ZONE;
}

static inline bool sameStack(void *hi, void *lo) {
  return (uintptr_t)hi - (uintptr_t)lo < SAME_STACK_DISTANCE;
}

// AArch64: on Linux, frame link is stored at the top of the frame,
// while on macOS, frame link is at the bottom.
static inline uintptr_t defaultSenderSP(uintptr_t sp, uintptr_t fp) {
#ifdef __APPLE__
    return sp + 2 * sizeof(void*);
#else
    return fp;
#endif
}

static inline void fillFrame(ASGCT_CallFrame &frame, ASGCT_CallFrameType type,
                             const char *name) {
  frame.bci = type;
  frame.method_id = (jmethodID)name;
}

static inline void fillFrame(ASGCT_CallFrame &frame, FrameTypeId type, int bci,
                             jmethodID method) {
  frame.bci = FrameType::encode(type, bci);
  frame.method_id = method;
}


static inline void fillErrorFrame(ASGCT_CallFrame& frame, const char *name, bool *truncated) {
  fillFrame(frame, BCI_ERROR, name);
  *truncated = true;
}

static inline void fillSkipFrame(ASGCT_CallFrame& frame) {
  fillFrame(frame, BCI_ERROR, "skipped_frames");
}

static jmethodID getMethodId(VMMethod *method) {
  if (!inDeadZone(method) && aligned((uintptr_t)method)) {
    jmethodID method_id = method->id();
    if (!inDeadZone(method_id) && aligned((uintptr_t)method_id) &&
        *(VMMethod **)method_id == method) {
      return method_id;
    }
  }
  return NULL;
}

int StackWalker::walkFP(void *ucontext, const void **callchain, int max_depth,
                        StackContext *java_ctx, bool *truncated) {
  const void *pc;
  uintptr_t fp;
  uintptr_t sp;
  uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

  StackFrame frame(ucontext);
  if (ucontext == NULL) {
    pc = __builtin_return_address(0);
    fp = (uintptr_t)__builtin_frame_address(1);
    sp = (uintptr_t)__builtin_frame_address(0);
  } else {
    StackFrame frame(ucontext);
    pc = (const void *)frame.pc();
    fp = frame.fp();
    sp = frame.sp();
  }

  int depth = 0;

  *truncated = false;

  // Walk until the bottom of the stack or until the first Java frame
  while (true) {
    if (depth == max_depth) {
      *truncated = true;
      break;
    }
    if (CodeHeap::contains(pc) && !(depth == 0 && frame.unwindAtomicStub(pc))) {
      java_ctx->set(pc, sp, fp);
      break;
    }

    callchain[depth++] = pc;

    // Check if the next frame is below on the current stack
    if (fp < sp || fp >= sp + MAX_FRAME_SIZE || fp >= bottom) {
      *truncated = fp != 0x0;
      break;
    }

    // Frame pointer must be word aligned
    if (!aligned(fp)) {
      *truncated = true;
      break;
    }

    pc = stripPointer(SafeAccess::load((void **)fp + FRAME_PC_SLOT));
    if (inDeadZone(pc)) {
      *truncated = pc != NULL;
      break;
    }

    sp = fp + (FRAME_PC_SLOT + 1) * sizeof(void *);
    fp = *(uintptr_t *)fp;
  }

  return depth;
}

int StackWalker::walkDwarf(void *ucontext, const void **callchain,
                           int max_depth, StackContext *java_ctx,
                           bool *truncated) {
  const void *pc;
  uintptr_t fp;
  uintptr_t sp;
  uintptr_t prev_sp;
  uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;
  StackFrame frame(ucontext);
  if (ucontext == NULL) {
    pc = __builtin_return_address(0);
    fp = (uintptr_t)__builtin_frame_address(1);
    sp = (uintptr_t)__builtin_frame_address(0);
  } else {
    pc = (const void *)frame.pc();
    fp = frame.fp();
    sp = frame.sp();
  }

  int depth = 0;
  Libraries *libraries = Libraries::instance();

  *truncated = false;

  // Walk until the bottom of the stack or until the first Java frame
  while (true) {
    if (depth == max_depth) {
      *truncated = true;
      break;
    }
    if (CodeHeap::contains(pc) && !(depth == 0 && frame.unwindAtomicStub(pc))) {
      const void* page_start = (const void*)((uintptr_t)pc & ~0xfffUL);
      // Don't dereference pc as it may point to unreadable memory
      // frame.adjustSP(page_start, pc, sp);
      java_ctx->set(pc, sp, fp);
      break;
    }

    callchain[depth++] = pc;
    prev_sp = sp;

    CodeCache *cc = libraries->findLibraryByAddress(pc);
    FrameDesc *f =
        cc != NULL ? cc->findFrameDesc(pc) : &FrameDesc::default_frame;

    u8 cfa_reg = (u8)f->cfa;
      int cfa_off = f->cfa >> 8; // cfa is encoded in the upper 8 bits of the CFA value

    if (cfa_reg == DW_REG_SP) {
      sp = sp + cfa_off;
    } else if (cfa_reg == DW_REG_FP) {
      sp = fp + cfa_off;
    } else if (cfa_reg == DW_REG_PLT) {
      sp += ((uintptr_t)pc & 15) >= 11 ? cfa_off * 2 : cfa_off;
    } else {
      *truncated = true;
      break;
    }

    // Check if the next frame is below on the current stack
    if (sp < prev_sp || sp >= prev_sp + MAX_FRAME_SIZE || sp >= bottom) {
      *truncated = sp != 0x0;
      break;
    }

    // Stack pointer must be word aligned
    if (!aligned(sp)) {
      *truncated = true;
      break;
    }

    if (f->fp_off & DW_PC_OFFSET) {
      pc = (const char *)pc + (f->fp_off >> 1);
    } else {
      if (f->fp_off != DW_SAME_FP && f->fp_off < MAX_FRAME_SIZE &&
          f->fp_off > -MAX_FRAME_SIZE) {
        fp = (uintptr_t)SafeAccess::load((void **)(sp + f->fp_off));
      }
      if (EMPTY_FRAME_SIZE > 0 || cfa_off != 0) {
        // x86 or AArch64 non-default frame
        pc = stripPointer(SafeAccess::load((void **)(sp + f->pc_off)));
      } else if (f->fp_off != DW_SAME_FP) {
        // AArch64 default_frame
        pc = stripPointer(SafeAccess::load((void **)(sp + f->pc_off)));
        sp = defaultSenderSP(sp, fp);
      } else if (depth <= 1) {
        pc = (const void *)frame.link();
      } else {
        // Stack bottom
        break;
      }
    }
  }
  return depth;
}

int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                        StackDetail detail, const void* pc, uintptr_t sp, uintptr_t fp, bool *truncated) {
  // extract StackFrame from uncontext
  StackFrame frame(ucontext);
  uintptr_t bottom = (uintptr_t)&frame + MAX_WALK_SIZE;

  if (inDeadZone(pc)) {
    *truncated = pc != NULL;
    return 0;
  }
  Profiler *profiler = Profiler::instance();
  Libraries *libraries = Libraries::instance();

  int bcp_offset = InterpreterFrame::bcp_offset();

  jmp_buf crash_protection_ctx;
  VMThread *vm_thread = VMThread::current();
  void *saved_exception = vm_thread != NULL ? vm_thread->exception() : NULL;

  // Should be preserved across setjmp/longjmp
  volatile int depth = 0;
  JavaFrameAnchor* anchor = nullptr;
  bool recovered_from_anchor = false;

  if (vm_thread != NULL) {
    vm_thread->exception() = &crash_protection_ctx;
    if (setjmp(crash_protection_ctx) != 0) {
      vm_thread->exception() = saved_exception;
      if (depth < max_depth) {
        TEST_LOG("Crash protection triggered");
        fillErrorFrame(frames[depth++], "break_not_walkable", truncated);
      }
      return depth;
    }
    anchor = vm_thread->anchor();
  }
  CodeCache *cc = NULL;

  bool got_start_thread = false;
  const void* prev_pc = 0;
  // Walk until the bottom of the stack or until the first Java frame
  while (depth < max_depth) {
    if (CodeHeap::contains(pc)) {
      // constant time
      NMethod *nm = CodeHeap::findNMethod(pc);
      if (nm == NULL) {
        fillErrorFrame(frames[depth++], "unknown_nmethod", truncated);
      } else {
        if (nm->isNMethod()) {
          int level = nm->level();
          FrameTypeId type = detail != VM_BASIC &&
              level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;
          fillFrame(frames[depth++], type, 0, nm->method()->id());

          if (nm->isFrameCompleteAt(pc)) {
            int scope_offset = nm->findScopeOffset(pc);
            if (scope_offset > 0) {
              depth--;
              ScopeDesc scope(nm);
              do {
                scope_offset = scope.decode(scope_offset);
                if (scope.method() == nullptr) {
                  fillErrorFrame(frames[depth++], "unknown_scope", truncated);
                  break;
                }
                if (detail != VM_BASIC) {
                  type = scope_offset > 0 ? FRAME_INLINED :
                         level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;
                }
                fillFrame(frames[depth++], type, scope.bci(),
                          scope.method()->id());
              } while (scope_offset > 0 && depth < max_depth);
            }

            // Handle situations when sp is temporarily changed in the compiled
            // code
            frame.adjustSP(nm->entry(), pc, sp);
            uintptr_t fpback = fp;
            sp += nm->frameSize() * sizeof(void *);
            fp = ((uintptr_t *)sp)[-FRAME_PC_SLOT - 1];
            pc = ((const void **)sp)[-FRAME_PC_SLOT];

            if (!profiler->isAddressInCode(pc, true)) {
              const void* newpc = stripPointer(*(const void **)(fpback + sizeof(void*)));
              if (profiler->isAddressInCode(newpc, true)) {
                TEST_LOG("Relinking via FP for entry: %lx, %s", nm->entry(), nm->name());
                fp = *(uintptr_t *)fpback;
                pc = newpc;
                sp = fp;
              } else {
                if (anchor && !recovered_from_anchor) {
                  TEST_LOG("Recovering from java frame anchor from entry: %lx, %s", nm->entry(), nm->name());
                  recovered_from_anchor = true;
                  if (anchor->lastJavaPC() == nullptr || anchor->lastJavaSP() == 0) {
                    // End of Java stack
                    break;
                  }
                  fillSkipFrame(frames[depth++]);
                  pc = anchor->lastJavaPC();
                  sp = anchor->lastJavaSP();
                  fp = anchor->lastJavaFP();
                  continue;
                }
                fillErrorFrame(frames[depth++], "break_compiled: no java anchor", truncated);
                break;
              }
            }
            continue;
          } else {
            if (frame.unwindCompiled(nm, (uintptr_t &)pc, sp, fp) && profiler->isAddressInCode(pc)) {
              continue;
            }
          }

          fillErrorFrame(frames[depth++], "break_compiled", truncated);
          break;
        } else if (nm->isInterpreter()) {
          if (vm_thread != NULL && vm_thread->inDeopt()) {
            fillErrorFrame(frames[depth++], "break_deopt", truncated);
            break;
          }

          bool is_plausible_interpreter_frame =
              !inDeadZone((const void *)fp) && aligned(fp) &&
              sp > fp - MAX_INTERPRETER_FRAME_SIZE &&
              sp < fp + bcp_offset * sizeof(void *);

          if (is_plausible_interpreter_frame) {
            VMMethod *method = ((VMMethod **)fp)[InterpreterFrame::method_offset];
            jmethodID method_id = getMethodId(method);
            if (method_id != NULL) {
              const char *bytecode_start = method->bytecode();
              const char *bcp = ((const char **)fp)[bcp_offset];
              int bci = bytecode_start == NULL || bcp < bytecode_start
                            ? 0
                            : bcp - bytecode_start;
              fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);

              sp = ((uintptr_t *)fp)[InterpreterFrame::sender_sp_offset];
              pc = stripPointer(((void **)fp)[FRAME_PC_SLOT]);
              fp = *(uintptr_t *)fp;
              continue;
            }
          }

          if (depth == 0) {
            VMMethod *method = (VMMethod *)frame.method();
            jmethodID method_id = getMethodId(method);
            if (method_id != NULL) {
              fillFrame(frames[depth++], FRAME_INTERPRETED, 0, method_id);

              if (is_plausible_interpreter_frame) {
                pc = stripPointer(((void **)fp)[FRAME_PC_SLOT]);
                sp = frame.senderSP();
                fp = *(uintptr_t *)fp;
              } else {
                pc = stripPointer(*(void **)sp);
                sp = frame.senderSP();
              }
              continue;
            }
          }

          if (!recovered_from_anchor && anchor && detail < VM_EXPERT) {
            if (anchor->lastJavaPC() == nullptr || anchor->lastJavaSP() == 0) {
              // End of Java stack
              break;
            }
            fillSkipFrame(frames[depth++]);
            fp = anchor->lastJavaFP();
            sp = anchor->lastJavaSP();
            pc = anchor->lastJavaPC();
            recovered_from_anchor = true;
            continue;
          }

          fillErrorFrame(frames[depth++], "break_interpreted", truncated);
          break;
        } else if (detail < VM_EXPERT && nm->isEntryFrame(pc)) {
          JavaFrameAnchor* e_anchor = JavaFrameAnchor::fromEntryFrame(fp);
          if (e_anchor == NULL) {
            if (anchor != NULL && !recovered_from_anchor && anchor->lastJavaSP() != 0) {
              TEST_LOG("Reusing thread anchor");
              fillSkipFrame(frames[depth++]);
              e_anchor = anchor;
            } else {
              fillErrorFrame(frames[depth++], "break_entry_frame: no anchor", truncated);
              break;
            }
          }
          uintptr_t prev_sp = sp;
          sp = e_anchor->lastJavaSP();
          fp = e_anchor->lastJavaFP();
          pc = e_anchor->lastJavaPC();
          if (sp == 0 || pc == NULL) {
            // End of Java stack
            break;
          }
          if (sp < prev_sp || sp >= bottom || !aligned(sp)) {
            TEST_LOG("Failed to unwind entry frame");
            fillErrorFrame(frames[depth++], "break_entry_frame: invalid anchor", truncated);
            break;
          }
          continue;
        } else {
          // linear time in number of runtime stubs
          CodeBlob *stub = profiler->findRuntimeStub(pc);
          const void *start = stub != NULL ? stub->_start : nm->code();
          const char *name = stub != NULL ? stub->_name : nm->name();

          if (detail != VM_BASIC) {
            fillFrame(frames[depth++], BCI_NATIVE_FRAME, name);
          }

          if (frame.unwindStub((instruction_t *)start, name, (uintptr_t &)pc, sp,
                               fp)) {
            continue;
          }

          if (nm->frameSize() == 0) {
            // stubs with 0 frame size are real
            pc = stripPointer(*(const void **)(fp +sizeof(void*)));
            fp = *(uintptr_t *)fp;
            sp = fp;
            continue;
          }
          if (depth > 1 && nm->frameSize() > 0) {
            sp += nm->frameSize() * sizeof(void *);
            fp = ((uintptr_t *)sp)[-FRAME_PC_SLOT - 1];
            pc = ((const void **)sp)[-FRAME_PC_SLOT];
            continue;
          }
        }
      }
    } else {
      // sometimes we seem to get into a long sequence of frames pointing to the same pc
      //   we just want to skip that over
      if (prev_pc != pc) {
        if (cc == NULL || !cc->contains(pc)) {
          cc = libraries->findLibraryByAddress(pc);
        }
        const char *name = cc == NULL ? NULL : cc->binarySearch(pc);

        fillFrame(frames[depth++], BCI_NATIVE_FRAME, name);

        if (Symbols::isRootSymbol(pc)) {
          break;
        }
        prev_pc = pc;
      }
    }

    uintptr_t prev_sp = sp;
    if (prev_sp == 0) {
      // Reached the initial frame
      break;
    }
    if (cc == NULL || !cc->contains(pc)) {
      cc = libraries->findLibraryByAddress(pc);
    }
    // It may happen that the current PC can not be resolved as belonging to any known library.
    // In that case we just use the default_frame which is a bit of gamble on aarch64 due to
    // no standard in the function epilogue - but the bet is that the GCC compiled code is
    // seen more often than the clang one.
    FrameDesc *f =
        cc != NULL ? cc->findFrameDesc(pc) : &FrameDesc::default_frame;

    u8 cfa_reg = (u8)f->cfa;
    int cfa_off = f->cfa >> 8;
    if (cfa_reg == DW_REG_SP) {
      sp = sp + cfa_off;
    } else if (cfa_reg == DW_REG_FP) {
      sp = fp + cfa_off;
    } else if (cfa_reg == DW_REG_PLT) {
      sp += ((uintptr_t)pc & 15) >= 11 ? cfa_off * 2 : cfa_off;
    } else {
      break;
    }

    // Check if the next frame is below on the current stack
    if (sp < prev_sp || sp >= prev_sp + MAX_FRAME_SIZE || sp >= bottom) {
      if (fp < 0xff && sp < 0xff && depth <= 1) {
        // Most likely MUSL signal trampoline
        // FP, SP, RET is completely garbled and unrecoverable
        // Let's try to jump to the stored Java frame -
        //   the garbled frame is leaf so there is no danger we 'loop' back to the top Java frame
        if (anchor && !recovered_from_anchor && anchor->lastJavaSP() != 0) {
          recovered_from_anchor = true;
          fillSkipFrame(frames[depth++]);
          sp = anchor->lastJavaSP();
          fp = anchor->lastJavaFP();
          pc = anchor->lastJavaPC();
          continue;
        }
      }
      break;
    }

    // Stack pointer must be word aligned
    if (!aligned(sp)) {
      break;
    }

    if (f->fp_off & DW_PC_OFFSET) {
      pc = (const char *)pc + (f->fp_off >> 1);
    } else {
      if (f->fp_off != DW_SAME_FP && f->fp_off < MAX_FRAME_SIZE &&
          f->fp_off > -MAX_FRAME_SIZE) {
        fp = *(uintptr_t *)(sp + f->fp_off);
      }
      if (EMPTY_FRAME_SIZE > 0 || cfa_off != 0) {
        // x86 or AArch64 non-default frame
        pc = stripPointer(*(void **)(sp + f->pc_off));
      } else if (f->fp_off != DW_SAME_FP) {
        // AArch64 default_frame
        pc = stripPointer(*(void **)(sp + f->pc_off));
        sp = defaultSenderSP(sp, fp);
      } else if (depth <= 1) {
        pc = (const void *)frame.link();
      } else {
        // Stack bottom
        break;
      }
    }

    if (anchor && !recovered_from_anchor && !VMStructs::goodPtr((const void*)fp) && anchor->lastJavaSP() != 0) {
      recovered_from_anchor = true;
      fillSkipFrame(frames[depth++]);
      sp = anchor->lastJavaSP();
      fp = anchor->lastJavaFP();
      pc = anchor->lastJavaPC();
    }

    if (inDeadZone(pc)) {
      break;
    }
  }

  if (vm_thread != NULL)
    vm_thread->exception() = saved_exception;

  return depth;
}

int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, JavaFrameAnchor* anchor, bool *truncated) {
  uintptr_t sp = anchor->lastJavaSP();
  if (sp == 0) {
    *truncated = true;
    return 0;
  }

  uintptr_t fp = anchor->lastJavaFP();
  if (fp == 0) {
    fp = sp;
  }

  const void* pc = anchor->lastJavaPC();
  if (pc == NULL) {
    pc = ((const void**)sp)[-1];
  }

  return walkVM(ucontext, frames, max_depth, VM_BASIC, pc, sp, fp, truncated);
}


#ifdef __aarch64__
// we are seeing false alarms on aarch64 GHA runners due to 'heap-use-after-free'
__attribute__((no_sanitize("address")))
#endif
int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, StackDetail detail, bool *truncated) {
  if (ucontext == NULL) {
    const void* pc = __builtin_return_address(0);
    uintptr_t sp = (uintptr_t)__builtin_frame_address(0) + LINKED_FRAME_SIZE;
    uintptr_t fp = (uintptr_t)__builtin_frame_address(1);
    return walkVM(ucontext, frames, max_depth, detail, pc, sp, fp, truncated);
  } else {
    StackFrame frame(ucontext);
    return walkVM(ucontext, frames, max_depth, detail, (const void*)frame.pc(), frame.sp(), frame.fp(), truncated);
  }
}

void StackWalker::checkFault(ProfiledThread* thrd) {
  VMThread *vm_thread = VMThread::current();
  if (vm_thread != NULL && sameStack(vm_thread->exception(), &vm_thread)) {
    if (thrd) {
      // going to longjmp out of the signal handler, reset the crash handler depth counter
      thrd->resetCrashHandler();
    }
    longjmp(*(jmp_buf *)vm_thread->exception(), 1);
  }
}
