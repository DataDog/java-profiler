/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#ifdef __linux__
#include "libraries.h"
#include "nativeTestResources_linux.h"
#include "libraryPatcher.h"
#include "nativeSocketInterposer.h"
#include "os.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <limits.h>
#include <memory>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <vector>

namespace {

class NettyEpollDiscoveryTest : public ::testing::TestWithParam<bool> {
protected:
  using FixtureFile = std::unique_ptr<FILE, decltype(&fclose)>;

  static void TearDownTestSuite() {
    inode_pins.clear();
  }

  void SetUp() override {
    ASSERT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    ASSERT_NE(nullptr, mkdtemp(temporary_directory));
    ASSERT_TRUE(nativeTestResourcePath("netty-epoll-discovery-lib/libjava.so",
                                       fixture_path, sizeof(fixture_path)));
    java_handle = dlopen(fixture_path, RTLD_NOW | RTLD_LOCAL);
    ASSERT_NE(nullptr, java_handle) << dlerror();
    *strrchr(fixture_path, '/') = '\0';
    fixture_root = fixture_path;
    // musl retains dlclosed fixture images, so measure their patch contribution
    // before loading this case's image instead of assuming a process-wide total.
    Libraries::instance()->updateSymbols(false);
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    existing_patches = LibraryPatcher::socket_patch_count_for_test();
    existing_libraries = LibraryPatcher::socket_library_count_for_test();
    LibraryPatcher::unpatch_socket_functions();
    RecordProperty("existing_patches", existing_patches);
    RecordProperty("existing_libraries", existing_libraries);
    char source_path[PATH_MAX];
    snprintf(source_path, sizeof(source_path), "%s/libshaded_netty_transport_native_epoll.so",
             fixture_root);
    snprintf(loaded_path, sizeof(loaded_path), "%s/relocated-transport.so", temporary_directory);
    FILE* source = fopen(source_path, "rb");
    ASSERT_NE(nullptr, source);
    FILE* target = fopen(loaded_path, "wb");
    if (target == nullptr) {
      fclose(source);
      FAIL() << "Cannot create fixture copy";
    }
    char buffer[4096];
    size_t count;
    while ((count = fread(buffer, 1, sizeof(buffer), source)) != 0) {
      EXPECT_EQ(count, fwrite(buffer, 1, count, target));
    }
    EXPECT_EQ(0, ferror(source));
    EXPECT_EQ(0, fclose(source));
    ASSERT_EQ(0, fclose(target));
    // Symbol discovery remembers parsed file identities across cases. Retain
    // each unlinked inode without a loader reference so unload checks still run.
    FixtureFile inode_pin(fopen(loaded_path, "rb"), fclose);
    ASSERT_NE(nullptr, inode_pin.get());
    struct stat identity;
    ASSERT_EQ(0, fstat(fileno(inode_pin.get()), &identity));
    for (const FixtureFile& previous : inode_pins) {
      struct stat previous_identity;
      ASSERT_EQ(0, fstat(fileno(previous.get()), &previous_identity));
      ASSERT_FALSE(identity.st_dev == previous_identity.st_dev &&
                   identity.st_ino == previous_identity.st_ino);
    }
    inode_pin_fd = fileno(inode_pin.get());
    inode_pins.push_back(std::move(inode_pin));
    fixture_file_id = CodeCache::makeFileId(major(identity.st_dev) << 8 | minor(identity.st_dev),
                                          identity.st_ino);
    printf("netty_fixture path=%s device=%lu inode=%lu file_id=%llu\n", loaded_path,
           static_cast<unsigned long>(identity.st_dev), static_cast<unsigned long>(identity.st_ino),
           static_cast<unsigned long long>(fixture_file_id));
    handle = dlopen(loaded_path, RTLD_NOW | RTLD_LOCAL);
    ASSERT_NE(nullptr, handle) << dlerror();
    symbol = dlsym(handle, "netty_fixture_read");
    ASSERT_NE(nullptr, symbol);
  }

  void TearDown() override {
    // Restoration precedes releasing the final loader reference on every exit.
    LibraryPatcher::unpatch_socket_functions();
    if (handle != nullptr) EXPECT_EQ(0, dlclose(handle));
    if (java_handle != nullptr) EXPECT_EQ(0, dlclose(java_handle));
    if (loaded_path[0] != '\0') unlink(loaded_path);
    if (inode_pin_fd >= 0) {
      struct stat identity;
      ASSERT_EQ(0, fstat(inode_pin_fd, &identity));
      EXPECT_EQ(0u, identity.st_nlink);
    }
    if (temporary_directory[0] != '\0') rmdir(temporary_directory);
  }

  CodeCache* loadedCache() {
    // The append-only symbol list retains unloaded ranges; dlopen may reuse one.
    const CodeCacheArray& libraries = Libraries::instance()->native_libs();
    for (int index = libraries.count() - 1; index >= 0; index--) {
      CodeCache* library = libraries.at(index);
      if (library != nullptr && strncmp(library->name(), loaded_path, strlen(loaded_path)) == 0) {
        return library;
      }
    }
    for (int index = 0; index < libraries.count(); index++) {
      CodeCache* library = libraries.at(index);
      if (library != nullptr) {
        printf("netty_cache path=%s file_id=%llu fixture_identity=%d\n", library->name(),
               static_cast<unsigned long long>(library->fileId()),
               library->fileId() == fixture_file_id);
      }
    }
    return nullptr;
  }

  static std::vector<FixtureFile> inode_pins;
  int inode_pin_fd = -1;
  u64 fixture_file_id = 0;
  char fixture_path[PATH_MAX] = {};
  const char* fixture_root = nullptr;
  int existing_patches = 0;
  int existing_libraries = 0;
  char temporary_directory[PATH_MAX] = "/tmp/ddprof-netty-discovery-XXXXXX";
  char loaded_path[PATH_MAX] = {};
  void* java_handle = nullptr;
  void* handle = nullptr;
  void* symbol = nullptr;
};

std::vector<NettyEpollDiscoveryTest::FixtureFile> NettyEpollDiscoveryTest::inode_pins;

TEST_P(NettyEpollDiscoveryTest, PatchesDeletedImageAndRetainsItUntilRestoration) {
  if (GetParam()) Libraries::instance()->updateSymbols(false);
  ASSERT_EQ(0, unlink(loaded_path));
  Libraries::instance()->updateSymbols(false);
  CodeCache* lib = loadedCache();
  ASSERT_NE(nullptr, lib);
  ASSERT_NE(nullptr, lib->findSymbol("JNI_OnLoad_netty_transport_native_epoll"));
  ASSERT_NE(nullptr, lib->findSymbol("JNI_OnUnload_netty_transport_native_epoll"));
  ASSERT_EQ(1u, lib->importCount(im_read));
  void** slot = lib->findImport(im_read);
  ASSERT_NE(nullptr, slot);
  void* original = __atomic_load_n(slot, __ATOMIC_ACQUIRE);
  ASSERT_NE(nullptr, original);
  size_t timed_count = lib->importCount(im_epoll_pwait2);
  ASSERT_GT(timed_count, 0u);
  ASSERT_LE(timed_count, 256u);
  std::vector<void**> timed_slots;
  std::vector<void*> timed_originals;
  size_t expected_patches = 1;
  for (size_t index = 0; index < timed_count; index++) {
    void** location = lib->findImport(im_epoll_pwait2, index);
    ASSERT_NE(nullptr, location);
    void* value = __atomic_load_n(location, __ATOMIC_ACQUIRE);
    timed_slots.push_back(location);
    timed_originals.push_back(value);
    expected_patches += value != nullptr;
  }
  void* timed_original = timed_originals.front();
  auto timed_wait = reinterpret_cast<int (*)()>(dlsym(handle, "netty_fixture_epoll_pwait2"));
  ASSERT_NE(nullptr, timed_wait);
  errno = 0;
  ASSERT_EQ(-1, timed_wait());
  int expected_errno = errno;
  ASSERT_TRUE(expected_errno == EBADF || expected_errno == ENOSYS);
  if (timed_original == nullptr) ASSERT_EQ(ENOSYS, expected_errno);
  RecordProperty("libc_epoll_pwait2", expected_errno == ENOSYS ? "ENOSYS" : "supported");
  auto verify_errno = [&]() {
    errno = 0;
    EXPECT_EQ(-1, timed_wait());
    EXPECT_EQ(expected_errno, errno);
  };

  ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
  EXPECT_EQ(existing_patches + expected_patches,
            static_cast<size_t>(LibraryPatcher::socket_patch_count_for_test()));
  EXPECT_EQ(existing_libraries + 1, LibraryPatcher::socket_library_count_for_test());
  EXPECT_EQ(reinterpret_cast<void*>(NativeSocketInterposer::read_hook),
            __atomic_load_n(slot, __ATOMIC_ACQUIRE));
  for (size_t index = 0; index < timed_count; index++) {
    EXPECT_EQ(timed_originals[index] == nullptr ? nullptr :
                  reinterpret_cast<void*>(NativeSocketInterposer::epoll_pwait2_hook),
              __atomic_load_n(timed_slots[index], __ATOMIC_ACQUIRE));
  }
  verify_errno();
  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(original, __atomic_load_n(slot, __ATOMIC_ACQUIRE));
  for (size_t index = 0; index < timed_count; index++) {
    EXPECT_EQ(timed_originals[index], __atomic_load_n(timed_slots[index], __ATOMIC_ACQUIRE));
  }
  verify_errno();

  // Reinstall and relinquish the caller's handle. The patcher's retained
  // reference must keep the deleted image mapped until it restores its slot.
  ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
  verify_errno();
  ASSERT_EQ(0, dlclose(handle));
  handle = nullptr;
  Dl_info info;
  ASSERT_NE(0, dladdr(symbol, &info));
  verify_errno();
  EXPECT_EQ(reinterpret_cast<void*>(NativeSocketInterposer::read_hook),
            __atomic_load_n(slot, __ATOMIC_ACQUIRE));
  LibraryPatcher::unpatch_socket_functions();
  if (!OS::isMusl()) EXPECT_EQ(0, dladdr(symbol, &info));
}

TEST_P(NettyEpollDiscoveryTest, PreservesNullOptionalSlotWithAvailableProvider) {
  // A relocation-time NULL must not become a positive Netty availability probe.
  // This is a slot-state control, not proof of an older-libc fallback cell.
  if (GetParam()) ASSERT_EQ(0, unlink(loaded_path));
  Libraries::instance()->updateSymbols(false);
  CodeCache* lib = loadedCache();
  ASSERT_NE(nullptr, lib);
  size_t count = lib->importCount(im_epoll_pwait2);
  ASSERT_GT(count, 0u);
  ASSERT_LE(count, 256u);
  std::vector<void**> slots;
  std::vector<void*> originals;
  for (size_t index = 0; index < count; index++) {
    void** location = lib->findImport(im_epoll_pwait2, index);
    ASSERT_NE(nullptr, location);
    slots.push_back(location);
    originals.push_back(__atomic_load_n(location, __ATOMIC_ACQUIRE));
  }
  ASSERT_TRUE(lib->prepareImportsForPatch());
  for (void** location : slots) {
    __atomic_store_n(location, static_cast<void*>(nullptr), __ATOMIC_RELEASE);
  }
  EXPECT_TRUE(LibraryPatcher::patch_socket_functions());
  EXPECT_EQ(existing_patches + 1, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(existing_libraries + 1, LibraryPatcher::socket_library_count_for_test());
  for (void** location : slots) {
    EXPECT_EQ(nullptr, __atomic_load_n(location, __ATOMIC_ACQUIRE));
  }
  LibraryPatcher::unpatch_socket_functions();
  for (size_t index = 0; index < count; index++) {
    EXPECT_EQ(nullptr, __atomic_load_n(slots[index], __ATOMIC_ACQUIRE));
    __atomic_store_n(slots[index], originals[index], __ATOMIC_RELEASE);
  }
}

INSTANTIATE_TEST_SUITE_P(ParsedBeforeUnlink, NettyEpollDiscoveryTest,
                         ::testing::Bool());

} // namespace
#endif // __linux__
