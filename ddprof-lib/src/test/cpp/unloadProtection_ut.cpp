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
#include <stdlib.h>
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

// Owns a file descriptor; closes it on scope exit.
class FdOwner {
 public:
  explicit FdOwner(int fd) : _fd(fd) {}
  ~FdOwner() { if (_fd >= 0) close(_fd); }
  FdOwner(const FdOwner&) = delete;
  FdOwner& operator=(const FdOwner&) = delete;
  int get() const { return _fd; }

 private:
  int _fd;
};

// Owns a read-only private mapping of a whole file; unmaps it on scope exit.
class FileMapping {
 public:
  explicit FileMapping(int fd) {
    struct stat st;
    if (fstat(fd, &st) == 0) {
      _size = st.st_size;
      _addr = mmap(NULL, _size, PROT_READ, MAP_PRIVATE, fd, 0);
    }
  }
  ~FileMapping() { if (_addr != MAP_FAILED) munmap(_addr, _size); }
  FileMapping(const FileMapping&) = delete;
  FileMapping& operator=(const FileMapping&) = delete;
  bool ok() const { return _addr != MAP_FAILED; }
  const char* base() const { return static_cast<const char*>(_addr); }
  size_t size() const { return _size; }

 private:
  void* _addr = MAP_FAILED;
  size_t _size = 0;
};

// A fresh copy of a file in TMPDIR, removed on scope exit.
class TempCopy {
 public:
  explicit TempCopy(const char* from) {
    const char* dir = getenv("TMPDIR");
    snprintf(_path, sizeof(_path), "%s/libunloadprot-XXXXXX.so",
             dir != nullptr && dir[0] != '\0' ? dir : "/tmp");
    FdOwner out(mkstemps(_path, 3));
    _created = out.get() >= 0;
    FdOwner in(_created ? open(from, O_RDONLY) : -1);
    char buf[8192];
    ssize_t n = -1;
    bool written = true;
    while (in.get() >= 0 && written && (n = read(in.get(), buf, sizeof(buf))) > 0) {
      written = write(out.get(), buf, n) == n;
    }
    _ok = in.get() >= 0 && written && n == 0;
  }
  ~TempCopy() { if (_created) unlink(_path); }
  TempCopy(const TempCopy&) = delete;
  TempCopy& operator=(const TempCopy&) = delete;
  bool ok() const { return _ok; }
  const char* path() const { return _path; }

 private:
  char _path[PATH_MAX];
  bool _created = false;
  bool _ok = false;
};

static bool isLoaded(const char* path) {
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
  ASSERT_TRUE(copy.ok()) << strerror(errno);
  FdOwner fd(open(copy.path(), O_RDONLY));
  ASSERT_GE(fd.get(), 0) << strerror(errno);
  FileMapping map(fd.get());
  ASSERT_TRUE(map.ok()) << strerror(errno);
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
