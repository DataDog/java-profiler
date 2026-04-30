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
//                         high nibble matches _fd_cache_gen mod 16.  Stale entries
//                         after fd reuse cause at most one extra getsockopt() call.
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
        _orig_send = s; _orig_recv = r; _orig_write = w; _orig_read = rd;
    }

    // For testing only: retrieve the current original function pointers.
    static void getOriginalFunctions(send_fn& s, recv_fn& r, write_fn& w, read_fn& rd) {
        s = _orig_send; r = _orig_recv; w = _orig_write; rd = _orig_read;
    }

private:
    static NativeSocketSampler* const _instance;

    // Set once by setOriginalFunctions() (called under _lock, before PLT patching) and
    // never reset to null while hooks are active.  No atomic needed: the __ATOMIC_RELEASE
    // on each PLT patch provides a store-store barrier that keeps these assignments
    // visible before the PLT entry becomes observable; the _socket_active release/acquire
    // pair establishes happens-before for any hook that sees _socket_active=true.
    static send_fn  _orig_send;
    static recv_fn  _orig_recv;
    static write_fn _orig_write;
    static read_fn  _orig_read;

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

    // fd -> "ip:port" string cache.  Bounded to MAX_FD_CACHE entries; no
    // eviction is performed (entries for closed/reused fds are stale until
    // the next stop(), but stale addresses are a known, accepted limitation).
    static const int MAX_FD_CACHE = 65536;
    std::unordered_map<int, std::string> _fd_cache;
    std::mutex _fd_cache_mutex;

    // fd-type cache for write/read hooks.  Lock-free: one atomic byte per fd number.
    // Encoding: bits [7:4] = generation mod 16, bits [3:0] = type (0=unknown/invalid,
    // 1=TCP socket, 2=non-TCP).  An entry is valid only when its high nibble equals
    // _fd_cache_gen mod 16.  Incrementing _fd_cache_gen invalidates all entries in
    // O(1) without touching the 65536-entry array.
    // Fds outside [0, FD_TYPE_CACHE_SIZE) are probed on every call.
    static const int     FD_TYPE_CACHE_SIZE  = 65536;
    static const uint8_t FD_TYPE_UNKNOWN     = 0;
    static const uint8_t FD_TYPE_SOCKET      = 1;
    static const uint8_t FD_TYPE_NON_SOCKET  = 2;
    std::atomic<uint8_t> _fd_cache_gen{0};   // incremented on each cache reset
    std::atomic<uint8_t> _fd_type_cache[FD_TYPE_CACHE_SIZE];

    NativeSocketSampler() = default;

    // Resolve the peer address for fd; returns empty string on failure.
    std::string resolveAddr(int fd);

    // Returns true if fd is a SOCK_STREAM socket (including AF_UNIX).
    // Uses the fd-type cache; calls getsockopt on first encounter per fd.
    bool isSocket(int fd);

    // Decide whether to sample and compute weight.
    // Returns true if the call should be recorded; sets weight out-param.
    // Implements per-thread Poisson-process sampling: each thread maintains its
    // own Exp-distributed countdown; when it expires the event is sampled and a
    // new countdown is drawn.  weight = 1 / (1 - exp(-duration/interval)).
    // duration_ticks: wall time of the I/O call in TSC ticks.
    // op: 0 = send, 1 = recv.
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
