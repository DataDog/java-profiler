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

#ifndef _STACKFRAME_H
#define _STACKFRAME_H

#include "arch.h"
#include <stdint.h>
#include <ucontext.h>

class NMethod;

class StackFrame {
private:
  ucontext_t *_ucontext;

  static bool withinCurrentStack(uintptr_t address) {
    // Check that the address is not too far from the stack pointer of current
    // context
    void *real_sp;
    return address - (uintptr_t)&real_sp <= 0xffff;
  }

public:
  explicit StackFrame(void *ucontext) { _ucontext = (ucontext_t *)ucontext; }

  void restore(uintptr_t saved_pc, uintptr_t saved_sp, uintptr_t saved_fp) {
    if (_ucontext != NULL) {
      pc() = saved_pc;
      sp() = saved_sp;
      fp() = saved_fp;
    }
  }

  uintptr_t stackAt(int slot) { return ((uintptr_t *)sp())[slot]; }

  uintptr_t &pc();
  uintptr_t &sp();
  uintptr_t &fp();

  uintptr_t &retval();
  uintptr_t link();
  uintptr_t arg0();
  uintptr_t arg1();
  uintptr_t arg2();
  uintptr_t arg3();
  uintptr_t jarg0();
  uintptr_t method();
  uintptr_t senderSP();

  void ret();

  bool unwindStub(instruction_t *entry, const char *name) {
    return unwindStub(entry, name, pc(), sp(), fp());
  }

  bool unwindCompiled(NMethod *nm) {
    return unwindCompiled(nm, pc(), sp(), fp());
  }

  bool unwindStub(instruction_t *entry, const char *name, uintptr_t &pc,
                  uintptr_t &sp, uintptr_t &fp);
  bool unwindCompiled(NMethod *nm, uintptr_t &pc, uintptr_t &sp, uintptr_t &fp);
  bool unwindAtomicStub(const void*& pc);

  void adjustSP(const void *entry, const void *pc, uintptr_t &sp);

  bool skipFaultInstruction();

  bool checkInterruptedSyscall();

  // Check if PC points to a syscall instruction
  static bool isSyscall(instruction_t *pc);
};

class StackFrameHolder {
 private:
  StackFrame _stack_frame;
  uintptr_t _sp;
  uintptr_t _fp;
  uintptr_t _pc;
 public:
  StackFrameHolder(void *ucontext) : _stack_frame(ucontext) {
    _sp = _stack_frame.sp();
    _fp = _stack_frame.fp();
    _pc = _stack_frame.pc();
  }

  ~StackFrameHolder() {
    _stack_frame.restore(_pc, _sp, _fp);
  }
  StackFrameHolder(const StackFrameHolder&) = delete;
  StackFrameHolder& operator=(const StackFrameHolder&) = delete;

  uintptr_t &fp() {
    return _stack_frame.fp();
  }

  uintptr_t &sp() {
    return _stack_frame.sp();
  }

  uintptr_t &pc() {
    return _stack_frame.pc();
  }

  void adjustSP(const void *entry, const void *pc, uintptr_t &sp) {
    _stack_frame.adjustSP(entry, pc, sp);
  }

  bool unwindAtomicStub(const void*& pc) {
    return _stack_frame.unwindAtomicStub(pc);
  }

  bool unwindCompiled(NMethod *nm, uintptr_t &pc, uintptr_t &sp, uintptr_t &fp) {
    return _stack_frame.unwindCompiled(nm, pc, sp, fp);
  }

  uintptr_t method() {
    return _stack_frame.method();
  }

  uintptr_t senderSP() {
    return _stack_frame.senderSP();
  }

  bool unwindStub(instruction_t *entry, const char *name, uintptr_t &pc,
                    uintptr_t &sp, uintptr_t &fp) {
                    return _stack_frame.unwindStub(entry, name, pc, sp, fp);
  }

  uintptr_t link() {
    return _stack_frame.link();
  }
};

#endif // _STACKFRAME_H
