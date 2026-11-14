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
#include "vmEntry.h"

#include <atomic>
#include <cerrno>
#include <chrono>
#include <future>
#include <cstdio>
#include <cstring>
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
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <vector>

// Unit-only dispatch control, not evidence of a running JVM.
class VMTestAccessor {
public:
  static bool exchangeHotspot(bool value) {
    bool saved = VM::_hotspot;
    VM::_hotspot = value;
    return saved;
  }
};

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
std::atomic<bool> g_blocking_probe_started{false};
std::atomic<bool> g_release_blocking_probe{false};
std::atomic<int> g_sequence{0};
std::atomic<int> g_raw_syscall_sequence{0};
std::atomic<int> g_taskblock_enter_sequence{0};
std::atomic<int> g_taskblock_exit_sequence{0};
std::atomic<u32> g_taskblock_kind{0};
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

int blocking_stream_fd_probe(int, int *so_type, int *probe_errno) {
  g_blocking_probe_started.store(true, std::memory_order_release);
  while (!g_release_blocking_probe.load(std::memory_order_acquire)) {
    std::this_thread::yield();
  }
  *so_type = SOCK_STREAM;
  *probe_errno = 0;
  return 0;
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

class ScopedHookOwnerPid {
public:
  explicit ScopedHookOwnerPid(pid_t pid)
      : _saved(NativeSocketInterposer::setHookOwnerPidForTest(pid)) {}
  ~ScopedHookOwnerPid() {
    NativeSocketInterposer::setHookOwnerPidForTest(_saved);
  }

private:
  pid_t _saved;
};

void expectJavaProfilerMark(void* fn_addr) {
  CodeCache* lib = Libraries::instance()->findLibraryByAddress(fn_addr);
  ASSERT_NE(nullptr, lib);
  const char* name = nullptr;
  lib->binarySearch(fn_addr, &name);
  ASSERT_NE(nullptr, name);
  EXPECT_EQ(MARK_JAVA_PROFILER, NativeFunc::read_mark(name)) << name;
}

TEST(NativeSocketInterposerMarkTest, MarksEverySampledSocketHookLayer) {
  Libraries::instance()->updateSymbols(false);
  ASSERT_TRUE(NativeSocketInterposer::markProfilerHooks());

  void* sampler_hooks[] = {
      reinterpret_cast<void*>(NativeSocketSampler::send_hook),
      reinterpret_cast<void*>(NativeSocketSampler::recv_hook),
      reinterpret_cast<void*>(NativeSocketSampler::write_hook),
      reinterpret_cast<void*>(NativeSocketSampler::read_hook),
  };
  for (void* hook : sampler_hooks) {
    expectJavaProfilerMark(hook);
  }

  const NativeSocketInterposer::NativeIoHookSpec* specs =
      NativeSocketInterposer::hookSpecs();
  for (int hook_index = NativeSocketInterposer::HOOK_SEND;
       hook_index <= NativeSocketInterposer::HOOK_READ; hook_index++) {
    expectJavaProfilerMark(specs[hook_index].hook);
    expectJavaProfilerMark(specs[hook_index].fork_safe_hook);
  }
}

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

void native_block_observer(const char* phase, NativeBlockKind kind, int) {
  int sequence = g_sequence.fetch_add(1) + 1;
  if (strcmp(phase, "enter") == 0) {
    g_taskblock_kind.store(static_cast<u32>(kind), std::memory_order_release);
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
    g_taskblock_kind = 0;
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
  bool saved_interposer_active;

  void SetUp() override {
    saved_interposer_active = NativeSocketInterposer::instance()->setActiveForTest(true);
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE,
                        reinterpret_cast<void*>(::close));
    setOriginalFunction(NativeSocketInterposer::HOOK_DUP2,
                        reinterpret_cast<void*>(::dup2));
    setOriginalFunction(NativeSocketInterposer::HOOK_DUP3, nullptr);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
  }

  void TearDown() override {
    NativeSocketInterposer::instance()->setActiveForTest(saved_interposer_active);
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
       InactiveStreamHooksDoNotClassifyOrEnterTaskBlock) {
  ScopedNativeSocketInterposerActive interposer_active(false);
  ScopedNativeSocketSamplerActive sampler_active(false);
  NativeSocketInterposer::instance()->clearFdTypeCache();
  NativeFdClassifier::resetProbeCountForTest();
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  g_send_ret = 11;
  g_recv_ret = 12;
  g_write_ret = 13;
  g_read_ret = 14;
  char buffer[1] = {};

  errno = E2BIG;
  EXPECT_EQ(11, NativeSocketInterposer::send_hook(-1, buffer, sizeof(buffer), 0));
  EXPECT_EQ(12, NativeSocketInterposer::recv_hook(-1, buffer, sizeof(buffer), 0));
  EXPECT_EQ(13, NativeSocketInterposer::write_hook(-1, buffer, sizeof(buffer)));
  EXPECT_EQ(14, NativeSocketInterposer::read_hook(-1, buffer, sizeof(buffer)));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, g_send_calls.load());
  EXPECT_EQ(1, g_recv_calls.load());
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(1, g_read_calls.load());
  EXPECT_EQ(0u, NativeFdClassifier::probeCountForTest());
  EXPECT_EQ(0, g_taskblock_enter_sequence.load());

  // A real stream fd exercises the successful-classification path as well.
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  EXPECT_EQ(13, NativeSocketInterposer::write_hook(fds[0], buffer, sizeof(buffer)));
  EXPECT_EQ(0u, NativeFdClassifier::probeCountForTest());
  EXPECT_EQ(0, g_taskblock_enter_sequence.load());
  close(fds[0]);
  close(fds[1]);
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
  ScopedNativeSocketInterposerActive interposer_active(true);
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  g_write_ret = 5;
  char buf[8] = {};
  NativeBlockScope::setHookObserverForTest(native_block_observer);

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::write_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(5, ret);
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(static_cast<u32>(NativeBlockKind::STREAM_SOCKET_WRITE),
            g_taskblock_kind.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, ActiveStreamSocketReadUsesReadBlockKind) {
  ScopedNativeSocketInterposerActive interposer_active(true);
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  g_read_ret = 5;
  char buf[8] = {};
  NativeBlockScope::setHookObserverForTest(native_block_observer);

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  ssize_t ret = NativeSocketInterposer::read_hook(fds[0], buf, sizeof(buf));

  EXPECT_EQ(5, ret);
  EXPECT_EQ(1, g_read_calls.load());
  EXPECT_EQ(static_cast<u32>(NativeBlockKind::STREAM_SOCKET_READ),
            g_taskblock_kind.load());
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

TEST_F(NativeSocketInterposerHookTest,
       ForkSafeOwnerProcessUsesInstrumentedHook) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedHookOwnerPid owner(getpid());
  ScopedNativeSocketInterposerActive interposer_active(true);
  ScopedFdProbeOverride override(recording_fd_probe);
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  g_write_ret = 37;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  ssize_t ret = NativeSocketInterposer::fork_safe_write_hook(
      fds[0], buf, sizeof(buf));

  EXPECT_EQ(37, ret);
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(1, g_fd_probe_calls.load());
  EXPECT_LT(0, g_taskblock_enter_sequence.load());
  EXPECT_LT(g_taskblock_enter_sequence.load(), g_raw_syscall_sequence.load());
  EXPECT_LT(g_raw_syscall_sequence.load(), g_taskblock_exit_sequence.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       ForkSafeChildBypassesProfilerState) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedHookOwnerPid owner(getpid() + 1);
  ScopedNativeSocketInterposerActive interposer_active(true);
  ScopedNativeSocketSamplerActive sampler_active(true);
  ScopedFdProbeOverride override(recording_fd_probe);
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  NativeSocketSampler::setHookObserverForTest(native_socket_sampler_observer);
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  g_send_ret = 41;
  char buf[8] = {};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  ssize_t ret = NativeSocketInterposer::fork_safe_send_hook(
      fds[0], buf, sizeof(buf), 0);

  EXPECT_EQ(41, ret);
  EXPECT_EQ(1, g_send_calls.load());
  EXPECT_EQ(0, g_sampler_send_calls.load());
  EXPECT_EQ(0, g_fd_probe_calls.load());
  EXPECT_EQ(0, g_taskblock_enter_sequence.load());
  EXPECT_EQ(0, g_taskblock_exit_sequence.load());
  EXPECT_EQ(0, g_sampler_record_sequence.load());
  EXPECT_EQ(E2BIG, errno);
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       ForkSafeChildReadAndPollBypassProfilerState) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedHookOwnerPid owner(getpid() + 1);
  ScopedNativeSocketInterposerActive interposer_active(true);
  ScopedFdProbeOverride override(recording_fd_probe);
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  g_read_ret = 47;
  g_poll_ret = 3;
  char buf[8] = {};
  struct pollfd poll_fd = {fds[0], POLLIN, 0};

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  EXPECT_EQ(47, NativeSocketInterposer::fork_safe_read_hook(
                    fds[0], buf, sizeof(buf)));
  EXPECT_EQ(3, NativeSocketInterposer::fork_safe_poll_hook(&poll_fd, 1, 10));

  EXPECT_EQ(1, g_read_calls.load());
  EXPECT_EQ(1, g_poll_calls.load());
  EXPECT_EQ(0, g_fd_probe_calls.load());
  EXPECT_EQ(0, g_taskblock_enter_sequence.load());
  EXPECT_EQ(0, g_taskblock_exit_sequence.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest,
       ForkSafeChildNullOriginalReturnsEnosysWithoutInstrumentation) {
  ScopedHookOwnerPid owner(getpid() + 1);
  setOriginalFunction(NativeSocketInterposer::HOOK_SEND, nullptr);
  char buf[8] = {};

  errno = 0;
  ssize_t ret = NativeSocketInterposer::fork_safe_send_hook(
      -1, buf, sizeof(buf), 0);

  EXPECT_EQ(-1, ret);
  EXPECT_EQ(ENOSYS, errno);
  EXPECT_EQ(0, g_send_calls.load());
  EXPECT_EQ(0, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerHookTest,
       ForkSafeChildCloseDoesNotClearProfilerCaches) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedHookOwnerPid owner(getpid() + 1);
  ScopedFdProbeOverride override(recording_fd_probe);
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  g_close_ret = 0;
  g_close_errno = E2BIG;

  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(fds[0]));
  NativeSocketSampler::instance()->fdAddrCacheInsertForTest(fds[0], "cached");
  g_fd_probe_calls = 0;
  errno = ERANGE;
  int ret = NativeSocketInterposer::fork_safe_close_hook(fds[0]);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_close_calls.load());
  EXPECT_EQ(E2BIG, errno);
  EXPECT_TRUE(NativeSocketSampler::instance()->fdAddrCacheContainsForTest(fds[0]));
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(fds[0]));
  EXPECT_EQ(0, g_fd_probe_calls.load());
  close(fds[0]);
  close(fds[1]);
}

TEST_F(NativeSocketInterposerHookTest, ForkSafeHookDetectsRealForkChild) {
  int fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, fds));
  ScopedHookOwnerPid owner(getpid());
  ScopedNativeSocketInterposerActive interposer_active(true);
  g_send_ret = 43;
  char buf[8] = {};

  pid_t child = fork();
  ASSERT_GE(child, 0);
  if (child == 0) {
    ssize_t ret = NativeSocketInterposer::fork_safe_send_hook(
        fds[0], buf, sizeof(buf), 0);
    _exit(ret == 43 ? 0 : 1);
  }

  int status = 0;
  ASSERT_EQ(child, waitpid(child, &status, 0));
  EXPECT_TRUE(WIFEXITED(status));
  EXPECT_EQ(0, WEXITSTATUS(status));
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

TEST(LibraryPatcherSocketStateTest,
     RestrictsSocketHooksToJdkNetworkingLibraries) {
  CodeCache standard("libnet.so");
  CodeCache openjdk_java("libjava.so");
  CodeCache partial_ibm_java("libjava.so");
  CodeCache ibm_java("libjava.so");
  CodeCache marked_other("libother.so");

  char marker_addresses[4] = {};
  partial_ibm_java.add(&marker_addresses[0], 1, "JCL_Send");
  const char* markers[] = {
      "JCL_Send", "JCL_Recv", "JCL_Connect", "JCL_Accept"};
  for (size_t index = 0; index < 4; index++) {
    ibm_java.add(&marker_addresses[index], 1, markers[index]);
    marked_other.add(&marker_addresses[index], 1, markers[index]);
  }

  EXPECT_EQ(SOCKET_PATCH_STANDARD_JDK_NETWORK,
            LibraryPatcher::socket_patch_target_for_test(
                &standard, "libnet.so", true));
  EXPECT_EQ(SOCKET_PATCH_STANDARD_JDK_NETWORK,
            LibraryPatcher::socket_patch_target_for_test(
                &standard, "libnio.so", true));

  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &openjdk_java, "libjava.so", true));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &partial_ibm_java, "libjava.so", true));
  EXPECT_EQ(SOCKET_PATCH_IBM_JCL_BRIDGE,
            LibraryPatcher::socket_patch_target_for_test(
                &ibm_java, "libjava.so", true));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &marked_other, "libother.so", true));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &ibm_java, "libjava.so", false));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &standard, "libnative-plugin.so", true));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &standard, "libnet.so.backup", true));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &standard, "libnet.so", false));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                &standard, nullptr, true));
  EXPECT_EQ(SOCKET_PATCH_NONE,
            LibraryPatcher::socket_patch_target_for_test(
                nullptr, "libnet.so", true));

  void* standard_hook = LibraryPatcher::socket_hook_for_target_for_test(
      SOCKET_PATCH_STANDARD_JDK_NETWORK, NativeSocketInterposer::HOOK_SEND);
  void* ibm_hook = LibraryPatcher::socket_hook_for_target_for_test(
      SOCKET_PATCH_IBM_JCL_BRIDGE, NativeSocketInterposer::HOOK_SEND);
  EXPECT_EQ(reinterpret_cast<void*>(NativeSocketInterposer::send_hook),
            standard_hook);
  EXPECT_EQ(reinterpret_cast<void*>(NativeSocketInterposer::fork_safe_send_hook),
            ibm_hook);
  EXPECT_NE(standard_hook, ibm_hook);
  for (int hook_index = 0;
       hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS; hook_index++) {
    void* regular = LibraryPatcher::socket_hook_for_target_for_test(
        SOCKET_PATCH_STANDARD_JDK_NETWORK, hook_index);
    void* fork_safe = LibraryPatcher::socket_hook_for_target_for_test(
        SOCKET_PATCH_IBM_JCL_BRIDGE, hook_index);
    EXPECT_NE(nullptr, regular) << hook_index;
    EXPECT_NE(nullptr, fork_safe) << hook_index;
    EXPECT_NE(regular, fork_safe) << hook_index;
  }
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

namespace {

class ScopedSocketImportFailure {
public:
  ScopedSocketImportFailure(CodeCache* target, void** written_slot)
      : _target(target), _written_slot(written_slot), _previous(_current) {
    _current = this;
    _previous_predicate = LibraryPatcher::exchangeSocketImportFailureForTest(failRead);
  }

  ~ScopedSocketImportFailure() {
    LibraryPatcher::exchangeSocketImportFailureForTest(_previous_predicate);
    _current = _previous;
  }

  int calls = 0;
  bool saw_partial_write = false;

private:
  static bool failRead(CodeCache* lib, ImportId id, size_t index) {
    if (_current == nullptr || lib != _current->_target || id != im_read || index != 0) {
      return false;
    }
    _current->calls++;
    _current->saw_partial_write =
        __atomic_load_n(_current->_written_slot, __ATOMIC_ACQUIRE) ==
        reinterpret_cast<void*>(NativeSocketInterposer::write_hook);
    return true;
  }

  CodeCache* _target;
  void** _written_slot;
  ScopedSocketImportFailure* _previous;
  LibraryPatcher::SocketImportFailureForTest _previous_predicate;
  static ScopedSocketImportFailure* _current;

  ScopedSocketImportFailure(const ScopedSocketImportFailure&) = delete;
  ScopedSocketImportFailure& operator=(const ScopedSocketImportFailure&) = delete;
};

ScopedSocketImportFailure* ScopedSocketImportFailure::_current = nullptr;

// Pause a real owner's start before the patcher's generation snapshot. A
// running refresh can fail in this window, before start resumes and succeeds.
class PausedSocketOwnerStart {
public:
  explicit PausedSocketOwnerStart(bool start_sampler) {
    _current = this;
    LibraryPatcher::setSocketPatchObserverForTest(observe);
    _worker = std::async(std::launch::async, [start_sampler]() {
      Arguments args;
      return !(start_sampler ? NativeSocketSampler::instance()->start(args)
                             : NativeSocketInterposer::instance()->start());
    });
  }

  ~PausedSocketOwnerStart() {
    resume();
    if (_worker.valid()) _worker.get();
    LibraryPatcher::setSocketPatchObserverForTest(nullptr);
    _current = nullptr;
  }

  bool waitSnapshot() {
    return _snapshot.wait_for(std::chrono::seconds(5)) == std::future_status::ready;
  }
  void resume() {
    if (!_resumed) { _resumed = true; _resume.set_value(); }
  }
  bool finish() {
    resume();
    return _worker.get();
  }

private:
  static void observe(const char* phase) {
    if (strcmp(phase, "before_start_snapshot") == 0) {
      _current->_at_snapshot.set_value();
      _current->_resume.get_future().wait();
    }
  }
  static PausedSocketOwnerStart* _current;
  std::promise<void> _at_snapshot, _resume;
  std::future<void> _snapshot = _at_snapshot.get_future();
  std::future<bool> _worker;
  bool _resumed = false;
};

PausedSocketOwnerStart* PausedSocketOwnerStart::_current = nullptr;

// Only the refresh thread pauses: the test thread must be able to reinstall.
class PausedSocketRefresh {
public:
  explicit PausedSocketRefresh(bool resume_at_owner_snapshot = false)
      : _resume_at_owner_snapshot(resume_at_owner_snapshot) {
    _current = this;
    LibraryPatcher::setSocketPatchObserverForTest(observe);
    _worker = std::async(std::launch::async, []() {
      _refresh_thread = true;
      LibraryPatcher::install_socket_hooks();
      _refresh_thread = false;
    });
  }

  ~PausedSocketRefresh() {
    resumeCommit();
    resumeResult();
    _worker.get();
    LibraryPatcher::setSocketPatchObserverForTest(nullptr);
    _current = nullptr;
  }

  bool committed() const { return _committed; }
  bool waitCommit() {
    return _commit.wait_for(std::chrono::seconds(5)) == std::future_status::ready;
  }
  bool waitResult() {
    return _result.wait_for(std::chrono::seconds(5)) == std::future_status::ready;
  }
  void resumeCommit() {
    if (!_commit_resumed) { _commit_resumed = true; _resume_commit.set_value(); }
  }
  void resumeResult() {
    if (!_result_resumed) { _result_resumed = true; _resume_result.set_value(); }
  }

private:
  static void observe(const char* phase) {
    if (!_refresh_thread) {
      if (_current->_resume_at_owner_snapshot && strcmp(phase, "start_snapshot") == 0) {
        _current->resumeCommit();
        EXPECT_TRUE(_current->waitResult());
      }
      return;
    }
    if (strcmp(phase, "committed") == 0) {
      _current->_committed = true;
    } else if (strcmp(phase, "before_commit") == 0) {
      _current->_at_commit.set_value();
      _current->_resume_commit.get_future().wait();
    } else if (strcmp(phase, "refresh_result") == 0) {
      _current->_at_result.set_value();
      _current->_resume_result.get_future().wait();
    }
  }
  static PausedSocketRefresh* _current;
  static thread_local bool _refresh_thread;
  std::promise<void> _at_commit, _at_result, _resume_commit, _resume_result;
  std::future<void> _commit = _at_commit.get_future();
  std::future<void> _result = _at_result.get_future();
  std::future<void> _worker;
  bool _commit_resumed = false, _result_resumed = false;
  bool _committed = false;
  bool _resume_at_owner_snapshot;
};

PausedSocketRefresh* PausedSocketRefresh::_current = nullptr;
thread_local bool PausedSocketRefresh::_refresh_thread = false;

class LibraryPatcherSocketTransactionTest : public ::testing::Test {
protected:
  // The parser caches inodes in an append-only library array. Run each unload/
  // reload scenario in a child so a prior test's CodeCache cannot alias a DSO.
  void initializeFixture() {
    // Bound a broken barrier/lock interleaving to this child, not the CI job.
    alarm(30);
    ASSERT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    ASSERT_EQ(0, LibraryPatcher::socket_library_count_for_test());
    ASSERT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    NativeSocketInterposer::getOriginalFunctions(saved_send, saved_recv, saved_write, saved_read);
    NativeSocketSampler::getOriginalFunctions(saved_sampler_send, saved_sampler_recv,
                                               saved_sampler_write, saved_sampler_read);
    originals_saved = true;

    // Same root/module working-directory alternatives as the unload fixture.
    const char* roots[] = {"build/test/resources/native-libs/socket-patch-transaction-lib",
                           "../build/test/resources/native-libs/socket-patch-transaction-lib"};
    for (const char* root : roots) {
      snprintf(directory, sizeof(directory), "%s", root);
      handles[0] = openLibrary("libjava.so");
      if (handles[0] != nullptr) {
        break;
      }
    }
    ASSERT_NE(nullptr, handles[0]) << dlerror();
    loadNetworkLibrary(0, "libnet.so");
  }

  void TearDown() override {
    // Restore imports before releasing any fixture mapping, including on ASSERT exits.
    LibraryPatcher::unpatch_socket_functions();
    for (void*& handle : handles) {
      if (handle != nullptr) {
        EXPECT_EQ(0, dlclose(handle));
        handle = nullptr;
      }
    }
    if (originals_saved) {
      NativeSocketInterposer::setOriginalFunctions(saved_send, saved_recv, saved_write, saved_read);
      NativeSocketSampler::setOriginalFunctions(saved_sampler_send, saved_sampler_recv,
                                                 saved_sampler_write, saved_sampler_read);
    }
  }

  void* openLibrary(const char* name) {
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", directory, name);
    return dlopen(path, RTLD_NOW | RTLD_LOCAL);
  }

  void loadNetworkLibrary(int index, const char* name) {
    handles[index + 1] = openLibrary(name);
    ASSERT_NE(nullptr, handles[index + 1]) << dlerror();
    symbols[index] = dlsym(handles[index + 1], "socket_patch_read");
    ASSERT_NE(nullptr, symbols[index]) << dlerror();
    Libraries::instance()->updateSymbols(false);
    libraries[index] = Libraries::instance()->findLibraryByAddress(symbols[index]);
    ASSERT_NE(nullptr, libraries[index]);
    ASSERT_EQ(1u, libraries[index]->importCount(im_write));
    ASSERT_EQ(1u, libraries[index]->importCount(im_read));
    slots[index][0] = libraries[index]->findImport(im_write);
    slots[index][1] = libraries[index]->findImport(im_read);
    for (int slot = 0; slot < 2; slot++) {
      ASSERT_NE(nullptr, slots[index][slot]);
      originals[index][slot] = __atomic_load_n(slots[index][slot], __ATOMIC_ACQUIRE);
      ASSERT_NE(nullptr, originals[index][slot]);
    }
  }

  void expectPipeForwarding(NativeSocketInterposer::write_fn writer,
                            NativeSocketInterposer::read_fn reader) {
    int descriptors[2];
    ASSERT_EQ(0, pipe(descriptors));
    int flags = fcntl(descriptors[0], F_GETFL);
    // A broken writer must fail the payload check rather than block the reader.
    if (flags < 0 || fcntl(descriptors[0], F_SETFL, flags | O_NONBLOCK) < 0) {
      int setup_errno = errno;
      EXPECT_EQ(0, ::close(descriptors[0]));
      EXPECT_EQ(0, ::close(descriptors[1]));
      FAIL() << "Failed to make pipe reader nonblocking: " << setup_errno;
    }
    const char payload[] = "rollback forwarding";
    char received[sizeof(payload)] = {};
    errno = E2BIG;
    ssize_t written = writer(descriptors[1], payload, sizeof(payload));
    int write_errno = errno;
    EXPECT_EQ(static_cast<ssize_t>(sizeof(payload)), written);
    EXPECT_EQ(E2BIG, write_errno);
    errno = EINPROGRESS;
    ssize_t read_bytes = reader(descriptors[0], received, sizeof(received));
    int read_errno = errno;
    EXPECT_EQ(static_cast<ssize_t>(sizeof(received)), read_bytes);
    EXPECT_EQ(EINPROGRESS, read_errno);
    EXPECT_EQ(0, std::memcmp(payload, received, sizeof(payload)));
    EXPECT_EQ(0, ::close(descriptors[0]));
    EXPECT_EQ(0, ::close(descriptors[1]));
  }

  void expectPublishedForwarders() {
    NativeSocketInterposer::send_fn current_send;
    NativeSocketInterposer::recv_fn current_recv;
    NativeSocketInterposer::write_fn interposer_write;
    NativeSocketInterposer::read_fn interposer_read;
    NativeSocketInterposer::write_fn sampler_current_write;
    NativeSocketInterposer::read_fn sampler_current_read;
    NativeSocketInterposer::getOriginalFunctions(current_send, current_recv,
                                                 interposer_write, interposer_read);
    NativeSocketSampler::getOriginalFunctions(current_send, current_recv,
                                               sampler_current_write, sampler_current_read);
    // GOT slots may bind executable sanitizer interceptors; forwarding targets
    // come from the profiler DSO's RTLD_NEXT lookup, not those slot originals.
    void* interposer_targets[] = {reinterpret_cast<void*>(interposer_write),
                                 reinterpret_cast<void*>(interposer_read)};
    void* sampler_targets[] = {reinterpret_cast<void*>(sampler_current_write),
                              reinterpret_cast<void*>(sampler_current_read)};
    void* sampler_hooks[] = {reinterpret_cast<void*>(NativeSocketSampler::write_hook),
                            reinterpret_cast<void*>(NativeSocketSampler::read_hook)};
    int hook_indices[] = {NativeSocketInterposer::HOOK_WRITE, NativeSocketInterposer::HOOK_READ};
    const NativeSocketInterposer::NativeIoHookSpec* hooks = NativeSocketInterposer::hookSpecs();
    for (int index = 0; index < 2; index++) {
      ASSERT_NE(nullptr, interposer_targets[index]);
      ASSERT_EQ(interposer_targets[index], sampler_targets[index]);
      ASSERT_NE(hooks[hook_indices[index]].hook, interposer_targets[index]);
      ASSERT_NE(hooks[hook_indices[index]].fork_safe_hook, interposer_targets[index]);
      ASSERT_NE(sampler_hooks[index], interposer_targets[index]);
    }
    expectPipeForwarding(NativeSocketInterposer::write_hook, NativeSocketInterposer::read_hook);
    expectPipeForwarding(NativeSocketSampler::write_hook, NativeSocketSampler::read_hook);
  }

  void expectImports(bool patched, int library_count) {
    void* hooks[] = {reinterpret_cast<void*>(NativeSocketInterposer::write_hook),
                      reinterpret_cast<void*>(NativeSocketInterposer::read_hook)};
    for (int library = 0; library < library_count; library++) {
      for (int slot = 0; slot < 2; slot++) {
        EXPECT_EQ(patched ? hooks[slot] : originals[library][slot],
                  __atomic_load_n(slots[library][slot], __ATOMIC_ACQUIRE))
            << "library=" << library << " slot=" << slot;
      }
    }
  }

  char directory[PATH_MAX] = {};
  void* handles[3] = {};
  void* symbols[2] = {};
  CodeCache* libraries[2] = {};
  void** slots[2][2] = {};
  void* originals[2][2] = {};
  bool originals_saved = false;
  NativeSocketInterposer::send_fn saved_send;
  NativeSocketInterposer::recv_fn saved_recv;
  NativeSocketInterposer::write_fn saved_write;
  NativeSocketInterposer::read_fn saved_read;
  NativeSocketSampler::send_fn saved_sampler_send;
  NativeSocketSampler::recv_fn saved_sampler_recv;
  NativeSocketSampler::write_fn saved_sampler_write;
  NativeSocketSampler::read_fn saved_sampler_read;
};

} // namespace

TEST_F(LibraryPatcherSocketTransactionTest,
       NonSocketLiveWalkRestoresOnlyItsImportsWhileSocketOwnerStaysActive) {
  ASSERT_EXIT({
    initializeFixture();
    if (HasFatalFailure()) _exit(1);
    ScopedNativeSocketInterposerActive interposer_active(true);
    ScopedHookOwnerPid owner(getpid());
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    expectImports(true, 1);
    ASSERT_NE(nullptr, libraries[0]->peekImport(im_pthread_create));
    void** thread_slot = libraries[0]->peekImport(im_pthread_create);
    void* thread_original = __atomic_load_n(thread_slot, __ATOMIC_ACQUIRE);
    u64 fingerprint = libraries[0]->imageFingerprint();
    ASSERT_NE(0ULL, fingerprint);

    LibraryPatcher::initialize();
    LibraryPatcher::patch_libraries();
    EXPECT_NE(thread_original, __atomic_load_n(thread_slot, __ATOMIC_ACQUIRE));
    expectImports(true, 1);
    EXPECT_TRUE(NativeSocketInterposer::instance()->active());
    LibraryPatcher::unpatch_libraries();
    EXPECT_EQ(thread_original, __atomic_load_n(thread_slot, __ATOMIC_ACQUIRE));
    EXPECT_EQ(fingerprint, libraries[0]->imageFingerprint());
    expectImports(true, 1);
    EXPECT_TRUE(NativeSocketInterposer::instance()->active());
    EXPECT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    expectPublishedForwarders();
    NativeSocketInterposer::instance()->stop();
    expectImports(false, 1);
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

TEST_F(LibraryPatcherSocketTransactionTest,
       OwnerRestartMakesReloadedFullRelroImportsWritable) {
  if (OS::isMusl()) GTEST_SKIP() << "musl does not unmap dlclosed DSOs";
  ASSERT_EXIT({
    initializeFixture();
    if (HasFatalFailure()) _exit(1);
    NativeSocketInterposer* interposer = NativeSocketInterposer::instance();
    CodeCache* cache = libraries[0];
    const void* original_base = cache->imageBase();
    void* original_symbol = symbols[0];
    ASSERT_FALSE(interposer->start());
    expectImports(true, 1);
    interposer->stop();
    expectImports(false, 1);
    ASSERT_EQ(0, LibraryPatcher::socket_library_count_for_test());

    ASSERT_EQ(0, dlclose(handles[1]));
    handles[1] = nullptr;
    Dl_info info;
    ASSERT_EQ(0, dladdr(original_symbol, &info));
    handles[1] = openLibrary("libnet.so");
    ASSERT_NE(nullptr, handles[1]) << dlerror();
    ASSERT_EQ(original_symbol, dlsym(handles[1], "socket_patch_read"));
    Libraries::instance()->updateSymbols(false);
    ASSERT_EQ(cache, Libraries::instance()->findLibraryByAddress(original_symbol));
    ASSERT_EQ(original_base, cache->imageBase());

    // A cached prepareImportsForPatch() would still return true, but this
    // reloaded full-RELRO mapping is read-only. Inspect it without findImport().
    FILE* maps = std::fopen("/proc/self/maps", "r");
    ASSERT_NE(nullptr, maps);
    char line[256];
    bool found_readonly = false;
    uintptr_t slot = reinterpret_cast<uintptr_t>(cache->peekImport(im_write));
    while (std::fgets(line, sizeof(line), maps) != nullptr) {
      unsigned long begin;
      unsigned long end;
      char permissions[5];
      if (std::sscanf(line, "%lx-%lx %4s", &begin, &end, permissions) == 3 &&
          slot >= begin && slot < end) {
        found_readonly = permissions[1] != 'w';
        break;
      }
    }
    ASSERT_EQ(0, std::fclose(maps));
    ASSERT_TRUE(found_readonly);
    ASSERT_FALSE(interposer->start());
    expectImports(true, 1);
    EXPECT_TRUE(interposer->active());
    EXPECT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    expectPublishedForwarders();
    interposer->stop();
    expectImports(false, 1);
    TearDown();
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

// Unlike patch_socket_import_for_test, this enters real admission, retention,
// original publication, writes and rollback through the production refresh path.
TEST_F(LibraryPatcherSocketTransactionTest,
       FailedRefreshRestoresEarlierInstallAndPartialLibrary) {
  ASSERT_EXIT({
    initializeFixture();
    if (HasFatalFailure()) _exit(1);
    ScopedNativeSocketInterposerActive interposer_active(true);
    ScopedNativeSocketSamplerActive sampler_active(true);
    ScopedHookOwnerPid owner(getpid());
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    ASSERT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    ASSERT_EQ(1, LibraryPatcher::socket_library_count_for_test());
    ASSERT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    ASSERT_TRUE(NativeSocketInterposer::instance()->active());
    ASSERT_TRUE(NativeSocketSampler::active());
    expectImports(true, 1);
    expectPublishedForwarders();

    loadNetworkLibrary(1, "libnio.so");
    ASSERT_FALSE(HasFatalFailure());
    // Discovery alone must not install or disturb the previously installed DSO.
    expectImports(true, 1);
    ASSERT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    ASSERT_EQ(originals[1][0], __atomic_load_n(slots[1][0], __ATOMIC_ACQUIRE));
    ASSERT_EQ(originals[1][1], __atomic_load_n(slots[1][1], __ATOMIC_ACQUIRE));

    {
      ScopedSocketImportFailure failure(libraries[1], slots[1][0]);
      LibraryPatcher::install_socket_hooks();
      EXPECT_EQ(1, failure.calls);
      EXPECT_TRUE(failure.saw_partial_write);
    }
    expectImports(false, 2);
    EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(0, LibraryPatcher::socket_library_count_for_test());
    EXPECT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    EXPECT_FALSE(NativeSocketInterposer::instance()->active());
    EXPECT_FALSE(NativeSocketSampler::active());
    expectPublishedForwarders();

    // Originals remain callable after disable/rollback, including errno behavior.
    char buffer = 0;
    errno = 0;
    EXPECT_EQ(-1, NativeSocketInterposer::read_hook(-1, &buffer, 1));
    EXPECT_EQ(EBADF, errno);
    errno = 0;
    EXPECT_EQ(-1, NativeSocketSampler::read_hook(-1, &buffer, 1));
    EXPECT_EQ(EBADF, errno);
    LibraryPatcher::install_socket_hooks();
    expectImports(false, 2);
    EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());

    // Removing the fault permits a real reinstall; stale base bookkeeping or
    // restoring hooks instead of pre-install values would break these controls.
    NativeSocketInterposer::instance()->setActiveForTest(true);
    NativeSocketSampler::setActiveForTest(true);
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    expectImports(true, 2);
    EXPECT_EQ(4, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(2, LibraryPatcher::socket_library_count_for_test());
    expectPublishedForwarders();
    LibraryPatcher::install_socket_hooks();
    EXPECT_EQ(4, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(2, LibraryPatcher::socket_library_count_for_test());

    NativeSocketInterposer::instance()->stop();
    expectImports(true, 2);
    EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    NativeSocketSampler::instance()->stop();
    expectImports(false, 2);
    EXPECT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(0, LibraryPatcher::socket_library_count_for_test());

    // A leaked completed-library or partial-candidate handle from either pass
    // keeps the DSO mapped after the last external reference is closed on glibc.
    for (int index = 0; index < 2; index++) {
      ASSERT_EQ(0, dlclose(handles[index + 1]));
      handles[index + 1] = nullptr;
      Dl_info info;
      if (!OS::isMusl()) {
        EXPECT_EQ(0, dladdr(symbols[index], &info));
      }
    }
    TearDown();
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

TEST_F(LibraryPatcherSocketTransactionTest,
       PreSnapshotRefreshFailureCannotDisableSuccessfulOwnerStart) {
  for (bool start_sampler : {false, true}) {
    SCOPED_TRACE(start_sampler ? "starting sampler" : "starting interposer");
    ASSERT_EXIT({
      initializeFixture();
      if (HasFatalFailure()) _exit(1);
      ScopedNativeSocketInterposerActive interposer_active(start_sampler);
      ScopedNativeSocketSamplerActive sampler_active(!start_sampler);
      ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
      loadNetworkLibrary(1, "libnio.so");
      ASSERT_FALSE(HasFatalFailure());
      {
        PausedSocketOwnerStart starting(start_sampler);
        ASSERT_TRUE(starting.waitSnapshot());
        {
          ScopedSocketImportFailure failure(libraries[1], slots[1][0]);
          LibraryPatcher::install_socket_hooks();
          ASSERT_EQ(1, failure.calls);
          ASSERT_TRUE(failure.saw_partial_write);
        }
        // Prove this was a real RUNNING refresh failure, not a cancelled/no-op
        // refresh or a fault that also affects the subsequent installation.
        expectImports(false, 2);
        ASSERT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
        ASSERT_FALSE(NativeSocketInterposer::instance()->active());
        ASSERT_FALSE(NativeSocketSampler::active());
        ASSERT_TRUE(starting.finish());
        TEST_LOG("pre-snapshot refresh rolled back partial write; %s start succeeded; "
                 "interposer_active=%d sampler_active=%d",
                 start_sampler ? "sampler" : "interposer",
                 NativeSocketInterposer::instance()->active(), NativeSocketSampler::active());
      }
      EXPECT_EQ(!start_sampler, NativeSocketInterposer::instance()->active());
      EXPECT_EQ(start_sampler, NativeSocketSampler::active());
      EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
      EXPECT_EQ(4, LibraryPatcher::socket_patch_count_for_test());
      EXPECT_EQ(2, LibraryPatcher::socket_library_count_for_test());
      expectImports(true, 2);
      expectPublishedForwarders();
      NativeSocketInterposer::instance()->stop();
      NativeSocketSampler::instance()->stop();
      expectImports(false, 2);
      TearDown();
      _exit(HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
  }
}

TEST_F(LibraryPatcherSocketTransactionTest,
       OwnerActivationReservationCancelsOlderRefreshBeforeStartCommit) {
  for (bool start_sampler : {false, true}) {
    SCOPED_TRACE(start_sampler ? "starting sampler" : "starting interposer");
    ASSERT_EXIT({
      initializeFixture();
      if (HasFatalFailure()) _exit(1);
      ScopedNativeSocketInterposerActive interposer_active(start_sampler);
      ScopedNativeSocketSamplerActive sampler_active(!start_sampler);
      ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
      {
        PausedSocketRefresh refresh(true);
        ASSERT_TRUE(refresh.waitCommit());
        // Resume the older refresh after owner reservation, before start's
        // discovery/commit, so a commit-time-only generation change is too late.
        Arguments args;
        ASSERT_FALSE(start_sampler ? NativeSocketSampler::instance()->start(args)
                                   : NativeSocketInterposer::instance()->start());
        ASSERT_TRUE(refresh.waitResult());
        EXPECT_FALSE(refresh.committed());
        refresh.resumeResult();
      }
      EXPECT_TRUE(NativeSocketInterposer::instance()->active());
      EXPECT_TRUE(NativeSocketSampler::active());
      EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
      EXPECT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
      expectImports(true, 1);
      NativeSocketInterposer::instance()->stop();
      NativeSocketSampler::instance()->stop();
      expectImports(false, 1);
      TearDown();
      _exit(HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
  }
}

TEST_F(LibraryPatcherSocketTransactionTest,
       CancelledRefreshCannotDisableRestartedOwners) {
  ASSERT_EXIT({
    initializeFixture();
    if (HasFatalFailure()) _exit(1);
    ScopedNativeSocketInterposerActive interposer_active(true);
    ScopedNativeSocketSamplerActive sampler_active(true);
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    {
      PausedSocketRefresh refresh;
      ASSERT_TRUE(refresh.waitCommit());
      NativeSocketInterposer::instance()->stop();
      NativeSocketSampler::instance()->stop();
      expectImports(false, 1);
      refresh.resumeCommit();
      ASSERT_TRUE(refresh.waitResult());
      NativeSocketInterposer::instance()->setActiveForTest(true);
      NativeSocketSampler::setActiveForTest(true);
      ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
      expectImports(true, 1);
      refresh.resumeResult();
    }
    EXPECT_TRUE(NativeSocketInterposer::instance()->active());
    EXPECT_TRUE(NativeSocketSampler::active());
    EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    EXPECT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    expectImports(true, 1);
    TearDown();
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

TEST_F(LibraryPatcherSocketTransactionTest,
       PreviousGenerationRefreshCannotRollBackRestartedOwners) {
  ASSERT_EXIT({
    initializeFixture();
    if (HasFatalFailure()) _exit(1);
    ScopedNativeSocketInterposerActive interposer_active(true);
    ScopedNativeSocketSamplerActive sampler_active(true);
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    {
      PausedSocketRefresh refresh;
      ASSERT_TRUE(refresh.waitCommit());
      NativeSocketInterposer::instance()->stop();
      NativeSocketSampler::instance()->stop();
      NativeSocketInterposer::instance()->setActiveForTest(true);
      NativeSocketSampler::setActiveForTest(true);
      ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
      // A new DSO is not part of the old refresh's discovery snapshot.
      loadNetworkLibrary(1, "libnio.so");
      ASSERT_FALSE(HasFatalFailure());
      refresh.resumeCommit();
      ASSERT_TRUE(refresh.waitResult());
      EXPECT_FALSE(refresh.committed());
      refresh.resumeResult();
    }
    EXPECT_TRUE(NativeSocketInterposer::instance()->active());
    EXPECT_TRUE(NativeSocketSampler::active());
    EXPECT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(originals[1][0], __atomic_load_n(slots[1][0], __ATOMIC_ACQUIRE));
    LibraryPatcher::install_socket_hooks();
    EXPECT_EQ(4, LibraryPatcher::socket_patch_count_for_test());
    expectImports(true, 2);
    // Starting the other owner can reinstall without a full unpatch. That
    // successful installation must also supersede an older discovery.
    {
      PausedSocketRefresh refresh;
      ASSERT_TRUE(refresh.waitCommit());
      ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
      refresh.resumeCommit();
      ASSERT_TRUE(refresh.waitResult());
      EXPECT_FALSE(refresh.committed());
      refresh.resumeResult();
    }
    EXPECT_TRUE(NativeSocketInterposer::instance()->active());
    EXPECT_TRUE(NativeSocketSampler::active());
    expectImports(true, 2);
    TearDown();
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

TEST_F(LibraryPatcherSocketTransactionTest,
       FailedRefreshCannotDisableRestartedOwners) {
  ASSERT_EXIT({
    initializeFixture();
    if (HasFatalFailure()) _exit(1);
    ScopedNativeSocketInterposerActive interposer_active(true);
    ScopedNativeSocketSamplerActive sampler_active(true);
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    loadNetworkLibrary(1, "libnio.so");
    ASSERT_FALSE(HasFatalFailure());
    {
      PausedSocketRefresh refresh;
      ASSERT_TRUE(refresh.waitCommit());
      {
        ScopedSocketImportFailure failure(libraries[1], slots[1][0]);
        refresh.resumeCommit();
        ASSERT_TRUE(refresh.waitResult());
        EXPECT_EQ(1, failure.calls);
        EXPECT_TRUE(failure.saw_partial_write);
      }
      expectImports(false, 2);
      EXPECT_FALSE(NativeSocketInterposer::instance()->active());
      EXPECT_FALSE(NativeSocketSampler::active());
      NativeSocketInterposer::instance()->setActiveForTest(true);
      NativeSocketSampler::setActiveForTest(true);
      ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
      refresh.resumeResult();
    }
    EXPECT_TRUE(NativeSocketInterposer::instance()->active());
    EXPECT_TRUE(NativeSocketSampler::active());
    EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    EXPECT_EQ(4, LibraryPatcher::socket_patch_count_for_test());
    expectImports(true, 2);
    TearDown();
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

TEST(LibraryPatcherDsoLifetimeTest, RetainsPatchedLibraryUntilImportsAreRestored) {
  // Gradle starts gtests from ddprof-lib, while GitLab runs the binaries from
  // the repository root. The support library is under the root build directory
  // in both cases.
  const char* paths[] = {
      "build/test/resources/native-libs/unloadable-io-lib/"
      "libunloadable-io.so",
      "../build/test/resources/native-libs/unloadable-io-lib/"
      "libunloadable-io.so",
  };
  void* handle = nullptr;
  for (const char* path : paths) {
    handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if (handle != nullptr) {
      break;
    }
  }
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

TEST_F(NativeSocketInterposerHookTest, ReadinessScopeEligibilityAndBlockKindTable) {
  enum Operation { EPOLL_WAIT, EPOLL_PWAIT, POLL, PPOLL, SELECT, PSELECT };
  enum Timeout { ZERO, POSITIVE, NEGATIVE, FRACTIONAL, INFINITE };
  struct Case {
    Operation operation;
    NativeBlockKind kind;
  };
  const Case cases[] = {
      {EPOLL_WAIT, NativeBlockKind::EPOLL_WAIT},
      {EPOLL_PWAIT, NativeBlockKind::EPOLL_WAIT},
      {POLL, NativeBlockKind::POLL},
      {PPOLL, NativeBlockKind::POLL},
      {SELECT, NativeBlockKind::SELECT},
      {PSELECT, NativeBlockKind::SELECT},
  };
  struct ScopedHotspot {
    bool saved = VMTestAccessor::exchangeHotspot(true);
    ~ScopedHotspot() { VMTestAccessor::exchangeHotspot(saved); }
  } hotspot;
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  g_epoll_wait_ret = g_epoll_pwait_ret = g_poll_ret = g_ppoll_ret =
      g_select_ret = g_pselect_ret = 7;
  for (const Case& test : cases) {
    for (bool active : {false, true}) {
      ScopedNativeSocketInterposerActive owner(active);
      for (int count : {0, 1}) {
        for (Timeout timeout : {ZERO, POSITIVE, NEGATIVE, FRACTIONAL, INFINITE}) {
          for (bool null_fds : {false, true}) {
            SCOPED_TRACE(::testing::Message() << "operation=" << test.operation
                         << " active=" << active << " count=" << count
                         << " timeout=" << timeout << " null_fds=" << null_fds);
            int integer_timeout = timeout == ZERO ? 0 : timeout == NEGATIVE || timeout == INFINITE ? -1 : 1;
            timespec ts = {timeout == POSITIVE ? 1 : timeout == NEGATIVE ? -1 : 0,
                           timeout == FRACTIONAL ? 1 : 0};
            timeval tv = {ts.tv_sec, ts.tv_nsec};
            pollfd fd = {0, POLLIN, 0};
            epoll_event event = {};
            g_taskblock_enter_sequence = g_taskblock_exit_sequence = g_taskblock_kind = 0;
            int calls_before = g_epoll_wait_calls + g_epoll_pwait_calls + g_poll_calls +
                g_ppoll_calls + g_select_calls + g_pselect_calls;
            errno = E2BIG;
            int result = -1;
            switch (test.operation) {
              case EPOLL_WAIT:
                result = NativeSocketInterposer::epoll_wait_hook(31, &event, count, integer_timeout);
                break;
              case EPOLL_PWAIT:
                result = NativeSocketInterposer::epoll_pwait_hook(31, &event, count, integer_timeout, nullptr);
                break;
              case POLL:
                result = NativeSocketInterposer::poll_hook(null_fds ? nullptr : &fd, count, integer_timeout);
                break;
              case PPOLL:
                result = NativeSocketInterposer::ppoll_hook(null_fds ? nullptr : &fd, count,
                    timeout == INFINITE ? nullptr : &ts, nullptr);
                break;
              case SELECT:
                result = NativeSocketInterposer::select_hook(count, nullptr, nullptr, nullptr,
                    timeout == INFINITE ? nullptr : &tv);
                break;
              case PSELECT:
                result = NativeSocketInterposer::pselect_hook(count, nullptr, nullptr, nullptr,
                    timeout == INFINITE ? nullptr : &ts, nullptr);
                break;
            }
            EXPECT_EQ(7, result);
            EXPECT_EQ(E2BIG, errno);
            EXPECT_EQ(calls_before + 1, g_epoll_wait_calls + g_epoll_pwait_calls + g_poll_calls +
                g_ppoll_calls + g_select_calls + g_pselect_calls);
            bool eligible = active && count > 0 && timeout != ZERO &&
                (!null_fds || (test.operation != POLL && test.operation != PPOLL));
            EXPECT_EQ(eligible, g_taskblock_enter_sequence.load() != 0);
            EXPECT_EQ(eligible, g_taskblock_exit_sequence.load() != 0);
            if (eligible) {
              EXPECT_EQ(static_cast<u32>(test.kind), g_taskblock_kind.load());
              EXPECT_LT(g_taskblock_enter_sequence.load(), g_taskblock_exit_sequence.load());
            }
          }
        }
      }
    }
  }
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

TEST_F(NativeSocketInterposerFdTest,
       ProbeStraddlingCloseAndReuseCannotPublishStaleStreamType) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));
  int pipe_fds[2];
  ASSERT_EQ(0, pipe(pipe_fds));
  int reused_fd = stream_fds[0];

  g_blocking_probe_started.store(false, std::memory_order_release);
  g_release_blocking_probe.store(false, std::memory_order_release);
  std::atomic<bool> stale_stream{true};
  {
    ScopedFdProbeOverride override(blocking_stream_fd_probe);
    std::thread probe([&]() {
      stale_stream.store(
          NativeSocketInterposer::instance()->isStreamSocket(reused_fd),
          std::memory_order_release);
    });

    while (!g_blocking_probe_started.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }
    int close_result = closeThroughHook(reused_fd);
    int dup_result = dup2ThroughHook(pipe_fds[0], reused_fd);
    g_release_blocking_probe.store(true, std::memory_order_release);
    probe.join();
    ASSERT_EQ(0, close_result);
    ASSERT_EQ(reused_fd, dup_result);
  }

  EXPECT_FALSE(stale_stream.load(std::memory_order_acquire));
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(reused_fd));

  ASSERT_EQ(0, closeThroughHook(reused_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[0]));
  ASSERT_EQ(0, closeThroughHook(pipe_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, RejectsNonSockets) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(fds[0]));
  ASSERT_EQ(0, closeThroughHook(fds[0]));
  ASSERT_EQ(0, closeThroughHook(fds[1]));
}

namespace {

class ScopedNativeIoFd {
public:
  explicit ScopedNativeIoFd(int fd) : _fd(fd) {}
  ~ScopedNativeIoFd() {
    if (_fd >= 0) {
      ::close(_fd);
    }
  }
  ScopedNativeIoFd(const ScopedNativeIoFd&) = delete;
  ScopedNativeIoFd& operator=(const ScopedNativeIoFd&) = delete;

private:
  int _fd;
};

class ScopedInvalidatingFdProbe {
public:
  ScopedInvalidatingFdProbe(NativeFdClassifier& classifier, uint32_t invalidations)
      : _classifier(classifier), _invalidations(invalidations) {
    _current = this;
    NativeFdClassifier::setProbeOverrideForTest(probe);
  }
  ~ScopedInvalidatingFdProbe() {
    NativeFdClassifier::setProbeOverrideForTest(nullptr);
    _current = nullptr;
  }

  uint32_t completed = 0;
  int calls = 0;

private:
  static int probe(int fd, int* so_type, int* probe_errno) {
    _current->calls++;
    for (uint32_t index = 0; index < _current->_invalidations; index++) {
      _current->_classifier.clearFdType(fd);
      _current->completed++;
    }
    *so_type = SOCK_STREAM;
    *probe_errno = 0;
    return 0;
  }

  NativeFdClassifier& _classifier;
  uint32_t _invalidations;
  static ScopedInvalidatingFdProbe* _current;
};

ScopedInvalidatingFdProbe* ScopedInvalidatingFdProbe::_current = nullptr;

} // namespace

TEST_F(NativeSocketInterposerFdTest,
       HighFdEpochWrapDoesNotResurrectOldStreamVerdict) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(recording_fd_probe);
  const int low_fd = 57;
  const int high_fd = kFdTypeCacheSizeForTest + 57;
  g_fd_probe_calls = 0;
  g_fd_probe_rc = 0;
  g_fd_probe_errno = 0;
  g_fd_probe_so_type = SOCK_STREAM;
  ASSERT_TRUE(classifier.isStreamSocket(low_fd));
  ASSERT_TRUE(classifier.isStreamSocket(high_fd));
  ASSERT_EQ(2, g_fd_probe_calls.load());

  // No intervening lookup may refresh the untouched high-FD entry's epoch.
  for (uint32_t generation = 0; generation < (1u << 17); generation++) {
    classifier.clearFdTypeCache();
  }
  g_fd_probe_so_type = SOCK_DGRAM;
  EXPECT_FALSE(classifier.isStreamSocket(high_fd));
  EXPECT_TRUE(classifier.isDatagramSocket(high_fd));
  EXPECT_FALSE(classifier.isStreamSocket(low_fd));
  EXPECT_TRUE(classifier.isDatagramSocket(low_fd));
  EXPECT_EQ(4, g_fd_probe_calls.load());
}

TEST_F(NativeSocketInterposerFdTest,
       HighFdIncarnationWrapCannotPublishPreInvalidationProbe) {
  const int fd = kFdTypeCacheSizeForTest + 58;
  for (uint32_t invalidations : {1u, 1u << 24}) {
    SCOPED_TRACE(invalidations);
    NativeFdClassifier classifier;
    classifier.clearFdType(fd);
    {
      // Invalidation runs after fdType captures its word and before its CAS.
      ScopedInvalidatingFdProbe probe(classifier, invalidations);
      EXPECT_FALSE(classifier.isStreamSocket(fd));
      EXPECT_EQ(1, probe.calls);
      EXPECT_EQ(invalidations, probe.completed);
    }
    ScopedFdProbeOverride override(stub_fd_probe);
    g_fd_probe_calls = 0;
    g_fd_probe_rc = 0;
    g_fd_probe_errno = 0;
    g_fd_probe_so_type = SOCK_DGRAM;
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_TRUE(classifier.isDatagramSocket(fd));
    EXPECT_EQ(1, g_fd_probe_calls.load());
  }
}

TEST_F(NativeSocketInterposerFdTest,
       OnlyEnotsockPublishesNegativeVerdictForLowAndHighFds) {
  NativeFdClassifier classifier;
  ScopedFdProbeOverride override(recording_fd_probe);
  for (int fd : {59, kFdTypeCacheSizeForTest + 59}) {
    for (int failure : {EBADF, EINTR, EIO, EAGAIN, ENOBUFS, EINVAL}) {
      SCOPED_TRACE(fd);
      SCOPED_TRACE(failure);
      classifier.clearFdType(fd);
      g_fd_probe_calls = 0;
      g_fd_probe_rc = -1;
      g_fd_probe_errno = failure;
      g_fd_probe_so_type = 0;
      errno = 0;
      EXPECT_FALSE(classifier.isStreamSocket(fd));
      EXPECT_EQ(failure, errno);
      EXPECT_FALSE(classifier.isDatagramSocket(fd));
      EXPECT_EQ(2, g_fd_probe_calls.load());

      g_fd_probe_rc = 0;
      g_fd_probe_so_type = SOCK_STREAM;
      EXPECT_TRUE(classifier.isStreamSocket(fd));
      EXPECT_TRUE(classifier.isStreamSocket(fd));
      EXPECT_EQ(3, g_fd_probe_calls.load());
    }
    classifier.clearFdType(fd);
    g_fd_probe_calls = 0;
    g_fd_probe_rc = -1;
    g_fd_probe_errno = ENOTSOCK;
    errno = 0;
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_EQ(ENOTSOCK, errno);
    g_fd_probe_rc = 0;
    g_fd_probe_so_type = SOCK_STREAM;
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_FALSE(classifier.isDatagramSocket(fd));
    EXPECT_EQ(1, g_fd_probe_calls.load());
    classifier.clearFdType(fd);
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_EQ(2, g_fd_probe_calls.load());
  }
}

TEST_F(NativeSocketInterposerHookTest,
       InactiveOwnersForwardAllStreamArgumentsDespiteInstalledState) {
  ScopedNativeSocketInterposerActive interposer_active(false);
  ScopedNativeSocketSamplerActive sampler_active(false);
  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  ScopedFdProbeOverride override(recording_fd_probe);
  NativeBlockScope::setHookObserverForTest(native_block_observer);
  NativeSocketSampler::setHookObserverForTest(native_socket_sampler_observer);
  static char buffer[8] = {};
  NativeSocketInterposer::setOriginalFunctions(
      [](int fd, const void* data, size_t len, int flags) -> ssize_t {
        EXPECT_EQ(65537, fd);
        EXPECT_EQ(static_cast<const void*>(buffer), data);
        EXPECT_EQ(3u, len);
        EXPECT_EQ(MSG_DONTWAIT, flags);
        g_send_calls++;
        errno = EPIPE;
        return -1;
      },
      [](int fd, void* data, size_t len, int flags) -> ssize_t {
        EXPECT_EQ(65537, fd);
        EXPECT_EQ(static_cast<void*>(buffer), data);
        EXPECT_EQ(4u, len);
        EXPECT_EQ(MSG_PEEK, flags);
        g_recv_calls++;
        errno = EINTR;
        return -1;
      },
      [](int fd, const void* data, size_t len) -> ssize_t {
        EXPECT_EQ(65537, fd);
        EXPECT_EQ(static_cast<const void*>(buffer), data);
        EXPECT_EQ(5u, len);
        g_write_calls++;
        errno = ERANGE;
        return 2;
      },
      [](int fd, void* data, size_t len) -> ssize_t {
        EXPECT_EQ(65537, fd);
        EXPECT_EQ(static_cast<void*>(buffer), data);
        EXPECT_EQ(6u, len);
        g_read_calls++;
        errno = E2BIG;
        return 0;
      });

  EXPECT_EQ(-1, NativeSocketInterposer::send_hook(65537, buffer, 3, MSG_DONTWAIT));
  EXPECT_EQ(EPIPE, errno);
  EXPECT_EQ(-1, NativeSocketInterposer::recv_hook(65537, buffer, 4, MSG_PEEK));
  EXPECT_EQ(EINTR, errno);
  EXPECT_EQ(2, NativeSocketInterposer::write_hook(65537, buffer, 5));
  EXPECT_EQ(ERANGE, errno);
  EXPECT_EQ(0, NativeSocketInterposer::read_hook(65537, buffer, 6));
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, g_send_calls.load());
  EXPECT_EQ(1, g_recv_calls.load());
  EXPECT_EQ(1, g_write_calls.load());
  EXPECT_EQ(1, g_read_calls.load());
  EXPECT_EQ(0, g_sampler_send_calls.load());
  EXPECT_EQ(0, g_sampler_write_calls.load());
  EXPECT_EQ(0, g_fd_probe_calls.load());
  EXPECT_EQ(0, g_taskblock_enter_sequence.load());
  EXPECT_EQ(0, g_taskblock_exit_sequence.load());
  EXPECT_EQ(0, g_sampler_record_sequence.load());
}

TEST_F(NativeSocketInterposerFdTest,
       UnpatchedReuseSeparatesSamplerRevalidationFromInterposerInvalidation) {
  for (int minimum : {0, kFdTypeCacheSizeForTest}) {
    SCOPED_TRACE(minimum);
    int sockets[2];
    ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));
    ScopedNativeIoFd stream(sockets[0]);
    ScopedNativeIoFd peer(sockets[1]);
    int pipes[2];
    ASSERT_EQ(0, pipe(pipes));
    ScopedNativeIoFd pipe_read(pipes[0]);
    ScopedNativeIoFd pipe_write(pipes[1]);
    int fd = fcntl(sockets[0], F_DUPFD_CLOEXEC, minimum);
    ASSERT_GE(fd, minimum);
    ScopedNativeIoFd target(fd);
    if (minimum == 0) ASSERT_LT(fd, kFdTypeCacheSizeForTest);
    NativeSocketInterposer* interposer = NativeSocketInterposer::instance();
    NativeSocketSampler* sampler = NativeSocketSampler::instance();
    interposer->clearFdTypeCache();
    sampler->clearFdCache();
    ASSERT_TRUE(interposer->isStreamSocket(fd));
    ASSERT_TRUE(sampler->isSocketForTest(fd));

    // This raw dup2 deliberately bypasses the patched lifecycle hooks.
    ASSERT_EQ(fd, ::dup2(pipes[1], fd));
    int type = 0;
    socklen_t size = sizeof(type);
    errno = 0;
    ASSERT_EQ(-1, getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &size));
    ASSERT_EQ(ENOTSOCK, errno);
    EXPECT_TRUE(interposer->isStreamSocket(fd));
    EXPECT_TRUE(sampler->isSocketForTest(fd));
    EXPECT_FALSE(sampler->revalidateSocketForTest(fd));
    EXPECT_FALSE(sampler->isSocketForTest(fd));
    EXPECT_TRUE(interposer->isStreamSocket(fd));

    ASSERT_EQ(fd, dup2ThroughHook(pipes[1], fd));
    EXPECT_FALSE(interposer->isStreamSocket(fd));
    EXPECT_FALSE(sampler->isSocketForTest(fd));
  }
}

TEST_F(NativeSocketInterposerHookTest,
       SamplerOnlyRealPipeIoPreservesSuccessfulAndFailingErrno) {
  ScopedNativeSocketInterposerActive interposer_active(false);
  ScopedNativeSocketSamplerActive sampler_active(true);
  NativeSocketSampler::setOriginalFunctions(::send, ::recv, ::write, ::read);
  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  for (int minimum : {0, kFdTypeCacheSizeForTest}) {
    SCOPED_TRACE(minimum);
    NativeSocketSampler::instance()->clearFdCache();
    int pipes[2];
    ASSERT_EQ(0, pipe2(pipes, O_NONBLOCK | O_CLOEXEC));
    ScopedNativeIoFd pipe_read(pipes[0]);
    ScopedNativeIoFd pipe_write(pipes[1]);
    int write_fd = fcntl(pipes[1], F_DUPFD_CLOEXEC, minimum);
    ASSERT_GE(write_fd, minimum);
    ScopedNativeIoFd write_target(write_fd);
    int read_fd = fcntl(pipes[0], F_DUPFD_CLOEXEC, minimum);
    ASSERT_GE(read_fd, minimum);
    ScopedNativeIoFd read_target(read_fd);
    if (minimum == 0) {
      ASSERT_LT(write_fd, kFdTypeCacheSizeForTest);
      ASSERT_LT(read_fd, kFdTypeCacheSizeForTest);
    }
    const char sent = 'x';
    char received = 0;
    errno = E2BIG;
    EXPECT_EQ(1, NativeSocketInterposer::write_hook(write_fd, &sent, 1));
    EXPECT_EQ(E2BIG, errno);
    errno = ERANGE;
    EXPECT_EQ(1, NativeSocketInterposer::read_hook(read_fd, &received, 1));
    EXPECT_EQ(ERANGE, errno);
    EXPECT_EQ(sent, received);

    errno = 0;
    EXPECT_EQ(-1, NativeSocketInterposer::read_hook(read_fd, &received, 1));
    EXPECT_EQ(EAGAIN, errno);
    errno = 0;
    EXPECT_EQ(-1, NativeSocketInterposer::send_hook(write_fd, &sent, 1, MSG_DONTWAIT));
    EXPECT_EQ(ENOTSOCK, errno);
    errno = 0;
    EXPECT_EQ(-1, NativeSocketInterposer::write_hook(-1, &sent, 1));
    EXPECT_EQ(EBADF, errno);
  }
}

#endif // __linux__
