/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
// Advisory estimator for the per-op cost of the NativeMem allocation
// accounting calls (recordAlloc/recordFreeBefore), replaying a recorded
// malloc/free trace; the exit status never reflects an estimate's size.

#include "estimatorSupport.h"
#include "nativeMem.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <string>
#include <utility>
#include <vector>

#ifndef ESTIMATOR_BUILD_FLAGS
#define ESTIMATOR_BUILD_FLAGS "unknown"
#endif

namespace {

// Recorded defaults the expected trace hash is bound to.
constexpr uint64_t kTraceSeed = 0x5EED5EED5EED5EEDULL;
constexpr uint64_t kPairSeed = 0xDA77DA77DA77DA77ULL;
constexpr uint64_t kBootstrapSeed = 0xB0075EEDB0075EEDULL;
constexpr size_t kOpCount = 2000000;
// Test/demo-only replay length for local pass-rate runs; the reported
// statistics are identical, only the per-pair averaging window shrinks.
constexpr size_t kDemoOpCount = 200000;

// Pair counts sized so each CI half-width stays small next to the injected
// margin; the calibration sample stays five times the reported I-A sample.
constexpr int kPairCount = 10;
constexpr int kAAPairCount = 40;
constexpr int kIAPairCount = 40;
constexpr int kSpinCalibrationPairsPerWindow = 5;
constexpr int kBootstrapResamples = 10000;

// Calibration setpoint for the injected spin; no exit condition gates on
// the size of an estimate.
constexpr double kInjectedTargetNanosPerOp = 128.0;

// Expected FNV-1a 64 hash of the default trace's op stream.
constexpr uint64_t kExpectedTraceHash = 0x9d32481bad903951ULL;
// Expected hash of the demo-length trace from the same seed.
constexpr uint64_t kDemoExpectedTraceHash = 0x02be578183e1d3a1ULL;

// Sizes span small and medium requests, all below the 128 KiB allocator
// mmap threshold, so every block is served from the arena fast path.
const size_t kSizes[] = {16,  32,  48,   64,   96,   112,  128,   192,   256,
                         384, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
const size_t kSizeCount = sizeof(kSizes) / sizeof(kSizes[0]);

// FNV-1a 64.
constexpr uint64_t kFnvOffset = 0xcbf29ce484222325ULL;
constexpr uint64_t kFnvPrime = 0x100000001b3ULL;

void hashByte(uint64_t &hash, uint8_t byte) {
    hash ^= byte;
    hash *= kFnvPrime;
}

struct TraceOp {
    bool alloc;
    size_t size;
};

// Builds the op stream from raw mt19937_64 output: the first raw word's
// low bit decides alloc vs free, the second picks the size. The even op
// count plus the forced free at live==remaining drains it to zero live.
void generateTrace(uint64_t seed, std::vector<TraceOp> &ops, uint64_t &hash, size_t opCount) {
    std::mt19937_64 rng(seed);
    ops.clear();
    ops.reserve(opCount);
    uint64_t h = kFnvOffset;
    size_t live = 0;
    for (size_t i = 0; i < opCount; i++) {
        uint64_t decision = rng();
        uint64_t pick = rng();
        size_t remaining = opCount - i;
        bool alloc = live == remaining ? false : (live == 0 ? true : (decision & 1) == 0);
        size_t size = kSizes[pick % kSizeCount];
        ops.push_back(TraceOp{alloc, size});
        live = alloc ? live + 1 : live - 1;
        hashByte(h, alloc ? 1 : 0);
        for (int s = 0; s < 8; s++) {
            hashByte(h, (uint8_t)(size >> (8 * s)));
        }
    }
    hash = h;
}

enum Mode { MODE_A, MODE_B, MODE_I };

// Set from calibration before any replay; zero only under --inject-zero.
int g_spinPerOp = 0;

// Escape sink for the spin chain: the volatile store keeps the chain from
// being moved past the timed region's clock read.
volatile uint64_t g_sink = 0;
constexpr uint64_t kSpinInit = 0x243F6A8885A308D3ULL;

// Dependent xorshift chain: register-bound, so its cost is independent of
// the allocator work it is interleaved with. The xor/shift interleaving
// breaks the ring structure of a pure multiply-add recurrence, which the
// optimizer can otherwise collapse into a closed form.
uint64_t spinChain(uint64_t x, int iterations) {
    for (int i = 0; i < iterations; i++) {
        x ^= x >> 12;
        x ^= x << 25;
        x ^= x >> 27;
    }
    return x;
}

// Probe pass at a fixed iteration count yields ns/iteration; the per-op
// iteration count is then chosen to land the injected cost near the target.
int calibrateSpinIterationsPerOp() {
    const int probe = 64;
    uint64_t sink = kSpinInit;
    uint64_t t0 = monotonicNanos();
    for (size_t i = 0; i < kOpCount; i++) {
        sink = spinChain(sink, probe);
    }
    g_sink = sink;
    double nsPerIter = (double)(monotonicNanos() - t0) / ((double)kOpCount * probe);
    int iters = (int)(kInjectedTargetNanosPerOp / nsPerIter);
    return iters < 1 ? 1 : iters;
}

double medianOf(std::vector<double> v) {
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    return n % 2 == 1 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]);
}

struct ReplayResult {
    double nsPerOp;
    long long countedOps;
    long long accountingCalls;
    bool balanced;
};

// Replays ops LIFO. Mode B calls the real production recordAlloc/
// recordFreeBefore on NM_MISC at these call sites; skipFirstAccountingCall
// drops one recordAlloc (test-only fault). Mode I adds the per-op spin.
ReplayResult replay(const std::vector<TraceOp> &ops, Mode mode, bool skipFirstAccountingCall) {
    std::vector<std::pair<void *, size_t>> live;
    long long counted = 0;
    bool skipped = false;
    bool failed = false;
    uint64_t sink = kSpinInit;
    uint64_t t0 = monotonicNanos();
    for (const TraceOp &op : ops) {
        if (op.alloc) {
            void *ptr = malloc(op.size);
            if (ptr == NULL) {
                fprintf(stderr, "error=allocation failed size=%zu\n", op.size);
                failed = true;
                break;
            }
            if (mode == MODE_B) {
                if (skipFirstAccountingCall && !skipped) {
                    skipped = true;
                } else {
                    NativeMem::recordAlloc(NM_MISC, ptr, op.size);
                }
            }
            live.push_back(std::make_pair(ptr, op.size));
        } else {
            std::pair<void *, size_t> block = live.back();
            live.pop_back();
            if (mode == MODE_B) {
                NativeMem::recordFreeBefore(NM_MISC, block.first, block.second);
            }
            free(block.first);
        }
        if (mode == MODE_I) {
            sink = spinChain(sink, g_spinPerOp);
        }
        counted++;
    }
    g_sink = sink;
    uint64_t elapsed = monotonicNanos() - t0;
    ReplayResult r;
    r.nsPerOp = failed ? 0.0 : (double)elapsed / (double)ops.size();
    r.countedOps = counted;
    // One increment per op in every mode keeps the counter cost identical
    // across modes; the recorded skip is the only call-site difference.
    r.accountingCalls = skipped ? counted - 1 : counted;
    r.balanced = !failed && live.empty();
    return r;
}

// Seeded percentile bootstrap over paired deltas; resample indices are raw
// mt19937_64 output mapped by % n, so the CI is reproducible.
void bootstrapMedianCi(const std::vector<double> &deltas, double &lo, double &hi) {
    std::mt19937_64 rng(kBootstrapSeed);
    const size_t n = deltas.size();
    std::vector<double> medians;
    medians.reserve(kBootstrapResamples);
    std::vector<double> resample;
    for (int b = 0; b < kBootstrapResamples; b++) {
        resample.clear();
        for (size_t i = 0; i < n; i++) {
            resample.push_back(deltas[(size_t)(rng() % n)]);
        }
        medians.push_back(medianOf(resample));
    }
    std::sort(medians.begin(), medians.end());
    lo = medians[(size_t)((kBootstrapResamples - 1) * 0.025)];
    hi = medians[(size_t)((kBootstrapResamples - 1) * 0.975)];
}

// Exact two-sided sign test: p = 2 * min(P(X <= w), P(X >= w)) with
// X ~ Bin(n, 1/2), capped at 1.
double signTestP(const std::vector<double> &deltas) {
    int n = 0;
    int w = 0;
    for (double d : deltas) {
        if (d > 0) {
            n++;
            w++;
        } else if (d < 0) {
            n++;
        }
    }
    if (n == 0) {
        return 1.0;
    }
    long double pmf = 1.0L; // C(n, k); normalized by 2^n below
    long double denom = 1.0L; // 2^n
    for (int i = 0; i < n; i++) {
        denom *= 2.0L;
    }
    long double pLow = 0.0L;
    long double pHigh = 0.0L;
    for (int k = 0; k <= n; k++) {
        if (k <= w) {
            pLow += pmf;
        }
        if (k >= w) {
            pHigh += pmf;
        }
        pmf = pmf * (n - k) / (k + 1);
    }
    long double p = 2.0L * std::min(pLow, pHigh) / denom;
    return (double)(p > 1.0L ? 1.0L : p);
}

// Runs one I-A pair in seed-drawn order and appends its delta; used for
// both the calibration pairs and the reported I-A sample.
bool runIAPair(const std::vector<TraceOp> &ops, std::mt19937_64 &orderRng,
               std::vector<double> &deltas) {
    ReplayResult ri;
    ReplayResult ra;
    bool iFirst = (orderRng() & 1) == 0;
    if (iFirst) {
        ri = replay(ops, MODE_I, false);
        ra = replay(ops, MODE_A, false);
    } else {
        ra = replay(ops, MODE_A, false);
        ri = replay(ops, MODE_I, false);
    }
    if (!ri.balanced || !ra.balanced) {
        fprintf(stderr, "error=unbalanced trace replay\n");
        return false;
    }
    deltas.push_back(ri.nsPerOp - ra.nsPerOp);
    return true;
}

void printUsage(FILE *out) {
    fprintf(out, "Usage: native_mem_cost_estimator [options]\n"
                 "Advisory measurement of the NativeMem accounting-call cost; the\n"
                 "exit status never depends on the size of an estimate.\n"
                 "Test-only fault injections:\n"
                 "  --force-bad-hash         compare the trace against a wrong "
                 "expected hash\n"
                 "  --skip-accounting-call   drop one B-mode accounting call\n"
                 "  --inject-zero            inject a zero-cost spin, forcing "
                 "the\n                           self-test to fail deterministically\n"
                 "  --demo                   test/demo only: replay 200000 ops "
                 "instead of 2000000\n"
                 "  --help                   print this usage\n");
}

} // namespace

int main(int argc, char **argv) {
    bool forceBadHash = false;
    bool skipAccountingCall = false;
    bool injectZero = false;
    bool demo = false;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--force-bad-hash") {
            forceBadHash = true;
        } else if (arg == "--skip-accounting-call") {
            skipAccountingCall = true;
        } else if (arg == "--inject-zero") {
            injectZero = true;
        } else if (arg == "--demo") {
            demo = true;
        } else if (arg == "--help") {
            printUsage(stdout);
            return 0;
        } else {
            fprintf(stderr, "error=unknown option %s\n", arg.c_str());
            printUsage(stderr);
            return 2;
        }
    }
    size_t opCount = demo ? kDemoOpCount : kOpCount;

    std::vector<TraceOp> ops;
    uint64_t hash = 0;
    generateTrace(kTraceSeed, ops, hash, opCount);
    uint64_t expected = demo ? kDemoExpectedTraceHash : kExpectedTraceHash;
    if (forceBadHash) {
        expected ^= 1;
    }
    if (hash != expected) {
        fprintf(stderr, "error=trace hash mismatch got=0x%016llx want=0x%016llx\n",
                (unsigned long long)hash, (unsigned long long)expected);
        return 1;
    }

    // The iteration count is picked before any replay, outside every timed
    // region; the delivered magnitude is measured by the calibration pairs
    // below.
    double injected = 0.0;
    if (injectZero) {
        g_spinPerOp = 0;
    } else {
        g_spinPerOp = calibrateSpinIterationsPerOp();
    }

    // Warm-up (never timed): allocator steady state, the header probe inside
    // the first recordAlloc, and the spin path.
    ReplayResult warm = replay(ops, MODE_A, false);
    if (!warm.balanced || warm.countedOps != (long long)opCount) {
        fprintf(stderr, "error=unbalanced trace replay\n");
        return 1;
    }
    NativeMem::reset();
    warm = replay(ops, MODE_B, skipAccountingCall);
    if (!warm.balanced || warm.accountingCalls != (long long)opCount ||
        NativeMem::live(NM_MISC) != 0 || NativeMem::max(NM_MISC) <= 0) {
        fprintf(stderr, "error=accounting mismatch calls=%lld live=%lld max=%lld\n",
                warm.accountingCalls, NativeMem::live(NM_MISC), NativeMem::max(NM_MISC));
        return 1;
    }
    long long accountingCalls = warm.accountingCalls;
    warm = replay(ops, MODE_I, false);
    if (!warm.balanced || warm.countedOps != (long long)opCount) {
        fprintf(stderr, "error=unbalanced trace replay\n");
        return 1;
    }

    std::mt19937_64 orderRng(kPairSeed);

    std::vector<double> deltaBA;
    std::vector<double> deltaAA;
    std::vector<double> deltaIA;
    std::vector<double> calibDelta;
    std::vector<std::string> windowMarkers;
    deltaBA.reserve(kPairCount);
    deltaAA.reserve(kAAPairCount);
    deltaIA.reserve(kIAPairCount);

    // Each pair is one measurement window: the marker record is read before
    // the pair's replays, never inside a timed region.
    for (int i = 0; i < kPairCount; i++) {
        windowMarkers.push_back(readMarkerRecord());
        ReplayResult rb;
        ReplayResult ra;
        bool bFirst = (orderRng() & 1) == 0;
        if (bFirst) {
            NativeMem::reset();
            rb = replay(ops, MODE_B, skipAccountingCall);
            ra = replay(ops, MODE_A, false);
        } else {
            ra = replay(ops, MODE_A, false);
            NativeMem::reset();
            rb = replay(ops, MODE_B, skipAccountingCall);
        }
        if (!rb.balanced || !ra.balanced || rb.accountingCalls != (long long)opCount ||
            NativeMem::live(NM_MISC) != 0 || NativeMem::max(NM_MISC) <= 0) {
            fprintf(stderr, "error=accounting mismatch calls=%lld live=%lld max=%lld\n",
                    rb.accountingCalls, NativeMem::live(NM_MISC), NativeMem::max(NM_MISC));
            return 1;
        }
        deltaBA.push_back(rb.nsPerOp - ra.nsPerOp);
    }

    for (int i = 0; i < kAAPairCount; i++) {
        windowMarkers.push_back(readMarkerRecord());
        ReplayResult r1 = replay(ops, MODE_A, false);
        ReplayResult r2 = replay(ops, MODE_A, false);
        if (!r1.balanced || !r2.balanced) {
            fprintf(stderr, "error=unbalanced trace replay\n");
            return 1;
        }
        // The seed flips the subtraction direction: under the null the two
        // replays are exchangeable, so the flip centers position drift at 0.
        deltaAA.push_back((orderRng() & 1) == 0 ? r2.nsPerOp - r1.nsPerOp
                                                : r1.nsPerOp - r2.nsPerOp);
    }

    for (int i = 0; i < kIAPairCount; i++) {
        windowMarkers.push_back(readMarkerRecord());
        // Calibration pairs interleave with the reported pairs so both samples
        // span the same drift; a zero injection has the exact magnitude 0.
        if (!injectZero) {
            for (int c = 0; c < kSpinCalibrationPairsPerWindow; c++) {
                if (!runIAPair(ops, orderRng, calibDelta)) {
                    return 1;
                }
            }
        }
        if (!runIAPair(ops, orderRng, deltaIA)) {
            return 1;
        }
    }
    // Paired replays, not a spin-only loop, measure the delivered cost:
    // interleaved with allocator work, a standalone spin partially overlaps
    // out-of-order execution.
    if (!injectZero) {
        injected = medianOf(calibDelta);
    }

    double medianBA = medianOf(deltaBA);
    double loBA = 0.0;
    double hiBA = 0.0;
    bootstrapMedianCi(deltaBA, loBA, hiBA);
    double p = signTestP(deltaBA);

    double medianAA = medianOf(deltaAA);
    double loAA = 0.0;
    double hiAA = 0.0;
    bootstrapMedianCi(deltaAA, loAA, hiAA);

    double medianIA = medianOf(deltaIA);
    double loIA = 0.0;
    double hiIA = 0.0;
    bootstrapMedianCi(deltaIA, loIA, hiIA);

    printf("trace_seed=0x%016llx\n", (unsigned long long)kTraceSeed);
    printf("pair_seed=0x%016llx\n", (unsigned long long)kPairSeed);
    printf("bootstrap_seed=0x%016llx\n", (unsigned long long)kBootstrapSeed);
    printf("ops=%zu\n", opCount);
    printf("trace_hash=0x%016llx\n", (unsigned long long)hash);
    printf("pair_count=%d\n", kPairCount);
    printf("aa_pair_count=%d\n", kAAPairCount);
    printf("ia_pair_count=%d\n", kIAPairCount);
    printf("bootstrap_resamples=%d\n", kBootstrapResamples);
    printf("spin_iterations_per_op=%d\n", g_spinPerOp);
    printf("injected_ns_per_op=%.6f\n", injected);
    printf("libc_name=%s\n", libcName().c_str());
    printf("libc_version=%s\n", libcVersion().c_str());
    printf("flags=%s\n", ESTIMATOR_BUILD_FLAGS);
    printf("accounting_calls=%lld\n", accountingCalls);
    printf("median_delta_ns_per_op=%.6f\n", medianBA);
    printf("delta_ci95_low_ns_per_op=%.6f\n", loBA);
    printf("delta_ci95_high_ns_per_op=%.6f\n", hiBA);
    printf("sign_test_p=%.6f\n", p);
    printf("aa_median_ns_per_op=%.6f\n", medianAA);
    printf("aa_ci95_low_ns_per_op=%.6f\n", loAA);
    printf("aa_ci95_high_ns_per_op=%.6f\n", hiAA);
    printf("ia_median_ns_per_op=%.6f\n", medianIA);
    printf("ia_ci95_low_ns_per_op=%.6f\n", loIA);
    printf("ia_ci95_high_ns_per_op=%.6f\n", hiIA);
    bool iaContainsMagnitude = loIA <= injected && injected <= hiIA;
    printf("ia_ci_contains_magnitude=%s\n", iaContainsMagnitude ? "yes" : "no");
    printf("marker_windows=%zu\n", windowMarkers.size());
    for (const std::string &m : windowMarkers) {
        printf("%s\n", m.c_str());
    }

    // The forced zero injection must report its dedicated reason before any
    // CI evaluation, so the structural ~5% CI flake cannot mask it.
    if (injectZero) {
        printf("self_test=fail\n");
        fprintf(stderr, "error=self-test forced failure: injected magnitude is zero\n");
        return 1;
    }
    // Only CI-vs-zero comparisons fail the self-test; containment of the
    // injected magnitude is a calibration report field, not an exit condition
    // (a 95% CI misses the true value ~5% of runs by construction).
    bool iaIncludesZero = loIA <= 0.0 && 0.0 <= hiIA;
    bool aaExcludesZero = !(loAA <= 0.0 && 0.0 <= hiAA);
    if (iaIncludesZero || aaExcludesZero) {
        printf("self_test=fail\n");
        fprintf(stderr,
                "error=self-test failed ia_ci=[%.6f,%.6f] aa_ci=[%.6f,%.6f]\n",
                loIA, hiIA, loAA, hiAA);
        return 1;
    }
    printf("self_test=pass\n");
    return 0;
}
