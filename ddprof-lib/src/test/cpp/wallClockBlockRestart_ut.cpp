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
#include "threadLocalData.inline.h"
#include "wallClockBlockTracker.h"

extern "C" {
jlong JNICALL Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(JNIEnv*, jclass, jint);
void JNICALL Java_com_datadoghq_profiler_JavaProfiler_blockExit0(JNIEnv*, jclass, jlong);
void JNICALL Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(JNIEnv*, jclass);
void JNICALL Java_com_datadoghq_profiler_JavaProfiler_parkExit0(JNIEnv*, jclass, jlong, jlong);
}

enum class RestartHook { BLOCK, PARK };

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
    }

    void TearDown() override {
        tracker->setBlockAdmissionHookForTest(nullptr, nullptr);
        registry->deactivateRecording();
        // release() also retires the identity while registry admission is closed.
        ProfiledThread::release();
    }

    u64 enterHook() {
        if (GetParam() == RestartHook::BLOCK) {
            return static_cast<u64>(Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(
                nullptr, nullptr, static_cast<jint>(OSThreadState::SLEEPING)));
        }
        Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(nullptr, nullptr);
        return ProfiledThread::current()->snapshotForTest().park_block_token;
    }

    void exitHook(u64 token) {
        if (GetParam() == RestartHook::BLOCK) {
            Java_com_datadoghq_profiler_JavaProfiler_blockExit0(
                nullptr, nullptr, static_cast<jlong>(token));
        } else {
            Java_com_datadoghq_profiler_JavaProfiler_parkExit0(nullptr, nullptr, 0, 0);
        }
    }

    OSThreadState hookState() const {
        return GetParam() == RestartHook::BLOCK
            ? OSThreadState::SLEEPING : OSThreadState::CONDVAR_WAIT;
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
    EXPECT_EQ(BlockRunOwner::JAVA, block->activeBlockOwner());
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
                        ::testing::Values(RestartHook::BLOCK, RestartHook::PARK),
                        [](const ::testing::TestParamInfo<RestartHook>& info) {
                            return info.param == RestartHook::BLOCK ? "Block" : "Park";
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
    int worker_tid = -1;
    int worker_slot = -1;
    u64 token = 0;
    std::thread worker([&] {
        auto* self = ProfiledThread::initCurrentThreadSignalSafe();
        ASSERT_NE(nullptr, self);
        worker_tid = self->tid();
        token = enterHook();
        worker_slot = self->filterSlotId();
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
    auto* block = tracker->slotForId(worker_slot);
    ASSERT_NE(nullptr, block);
    EXPECT_EQ(BlockRunOwner::NONE, block->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block->activeBlockState());

    registry->init("", true);
    u64 new_token = enterHook();
    ASSERT_NE(0u, new_token);
    EXPECT_NE(nullptr, registry->activeSlotForId(current->filterSlotId(), current->tid()));
    EXPECT_NE(token, new_token);
    exitHook(new_token);
}
