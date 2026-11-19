/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <array>
#include <cstddef>
#include "hotspot/vmStructs.h"

class VMStructsTestAccessor {
public:
    static std::array<offset*, 9> deoptimizationOffsets() {
        return {{&VMStructs::_nmethod_orig_pc_offset,
                 &VMStructs::_nmethod_deopt_handler_address,
                 &VMStructs::_nmethod_deopt_mh_handler_address,
                 &VMStructs::_nmethod_deopt_handler_offset,
                 &VMStructs::_nmethod_deopt_mh_handler_offset,
                 &VMStructs::_code_address, &VMStructs::_code_offset,
                 &VMStructs::_blob_size_offset, &VMStructs::_nmethod_deopt_handler_entry_offset}};
    }
};

namespace {

// The same recovery code must handle absolute handler addresses on JDK 21/22
// and relative offsets on JDK 23+, with a single handler entry on JDK 26+.
class FrozenDeoptimizationTest : public ::testing::TestWithParam<int> {
protected:
    struct Metadata {
        int size;
        int original_slot;
        const void* code;
        const void* handler;
        const void* mh_handler;
        int handler_offset;
        int mh_handler_offset;
        int code_offset;
    };

    alignas(16) char blob[512] = {};
    uintptr_t stack[16] = {};
    std::array<offset*, 9> fields = VMStructsTestAccessor::deoptimizationOffsets();
    std::array<offset, 9> saved;

    void SetUp() override {
        for (size_t i = 0; i < fields.size(); i++) saved[i] = *fields[i];
        *fields[0] = offsetof(Metadata, original_slot);
        *fields[1] = GetParam() ? -1 : offsetof(Metadata, handler);
        *fields[2] = GetParam() ? -1 : offsetof(Metadata, mh_handler);
        *fields[3] = GetParam() == 1 ? offsetof(Metadata, handler_offset) : -1;
        *fields[4] = GetParam() == 1 ? offsetof(Metadata, mh_handler_offset) : -1;
        *fields[5] = GetParam() ? -1 : offsetof(Metadata, code);
        *fields[6] = GetParam() ? offsetof(Metadata, code_offset) : -1;
        *fields[7] = offsetof(Metadata, size);
        *fields[8] = GetParam() == 2 ? offsetof(Metadata, handler_offset) : -1;
        metadata().size = sizeof(blob);
        metadata().original_slot = 0;
        metadata().code = blob + 128;
        metadata().handler = blob + 256;
        metadata().mh_handler = blob + 288;
        metadata().handler_offset = 256;
        metadata().mh_handler_offset = 288;
        metadata().code_offset = 128;
        stack[4] = (uintptr_t)(blob + 160);
    }

    void TearDown() override {
        for (size_t i = 0; i < fields.size(); i++) *fields[i] = saved[i];
    }

    Metadata& metadata() { return *(Metadata*)blob; }

    const void* resolve(const void* pc) {
        return ((VMNMethod*)blob)->originalPC(pc, (uintptr_t)&stack[4],
                                            (uintptr_t)&stack[0], (uintptr_t)&stack[12]);
    }
};

TEST_P(FrozenDeoptimizationTest, LeavesOrdinaryReturnPcUnchanged) {
    EXPECT_EQ(blob + 176, resolve(blob + 176));
}

TEST_P(FrozenDeoptimizationTest, RestoresNormalAndMethodHandleHandlersAtSlotZero) {
    EXPECT_EQ(blob + 160, resolve(blob + 256));
    if (GetParam() != 2) EXPECT_EQ(blob + 160, resolve(blob + 288));
}

TEST_P(FrozenDeoptimizationTest, UsesByteOffsetFromUnextendedSp) {
    metadata().original_slot = 2 * sizeof(uintptr_t);
    stack[4] = 0;
    stack[6] = (uintptr_t)(blob + 176);
    EXPECT_EQ(blob + 176, resolve(blob + 256));
}

TEST_P(FrozenDeoptimizationTest, AcceptsLastSlotButRejectsReadAcrossFrameEnd) {
    metadata().original_slot = 7 * sizeof(uintptr_t);
    stack[11] = (uintptr_t)(blob + 176);
    EXPECT_EQ(blob + 176, resolve(blob + 256));
    metadata().original_slot++;
    EXPECT_EQ(nullptr, resolve(blob + 256));
    metadata().original_slot = 8 * sizeof(uintptr_t);
    EXPECT_EQ(nullptr, resolve(blob + 256));
}

TEST_P(FrozenDeoptimizationTest, RejectsNegativeAndUnalignedOffsets) {
    metadata().original_slot = -1;
    EXPECT_EQ(nullptr, resolve(blob + 256));
    metadata().original_slot = 1;
    EXPECT_EQ(nullptr, resolve(blob + 256));
}

TEST_P(FrozenDeoptimizationTest, RejectsInvalidFrameBounds) {
    auto* nm = (VMNMethod*)blob;
    uintptr_t low = (uintptr_t)&stack[0];
    uintptr_t sp = (uintptr_t)&stack[4];
    EXPECT_EQ(nullptr, nm->originalPC(blob + 256, sp, sp + 8, sp + 64));
    EXPECT_EQ(nullptr, nm->originalPC(blob + 256, sp, low, sp - 8));
    EXPECT_EQ(nullptr, nm->originalPC(blob + 256, sp, low, sp));
}

TEST_P(FrozenDeoptimizationTest, RejectsHandlerNullMetadataAndForeignSavedPcs) {
    for (const void* pc : std::array<const void*, 5>{{nullptr, blob + 256, GetParam() == 2 ? blob + 256 : blob + 288,
                                                   blob + 16, blob + sizeof(blob)}}) {
        stack[4] = (uintptr_t)pc;
        EXPECT_EQ(nullptr, resolve(blob + 256));
    }
}

TEST_P(FrozenDeoptimizationTest, MissingMetadataDeclinesRecovery) {
    *fields[0] = -1;
    EXPECT_EQ(nullptr, resolve(blob + 256));
    *fields[0] = offsetof(Metadata, original_slot);
    *fields[2] = *fields[4] = -1;
    *fields[8] = -1;
    EXPECT_EQ(nullptr, resolve(blob + 256));
}

INSTANTIATE_TEST_SUITE_P(HandlerLayouts, FrozenDeoptimizationTest, ::testing::Values(0, 1, 2));

} // namespace
