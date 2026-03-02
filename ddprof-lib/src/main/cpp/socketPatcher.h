/*
 * Copyright 2026, Datadog, Inc.
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

#ifndef _SOCKETPATCHER_H
#define _SOCKETPATCHER_H

#include "codeCache.h"
#include "spinLock.h"

#ifdef __linux__

static const int MAX_SOCKET_PATCHED_LIBS = 16;

// Stores the set of PLT entries patched for a single library.
// Each entry holds the PLT location and the original function pointer
// for one of the six intercepted socket functions.
typedef struct _socketPatchSet {
  CodeCache* _lib;
  void** _locations[6];  // recv, send, recvfrom, sendto, readv, writev
  void*  _originals[6];
} SocketPatchSet;

// Patches PLT entries for socket I/O functions (recv, send, recvfrom, sendto,
// readv, writev) in Netty native transport libraries. Hook functions record
// NativeSocketEvent entries to JFR via the profiler's recording pipeline.
//
// Only libraries whose basename contains "libnetty_transport_native" are
// patched. The profiler's own library is never patched — hook functions
// resolve to real libc symbols through the profiler's unpatched PLT.
class SocketPatcher {
private:
  static SpinLock       _lock;
  static SocketPatchSet _patched_libs[MAX_SOCKET_PATCHED_LIBS];
  static int            _size;

  static void patch_library_unlocked(CodeCache* lib);

public:
  static bool isNettyNativeLibrary(const char* name);
  static void patch_libraries();
  static void unpatch_libraries();
};

#else

class SocketPatcher {
public:
  static void patch_libraries() { }
  static void unpatch_libraries() { }
};

#endif

#endif // _SOCKETPATCHER_H
