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

#include "socketPatcher.h"

#ifdef __linux__
#include "common.h"
#include "context.h"
#include "event.h"
#include "guards.h"
#include "libraries.h"
#include "log.h"
#include "profiler.h"
#include "tsc.h"

#include <string.h>
#include <sys/socket.h>
#include <sys/uio.h>

SpinLock       SocketPatcher::_lock;
SocketPatchSet SocketPatcher::_patched_libs[MAX_SOCKET_PATCHED_LIBS];
int            SocketPatcher::_size = 0;

// Index positions in SocketPatchSet arrays — must match ImportId order
enum SocketFuncIndex {
  SF_RECV = 0,
  SF_SEND = 1,
  SF_RECVFROM = 2,
  SF_SENDTO = 3,
  SF_READV = 4,
  SF_WRITEV = 5,
};

static void recordEvent(int fd, u64 bytes, u32 operation, u64 start) {
  u64 end = TSC::ticks();
  NativeSocketEvent event;
  event._start = start;
  event._end = end;
  event._fd = fd;
  event._bytes = bytes;
  event._operation = operation;
  Profiler::instance()->recordNativeSocketEvent(&event);
}

// --- Hook functions ---
// Each hook: capture start ticks, call real function (via profiler's own PLT),
// record event on success. The real libc functions resolve through the
// profiler library's unpatched PLT entries.

static ssize_t recv_hook(int fd, void* buf, size_t len, int flags) {
  u64 start = TSC::ticks();
  ssize_t ret = recv(fd, buf, len, flags);
  if (ret > 0) {
    recordEvent(fd, (u64)ret, SOCKET_OP_RECV, start);
  }
  return ret;
}

static ssize_t send_hook(int fd, const void* buf, size_t len, int flags) {
  u64 start = TSC::ticks();
  ssize_t ret = send(fd, buf, len, flags);
  if (ret > 0) {
    recordEvent(fd, (u64)ret, SOCKET_OP_SEND, start);
  }
  return ret;
}

static ssize_t recvfrom_hook(int fd, void* buf, size_t len, int flags,
                             struct sockaddr* src_addr, socklen_t* addrlen) {
  u64 start = TSC::ticks();
  ssize_t ret = recvfrom(fd, buf, len, flags, src_addr, addrlen);
  if (ret > 0) {
    recordEvent(fd, (u64)ret, SOCKET_OP_RECVFROM, start);
  }
  return ret;
}

static ssize_t sendto_hook(int fd, const void* buf, size_t len, int flags,
                           const struct sockaddr* dest_addr, socklen_t addrlen) {
  u64 start = TSC::ticks();
  ssize_t ret = sendto(fd, buf, len, flags, dest_addr, addrlen);
  if (ret > 0) {
    recordEvent(fd, (u64)ret, SOCKET_OP_SENDTO, start);
  }
  return ret;
}

// readv/writev are generic I/O syscalls that work on any fd type (sockets,
// pipes, files). We only patch them inside Netty native transport libraries
// where they are used exclusively for socket I/O. The rare false positive
// (e.g. Netty's internal wakeup pipe) is acceptable — it avoids a getsockopt()
// syscall on every call that would double the syscall cost.
static ssize_t readv_hook(int fd, const struct iovec* iov, int iovcnt) {
  u64 start = TSC::ticks();
  ssize_t ret = readv(fd, iov, iovcnt);
  if (ret > 0) {
    recordEvent(fd, (u64)ret, SOCKET_OP_READV, start);
  }
  return ret;
}

static ssize_t writev_hook(int fd, const struct iovec* iov, int iovcnt) {
  u64 start = TSC::ticks();
  ssize_t ret = writev(fd, iov, iovcnt);
  if (ret > 0) {
    recordEvent(fd, (u64)ret, SOCKET_OP_WRITEV, start);
  }
  return ret;
}

// Hook function pointers indexed by SocketFuncIndex
static void* const _hook_funcs[] = {
  (void*)recv_hook,
  (void*)send_hook,
  (void*)recvfrom_hook,
  (void*)sendto_hook,
  (void*)readv_hook,
  (void*)writev_hook,
};

// ImportId values for each socket function, indexed by SocketFuncIndex
static const ImportId _import_ids[] = {
  im_recv, im_send, im_recvfrom, im_sendto, im_readv, im_writev,
};

bool SocketPatcher::isNettyNativeLibrary(const char* name) {
  if (name == nullptr) return false;
  // Find basename
  const char* base = strrchr(name, '/');
  base = (base != nullptr) ? base + 1 : name;
  return strstr(base, "libnetty_transport_native") != nullptr;
}

void SocketPatcher::patch_library_unlocked(CodeCache* lib) {
  if (!isNettyNativeLibrary(lib->name())) {
    return;
  }

  // Check if already patched
  for (int i = 0; i < _size; i++) {
    if (_patched_libs[i]._lib == lib) {
      return;
    }
  }

  if (_size >= MAX_SOCKET_PATCHED_LIBS) {
    Log::warn("SocketPatcher: too many Netty libraries, skipping %s", lib->name());
    return;
  }

  SocketPatchSet& ps = _patched_libs[_size];
  ps._lib = lib;
  int patched_count = 0;

  for (int i = 0; i < 6; i++) {
    void** location = (void**)lib->findImport(_import_ids[i]);
    if (location != nullptr) {
      ps._locations[i] = location;
      ps._originals[i] = __atomic_load_n(location, __ATOMIC_RELAXED);
      __atomic_store_n(location, _hook_funcs[i], __ATOMIC_RELAXED);
      patched_count++;
    } else {
      ps._locations[i] = nullptr;
      ps._originals[i] = nullptr;
    }
  }

  // Always increment to record that this library was examined,
  // preventing redundant re-scanning on subsequent patch_libraries() calls.
  _size++;
  if (patched_count > 0) {
    TEST_LOG("SocketPatcher: patching %s (%d functions)", lib->name(), patched_count);
  }
}

void SocketPatcher::patch_libraries() {
  if (!Profiler::instance()->nativeSockets()) {
    TEST_LOG("SocketPatcher: disabled by nativesock=false");
    return;
  }

  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int num_of_libs = native_libs.count();
  ExclusiveLockGuard locker(&_lock);
  for (int i = 0; i < num_of_libs; i++) {
    CodeCache* lib = native_libs.at(i);
    patch_library_unlocked(lib);
  }
}

void SocketPatcher::unpatch_libraries() {
  ExclusiveLockGuard locker(&_lock);
  for (int i = 0; i < _size; i++) {
    SocketPatchSet& ps = _patched_libs[i];
    for (int j = 0; j < 6; j++) {
      if (ps._locations[j] != nullptr) {
        __atomic_store_n(ps._locations[j], ps._originals[j], __ATOMIC_RELAXED);
      }
    }
  }
  TEST_LOG("SocketPatcher: restored %d libraries", _size);
  _size = 0;
}

#endif // __linux__
