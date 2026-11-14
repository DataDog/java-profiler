/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Symbols::parseLibraries() reads a library's dynamic section in memory only when
// UnloadProtection is valid, so it must reject a file mapping the loader has not
// finished, as /proc/self/maps shows during a concurrent dlopen() on musl.

#ifdef __linux__

#include <gtest/gtest.h>

#include "codeCache.h"
#include "symbols.h"

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <link.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace {

class UnloadProtectionTest : public ::testing::Test {
 protected:
  char _lib_path[PATH_MAX];

  // The binary lives in build/bin/gtest/<config>_<test>/; the DSO is built by
  // :ddprof-lib:buildNativeLibs, so a missing one is a build problem.
  void SetUp() override {
    char exe[PATH_MAX - 128];
    ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
    ASSERT_GT(len, 0) << strerror(errno);
    exe[len] = '\0';
    *strrchr(exe, '/') = '\0';
    snprintf(_lib_path, sizeof(_lib_path),
             "%s/../../../test/resources/native-libs/patch-target-lib/libpatchtarget.so", exe);
    ASSERT_EQ(access(_lib_path, R_OK), 0) << "Missing test resource " << _lib_path;
  }

  // Loads the test DSO, left loaded for the rest of the binary, and returns the
  // start of its lowest mapping, or nullptr on failure.
  const char* loadImageBase() {
    void* handle = dlopen(_lib_path, RTLD_NOW);
    EXPECT_NE(handle, nullptr) << dlerror();
    struct link_map* map;
    Dl_info info;
    if (handle == nullptr || dlinfo(handle, RTLD_DI_LINKMAP, &map) != 0 ||
        dladdr(map->l_ld, &info) == 0) {
      return nullptr;
    }
    return static_cast<const char*>(info.dli_fbase);
  }
};

// Copies the test DSO to a fresh file, so no test in this binary has loaded it.
static bool copyFile(const char* from, char* to, size_t size) {
  snprintf(to, size, "/tmp/libunloadprot-XXXXXX.so");
  int out = mkstemps(to, 3);
  if (out < 0) return false;
  int in = open(from, O_RDONLY);
  bool ok = in >= 0;
  char buf[8192];
  ssize_t n;
  while (ok && (n = read(in, buf, sizeof(buf))) > 0) {
    ok = write(out, buf, n) == n;
  }
  if (in >= 0) close(in);
  close(out);
  return ok;
}

}  // namespace

// The loader's first mapping of a library it is still loading: executable, at
// file offset 0, not yet known to the loader.
TEST_F(UnloadProtectionTest, RejectsImageNotLoadedByTheLoader) {
  char path[64];
  ASSERT_TRUE(copyFile(_lib_path, path, sizeof(path))) << strerror(errno);
  int fd = open(path, O_RDONLY);
  ASSERT_GE(fd, 0) << strerror(errno);
  struct stat st;
  ASSERT_EQ(fstat(fd, &st), 0);
  void* map = mmap(NULL, st.st_size, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);
  close(fd);
  ASSERT_NE(map, MAP_FAILED) << strerror(errno);
  ASSERT_EQ(dlopen(path, RTLD_LAZY | RTLD_NOLOAD), nullptr) << "the copy must not be loaded";

  const char* base = static_cast<const char*>(map);
  CodeCache cc(path, 0, base, base + st.st_size, base);
  EXPECT_FALSE(UnloadProtection(&cc).isValid());

  munmap(map, st.st_size);
  unlink(path);
}

TEST_F(UnloadProtectionTest, AcceptsLoadedImage) {
  const char* base = loadImageBase();
  ASSERT_NE(base, nullptr);
  CodeCache cc(_lib_path, 0, base, base + 1, base);
  EXPECT_TRUE(UnloadProtection(&cc).isValid());
}

// An address inside a loaded library that is not where its image starts.
TEST_F(UnloadProtectionTest, RejectsLoadedImageAtWrongBase) {
  const char* base = loadImageBase();
  ASSERT_NE(base, nullptr);
  const char* inside = base + 16;
  Dl_info info;
  ASSERT_NE(dladdr(inside, &info), 0) << "the address must belong to the loaded library";
  CodeCache cc(_lib_path, 0, inside, inside + 1, inside);
  EXPECT_FALSE(UnloadProtection(&cc).isValid());
}

#endif  // __linux__
