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
        // fromOop reads the header and probes the decoded Klass, as walkVM does under crash protection.
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

// Decoded Klass addresses must be readable, so the nonzero-base cases aim at real storage.
alignas(16) uintptr_t klass_storage[2];
const uintptr_t KLASS = reinterpret_cast<uintptr_t>(klass_storage);

TEST_F(VMKlassFromOopTest, ZeroBaseRejectsUnmappedDecodedKlass) {
    header.klass = 0x12340;
    EXPECT_EQ(0u, decode(0, 0));
    EXPECT_EQ(0u, decode(0, 3));
}

TEST_F(VMKlassFromOopTest, NonzeroBaseWithNonzeroEncodedKlass) {
    header.klass = 0x12340;
    EXPECT_EQ(KLASS, decode(KLASS - 0x12340, 0));
    EXPECT_EQ(KLASS, decode(KLASS - (uintptr_t(0x12340) << 3), 3));
}

TEST_F(VMKlassFromOopTest, ZeroEncodedKlassIsNull) {
    header.klass = 0;
    EXPECT_EQ(0u, decode(0, 0));
    EXPECT_EQ(0u, decode(KLASS, 0));
    EXPECT_EQ(0u, decode(KLASS, 3));
}

TEST_F(VMKlassFromOopTest, UncompressedKlassUsesFullPointer) {
    header.klass = reinterpret_cast<uintptr_t>(&header);
    EXPECT_EQ(header.klass, decode(0x100000, -1));
}

TEST_F(VMKlassFromOopTest, OrdinaryCompactHeaderUsesSameAddressReconstruction) {
    VMStructsTestAccessor::compact() = true;
    header.mark = (uintptr_t(0x12340) << 32) | 1;
    header.klass = 0xbad;
    EXPECT_EQ(KLASS, decode(KLASS - 0x12340, 0));
    EXPECT_EQ(KLASS, decode(KLASS - (uintptr_t(0x12340) << 3), 3));
    EXPECT_EQ(0u, decode(0, 3));
}

} // namespace
