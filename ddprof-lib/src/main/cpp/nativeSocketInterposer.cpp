/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeSocketInterposer.h"

#if defined(__linux__)

#include "libraryPatcher.h"
#include "nativeSocketSampler.h"

#include <errno.h>

namespace {

static inline bool nonZeroTimeval(const struct timeval* timeout) {
  return timeout == nullptr || timeout->tv_sec != 0 || timeout->tv_usec != 0;
}

static inline bool nonZeroTimespec(const struct timespec* timeout) {
  return timeout == nullptr || timeout->tv_sec != 0 || timeout->tv_nsec != 0;
}

template <typename Ret, typename Fn, typename Call>
static inline Ret runNativeIoHook(bool eligible, NativeBlockKind kind,
                                  int fd, Fn fn, Call call) {
  if (fn == nullptr) {
    errno = ENOSYS;
    return static_cast<Ret>(-1);
  }
  if (!NativeSocketInterposer::instance()->active() || !eligible) {
    return call(fn);
  }

  NativeBlockScope block(kind, fd);
  Ret ret = call(fn);
  return ret;
}

template <typename Ret, typename Fn, typename Call>
static inline Ret runStreamSocketHook(int fd, Fn fn, Call call) {
  int entry_errno = errno;
  bool eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  errno = entry_errno;
  return runNativeIoHook<Ret>(eligible, NativeBlockKind::STREAM_SOCKET, fd, fn,
                              call);
}

template <typename Ret, typename Fn, typename Call>
static inline Ret runDatagramSocketHook(int fd, Fn fn, Call call) {
  int entry_errno = errno;
  bool eligible = NativeSocketInterposer::instance()->isDatagramSocket(fd);
  errno = entry_errno;
  return runNativeIoHook<Ret>(eligible, NativeBlockKind::UDP_RECEIVE, fd, fn,
                              call);
}

} // namespace

NativeSocketInterposer* const NativeSocketInterposer::_instance = new NativeSocketInterposer();
NativeSocketInterposer::send_fn NativeSocketInterposer::_orig_send = nullptr;
NativeSocketInterposer::recv_fn NativeSocketInterposer::_orig_recv = nullptr;
NativeSocketInterposer::write_fn NativeSocketInterposer::_orig_write = nullptr;
NativeSocketInterposer::read_fn NativeSocketInterposer::_orig_read = nullptr;
NativeSocketInterposer::close_fn NativeSocketInterposer::_orig_close = nullptr;
NativeSocketInterposer::connect_fn NativeSocketInterposer::_orig_connect = nullptr;
NativeSocketInterposer::accept_fn NativeSocketInterposer::_orig_accept = nullptr;
NativeSocketInterposer::accept4_fn NativeSocketInterposer::_orig_accept4 = nullptr;
NativeSocketInterposer::recvfrom_fn NativeSocketInterposer::_orig_recvfrom = nullptr;
NativeSocketInterposer::recvmsg_fn NativeSocketInterposer::_orig_recvmsg = nullptr;
NativeSocketInterposer::epoll_wait_fn NativeSocketInterposer::_orig_epoll_wait = nullptr;
NativeSocketInterposer::epoll_pwait_fn NativeSocketInterposer::_orig_epoll_pwait = nullptr;
NativeSocketInterposer::poll_fn NativeSocketInterposer::_orig_poll = nullptr;
NativeSocketInterposer::ppoll_fn NativeSocketInterposer::_orig_ppoll = nullptr;
NativeSocketInterposer::select_fn NativeSocketInterposer::_orig_select = nullptr;
NativeSocketInterposer::pselect_fn NativeSocketInterposer::_orig_pselect = nullptr;

const NativeSocketInterposer::NativeIoHookSpec* NativeSocketInterposer::hookSpecs() {
  static const NativeIoHookSpec specs[NUM_NATIVE_IO_HOOKS] = {
      {im_send, "send", reinterpret_cast<void*>(send_hook)},
      {im_recv, "recv", reinterpret_cast<void*>(recv_hook)},
      {im_write, "write", reinterpret_cast<void*>(write_hook)},
      {im_read, "read", reinterpret_cast<void*>(read_hook)},
      {im_close, "close", reinterpret_cast<void*>(close_hook)},
      {im_connect, "connect", reinterpret_cast<void*>(connect_hook)},
      {im_accept, "accept", reinterpret_cast<void*>(accept_hook)},
      {im_accept4, "accept4", reinterpret_cast<void*>(accept4_hook)},
      {im_recvfrom, "recvfrom", reinterpret_cast<void*>(recvfrom_hook)},
      {im_recvmsg, "recvmsg", reinterpret_cast<void*>(recvmsg_hook)},
      {im_epoll_wait, "epoll_wait", reinterpret_cast<void*>(epoll_wait_hook)},
      {im_epoll_pwait, "epoll_pwait", reinterpret_cast<void*>(epoll_pwait_hook)},
      {im_poll, "poll", reinterpret_cast<void*>(poll_hook)},
      {im_ppoll, "ppoll", reinterpret_cast<void*>(ppoll_hook)},
      {im_select, "select", reinterpret_cast<void*>(select_hook)},
      {im_pselect, "pselect", reinterpret_cast<void*>(pselect_hook)},
  };
  return specs;
}

bool NativeSocketInterposer::setOriginalFunction(int hook_index, void* original) {
  switch (hook_index) {
    case HOOK_SEND:
      _orig_send = reinterpret_cast<send_fn>(original);
      return true;
    case HOOK_RECV:
      _orig_recv = reinterpret_cast<recv_fn>(original);
      return true;
    case HOOK_WRITE:
      _orig_write = reinterpret_cast<write_fn>(original);
      return true;
    case HOOK_READ:
      _orig_read = reinterpret_cast<read_fn>(original);
      return true;
    case HOOK_CLOSE:
      _orig_close = reinterpret_cast<close_fn>(original);
      return true;
    case HOOK_CONNECT:
      _orig_connect = reinterpret_cast<connect_fn>(original);
      return true;
    case HOOK_ACCEPT:
      _orig_accept = reinterpret_cast<accept_fn>(original);
      return true;
    case HOOK_ACCEPT4:
      _orig_accept4 = reinterpret_cast<accept4_fn>(original);
      return true;
    case HOOK_RECVFROM:
      _orig_recvfrom = reinterpret_cast<recvfrom_fn>(original);
      return true;
    case HOOK_RECVMSG:
      _orig_recvmsg = reinterpret_cast<recvmsg_fn>(original);
      return true;
    case HOOK_EPOLL_WAIT:
      _orig_epoll_wait = reinterpret_cast<epoll_wait_fn>(original);
      return true;
    case HOOK_EPOLL_PWAIT:
      _orig_epoll_pwait = reinterpret_cast<epoll_pwait_fn>(original);
      return true;
    case HOOK_POLL:
      _orig_poll = reinterpret_cast<poll_fn>(original);
      return true;
    case HOOK_PPOLL:
      _orig_ppoll = reinterpret_cast<ppoll_fn>(original);
      return true;
    case HOOK_SELECT:
      _orig_select = reinterpret_cast<select_fn>(original);
      return true;
    case HOOK_PSELECT:
      _orig_pselect = reinterpret_cast<pselect_fn>(original);
      return true;
    default:
      return false;
  }
}

bool NativeSocketInterposer::isStreamSocket(int fd) {
  return _fd_classifier.isStreamSocket(fd);
}

bool NativeSocketInterposer::isDatagramSocket(int fd) {
  return _fd_classifier.isDatagramSocket(fd);
}

void NativeSocketInterposer::clearFdType(int fd) {
  _fd_classifier.clearFdType(fd);
}

void NativeSocketInterposer::clearFdTypeCache() {
  _fd_classifier.clearFdTypeCache();
}

Error NativeSocketInterposer::start() {
  clearFdTypeCache();
  _active.store(true, std::memory_order_release);
  if (!LibraryPatcher::patch_socket_functions()) {
    _active.store(false, std::memory_order_release);
    return Error("failed to install native I/O hooks");
  }
  return Error::OK;
}

void NativeSocketInterposer::stop() {
  _active.store(false, std::memory_order_release);
  if (!NativeSocketSampler::active()) {
    LibraryPatcher::unpatch_socket_functions();
  }
  clearFdTypeCache();
}

ssize_t NativeSocketInterposer::send_hook(int fd, const void* buf, size_t len,
                                          int flags) {
  return runStreamSocketHook<ssize_t>(fd, _orig_send, [&](send_fn fn) {
    if (NativeSocketSampler::active()) {
      return NativeSocketSampler::send_hook(fd, buf, len, flags);
    }
    return fn(fd, buf, len, flags);
  });
}

ssize_t NativeSocketInterposer::recv_hook(int fd, void* buf, size_t len,
                                          int flags) {
  return runStreamSocketHook<ssize_t>(fd, _orig_recv, [&](recv_fn fn) {
    if (NativeSocketSampler::active()) {
      return NativeSocketSampler::recv_hook(fd, buf, len, flags);
    }
    return fn(fd, buf, len, flags);
  });
}

ssize_t NativeSocketInterposer::write_hook(int fd, const void* buf, size_t len) {
  return runStreamSocketHook<ssize_t>(fd, _orig_write, [&](write_fn fn) {
    if (NativeSocketSampler::active()) {
      return NativeSocketSampler::write_hook(fd, buf, len);
    }
    return fn(fd, buf, len);
  });
}

ssize_t NativeSocketInterposer::read_hook(int fd, void* buf, size_t len) {
  return runStreamSocketHook<ssize_t>(fd, _orig_read, [&](read_fn fn) {
    if (NativeSocketSampler::active()) {
      return NativeSocketSampler::read_hook(fd, buf, len);
    }
    return fn(fd, buf, len);
  });
}

int NativeSocketInterposer::close_hook(int fd) {
  if (_orig_close == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  int ret = _orig_close(fd);
  int saved_errno = errno;
  if (ret == 0) {
    NativeSocketInterposer::instance()->clearFdType(fd);
  }
  errno = saved_errno;
  return ret;
}

int NativeSocketInterposer::connect_hook(int fd, const struct sockaddr* addr,
                                         socklen_t addrlen) {
  int entry_errno = errno;
  bool eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  errno = entry_errno;
  return runNativeIoHook<int>(eligible, NativeBlockKind::CONNECT, fd, _orig_connect,
                              [&](connect_fn fn) { return fn(fd, addr, addrlen); });
}

int NativeSocketInterposer::accept_hook(int fd, struct sockaddr* addr,
                                        socklen_t* addrlen) {
  int entry_errno = errno;
  bool eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  errno = entry_errno;
  return runNativeIoHook<int>(eligible, NativeBlockKind::ACCEPT, fd, _orig_accept,
                              [&](accept_fn fn) { return fn(fd, addr, addrlen); });
}

int NativeSocketInterposer::accept4_hook(int fd, struct sockaddr* addr,
                                         socklen_t* addrlen, int flags) {
  int entry_errno = errno;
  bool eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  errno = entry_errno;
  return runNativeIoHook<int>(eligible, NativeBlockKind::ACCEPT, fd, _orig_accept4,
                              [&](accept4_fn fn) { return fn(fd, addr, addrlen, flags); });
}

ssize_t NativeSocketInterposer::recvfrom_hook(int fd, void* buf, size_t len,
                                              int flags, struct sockaddr* src_addr,
                                              socklen_t* addrlen) {
  return runDatagramSocketHook<ssize_t>(fd, _orig_recvfrom, [&](recvfrom_fn fn) {
    return fn(fd, buf, len, flags, src_addr, addrlen);
  });
}

ssize_t NativeSocketInterposer::recvmsg_hook(int fd, struct msghdr* msg, int flags) {
  return runDatagramSocketHook<ssize_t>(fd, _orig_recvmsg, [&](recvmsg_fn fn) {
    return fn(fd, msg, flags);
  });
}

int NativeSocketInterposer::epoll_wait_hook(int epfd, struct epoll_event* events,
                                            int maxevents, int timeout) {
  bool eligible = maxevents > 0 && timeout != 0;
  return runNativeIoHook<int>(eligible, NativeBlockKind::EPOLL_WAIT, epfd, _orig_epoll_wait,
                              [&](epoll_wait_fn fn) {
                                return fn(epfd, events, maxevents, timeout);
                              });
}

int NativeSocketInterposer::epoll_pwait_hook(int epfd, struct epoll_event* events,
                                             int maxevents, int timeout,
                                             const sigset_t* sigmask) {
  bool eligible = maxevents > 0 && timeout != 0;
  return runNativeIoHook<int>(eligible, NativeBlockKind::EPOLL_WAIT, epfd, _orig_epoll_pwait,
                              [&](epoll_pwait_fn fn) {
                                return fn(epfd, events, maxevents, timeout, sigmask);
                              });
}

int NativeSocketInterposer::poll_hook(struct pollfd* fds, nfds_t nfds, int timeout) {
  bool eligible = fds != nullptr && nfds > 0 && timeout != 0;
  return runNativeIoHook<int>(eligible, NativeBlockKind::POLL, 0, _orig_poll,
                              [&](poll_fn fn) { return fn(fds, nfds, timeout); });
}

int NativeSocketInterposer::ppoll_hook(struct pollfd* fds, nfds_t nfds,
                                       const struct timespec* timeout_ts,
                                       const sigset_t* sigmask) {
  bool eligible = fds != nullptr && nfds > 0 && nonZeroTimespec(timeout_ts);
  return runNativeIoHook<int>(eligible, NativeBlockKind::POLL, 0, _orig_ppoll,
                              [&](ppoll_fn fn) { return fn(fds, nfds, timeout_ts, sigmask); });
}

int NativeSocketInterposer::select_hook(int nfds, fd_set* readfds, fd_set* writefds,
                                        fd_set* exceptfds, struct timeval* timeout) {
  bool eligible = nfds > 0 && nonZeroTimeval(timeout);
  return runNativeIoHook<int>(eligible, NativeBlockKind::SELECT, 0, _orig_select,
                              [&](select_fn fn) {
                                return fn(nfds, readfds, writefds, exceptfds, timeout);
                              });
}

int NativeSocketInterposer::pselect_hook(int nfds, fd_set* readfds, fd_set* writefds,
                                         fd_set* exceptfds,
                                         const struct timespec* timeout_ts,
                                         const sigset_t* sigmask) {
  bool eligible = nfds > 0 && nonZeroTimespec(timeout_ts);
  return runNativeIoHook<int>(eligible, NativeBlockKind::SELECT, 0, _orig_pselect,
                              [&](pselect_fn fn) {
                                return fn(nfds, readfds, writefds, exceptfds,
                                          timeout_ts, sigmask);
                              });
}

#else

NativeSocketInterposer* const NativeSocketInterposer::_instance = new NativeSocketInterposer();

#endif
