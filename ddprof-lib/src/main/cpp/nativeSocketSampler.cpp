/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeSocketSampler.h"

#if defined(__linux__)

#include "common.h"
#include "flightRecorder.h"
#include "libraryPatcher.h"
#include "log.h"
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
std::atomic<NativeSocketSampler::send_fn>  NativeSocketSampler::_orig_send{nullptr};
std::atomic<NativeSocketSampler::recv_fn>  NativeSocketSampler::_orig_recv{nullptr};
std::atomic<NativeSocketSampler::write_fn> NativeSocketSampler::_orig_write{nullptr};
std::atomic<NativeSocketSampler::read_fn>  NativeSocketSampler::_orig_read{nullptr};

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
        // A cached NON_SOCKET verdict is safe to trust: the worst case is that a
        // newly-socketed fd reuse under-samples until the next gen reset, which is
        // the documented accepted staleness tradeoff.
        if (type == FD_TYPE_NON_SOCKET) return false;
        // Cached SOCKET: trust the verdict on the hot path; revalidation is deferred
        // to recordEvent() on sampled write/read events (see revalidateSocket()).
        if (type == FD_TYPE_SOCKET) return true;
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

void NativeSocketSampler::insertFdAddrLocked(int fd, std::string addr) {
    auto it = _fd_cache.find(fd);
    if (it != _fd_cache.end()) {
        it->second->second = std::move(addr);
        _fd_lru_list.splice(_fd_lru_list.begin(), _fd_lru_list, it->second);
    } else {
        if ((int)_fd_cache.size() >= MAX_FD_CACHE) {
            _fd_cache.erase(_fd_lru_list.back().first);
            _fd_lru_list.pop_back();
        }
        _fd_lru_list.emplace_front(fd, std::move(addr));
        _fd_cache.emplace(fd, _fd_lru_list.begin());
    }
}

bool NativeSocketSampler::revalidateSocket(int fd) {
    int so_type;
    socklen_t solen = sizeof(so_type);
    int rc = getsockopt(fd, SOL_SOCKET, SO_TYPE, &so_type, &solen);
    if (rc == 0 && so_type == SOCK_STREAM) return true;
    // fd was reused for a non-socket or is already closed; update the type cache.
    if (fd >= 0 && (size_t)fd < (size_t)FD_TYPE_CACHE_SIZE) {
        uint8_t gen = _fd_cache_gen.load(std::memory_order_acquire);
        _fd_type_cache[fd].store(
            (uint8_t)(((gen & 0xF) << 4) | FD_TYPE_NON_SOCKET),
            std::memory_order_release);
    }
    return false;
}

bool NativeSocketSampler::shouldSample(u64 duration_ticks, int op, float &weight) {
    // op 0 (send) and op 2 (write) are outbound → share _send_sampler.
    // op 1 (recv) and op 3 (read) are inbound  → share _recv_sampler.
    PoissonSampler &sampler = (op == 0 || op == 2) ? _send_sampler : _recv_sampler;
    return sampler.sample(duration_ticks,
                          (u64)_rate_limiter.interval(),
                          _rate_limiter.epoch(),
                          weight);
}

void NativeSocketSampler::recordEvent(int fd, u64 t0, u64 t1, ssize_t bytes, u8 op) {
    if (!Profiler::instance()->isRunning()) return;
    // Clamp TSC inversion: a thread migrating cores between the two TSC reads can
    // observe t1 < t0.  Pass 0 to the sampler so the event is not force-sampled,
    // and record duration 0 in the JFR event (consistent with safeDuration in flightRecorder).
    u64 dur = t1 >= t0 ? t1 - t0 : 0;
    float weight = 0.0f;
    bool sampled = shouldSample(dur, op, weight);
    if (!sampled) {
#ifdef DEBUG
        uint64_t n = _record_reject_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::recordEvent REJECT #%llu fd=%d op=%u bytes=%zd dur_ticks=%llu",
                     (unsigned long long)(n + 1), fd, (unsigned)op, bytes,
                     (unsigned long long)dur);
        }
#endif
        return;
    }
    // write/read hooks (op 2/3) call isSocket() which trusts the cached SOCKET verdict
    // without re-probing, to avoid a getsockopt syscall on every I/O.  Revalidate here,
    // on sampled events only, so a closed-and-reused fd is caught before we emit an event.
    if ((op == 2 || op == 3) && !revalidateSocket(fd)) return;
#ifdef DEBUG
    {
        uint64_t n = _record_accept_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3F) == 0) {
            TEST_LOG("NativeSocketSampler::recordEvent ACCEPT #%llu fd=%d op=%u bytes=%zd dur_ticks=%llu weight=%f",
                     (unsigned long long)(n + 1), fd, (unsigned)op, bytes,
                     (unsigned long long)dur, (double)weight);
        }
    }
#endif

    NativeSocketEvent event;
    event._start_time = t0;
    event._end_time   = t1;
    event._operation  = op;
    event._remote_addr[0] = '\0';
    // Always re-probe the peer address on sampled events so that a closed-and-reused
    // fd (new TCP connection on the same fd number) gets a fresh address rather than
    // the previous peer's address from the LRU cache.  The cost (one getpeername per
    // sampled event) is bounded by the sampling rate and acceptable here.
    {
        std::string resolved = resolveAddr(fd);
        if (!resolved.empty()) {
            strncpy(event._remote_addr, resolved.c_str(), sizeof(event._remote_addr) - 1);
            event._remote_addr[sizeof(event._remote_addr) - 1] = '\0';
            std::lock_guard<std::mutex> lock(_fd_cache_mutex);
            insertFdAddrLocked(fd, std::move(resolved));
        } else {
            // resolveAddr returned empty (AF_UNIX, not yet connected, etc.); fall back
            // to the cached value if one exists.
            std::lock_guard<std::mutex> lock(_fd_cache_mutex);
            auto it = _fd_cache.find(fd);
            if (it != _fd_cache.end()) {
                _fd_lru_list.splice(_fd_lru_list.begin(), _fd_lru_list, it->second);
                strncpy(event._remote_addr, it->second->second.c_str(), sizeof(event._remote_addr) - 1);
                event._remote_addr[sizeof(event._remote_addr) - 1] = '\0';
            }
        }
    }
    // ret > 0 checked above; cast is safe.
    event._bytes  = (u64)bytes;
    event._weight = weight;

    Profiler::instance()->recordSample(NULL, (u64)bytes, OS::threadId(),
                                       BCI_NATIVE_SOCKET, 0, &event);

    _rate_limiter.recordFire();
}

ssize_t NativeSocketSampler::send_hook(int fd, const void* buf, size_t len, int flags) {
    // Defensive guard against direct invocation outside of PLT dispatch (e.g. tests
    // that obtain the static symbol address before LibraryPatcher::patch_socket_functions
    // has run).  Production hooks are unreachable until setOriginalFunctions() has been
    // called under _lock, so this branch is not exercised on the normal path.
    send_fn fn = _orig_send.load(std::memory_order_acquire);
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len, flags);
    NativeSocketSampler* self = _instance;
    if (!self->isSocket(fd)) return fn(fd, buf, len, flags);
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
    recv_fn fn = _orig_recv.load(std::memory_order_acquire);
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len, flags);
    NativeSocketSampler* self = _instance;
    if (!self->isSocket(fd)) return fn(fd, buf, len, flags);
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
    write_fn fn = _orig_write.load(std::memory_order_acquire);
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len);
    NativeSocketSampler* self = _instance;
    bool is_socket = self->isSocket(fd);
#ifdef DEBUG
    {
        uint64_t n = _write_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::write_hook #%llu fd=%d len=%zu is_socket=%d",
                     (unsigned long long)(n + 1), fd, len, (int)is_socket);
        }
    }
#endif
    if (!is_socket) return fn(fd, buf, len);
    u64 t0 = TSC::ticks();
    return record_if_positive(fd, fn(fd, buf, len), t0, TSC::ticks(), 2);
}

ssize_t NativeSocketSampler::read_hook(int fd, void* buf, size_t len) {
    read_fn fn = _orig_read.load(std::memory_order_acquire);
    if (fn == nullptr) { errno = ENOSYS; return -1; }
    if (!LibraryPatcher::_socket_active.load(std::memory_order_acquire)) return fn(fd, buf, len);
    NativeSocketSampler* self = _instance;
    bool is_socket = self->isSocket(fd);
#ifdef DEBUG
    {
        uint64_t n = _read_hook_calls.fetch_add(1, std::memory_order_relaxed);
        if (n < 3 || (n & 0x3FF) == 0) {
            TEST_LOG("NativeSocketSampler::read_hook #%llu fd=%d len=%zu is_socket=%d",
                     (unsigned long long)(n + 1), fd, len, (int)is_socket);
        }
    }
#endif
    if (!is_socket) return fn(fd, buf, len);
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
        // Guard secs * tsc_freq against u64 overflow before the LONG_MAX clamp.
        // At 3 GHz the product wraps at secs ≈ 6.1e9; clamp early to avoid UB.
        u64 ticks;
        if (tsc_freq > 0 && secs > (u64)LONG_MAX / tsc_freq) {
            ticks = (u64)LONG_MAX;
        } else {
            ticks = secs * tsc_freq + (sub_ns * tsc_freq) / 1000000000ULL;
            if (ticks > (u64)LONG_MAX) ticks = (u64)LONG_MAX;
        }
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
    // Clear the fd->addr cache and reset the fd-type cache generation for the new
    // session so stale entries from a prior run cannot produce misattributed events
    // even if stop() was not called.  clearFdCache() bumps _fd_cache_gen under the
    // mutex so the clear and the gen bump are atomic with respect to concurrent
    // isSocket() calls.  A single call per start() keeps the mod-16 generation-wrap
    // budget at the full 16 cycles documented in nativeSocketSampler.h.
    clearFdCache();
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
    _fd_lru_list.clear();
    // Bump the generation under the lock so the clear and the bump are atomic
    // with respect to concurrent isSocket() calls: no thread can insert an
    // entry tagged with the old generation after the map is cleared.
    _fd_cache_gen.fetch_add(1, std::memory_order_release);
}

#else // !__linux__

NativeSocketSampler* const NativeSocketSampler::_instance = new NativeSocketSampler();

#endif // __linux__
