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
// Two further boundary properties of the same encoder are pinned here at the
// byte level (these cannot be checked through JMC, which only sees a valid
// recording):
//   - an event whose chain exceeds MAX_REFERENCE_CHAIN_EVENT_HOPS is
//     truncated to a size that still fits inside the fixed recording buffer
//     (a fixed hop cap large enough to permit a worst case beyond the buffer
//     size would write past the buffer - debug assert, release corruption),
//     and the emitted hops keep their edge labels (labels align with the
//     chain's leaf-first element order, so the first emitted_size labels are
//     exactly the labels of the emitted range);
//   - ObjectLivenessEvent's leak_tag defaults to 0, so a construction path
//     that forgets to set it serializes a defined "untagged" value, never
//     indeterminate data.
//
// Constructing a real `Recording` outside of Profiler::start()'s state
// machine is unavoidable here: this gtest binary has no live JVM attached
// (see referenceChains_ut.cpp's and jvmSupport_ut.cpp's fixture comments for
// the same, already-established constraint), and Profiler::start()/check()
// both require live JVM introspection (checkJvmCapabilities() ->
// JVMThread::hasJavaThreadId(), VMStructs-backed queries) that cannot be
// satisfied without one. Recording's constructor, recordReferenceChain()
// and recordHeapLiveObject() are already public production API
// (flightRecorder.h) that do not go through Profiler::start()/stop()/dump()
// at all, so using them directly is not a new hook - it is the same "drive
// the real machinery, don't hand-roll the format" approach as every other
// test in this file's neighbourhood, just entered one layer lower. The two
// remaining unavoidable null-pointer dependencies of Recording::
// finishChunk() - Profiler::cpuEngine()/wallEngine() (NULL until
// Profiler::start() runs) and VM::jni() (NULL _vm otherwise) - are supplied
// via the exact same pre-existing, already test-appropriate
// friend-accessor mechanism this codebase already uses for VM::_jvmti
// (VMTestAccessor) and Profiler::_state (ProfilerTestAccessor,
// jvmSupport_ut.cpp): profiler.h and vmEntry.h already declare `friend
// class ProfilerTestAccessor;` / `friend class VMTestAccessor;` for exactly
// this purpose, so defining those classes here (per-translation-unit, like
// every other _ut.cpp that does the same) adds no new production surface.
// ---------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "arguments.h"
#include "buffers.h"
#include "codeCache.h"
#include "common.h"
#include "engine.h"
#include "flightRecorder.h"
#include "jfrMetadata.h"
#include "profiler.h"
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
    static CodeCache *getLibjvm() { return VM::_libjvm; }
    static void setLibjvm(CodeCache *lib) { VM::_libjvm = lib; }
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
    CodeCache *orig_libjvm = nullptr;
    Engine *orig_cpu_engine = nullptr;
    Engine *orig_wall_engine = nullptr;

    void SetUp() override {
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
        // VM::libjvm()->hasDebugSymbols() - VM::_libjvm is NULL until
        // VM::openJvmLibrary() has resolved a real libjvm.so, which never
        // happens without a live JVM (VM::libjvm() asserts non-null rather
        // than returning NULL). A name-only, no-symbols CodeCache (the same
        // "fake shared library" construction libraries_ut.cpp's fixture
        // already uses) is enough: hasDebugSymbols() degrades to false for
        // it, same as a never-resolved real library with no debug info.
        static CodeCache fake_libjvm("fake_libjvm.so");
        orig_libjvm = VMTestAccessor::getLibjvm();
        VMTestAccessor::setLibjvm(&fake_libjvm);

        // VMStructs::libjvm() is a separate cache (VMStructs::_libjvm, only
        // populated by VMStructs::init() after a real symbol scan) from
        // VM::libjvm() above - nothing in this test's write path reads it,
        // but VMStructs::init(CodeCache*) is already public production API
        // (hotspot/vmStructs.h) and idempotent (readSymbol() degrades to 0
        // for every unresolved symbol, per its own comment), so initializing
        // it here too keeps this fixture consistent with every other _ut.cpp
        // that touches this process-wide singleton.
        VMStructs::init(&fake_libjvm);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        VMTestAccessor::setVm(orig_vm);
        VMTestAccessor::setLibjvm(orig_libjvm);
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

// Length of Buffer::putVar64()'s encoding for v: its 3-bytes-per-group
// shortcut carries the same 21 bits per 3 bytes as plain LEB128, so the
// lengths agree for every v < 2^63 (test-chosen values and TSC ticks are
// all far below that).
static int sizeOfVar64(u64 v) {
    int len = 1;
    while (v > 0x7f) {
        len++;
        v >>= 7;
    }
    return len;
}

// Decode a little-endian base-128 var32 (Buffer::putVar32's encoding) at
// data[*off], advancing *off past it.
static u32 decodeVar32(const char *data, int *off) {
    u32 v = 0;
    int shift = 0;
    while (true) {
        char b = data[(*off)++];
        v |= (u32)(u8)(b & 0x7f) << shift;
        if ((b & 0x80) == 0) {
            return v;
        }
        shift += 7;
    }
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

    // A deterministic leaf <- middle <- root chain, in the same leaf-first
    // element order ReferenceChainTracker::buildChainEvent() produces (the
    // tracker-driven path to the identical event is covered by
    // referenceChains_ut.cpp's ReconstructsChainForSyntheticGraph; this file
    // pins the JFR encoding, so the event is built directly).
    ReferenceChainEvent event;
    event._target_tag = 3;
    event._depth = 2;
    event._root_kind = 21; // JVMTI_HEAP_REFERENCE_JNI_GLOBAL - exercises the
                           // rootKind field end to end, mirroring how
                           // heapReferenceCallback() only ever sets it on a
                           // parent_tag==0 entry.
    event._chain = {(u32)leafKlass, (u32)middleKlass, (u32)rootKlass};
    // With the null JNIEnv a live field-name decode would crash on this
    // binary's unstubbed JVMTI table, so the labels are the degraded
    // edge-KIND strings fillHopEdgeLabels() produces in exactly that
    // situation - which is what the Java-side parser test
    // (ReferenceChainJfrParserTest) asserts this recording's "edges" field
    // contains.
    event._edges = {"field", "element", "jni_global"};
    event._start_time = TSC::ticks();

    const std::string path = chainRoundtripJfrPath();
    {
        int fd = open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
        ASSERT_GE(fd, 0) << "could not open " << path << " for writing";

        // Recording(fd, args) and recordReferenceChain() are already public
        // production API (flightRecorder.h) - this drives the real chunk
        // header/metadata/settings write (constructor) and the real
        // datadog.ReferenceChain event encoding (recordReferenceChain(),
        // the exact F_CPOOL|F_ARRAY `chain` field this test exists to
        // answer for), not a hand-rolled byte layout.
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

// A chain longer than MAX_REFERENCE_CHAIN_EVENT_HOPS with worst-case (96
// byte) edge labels must be truncated to exactly the buffer-derived hop cap,
// and the emitted hops must keep their aligned edge labels - the first
// emitted_size entries of the leaf-first chain are the emitted range, so
// their labels are too. The whole event must stay inside the recording
// buffer (a hop cap permitting a worst case beyond RECORDING_BUFFER_LIMIT
// underflows recordReferenceChain()'s reservation and writes past the
// buffer).
TEST_F(ReferenceChainJfrRoundtripTest, TruncatesOversizeChainAndKeepsEmittedLabels) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    args._jfr_options = JFR_SYNC_OPTS;

    // Own file, NOT the companion JMC round-trip path: this test's event uses
    // raw class ids that were never registered in the class dictionary (no
    // JMC read-back is intended), and leaving it on the companion path would
    // make the Java parser test resolve every chain[] element to null.
    const std::string path = chainRoundtripJfrPath() + ".trunc";
    int fd = open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
    ASSERT_GE(fd, 0) << "could not open " << path << " for writing";

    u32 total_hops = (u32)MAX_REFERENCE_CHAIN_EVENT_HOPS + 40;
    std::string longest_label(MAX_REFERENCE_CHAIN_EDGE_LABEL, 'x');
    ReferenceChainEvent event;
    event._target_tag = 7;
    event._depth = (u32)total_hops;
    event._root_kind = 21;
    event._start_time = TSC::ticks();
    event._chain.reserve(total_hops);
    event._edges.reserve(total_hops);
    for (u32 i = 0; i < total_hops; i++) {
        // Small class ids (single-byte var32) and a small target tag keep
        // the byte walk below deterministic without constraining the
        // encoder.
        event._chain.push_back(100 + i);
        event._edges.push_back(longest_label);
    }

    Recording rec(fd, args);
    Buffer *buf = rec.buffer(/*lock_index=*/0);

    // Flush whatever the constructor wrote (limit 0 = always) so the event's
    // buffer position is deterministic: it starts at offset 0 and the
    // reservation inside recordReferenceChain() (margin = RECORDING_BUFFER_LIMIT
    // minus the worst case) cannot trigger a second flush for a freshly
    // flushed buffer.
    rec.flushIfNeeded(buf, /*limit=*/0);

    int offset_before = buf->offset();
    ASSERT_EQ(0, offset_before);
    rec.recordReferenceChain(buf, &event);
    int offset_after = buf->offset();

    // The whole event stayed inside the buffer - the exact invariant a fixed
    // 4096-hop cap broke with near-limit labels (worst case ~438 KB against
    // a ~61 KB buffer: debug assert, release write past the buffer).
    EXPECT_LE(offset_after, RECORDING_BUFFER_LIMIT);

    // Walk the just-written event's bytes. recordReferenceChain() reserves a
    // fixed MAX_VAR32_LENGTH size prefix and patches the minimal var32 over
    // its head, with the body always starting at offset_before +
    // MAX_VAR32_LENGTH (the skip() reservation), so the field offsets are
    // computable from the values this test chose.
    const char *data = buf->data() + offset_before;
    // The size prefix is Buffer::putVar32(int offset, u32)'s FIXED 5-byte
    // form: little-endian 7-bit groups with the continuation bit forced on
    // the first four bytes, so it decodes positionally, not via minimal
    // LEB128.
    auto decodeFixedVar32 = [&data](int off) {
        return (u32)(u8)data[off] | ((u32)(u8)data[off + 1] & 0x7fu) << 7 |
               ((u32)(u8)data[off + 2] & 0x7fu) << 14 |
               ((u32)(u8)data[off + 3] & 0x7fu) << 21 |
               ((u32)(u8)data[off + 4]) << 28;
    };
    u32 encoded_size = decodeFixedVar32(0);
    ASSERT_GT(encoded_size, 0u);
    ASSERT_EQ((u32)(offset_after - offset_before), encoded_size)
        << "the patched size prefix must cover exactly the written event";

    int off = MAX_VAR32_LENGTH; // body start: fixed reservation, then fields
    off += sizeOfVar64((u64)T_REFERENCE_CHAIN); // type id
    off += sizeOfVar64(event._start_time);
    off += sizeOfVar64(event._target_tag);
    off += sizeOfVar64(event._depth); // depth, small by construction
    // rootKind putUtf8: 1 encoding-tag byte + var32 length + payload.
    const char *root_kind_name = "jni_global"; // rootKindName(21)
    off += 1 + sizeOfVar64((u64)strlen(root_kind_name)) + (int)strlen(root_kind_name);
    u32 chain_size = decodeVar32(data, &off);
    u32 emitted_size = decodeVar32(data, &off);
    // The chain's own entries sit between the counts and the edge labels.
    for (u32 i = 0; i < emitted_size; i++) {
        decodeVar32(data, &off);
    }
    u32 edge_count = decodeVar32(data, &off);

    EXPECT_EQ(total_hops, chain_size)
        << "totalHops must carry the pre-truncation chain length";
    EXPECT_EQ((u32)MAX_REFERENCE_CHAIN_EVENT_HOPS, emitted_size)
        << "the event must be truncated to exactly the buffer-derived hop cap";
    EXPECT_EQ((u32)MAX_REFERENCE_CHAIN_EVENT_HOPS, edge_count)
        << "truncation keeps the emitted range's aligned edge labels - "
           "dropping all labels is the misaligned-array bug this pins";

    unlink(path.c_str());
}

// A default-constructed ObjectLivenessEvent must carry leak_tag == 0 so any
// construction path that forgets to set it serializes a defined "untagged"
// value instead of indeterminate data (recordHeapLiveObject() reads the
// field unconditionally).
TEST_F(ReferenceChainJfrRoundtripTest, DefaultLivenessEventHasZeroLeakTag) {
    ObjectLivenessEvent event;
    EXPECT_EQ(0, event.leak_tag);
}
