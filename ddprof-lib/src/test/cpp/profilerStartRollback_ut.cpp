// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>

#include "engine.h"
#include "flightRecorder.h"
#include "profiler.h"
#include "recordingWriteFailureFixture.h"

// Inert engines let the real rollback run without starting a JVM recording.
// Restore the singleton's slots and registry even when an assertion returns early.
class ProfilerTestAccessor {
    Profiler* _profiler;
    Engine* _cpu;
    Engine* _wall;
    State _state;

public:
    ProfilerTestAccessor(Profiler* profiler, Engine* engine)
        : _profiler(profiler), _cpu(profiler->_cpu_engine), _wall(profiler->_wall_engine),
          _state(profiler->state()) {
        _profiler->_cpu_engine = engine;
        _profiler->_wall_engine = engine;
    }

    ~ProfilerTestAccessor() {
        _profiler->_thread_filter.deactivateRecording();
        _profiler->_cpu_engine = _cpu;
        _profiler->_wall_engine = _wall;
        _profiler->_state.store(_state, std::memory_order_release);
        _profiler->_intern_open.store(false, std::memory_order_release);
        delete takeRecording();
    }

    ProfilerTestAccessor(const ProfilerTestAccessor&) = delete;
    ProfilerTestAccessor& operator=(const ProfilerTestAccessor&) = delete;

    Error rollBackStart() { return _profiler->rollBackStart(); }
    // Models the state start() leaves before it fails: an active recording and an open gate.
    void beginRecording(Recording* recording) {
        _profiler->_jfr._rec = recording;
        _profiler->_intern_open.store(true, std::memory_order_release);
    }
    State state() const { return _profiler->state(); }
    Recording* recording() const { return _profiler->_jfr._rec; }
    Recording* takeRecording() {
        Recording* recording = _profiler->_jfr._rec;
        _profiler->_jfr._rec = nullptr;
        return recording;
    }
    void failStart() { Profiler::RecordingMemoryScope scope(_profiler); }
};

class RecordingTestAccessor {
public:
    // Match post-start hot writes: real flush failures retain bytes instead of throwing.
    static void activateHotWrites(Recording* recording) { recording->_cold_io = false; }
    // A failed append quarantines the output, as a failed write during start() would.
    static void failAppend(Recording* recording) {
        RecordingBuffer* buffer = recording->buffer(0);
        buffer->put8(0);
        recording->flush(buffer);
    }
};

class VMTestAccessor {
    jvmtiInterface_1_ _functions{};
    _jvmtiEnv _environment{};
    JNIInvokeInterface_ _vm_functions{};
    JavaVM_ _vm{&_vm_functions};
    jvmtiEnv* _previous;
    JavaVM* _previous_vm;

public:
    VMTestAccessor() : _previous(VM::_jvmti), _previous_vm(VM::_vm) {
        // There is no JVM in this binary: no Java threads, and no JNIEnv for this thread.
        _functions.GetAllThreads = +[](jvmtiEnv*, jint*, jthread**) {
            return JVMTI_ERROR_WRONG_PHASE;
        };
        _vm_functions.GetEnv = +[](JavaVM*, void** env, jint) {
            *env = nullptr;
            return JNI_EDETACHED;
        };
        _environment.functions = &_functions;
        VM::_jvmti = &_environment;
        VM::_vm = &_vm;
    }
    ~VMTestAccessor() {
        VM::_jvmti = _previous;
        VM::_vm = _previous_vm;
    }
    VMTestAccessor(const VMTestAccessor&) = delete;
    VMTestAccessor& operator=(const VMTestAccessor&) = delete;
};

namespace {
constexpr char kRetainedKey[] = "RollbackRetainedKey";

u32 internRetainedKey(Profiler* profiler) {
    return profiler->classMap()->lookup(kRetainedKey, sizeof(kRetainedKey) - 1);
}
} // namespace

// Failed output keeps the recording, so the failed start must leave a terminal state
// that keeps the memory it references and admits no more interning.
TEST(ProfilerStartRollbackOutputTest, RetainedRecordingMakesFailedStartTerminal) {
    Profiler* profiler = Profiler::instance();
    Engine engine;
    VMTestAccessor vm;
    // Outlives restore, which deletes a retained recording that writes to it.
    RecordingWriteFailureFixture output;
    ProfilerTestAccessor restore(profiler, &engine);
    ASSERT_TRUE(output.valid());
    Recording* recording = new Recording(output.fd());
    RecordingTestAccessor::activateHotWrites(recording);
    restore.beginRecording(recording);
    const u32 id = internRetainedKey(profiler);
    ASSERT_NE(0U, id);
    const u64 generation = profiler->classMap()->generation();
    ASSERT_TRUE(output.failWrites());
    RecordingTestAccessor::failAppend(recording);
    ASSERT_FALSE(recording->outputGood());

    Error error = restore.rollBackStart();
    ASSERT_TRUE(error);
    EXPECT_STREQ("Incomplete recording output retained; restart refused", error.message());
    EXPECT_EQ(recording, restore.recording());
    EXPECT_EQ(ERROR, restore.state());

    restore.failStart();
    EXPECT_FALSE(profiler->internOpen());
    EXPECT_EQ(generation, profiler->classMap()->generation());
    EXPECT_EQ(id, internRetainedKey(profiler));
}

// Without a retained recording nothing references the memory, so the failed start frees it.
TEST(ProfilerStartRollbackOutputTest, UnretainedFailedStartReleasesMemoryAndStaysRestartable) {
    Profiler* profiler = Profiler::instance();
    Engine engine;
    VMTestAccessor vm;
    ProfilerTestAccessor restore(profiler, &engine);
    const State before = restore.state();
    restore.beginRecording(nullptr);
    ASSERT_NE(0U, internRetainedKey(profiler));
    const u64 generation = profiler->classMap()->generation();

    EXPECT_FALSE(restore.rollBackStart());
    EXPECT_EQ(before, restore.state());

    restore.failStart();
    EXPECT_FALSE(profiler->internOpen());
    EXPECT_NE(generation, profiler->classMap()->generation());
}

class ProfilerStartRollbackTest : public ::testing::TestWithParam<bool> {};

// Shared rollback closes the registry on every post-JFR start failure path.
TEST_P(ProfilerStartRollbackTest, DeactivatesRecordingRegistry) {
    Profiler* profiler = Profiler::instance();
    Engine engine;
    ProfilerTestAccessor restore(profiler, &engine);
    ThreadFilter* filter = profiler->threadFilter();
    const bool unfiltered = GetParam();
    filter->init(unfiltered ? "" : "0", unfiltered);
    ASSERT_TRUE(filter->registryActive());
    ASSERT_EQ(!unfiltered, filter->enabled());
    ASSERT_EQ(unfiltered, filter->unfilteredWallTrackingActive());
    if (unfiltered) {
        ASSERT_NE(0, filter->recordingEpoch());
    }

    restore.rollBackStart();

    EXPECT_FALSE(filter->registryActive());
    EXPECT_FALSE(filter->enabled());
    EXPECT_FALSE(filter->unfilteredWallTrackingActive());
    EXPECT_EQ(0, filter->recordingEpoch());
}

INSTANTIATE_TEST_SUITE_P(
    RecordingModes, ProfilerStartRollbackTest, ::testing::Bool(),
    [](const ::testing::TestParamInfo<bool>& info) {
        return info.param ? "Unfiltered" : "Filtered";
    });
