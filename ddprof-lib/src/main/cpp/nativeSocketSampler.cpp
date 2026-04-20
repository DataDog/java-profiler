/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeSocketSampler.h"

#if defined(__linux__) && defined(__GLIBC__)

#include "flightRecorder.h"
#include "libraryPatcher.h"
#include "os.h"
#include "profiler.h"
#include "tsc.h"
#include "vmEntry.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

static thread_local PoissonSampler _send_sampler;
static thread_local PoissonSampler _recv_sampler;

NativeSocketSampler* const NativeSocketSampler::_instance = new NativeSocketSampler();
NativeSocketSampler::send_fn  NativeSocketSampler::_orig_send  = nullptr;
NativeSocketSampler::recv_fn  NativeSocketSampler::_orig_recv  = nullptr;
NativeSocketSampler::write_fn NativeSocketSampler::_orig_write = nullptr;
NativeSocketSampler::read_fn  NativeSocketSampler::_orig_read  = nullptr;

std::string NativeSocketSampler::resolveAddr(int fd) {
    struct sockaddr_storage ss;
    socklen_t len = sizeof(ss);
    if (getpeername(fd, (struct sockaddr*)&ss, &len) != 0) {
        return "";
    }
    char host[INET6_ADDRSTRLEN];
    int port = 0;
    if (ss.ss_family == AF_INET) {
        struct sockaddr_in* s = (struct sockaddr_in*)&ss;
        inet_ntop(AF_INET, &s->sin_addr, host, sizeof(host));
        port = ntohs(s->sin_port);
    } else if (ss.ss_family == AF_INET6) {
        struct sockaddr_in6* s = (struct sockaddr_in6*)&ss;
        inet_ntop(AF_INET6, &s->sin6_addr, host, sizeof(host));
        port = ntohs(s->sin6_port);
    } else {
        return "";
    }
    char buf[INET6_ADDRSTRLEN + 10];
    if (ss.ss_family == AF_INET6) {
        snprintf(buf, sizeof(buf), "[%s]:%d", host, port);
    } else {
        snprintf(buf, sizeof(buf), "%s:%d", host, port);
    }
    return std::string(buf);
}

bool NativeSocketSampler::isSocket(int fd) {
    if ((unsigned)fd >= (unsigned)FD_TYPE_CACHE_SIZE) {
        int so_type;
        socklen_t solen = sizeof(so_type);
        return getsockopt(fd, SOL_SOCKET, SO_TYPE, &so_type, &solen) == 0
               && so_type == SOCK_STREAM;
    }
    uint8_t cached = _fd_type_cache[fd].load(std::memory_order_relaxed);
    if (cached == FD_TYPE_SOCKET)     return true;
    if (cached == FD_TYPE_NON_SOCKET) return false;

    int so_type;
    socklen_t solen = sizeof(so_type);
    bool tcp = getsockopt(fd, SOL_SOCKET, SO_TYPE, &so_type, &solen) == 0
               && so_type == SOCK_STREAM;
    _fd_type_cache[fd].store(tcp ? FD_TYPE_SOCKET : FD_TYPE_NON_SOCKET,
                             std::memory_order_relaxed);
    return tcp;
}

bool NativeSocketSampler::shouldSample(u64 duration_ticks, int op, float &weight) {
    PoissonSampler &sampler = (op == 0) ? _send_sampler : _recv_sampler;
    return sampler.sample(duration_ticks,
                          (u64)_rate_limiter.interval(),
                          _rate_limiter.epoch(),
                          weight);
}

void NativeSocketSampler::recordEvent(int fd, u64 t0, u64 t1, ssize_t bytes, u8 op) {
    float weight = 0.0f;
    if (!shouldSample(t1 - t0, op, weight)) {
        return;
    }

    std::string addr;
    {
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        auto it = _fd_cache.find(fd);
        if (it != _fd_cache.end()) {
            addr = it->second;
        }
    }
    if (addr.empty()) {
        addr = resolveAddr(fd);
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        if ((int)_fd_cache.size() < MAX_FD_CACHE) {
            _fd_cache.emplace(fd, addr);
        }
    }

    NativeSocketEvent event;
    event._start_time = t0;
    event._end_time   = t1;
    event._operation  = op;
    strncpy(event._remote_addr, addr.c_str(), sizeof(event._remote_addr) - 1);
    event._remote_addr[sizeof(event._remote_addr) - 1] = '\0';
    event._bytes  = (u64)bytes;
    event._weight = weight;

    // Pass NULL ucontext (mirrors MallocTracer): recordSample routes
    // BCI_NATIVE_SOCKET to walkVM with no signal context, which walks native
    // frames via DWARF/FP and falls back to JavaFrameAnchor for Java frames.
    Profiler::instance()->recordSample(NULL, (u64)bytes, OS::threadId(),
                                       BCI_NATIVE_SOCKET, 0, &event);

    _rate_limiter.recordFire();
}

ssize_t NativeSocketSampler::send_hook(int fd, const void* buf, size_t len, int flags) {
    u64 t0 = TSC::ticks();
    ssize_t ret = _orig_send(fd, buf, len, flags);
    u64 t1 = TSC::ticks();
    if (ret > 0) {
        _instance->recordEvent(fd, t0, t1, ret, 0);
    }
    return ret;
}

ssize_t NativeSocketSampler::recv_hook(int fd, void* buf, size_t len, int flags) {
    u64 t0 = TSC::ticks();
    ssize_t ret = _orig_recv(fd, buf, len, flags);
    u64 t1 = TSC::ticks();
    if (ret > 0) {
        _instance->recordEvent(fd, t0, t1, ret, 1);
    }
    return ret;
}

ssize_t NativeSocketSampler::write_hook(int fd, const void* buf, size_t len) {
    NativeSocketSampler* self = _instance;
    if (!self->isSocket(fd)) {
        return _orig_write(fd, buf, len);
    }
    u64 t0 = TSC::ticks();
    ssize_t ret = _orig_write(fd, buf, len);
    u64 t1 = TSC::ticks();
    if (ret > 0) {
        self->recordEvent(fd, t0, t1, ret, 0);
    }
    return ret;
}

ssize_t NativeSocketSampler::read_hook(int fd, void* buf, size_t len) {
    NativeSocketSampler* self = _instance;
    if (!self->isSocket(fd)) {
        return _orig_read(fd, buf, len);
    }
    u64 t0 = TSC::ticks();
    ssize_t ret = _orig_read(fd, buf, len);
    u64 t1 = TSC::ticks();
    if (ret > 0) {
        self->recordEvent(fd, t0, t1, ret, 1);
    }
    return ret;
}

Error NativeSocketSampler::check(Arguments &args) {
    if (!args._nativesocket) {
        return Error("natsock profiling not requested");
    }
    return Error::OK;
}

Error NativeSocketSampler::start(Arguments &args) {
    // Default interval: 1 ms in TSC ticks (time-weighted sampling).
    long init_interval = (long)(TSC::frequency() / 1000);
    if (init_interval < 1) {
        init_interval = DEFAULT_INTERVAL_TICKS;
    }
    // One limiter for all four hooks (send/write and recv/read): ~83 events/s (~5000/min) total.
    // A large interval driven by heavy write traffic does not suppress long blocking reads:
    // time-weighted sampling gives P = 1 - exp(-duration/interval) → 1 when duration >> interval,
    // so slow calls self-select regardless of interval magnitude.  Only short-duration calls
    // (which carry no latency signal) are suppressed when the interval is large.
    _rate_limiter.start(init_interval, TARGET_EVENTS_PER_SECOND,
                        PID_WINDOW_SECS, PID_P_GAIN, PID_I_GAIN, PID_D_GAIN, PID_CUTOFF_S);
    // Reset fd-type cache so stale classifications from a prior session don't
    // cause write/read hooks to skip newly opened socket fds.
    for (int i = 0; i < FD_TYPE_CACHE_SIZE; i++) {
        _fd_type_cache[i].store(FD_TYPE_UNKNOWN, std::memory_order_relaxed);
    }
    LibraryPatcher::patch_socket_functions();
    return Error::OK;
}

void NativeSocketSampler::stop() {
    LibraryPatcher::unpatch_socket_functions();
    clearFdCache();
}

void NativeSocketSampler::clearFdCache() {
    std::lock_guard<std::mutex> lock(_fd_cache_mutex);
    _fd_cache.clear();
}

#else // !(__linux__ && __GLIBC__)

NativeSocketSampler* const NativeSocketSampler::_instance = new NativeSocketSampler();

#endif // __linux__ && __GLIBC__
