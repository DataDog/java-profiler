// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include "mallocTracer.h"
#include "threadExitRegistry.h"
#include "threadLocalData.inline.h"
#include "threadLocalDataPool.h"

static int acquisitions;
static int samples;
static MallocEvent recorded_event;
static int recorded_tid;

static void countAcquisition() { acquisitions++; }
static void recordSample(int tid, const MallocEvent& event) {
    samples++;
    recorded_event = event;
    recorded_tid = tid;
}

// Observe admission and the stack-capture boundary without requiring a JVM.
class MallocTracerTestAccess {
  public:
    MallocTracerTestAccess() {
        MallocTracer::_interval = 0;
        MallocTracer::_sample_count = 0;
        MallocTracer::beforeAcquireForTest = countAcquisition;
        MallocTracer::recordSampleForTest = recordSample;
        acquisitions = samples = 0;
        setRunning(true);
    }
    ~MallocTracerTestAccess() {
        setRunning(false);
        MallocTracer::beforeAcquireForTest = nullptr;
        MallocTracer::recordSampleForTest = nullptr;
    }
    MallocTracerTestAccess(const MallocTracerTestAccess&) = delete;
    MallocTracerTestAccess& operator=(const MallocTracerTestAccess&) = delete;
    static void setRunning(bool running) {
        __atomic_store_n(&MallocTracer::_running, running, __ATOMIC_RELEASE);
    }
    static u64 sampleCount() {
        return __atomic_load_n(&MallocTracer::_sample_count, __ATOMIC_ACQUIRE);
    }
};

struct ProfiledThreadOwner {
    ProfiledThreadOwner() { ProfiledThread::initCurrentThreadSignalSafe(); }
    ~ProfiledThreadOwner() {
        ProfiledThread::release();
        ThreadExitRegistry::clearCurrent();
    }
    ProfiledThreadOwner(const ProfiledThreadOwner&) = delete;
    ProfiledThreadOwner& operator=(const ProfiledThreadOwner&) = delete;
};

TEST(MallocTracerAdmissionTest, MarkedThreadWithLiveTlsRejectsTeardownAllocation) {
    std::thread worker([]() {
        ProfiledThreadOwner owner;
        ProfiledThread* tls = ProfiledThread::current();
        ASSERT_NE(nullptr, tls);
        MallocTracerTestAccess tracer;
        ThreadExitRegistry::markCurrent();
        ASSERT_TRUE(ThreadExitRegistry::contains(ThreadExitRegistry::currentId()));
        std::unique_ptr<char[]> allocation(new char[64]);
        MallocTracer::maybeRecord(allocation.get(), 64);
        EXPECT_EQ(tls, ProfiledThread::current());
        EXPECT_EQ(0, acquisitions);
        EXPECT_EQ(0, samples);
        EXPECT_EQ(0u, MallocTracerTestAccess::sampleCount());

        ThreadExitRegistry::clearCurrent();
        MallocTracer::maybeRecord(allocation.get(), 64);
        EXPECT_EQ(1, acquisitions);
        EXPECT_EQ(1, samples);
        EXPECT_EQ(1u, MallocTracerTestAccess::sampleCount());
        EXPECT_EQ(tls->tid(), recorded_tid);
        EXPECT_EQ(reinterpret_cast<uintptr_t>(allocation.get()), recorded_event._address);
        EXPECT_EQ(64u, recorded_event._size);
        EXPECT_EQ(1.0f, recorded_event._weight);
        EXPECT_NE(0u, recorded_event._start_time);
    });
    worker.join();
}

TEST(MallocTracerAdmissionTest, MarkedThreadWithoutTlsDoesNotAcquirePoolSlot) {
    ThreadLocalDataPool::initialize();
    std::thread worker([]() {
        ASSERT_EQ(nullptr, ProfiledThread::current());
        MallocTracerTestAccess tracer;
        ThreadExitRegistry::markCurrent();
        char allocation;
        MallocTracer::maybeRecord(&allocation, sizeof(allocation));
        EXPECT_EQ(nullptr, ProfiledThread::current());
        EXPECT_EQ(0, acquisitions);
        EXPECT_EQ(0, samples);
        ThreadExitRegistry::clearCurrent();
        ProfiledThreadOwner cleanup;
    });
    worker.join();
}

TEST(MallocTracerAdmissionTest, InactiveNullAndEmptyAllocationsDoNotAcquireTls) {
    std::thread worker([]() {
        ProfiledThreadOwner owner;
        MallocTracerTestAccess tracer;
        char allocation;
        MallocTracer::maybeRecord(nullptr, 1);
        MallocTracer::maybeRecord(&allocation, 0);
        MallocTracerTestAccess::setRunning(false);
        MallocTracer::maybeRecord(&allocation, 1);
        EXPECT_EQ(0, acquisitions);
        EXPECT_EQ(0, samples);
    });
    worker.join();
}
