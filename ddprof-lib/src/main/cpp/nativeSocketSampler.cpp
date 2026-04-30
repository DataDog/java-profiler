/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeSocketSampler.h"

#if defined(__linux__)

#include "common.h"
#include "flightRecorder.h"
#include "libraryPatcher.h"
#include "os.h"
#include "profiler.h"
#include "tsc.h"
#include "vmEntry.h"

#include <arpa/inet.h>
#include <atomic>
#include <climits>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

static thread_local PoissonSampler _send_sampler;
static thread_local PoissonSampler _recv_sampler;

// Debug-only hook-fire counters, paired with TEST_LOG (common.h). Gated at
// compile time to keep release hot paths free of cross-thread atomic writes.
#ifdef DEBUG
static std::atomic<uint64_t> _send_hook_calls{0};
static std::atomic<uint64_t> _recv_hook_calls{0};
static std::atomic<uint64_t> _write_hook_calls{0};
static std::atomic<uint64_t> _read_hook_calls{0};
static std::atomic<uint64_t> _record_accept_calls{0};
static std::atomic<uint64_t> _record_reject_calls{0};
#endif

// intentional process-lifetime singleton — matches MallocTracer pattern; no destructor needed
NativeSocketSampler* const NativeSocketSampler::_instance = new NativeSocketSampler();
NativeSocketSampler::send_fn  NativeSocketSampler::_orig_send  = nullptr;
NativeSocketSampler::recv_fn  NativeSocketSampler::_orig_recv  = nullptr;
NativeSocketSampler::write_fn NativeSocketSampler::_orig_write = nullptr;
NativeSocketSampler::read_fn  NativeSocketSampler::_orig_read  = nullptr;

std::string NativeSocketSampler::resolveAddr(int fd) {
    struct sockaddr_storage ss;
    socklen_t len = sizeof(ss);
    if (getpeername(fd, (struct sockaddr*)&ss, &len) != 0) {
        TEST_LOG("NativeSocketSampler::resolveAddr getpeername fd=%d failed errno=%d", fd, errno);
        return "";
    }
    char host[INET6_ADDRSTRLEN];
    int port = 0;
    if (ss.ss_family == AF_INET) {
        struct sockaddr_in* s = (struct sockaddr_in*)&ss;
        if (inet_ntop(AF_INET, &s->sin_addr, host, sizeof(host)) == nullptr) return "";
        port = ntohs(s->sin_port);
    } else if (ss.ss_family == AF_INET6) {
        struct sockaddr_in6* s = (struct sockaddr_in6*)&ss;
        if (inet_ntop(AF_INET6, &s->sin6_addr, host, sizeof(host)) == nullptr) return "";
        port = ntohs(s->sin6_port);
    } else {
        return "";
    }
    // [addr]:port — INET6_ADDRSTRLEN(46) + brackets(2) + colon(1) + port(5) + NUL(1) = 55; round to 64.
    static const int FORMATTED_ADDR_BUF = 64;
    char buf[FORMATTED_ADDR_BUF];
    int n;
    if (ss.ss_family == AF_INET6) {
        n = snprintf(buf, sizeof(buf), "[%s]:%d", host, port);
    } else {
        n = snprintf(buf, sizeof(buf), "%s:%d", host, port);
    }
    // Truncation is theoretical (buf is 64 bytes, max needed is 55), but snprintf
    // already NUL-terminates on truncation; suppress unused-variable warning in release.
    (void)n;
    return std::string(buf);
}

bool NativeSocketSampler::isSocket(int fd) {
    // Accepts any SOCK_STREAM socket (including AF_UNIX); AF_INET/AF_INET6 filtering
    // is deferred to resolveAddr() which is only called for sampled events. AF_UNIX
    // will produce an empty remoteAddress field in the JFR event.
    if (fd < 0) return false;
    if ((size_t)fd >= (size_t)FD_TYPE_CACHE_SIZE) {
        int so_type;
        socklen_t solen = sizeof(so_type);
        return getsockopt(fd, SOL_SOCKET, SO_TYPE, &so_type, &solen) == 0
               && so_type == SOCK_STREAM;
    }
    // Acquire on the gen load pairs with the release on the gen-bump in start()
    // and on the cache cell store below; without it, on a weakly-ordered arch
    // (aarch64) a thread could observe a freshly written cell without the matching
    // gen bump (or vice versa), defeating the generation-tag invalidation contract.
    uint8_t gen = _fd_cache_gen.load(std::memory_order_acquire);
    uint8_t cached = _fd_type_cache[fd].load(std::memory_order_acquire);
    // High nibble encodes generation; entry is valid only when it matches current gen mod 16.
    if ((cached >> 4) == (gen & 0xF)) {
        uint8_t type = cached & 0xF;
        if (type == FD_TYPE_SOCKET)     return true;
        if (type == FD_TYPE_NON_SOCKET) return false;
    }

    int so_type;
    socklen_t solen = sizeof(so_type);
    int rc = getsockopt(fd, SOL_SOCKET, SO_TYPE, &so_type, &solen);
    if (rc == 0) {
        bool tcp = (so_type == SOCK_STREAM);
        uint8_t type = tcp ? FD_TYPE_SOCKET : FD_TYPE_NON_SOCKET;
        _fd_type_cache[fd].store((uint8_t)(((gen & 0xF) << 4) | type),
                                 std::memory_order_release);
        return tcp;
    }
    // Only cache the non-socket verdict when getsockopt definitively says
    // "not a socket" (ENOTSOCK).  Transient errors (EBADF on a racing close,
    // EINTR, etc.) must NOT poison the cache: a sticky misclassification
    // would survive fd reuse via dup2() and silently suppress sampling for
    // the rest of the session.
    if (errno == ENOTSOCK) {
        _fd_type_cache[fd].store((uint8_t)(((gen & 0xF) << 4) | FD_TYPE_NON_SOCKET),
                                 std::memory_order_release);
    }
    return false;
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
    bool sampled = shouldSample(t1 - t0, op, weight);
    if (!sampled) {
#ifdef DEBUG
        uint64_t n = _record_reject_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::recordEvent REJECT #%llu fd=%d op=%u bytes=%zd dur_ticks=%llu",
                     (unsigned long long)(n + 1), fd, (unsigned)op, bytes,
                     (unsigned long long)(t1 - t0));
        }
#endif
        return;
    }
#ifdef DEBUG
    {
        uint64_t n = _record_accept_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3F) == 0) {
            TEST_LOG("NativeSocketSampler::recordEvent ACCEPT #%llu fd=%d op=%u bytes=%zd dur_ticks=%llu weight=%f",
                     (unsigned long long)(n + 1), fd, (unsigned)op, bytes,
                     (unsigned long long)(t1 - t0), (double)weight);
        }
    }
#endif

    NativeSocketEvent event;
    event._start_time = t0;
    event._end_time   = t1;
    event._operation  = op;
    event._remote_addr[0] = '\0';
    {
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        auto it = _fd_cache.find(fd);
        if (it != _fd_cache.end()) {
            strncpy(event._remote_addr, it->second.c_str(), sizeof(event._remote_addr) - 1);
            event._remote_addr[sizeof(event._remote_addr) - 1] = '\0';
        }
    }
    // TOCTOU: resolveAddr runs without the lock; concurrent emplace is safe (first writer wins).
    // Skip resolveAddr entirely once the cache is full — otherwise the hot path
    // degrades to per-event getpeername+inet_ntop+std::string for fds that will
    // never be cached.
    if (event._remote_addr[0] == '\0' && !_fd_cache_full.load(std::memory_order_acquire)) {
        std::string resolved = resolveAddr(fd);
        strncpy(event._remote_addr, resolved.c_str(), sizeof(event._remote_addr) - 1);
        event._remote_addr[sizeof(event._remote_addr) - 1] = '\0';
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        if ((int)_fd_cache.size() < MAX_FD_CACHE) {
            _fd_cache.emplace(fd, resolved);
            if ((int)_fd_cache.size() >= MAX_FD_CACHE) {
                _fd_cache_full.store(true, std::memory_order_release);
            }
        }
    }
    // ret > 0 checked above; cast is safe.
    event._bytes  = (u64)bytes;
    event._weight = weight;

    // Pass NULL ucontext (mirrors MallocTracer): recordSample routes
    // BCI_NATIVE_SOCKET to walkVM with no signal context, which walks native
    // frames via DWARF/FP and falls back to JavaFrameAnchor for Java frames.
    // No isRunning() guard here: hook bodies check _socket_active before calling
    // recordEvent(), so in-flight calls that slip through during unpatch are
    // benign — recordSample() will simply fail to acquire a lock slot and return.
    Profiler::instance()->recordSample(NULL, (u64)bytes, OS::threadId(),
                                       BCI_NATIVE_SOCKET, 0, &event);

    _rate_limiter.recordFire();
}

ssize_t NativeSocketSampler::send_hook(int fd, const void* buf, size_t len, int flags) {
    // Defensive guard against direct invocation outside of PLT dispatch (e.g. tests
    // that obtain the static symbol address before LibraryPatcher::patch_socket_functions
    // has run).  Production hooks are unreachable until setOriginalFunctions() has been
    // called under _lock, so this branch is not exercised on the normal path.
    send_fn fn = _orig_send;
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len, flags);
#ifdef DEBUG
    {
        uint64_t n = _send_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::send_hook #%llu fd=%d len=%zu flags=0x%x",
                     (unsigned long long)(n + 1), fd, len, flags);
        }
    }
#endif
    u64 t0 = TSC::ticks();
    return record_if_positive(fd, fn(fd, buf, len, flags), t0, TSC::ticks(), 0);
}

ssize_t NativeSocketSampler::recv_hook(int fd, void* buf, size_t len, int flags) {
    recv_fn fn = _orig_recv;
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len, flags);
#ifdef DEBUG
    {
        uint64_t n = _recv_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::recv_hook #%llu fd=%d len=%zu flags=0x%x",
                     (unsigned long long)(n + 1), fd, len, flags);
        }
    }
#endif
    u64 t0 = TSC::ticks();
    return record_if_positive(fd, fn(fd, buf, len, flags), t0, TSC::ticks(), 1);
}

ssize_t NativeSocketSampler::write_hook(int fd, const void* buf, size_t len) {
    write_fn fn = _orig_write;
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len);
    NativeSocketSampler* self = _instance;
    if (!self->isSocket(fd)) {
#ifdef DEBUG
        uint64_t n = _write_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::write_hook #%llu fd=%d len=%zu is_socket=0",
                     (unsigned long long)(n + 1), fd, len);
        }
#endif
        return fn(fd, buf, len);
    }
#ifdef DEBUG
    {
        uint64_t n = _write_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::write_hook #%llu fd=%d len=%zu is_socket=1",
                     (unsigned long long)(n + 1), fd, len);
        }
    }
#endif
    u64 t0 = TSC::ticks();
    return record_if_positive(fd, fn(fd, buf, len), t0, TSC::ticks(), 2);
}

ssize_t NativeSocketSampler::read_hook(int fd, void* buf, size_t len) {
    read_fn fn = _orig_read;
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len);
    NativeSocketSampler* self = _instance;
    if (!self->isSocket(fd)) {
#ifdef DEBUG
        uint64_t n = _read_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::read_hook #%llu fd=%d len=%zu is_socket=0",
                     (unsigned long long)(n + 1), fd, len);
        }
#endif
        return fn(fd, buf, len);
    }
#ifdef DEBUG
    {
        uint64_t n = _read_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::read_hook #%llu fd=%d len=%zu is_socket=1",
                     (unsigned long long)(n + 1), fd, len);
        }
    }
#endif
    u64 t0 = TSC::ticks();
    return record_if_positive(fd, fn(fd, buf, len), t0, TSC::ticks(), 3);
}

Error NativeSocketSampler::check(Arguments &args) {
    if (!args._nativesocket) {
        return Error("natsock profiling not requested");
    }
    return Error::OK;
}

Error NativeSocketSampler::start(Arguments &args) {
    // Clear the fd cache on start so stale entries from a prior session don't
    // produce misattributed events even if stop() was not called.
    clearFdCache();
    // Initial sampling period: args._nativesocket_interval (ns) when > 0,
    // otherwise 1 ms default.  Converted to TSC ticks (time-weighted sampling).
    //
    // Overflow guard: the naive (interval_ns * tsc_freq) can wrap u64 when the
    // configured interval is large.  At a 3 GHz TSC the product overflows around
    // interval_ns ≈ 6.1 s.  Compute via divide-first to keep the intermediate
    // bounded: ticks = interval_ns * (freq/1e9) ≈ ns_per_tick⁻¹ * interval_ns.
    long init_interval;
    if (args._nativesocket_interval > 0) {
        u64 ns       = (u64)args._nativesocket_interval;
        u64 tsc_freq = TSC::frequency();
        u64 secs     = ns / 1000000000ULL;
        u64 sub_ns   = ns % 1000000000ULL;
        u64 ticks    = secs * tsc_freq + (sub_ns * tsc_freq) / 1000000000ULL;
        // Clamp to LONG_MAX (the field is `long`).  Anything >2^63 ticks is
        // effectively "never sample" — we cap at a sentinel that the PID
        // controller can still drive down.
        if (ticks > (u64)LONG_MAX) ticks = (u64)LONG_MAX;
        init_interval = (long)ticks;
    } else {
        init_interval = (long)(TSC::frequency() / 1000);
    }
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
    // Reset fd-type cache in O(1): incrementing _fd_cache_gen invalidates all
    // entries without touching the 65536-entry array (generation mismatch in
    // isSocket() causes a fresh getsockopt probe on next access).
    // Release pairs with the acquire in isSocket() so cache cells written after
    // the bump are observed alongside the new generation on weakly-ordered archs.
    _fd_cache_gen.fetch_add(1, std::memory_order_release);
#ifdef DEBUG
    _send_hook_calls.store(0, std::memory_order_relaxed);
    _recv_hook_calls.store(0, std::memory_order_relaxed);
    _write_hook_calls.store(0, std::memory_order_relaxed);
    _read_hook_calls.store(0, std::memory_order_relaxed);
    _record_accept_calls.store(0, std::memory_order_relaxed);
    _record_reject_calls.store(0, std::memory_order_relaxed);
    TEST_LOG("NativeSocketSampler::start interval_ticks=%ld tsc_freq=%llu",
             init_interval, (unsigned long long)TSC::frequency());
#endif
    if (!LibraryPatcher::patch_socket_functions()) {
        return Error("failed to install native socket hooks (dlsym returned NULL)");
    }
    return Error::OK;
}

void NativeSocketSampler::stop() {
#ifdef DEBUG
    TEST_LOG("NativeSocketSampler::stop summary send=%llu recv=%llu write=%llu read=%llu accept=%llu reject=%llu",
             (unsigned long long)_send_hook_calls.load(std::memory_order_relaxed),
             (unsigned long long)_recv_hook_calls.load(std::memory_order_relaxed),
             (unsigned long long)_write_hook_calls.load(std::memory_order_relaxed),
             (unsigned long long)_read_hook_calls.load(std::memory_order_relaxed),
             (unsigned long long)_record_accept_calls.load(std::memory_order_relaxed),
             (unsigned long long)_record_reject_calls.load(std::memory_order_relaxed));
#endif
    LibraryPatcher::unpatch_socket_functions();
    clearFdCache();
}

void NativeSocketSampler::clearFdCache() {
    std::lock_guard<std::mutex> lock(_fd_cache_mutex);
    _fd_cache.clear();
    _fd_cache_full.store(false, std::memory_order_release);
}

#else // !__linux__

NativeSocketSampler* const NativeSocketSampler::_instance = new NativeSocketSampler();

#endif // __linux__
