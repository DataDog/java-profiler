/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Unit tests for ErrnoPreserver (guards.h): errno is restored when the
// guarded scope exits, and -- because the guard is declared first and so
// destructs last -- the restore is the final word even when a later guard's
// destructor clobbers errno on its way out.

#include <gtest/gtest.h>
#include "guards.h"
#include "gtest_crash_handler.h"
#include <cerrno>

static constexpr char GUARDS_TEST_NAME[] = "GuardsTest";

class GuardsTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<GUARDS_TEST_NAME>();
    }
    void TearDown() override {
        restoreDefaultSignalHandlers();
    }
};

namespace {
// Stand-in for a guard whose destructor makes a syscall (e.g.
// PerfFdRearmGuard's ioctl()) and therefore leaves errno clobbered.
class ErrnoClobberingGuard {
public:
    explicit ErrnoClobberingGuard(int value) : _value(value) {}
    ~ErrnoClobberingGuard() { errno = _value; }
private:
    int _value;
};
}

TEST_F(GuardsTest, ErrnoPreserverRestoresOnScopeExit) {
    errno = EAGAIN;
    {
        ErrnoPreserver errno_preserver;
        errno = EINVAL;
    }
    EXPECT_EQ(EAGAIN, errno);
}

TEST_F(GuardsTest, ErrnoPreserverRestoresOnEarlyReturn) {
    errno = EAGAIN;
    [] {
        ErrnoPreserver errno_preserver;
        errno = EINVAL;
        return;
    }();
    EXPECT_EQ(EAGAIN, errno);
}

// The ordering invariant the handlers rely on: declared first, the preserver
// destructs last, after the clobbering guard has already run.
TEST_F(GuardsTest, ErrnoPreserverDeclaredFirstOutlivesClobberingGuard) {
    errno = EAGAIN;
    {
        ErrnoPreserver errno_preserver;
        ErrnoClobberingGuard clobber(EPIPE);
        errno = EINVAL;
    }
    EXPECT_EQ(EAGAIN, errno);
}
