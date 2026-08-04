/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NATIVESOCKETSAMPLER_H
#define _NATIVESOCKETSAMPLER_H

#include "arch.h"
#include "arguments.h"
#include "engine.h"
#include "event.h"

#if defined(__linux__)

#include "poissonSampler.h"
#include "rateLimiter.h"
#include <atomic>
#include <list>
#include <mutex>
#include <sys/socket.h>
#include <unordered_map>

class LibraryPatcher;

// Synchronisation strategy
// -------------------------
// Hook functions (send_hook / recv_hook / write_hook / read_hook) run on the
// calling Java thread, NOT in a signal handler.  Therefore malloc and locking
// are safe inside hooks.
//
// fd-to-addr cache      : guarded by _fd_cache_mutex (std::mutex).
//                         TOCTOU note: the cache is checked under lock, then
//                         released for resolveAddr(); a concurrent thread may
//                         emplace the same fd before re-acquisition. emplace()
//                         is idempotent in that case (first writer wins).
//                         Address staleness on fd reuse is accepted: worst case
//                         is one misattributed event per reuse.
// _fd_type_cache        : std::atomic<uint8_t> array, lock-free.  Entry encoding:
//                         bits [7:4] = generation mod 16, bits [3:0] = type
//                         (0=unknown, 1=TCP socket, 2=non-TCP).  Valid only when
//                         high nibble matches _fd_cache_gen mod 16.  A cached SOCKET
//                         verdict is trusted on the hot path; revalidation via
//                         getsockopt() is deferred to recordEvent() for sampled
//                         write/read events (revalidateSocket()).  A cached NON_SOCKET
//                         verdict is trusted (worst case: a reused fd under-samples
//                         until the next gen reset).
// _rate_limiter         : RateLimiter — owns std::atomic interval, epoch, and
//                         event count.  PID update races are resolved by CAS
//                         inside RateLimiter::maybeUpdateInterval().
// Sampling state        : thread_local PoissonSampler (in nativeSocketSampler.cpp).
//                         No cross-thread contention; each thread maintains its
//                         own independent Poisson process.  The per-second PID
//                         window observes the aggregate fire count via the shared
//                         atomic inside RateLimiter.
// Hook install/remove   : guarded by the profiler's main state lock (MutexLocker
//                         in Profiler::start / Profiler::stop).  No deadlock
//                         risk because hook bodies do NOT acquire the profiler
//                         signal lock.

class NativeSocketSampler : public Engine {
public:
    // Typedefs for libc send/recv/write/read signatures.
    typedef ssize_t (*send_fn)(int, const void*, size_t, int);
    typedef ssize_t (*recv_fn)(int, void*, size_t, int);
    typedef ssize_t (*write_fn)(int, const void*, size_t);
    typedef ssize_t (*read_fn)(int, void*, size_t);

    static NativeSocketSampler* instance() { return _instance; }

    Error check(Arguments &args) override;
    Error start(Arguments &args) override;
    void  stop()                 override;

    // Clears the fd-to-address cache and resets the fd-type cache.
    // Called from both start() (to reset state on restart) and stop().
    // Intentionally NOT called on JFR chunk boundaries.
    void clearFdCache();

    // PLT hooks installed by LibraryPatcher::patch_socket_functions().
    static ssize_t send_hook(int fd, const void* buf, size_t len, int flags);
    static ssize_t recv_hook(int fd,       void* buf, size_t len, int flags);
    static ssize_t write_hook(int fd, const void* buf, size_t len);
    static ssize_t read_hook(int fd,        void* buf, size_t len);

    // Called once by LibraryPatcher::patch_socket_functions() to install the
    // real libc function pointers before any PLT entries are patched.
    static void setOriginalFunctions(send_fn s, recv_fn r, write_fn w, read_fn rd) {
        _orig_send.store(s, std::memory_order_release);
        _orig_recv.store(r, std::memory_order_release);
        _orig_write.store(w, std::memory_order_release);
        _orig_read.store(rd, std::memory_order_release);
    }

    // For testing only: retrieve the current original function pointers.
    static void getOriginalFunctions(send_fn& s, recv_fn& r, write_fn& w, read_fn& rd) {
        s = _orig_send.load(std::memory_order_acquire);
        r = _orig_recv.load(std::memory_order_acquire);
        w = _orig_write.load(std::memory_order_acquire);
        rd = _orig_read.load(std::memory_order_acquire);
    }

private:
    static NativeSocketSampler* const _instance;

    // Set by setOriginalFunctions() (called under _lock, before PLT patching) and
    // read by the hooks on arbitrary application threads.  Declared std::atomic with
    // release/acquire pairing so a stop()→start() restart cycle, which rewrites these
    // pointers while a stale-epoch hook may still be in flight, has no data race and no
    // value tearing on any memory model.  The acquire load in each hook also pairs with
    // the release store here to publish the pointer before the hook observes it.
    static std::atomic<send_fn>  _orig_send;
    static std::atomic<recv_fn>  _orig_recv;
    static std::atomic<write_fn> _orig_write;
    static std::atomic<read_fn>  _orig_read;

    // Target aggregate event rate: ~83 events/s (~5000/min) across all four hooks
    // (send/write and recv/read) combined.
    static const int TARGET_EVENTS_PER_SECOND = 83;
    static const int PID_WINDOW_SECS          = 1;

    // PID controller gains.  Tuned for a 1-second observation window targeting
    // ~83 events/s.  P=31 is proportional gain; I=511 accumulates steady-state
    // error over the window; D=3 damps oscillation; cutoff=15s low-passes the
    // derivative to suppress high-frequency noise.
    static constexpr double PID_P_GAIN    = 31.0;
    static constexpr double PID_I_GAIN    = 511.0;
    static constexpr double PID_D_GAIN    = 3.0;
    static constexpr double PID_CUTOFF_S  = 15.0;

    // Default sampling interval in TSC ticks (equals 1 ms only on a ~1 GHz TSC;
    // serves as a numeric floor for pathologically low TSC frequencies).
    static const long DEFAULT_INTERVAL_TICKS  = 1000000; // fallback used in start() when the TSC-derived interval rounds to < 1

    // Rate limiter: owns the PID controller, interval, epoch, and fire counter.
    // NativeSocketSampler uses it directly (not via RateLimitedSampler) because
    // it has two sampling channels (send + recv) that share one rate target but
    // need independent per-thread PoissonSampler state.
    RateLimiter _rate_limiter;

    // fd → "ip:port" LRU cache.  Bounded to MAX_FD_CACHE entries; on overflow
    // the least-recently-used entry is evicted.  All access is under _fd_cache_mutex.
    // Address is always re-probed on sampled events (see recordEvent) so fd reuse
    // is detected within one sampling interval.
    using FdAddrList = std::list<std::pair<int, std::string>>;
    FdAddrList _fd_lru_list;
    std::unordered_map<int, FdAddrList::iterator> _fd_cache;
    std::mutex _fd_cache_mutex;

    // fd-type cache for write/read hooks.  Lock-free: one atomic byte per fd number.
    // Encoding: bits [7:4] = generation mod 16, bits [3:0] = type (0=unknown/invalid
    // — implicit zero in fresh array, never written explicitly; 1=TCP socket;
    // 2=non-TCP).  An entry is valid only when its high nibble equals _fd_cache_gen
    // mod 16.  Incrementing _fd_cache_gen invalidates all entries in O(1) without
    // touching the 65536-entry array.
    //
    // KNOWN LIMITATION (mod-16 generation wrap): _fd_cache_gen is only consulted via
    // its low 4 bits.  After 16 start() cycles the generation wraps and stale entries
    // from a previous incarnation become indistinguishable from current ones until each
    // fd is naturally re-probed.  Profiler restarts are not exercised in production
    // (only in tests), so the wrap is benign in practice.  If restart-in-prod ever
    // becomes a supported mode, widen _fd_cache_gen to uint32_t and store the full
    // generation in a wider per-fd cell.
    // Fds outside [0, FD_TYPE_CACHE_SIZE) are probed on every call.
    static const int     FD_TYPE_CACHE_SIZE  = 65536;
    // FD_TYPE_UNKNOWN is the implicit value-zero sentinel for never-written entries
    // and gen-mismatch entries; it is decoded by the (cached >> 4) != gen path in
    // isSocket(), not by an explicit comparison against this constant.
    static const uint8_t FD_TYPE_UNKNOWN     = 0;
    static const uint8_t FD_TYPE_SOCKET      = 1;
    static const uint8_t FD_TYPE_NON_SOCKET  = 2;
    std::atomic<uint8_t> _fd_cache_gen{0};   // incremented on each cache reset
    std::atomic<uint8_t> _fd_type_cache[FD_TYPE_CACHE_SIZE];

    NativeSocketSampler() = default;

    // Resolve the peer address for fd; returns empty string on failure.
    std::string resolveAddr(int fd);

    // Revalidates that fd is still a SOCK_STREAM socket; updates the type cache on
    // mismatch.  Called from recordEvent() for write/read ops on sampled events only.
    bool revalidateSocket(int fd);

    // Inserts or updates fd→addr in the LRU cache, evicting the LRU entry if full.
    // Must be called with _fd_cache_mutex held.
    void insertFdAddrLocked(int fd, std::string addr);

public:
    // Test seams — not part of the production API.
    static const int MAX_FD_CACHE = 65536;

    int  fdAddrCacheSizeForTest() {
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        return (int)_fd_cache.size();
    }
    void fdAddrCacheInsertForTest(int fd, const std::string& addr) {
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        insertFdAddrLocked(fd, addr);
    }

private:

    // Returns true if fd is a SOCK_STREAM socket (including AF_UNIX).
    // Uses the fd-type cache; calls getsockopt on first encounter per fd and on
    // every cached-SOCKET hit to revalidate against fd reuse (a closed socket fd
    // reassigned to a regular file/pipe must not keep emitting socket events).
    bool isSocket(int fd);

    // Decide whether to sample and compute weight.
    // Returns true if the call should be recorded; sets weight out-param.
    // Implements per-thread Poisson-process sampling: each thread maintains its
    // own Exp-distributed countdown; when it expires the event is sampled and a
    // new countdown is drawn.  weight = 1 / (1 - exp(-duration/interval)).
    // duration_ticks: wall time of the I/O call in TSC ticks.
    // op: 0 = send, 1 = recv, 2 = write, 3 = read.
    bool shouldSample(u64 duration_ticks, int op, float &weight);

    // Common recording logic shared by all four hooks.
    void recordEvent(int fd, u64 t0, u64 t1, ssize_t bytes, u8 op);

    // Records the event if ret > 0; returns ret unchanged.  Shared tail for all four hooks.
    static inline ssize_t record_if_positive(int fd, ssize_t ret, u64 t0, u64 t1, u8 op) {
        if (ret > 0) _instance->recordEvent(fd, t0, t1, ret, op);
        return ret;
    }
};

#else // !__linux__

class NativeSocketSampler : public Engine {
public:
    static NativeSocketSampler* instance() { return _instance; }
    Error check(Arguments &args) override { return Error::OK; }
    Error start(Arguments &args) override { return Error::OK; }
    void  stop()                 override {}
    void clearFdCache()          {}
private:
    static NativeSocketSampler* const _instance;
    NativeSocketSampler() {}
};

#endif // __linux__

#endif // _NATIVESOCKETSAMPLER_H
