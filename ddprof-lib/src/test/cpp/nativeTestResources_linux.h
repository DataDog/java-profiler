// Copyright 2026, Datadog, Inc.

#ifndef NATIVE_TEST_RESOURCES_LINUX_H
#define NATIVE_TEST_RESOURCES_LINUX_H

#include <gtest/gtest.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

// Gtest binaries live in build/bin/gtest/<config>_<test>/, independently of cwd.
// Missing fixtures fail their caller instead of letting a suite exit without XML.
static ::testing::AssertionResult nativeTestResourcePath(const char* resource, char* path,
                                                        size_t capacity) {
    char executable[PATH_MAX];
    ssize_t length = readlink("/proc/self/exe", executable, sizeof(executable));
    if (length < 0 || static_cast<size_t>(length) == sizeof(executable)) {
        return ::testing::AssertionFailure() << "Cannot resolve the complete test executable path";
    }
    executable[length] = '\0';
    int required = snprintf(path, capacity, "%s/../../../test/resources/native-libs/%s",
                            dirname(executable), resource);
    if (static_cast<size_t>(required) >= capacity) {
        return ::testing::AssertionFailure() << "Native test resource path exceeds buffer capacity";
    }
    if (access(path, R_OK) != 0) {
        return ::testing::AssertionFailure() << "Missing test resource " << path
                                            << " (built by :ddprof-lib:buildNativeLibs)";
    }
    return ::testing::AssertionSuccess();
}

#endif
