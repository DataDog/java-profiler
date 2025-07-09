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

SafeAccess::SafeFetch32 SafeAccess::_safeFetch32Func = nullptr;

void SafeAccess::initSafeFetch(CodeCache* libjvm) {
  // Hotspot JVM's safefetch implementation appears better, e.g. it actually returns errorValue,
  // when the address is invalid. let's use it whenever possible.
  // When the methods are not available, fallback to SafeAccess::load32() implementation.
  _safeFetch32Func = (SafeFetch32)libjvm->findSymbol("SafeFetch32_impl");
  if (_safeFetch32Func == nullptr && !WX_MEMORY) {
    // jdk11 stub implementation other than Macosx/aarch64
    void** entry = (void**)libjvm->findSymbol("_ZN12StubRoutines18_safefetch32_entryE");
    if (entry != nullptr && *entry != nullptr) {
      _safeFetch32Func = (SafeFetch32)*entry;
    }
  }
  // Fallback
  if (_safeFetch32Func == nullptr) {
    _safeFetch32Func = (SafeFetch32)load32;
  }
}
