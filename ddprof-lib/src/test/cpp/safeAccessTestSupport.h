/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SAFEACCESS_TEST_SUPPORT_H
#define _SAFEACCESS_TEST_SUPPORT_H

#include <cstring>
#include <signal.h>
#include <sys/mman.h>

#include "os.h"
#include "safeAccess.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Installs a SIGSEGV/SIGBUS handler that lets SafeAccess reads fault safely,
// and restores the previous handlers on scope exit. Faults that are not
// SafeAccess's go to the previous handler, or to the gtest crash handler.
class ScopedSafeAccessHandler {
public:
  explicit ScopedSafeAccessHandler(const char* test_name) {
    s_test_name = test_name;
    s_orig_segv = OS::replaceSigsegvHandler(handle);
    s_orig_bus = OS::replaceSigbusHandler(handle);
  }
  ~ScopedSafeAccessHandler() {
    OS::replaceSigsegvHandler(s_orig_segv);
    OS::replaceSigbusHandler(s_orig_bus);
  }
  ScopedSafeAccessHandler(const ScopedSafeAccessHandler&) = delete;
  ScopedSafeAccessHandler& operator=(const ScopedSafeAccessHandler&) = delete;

private:
  using Handler = void (*)(int, siginfo_t*, void*);

  static void handle(int signo, siginfo_t* siginfo, void* context) {
    if (SafeAccess::handle_safefetch(signo, context)) {
      return;
    }
    Handler orig = signo == SIGBUS ? s_orig_bus : s_orig_segv;
    if (orig != nullptr) {
      orig(signo, siginfo, context);
    } else {
      gtestCrashHandler(signo, siginfo, context, s_test_name);
    }
  }

  static inline Handler s_orig_segv = nullptr;
  static inline Handler s_orig_bus = nullptr;
  static inline const char* s_test_name = "";
};

// Owns `readable_pages` readable pages followed by a PROT_NONE guard page,
// unmapped on scope exit. The guard stays mapped, unlike a munmap()ed page
// that a concurrent mmap may reuse, so a read past the readable pages always faults.
class GuardedPage {
public:
  explicit GuardedPage(size_t readable_pages = 1)
      : _readable_pages(readable_pages),
        _region(mmap(NULL, (readable_pages + 1) * OS::page_size, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) {
    if (_region != MAP_FAILED &&
        mprotect(guardStart(), OS::page_size, PROT_NONE) != 0) {
      munmap(_region, (_readable_pages + 1) * OS::page_size);
      _region = MAP_FAILED;
    }
  }
  ~GuardedPage() {
    if (_region != MAP_FAILED) {
      munmap(_region, (_readable_pages + 1) * OS::page_size);
    }
  }
  GuardedPage(const GuardedPage&) = delete;
  GuardedPage& operator=(const GuardedPage&) = delete;

  // Mapped and the guard verifiably faults; needs ScopedSafeAccessHandler.
  bool ok() const {
    return _region != MAP_FAILED && !SafeAccess::isReadable(guardStart());
  }
  // One past the last readable byte: the first byte of the guard page.
  char* guardStart() const {
    return static_cast<char*>(_region) + _readable_pages * OS::page_size;
  }
  // Copies s, NUL included, so that its NUL is the last readable byte.
  char* placeAtEnd(const char* s) const {
    size_t len = strlen(s) + 1;
    char* dst = guardStart() - len;
    memcpy(dst, s, len);
    return dst;
  }

private:
  size_t _readable_pages;
  void* _region;
};

#endif // _SAFEACCESS_TEST_SUPPORT_H
