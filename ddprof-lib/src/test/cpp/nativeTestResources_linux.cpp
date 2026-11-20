// Copyright 2026, Datadog, Inc.

#ifdef __linux__

#include <gtest/gtest.h>
#include <unistd.h>

using ReadExecutableLink = ssize_t (*)(const char*, char*, size_t);
// These cases run serially; death-test children inherit a private callback copy.
static ReadExecutableLink readExecutableLinkForTest = ::readlink;

// Substitute only this header's syscall so its error guards can be exercised.
#define readlink readExecutableLinkForTest
#include "nativeTestResources_linux.h"
#undef readlink

#include <string.h>
#include <vector>

class ScopedExecutableLink {
public:
    explicit ScopedExecutableLink(ReadExecutableLink replacement)
        : _previous(readExecutableLinkForTest) {
        readExecutableLinkForTest = replacement;
    }
    ~ScopedExecutableLink() { readExecutableLinkForTest = _previous; }
    ScopedExecutableLink(const ScopedExecutableLink&) = delete;
    ScopedExecutableLink& operator=(const ScopedExecutableLink&) = delete;

private:
    ReadExecutableLink _previous;
};

TEST(NativeTestResourcesTest, ResolvesReadableFixtureOutsideCheckout) {
    ASSERT_EXIT({
        if (chdir("/tmp") != 0) _exit(1);
        char path[PATH_MAX];
        if (!nativeTestResourcePath("patch-target-lib/libpatchtarget.so", path, sizeof(path))) {
            _exit(2);
        }
        _exit(access(path, R_OK) == 0 ? 0 : 3);
    }, ::testing::ExitedWithCode(0), "");
}

TEST(NativeTestResourcesTest, MissingFixtureFailsInsteadOfSkipping) {
    char path[PATH_MAX];
    auto result = nativeTestResourcePath("patch-target-lib/no-such-fixture.so", path, sizeof(path));
    ASSERT_FALSE(result);
    EXPECT_NE(nullptr, strstr(result.message(), "Missing test resource"));
    EXPECT_NE(nullptr, strstr(result.message(), "patch-target-lib/no-such-fixture.so"));
}

TEST(NativeTestResourcesTest, RejectsUnreadableExecutablePath) {
    ScopedExecutableLink link([](const char*, char*, size_t) -> ssize_t { return -1; });
    char path[PATH_MAX];
    auto result = nativeTestResourcePath("patch-target-lib/libpatchtarget.so", path, sizeof(path));
    ASSERT_FALSE(result);
    EXPECT_NE(nullptr, strstr(result.message(), "complete test executable path"));
}

TEST(NativeTestResourcesTest, RejectsTruncatedExecutablePath) {
    ScopedExecutableLink link([](const char*, char*, size_t capacity) -> ssize_t {
        return static_cast<ssize_t>(capacity);
    });
    char path[PATH_MAX];
    auto result = nativeTestResourcePath("patch-target-lib/libpatchtarget.so", path, sizeof(path));
    ASSERT_FALSE(result);
    EXPECT_NE(nullptr, strstr(result.message(), "complete test executable path"));
}

TEST(NativeTestResourcesTest, RequiresCapacityForTerminator) {
    char path[PATH_MAX];
    ASSERT_TRUE(nativeTestResourcePath("patch-target-lib/libpatchtarget.so", path, sizeof(path)));
    size_t length = strlen(path);
    std::vector<char> exact(length + 1);
    ASSERT_TRUE(nativeTestResourcePath("patch-target-lib/libpatchtarget.so", exact.data(), exact.size()));
    EXPECT_STREQ(path, exact.data());
    auto result = nativeTestResourcePath("patch-target-lib/libpatchtarget.so", exact.data(), length);
    ASSERT_FALSE(result);
    EXPECT_NE(nullptr, strstr(result.message(), "buffer capacity"));
    EXPECT_FALSE(nativeTestResourcePath("patch-target-lib/libpatchtarget.so", exact.data(), 0));
}

#endif
