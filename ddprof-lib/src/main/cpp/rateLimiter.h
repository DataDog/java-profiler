/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _RATELIMITER_H
#define _RATELIMITER_H

#include "arch.h"
#include "os.h"
#include "pidController.h"
#include <atomic>

/**
 * Thread-safe rate limiter based on a PID controller.
 *
 * Maintains a shared target event rate by adjusting a sampling interval
 * (in arbitrary units — TSC ticks, bytes, counts, …) via a PID feedback
 * loop driven by the aggregate observed fire count across all threads.
 *
 * ## Typical use
 *
 * One RateLimiter instance is shared across threads.  Per-thread sampling
 * decisions are made by a companion sampler (e.g. PoissonSampler) that
 * reads interval() and epoch() from this object.  After each sampled event
 * the thread calls recordFire() to feed back into the rate controller.
 *
 * ## Epoch-based lazy reset
 *
 * start() bumps an epoch counter.  Per-thread samplers compare their cached
 * epoch against epoch() on every sample call; a mismatch triggers a lazy
 * reinitialisation, so no explicit iteration over threads is needed at start.
 */
class RateLimiter {
public:
    RateLimiter() = default;

    /**
     * Initialise for a new profiling session.
     *
     * @param init_interval_units  Initial sampling interval in the chosen unit
     *                             (e.g. TSC ticks for ~1 ms).  Must be >= 1.
     * @param target_per_second    Target aggregate fire rate (events / second).
     * @param pid_window_secs      PID observation window in seconds.
     * @param p_gain               PID proportional gain.
     * @param i_gain               PID integral gain.
     * @param d_gain               PID derivative gain.
     * @param cutoff_secs          PID derivative low-pass cutoff in seconds.
     */
    void start(long init_interval_units,
               u64  target_per_second,
               int  pid_window_secs,
               double p_gain, double i_gain, double d_gain,
               double cutoff_secs) {
        _interval.store(init_interval_units, std::memory_order_release);
        _event_count.store(0, std::memory_order_relaxed);
        _last_update_ns.store(OS::nanotime(), std::memory_order_release);
        _epoch.fetch_add(1, std::memory_order_release);
        _pid = PidController(target_per_second, p_gain, i_gain, d_gain,
                             pid_window_secs, cutoff_secs);
    }

    /** Current sampling interval in the chosen unit. */
    long interval() const {
        return _interval.load(std::memory_order_relaxed);
    }

    /** Current epoch; bumped on every start(). */
    u64 epoch() const {
        return _epoch.load(std::memory_order_relaxed);
    }

    /**
     * Record one sampled event and update the PID controller at most once
     * per second.  Safe to call from any thread concurrently.
     */
    void recordFire() {
        _event_count.fetch_add(1, std::memory_order_relaxed);
        maybeUpdateInterval();
    }

private:
    static const u64 ONE_SECOND_NS = 1000000000ULL;

    std::atomic<long> _interval{1};
    std::atomic<u64>  _epoch{0};
    std::atomic<long> _event_count{0};
    std::atomic<u64>  _last_update_ns{0};
    PidController     _pid{1, 1.0, 1.0, 1.0, 1, 1.0};

    void maybeUpdateInterval() {
        u64 now  = OS::nanotime();
        u64 prev = _last_update_ns.load(std::memory_order_relaxed);
        if (now - prev < ONE_SECOND_NS) {
            return;
        }
        if (!_last_update_ns.compare_exchange_strong(prev, now,
                                                     std::memory_order_acq_rel,
                                                     std::memory_order_relaxed)) {
            return;
        }
        // One-event-per-window imprecision: a concurrent recordFire() after this exchange
        // loses its count for this window. Accepted: the PID controller tolerates this level
        // of measurement noise without instability.
        long count = _event_count.exchange(0, std::memory_order_relaxed);
        double signal = _pid.compute(static_cast<u64>(count), 1.0);
        long new_interval = _interval.load(std::memory_order_relaxed)
                            - static_cast<long>(signal);
        if (new_interval < 1) {
            new_interval = 1;
        }
        // Relaxed store: eventual consistency is acceptable. Threads reading _interval
        // with relaxed loads will see the update within at most one additional window.
        // Forcing release ordering here would add unnecessary cost on weak-ordering architectures.
        _interval.store(new_interval, std::memory_order_relaxed);
    }
};

#endif // _RATELIMITER_H
