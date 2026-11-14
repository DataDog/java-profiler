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
#include "testTempFile.h"

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

// Owns a read-only private mapping of a whole file; unmaps it on scope exit.
class FileMapping {
 public:
  explicit FileMapping(int fd) {
    struct stat st;
    if (fstat(fd, &st) != 0) {
      _failed_step = "fstat";
      _error = errno;
      return;
    }
    _size = st.st_size;
    _addr = mmap(NULL, _size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (_addr == MAP_FAILED) {
      _failed_step = "mmap";
      _error = errno;
    }
  }
  ~FileMapping() { if (_addr != MAP_FAILED) munmap(_addr, _size); }
  FileMapping(const FileMapping&) = delete;
  FileMapping& operator=(const FileMapping&) = delete;
  bool ok() const { return _addr != MAP_FAILED; }
  const char* failedStep() const { return _failed_step; }
  int error() const { return _error; }
  const char* base() const { return static_cast<const char*>(_addr); }
  size_t size() const { return _size; }

 private:
  void* _addr = MAP_FAILED;
  size_t _size = 0;
  const char* _failed_step = "";
  int _error = 0;
};

// A fresh copy of a file in TMPDIR, or /tmp when unset, removed on scope exit.
class TempCopy {
 public:
  explicit TempCopy(const char* from)
      : _error(copyToTempFile(from, nullptr, "libunloadprot", _path, sizeof(_path))) {}
  ~TempCopy() { if (_error == 0) unlink(_path); }
  TempCopy(const TempCopy&) = delete;
  TempCopy& operator=(const TempCopy&) = delete;
  int error() const { return _error; }
  const char* path() const { return _path; }

 private:
  char _path[PATH_MAX];
  int _error;
};

bool isLoaded(const char* path) {
  void* handle = dlopen(path, RTLD_LAZY | RTLD_NOLOAD);
  if (handle != nullptr) dlclose(handle);
  return handle != nullptr;
}

}  // namespace

// The loader's first mapping of a library it is still loading: at file offset 0,
// not yet known to the loader. UnloadProtection ignores the mapping's protection,
// so PROT_READ keeps the test working on a noexec TMPDIR.
TEST_F(UnloadProtectionTest, RejectsImageNotLoadedByTheLoader) {
  TempCopy copy(_lib_path);
  ASSERT_EQ(copy.error(), 0) << "copy to " << copy.path() << ": " << strerror(copy.error());
  FdOwner fd(open(copy.path(), O_RDONLY));
  ASSERT_GE(fd.get(), 0) << "open: " << strerror(errno);
  FileMapping map(fd.get());
  ASSERT_TRUE(map.ok()) << map.failedStep() << ": " << strerror(map.error());
  ASSERT_FALSE(isLoaded(copy.path())) << "the copy must not be loaded";

  CodeCache cc(copy.path(), 0, map.base(), map.base() + map.size(), map.base());
  EXPECT_FALSE(UnloadProtection(&cc).isValid());
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
