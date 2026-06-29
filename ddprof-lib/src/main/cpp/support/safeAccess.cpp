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
extern "C" int64_t safefetch64_cont(int64_t* adr, int64_t errValue);

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
    )");
  #endif
#endif

bool SafeAccess::safeCopy(void* dst, const void* src, size_t len) {
  // Two-sentinel pattern (same as isReadable): a real-data word may equal
  // one sentinel by chance, but not both — if both fetches return their
  // sentinel, the access truly faulted.
  //
  // All safefetch32 loads issued here use 4-byte-aligned addresses. Pages
  // are 4 KiB (or 16 KiB on Apple Silicon), both divisible by 4, so an
  // aligned 4-byte load never spans a page boundary. The only fault
  // possible is when the aligned address itself lies in an unmapped page;
  // we never spuriously fault on an over-read past `src + len`.
  static const int32_t SENT_A = (int32_t)0x55AA55AA;
  static const int32_t SENT_B = (int32_t)0xAA55AA55;
  uint8_t* d = (uint8_t*)dst;
  const uint8_t* s = (const uint8_t*)src;
  size_t i = 0;

  // Front fixup: if `src` is not 4-byte aligned, fetch at the previous
  // aligned address (1..3 bytes before src). That address lies in the
  // same 4-byte word as src — and since pages are 4-byte aligned, in
  // the same page as src. The leading k bytes of the fetched word lie
  // before the caller's range and are discarded via the +k offset; they
  // never reach `dst`.
  size_t k = (uintptr_t)s & 3u;
  if (k != 0 && i < len) {
    int32_t* aligned = (int32_t*)(s - k);
    int32_t v1 = safefetch32_impl(aligned, SENT_A);
    int32_t v2 = safefetch32_impl(aligned, SENT_B);
    if (v1 == SENT_A && v2 == SENT_B) {
      return false;
    }
    size_t take = (4 - k < len) ? (4 - k) : len;
    memcpy(d, ((const uint8_t*)&v1) + k, take);
    i = take;
  }

  // Middle + tail: (s + i) is now 4-byte aligned. The final iteration may
  // load up to 3 over-read bytes past `src + len`, but those bytes sit in
  // the same 4-byte-aligned word and therefore the same page as the bytes
  // we actually wanted — never a fault from the over-read alone.
  while (i < len) {
    int32_t* aligned = (int32_t*)(s + i);
    int32_t v1 = safefetch32_impl(aligned, SENT_A);
    int32_t v2 = safefetch32_impl(aligned, SENT_B);
    if (v1 == SENT_A && v2 == SENT_B) {
      return false;
    }
    size_t chunk = (len - i >= 4) ? 4 : (len - i);
    memcpy(d + i, &v1, chunk);  // memcpy from local — no UAF risk
    i += chunk;
  }
  return true;
}

bool SafeAccess::handle_safefetch(int sig, void* context) {
  ucontext_t* uc = (ucontext_t*)context;
  uintptr_t pc = uc->current_pc;
  if ((sig == SIGSEGV || sig == SIGBUS) && uc != nullptr) {
    if (pc == (uintptr_t)safefetch32_impl) {
      uc->current_pc = (uintptr_t)safefetch32_cont;
      return true;
    } else if (pc == (uintptr_t)safefetch64_impl) {
      uc->current_pc = (uintptr_t)safefetch64_cont;
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
  int res = safefetch32_impl((int*)ptr, (int)default_value);
  return static_cast<int32_t>(res);
}

void* SafeAccess::loadPtr(void** ptr, void* default_value) {
#if defined(__x86_64__) || defined(__aarch64__)
  int64_t res = safefetch64_impl((int64_t*)ptr, (int64_t)reinterpret_cast<uintptr_t>(default_value));
  return (void*)static_cast<uintptr_t>(res);
#elif defined(__i386__) || defined(__arm__) || defined(__thumb__)
  int res = safefetch32_impl((int*)ptr, (int)default_value);
  return (void*)res;
#endif
  return *ptr;
}
