/*
 * Copyright 2025 Datadog, Inc
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


#include "safeAccess.h"
#include <signal.h>
#include <ucontext.h>

extern "C" int safefetch32_cont(int* adr, int errValue);

#ifdef __APPLE__
    #if defined(__x86_64__)
      #define current_pc context_rip
    #elif defined(__aarch64__)
      #define DU3_PREFIX(s, m) __ ## s.__ ## m
      #define current_pc uc_mcontext->DU3_PREFIX(ss,pc)
    #endif
#else
    #if defined(__x86_64__)
      #define current_pc uc_mcontext.gregs[REG_RIP]
    #elif defined(__aarch64__)
      #define current_pc uc_mcontext.pc
    #endif
#endif

#if defined(__x86_64__)
  #ifdef __APPLE__
    asm(R"(
        .globl _safefetch32_impl
        .private_extern _safefetch32_impl
        _safefetch32_impl:
            movl (%rdi), %eax
            ret
        .globl _safefetch32_cont
        .private_extern _safefetch32_cont
        _safefetch32_cont:
            movl %esi, %eax
            ret
    )");
  #else
    asm(R"(
        .text
        .globl safefetch32_impl
        .hidden safefetch32_impl
        .type safefetch32_imp, %function
        safefetch32_impl:
            movl (%rdi), %eax
            ret
        .globl safefetch32_cont
        .hidden safefetch32_cont
        .type safefetch32_cont, %function
        safefetch32_cont:
            movl %esi, %eax
            ret
    )");
  #endif // __APPLE__
#elif defined(__aarch64__)
  #ifdef __APPLE__
    asm(R"(
        .globl _safefetch32_impl
        .private_extern _safefetch32_impl
        _safefetch32_impl:
            ldr      w0, [x0]
            ret
        .globl _safefetch32_cont
        .private_extern _safefetch32_cont
        _safefetch32_cont:
            mov      x0, x1
            ret
    )");
  #else
    asm(R"(
        .text
        .globl safefetch32_impl
        .hidden safefetch32_impl
        .type safefetch32_impl, %function
        safefetch32_impl:
            ldr      w0, [x0]
            ret
        .globl safefetch32_cont
        .hidden safefetch32_cont
        .type safefetch32_cont, %function
        safefetch32_cont:
            mov      x0, x1
            ret
    )");
  #endif
#endif

bool SafeAccess::handle_safefetch(int sig, void* context) {
  ucontext_t* uc = (ucontext_t*)context;
  uintptr_t pc = uc->current_pc;
  if ((sig == SIGSEGV || sig == SIGBUS) && uc != nullptr) {
    if (pc == (uintptr_t)safefetch32_impl) {
      uc->current_pc = (uintptr_t)safefetch32_cont;
      return true;
    }
  }
  return false;
}
