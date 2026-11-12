/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "guards.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "vmEntry.h"
#include "threadLocalData.inline.h"
#include "wallClockBlockTracker.h"

extern "C" {
jlong JNICALL Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(JNIEnv*, jclass, jint);
void JNICALL Java_com_datadoghq_profiler_JavaProfiler_blockExit0(JNIEnv*, jclass, jlong);
void JNICALL Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(JNIEnv*, jclass);
void JNICALL Java_com_datadoghq_profiler_JavaProfiler_parkExit0(JNIEnv*, jclass, jlong, jlong);
jlong JNICALL Java_com_datadoghq_profiler_JavaProfiler_beginTaskBlock0(JNIEnv*, jclass, jthread);
jboolean JNICALL Java_com_datadoghq_profiler_JavaProfiler_endTaskBlock0(
    JNIEnv*, jclass, jthread, jlong, jlong, jlong);
}

enum class RestartHook { BLOCK, PARK, TASK_BLOCK };

class ProfilerTestAccessor {
public:
    static State exchangeState(State state) {
        return Profiler::instance()->_state.exchange(state, std::memory_order_acq_rel);
    }
    static bool exchangeTaskBlockEnabled(bool enabled) {
        return Profiler::instance()->_task_block_enabled.exchange(enabled, std::memory_order_acq_rel);
    }
};

class VMTestAccessor {
public:
    static jvmtiEnv* exchangeJvmti(jvmtiEnv* env) {
        jvmtiEnv* previous = VM::_jvmti;
        VM::_jvmti = env;
        return previous;
    }
};

// The real JNI bodies do not use JNIEnv. Exercise their TLS, slot validation,
// admission, and exit paths on real native threads without bootstrapping a JVM.
class WallClockBlockRestartTest : public ::testing::TestWithParam<RestartHook> {
protected:
    void SetUp() override {
        registry = Profiler::instance()->threadFilter();
        tracker = Profiler::instance()->blockTracker();
        registry->init("", true);
        current = ProfiledThread::initCurrentThreadSignalSafe();
        ASSERT_NE(nullptr, current);
        current->setFilterSlotId(-1);
        if (GetParam() == RestartHook::TASK_BLOCK) {
            // Mock only JVM identity/classification. Admission, paired TLS
            // lifecycle and stop/start registry transitions remain production.
            functions.GetVersion = [](JNIEnv*) -> jint { return JNI_VERSION_1_8; };
            functions.IsSameObject = [](JNIEnv*, jobject a, jobject b) -> jboolean { return a == b; };
            functions.DeleteLocalRef = [](JNIEnv*, jobject) {};
            env.functions = &functions;
            jvmti_functions.GetCurrentThread = [](jvmtiEnv*, jthread* thread) -> jvmtiError {
                *thread = reinterpret_cast<jthread>(1);
                return JVMTI_ERROR_NONE;
            };
            jvmti.functions = &jvmti_functions;
            previous_jvmti = VMTestAccessor::exchangeJvmti(&jvmti);
            previous_state = ProfilerTestAccessor::exchangeState(RUNNING);
            previous_enabled = ProfilerTestAccessor::exchangeTaskBlockEnabled(true);
            initializeTaskBlockDurationThreshold();
        }
    }

    void TearDown() override {
        tracker->setBlockAdmissionHookForTest(nullptr, nullptr);
        Profiler::setTaskBlockActivityHookForTest(nullptr);
        registry->deactivateRecording();
        // release() also retires the identity while registry admission is closed.
        ProfiledThread::release();
        if (GetParam() == RestartHook::TASK_BLOCK) {
            ProfilerTestAccessor::exchangeTaskBlockEnabled(previous_enabled);
            ProfilerTestAccessor::exchangeState(previous_state);
            VMTestAccessor::exchangeJvmti(previous_jvmti);
        }
    }

    u64 enterHook() {
        if (GetParam() == RestartHook::TASK_BLOCK) {
            return Java_com_datadoghq_profiler_JavaProfiler_beginTaskBlock0(
                &env, nullptr, reinterpret_cast<jthread>(1));
        }
        if (GetParam() == RestartHook::BLOCK) {
            return static_cast<u64>(Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(
                nullptr, nullptr, static_cast<jint>(OSThreadState::SLEEPING)));
        }
        Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(nullptr, nullptr);
        return ProfiledThread::current()->snapshotForTest().park_block_token;
    }

    void exitHook(u64 token) {
        if (GetParam() == RestartHook::TASK_BLOCK) {
            Java_com_datadoghq_profiler_JavaProfiler_endTaskBlock0(
                &env, nullptr, reinterpret_cast<jthread>(1), token, 0, 0);
        } else if (GetParam() == RestartHook::BLOCK) {
            Java_com_datadoghq_profiler_JavaProfiler_blockExit0(
                nullptr, nullptr, static_cast<jlong>(token));
        } else {
            Java_com_datadoghq_profiler_JavaProfiler_parkExit0(nullptr, nullptr, 0, 0);
        }
    }

    OSThreadState hookState() const {
        return GetParam() == RestartHook::PARK
            ? OSThreadState::CONDVAR_WAIT : OSThreadState::SLEEPING;
    }

    BlockRunOwner hookOwner() const {
        return GetParam() == RestartHook::TASK_BLOCK ? BlockRunOwner::TASK_BLOCK : BlockRunOwner::JAVA;
    }

    struct AdmissionPause {
        std::mutex mutex;
        std::condition_variable changed;
        bool reached = false;
        bool resume = false;

        static void pause(void* arg) {
            auto* self = static_cast<AdmissionPause*>(arg);
            std::unique_lock<std::mutex> lock(self->mutex);
            self->reached = true;
            self->changed.notify_all();
            self->changed.wait(lock, [&] { return self->resume; });
        }
    };

    // release() blocks profiling signals; restore the test thread's mask after
    // cleanup so this fixture does not change later tests' signal environment.
    JNINativeInterface_ functions{};
    JNIEnv env{};
    jvmtiInterface_1_ jvmti_functions{};
    jvmtiEnv jvmti{};
    jvmtiEnv* previous_jvmti = nullptr;
    State previous_state = NEW;
    bool previous_enabled = false;
    SignalBlocker signal_blocker;
    ThreadFilter* registry = nullptr;
    WallClockBlockTracker* tracker = nullptr;
    ProfiledThread* current = nullptr;
};

TEST_P(WallClockBlockRestartTest, HookWithoutRestartHasNormalLifecycle) {
    u64 token = enterHook();
    ASSERT_NE(0u, token);
    auto* block = tracker->slotForId(current->filterSlotId());
    ASSERT_NE(nullptr, block);
    EXPECT_EQ(hookOwner(), block->activeBlockOwner());
    EXPECT_EQ(hookState(), block->activeBlockState());
    exitHook(token);
    EXPECT_EQ(BlockRunOwner::NONE, block->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block->activeBlockState());
}

TEST_P(WallClockBlockRestartTest, PausedHookDoesNotMutateReplacementAcrossRestart) {
    AdmissionPause pause;
    tracker->setBlockAdmissionHookForTest(AdmissionPause::pause, &pause);
    int old_slot = -1;
    std::thread worker([&] {
        auto* self = ProfiledThread::initCurrentThreadSignalSafe();
        ASSERT_NE(nullptr, self);
        old_slot = registry->registerThread(self->tid());
        self->setFilterSlotId(old_slot);
        u64 token = enterHook();
        exitHook(token);
        if (GetParam() == RestartHook::TASK_BLOCK) {
            EXPECT_EQ(0ULL, self->snapshotForTest().task_block_token)
                << "paired exit must consume a token even across restart";
        }
        registry->unregisterThread(self->filterSlotId(), self->tid());
        ProfiledThread::release();
    });

    bool reached;
    {
        std::unique_lock<std::mutex> lock(pause.mutex);
        reached = pause.changed.wait_for(lock, std::chrono::seconds(5),
                                         [&] { return pause.reached; });
    }
    int replacement_slot = -1;
    ThreadFilter::RecordingEpoch previous_epoch = registry->recordingEpoch();
    if (reached) {
        // These are the registry transitions used by Profiler::stop()/start().
        // The worker is still inside the real JNI call after slot validation.
        registry->deactivateRecording();
        registry->init("", true);
        replacement_slot = registry->registerThread(current->tid());
        current->setFilterSlotId(replacement_slot);
    }
    {
        std::lock_guard<std::mutex> lock(pause.mutex);
        pause.resume = true;
        pause.changed.notify_all();
    }
    worker.join();
    tracker->setBlockAdmissionHookForTest(nullptr, nullptr);

    ASSERT_TRUE(reached) << "JNI hook did not reach the admission barrier";
    ASSERT_GE(old_slot, 0);
    ASSERT_GE(replacement_slot, 0);
    ASSERT_NE(previous_epoch, registry->recordingEpoch());
    SCOPED_TRACE(::testing::Message() << "old slot=" << old_slot
                                    << ", replacement slot=" << replacement_slot);

    auto* identity = registry->activeSlotForId(replacement_slot, current->tid());
    auto* block = tracker->slotForId(replacement_slot);
    ASSERT_NE(nullptr, identity);
    ASSERT_NE(nullptr, block);
    EXPECT_EQ(BlockRunOwner::NONE, block->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block->activeBlockState());

    // Model only successful sample completion, as finishWallPrecheck() does.
    // Admission and the stale caller's exit above use the actual JNI bodies.
    if (block->activeBlockOwner() != BlockRunOwner::NONE) {
        block->markBlockGenerationSampled(block->blockGeneration());
    }
    ThreadEntry replacement{current->tid(), identity, replacement_slot,
                             identity->lifecycleGeneration(), identity->recordingEpoch()};
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(registry, replacement))
        << "A thread that never entered a block became suppressible";

    // A bogus active run must also not prevent the new owner arming its own run.
    u64 replacement_token = enterHook();
    EXPECT_NE(0u, replacement_token);
    exitHook(replacement_token);
}

INSTANTIATE_TEST_SUITE_P(JniHooks, WallClockBlockRestartTest,
                        ::testing::Values(RestartHook::BLOCK, RestartHook::PARK, RestartHook::TASK_BLOCK),
                        [](const ::testing::TestParamInfo<RestartHook>& info) {
                            switch (info.param) {
                                case RestartHook::BLOCK: return "Block";
                                case RestartHook::PARK: return "Park";
                                case RestartHook::TASK_BLOCK: return "TaskBlock";
                            }
                            return "Invalid";
                        });

TEST_P(WallClockBlockRestartTest, SurvivingOwnerRefreshesOnlyRecordingState) {
    u64 old_token = enterHook();
    ASSERT_NE(0u, old_token);
    int slot_id = current->filterSlotId();
    auto* identity = registry->slotForId(slot_id);
    auto* block = tracker->slotForId(slot_id);
    u64 generation = identity->lifecycleGeneration();
    u64 epoch = registry->recordingEpoch();
    block->markBlockGenerationSampled(block->blockGeneration());
    ThreadEntry stale{current->tid(), identity, slot_id, generation, epoch};
    ASSERT_TRUE(tracker->isOwnedBlockSuppressionCandidate(registry, stale));

    registry->deactivateRecording();
    registry->init("", true);
    ASSERT_EQ(identity, registry->lookupByTid(current->tid()));
    EXPECT_EQ(generation, identity->lifecycleGeneration());
    EXPECT_EQ(nullptr, registry->activeSlotForId(slot_id, current->tid()));
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(registry, stale));
    exitHook(old_token);

    u64 new_token = enterHook();
    EXPECT_NE(0u, new_token);
    EXPECT_NE(old_token, new_token);
    EXPECT_EQ(slot_id, current->filterSlotId());
    EXPECT_EQ(registry->recordingEpoch(), identity->recordingEpoch());
    EXPECT_EQ(0ULL, block->sampledBlockGeneration());
    EXPECT_EQ(hookState(), block->activeBlockState());
    exitHook(new_token);
}

TEST_P(WallClockBlockRestartTest, ThreadExitWhileStoppedRetiresIdentity) {
    AdmissionPause pause;
    // Make the caller register again rather than refresh a retained identity.
    registry->unregisterThreadByTid(current->tid());
    int worker_tid = -1;
    int worker_slot = -1;
    u64 worker_lifecycle_generation = 0;
    u64 token = 0;
    std::thread worker([&] {
        auto* self = ProfiledThread::initCurrentThreadSignalSafe();
        ASSERT_NE(nullptr, self);
        worker_tid = self->tid();
        token = enterHook();
        worker_slot = self->filterSlotId();
        worker_lifecycle_generation = registry->slotForId(worker_slot)->lifecycleGeneration();
        AdmissionPause::pause(&pause);
        // No ThreadEnd callback or explicit unregister: pthread teardown must
        // retire this identity while registry admission is disabled.
    });
    bool reached;
    {
        std::unique_lock<std::mutex> lock(pause.mutex);
        reached = pause.changed.wait_for(lock, std::chrono::seconds(5),
                                         [&] { return pause.reached; });
    }
    registry->deactivateRecording();
    {
        std::lock_guard<std::mutex> lock(pause.mutex);
        pause.resume = true;
        pause.changed.notify_all();
    }
    worker.join();
    ASSERT_TRUE(reached);
    ASSERT_NE(0u, token);
    EXPECT_EQ(nullptr, registry->lookupByTid(worker_tid));
    auto* retired_identity = registry->slotForId(worker_slot);
    ASSERT_NE(nullptr, retired_identity);
    EXPECT_EQ(-1, retired_identity->nativeTid());
    EXPECT_EQ(0u, retired_identity->recordingEpoch());
    auto* block = tracker->slotForId(worker_slot);
    ASSERT_NE(nullptr, block);
    EXPECT_EQ(BlockRunOwner::NONE, block->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block->activeBlockState());

    registry->init("", true);
    u64 new_token = enterHook();
    ASSERT_NE(0u, new_token);
    auto* new_identity = registry->activeSlotForId(current->filterSlotId(), current->tid());
    ASSERT_NE(nullptr, new_identity);
    EXPECT_EQ(current->tid(), new_identity->nativeTid());
    // popFromFreeList() starts at a shard selected by the calling thread's ID,
    // so the caller may receive another free slot. Lifecycle counters belong
    // to individual slots and can only be compared when the slot is reused.
    if (current->filterSlotId() == worker_slot) {
        EXPECT_GT(new_identity->lifecycleGeneration(), worker_lifecycle_generation);
    }
    auto* new_block = tracker->slotForId(current->filterSlotId());
    ASSERT_NE(nullptr, new_block);
    EXPECT_EQ(hookOwner(), new_block->activeBlockOwner());
    EXPECT_EQ(hookState(), new_block->activeBlockState());
    exitHook(new_token);
}

// The paired exit also has an admission boundary after its TLS token was
// consumed. Pause there while the stop/start registry transitions run.
class PairedTaskBlockRestartTest : public WallClockBlockRestartTest {
protected:
    inline static AdmissionPause* exit_pause = nullptr;
    static void pauseExit(Profiler::TaskBlockActivityStage stage) {
        if (stage == Profiler::TaskBlockActivityStage::BEFORE_RESERVATION) AdmissionPause::pause(exit_pause);
    }
};

TEST_P(PairedTaskBlockRestartTest, PausedEndCannotRecordOrMutateReplacementAcrossRestart) {
    AdmissionPause pause;
    exit_pause = &pause;
    Profiler* profiler = Profiler::instance();
    Profiler::setTaskBlockActivityHookForTest(pauseExit);
    long long dropped_before = Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION);
    bool recorded = true;
    std::thread worker([&] {
        auto* self = ProfiledThread::initCurrentThreadSignalSafe();
        ASSERT_NE(nullptr, self);
        u64 token = enterHook();
        EXPECT_NE(0ULL, token);
        recorded = Java_com_datadoghq_profiler_JavaProfiler_endTaskBlock0(
            &env, nullptr, reinterpret_cast<jthread>(1), token, 0, 0);
        EXPECT_EQ(0ULL, self->snapshotForTest().task_block_token);
        ProfiledThread::release();
    });
    bool reached;
    {
        std::unique_lock<std::mutex> lock(pause.mutex);
        reached = pause.changed.wait_for(lock, std::chrono::seconds(5), [&] { return pause.reached; });
    }
    EXPECT_TRUE(reached);
    bool drained = profiler->beginTaskBlockRotationForTest();
    EXPECT_TRUE(drained);
    registry->deactivateRecording();
    registry->init("", true);
    u64 replacement_token = enterHook();
    EXPECT_NE(0ULL, replacement_token);
    auto* replacement = tracker->slotForId(current->filterSlotId());
    {
        std::lock_guard<std::mutex> lock(pause.mutex);
        pause.resume = true;
        pause.changed.notify_all();
    }
    worker.join();
    Profiler::setTaskBlockActivityHookForTest(nullptr);
    exit_pause = nullptr;
    EXPECT_FALSE(recorded);
    EXPECT_EQ(dropped_before + 1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
    EXPECT_EQ(0, profiler->taskBlockInflightForTest());
    if (replacement != nullptr) {
        EXPECT_EQ(BlockRunOwner::TASK_BLOCK, replacement->activeBlockOwner());
        EXPECT_EQ(WallClockBlockTracker::tokenGeneration(replacement_token), replacement->blockGeneration());
    } else {
        ADD_FAILURE() << "replacement has no block slot";
    }
    profiler->endTaskBlockRotationForTest();
    exitHook(replacement_token);
}

INSTANTIATE_TEST_SUITE_P(PairedJniHooks, PairedTaskBlockRestartTest,
                        ::testing::Values(RestartHook::TASK_BLOCK));
