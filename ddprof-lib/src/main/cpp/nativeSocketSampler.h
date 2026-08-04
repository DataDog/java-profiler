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

#include "nativeFdClassifier.h"
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
// Hook functions (send_hook / recv_hook / write_hook / read_hook) are installed
// in the JDK's libnet and libnio DSOs. IBM's JCL networking bridge in libjava
// uses separate wrappers that bypass all profiler state in a post-fork child.
// Arbitrary JNI libraries remain excluded from code that locks or allocates.
//
// fd-to-addr cache      : guarded by _fd_cache_mutex (std::mutex).
//                         TOCTOU note: the cache is checked under lock, then
//                         released for resolveAddr(); a concurrent thread may
//                         emplace the same fd before re-acquisition. emplace()
//                         is idempotent in that case (first writer wins).
//                         Address staleness is possible only after fd reuse
//                         through unobserved lifecycle paths.
// _fd_classifier        : lock-free fd-type classifier shared as code with the
//                         native I/O interposer. A cached stream-socket verdict
//                         is trusted on the hot path; sampled write/read events
//                         revalidate before recording (revalidateSocket()).
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
    static void disableAfterPatchFailure();
    static bool active() { return _active.load(std::memory_order_acquire); }

    // Clears the fd-to-address cache and resets the fd-type cache.
    // Called from both start() (to reset state on restart) and stop().
    // Intentionally NOT called on JFR chunk boundaries.
    void clearFdCache();
    void clearFdCacheEntry(int fd);

    // PLT hooks installed by LibraryPatcher::patch_socket_functions().
    static ssize_t send_hook(int fd, const void* buf, size_t len, int flags);
    static ssize_t recv_hook(int fd,       void* buf, size_t len, int flags);
    static ssize_t write_hook(int fd, const void* buf, size_t len);
    static ssize_t read_hook(int fd,        void* buf, size_t len);
    static ssize_t recordHookResult(int fd, ssize_t ret, u64 t0, u64 t1, u8 op) {
        return recordResultForHook(fd, ret, t0, t1, op);
    }

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

#ifdef UNIT_TEST
    static bool setActiveForTest(bool active) {
        return _active.exchange(active, std::memory_order_acq_rel);
    }
    using HookObserver = void (*)(const char* phase, int fd, u8 op, ssize_t ret);
    static void setHookObserverForTest(HookObserver observer);
    // Compatibility wrappers for sampler tests; probe override/counting is owned
    // by NativeFdClassifier now that sampler delegates fd classification to it.
    static uint64_t socketProbeCountForTest();
    static void resetSocketProbeCountForTest();
    using ProbeOverride = int (*)(int fd, int *so_type, int *probe_errno);
    static void setProbeOverrideForTest(ProbeOverride probe);
#endif

private:
    static NativeSocketSampler* const _instance;

    // Production publishes these once before PLT patching. Atomic access pairs
    // that publication with hook reads and also keeps test overrides data-race-free.
    static std::atomic<send_fn>  _orig_send;
    static std::atomic<recv_fn>  _orig_recv;
    static std::atomic<write_fn> _orig_write;
    static std::atomic<read_fn>  _orig_read;
    static std::atomic<bool>     _active;

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

    NativeFdClassifier _fd_classifier;

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
    bool fdAddrCacheContainsForTest(int fd) {
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        return _fd_cache.find(fd) != _fd_cache.end();
    }
    void fdAddrCacheInsertForTest(int fd, const std::string& addr) {
        std::lock_guard<std::mutex> lock(_fd_cache_mutex);
        insertFdAddrLocked(fd, addr);
    }
    bool isSocketForTest(int fd) {
        return isSocket(fd);
    }
#ifdef UNIT_TEST
    bool revalidateSocketForTest(int fd) {
        return revalidateSocket(fd);
    }
#endif

private:

    // Returns true if fd is a SOCK_STREAM socket (including AF_UNIX).
    // Uses the fd classifier; calls getsockopt on first encounter per fd.
    // Cached SOCKET verdicts are revalidated only on sampled write/read events.
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

    static inline ssize_t recordResultForHook(int fd, ssize_t ret, u64 t0, u64 t1, u8 op) {
#ifdef UNIT_TEST
        observeHookPhaseForTest("record", fd, op, ret);
#endif
        return record_if_positive(fd, ret, t0, t1, op);
    }

#ifdef UNIT_TEST
    static void observeHookPhaseForTest(const char* phase, int fd, u8 op, ssize_t ret);
#endif
};

#else // !__linux__

class NativeSocketSampler : public Engine {
public:
    static NativeSocketSampler* instance() { return _instance; }
    Error check(Arguments &args) override { return Error::OK; }
    Error start(Arguments &args) override { return Error::OK; }
    void  stop()                 override {}
    static void disableAfterPatchFailure() {}
    void clearFdCache()          {}
    void clearFdCacheEntry(int fd) { (void)fd; }
private:
    static NativeSocketSampler* const _instance;
    NativeSocketSampler() {}
};

#endif // __linux__

#endif // _NATIVESOCKETSAMPLER_H
