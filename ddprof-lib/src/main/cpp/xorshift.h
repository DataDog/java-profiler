/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _XORSHIFT_H
#define _XORSHIFT_H

#include "arch.h"
#include "common.h"
#include <cmath>
#include <cstdint>

/**
 * xorshift64 (Marsaglia 2003) and the draws built on it: the profiler's
 * uniform random source.
 *
 * ## Why not the C++ <random> facility
 *
 * std::mt19937 and its companions are unsuitable for sampling code here:
 *
 *   1. **No allocation, no exceptions.**  std::random_device and the
 *      distribution wrappers (std::uniform_real_distribution, etc.) may
 *      allocate and may throw.  Callers include PLT hooks and allocation
 *      callbacks that run on arbitrary application threads, where neither is
 *      safe.
 *
 *   2. **Seeding.**  std::random_device may block, throw, or return
 *      low-entropy values depending on the host (early boot, containers
 *      without /dev/urandom entropy).  Its behaviour also depends on the
 *      libstdc++ the library was compiled against rather than on anything in
 *      this source.  seed() below is always available, costs nothing, and
 *      needs no OS interaction.
 *
 *   3. **Size.**  std::mt19937 carries ~2.5 KB of state and its generate step
 *      touches all of it.  The state here is a single u64 field, which fits in
 *      structures that are already per-thread.
 *
 *   4. **Statistical sufficiency.**  xorshift64 passes the Diehard battery.
 *      It fails some BigCrush tests for linear-algebra-based statistics
 *      (MatrixRank, LinearComp), which do not bear on the sampling decisions
 *      and inverse-CDF draws made here.
 *
 * ## Seeding
 *
 * seed() mixes a caller-chosen identity (typically an object address, which
 * differs per thread for thread-local instances) with a caller-chosen sequence
 * number (an epoch, a thread id) so that each (thread, instance, session)
 * triple gets an independent stream. Streams are reproducible for a given
 * address and sequence, which is deliberate: it needs no entropy source, and
 * sampling decisions require independence rather than unpredictability.
 */
namespace xorshift {

// Fibonacci hashing constant. Spreads low-entropy inputs -- a small thread id,
// an epoch counter that starts at 0 -- across the full 64-bit range before they
// are mixed with the identity.
static constexpr u64 KNUTH = (u64)KNUTH_MULTIPLICATIVE_CONSTANT;

// 1/2^64, for mapping a u64 onto the unit interval.
static constexpr double UNIT_SCALE = 5.421010862427522e-20;

// The largest double below 1, i.e. 1 - 2^-53. (x + 0.5) / 2^64 for the largest
// u64 is 1 - 2^-65, which is not representable and rounds to exactly 1.0, so
// the top of the range needs an explicit stop.
static constexpr double UNIT_MAX = 0x1.fffffffffffffp-1;

// M_PI is not guaranteed by the standard headers, so carry the constant.
static constexpr double TWO_PI = 6.283185307179586476925286766559;

/**
 * Derive a stream seed from an identity and a sequence number.
 *
 * 0 is a fixed point of the recurrence, so the result is forced away from it;
 * that costs one value out of 2^64 and keeps next() from degenerating.
 */
inline u64 seed(u64 identity, u64 sequence) {
  u64 state = identity ^ (sequence * KNUTH);
  return state != 0 ? state : 1;
}

/**
 * One xorshift64 step, in place. Async-signal-safe: no allocation, no locks,
 * no libc calls. @p state must be non-zero, which seed() guarantees.
 */
inline u64 next(u64 &state) {
  state ^= state << 13;
  state ^= state >> 7;
  state ^= state << 17;
  return state;
}

/**
 * Map a draw onto a uniform double in (0, 1).
 *
 * The result is strictly inside (0, 1): the +0.5 offset keeps it above 0 even
 * for x == 0, and the clamp keeps it below 1 for the largest x. Both ends
 * matter because callers take log() of the draw, and some take log(1 - f(draw))
 * a step later; either bound would make one of those infinite.
 *
 * double rather than float because it maps the 2^64 inputs onto 2^53 distinct
 * outputs instead of 2^24, which matters where the result is fed through an
 * inverse CDF: float clusters the draws near the high end.
 */
inline double toUnitDouble(u64 x) {
  double u = ((double)x + 0.5) * UNIT_SCALE;
  return u < 1.0 ? u : UNIT_MAX;
}

/**
 * Express a probability as a threshold for `next(state) < threshold`, so a
 * sampling decision costs one integer compare and no floating point.
 *
 * p <= 0 yields 0, which never fires. p >= 1 yields UINT64_MAX, which fires for
 * every draw but the single largest -- callers wanting exactly "always" should
 * skip the draw instead.
 */
inline u64 threshold(double p) {
  if (p <= 0.0) {
    return 0;
  }
  // 2^64 is not representable as u64, and casting a double at or above it is
  // undefined, so saturate before the cast rather than after.
  const double scale = 18446744073709551616.0; // 2^64
  double scaled = p * scale;
  if (scaled >= (double)UINT64_MAX) {
    return UINT64_MAX;
  }
  return (u64)scaled;
}

/**
 * Map a draw onto a uniform index in [0, n).
 *
 * Multiply-shift on the high 32 bits rather than `x % n`: modulo over-selects
 * the low indices whenever n does not divide 2^64, and for the reservoir sizes
 * here that bias is concentrated in exactly the slots that would then be
 * overwritten most often. Returns 0 for n == 0, the only defensible answer for
 * an empty range.
 */
inline u32 boundedIndex(u64 x, u32 n) {
  if (n == 0) {
    return 0;
  }
  return (u32)(((x >> 32) * (u64)n) >> 32);
}

/**
 * Draw from a normal distribution with the given mean and standard deviation,
 * by the Box-Muller transform.
 *
 * Box-Muller produces two independent normals per pair of uniforms; this
 * returns one and discards the other, which is the right trade at the call
 * rates here (order 10 draws/second) and keeps the function stateless beyond
 * the generator itself.
 */
inline double nextNormal(u64 &state, double mean, double stddev) {
  double u1 = toUnitDouble(next(state));
  double u2 = toUnitDouble(next(state));
  double magnitude = stddev * sqrt(-2.0 * log(u1));
  return mean + magnitude * cos(TWO_PI * u2);
}

} // namespace xorshift

#endif // _XORSHIFT_H
