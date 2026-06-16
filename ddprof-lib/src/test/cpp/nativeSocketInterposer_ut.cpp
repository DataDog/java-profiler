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

#include "libraryPatcher.h"
#include "nativeBlock.h"
#include "nativeSocketInterposer.h"

#include <atomic>
#include <cerrno>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

namespace {

std::atomic<int> g_send_calls{0};
std::atomic<int> g_recv_calls{0};
std::atomic<int> g_write_calls{0};
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
std::atomic<ssize_t> g_send_ret{0};
std::atomic<ssize_t> g_recv_ret{0};
std::atomic<ssize_t> g_write_ret{0};
std::atomic<ssize_t> g_read_ret{0};
std::atomic<int> g_close_ret{0};
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

ssize_t stub_recv(int, void*, size_t, int) {
  g_recv_calls++;
  return g_recv_ret.load();
}

ssize_t stub_write(int, const void*, size_t) {
  g_write_calls++;
  return g_write_ret.load();
}

ssize_t stub_read(int, void*, size_t) {
  g_read_calls++;
  return g_read_ret.load();
}

int stub_close(int) {
  g_close_calls++;
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
  bool saved_active = false;

  void SetUp() override {
    NativeSocketInterposer::getOriginalFunctions(saved_send, saved_recv, saved_write,
                                                 saved_read);
    NativeSocketInterposer::setOriginalFunctions(stub_send, stub_recv, stub_write,
                                                 stub_read);
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
    g_send_calls = 0;
    g_recv_calls = 0;
    g_write_calls = 0;
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
    g_send_ret = 0;
    g_recv_ret = 0;
    g_write_ret = 0;
    g_read_ret = 0;
    g_close_ret = 0;
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
  }
};

class NativeSocketInterposerFdTest : public ::testing::Test {
protected:
  void SetUp() override {
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE,
                        reinterpret_cast<void*>(::close));
    NativeSocketInterposer::instance()->clearFdTypeCache();
  }

  void TearDown() override {
    setOriginalFunction(NativeSocketInterposer::HOOK_CLOSE, nullptr);
    NativeSocketInterposer::instance()->clearFdTypeCache();
  }

  int closeThroughHook(int fd) {
    return NativeSocketInterposer::close_hook(fd);
  }
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

TEST_F(NativeSocketInterposerHookTest, CloseForwardsAndPreservesErrno) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  g_close_ret = 0;

  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  errno = E2BIG;
  int ret = NativeSocketInterposer::close_hook(fds[0]);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(1, g_close_calls.load());
  EXPECT_EQ(E2BIG, errno);
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

TEST(NativeBlockScopeTest, EncodesKindAndBlockerId) {
  EXPECT_EQ((static_cast<u64>(NativeBlockKind::CONNECT) << 32) | 17,
            NativeBlockScope::blocker(NativeBlockKind::CONNECT, 17));
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

TEST_F(NativeSocketInterposerFdTest, CloseHookInvalidatesFdBeforeReuse) {
  int stream_fds[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds));

  int reused_fd = stream_fds[0];
  EXPECT_TRUE(NativeSocketInterposer::instance()->isStreamSocket(reused_fd));
  ASSERT_EQ(0, closeThroughHook(reused_fd));

  int datagram_fd = socket(AF_INET, SOCK_DGRAM, 0);
  ASSERT_EQ(reused_fd, datagram_fd);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));

  ASSERT_EQ(0, closeThroughHook(datagram_fd));
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

  int datagram_fd = socket(AF_INET, SOCK_DGRAM, 0);
  ASSERT_EQ(reused_fd, datagram_fd);
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(datagram_fd));

  ASSERT_EQ(0, closeThroughHook(datagram_fd));
  ASSERT_EQ(0, closeThroughHook(stream_fds[1]));
}

TEST_F(NativeSocketInterposerFdTest, RejectsNonSockets) {
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  EXPECT_FALSE(NativeSocketInterposer::instance()->isStreamSocket(fds[0]));
  ASSERT_EQ(0, closeThroughHook(fds[0]));
  ASSERT_EQ(0, closeThroughHook(fds[1]));
}

#endif // __linux__
