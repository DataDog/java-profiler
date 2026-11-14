/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <gtest/gtest.h>

#if defined(__linux__)
#include "counters.h"
#include "nativeBlock.h"
#include "nativeSocketInterposer.h"
#include "safeAccess.h"
#include "vmEntry.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <signal.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

// Unit-only VM dispatch control; these flags are not evidence of a running JVM.
class VMTestAccessor {
public:
  static void setTimeoutTestVm(int kind) {
    VM::_hotspot = kind == 0;
    VM::_openj9 = kind == 1;
    VM::_zing = kind == 2;
  }
};

namespace {
enum TimeoutOperation { PPOLL, PSELECT, SELECT };
enum TimeoutScenario { KERNEL_FAULT, READABLE_CONTROLS, LIBC_BASELINE, LIBC_HOOK };

volatile sig_atomic_t recovered_faults;
int original_calls;
int scope_entries;
bool kernel_original;
const void *expected_timeout;

void timeoutFaultHandler(int signo, siginfo_t *, void *context) {
  if (SafeAccess::handle_safefetch(signo, context)) {
    recovered_faults++;
    return;
  }
  // Contain a legacy eligibility read or a libc-origin fault in this child.
  _exit(128 + signo);
}

bool originalArgumentsMatch(const void *timeout) {
  original_calls++;
  return timeout == expected_timeout && errno == E2BIG;
}

int ppollOriginal(struct pollfd *fds, nfds_t nfds, const struct timespec *timeout,
                  const sigset_t *mask) {
  if (!originalArgumentsMatch(timeout) || fds == nullptr || nfds != 1 || mask != nullptr) {
    errno = EPROTO;
    return -1;
  }
  if (kernel_original)
    return syscall(SYS_ppoll, fds, nfds, timeout, mask, 8);
  errno = EPIPE;
  return 7;
}

int pselectOriginal(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                    const struct timespec *timeout, const sigset_t *mask) {
  if (!originalArgumentsMatch(timeout) || nfds != 1 || readfds != nullptr || writefds != nullptr ||
      exceptfds != nullptr || mask != nullptr) {
    errno = EPROTO;
    return -1;
  }
  if (kernel_original)
    return syscall(SYS_pselect6, nfds, readfds, writefds, exceptfds, timeout, nullptr);
  errno = EPIPE;
  return 7;
}

int selectOriginal(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                   struct timeval *timeout) {
  if (!originalArgumentsMatch(timeout) || nfds != 1 || readfds != nullptr || writefds != nullptr ||
      exceptfds != nullptr) {
    errno = EPROTO;
    return -1;
  }
  if (kernel_original) {
#ifdef SYS_select
    return syscall(SYS_select, nfds, readfds, writefds, exceptfds, timeout);
#else
    // arm64 exposes pselect6, not the select syscall. This original checks
    // forwarding/errno only; ppoll/pselect above still reach the real kernel.
    errno = EFAULT;
    return -1;
#endif
  }
  errno = EPIPE;
  return 7;
}

int invokeTimeoutHook(TimeoutOperation operation, void *timeout, bool hook) {
  struct pollfd fd = {-1, POLLIN, 0};
  if (operation == PPOLL) {
    return hook ? NativeSocketInterposer::ppoll_hook(&fd, 1, static_cast<timespec *>(timeout),
                                                     nullptr)
                : ::ppoll(&fd, 1, static_cast<timespec *>(timeout), nullptr);
  }
  if (operation == PSELECT) {
    return hook
               ? NativeSocketInterposer::pselect_hook(1, nullptr, nullptr, nullptr,
                                                      static_cast<timespec *>(timeout), nullptr)
               : ::pselect(1, nullptr, nullptr, nullptr, static_cast<timespec *>(timeout), nullptr);
  }
  return hook ? NativeSocketInterposer::select_hook(1, nullptr, nullptr, nullptr,
                                                    static_cast<timeval *>(timeout))
              : ::select(1, nullptr, nullptr, nullptr, static_cast<timeval *>(timeout));
}

int timeoutChild(int vm, TimeoutOperation operation, TimeoutScenario scenario, bool active,
                 bool partial) {
  // A stuck fault handler or accidentally blocking original is a test failure,
  // not an unbounded orphan. This limit is for this finite I/O test only.
  alarm(10);
  struct rlimit core_limit = {0, 0};
  if (setrlimit(RLIMIT_CORE, &core_limit) != 0)
    return 24;
  VMTestAccessor::setTimeoutTestVm(vm);
  NativeSocketInterposer::instance()->setActiveForTest(active);
  if (vm != 2) {
    (void)Counters::getCounters();
    struct sigaction action = {};
    action.sa_sigaction = timeoutFaultHandler;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGSEGV, &action, nullptr) != 0 || sigaction(SIGBUS, &action, nullptr) != 0)
      return 20;
  } else {
    struct sigaction action = {};
    action.sa_handler = SIG_DFL;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGSEGV, &action, nullptr) != 0 || sigaction(SIGBUS, &action, nullptr) != 0)
      return 21;
  }
  const size_t page = static_cast<size_t>(sysconf(_SC_PAGESIZE));
  char *memory = static_cast<char *>(
      mmap(nullptr, 2 * page, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
  if (memory == MAP_FAILED)
    return 22;
  if (mprotect(memory + page, page, PROT_NONE) != 0)
    return 23;
  NativeBlockScope::setHookObserverForTest([](const char *phase, NativeBlockKind, int) {
    if (strcmp(phase, "enter") == 0)
      scope_entries++;
  });
  bool libc_original = scenario == LIBC_BASELINE || scenario == LIBC_HOOK;
  NativeSocketInterposer::setOriginalFunction(
      NativeSocketInterposer::HOOK_PPOLL,
      reinterpret_cast<void *>(libc_original ? ::ppoll : ppollOriginal));
  NativeSocketInterposer::setOriginalFunction(
      NativeSocketInterposer::HOOK_PSELECT,
      reinterpret_cast<void *>(libc_original ? ::pselect : pselectOriginal));
  NativeSocketInterposer::setOriginalFunction(
      NativeSocketInterposer::HOOK_SELECT,
      reinterpret_cast<void *>(libc_original ? ::select : selectOriginal));
  if (scenario == READABLE_CONTROLS) {
    kernel_original = false;
    for (int value = 0; value < 4; value++) {
      // A readable structure ends exactly at the inaccessible page: a safeCopy
      // must not over-read it. Check null, zero, seconds and fractional timeouts.
      void *timeout = value == 0 ? nullptr : memory + page - sizeof(timespec);
      if (timeout != nullptr) {
        if (operation == SELECT) {
          struct timeval t = {value == 2 ? 1 : 0, value == 3 ? 1 : 0};
          memcpy(timeout, &t, sizeof(t));
        } else {
          struct timespec t = {value == 2 ? 1 : 0, value == 3 ? 1 : 0};
          memcpy(timeout, &t, sizeof(t));
        }
      }
      expected_timeout = timeout;
      original_calls = scope_entries = recovered_faults = 0;
      errno = E2BIG;
      int result = invokeTimeoutHook(operation, timeout, true);
      if (result != 7 || errno != EPIPE || original_calls != 1 || recovered_faults != 0)
        return 30 + value;
      bool eligible = active && (value == 0 || (vm != 2 && value > 1));
      if (scope_entries != (eligible ? 1 : 0))
        return 40 + value;
    }
    return 0;
  }
  // Partial layout has tv_sec readable and tv_nsec/tv_usec inaccessible.
  void *timeout = memory + page - (partial ? sizeof(time_t) : 0);
  if (partial) {
    time_t seconds = 1;
    memcpy(timeout, &seconds, sizeof(seconds));
  }
  expected_timeout = timeout;
  original_calls = scope_entries = recovered_faults = 0;
  kernel_original = true;
  errno = E2BIG;
  int result = invokeTimeoutHook(operation, timeout, scenario != LIBC_BASELINE);
  if (libc_original)
    return result == -1 && errno == EFAULT ? 0 : 60;
  if (result != -1 || errno != EFAULT || original_calls != 1 || scope_entries != 0)
    return 61;
  return recovered_faults == (active && vm != 2 ? 1 : 0) ? 0 : 62;
}

int waitForTimeoutChild(int vm, TimeoutOperation operation, TimeoutScenario scenario, bool active,
                        bool partial = false) {
  pid_t child = fork();
  if (child < 0)
    return -1;
  if (child == 0)
    _exit(timeoutChild(vm, operation, scenario, active, partial));
  int status;
  pid_t result;
  do {
    result = waitpid(child, &status, 0);
  } while (result < 0 && errno == EINTR);
  return result == child ? status : -1;
}

TEST(NativeIoTimeoutTest, ProtectedVmFaultRecoveryForwardsUnchangedToKernelOriginal) {
  for (int vm : {0, 1}) {
    for (TimeoutOperation operation : {PPOLL, PSELECT, SELECT}) {
      for (bool partial : {false, true}) {
        SCOPED_TRACE(vm);
        SCOPED_TRACE(operation);
        SCOPED_TRACE(partial);
        EXPECT_EQ(0, waitForTimeoutChild(vm, operation, KERNEL_FAULT, true, partial));
      }
    }
  }
}

TEST(NativeIoTimeoutTest, UnprotectedAndInactiveHooksDoNotReadTimeoutBeforeOriginal) {
  for (int vm : {0, 1, 2}) {
    for (TimeoutOperation operation : {PPOLL, PSELECT, SELECT}) {
      SCOPED_TRACE(vm);
      SCOPED_TRACE(operation);
      EXPECT_EQ(0, waitForTimeoutChild(vm, operation, KERNEL_FAULT, false));
      if (vm == 2)
        EXPECT_EQ(0, waitForTimeoutChild(vm, operation, KERNEL_FAULT, true));
    }
  }
}

TEST(NativeIoTimeoutTest, BoundedReadableTimeoutsKeepEligibilityAndErrno) {
  for (int vm : {0, 1, 2}) {
    for (TimeoutOperation operation : {PPOLL, PSELECT, SELECT}) {
      for (bool active : {false, true}) {
        SCOPED_TRACE(vm);
        SCOPED_TRACE(operation);
        SCOPED_TRACE(active);
        EXPECT_EQ(0, waitForTimeoutChild(vm, operation, READABLE_CONTROLS, active));
      }
    }
  }
}

TEST(NativeIoTimeoutTest, ActualLibcFaultComparisonDoesNotAssumeUniversalEfault) {
  for (int vm : {0, 1, 2}) {
    for (TimeoutOperation operation : {PPOLL, PSELECT, SELECT}) {
      int baseline = waitForTimeoutChild(vm, operation, LIBC_BASELINE, true);
      int hooked = waitForTimeoutChild(vm, operation, LIBC_HOOK, true);
      printf("native-timeout-libc vm_dispatch=%d operation=%d baseline_wait_status=%d "
             "hook_wait_status=%d\n",
             vm, operation, baseline, hooked);
      SCOPED_TRACE(vm);
      SCOPED_TRACE(operation);
      ASSERT_NE(-1, baseline);
      ASSERT_NE(-1, hooked);
      for (int status : {baseline, hooked}) {
        bool fault_exit = WIFEXITED(status) && (WEXITSTATUS(status) == 128 + SIGSEGV ||
                                                WEXITSTATUS(status) == 128 + SIGBUS);
        bool fault_signal =
            WIFSIGNALED(status) && (WTERMSIG(status) == SIGSEGV || WTERMSIG(status) == SIGBUS);
        ASSERT_TRUE(status == 0 || fault_exit || fault_signal)
            << "setup failure, timeout or unclassified libc result: " << status;
      }
      // Capture the actual libc result rather than require EFAULT: glibc's
      // timeout copy may fault before the kernel can validate the pointer.
      EXPECT_EQ(baseline, hooked);
    }
  }
}
} // namespace
#endif // __linux__
