/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <gtest/gtest.h>
#if defined(__linux__)
#include "libraryPatcher.h"
#include "nativeBlock.h"
#include "nativeFdClassifier.h"
#include "nativeSocketInterposer.h"
#include "nativeSocketSampler.h"
#include <chrono>
#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>

namespace {
class OwnedIoFd {
public:
  explicit OwnedIoFd(int fd) : _fd(fd) {}
  ~OwnedIoFd() { if (_fd >= 0) ::close(_fd); }
  int release() { int fd = _fd; _fd = -1; return fd; }
  void reset(int fd) { if (_fd >= 0) ::close(_fd); _fd = fd; }
  OwnedIoFd(const OwnedIoFd&) = delete;
  OwnedIoFd& operator=(const OwnedIoFd&) = delete;
private:
  int _fd;
};

class NativeIoFreshAdmissionTest : public ::testing::Test {
protected:
  void SetUp() override {
    NativeSocketInterposer::getOriginalFunctions(send, recv, write, read);
    NativeSocketSampler::getOriginalFunctions(sampler_send, sampler_recv, sampler_write, sampler_read);
    saved_interposer = NativeSocketInterposer::instance()->setActiveForTest(false);
    saved_sampler = NativeSocketSampler::setActiveForTest(false);
    saved_installed = LibraryPatcher::_socket_active.exchange(true, std::memory_order_acq_rel);
    NativeSocketInterposer::setOriginalFunctions(::send, ::recv, ::write, ::read);
    NativeSocketSampler::setOriginalFunctions(::send, ::recv, ::write, ::read);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
    NativeBlockScope::setHookObserverForTest(observe);
  }
  void TearDown() override {
    NativeBlockScope::setHookObserverForTest(nullptr);
    NativeSocketSampler::setHookObserverForTest(nullptr);
    NativeFdClassifier::setProbeOverrideForTest(nullptr);
    NativeSocketInterposer::setOriginalFunctions(send, recv, write, read);
    NativeSocketSampler::setOriginalFunctions(sampler_send, sampler_recv, sampler_write, sampler_read);
    NativeSocketInterposer::instance()->setActiveForTest(saved_interposer);
    NativeSocketSampler::setActiveForTest(saved_sampler);
    LibraryPatcher::_socket_active.store(saved_installed, std::memory_order_release);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
  }
  static void observe(const char* phase, NativeBlockKind, int) {
    if (phase[0] == 'e' && phase[1] == 'n') entries++;
  }
  NativeSocketInterposer::send_fn send;
  NativeSocketInterposer::recv_fn recv;
  NativeSocketInterposer::write_fn write;
  NativeSocketInterposer::read_fn read;
  NativeSocketSampler::send_fn sampler_send;
  NativeSocketSampler::recv_fn sampler_recv;
  NativeSocketSampler::write_fn sampler_write;
  NativeSocketSampler::read_fn sampler_read;
  bool saved_interposer, saved_sampler, saved_installed;
  static int entries;
};
int NativeIoFreshAdmissionTest::entries = 0;

TEST_F(NativeIoFreshAdmissionTest, InactiveEnteredHooksDoNotAllocateClassifiersOrEnterScopes) {
  uint64_t allocations = NativeFdClassifier::cacheAllocationCountForTest();
  NativeFdClassifier::resetProbeCountForTest();
  entries = 0;
  for (bool installed : {false, true}) {
    LibraryPatcher::_socket_active.store(installed, std::memory_order_release);
    char byte = 0;
    EXPECT_EQ(-1, NativeSocketInterposer::send_hook(INT_MAX, &byte, 1, 0));
    EXPECT_EQ(-1, NativeSocketInterposer::recv_hook(INT_MAX, &byte, 1, 0));
    EXPECT_EQ(-1, NativeSocketInterposer::write_hook(INT_MAX, &byte, 1));
    EXPECT_EQ(-1, NativeSocketInterposer::read_hook(INT_MAX, &byte, 1));
    EXPECT_EQ(-1, NativeSocketSampler::send_hook(INT_MAX, &byte, 1, 0));
    EXPECT_EQ(-1, NativeSocketSampler::recv_hook(INT_MAX, &byte, 1, 0));
    EXPECT_EQ(-1, NativeSocketSampler::write_hook(INT_MAX, &byte, 1));
    EXPECT_EQ(-1, NativeSocketSampler::read_hook(INT_MAX, &byte, 1));
    EXPECT_EQ(-1, NativeSocketInterposer::close_hook(INT_MAX));
    EXPECT_EQ(0, entries);
    EXPECT_EQ(0u, NativeFdClassifier::probeCountForTest());
    EXPECT_EQ(allocations, NativeFdClassifier::cacheAllocationCountForTest());
  }
}

TEST_F(NativeIoFreshAdmissionTest, ScopeAndCombinedRecordingPreserveOriginalEntryAndResultErrno) {
  static int original_calls;
  static int record_calls;
  NativeBlockScope::setHookObserverForTest([](const char*, NativeBlockKind, int) {
    entries++;
    errno = ENOSPC;
  });
  NativeSocketSampler::setHookObserverForTest([](const char*, int, u8, ssize_t) {
    record_calls++;
    errno = ENOMEM;
  });
  NativeFdClassifier::setProbeOverrideForTest([](int, int* type, int* failure) {
    *type = SOCK_STREAM;
    *failure = 0;
    errno = EIO;
    return 0;
  });
  NativeSocketInterposer::setOriginalFunctions(
      [](int, const void*, size_t, int) -> ssize_t {
        original_calls++;
        EXPECT_EQ(E2BIG, errno);
        errno = EPIPE;
        return 1;
      },
      [](int, void*, size_t, int) -> ssize_t {
        original_calls++;
        EXPECT_EQ(E2BIG, errno);
        errno = EPIPE;
        return 1;
      },
      [](int, const void*, size_t) -> ssize_t {
        original_calls++;
        EXPECT_EQ(E2BIG, errno);
        errno = EPIPE;
        return 1;
      },
      [](int, void*, size_t) -> ssize_t {
        original_calls++;
        EXPECT_EQ(E2BIG, errno);
        errno = EPIPE;
        return 1;
      });
  for (bool sampler_active : {false, true}) {
    SCOPED_TRACE(sampler_active);
    NativeSocketInterposer::instance()->setActiveForTest(true);
    NativeSocketSampler::setActiveForTest(sampler_active);
    original_calls = record_calls = entries = 0;
    char byte = 'x';
    for (int op = 0; op < 4; op++) {
      errno = E2BIG;
      ssize_t result = op == 0 ? NativeSocketInterposer::send_hook(7, &byte, 1, 0)
          : op == 1 ? NativeSocketInterposer::recv_hook(7, &byte, 1, 0)
          : op == 2 ? NativeSocketInterposer::write_hook(7, &byte, 1)
                    : NativeSocketInterposer::read_hook(7, &byte, 1);
      EXPECT_EQ(1, result);
      EXPECT_EQ(EPIPE, errno);
    }
    EXPECT_EQ(4, original_calls);
    EXPECT_EQ(8, entries) << "both scope constructor and destructor must run";
    EXPECT_EQ(sampler_active ? 4 : 0, record_calls);
  }
}

TEST_F(NativeIoFreshAdmissionTest, RawDup2ReuseRevalidatesPositiveAndNegativeAdmissionForEveryOwner) {
  auto* interposer = NativeSocketInterposer::instance();
  auto* sampler = NativeSocketSampler::instance();
  for (int owners : {1, 2, 3}) {
    for (int minimum : {0, 65536}) {
      for (bool inbound : {false, true}) {
        SCOPED_TRACE(owners);
        SCOPED_TRACE(minimum);
        SCOPED_TRACE(inbound);
        interposer->setActiveForTest((owners & 1) != 0);
        NativeSocketSampler::setActiveForTest((owners & 2) != 0);
        int sockets[2];
        ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, sockets));
        OwnedIoFd stream(sockets[0]), peer(sockets[1]);
        int pipes[2];
        ASSERT_EQ(0, pipe2(pipes, O_CLOEXEC | O_NONBLOCK));
        OwnedIoFd pipe_read(pipes[0]), pipe_write(pipes[1]);
        int fd = fcntl(sockets[0], F_DUPFD_CLOEXEC, minimum);
        ASSERT_GE(fd, minimum);
        OwnedIoFd target(fd);
        interposer->clearFdType(fd);
        sampler->clearFdCacheEntry(fd);
        ASSERT_TRUE(interposer->isStreamSocket(fd));
        ASSERT_TRUE(sampler->isSocketForTest(fd));
        // Neither raw close nor the subsequent raw dup2 passes a lifecycle hook.
        ASSERT_EQ(0, ::close(target.release()));
        int replacement = ::dup2(pipes[inbound ? 0 : 1], fd);
        target.reset(replacement);
        ASSERT_EQ(fd, replacement);
        entries = 0;
        NativeFdClassifier::resetProbeCountForTest();
        char byte = 'x';
        if (inbound) {
          ASSERT_EQ(1, ::write(pipes[1], &byte, 1));
          EXPECT_EQ(-1, NativeSocketInterposer::recv_hook(fd, &byte, 1, MSG_DONTWAIT));
          EXPECT_EQ(ENOTSOCK, errno);
          errno = E2BIG;
          EXPECT_EQ(1, NativeSocketInterposer::read_hook(fd, &byte, 1));
        } else {
          EXPECT_EQ(-1, NativeSocketInterposer::send_hook(fd, &byte, 1, MSG_DONTWAIT));
          EXPECT_EQ(ENOTSOCK, errno);
          errno = E2BIG;
          EXPECT_EQ(1, NativeSocketInterposer::write_hook(fd, &byte, 1));
          EXPECT_EQ(E2BIG, errno);
          ASSERT_EQ(1, ::read(pipes[0], &byte, 1));
        }
        EXPECT_EQ(E2BIG, errno);
        EXPECT_EQ(0, entries) << "raw socket-to-pipe reuse must not enter TaskBlock";
        EXPECT_EQ(2u, NativeFdClassifier::probeCountForTest())
            << "exactly one admission probe per hook, even with both owners active";
        // Establish ready negative verdicts in both independent caches.
        interposer->clearFdType(fd);
        sampler->clearFdCacheEntry(fd);
        ASSERT_FALSE(interposer->isStreamSocket(fd));
        ASSERT_FALSE(sampler->isSocketForTest(fd));
        ASSERT_EQ(fd, ::dup2(sockets[0], fd));
        entries = 0;
        NativeFdClassifier::resetProbeCountForTest();
        for (int generic = 0; generic < 2; generic++) {
          if (inbound) ASSERT_EQ(1, ::write(sockets[1], &byte, 1));
          errno = E2BIG;
          ssize_t result = inbound
              ? (generic ? NativeSocketInterposer::read_hook(fd, &byte, 1)
                         : NativeSocketInterposer::recv_hook(fd, &byte, 1, MSG_DONTWAIT))
              : (generic ? NativeSocketInterposer::write_hook(fd, &byte, 1)
                         : NativeSocketInterposer::send_hook(fd, &byte, 1, MSG_DONTWAIT));
          EXPECT_EQ(1, result);
          EXPECT_EQ(E2BIG, errno);
          if (!inbound) ASSERT_EQ(1, ::read(sockets[1], &byte, 1));
        }
        EXPECT_EQ((owners & 1) ? 2 : 0, entries)
            << "raw pipe-to-stream reuse must repair negative admission";
        EXPECT_EQ(2u, NativeFdClassifier::probeCountForTest());
      }
    }
  }
}

TEST_F(NativeIoFreshAdmissionTest, RepeatedAdmissionHasBoundedProbeAndDescriptorCost) {
  struct rlimit limit;
  ASSERT_EQ(0, getrlimit(RLIMIT_NOFILE, &limit));
  ASSERT_GT(limit.rlim_cur, 65536u) << "high-FD qualification requires a real sufficient limit";
  const int iterations = 10000;
  for (int owners : {1, 2, 3}) {
    for (int minimum : {0, 65536}) {
      SCOPED_TRACE(owners);
      SCOPED_TRACE(minimum);
      int sockets[2];
      int fd = -1;
      {
        ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, sockets));
        OwnedIoFd stream(sockets[0]), peer(sockets[1]);
        fd = fcntl(sockets[0], F_DUPFD_CLOEXEC, minimum);
        ASSERT_GE(fd, minimum);
        OwnedIoFd target(fd);
        if (minimum == 0) ASSERT_LT(fd, 65536);
        ASSERT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(fd));
        ASSERT_TRUE(NativeSocketSampler::instance()->isSocketForTest(fd));
        auto transfer = [&](bool hooked) {
          char byte = 'x';
          for (int i = 0; i < iterations; i++) {
            ASSERT_EQ(1, hooked ? NativeSocketInterposer::send_hook(fd, &byte, 1, MSG_DONTWAIT)
                                : ::send(fd, &byte, 1, MSG_DONTWAIT));
            ASSERT_EQ(1, ::read(sockets[1], &byte, 1));
            ASSERT_EQ(1, hooked ? NativeSocketInterposer::write_hook(fd, &byte, 1)
                                : ::write(fd, &byte, 1));
            ASSERT_EQ(1, ::read(sockets[1], &byte, 1));
            ASSERT_EQ(1, ::write(sockets[1], &byte, 1));
            ASSERT_EQ(1, hooked ? NativeSocketInterposer::recv_hook(fd, &byte, 1, MSG_DONTWAIT)
                                : ::recv(fd, &byte, 1, MSG_DONTWAIT));
            ASSERT_EQ(1, ::write(sockets[1], &byte, 1));
            ASSERT_EQ(1, hooked ? NativeSocketInterposer::read_hook(fd, &byte, 1)
                                : ::read(fd, &byte, 1));
          }
        };
        NativeSocketInterposer::instance()->setActiveForTest((owners & 1) != 0);
        NativeSocketSampler::setActiveForTest((owners & 2) != 0);
        auto start = std::chrono::steady_clock::now();
        transfer(false);
        ASSERT_FALSE(HasFatalFailure());
        auto raw_end = std::chrono::steady_clock::now();
        entries = 0;
        NativeFdClassifier::resetProbeCountForTest();
        transfer(true);
        ASSERT_FALSE(HasFatalFailure());
        auto hook_end = std::chrono::steady_clock::now();
        EXPECT_EQ(4u * iterations, NativeFdClassifier::probeCountForTest());
        EXPECT_EQ((owners & 1) ? 4 * iterations : 0, entries);
        auto raw_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(raw_end - start).count();
        auto hook_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(hook_end - raw_end).count();
        std::printf("native_io_admission_cost owners=%d fd=%d operations=%d raw_ns=%lld hook_ns=%lld\n",
                    owners, fd, 4 * iterations,
                    static_cast<long long>(raw_ns), static_cast<long long>(hook_ns));
      }
      for (int closed_fd : {sockets[0], sockets[1], fd}) {
        errno = 0;
        EXPECT_EQ(-1, fcntl(closed_fd, F_GETFD));
        EXPECT_EQ(EBADF, errno);
      }
    }
  }
}

int exhaustion_type = SOCK_STREAM;
int exhaustion_calls = 0;
NativeFdClassifier* exhausting = nullptr;
int exhaustion_probe(int, int* type, int* failure) {
  exhaustion_calls++;
  *type = exhaustion_type;
  *failure = 0;
  if (exhausting != nullptr) {
    for (uint32_t i = 0; i < (1u << 18); i++) exhausting->clearFdTypeCache();
    *failure = ENOTSOCK;
    return -1;
  }
  return 0;
}

TEST(NativeIoCacheExhaustionTest, RetiredBanksStayUncachedWithoutDisablingClassification) {
  NativeFdClassifier classifier;
  NativeFdClassifier::setProbeOverrideForTest(exhaustion_probe);
  struct Cleanup {
    ~Cleanup() { NativeFdClassifier::setProbeOverrideForTest(nullptr); exhausting = nullptr; }
  } cleanup;
  exhaustion_calls = 0;
  exhausting = &classifier;
  EXPECT_FALSE(classifier.isStreamSocket(65536 + 7));
  EXPECT_EQ(1, exhaustion_calls);
  exhausting = nullptr;
  exhaustion_type = SOCK_STREAM;
  EXPECT_TRUE(classifier.isStreamSocket(65536 + 7));
  EXPECT_TRUE(classifier.isStreamSocket(65536 + 7));
  EXPECT_EQ(3, exhaustion_calls) << "exhaustion must not reuse an old packed epoch";
  exhaustion_type = SOCK_DGRAM;
  EXPECT_FALSE(classifier.isStreamSocket(65536 + 7));
  EXPECT_TRUE(classifier.isDatagramSocket(65536 + 7));
  EXPECT_EQ(5, exhaustion_calls);
}
} // namespace
#endif // __linux__
