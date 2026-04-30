/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _POISSONSAMPLER_H
#define _POISSONSAMPLER_H

#include "arch.h"
#include <cmath>

/**
 * @file poissonSampler.h
 *
 * Thread-local, dimension-agnostic Poisson-process sampler.
 *
 * ## Concept
 *
 * Many profiler engines need to sub-sample a high-frequency stream of
 * measurements and produce an unbiased aggregate estimate from the surviving
 * samples.  The classic approach is a deterministic threshold counter (fire
 * every N units), but that creates phase-locking artifacts and handles
 * measurements that span multiple intervals poorly.
 *
 * PoissonSampler models the stream as a Poisson process: between consecutive
 * sample points the gap is drawn independently from Exp(mean = @p interval).
 * This guarantees memoryless inter-arrival times and correct behaviour for
 * measurements of any size relative to the interval.
 *
 * ## Sampling decision
 *
 * The sampler maintains a monotonically growing accumulator @c _used and a
 * Exp-distributed threshold @c _threshold.  On each call:
 *
 *   1. @p value is added to @c _used.
 *   2. If @c _used < @c _threshold: no sample, return false.
 *   3. Otherwise: the threshold has been crossed.  Advance @c _threshold by
 *      a fresh draw from Exp(@p interval) so the next gap is independent.
 *      Compute and return the weight (see below), return true.
 *
 * ## Weight formula and estimator invariant
 *
 * The probability that a Poisson process with rate 1/@p interval produces
 * at least one event during an interval of length @p value is:
 *
 *   P = 1 - exp(-value / interval)
 *
 * The inverse-transform weight is:
 *
 *   weight = 1 / P = 1 / (1 - exp(-value / interval))
 *
 * This satisfies the unbiasedness invariant for every measurement:
 *
 *   E[weight * value | sampled] * P(sampled) = (1/P) * value * P = value
 *
 * Therefore sum(weight_i * value_i) over all sampled events is an unbiased
 * estimator of the total accumulated dimension over the recording window,
 * regardless of the distribution of individual measurement sizes:
 *
 *   - value << interval  →  P ≈ value/interval,  weight ≈ interval/value,
 *                            weight * value ≈ interval  (one interval per event)
 *   - value >> interval  →  P ≈ 1,               weight ≈ 1,
 *                            weight * value ≈ value  (full measurement credited)
 *
 * ## Dimension agnosticism
 *
 * The class is generic over the accumulated dimension.  The caller chooses
 * what @p value represents; @p interval must be in the same units:
 *
 *   - TSC ticks     → latency / time-in-I/O profiling
 *   - Bytes         → throughput / allocation profiling
 *   - Event count   → frequency profiling (pass value = 1 per event)
 *
 * ## Thread safety and epoch-based reset
 *
 * Instances must be declared @c thread_local.  All state is private to the
 * owning thread; no locks or atomics are used in the hot path.
 *
 * To support profiler restart, the engine exposes a shared
 * @c std::atomic<u64> epoch counter that it increments on @c start().
 * Each PoissonSampler caches the last seen epoch; when it differs the
 * sampler reinitialises lazily on the next @c sample() call, re-seeding
 * the PRNG and resetting the accumulator and threshold.
 *
 * ## Usage
 *
 * @code
 *   // Engine header:
 *   std::atomic<u64> _epoch{0};   // bumped in start()
 *   std::atomic<long> _interval;  // PID-controlled mean gap
 *
 *   // Engine translation unit:
 *   static thread_local PoissonSampler _send_sampler;
 *   static thread_local PoissonSampler _recv_sampler;
 *
 *   // In the hook / measurement path:
 *   float weight;
 *   if (_send_sampler.sample(value, (u64)_interval.load(), _epoch.load(), weight)) {
 *       // record event; sum(weight * value) estimates total accumulated value
 *   }
 * @endcode
 */
class PoissonSampler {
public:
    /**
     * Decide whether to sample this measurement and compute its weight.
     *
     * @param value      The measurement for this call, in the chosen unit.
     *                   Must be in the same units as @p interval.
     *                   A value of 0 is never sampled.
     * @param interval   Mean inter-sample gap in the same units as @p value.
     *                   Controls the average number of events recorded per
     *                   unit of accumulated @p value.  Must be > 0.
     * @param epoch_now  Current profiler epoch from the owning engine's
     *                   shared atomic.  When it differs from the cached epoch
     *                   the sampler resets all state before evaluating the
     *                   current measurement.
     * @param weight     [out] Set on true return to 1/(1-exp(-value/interval)).
     *                   Multiply by @p value to get this event's contribution
     *                   to the total-accumulated-value estimate.
     * @return           true if this measurement should be recorded.
     */
    bool sample(u64 value, u64 interval, u64 epoch_now, float &weight) {
        if (value == 0 || interval == 0) {
            return false;
        }
        if (_epoch != epoch_now) {
            reset(interval, epoch_now);
        }
        _used += value;
        if (_used < _threshold) {
            return false;
        }
        // Threshold crossed: advance by a fresh Exp draw so the next
        // inter-arrival gap is independent of all previous ones.
        _threshold += nextExp(interval);
        // Float precision: when value >> interval, expf(-value/interval) rounds to 0.0f,
        // so weight = 1.0f / (1.0f - 0.0f) = 1.0f. This is a conservative lower bound —
        // large events count as weight >= 1.0. Intentional; avoids the cost of double arithmetic.
        float p = 1.0f - expf(-(float)value / (float)interval);
        weight = (p > 0.0f) ? 1.0f / p : 1.0f;
        return true;
    }

private:
    u64 _epoch{0};      // last seen profiler epoch; 0 = not yet initialised
    u64 _used{0};       // accumulated value since the last threshold crossing
    u64 _threshold{0};  // next Exp-distributed threshold to cross
    u64 _rng{0};        // xorshift64 PRNG state; must never be 0

    /**
     * Reinitialise all state for a new profiling session.
     *
     * The PRNG is seeded from the instance's own address XOR'd with a
     * multiple of the new epoch.  Because @c thread_local instances live at
     * fixed but thread-specific addresses, and because distinct samplers
     * within the same thread occupy different addresses, each (thread,
     * sampler, session) triple receives an independent random stream.
     */
    void reset(u64 interval, u64 epoch_now) {
        // Fibonacci hashing of epoch_now spreads low-entropy epoch values
        // across the full 64-bit range before XOR-ing with the address.
        _rng = (u64)(uintptr_t)this ^ (epoch_now * 0x9e3779b97f4a7c15ULL);
        if (_rng == 0) _rng = 1; // xorshift64 must not start at 0
        _used      = 0;
        _threshold = nextExp(interval);
        _epoch     = epoch_now;
    }

    /**
     * Draw one sample from Exp(mean = @p interval).
     *
     * Uses xorshift64 to produce a uniform pseudo-random value, then applies
     * the inverse CDF of the exponential distribution:
     *
     *   X = -interval * ln(U),   U ~ Uniform(0, 1]
     *
     * U > 0 because the +0.5f offset in `((float)_rng + 0.5f) * 5.42101086e-20f` ensures
     * the product is strictly positive even if _rng were 0. The xorshift64 invariant
     * (_rng != 0) is independently required by the recurrence (0 is a fixed point).
     * The magic constant 5.42101086e-20 ≈ 1/2^64 converts a u64 to [0, 1].
     *
     * ### Why xorshift64 instead of a C++ standard generator?
     *
     * The C++ <random> facility (std::mt19937, std::minstd_rand, …) is
     * unsuitable here for several reasons:
     *
     *   1. **Hot-path overhead.**  nextExp() is called only once per fired
     *      event (~83 times/second at the default rate), so raw throughput
     *      is not the primary concern.  The concern is code-size and
     *      instruction-cache pressure: std::mt19937 carries ~2.5 KB of
     *      state and its generate step touches all of it.  xorshift64 fits
     *      in a single 8-byte field already present in the struct.
     *
     *   2. **Seeding.**  std::random_device — the canonical seed source —
     *      may block, throw, or return low-entropy values on some Linux
     *      configurations (e.g., early boot, containers without /dev/urandom
     *      entropy).  Our seed (instance address XOR epoch hash) is always
     *      available, zero-cost, and produces independent streams per thread
     *      and per profiling session without any OS interaction.
     *
     *   3. **No allocation, no exceptions.**  std::random_device and the
     *      distribution wrappers (std::uniform_real_distribution, etc.) may
     *      allocate and may throw.  This code runs inside PLT hooks that
     *      intercept arbitrary application threads; allocation and exception
     *      handling in that context would be unsafe.
     *
     *   4. **Statistical sufficiency.**  xorshift64 (Marsaglia 2003) passes the
     *      Diehard battery; it fails some BigCrush tests for linear-algebra-based
     *      statistics (MatrixRank, LinearComp), but those failure modes are
     *      irrelevant to inverse-CDF Exp sampling for aggregate weight estimates.
     *      The inverse-CDF transform amplifies non-uniformity only near U ≈ 0
     *      (i.e., extremely large Exp draws), which correspond to very long
     *      inter-sample gaps — a rare tail that has negligible effect on aggregate
     *      estimates.
     */
    u64 nextExp(u64 interval) {
        _rng ^= _rng << 13;
        _rng ^= _rng >> 7;
        _rng ^= _rng << 17;
        float u = ((float)_rng + 0.5f) * 5.42101086e-20f;
        return (u64)(-(float)interval * logf(u));
    }
};

#endif // _POISSONSAMPLER_H
