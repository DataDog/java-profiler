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
#include <cassert>
#include <stdint.h>

extern "C" int safefetch32_impl(int* adr, int errValue);
extern "C" int64_t safefetch64_impl(int64_t* adr, int64_t errValue);

#ifdef __clang__
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE __attribute__((noinline, noclone))
#endif
#define NOADDRSANITIZE __attribute__((no_sanitize("address")))

class SafeAccess {
public:

  static inline int safeFetch32(int* ptr, int errorValue) {
    return safefetch32_impl(ptr, errorValue);
  }

  static inline int64_t safeFetch64(int64_t* ptr, int64_t errorValue) {
    return safefetch64_impl(ptr, errorValue);
  }

  static bool handle_safefetch(int sig, void* context);

  static inline void *load(void **ptr, void* default_value = nullptr) {
    return loadPtr(ptr, nullptr);
  }

  static inline u32 load32(u32 *ptr, u32 default_value = 0) {
    int res = safefetch32_impl((int*)ptr, (int)default_value);
    return static_cast<u32>(res);
  }

  static inline void *loadPtr(void** ptr, void* default_value) {
  #if defined(__x86_64__) || defined(__aarch64__)
    int64_t res = safefetch64_impl((int64_t*)ptr, (int64_t)reinterpret_cast<uintptr_t>(default_value));
    return (void*)static_cast<uintptr_t>(res);
  #elif defined(__i386__) || defined(__arm__) || defined(__thumb__)
    int res = safefetch32_impl((int*)ptr, (int)default_value);
    return (void*)res;
  #endif
    return *ptr;
  }
};

#endif // _SAFEACCESS_H
