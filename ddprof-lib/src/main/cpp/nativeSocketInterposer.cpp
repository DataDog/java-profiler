/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeSocketInterposer.h"

#if defined(__linux__)

#include "libraryPatcher.h"
#include "nativeSocketSampler.h"
#include "tsc.h"

#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>

static inline bool nonZeroTimeval(const struct timeval* timeout) {
  return timeout == nullptr || timeout->tv_sec != 0 || timeout->tv_usec != 0;
}

static inline bool nonZeroTimespec(const struct timespec* timeout) {
  return timeout == nullptr || timeout->tv_sec != 0 || timeout->tv_nsec != 0;
}

class ErrnoGuard {
public:
  ErrnoGuard() : _saved(errno) {}
  ~ErrnoGuard() { errno = _saved; }

private:
  int _saved;
};

template <typename Ret, typename Fn, typename Call>
static inline Ret runNativeIoHook(bool eligible, NativeBlockKind kind, int fd,
                                  Fn fn, Call call) {
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

template <typename Fn, typename Call>
static inline ssize_t runStreamSocketHook(int fd, Fn fn, u8 op, Call call) {
  if (fn == nullptr) {
    errno = ENOSYS;
    return -1;
  }

  // read/write are intentionally routed through the socket classifier because
  // socket I/O often uses generic fd APIs. Non-socket fds are cached after the
  // first stable ENOTSOCK probe; high or transiently failing fds may be probed
  // again on later calls.
  bool eligible;
  {
    ErrnoGuard errno_guard;
    eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  }
  if (!eligible) {
    return call(fn);
  }

  u64 t0 = TSC::ticks();
  ssize_t ret;
  {
    NativeBlockScope block(NativeBlockKind::STREAM_SOCKET, fd);
    ret = call(fn);
  }
  u64 t1 = TSC::ticks();
  if (NativeSocketSampler::active()) {
    ErrnoGuard errno_guard;
    return NativeSocketSampler::recordHookResult(fd, ret, t0, t1, op);
  }
  return ret;
}

template <typename Ret, typename Fn, typename Call>
static inline Ret runDatagramSocketHook(int fd, Fn fn, Call call) {
  bool eligible;
  {
    ErrnoGuard errno_guard;
    eligible = NativeSocketInterposer::instance()->isDatagramSocket(fd);
  }
  return runNativeIoHook<Ret>(eligible, NativeBlockKind::UDP_RECEIVE, fd, fn,
                              call);
}

NativeSocketInterposer* const NativeSocketInterposer::_instance = new NativeSocketInterposer();
std::atomic<NativeSocketInterposer::send_fn> NativeSocketInterposer::_orig_send{nullptr};
std::atomic<NativeSocketInterposer::recv_fn> NativeSocketInterposer::_orig_recv{nullptr};
std::atomic<NativeSocketInterposer::write_fn> NativeSocketInterposer::_orig_write{nullptr};
std::atomic<NativeSocketInterposer::read_fn> NativeSocketInterposer::_orig_read{nullptr};
std::atomic<NativeSocketInterposer::close_fn> NativeSocketInterposer::_orig_close{nullptr};
std::atomic<NativeSocketInterposer::dup2_fn> NativeSocketInterposer::_orig_dup2{nullptr};
std::atomic<NativeSocketInterposer::dup3_fn> NativeSocketInterposer::_orig_dup3{nullptr};
std::atomic<NativeSocketInterposer::connect_fn> NativeSocketInterposer::_orig_connect{nullptr};
std::atomic<NativeSocketInterposer::accept_fn> NativeSocketInterposer::_orig_accept{nullptr};
std::atomic<NativeSocketInterposer::accept4_fn> NativeSocketInterposer::_orig_accept4{nullptr};
std::atomic<NativeSocketInterposer::recvfrom_fn> NativeSocketInterposer::_orig_recvfrom{nullptr};
std::atomic<NativeSocketInterposer::recvmsg_fn> NativeSocketInterposer::_orig_recvmsg{nullptr};
std::atomic<NativeSocketInterposer::epoll_wait_fn> NativeSocketInterposer::_orig_epoll_wait{nullptr};
std::atomic<NativeSocketInterposer::epoll_pwait_fn> NativeSocketInterposer::_orig_epoll_pwait{nullptr};
std::atomic<NativeSocketInterposer::poll_fn> NativeSocketInterposer::_orig_poll{nullptr};
std::atomic<NativeSocketInterposer::ppoll_fn> NativeSocketInterposer::_orig_ppoll{nullptr};
std::atomic<NativeSocketInterposer::select_fn> NativeSocketInterposer::_orig_select{nullptr};
std::atomic<NativeSocketInterposer::pselect_fn> NativeSocketInterposer::_orig_pselect{nullptr};
std::atomic<pid_t> NativeSocketInterposer::_hook_owner_pid{0};

static_assert(std::atomic<NativeSocketInterposer::send_fn>::is_always_lock_free,
              "native I/O hook function pointers must be lock-free");
static_assert(std::atomic<pid_t>::is_always_lock_free,
              "native I/O hook owner PID must be lock-free");

const NativeSocketInterposer::NativeIoHookSpec* NativeSocketInterposer::hookSpecs() {
  static const NativeIoHookSpec specs[NUM_NATIVE_IO_HOOKS] = {
      {im_send, "send", reinterpret_cast<void*>(send_hook),
       reinterpret_cast<void*>(fork_safe_send_hook)},
      {im_recv, "recv", reinterpret_cast<void*>(recv_hook),
       reinterpret_cast<void*>(fork_safe_recv_hook)},
      {im_write, "write", reinterpret_cast<void*>(write_hook),
       reinterpret_cast<void*>(fork_safe_write_hook)},
      {im_read, "read", reinterpret_cast<void*>(read_hook),
       reinterpret_cast<void*>(fork_safe_read_hook)},
      {im_close, "close", reinterpret_cast<void*>(close_hook),
       reinterpret_cast<void*>(fork_safe_close_hook)},
      {im_dup2, "dup2", reinterpret_cast<void*>(dup2_hook),
       reinterpret_cast<void*>(fork_safe_dup2_hook)},
      {im_dup3, "dup3", reinterpret_cast<void*>(dup3_hook),
       reinterpret_cast<void*>(fork_safe_dup3_hook)},
      {im_connect, "connect", reinterpret_cast<void*>(connect_hook),
       reinterpret_cast<void*>(fork_safe_connect_hook)},
      {im_accept, "accept", reinterpret_cast<void*>(accept_hook),
       reinterpret_cast<void*>(fork_safe_accept_hook)},
      {im_accept4, "accept4", reinterpret_cast<void*>(accept4_hook),
       reinterpret_cast<void*>(fork_safe_accept4_hook)},
      {im_recvfrom, "recvfrom", reinterpret_cast<void*>(recvfrom_hook),
       reinterpret_cast<void*>(fork_safe_recvfrom_hook)},
      {im_recvmsg, "recvmsg", reinterpret_cast<void*>(recvmsg_hook),
       reinterpret_cast<void*>(fork_safe_recvmsg_hook)},
      {im_epoll_wait, "epoll_wait", reinterpret_cast<void*>(epoll_wait_hook),
       reinterpret_cast<void*>(fork_safe_epoll_wait_hook)},
      {im_epoll_pwait, "epoll_pwait", reinterpret_cast<void*>(epoll_pwait_hook),
       reinterpret_cast<void*>(fork_safe_epoll_pwait_hook)},
      {im_poll, "poll", reinterpret_cast<void*>(poll_hook),
       reinterpret_cast<void*>(fork_safe_poll_hook)},
      {im_ppoll, "ppoll", reinterpret_cast<void*>(ppoll_hook),
       reinterpret_cast<void*>(fork_safe_ppoll_hook)},
      {im_select, "select", reinterpret_cast<void*>(select_hook),
       reinterpret_cast<void*>(fork_safe_select_hook)},
      {im_pselect, "pselect", reinterpret_cast<void*>(pselect_hook),
       reinterpret_cast<void*>(fork_safe_pselect_hook)},
  };
  return specs;
}

bool NativeSocketInterposer::isForkChild() {
  pid_t current_pid = getpid();
  return current_pid != _hook_owner_pid.load(std::memory_order_acquire);
}

bool NativeSocketInterposer::setOriginalFunction(int hook_index, void* original) {
  switch (hook_index) {
    case HOOK_SEND:
      _orig_send.store(reinterpret_cast<send_fn>(original),
                       std::memory_order_release);
      return true;
    case HOOK_RECV:
      _orig_recv.store(reinterpret_cast<recv_fn>(original),
                       std::memory_order_release);
      return true;
    case HOOK_WRITE:
      _orig_write.store(reinterpret_cast<write_fn>(original),
                        std::memory_order_release);
      return true;
    case HOOK_READ:
      _orig_read.store(reinterpret_cast<read_fn>(original),
                       std::memory_order_release);
      return true;
    case HOOK_CLOSE:
      _orig_close.store(reinterpret_cast<close_fn>(original),
                        std::memory_order_release);
      return true;
    case HOOK_DUP2:
      _orig_dup2.store(reinterpret_cast<dup2_fn>(original),
                       std::memory_order_release);
      return true;
    case HOOK_DUP3:
      _orig_dup3.store(reinterpret_cast<dup3_fn>(original),
                       std::memory_order_release);
      return true;
    case HOOK_CONNECT:
      _orig_connect.store(reinterpret_cast<connect_fn>(original),
                          std::memory_order_release);
      return true;
    case HOOK_ACCEPT:
      _orig_accept.store(reinterpret_cast<accept_fn>(original),
                         std::memory_order_release);
      return true;
    case HOOK_ACCEPT4:
      _orig_accept4.store(reinterpret_cast<accept4_fn>(original),
                          std::memory_order_release);
      return true;
    case HOOK_RECVFROM:
      _orig_recvfrom.store(reinterpret_cast<recvfrom_fn>(original),
                           std::memory_order_release);
      return true;
    case HOOK_RECVMSG:
      _orig_recvmsg.store(reinterpret_cast<recvmsg_fn>(original),
                          std::memory_order_release);
      return true;
    case HOOK_EPOLL_WAIT:
      _orig_epoll_wait.store(reinterpret_cast<epoll_wait_fn>(original),
                             std::memory_order_release);
      return true;
    case HOOK_EPOLL_PWAIT:
      _orig_epoll_pwait.store(reinterpret_cast<epoll_pwait_fn>(original),
                              std::memory_order_release);
      return true;
    case HOOK_POLL:
      _orig_poll.store(reinterpret_cast<poll_fn>(original),
                       std::memory_order_release);
      return true;
    case HOOK_PPOLL:
      _orig_ppoll.store(reinterpret_cast<ppoll_fn>(original),
                        std::memory_order_release);
      return true;
    case HOOK_SELECT:
      _orig_select.store(reinterpret_cast<select_fn>(original),
                         std::memory_order_release);
      return true;
    case HOOK_PSELECT:
      _orig_pselect.store(reinterpret_cast<pselect_fn>(original),
                          std::memory_order_release);
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
  LibraryPatcher::unpatch_socket_functions_if_inactive();
  clearFdTypeCache();
}

void NativeSocketInterposer::disableAfterPatchFailure() {
  _active.store(false, std::memory_order_release);
  clearFdTypeCache();
}

ssize_t NativeSocketInterposer::send_hook(int fd, const void* buf, size_t len,
                                          int flags) {
  if (!NativeSocketInterposer::instance()->active() && NativeSocketSampler::active()) {
    return NativeSocketSampler::send_hook(fd, buf, len, flags);
  }
  return runStreamSocketHook(fd, _orig_send.load(std::memory_order_acquire), 0,
                             [&](send_fn fn) { return fn(fd, buf, len, flags); });
}

ssize_t NativeSocketInterposer::recv_hook(int fd, void* buf, size_t len,
                                          int flags) {
  if (!NativeSocketInterposer::instance()->active() && NativeSocketSampler::active()) {
    return NativeSocketSampler::recv_hook(fd, buf, len, flags);
  }
  return runStreamSocketHook(fd, _orig_recv.load(std::memory_order_acquire), 1,
                             [&](recv_fn fn) { return fn(fd, buf, len, flags); });
}

ssize_t NativeSocketInterposer::write_hook(int fd, const void* buf, size_t len) {
  if (!NativeSocketInterposer::instance()->active() && NativeSocketSampler::active()) {
    return NativeSocketSampler::write_hook(fd, buf, len);
  }
  return runStreamSocketHook(fd, _orig_write.load(std::memory_order_acquire), 2,
                             [&](write_fn fn) { return fn(fd, buf, len); });
}

ssize_t NativeSocketInterposer::read_hook(int fd, void* buf, size_t len) {
  if (!NativeSocketInterposer::instance()->active() && NativeSocketSampler::active()) {
    return NativeSocketSampler::read_hook(fd, buf, len);
  }
  return runStreamSocketHook(fd, _orig_read.load(std::memory_order_acquire), 3,
                             [&](read_fn fn) { return fn(fd, buf, len); });
}

int NativeSocketInterposer::close_hook(int fd) {
  int ret;
  close_fn original = _orig_close.load(std::memory_order_acquire);
  if (original == nullptr) {
    ret = static_cast<int>(syscall(SYS_close, fd));
  } else {
    ret = original(fd);
  }
  {
    ErrnoGuard errno_guard;
    NativeSocketInterposer::instance()->clearFdType(fd);
    NativeSocketSampler::instance()->clearFdCacheEntry(fd);
  }
  return ret;
}

int NativeSocketInterposer::dup2_hook(int oldfd, int newfd) {
  int ret;
  dup2_fn original = _orig_dup2.load(std::memory_order_acquire);
  if (original == nullptr) {
#ifdef SYS_dup2
    ret = static_cast<int>(syscall(SYS_dup2, oldfd, newfd));
#else
    errno = ENOSYS;
    ret = -1;
#endif
  } else {
    ret = original(oldfd, newfd);
  }
  {
    ErrnoGuard errno_guard;
    if (ret >= 0) {
      // dup2() implicitly closes newfd before reusing it, so clear stale fd
      // classification and address state for the target descriptor.
      NativeSocketInterposer::instance()->clearFdType(newfd);
      NativeSocketSampler::instance()->clearFdCacheEntry(newfd);
    }
  }
  return ret;
}

int NativeSocketInterposer::dup3_hook(int oldfd, int newfd, int flags) {
  int ret;
  dup3_fn original = _orig_dup3.load(std::memory_order_acquire);
  if (original == nullptr) {
#ifdef SYS_dup3
    ret = static_cast<int>(syscall(SYS_dup3, oldfd, newfd, flags));
#else
    errno = ENOSYS;
    ret = -1;
#endif
  } else {
    ret = original(oldfd, newfd, flags);
  }
  {
    ErrnoGuard errno_guard;
    if (ret >= 0) {
      // dup3() implicitly closes newfd before reusing it, so clear stale fd
      // classification and address state for the target descriptor.
      NativeSocketInterposer::instance()->clearFdType(newfd);
      NativeSocketSampler::instance()->clearFdCacheEntry(newfd);
    }
  }
  return ret;
}

int NativeSocketInterposer::connect_hook(int fd, const struct sockaddr* addr,
                                         socklen_t addrlen) {
  bool eligible;
  {
    ErrnoGuard errno_guard;
    eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  }
  return runNativeIoHook<int>(eligible, NativeBlockKind::CONNECT, fd,
                              _orig_connect.load(std::memory_order_acquire),
                              [&](connect_fn fn) { return fn(fd, addr, addrlen); });
}

int NativeSocketInterposer::accept_hook(int fd, struct sockaddr* addr,
                                        socklen_t* addrlen) {
  bool eligible;
  {
    ErrnoGuard errno_guard;
    eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  }
  return runNativeIoHook<int>(eligible, NativeBlockKind::ACCEPT, fd,
                              _orig_accept.load(std::memory_order_acquire),
                              [&](accept_fn fn) { return fn(fd, addr, addrlen); });
}

int NativeSocketInterposer::accept4_hook(int fd, struct sockaddr* addr,
                                         socklen_t* addrlen, int flags) {
  bool eligible;
  {
    ErrnoGuard errno_guard;
    eligible = NativeSocketInterposer::instance()->isStreamSocket(fd);
  }
  return runNativeIoHook<int>(eligible, NativeBlockKind::ACCEPT, fd,
                              _orig_accept4.load(std::memory_order_acquire),
                              [&](accept4_fn fn) { return fn(fd, addr, addrlen, flags); });
}

ssize_t NativeSocketInterposer::recvfrom_hook(int fd, void* buf, size_t len,
                                              int flags, struct sockaddr* src_addr,
                                              socklen_t* addrlen) {
  return runDatagramSocketHook<ssize_t>(
      fd, _orig_recvfrom.load(std::memory_order_acquire), [&](recvfrom_fn fn) {
        return fn(fd, buf, len, flags, src_addr, addrlen);
      });
}

ssize_t NativeSocketInterposer::recvmsg_hook(int fd, struct msghdr* msg, int flags) {
  return runDatagramSocketHook<ssize_t>(
      fd, _orig_recvmsg.load(std::memory_order_acquire), [&](recvmsg_fn fn) {
        return fn(fd, msg, flags);
      });
}

int NativeSocketInterposer::epoll_wait_hook(int epfd, struct epoll_event* events,
                                            int maxevents, int timeout) {
  bool eligible = maxevents > 0 && timeout != 0;
  return runNativeIoHook<int>(
      eligible, NativeBlockKind::EPOLL_WAIT, epfd,
      _orig_epoll_wait.load(std::memory_order_acquire),
      [&](epoll_wait_fn fn) {
        return fn(epfd, events, maxevents, timeout);
      });
}

int NativeSocketInterposer::epoll_pwait_hook(int epfd, struct epoll_event* events,
                                             int maxevents, int timeout,
                                             const sigset_t* sigmask) {
  bool eligible = maxevents > 0 && timeout != 0;
  return runNativeIoHook<int>(
      eligible, NativeBlockKind::EPOLL_WAIT, epfd,
      _orig_epoll_pwait.load(std::memory_order_acquire),
      [&](epoll_pwait_fn fn) {
        return fn(epfd, events, maxevents, timeout, sigmask);
      });
}

int NativeSocketInterposer::poll_hook(struct pollfd* fds, nfds_t nfds, int timeout) {
  bool eligible = fds != nullptr && nfds > 0 && timeout != 0;
  return runNativeIoHook<int>(eligible, NativeBlockKind::POLL, 0,
                              _orig_poll.load(std::memory_order_acquire),
                              [&](poll_fn fn) { return fn(fds, nfds, timeout); });
}

int NativeSocketInterposer::ppoll_hook(struct pollfd* fds, nfds_t nfds,
                                       const struct timespec* timeout_ts,
                                       const sigset_t* sigmask) {
  bool eligible = fds != nullptr && nfds > 0 && nonZeroTimespec(timeout_ts);
  return runNativeIoHook<int>(eligible, NativeBlockKind::POLL, 0,
                              _orig_ppoll.load(std::memory_order_acquire),
                              [&](ppoll_fn fn) { return fn(fds, nfds, timeout_ts, sigmask); });
}

int NativeSocketInterposer::select_hook(int nfds, fd_set* readfds, fd_set* writefds,
                                        fd_set* exceptfds, struct timeval* timeout) {
  bool eligible = nfds > 0 && nonZeroTimeval(timeout);
  return runNativeIoHook<int>(eligible, NativeBlockKind::SELECT, 0,
                              _orig_select.load(std::memory_order_acquire),
                              [&](select_fn fn) {
                                return fn(nfds, readfds, writefds, exceptfds, timeout);
                              });
}

int NativeSocketInterposer::pselect_hook(int nfds, fd_set* readfds, fd_set* writefds,
                                         fd_set* exceptfds,
                                         const struct timespec* timeout_ts,
                                         const sigset_t* sigmask) {
  bool eligible = nfds > 0 && nonZeroTimespec(timeout_ts);
  return runNativeIoHook<int>(eligible, NativeBlockKind::SELECT, 0,
                              _orig_pselect.load(std::memory_order_acquire),
                              [&](pselect_fn fn) {
                                return fn(nfds, readfds, writefds, exceptfds,
                                          timeout_ts, sigmask);
                              });
}

ssize_t NativeSocketInterposer::fork_safe_send_hook(int fd, const void* buf,
                                                     size_t len, int flags) {
  if (!isForkChild()) {
    return send_hook(fd, buf, len, flags);
  }
  send_fn original = _orig_send.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, buf, len, flags);
}

ssize_t NativeSocketInterposer::fork_safe_recv_hook(int fd, void* buf,
                                                     size_t len, int flags) {
  if (!isForkChild()) {
    return recv_hook(fd, buf, len, flags);
  }
  recv_fn original = _orig_recv.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, buf, len, flags);
}

ssize_t NativeSocketInterposer::fork_safe_write_hook(int fd, const void* buf,
                                                      size_t len) {
  if (!isForkChild()) {
    return write_hook(fd, buf, len);
  }
  write_fn original = _orig_write.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, buf, len);
}

ssize_t NativeSocketInterposer::fork_safe_read_hook(int fd, void* buf,
                                                     size_t len) {
  if (!isForkChild()) {
    return read_hook(fd, buf, len);
  }
  read_fn original = _orig_read.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, buf, len);
}

int NativeSocketInterposer::fork_safe_close_hook(int fd) {
  if (!isForkChild()) {
    return close_hook(fd);
  }
  close_fn original = _orig_close.load(std::memory_order_acquire);
  return original == nullptr ? static_cast<int>(syscall(SYS_close, fd))
                             : original(fd);
}

int NativeSocketInterposer::fork_safe_dup2_hook(int oldfd, int newfd) {
  if (!isForkChild()) {
    return dup2_hook(oldfd, newfd);
  }
  dup2_fn original = _orig_dup2.load(std::memory_order_acquire);
  if (original != nullptr) {
    return original(oldfd, newfd);
  }
#ifdef SYS_dup2
  return static_cast<int>(syscall(SYS_dup2, oldfd, newfd));
#else
  errno = ENOSYS;
  return -1;
#endif
}

int NativeSocketInterposer::fork_safe_dup3_hook(int oldfd, int newfd, int flags) {
  if (!isForkChild()) {
    return dup3_hook(oldfd, newfd, flags);
  }
  dup3_fn original = _orig_dup3.load(std::memory_order_acquire);
  if (original != nullptr) {
    return original(oldfd, newfd, flags);
  }
#ifdef SYS_dup3
  return static_cast<int>(syscall(SYS_dup3, oldfd, newfd, flags));
#else
  errno = ENOSYS;
  return -1;
#endif
}

int NativeSocketInterposer::fork_safe_connect_hook(
    int fd, const struct sockaddr* addr, socklen_t addrlen) {
  if (!isForkChild()) {
    return connect_hook(fd, addr, addrlen);
  }
  connect_fn original = _orig_connect.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, addr, addrlen);
}

int NativeSocketInterposer::fork_safe_accept_hook(int fd, struct sockaddr* addr,
                                                   socklen_t* addrlen) {
  if (!isForkChild()) {
    return accept_hook(fd, addr, addrlen);
  }
  accept_fn original = _orig_accept.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, addr, addrlen);
}

int NativeSocketInterposer::fork_safe_accept4_hook(int fd, struct sockaddr* addr,
                                                    socklen_t* addrlen,
                                                    int flags) {
  if (!isForkChild()) {
    return accept4_hook(fd, addr, addrlen, flags);
  }
  accept4_fn original = _orig_accept4.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, addr, addrlen, flags);
}

ssize_t NativeSocketInterposer::fork_safe_recvfrom_hook(
    int fd, void* buf, size_t len, int flags, struct sockaddr* src_addr,
    socklen_t* addrlen) {
  if (!isForkChild()) {
    return recvfrom_hook(fd, buf, len, flags, src_addr, addrlen);
  }
  recvfrom_fn original = _orig_recvfrom.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, buf, len, flags, src_addr, addrlen);
}

ssize_t NativeSocketInterposer::fork_safe_recvmsg_hook(int fd,
                                                        struct msghdr* msg,
                                                        int flags) {
  if (!isForkChild()) {
    return recvmsg_hook(fd, msg, flags);
  }
  recvmsg_fn original = _orig_recvmsg.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fd, msg, flags);
}

int NativeSocketInterposer::fork_safe_epoll_wait_hook(
    int epfd, struct epoll_event* events, int maxevents, int timeout) {
  if (!isForkChild()) {
    return epoll_wait_hook(epfd, events, maxevents, timeout);
  }
  epoll_wait_fn original = _orig_epoll_wait.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(epfd, events, maxevents, timeout);
}

int NativeSocketInterposer::fork_safe_epoll_pwait_hook(
    int epfd, struct epoll_event* events, int maxevents, int timeout,
    const sigset_t* sigmask) {
  if (!isForkChild()) {
    return epoll_pwait_hook(epfd, events, maxevents, timeout, sigmask);
  }
  epoll_pwait_fn original = _orig_epoll_pwait.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(epfd, events, maxevents, timeout, sigmask);
}

int NativeSocketInterposer::fork_safe_poll_hook(struct pollfd* fds,
                                                 nfds_t nfds, int timeout) {
  if (!isForkChild()) {
    return poll_hook(fds, nfds, timeout);
  }
  poll_fn original = _orig_poll.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fds, nfds, timeout);
}

int NativeSocketInterposer::fork_safe_ppoll_hook(
    struct pollfd* fds, nfds_t nfds, const struct timespec* timeout_ts,
    const sigset_t* sigmask) {
  if (!isForkChild()) {
    return ppoll_hook(fds, nfds, timeout_ts, sigmask);
  }
  ppoll_fn original = _orig_ppoll.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(fds, nfds, timeout_ts, sigmask);
}

int NativeSocketInterposer::fork_safe_select_hook(
    int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds,
    struct timeval* timeout) {
  if (!isForkChild()) {
    return select_hook(nfds, readfds, writefds, exceptfds, timeout);
  }
  select_fn original = _orig_select.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(nfds, readfds, writefds, exceptfds, timeout);
}

int NativeSocketInterposer::fork_safe_pselect_hook(
    int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds,
    const struct timespec* timeout_ts, const sigset_t* sigmask) {
  if (!isForkChild()) {
    return pselect_hook(nfds, readfds, writefds, exceptfds, timeout_ts, sigmask);
  }
  pselect_fn original = _orig_pselect.load(std::memory_order_acquire);
  if (original == nullptr) {
    errno = ENOSYS;
    return -1;
  }
  return original(nfds, readfds, writefds, exceptfds, timeout_ts, sigmask);
}

#else

NativeSocketInterposer* const NativeSocketInterposer::_instance = new NativeSocketInterposer();

#endif
