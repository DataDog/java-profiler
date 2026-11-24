// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>
#include "hotspot/vmStructs.h"
#include "profiler.h"
#include "trap.h"
#include "vmEntry.h"

class VMTestAccessor {
public:
    static void setHotspot(bool v) { VM::_hotspot = v; }
};

class VMStructsTestAccessor {
public:
    static void setInterpretedFrameValid(const void* start, const void* end) {
        VMStructs::_interpreted_frame_valid_start = start;
        VMStructs::_interpreted_frame_valid_end = end;
    }
};

class ProfilerTestAccessor {
public:
    static void setNeed8313796(bool v) { Profiler::_need_JDK_8313796_workaround = v; }
};

namespace {
constexpr uintptr_t kRangeMin = 0x10000;
constexpr uintptr_t kRangeMax = 0x20000;
// Far from the range above and from any page the trap test assigns.
constexpr uintptr_t kInterpreterPc = 0x7000;

NOINLINE void trapTarget() {
    asm volatile("");
}

class CrashFaultPrefilterTest : public ::testing::Test {
protected:
    void SetUp() override { Profiler::setAddressRangeForTest(kRangeMin, kRangeMax); }
    void TearDown() override {
        Profiler::resetAddressRangeForTest();
        VMTestAccessor::setHotspot(false);
        VMStructsTestAccessor::setInterpretedFrameValid(nullptr, nullptr);
        ProfilerTestAccessor::setNeed8313796(true);
    }
};
}

TEST_F(CrashFaultPrefilterTest, RangeBoundsAreHalfOpen) {
    EXPECT_TRUE(Profiler::isProfilerOwnedFault(kRangeMin));
    EXPECT_TRUE(Profiler::isProfilerOwnedFault(kRangeMax - 1));
    EXPECT_FALSE(Profiler::isProfilerOwnedFault(kRangeMin - 1));
    EXPECT_FALSE(Profiler::isProfilerOwnedFault(kRangeMax));
}

TEST_F(CrashFaultPrefilterTest, UnknownRangeIsConservative) {
    Profiler::resetAddressRangeForTest();
    EXPECT_TRUE(Profiler::isProfilerOwnedFault(kRangeMax + 1));
}

TEST_F(CrashFaultPrefilterTest, InterpretedFrameValidRequiresHotspotAndWorkaround) {
    const void* start = reinterpret_cast<const void*>(kInterpreterPc);
    const void* end = reinterpret_cast<const void*>(kInterpreterPc + 0x100);
    VMStructsTestAccessor::setInterpretedFrameValid(start, end);
    EXPECT_FALSE(Profiler::isProfilerOwnedFault(kInterpreterPc)) << "not HotSpot";
    VMTestAccessor::setHotspot(true);
    EXPECT_TRUE(Profiler::isProfilerOwnedFault(kInterpreterPc));
    EXPECT_FALSE(Profiler::isProfilerOwnedFault(kInterpreterPc + 0x100));
    ProfilerTestAccessor::setNeed8313796(false);
    EXPECT_FALSE(Profiler::isProfilerOwnedFault(kInterpreterPc)) << "JDK fixed";
}

// Trap::assign() records the trap page process-wide; this binary installs no
// other trap, so the page stays owned only by this test.
TEST_F(CrashFaultPrefilterTest, WxTrapPageIsOwnedOnlyWithWxMemory) {
    Trap trap(0);
    trap.assign(reinterpret_cast<const void*>(&trapTarget), 0);
    EXPECT_EQ(WX_MEMORY, Profiler::isProfilerOwnedFault(trap.entry()));
}
