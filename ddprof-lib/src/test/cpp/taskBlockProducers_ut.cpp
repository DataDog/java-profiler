/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "guards.h"
#include "javaApi.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "threadLocalData.inline.h"

class ProfilerTestAccessor {
public:
    static void setProducerState(Profiler* profiler, bool enabled) {
        profiler->_task_block_enabled.store(enabled, std::memory_order_release);
        profiler->_task_block_monitor_events_enabled.store(enabled, std::memory_order_release);
    }
    static State exchangeState(Profiler* profiler, State state) {
        return profiler->_state.exchange(state, std::memory_order_acq_rel);
    }
};

class VMTestAccessor {
public:
    static jvmtiEnv* exchangeJvmti(jvmtiEnv* jvmti) {
        jvmtiEnv* previous = VM::_jvmti;
        VM::_jvmti = jvmti;
        return previous;
    }
};

// Exercise the real producer lifecycle and registry with a minimal JNI thread
// identity. JFR stack capture is covered by the Java integration suites.
class TaskBlockProducersTest : public ::testing::Test {
protected:
    void SetUp() override {
        jni_functions.GetVersion = [](JNIEnv*) -> jint { return JNI_VERSION_1_8; };
        jni_functions.IsSameObject = [](JNIEnv*, jobject a, jobject b) -> jboolean {
            return a == b ? JNI_TRUE : JNI_FALSE;
        };
        jni_functions.DeleteLocalRef = [](JNIEnv*, jobject) {};
        jni.functions = &jni_functions;
        jvmti_functions.GetCurrentThread = [](jvmtiEnv*, jthread* thread) -> jvmtiError {
            *thread = testThread();
            return JVMTI_ERROR_NONE;
        };
        jvmti.functions = &jvmti_functions;
        previous_jvmti = VMTestAccessor::exchangeJvmti(&jvmti);
        previous_state = ProfilerTestAccessor::exchangeState(profiler, RUNNING);
        ProfilerTestAccessor::setProducerState(profiler, true);
        Profiler::setTaskBlockRecordOverrideForTest(
            [](int, jthread, int, TaskBlockEvent*) {
                return Profiler::TaskBlockRecordResult::RECORDED;
            });
        registry->init("", true);
        current = ProfiledThread::initCurrentThreadSignalSafe();
        ASSERT_NE(nullptr, current);
        current->setFilterSlotId(-1);
    }

    void TearDown() override {
        ProfilerTestAccessor::setProducerState(profiler, false);
        ProfilerTestAccessor::exchangeState(profiler, previous_state);
        Profiler::setTaskBlockRecordOverrideForTest(nullptr);
        VMTestAccessor::exchangeJvmti(previous_jvmti);
        registry->deactivateRecording();
        ProfiledThread::release();
    }

    static jthread testThread() {
        static int identity;
        return reinterpret_cast<jthread>(&identity);
    }

    u64 begin() {
        return Java_com_datadoghq_profiler_JavaProfiler_beginTaskBlock0(
            &jni, nullptr, testThread());
    }

    void end(u64 token) {
        Java_com_datadoghq_profiler_JavaProfiler_endTaskBlock0(
            &jni, nullptr, testThread(), token, 0, 0);
    }

    WallClockBlockTracker::BlockState* block() {
        return tracker->slotForId(current->filterSlotId());
    }

    SignalBlocker signal_blocker;
    Profiler* profiler = Profiler::instance();
    ThreadFilter* registry = profiler->threadFilter();
    WallClockBlockTracker* tracker = profiler->blockTracker();
    ProfiledThread* current = nullptr;
    JNINativeInterface_ jni_functions{};
    JNIEnv jni{};
    jvmtiInterface_1_ jvmti_functions{};
    jvmtiEnv jvmti{};
    jvmtiEnv* previous_jvmti = nullptr;
    State previous_state = NEW;
};

TEST_F(TaskBlockProducersTest, PairedApiRecoversAbandonedIntervalAfterRestart) {
    u64 old_token = begin();
    ASSERT_NE(0u, old_token);
    int slot_id = current->filterSlotId();
    auto* identity = registry->slotForId(slot_id);
    u64 lifecycle = identity->lifecycleGeneration();

    registry->deactivateRecording();
    registry->init("", true);
    // Another hook may refresh the registry first, independently of producer TLS.
    ASSERT_EQ(slot_id, registry->ensureCurrentThreadSlot(current));
    u64 new_token = begin();
    ASSERT_NE(0u, new_token);
    EXPECT_NE(old_token, new_token);
    EXPECT_EQ(identity, registry->activeSlotForId(slot_id, current->tid()));
    EXPECT_EQ(lifecycle, identity->lifecycleGeneration());

    end(old_token);
    EXPECT_EQ(new_token, current->taskBlockToken());
    EXPECT_EQ(BlockRunOwner::TASK_BLOCK, block()->activeBlockOwner());
    end(new_token);
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

TEST_F(TaskBlockProducersTest, PairedApiRecoversAbandonedGenericHookAfterContextEntry) {
    u64 old_token = Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(
        &jni, nullptr, JNI_FALSE, static_cast<jint>(OSThreadState::SLEEPING));
    ASSERT_NE(0u, old_token);
    ASSERT_TRUE(registry->add(current->tid(), current->filterSlotId()));
    registry->remove(current->filterSlotId());
    ASSERT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());

    u64 token = begin();
    ASSERT_NE(0u, token);
    EXPECT_NE(old_token, token);
    EXPECT_EQ(0u, begin()) << "A nested begin must preserve the current owner";
    EXPECT_EQ(token, current->taskBlockToken());
    end(token);
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

TEST_F(TaskBlockProducersTest, GenericExitAfterRestartClearsAbandonedTls) {
    u64 token = Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(
        &jni, nullptr, JNI_FALSE, static_cast<jint>(OSThreadState::SLEEPING));
    ASSERT_NE(0u, token);
    registry->deactivateRecording();
    registry->init("", true);
    Java_com_datadoghq_profiler_JavaProfiler_blockExit0(
        &jni, nullptr, JNI_FALSE, token, 0, 0);
    EXPECT_EQ(0u, current->taskBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
    u64 next = begin();
    ASSERT_NE(0u, next);
    end(next);
}

TEST_F(TaskBlockProducersTest, MonitorRestartPreservesIdentityAndRejectsOldWaitExit) {
    EXPECT_EQ(-1, current->filterSlotId()) << "Thread start must not reserve a slot";
    MonitorWait(&jvmti, &jni, testThread(), nullptr, 100);
    u64 old_token = current->monitorBlockToken();
    ASSERT_NE(0u, old_token);
    int slot_id = current->filterSlotId();
    auto* identity = registry->slotForId(slot_id);
    u64 lifecycle = identity->lifecycleGeneration();

    registry->deactivateRecording();
    registry->init("", true);
    MonitorContendedEnter(&jvmti, &jni, testThread(), nullptr);
    u64 new_token = current->monitorBlockToken();
    ASSERT_NE(0u, new_token);
    EXPECT_NE(old_token, new_token);
    EXPECT_EQ(slot_id, current->filterSlotId());
    EXPECT_EQ(lifecycle, identity->lifecycleGeneration());
    EXPECT_EQ(OSThreadState::MONITOR_WAIT, block()->activeBlockState());
    MonitorWaited(&jvmti, &jni, testThread(), nullptr, JNI_FALSE);
    EXPECT_EQ(new_token, current->monitorBlockToken());
    MonitorContendedEntered(&jvmti, &jni, testThread(), nullptr);
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

TEST_F(TaskBlockProducersTest, InflightMonitorExitCleansUpAfterAdmissionCloses) {
    MonitorWait(&jvmti, &jni, testThread(), nullptr, 100);
    ASSERT_NE(0u, current->monitorBlockToken());
    ProfilerTestAccessor::setProducerState(profiler, false);
    registry->deactivateRecording();
    MonitorWaited(&jvmti, &jni, testThread(), nullptr, JNI_FALSE);
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

class MonitorTaskBlockHashTest : public TaskBlockProducersTest,
                                 public ::testing::WithParamInterface<bool> {
protected:
    inline static int hash_calls;
    inline static jobject hashed_object;
    inline static int record_calls;
    inline static TaskBlockEvent recorded_event;
    static constexpr jint MONITOR_HASH = -12345;
    _jobject monitor;

    void SetUp() override {
        TaskBlockProducersTest::SetUp();
        Counters::reset();
        initializeTaskBlockDurationThreshold();
        hash_calls = 0;
        hashed_object = nullptr;
        record_calls = 0;
        recorded_event = {};
        jvmti_functions.GetObjectHashCode = [](jvmtiEnv*, jobject object, jint* hash) -> jvmtiError {
            hash_calls++;
            hashed_object = object;
            *hash = MONITOR_HASH;
            return JVMTI_ERROR_NONE;
        };
        Profiler::setTaskBlockRecordOverrideForTest(
            [](int, jthread, int, TaskBlockEvent* event) {
                record_calls++;
                recorded_event = *event;
                return Profiler::TaskBlockRecordResult::RECORDED;
            });
    }

    void TearDown() override {
        setMonitorTaskBlockTicksForTest(0);
        TaskBlockProducersTest::TearDown();
        Counters::reset();
    }

    void enterMonitor() {
        if (GetParam()) {
            MonitorWait(&jvmti, &jni, testThread(), &monitor, 100);
        } else {
            MonitorContendedEnter(&jvmti, &jni, testThread(), &monitor);
        }
    }

    void exitMonitor() {
        if (GetParam()) {
            MonitorWaited(&jvmti, &jni, testThread(), &monitor, JNI_FALSE);
        } else {
            MonitorContendedEntered(&jvmti, &jni, testThread(), &monitor);
        }
    }
};

INSTANTIATE_TEST_SUITE_P(MonitorCallbacks, MonitorTaskBlockHashTest, ::testing::Bool());

TEST_P(MonitorTaskBlockHashTest, ShortBlockSkipsHashAndNextEligibleBlockHashesOnce) {
    u64 min_ticks = TSC::frequency() / 1000;
    ASSERT_GT(min_ticks, 1u);
    u64 start_ticks = 100;
    setMonitorTaskBlockTicksForTest(start_ticks);
    enterMonitor();
    ASSERT_NE(0u, current->monitorBlockToken());
    EXPECT_EQ(0, hash_calls) << "Entry must not resolve the monitor hash";

    setMonitorTaskBlockTicksForTest(start_ticks + min_ticks - 1);
    exitMonitor();
    EXPECT_EQ(0, hash_calls) << "A below-threshold exit must not resolve the monitor hash";
    EXPECT_EQ(0, record_calls);
    EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());

    start_ticks += min_ticks + 100;
    setMonitorTaskBlockTicksForTest(start_ticks);
    enterMonitor();
    ASSERT_NE(0u, current->monitorBlockToken());
    EXPECT_EQ(0, hash_calls);

    setMonitorTaskBlockTicksForTest(start_ticks + min_ticks);
    exitMonitor();
    EXPECT_EQ(1, hash_calls);
    EXPECT_EQ(&monitor, hashed_object);
    EXPECT_EQ(1, record_calls);
    EXPECT_EQ(static_cast<u64>(static_cast<uint32_t>(MONITOR_HASH)), recorded_event._blocker);
    EXPECT_EQ(start_ticks, recorded_event._start);
    EXPECT_EQ(start_ticks + min_ticks, recorded_event._end);
    EXPECT_EQ(GetParam() ? OSThreadState::OBJECT_WAIT : OSThreadState::MONITOR_WAIT,
              recorded_event._observedBlockingState);
    EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());

    exitMonitor();
    EXPECT_EQ(1, hash_calls);
    EXPECT_EQ(1, record_calls);
}

TEST_F(TaskBlockProducersTest, ParkLifecycleDoesNotRequireRegistryAdmission) {
    ProfilerTestAccessor::setProducerState(profiler, false);
    registry->deactivateRecording();
    EXPECT_EQ(JNI_TRUE, Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(
        &jni, nullptr, testThread(), JNI_FALSE));
    EXPECT_EQ(-1, current->filterSlotId());
    EXPECT_EQ(0u, current->snapshotForTest().park_block_token);
    EXPECT_EQ(JNI_FALSE, Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(
        &jni, nullptr, testThread(), JNI_FALSE));
    Java_com_datadoghq_profiler_JavaProfiler_parkExit0(
        &jni, nullptr, testThread(), JNI_FALSE, 0, 0);
    EXPECT_EQ(JNI_TRUE, Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(
        &jni, nullptr, testThread(), JNI_FALSE));
    Java_com_datadoghq_profiler_JavaProfiler_parkExit0(
        &jni, nullptr, testThread(), JNI_FALSE, 0, 0);
}

TEST_F(TaskBlockProducersTest, RotationDefersOwnershipWithoutDiscardingUnownedTail) {
    int slot_id = registry->ensureCurrentThreadSlot(current);
    ASSERT_GE(slot_id, 0);
    block()->recordUnownedBlockedSample(0x1234, OSThreadState::SLEEPING);
    ASSERT_TRUE(block()->shouldRecordUnownedBlockedSample());
    ASSERT_FALSE(block()->shouldRecordUnownedBlockedSample());
    profiler->beginTaskBlockRotationForTest();
    u64 token = enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT);
    profiler->endTaskBlockRotationForTest();

    EXPECT_EQ(0u, token);
    EXPECT_EQ(1u, block()->unowned_blocked_pending_weight.load(std::memory_order_acquire));
    EXPECT_EQ(0x1234u, block()->unowned_blocked_call_trace_id.load(std::memory_order_acquire));
    EXPECT_TRUE(block()->unownedBlockedFallbackEnabled());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

TEST_F(TaskBlockProducersTest, RejectedContextAdmissionRestoresUnownedFallback) {
    int slot_id = registry->ensureCurrentThreadSlot(current);
    ASSERT_GE(slot_id, 0);
    ASSERT_TRUE(registry->add(current->tid(), slot_id));
    EXPECT_EQ(0u, enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT));
    EXPECT_TRUE(block()->unownedBlockedFallbackEnabled());
    registry->remove(slot_id);
}
