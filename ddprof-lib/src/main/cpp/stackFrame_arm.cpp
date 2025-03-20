/*
 * Copyright 2017 Andrei Pangin
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

#if defined(__arm__) || defined(__thumb__)

#include "stackFrame.h"
#include "vmStructs.h"
#include <errno.h>
#include <string.h>

#include "counters.h"
#include "tsc.h"

uintptr_t &StackFrame::pc() {
  return (uintptr_t &)_ucontext->uc_mcontext.arm_pc;
}

uintptr_t &StackFrame::sp() {
  return (uintptr_t &)_ucontext->uc_mcontext.arm_sp;
}

uintptr_t &StackFrame::fp() {
  return (uintptr_t &)_ucontext->uc_mcontext.arm_fp;
}

uintptr_t &StackFrame::retval() {
  return (uintptr_t &)_ucontext->uc_mcontext.arm_r0;
}

uintptr_t StackFrame::link() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_lr;
}

uintptr_t StackFrame::arg0() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_r0;
}

uintptr_t StackFrame::arg1() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_r1;
}

uintptr_t StackFrame::arg2() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_r2;
}

uintptr_t StackFrame::arg3() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_r3;
}

uintptr_t StackFrame::jarg0() {
  // Unimplemented
  return 0;
}

uintptr_t StackFrame::method() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_r9;
}

uintptr_t StackFrame::senderSP() {
  return (uintptr_t)_ucontext->uc_mcontext.arm_r4;
}

void StackFrame::ret() { pc() = link(); }

bool StackFrame::unwindStub(instruction_t *entry, const char *name,
                            uintptr_t &pc, uintptr_t &sp, uintptr_t &fp) {
  const u64 startTime = TSC::ticks();
  instruction_t *ip = (instruction_t *)pc;
  if (ip == entry || *ip == 0xe12fff1e || strncmp(name, "itable", 6) == 0 ||
      strncmp(name, "vtable", 6) == 0 ||
      strcmp(name, "InlineCacheBuffer") == 0) {
    pc = link();

    const u64 endTime = TSC::ticks();
    const u64 duration = TSC::ticks_to_millis(endTime - startTime);
    if (duration > 1) {
      Counters::increment(UNWINDING_STUB_TIME, duration);
    }
    return true;
  }

  const u64 endTime = TSC::ticks();
  u64 duration = TSC::ticks_to_millis(endTime - startTime);
  if (duration > 1) {
    Counters::increment(UNWINDING_STUB_TIME, duration);
  }
  return false;
}

bool StackFrame::unwindCompiled(NMethod *nm, uintptr_t &pc, uintptr_t &sp,
                                uintptr_t &fp) {
  const u64 startTime = TSC::ticks();
  instruction_t *ip = (instruction_t *)pc;
  instruction_t *entry = (instruction_t *)nm->entry();
  if (ip > entry && ip <= entry + 4 && (*ip & 0xffffff00) == 0xe24dd000) {
    //    push  {r11, lr}
    //    mov   r11, sp (optional)
    // -> sub   sp, sp, #offs
    fp = ((uintptr_t *)sp)[0];
    pc = ((uintptr_t *)sp)[1];
    sp += 8;

    const u64 endTime = TSC::ticks();
    const u64 duration = TSC::ticks_to_millis(endTime - startTime);
    if (duration > 1) {
      Counters::increment(UNWINDING_COMPILED_TIME, duration);
    }
    return true;
  } else if (*ip == 0xe8bd4800) {
    //    add   sp, sp, #offs
    // -> pop   {r11, lr}
    fp = ((uintptr_t *)sp)[0];
    pc = ((uintptr_t *)sp)[1];
    sp += 8;

    const u64 endTime = TSC::ticks();
    const u64 duration = TSC::ticks_to_millis(endTime - startTime);
    if (duration > 1) {
      Counters::increment(UNWINDING_COMPILED_TIME, duration);
    }
    return true;
  }
  pc = link();

  const u64 endTime = TSC::ticks();
  const u64 duration = TSC::ticks_to_millis(endTime - startTime);
  if (duration > 1) {
    Counters::increment(UNWINDING_COMPILED_TIME, duration);
  }
  return true;
}

void StackFrame::adjustSP(const void *entry, const void *pc, uintptr_t &sp) {
  // Not needed
}

bool StackFrame::unwindAtomicStub(const void*& pc) {
  // Not needed
  return false;
}

bool StackFrame::skipFaultInstruction() { return false; }

bool StackFrame::checkInterruptedSyscall() {
  return retval() == (uintptr_t)-EINTR;
}

bool StackFrame::isSyscall(instruction_t *pc) {
  // swi #0
  return *pc == 0xef000000;
}

#endif // defined(__arm__) || defined(__thumb__)
