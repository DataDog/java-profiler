/*
 * Copyright 2025, 2026 Datadog, Inc
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
#include "counters.h"

#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <ucontext.h>
#ifdef DEBUG
#include "threadLocalData.h"  // ProfiledThread::currentSignalSafe / isProtected
#endif

extern "C" int safefetch32_cont(int* adr, int errValue);
extern "C" int64_t safefetch64_cont(int64_t* adr, int64_t errValue);

// safecopy_impl copies `len` bytes from `src` to `dst` one byte at a time and
// returns 1 on success. If any load from `src` faults, the signal handler
// redirects the pc anywhere in [safecopy_impl, safecopy_cont) to safecopy_cont,
// which returns 0. Both are leaf routines with no stack frame, so the redirect
// keeps the return address intact.
extern "C" int safecopy_impl(void* dst, const void* src, size_t len);
extern "C" int safecopy_cont(void* dst, const void* src, size_t len);

#ifdef DEBUG
// handle_safefetch protects safeCopy by treating any fault whose pc lands in
// [safecopy_impl, safecopy_cont) as a recoverable read fault. That range is
// only valid if the assembler/linker keeps safecopy_cont strictly above
// safecopy_impl (they are emitted adjacently in one asm block). A future
// toolchain change could in principle reorder them, collapsing the range to
// empty and silently disabling fault protection. Assert the invariant once at
// load time so such a regression aborts loudly at startup instead of turning
// safeCopy into an unprotected crash. Debug builds only: this is a
// toolchain-regression tripwire, not a runtime safety check.
__attribute__((constructor))
static void verify_safecopy_range() {
  if ((uintptr_t)safecopy_cont <= (uintptr_t)safecopy_impl) {
    fprintf(stderr,
            "FATAL: safecopy_cont (%p) is not above safecopy_impl (%p); "
            "safeCopy fault protection would be lost\n",
            (void*)safecopy_cont, (void*)safecopy_impl);
    abort();
  }
}
#endif // DEBUG

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

/**
 Loading a 32-bit/64-bit value from specific address, the errValue will be returned
 if the address is invalid.
 The load is protected by the 'handle_safefetch` signal handler, who sets next `pc`
 to `safefetch32_cont/safefetch64_cont`, upon returning from signal handler,
 `safefetch32_cont/safefetch64_cont` returns `errValue`
 **/
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
        .globl _safefetch64_impl
        .private_extern _safefetch64_impl
        _safefetch64_impl:
             movq (%rdi), %rax
             ret
        .globl _safefetch64_cont
        .private_extern _safefetch64_cont
        _safefetch64_cont:
            movq %rsi, %rax
            ret
        .globl _safecopy_impl
        .private_extern _safecopy_impl
        _safecopy_impl:
            xorl %ecx, %ecx
        Lsafecopy_loop:
            cmpq %rdx, %rcx
            jae Lsafecopy_done
            movzbl (%rsi,%rcx,1), %eax
            movb %al, (%rdi,%rcx,1)
            incq %rcx
            jmp Lsafecopy_loop
        Lsafecopy_done:
            movl $1, %eax
            ret
        .globl _safecopy_cont
        .private_extern _safecopy_cont
        _safecopy_cont:
            xorl %eax, %eax
            ret
    )");
  #else
    asm(R"(
        .text
        .globl safefetch32_impl
        .hidden safefetch32_impl
        .type safefetch32_impl, %function
        safefetch32_impl:
            movl (%rdi), %eax
            ret
        .globl safefetch32_cont
        .hidden safefetch32_cont
        .type safefetch32_cont, %function
        safefetch32_cont:
            movl %esi, %eax
            ret
        .globl safefetch64_impl
        .hidden safefetch64_impl
        .type safefetch64_impl, %function
        safefetch64_impl:
            movq (%rdi), %rax
            ret
        .globl safefetch64_cont
        .hidden safefetch64_cont
        .type safefetch64_cont, %function
        safefetch64_cont:
            movq %rsi, %rax
            ret
        .globl safecopy_impl
        .hidden safecopy_impl
        .type safecopy_impl, %function
        safecopy_impl:
            xorl %ecx, %ecx
        .Lsafecopy_loop:
            cmpq %rdx, %rcx
            jae .Lsafecopy_done
            movzbl (%rsi,%rcx,1), %eax
            movb %al, (%rdi,%rcx,1)
            incq %rcx
            jmp .Lsafecopy_loop
        .Lsafecopy_done:
            movl $1, %eax
            ret
        .globl safecopy_cont
        .hidden safecopy_cont
        .type safecopy_cont, %function
        safecopy_cont:
            xorl %eax, %eax
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
            mov      w0, w1
            ret
        .globl _safefetch64_impl
        .private_extern _safefetch64_impl
        _safefetch64_impl:
            ldr      x0, [x0]
            ret
        .globl _safefetch64_cont
        .private_extern _safefetch64_cont
        _safefetch64_cont:
            mov      x0, x1
            ret
        .globl _safecopy_impl
        .private_extern _safecopy_impl
        _safecopy_impl:
            mov      x3, xzr
        Lsafecopy_loop:
            cmp      x3, x2
            b.hs     Lsafecopy_done
            ldrb     w4, [x1, x3]
            strb     w4, [x0, x3]
            add      x3, x3, #1
            b        Lsafecopy_loop
        Lsafecopy_done:
            mov      w0, #1
            ret
        .globl _safecopy_cont
        .private_extern _safecopy_cont
        _safecopy_cont:
            mov      w0, #0
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
            mov      w0, w1
            ret
        .globl safefetch64_impl
        .hidden safefetch64_impl
        .type safefetch64_impl, %function
        safefetch64_impl:
            ldr      x0, [x0]
            ret
        .globl safefetch64_cont
        .hidden safefetch64_cont
        .type safefetch64_cont, %function
        safefetch64_cont:
            mov      x0, x1
            ret
        .globl safecopy_impl
        .hidden safecopy_impl
        .type safecopy_impl, %function
        safecopy_impl:
            mov      x3, xzr
        .Lsafecopy_loop:
            cmp      x3, x2
            b.hs     .Lsafecopy_done
            ldrb     w4, [x1, x3]
            strb     w4, [x0, x3]
            add      x3, x3, #1
            b        .Lsafecopy_loop
        .Lsafecopy_done:
            mov      w0, #1
            ret
        .globl safecopy_cont
        .hidden safecopy_cont
        .type safecopy_cont, %function
        safecopy_cont:
            mov      w0, #0
            ret
    )");
  #endif
#endif

#ifdef DEBUG
void SafeAccess::countIfLongjmpProtected(bool isCopy) {
  ProfiledThread* t = ProfiledThread::currentSignalSafe();  // never allocates
  if (t != nullptr && t->isProtected()) {
    Counters::increment(isCopy ? SAFECOPY_WHILE_PROTECTED
                               : SAFEFETCH_WHILE_PROTECTED);
  }
}
#endif

bool SafeAccess::safeCopy(void* dst, const void* src, size_t len) {
#ifdef DEBUG
  countIfLongjmpProtected(true);
#endif
  // The copy runs entirely inside the safecopy_impl assembly stub, which
  // reads `src` one byte at a time. If a load faults, handle_safefetch
  // redirects execution to safecopy_cont, which returns 0. Because the copy
  // is byte-granular it only ever touches bytes in [src, src+len) — there is
  // no over-read past the requested range and no alignment reasoning needed.
  // A fault mid-copy may leave up to len-1 bytes already written to `dst`.
  return safecopy_impl(dst, src, len) != 0;
}

bool SafeAccess::handle_safefetch(int sig, void* context) {
  ucontext_t* uc = (ucontext_t*)context;
  uintptr_t pc = uc->current_pc;
  if ((sig == SIGSEGV || sig == SIGBUS) && uc != nullptr) {
    if (pc == (uintptr_t)safefetch32_impl) {
      uc->current_pc = (uintptr_t)safefetch32_cont;
      Counters::increment(SAFEFETCH_FAILED);
      return true;
    } else if (pc == (uintptr_t)safefetch64_impl) {
      uc->current_pc = (uintptr_t)safefetch64_cont;
      Counters::increment(SAFEFETCH_FAILED);
      return true;
    } else if (pc >= (uintptr_t)safecopy_impl && pc < (uintptr_t)safecopy_cont) {
      // Unlike safefetch, the faulting load can be at any pc inside the copy
      // loop, so match the whole [safecopy_impl, safecopy_cont) range.
      uc->current_pc = (uintptr_t)safecopy_cont;
      Counters::increment(SAFECOPY_FAILED);
      return true;
    }
  }
  return false;
}

// NOINLINE implementations using safefetch infrastructure
// These provide stable function addresses for JVM patching in vmStructs.cpp
void* SafeAccess::load(void** ptr, void* default_value) {
  return loadPtr(ptr, default_value);
}

int32_t SafeAccess::load32(int32_t* ptr, int32_t default_value) {
#ifdef DEBUG
  countIfLongjmpProtected(false);
#endif
  int res = safefetch32_impl((int*)ptr, (int)default_value);
  return static_cast<int32_t>(res);
}

void* SafeAccess::loadPtr(void** ptr, void* default_value) {
#ifdef DEBUG
  countIfLongjmpProtected(false);
#endif
#if defined(__x86_64__) || defined(__aarch64__)
  int64_t res = safefetch64_impl((int64_t*)ptr, (int64_t)reinterpret_cast<uintptr_t>(default_value));
  return (void*)static_cast<uintptr_t>(res);
#elif defined(__i386__) || defined(__arm__) || defined(__thumb__)
  int res = safefetch32_impl((int*)ptr, (int)default_value);
  return (void*)res;
#endif
  return *ptr;
}
