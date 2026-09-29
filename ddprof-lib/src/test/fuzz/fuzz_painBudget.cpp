/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for PainBudget (painBudget.h) - the leaky-bucket
 * cost budget pacing ReferenceChainTracker's BFS passes and full-heap walks.
 *
 * PainBudget is a pure header-only class driven entirely by caller-supplied
 * timestamps, so the fuzzer supplies the clock - including hostile clocks:
 * steps backward, steps of ~2^64 ns, zero refill rates, rate changes stacked
 * on undrained debt. Every production caller feeds it OS::nanotime() deltas
 * that are usually well-behaved, but the drain() arithmetic is documented to
 * survive arbitrary monotone-adjacent clocks (the backward-clock clamp
 * comment), and a wrap in the unsigned elapsed subtraction would silently
 * drain the whole debt and un-block a full-heap BFS back-to-back.
 *
 * Invariants asserted on every op sequence:
 *   I1. balanceMs() is never negative - drain() clamps at 0.
 *   I2. canStartNow(now) is false immediately after spend() at the same now:
 *       zero wall-clock elapsed can never clear a positive debt (for any
 *       refill rate, including 0 and >1).
 *   I3. With refill_rate > 0, the debt is affordable once wall-clock time
 *       balance/rate has passed: canStartNow(now + ceil(balance/rate) + 1)
 *       must be true. (No-wrap case only - a wrapped clock hits the
 *       backward-clamp path instead, which I4 covers.)
 *   I4. A backward clock step never changes the balance: drain() must
 *       re-baseline to zero elapsed, never unsigned-wrap-drain the debt.
 *   I5. refill_rate == 0 blocks forever once in debt (the documented no-op
 *       refill): canStartNow stays false at any forward time.
 *
 * Clock domain: the clock is kept >= 1 ns, mirroring production - drain()'s
 * "0 = never drained yet" sentinel comment makes OS::nanotime()-based clocks
 * the contract, and a real nanotime never reads 0. A clock that lands exactly
 * on 0 collides with the sentinel (a legitimate zero baseline reads as
 * "never drained", so no retroactive drain happens) - verified as a crafted
 * input during bring-up, NOT a production bug.
 */

#include <stddef.h>
#include <stdint.h>

#include "painBudget.h"

namespace {

constexpr u64 kNsPerMs = 1000000ULL;

// One-millisecond-granularity shadows of the checked invariants, kept at the
// same precision PainBudget's double arithmetic actually works in so the
// epsilon bounds below are honest.
u64 msToNs(u64 ms) { return ms * kNsPerMs; }

u64 readLe(const uint8_t *data, size_t size, size_t &pos) {
    u64 v = 0;
    for (int i = 0; i < 4; i++) {
        v |= (u64)(pos < size ? data[pos++] : 0) << (8 * i);
    }
    return v;
}

} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    size_t pos = 0;
    int ops = (int)(readLe(data, size, pos) % 64) + 1;

    // The fuzzer drives the clock directly; start it somewhere plausible
    // (nanotime bases are arbitrary) and let the op stream move it anywhere,
    // including backward and across the u64 wrap.
    u64 clock = 1000000000ULL + readLe(data, size, pos);

    // Construct WITH the initial rate: the default constructor is the
    // documented blocking no-op (refill 0.0), which would desync the object
    // from this shadow's refill_rate and falsify I3/I5 (found by this
    // target's own first run - the shadow said 0.01 while the object
    // never drained).
    double refill_rate = 0.01; // the production default for the BFS budget
    PainBudget budget(refill_rate);
    bool in_debt_at_rate_zero = false;

    for (int i = 0; i < ops; i++) {
        int kind = (int)(readLe(data, size, pos) % 5);
        u64 argA = readLe(data, size, pos);
        u64 argB = readLe(data, size, pos);

        switch (kind) {
        case 0: {
            // spend(H) at the current clock, then I2 at zero elapsed.
            // balanceMs(clock) first: it drains up to 'now', so the spend is
            // the last thing that happened at exactly 'now' - without this,
            // a clock that jumped forward after the previous drain could
            // legitimately clear part of the new debt through the stale
            // baseline, and I2 would false-positive.
            budget.balanceMs(clock);
            u64 pain_ms = argA % 10000;
            budget.spend(pain_ms);
            if (pain_ms > 0 && budget.canStartNow(clock)) {
                __builtin_trap(); // I2
            }
            in_debt_at_rate_zero |= pain_ms > 0 && refill_rate == 0.0;
            break;
        }
        case 1: {
            // Forward time, then I3: the debt must clear within
            // balance/rate (+1ms slack for double rounding) - no-wrap only.
            double before = budget.balanceMs(clock);
            u64 jump_ms = argA % (48ULL * 3600 * 1000); // < 48h, no wrap
            u64 target = clock + msToNs(jump_ms);
            if (refill_rate > 0.0 && before > 0.0 && target >= clock) {
                u64 afford_ms = (u64)(before / refill_rate) + 1;
                if (!budget.canStartNow(clock + msToNs(afford_ms))) {
                    __builtin_trap(); // I3
                }
            }
            clock = target;
            break;
        }
        case 2: {
            // Rate change: drains at the old rate first (documented). Rate in
            // [0, 1.5]; 0 exercises the blocking no-op refill.
            double new_rate = (double)(argA % 16) / 10.0; // 0.0 .. 1.5
            budget.setRefillRate(new_rate, clock);
            refill_rate = new_rate;
            in_debt_at_rate_zero |= budget.balanceMs(clock) > 0 && new_rate == 0.0;
            break;
        }
        case 3: {
            // Backward clock step: I4 - the balance must be untouched. The
            // documented failure direction of a wrap in the unsigned elapsed
            // subtraction is a FULL drain (balance collapses to 0), so this
            // must hold as equality, not merely "did not grow".
            double bal_before = budget.balanceMs(clock);
            u64 back_ms = argB % (48ULL * 3600 * 1000);
            u64 back_ns = msToNs(back_ms);
            // Keep the clock >= 1 ns - see the clock-domain note above
            // (a zero clock collides with drain()'s never-drained sentinel).
            clock = back_ns >= clock ? 1 : clock - back_ns;
            double bal_after = budget.balanceMs(clock);
            if (bal_before > 0.0 && bal_after < bal_before - 1e-6) {
                __builtin_trap(); // I4: backward step drained debt
            }
            if (bal_after < -1e-6) {
                __builtin_trap(); // I1: negative balance
            }
            in_debt_at_rate_zero |= bal_after > 0 && refill_rate == 0.0;
            break;
        }
        case 4: {
            // I5: rate 0 + debt blocks forever, any forward time.
            double bal = budget.balanceMs(clock);
            if (in_debt_at_rate_zero && refill_rate == 0.0 && bal > 0.0) {
                u64 jump = clock + msToNs(argA % (24ULL * 3600 * 1000));
                if (jump > clock && budget.canStartNow(jump)) {
                    __builtin_trap(); // I5
                }
            }
            break;
        }
        default:
            break;
        }

        // I1 at every step.
        if (budget.balanceMs(clock) < -1e-6) {
            __builtin_trap();
        }
    }
    return 0;
}
