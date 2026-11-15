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
#include "symbols.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <future>
#include <limits.h>
#include <link.h>
#include <memory>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <vector>

namespace {

// Finish a concurrent final dlclose before discovery inspects the live image.
// The patcher's pin must retain it until the imports have been restored.
class UnloadAtMappingLookup {
public:
  UnloadAtMappingLookup(void*& handle, void* symbol, const char* phase = "mapping_lookup")
      : _handle(handle), _symbol(symbol), _phase(phase) {
    _current = this;
    LibraryPatcher::setSocketPatchObserverForTest(observe);
  }

  ~UnloadAtMappingLookup() {
    LibraryPatcher::setSocketPatchObserverForTest(nullptr);
    _current = nullptr;
  }

  UnloadAtMappingLookup(const UnloadAtMappingLookup&) = delete;
  UnloadAtMappingLookup& operator=(const UnloadAtMappingLookup&) = delete;

  bool reached = false;
  bool retained = false;

private:
  static void observe(const char* phase) {
    if (strcmp(phase, _current->_phase) != 0 || _current->reached) return;
    _current->reached = true;
    EXPECT_EQ(0, std::async(std::launch::async, []() {
      return dlclose(_current->_handle);
    }).get());
    _current->_handle = nullptr;
    Dl_info info;
    _current->retained = dladdr(_current->_symbol, &info) != 0;
  }

  static UnloadAtMappingLookup* _current;
  void*& _handle;
  void* _symbol;
  const char* _phase;
};

UnloadAtMappingLookup* UnloadAtMappingLookup::_current = nullptr;

class NettyEpollDiscoveryTest : public ::testing::TestWithParam<bool> {
protected:
  using FixtureFile = std::unique_ptr<FILE, decltype(&fclose)>;

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
    snprintf(loaded_path, sizeof(loaded_path), "%s/relocated-transport.so", temporary_directory);
    copyFixture("libshaded_netty_transport_native_epoll.so", loaded_path);
    ASSERT_FALSE(HasFatalFailure());
    pinFixtureInode(loaded_path);
    ASSERT_FALSE(HasFatalFailure());
    handle = dlopen(loaded_path, RTLD_NOW | RTLD_LOCAL);
    ASSERT_NE(nullptr, handle) << dlerror();
    symbol = dlsym(handle, "netty_fixture_read");
    ASSERT_NE(nullptr, symbol);
  }

  void copyFixture(const char* filename, const char* destination) {
    char source_path[PATH_MAX];
    snprintf(source_path, sizeof(source_path), "%s/%s", fixture_root, filename);
    FILE* source = fopen(source_path, "rb");
    ASSERT_NE(nullptr, source);
    FILE* target = fopen(destination, "wb");
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
  }

  void pinFixtureInode(const char* path) {
    // Symbol discovery remembers parsed identities for the process lifetime.
    // An FD retains the inode without preventing the DSO from unloading.
    FixtureFile inode_pin(fopen(path, "rb"), fclose);
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
    // This count outlives GoogleTest suite repeats, like the parsed-inode cache.
    static size_t pins_created = 0;
    ASSERT_EQ(++pins_created, inode_pins.size());
    fixture_file_id = CodeCache::makeFileId(major(identity.st_dev) << 8 | minor(identity.st_dev),
                                          identity.st_ino);
    printf("netty_fixture path=%s device=%lu inode=%lu file_id=%llu\n", loaded_path,
           static_cast<unsigned long>(identity.st_dev), static_cast<unsigned long>(identity.st_ino),
           static_cast<unsigned long long>(fixture_file_id));
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

TEST_P(NettyEpollDiscoveryTest, PinsFilenameBeforeConcurrentFinalClose) {
  if (OS::isMusl()) GTEST_SKIP() << "musl does not unmap dlclosed DSOs";
  Libraries::instance()->updateSymbols(false);
  CodeCache* lib = loadedCache();
  ASSERT_NE(nullptr, lib);
  if (GetParam()) ASSERT_EQ(0, unlink(loaded_path));
  UnloadAtMappingLookup unload(handle, symbol);
  ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
  ASSERT_TRUE(unload.reached);
  ASSERT_TRUE(unload.retained) << "filename lookup must retain the image across final dlclose";
  EXPECT_EQ(existing_libraries + 1, LibraryPatcher::socket_library_count_for_test());
  Dl_info info;
  EXPECT_NE(0, dladdr(symbol, &info));
  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(0, dladdr(symbol, &info));
}

TEST_P(NettyEpollDiscoveryTest, SkipsImageUnloadedBeforePin) {
  if (OS::isMusl()) GTEST_SKIP() << "musl does not unmap dlclosed DSOs";
  Libraries::instance()->updateSymbols(false);
  ASSERT_NE(nullptr, loadedCache());
  if (GetParam()) ASSERT_EQ(0, unlink(loaded_path));
  UnloadAtMappingLookup unload(handle, symbol, "start_snapshot");
  ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
  ASSERT_TRUE(unload.reached);
  EXPECT_FALSE(unload.retained);
  EXPECT_EQ(existing_patches, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(existing_libraries, LibraryPatcher::socket_library_count_for_test());
}

TEST_P(NettyEpollDiscoveryTest, RejectsCacheWithoutImageFingerprint) {
  Libraries::instance()->updateSymbols(false);
  CodeCache* lib = loadedCache();
  ASSERT_NE(nullptr, lib);
  ASSERT_NE(0ULL, lib->imageFingerprint());
  lib->setImageFingerprint(0);
  if (GetParam()) ASSERT_EQ(0, unlink(loaded_path));
  ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
  EXPECT_EQ(existing_patches, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(existing_libraries, LibraryPatcher::socket_library_count_for_test());
}

TEST_P(NettyEpollDiscoveryTest, RejectsDifferentImageAtSamePathAndBase) {
  if (OS::isMusl()) GTEST_SKIP() << "musl does not unmap dlclosed DSOs";
  Libraries::instance()->updateSymbols(false);
  CodeCache* lib = loadedCache();
  ASSERT_NE(nullptr, lib);
  ASSERT_NE(0ULL, lib->imageFingerprint());
  void** old_slot = lib->peekImport(im_read);
  ASSERT_NE(nullptr, old_slot);
  const void* base = lib->imageBase();
  ASSERT_EQ(0, dlclose(handle));
  handle = nullptr;
  Dl_info info;
  ASSERT_EQ(0, dladdr(symbol, &info));
  ASSERT_EQ(0, unlink(loaded_path));
  copyFixture("libreplacement_netty_transport_native_epoll.so", loaded_path);
  ASSERT_FALSE(HasFatalFailure());
  pinFixtureInode(loaded_path);
  ASSERT_FALSE(HasFatalFailure());
  handle = dlopen(loaded_path, RTLD_NOW | RTLD_LOCAL);
  ASSERT_NE(nullptr, handle) << dlerror();
  symbol = dlsym(handle, "netty_fixture_read");
  ASSERT_NE(nullptr, symbol);
  ASSERT_NE(0, dladdr(symbol, &info));
  ASSERT_EQ(base, info.dli_fbase) << "replacement must actually reuse the cached base";
  ASSERT_STREQ(loaded_path, info.dli_fname);
  struct Query { const void* base; u64 fingerprint; } query{base, 0};
  dl_iterate_phdr([](struct dl_phdr_info* image, size_t, void* data) {
    Query* query = static_cast<Query*>(data);
    if (reinterpret_cast<const void*>(image->dlpi_addr) != query->base) return 0;
    query->fingerprint = Symbols::imageFingerprint(image->dlpi_phdr, image->dlpi_phnum,
                                                  image->dlpi_addr);
    return 1;
  }, &query);
  ASSERT_NE(0ULL, query.fingerprint);
  ASSERT_NE(lib->imageFingerprint(), query.fingerprint);
  if (GetParam()) ASSERT_EQ(0, unlink(loaded_path));
  void* replacement_value = __atomic_load_n(old_slot, __ATOMIC_ACQUIRE);
  ASSERT_NE(nullptr, replacement_value);
  ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
  EXPECT_EQ(replacement_value, __atomic_load_n(old_slot, __ATOMIC_ACQUIRE));
  EXPECT_EQ(existing_patches, LibraryPatcher::socket_patch_count_for_test());
  EXPECT_EQ(existing_libraries, LibraryPatcher::socket_library_count_for_test());
  LibraryPatcher::unpatch_socket_functions();
  EXPECT_EQ(replacement_value, __atomic_load_n(old_slot, __ATOMIC_ACQUIRE));
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
