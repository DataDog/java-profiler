/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// ---------------------------------------------------------------------------
// PROF-15341 design doc, Open Question: does JMC's parser actually resolve
// the datadog.ReferenceChain event's `chain` field - declared in
// jfrMetadata.cpp as field("chain", T_CLASS, ..., F_CPOOL | F_ARRAY), i.e. an
// *array of scalar constant-pool-index* T_CLASS values - the same way it
// resolves a plain scalar F_CPOOL field (e.g. objectClass) or a plain
// F_ARRAY-of-composite-struct field (e.g. StackTrace.frames)? Neither of
// those two existing, already-exercised shapes proves this combination.
//
// This test answers that empirically, not by inspecting the JFR spec: it
// drives the *real* production write path (Recording - not a hand-rolled
// byte layout) to produce one complete, standalone, chunk-finalized .jfr
// file containing a real datadog.ReferenceChain event plus its class
// checkpoint, and leaves the actual JMC read-back to the companion Java test
// (ddprof-test's ReferenceChainJfrParserTest), which loads this file with
// org.openjdk.jmc.flightrecorder.JfrLoaderToolkit and asserts the resolved
// class names.
//
// Constructing a real `Recording` outside of Profiler::start()'s state
// machine is unavoidable here: this gtest binary has no live JVM attached
// (see referenceChains_ut.cpp's and jvmSupport_ut.cpp's fixture comments for
// the same, already-established constraint), and Profiler::start()/check()
// both require live JVM introspection (checkJvmCapabilities() ->
// JVMThread::hasJavaThreadId(), VMStructs-backed queries) that cannot be
// satisfied without one. Recording's constructor and recordReferenceChain()
// are already public production API (flightRecorder.h) that do not go
// through Profiler::start()/stop()/dump() at all, so using them directly is
// not a new hook - it is the same "drive the real machinery, don't hand-roll
// the format" approach as every other test in this file's neighbourhood,
// just entered one layer lower. The two remaining unavoidable null-pointer
// dependencies of Recording::finishChunk() - Profiler::cpuEngine()/
// wallEngine() (NULL until Profiler::start() runs) and VM::jni() (NULL
// _vm otherwise) - are supplied via the exact same pre-existing, already
// test-appropriate friend-accessor mechanism this codebase already uses for
// VM::_jvmti (VMTestAccessor) and Profiler::_state (ProfilerTestAccessor,
// jvmSupport_ut.cpp): profiler.h and vmEntry.h already declare `friend class
// ProfilerTestAccessor;` / `friend class VMTestAccessor;` for exactly this
// purpose, so defining those classes here (per-translation-unit, like every
// other _ut.cpp that does the same) adds no new production surface.
// ---------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "arguments.h"
#include "codeCache.h"
#include "common.h"
#include "engine.h"
#include "flightRecorder.h"
#include "jfrMetadata.h"
#include "profiler.h"
#include "referenceChains.h"
#include "tsc.h"
#include "vmEntry.h"
#include "hotspot/vmStructs.h"
#ifdef ASAN_ENABLED
#include <sanitizer/lsan_interface.h>
#endif
#include "gtest_crash_handler.h"

static constexpr char REFERENCE_CHAIN_JFR_TEST_NAME[] = "ReferenceChainJfrRoundtripTest";

class ReferenceChainJfrRoundtripGlobalSetup {
public:
    ReferenceChainJfrRoundtripGlobalSetup() {
        installGtestCrashHandler<REFERENCE_CHAIN_JFR_TEST_NAME>();
    }
    ~ReferenceChainJfrRoundtripGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};
static ReferenceChainJfrRoundtripGlobalSetup global_setup;

// ---------------------------------------------------------------------------
// VMTestAccessor - friend of VM (vmEntry.h). Same purpose/name as the
// identically-named, independently-defined class in referenceChains_ut.cpp
// and jvmSupport_ut.cpp (each _ut.cpp translation unit defines its own copy;
// see this codebase's established convention). Extended here with a _vm
// setter: Recording::finishChunk() (flightRecorder.cpp) unconditionally
// calls VM::jni(), which dereferences VM::_vm - NULL by default in this
// live-JVM-less gtest binary - so a mocked JavaVM is required the same way
// a mocked jvmtiEnv already is for VM::_jvmti.
// ---------------------------------------------------------------------------
class VMTestAccessor {
public:
    static jvmtiEnv *getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv *env) { VM::_jvmti = env; }
    static JavaVM *getVm() { return VM::_vm; }
    static void setVm(JavaVM *vm) { VM::_vm = vm; }
};

// ---------------------------------------------------------------------------
// ProfilerTestAccessor - friend of Profiler (profiler.h), same mechanism
// jvmSupport_ut.cpp already uses for Profiler::_state. Recording::
// finishChunk() unconditionally dereferences Profiler::instance()->
// cpuEngine()/wallEngine() (writeDatadogProfilerConfig) - both NULL until
// Profiler::start() runs, which (per this file's header comment) cannot run
// in this gtest binary. Engine's base-class methods (name()="None",
// interval()=0) are safe no-op defaults, so a plain Engine instance is
// sufficient here - no engine-specific behaviour is exercised by this test.
// ---------------------------------------------------------------------------
class ProfilerTestAccessor {
public:
    static void setCpuEngine(Profiler *p, Engine *e) { p->_cpu_engine = e; }
    static void setWallEngine(Profiler *p, Engine *e) { p->_wall_engine = e; }
};

// ---------------------------------------------------------------------------
// ReferenceChainsTestAccessor - friend of ReferenceChainTracker
// (referenceChains.h), same reset() as referenceChains_ut.cpp's own
// identically-named class (this file's independent copy, per this
// codebase's established per-translation-unit convention - see
// VMTestAccessor's comment above). Required because ReferenceChainTracker::
// instance() is a process-wide singleton shared with every other _ut.cpp in
// this gtest binary.
// ---------------------------------------------------------------------------
class ReferenceChainsTestAccessor {
public:
    static void reset() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        delete t->_frontier;
        t->_frontier = nullptr;
        t->_class_tags = ClassTagTable();
        t->_next_tag = 1;
        t->_next_class_tag_magnitude = 1;
        t->_search_started = false;
        t->_search_state = SearchState::RUNNING;
        t->_abandon_reason = SearchAbandonReason::NONE;
        t->_search_start_ns = 0;
        t->_pending_expand.clear();
        t->_last_pass_gc_finish_epoch = 0;
        t->_last_pass_ns = 0;
        t->_passes_run = 0;
        t->_emitted_target_tags.clear();
        t->_emitted_search_start_ns = 0;
    }
};

static jvmtiError JNICALL mock_SetEventNotificationMode(jvmtiEnv *, jvmtiEventMode,
                                                         jvmtiEvent, jthread, ...) {
    return JVMTI_ERROR_NONE;
}

static jvmtiError JNICALL mock_GetAvailableProcessors(jvmtiEnv *, jint *count_ptr) {
    *count_ptr = 1;
    return JVMTI_ERROR_NONE;
}

// Recording::finishChunk() pins currently-loaded classes via
// GetLoadedClasses() before/after serialization (see its own comment on the
// GC-unload race this guards against in a real JVM). Reporting zero loaded
// classes here is a faithful, not a cheated, answer for this gtest binary:
// there genuinely are no JVMTI-visible loaded classes without a live JVM,
// so the DeleteLocalRef()/Deallocate() cleanup loop that follows is a no-op.
static jvmtiError JNICALL mock_GetLoadedClasses(jvmtiEnv *, jint *count_ptr,
                                                 jclass **classes_ptr) {
    *count_ptr = 0;
    *classes_ptr = nullptr;
    return JVMTI_ERROR_NONE;
}

static jvmtiError JNICALL mock_Deallocate(jvmtiEnv *, unsigned char *mem) {
    free(mem);
    return JVMTI_ERROR_NONE;
}

static JNIEnv_ g_mock_jni_env{};

static jint JNICALL mock_GetEnv(JavaVM *, void **penv, jint) {
    *penv = &g_mock_jni_env;
    return 0; // JNI_OK
}

class ReferenceChainJfrRoundtripTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    JNIInvokeInterface_ vm_tbl{};
    JavaVM_ mock_vm{};
    Engine noop_engine;

    jvmtiEnv *orig_jvmti = nullptr;
    JavaVM *orig_vm = nullptr;
    Engine *orig_cpu_engine = nullptr;
    Engine *orig_wall_engine = nullptr;

    void SetUp() override {
        ReferenceChainsTestAccessor::reset();

        orig_jvmti = VMTestAccessor::getJvmti();
        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.GetAvailableProcessors = &mock_GetAvailableProcessors;
        jvmti_tbl.GetLoadedClasses = &mock_GetLoadedClasses;
        jvmti_tbl.Deallocate = &mock_Deallocate;
        mock_jvmti.functions = &jvmti_tbl;
        VMTestAccessor::setJvmti(&mock_jvmti);

        orig_vm = VMTestAccessor::getVm();
        vm_tbl = JNIInvokeInterface_{};
        vm_tbl.GetEnv = &mock_GetEnv;
        mock_vm.functions = &vm_tbl;
        VMTestAccessor::setVm(&mock_vm);

        orig_cpu_engine = Profiler::instance()->cpuEngine();
        orig_wall_engine = Profiler::instance()->wallEngine();
        ProfilerTestAccessor::setCpuEngine(Profiler::instance(), &noop_engine);
        ProfilerTestAccessor::setWallEngine(Profiler::instance(), &noop_engine);

        // writeSettings() (flightRecorder.cpp) unconditionally calls
        // VMStructs::libjvm()->hasDebugSymbols() - VMStructs::_libjvm is
        // NULL until VMStructs::init() has scanned a real libjvm.so, which
        // never happens without a live JVM. VMStructs::init(CodeCache*) is
        // already public production API (hotspot/vmStructs.h) - calling it
        // with a name-only, no-symbols CodeCache (the same "fake shared
        // library" construction libraries_ut.cpp's fixture already uses) is
        // not a new hook: VMStructs::readSymbol() already degrades to 0
        // ("avoid JVM crash in case of missing symbols", vmStructs.cpp) for
        // every symbol this resolves, so every _has_* capability flag stays
        // false, identical to VMStructs's never-initialized state - only
        // libjvm() stops returning NULL. Idempotent and process-global like
        // every other singleton this fixture touches; no other _ut.cpp in
        // this binary reads VMStructs::libjvm()/_has_* state.
        static CodeCache fake_libjvm("fake_libjvm.so");
        VMStructs::init(&fake_libjvm);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        VMTestAccessor::setVm(orig_vm);
        ProfilerTestAccessor::setCpuEngine(Profiler::instance(), orig_cpu_engine);
        ProfilerTestAccessor::setWallEngine(Profiler::instance(), orig_wall_engine);
    }
};

// Path agreed with the companion Java test (ddprof-test's
// ReferenceChainJfrParserTest), which reads the same file back via JMC's
// JfrLoaderToolkit. Both sides resolve it via the OS temp dir so the
// producer (this gtest) and the consumer (the Java test, run afterwards by
// the same operator/CI job on the same machine) agree without either side
// needing to know the other module's build directory layout.
static std::string chainRoundtripJfrPath() {
    const char *tmp = getenv("TMPDIR");
    std::string dir = (tmp != nullptr && *tmp != 0) ? tmp : "/tmp";
    if (dir.back() != '/') {
        dir += '/';
    }
    return dir + "datadog_reference_chain_roundtrip.jfr";
}

TEST_F(ReferenceChainJfrRoundtripTest, ProducesValidStandaloneJfrWithChainEvent) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    // Skip OS/CPU info, JVM info, system properties and native library
    // enumeration - all of them call further JVMTI/JNI entry points this
    // fixture does not mock, and none of them are relevant to the question
    // this test answers (whether JMC resolves the chain[] field).
    args._jfr_options = JFR_SYNC_OPTS;

    // Recording::writeMetadata() (flightRecorder.cpp) serializes JfrMetadata::root()
    // as-is - it does not build it. That tree is normally populated exactly once by
    // JfrMetadata::initialize() (jfrMetadata.cpp), called from Profiler::start()
    // (profiler.cpp:1433) - which this test does not call (per this file's header
    // comment). initialize() is itself public, JVM-independent (pure fluent-builder
    // data construction, no JVMTI/JNI calls) and idempotent (_initialized guard,
    // jfrMetadata.cpp) - calling it directly here is completing the same
    // one-time setup step every real Recording implicitly depends on, not a new
    // hook; without it, writeMetadata() would serialize an empty "root" element
    // (no datadog.ReferenceChain type declaration at all) instead of the real
    // metadata tree.
    // JfrMetadata::initialize() populates the static Element/Attribute tree
    // (JfrMetadata::_root) exactly once for the life of the process - the same
    // one-time, never-freed allocation every real agent process makes via
    // Profiler::start() and relies on the OS to reclaim at exit. This gtest
    // binary is the only asan unit test that calls initialize() directly, so
    // LeakSanitizer flags that intentional process-lifetime allocation as a
    // leak on test exit. Disable leak detection for this call only - it is
    // not a bug in JfrMetadata or the reference-chain code under test.
#ifdef ASAN_ENABLED
    {
      __lsan::ScopedDisabler lsan_disabler;
      JfrMetadata::initialize(args._context_attributes);
    }
#else
    JfrMetadata::initialize(args._context_attributes);
#endif

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Register three distinct, recognisable class names in the same
    // StringDictionary (Profiler::classMap()) writeClasses() (flightRecorder.cpp)
    // serializes into the T_CLASS checkpoint - this is the exact API
    // Profiler::lookupClass() already-existing tests use (e.g.
    // referenceChains_ut.cpp's ReconstructsChainForSyntheticGraph).
    int leafKlass = Profiler::instance()->lookupClass(
        "com/test/ChainLeaf", strlen("com/test/ChainLeaf"));
    int middleKlass = Profiler::instance()->lookupClass(
        "com/test/ChainMiddle", strlen("com/test/ChainMiddle"));
    int rootKlass = Profiler::instance()->lookupClass(
        "com/test/ChainRoot", strlen("com/test/ChainRoot"));
    ASSERT_NE(-1, leafKlass);
    ASSERT_NE(-1, middleKlass);
    ASSERT_NE(-1, rootKlass);

    // writeClasses() only serializes classMap()->standby() (the snapshot
    // captured by rotate()) - without this, the three lookupClass() calls
    // above would sit in the live "active" buffer only and never reach the
    // checkpoint. StringDictionary::rotate() is public production API
    // (stringDictionary.h), the same one Profiler::rotateDictsAndRun() calls
    // internally for every real dump - calling it directly here is not a
    // hand-rolled substitute, just the same operation invoked without the
    // rest of Profiler::dump()'s live-JVM-dependent machinery.
    Profiler::instance()->classMap()->rotate();

    // Seed a deterministic leaf(tag=3) <- middle(tag=2) <- root(tag=1)
    // parent chain directly into the tracker's own FrontierTable, exactly
    // mirroring referenceChains_ut.cpp's ReconstructsChainForSyntheticGraph
    // test (which builds the same shape via a scripted heap walk instead of
    // direct insertion - both reach the same FrontierTable state that
    // buildChainEvent() below reads).
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_NE(nullptr, frontier);
    // root_kind=21 (JVMTI_HEAP_REFERENCE_JNI_GLOBAL) on the root-attached
    // entry only - exercises the new rootKind field end to end through
    // buildChainEvent()/recordReferenceChain(), mirroring how
    // heapReferenceCallback() only ever sets it on a parent_tag==0 entry.
    ASSERT_TRUE(frontier->insert(1, 0, (u32)rootKlass, 0,
                                 FrontierEntryState::EDGE, /*root_kind=*/21));
    ASSERT_TRUE(frontier->insert(2, 1, (u32)middleKlass, 1, FrontierEntryState::EDGE));
    ASSERT_TRUE(frontier->insert(3, 2, (u32)leafKlass, 2, FrontierEntryState::EDGE));

    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(/*target_tag=*/3, &event));
    ASSERT_EQ(3u, event._chain.size());
    EXPECT_EQ((u32)leafKlass, event._chain[0]);
    EXPECT_EQ((u32)middleKlass, event._chain[1]);
    EXPECT_EQ((u32)rootKlass, event._chain[2]);
    EXPECT_EQ(21u, event._root_kind);
    event._start_time = TSC::ticks();

    const std::string path = chainRoundtripJfrPath();
    {
        int fd = open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
        ASSERT_GE(fd, 0) << "could not open " << path << " for writing";

        // Recording(fd, args) and recordReferenceChain() are already public
        // production API (flightRecorder.h) - this drives the real chunk
        // header/metadata/settings write (constructor) and the real
        // datadog.ReferenceChain event encoding (recordReferenceChain(),
        // flightRecorder.cpp:1937 - the exact F_CPOOL|F_ARRAY `chain` field
        // this test exists to answer for), not a hand-rolled byte layout.
        Recording rec(fd, args);
        Buffer *buf = rec.buffer(/*lock_index=*/0);
        rec.recordReferenceChain(buf, &event);
        // ~Recording() (end of scope) calls finishChunk(true): flushes buf,
        // writes the real class/symbol/package constant-pool checkpoint
        // (writeCpool() -> writeClasses(), which is what makes leafKlass/
        // middleKlass/rootKlass resolvable to their names at all), patches
        // the chunk header's size/cpool-offset fields, and closes fd - the
        // same finalization every real recording chunk goes through.
    }

    FILE *f = fopen(path.c_str(), "rb");
    ASSERT_NE(nullptr, f) << "expected " << path << " to have been written";
    char magic[4] = {0, 0, 0, 0};
    size_t read = fread(magic, 1, 4, f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);

    ASSERT_EQ(4u, read);
    EXPECT_EQ(0, memcmp(magic, "FLR\0", 4))
        << "produced file does not start with the JFR chunk magic";
    EXPECT_GT(size, 4) << "produced file is empty beyond the magic header";

    TEST_LOG("Wrote standalone reference-chain roundtrip JFR to %s (%ld bytes)",
             path.c_str(), size);
}
