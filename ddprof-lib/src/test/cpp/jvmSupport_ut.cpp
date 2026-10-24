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
    static constexpr LoadState LazyLoaded()    { return JVMSupport::Lazy_loaded; }
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
    // The stack walker mode as Profiler::start() resolved it from the arguments.
    static CStack getCStack(Profiler* p) { return p->_cstack; }
    static void setCStack(Profiler* p, CStack c) { p->_cstack = c; }
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
    JVMSupportTestAccessor::LoadState _orig_load_state;
    CStack _orig_cstack;

    void SetUp() override {
        _orig_hotspot = VMTestAccessor::getHotspot();
        VMTestAccessor::setHotspot(true);
        _orig_load_state = JVMSupportTestAccessor::getLoadState();
        JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::NoLoaded());
        // As if Profiler::start() had resolved the arguments to the VM walker.
        _orig_cstack = ProfilerTestAccessor::getCStack(Profiler::instance());
        ProfilerTestAccessor::setCStack(Profiler::instance(), CSTACK_VM);

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
        JVMSupportTestAccessor::setLoadState(_orig_load_state);
        ProfilerTestAccessor::setCStack(Profiler::instance(), _orig_cstack);
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

    // Regression: before the fix, a stale Fully_loaded state short-circuited initExecution()...
    // so the state stayed Fully_loaded instead of downgrading.
    EXPECT_EQ(JVMSupportTestAccessor::PartialLoaded(), JVMSupportTestAccessor::getLoadState());
}

// fjmethodid=lazy needs VMStructs::hasKlassMethods(); without the Klass*/methods
// structs (as in this binary, where no JVM populated VMStructs) it must fall
// back to the partial preload mode, never enter Lazy_loaded with nothing to
// resolve frames against.
TEST_F(JVMSupportRestartTest, LazyFallsBackToPartialWithoutKlassStructs) {
    Arguments lazy_args;
    lazy_args._force_jmethodID = false;
    lazy_args._lazy_jmethodID = true;
    lazy_args._cstack = CSTACK_VM;

    JVMSupport::initExecution(lazy_args, &mock_jvmti, reinterpret_cast<JNIEnv*>(&mock_jni));

    EXPECT_NE(JVMSupportTestAccessor::LazyLoaded(), JVMSupportTestAccessor::getLoadState());
    EXPECT_EQ(JVMSupportTestAccessor::PartialLoaded(), JVMSupportTestAccessor::getLoadState());
}

// Lazy mode, like partial mode, relies on walkVM's raw Method* frames; with a
// cstack mode that goes through AsyncGetCallTrace it must preload everything.
TEST_F(JVMSupportRestartTest, LazyRequiresVmStackWalker) {
    Arguments lazy_args;
    lazy_args._force_jmethodID = false;
    lazy_args._lazy_jmethodID = true;
    lazy_args._cstack = CSTACK_NO;
    ProfilerTestAccessor::setCStack(Profiler::instance(), CSTACK_NO);

    JVMSupport::initExecution(lazy_args, &mock_jvmti, reinterpret_cast<JNIEnv*>(&mock_jni));

    EXPECT_EQ(JVMSupportTestAccessor::FullyLoaded(), JVMSupportTestAccessor::getLoadState());
}

// What counts is the stack walker mode Profiler::start() resolved, not the
// argument: cstack=default becomes DWARF where the VM walker is unavailable
// (macOS, or a JVM without the stack vmStructs), and then Java frames come from
// AsyncGetCallTrace, which needs every jmethodID preloaded.
TEST_F(JVMSupportRestartTest, DefaultCstackResolvedToDwarfPreloadsEverything) {
    ProfilerTestAccessor::setCStack(Profiler::instance(), CSTACK_DWARF);
    for (bool lazy : {true, false}) {
        JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::NoLoaded());
        Arguments args;
        args._force_jmethodID = false;
        args._lazy_jmethodID = lazy;
        args._cstack = CSTACK_DEFAULT;

        JVMSupport::initExecution(args, &mock_jvmti, reinterpret_cast<JNIEnv*>(&mock_jni));

        EXPECT_EQ(JVMSupportTestAccessor::FullyLoaded(), JVMSupportTestAccessor::getLoadState()) << lazy;
    }
}
