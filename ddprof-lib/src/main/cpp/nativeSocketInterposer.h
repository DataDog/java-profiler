/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NATIVE_SOCKET_INTERPOSER_H
#define _NATIVE_SOCKET_INTERPOSER_H

#include "arguments.h"

#include <stddef.h>
#include <sys/types.h>

#if defined(__linux__)

#include "codeCache.h"
#include "nativeBlock.h"
#include "nativeFdClassifier.h"

#include <poll.h>
#include <atomic>
#include <stdint.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>

class NativeSocketInterposer {
public:
  typedef ssize_t (*send_fn)(int, const void*, size_t, int);
  typedef ssize_t (*recv_fn)(int, void*, size_t, int);
  typedef ssize_t (*write_fn)(int, const void*, size_t);
  typedef ssize_t (*read_fn)(int, void*, size_t);
  typedef int (*close_fn)(int);
  typedef int (*dup2_fn)(int, int);
  typedef int (*dup3_fn)(int, int, int);
  typedef int (*connect_fn)(int, const struct sockaddr*, socklen_t);
  typedef int (*accept_fn)(int, struct sockaddr*, socklen_t*);
  typedef int (*accept4_fn)(int, struct sockaddr*, socklen_t*, int);
  typedef ssize_t (*recvfrom_fn)(int, void*, size_t, int, struct sockaddr*, socklen_t*);
  typedef ssize_t (*recvmsg_fn)(int, struct msghdr*, int);
  typedef int (*epoll_wait_fn)(int, struct epoll_event*, int, int);
  typedef int (*epoll_pwait_fn)(int, struct epoll_event*, int, int, const sigset_t*);
  typedef int (*poll_fn)(struct pollfd*, nfds_t, int);
  typedef int (*ppoll_fn)(struct pollfd*, nfds_t, const struct timespec*, const sigset_t*);
  typedef int (*select_fn)(int, fd_set*, fd_set*, fd_set*, struct timeval*);
  typedef int (*pselect_fn)(int, fd_set*, fd_set*, fd_set*, const struct timespec*,
                            const sigset_t*);

  enum NativeIoHookIndex : int {
    HOOK_SEND = 0,
    HOOK_RECV,
    HOOK_WRITE,
    HOOK_READ,
    HOOK_CLOSE,
    HOOK_DUP2,
    HOOK_DUP3,
    HOOK_CONNECT,
    HOOK_ACCEPT,
    HOOK_ACCEPT4,
    HOOK_RECVFROM,
    HOOK_RECVMSG,
    HOOK_EPOLL_WAIT,
    HOOK_EPOLL_PWAIT,
    HOOK_POLL,
    HOOK_PPOLL,
    HOOK_SELECT,
    HOOK_PSELECT,
    NUM_NATIVE_IO_HOOKS
  };

  struct NativeIoHookSpec {
    ImportId import_id;
    const char* name;
    void* hook;
    void* fork_safe_hook;
  };

  static NativeSocketInterposer* instance() { return _instance; }

  Error start();
  void stop();
  void disableAfterPatchFailure();
  bool active() const { return _active.load(std::memory_order_acquire); }

#ifdef UNIT_TEST
  bool setActiveForTest(bool active) {
    return _active.exchange(active, std::memory_order_acq_rel);
  }
  static pid_t setHookOwnerPidForTest(pid_t pid) {
    return _hook_owner_pid.exchange(pid, std::memory_order_acq_rel);
  }
#endif

  bool isStreamSocket(int fd);
  bool isDatagramSocket(int fd);
  void clearFdType(int fd);
  void clearFdTypeCache();

  static const NativeIoHookSpec* hookSpecs();
  static bool setOriginalFunction(int hook_index, void* original);
  static void setHookOwnerPid(pid_t pid) {
    _hook_owner_pid.store(pid, std::memory_order_release);
  }

  static ssize_t send_hook(int fd, const void* buf, size_t len, int flags);
  static ssize_t recv_hook(int fd, void* buf, size_t len, int flags);
  static ssize_t write_hook(int fd, const void* buf, size_t len);
  static ssize_t read_hook(int fd, void* buf, size_t len);
  static int close_hook(int fd);
  static int dup2_hook(int oldfd, int newfd);
  static int dup3_hook(int oldfd, int newfd, int flags);
  static int connect_hook(int fd, const struct sockaddr* addr, socklen_t addrlen);
  static int accept_hook(int fd, struct sockaddr* addr, socklen_t* addrlen);
  static int accept4_hook(int fd, struct sockaddr* addr, socklen_t* addrlen, int flags);
  static ssize_t recvfrom_hook(int fd, void* buf, size_t len, int flags,
                               struct sockaddr* src_addr, socklen_t* addrlen);
  static ssize_t recvmsg_hook(int fd, struct msghdr* msg, int flags);
  static int epoll_wait_hook(int epfd, struct epoll_event* events, int maxevents,
                             int timeout);
  static int epoll_pwait_hook(int epfd, struct epoll_event* events, int maxevents,
                              int timeout, const sigset_t* sigmask);
  static int poll_hook(struct pollfd* fds, nfds_t nfds, int timeout);
  static int ppoll_hook(struct pollfd* fds, nfds_t nfds,
                        const struct timespec* timeout_ts, const sigset_t* sigmask);
  static int select_hook(int nfds, fd_set* readfds, fd_set* writefds,
                         fd_set* exceptfds, struct timeval* timeout);
  static int pselect_hook(int nfds, fd_set* readfds, fd_set* writefds,
                          fd_set* exceptfds, const struct timespec* timeout_ts,
                          const sigset_t* sigmask);

  // These hooks are installed only in JDK libraries that may also execute in
  // a post-fork child. In that child they call libc directly, before touching
  // profiler TLS, caches, locks, clocks, or recording state.
  static ssize_t fork_safe_send_hook(int fd, const void* buf, size_t len, int flags);
  static ssize_t fork_safe_recv_hook(int fd, void* buf, size_t len, int flags);
  static ssize_t fork_safe_write_hook(int fd, const void* buf, size_t len);
  static ssize_t fork_safe_read_hook(int fd, void* buf, size_t len);
  static int fork_safe_close_hook(int fd);
  static int fork_safe_dup2_hook(int oldfd, int newfd);
  static int fork_safe_dup3_hook(int oldfd, int newfd, int flags);
  static int fork_safe_connect_hook(int fd, const struct sockaddr* addr,
                                    socklen_t addrlen);
  static int fork_safe_accept_hook(int fd, struct sockaddr* addr,
                                   socklen_t* addrlen);
  static int fork_safe_accept4_hook(int fd, struct sockaddr* addr,
                                    socklen_t* addrlen, int flags);
  static ssize_t fork_safe_recvfrom_hook(int fd, void* buf, size_t len, int flags,
                                         struct sockaddr* src_addr,
                                         socklen_t* addrlen);
  static ssize_t fork_safe_recvmsg_hook(int fd, struct msghdr* msg, int flags);
  static int fork_safe_epoll_wait_hook(int epfd, struct epoll_event* events,
                                       int maxevents, int timeout);
  static int fork_safe_epoll_pwait_hook(int epfd, struct epoll_event* events,
                                        int maxevents, int timeout,
                                        const sigset_t* sigmask);
  static int fork_safe_poll_hook(struct pollfd* fds, nfds_t nfds, int timeout);
  static int fork_safe_ppoll_hook(struct pollfd* fds, nfds_t nfds,
                                  const struct timespec* timeout_ts,
                                  const sigset_t* sigmask);
  static int fork_safe_select_hook(int nfds, fd_set* readfds, fd_set* writefds,
                                   fd_set* exceptfds, struct timeval* timeout);
  static int fork_safe_pselect_hook(int nfds, fd_set* readfds, fd_set* writefds,
                                    fd_set* exceptfds,
                                    const struct timespec* timeout_ts,
                                    const sigset_t* sigmask);

  static void setOriginalFunctions(send_fn s, recv_fn r, write_fn w, read_fn rd) {
    _orig_send.store(s, std::memory_order_release);
    _orig_recv.store(r, std::memory_order_release);
    _orig_write.store(w, std::memory_order_release);
    _orig_read.store(rd, std::memory_order_release);
  }

  static void getOriginalFunctions(send_fn& s, recv_fn& r, write_fn& w, read_fn& rd) {
    s = _orig_send.load(std::memory_order_acquire);
    r = _orig_recv.load(std::memory_order_acquire);
    w = _orig_write.load(std::memory_order_acquire);
    rd = _orig_read.load(std::memory_order_acquire);
  }

private:
  static NativeSocketInterposer* const _instance;
  // Production publishes these once before installing any import hook. Atomic
  // access also keeps test overrides and hook reads data-race-free.
  static std::atomic<send_fn> _orig_send;
  static std::atomic<recv_fn> _orig_recv;
  static std::atomic<write_fn> _orig_write;
  static std::atomic<read_fn> _orig_read;
  static std::atomic<close_fn> _orig_close;
  static std::atomic<dup2_fn> _orig_dup2;
  static std::atomic<dup3_fn> _orig_dup3;
  static std::atomic<connect_fn> _orig_connect;
  static std::atomic<accept_fn> _orig_accept;
  static std::atomic<accept4_fn> _orig_accept4;
  static std::atomic<recvfrom_fn> _orig_recvfrom;
  static std::atomic<recvmsg_fn> _orig_recvmsg;
  static std::atomic<epoll_wait_fn> _orig_epoll_wait;
  static std::atomic<epoll_pwait_fn> _orig_epoll_pwait;
  static std::atomic<poll_fn> _orig_poll;
  static std::atomic<ppoll_fn> _orig_ppoll;
  static std::atomic<select_fn> _orig_select;
  static std::atomic<pselect_fn> _orig_pselect;
  static std::atomic<pid_t> _hook_owner_pid;

  static bool isForkChild();

  NativeFdClassifier _fd_classifier;
  std::atomic<bool> _active{false};

  NativeSocketInterposer() = default;
};

#else

class NativeSocketInterposer {
public:
  static NativeSocketInterposer* instance() { return _instance; }
  Error start() { return Error::OK; }
  void stop() {}
  void disableAfterPatchFailure() {}
  void clearFdTypeCache() {}

private:
  static NativeSocketInterposer* const _instance;
  NativeSocketInterposer() = default;
};

#endif

#endif // _NATIVE_SOCKET_INTERPOSER_H
