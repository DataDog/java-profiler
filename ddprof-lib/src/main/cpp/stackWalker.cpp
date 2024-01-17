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

#include <setjmp.h>
#include "stackWalker.h"
#include "safeAccess.h"
#include "dwarf.h"
#include "profiler.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "vmStructs.h"


const uintptr_t SAME_STACK_DISTANCE = 8192;
const uintptr_t MAX_WALK_SIZE = 0x100000;
const intptr_t MAX_FRAME_SIZE = 0x40000;
const intptr_t MAX_INTERPRETER_FRAME_SIZE = 0x1000;
const intptr_t DEAD_ZONE = 0x1000;


static inline bool aligned(uintptr_t ptr) {
    return (ptr & (sizeof(uintptr_t) - 1)) == 0;
}

static inline bool inDeadZone(const void* ptr) {
    return ptr < (const void*)DEAD_ZONE || ptr > (const void*)-DEAD_ZONE;
}

static inline bool sameStack(void* hi, void* lo) {
    return (uintptr_t)hi - (uintptr_t)lo < SAME_STACK_DISTANCE;
}

static inline void fillFrame(ASGCT_CallFrame& frame, ASGCT_CallFrameType type, const char* name) {
    frame.bci = type;
    frame.method_id = (jmethodID)name;
}

static inline void fillFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci, jmethodID method) {
    frame.bci = FrameType::encode(type, bci);
    frame.method_id = method;
}

static jmethodID getMethodId(VMMethod* method) {
    if (!inDeadZone(method) && aligned((uintptr_t)method)) {
        jmethodID method_id = method->id();
        if (!inDeadZone(method_id) && aligned((uintptr_t)method_id) && *(VMMethod**)method_id == method) {
            return method_id;
        }
    }
    return NULL;
}


int StackWalker::walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool *truncated) {
    const void* pc;
    uintptr_t fp;
    uintptr_t sp;
    uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

    if (ucontext == NULL) {
        pc = __builtin_return_address(0);
        fp = (uintptr_t)__builtin_frame_address(1);
        sp = (uintptr_t)__builtin_frame_address(0);
    } else {
        StackFrame frame(ucontext);
        pc = (const void*)frame.pc();
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
        if (CodeHeap::contains(pc)) {
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

        pc = stripPointer(SafeAccess::load((void**)fp + FRAME_PC_SLOT));
        if (inDeadZone(pc)) {
            *truncated = pc != NULL;
            break;
        }

        sp = fp + (FRAME_PC_SLOT + 1) * sizeof(void*);
        fp = *(uintptr_t*)fp;
    }

    return depth;
}

int StackWalker::walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool *truncated) {
    const void* pc;
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
        pc = (const void*)frame.pc();
        fp = frame.fp();
        sp = frame.sp();
    }

    int depth = 0;
    Profiler* profiler = Profiler::instance();

    *truncated = false;

    // Walk until the bottom of the stack or until the first Java frame
    while (true) {
        if (depth == max_depth) {
            *truncated = true;
            break;
        }
        if (CodeHeap::contains(pc)) {
            java_ctx->set(pc, sp, fp);
            break;
        }

        callchain[depth++] = pc;
        prev_sp = sp;

        FrameDesc* f;
        CodeCache* cc = profiler->findLibraryByAddress(pc);
        if (cc == NULL || (f = cc->findFrameDesc(pc)) == NULL) {
            f = &FrameDesc::default_frame;
        }

        u8 cfa_reg = (u8)f->cfa;
        int cfa_off = f->cfa >> 8;
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
            pc = (const char*)pc + (f->fp_off >> 1);
        } else {
            if (f->fp_off != DW_SAME_FP && f->fp_off < MAX_FRAME_SIZE && f->fp_off > -MAX_FRAME_SIZE) {
                fp = (uintptr_t)SafeAccess::load((void**)(sp + f->fp_off));
            }
            if (EMPTY_FRAME_SIZE > 0 || cfa_off != 0) {
                // x86 or AArch64 non-default frame
                pc = stripPointer(SafeAccess::load((void**)(sp + f->pc_off)));
            } else if (f->fp_off != DW_SAME_FP) {
                // AArch64 default_frame
                pc = stripPointer(SafeAccess::load((void**)(sp + f->pc_off)));
                sp = fp;
            } else if (depth <= 1) {
                pc = (const void*)frame.link();
            } else {
                // Stack bottom
                break;
            }
        }

        if (inDeadZone(pc)) {
            *truncated = pc != NULL;
            break;
        }
    }

    return depth;
}

int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth) {
    const void* pc;
    uintptr_t fp;
    uintptr_t sp;
    uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

    StackFrame frame(ucontext);
    if (ucontext == NULL) {
        pc = __builtin_return_address(0);
        fp = (uintptr_t)__builtin_frame_address(1);
        sp = (uintptr_t)__builtin_frame_address(0);
    } else {
        pc = (const void*)frame.pc();
        fp = frame.fp();
        sp = frame.sp();
    }

    Profiler* profiler = Profiler::instance();
    int bcp_offset = InterpreterFrame::bcp_offset();

    jmp_buf crash_protection_ctx;
    VMThread* vm_thread = VMThread::current();
    void* saved_exception = vm_thread != NULL ? vm_thread->exception() : NULL;

    // Should be preserved across setjmp/longjmp
    volatile int depth = 0;

    if (vm_thread != NULL) {
        vm_thread->exception() = &crash_protection_ctx;
        if (setjmp(crash_protection_ctx) != 0) {
            vm_thread->exception() = saved_exception;
            if (depth < max_depth) {
                fillFrame(frames[depth++], BCI_ERROR, "break_not_walkable");
            }
            return depth;
        }
    }

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < max_depth) {
        if (CodeHeap::contains(pc)) {
            NMethod* nm = CodeHeap::findNMethod(pc);
            if (nm == NULL) {
                fillFrame(frames[depth++], BCI_ERROR, "unknown_nmethod");
            } else if (nm->isNMethod()) {
                int level = nm->level();
                FrameTypeId type = level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;
                fillFrame(frames[depth++], type, 0, nm->method()->id());

                if (nm->isFrameCompleteAt(pc)) {
                    int scope_offset = nm->findScopeOffset(pc);
                    if (scope_offset > 0) {
                        depth--;
                        ScopeDesc scope(nm);
                        do {
                            scope_offset = scope.decode(scope_offset);
                            type = scope_offset > 0 ? FRAME_INLINED :
                                   level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;
                            fillFrame(frames[depth++], type, scope.bci(), scope.method()->id());
                        } while (scope_offset > 0 && depth < max_depth);
                    }

                    sp += nm->frameSize() * sizeof(void*);
                    fp = ((uintptr_t*)sp)[-FRAME_PC_SLOT - 1];
                    pc = ((const void**)sp)[-FRAME_PC_SLOT];
                    continue;
                } else if (frame.unwindCompiled((instruction_t*)nm->entry(), (uintptr_t&)pc, sp, fp)
                               && profiler->isAddressInCode(pc)) {
                    continue;
                }

                fillFrame(frames[depth++], BCI_ERROR, "break_compiled");
                break;
            } else if (nm->isInterpreter()) {
                if (vm_thread != NULL && vm_thread->inDeopt()) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_deopt");
                    break;
                }

                bool is_plausible_interpreter_frame = !inDeadZone((const void*)fp) && aligned(fp)
                    && sp > fp - MAX_INTERPRETER_FRAME_SIZE
                    && sp < fp + bcp_offset * sizeof(void*);

                if (is_plausible_interpreter_frame) {
                    VMMethod* method = ((VMMethod**)fp)[InterpreterFrame::method_offset];
                    jmethodID method_id = getMethodId(method);
                    if (method_id != NULL) {
                        const char* bytecode_start = method->bytecode();
                        const char* bcp = ((const char**)fp)[bcp_offset];
                        int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                        fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);

                        sp = ((uintptr_t*)fp)[InterpreterFrame::sender_sp_offset];
                        pc = stripPointer(((void**)fp)[FRAME_PC_SLOT]);
                        fp = *(uintptr_t*)fp;
                        continue;
                    }
                }

                if (depth == 0) {
                    VMMethod* method = (VMMethod*)frame.method();
                    jmethodID method_id = getMethodId(method);
                    if (method_id != NULL) {
                        fillFrame(frames[depth++], FRAME_INTERPRETED, 0, method_id);

                        if (is_plausible_interpreter_frame) {
                            pc = stripPointer(((void**)fp)[FRAME_PC_SLOT]);
                            sp = frame.senderSP();
                            fp = *(uintptr_t*)fp;
                        } else {
                            pc = stripPointer(*(void**)sp);
                            sp = frame.senderSP();
                        }
                        continue;
                    }
                }

                fillFrame(frames[depth++], BCI_ERROR, "break_interpreted");
                break;
            } else {
                CodeBlob* stub = profiler->findRuntimeStub(pc);
                const void* start = stub != NULL ? stub->_start : nm->code();
                const char* name = stub != NULL ? stub->_name : nm->name();
                fillFrame(frames[depth++], BCI_NATIVE_FRAME, name);

                if (frame.unwindStub((instruction_t*)start, name, (uintptr_t&)pc, sp, fp)) {
                    continue;
                }

                if (depth > 1 && nm->frameSize() > 0) {
                    sp += nm->frameSize() * sizeof(void*);
                    fp = ((uintptr_t*)sp)[-FRAME_PC_SLOT - 1];
                    pc = ((const void**)sp)[-FRAME_PC_SLOT];
                    continue;
                }
            }
        } else {
            fillFrame(frames[depth++], BCI_NATIVE_FRAME, profiler->findNativeMethod(pc));
        }

        FrameDesc* f;
        CodeCache* cc = profiler->findLibraryByAddress(pc);
        if (cc == NULL || (f = cc->findFrameDesc(pc)) == NULL) {
            f = &FrameDesc::default_frame;
        }

        uintptr_t prev_sp = sp;

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
            break;
        }

        // Stack pointer must be word aligned
        if (!aligned(sp)) {
            break;
        }

        if (f->fp_off & DW_PC_OFFSET) {
            pc = (const char*)pc + (f->fp_off >> 1);
        } else {
            if (f->fp_off != DW_SAME_FP && f->fp_off < MAX_FRAME_SIZE && f->fp_off > -MAX_FRAME_SIZE) {
                fp = *(uintptr_t*)(sp + f->fp_off);
            }
            if (EMPTY_FRAME_SIZE > 0 || cfa_off != 0) {
                // x86 or AArch64 non-default frame
                pc = stripPointer(*(void**)(sp + f->pc_off));
            } else if (f->fp_off != DW_SAME_FP) {
                // AArch64 default_frame
                pc = stripPointer(*(void**)(sp + f->pc_off));
                sp = fp;
            } else if (depth <= 1) {
                pc = (const void*)frame.link();
            } else {
                // Stack bottom
                break;
            }
        }

        if (inDeadZone(pc)) {
            break;
        }
    }

    if (vm_thread != NULL) vm_thread->exception() = saved_exception;

    return depth;
}

void StackWalker::checkFault() {
    VMThread* vm_thread = VMThread::current();
    if (vm_thread != NULL && sameStack(vm_thread->exception(), &vm_thread)) {
        longjmp(*(jmp_buf*)vm_thread->exception(), 1);
    }
}
