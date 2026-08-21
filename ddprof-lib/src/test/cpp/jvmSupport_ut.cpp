/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstring>
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
// VMTestAccessor — friend of VM, lets tests swap VM::_jvmti/_hotspot for a
// mock/forced value so JVM-vendor-dependent code paths can be exercised
// deterministically without a live JVM.
// ---------------------------------------------------------------------------
class VMTestAccessor {
public:
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool value) { VM::_hotspot = value; }
};

class JvmSupportThreadClassificationTest : public ::testing::Test {
protected:
    using JniFunction = void (JNICALL*)();

    static constexpr int GET_VERSION_INDEX = 4;
    static constexpr int IS_VIRTUAL_THREAD_INDEX = 234;
    static constexpr int FUNCTION_TABLE_SIZE = IS_VIRTUAL_THREAD_INDEX + 1;

    inline static jint jni_version;
    inline static jboolean virtual_thread;
    inline static int is_virtual_thread_calls;
    inline static jobject last_thread;

    JniFunction function_table[FUNCTION_TABLE_SIZE]{};
    JNIEnv jni{};
    _jobject thread_object;
    jthread thread = &thread_object;
    bool _orig_hotspot = false;

    static jint JNICALL getVersion(JNIEnv*) { return jni_version; }

    static jboolean JNICALL isVirtualThread(JNIEnv*, jobject candidate) {
        is_virtual_thread_calls++;
        last_thread = candidate;
        return virtual_thread;
    }

    void SetUp() override {
        _orig_hotspot = VMTestAccessor::getHotspot();
        VMTestAccessor::setHotspot(true);
        jni_version = 0x00150000;
        virtual_thread = JNI_FALSE;
        is_virtual_thread_calls = 0;
        last_thread = nullptr;
        function_table[GET_VERSION_INDEX] =
            reinterpret_cast<JniFunction>(&getVersion);
        function_table[IS_VIRTUAL_THREAD_INDEX] =
            reinterpret_cast<JniFunction>(&isVirtualThread);
        jni.functions =
            reinterpret_cast<const JNINativeInterface_*>(function_table);
    }

    void TearDown() override {
        VMTestAccessor::setHotspot(_orig_hotspot);
    }
};

TEST_F(JvmSupportThreadClassificationTest, NullInputsFailClosed) {
    EXPECT_FALSE(JVMSupport::isPlatformThread(nullptr, thread));
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, nullptr));
}

TEST_F(JvmSupportThreadClassificationTest, InvalidJniVersionFailsClosed) {
    jni_version = 0;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

TEST_F(JvmSupportThreadClassificationTest, PreJni19ThreadIsPlatform) {
    jni_version = 0x000a0000;
    function_table[IS_VIRTUAL_THREAD_INDEX] = nullptr;
    EXPECT_TRUE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

TEST_F(JvmSupportThreadClassificationTest, Jni19PlatformThreadIsAccepted) {
    jni_version = 0x00130000;
    EXPECT_TRUE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(1, is_virtual_thread_calls);
    EXPECT_EQ(thread, last_thread);
}

TEST_F(JvmSupportThreadClassificationTest, Jni19VirtualThreadIsRejected) {
    jni_version = 0x00130000;
    virtual_thread = JNI_TRUE;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(1, is_virtual_thread_calls);
    EXPECT_EQ(thread, last_thread);
}

TEST_F(JvmSupportThreadClassificationTest, MissingJni19FunctionFailsClosed) {
    jni_version = 0x00130000;
    function_table[IS_VIRTUAL_THREAD_INDEX] = nullptr;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

TEST_F(JvmSupportThreadClassificationTest, Jni20PlatformThreadIsAccepted) {
    jni_version = 0x00140000;
    EXPECT_TRUE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(1, is_virtual_thread_calls);
    EXPECT_EQ(thread, last_thread);
}

TEST_F(JvmSupportThreadClassificationTest, Jni20VirtualThreadIsRejected) {
    jni_version = 0x00140000;
    virtual_thread = JNI_TRUE;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(1, is_virtual_thread_calls);
    EXPECT_EQ(thread, last_thread);
}

TEST_F(JvmSupportThreadClassificationTest, MissingJni20FunctionFailsClosed) {
    jni_version = 0x00140000;
    function_table[IS_VIRTUAL_THREAD_INDEX] = nullptr;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

TEST_F(JvmSupportThreadClassificationTest, Jni21PlatformThreadIsAccepted) {
    EXPECT_TRUE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(1, is_virtual_thread_calls);
    EXPECT_EQ(thread, last_thread);
}

TEST_F(JvmSupportThreadClassificationTest, Jni21VirtualThreadIsRejected) {
    virtual_thread = JNI_TRUE;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(1, is_virtual_thread_calls);
    EXPECT_EQ(thread, last_thread);
}

TEST_F(JvmSupportThreadClassificationTest, MissingJni21FunctionFailsClosed) {
    function_table[IS_VIRTUAL_THREAD_INDEX] = nullptr;
    EXPECT_FALSE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

// ---------------------------------------------------------------------------
// JvmSupportNonHotspotTest — verifies isPlatformThread() short-circuits to
// true on non-HotSpot JVMs at JNI>=19 without ever indexing the HotSpot-only
// IsVirtualThread vtable slot (which may not even be a valid function
// pointer there).
// ---------------------------------------------------------------------------
class JvmSupportNonHotspotTest : public ::testing::Test {
protected:
    using JniFunction = void (JNICALL*)();

    static constexpr int GET_VERSION_INDEX = 4;
    static constexpr int IS_VIRTUAL_THREAD_INDEX = 234;
    static constexpr int FUNCTION_TABLE_SIZE = IS_VIRTUAL_THREAD_INDEX + 1;

    inline static jint jni_version;
    inline static int is_virtual_thread_calls;

    JniFunction function_table[FUNCTION_TABLE_SIZE]{};
    JNIEnv jni{};
    _jobject thread_object;
    jthread thread = &thread_object;
    bool _orig_hotspot = false;

    static jint JNICALL getVersion(JNIEnv*) { return jni_version; }
    static jboolean JNICALL isVirtualThread(JNIEnv*, jobject) {
        is_virtual_thread_calls++;
        return JNI_TRUE;
    }

    void SetUp() override {
        _orig_hotspot = VMTestAccessor::getHotspot();
        VMTestAccessor::setHotspot(false);
        jni_version = 0x00150000;
        is_virtual_thread_calls = 0;
        function_table[GET_VERSION_INDEX] =
            reinterpret_cast<JniFunction>(&getVersion);
        function_table[IS_VIRTUAL_THREAD_INDEX] =
            reinterpret_cast<JniFunction>(&isVirtualThread);
        jni.functions =
            reinterpret_cast<const JNINativeInterface_*>(function_table);
    }

    void TearDown() override {
        VMTestAccessor::setHotspot(_orig_hotspot);
    }
};

TEST_F(JvmSupportNonHotspotTest, Jni21ThreadIsAcceptedWithoutIndexingVtable) {
    EXPECT_TRUE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

TEST_F(JvmSupportNonHotspotTest, PreJni19ThreadIsStillAccepted) {
    jni_version = 0x000a0000;
    EXPECT_TRUE(JVMSupport::isPlatformThread(&jni, thread));
    EXPECT_EQ(0, is_virtual_thread_calls);
}

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

    // Under -PenableFaultInjection, checkState() checks prewarmUnwinder()
    // before JVMSupport::initialize() (see profiler.cpp), so an injected
    // fault could occasionally surface "Missing libgcc_s.so" here instead of
    // the JVMSupport::initialize() failure this test targets. Retry past any
    // such injected failure. If it persists across retries, libgcc_s is likely
    // genuinely absent on this host and this test cannot exercise the intended path.
    Error error = Error::OK;
    for (int i = 0; i < 100; i++) {
        error = p->checkState();
        if (!error || std::strcmp(error.message(), "Missing libgcc_s.so.1") != 0) {
            break;
        }
        ProfilerTestAccessor::setState(p, NEW);
    }
    if (error && std::strcmp(error.message(), "Missing libgcc_s.so.1") == 0) {
        GTEST_SKIP() << "libgcc_s.so.1 is missing on this host; cannot exercise JVMSupport::initialize() failure path";
    }
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

// Profiler::init() (invoked from JavaProfiler.init0() right after the native
// library loads) shares checkState()'s NEW-state JVMSupport::initialize()
// gate. It must surface the same failure and latch ERROR instead of
// proceeding to ProfiledThread::initCurrentThread().
TEST_F(JvmSupportInitFailureTest, InitReturnsErrorAndLatchesErrorState) {
    Profiler* p = Profiler::instance();

    Error error = p->init();
    bool has_error = (bool)error;

    EXPECT_TRUE(has_error);
    EXPECT_STREQ("Profiler encountered fatal error", error.message());
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
