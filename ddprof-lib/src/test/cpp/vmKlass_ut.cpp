// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>
#include <cstddef>
#include "guards.h"
#include "hotspot/vmStructs.inline.h"

class VMStructsTestAccessor {
public:
    static int& shift() { return VMStructs::_narrow_klass_shift; }
    static char*& base() { return VMStructs::_narrow_klass_base; }
    static bool& compact() { return VMStructs::_compact_object_headers; }
    static offset& klassOffset() { return VMStructs::_oop_klass_offset; }
    static long& markShift() { return VMStructs::_markWord_klass_shift; }
    static uint64_t& klassSize() { return VMStructs::TYPE_SIZE_NAME(VMKlass); }
};

class VMTestAccessor {
public:
    static bool& hotspot() { return VM::_hotspot; }
};

namespace {

class VMKlassFromOopTest : public ::testing::Test {
protected:
    int saved_shift = VMStructsTestAccessor::shift();
    char* saved_base = VMStructsTestAccessor::base();
    bool saved_compact = VMStructsTestAccessor::compact();
    offset saved_offset = VMStructsTestAccessor::klassOffset();
    long saved_mark_shift = VMStructsTestAccessor::markShift();
    uint64_t saved_size = VMStructsTestAccessor::klassSize();
    bool saved_hotspot = VMTestAccessor::hotspot();
    bool owns_thread = false;
    struct Header {
        uintptr_t mark;
        uintptr_t klass;
    } header{};

    void SetUp() override {
        owns_thread = ProfiledThread::current() == nullptr;
        if (owns_thread) ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        VMTestAccessor::hotspot() = true;
        VMStructsTestAccessor::klassSize() = sizeof(uintptr_t);
        VMStructsTestAccessor::klassOffset() = offsetof(Header, klass);
        VMStructsTestAccessor::markShift() = 32;
        VMStructsTestAccessor::compact() = false;
    }

    void TearDown() override {
        VMStructsTestAccessor::shift() = saved_shift;
        VMStructsTestAccessor::base() = saved_base;
        VMStructsTestAccessor::compact() = saved_compact;
        VMStructsTestAccessor::klassOffset() = saved_offset;
        VMStructsTestAccessor::markShift() = saved_mark_shift;
        VMStructsTestAccessor::klassSize() = saved_size;
        VMTestAccessor::hotspot() = saved_hotspot;
        if (owns_thread) ProfiledThread::release();
    }

    uintptr_t decode(uintptr_t base, int shift) {
        VMStructsTestAccessor::base() = reinterpret_cast<char*>(base);
        VMStructsTestAccessor::shift() = shift;
        // Decoded addresses are opaque: protected casts must not probe synthetic Klass memory.
        sigjmp_buf ctx;
        JmpCtxScope scope(ProfiledThread::current());
        if (sigsetjmp(ctx, 1) != 0) {
            SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
            scope.restore();
            ADD_FAILURE() << "Unexpected header access fault";
            return 0;
        }
        scope.install(&ctx);
        return reinterpret_cast<uintptr_t>(VMKlass::fromOop(reinterpret_cast<uintptr_t>(&header)));
    }
};

TEST_F(VMKlassFromOopTest, ZeroBaseWithNonzeroEncodedKlass) {
    header.klass = 0x12340;
    EXPECT_EQ(0x12340u, decode(0, 0));
    EXPECT_EQ(0x91a00u, decode(0, 3));
}

TEST_F(VMKlassFromOopTest, NonzeroBaseWithNonzeroEncodedKlass) {
    header.klass = 0x12340;
    EXPECT_EQ(0x112340u, decode(0x100000, 0));
    EXPECT_EQ(0x191a00u, decode(0x100000, 3));
}

TEST_F(VMKlassFromOopTest, ZeroEncodedKlassPreservesAddressAlgebra) {
    header.klass = 0;
    EXPECT_EQ(0u, decode(0, 0));
    EXPECT_EQ(0u, decode(0, 3));
    EXPECT_EQ(0x100000u, decode(0x100000, 0));
    EXPECT_EQ(0x100000u, decode(0x100000, 3));
}

TEST_F(VMKlassFromOopTest, UncompressedKlassUsesFullPointer) {
    header.klass = reinterpret_cast<uintptr_t>(&header);
    EXPECT_EQ(header.klass, decode(0x100000, -1));
}

TEST_F(VMKlassFromOopTest, OrdinaryCompactHeaderUsesSameAddressReconstruction) {
    VMStructsTestAccessor::compact() = true;
    header.mark = (uintptr_t(0x12340) << 32) | 1;
    header.klass = 0xbad;
    EXPECT_EQ(0x12340u, decode(0, 0));
    EXPECT_EQ(0x91a00u, decode(0, 3));
    EXPECT_EQ(0x191a00u, decode(0x100000, 3));
}

} // namespace
