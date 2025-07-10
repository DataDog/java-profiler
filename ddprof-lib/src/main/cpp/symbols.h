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

#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#include "codeCache.h"
#include "mutex.h"

class Symbols {
private:
  static Mutex _parse_lock;
  static bool _have_kernel_symbols;
  static bool _libs_limit_reported;

public:
  static void parseKernelSymbols(CodeCache *cc);
  static void parseLibraries(CodeCacheArray *array, bool kernel_symbols);
  // The clear function is mainly for test purposes
  // There are internal caches that are not associated to the array
  static void clearParsingCaches();
  static bool haveKernelSymbols() { return _have_kernel_symbols; }

  // Some symbols are always roots - eg. no unwinding should be attempted once they are encountered
  static bool isRootSymbol(const void* address);
};

#endif // _SYMBOLS_H
