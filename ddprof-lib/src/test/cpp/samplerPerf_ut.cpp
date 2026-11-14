/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <cstring>
#include <vector>

#include "counters.h"
#include "samplerPerf.h"
#include "tsc.h"

// ---------------------------------------------------------------------------
// Mode-independent: ticksToNanos() and the sampler name table are compiled in
// both ways, since the report helper is declared unconditionally.
// ---------------------------------------------------------------------------

TEST(SamplerPerfTest, TicksToNanosDoesNotOverflow) {
  const u64 freq = TSC::frequency();
  ASSERT_GT(freq, 0ULL);

  // One hour of ticks. The naive ticks * 1e9 / freq overflows u64 here (at
  // 3 GHz it silently reports ~2.88s instead of 3600s), so this is the case
  // that justifies the split form.
  const u64 one_hour_ticks = freq * 3600ULL;
  EXPECT_EQ(3600ULL * 1000000000ULL, SamplerPerf::ticksToNanos(one_hour_ticks));

  // Exactness at smaller magnitudes, including the sub-second remainder path.
  EXPECT_EQ(0ULL, SamplerPerf::ticksToNanos(0));
  EXPECT_EQ(1000000000ULL, SamplerPerf::ticksToNanos(freq));
  EXPECT_EQ(500000000ULL, SamplerPerf::ticksToNanos(freq / 2));
}

TEST(SamplerPerfTest, EverySamplerHasAName) {
  for (int i = 0; i < SP_NUM_SAMPLERS; i++) {
    const char *n = SamplerPerf::name((SamplerId)i);
    ASSERT_NE(nullptr, n);
    EXPECT_STRNE("unknown", n);
    EXPECT_GT(strlen(n), 0u);
  }
  EXPECT_STREQ("cpu", SamplerPerf::name(SP_CPU));
  EXPECT_STREQ("wallclock", SamplerPerf::name(SP_WALL));
  // Out-of-range ids must not read past the table.
  EXPECT_STREQ("unknown", SamplerPerf::name((SamplerId)SP_NUM_SAMPLERS));
  EXPECT_STREQ("unknown", SamplerPerf::name((SamplerId)-1));
}

TEST(SamplerPerfTest, ReportIsSafeWithNoSamples) {
  // Must not crash or print a table when nothing ran. Also the only coverage
  // report() gets in the default build, where it is a no-op.
  SamplerPerf::report();
}

// ---------------------------------------------------------------------------
// (a) Disabled build: the probe must be inert and cost nothing. Compiled only
// when the flag is absent (the default gtest / CI build). This is the guard
// that protects production from any behavioural change.
// ---------------------------------------------------------------------------
#ifndef __SAMPLER_PERF__

TEST(SamplerPerfTest, DisabledProbeIsInert) {
  // The macro must still be a well-formed expression statement, including as
  // the sole body of an unbraced if/else -- that is why it expands to
  // ((void)0) rather than to nothing.
  if (true)
    SAMPLER_PERF_PROBE(SP_CPU);
  else
    SAMPLER_PERF_PROBE(SP_WALL);

  for (int i = 0; i < 4; i++) {
    SAMPLER_PERF_PROBE(SP_ALLOC);
  }
  // Nothing to assert on beyond compiling and not crashing: the counter slots
  // do not exist in this build, which DisabledCountersAreAbsentFromTable below
  // verifies from the other direction.
}

TEST(SamplerPerfTest, DisabledCountersAreAbsentFromTable) {
  // The whole point of appending the sub-table conditionally is that a default
  // build carries no sampler_* slot at all -- no enum entry, no storage, and
  // nothing surfacing through getDebugCounters()/JFR.
  std::vector<const char *> names = Counters::describeCounters();
  for (const char *n : names) {
    EXPECT_NE(0, strncmp(n, "sampler_ticks.", 14))
        << "unexpected counter in default build: " << n;
    EXPECT_NE(0, strncmp(n, "sampler_count.", 14))
        << "unexpected counter in default build: " << n;
  }
}

#else // __SAMPLER_PERF__ enabled (built under -PenableSamplerPerf)

class SamplerPerfEnabledTest : public ::testing::Test {
protected:
  void SetUp() override { Counters::reset(); }
  void TearDown() override { Counters::reset(); }

  static long long ticksOf(SamplerId id) {
    return Counters::getCounter(SAMPLER_TICKS_CPU, 2 * (int)id);
  }
  static long long countOf(SamplerId id) {
    return Counters::getCounter(SAMPLER_TICKS_CPU, 2 * (int)id + 1);
  }
};

TEST_F(SamplerPerfEnabledTest, CountersAppearInTable) {
  std::vector<const char *> names = Counters::describeCounters();
  bool found_cpu_ticks = false;
  bool found_cpu_count = false;
  for (const char *n : names) {
    if (strcmp(n, "sampler_ticks.cpu") == 0) found_cpu_ticks = true;
    if (strcmp(n, "sampler_count.cpu") == 0) found_cpu_count = true;
  }
  EXPECT_TRUE(found_cpu_ticks);
  EXPECT_TRUE(found_cpu_count);
}

// The probe addresses its slots as SAMPLER_TICKS_CPU + 2*id (+1), which only
// works while DD_COUNTER_TABLE_SAMPLER_PERF stays in DD_SAMPLER_LIST order.
// samplerPerf.h static_asserts that at compile time; this checks the same
// relationship at runtime, so a reader can see what the asserts are protecting.
TEST_F(SamplerPerfEnabledTest, OffsetAddressingMatchesNamedEnums) {
  Counters::increment(SAMPLER_TICKS_WALL, 4242);
  Counters::increment(SAMPLER_COUNT_NATIVESOCKET, 7);

  EXPECT_EQ(4242, ticksOf(SP_WALL));
  EXPECT_EQ(7, countOf(SP_NATIVESOCKET));
  // Neighbouring slots must be untouched -- catches an off-by-one in the
  // 2*id stride that a single-slot check would miss.
  EXPECT_EQ(0, countOf(SP_WALL));
  EXPECT_EQ(0, ticksOf(SP_NATIVESOCKET));
  EXPECT_EQ(0, ticksOf(SP_CPU));
  EXPECT_EQ(0, countOf(SP_CPU));
}

TEST_F(SamplerPerfEnabledTest, ProbeAccumulatesTicksAndCounts) {
  const u64 before = TSC::ticks();
  {
    SAMPLER_PERF_PROBE(SP_CPU);
    // Busy-spin rather than sleep: TSC::ticks() is monotonic either way, but a
    // spin keeps the test independent of nanosleep granularity.
    while (TSC::ticks() - before < TSC::frequency() / 1000) {
      // ~1ms
    }
  }
  const u64 elapsed = TSC::ticks() - before;

  EXPECT_EQ(1, countOf(SP_CPU));
  EXPECT_GT(ticksOf(SP_CPU), 0);
  // The probe's window is a subset of [before, now], so it cannot exceed it.
  EXPECT_LE((u64)ticksOf(SP_CPU), elapsed);
  // Other samplers must be untouched.
  EXPECT_EQ(0, countOf(SP_WALL));
  EXPECT_EQ(0, ticksOf(SP_WALL));
}

TEST_F(SamplerPerfEnabledTest, ProbeCountsEachScopeOnce) {
  for (int i = 0; i < 5; i++) {
    SAMPLER_PERF_PROBE(SP_ALLOC);
  }
  EXPECT_EQ(5, countOf(SP_ALLOC));
}

// The probe is declared at handler entry precisely so that the many early
// returns in the real handlers (CriticalSection reject, disabled engine,
// init-window tick) still record the work they did.
TEST_F(SamplerPerfEnabledTest, ProbeRecordsOnEarlyReturn) {
  auto bail_out = [](bool early) {
    SAMPLER_PERF_PROBE(SP_NATIVEMEM);
    if (early) {
      return;
    }
  };
  bail_out(true);
  bail_out(true);
  bail_out(false);
  EXPECT_EQ(3, countOf(SP_NATIVEMEM));
}

TEST_F(SamplerPerfEnabledTest, NestedProbesOfDifferentSamplersBothRecord) {
  // Mirrors a wallclock signal landing inside a CPU handler: both totals get
  // the inner interval, which is the documented double-count in samplerPerf.h.
  {
    SAMPLER_PERF_PROBE(SP_CPU);
    {
      SAMPLER_PERF_PROBE(SP_WALL);
    }
  }
  EXPECT_EQ(1, countOf(SP_CPU));
  EXPECT_EQ(1, countOf(SP_WALL));
}

TEST_F(SamplerPerfEnabledTest, ReportSkipsSamplersThatNeverRan) {
  // Only assert it is callable with a partially populated table; the format
  // itself goes to stderr and is not machine-read.
  Counters::increment(SAMPLER_TICKS_ALLOC, 5000000);
  Counters::increment(SAMPLER_COUNT_ALLOC, 2);
  EXPECT_EQ(0, countOf(SP_WALL));
  SamplerPerf::report();
}

#endif // __SAMPLER_PERF__
