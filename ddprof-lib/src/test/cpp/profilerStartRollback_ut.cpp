// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>

#include "engine.h"
#include "profiler.h"

// Inert engines let the real rollback run without starting a JVM recording.
// Restore the singleton's slots and registry even when an assertion returns early.
class ProfilerTestAccessor {
    Profiler* _profiler;
    Engine* _cpu;
    Engine* _wall;

public:
    ProfilerTestAccessor(Profiler* profiler, Engine* engine)
        : _profiler(profiler), _cpu(profiler->_cpu_engine), _wall(profiler->_wall_engine) {
        _profiler->_cpu_engine = engine;
        _profiler->_wall_engine = engine;
    }

    ~ProfilerTestAccessor() {
        _profiler->_thread_filter.deactivateRecording();
        _profiler->_cpu_engine = _cpu;
        _profiler->_wall_engine = _wall;
    }

    ProfilerTestAccessor(const ProfilerTestAccessor&) = delete;
    ProfilerTestAccessor& operator=(const ProfilerTestAccessor&) = delete;

    void rollBackStart() { _profiler->rollBackStart(); }
};

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
