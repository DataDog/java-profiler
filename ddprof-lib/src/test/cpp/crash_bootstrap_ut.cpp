// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>
#include "guards.h"
#include "profiler.h"
#include "safeAccess.h"
#include "threadLocalData.inline.h"
#include "threadExitRegistry.h"
#include "os.h"
#include "wallClock.h"
#include <sys/syscall.h>
#include <pthread.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

extern void wakeupHandlerForTest(int signo);

namespace {
static int entry_pipe;
static volatile sig_atomic_t entries;
static void* poison;
static uintptr_t stack_bottom;
static volatile sig_atomic_t observed_mask;
static volatile sig_atomic_t nested_depth;

static void faultInBootstrap() {
    char entry = 'E';
    if (write(entry_pipe, &entry, 1) != 1) _exit(91);
    // Bound the unfenced regression before it exhausts the child's stack.
    if (++entries == 3) _exit(93);
    *static_cast<volatile char*>(poison) = 1;
}

static void observeMask() {
    sigset_t mask;
    if (sigprocmask(SIG_BLOCK, nullptr, &mask) != 0) _exit(94);
    observed_mask = sigismember(&mask, SIGSEGV) && sigismember(&mask, SIGBUS) &&
                    sigismember(&mask, SIGPROF) && sigismember(&mask, SIGVTALRM);
}

static void countBootstrap() {
    ++entries;
}

// Observes a bootstrap without faulting: the parent counts handler entries
// on a thread whose handler must run to completion and return.
static void markBootstrap() {
    char entry = 'E';
    if (write(entry_pipe, &entry, 1) != 1) _exit(90);
}

static void installHandlers() {
    struct sigaction action = {};
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
    action.sa_sigaction = Profiler::segvHandler;
    if (sigaction(SIGSEGV, &action, nullptr) != 0) _exit(95);
    action.sa_sigaction = Profiler::busHandler;
    if (sigaction(SIGBUS, &action, nullptr) != 0) _exit(96);
}

// Keep a measured 16 KiB for kernel delivery and the fenced handler bootstrap.
static NOINLINE void descendStack() {
    volatile char padding[512];
    padding[0] = 1;
    if (reinterpret_cast<uintptr_t>(&padding[0]) > stack_bottom + 16384) {
        descendStack();
    } else {
        char reached = 'S';
        if (write(entry_pipe, &reached, 1) != 1) _exit(97);
        raise(SIGBUS);
    }
    if (padding[0] != 1) _exit(98);
}

static void* smallStackThread(void*) {
    ProfiledThread::initCurrentThread();
    descendStack();
    return nullptr;
}

static void runFaultChild(int signal, bool small_stack) {
    struct rlimit no_core = {0, 0};
    setrlimit(RLIMIT_CORE, &no_core);
    alarm(5);
    entries = 0;
    ProfiledThread::initCurrentThread();
    installHandlers();
    poison = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (poison == MAP_FAILED) _exit(99);
    SignalHandlerScope::bootstrapHookForTest = faultInBootstrap;
    if (small_stack) {
        constexpr size_t stack_size = 128 * 1024;
        void* stack = mmap(nullptr, stack_size, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANON, -1, 0);
        if (stack == MAP_FAILED) _exit(100);
        if (mprotect(stack, 4096, PROT_NONE) != 0) _exit(107);
        stack_bottom = reinterpret_cast<uintptr_t>(stack) + 4096;
        pthread_attr_t attr;
        pthread_t thread;
        if (pthread_attr_init(&attr) != 0 ||
            pthread_attr_setstack(&attr, stack, stack_size) != 0 ||
            pthread_create(&thread, &attr, smallStackThread, nullptr) != 0) _exit(101);
        pthread_join(thread, nullptr);
    } else {
        raise(signal);
    }
    _exit(102);
}

static void expectBoundedFault(int signal, bool small_stack = false) {
    int fds[2];
    ASSERT_EQ(0, pipe(fds));
    pid_t child = fork();
    ASSERT_GE(child, 0);
    if (child == 0) {
        close(fds[0]);
        entry_pipe = fds[1];
        runFaultChild(signal, small_stack);
    }
    close(fds[1]);
    char events[16];
    int count = 0;
    ssize_t size;
    while ((size = read(fds[0], events + count, sizeof(events) - count)) > 0) count += size;
    close(fds[0]);
    int status = 0;
    ASSERT_EQ(child, waitpid(child, &status, 0));
    int entry_count = 0;
    int stack_markers = 0;
    for (int i = 0; i < count; ++i) {
        entry_count += events[i] == 'E';
        stack_markers += events[i] == 'S';
    }
    EXPECT_EQ(small_stack ? 1 : 0, stack_markers);
    EXPECT_EQ(1, entry_count) << "bootstrap must not re-enter";
    ASSERT_TRUE(WIFSIGNALED(status)) << "child status=" << status;
    EXPECT_TRUE(WTERMSIG(status) == SIGSEGV || WTERMSIG(status) == SIGBUS);
}

static void wallHandler(int) {
    SIGNAL_HANDLER_GUARD_OR_DROP();
    nested_depth = getInSignalDepth();
}

static void cpuHandler(int) {
    SIGNAL_HANDLER_GUARD_OR_DROP();
    raise(SIGVTALRM);
}
}

#ifdef __linux__
TEST(CrashBootstrapTest, PrefixFaultDoesNotReEnterSegvHandler) {
    expectBoundedFault(SIGSEGV);
}

TEST(CrashBootstrapTest, PrefixFaultDoesNotReEnterBusHandler) {
    expectBoundedFault(SIGBUS);
}
#else
// The kernel-armed fence is Linux-only: on macOS a blocked synchronous fault
// stays pending and the thread spins on the faulting instruction, so the fence
// is compiled to a no-op there (see CrashBootstrapFence in guards.h).
TEST(CrashBootstrapTest, PrefixFaultDoesNotReEnterSegvHandler) {
    GTEST_SKIP() << "CrashBootstrapFence arms on Linux only";
}
TEST(CrashBootstrapTest, PrefixFaultDoesNotReEnterBusHandler) {
    GTEST_SKIP() << "CrashBootstrapFence arms on Linux only";
}
#endif

#ifdef __linux__
TEST(CrashBootstrapTest, CrashBootstrapFenceHoldsMaskDuringPrefix) {
    EXPECT_EXIT({
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        sigset_t empty;
        sigemptyset(&empty);
        if (sigprocmask(SIG_SETMASK, &empty, nullptr) != 0) _exit(120);
        SignalHandlerScope::bootstrapHookForTest = observeMask;
        raise(SIGBUS);
        sigset_t after;
        sigprocmask(SIG_BLOCK, nullptr, &after);
        _exit(observed_mask == 1 && !sigismember(&after, SIGSEGV) &&
              !sigismember(&after, SIGBUS) && !sigismember(&after, SIGPROF) &&
              !sigismember(&after, SIGVTALRM) && getInSignalDepth() == 0 &&
              ProfiledThread::current()->snapshotForTest().crash_depth == 0 ? 0 : 103);
    }, ::testing::ExitedWithCode(0), "");
}

#else
TEST(CrashBootstrapTest, CrashBootstrapFenceHoldsMaskDuringPrefix) {
    GTEST_SKIP() << "CrashBootstrapFence arms on Linux only";
}
#endif

TEST(CrashBootstrapTest, FenceIsDisarmedBeforeSafefetchRecovery) {
    EXPECT_EXIT({
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        void* page = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (page == MAP_FAILED) _exit(104);
        ProfiledThread* pt = ProfiledThread::current();
        // Recovery must bypass admission rejection even at the nesting limit.
        while (pt->enterCrashHandler()) {}
        u32 saved_depth = pt->snapshotForTest().crash_depth;
        int64_t result = SafeAccess::safeFetch64(static_cast<int64_t*>(page), -42);
        _exit(result == -42 && getInSignalDepth() == 0 &&
              pt->snapshotForTest().crash_depth == saved_depth ? 0 : 105);
    }, ::testing::ExitedWithCode(0), "");
}

// TSan's sigaction_impl forces sigfillset on handler masks. The three TSan-gated
// tests require user-mask semantics for nested delivery or post-disarm recovery.
TEST(CrashBootstrapTest, LegitimateNestingUnchangedAfterFence) {
#if defined(TSAN_ENABLED)
    GTEST_SKIP() << "TSan's sigaction interceptor forces sigfillset, preventing nested CPU/wall delivery";
#else
    EXPECT_EXIT({
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        raise(SIGBUS);
        struct sigaction action = {};
        sigemptyset(&action.sa_mask);
        action.sa_handler = cpuHandler;
        sigaction(SIGPROF, &action, nullptr);
        action.sa_handler = wallHandler;
        sigaction(SIGVTALRM, &action, nullptr);
        raise(SIGPROF);
        _exit(nested_depth == 2 && getInSignalDepth() == 0 ? 0 : 106);
    }, ::testing::ExitedWithCode(0), "");
#endif
}

TEST(CrashBootstrapTest, WakeupHandlerPerformsNoBookkeeping) {
    ProfiledThread::initCurrentThread();
    entries = 0;
    SignalHandlerScope::bootstrapHookForTest = countBootstrap;
    wakeupHandlerForTest(SIGIO);
    SignalHandlerScope::bootstrapHookForTest = nullptr;
    EXPECT_EQ(0, entries) << "wakeup must not bootstrap TLS";
    EXPECT_EQ(0, getInSignalDepth());
    ProfiledThread::release();
}

#ifdef __linux__
TEST(CrashBootstrapTest, StackNearExhaustionEntry) {
    expectBoundedFault(SIGBUS, true);
}
#else
TEST(CrashBootstrapTest, StackNearExhaustionEntry) {
    GTEST_SKIP() << "CrashBootstrapFence arms on Linux only";
}
#endif

namespace {
static void expectExitingThreadFault() {
    int fds[2];
    ASSERT_EQ(0, pipe(fds));
    pid_t child = fork();
    ASSERT_GE(child, 0);
    if (child == 0) {
        close(fds[0]);
        entry_pipe = fds[1];
        entries = 0;
        struct rlimit no_core = {0, 0};
        setrlimit(RLIMIT_CORE, &no_core);
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        SignalHandlerScope::bootstrapHookForTest = markBootstrap;
        ThreadExitRegistry::markCurrent();
        raise(SIGSEGV);
        SignalHandlerScope::bootstrapHookForTest = nullptr;
        _exit(102);
    }
    close(fds[1]);
    char events[16];
    int count = 0;
    ssize_t size;
    while ((size = read(fds[0], events + count, sizeof(events) - count)) > 0) count += size;
    close(fds[0]);
    int status = 0;
    ASSERT_EQ(child, waitpid(child, &status, 0));
    int entry_count = 0;
    for (int i = 0; i < count; ++i) entry_count += events[i] == 'E';
    EXPECT_EQ(0, entry_count) << "exiting thread must not bootstrap TLS";
    ASSERT_TRUE(WIFSIGNALED(status)) << "child status=" << status;
    EXPECT_EQ(SIGSEGV, WTERMSIG(status));
}

static void expectLiveThreadBootstraps() {
    int fds[2];
    ASSERT_EQ(0, pipe(fds));
    pid_t child = fork();
    ASSERT_GE(child, 0);
    if (child == 0) {
        close(fds[0]);
        entry_pipe = fds[1];
        entries = 0;
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        SignalHandlerScope::bootstrapHookForTest = markBootstrap;
        raise(SIGSEGV);
        SignalHandlerScope::bootstrapHookForTest = nullptr;
        _exit(0);
    }
    close(fds[1]);
    char events[16];
    int count = 0;
    ssize_t size;
    while ((size = read(fds[0], events + count, sizeof(events) - count)) > 0) count += size;
    close(fds[0]);
    int status = 0;
    ASSERT_EQ(child, waitpid(child, &status, 0));
    int entry_count = 0;
    for (int i = 0; i < count; ++i) entry_count += events[i] == 'E';
    EXPECT_EQ(1, entry_count) << "live thread must bootstrap normally";
    ASSERT_TRUE(WIFEXITED(status)) << "child status=" << status;
    EXPECT_EQ(0, WEXITSTATUS(status));
}

struct TidBox {
    uint64_t tid;
};

static void* registryThread(void* arg) {
    ProfiledThread::initCurrentThread();
    static_cast<TidBox*>(arg)->tid = ThreadExitRegistry::currentId();
    return nullptr;
}
}

TEST(CrashBootstrapTest, ThreadExitRegistrySkipsBootstrapOnExitingThread) {
    expectExitingThreadFault();
}

TEST(CrashBootstrapTest, ThreadExitRegistryLeavesLiveThreadBootstrap) {
    expectLiveThreadBootstraps();
}

TEST(CrashBootstrapTest, ThreadExitRegistryLifecycle) {
    uint64_t tid = ThreadExitRegistry::currentId();
    ThreadExitRegistry::markCurrent();
    EXPECT_TRUE(ThreadExitRegistry::contains(tid));
    // Registering a reused tid must clear the stale mark.
    ProfiledThread::initCurrentThread();
    EXPECT_FALSE(ThreadExitRegistry::contains(tid));
    ProfiledThread::release();

    // Thread exit marks the tid again: the ProfiledThread TSD destructor
    // (freeValue) marks before releasing the TLS value.
    TidBox box = {0};
    pthread_t thread;
    ASSERT_EQ(0, pthread_create(&thread, nullptr, registryThread, &box));
    ASSERT_EQ(0, pthread_join(thread, nullptr));
    EXPECT_NE(0, box.tid);
    EXPECT_TRUE(ThreadExitRegistry::contains(box.tid));
    ThreadExitRegistry::clear(box.tid);
    EXPECT_FALSE(ThreadExitRegistry::contains(box.tid));
}

namespace {
constexpr uint64_t collision_tid = 1701;
static void installReplacement() {
    ThreadExitRegistry::beforeClearForTest = nullptr;
    ThreadExitRegistry::markForTest(collision_tid + 64 * 4096);
}

static volatile sig_atomic_t interrupting_signal;
static volatile sig_atomic_t prefix_completed;
static volatile sig_atomic_t profiling_recovered;
static void faultableProfilingHandler(int) {
    SIGNAL_HANDLER_GUARD_OR_DROP();
    CriticalSection cs(SIGNAL_HANDLER_CURRENT_THREAD());
    if (!cs.entered()) _exit(110);
    if (SafeAccess::safeFetch64(static_cast<int64_t*>(poison), -43) != -43) _exit(111);
    profiling_recovered = 1;
    if (!prefix_completed) _exit(112);
}
static void interruptPrefix() {
    SignalHandlerScope::bootstrapHookForTest = nullptr;
    raise(interrupting_signal);
    prefix_completed = 1;
}
}

TEST(CrashBootstrapTest, RegistryCollisionChainSurvivesClear) {
    EXPECT_EXIT({
        ThreadExitRegistry::resetForTest();
        ThreadExitRegistry::markForTest(collision_tid);
        ThreadExitRegistry::markForTest(collision_tid + 4096);
        ThreadExitRegistry::clear(collision_tid);
        if (!ThreadExitRegistry::contains(collision_tid + 4096)) _exit(113);
        ThreadExitRegistry::markForTest(collision_tid + 4096);
        ThreadExitRegistry::clear(collision_tid + 4096);
        _exit(!ThreadExitRegistry::contains(collision_tid + 4096) ? 0 : 114);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(CrashBootstrapTest, RegistryClearPreservesConcurrentReplacement) {
    EXPECT_EXIT({
        ThreadExitRegistry::resetForTest();
        for (int i = 0; i < 64; ++i) ThreadExitRegistry::markForTest(collision_tid + i * 4096);
        ThreadExitRegistry::beforeClearForTest = installReplacement;
        ThreadExitRegistry::clear(collision_tid);
        _exit(ThreadExitRegistry::contains(collision_tid + 64 * 4096) ? 0 : 115);
    }, ::testing::ExitedWithCode(0), "");
}

// The 64th probe position is searched by contains(); its 63 predecessors survive.
TEST(CrashBootstrapTest, RegistryContainsFindsMarkAtLastProbe) {
    EXPECT_EXIT({
        ThreadExitRegistry::resetForTest();
        for (int i = 0; i < 63; ++i) ThreadExitRegistry::markForTest(collision_tid + i * 4096);
        ThreadExitRegistry::markForTest(collision_tid + 63 * 4096);
        for (int i = 0; i < 63; ++i) {
            if (!ThreadExitRegistry::contains(collision_tid + i * 4096)) _exit(116);
        }
        _exit(ThreadExitRegistry::contains(collision_tid + 63 * 4096) ? 0 : 117);
    }, ::testing::ExitedWithCode(0), "");
}

// The 64th probe position is searched by clear(); its 63 predecessors survive.
TEST(CrashBootstrapTest, RegistryClearRemovesMarkAtLastProbe) {
    EXPECT_EXIT({
        ThreadExitRegistry::resetForTest();
        for (int i = 0; i < 64; ++i) ThreadExitRegistry::markForTest(collision_tid + i * 4096);
        ThreadExitRegistry::clear(collision_tid + 63 * 4096);
        if (ThreadExitRegistry::contains(collision_tid + 63 * 4096)) _exit(118);
        for (int i = 0; i < 63; ++i) {
            if (!ThreadExitRegistry::contains(collision_tid + i * 4096)) _exit(119);
        }
        _exit(0);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(CrashBootstrapTest, RegistryIdentityUsesRawSyscall) {
#ifdef __linux__
    uint64_t raw_id = syscall(SYS_gettid);
#else
    uint64_t raw_id = 0;
    ASSERT_EQ(0, pthread_threadid_np(nullptr, &raw_id));
#endif
    ASSERT_NE(0u, raw_id);
    EXPECT_EQ(raw_id, ThreadExitRegistry::currentId());
    ThreadExitRegistry::markCurrent();
    EXPECT_TRUE(ThreadExitRegistry::contains(raw_id));
    ThreadExitRegistry::clearCurrent();
    EXPECT_FALSE(ThreadExitRegistry::contains(raw_id));
}

TEST(CrashBootstrapTest, RegistryKeepsFullWidthIdentitiesDistinct) {
    EXPECT_EXIT({
        ThreadExitRegistry::resetForTest();
        uint64_t high_tid = (1ull << 40) | collision_tid;
        ThreadExitRegistry::markForTest(collision_tid);
        ThreadExitRegistry::markForTest(high_tid);
        ThreadExitRegistry::clear(collision_tid);
        _exit(ThreadExitRegistry::contains(high_tid) &&
              !ThreadExitRegistry::contains(collision_tid) ? 0 : 140);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(CrashBootstrapTest, ProfilingInterruptionOfFenceRecoversAccess) {
#if defined(TSAN_ENABLED)
    GTEST_SKIP() << "TSan's sigaction interceptor forces sigfillset, blocking nested SafeFetch recovery signals";
#elif defined(__linux__)
    for (int profiling_signal : {SIGPROF, SIGVTALRM}) {
      SCOPED_TRACE(profiling_signal);
      EXPECT_EXIT({
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        poison = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (poison == MAP_FAILED) _exit(116);
        struct sigaction action = {};
        sigemptyset(&action.sa_mask);
        action.sa_handler = faultableProfilingHandler;
        if (sigaction(profiling_signal, &action, nullptr) != 0) _exit(117);
        sigset_t profiling;
        sigemptyset(&profiling);
        sigaddset(&profiling, SIGPROF);
        sigaddset(&profiling, SIGVTALRM);
        if (sigprocmask(SIG_UNBLOCK, &profiling, nullptr) != 0) _exit(119);
        interrupting_signal = profiling_signal;
        prefix_completed = profiling_recovered = 0;
        SignalHandlerScope::bootstrapHookForTest = interruptPrefix;
        raise(SIGBUS);
        _exit(profiling_recovered == 1 && getInSignalDepth() == 0 &&
              ProfiledThread::current()->snapshotForTest().crash_depth == 0 ? 0 : 118);
      }, ::testing::ExitedWithCode(0), "");
    }
#else
    GTEST_SKIP() << "CrashBootstrapFence arms on Linux only";
#endif
}

namespace {
static volatile sig_atomic_t nested_recovered;
static void recoverDuringActiveCrashHandler() {
    Profiler::crashHandlerAdmittedForTest = nullptr;
    ProfiledThread* pt = ProfiledThread::current();
    if (pt->snapshotForTest().crash_depth != 1 || getInSignalDepth() != 1) _exit(121);
    sigset_t mask;
    if (sigprocmask(SIG_BLOCK, nullptr, &mask) != 0 ||
        sigismember(&mask, SIGSEGV) || sigismember(&mask, SIGBUS)) _exit(122);
    if (SafeAccess::safeFetch64(static_cast<int64_t*>(poison), -44) != -44) _exit(123);
    if (pt->snapshotForTest().crash_depth != 1 || getInSignalDepth() != 1) _exit(124);
    nested_recovered = 1;
}

static void requireEarlyMark() {
    if (!ThreadExitRegistry::contains(ThreadExitRegistry::currentId())) _exit(125);
    ++entries;
}
static void observeJvmtiEarlyMark() {
    requireEarlyMark();
    _exit(entries == 1 ? 0 : 126);
}

class ExitingWallClockForTest : public BaseWallClock {
    void timerLoop() override {
        ProfiledThread::initCurrentThread();
        if (ThreadExitRegistry::contains(ThreadExitRegistry::currentId())) _exit(127);
    }
public:
    const char* name() override { return "ExitingWallClockForTest"; }
    static void* run(void* clock) { return threadEntry(clock); }
};

#ifdef __linux__
static void* wrappedRoutine(void* mode) {
    if (ThreadExitRegistry::contains(ThreadExitRegistry::currentId())) _exit(128);
    int exit_mode = *static_cast<int*>(mode);
    if (exit_mode == 1) pthread_exit(nullptr);
    if (exit_mode == 2) {
        if (pthread_cancel(pthread_self()) != 0) _exit(138);
        pthread_testcancel();
        _exit(139);
    }
    return nullptr;
}
#endif
}

TEST(CrashBootstrapTest, SafefetchNestedDuringActiveCrashHandlerBalancesAdmission) {
#if defined(TSAN_ENABLED)
    GTEST_SKIP() << "TSan's sigaction interceptor forces sigfillset, conflicting with unblocked fault masks after disarm";
#else
    EXPECT_EXIT({
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        poison = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (poison == MAP_FAILED) _exit(129);
        nested_recovered = 0;
        Profiler::crashHandlerAdmittedForTest = recoverDuringActiveCrashHandler;
        raise(SIGBUS);
        if (nested_recovered != 1 || ProfiledThread::current()->snapshotForTest().crash_depth != 0 ||
            getInSignalDepth() != 0) _exit(130);
        if (SafeAccess::safeFetch64(static_cast<int64_t*>(poison), -45) != -45) _exit(131);
        _exit(ProfiledThread::current()->snapshotForTest().crash_depth == 0 &&
              getInSignalDepth() == 0 ? 0 : 132);
    }, ::testing::ExitedWithCode(0), "");
#endif
}

TEST(CrashBootstrapTest, JvmtiMarksBeforeTeardown) {
    EXPECT_EXIT({
        alarm(5);
        ProfiledThread::initCurrentThread();
        entries = 0;
        Profiler::threadEndMarkedForTest = observeJvmtiEarlyMark;
        Profiler::instance()->onThreadEndForTest();
        _exit(133);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(CrashBootstrapTest, EngineMarksBeforeTsdTeardown) {
    EXPECT_EXIT({
        alarm(5);
        entries = 0;
        ProfiledThread::beforeFreeValueForTest = requireEarlyMark;
        ExitingWallClockForTest clock;
        pthread_t thread;
        if (pthread_create(&thread, nullptr, ExitingWallClockForTest::run, &clock) != 0 ||
            pthread_join(thread, nullptr) != 0) _exit(134);
        _exit(entries == 1 ? 0 : 135);
    }, ::testing::ExitedWithCode(0), "");
}

#ifdef __linux__
extern int pthread_create_with_cleanup_unregister_for_test(pthread_t*, void* (*)(void*), void*);
TEST(CrashBootstrapTest, WrapperMarksBeforeTlsTeardown) {
    for (int mode : {0, 1, 2}) {
      SCOPED_TRACE(mode);
      EXPECT_EXIT({
        alarm(5);
        entries = 0;
        ProfiledThread::beforeFreeValueForTest = requireEarlyMark;
        pthread_t thread;
        if (pthread_create_with_cleanup_unregister_for_test(&thread, wrappedRoutine, &mode) != 0 ||
            pthread_join(thread, nullptr) != 0) _exit(136);
        _exit(entries == 1 ? 0 : 137);
      }, ::testing::ExitedWithCode(0), "");
    }
}
#endif

namespace {
static volatile sig_atomic_t profiling_signal_entries;

static void countProfiledSignal(int) {
    ++profiling_signal_entries;
}

// ThreadEnd boundary: the exit mark publishes only after profiling signals
// are blocked, so a queued sample stays pending instead of walking a thread
// whose crash-handler recovery the mark disables.
static void observeThreadEndSignalBoundary() {
    if (!ThreadExitRegistry::contains(ThreadExitRegistry::currentId())) _exit(141);
    sigset_t mask;
    if (sigprocmask(SIG_BLOCK, nullptr, &mask) != 0 ||
        !sigismember(&mask, SIGPROF) || !sigismember(&mask, SIGVTALRM)) _exit(142);
    profiling_signal_entries = 0;
    if (raise(SIGPROF) != 0 || raise(SIGVTALRM) != 0) _exit(143);
    if (profiling_signal_entries != 0) _exit(144);
    sigset_t pending;
    if (sigpending(&pending) != 0 ||
        !sigismember(&pending, SIGPROF) || !sigismember(&pending, SIGVTALRM)) _exit(145);
    _exit(0);
}

static void installCountingProfiledHandlers() {
    struct sigaction action = {};
    sigemptyset(&action.sa_mask);
    action.sa_handler = countProfiledSignal;
    if (sigaction(SIGPROF, &action, nullptr) != 0 ||
        sigaction(SIGVTALRM, &action, nullptr) != 0) _exit(146);
}

static void disableCoreForTest() {
    struct rlimit no_core = {0, 0};
    setrlimit(RLIMIT_CORE, &no_core);
}

// The gtest parent can carry profiling signals blocked, and forked children
// inherit that mask; start from a clean baseline so the block under test is
// onThreadEnd's own.
static void clearProfiledSignalMaskForTest() {
    sigset_t empty;
    sigemptyset(&empty);
    if (sigprocmask(SIG_SETMASK, &empty, nullptr) != 0) _exit(158);
}

// The crash window: with the mark published before the signal block, an
// armed sampler still runs on the marked thread; its recoverable walk fault
// chains out and kills the process. With the block first, the queued sample
// never runs and the unmarked live identity keeps its SafeAccess recovery.
static void observeThreadEndSamplerWindow() {
    if (!ThreadExitRegistry::contains(ThreadExitRegistry::currentId())) _exit(147);
    profiling_recovered = 0;
    prefix_completed = 1;
    if (raise(SIGVTALRM) != 0) _exit(148);
    if (profiling_recovered != 0) _exit(149);
    sigset_t pending;
    if (sigpending(&pending) != 0 || !sigismember(&pending, SIGVTALRM)) _exit(150);
    ThreadExitRegistry::clearCurrent();
    if (SafeAccess::safeFetch64(static_cast<int64_t*>(poison), -46) != -46) _exit(151);
    if (getInSignalDepth() != 0) _exit(152);
    _exit(0);
}
}

TEST(CrashBootstrapTest, ThreadEndBlocksProfilingBeforeExitMark) {
    EXPECT_EXIT({
        alarm(5);
        disableCoreForTest();
        ProfiledThread::initCurrentThread();
        installHandlers();
        installCountingProfiledHandlers();
        clearProfiledSignalMaskForTest();
        Profiler::threadEndMarkedForTest = observeThreadEndSignalBoundary;
        Profiler::instance()->onThreadEndForTest();
        _exit(153);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(CrashBootstrapTest, ThreadEndBlocksProfilingBeforeExitMarkWithoutTls) {
    EXPECT_EXIT({
        alarm(5);
        disableCoreForTest();
        if (ProfiledThread::current() != nullptr) ProfiledThread::release();
        installHandlers();
        installCountingProfiledHandlers();
        clearProfiledSignalMaskForTest();
        Profiler::threadEndMarkedForTest = observeThreadEndSignalBoundary;
        Profiler::instance()->onThreadEndForTest();
        _exit(154);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(CrashBootstrapTest, ThreadEndMarkedSamplerFaultIsNotAdmitted) {
    EXPECT_EXIT({
        alarm(5);
        disableCoreForTest();
        ProfiledThread::initCurrentThread();
        installHandlers();
        clearProfiledSignalMaskForTest();
        poison = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (poison == MAP_FAILED) _exit(155);
        struct sigaction action = {};
        sigemptyset(&action.sa_mask);
        action.sa_handler = faultableProfilingHandler;
        if (sigaction(SIGVTALRM, &action, nullptr) != 0) _exit(156);
        Profiler::threadEndMarkedForTest = observeThreadEndSamplerWindow;
        Profiler::instance()->onThreadEndForTest();
        _exit(157);
    }, ::testing::ExitedWithCode(0), "");
}

namespace {
static void markAdmitted() {
    char entry = 'A';
    if (write(entry_pipe, &entry, 1) != 1) _exit(160);
}

// Raises signal in a child with the given address range and reports, through
// the pipe, every TLS bootstrap ('E') and crash-handler admission ('A').
static void runPrefilterChild(int signal, uintptr_t min, uintptr_t max, int* entry_count,
                              int* admit_count, int* status) {
    int fds[2];
    ASSERT_EQ(0, pipe(fds));
    pid_t child = fork();
    ASSERT_GE(child, 0);
    if (child == 0) {
        close(fds[0]);
        entry_pipe = fds[1];
        disableCoreForTest();
        alarm(5);
        ProfiledThread::initCurrentThread();
        installHandlers();
        Profiler::setAddressRangeForTest(min, max);
        SignalHandlerScope::bootstrapHookForTest = markBootstrap;
        Profiler::crashHandlerAdmittedForTest = markAdmitted;
        raise(signal);
        _exit(0);
    }
    close(fds[1]);
    char events[16];
    int count = 0;
    ssize_t size;
    while ((size = read(fds[0], events + count, sizeof(events) - count)) > 0) count += size;
    close(fds[0]);
    ASSERT_EQ(child, waitpid(child, status, 0));
    *entry_count = 0;
    *admit_count = 0;
    for (int i = 0; i < count; ++i) {
        *entry_count += events[i] == 'E';
        *admit_count += events[i] == 'A';
    }
}

// raise() faults inside libc, so [1, 2) excludes the PC and [1, max) covers it.
static void expectForeignFaultChains(int signal) {
    int entry_count = -1, admit_count = -1, status = 0;
    runPrefilterChild(signal, 1, 2, &entry_count, &admit_count, &status);
    EXPECT_EQ(0, entry_count) << "foreign fault must not bootstrap TLS";
    EXPECT_EQ(0, admit_count) << "foreign fault must not reach crashHandlerInternal";
    ASSERT_TRUE(WIFSIGNALED(status)) << "child status=" << status;
    EXPECT_EQ(signal, WTERMSIG(status));
}

static void expectOwnedFaultAdmitted(int signal, uintptr_t min, uintptr_t max) {
    int entry_count = -1, admit_count = -1, status = 0;
    runPrefilterChild(signal, min, max, &entry_count, &admit_count, &status);
    EXPECT_EQ(1, entry_count);
    EXPECT_EQ(1, admit_count);
    ASSERT_TRUE(WIFEXITED(status)) << "child status=" << status;
    EXPECT_EQ(0, WEXITSTATUS(status));
}
}

TEST(CrashBootstrapTest, PrefilterChainsSegvOutsideProfilerRange) {
    expectForeignFaultChains(SIGSEGV);
}

TEST(CrashBootstrapTest, PrefilterChainsBusOutsideProfilerRange) {
    expectForeignFaultChains(SIGBUS);
}

TEST(CrashBootstrapTest, PrefilterAdmitsFaultInsideProfilerRange) {
    expectOwnedFaultAdmitted(SIGSEGV, 1, UINTPTR_MAX);
    expectOwnedFaultAdmitted(SIGBUS, 1, UINTPTR_MAX);
}

TEST(CrashBootstrapTest, PrefilterAdmitsFaultWhileRangeUnknown) {
    expectOwnedFaultAdmitted(SIGSEGV, 0, 0);
    expectOwnedFaultAdmitted(SIGBUS, 0, 0);
}
