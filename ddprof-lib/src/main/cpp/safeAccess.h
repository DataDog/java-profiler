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

#include "arch.h"
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

  /**
   * Safely reads a 32-bit value from the given address.
   *
   * <p>CRITICAL: This function MUST NOT be inlined. The safefetch mechanism relies on
   * faults occurring at the exact address of safefetch32_impl. If this function is
   * inlined, the compiler may optimize the load into the caller's code, bypassing
   * the fault protection in handle_safefetch().
   *
   * @param ptr Address to read from (may be invalid)
   * @param errorValue Value to return if the read faults
   * @return The value at ptr, or errorValue if the read faults
   */
  NOINLINE
  static int safeFetch32(int* ptr, int errorValue) {
    return safefetch32_impl(ptr, errorValue);
  }

  /**
   * Safely reads a 64-bit value from the given address.
   *
   * <p>CRITICAL: This function MUST NOT be inlined. See safeFetch32 for details.
   */
  NOINLINE
  static int64_t safeFetch64(int64_t* ptr, int64_t errorValue) {
    return safefetch64_impl(ptr, errorValue);
  }

  static bool handle_safefetch(int sig, void* context);

  // NOINLINE functions with stable addresses for JVM patching (vmStructs.cpp)
  NOINLINE __attribute__((aligned(16)))
  static void *load(void **ptr, void* default_value = nullptr);

  NOINLINE __attribute__((aligned(16)))
  static int32_t load32(int32_t *ptr, int32_t default_value = 0);

  NOINLINE __attribute__((aligned(16)))
  static void *loadPtr(void** ptr, void* default_value);
};

#endif // _SAFEACCESS_H
