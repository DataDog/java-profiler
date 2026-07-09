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
// JVMThread::currentThreadSlow() can be exercised without a live JVM. Also
// lets tests force VM::isHotspot() so JVMSupport::initExecution()'s HotSpot
// branch can be exercised deterministically.
// ---------------------------------------------------------------------------
class VMTestAccessor {
public:
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool v) { VM::_hotspot = v; }
};

// ---------------------------------------------------------------------------
// JVMSupportTestAccessor — friend of JVMSupport, lets tests read/reset the
// private jmethodID_load_state directly instead of only observing its
// effects through initExecution()'s side effects.
// ---------------------------------------------------------------------------
class JVMSupportTestAccessor {
public:
    using LoadState = JVMSupport::JMethodIDLoadStats;
    static LoadState getLoadState() { return JVMSupport::getLoadState(); }
    static void setLoadState(LoadState s) { JVMSupport::setLoadState(s); }
    static constexpr LoadState NoLoaded()      { return JVMSupport::No_loaded; }
    static constexpr LoadState PartialLoaded() { return JVMSupport::Partial_loaded; }
    static constexpr LoadState FullyLoaded()   { return JVMSupport::Fully_loaded; }
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

// ---------------------------------------------------------------------------
// Regression tests for JVMSupport::initExecution(): a stale jmethodID_load_state
// left over from a previous execution must not short-circuit before the
// current Arguments are evaluated (otherwise a restart with fjmethodid=false
// after a full-preload session silently keeps full-preload mode).
//
// initExecution() with load_all=false calls HotspotSupport::initClassloaderInfo(jni),
// which calls jni->FindClass("java/lang/ClassLoader") first; mocking FindClass
// to return nullptr makes it take the early-exit path (jni->ExceptionClear(); return;)
// without touching any other JNI/VMStructs machinery.
// ---------------------------------------------------------------------------
static jclass JNICALL mock_FindClass_returns_null(JNIEnv*, const char*) {
    return nullptr;
}
static void JNICALL mock_ExceptionClear_noop(JNIEnv*) {}

static jvmtiError JNICALL mock_GetLoadedClasses_empty(jvmtiEnv*, jint* class_count_ptr, jclass** classes_ptr) {
    *class_count_ptr = 0;
    *classes_ptr = nullptr;
    return JVMTI_ERROR_NONE;
}
static jvmtiError JNICALL mock_GetClassMethods_empty(jvmtiEnv*, jclass, jint* method_count_ptr, jmethodID** methods_ptr) {
    *method_count_ptr = 0;
    *methods_ptr = nullptr;
    return JVMTI_ERROR_NONE;
}
static jvmtiError JNICALL mock_Deallocate_noop(jvmtiEnv*, unsigned char*) {
    return JVMTI_ERROR_NONE;
}

class JVMSupportRestartTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ mock_jni{};
    bool _orig_hotspot;

    void SetUp() override {
        _orig_hotspot = VMTestAccessor::getHotspot();
        VMTestAccessor::setHotspot(true);
        JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::NoLoaded());

        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.GetLoadedClasses = &mock_GetLoadedClasses_empty;
        jvmti_tbl.GetClassMethods = &mock_GetClassMethods_empty;
        jvmti_tbl.Deallocate = &mock_Deallocate_noop;
        mock_jvmti.functions = &jvmti_tbl;

        jni_tbl = JNINativeInterface_{};
        jni_tbl.FindClass = &mock_FindClass_returns_null;
        jni_tbl.ExceptionClear = &mock_ExceptionClear_noop;
        mock_jni.functions = &jni_tbl;
    }

    void TearDown() override {
        VMTestAccessor::setHotspot(_orig_hotspot);
    }
};

TEST_F(JVMSupportRestartTest, SecondStartWithPartialPreloadIsNotBlockedByStaleFullyLoaded) {
    Arguments full_args;
    full_args._force_jmethodID = true; // -> shouldPreloadJmethodIDs()==true -> Fully_loaded

    JVMSupport::initExecution(full_args, &mock_jvmti, reinterpret_cast<JNIEnv*>(&mock_jni));
    EXPECT_EQ(JVMSupportTestAccessor::FullyLoaded(), JVMSupportTestAccessor::getLoadState());

    Arguments partial_args;
    partial_args._force_jmethodID = false;
    partial_args._cstack = CSTACK_VM; // -> shouldPreloadJmethodIDs()==false -> Partial_loaded

    JVMSupport::initExecution(partial_args, &mock_jvmti, reinterpret_cast<JNIEnv*>(&mock_jni));

    // Fails today: the stale Fully_loaded state short-circuits initExecution()
    // before shouldPreloadJmethodIDs(partial_args) is ever evaluated, so the
    // state incorrectly stays Fully_loaded instead of downgrading.
    EXPECT_EQ(JVMSupportTestAccessor::PartialLoaded(), JVMSupportTestAccessor::getLoadState());
}
