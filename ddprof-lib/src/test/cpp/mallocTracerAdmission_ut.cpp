// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>
#include <memory>
#include <signal.h>
#include <thread>
#include "counters.h"
#include "guards.h"
#include "mallocTracer.h"
#include "threadExitRegistry.h"
#include "threadLocalData.inline.h"
#include "threadLocalDataPool.h"

static int exit_checks;
static int acquisitions;
static int samples;
static MallocEvent recorded_event;
static int recorded_tid;

static void countExitCheck() { exit_checks++; }
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
        MallocTracer::beforeExitCheckForTest = countExitCheck;
        MallocTracer::beforeAcquireForTest = countAcquisition;
        MallocTracer::recordSampleForTest = recordSample;
        exit_checks = acquisitions = samples = 0;
        setRunning(true);
    }
    ~MallocTracerTestAccess() {
        setRunning(false);
        MallocTracer::_interval = 0;
        MallocTracer::_bytes_until_sample = 0;
        MallocTracer::beforeExitCheckForTest = nullptr;
        MallocTracer::beforeAcquireForTest = nullptr;
        MallocTracer::recordSampleForTest = nullptr;
    }
    MallocTracerTestAccess(const MallocTracerTestAccess&) = delete;
    MallocTracerTestAccess& operator=(const MallocTracerTestAccess&) = delete;
    static void setRunning(bool running) {
        __atomic_store_n(&MallocTracer::_running, running, __ATOMIC_RELEASE);
    }
    // Interval > 1 enables Poisson sampling; the next sample is due after `bytes_until`.
    static void setSampling(u64 interval, u64 bytes_until) {
        MallocTracer::_interval = interval;
        MallocTracer::_bytes_until_sample = bytes_until;
    }
    static u64 bytesUntilSample() {
        return __atomic_load_n(&MallocTracer::_bytes_until_sample, __ATOMIC_ACQUIRE);
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

static void initializePoolOnce() {
    static const bool initialized = (ThreadLocalDataPool::initialize(), true);
    (void)initialized;
}

static void unblockProfilingSignals() {
    sigset_t profiling;
    sigemptyset(&profiling);
    sigaddset(&profiling, SIGPROF);
    sigaddset(&profiling, SIGVTALRM);
    ASSERT_EQ(0, pthread_sigmask(SIG_UNBLOCK, &profiling, nullptr));
}

TEST(MallocTracerAdmissionTest, MarkedThreadWithLiveTlsRejectsTeardownAllocation) {
    std::thread worker([]() {
        ProfiledThreadOwner owner;
        ProfiledThread* tls = ProfiledThread::current();
        ASSERT_NE(nullptr, tls);
        // Live TLS alone must identify the exiting thread.
        unblockProfilingSignals();
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

// Mirrors the mark sites: block profiling signals, mark, then release TLS.
TEST(MallocTracerAdmissionTest, ExitingThreadWithoutTlsDoesNotAcquirePoolSlot) {
    initializePoolOnce();
    std::thread worker([]() {
        ASSERT_EQ(nullptr, ProfiledThread::current());
        MallocTracerTestAccess tracer;
        blockProfilingForExit();
        ThreadExitRegistry::markCurrent();
        char allocation;
        MallocTracer::maybeRecord(&allocation, sizeof(allocation));
        EXPECT_EQ(nullptr, ProfiledThread::current());
        EXPECT_EQ(0, acquisitions);
        EXPECT_EQ(0, samples);
        EXPECT_TRUE(ThreadExitRegistry::contains(ThreadExitRegistry::currentId()));
        ThreadExitRegistry::clearCurrent();
    });
    worker.join();
}

// A stale mark from an earlier thread with the same tid: no TLS, signals unblocked.
TEST(MallocTracerAdmissionTest, ReusedIdentityClearsStaleMarkAndSamples) {
    initializePoolOnce();
    std::thread worker([]() {
        ASSERT_EQ(nullptr, ProfiledThread::current());
        unblockProfilingSignals();
        MallocTracerTestAccess tracer;
        ThreadExitRegistry::markCurrent();
        long long before = Counters::getCounter(MALLOC_SAMPLES_DROPPED);
        char allocation;
        MallocTracer::maybeRecord(&allocation, sizeof(allocation));
        EXPECT_FALSE(ThreadExitRegistry::contains(ThreadExitRegistry::currentId()));
        EXPECT_EQ(1, acquisitions);
        EXPECT_EQ(1, samples);
        EXPECT_EQ(before, Counters::getCounter(MALLOC_SAMPLES_DROPPED));
        ASSERT_NE(nullptr, ProfiledThread::current());
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

TEST(MallocTracerAdmissionTest, UnsampledAllocationSkipsExitCheckAndTls) {
    std::thread worker([]() {
        ProfiledThreadOwner owner;
        MallocTracerTestAccess tracer;
        MallocTracerTestAccess::setSampling(1 << 20, 1000);
        char allocation[64];
        MallocTracer::maybeRecord(allocation, 64);
        EXPECT_EQ(936u, MallocTracerTestAccess::bytesUntilSample());
        EXPECT_EQ(0, exit_checks);
        EXPECT_EQ(0, acquisitions);
        EXPECT_EQ(0, samples);

        // Crossing the countdown samples the allocation, which then pays the exit check.
        MallocTracer::maybeRecord(allocation, 936);
        EXPECT_EQ(1, exit_checks);
        EXPECT_EQ(1, acquisitions);
        EXPECT_EQ(1, samples);
    });
    worker.join();
}

TEST(MallocTracerAdmissionTest, SampledAllocationOnMarkedThreadIsCountedAsDropped) {
    std::thread worker([]() {
        ProfiledThreadOwner owner;
        MallocTracerTestAccess tracer;
        ThreadExitRegistry::markCurrent();
        long long before = Counters::getCounter(MALLOC_SAMPLES_DROPPED);
        char allocation;
        MallocTracer::maybeRecord(&allocation, 1);
        EXPECT_EQ(1, exit_checks);
        EXPECT_EQ(0, acquisitions);
        EXPECT_EQ(0, samples);
        EXPECT_EQ(before + 1, Counters::getCounter(MALLOC_SAMPLES_DROPPED));
    });
    worker.join();
}

TEST(MallocTracerAdmissionTest, SampledReentrantAllocationIsCountedAsDropped) {
    std::thread worker([]() {
        ProfiledThreadOwner owner;
        MallocTracerTestAccess tracer;
        CriticalSection outer(ProfiledThread::current());
        ASSERT_TRUE(outer.entered());
        long long before = Counters::getCounter(MALLOC_SAMPLES_DROPPED);
        char allocation;
        MallocTracer::maybeRecord(&allocation, 1);
        EXPECT_EQ(1, acquisitions);
        EXPECT_EQ(0, samples);
        EXPECT_EQ(before + 1, Counters::getCounter(MALLOC_SAMPLES_DROPPED));
    });
    worker.join();
}

TEST(MallocTracerAdmissionTest, ExitCheckClearsMarkOfReusedIdentity) {
    std::thread worker([]() {
        ASSERT_EQ(nullptr, ProfiledThread::current());
        unblockProfilingSignals();
        ThreadExitRegistry::markCurrent();
        EXPECT_FALSE(ThreadExitRegistry::isCurrentExiting());
        EXPECT_FALSE(ThreadExitRegistry::contains(ThreadExitRegistry::currentId()));
        EXPECT_EQ(nullptr, ProfiledThread::current());
    });
    worker.join();
}
