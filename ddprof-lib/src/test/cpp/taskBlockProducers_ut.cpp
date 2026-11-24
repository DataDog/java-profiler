/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <cstring>
#include <thread>

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
    static bool exchangeOmit(Profiler* profiler, bool omit) {
        bool previous = profiler->_omit_stacktraces;
        profiler->_omit_stacktraces = omit;
        return previous;
    }
    static int exchangeDepth(Profiler* profiler, int depth) {
        int previous = profiler->_max_stack_depth;
        profiler->_max_stack_depth = depth;
        return previous;
    }
};

class VMTestAccessor {
public:
    static jvmtiEnv* exchangeJvmti(jvmtiEnv* jvmti) {
        jvmtiEnv* previous = VM::_jvmti;
        VM::_jvmti = jvmti;
        return previous;
    }
    static bool exchangeHotspot(bool hotspot) {
        bool previous = VM::_hotspot;
        VM::_hotspot = hotspot;
        return previous;
    }
    static bool exchangeWaitDelegation(bool delegated) {
        bool previous = VM::_monitor_wait_events_delegated.value();
        VM::_monitor_wait_events_delegated.set(delegated);
        return previous;
    }
};

class WaitDelegationOverride {
public:
    explicit WaitDelegationOverride(bool delegated)
        : _saved(VMTestAccessor::exchangeWaitDelegation(delegated)) {}
    ~WaitDelegationOverride() { VMTestAccessor::exchangeWaitDelegation(_saved); }
    WaitDelegationOverride(const WaitDelegationOverride&) = delete;
    WaitDelegationOverride& operator=(const WaitDelegationOverride&) = delete;
private:
    bool _saved;
};

class HotspotOverride {
public:
    explicit HotspotOverride(bool hotspot) : _saved(VMTestAccessor::exchangeHotspot(hotspot)) {}
    ~HotspotOverride() { VMTestAccessor::exchangeHotspot(_saved); }
    HotspotOverride(const HotspotOverride&) = delete;
    HotspotOverride& operator=(const HotspotOverride&) = delete;
private:
    bool _saved;
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
        current->setJvmInternalThread(false);
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
    ASSERT_EQ(slot_id, registry->ensureOwnerSlot(*current));
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
    registry->onContextWindowEnter(*current);
    registry->onContextWindowExit(*current);
    ASSERT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());

    u64 token = begin();
    ASSERT_NE(0u, token) << "paired API must recover the abandoned generic-hook payload";
    EXPECT_NE(old_token, token);
    end(old_token);
    EXPECT_EQ(token, current->taskBlockToken());
    u64 replacement = begin();
    ASSERT_NE(0u, replacement) << "a nested begin must supersede the current owner";
    EXPECT_NE(token, replacement);
    end(token);
    EXPECT_EQ(replacement, current->taskBlockToken());
    EXPECT_EQ(BlockRunOwner::TASK_BLOCK, block()->activeBlockOwner());
    end(replacement);
    EXPECT_EQ(0u, current->taskBlockToken());
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

TEST_F(TaskBlockProducersTest, MonitorContextWindowRejectionDoesNotCountAsTraceContext) {
    registry->onContextWindowEnter(*current);
    long long window_before = Counters::getCounter(TASK_BLOCK_SKIPPED_CONTEXT_WINDOW);
    long long trace_before = Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    MonitorContendedEnter(&jvmti, &jni, testThread(), nullptr);
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
    EXPECT_EQ(window_before + 1, Counters::getCounter(TASK_BLOCK_SKIPPED_CONTEXT_WINDOW));
    EXPECT_EQ(trace_before, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
    registry->onContextWindowExit(*current);
    MonitorContendedEnter(&jvmti, &jni, testThread(), nullptr);
    EXPECT_NE(0u, current->monitorBlockToken());
    MonitorContendedEntered(&jvmti, &jni, testThread(), nullptr);
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

static int g_is_virtual_thread_calls;

TEST_F(TaskBlockProducersTest, MonitorProducersAreInertOnNonHotspotJni21) {
    using JniFunction = void (JNICALL*)();
    constexpr size_t GET_VERSION_INDEX = 4;
    constexpr size_t IS_VIRTUAL_THREAD_INDEX = 234;
    JniFunction table[IS_VIRTUAL_THREAD_INDEX + 1]{};
    std::memcpy(table, &jni_functions, std::min(sizeof(table), sizeof(jni_functions)));
    table[GET_VERSION_INDEX] = reinterpret_cast<JniFunction>(
        +[](JNIEnv*) -> jint { return 0x00150000; });
    table[IS_VIRTUAL_THREAD_INDEX] = reinterpret_cast<JniFunction>(
        +[](JNIEnv*, jobject) -> jboolean { g_is_virtual_thread_calls++; return JNI_FALSE; });
    JNIEnv jni21{};
    jni21.functions = reinterpret_cast<const JNINativeInterface_*>(table);
    g_is_virtual_thread_calls = 0;
    {
        HotspotOverride non_hotspot(false);
        MonitorContendedEnter(&jvmti, &jni21, testThread(), nullptr);
        EXPECT_EQ(0u, current->monitorBlockToken());
        MonitorWait(&jvmti, &jni21, testThread(), nullptr, 100);
        EXPECT_EQ(0u, current->monitorBlockToken());
        EXPECT_EQ(0, g_is_virtual_thread_calls) << "non-HotSpot must not call JNI slot 234";
    }
    // Positive control: the same JNI 21 table arms the interval on HotSpot.
    HotspotOverride hotspot(true);
    MonitorContendedEnter(&jvmti, &jni21, testThread(), nullptr);
    EXPECT_NE(0u, current->monitorBlockToken());
    EXPECT_EQ(1, g_is_virtual_thread_calls);
    MonitorContendedEntered(&jvmti, &jni21, testThread(), nullptr);
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

static int g_get_version_calls;
static bool g_profiled_thread_at_get_version;

TEST_F(TaskBlockProducersTest, MonitorCallbacksAttachProfiledThreadBeforeJni) {
    JNINativeInterface_ functions = jni_functions;
    // An invalid version stops classification after the probe records the TLS state.
    functions.GetVersion = [](JNIEnv*) -> jint {
        g_get_version_calls++;
        g_profiled_thread_at_get_version = ProfiledThread::current() != nullptr;
        return 0;
    };
    JNIEnv probe_jni{};
    probe_jni.functions = &functions;
    g_get_version_calls = 0;
    g_profiled_thread_at_get_version = false;
    bool exit_had_thread = true;
    bool enter_left_thread = false;
    std::thread fresh([&] {
        MonitorContendedEntered(&jvmti, &probe_jni, testThread(), nullptr);
        exit_had_thread = ProfiledThread::current() != nullptr;
        MonitorContendedEnter(&jvmti, &probe_jni, testThread(), nullptr);
        enter_left_thread = ProfiledThread::current() != nullptr;
        ProfiledThread::release();
    });
    fresh.join();
    EXPECT_FALSE(exit_had_thread) << "an exit must not attach a ProfiledThread";
    EXPECT_TRUE(enter_left_thread);
    EXPECT_EQ(1, g_get_version_calls) << "only the entry may reach JNI on a fresh thread";
    EXPECT_TRUE(g_profiled_thread_at_get_version)
        << "entry must attach the ProfiledThread before any JNI call";
}

class MonitorTaskBlockRecordTest : public TaskBlockProducersTest {
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
};

// A contended re-entry after Object.wait() returns belongs to the wait interval.
TEST_F(MonitorTaskBlockRecordTest, NestedContentionKeepsObjectWaitInterval) {
    u64 min_ticks = TSC::frequency() / 1000;
    ASSERT_GT(min_ticks, 1u);
    constexpr u64 start_ticks = 100;
    setMonitorTaskBlockTicksForTest(start_ticks);
    MonitorWait(&jvmti, &jni, testThread(), &monitor, 100);
    u64 token = current->monitorBlockToken();
    ASSERT_NE(0u, token);

    MonitorContendedEnter(&jvmti, &jni, testThread(), &monitor);
    EXPECT_EQ(token, current->monitorBlockToken()) << "the live wait owner must be retained";
    EXPECT_EQ(OSThreadState::OBJECT_WAIT, block()->activeBlockState());
    setMonitorTaskBlockTicksForTest(start_ticks + min_ticks);
    MonitorContendedEntered(&jvmti, &jni, testThread(), &monitor);
    EXPECT_EQ(token, current->monitorBlockToken()) << "the nested exit must not end the wait";
    EXPECT_EQ(0, record_calls);

    MonitorWaited(&jvmti, &jni, testThread(), &monitor, JNI_FALSE);
    EXPECT_EQ(1, record_calls);
    EXPECT_EQ(OSThreadState::OBJECT_WAIT, recorded_event._observedBlockingState);
    EXPECT_EQ(start_ticks, recorded_event._start);
    EXPECT_EQ(0u, current->monitorBlockToken());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
}

// The open segment starts at the monitor entry tick, not at a later clock read.
TEST_F(MonitorTaskBlockRecordTest, EntryTickSeedsTheOpenSegment) {
    constexpr u64 start_ticks = 100;
    setMonitorTaskBlockTicksForTest(start_ticks);
    MonitorContendedEnter(&jvmti, &jni, testThread(), &monitor);
    u64 token = current->monitorBlockToken();
    ASSERT_NE(0u, token);
    BlockRunSnapshot snapshot;
    ASSERT_TRUE(profiler->blockTracker()->snapshotAndExitBlockedRun(
        registry, current->filterSlotId(), WallClockBlockTracker::tokenGeneration(token), &snapshot));
    EXPECT_TRUE(snapshot.segment_claimed);
    EXPECT_EQ(start_ticks, snapshot.segment_start);
    current->clearMonitorBlock();
}

// With Object.wait delegated to Java, the native wait callbacks own nothing.
TEST_F(MonitorTaskBlockRecordTest, DelegatedWaitCallbacksAreNoOps) {
    {
        WaitDelegationOverride delegated(true);
        MonitorWait(&jvmti, &jni, testThread(), &monitor, 100);
        EXPECT_EQ(0u, current->monitorBlockToken());
        EXPECT_EQ(-1, current->filterSlotId()) << "a delegated wait must not reserve a slot";
    }
    // Positive control: without delegation the same wait arms, and a delegated
    // MonitorWaited leaves that native-owned interval for its own exit.
    MonitorWait(&jvmti, &jni, testThread(), &monitor, 100);
    u64 token = current->monitorBlockToken();
    ASSERT_NE(0u, token);
    {
        WaitDelegationOverride delegated(true);
        MonitorWaited(&jvmti, &jni, testThread(), &monitor, JNI_FALSE);
        EXPECT_EQ(token, current->monitorBlockToken());
    }
    MonitorWaited(&jvmti, &jni, testThread(), &monitor, JNI_FALSE);
    EXPECT_EQ(0u, current->monitorBlockToken());
}

class MonitorTaskBlockHashTest : public MonitorTaskBlockRecordTest,
                                 public ::testing::WithParamInterface<bool> {
protected:
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
    EXPECT_EQ(0u, current->snapshotForTest().park_slot.block_token);
    EXPECT_EQ(JNI_FALSE, Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(
        &jni, nullptr, testThread(), JNI_FALSE));
    Java_com_datadoghq_profiler_JavaProfiler_parkExit0(
        &jni, nullptr, testThread(), JNI_FALSE, 0, 0);
    EXPECT_EQ(JNI_TRUE, Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(
        &jni, nullptr, testThread(), JNI_FALSE));
    Java_com_datadoghq_profiler_JavaProfiler_parkExit0(
        &jni, nullptr, testThread(), JNI_FALSE, 0, 0);
}

// Captures producer-side tail flushes; a false result models a failed JFR write.
struct TailFlushCapture {
    static inline int writes;
    static inline u64 trace;
    static inline u64 weight;
    static inline bool accept;

    explicit TailFlushCapture(Profiler* profiler, bool accept_writes) : _profiler(profiler) {
        writes = 0;
        trace = 0;
        weight = 0;
        accept = accept_writes;
        profiler->sampleWriteHookForTest = [](u32, u64 id, Event* event, const Context*, void*) {
            ++writes;
            trace = id;
            weight = static_cast<ExecutionEvent*>(event)->_weight;
            return accept;
        };
    }
    ~TailFlushCapture() { _profiler->sampleWriteHookForTest = nullptr; }
    TailFlushCapture(const TailFlushCapture&) = delete;
    TailFlushCapture& operator=(const TailFlushCapture&) = delete;

private:
    Profiler* _profiler;
};

class OwnedBlockAdmissionTest : public TaskBlockProducersTest {
protected:
    static constexpr u64 kOrigin = 0x1234;
    int slot_id = -1;

    void SetUp() override {
        TaskBlockProducersTest::SetUp();
        tracker->setUnownedContextSnapshotsNeeded(true);
        slot_id = registry->ensureOwnerSlot(*current);
        ASSERT_GE(slot_id, 0);
        // The writer replays the published context once per deferred epoch segment.
        ASSERT_TRUE(tracker->publishUnownedTrace(slot_id, kOrigin, OSThreadState::SLEEPING, Context{}));
        ASSERT_TRUE(tracker->deferUnownedWeight(slot_id, TSC::ticks()));
        ASSERT_EQ(1u, pendingWeight());
    }

    void TearDown() override {
        block()->resetUnownedBlockedSampling();
        tracker->setUnownedContextSnapshotsNeeded(false);
        TaskBlockProducersTest::TearDown();
    }

    u64 pendingWeight() {
        return block()->unowned_blocked_pending_weight.load(std::memory_order_acquire);
    }

    void expectTailRetained() {
        EXPECT_EQ(1u, pendingWeight());
        EXPECT_EQ(kOrigin, block()->unowned_blocked_call_trace_id.load(std::memory_order_acquire));
        EXPECT_TRUE(block()->unownedBlockedFallbackEnabled());
        EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
    }
};

TEST_F(OwnedBlockAdmissionTest, FlushesPendingTailThenOwnsRunWithFallbackPaused) {
    TailFlushCapture capture(profiler, true);
    u64 token = enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT);
    ASSERT_NE(0u, token);
    EXPECT_EQ(1, TailFlushCapture::writes);
    EXPECT_EQ(kOrigin, TailFlushCapture::trace);
    EXPECT_EQ(1u, TailFlushCapture::weight);
    EXPECT_EQ(0u, pendingWeight());
    EXPECT_FALSE(block()->unownedBlockedFallbackEnabled()) << "an owned run pauses the fallback";
    EXPECT_EQ(BlockRunOwner::JAVA, block()->activeBlockOwner());
    u64 generation = 0;
    ASSERT_TRUE(WallClockBlockTracker::decodeBlockRunToken(token, slot_id, generation));
    tracker->exitBlockedRun(slot_id, generation);
}

TEST_F(OwnedBlockAdmissionTest, FailedTailFlushRejectsAdmissionAndRetainsTail) {
    TailFlushCapture capture(profiler, false);
    EXPECT_EQ(0u, enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT));
    EXPECT_EQ(1, TailFlushCapture::writes);
    expectTailRetained();
}

TEST_F(OwnedBlockAdmissionTest, RotationDefersOwnershipWithoutDiscardingUnownedTail) {
    TailFlushCapture capture(profiler, true);
    long long dropped = Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION);
    profiler->beginTaskBlockRotationForTest();
    u64 token = enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT);
    profiler->endTaskBlockRotationForTest();

    EXPECT_EQ(0u, token);
    EXPECT_EQ(dropped + 1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
    EXPECT_EQ(0, TailFlushCapture::writes);
    expectTailRetained();
    // Positive control: the same admission succeeds once rotation ends.
    token = enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT);
    ASSERT_NE(0u, token);
    EXPECT_EQ(1, TailFlushCapture::writes);
    u64 generation = 0;
    ASSERT_TRUE(WallClockBlockTracker::decodeBlockRunToken(token, slot_id, generation));
    tracker->exitBlockedRun(slot_id, generation);
}

TEST_F(OwnedBlockAdmissionTest, RejectedContextAdmissionRestoresUnownedFallback) {
    TailFlushCapture capture(profiler, true);
    ASSERT_TRUE(registry->add(current->tid(), slot_id));
    EXPECT_EQ(0u, enterOwnedBlockRun(current, slot_id, OSThreadState::CONDVAR_WAIT));
    EXPECT_EQ(1, TailFlushCapture::writes) << "admission must flush before the context check";
    EXPECT_EQ(0u, pendingWeight());
    EXPECT_TRUE(block()->unownedBlockedFallbackEnabled());
    EXPECT_EQ(BlockRunOwner::NONE, block()->activeBlockOwner());
    registry->remove(slot_id);
}

// Drives the real callbacks with a fake GetStackTrace to check entry capture and slot custody.
class MonitorEntryStackTest : public MonitorTaskBlockRecordTest {
protected:
    static constexpr int kDepth = 4;
    inline static int stack_calls;
    MonitorEntryStacks* stacks = profiler->monitorEntryStacks();
    bool previous_omit = false;
    int previous_depth = 0;
    u64 min_ticks = 0;

    void SetUp() override {
        MonitorTaskBlockRecordTest::SetUp();
        stack_calls = 0;
        jvmti_functions.GetStackTrace = [](jvmtiEnv*, jthread, jint, jint, jvmtiFrameInfo* frames,
                                           jint* count) -> jvmtiError {
            stack_calls++;
            frames[0] = {reinterpret_cast<jmethodID>(0x5150), 3};
            *count = 1;
            return JVMTI_ERROR_NONE;
        };
        previous_omit = ProfilerTestAccessor::exchangeOmit(profiler, false);
        previous_depth = ProfilerTestAccessor::exchangeDepth(profiler, kDepth);
        ASSERT_TRUE(stacks->allocate(kDepth));
        min_ticks = TSC::frequency() / 1000;
        ASSERT_GT(min_ticks, 1u);
        setMonitorTaskBlockTicksForTest(100);
    }

    void TearDown() override {
        stacks->release();
        ProfilerTestAccessor::exchangeDepth(profiler, previous_depth);
        ProfilerTestAccessor::exchangeOmit(profiler, previous_omit);
        MonitorTaskBlockRecordTest::TearDown();
    }

    void enter() {
        MonitorContendedEnter(&jvmti, &jni, testThread(), &monitor);
        ASSERT_NE(0u, current->monitorBlockToken());
    }

    void exitAfter(u64 duration) {
        setMonitorTaskBlockTicksForTest(100 + duration);
        MonitorContendedEntered(&jvmti, &jni, testThread(), &monitor);
    }

    u64 heldLease() {
        u64 lease = current->exchangeMonitorEntryStackLease(0);
        current->exchangeMonitorEntryStackLease(lease);
        return lease;
    }
};

TEST_F(MonitorEntryStackTest, EntryCapturesOnceAndEligibleExitReleasesSlot) {
    enter();
    EXPECT_EQ(1, stack_calls) << "contended entry must capture before the lock is held";
    EXPECT_EQ(1, stacks->claimedForTest());
    int num_frames = 0;
    bool truncated = true;
    ASSERT_NE(nullptr, stacks->frames(heldLease(), num_frames, truncated));
    EXPECT_EQ(1, num_frames);
    EXPECT_FALSE(truncated);
    exitAfter(min_ticks);
    EXPECT_EQ(1, record_calls);
    EXPECT_EQ(1, stack_calls);
    EXPECT_EQ(0, stacks->claimedForTest());
    EXPECT_EQ(0u, heldLease());
}

TEST_F(MonitorEntryStackTest, ShortExitReleasesSlot) {
    enter();
    exitAfter(min_ticks - 1);
    EXPECT_EQ(0, record_calls);
    EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
    EXPECT_EQ(0, stacks->claimedForTest());
    EXPECT_EQ(0u, heldLease());
}

TEST_F(MonitorEntryStackTest, ExitWithoutOpenIntervalReleasesSlot) {
    enter();
    current->clearMonitorBlock();
    exitAfter(min_ticks);
    EXPECT_EQ(0, record_calls);
    EXPECT_EQ(0, stacks->claimedForTest());
}

TEST_F(MonitorEntryStackTest, UnclassifiedExitReleasesSlot) {
    enter();
    JNINativeInterface_ functions = jni_functions;
    functions.GetVersion = [](JNIEnv*) -> jint { return 0; };
    JNIEnv probe_jni{};
    probe_jni.functions = &functions;
    setMonitorTaskBlockTicksForTest(100 + min_ticks);
    MonitorContendedEntered(&jvmti, &probe_jni, testThread(), &monitor);
    EXPECT_EQ(0, stacks->claimedForTest());
    current->clearMonitorBlock();
}

TEST_F(MonitorEntryStackTest, DisabledRecordingExitReleasesSlot) {
    enter();
    ProfilerTestAccessor::setProducerState(profiler, false);
    exitAfter(min_ticks);
    EXPECT_EQ(0, record_calls);
    EXPECT_EQ(0, stacks->claimedForTest());
}

TEST_F(MonitorEntryStackTest, RejectedRecordReleasesSlot) {
    Profiler::setTaskBlockRecordOverrideForTest([](int, jthread, int, TaskBlockEvent*) {
        record_calls++;
        return Profiler::TaskBlockRecordResult::RECORD_FAILED;
    });
    enter();
    exitAfter(min_ticks);
    EXPECT_EQ(1, record_calls);
    EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
    EXPECT_EQ(0, stacks->claimedForTest());
}

TEST_F(MonitorEntryStackTest, UnconsumedLeaseIsReleasedByNextEntry) {
    // Models an exit callback that never ran, e.g. events disabled mid-block.
    u64 stale = stacks->claim(kDepth);
    ASSERT_NE(0u, stale);
    current->exchangeMonitorEntryStackLease(stale);
    enter();
    EXPECT_EQ(1, stack_calls);
    EXPECT_EQ(1, stacks->claimedForTest()) << "the stale lease must be released, not leaked";
    EXPECT_NE(stale, heldLease());
    exitAfter(min_ticks);
    EXPECT_EQ(0, stacks->claimedForTest());
}

TEST_F(MonitorEntryStackTest, ObjectWaitDoesNotCaptureAtEntry) {
    MonitorWait(&jvmti, &jni, testThread(), &monitor, 100);
    ASSERT_NE(0u, current->monitorBlockToken());
    EXPECT_EQ(0, stack_calls);
    EXPECT_EQ(0, stacks->claimedForTest());
    setMonitorTaskBlockTicksForTest(100 + min_ticks);
    MonitorWaited(&jvmti, &jni, testThread(), &monitor, JNI_FALSE);
    EXPECT_EQ(1, record_calls);
}

TEST_F(MonitorEntryStackTest, RotationSkipsEntryCaptureWithoutCountingADrop) {
    profiler->beginTaskBlockRotationForTest();
    MonitorContendedEnter(&jvmti, &jni, testThread(), &monitor);
    profiler->endTaskBlockRotationForTest();
    ASSERT_NE(0u, current->monitorBlockToken()) << "the interval is still owned";
    EXPECT_EQ(0, stack_calls);
    EXPECT_EQ(0, stacks->claimedForTest());
    EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
    exitAfter(min_ticks);
    EXPECT_EQ(1, record_calls);
}

TEST_F(MonitorEntryStackTest, FailedEntryCaptureLeavesNoLease) {
    jvmti_functions.GetStackTrace = [](jvmtiEnv*, jthread, jint, jint, jvmtiFrameInfo*,
                                       jint* count) -> jvmtiError {
        stack_calls++;
        *count = 0;
        return JVMTI_ERROR_NONE;
    };
    enter();
    EXPECT_EQ(1, stack_calls);
    EXPECT_EQ(0u, heldLease());
    EXPECT_EQ(0, stacks->claimedForTest());
    exitAfter(min_ticks);
    EXPECT_EQ(1, record_calls);
}

TEST_F(MonitorEntryStackTest, ReleasedStacksAreNotClaimedAfterStop) {
    stacks->release();
    enter();
    EXPECT_EQ(0, stack_calls) << "a late callback must find the storage unallocated";
    EXPECT_EQ(0u, heldLease());
    exitAfter(min_ticks);
    ASSERT_TRUE(stacks->allocate(kDepth));
}
