/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "jvmSupport.h"
#include "jvmThread.h"
#include "vmEntry.h"
#include "profiler.h"
#include "gtest_crash_handler.h"

// Regression/contract tests for JVMSupport::initialize() and its callers.
//
// Profiler::checkState() (shared by Profiler::start() and Profiler::check())
// lazily calls JVMSupport::initialize() the first time the profiler leaves
// the NEW state, because the JVMTI VMInit callback that would normally do it
// arrives too late (see profiler.cpp). If JVMSupport::initialize() fails —
// e.g. JVMThread::initialize() cannot resolve the current JVMTI thread —
// checkState() must latch the profiler into the ERROR state and return an
// Error, so start()/check() never proceed to touch JVM structures that were
// never set up.
//
// This gtest binary has no live JVM attached, so JVMThread::initialize()
// naturally fails here the same way it would against an unsupported/degraded
// JVM: VM::jvmti()->GetCurrentThread() has nothing real to answer. Rather
// than leaving VM::_jvmti as the process default (nullptr, which would
// crash on the first indirect call through it), a minimal mock JVMTI table
// is installed so the failure is deterministic and doesn't depend on
// dereferencing a null environment pointer.

static constexpr char JVM_SUPPORT_TEST_NAME[] = "JvmSupportInitTest";
class JvmSupportGlobalSetup {
public:
  JvmSupportGlobalSetup()  { installGtestCrashHandler<JVM_SUPPORT_TEST_NAME>(); }
  ~JvmSupportGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static JvmSupportGlobalSetup jvm_support_global_setup;

// ---------------------------------------------------------------------------
// VMTestAccessor — friend of VM, lets tests swap VM::_jvmti for a mock so
// JVMThread::currentThreadSlow() can be exercised without a live JVM.
// ---------------------------------------------------------------------------
class VMTestAccessor {
public:
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

// ---------------------------------------------------------------------------
// ProfilerTestAccessor — friend of Profiler, lets tests force the internal
// state machine to a known value so checkState()/start()/check() can be
// exercised from a specific branch independently of what earlier tests (or
// gtest_main's own startup) left the process-wide singleton in.
// ---------------------------------------------------------------------------
class ProfilerTestAccessor {
public:
    static void setState(Profiler* p, State s) {
        p->_state.store(s, std::memory_order_release);
    }
    static State getState(Profiler* p) {
        return p->_state.load(std::memory_order_acquire);
    }
};

// GetCurrentThread failing is exactly what JVMThread::currentThreadSlow()
// sees against a JVM that hasn't (yet) attached this thread — it early
// returns nullptr before touching JNI or any HotSpot-specific vmStructs, so
// mocking this single entry point is enough to make the whole
// JVMSupport::initialize() chain fail deterministically.
static jvmtiError JNICALL mock_GetCurrentThread_fails(jvmtiEnv*, jthread*) {
    return JVMTI_ERROR_INTERNAL;
}

class JvmSupportInitFailureTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_env{};
    jvmtiEnv* _orig_jvmti = nullptr;

    void SetUp() override {
        _orig_jvmti = VMTestAccessor::getJvmti();
        tbl = jvmtiInterface_1_{};
        tbl.GetCurrentThread = &mock_GetCurrentThread_fails;
        mock_env.functions = &tbl;
        VMTestAccessor::setJvmti(&mock_env);

        // Every test starts the shared Profiler singleton fresh at NEW so
        // the JVMSupport::initialize() branch in checkState() is actually
        // exercised, regardless of what state other tests in this binary
        // left it in.
        ProfilerTestAccessor::setState(Profiler::instance(), NEW);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(_orig_jvmti);
    }
};

TEST_F(JvmSupportInitFailureTest, JVMThreadInitializeFailsWithoutLiveJvm) {
    EXPECT_FALSE(JVMThread::initialize());
}

TEST_F(JvmSupportInitFailureTest, JVMSupportInitializeFailsWhenJVMThreadFails) {
    EXPECT_FALSE(JVMSupport::initialize());
}

// The core contract: checkState() must not let a NEW profiler proceed past
// a failed JVMSupport::initialize() call, and must latch ERROR so it can
// never retry (and re-attempt initialize()) on a later call.
TEST_F(JvmSupportInitFailureTest, CheckStateBlocksOnInitFailureAndLatchesError) {
    Profiler* p = Profiler::instance();

    Error error = p->checkState();
    bool has_error = (bool)error;

    EXPECT_TRUE(has_error);
    EXPECT_STREQ("Profiler encountered fatal error", error.message());
    EXPECT_EQ(ERROR, ProfilerTestAccessor::getState(p));
}

// Profiler::start() must surface the same failure and never reach engine
// selection / buffer allocation when JVMSupport can't be initialized.
TEST_F(JvmSupportInitFailureTest, StartReturnsErrorAndLatchesErrorState) {
    Profiler* p = Profiler::instance();
    Arguments args;

    Error error = p->start(args, /*reset=*/false);
    bool has_error = (bool)error;

    EXPECT_TRUE(has_error);
    EXPECT_EQ(ERROR, ProfilerTestAccessor::getState(p));
}

// Profiler::check() (dry-run validation, used by the `check` diagnostic
// command) must bail out the same way start() does.
TEST_F(JvmSupportInitFailureTest, CheckReturnsErrorAndLatchesErrorState) {
    Profiler* p = Profiler::instance();
    Arguments args;

    Error error = p->check(args);
    bool has_error = (bool)error;

    EXPECT_TRUE(has_error);
    EXPECT_EQ(ERROR, ProfilerTestAccessor::getState(p));
}

// Once JVMSupport initialization has failed once, the profiler is
// permanently disabled: checkState() must short-circuit on the ERROR state
// on every later call without retrying JVMSupport::initialize() (no mock
// JVMTI installed here — if it retried, it would dereference a null
// VM::_jvmti and crash, so a pass here also proves it didn't retry).
TEST(JvmSupportErrorLatchTest, CheckStateStaysBlockedOnceInError) {
    Profiler* p = Profiler::instance();
    ProfilerTestAccessor::setState(p, ERROR);

    Error error = p->checkState();
    bool has_error = (bool)error;

    EXPECT_TRUE(has_error);
    EXPECT_STREQ("Profiler encountered fatal error", error.message());
    EXPECT_EQ(ERROR, ProfilerTestAccessor::getState(p));
}
