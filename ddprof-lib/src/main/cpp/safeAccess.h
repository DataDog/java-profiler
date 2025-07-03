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

#ifndef _SAFEACCESS_H
#define _SAFEACCESS_H

#include "arch_dd.h"
#include "codeCache.h"
#include <stdint.h>

#ifdef __clang__
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE __attribute__((noinline, noclone))
#endif
#define NOADDRSANITIZE __attribute__((no_sanitize("address")))

class SafeAccess {
private:
   typedef int (*SafeFetch32)(int* ptr, int defaultValue);
   static SafeFetch32 _safeFetch32Func;

public:
  static void initSafeFetch(CodeCache* libjvm);

  static bool hasSafeFetch() {
    return _safeFetch32Func != nullptr;
  }

  static int safeFetch(int* ptr, int defaultValue) {
    if (_safeFetch32Func != nullptr) {
      return _safeFetch32Func(ptr, defaultValue);
    } else {
      return defaultValue;
    }
  }

  NOINLINE NOADDRSANITIZE __attribute__((aligned(16))) static void *load(void **ptr) {
    return *ptr;
  }

  NOINLINE NOADDRSANITIZE __attribute__((aligned(16))) static u32 load32(u32 *ptr,
                                                          u32 default_value) {
    return *ptr;
  }

  NOINLINE NOADDRSANITIZE __attribute__((aligned(16))) static void *
  loadPtr(void **ptr, void *default_value) {
    return *ptr;
  }

  NOADDRSANITIZE static uintptr_t skipLoad(uintptr_t pc) {
    if (pc - (uintptr_t)load < sizeSafeLoadFunc) {
#if defined(__x86_64__)
      return *(u16 *)pc == 0x8b48 ? 3 : 0; // mov rax, [reg]
#elif defined(__i386__)
      return *(u8 *)pc == 0x8b ? 2 : 0; // mov eax, [reg]
#elif defined(__arm__) || defined(__thumb__)
      return (*(instruction_t *)pc & 0x0e50f000) == 0x04100000
                 ? 4
                 : 0; // ldr r0, [reg]
#elif defined(__aarch64__)
      return (*(instruction_t *)pc & 0xffc0001f) == 0xf9400000
                 ? 4
                 : 0; // ldr x0, [reg]
#else
      return sizeof(instruction_t);
#endif
    }
    return 0;
  }

  static uintptr_t skipLoadArg(uintptr_t pc) {
#if defined(__aarch64__)
    if ((pc - (uintptr_t)load32) < sizeSafeLoadFunc ||
        (pc - (uintptr_t)loadPtr) < sizeSafeLoadFunc) {
      return 4;
    }
#endif
    return 0;
  }
#ifndef __SANITIZE_ADDRESS__
  constexpr static size_t sizeSafeLoadFunc = 16;
#else
  // asan significantly increases the size of the load function
  // checking disassembled code can help adjust the value
  // gdb --batch -ex 'disas _ZN10SafeAccess4loadEPPv' ./elfparser_ut
  // I see that the functions can also have a 156 bytes size for the load32
  // and 136 for the loadPtr functions
  constexpr static inline size_t sizeSafeLoadFunc = 132;
#endif
};

#endif // _SAFEACCESS_H
