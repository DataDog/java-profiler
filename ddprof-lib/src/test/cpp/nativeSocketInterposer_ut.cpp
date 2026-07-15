/*
 * Copyright 2026 Datadog, Inc.
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

#include <gtest/gtest.h>

#if defined(__linux__)

#include "libraries.h"
#include "libraryPatcher.h"
#include "nativeBlock.h"
#include "nativeFdClassifier.h"
#include "nativeSocketInterposer.h"
#include "nativeSocketSampler.h"
#include "os.h"
#include "profiler.h"

#include <atomic>
#include <cerrno>
#include <cstdio>
#include <dlfcn.h>
#include <fcntl.h>
#include <limits.h>
#include <memory>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <vector>

namespace {

static const int kFdTypeCacheSizeForTest = 65536;
static const int kHighFdCacheSizeForTest = 4096;

std::atomic<int> g_send_calls{0};
std::atomic<int> g_sampler_send_calls{0};
std::atomic<int> g_recv_calls{0};
std::atomic<int> g_write_calls{0};
std::atomic<int> g_sampler_write_calls{0};
std::atomic<int> g_read_calls{0};
std::atomic<int> g_close_calls{0};
std::atomic<int> g_connect_calls{0};
std::atomic<int> g_accept_calls{0};
std::atomic<int> g_accept4_calls{0};
std::atomic<int> g_recvfrom_calls{0};
std::atomic<int> g_recvmsg_calls{0};
std::atomic<int> g_epoll_wait_calls{0};
std::atomic<int> g_epoll_pwait_calls{0};
std::atomic<int> g_poll_calls{0};
std::atomic<int> g_ppoll_calls{0};
std::atomic<int> g_select_calls{0};
std::atomic<int> g_pselect_calls{0};
std::atomic<int> g_fd_probe_calls{0};
std::atomic<int> g_fd_probe_rc{0};
std::atomic<int> g_fd_probe_errno{0};
std::atomic<int> g_fd_probe_so_type{0};
std::atomic<int> g_fd_probe_last_fd{0};
std::atomic<int> g_sequence{0};
std::atomic<int> g_raw_syscall_sequence{0};
std::atomic<int> g_taskblock_enter_sequence{0};
std::atomic<int> g_taskblock_exit_sequence{0};
std::atomic<int> g_sampler_record_sequence{0};
std::atomic<ssize_t> g_send_ret{0};
std::atomic<ssize_t> g_sampler_send_ret{0};
std::atomic<ssize_t> g_recv_ret{0};
std::atomic<ssize_t> g_write_ret{0};
std::atomic<ssize_t> g_sampler_write_ret{0};
std::atomic<ssize_t> g_read_ret{0};
std::atomic<int> g_close_ret{0};
std::atomic<int> g_close_errno{0};
std::atomic<int> g_connect_ret{0};
std::atomic<int> g_accept_ret{0};
std::atomic<int> g_accept4_ret{0};
std::atomic<ssize_t> g_recvfrom_ret{0};
std::atomic<ssize_t> g_recvmsg_ret{0};
std::atomic<int> g_epoll_wait_ret{0};
std::atomic<int> g_epoll_pwait_ret{0};
std::atomic<int> g_poll_ret{0};
std::atomic<int> g_ppoll_ret{0};
std::atomic<int> g_select_ret{0};
std::atomic<int> g_pselect_ret{0};

ssize_t stub_send(int, const void*, size_t, int) {
  g_send_calls++;
  return g_send_ret.load();
}

ssize_t sampler_stub_send(int, const void*, size_t, int) {
  g_sampler_send_calls++;
  return g_sampler_send_ret.load();
}

int stub_fd_probe(int, int *so_type, int *probe_errno) {
  g_fd_probe_calls++;
  *so_type = g_fd_probe_so_type.load(std::memory_order_acquire);
  *probe_errno = g_fd_probe_errno.load(std::memory_order_acquire);
  return g_fd_probe_rc.load(std::memory_order_acquire);
}

int recording_fd_probe(int fd, int *so_type, int *probe_errno) {
  g_fd_probe_last_fd.store(fd, std::memory_order_release);
  return stub_fd_probe(fd, so_type, probe_errno);
}

class ScopedFdProbeOverride {
public:
  explicit ScopedFdProbeOverride(NativeFdClassifier::ProbeOverride probe) {
    NativeFdClassifier::setProbeOverrideForTest(probe);
  }
  ~ScopedFdProbeOverride() {
    NativeFdClassifier::setProbeOverrideForTest(nullptr);
  }
};

class ScopedTaskBlockEnabled {
public:
  explicit ScopedTaskBlockEnabled(bool enabled)
      : _saved(Profiler::instance()->setTaskBlockEnabledForTest(enabled)) {}
  ~ScopedTaskBlockEnabled() {
    Profiler::instance()->setTaskBlockEnabledForTest(_saved);
  }

private:
  bool _saved;
};

class ScopedNativeSocketInterposerActive {
public:
  explicit ScopedNativeSocketInterposerActive(bool active)
      : _saved(NativeSocketInterposer::instance()->setActiveForTest(active)) {}
  ~ScopedNativeSocketInterposerActive() {
    NativeSocketInterposer::instance()->setActiveForTest(_saved);
  }

private:
  bool _saved;
};

class ScopedNativeSocketSamplerActive {
public:
  explicit ScopedNativeSocketSamplerActive(bool active)
      : _saved(NativeSocketSampler::setActiveForTest(active)) {}
  ~ScopedNativeSocketSamplerActive() {
    NativeSocketSampler::setActiveForTest(_saved);
  }

private:
  bool _saved;
};

ssize_t stub_recv(int, void*, size_t, int) {
  g_recv_calls++;
  return g_recv_ret.load();
}

ssize_t stub_write(int, const void*, size_t) {
  g_write_calls++;
  g_raw_syscall_sequence.store(g_sequence.fetch_add(1) + 1,
                               std::memory_order_release);
  return g_write_ret.load();
}

ssize_t sampler_stub_write(int, const void*, size_t) {
  g_sampler_write_calls++;
  g_raw_syscall_sequence.store(g_sequence.fetch_add(1) + 1,
                               std::memory_order_release);
  return g_sampler_write_ret.load();
}

ssize_t stub_read(int, void*, size_t) {
  g_read_calls++;
  g_raw_syscall_sequence.store(g_sequence.fetch_add(1) + 1,
                               std::memory_order_release);
  return g_read_ret.load();
}

void native_block_observer(const char* phase, NativeBlockKind, int) {
  int sequence = g_sequence.fetch_add(1) + 1;
  if (strcmp(phase, "enter") == 0) {
    g_taskblock_enter_sequence.store(sequence, std::memory_order_release);
  } else if (strcmp(phase, "exit") == 0) {
    g_taskblock_exit_sequence.store(sequence, std::memory_order_release);
  }
}

void native_socket_sampler_observer(const char* phase, int, u8, ssize_t) {
  if (strcmp(phase, "record") == 0) {
    g_sampler_record_sequence.store(g_sequence.fetch_add(1) + 1,
                                    std::memory_order_release);
  }
}

int stub_close(int) {
  g_close_calls++;
  errno = g_close_errno.load();
  return g_close_ret.load();
}

int stub_connect(int, const struct sockaddr*, socklen_t) {
  g_connect_calls++;
  return g_connect_ret.load();
}

int stub_accept(int, struct sockaddr*, socklen_t*) {
  g_accept_calls++;
  return g_accept_ret.load();
}

int stub_accept4(int, struct sockaddr*, socklen_t*, int) {
  g_accept4_calls++;
  return g_accept4_ret.load();
}

ssize_t stub_recvfrom(int, void*, size_t, int, struct sockaddr*, socklen_t*) {
  g_recvfrom_calls++;
  return g_recvfrom_ret.load();
}

ssize_t stub_recvmsg(int, struct msghdr*, int) {
  g_recvmsg_calls++;
  return g_recvmsg_ret.load();
}

int stub_epoll_wait(int, struct epoll_event*, int, int) {
  g_epoll_wait_calls++;
  return g_epoll_wait_ret.load();
}

int stub_epoll_pwait(int, struct epoll_event*, int, int, const sigset_t*) {
  g_epoll_pwait_calls++;
  return g_epoll_pwait_ret.load();
}

int stub_poll(struct pollfd*, nfds_t, int) {
  g_poll_calls++;
  return g_poll_ret.load();
}

int stub_ppoll(struct pollfd*, nfds_t, const struct timespec*, const sigset_t*) {
  g_ppoll_calls++;
  return g_ppoll_ret.load();
}

int stub_select(int, fd_set*, fd_set*, fd_set*, struct timeval*) {
  g_select_calls++;
  return g_select_ret.load();
}

int stub_pselect(int, fd_set*, fd_set*, fd_set*, const struct timespec*,
                 const sigset_t*) {
  g_pselect_calls++;
  return g_pselect_ret.load();
}

void setOriginalFunction(NativeSocketInterposer::NativeIoHookIndex hook, void* fn) {
  ASSERT_TRUE(NativeSocketInterposer::setOriginalFunction(hook, fn));
}

class NativeSocketInterposerHookTest : public ::testing::Test {
protected:
  NativeSocketInterposer::send_fn saved_send = nullptr;
  NativeSocketInterposer::recv_fn saved_recv = nullptr;
  NativeSocketInterposer::write_fn saved_write = nullptr;
  NativeSocketInterposer::read_fn saved_read = nullptr;
  NativeSocketSampler::send_fn saved_sampler_send = nullptr;
  NativeSocketSampler::recv_fn saved_sampler_recv = nullptr;
  NativeSocketSampler::write_fn saved_sampler_write = nullptr;
  NativeSocketSampler::read_fn saved_sampler_read = nullptr;
  bool saved_active = false;

  void SetUp() override {
    NativeSocketInterposer::getOriginalFunctions(saved_send, saved_recv, saved_write,
                                                 saved_read);
    NativeSocketSampler::getOriginalFunctions(saved_sampler_send, saved_sampler_recv,
                                              saved_sampler_write, saved_sampler_read);
    NativeSocketInterposer::setOriginalFunctions(stub_send, stub_recv, stub_write,
                                                 stub_read);
    NativeSocketSampler::setOriginalFunctions(sampler_stub_send, stub_recv,
                                              sampler_stub_write, stub_read);
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE,
                        reinterpret_cast<void*>(stub_close));
    setOriginalFunction(NativeSocketInterposer::HOOK_CONNECT,
                        reinterpret_cast<void*>(stub_connect));
    setOriginalFunction(NativeSocketInterposer::HOOK_ACCEPT,
                        reinterpret_cast<void*>(stub_accept));
    setOriginalFunction(NativeSocketInterposer::HOOK_ACCEPT4,
                        reinterpret_cast<void*>(stub_accept4));
    setOriginalFunction(NativeSocketInterposer::HOOK_RECVFROM,
                        reinterpret_cast<void*>(stub_recvfrom));
    setOriginalFunction(NativeSocketInterposer::HOOK_RECVMSG,
                        reinterpret_cast<void*>(stub_recvmsg));
    setOriginalFunction(NativeSocketInterposer::HOOK_EPOLL_WAIT,
                        reinterpret_cast<void*>(stub_epoll_wait));
    setOriginalFunction(NativeSocketInterposer::HOOK_EPOLL_PWAIT,
                        reinterpret_cast<void*>(stub_epoll_pwait));
    setOriginalFunction(NativeSocketInterposer::HOOK_POLL,
                        reinterpret_cast<void*>(stub_poll));
    setOriginalFunction(NativeSocketInterposer::HOOK_PPOLL,
                        reinterpret_cast<void*>(stub_ppoll));
    setOriginalFunction(NativeSocketInterposer::HOOK_SELECT,
                        reinterpret_cast<void*>(stub_select));
    setOriginalFunction(NativeSocketInterposer::HOOK_PSELECT,
                        reinterpret_cast<void*>(stub_pselect));
    saved_active = LibraryPatcher::_socket_active.load(std::memory_order_acquire);
    LibraryPatcher::_socket_active.store(false, std::memory_order_release);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
    NativeSocketSampler::resetSocketProbeCountForTest();
    NativeBlockScope::setHookObserverForTest(nullptr);
    NativeSocketSampler::setHookObserverForTest(nullptr);
    g_send_calls = 0;
    g_sampler_send_calls = 0;
    g_recv_calls = 0;
    g_write_calls = 0;
    g_sampler_write_calls = 0;
    g_read_calls = 0;
    g_close_calls = 0;
    g_connect_calls = 0;
    g_accept_calls = 0;
    g_accept4_calls = 0;
    g_recvfrom_calls = 0;
    g_recvmsg_calls = 0;
    g_epoll_wait_calls = 0;
    g_epoll_pwait_calls = 0;
    g_poll_calls = 0;
    g_ppoll_calls = 0;
    g_select_calls = 0;
    g_pselect_calls = 0;
    g_fd_probe_calls = 0;
    g_sequence = 0;
    g_raw_syscall_sequence = 0;
    g_taskblock_enter_sequence = 0;
    g_taskblock_exit_sequence = 0;
    g_sampler_record_sequence = 0;
    g_send_ret = 0;
    g_sampler_send_ret = 0;
    g_recv_ret = 0;
    g_write_ret = 0;
    g_sampler_write_ret = 0;
    g_read_ret = 0;
    g_close_ret = 0;
    g_close_errno = 0;
    g_connect_ret = 0;
    g_accept_ret = 0;
    g_accept4_ret = 0;
    g_recvfrom_ret = 0;
    g_recvmsg_ret = 0;
    g_epoll_wait_ret = 0;
    g_epoll_pwait_ret = 0;
    g_poll_ret = 0;
    g_ppoll_ret = 0;
    g_select_ret = 0;
    g_pselect_ret = 0;
  }

  void TearDown() override {
    LibraryPatcher::_socket_active.store(saved_active, std::memory_order_release);
    NativeSocketInterposer::setOriginalFunctions(saved_send, saved_recv, saved_write,
                                                 saved_read);
    NativeSocketSampler::setOriginalFunctions(saved_sampler_send, saved_sampler_recv,
                                              saved_sampler_write, saved_sampler_read);
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_CONNECT, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_ACCEPT, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_ACCEPT4, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_RECVFROM, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_RECVMSG, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_EPOLL_WAIT, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_EPOLL_PWAIT, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_POLL, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_PPOLL, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_SELECT, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_PSELECT, nullptr);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
    NativeSocketSampler::resetSocketProbeCountForTest();
    NativeBlockScope::setHookObserverForTest(nullptr);
    NativeSocketSampler::setHookObserverForTest(nullptr);
  }
};

class NativeSocketInterposerFdTest : public ::testing::Test {
protected:
  void SetUp() override {
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE,
                        reinterpret_cast<void*>(::close));
    setOriginalFunction(NativeSocketInterposer::HOOK_DUP2,
                        reinterpret_cast<void*>(::dup2));
    setOriginalFunction(NativeSocketInterposer::HOOK_DUP3, nullptr);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
  }

  void TearDown() override {
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_DUP2, nullptr);
    setOriginalFunction(NativeSocketInterposer::HOOK_DUP3, nullptr);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
  }

  int closeThroughHook(int fd) {
    return NativeSocketInterposer::close_hook(fd);
  }

  int dup2ThroughHook(int oldfd, int newfd) {
    return NativeSocketInterposer::dup2_hook(oldfd, newfd);
  }

  int dup3ThroughHook(int oldfd, int newfd, int flags) {
    return NativeSocketInterposer::dup3_hook(oldfd, newfd, flags);
  }

  int datagramSocketAtFd(int target_fd) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0 || fd == target_fd) {
      return fd;
    }

    int ret = ::dup2(fd, target_fd);
    int saved_errno = errno;
    ::close(fd);
    errno = saved_errno;
    return ret;
  }
};

class LibraryPatcherImportTest : public ::testing::Test {
protected:
  void SetUp() override {
    LibraryPatcher::unpatch_socket_functions();
  }

  void TearDown() override {
    LibraryPatcher::unpatch_socket_functions();
    cache.reset();
  }

  void initializeImports(size_t count) {
    imports[0] = reinterpret_cast<void*>(stub_read);
    imports[1] = reinterpret_cast<void*>(stub_write);
    imports[2] = reinterpret_cast<void*>(stub_recv);
    cache = std::make_unique<CodeCache>("import-test", -1,
                                        NO_MIN_ADDRESS, NO_MAX_ADDRESS,
                                        nullptr, true);
    for (size_t index = 0; index < count; index++) {
      cache->addImport(&imports[index], "read");
    }
  }

  std::unique_ptr<CodeCache> cache;
  void* imports[3] = {};
};

} // namespace

TEST_F(NativeSocketInterposerHookTest, InactiveHookForwardsWithoutChangingErrno) {
  g_send_ret = 13;
  char buf[8] = {};

  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::send_hook(0, buf, sizeof(buf), 0);

  EXPECT_EQ(13, ret);
  EXPECT_EQ(1, g_send_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest,
       OriginalFunctionCanBePublishedWhileHooksReadIt) {
  constexpr int iterations = 100000;
  std::atomic<bool> start{false};
  char buffer[1] = {};

  std::thread reader([&]() {
    while (!start.load(std::memory_order_acquire)) {
    }
    for (int index = 0; index < iterations; index++) {
      NativeSocketInterposer::send_hook(0, buffer, sizeof(buffer), 0);
    }
  });

  start.store(true, std::memory_order_release);
  for (int index = 0; index < iterations; index++) {
    setOriginalFunction(
        NativeSocketInterposer::HOOK_SEND,
        reinterpret_cast<void*>(index % 2 == 0 ? stub_send : sampler_stub_send));
  }
  reader.join();

  EXPECT_EQ(iterations, g_send_calls.load() + g_sampler_send_calls.load());
  setOriginalFunction(NativeSocketInterposer::HOOK_SEND,
                      reinterpret_cast<void*>(stub_send));
}

TEST_F(NativeSocketInterposerHookTest, ActiveNonSocketReadPreservesEntryErrno) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  g_read_ret = 7;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::read_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(7, ret);
  EXPECT_EQ(1, g_read_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, ActiveStreamSocketWriteForwards) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  g_write_ret = 5;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::write_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(5, ret);
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       CombinedActiveStreamSendUsesSharedRawSyscall) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedNativeSocketInterposerActive interposer_active(true);
  ScopedNativeSocketSamplerActive sampler_active(true);
  g_send_ret = 11;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::send_hook(fds[0], buf, sizeof(buf), 0);

  EXPECT_EQ(11, ret);
  EXPECT_EQ(1, g_send_calls.load());
  EXPECT_EQ(0, g_sampler_send_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       CombinedActiveStreamWriteUsesSharedRawSyscall) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedNativeSocketInterposerActive interposer_active(true);
  ScopedNativeSocketSamplerActive sampler_active(true);
  g_write_ret = 11;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::write_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(11, ret);
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(0, g_sampler_write_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       SamplerOnlyStreamWriteClassifiesThroughSamplerClassifier) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedNativeSocketInterposerActive interposer_active(false);
  ScopedNativeSocketSamplerActive sampler_active(true);
  ScopedFdProbeOverride override(recording_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  g_sampler_write_ret = 23;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::write_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(23, ret);
  EXPECT_EQ(0, g_write_calls.load());
  EXPECT_EQ(1, g_sampler_write_calls.load());
  EXPECT_EQ(1, g_fd_probe_calls.load())
      << "sampler-only path must classify through its NativeFdClassifier instance";
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       CombinedActiveStreamWriteClassifiesOnceAndRecordsAfterTaskBlockScope) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedNativeSocketInterposerActive interposer_active(true);
  ScopedNativeSocketSamplerActive sampler_active(true);
  ScopedFdProbeOverride override(recording_fd_probe);
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  NativeSocketSampler::setHookObserverForTest(native_socket_sampler_observer);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  g_write_ret = 31;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  ssize_t ret = NativeSocketInterposer::write_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(31, ret);
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(0, g_sampler_write_calls.load());
  EXPECT_EQ(1, g_fd_probe_calls.load());
  EXPECT_LT(0, g_taskblock_enter_sequence.load());
  EXPECT_LT(g_taskblock_enter_sequence.load(), g_raw_syscall_sequence.load());
  EXPECT_LT(g_raw_syscall_sequence.load(), g_taskblock_exit_sequence.load());
  EXPECT_LT(g_taskblock_exit_sequence.load(), g_sampler_record_sequence.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, CloseForwardsAndPreservesErrno) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  g_close_ret = 0;
  g_close_errno = E2BIG;

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = ERANGE;
  int ret = NativeSocketInterposer::close_hook(fds[0]);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_close_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, NullStreamSendOriginalReturnsEnosys) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  setOriginalFunction(NativeSocketInterposer::HOOK_SEND, nullptr);
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = 0;
  ssize_t ret = NativeSocketInterposer::send_hook(fds[0], buf, sizeof(buf), 0);

  EXPECT_EQ(-1, ret);
  EXPECT_EQ(ENOSYS, errno);
  EXPECT_EQ(0, g_send_calls.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, NullStreamRecvOriginalReturnsEnosys) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  setOriginalFunction(NativeSocketInterposer::HOOK_RECV, nullptr);
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = 0;
  ssize_t ret = NativeSocketInterposer::recv_hook(fds[0], buf, sizeof(buf), 0);

  EXPECT_EQ(-1, ret);
  EXPECT_EQ(ENOSYS, errno);
  EXPECT_EQ(0, g_recv_calls.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, NullStreamWriteOriginalReturnsEnosys) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  setOriginalFunction(NativeSocketInterposer::HOOK_WRITE, nullptr);
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = 0;
  ssize_t ret = NativeSocketInterposer::write_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(-1, ret);
  EXPECT_EQ(ENOSYS, errno);
  EXPECT_EQ(0, g_write_calls.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, NullStreamReadOriginalReturnsEnosys) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  setOriginalFunction(NativeSocketInterposer::HOOK_READ, nullptr);
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = 0;
  ssize_t ret = NativeSocketInterposer::read_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(-1, ret);
  EXPECT_EQ(ENOSYS, errno);
  EXPECT_EQ(0, g_read_calls.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerFdTest, CloseFallsBackToSyscallWhenOriginalIsMissing) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE, nullptr);

  errno = E2BIG;
  int ret = closeThroughHook(fds[0]);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(E2BIG, errno);
  errno = 0;
  EXPECT_EQ(-1, close(fds[0]));
  EXPECT_EQ(EBADF, errno);
  close(fds[1]);
}

TEST(LibraryPatcherSocketStateTest, ConditionalUnpatchClearsSocketActiveWhenOwnersInactive) {
  bool saved_active =
      LibraryPatcher::_socket_active.exchange(true, std::memory_order_acq_rel);

  EXPECT_TRUE(LibraryPatcher::unpatch_socket_functions_if_inactive());
  EXPECT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));

  LibraryPatcher::_socket_active.store(saved_active, std::memory_order_release);
}

TEST(LibraryPatcherSocketStateTest, ConditionalUnpatchKeepsSocketActiveWhenSamplerActive) {
  bool saved_active =
      LibraryPatcher::_socket_active.exchange(true, std::memory_order_acq_rel);
  ScopedNativeSocketSamplerActive sampler_active(true);

  EXPECT_FALSE(LibraryPatcher::unpatch_socket_functions_if_inactive());
  EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));

  LibraryPatcher::_socket_active.store(saved_active, std::memory_order_release);
}

TEST(LibraryPatcherSocketStateTest, ConditionalUnpatchKeepsSocketActiveWhenInterposerActive) {
  bool saved_active =
      LibraryPatcher::_socket_active.exchange(true, std::memory_order_acq_rel);
  ScopedNativeSocketInterposerActive interposer_active(true);

  EXPECT_FALSE(LibraryPatcher::unpatch_socket_functions_if_inactive());
  EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));

  LibraryPatcher::_socket_active.store(saved_active, std::memory_order_release);
}

TEST(LibraryPatcherSocketStateTest,
     RefreshDoesNotPatchAfterSocketHooksBecomeInactive) {
  LibraryPatcher::unpatch_socket_functions();

  EXPECT_FALSE(LibraryPatcher::patch_socket_functions(true));
  EXPECT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
  EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(0, LibraryPatcher::socket_library_count_for_test());
}

TEST_F(LibraryPatcherImportTest, PatchesAndRestoresEveryImportLocation) {
  initializeImports(3);
  void* originals[3] = {imports[0], imports[1], imports[2]};
  void* hook = reinterpret_cast<void*>(NativeSocketInterposer::read_hook);

  EXPECT_EQ(3, LibraryPatcher::patch_socket_import_for_test(
                   cache.get(), im_read, hook, "read"));
  EXPECT_EQ(3, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(hook, imports[0]);
  EXPECT_EQ(hook, imports[1]);
  EXPECT_EQ(hook, imports[2]);

  EXPECT_EQ(0, LibraryPatcher::patch_socket_import_for_test(
                   cache.get(), im_read, hook, "read"));
  EXPECT_EQ(3, LibraryPatcher::socket_patch_count_for_test());

  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(originals[0], imports[0]);
  EXPECT_EQ(originals[1], imports[1]);
  EXPECT_EQ(originals[2], imports[2]);
  EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
}

TEST_F(LibraryPatcherImportTest, PatchesSingleImportLocation) {
  initializeImports(1);
  void* original = imports[0];
  void* hook = reinterpret_cast<void*>(NativeSocketInterposer::read_hook);

  EXPECT_EQ(1, LibraryPatcher::patch_socket_import_for_test(
                   cache.get(), im_read, hook, "read"));
  EXPECT_EQ(hook, imports[0]);
  EXPECT_EQ(1, LibraryPatcher::socket_patch_count_for_test());

  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(original, imports[0]);
}

TEST_F(LibraryPatcherImportTest, MissingImportDoesNotConsumePatchSlot) {
  initializeImports(1);
  void* hook = reinterpret_cast<void*>(NativeSocketInterposer::send_hook);

  EXPECT_EQ(0, LibraryPatcher::patch_socket_import_for_test(
                   cache.get(), im_send, hook, "send"));
  EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
}

TEST(LibraryPatcherDsoLifetimeTest, RetainsPatchedLibraryUntilImportsAreRestored) {
  char cwd[PATH_MAX - 64];
  ASSERT_NE(nullptr, getcwd(cwd, sizeof(cwd)));
  char path[PATH_MAX];
  snprintf(path, sizeof(path),
           "%s/../build/test/resources/native-libs/unloadable-io-lib/"
           "libunloadable-io.so",
           cwd);

  void* handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
  ASSERT_NE(nullptr, handle) << dlerror();
  void* symbol = dlsym(handle, "unloadable_read");
  ASSERT_NE(nullptr, symbol) << dlerror();

  Libraries::instance()->updateSymbols(false);
  CodeCache* lib =
      Libraries::instance()->findLibraryByName("libunloadable-io");
  ASSERT_NE(nullptr, lib);
  ASSERT_EQ(1u, lib->importCount(im_read));

  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(1, LibraryPatcher::patch_socket_import_for_test(
                   lib, im_read,
                   reinterpret_cast<void*>(NativeSocketInterposer::read_hook),
                   "read", true));
  EXPECT_EQ(1, LibraryPatcher::socket_library_count_for_test());

  ASSERT_EQ(0, dlclose(handle));
  Dl_info info;
  EXPECT_NE(0, dladdr(symbol, &info));

  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(0, LibraryPatcher::socket_library_count_for_test());
  if (OS::isMusl()) {
    EXPECT_NE(0, dladdr(symbol, &info));
  } else {
    EXPECT_EQ(0, dladdr(symbol, &info));
  }
}

TEST_F(NativeSocketInterposerHookTest, ActiveStreamSocketConnectForwards) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  g_connect_ret = 0;

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::connect_hook(fds[0], nullptr, 0);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_connect_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, ActiveStreamSocketAcceptForwards) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  g_accept_ret = 17;

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::accept_hook(fds[0], nullptr, nullptr);

  EXPECT_EQ(17, ret);
  EXPECT_EQ(1, g_accept_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, ActiveStreamSocketAccept4Forwards) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  g_accept4_ret = 19;

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::accept4_hook(fds[0], nullptr, nullptr, 0);

  EXPECT_EQ(19, ret);
  EXPECT_EQ(1, g_accept4_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, ActiveDatagramRecvfromForwards) {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  ASSERT_GE(fd, 0);
  g_recvfrom_ret = 3;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::recvfrom_hook(fd, buf, sizeof(buf), 0,
                                                      nullptr, nullptr);

  EXPECT_EQ(3, ret);
  EXPECT_EQ(1, g_recvfrom_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fd);
}

TEST_F(NativeSocketInterposerHookTest, ActiveDatagramRecvmsgForwards) {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  ASSERT_GE(fd, 0);
  g_recvmsg_ret = 4;
  struct msghdr msg = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::recvmsg_hook(fd, &msg, 0);

  EXPECT_EQ(4, ret);
  EXPECT_EQ(1, g_recvmsg_calls.load());
  EXPECT_EQ(E2BIG, errno);
  close(fd);
}

TEST_F(NativeSocketInterposerHookTest, ActiveEpollZeroTimeoutForwards) {
  g_epoll_wait_ret = 0;
  struct epoll_event events[1] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::epoll_wait_hook(31, events, 1, 0);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_epoll_wait_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest, ActiveEpollPwaitZeroTimeoutForwards) {
  g_epoll_pwait_ret = 0;
  struct epoll_event events[1] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::epoll_pwait_hook(31, events, 1, 0, nullptr);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_epoll_pwait_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest, ActivePollZeroTimeoutForwards) {
  g_poll_ret = 0;
  struct pollfd fds[1] = {{0, POLLIN, 0}};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::poll_hook(fds, 1, 0);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_poll_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest, ActivePpollZeroTimeoutForwards) {
  g_ppoll_ret = 0;
  struct pollfd fds[1] = {{0, POLLIN, 0}};
  struct timespec timeout = {0, 0};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::ppoll_hook(fds, 1, &timeout, nullptr);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_ppoll_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest, ActiveSelectZeroTimeoutForwards) {
  g_select_ret = 0;
  struct timeval timeout = {0, 0};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::select_hook(1, nullptr, nullptr, nullptr,
                                                &timeout);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_select_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest, ActivePselectZeroTimeoutForwards) {
  g_pselect_ret = 0;
  struct timespec timeout = {0, 0};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::pselect_hook(1, nullptr, nullptr, nullptr,
                                                 &timeout, nullptr);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_pselect_calls.load());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerHookTest, ActiveEpollPositiveTimeoutEligibleForwards) {
  g_epoll_wait_ret = 1;
  g_epoll_pwait_ret = 2;
  struct epoll_event events[1] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  EXPECT_EQ(1, NativeSocketInterposer::epoll_wait_hook(31, events, 1, 1));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(2, NativeSocketInterposer::epoll_pwait_hook(31, events, 1, -1, nullptr));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, g_epoll_wait_calls.load());
  EXPECT_EQ(1, g_epoll_pwait_calls.load());
}

TEST_F(NativeSocketInterposerHookTest, ActivePollPositiveAndNullTimeoutEligibleForwards) {
  g_poll_ret = 1;
  g_ppoll_ret = 2;
  struct pollfd fds[1] = {{0, POLLIN, 0}};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  EXPECT_EQ(1, NativeSocketInterposer::poll_hook(fds, 1, -1));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(2, NativeSocketInterposer::ppoll_hook(fds, 1, nullptr, nullptr));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, g_poll_calls.load());
  EXPECT_EQ(1, g_ppoll_calls.load());
}

TEST_F(NativeSocketInterposerHookTest, ActiveSelectPositiveAndNullTimeoutEligibleForwards) {
  g_select_ret = 1;
  g_pselect_ret = 2;
  struct timeval select_timeout = {1, 0};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  EXPECT_EQ(1, NativeSocketInterposer::select_hook(1, nullptr, nullptr, nullptr,
                                                  &select_timeout));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(2, NativeSocketInterposer::pselect_hook(1, nullptr, nullptr, nullptr,
                                                   nullptr, nullptr));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, g_select_calls.load());
  EXPECT_EQ(1, g_pselect_calls.load());
}

TEST(NativeBlockScopeTest, EncodesKindAndBlockerId) {
  EXPECT_EQ((static_cast<u64>(NativeBlockKind::CONNECT) << 32) | 17,
            NativeBlockScope::blocker(NativeBlockKind::CONNECT, 17));
}

TEST(NativeBlockScopeTest, DisabledTaskBlockGateLeavesScopeInactiveAndPreservesErrno) {
  ScopedTaskBlockEnabled task_block_enabled(false);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeSocketInterposerFdTest, ClassifiesStreamSocketsOnly) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(stream_fds[0]));
  ASSERT_EQ(0, closeThroughHook(stream_fds[0]));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));

  int datagram_fd = socket(AF_INET, SOCK_DGRAM, 0);
  ASSERT_GE(datagram_fd, 0);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));
  ASSERT_EQ(0, closeThroughHook(datagram_fd));
}

TEST_F(NativeSocketInterposerFdTest, ClassifiesDatagramSocketsOnly) {
  int datagram_fd = socket(AF_INET, SOCK_DGRAM, 0);
  ASSERT_GE(datagram_fd, 0);
  EXPECT_TRUE(NativeSocketInterposer::instance()->isDatagramSocket(datagram_fd));
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));
  ASSERT_EQ(0, closeThroughHook(datagram_fd));

  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  EXPECT_FALSE(NativeSocketInterposer::instance()->isDatagramSocket(stream_fds[0]));
  ASSERT_EQ(0, closeThroughHook(stream_fds[0]));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, TransientFdProbeFailureIsNotCached) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = -1;
  g_fd_probe_errno = EIO;
  g_fd_probe_so_type = 0;
  int fd = 42;

  EXPECT_FALSE(classifier.isStreamSocket(fd));
  EXPECT_EQ(1, g_fd_probe_calls.load());

  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;

  EXPECT_TRUE(classifier.isStreamSocket(fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  EXPECT_TRUE(classifier.isStreamSocket(fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, NegativeFdDoesNotProbe) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(recording_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_so_type = SOCK_STREAM;

  EXPECT_FALSE(classifier.isStreamSocket(-1));
  EXPECT_FALSE(classifier.isDatagramSocket(-1));
  EXPECT_EQ(0, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, EnotsockFailureIsCachedAsNonSocket) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = -1;
  g_fd_probe_errno = ENOTSOCK;
  g_fd_probe_so_type = 0;

  EXPECT_FALSE(classifier.isStreamSocket(43));
  EXPECT_FALSE(classifier.isDatagramSocket(43));
  EXPECT_EQ(1, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, CacheNonSocketOverridesCachedStreamType) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;

  ASSERT_TRUE(classifier.isStreamSocket(43));
  EXPECT_EQ(1, g_fd_probe_calls.load());

  classifier.cacheNonSocket(43);

  EXPECT_FALSE(classifier.isStreamSocket(43));
  EXPECT_FALSE(classifier.isDatagramSocket(43));
  EXPECT_EQ(1, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, OtherSocketTypeIsCachedAsNeitherStreamNorDatagram) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_RAW;

  EXPECT_FALSE(classifier.isStreamSocket(44));
  EXPECT_FALSE(classifier.isDatagramSocket(44));
  EXPECT_EQ(1, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, HighFdUsesClassifierCache) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(recording_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;

  EXPECT_TRUE(classifier.isStreamSocket(kFdTypeCacheSizeForTest));
  EXPECT_TRUE(classifier.isStreamSocket(kFdTypeCacheSizeForTest));
  EXPECT_EQ(1, g_fd_probe_calls.load());
  EXPECT_EQ(kFdTypeCacheSizeForTest, g_fd_probe_last_fd.load());
}

TEST_F(NativeSocketInterposerFdTest, HighFdTransientProbeFailureIsNotCached) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  int fd = kFdTypeCacheSizeForTest + 1;
  g_fd_probe_calls = 0;
  g_fd_probe_rc = -1;
  g_fd_probe_errno = EIO;
  g_fd_probe_so_type = 0;

  EXPECT_FALSE(classifier.isStreamSocket(fd));
  EXPECT_EQ(1, g_fd_probe_calls.load());

  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;

  EXPECT_TRUE(classifier.isStreamSocket(fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  EXPECT_TRUE(classifier.isStreamSocket(fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, ClearFdTypeInvalidatesHighFdOnly) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  int fd = kFdTypeCacheSizeForTest + 2;
  int other_fd = fd + 1;
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  ASSERT_TRUE(classifier.isStreamSocket(fd));
  ASSERT_TRUE(classifier.isStreamSocket(other_fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  g_fd_probe_so_type = SOCK_DGRAM;
  classifier.clearFdType(fd);

  EXPECT_FALSE(classifier.isStreamSocket(fd));
  EXPECT_TRUE(classifier.isDatagramSocket(fd));
  EXPECT_TRUE(classifier.isStreamSocket(other_fd));
  EXPECT_EQ(3, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, ClearFdTypeCacheInvalidatesHighFds) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  int fd = kFdTypeCacheSizeForTest + 3;
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  ASSERT_TRUE(classifier.isStreamSocket(fd));
  EXPECT_EQ(1, g_fd_probe_calls.load());

  g_fd_probe_so_type = SOCK_DGRAM;
  classifier.clearFdTypeCache();

  EXPECT_FALSE(classifier.isStreamSocket(fd));
  EXPECT_TRUE(classifier.isDatagramSocket(fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, HighFdCacheCollisionReprobesExactFd) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(recording_fd_probe);
  int stream_fd = kFdTypeCacheSizeForTest + 4;
  int datagram_fd = stream_fd + kHighFdCacheSizeForTest;
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;

  g_fd_probe_so_type = SOCK_STREAM;
  ASSERT_TRUE(classifier.isStreamSocket(stream_fd));
  EXPECT_EQ(1, g_fd_probe_calls.load());

  g_fd_probe_so_type = SOCK_DGRAM;
  EXPECT_FALSE(classifier.isStreamSocket(datagram_fd));
  EXPECT_TRUE(classifier.isDatagramSocket(datagram_fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());
  EXPECT_EQ(datagram_fd, g_fd_probe_last_fd.load());

  g_fd_probe_so_type = SOCK_STREAM;
  EXPECT_TRUE(classifier.isStreamSocket(stream_fd));
  EXPECT_EQ(3, g_fd_probe_calls.load());
  EXPECT_EQ(stream_fd, g_fd_probe_last_fd.load());
}

TEST_F(NativeSocketInterposerFdTest, ClearFdTypeInvalidatesOnlyThatFd) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  ASSERT_TRUE(classifier.isStreamSocket(45));
  ASSERT_TRUE(classifier.isStreamSocket(46));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  g_fd_probe_so_type = SOCK_DGRAM;
  classifier.clearFdType(45);

  EXPECT_FALSE(classifier.isStreamSocket(45));
  EXPECT_TRUE(classifier.isDatagramSocket(45));
  EXPECT_TRUE(classifier.isStreamSocket(46));
  EXPECT_EQ(3, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, ClearFdTypeCacheInvalidatesCachedFds) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  ASSERT_TRUE(classifier.isStreamSocket(47));
  EXPECT_EQ(1, g_fd_probe_calls.load());

  g_fd_probe_so_type = SOCK_DGRAM;
  classifier.clearFdTypeCache();

  EXPECT_FALSE(classifier.isStreamSocket(47));
  EXPECT_TRUE(classifier.isDatagramSocket(47));
  EXPECT_EQ(2, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest, ClassifierInstancesHaveIndependentCacheState) {
  NativeFdClassifier first;
  NativeFdClassifier second;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;

  ASSERT_TRUE(first.isStreamSocket(48));
  ASSERT_TRUE(second.isStreamSocket(48));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  first.cacheNonSocket(48);

  EXPECT_FALSE(first.isStreamSocket(48));
  EXPECT_TRUE(second.isStreamSocket(48));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  first.clearFdTypeCache();
  g_fd_probe_so_type = SOCK_DGRAM;

  EXPECT_FALSE(first.isStreamSocket(48));
  EXPECT_TRUE(second.isStreamSocket(48));
  EXPECT_EQ(3, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest,
       SamplerAndInterposerClassifiersHaveIndependentCacheState) {
  NativeSocketInterposer* interposer = NativeSocketInterposer::instance();
  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  interposer->clearFdTypeCache();
  sampler->clearFdCache();
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  const int fd = 49;

  ASSERT_TRUE(interposer->isStreamSocket(fd));
  EXPECT_EQ(1, g_fd_probe_calls.load());
  ASSERT_TRUE(sampler->isSocketForTest(fd));
  EXPECT_EQ(2, g_fd_probe_calls.load());

  g_fd_probe_so_type = SOCK_DGRAM;
  interposer->clearFdType(fd);

  EXPECT_FALSE(interposer->isStreamSocket(fd));
  EXPECT_TRUE(interposer->isDatagramSocket(fd));
  EXPECT_EQ(3, g_fd_probe_calls.load());
  EXPECT_TRUE(sampler->isSocketForTest(fd));
  EXPECT_EQ(3, g_fd_probe_calls.load());

  sampler->clearFdCacheEntry(fd);

  EXPECT_FALSE(sampler->isSocketForTest(fd));
  EXPECT_EQ(4, g_fd_probe_calls.load());
  interposer->clearFdTypeCache();
  sampler->clearFdCache();
}

TEST_F(NativeSocketInterposerFdTest, ConcurrentClassifierReadsAndClearsAreSafe) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(stub_fd_probe);
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  static constexpr int kReaders = 4;
  std::atomic<bool> start{false};
  std::atomic<bool> stop{false};
  std::atomic<int> ready_readers{0};
  std::atomic<int> reads{0};
  int fd = 48;

  std::thread clearer([&]() {
    while (ready_readers.load(std::memory_order_acquire) < kReaders) {
      std::this_thread::yield();
    }
    start.store(true, std::memory_order_release);
    for (int i = 0; i < 1000; i++) {
      g_fd_probe_so_type = (i % 2 == 0) ? SOCK_STREAM : SOCK_DGRAM;
      classifier.clearFdType(fd);
      if ((i % 16) == 0) {
        classifier.clearFdTypeCache();
      }
      std::this_thread::yield();
    }
    stop.store(true, std::memory_order_release);
  });

  std::vector<std::thread> readers;
  for (int i = 0; i < kReaders; i++) {
    readers.emplace_back([&]() {
      ready_readers.fetch_add(1, std::memory_order_release);
      while (!start.load(std::memory_order_acquire)) {
        std::this_thread::yield();
      }
      while (!stop.load(std::memory_order_acquire)) {
        (void)classifier.isStreamSocket(fd);
        (void)classifier.isDatagramSocket(fd);
        reads.fetch_add(1, std::memory_order_relaxed);
      }
    });
  }

  clearer.join();
  for (auto& reader : readers) {
    reader.join();
  }

  EXPECT_GT(reads.load(std::memory_order_relaxed), 0);
  EXPECT_GT(g_fd_probe_calls.load(), 0);
}

TEST_F(NativeSocketInterposerFdTest, CloseHookInvalidatesFdBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  int reused_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(reused_fd));
  ASSERT_EQ(0, closeThroughHook(reused_fd));

  int datagram_fd = datagramSocketAtFd(reused_fd);
  ASSERT_EQ(reused_fd, datagram_fd);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));

  ASSERT_EQ(0, closeThroughHook(datagram_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest,
       CloseHookInvalidatesNativeSocketSamplerFdStateBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  int reused_fd = stream_fds[0];
  EXPECT_TRUE(sampler->isSocketForTest(reused_fd));
  sampler->fdAddrCacheInsertForTest(reused_fd, "127.0.0.1:12345");
  ASSERT_TRUE(sampler->fdAddrCacheContainsForTest(reused_fd));

  errno = E2BIG;
  ASSERT_EQ(0, closeThroughHook(reused_fd));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_FALSE(sampler->fdAddrCacheContainsForTest(reused_fd));

  int datagram_fd = datagramSocketAtFd(reused_fd);
  ASSERT_EQ(reused_fd, datagram_fd);
  EXPECT_FALSE(sampler->isSocketForTest(datagram_fd));

  ASSERT_EQ(0, closeThroughHook(datagram_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, FailedCloseInvalidatesCachesAndPreservesErrno) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  int fd = stream_fds[0];
  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(fd));
  EXPECT_TRUE(sampler->isSocketForTest(fd));
  sampler->fdAddrCacheInsertForTest(fd, "127.0.0.1:12345");
  ASSERT_TRUE(sampler->fdAddrCacheContainsForTest(fd));

  setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE,
                      reinterpret_cast<void*>(stub_close));
  g_close_ret = -1;
  g_close_errno = EINTR;
  uint64_t probes_before = NativeFdClassifier::probeCountForTest();

  errno = E2BIG;
  EXPECT_EQ(-1, closeThroughHook(fd));
  EXPECT_EQ(EINTR, errno);
  EXPECT_FALSE(sampler->fdAddrCacheContainsForTest(fd));
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(fd));
  EXPECT_GT(NativeFdClassifier::probeCountForTest(), probes_before);

  setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE,
                      reinterpret_cast<void*>(::close));
  ASSERT_EQ(0, closeThroughHook(fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, RepeatedCacheClearsDoNotResurrectOldFdType) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  int reused_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(reused_fd));
  ASSERT_EQ(0, close(reused_fd));

  for (int i = 0; i < 1024; i++) {
    NativeSocketInterposer::instance()->clearFdTypeCache();
  }

  int datagram_fd = datagramSocketAtFd(reused_fd);
  ASSERT_EQ(reused_fd, datagram_fd);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));

  ASSERT_EQ(0, closeThroughHook(datagram_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, Dup2InvalidatesTargetFdBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  int pipe_fds[2];
  ASSERT_EQ(0, pipe(pipe_fds));

  int target_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  errno = E2BIG;
  ASSERT_EQ(target_fd, dup2ThroughHook(pipe_fds[0], target_fd));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[0]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest,
       Dup2InvalidatesNativeSocketSamplerTargetFdStateBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  int pipe_fds[2];
  ASSERT_EQ(0, pipe(pipe_fds));

  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  int target_fd = stream_fds[0];
  EXPECT_TRUE(sampler->isSocketForTest(target_fd));
  sampler->fdAddrCacheInsertForTest(target_fd, "127.0.0.1:12345");
  ASSERT_TRUE(sampler->fdAddrCacheContainsForTest(target_fd));

  errno = E2BIG;
  ASSERT_EQ(target_fd, dup2ThroughHook(pipe_fds[0], target_fd));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_FALSE(sampler->fdAddrCacheContainsForTest(target_fd));
  EXPECT_FALSE(sampler->isSocketForTest(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[0]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, FailedDup2DoesNotInvalidateTargetFd) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  int target_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  errno = 0;
  EXPECT_EQ(-1, dup2ThroughHook(-1, target_fd));
  EXPECT_EQ(EBADF, errno);
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest,
       FailedDup2DoesNotInvalidateNativeSocketSamplerTargetFdState) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  int target_fd = stream_fds[0];
  EXPECT_TRUE(sampler->isSocketForTest(target_fd));
  sampler->fdAddrCacheInsertForTest(target_fd, "127.0.0.1:12345");
  ASSERT_TRUE(sampler->fdAddrCacheContainsForTest(target_fd));

  errno = 0;
  EXPECT_EQ(-1, dup2ThroughHook(-1, target_fd));
  EXPECT_EQ(EBADF, errno);
  EXPECT_TRUE(sampler->isSocketForTest(target_fd));
  EXPECT_TRUE(sampler->fdAddrCacheContainsForTest(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

#ifdef SYS_dup3
TEST_F(NativeSocketInterposerFdTest, Dup3InvalidatesTargetFdBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  int pipe_fds[2];
  ASSERT_EQ(0, pipe(pipe_fds));

  int target_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  errno = E2BIG;
  ASSERT_EQ(target_fd, dup3ThroughHook(pipe_fds[0], target_fd, 0));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[0]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, Dup3PreservesErrnoOnSuccessfulInvalidation) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  int pipe_fds[2];
  ASSERT_EQ(0, pipe(pipe_fds));

  int target_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  errno = E2BIG;
  ASSERT_EQ(target_fd, dup3ThroughHook(pipe_fds[0], target_fd, O_CLOEXEC));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[0]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest,
       Dup3InvalidatesNativeSocketSamplerTargetFdStateBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  int pipe_fds[2];
  ASSERT_EQ(0, pipe(pipe_fds));

  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  int target_fd = stream_fds[0];
  EXPECT_TRUE(sampler->isSocketForTest(target_fd));
  sampler->fdAddrCacheInsertForTest(target_fd, "127.0.0.1:12345");
  ASSERT_TRUE(sampler->fdAddrCacheContainsForTest(target_fd));

  errno = E2BIG;
  ASSERT_EQ(target_fd, dup3ThroughHook(pipe_fds[0], target_fd, 0));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_FALSE(sampler->fdAddrCacheContainsForTest(target_fd));
  EXPECT_FALSE(sampler->isSocketForTest(target_fd));

  ASSERT_EQ(0, closeThroughHook(target_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[0]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[1]));
}
#endif

TEST_F(NativeSocketInterposerFdTest, ConcurrentFdReuseInvalidationDoesNotPreserveStaleStreamType) {
  for (int i = 0; i < 64; i++) {
    int stream_fds[2];
    ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
    int reused_fd = stream_fds[0];
    ASSERT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(reused_fd));

    std::atomic<bool> done{false};
    std::thread reader([&]() {
      while (!done.load(std::memory_order_acquire)) {
        (void)NativeSocketInterposer::instance()->isStreamSocket(reused_fd);
        std::this_thread::yield();
      }
    });

    ASSERT_EQ(0, closeThroughHook(reused_fd));
    done.store(true, std::memory_order_release);
    reader.join();

    int datagram_fd = datagramSocketAtFd(reused_fd);
    ASSERT_EQ(reused_fd, datagram_fd);

    EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));
    EXPECT_TRUE(NativeSocketInterposer::instance()->isDatagramSocket(datagram_fd));
    ASSERT_EQ(0, closeThroughHook(datagram_fd));
    ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  }
}

TEST_F(NativeSocketInterposerFdTest, RejectsNonSockets) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(fds[0]));
  ASSERT_EQ(0, closeThroughHook(fds[0]));
  ASSERT_EQ(0, closeThroughHook(fds[1]));
}

#endif // __linux__
