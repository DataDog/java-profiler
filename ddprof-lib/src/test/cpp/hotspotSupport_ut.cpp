/*
 * Copyright 2026, Datadog, Inc.
 */

#include <gtest/gtest.h>
#include <cerrno>
#include <cstddef>
#include <functional>
#include <memory>
#include <system_error>
#include <vector>
#include <sys/mman.h>
#include <unistd.h>
#include "../../main/cpp/asyncSampleMutex.h"
#include "../../main/cpp/jvmSupport.h"
#include "../../main/cpp/jvmThread.h"
#include "../../main/cpp/os.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/hotspot/vmStructs.inline.h"

static constexpr char HOTSPOT_SUPPORT_TEST_NAME[] = "HotspotSupportTest";
class HotspotSupportGlobalSetup {
public:
    HotspotSupportGlobalSetup()  { installGtestCrashHandler<HOTSPOT_SUPPORT_TEST_NAME>(); }
    ~HotspotSupportGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static HotspotSupportGlobalSetup hotspot_support_global_setup;

// Existing friend seam for receiver capture, ASGCT recovery and method-ID loading.
class HotspotSupportTestAccessor {
public:
    static VMSymbol* captureVtableReceiver(HotspotStackFrame& frame, uintptr_t pc,
                                          uintptr_t sp, uintptr_t fp, StackWalkFeatures features) {
        return HotspotSupport::captureVtableReceiver(frame, pc, sp, fp, features);
    }

    static int getJavaTraceAsync(void* context, ASGCT_CallFrame* frames, int max_depth,
                                 StackContext* java_ctx, bool* truncated = nullptr) {
        HotspotStackFrame::RegisterSnapshot snapshot(context);
        return HotspotSupport::getJavaTraceAsync(context, frames, max_depth, java_ctx, truncated, snapshot);
    }

    static int getJavaTraceAsyncWithRecovery(void* context, ASGCT_CallFrame* frames, int max_depth,
                                             StackContext* java_ctx, bool* truncated) {
        volatile int depth = 0;
        return HotspotSupport::withUcontextFaultRecovery(
            context, ProfiledThread::current(), truncated, depth,
            [&](HotspotStackFrame::RegisterSnapshot& snapshot) {
                depth = HotspotSupport::getJavaTraceAsync(context, frames, max_depth, java_ctx, truncated, snapshot);
            });
    }

    static uintptr_t receiverCapturePC() {
        return reinterpret_cast<uintptr_t>(&HotspotSupport::captureVtableReceiver);
    }

    static int walkVM(void* context, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, bool seeded_from_anchor) {
        HotspotStackFrame frame(context);
        return HotspotSupport::walkVM(context, frames, max_depth, features, EXECUTION_SAMPLE,
                                      reinterpret_cast<const void*>(frame.pc()), seeded_from_anchor,
                                      frame.sp(), frame.fp(), 0, nullptr, seeded_from_anchor);
    }

    static bool loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all) {
        return HotspotSupport::loadMethodIDsIfNeededImpl(jvmti, jni, klass, load_all);
    }
};

// ---------------------------------------------------------------------------
// Mock JVMTI infrastructure. With load_all=true, loadMethodIDsIfNeededImpl()
// skips its hidden-class/system-classloader checks entirely and calls
// patchClassLoaderData() (a no-op here, since VM::hotspot_version() defaults
// to 0 -- not 8 -- in this gtest binary with no live JVM attached) followed
// by JVMSupport::loadMethodIDsImpl(), whose only JVMTI calls are
// GetClassMethods and Deallocate.
// ---------------------------------------------------------------------------
static int g_get_class_methods_calls = 0;

static jvmtiError JNICALL mock_GetClassMethods_ok(jvmtiEnv*, jclass, jint* method_count_ptr, jmethodID** methods_ptr) {
    g_get_class_methods_calls++;
    *method_count_ptr = 0;
    *methods_ptr = nullptr;
    return JVMTI_ERROR_NONE;
}
static jvmtiError JNICALL mock_Deallocate_noop(jvmtiEnv*, unsigned char*) {
    return JVMTI_ERROR_NONE;
}

class HotspotSupportLoadMethodIDsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_jvmti{};

    void SetUp() override {
        g_get_class_methods_calls = 0;
        tbl = jvmtiInterface_1_{};
        tbl.GetClassMethods = &mock_GetClassMethods_ok;
        tbl.Deallocate = &mock_Deallocate_noop;
        mock_jvmti.functions = &tbl;
    }
};

TEST_F(HotspotSupportLoadMethodIDsTest, LoadAllSucceedsAndCallsGetClassMethodsOnce) {
    jclass fake_klass = reinterpret_cast<jclass>(0x1);

    bool result = HotspotSupportTestAccessor::loadMethodIDsIfNeededImpl(
        &mock_jvmti, /*jni=*/nullptr, fake_klass, /*load_all=*/true);

    EXPECT_TRUE(result);
    EXPECT_EQ(1, g_get_class_methods_calls)
        << "the <clinit> resolve() fallback must go through this exact path "
           "(load_all=true), which is what now applies patchClassLoaderData() "
           "before allocating jmethodIDs";
}

// Model an uncompressed oop -> Klass -> Symbol chain. These scoped overrides
// use the same VMStructs offsets as production, without requiring a live JVM.
class VMStructsTestAccessor {
    bool _has_class_names = VMStructs::_has_class_names;
    int _narrow_klass_shift = VMStructs::_narrow_klass_shift;
    int _oop_klass_offset = VMStructs::_oop_klass_offset;
    int _klass_name_offset = VMStructs::_klass_name_offset;
    uint64_t _klass_size = VMStructs::TYPE_SIZE_NAME(VMKlass);
    uint64_t _symbol_size = VMStructs::TYPE_SIZE_NAME(VMSymbol);
    std::vector<std::function<void()>> _restores;
public:
    VMStructsTestAccessor() {
        VMStructs::_has_class_names = true;
        VMStructs::_narrow_klass_shift = -1;
        VMStructs::_oop_klass_offset = sizeof(uintptr_t);
        VMStructs::_klass_name_offset = 0;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = sizeof(uintptr_t);
        VMStructs::TYPE_SIZE_NAME(VMSymbol) = sizeof(uintptr_t);
    }
    ~VMStructsTestAccessor() {
        for (auto it = _restores.rbegin(); it != _restores.rend(); ++it) (*it)();
        VMStructs::_has_class_names = _has_class_names;
        VMStructs::_narrow_klass_shift = _narrow_klass_shift;
        VMStructs::_oop_klass_offset = _oop_klass_offset;
        VMStructs::_klass_name_offset = _klass_name_offset;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = _klass_size;
        VMStructs::TYPE_SIZE_NAME(VMSymbol) = _symbol_size;
    }
    VMStructsTestAccessor(const VMStructsTestAccessor&) = delete;
    VMStructsTestAccessor& operator=(const VMStructsTestAccessor&) = delete;
    void disableClassNames() { VMStructs::_has_class_names = false; }

    template<typename T> void set(T& field, T value) {
        T previous = field;
        _restores.emplace_back([&field, previous] { field = previous; });
        field = value;
    }
};

class VMTestAccessor {
    bool _hotspot = VM::_hotspot;
public:
    VMTestAccessor() { VM::_hotspot = true; }
    ~VMTestAccessor() { VM::_hotspot = _hotspot; }
    VMTestAccessor(const VMTestAccessor&) = delete;
    VMTestAccessor& operator=(const VMTestAccessor&) = delete;
    static JavaVM*& javaVM() { return VM::_vm; }
    static AsyncGetCallTrace& asgct() { return VM::_asyncGetCallTrace; }
};

class VtableReceiverCaptureTest : public ::testing::Test {
protected:
    VMTestAccessor _vm;
    VMStructsTestAccessor _layout;
    ucontext_t _ctx{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT _mctx{};
#endif
    uintptr_t _symbol = 0;
    void* _klass = &_symbol;
    uintptr_t _oop[2] = {0, reinterpret_cast<uintptr_t>(&_klass)};
    StackWalkFeatures _features{};

    void SetUp() override {
#ifdef __APPLE__
        _ctx.uc_mcontext = &_mctx;
#endif
        HotspotStackFrame frame(&_ctx);
        frame.restore(0x1000, 0x2000, 0x3000);
        setReceiver(reinterpret_cast<uintptr_t>(_oop));
        _features.vtable_target = 1;
    }

    void setReceiver(uintptr_t receiver) {
#if defined(__APPLE__) && defined(__aarch64__)
        _ctx.uc_mcontext->__ss.__x[1] = receiver;
#elif defined(__APPLE__) && defined(__x86_64__)
        _ctx.uc_mcontext->__ss.__rsi = receiver;
#elif defined(__aarch64__)
        _ctx.uc_mcontext.regs[1] = receiver;
#elif defined(__x86_64__)
        _ctx.uc_mcontext.gregs[REG_RSI] = receiver;
#endif
    }

    VMSymbol* capture(uintptr_t pc = 0x1000, uintptr_t sp = 0x2000, uintptr_t fp = 0x3000) {
        HotspotStackFrame frame(&_ctx);
        return HotspotSupportTestAccessor::captureVtableReceiver(frame, pc, sp, fp, _features);
    }
};

TEST_F(VtableReceiverCaptureTest, CapturesRawSymbolFromInterruptedReceiver) {
    EXPECT_EQ(reinterpret_cast<VMSymbol*>(&_symbol), capture());
}

TEST_F(VtableReceiverCaptureTest, RejectsRecoveredCallerWithInterruptedArguments) {
    // Mimic java_ctx redirecting pc/sp/fp while the argument registers still
    // contain the interrupted leaf's receiver. Any changed coordinate rejects it.
    EXPECT_EQ(nullptr, capture(0x1004));
    EXPECT_EQ(nullptr, capture(0x1000, 0x2008));
    EXPECT_EQ(nullptr, capture(0x1000, 0x2000, 0x3010));
    HotspotStackFrame(&_ctx).restore(0x4000, 0x5000, 0x6000);
    EXPECT_EQ(nullptr, capture());
}

TEST_F(VtableReceiverCaptureTest, DisabledFeatureDoesNotReadRegisters) {
    _features.vtable_target = 0;
    HotspotStackFrame frame(nullptr);
    EXPECT_EQ(nullptr, HotspotSupportTestAccessor::captureVtableReceiver(frame, 0, 0, 0, _features));
}

TEST_F(VtableReceiverCaptureTest, MissingClassNamesDoesNotReadRegisters) {
    _layout.disableClassNames();
    HotspotStackFrame frame(nullptr);
    EXPECT_EQ(nullptr, HotspotSupportTestAccessor::captureVtableReceiver(frame, 0, 0, 0, _features));
}

TEST_F(VtableReceiverCaptureTest, NullReceiverKlassAndSymbolAreNotCaptured) {
    setReceiver(0);
    EXPECT_EQ(nullptr, capture());
    setReceiver(reinterpret_cast<uintptr_t>(_oop));
    _oop[1] = 0;
    EXPECT_EQ(nullptr, capture());
    _oop[1] = reinterpret_cast<uintptr_t>(&_klass);
    _klass = nullptr;
    EXPECT_EQ(nullptr, capture());
}

class ProfilerTestAccessor {
public:
    static CStack& cstack() { return Profiler::instance()->_cstack; }
    static StackWalkFeatures& features() { return Profiler::instance()->_features; }
    static int& safeMode() { return Profiler::instance()->_safe_mode; }
};

class JVMThreadTestAccessor {
    pthread_key_t _old_key = JVMThread::key();
    jfieldID _old_tid = JVMThread::_tid;
    pthread_key_t _key = INVALID_KEY;
public:
    bool install(void* thread) {
        if (pthread_key_create(&_key, nullptr) != 0) return false;
        if (pthread_setspecific(_key, thread) != 0) return false;
        JVMThread::_jvm_thread._key = _key;
        JVMThread::_tid = reinterpret_cast<jfieldID>(1);
        return true;
    }
    ~JVMThreadTestAccessor() {
        JVMThread::_jvm_thread._key = _old_key;
        JVMThread::_tid = _old_tid;
        if (_key != INVALID_KEY) pthread_key_delete(_key);
    }
    JVMThreadTestAccessor() = default;
    JVMThreadTestAccessor(const JVMThreadTestAccessor&) = delete;
    JVMThreadTestAccessor& operator=(const JVMThreadTestAccessor&) = delete;
};

namespace {

std::vector<int> asgct_budgets;
std::vector<uintptr_t> asgct_pcs;
bool asgct_retry_fails = false;
int asgct_initial_error = ticks_unknown_Java;

void stubAsgct(ASGCT_CallTrace* trace, jint max_depth, void* context) {
    asgct_budgets.push_back(max_depth);
    asgct_pcs.push_back(StackFrame(context).pc());
    if (asgct_budgets.size() == 1 || asgct_retry_fails) {
        trace->num_frames = asgct_initial_error;
    } else {
        ASSERT_GT(max_depth, 0);
        trace->frames[0].bci = 0;
        trace->frames[0].method_id = reinterpret_cast<jmethodID>(0x1230);
        trace->num_frames = 1;
    }
}

jint JNICALL stubGetEnv(JavaVM*, void** env, jint) {
    *env = reinterpret_cast<JNIEnv*>(1);
    return JNI_OK;
}

} // namespace

// Modeled thread, CodeHeap and object layouts plus mocked GetEnv/ASGCT calls
// drive the production walkers' receiver capture, prefix insertion and unwinding.
class AsgctVtableReceiverTest : public VtableReceiverCaptureTest,
                               protected VMStructs, public ::testing::WithParamInterface<bool> {
protected:
    struct Anchor { uintptr_t sp; uintptr_t fp; const void* pc; };
    struct Thread { uintptr_t state; Anchor anchor; } _thread{};
    struct Blob {
        const char* name;
        instruction_t code[8];
        int size;
        int code_offset;
        int frame_size;
        void* method;
        signed char state;
    };
    struct alignas(256) Block { uintptr_t used; Blob blob; };
    // Runtime-stub registration is append-only, so the registered code outlives every fixture.
    static Block _blocks[2];
    struct Heap { void* low; void* high; void* map; } _heap{};
    unsigned char _segmap[2]{};
    JVMThreadTestAccessor _jvm_thread;
    JNIInvokeInterface_ _invoke{};
    JavaVM_ _java_vm{};
    uintptr_t _stack[8]{};
    ASGCT_CallFrame _frames[5]{};

public:
    static void SetUpTestSuite() {
        for (Block& block : _blocks) {
            block.used = 1;
            block.blob.name = "vtable chunks test";
            block.blob.size = sizeof(Blob);
            block.blob.code_offset = offsetof(Blob, code);
#ifdef __aarch64__
            block.blob.code[0] = 0xd65f03c0; // ret: unwind to the saved link register
#else
            block.blob.code[0] = 0xc3; // ret: unwind to the return-address slot
#endif
        }
        JitCodeCache::DynamicCodeGenerated(nullptr, "vtable chunks test",
                                           _blocks[0].blob.code, sizeof(Blob::code));
    }

protected:
    void SetUp() override {
        VtableReceiverCaptureTest::SetUp();
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        ProfiledThread::current()->setJavaThread(true);
        ASSERT_TRUE(_jvm_thread.install(&_thread));
        _invoke.GetEnv = stubGetEnv;
        _java_vm.functions = &_invoke;
        _layout.set(VMTestAccessor::javaVM(), &_java_vm);
        _layout.set(VMTestAccessor::asgct(), &stubAsgct);
        _layout.set(ProfilerTestAccessor::cstack(), CSTACK_DWARF);
        _layout.set(ProfilerTestAccessor::features(), _features);
        _layout.set(ProfilerTestAccessor::safeMode(), 0);
        _layout.set(TYPE_SIZE_NAME(VMThread), uint64_t(sizeof(Thread)));
        _layout.set(TYPE_SIZE_NAME(VMJavaFrameAnchor), uint64_t(sizeof(Anchor)));
        _layout.set(TYPE_SIZE_NAME(VMNMethod), uint64_t(sizeof(Blob)));
        _layout.set(_thread_state_offset, offset(offsetof(Thread, state)));
        _layout.set(_thread_anchor_offset, offset(offsetof(Thread, anchor)));
        _layout.set(_anchor_sp_offset, offset(offsetof(Anchor, sp)));
        _layout.set(_anchor_fp_offset, offset(offsetof(Anchor, fp)));
        _layout.set(_anchor_pc_offset, offset(offsetof(Anchor, pc)));
        _layout.set(_has_method_structs, true);
        _layout.set(_code_heap_low, static_cast<const void*>(_blocks));
        _layout.set(_code_heap_high, static_cast<const void*>(_blocks + 2));
        _layout.set(_code_heap[0], reinterpret_cast<char*>(&_heap));
        _layout.set(_code_heap[1], static_cast<char*>(nullptr));
        _layout.set(_code_heap[2], static_cast<char*>(nullptr));
        _layout.set(_code_heap_memory_offset, offset(0));
        _layout.set(_code_heap_segmap_offset, offset(offsetof(Heap, map)));
        _layout.set(_code_heap_segment_shift, offset(8));
        _layout.set(_heap_block_used_offset, offset(0));
        _layout.set(_vs_low_offset, offset(offsetof(Heap, low)));
        _layout.set(_vs_high_offset, offset(offsetof(Heap, high)));
        _layout.set(_nmethod_name_offset, offset(offsetof(Blob, name)));
        _layout.set(_blob_size_offset, offset(offsetof(Blob, size)));
        _layout.set(_code_offset, offset(offsetof(Blob, code_offset)));
        _layout.set(_frame_size_offset, offset(offsetof(Blob, frame_size)));
        _heap = {_blocks, _blocks + 2, _segmap};
        ASSERT_EQ(reinterpret_cast<VMNMethod*>(&_blocks[GetParam() ? 0 : 1].blob),
                  CodeHeap::findNMethod(reinterpret_cast<const void*>(leafPC())));
        const void* stub_start = nullptr;
        const char* stub_name = nullptr;
        ASSERT_EQ(GetParam(), JitCodeCache::findRuntimeStub(reinterpret_cast<const void*>(leafPC()),
                                                          &stub_start, &stub_name));
        _thread.state = _thread_in_Java;
        _thread.anchor = {reinterpret_cast<uintptr_t>(_stack), 0, _blocks[0].blob.code};
        _stack[0] = callerAddress();
        asgct_retry_fails = false;
        _layout.set(asgct_initial_error, static_cast<int>(ticks_unknown_Java));
    }

    void TearDown() override {
        ProfiledThread::release();
    }

    uintptr_t leafPC() { return reinterpret_cast<uintptr_t>(_blocks[GetParam() ? 0 : 1].blob.code); }
    uintptr_t callerAddress() { return reinterpret_cast<uintptr_t>(_blocks[0].blob.code + 2); }
    uintptr_t retryPC() {
#ifdef __x86_64__
        return callerAddress() - 1;
#else
        return callerAddress();
#endif
    }

    void prepareWalk() {
        asgct_budgets.clear();
        asgct_pcs.clear();
        for (ASGCT_CallFrame& frame : _frames) {
            frame.bci = 12345;
            frame.method_id = reinterpret_cast<jmethodID>(0x5670);
        }
        HotspotStackFrame(&_ctx).restore(leafPC(), reinterpret_cast<uintptr_t>(_stack), 0);
#if defined(__APPLE__) && defined(__aarch64__)
        _ctx.uc_mcontext->__ss.__lr = callerAddress();
#elif defined(__aarch64__)
        _ctx.uc_mcontext.regs[30] = callerAddress();
#endif
    }

    int walk(int max_depth, StackContext java_ctx = {}, bool* truncated = nullptr) {
        prepareWalk();
        return HotspotSupportTestAccessor::getJavaTraceAsync(&_ctx, _frames, max_depth, &java_ctx, truncated);
    }

    void expectCanary(int index) {
        EXPECT_EQ(12345, _frames[index].bci);
        EXPECT_EQ(reinterpret_cast<jmethodID>(0x5670), _frames[index].method_id);
    }
};

AsgctVtableReceiverTest::Block AsgctVtableReceiverTest::_blocks[2]{};

// Each member restores its own full action, including when a later install throws.
class ReceiverReadSignalActionScope {
    int _signo;
    struct sigaction _old{};
public:
    ReceiverReadSignalActionScope(int signo, const struct sigaction& action) : _signo(signo) {
        if (sigaction(signo, &action, &_old) != 0) {
            throw std::system_error(errno, std::generic_category(), "install receiver-read signal action");
        }
    }
    ~ReceiverReadSignalActionScope() {
        EXPECT_EQ(0, sigaction(_signo, &_old, nullptr));
    }
    ReceiverReadSignalActionScope(const ReceiverReadSignalActionScope&) = delete;
    ReceiverReadSignalActionScope& operator=(const ReceiverReadSignalActionScope&) = delete;
};

class ReceiverReadFaultScope {
    ReceiverReadSignalActionScope _segv;
    ReceiverReadSignalActionScope _bus;
    static volatile sig_atomic_t _count;
    static volatile uintptr_t _address;
    static volatile uintptr_t _pc;

    static void recordFault(siginfo_t* info, void* context) {
        _count++;
        _address = reinterpret_cast<uintptr_t>(info->si_addr);
        _pc = StackFrame(context).pc();
    }
    static void segvHandler(int signo, siginfo_t* info, void* context) {
        recordFault(info, context);
        Profiler::segvHandler(signo, info, context);
        _exit(128 + signo);
    }
    static void busHandler(int signo, siginfo_t* info, void* context) {
        recordFault(info, context);
        Profiler::busHandler(signo, info, context);
        _exit(128 + signo);
    }
    static struct sigaction faultAction(SigAction handler) {
        struct sigaction action{};
        sigemptyset(&action.sa_mask);
        action.sa_sigaction = handler;
        action.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
        return action;
    }

public:
    static constexpr uintptr_t RANGE_MARGIN = 256 * 1024;
    ReceiverReadFaultScope() : _segv(SIGSEGV, faultAction(segvHandler)), _bus(SIGBUS, faultAction(busHandler)) {
        _count = 0;
        _address = _pc = 0;
        uintptr_t capture_pc = HotspotSupportTestAccessor::receiverCapturePC();
        Profiler::setAddressRangeForTest(capture_pc - RANGE_MARGIN, capture_pc + RANGE_MARGIN);
    }
    ~ReceiverReadFaultScope() {
        Profiler::resetAddressRangeForTest();
    }
    ReceiverReadFaultScope(const ReceiverReadFaultScope&) = delete;
    ReceiverReadFaultScope& operator=(const ReceiverReadFaultScope&) = delete;
    static int count() { return _count; }
    static uintptr_t address() { return _address; }
    static uintptr_t pc() { return _pc; }
};

volatile sig_atomic_t ReceiverReadFaultScope::_count = 0;
volatile uintptr_t ReceiverReadFaultScope::_address = 0;
volatile uintptr_t ReceiverReadFaultScope::_pc = 0;

static void expectSignalActionRestored(int signo, const struct sigaction& before) {
    SCOPED_TRACE(signo);
    struct sigaction after{};
    ASSERT_EQ(0, sigaction(signo, nullptr, &after));
    EXPECT_EQ(before.sa_flags, after.sa_flags);
    if (before.sa_flags & SA_SIGINFO) {
        EXPECT_EQ(before.sa_sigaction, after.sa_sigaction);
    } else {
        EXPECT_EQ(before.sa_handler, after.sa_handler);
    }
    for (int signal = 1; signal < NSIG; signal++) {
        EXPECT_EQ(sigismember(&before.sa_mask, signal), sigismember(&after.sa_mask, signal)) << signal;
    }
}

TEST(ReceiverReadFaultScopeTest, RestoresDistinctFullActionsAcrossRepeatedScopes) {
    struct sigaction original_segv{}, original_bus{};
    ASSERT_EQ(0, sigaction(SIGSEGV, nullptr, &original_segv));
    ASSERT_EQ(0, sigaction(SIGBUS, nullptr, &original_bus));
    {
        struct sigaction segv_action = original_segv;
        segv_action.sa_flags = SA_SIGINFO | SA_ONSTACK;
        ASSERT_EQ(0, sigaddset(&segv_action.sa_mask, SIGUSR1));
        struct sigaction bus_action{};
        bus_action.sa_handler = SIG_IGN;
        bus_action.sa_flags = SA_RESTART;
        ASSERT_EQ(0, sigemptyset(&bus_action.sa_mask));
        ASSERT_EQ(0, sigaddset(&bus_action.sa_mask, SIGUSR2));
        ReceiverReadSignalActionScope segv_scope(SIGSEGV, segv_action);
        ReceiverReadSignalActionScope bus_scope(SIGBUS, bus_action);
        struct sigaction before_segv{}, before_bus{};
        ASSERT_EQ(0, sigaction(SIGSEGV, nullptr, &before_segv));
        ASSERT_EQ(0, sigaction(SIGBUS, nullptr, &before_bus));
        for (int repetition = 0; repetition < 2; repetition++) {
            SCOPED_TRACE(repetition);
            {
                ReceiverReadFaultScope fault_scope;
                for (int signo : {SIGSEGV, SIGBUS}) {
                    struct sigaction installed{};
                    ASSERT_EQ(0, sigaction(signo, nullptr, &installed));
                    constexpr int fault_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
                    EXPECT_EQ(fault_flags, installed.sa_flags & fault_flags);
                    EXPECT_NE(before_segv.sa_sigaction, installed.sa_sigaction);
                    EXPECT_NE(SIG_IGN, installed.sa_handler);
                    for (int signal = 1; signal < NSIG; signal++) {
                        EXPECT_EQ(0, sigismember(&installed.sa_mask, signal)) << signal;
                    }
                }
            }
            expectSignalActionRestored(SIGSEGV, before_segv);
            expectSignalActionRestored(SIGBUS, before_bus);
        }
    }
    expectSignalActionRestored(SIGSEGV, original_segv);
    expectSignalActionRestored(SIGBUS, original_bus);
}

TEST(ReceiverReadFaultScopeTest, RollsBackEarlierActionWhenLaterInstallationFails) {
    struct sigaction before_segv{}, before_bus{};
    ASSERT_EQ(0, sigaction(SIGSEGV, nullptr, &before_segv));
    ASSERT_EQ(0, sigaction(SIGBUS, nullptr, &before_bus));
    struct sigaction action{};
    action.sa_handler = SIG_IGN;
    ASSERT_EQ(0, sigemptyset(&action.sa_mask));
    ASSERT_EQ(0, sigaddset(&action.sa_mask, SIGUSR1));
    EXPECT_THROW({
        ReceiverReadSignalActionScope segv_scope(SIGSEGV, action);
        struct sigaction installed{};
        ASSERT_EQ(0, sigaction(SIGSEGV, nullptr, &installed));
        ASSERT_EQ(SIG_IGN, installed.sa_handler);
        ReceiverReadSignalActionScope invalid_scope(-1, action);
    }, std::system_error);
    expectSignalActionRestored(SIGSEGV, before_segv);
    expectSignalActionRestored(SIGBUS, before_bus);
}

TEST_P(AsgctVtableReceiverTest, VmReceiverPrefixReservesTheStubAtShallowDepth) {
    // Keep the native-transition anchor empty so the walk stays on the interrupted leaf.
    _thread.anchor = {};
    for (int budget : {0, 1, 2}) {
        SCOPED_TRACE(budget);
        prepareWalk();
        ASSERT_EQ(budget, HotspotSupportTestAccessor::walkVM(&_ctx, _frames, budget, _features, false));
        EXPECT_TRUE(asgct_budgets.empty());
        if (budget == 2) {
            EXPECT_EQ(BCI_VTABLE_RECEIVER, _frames[0].bci);
            EXPECT_EQ(reinterpret_cast<jmethodID>(&_symbol), _frames[0].method_id);
        }
        if (budget > 0) {
            EXPECT_EQ(BCI_NATIVE_FRAME, _frames[budget - 1].bci);
            EXPECT_STREQ("vtable chunks test", reinterpret_cast<const char*>(_frames[budget - 1].method_id));
        }
        expectCanary(budget);
    }
}

TEST_P(AsgctVtableReceiverTest, VmAnchorSeededReturnAddressDoesNotCaptureInterruptedArguments) {
    for (int budget : {1, 2}) {
        SCOPED_TRACE(budget);
        prepareWalk();
        _thread.anchor = {reinterpret_cast<uintptr_t>(_stack), 0, reinterpret_cast<const void*>(leafPC())};
        ASSERT_EQ(budget, HotspotSupportTestAccessor::walkVM(&_ctx, _frames, budget, _features, true));
        EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
        EXPECT_STREQ("vtable chunks test", reinterpret_cast<const char*>(_frames[0].method_id));
        if (budget == 2) {
            EXPECT_EQ(BCI_ERROR, _frames[1].bci);
            EXPECT_STREQ("break_unwind_stub_failed", reinterpret_cast<const char*>(_frames[1].method_id));
        }
        EXPECT_TRUE(asgct_budgets.empty());
        expectCanary(budget);
    }
}

TEST_P(AsgctVtableReceiverTest, CompiledPrefixSaturationDoesNotRetryWithZeroBudget) {
    struct Klass { jmethodID* ids; };
    struct Pool { Klass* holder; };
    struct ConstMethod { Pool* constants; uint32_t idnum; };
    struct Method { ConstMethod* const_method; };
    jmethodID ids[] = {reinterpret_cast<jmethodID>(1), reinterpret_cast<jmethodID>(0x4560)};
    Klass klass{ids};
    Pool pool{&klass};
    ConstMethod const_method{&pool, 0};
    Method method{&const_method};
    _layout.set(TYPE_SIZE_NAME(VMMethod), uint64_t(sizeof(Method)));
    _layout.set(_method_constmethod_offset, offset(offsetof(Method, const_method)));
    _layout.set(_constmethod_constants_offset, offset(offsetof(ConstMethod, constants)));
    _layout.set(_constmethod_idnum_offset, offset(offsetof(ConstMethod, idnum)));
    _layout.set(_pool_holder_offset, offset(offsetof(Pool, holder)));
    _layout.set(_jmethod_ids_offset, offset(offsetof(Klass, ids)));
    _layout.set(_nmethod_method_offset, offset(offsetof(Blob, method)));
    _layout.set(_nmethod_state_offset, offset(offsetof(Blob, state)));
    _layout.set(_blocks[1].blob.name, static_cast<const char*>("nmethod"));
    _layout.set(_blocks[1].blob.method, static_cast<void*>(&method));
    ProfilerTestAccessor::safeMode() = POP_METHOD;
    auto* nmethod = reinterpret_cast<VMNMethod*>(&_blocks[1].blob);
    ASSERT_TRUE(nmethod->isNMethod());
    ASSERT_TRUE(nmethod->isAlive());
    ASSERT_EQ(ids[1], nmethod->method()->id());

    // The registered-stub case redirects java_ctx into the unregistered compiled blob.
    StackContext java_ctx{};
    java_ctx.pc = _blocks[1].blob.code;
    java_ctx.sp = reinterpret_cast<uintptr_t>(_stack);
    for (bool initial : {false, true}) {
        SCOPED_TRACE(initial);
        bool truncated = initial;
        ASSERT_EQ(1, walk(1, java_ctx, &truncated));
        EXPECT_TRUE(truncated);
        EXPECT_EQ(0, _frames[0].bci);
        EXPECT_EQ(ids[1], _frames[0].method_id);
        EXPECT_EQ(std::vector<int>({1}), asgct_budgets);
        EXPECT_EQ(std::vector<uintptr_t>({reinterpret_cast<uintptr_t>(java_ctx.pc)}), asgct_pcs);
        expectCanary(1);
    }
    ASSERT_EQ(1, walk(1, java_ctx));
    EXPECT_EQ(ids[1], _frames[0].method_id);
    EXPECT_EQ(std::vector<int>({1}), asgct_budgets);
    expectCanary(1);
}

TEST_P(AsgctVtableReceiverTest, NotWalkableJavaAlsoCapturesReceiverBeforeRetry) {
    asgct_initial_error = ticks_not_walkable_Java;
    ASSERT_EQ(3, walk(3));
    EXPECT_EQ(BCI_VTABLE_RECEIVER, _frames[0].bci);
    EXPECT_EQ(reinterpret_cast<jmethodID>(&_symbol), _frames[0].method_id);
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[1].bci);
    EXPECT_STREQ("vtable chunks test", reinterpret_cast<const char*>(_frames[1].method_id));
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[2].method_id);
    EXPECT_EQ(std::vector<int>({3, 1}), asgct_budgets);
    EXPECT_EQ(std::vector<uintptr_t>({leafPC(), retryPC()}), asgct_pcs);
    expectCanary(3);
}

TEST_P(AsgctVtableReceiverTest, ReceiverReadFaultRecoversThroughProductionUcontextWrapper) {
    size_t page_size = static_cast<size_t>(getpagesize());
    auto unmap = [page_size](void* page) { munmap(page, page_size); };
    std::unique_ptr<void, decltype(unmap)> bad_page(
        mmap(nullptr, page_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0), unmap);
    ASSERT_NE(MAP_FAILED, bad_page.get());
    struct sigaction before_segv{}, before_bus{};
    ASSERT_EQ(0, sigaction(SIGSEGV, nullptr, &before_segv));
    ASSERT_EQ(0, sigaction(SIGBUS, nullptr, &before_bus));
    {
        ReceiverReadFaultScope fault_scope;
        prepareWalk();
        setReceiver(reinterpret_cast<uintptr_t>(bad_page.get()));
        bool truncated = false;
        ProfiledThread* thread = ProfiledThread::current();
        ASSERT_FALSE(thread->isProtected());
        sigjmp_buf outer_ctx;
        JmpCtxScope outer_scope(thread);
        outer_scope.install(&outer_ctx);
        StackContext java_ctx{};
        {
            AsyncSampleMutex mutex(thread);
            ASSERT_TRUE(mutex.acquired());
            ASSERT_EQ(0, HotspotSupportTestAccessor::getJavaTraceAsyncWithRecovery(
                &_ctx, _frames, 3, &java_ctx, &truncated));
            EXPECT_TRUE(thread->is_unwinding_Java());
        }
        EXPECT_TRUE(truncated);
        EXPECT_EQ(1, ReceiverReadFaultScope::count());
        EXPECT_EQ(reinterpret_cast<uintptr_t>(bad_page.get()) + sizeof(uintptr_t), ReceiverReadFaultScope::address());
        uintptr_t capture_pc = HotspotSupportTestAccessor::receiverCapturePC();
        EXPECT_GE(ReceiverReadFaultScope::pc(), capture_pc - ReceiverReadFaultScope::RANGE_MARGIN);
        EXPECT_LT(ReceiverReadFaultScope::pc(), capture_pc + ReceiverReadFaultScope::RANGE_MARGIN);
        EXPECT_EQ(std::vector<int>({3}), asgct_budgets);
        EXPECT_EQ(std::vector<uintptr_t>({leafPC()}), asgct_pcs);
        EXPECT_EQ(leafPC(), HotspotStackFrame(&_ctx).pc());
        EXPECT_EQ(reinterpret_cast<uintptr_t>(_stack), HotspotStackFrame(&_ctx).sp());
        EXPECT_EQ(0u, HotspotStackFrame(&_ctx).fp());
        EXPECT_EQ(&outer_ctx, thread->getJmpCtx());
        EXPECT_FALSE(thread->is_unwinding_Java());
        EXPECT_EQ(0, thread->signalDepth());
        expectCanary(0);
        expectCanary(3);
    }
    expectSignalActionRestored(SIGSEGV, before_segv);
    expectSignalActionRestored(SIGBUS, before_bus);
}

TEST_P(AsgctVtableReceiverTest, CapturesReceiverBeforeUnwindingAndReservesRetrySlot) {
    ASSERT_EQ(3, walk(3));
    EXPECT_EQ(BCI_VTABLE_RECEIVER, _frames[0].bci);
    EXPECT_EQ(reinterpret_cast<jmethodID>(&_symbol), _frames[0].method_id);
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[1].bci);
    EXPECT_STREQ("vtable chunks test", reinterpret_cast<const char*>(_frames[1].method_id));
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[2].method_id);
    EXPECT_EQ(std::vector<int>({3, 1}), asgct_budgets);
    EXPECT_EQ(std::vector<uintptr_t>({leafPC(), retryPC()}), asgct_pcs);
    EXPECT_EQ(leafPC(), HotspotStackFrame(&_ctx).pc());
    expectCanary(3);
}

TEST_P(AsgctVtableReceiverTest, DepthBudgetsDoNotWritePastThePrefixOrRetryLimit) {
    for (int budget : {0, 1, 2}) {
        SCOPED_TRACE(budget);
        ASSERT_EQ(budget, walk(budget));
        expectCanary(budget);
        if (budget == 0) {
            EXPECT_TRUE(asgct_budgets.empty());
        } else {
            EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
            EXPECT_STREQ("vtable chunks test", reinterpret_cast<const char*>(_frames[0].method_id));
            EXPECT_EQ(budget == 1 ? std::vector<int>({1}) : std::vector<int>({2, 1}), asgct_budgets);
        }
    }
}

TEST_P(AsgctVtableReceiverTest, CapacityStoppedStubPrefixReportsTruncation) {
    for (int error : {ticks_unknown_Java, ticks_not_walkable_Java}) {
        SCOPED_TRACE(error);
        asgct_initial_error = error;
        for (int safe_mode : {0, static_cast<int>(POP_STUB)}) {
            SCOPED_TRACE(safe_mode);
            ProfilerTestAccessor::safeMode() = safe_mode;
            for (bool initial : {false, true}) {
                SCOPED_TRACE(initial);
                bool truncated = initial;
                ASSERT_EQ(1, walk(1, {}, &truncated));
                EXPECT_TRUE(truncated);
                EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
                EXPECT_STREQ("vtable chunks test", reinterpret_cast<const char*>(_frames[0].method_id));
                EXPECT_EQ(std::vector<int>({1}), asgct_budgets);
                EXPECT_EQ(std::vector<uintptr_t>({leafPC()}), asgct_pcs);
                expectCanary(1);
            }
        }
    }
}

TEST_P(AsgctVtableReceiverTest, SuccessfulRecoveryAndZeroBudgetPreserveTruncation) {
    for (bool initial : {false, true}) {
        SCOPED_TRACE(initial);
        for (int budget : {0, 2, 3}) {
            SCOPED_TRACE(budget);
            bool truncated = initial;
            ASSERT_EQ(budget, walk(budget, {}, &truncated));
            EXPECT_EQ(initial, truncated);
            if (budget == 0) {
                EXPECT_TRUE(asgct_budgets.empty());
            } else {
                EXPECT_EQ(0, _frames[budget - 1].bci);
                EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[budget - 1].method_id);
                EXPECT_EQ(std::vector<int>({budget, 1}), asgct_budgets);
                EXPECT_EQ(std::vector<uintptr_t>({leafPC(), retryPC()}), asgct_pcs);
            }
            expectCanary(budget);
        }
    }
}

TEST_P(AsgctVtableReceiverTest, FailedRetryLeavesRoomForTheErrorFrame) {
    asgct_retry_fails = true;
    ASSERT_EQ(3, walk(3));
    EXPECT_EQ(BCI_VTABLE_RECEIVER, _frames[0].bci);
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[1].bci);
    EXPECT_EQ(BCI_ERROR, _frames[2].bci);
    EXPECT_STREQ("unknown_Java", reinterpret_cast<const char*>(_frames[2].method_id));
    EXPECT_EQ(std::vector<int>({3, 1}), asgct_budgets);
    expectCanary(3);
}

TEST_P(AsgctVtableReceiverTest, RedirectedJavaContextDoesNotReuseInterruptedReceiver) {
    StackContext java_ctx{};
    java_ctx.pc = _blocks[GetParam() ? 1 : 0].blob.code;
    java_ctx.sp = reinterpret_cast<uintptr_t>(_stack);
    ASSERT_EQ(2, walk(3, java_ctx));
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[1].method_id);
    EXPECT_EQ(std::vector<int>({3, 2}), asgct_budgets);
    expectCanary(2);
}

TEST_P(AsgctVtableReceiverTest, NativeStacksDisabledOmitsReceiverAndStub) {
    ProfilerTestAccessor::cstack() = CSTACK_NO;
    ASSERT_EQ(1, walk(3));
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[0].method_id);
    EXPECT_EQ(std::vector<int>({3, 3}), asgct_budgets);
    expectCanary(1);
}

TEST_P(AsgctVtableReceiverTest, CaptureGatesPreserveTheStubAndRetry) {
    ProfilerTestAccessor::features().vtable_target = 0;
    ASSERT_EQ(2, walk(3));
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[1].method_id);
    EXPECT_EQ(std::vector<int>({3, 2}), asgct_budgets);
    expectCanary(2);

    ProfilerTestAccessor::features().vtable_target = 1;
    _layout.disableClassNames();
    ASSERT_EQ(2, walk(3));
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[1].method_id);
    EXPECT_EQ(std::vector<int>({3, 2}), asgct_budgets);
    expectCanary(2);
}

TEST_P(AsgctVtableReceiverTest, NonVtableStubDoesNotReadTheReceiver) {
    _layout.set(_blocks[GetParam() ? 0 : 1].blob.name, static_cast<const char*>("other test stub"));
    setReceiver(1); // Not a readable oop; a non-vtable stub must not inspect it.
    ASSERT_EQ(2, walk(3));
    EXPECT_EQ(BCI_NATIVE_FRAME, _frames[0].bci);
    EXPECT_EQ(reinterpret_cast<jmethodID>(0x1230), _frames[1].method_id);
    EXPECT_EQ(std::vector<int>({3, 2}), asgct_budgets);
    expectCanary(2);
}

TEST_P(AsgctVtableReceiverTest, UnknownJavaSafeModeDoesNotInsertAStubPrefix) {
    ProfilerTestAccessor::safeMode() = UNKNOWN_JAVA;
    ASSERT_EQ(1, walk(3));
    EXPECT_EQ(BCI_ERROR, _frames[0].bci);
    EXPECT_EQ(std::vector<int>({3}), asgct_budgets);
    expectCanary(1);
}

INSTANTIATE_TEST_SUITE_P(RuntimeAndCodeHeapStubs, AsgctVtableReceiverTest,
                        ::testing::Bool(), [](const ::testing::TestParamInfo<bool>& info) {
                            return info.param ? "RegisteredRuntimeStub" : "CodeHeapOnlyStub";
                        });
