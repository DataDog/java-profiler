/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// ---------------------------------------------------------------------------
// Byte-level JFR encoding checks for the datadog.ReferenceChain event: drives
// the real production write path (Recording/recordReferenceChain/
// recordHeapLiveObject) to produce a complete, chunk-finalized .jfr file, and
// pins two properties only checkable at the byte level:
//  - a chain over MAX_REFERENCE_CHAIN_EVENT_HOPS is truncated to the
//    buffer-derived cap, keeping the emitted hops' edge labels aligned
//    (a cap permitting a worst case beyond the buffer would write past
//    RECORDING_BUFFER_LIMIT);
//  - ObjectLivenessEvent::leak_tag defaults to 0 - a defined "untagged" value.
//
// No live JVM here, so Recording's NULL dependencies (Profiler::cpuEngine()
// /wallEngine(), VM::jni(), VM::libjvm()) are injected via the friend
// accessors already declared in vmEntry.h / profiler.h.
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
// VMTestAccessor - friend of VM (vmEntry.h); per-_ut.cpp copy, as in
// referenceChains_ut.cpp. _vm setter needed: Recording::finishChunk() calls
// VM::jni(), dereferencing VM::_vm (NULL without a live JVM).
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
// ProfilerTestAccessor - friend of Profiler (profiler.h). Recording::
// finishChunk() dereferences Profiler::instance()->cpuEngine()/wallEngine()
// (NULL until Profiler::start()); Engine's base methods are safe no-ops.
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

// Recording::finishChunk() pins loaded classes via GetLoadedClasses(); zero
// is faithful here - no JVMTI-visible classes exist without a live JVM.
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

        // writeSettings() calls VM::libjvm()->hasDebugSymbols(); a name-only
        // CodeCache degrades to no symbols, like an unresolved real library.
        static CodeCache fake_libjvm("fake_libjvm.so");
        orig_libjvm = VMTestAccessor::getLibjvm();
        VMTestAccessor::setLibjvm(&fake_libjvm);

        // VMStructs::_libjvm is a separate cache from VM::libjvm() above;
        // nothing in this test's write path reads it, but keep the
        // process-wide singleton consistent for this fixture.
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

// Resolved via the OS temp dir.
static std::string chainRoundtripJfrPath() {
    const char *tmp = getenv("TMPDIR");
    std::string dir = (tmp != nullptr && *tmp != 0) ? tmp : "/tmp";
    if (dir.back() != '/') {
        dir += '/';
    }
    return dir + "datadog_reference_chain_roundtrip.jfr";
}

// Length of Buffer::putVar64()'s encoding for v: its 3-bytes-per-group
// shortcut carries the same bits per byte as plain LEB128, so lengths agree.
static int sizeOfVar64(u64 v) {
    int len = 1;
    while (v > 0x7f) {
        len++;
        v >>= 7;
    }
    return len;
}

// Decode Buffer::putVar32's little-endian base-128 var32 at data[*off].
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
    // enumeration - they need JVMTI/JNI entry points this fixture does not mock.
    args._jfr_options = JFR_SYNC_OPTS;

    // writeMetadata() serializes JfrMetadata::root() as-is; the tree is built
    // once by JfrMetadata::initialize() (normally from Profiler::start(),
    // which this test cannot call). initialize() is public, JVM-independent
    // and idempotent; without it writeMetadata() would emit an empty root
    // element with no datadog.ReferenceChain type declaration.
    // initialize() allocates that static tree for the life of the process -
    // LeakSanitizer would flag it on test exit, so disable leak detection
    // for this call only.
#ifdef ASAN_ENABLED
    {
      __lsan::ScopedDisabler lsan_disabler;
      JfrMetadata::initialize(args._context_attributes);
    }
#else
    JfrMetadata::initialize(args._context_attributes);
#endif

    // Register three class names in the StringDictionary writeClasses() serializes.
    int leafKlass = Profiler::instance()->lookupClass(
        "com/test/ChainLeaf", strlen("com/test/ChainLeaf"));
    int middleKlass = Profiler::instance()->lookupClass(
        "com/test/ChainMiddle", strlen("com/test/ChainMiddle"));
    int rootKlass = Profiler::instance()->lookupClass(
        "com/test/ChainRoot", strlen("com/test/ChainRoot"));
    ASSERT_NE(-1, leafKlass);
    ASSERT_NE(-1, middleKlass);
    ASSERT_NE(-1, rootKlass);

    // writeClasses() only serializes classMap()->standby() (captured by
    // rotate()); without this the lookups never reach the checkpoint.
    Profiler::instance()->classMap()->rotate();

    // Deterministic leaf <- middle <- root chain, leaf-first like production.
    ReferenceChainEvent event;
    event._target_tag = 3;
    event._depth = 2;
    event._root_kind = 21; // JVMTI_HEAP_REFERENCE_JNI_GLOBAL - exercises the
                           // rootKind field end to end.
    // Null JNIEnv: labels are the degraded edge-KIND strings production resolves to.
    event._hops = {{(u32)leafKlass, "field"},
                   {(u32)middleKlass, "element"},
                   {(u32)rootKlass, "jni_global"}};
    event._start_time = TSC::ticks();

    const std::string path = chainRoundtripJfrPath();
    {
        int fd = open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
        ASSERT_GE(fd, 0) << "could not open " << path << " for writing";

        // Real production write path: chunk header/metadata/settings
        // (Recording ctor) plus the datadog.ReferenceChain event encoding.
        Recording rec(fd, args);
        Buffer *buf = rec.buffer(/*lock_index=*/0);
        rec.recordReferenceChain(buf, &event);
        // ~Recording() calls finishChunk(true): flushes buf, writes the class
        // checkpoint (what makes the three klasses resolvable), patches the
        // chunk header, and closes fd.
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

// A chain over MAX_REFERENCE_CHAIN_EVENT_HOPS with worst-case (96 byte) edge
// labels is truncated to the buffer-derived hop cap, keeping the emitted
// hops' aligned edge labels, and stays inside the recording buffer.
TEST_F(ReferenceChainJfrRoundtripTest, TruncatesOversizeChainAndKeepsEmittedLabels) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    args._jfr_options = JFR_SYNC_OPTS;

    // Own file: this event's raw class ids were never registered, so keep it
    // off the round-trip path.
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
    event._hops.reserve(total_hops);
    for (u32 i = 0; i < total_hops; i++) {
        // Small class ids (single-byte var32) keep the byte walk deterministic.
        event._hops.push_back({100 + i, longest_label});
    }

    Recording rec(fd, args);
    Buffer *buf = rec.buffer(/*lock_index=*/0);

    // Flush the constructor's output (limit 0 = always) so the event starts
    // at offset 0 and recordReferenceChain()'s reservation cannot re-flush.
    rec.flushIfNeeded(buf, /*limit=*/0);

    int offset_before = buf->offset();
    ASSERT_EQ(0, offset_before);
    rec.recordReferenceChain(buf, &event);
    int offset_after = buf->offset();

    // The whole event stayed inside the buffer.
    EXPECT_LE(offset_after, RECORDING_BUFFER_LIMIT);

    // Walk the just-written event's bytes. recordReferenceChain() reserves a
    // fixed MAX_VAR32_LENGTH size prefix and patches the minimal var32 over
    // its head, with the body starting at offset_before + MAX_VAR32_LENGTH.
    const char *data = buf->data() + offset_before;
    // The size prefix is putVar32(int, u32)'s FIXED 5-byte form (continuation
    // bit forced on the first four bytes): positional, not minimal LEB128.
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
    off += sizeOfVar64(event._depth);
    // rootKind putUtf8: 1 encoding-tag byte + var32 length + payload.
    const char *root_kind_name = "jni_global"; // rootKindName(21)
    off += 1 + sizeOfVar64((u64)strlen(root_kind_name)) + (int)strlen(root_kind_name);
    u32 chain_size = decodeVar32(data, &off);
    u32 emitted_size = decodeVar32(data, &off);
    for (u32 i = 0; i < emitted_size; i++) { // skip chain entries
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

// A default-constructed ObjectLivenessEvent must carry leak_tag == 0 so a
// path that forgets to set it serializes a defined "untagged" value.
TEST_F(ReferenceChainJfrRoundtripTest, DefaultLivenessEventHasZeroLeakTag) {
    ObjectLivenessEvent event;
    EXPECT_EQ(0, event.leak_tag);
}
