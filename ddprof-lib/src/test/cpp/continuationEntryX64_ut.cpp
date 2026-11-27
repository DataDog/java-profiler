/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include "hotspot/hotspotStackFrame.h"
#include "hotspot/vmStructs.inline.h"

#ifdef __x86_64__
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

class ContinuationEntryX64Test : public ::testing::Test, protected VMStructs {
protected:
    struct Method {
        int words = 10;
        int size = sizeof(Method);
        short complete = 8;
        const void* code_begin = code;
        const void* entry = code;
        unsigned char code[1200];
    } method;
    ScopedOffset frame_size{_frame_size_offset, offsetof(Method, words)};
    ScopedOffset blob_size{_blob_size_offset, offsetof(Method, size)};
    ScopedOffset complete{_frame_complete_offset, offsetof(Method, complete)};
    ScopedOffset code_offset{_code_offset, -1};
    ScopedOffset code_address{_code_address, offsetof(Method, code_begin)};
    ScopedOffset entry_offset{_nmethod_entry_offset, -1};
    ScopedOffset entry_address{_nmethod_entry_address, offsetof(Method, entry)};

    void SetUp() override {
        memset(method.code, 0x90, sizeof(method.code));
        const unsigned char setup[] = {0x55, 0x48, 0x8b, 0xec, 0x48, 0x83, 0xec, 0x40};
        memcpy(method.code, setup, sizeof(setup));
    }

    int wordsAt(int offset) {
        HotspotStackFrame frame(nullptr);
        return frame.continuationEntryFrameWords(reinterpret_cast<VMNMethod*>(&method), method.code + offset);
    }

    void exitSequence(bool large = false) {
        // gen_continuation_enter (OpenJDK 21u, 25u and main): the normal
        // add rsp; pop rbp; ret precedes the separate exception exit.
        const unsigned char normal[] = {0x48, 0x83, 0xc4, 0x40, 0x5d, 0xc3};
        const unsigned char normal_large[] = {0x48, 0x81, 0xc4, 0x80, 0, 0, 0, 0x5d, 0xc3};
        const unsigned char restore_parent[] = {0x49, 0x89, 0x9f, 0x38, 0x05, 0, 0};
        memcpy(method.code + 25, restore_parent, sizeof(restore_parent));
        memcpy(method.code + 32, large ? normal_large : normal, large ? sizeof(normal_large) : sizeof(normal));
        // The resolver's address setup/alignment is omitted. The exception
        // stack phases, including the final return PC in RDX, are retained.
        const unsigned char exception[] = {
            0x48, 0x83, 0xc4, 0x40, // cleanup: add rsp, 64
            0x5d,                   // pop rbp
            0x49, 0x8b, 0xff,       // mov rdi, r15
            0x48, 0x8b, 0x34, 0x24, // mov rsi, [rsp]
            0x50,                   // push rax (exception oop)
            0xe8, 0, 0, 0, 0,      // call resolver
            0x48, 0x8b, 0xd8,       // mov rbx, rax (handler)
            0x58,                   // pop rax
            0x5a,                   // pop rdx (return PC)
            0xff, 0xe3,             // jmp rbx
        };
        memcpy(method.code + 64, exception, sizeof(exception));
    }
};

TEST_F(ContinuationEntryX64Test, RejectsExceptionSectionBeforeAndAfterRestoringRegisters) {
    exitSequence();
    for (int phase : {0, 4, 5, 8, 12, 13, 18, 21, 22, 23}) {
        EXPECT_EQ(-1, wordsAt(64 + phase)) << "exception byte offset=" << phase;
    }
}

TEST_F(ContinuationEntryX64Test, PreservesNormalEntryBodyAndExitPhases) {
    exitSequence();
    EXPECT_EQ(1, wordsAt(0));
    EXPECT_EQ(2, wordsAt(1));
    EXPECT_EQ(2, wordsAt(4));
    EXPECT_EQ(10, wordsAt(8));
    EXPECT_EQ(10, wordsAt(32));
    EXPECT_EQ(2, wordsAt(36));
    EXPECT_EQ(1, wordsAt(37));
}

TEST_F(ContinuationEntryX64Test, HandlesLargeImmediateSetupAndCleanup) {
    method.words = 18;
    method.complete = 11;
    const unsigned char setup[] = {0x55, 0x48, 0x8b, 0xec, 0x48, 0x81, 0xec, 0x80, 0, 0, 0};
    memcpy(method.code, setup, sizeof(setup));
    exitSequence(true);
    EXPECT_EQ(2, wordsAt(4));
    EXPECT_EQ(18, wordsAt(11));
    EXPECT_EQ(2, wordsAt(39));
    EXPECT_EQ(1, wordsAt(40));
    EXPECT_EQ(-1, wordsAt(64));
}

TEST_F(ContinuationEntryX64Test, RequiresMatchingStoragePopAndReturn) {
    // Without a recognized normal exit, no PC may use the complete frame size.
    exitSequence();
    method.code[35] = 0x30; // wrong storage size
    EXPECT_EQ(-1, wordsAt(8));
    EXPECT_EQ(-1, wordsAt(48));
    method.code[35] = 0x40;
    method.code[36] = 0x58; // pop rax instead of rbp
    EXPECT_EQ(-1, wordsAt(48));
    method.code[36] = 0x5d;
    method.code[37] = 0x90; // no ret
    EXPECT_EQ(-1, wordsAt(48));
}

TEST_F(ContinuationEntryX64Test, UnrecognizedExitRejectsExceptionJump) {
    exitSequence();
    method.code[27] = 0x90; // the cleanup store no longer precedes add rsp
    EXPECT_EQ(-1, wordsAt(64 + 23)) << "final jmp rbx after pop rdx";
    EXPECT_EQ(-1, wordsAt(64 + 4)) << "exception pop rbp";
}

TEST_F(ContinuationEntryX64Test, DoesNotScanBeforeTheVerifiedEntry) {
    exitSequence();
    // A second exit after the verified entry: a scan from code would instead see the one at 32.
    const unsigned char restore_parent[] = {0x49, 0x89, 0x9f, 0x38, 0x05, 0, 0};
    const unsigned char normal[] = {0x48, 0x83, 0xc4, 0x40, 0x5d, 0xc3};
    memcpy(method.code + 100, restore_parent, sizeof(restore_parent));
    memcpy(method.code + 107, normal, sizeof(normal));
    method.entry = method.code + 48;
    method.complete = 48;
    EXPECT_EQ(10, wordsAt(64));
}

TEST_F(ContinuationEntryX64Test, IgnoresEpilogueBytesInsideAnImmediate) {
    const unsigned char literal[] = {0x48, 0xb8, 0x48, 0x83, 0xc4, 0x40, 0x5d, 0xc3, 0, 0};
    memcpy(method.code + 16, literal, sizeof(literal));
    exitSequence();
    EXPECT_EQ(10, wordsAt(30));
}

TEST_F(ContinuationEntryX64Test, RejectsOutOfBlobAndUnboundedCodePositions) {
    EXPECT_EQ(-1, wordsAt(1100));
    method.size = offsetof(Method, code) + 16;
    EXPECT_EQ(-1, wordsAt(32));
}

TEST_F(ContinuationEntryX64Test, IgnoresAnExitThatStraddlesTheBlobEnd) {
    exitSequence();
    method.size = offsetof(Method, code) + 37; // the exit's ret lies outside the nmethod
    EXPECT_EQ(-1, wordsAt(8));
}

TEST_F(ContinuationEntryX64Test, RejectsInvalidFrameSizes) {
    for (int words : {0, 2, 9, 258}) {
        method.words = words;
        EXPECT_EQ(-1, wordsAt(8));
    }
}

TEST_F(ContinuationEntryX64Test, AcceptsTheLargestFrameSize) {
    method.words = 256;
    method.complete = 64;
    const unsigned char setup[] = {0x55, 0x48, 0x8b, 0xec, 0x48, 0x81, 0xec, 0xf0, 0x07, 0, 0};
    memcpy(method.code, setup, sizeof(setup));
    EXPECT_EQ(256, wordsAt(11));
    method.words = 258;
    method.code[7] = 0x00; // storage (258 - 2) * 8 = 0x800: only the size bound rejects it
    method.code[8] = 0x08;
    EXPECT_EQ(-1, wordsAt(11));
}

TEST_F(ContinuationEntryX64Test, RejectsAPrologueCutOffByTheBlobEnd) {
    method.complete = 64;
    method.size = offsetof(Method, code) + 7; // sub rsp's imm8 lies outside the nmethod
    EXPECT_EQ(-1, wordsAt(0));
    method.size = offsetof(Method, code) + 8;
    EXPECT_EQ(1, wordsAt(0));

    const unsigned char setup[] = {0x55, 0x48, 0x8b, 0xec, 0x48, 0x81, 0xec, 0x40, 0, 0, 0};
    memcpy(method.code, setup, sizeof(setup));
    method.size = offsetof(Method, code) + 10; // the imm32's last byte lies outside
    EXPECT_EQ(-1, wordsAt(0));
    method.size = offsetof(Method, code) + 11;
    EXPECT_EQ(1, wordsAt(0));
}

} // namespace
#else
TEST(ContinuationEntryX64Test, RequiresX64) {
    GTEST_SKIP() << "x64 continuation entry decoding";
}
#endif
