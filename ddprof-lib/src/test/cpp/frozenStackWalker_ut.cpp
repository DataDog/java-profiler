/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <unistd.h>
#include "hotspot/frozenStackWalker.h"
#include "vmEntry.h"

class VMTestAccessor {
public:
    static void configureFrozenWalker() {
        VM::_java_version = 21;
        VM::_hotspot_version = 21;
        VM::_hotspot = true;
    }
};

namespace {

// Every test initializes the production singleton in a child. The parent never
// publishes a layout, so independent tests need no production reset entry point.
class FrozenStackWalkerInitializationTest : public ::testing::Test, protected VMStructs {
protected:
    struct Flag {
        const char* name;
        void* value;
        int type;
    };

    CodeCache symbols{"frozen stack layout fixture"};
    bool collector = true;
    bool compressed = false;
    Flag flags[2]{{"UseG1GC", &collector, VMFlag::Bool},
                  {"UseCompressedOops", &compressed, VMFlag::Bool}};
    const char* flag_base = (const char*)flags;
    size_t flag_count = 2;
    int offsets[9]{8, 16, 24, 32, 40, 48, 56, 64, 72};

    void configure() {
        VMTestAccessor::configureFrozenWalker();
        _libjvm = &symbols;
        _thread_oop_offset = 8;
        _oop_handle_offset = 0;
        _flags_addr = (address)&flag_base;
        _flag_count = (address)&flag_count;
        _flag_name_offset = offsetof(Flag, name);
        _flag_addr_offset = offsetof(Flag, value);
        _flag_type_offset = offsetof(Flag, type);
        TYPE_SIZE_NAME(VMFlag) = sizeof(Flag);
    }

    void exportLayout() {
        const char* names[]{
            "_ZN16java_lang_Thread20_continuation_offsetE",
            "_ZN28jdk_internal_vm_Continuation14_parent_offsetE",
            "_ZN28jdk_internal_vm_Continuation12_tail_offsetE",
            "_ZN26jdk_internal_vm_StackChunk14_parent_offsetE",
            "_ZN26jdk_internal_vm_StackChunk12_size_offsetE",
            "_ZN26jdk_internal_vm_StackChunk10_sp_offsetE",
            "_ZN26jdk_internal_vm_StackChunk14_bottom_offsetE",
            "_ZN26jdk_internal_vm_StackChunk15_argsize_offsetE",
            "_ZN23InstanceStackChunkKlass16_offset_of_stackE"};
        for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
            symbols.add(&offsets[i], sizeof(offsets[i]), names[i]);
        }
    }
};

TEST_F(FrozenStackWalkerInitializationTest, SuccessfulLayoutRemainsAvailableAcrossRepeatedInitialization) {
    ASSERT_EXIT({
        configure();
        exportLayout();
        FrozenStackWalker::init();
        EXPECT_TRUE(FrozenStackWalker::available());
        collector = false;
        FrozenStackWalker::init();
        EXPECT_TRUE(FrozenStackWalker::available());
        _exit(::testing::Test::HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
}

TEST_F(FrozenStackWalkerInitializationTest, SuccessfulLayoutDoesNotRereadMetadata) {
    ASSERT_EXIT({
        configure();
        exportLayout();
        FrozenStackWalker::init();
        EXPECT_TRUE(FrozenStackWalker::available());
        _flags_addr = nullptr;
        _libjvm = nullptr;
        FrozenStackWalker::init();
        EXPECT_TRUE(FrozenStackWalker::available());
        _exit(::testing::Test::HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
}

TEST_F(FrozenStackWalkerInitializationTest, IncompleteMetadataCanBeRetriedBeforePublication) {
    ASSERT_EXIT({
        configure();
        FrozenStackWalker::init();
        EXPECT_FALSE(FrozenStackWalker::available());
        exportLayout();
        FrozenStackWalker::init();
        EXPECT_TRUE(FrozenStackWalker::available());
        _exit(::testing::Test::HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
}

} // namespace
