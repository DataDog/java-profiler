/*
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "socketTracer.h"

#ifdef __linux__

#include "common.h"
#include "event.h"
#include "libraries.h"
#include "profiler.h"
#include "thread.h"
#include "tsc.h"

#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <ucontext.h>
#include <unistd.h>

// --------------------------------------------------------------------------
// Type aliases for the original libc function signatures
// --------------------------------------------------------------------------

typedef ssize_t (*func_read)(int fd, void* buf, size_t count);
typedef ssize_t (*func_write)(int fd, const void* buf, size_t count);
typedef ssize_t (*func_readv)(int fd, const struct iovec* iov, int iovcnt);
typedef ssize_t (*func_writev)(int fd, const struct iovec* iov, int iovcnt);
typedef ssize_t (*func_recv)(int fd, void* buf, size_t len, int flags);
typedef ssize_t (*func_send)(int fd, const void* buf, size_t len, int flags);
typedef ssize_t (*func_recvmsg)(int fd, struct msghdr* msg, int flags);
typedef ssize_t (*func_sendmsg)(int fd, const struct msghdr* msg, int flags);
typedef int     (*func_connect)(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
typedef int     (*func_accept)(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
typedef int     (*func_accept4)(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags);
typedef int     (*func_epoll_wait)(int epfd, struct epoll_event* events, int maxevents, int timeout);

// --------------------------------------------------------------------------
// Static state
// --------------------------------------------------------------------------

SpinLock SocketTracer::_lock;
bool SocketTracer::_initialized = false;
SocketTracer::PatchedLib SocketTracer::_patched_libs[SocketTracer::MAX_PATCHED_LIBS];
int SocketTracer::_patched_count = 0;

// Original function pointers resolved once via dlsym so that we always call
// the real libc function without triggering the lazy-binding resolver, which
// would write the resolved address back to the GOT and overwrite our hook.
static func_read        _orig_read        = nullptr;
static func_write       _orig_write       = nullptr;
static func_readv       _orig_readv       = nullptr;
static func_writev      _orig_writev      = nullptr;
static func_recv        _orig_recv        = nullptr;
static func_send        _orig_send        = nullptr;
static func_recvmsg     _orig_recvmsg     = nullptr;
static func_sendmsg     _orig_sendmsg     = nullptr;
static func_connect     _orig_connect     = nullptr;
static func_accept      _orig_accept      = nullptr;
static func_accept4     _orig_accept4     = nullptr;
static func_epoll_wait  _orig_epoll_wait  = nullptr;

// --------------------------------------------------------------------------
// Resolve all original function pointers via dlsym once
// --------------------------------------------------------------------------

static void resolveOriginals() {
    if (_orig_read == nullptr)
        _orig_read       = (func_read)       dlsym(RTLD_DEFAULT, "read");
    if (_orig_write == nullptr)
        _orig_write      = (func_write)      dlsym(RTLD_DEFAULT, "write");
    if (_orig_readv == nullptr)
        _orig_readv      = (func_readv)      dlsym(RTLD_DEFAULT, "readv");
    if (_orig_writev == nullptr)
        _orig_writev     = (func_writev)     dlsym(RTLD_DEFAULT, "writev");
    if (_orig_recv == nullptr)
        _orig_recv       = (func_recv)       dlsym(RTLD_DEFAULT, "recv");
    if (_orig_send == nullptr)
        _orig_send       = (func_send)       dlsym(RTLD_DEFAULT, "send");
    if (_orig_recvmsg == nullptr)
        _orig_recvmsg    = (func_recvmsg)    dlsym(RTLD_DEFAULT, "recvmsg");
    if (_orig_sendmsg == nullptr)
        _orig_sendmsg    = (func_sendmsg)    dlsym(RTLD_DEFAULT, "sendmsg");
    if (_orig_connect == nullptr)
        _orig_connect    = (func_connect)    dlsym(RTLD_DEFAULT, "connect");
    if (_orig_accept == nullptr)
        _orig_accept     = (func_accept)     dlsym(RTLD_DEFAULT, "accept");
    if (_orig_accept4 == nullptr)
        _orig_accept4    = (func_accept4)    dlsym(RTLD_DEFAULT, "accept4");
    if (_orig_epoll_wait == nullptr)
        _orig_epoll_wait = (func_epoll_wait) dlsym(RTLD_DEFAULT, "epoll_wait");
}

// --------------------------------------------------------------------------
// Helper: emit a SocketIOEvent to the profiler
// --------------------------------------------------------------------------

static inline void emitSocketIOEvent(const char* operation, u64 start, u64 end, long bytes) {
    int tid = ProfiledThread::currentTid();
    if (tid < 0) {
        return;
    }
    SocketIOEvent event;
    event._start     = start;
    event._end       = end;
    event._operation = operation;
    event._bytes     = bytes;

    // Capture current context for stack walking
    ucontext_t uctx;
    void* ucontext_ptr = nullptr;
    if (getcontext(&uctx) == 0) {
        ucontext_ptr = &uctx;
    }

    // Call recordSample with BCI_SOCKET_IO event type
    // counter=0, call_trace_id=0 (will be captured by recordSample)
    Profiler::instance()->recordSample(ucontext_ptr, 0, tid, BCI_SOCKET_IO, 0, (Event*)&event);
}

// --------------------------------------------------------------------------
// Hook implementations
// --------------------------------------------------------------------------

__attribute__((visibility("hidden")))
static ssize_t read_hook(int fd, void* buf, size_t count) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_read(fd, buf, count);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_READ, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t write_hook(int fd, const void* buf, size_t count) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_write(fd, buf, count);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_WRITE, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t readv_hook(int fd, const struct iovec* iov, int iovcnt) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_readv(fd, iov, iovcnt);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_READV, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t writev_hook(int fd, const struct iovec* iov, int iovcnt) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_writev(fd, iov, iovcnt);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_WRITEV, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t recv_hook(int fd, void* buf, size_t len, int flags) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_recv(fd, buf, len, flags);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_RECV, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t send_hook(int fd, const void* buf, size_t len, int flags) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_send(fd, buf, len, flags);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_SEND, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t recvmsg_hook(int fd, struct msghdr* msg, int flags) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_recvmsg(fd, msg, flags);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_RECVMSG, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static ssize_t sendmsg_hook(int fd, const struct msghdr* msg, int flags) {
    u64 start = TSC::ticks();
    ssize_t ret = _orig_sendmsg(fd, msg, flags);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_SENDMSG, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static int connect_hook(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    u64 start = TSC::ticks();
    int ret = _orig_connect(sockfd, addr, addrlen);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_CONNECT, start, end, -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static int accept_hook(int sockfd, struct sockaddr* addr, socklen_t* addrlen) {
    u64 start = TSC::ticks();
    int ret = _orig_accept(sockfd, addr, addrlen);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_ACCEPT, start, end, -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static int accept4_hook(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags) {
    u64 start = TSC::ticks();
    int ret = _orig_accept4(sockfd, addr, addrlen, flags);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_ACCEPT4, start, end, -1);
    errno = saved_errno;
    return ret;
}

__attribute__((visibility("hidden")))
static int epoll_wait_hook(int epfd, struct epoll_event* events, int maxevents, int timeout) {
    u64 start = TSC::ticks();
    int ret = _orig_epoll_wait(epfd, events, maxevents, timeout);
    int saved_errno = errno;
    u64 end = TSC::ticks();
    emitSocketIOEvent(SOCKET_OP_EPOLL_WAIT, start, end, ret >= 0 ? ret : -1);
    errno = saved_errno;
    return ret;
}

// --------------------------------------------------------------------------
// Library detection and patching
// --------------------------------------------------------------------------

bool SocketTracer::isNettyLibrary(const char* name) {
    if (name == nullptr) {
        return false;
    }
    return strstr(name, "netty") != nullptr;
}

void SocketTracer::patchLibraryUnlocked(CodeCache* lib) {
    if (!isNettyLibrary(lib->name())) {
        return;
    }

    // Prevent double-patching
    for (int i = 0; i < _patched_count; i++) {
        if (_patched_libs[i].lib == lib) {
            return;
        }
    }

    if (_patched_count >= MAX_PATCHED_LIBS) {
        return;
    }

    // Resolve all original function pointers via dlsym before patching.
    // This ensures _orig_xxx always points to the real libc function, not a
    // PLT stub. If we stored the PLT stub, the first call through our hook
    // would invoke the lazy-binding resolver, which writes the real address
    // back to the GOT — overwriting our hook and making all subsequent calls
    // bypass instrumentation.
    resolveOriginals();

    PatchedLib& entry = _patched_libs[_patched_count];
    entry.lib              = lib;
    entry.original_read    = nullptr;
    entry.original_write   = nullptr;
    entry.original_readv   = nullptr;
    entry.original_writev  = nullptr;
    entry.original_recv    = nullptr;
    entry.original_send    = nullptr;
    entry.original_recvmsg = nullptr;
    entry.original_sendmsg = nullptr;
    entry.original_connect = nullptr;
    entry.original_accept  = nullptr;
    entry.original_accept4 = nullptr;
    entry.original_epoll_wait = nullptr;

    void** loc;

#define PATCH(import_id, field, hook) \
    if ((loc = lib->findImport(import_id)) != nullptr) { \
        entry.field = *loc; \
        __atomic_store_n(loc, (void*)(hook), __ATOMIC_RELAXED); \
    }

    PATCH(im_read,       original_read,       read_hook)
    PATCH(im_write,      original_write,      write_hook)
    PATCH(im_readv,      original_readv,      readv_hook)
    PATCH(im_writev,     original_writev,     writev_hook)
    PATCH(im_recv,       original_recv,       recv_hook)
    PATCH(im_send,       original_send,       send_hook)
    PATCH(im_recvmsg,    original_recvmsg,    recvmsg_hook)
    PATCH(im_sendmsg,    original_sendmsg,    sendmsg_hook)
    PATCH(im_connect,    original_connect,    connect_hook)
    PATCH(im_accept,     original_accept,     accept_hook)
    PATCH(im_accept4,    original_accept4,    accept4_hook)
    PATCH(im_epoll_wait, original_epoll_wait, epoll_wait_hook)

#undef PATCH

    _patched_count++;
    TEST_LOG("SocketTracer: patched library: %s", lib->name());
}

void SocketTracer::initialize() {
    ExclusiveLockGuard locker(&_lock);
    _initialized = true;
}

void SocketTracer::patchLibraries() {
    if (!_initialized) {
        return;
    }

    const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
    int count = native_libs.count();
    ExclusiveLockGuard locker(&_lock);
    for (int i = 0; i < count; i++) {
        patchLibraryUnlocked(native_libs.at(i));
    }
}

void SocketTracer::unpatchLibraries() {
    ExclusiveLockGuard locker(&_lock);
    for (int i = 0; i < _patched_count; i++) {
        PatchedLib& entry = _patched_libs[i];
        void** loc;

#define UNPATCH(import_id, field) \
        if (entry.field != nullptr && (loc = entry.lib->findImport(import_id)) != nullptr) { \
            __atomic_store_n(loc, entry.field, __ATOMIC_RELAXED); \
        }

        UNPATCH(im_read,       original_read)
        UNPATCH(im_write,      original_write)
        UNPATCH(im_readv,      original_readv)
        UNPATCH(im_writev,     original_writev)
        UNPATCH(im_recv,       original_recv)
        UNPATCH(im_send,       original_send)
        UNPATCH(im_recvmsg,    original_recvmsg)
        UNPATCH(im_sendmsg,    original_sendmsg)
        UNPATCH(im_connect,    original_connect)
        UNPATCH(im_accept,     original_accept)
        UNPATCH(im_accept4,    original_accept4)
        UNPATCH(im_epoll_wait, original_epoll_wait)

#undef UNPATCH
    }
    _patched_count = 0;
    _orig_read       = nullptr;
    _orig_write      = nullptr;
    _orig_readv      = nullptr;
    _orig_writev     = nullptr;
    _orig_recv       = nullptr;
    _orig_send       = nullptr;
    _orig_recvmsg    = nullptr;
    _orig_sendmsg    = nullptr;
    _orig_connect    = nullptr;
    _orig_accept     = nullptr;
    _orig_accept4    = nullptr;
    _orig_epoll_wait = nullptr;
    TEST_LOG("SocketTracer: unpatched all libraries");
}

#endif  // __linux__
