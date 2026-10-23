/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <string>
#include "arguments.h"
#include "mallocTracer.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char ARGUMENTS_TEST_NAME[] = "ArgumentsTest";

class ArgumentsGlobalSetup {
public:
    ArgumentsGlobalSetup() {
        installGtestCrashHandler<ARGUMENTS_TEST_NAME>();
    }
    ~ArgumentsGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static ArgumentsGlobalSetup global_setup;

class ArgumentsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ArgumentsTest, NativeMemoryOutputDefaultsForThePlatformAndIsNotExplicit) {
    Arguments args;
    EXPECT_EQ(args._nativemem_output, DEFAULT_NATIVE_MEMORY_OUTPUT);
    EXPECT_FALSE(args._nativemem_output_set);

    ASSERT_FALSE(args.parse("nativemem=512"));
    EXPECT_EQ(args._nativemem_output, DEFAULT_NATIVE_MEMORY_OUTPUT);
    EXPECT_FALSE(args._nativemem_output_set);

    MallocTracer tracer;
    EXPECT_FALSE(tracer.check(args));
}

TEST_F(ArgumentsTest, NativeMemoryOutputParsesAllValuesCaseInsensitively) {
    Arguments jfr;
    ASSERT_FALSE(jfr.parse("nativemem=512,nativememoutput=JFR"));
    EXPECT_EQ(jfr._nativemem_output, NATIVE_MEMORY_JFR);
    EXPECT_TRUE(jfr._nativemem_output_set);

    Arguments usdt;
    ASSERT_FALSE(usdt.parse("nativememoutput=UsDt,nativemem=512"));
    EXPECT_EQ(usdt._nativemem_output, NATIVE_MEMORY_USDT);
    EXPECT_TRUE(usdt._nativemem_output_set);

    Arguments both;
    ASSERT_FALSE(both.parse("nativemem=512,nativememoutput=BoTh"));
    EXPECT_EQ(both._nativemem_output, NATIVE_MEMORY_BOTH);
    EXPECT_TRUE(both._nativemem_output_set);
}

TEST_F(ArgumentsTest, NativeMemoryOutputRejectsMissingEmptyAndUnknownValues) {
    Arguments missing;
    EXPECT_TRUE(missing.parse("nativememoutput"));

    Arguments empty;
    EXPECT_TRUE(empty.parse("nativememoutput="));

    Arguments unknown;
    EXPECT_TRUE(unknown.parse("nativememoutput=jfr-and-usdt"));
}

TEST_F(ArgumentsTest, NativeMemoryOutputRequiresNativeMemoryRegardlessOfOrder) {
    MallocTracer tracer;

    Arguments output_only;
    ASSERT_FALSE(output_only.parse("nativememoutput=jfr"));
    EXPECT_TRUE(tracer.check(output_only));

    Arguments output_first;
    ASSERT_FALSE(output_first.parse("nativememoutput=usdt,nativemem=512"));
#if defined(__linux__)
    EXPECT_FALSE(tracer.check(output_first));
    EXPECT_EQ(output_first._nativemem_output, NATIVE_MEMORY_USDT);
#else
    testing::internal::CaptureStderr();
    EXPECT_FALSE(tracer.check(output_first));
    std::string usdt_warning = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output_first._nativemem_output, NATIVE_MEMORY_NOOP);
    EXPECT_NE(std::string::npos, usdt_warning.find(
        "nativememoutput=usdt is supported only on Linux; "
        "native memory profiling will be disabled"));
#endif

    Arguments memory_first;
    ASSERT_FALSE(memory_first.parse("nativemem=512,nativememoutput=both"));
#if defined(__linux__)
    EXPECT_FALSE(tracer.check(memory_first));
    EXPECT_EQ(memory_first._nativemem_output, NATIVE_MEMORY_BOTH);
#else
    testing::internal::CaptureStderr();
    EXPECT_FALSE(tracer.check(memory_first));
    std::string both_warning = testing::internal::GetCapturedStderr();
    EXPECT_EQ(memory_first._nativemem_output, NATIVE_MEMORY_JFR);
    EXPECT_NE(std::string::npos, both_warning.find(
        "USDT output is supported only on Linux; continuing with JFR only"));
#endif
}

TEST_F(ArgumentsTest, ExplicitJfrRemainsSupportedOnEveryPlatform) {
    MallocTracer tracer;
    Arguments args;
    ASSERT_FALSE(args.parse("nativemem=512,nativememoutput=jfr"));
    EXPECT_FALSE(tracer.check(args));
}

// hops/budget/framecap are ceiling-clamped (MAX_REFERENCE_CHAINS_HOP_CAP/
// _BUDGET/_FRONTIER_CAP, arguments.h) as well as floored at 1 - an operator
// typo (an extra digit) must not flow straight into a loop bound or
// the frontier table's allocation unchecked.
TEST_F(ArgumentsTest, HopsBudgetFrameCapAreCeilingClamped) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=2000000000:budget=2000000000:framecap=2000000000");
    EXPECT_FALSE(error);
    EXPECT_EQ(args._reference_chains_hop_cap, MAX_REFERENCE_CHAINS_HOP_CAP);
    EXPECT_EQ(args._reference_chains_budget, MAX_REFERENCE_CHAINS_BUDGET);
    EXPECT_EQ(args._reference_chains_frontier_cap, MAX_REFERENCE_CHAINS_FRONTIER_CAP);
}

TEST_F(ArgumentsTest, HopsBudgetFrameCapStillFlooredAtOne) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=-5:budget=-5:framecap=-5");
    EXPECT_FALSE(error);
    EXPECT_EQ(args._reference_chains_hop_cap, 1);
    EXPECT_EQ(args._reference_chains_budget, 1);
    EXPECT_EQ(args._reference_chains_frontier_cap, 1);
}

// An unrecognized top-level token must not be dropped silently: every unmatched
// token has to end up in _unknown_args, not just the first one.
TEST_F(ArgumentsTest, UnknownTopLevelArgsAreAllCaptured) {
    Arguments args;
    Error error = args.parse("start,foo=1,bar=2");
    EXPECT_FALSE(error);
    ASSERT_EQ(args._unknown_args.size(), 2u);
    EXPECT_EQ(args._unknown_args[0], "foo");
    EXPECT_EQ(args._unknown_args[1], "bar");
}

// referencechains sub-options are parsed by their own colon-delimited loop,
// separate from the outer comma-token switch - an unmatched sub-key must still
// surface through the same _unknown_args reporting path instead of vanishing.
TEST_F(ArgumentsTest, UnknownReferenceChainsSubOptionIsCaptured) {
    Arguments args;
    Error error = args.parse("referencechains=true:budgt=500");
    EXPECT_FALSE(error);
    ASSERT_EQ(args._unknown_args.size(), 1u);
    EXPECT_EQ(args._unknown_args[0], "budgt");
    // The typo must not silently apply as if it were "budget".
    EXPECT_EQ(args._reference_chains_budget, DEFAULT_REFERENCE_CHAINS_BUDGET);
}

// A referencechains sub-token with no '=' at all (e.g. a stray colon) must also
// be reported rather than silently skipped.
TEST_F(ArgumentsTest, ReferenceChainsSubOptionWithoutEqualsIsCaptured) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=10:bogus");
    EXPECT_FALSE(error);
    ASSERT_EQ(args._unknown_args.size(), 1u);
    EXPECT_EQ(args._unknown_args[0], "bogus");
    EXPECT_EQ(args._reference_chains_hop_cap, 10);
}

TEST_F(ArgumentsTest, InvalidCstackValueIsAnError) {
    Arguments args;
    Error error = args.parse("cstack=dwrf");
    EXPECT_TRUE(error);
}

// "no" is a documented cstack value distinct from a typo and must keep working.
TEST_F(ArgumentsTest, CstackNoIsStillValid) {
    Arguments args;
    Error error = args.parse("cstack=no");
    EXPECT_FALSE(error);
    EXPECT_EQ(args._cstack, CSTACK_NO);
}

TEST_F(ArgumentsTest, InvalidWallsamplerValueIsAnError) {
    Arguments args;
    Error error = args.parse("wallsampler=x");
    EXPECT_TRUE(error);
}

// wallsampler used to switch on value[0] alone, so any value starting with 'j' or
// 'a' was silently accepted - a typo like "junk" or "anything" must now be rejected.
TEST_F(ArgumentsTest, InvalidWallsamplerJTypoIsAnError) {
    Arguments args;
    Error error = args.parse("wallsampler=junk");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, InvalidWallsamplerATypoIsAnError) {
    Arguments args;
    Error error = args.parse("wallsampler=anything");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, WallsamplerValidValuesStillWork) {
    Arguments args;
    Error error = args.parse("wallsampler=jvmti");
    EXPECT_FALSE(error);
    EXPECT_EQ(args._wallclock_sampler, JVMTI);

    Arguments args2;
    error = args2.parse("wallsampler=asgct");
    EXPECT_FALSE(error);
    EXPECT_EQ(args2._wallclock_sampler, ASGCT);
}

// mcleanup previously grouped its `default:` case with the "true" branch, so a
// typo silently enabled the feature instead of erroring.
TEST_F(ArgumentsTest, InvalidMcleanupValueIsAnError) {
    Arguments args;
    Error error = args.parse("mcleanup=xyz");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, InvalidRemotesymValueIsAnError) {
    Arguments args;
    Error error = args.parse("remotesym=xyz");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, InvalidNosanityValueIsAnError) {
    Arguments args;
    Error error = args.parse("nosanity=xyz");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, InvalidJvmtistacksValueIsAnError) {
    Arguments args;
    Error error = args.parse("jvmtistacks=xyz");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, InvalidLightweightValueIsAnError) {
    Arguments args;
    Error error = args.parse("lightweight=xyz");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, InvalidReferenceChainsBooleanValueIsAnError) {
    Arguments args;
    Error error = args.parse("referencechains=xyz");
    EXPECT_TRUE(error);
}

// A bare 'referencechains' with no '=' at all must still enable the feature - the
// parseBoolOption rewrite must not turn the no-value case into a silent no-op.
TEST_F(ArgumentsTest, BareReferenceChainsEnablesFeature) {
    Arguments args;
    Error error = args.parse("referencechains");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
}

// Sub-options only attach after an explicit boolean ("referencechains=true:hops=10").
// A bare "referencechains:hops=10" has no '=' right after the option name, so the
// top-level arg/value split (which cuts at the *first* '=' in the whole token) lands
// on the one inside "hops=10" instead - the resulting token "referencechains:hops"
// doesn't match the CASE at all and must be captured as unknown rather than silently
// misparsed as if hops=10 had been applied.
TEST_F(ArgumentsTest, ReferenceChainsSubOptionsWithoutBooleanIsUnknown) {
    Arguments args;
    Error error = args.parse("referencechains:hops=10");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._reference_chains);
    EXPECT_EQ(args._reference_chains_hop_cap, DEFAULT_REFERENCE_CHAINS_HOP_CAP);
    ASSERT_EQ(args._unknown_args.size(), 1u);
    EXPECT_EQ(args._unknown_args[0], "referencechains:hops");
}

TEST_F(ArgumentsTest, InvalidGenerationsValueIsAnError) {
    Arguments args;
    Error error = args.parse("generations=xyz");
    EXPECT_TRUE(error);
}

TEST_F(ArgumentsTest, GenerationsTrueAndFalseStillWork) {
    Arguments args;
    Error error = args.parse("generations=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._gc_generations);

    Arguments args2;
    error = args2.parse("generations=false");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args2._gc_generations);
}

// generations used to accept only the literal strings "true"/"false", unlike every
// other boolean option in this file - a user had no way to know that from the command
// string alone. It now goes through the same parseBoolOption convention as the rest.
TEST_F(ArgumentsTest, GenerationsAcceptsSharedBooleanConvention) {
    Arguments args;
    Error error = args.parse("generations=1,memory=128");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._gc_generations);

    Arguments args2;
    error = args2.parse("generations=no,memory=128");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args2._gc_generations);
}

// The established yes/no spelling (LightweightContextCpuTest.java, remoteargs_ut.cpp,
// wallprecheck_args_ut.cpp, SanityChecks.md) must keep working through the shared
// parseBoolOption helper.
TEST_F(ArgumentsTest, YesNoSpellingStillAccepted) {
    Arguments args;
    Error error = args.parse("lightweight=yes,remotesym=no");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._lightweight);
    EXPECT_FALSE(args._remote_symbolication);
}

// A typo that merely starts with a valid boolean letter (e.g. "tweq" starts with
// 't', "fjdw" starts with 'f') must still be rejected - parseBoolOption matches the
// whole value, not just value[0], otherwise these bugs would remain silent.
TEST_F(ArgumentsTest, BooleanOptionRejectsTypoSharingFirstLetterWithValidValue) {
    {
        Arguments args;
        Error error = args.parse("mcleanup=tweq");
        EXPECT_TRUE(error);
    }
    {
        Arguments args;
        Error error = args.parse("mcleanup=fjdw");
        EXPECT_TRUE(error);
    }
}

// fjmethodid takes true/false/lazy; lazy implies no preloading, and a later
// true/false in the same string must clear the lazy flag again.
TEST_F(ArgumentsTest, FjmethodidAcceptsLazy) {
    {
        Arguments args;
        EXPECT_TRUE(args._force_jmethodID);
        EXPECT_FALSE(args._lazy_jmethodID);
    }
    {
        Arguments args;
        EXPECT_FALSE(args.parse("fjmethodid=lazy"));
        EXPECT_FALSE(args._force_jmethodID);
        EXPECT_TRUE(args._lazy_jmethodID);
    }
    {
        Arguments args;
        EXPECT_FALSE(args.parse("fjmethodid=lazy,fjmethodid=false"));
        EXPECT_FALSE(args._force_jmethodID);
        EXPECT_FALSE(args._lazy_jmethodID);
    }
    {
        Arguments args;
        EXPECT_FALSE(args.parse("fjmethodid=lazy,fjmethodid=true"));
        EXPECT_TRUE(args._force_jmethodID);
        EXPECT_FALSE(args._lazy_jmethodID);
    }
    {
        Arguments args;
        EXPECT_TRUE(args.parse("fjmethodid=lazyx"));
    }
}
