/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include <signal.h>
#include <setjmp.h>
#include <atomic>

#include "os.h"

/**
 * Test for signal handler chaining to prevent infinite loops.
 *
 * This test verifies that when we intercept sigaction calls from other libraries
 * (like wasmtime), the oldact we return points to the original handler (e.g., JVM's),
 * not to our handler. If we return our handler as oldact, the chain becomes:
 *   Us -> other_lib -> Us -> other_lib -> ... (infinite loop)
 *
 * The correct chain should be:
 *   Us -> other_lib -> original_handler (JVM)
 */

// Type for our sigaction hook function
typedef int (*sigaction_hook_t)(int, const struct sigaction*, struct sigaction*);

// Counter to detect infinite loops
static std::atomic<int> handler_call_count{0};
static const int MAX_HANDLER_CALLS = 10;

// Jump buffer for escaping infinite loops
static sigjmp_buf escape_jmp;
static std::atomic<bool> should_escape{false};

// The "other library's" handler (simulating wasmtime)
static struct sigaction other_lib_saved_oldact;

static void other_lib_handler(int signo, siginfo_t* siginfo, void* context) {
    handler_call_count++;

    // Detect infinite loop
    if (handler_call_count > MAX_HANDLER_CALLS) {
        // We're in an infinite loop - escape
        if (should_escape) {
            siglongjmp(escape_jmp, 1);
        }
        return;
    }

    // Simulate what wasmtime does: if we don't handle it, chain to "previous" handler
    // If oldact points back to our handler, this will cause infinite recursion
    if (other_lib_saved_oldact.sa_flags & SA_SIGINFO) {
        if (other_lib_saved_oldact.sa_sigaction != nullptr) {
            other_lib_saved_oldact.sa_sigaction(signo, siginfo, context);
        }
    } else if (other_lib_saved_oldact.sa_handler != SIG_DFL &&
               other_lib_saved_oldact.sa_handler != SIG_IGN &&
               other_lib_saved_oldact.sa_handler != nullptr) {
        other_lib_saved_oldact.sa_handler(signo);
    }
    // If oldact is SIG_DFL, we just return (signal will re-trigger or terminate)
}

// Our handler (profiler's handler)
static void our_handler(int signo, siginfo_t* siginfo, void* context) {
    handler_call_count++;

    // Detect infinite loop
    if (handler_call_count > MAX_HANDLER_CALLS) {
        if (should_escape) {
            siglongjmp(escape_jmp, 1);
        }
        return;
    }

    // We don't handle this signal, chain to the "other library" via chain target
    SigAction chain = OS::getSegvChainTarget();
    if (chain != nullptr) {
        chain(signo, siginfo, context);
    }
    // After chain returns (or if no chain), we return
}

// Original handler (simulating JVM's handler)
static std::atomic<bool> original_handler_called{false};
static void original_handler(int signo, siginfo_t* siginfo, void* context) {
    original_handler_called = true;
    // The original handler would normally handle the signal or terminate.
    // For this test, we just mark that we were called.
    if (should_escape) {
        siglongjmp(escape_jmp, 1);
    }
}

class SigactionInterceptionTest : public ::testing::Test {
protected:
    struct sigaction saved_segv_action;

    void SetUp() override {
        // Save current SIGSEGV handler
        sigaction(SIGSEGV, nullptr, &saved_segv_action);

        // Reset state
        handler_call_count = 0;
        original_handler_called = false;
        should_escape = false;
        memset(&other_lib_saved_oldact, 0, sizeof(other_lib_saved_oldact));
    }

    void TearDown() override {
        // Restore original SIGSEGV handler
        sigaction(SIGSEGV, &saved_segv_action, nullptr);
    }
};

/**
 * Test that sigaction interception returns the correct oldact.
 *
 * Setup:
 * 1. Install "original" handler (simulating JVM)
 * 2. Call protectSignalHandlers with "our" handler
 * 3. Install "our" handler
 * 4. "Other library" calls sigaction (via the hook) to install its handler
 * 5. Verify that oldact returned to "other library" is the original handler, not ours
 *
 * This ensures that when "other library" chains to oldact, it goes to the original
 * handler, not back to us (which would cause infinite loop).
 *
 * NOTE: We call the sigaction hook directly because in a standalone test binary,
 * GOT patching isn't active. This tests the core logic of the hook function.
 */
TEST_F(SigactionInterceptionTest, OldactPointsToOriginalHandler) {
    // Get the sigaction hook function
    sigaction_hook_t hook = (sigaction_hook_t)OS::getSigactionHook();
#ifdef __APPLE__
    // Sigaction interception is only implemented on Linux
    if (hook == nullptr) {
        GTEST_SKIP() << "Sigaction interception not implemented on macOS";
    }
#endif
    ASSERT_NE(hook, nullptr) << "getSigactionHook returned nullptr";

    // Step 1: Install "original" handler (simulating JVM)
    struct sigaction original_sa;
    memset(&original_sa, 0, sizeof(original_sa));
    original_sa.sa_sigaction = original_handler;
    original_sa.sa_flags = SA_SIGINFO;
    sigemptyset(&original_sa.sa_mask);
    sigaction(SIGSEGV, &original_sa, nullptr);

    // Step 2 & 3: Protect and install our handler
    // Note: protectSignalHandlers should save the current (original) handler
    OS::protectSignalHandlers(our_handler, nullptr);
    OS::replaceSigsegvHandler(our_handler);

    // Step 4: "Other library" calls sigaction via the hook to install its handler
    struct sigaction other_lib_sa;
    memset(&other_lib_sa, 0, sizeof(other_lib_sa));
    other_lib_sa.sa_sigaction = other_lib_handler;
    other_lib_sa.sa_flags = SA_SIGINFO;
    sigemptyset(&other_lib_sa.sa_mask);

    // Call the hook directly (simulates what GOT patching does in production)
    int result = hook(SIGSEGV, &other_lib_sa, &other_lib_saved_oldact);
    ASSERT_EQ(result, 0);

    // Step 5: Verify oldact
    // The oldact should point to original_handler, NOT to our_handler
    // If it points to our_handler, chaining will cause infinite loop

    // Check that oldact is not our handler
    if (other_lib_saved_oldact.sa_flags & SA_SIGINFO) {
        EXPECT_NE(other_lib_saved_oldact.sa_sigaction, our_handler)
            << "oldact points to our handler - this would cause infinite loop!";

        // It should be the original handler
        EXPECT_EQ(other_lib_saved_oldact.sa_sigaction, original_handler)
            << "oldact should be the original (JVM's) handler";
    } else {
        // If not SA_SIGINFO, check sa_handler
        EXPECT_NE(other_lib_saved_oldact.sa_handler, (void (*)(int))our_handler)
            << "oldact points to our handler - this would cause infinite loop!";
    }
}

/**
 * Test that signal chaining doesn't cause infinite loop.
 *
 * This test actually triggers a SIGSEGV and verifies the chain doesn't loop forever.
 * The chain should be: our_handler -> other_lib_handler -> original_handler
 *
 * NOTE: We use the hook directly to set up the interception since GOT patching
 * isn't active in the standalone test binary.
 */
TEST_F(SigactionInterceptionTest, NoInfiniteLoopOnChaining) {
    // Get the sigaction hook function
    sigaction_hook_t hook = (sigaction_hook_t)OS::getSigactionHook();
#ifdef __APPLE__
    // Sigaction interception is only implemented on Linux
    if (hook == nullptr) {
        GTEST_SKIP() << "Sigaction interception not implemented on macOS";
    }
#endif
    ASSERT_NE(hook, nullptr) << "getSigactionHook returned nullptr";

    // Setup: Install original handler (simulating JVM)
    struct sigaction original_sa;
    memset(&original_sa, 0, sizeof(original_sa));
    original_sa.sa_sigaction = original_handler;
    original_sa.sa_flags = SA_SIGINFO;
    sigemptyset(&original_sa.sa_mask);
    sigaction(SIGSEGV, &original_sa, nullptr);

    // Protect and install our handler
    OS::protectSignalHandlers(our_handler, nullptr);
    OS::replaceSigsegvHandler(our_handler);

    // "Other library" installs its handler via the hook
    struct sigaction other_lib_sa;
    memset(&other_lib_sa, 0, sizeof(other_lib_sa));
    other_lib_sa.sa_sigaction = other_lib_handler;
    other_lib_sa.sa_flags = SA_SIGINFO;
    sigemptyset(&other_lib_sa.sa_mask);
    hook(SIGSEGV, &other_lib_sa, &other_lib_saved_oldact);

    // Now trigger a SIGSEGV and see what happens
    should_escape = true;

    if (sigsetjmp(escape_jmp, 1) == 0) {
        // Trigger SIGSEGV by accessing null pointer
        volatile int* p = nullptr;
        *p = 42;  // This will trigger SIGSEGV

        // Should not reach here
        FAIL() << "SIGSEGV was not triggered";
    } else {
        // We escaped via siglongjmp
        // Check that we didn't loop too many times
        EXPECT_LE(handler_call_count.load(), MAX_HANDLER_CALLS)
            << "Handler was called too many times - possible infinite loop!";

        // Ideally, the chain should be: our_handler(1) -> other_lib(2) -> original(3)
        // So we expect around 3 calls, definitely less than MAX_HANDLER_CALLS
        EXPECT_LE(handler_call_count.load(), 5)
            << "Handler chain is longer than expected";

        // Verify the original handler was actually called (chain completed)
        EXPECT_TRUE(original_handler_called)
            << "Original handler was not called - chain may not be set up correctly";
    }
}
