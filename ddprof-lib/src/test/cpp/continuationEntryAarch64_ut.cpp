/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include "hotspot/hotspotStackFrame.h"
#include "hotspot/vmStructs.inline.h"

#ifdef __aarch64__
namespace {

class ScopedOffset {
    int& _slot;
    int _saved;
public:
    ScopedOffset(int& slot, int value) : _slot(slot), _saved(slot) { slot = value; }
    ~ScopedOffset() { _slot = _saved; }
    ScopedOffset(const ScopedOffset&) = delete;
    ScopedOffset& operator=(const ScopedOffset&) = delete;
};

class ContinuationEntryAarch64Test : public ::testing::Test, protected VMStructs {
protected:
    struct Method {
        int words = 10;
        int size = sizeof(Method);
        short complete = 64;
        const void* code_begin = code;
        const void* entry = code;
        instruction_t code[64];
    } method;
    ScopedOffset frame_size{_frame_size_offset, offsetof(Method, words)};
    ScopedOffset blob_size{_blob_size_offset, offsetof(Method, size)};
    ScopedOffset complete{_frame_complete_offset, offsetof(Method, complete)};
    ScopedOffset code_offset{_code_offset, -1};
    ScopedOffset code_address{_code_address, offsetof(Method, code_begin)};
    ScopedOffset entry_offset{_nmethod_entry_offset, -1};
    ScopedOffset entry_address{_nmethod_entry_address, offsetof(Method, entry)};

    void SetUp() override {
        for (auto& instruction : method.code) instruction = 0xd503201f; // nop
        setup(0);
    }

    // MacroAssembler::enter, then continuation_enter_setup's sub sp, sp, #(words - 2) * 8.
    void setup(int at) {
        method.code[at] = 0xa9bf7bfd;     // stp x29, x30, [sp, #-16]!
        method.code[at + 1] = 0x910003fd; // mov x29, sp
        method.code[at + 2] = 0xd10003ffU | ((method.words - 2) * sizeof(uintptr_t) << 10);
    }

    void cutAfter(int bytes) { method.size = offsetof(Method, code) + bytes; }

    int wordsAt(int index) {
        HotspotStackFrame frame(nullptr);
        return frame.continuationEntryFrameWords(reinterpret_cast<VMNMethod*>(&method), method.code + index);
    }
};

TEST_F(ContinuationEntryAarch64Test, DecodesProloguePhases) {
    EXPECT_EQ(0, wordsAt(0));  // before stp: FP and LR are still in registers
    EXPECT_EQ(2, wordsAt(1));
    EXPECT_EQ(2, wordsAt(2));
    EXPECT_EQ(10, wordsAt(3)); // storage allocated
}

TEST_F(ContinuationEntryAarch64Test, RejectsAPrologueWindowCutOffByTheBlobEnd) {
    cutAfter(27); // four padding words plus stp/mov/sub need 28 bytes from the entry
    EXPECT_EQ(-1, wordsAt(0));
    cutAfter(28);
    EXPECT_EQ(0, wordsAt(0));
}

TEST_F(ContinuationEntryAarch64Test, RejectsPcsOutsideTheBlob) {
    method.complete = 8; // a frame-complete PC skips the prologue window
    cutAfter(8);
    EXPECT_EQ(-1, wordsAt(3));
    cutAfter(16);
    EXPECT_EQ(10, wordsAt(3));
}

TEST_F(ContinuationEntryAarch64Test, RejectsAnEntryOutsideTheBlob) {
    method.entry = method.code + 8;
    cutAfter(28); // the prologue window fits, but the verified entry lies outside
    EXPECT_EQ(-1, wordsAt(0));
}

} // namespace
#else
TEST(ContinuationEntryAarch64Test, RequiresAarch64) {
    GTEST_SKIP() << "aarch64 continuation entry decoding";
}
#endif
