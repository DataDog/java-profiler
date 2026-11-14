/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include "log.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char LOG_TEST_NAME[] = "LogTest";

class LogGlobalSetup {
public:
    LogGlobalSetup() {
        installGtestCrashHandler<LOG_TEST_NAME>();
    }
    ~LogGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static LogGlobalSetup global_setup;

static std::string readFile(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == nullptr) {
        return "";
    }
    std::string contents;
    char buf[256];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        contents.append(buf, n);
    }
    fclose(f);
    return contents;
}

// Log::open(NULL, NULL) is what a rejected execute0() command triggers when the
// command itself didn't specify log=/loglevel=. It must not clobber an already
// active custom log file - see javaApi.cpp's execute0 and log.cpp's Log::open.
TEST(LogTest, OpenWithBothNullDoesNotResetActiveLog) {
    char path[] = "/tmp/ddprof_log_ut_XXXXXX";
    int fd = mkstemp(path);
    ASSERT_GE(fd, 0);
    close(fd);

    Log::open(path, "DEBUG");
    Log::error("marker-before");

    Log::open(NULL, NULL);
    Log::error("marker-after");

    std::string contents = readFile(path);
    EXPECT_NE(contents.find("marker-before"), std::string::npos);
    EXPECT_NE(contents.find("marker-after"), std::string::npos);

    // Restore process-wide defaults before other gtest cases in this binary run.
    Log::open(NULL, "NONE");
    unlink(path);
}
