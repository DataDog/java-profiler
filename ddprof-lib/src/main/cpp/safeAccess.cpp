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

#ifdef __APPLE__
    #if defined(__x86_64__)
      #define context_pc context_rip
    #elif defined(__aarch64__)
      #define DU3_PREFIX(s, m) __ ## s.__ ## m
      #define context_pc uc_mcontext->DU3_PREFIX(ss,pc)
    #endif
#else
    #if defined(__x86_64__)
      #define context_pc uc_mcontext.gregs[REG_RIP]
    #elif defined(__aarch64__)
      #define context_pc uc_mcontext.gregs[_REG_ELR]
    #endif
#endif

extern "C" char _SafeFetch32_continuation[] __attribute__ ((visibility ("hidden")));
extern "C" char _SafeFetch32_fault[] __attribute__ ((visibility ("hidden")));

bool SafeAccess::handle_safefetch(int sig, void* context) {
  ucontext_t* uc = (ucontext_t*)context;
  uintptr_t pc = uc->context_pc;
  if ((sig == SIGSEGV || sig == SIGBUS) && uc != nullptr) {
    if (pc == (uintptr_t)_SafeFetch32_fault) {
      uc->context_pc = (uintptr_t)_SafeFetch32_continuation;
      return true;
    }
  }
  return false;
}
