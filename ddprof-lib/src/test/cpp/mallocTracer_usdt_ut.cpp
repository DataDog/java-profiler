/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <limits.h>
#include <math.h>
#include <string.h>

#include "mallocTracer.h"
#include "nativeAllocationUsdt.h"
#include "threadLocalData.inline.h"
#include "threadLocalDataPool.h"

namespace {

int jfr_count;
int active_count;
int emit_count;
uint16_t active_value;
void* emitted_address;
uint64_t emitted_size;
uint64_t emitted_weight;
bool sample_result;
bool critical_result;
ProfiledThread* acquire_result;
const char* stages[16];
size_t stage_count;

ProfiledThread* acquireHook() {
    return acquire_result;
}

bool criticalHook(bool entered) {
    return entered && critical_result;
}

bool sampleHook(size_t) {
    return sample_result;
}

void jfrHook(void*, size_t, int, MallocEvent*) {
    jfr_count++;
}

bool activeHook() {
    active_count++;
    return active_value != 0;
}

void emitHook(void* address, uint64_t size, uint64_t weight) {
    emit_count++;
    emitted_address = address;
    emitted_size = size;
    emitted_weight = weight;
}

void stageHook(const char* stage) {
    ASSERT_LT(stage_count, sizeof(stages) / sizeof(stages[0]));
    stages[stage_count++] = stage;
}

class MallocTracerUsdtTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!ThreadLocalDataPool::isInitialized()) {
            ThreadLocalDataPool::initialize();
        }
        ASSERT_NE(nullptr, ProfiledThread::initCurrentThreadSignalSafe());
    }

    void SetUp() override {
        jfr_count = 0;
        active_count = 0;
        emit_count = 0;
        active_value = 0;
        emitted_address = nullptr;
        emitted_size = 0;
        emitted_weight = 0;
        sample_result = true;
        critical_result = true;
        acquire_result = ProfiledThread::current();
        stage_count = 0;
        MallocTracer::configureForTest(NATIVE_MEMORY_JFR, 512, true);
        MallocTracer::setTestHooks(acquireHook, criticalHook, sampleHook,
                                   jfrHook, activeHook, emitHook, stageHook);
    }

    void TearDown() override {
        MallocTracer::resetTestHooks();
    }

    void expectStages(std::initializer_list<const char*> expected) {
        ASSERT_EQ(expected.size(), stage_count);
        size_t index = 0;
        for (const char* stage : expected) {
            EXPECT_STREQ(stage, stages[index++]);
        }
    }
};

TEST_F(MallocTracerUsdtTest, WeightUsesWeightedBytesContract) {
    EXPECT_EQ(0u, nativeAllocationUsdtWeight(0, 512));
    EXPECT_EQ(1u, nativeAllocationUsdtWeight(1, 0));
    EXPECT_EQ(17u, nativeAllocationUsdtWeight(17, 1));
    EXPECT_EQ(513u, nativeAllocationUsdtWeight(1, 512));
    EXPECT_EQ(810u, nativeAllocationUsdtWeight(512, 512));
    EXPECT_EQ(1184u, nativeAllocationUsdtWeight(1024, 512));
    EXPECT_EQ(4097u, nativeAllocationUsdtWeight(4096, 512));
    EXPECT_EQ((uint64_t)INT64_MAX,
              nativeAllocationUsdtWeight((size_t)INT64_MAX, UINT64_MAX));
}

TEST_F(MallocTracerUsdtTest, JfrModeNeverQueriesOrEmitsUsdt) {
    active_value = 1;
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1234), 512, 7);

    EXPECT_EQ(1, jfr_count);
    EXPECT_EQ(0, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"jfr", "accounting"});
}

TEST_F(MallocTracerUsdtTest, NoopModeProducesNoOutput) {
    active_value = 1;
    MallocTracer::configureForTest(NATIVE_MEMORY_NOOP, 512, true);
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1234), 512, 7);

    EXPECT_EQ(0, jfr_count);
    EXPECT_EQ(0, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"accounting"});
}

TEST_F(MallocTracerUsdtTest, NoopModeDoesNotStartTracer) {
    Arguments args;
    args._nativemem = 512;
    args._nativemem_output = NATIVE_MEMORY_NOOP;
    MallocTracer tracer;

    EXPECT_FALSE(tracer.start(args));
    EXPECT_FALSE(MallocTracer::running());
    expectStages({});
}

TEST_F(MallocTracerUsdtTest, UsdtModeSkipsJfrAndEmitsWeightedPayload) {
    active_value = 2;
    void* address = reinterpret_cast<void*>(0x1234);
    MallocTracer::configureForTest(NATIVE_MEMORY_USDT, 512, true);
    MallocTracer::recordMalloc(address, 512, 7);

    EXPECT_EQ(0, jfr_count);
    EXPECT_EQ(1, active_count);
    EXPECT_EQ(1, emit_count);
    EXPECT_EQ(address, emitted_address);
    EXPECT_EQ(512u, emitted_size);
    EXPECT_EQ(810u, emitted_weight);
    expectStages({"usdt", "accounting"});
}

TEST_F(MallocTracerUsdtTest, BothModeWritesJfrBeforeUsdtThenAccountsOnce) {
    active_value = 1;
    MallocTracer::configureForTest(NATIVE_MEMORY_BOTH, 512, true);
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1234), 512, 7);

    EXPECT_EQ(1, jfr_count);
    EXPECT_EQ(1, active_count);
    EXPECT_EQ(1, emit_count);
    expectStages({"jfr", "usdt", "accounting"});
}

TEST_F(MallocTracerUsdtTest, EveryNonzeroSemaphoreValueIsActive) {
    MallocTracer::configureForTest(NATIVE_MEMORY_USDT, 1, true);
    for (uint16_t value : {uint16_t(0), uint16_t(1), uint16_t(2), uint16_t(UINT16_MAX)}) {
        active_value = value;
        int before = emit_count;
        MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1234), 8, 7);
        EXPECT_EQ(before + (value == 0 ? 0 : 1), emit_count);
    }
    EXPECT_EQ(4, active_count);
}

#if defined(__linux__)
TEST_F(MallocTracerUsdtTest, SemaphoreUsesTheKernelReferenceCountSemantics) {
    for (uint16_t value : {uint16_t(0), uint16_t(1), uint16_t(2), uint16_t(UINT16_MAX)}) {
        setNativeAllocationUsdtSemaphoreForTest(value);
        EXPECT_EQ(value != 0, isNativeAllocationUsdtEnabled());
    }
    setNativeAllocationUsdtSemaphoreForTest(0);
}
#endif

TEST_F(MallocTracerUsdtTest, AttachDetachDoesNotResetAcceptedSampleAccounting) {
    MallocTracer::configureForTest(NATIVE_MEMORY_USDT, 1, true);
    active_value = 0;
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1000), 8, 7);
    active_value = 1;
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x2000), 8, 7);
    active_value = 0;
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x3000), 8, 7);

    EXPECT_EQ(3, active_count);
    EXPECT_EQ(1, emit_count);
    size_t accounting_count = 0;
    for (size_t i = 0; i < stage_count; i++) {
        if (strcmp(stages[i], "accounting") == 0) accounting_count++;
    }
    EXPECT_EQ(3u, accounting_count);
}

#if SIZE_MAX > INT64_MAX
TEST_F(MallocTracerUsdtTest, OversizedAllocationStillUsesJfrAndAccountingInBothMode) {
    active_value = 1;
    MallocTracer::configureForTest(NATIVE_MEMORY_BOTH, 512, true);
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1234),
                               (size_t)INT64_MAX + 1, 7);

    EXPECT_EQ(1, jfr_count);
    EXPECT_EQ(0, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"jfr", "accounting"});
}
#endif

TEST_F(MallocTracerUsdtTest, MaybeRecordPreservesGuardAndOutputOrder) {
    MallocTracer::maybeRecord(reinterpret_cast<void*>(0x1234), 512);
    expectStages({"acquire", "critical-section", "sampling", "jfr", "accounting"});
}

TEST_F(MallocTracerUsdtTest, AcquisitionFailureStopsBeforeGuardAndSampling) {
    acquire_result = nullptr;
    MallocTracer::maybeRecord(reinterpret_cast<void*>(0x1234), 512);

    EXPECT_EQ(0, jfr_count);
    EXPECT_EQ(0, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"acquire"});
}

TEST_F(MallocTracerUsdtTest, CriticalSectionRejectionStopsBeforeSampling) {
    critical_result = false;
    MallocTracer::maybeRecord(reinterpret_cast<void*>(0x1234), 512);

    EXPECT_EQ(0, jfr_count);
    EXPECT_EQ(0, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"acquire", "critical-section"});
}

TEST_F(MallocTracerUsdtTest, RejectedSampleHasNoOutputOrAccounting) {
    sample_result = false;
    MallocTracer::maybeRecord(reinterpret_cast<void*>(0x1234), 512);

    EXPECT_EQ(0, jfr_count);
    EXPECT_EQ(0, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"acquire", "critical-section", "sampling"});
}

TEST_F(MallocTracerUsdtTest, InactiveUsdtSkipsWeightAndEmissionButAccounts) {
    MallocTracer::configureForTest(NATIVE_MEMORY_USDT, 512, true);
    active_value = 0;
    MallocTracer::recordMalloc(reinterpret_cast<void*>(0x1234), 512, 7);

    EXPECT_EQ(0, jfr_count);
    EXPECT_EQ(1, active_count);
    EXPECT_EQ(0, emit_count);
    expectStages({"accounting"});
}

} // namespace
