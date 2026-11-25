/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// LibraryPatcher keeps raw GOT-slot addresses of patched DSOs (and
// CodeCacheArray never drops a CodeCache), but nothing pins those DSOs. Once a
// patched DSO is dlclose()d and unmapped, restoring the hooks on stop, or
// re-installing them on the next start, must not write through the stale
// address: that is a SIGSEGV if the range is unmapped and silent corruption if
// something else reused it.

#ifdef __linux__

#include <gtest/gtest.h>

#include "codeCache.h"
#include "libraries.h"
#include "libraryPatcher.h"
#include "libraryPatcherTestAccessor.h"
#include "nativeSocketSampler.h"
#include "os.h"
#include "symbols.h"
#include "testTempFile.h"

#include <atomic>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <link.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#ifndef MAP_FIXED_NOREPLACE
#define MAP_FIXED_NOREPLACE 0x100000
#endif

namespace {

// Child exit codes. Anything not listed here is unexpected.
enum ChildExit {
  CHILD_OK = 0,
  CHILD_SANITIZER = 1,      // sanitizers report a SEGV by exiting with 1, not by the signal
  CHILD_CORRUPTED = 20,     // the stale GOT write landed in a foreign mapping
  CHILD_SKIP = 77,          // environment cannot exercise the scenario
  CHILD_DLOPEN_FAILED = 10,
  CHILD_LIB_NOT_FOUND = 11,
  CHILD_NO_IMPORT = 12,
  CHILD_SLOT_NOT_HOOKED = 14,
  CHILD_NOT_RESTORED = 15,  // the DSO is mapped but unpatching did not restore its slot
  CHILD_NO_FINGERPRINT = 16,
  CHILD_SAME_FINGERPRINT = 17,  // two different builds got the same fingerprint
  CHILD_DEADLOCK = 18,          // patching threads still blocked when the alarm fired
  CHILD_THREAD_FAILED = 19,
  CHILD_UNHOOKED_BY_STOP = 21,  // a persistent hook was undone by the recording unpatch
  CHILD_FOREIGN_TAKEN = 22,     // a slot holding a foreign value was overwritten
  CHILD_NOT_RECHECKED = 23,     // a pending library was not looked at again
  CHILD_RECHECKED_SETTLED = 24, // a pending entry made a settled one be re-checked
  CHILD_STILL_PENDING = 25,     // an unloaded library's entry stayed pending
  CHILD_NOT_CAPTURED = 26,      // the pass did not take the profiler's bound PLT slot
  CHILD_PATCHED_UNAWAITED = 27, // the extra pass ran with no capture awaited
};

const unsigned char SENTINEL = 0xA5;

char g_lib_path[PATH_MAX];

// The LibraryPatcher patching under test.
struct PatchKind {
  const char* name;
  ImportId import;  // the test DSO's import that gets patched
  void (*patch)();
  void (*unpatch)();
  // The hook outlives the recording unpatch: the slot must stay hooked after it.
  bool persistent;
};

const PatchKind SOCKET = {
  "socket", im_write,
  []() { LibraryPatcher::patch_socket_functions(); },
  []() { LibraryPatcher::unpatch_socket_functions(); },
  false,
};

const PatchKind PTHREAD_CREATE = {
  "pthread_create", im_pthread_create,
  []() {
    LibraryPatcher::initialize_persistent();
    LibraryPatcher::patch_libraries();
  },
  // The pthread_create hook is persistent: unpatch_recording_hooks() only undoes
  // the socket hooks, and the tests check that the slot stays hooked.
  []() { LibraryPatcher::unpatch_recording_hooks(); },
  true,
};

struct LoadedLib {
  void* handle;
  void** slot;  // the DSO's GOT slot for the patched import
  void* orig;   // the slot's value before patching
};

// Skips unless dlclose() really unmaps the test DSO at path when nothing else
// holds it (it never does on musl). Runs before the profiler sees the DSO, so
// a fix that pins patched DSOs cannot turn this into a skip.
void requireUnloadableEnvironment(const char* path = g_lib_path) {
  void* handle = dlopen(path, RTLD_NOW);
  if (handle == nullptr) _exit(CHILD_DLOPEN_FAILED);
  dlclose(handle);
  if (dlopen(path, RTLD_NOLOAD | RTLD_LAZY) != nullptr) _exit(CHILD_SKIP);
}

// Loads the test DSO, registers it with Libraries and returns its GOT slot
// for kind's import. Exits the child on any failure so callers stay linear.
LoadedLib loadLib(const PatchKind& kind) {
  requireUnloadableEnvironment();
  void* handle = dlopen(g_lib_path, RTLD_NOW);
  if (handle == nullptr) _exit(CHILD_DLOPEN_FAILED);
  Libraries* libs = Libraries::instance();
  libs->updateSymbols(false);
  CodeCache* cc = libs->findLibraryByName("libpatchtarget");
  if (cc == nullptr) _exit(CHILD_LIB_NOT_FOUND);
  void** slot = cc->findImport(kind.import);
  if (slot == nullptr) _exit(CHILD_NO_IMPORT);
  return {handle, slot, *slot};
}

void patchAndVerify(const PatchKind& kind, const LoadedLib& lib) {
  kind.patch();
  if (*lib.slot == lib.orig) _exit(CHILD_SLOT_NOT_HOOKED);
}

uintptr_t pageOf(void** slot) {
  return (uintptr_t)slot & ~((uintptr_t)sysconf(_SC_PAGESIZE) - 1);
}

// Drops the test's reference to the DSO. Returns true if the DSO got
// unmapped, false if it stayed loaded, i.e. the profiler pinned it (the
// environment check already showed nothing else would). In the latter case a
// reference is kept so the slot stays readable.
bool unload(void* handle, void** slot, const char* path = g_lib_path) {
  dlclose(handle);
  if (dlopen(path, RTLD_NOLOAD | RTLD_LAZY) != nullptr) return false;
  // msync() fails with ENOMEM iff the range is not mapped.
  if (msync((void*)pageOf(slot), sysconf(_SC_PAGESIZE), MS_ASYNC) == 0 || errno != ENOMEM) {
    _exit(CHILD_SKIP);  // already reused by an unrelated mapping
  }
  return true;
}

// For a DSO that stayed loaded: unpatching must restore the original binding,
// except for a persistent hook, which must stay in place.
void unpatchAndVerifyRestored(const PatchKind& kind, const LoadedLib& lib) {
  kind.unpatch();
  if (kind.persistent) {
    if (*lib.slot == lib.orig) _exit(CHILD_UNHOOKED_BY_STOP);
    return;
  }
  if (*lib.slot != lib.orig) _exit(CHILD_NOT_RESTORED);
}

// Maps an anonymous page where the stale GOT slot used to live and fills it
// with SENTINEL, emulating an unrelated mapping that reused the address.
unsigned char* mapSentinelPage(void** slot) {
  size_t ps = sysconf(_SC_PAGESIZE);
  void* want = (void*)pageOf(slot);
  void* got = mmap(want, ps, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
  if (got != want) _exit(CHILD_SKIP);
  memset(got, SENTINEL, ps);
  return (unsigned char*)got;
}

bool sentinelIntact(const unsigned char* page) {
  size_t ps = sysconf(_SC_PAGESIZE);
  for (size_t i = 0; i < ps; i++) {
    if (page[i] != SENTINEL) return false;
  }
  return true;
}

// Reloads the test DSO after unload(). Skips unless it lands at its old base,
// which is what the scenarios using this need.
void* reloadAtSameBase(void* old_base) {
  void* handle = dlopen(g_lib_path, RTLD_NOW);
  if (handle == nullptr) _exit(CHILD_DLOPEN_FAILED);
  struct link_map* map = nullptr;
  if (dlinfo(handle, RTLD_DI_LINKMAP, &map) != 0 || (void*)map->l_addr != old_base) {
    _exit(CHILD_SKIP);
  }
  return handle;
}

void* loadBaseOf(void* handle) {
  struct link_map* map = nullptr;
  if (dlinfo(handle, RTLD_DI_LINKMAP, &map) != 0) _exit(CHILD_DLOPEN_FAILED);
  return (void*)map->l_addr;
}

// Runs scenario in a forked child (patching is process-global and the bug can
// crash) and turns the outcome into a gtest result.
template <typename Scenario>
void runInChild(Scenario scenario) {
  fflush(stdout);
  fflush(stderr);
  pid_t pid = fork();
  ASSERT_NE(pid, -1) << strerror(errno);
  if (pid == 0) {
    scenario();
    _exit(CHILD_OK);
  }
  int status = 0;
  ASSERT_EQ(waitpid(pid, &status, 0), pid);
  if (WIFSIGNALED(status)) {
    FAIL() << "child crashed with signal " << WTERMSIG(status) << " ("
           << strsignal(WTERMSIG(status)) << ") writing through a stale GOT slot";
  }
  ASSERT_TRUE(WIFEXITED(status));
  int code = WEXITSTATUS(status);
  if (code == CHILD_SKIP) {
    GTEST_SKIP() << "patched DSO was not unmapped by dlclose() or its address could not be reclaimed";
  }
  ASSERT_NE(code, CHILD_SANITIZER) << "child died in a sanitizer report (SEGV writing through a stale GOT slot?)";
  ASSERT_NE(code, CHILD_CORRUPTED) << "stale GOT write corrupted the mapping that reused the address";
  ASSERT_NE(code, CHILD_NOT_RESTORED) << "DSO is still mapped but its slot was not restored";
  ASSERT_NE(code, CHILD_SLOT_NOT_HOOKED) << "patching did not hook the loaded DSO";
  ASSERT_NE(code, CHILD_UNHOOKED_BY_STOP) << "a persistent hook was undone by the recording unpatch";
  ASSERT_NE(code, CHILD_FOREIGN_TAKEN) << "a slot holding a foreign value was overwritten";
  ASSERT_NE(code, CHILD_NOT_RECHECKED) << "a pending library was not looked at again";
  ASSERT_NE(code, CHILD_RECHECKED_SETTLED) << "a pending entry made a settled one be re-checked";
  ASSERT_NE(code, CHILD_STILL_PENDING) << "an unloaded library's entry stayed pending";
  ASSERT_NE(code, CHILD_NOT_CAPTURED) << "the pass did not take the profiler's bound PLT slot";
  ASSERT_NE(code, CHILD_PATCHED_UNAWAITED) << "the extra pass ran with no capture awaited";
  ASSERT_NE(code, CHILD_NO_FINGERPRINT) << "the test DSO's CodeCache has no image fingerprint";
  ASSERT_NE(code, CHILD_SAME_FINGERPRINT) << "two different builds have the same fingerprint";
  ASSERT_NE(code, CHILD_DEADLOCK) << "patching deadlocked against the loader's dl_load_write_lock";
  ASSERT_EQ(code, CHILD_OK) << "child precondition failed with exit code " << code;
}

// The binary lives in build/bin/gtest/<config>_<test>/; resolve the DSO
// relative to it so the result does not depend on the working directory.
// A missing DSO is a build problem, so fail instead of skipping.
void resolveLibPath() {
  char exe[PATH_MAX - 128];
  ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
  ASSERT_GT(len, 0) << strerror(errno);
  exe[len] = '\0';
  *strrchr(exe, '/') = '\0';
  snprintf(g_lib_path, sizeof(g_lib_path),
           "%s/../../../test/resources/native-libs/patch-target-lib/libpatchtarget.so", exe);
  ASSERT_EQ(access(g_lib_path, R_OK), 0) << "Missing test resource " << g_lib_path
                                         << " (built by :ddprof-lib:buildNativeLibs)";
}

class LibraryPatcherUnloadTest : public ::testing::TestWithParam<const PatchKind*> {
 protected:
  void SetUp() override { resolveLibPath(); }
};

class LibraryPatcherIdentityTest : public ::testing::Test {
 protected:
  void SetUp() override { resolveLibPath(); }
};

class LibraryPatcherRecheckTest : public ::testing::Test {
 protected:
  void SetUp() override { resolveLibPath(); }
};

class LibraryPatcherLockOrderTest : public ::testing::Test {
 protected:
  void SetUp() override { resolveLibPath(); }
};

}  // namespace

// Stop after the patched DSO was unloaded and its address reused: restoring
// the hooks must not write into the new mapping.
TEST_P(LibraryPatcherUnloadTest, UnpatchDoesNotWriteIntoReusedMapping) {
  const PatchKind& kind = *GetParam();
  runInChild([&]() {
    LoadedLib lib = loadLib(kind);
    patchAndVerify(kind, lib);
    if (!unload(lib.handle, lib.slot)) return unpatchAndVerifyRestored(kind, lib);
    unsigned char* page = mapSentinelPage(lib.slot);
    kind.unpatch();
    if (!sentinelIntact(page)) _exit(CHILD_CORRUPTED);
  });
}

// Stop after the patched DSO was unloaded and the range left unmapped:
// restoring the hooks must not fault.
TEST_P(LibraryPatcherUnloadTest, UnpatchDoesNotFaultOnUnmappedLibrary) {
  const PatchKind& kind = *GetParam();
  runInChild([&]() {
    LoadedLib lib = loadLib(kind);
    patchAndVerify(kind, lib);
    if (!unload(lib.handle, lib.slot)) return unpatchAndVerifyRestored(kind, lib);
    kind.unpatch();
  });
}

// Start/stop, unload while stopped, start again: the re-scan of the
// never-pruned library list must not touch the unloaded DSO's GOT slot.
TEST_P(LibraryPatcherUnloadTest, RepatchDoesNotWriteIntoReusedMapping) {
  const PatchKind& kind = *GetParam();
  runInChild([&]() {
    LoadedLib lib = loadLib(kind);
    patchAndVerify(kind, lib);
    kind.unpatch();
    if (!unload(lib.handle, lib.slot)) return;  // still mapped: re-patching it is legitimate
    unsigned char* page = mapSentinelPage(lib.slot);
    // Check before any unpatch: restoring would write back the sentinel bytes
    // the buggy patch read from the slot and hide the corruption.
    kind.patch();
    if (!sentinelIntact(page)) _exit(CHILD_CORRUPTED);
  });
}

// The same file reloaded at the same base is still represented by the old
// CodeCache: the reload is not re-parsed, since its inode was seen before. Its
// saved slots are valid for the identical layout, but the test DSO has full
// RELRO, so the new mapping's GOT is read-only again. Re-installing the hooks
// on the next start must make it writable rather than trust the old state.
// For the persistent pthread_create patch the unpatch is a no-op, so this also
// checks that its stale entry does not stop the reloaded GOT being re-hooked.
TEST_P(LibraryPatcherUnloadTest, RepatchAfterReloadAtSameBase) {
  const PatchKind& kind = *GetParam();
  runInChild([&]() {
    LoadedLib lib = loadLib(kind);
    void* base = loadBaseOf(lib.handle);
    patchAndVerify(kind, lib);
    kind.unpatch();
    if (!unload(lib.handle, lib.slot)) return;  // still mapped: nothing was reloaded
    lib.handle = reloadAtSameBase(base);
    lib.orig = *lib.slot;
    patchAndVerify(kind, lib);
    unpatchAndVerifyRestored(kind, lib);
  });
}

// As above, but the reload happens while patched: stopping must restore the
// new mapping's read-only slot.
TEST_P(LibraryPatcherUnloadTest, UnpatchAfterReloadAtSameBase) {
  const PatchKind& kind = *GetParam();
  runInChild([&]() {
    LoadedLib lib = loadLib(kind);
    void* base = loadBaseOf(lib.handle);
    patchAndVerify(kind, lib);
    if (!unload(lib.handle, lib.slot)) return unpatchAndVerifyRestored(kind, lib);
    lib.handle = reloadAtSameBase(base);
    // With -z now the reload resolves the slot to the same function, which is
    // also the value saved when patching.
    if (*lib.slot != lib.orig) _exit(CHILD_SKIP);
    // A persistent hook is not re-applied to a reloaded image before the next
    // patch pass, so its fresh slot is unhooked here: nothing to check.
    if (kind.persistent) {
      kind.unpatch();
      return;
    }
    unpatchAndVerifyRestored(kind, lib);
  });
}

// The liveness check must not get in the way of a DSO that is still loaded.
TEST_P(LibraryPatcherUnloadTest, UnpatchRestoresLoadedLibrary) {
  const PatchKind& kind = *GetParam();
  runInChild([&]() {
    LoadedLib lib = loadLib(kind);
    patchAndVerify(kind, lib);
    unpatchAndVerifyRestored(kind, lib);
  });
}

INSTANTIATE_TEST_SUITE_P(PatchKinds, LibraryPatcherUnloadTest,
                         ::testing::Values(&SOCKET, &PTHREAD_CREATE),
                         [](const ::testing::TestParamInfo<const PatchKind*>& info) {
                           return std::string(info.param == &SOCKET ? "Socket" : "PthreadCreate");
                         });

// Exits the child with code after removing the temporary file at path.
[[noreturn]] static void exitRemoving(const char* path, int code) {
  unlink(path);
  _exit(code);
}

// Copies the test DSO to a fresh file in /tmp and returns its path in path_out.
// /tmp, not TMPDIR: the copy is dlopen()ed, and a noexec TMPDIR would make that
// fail. Exits the child on failure.
static void copyLibToTemp(char* path_out, size_t size) {
  int err = copyToTempFile(g_lib_path, "/tmp", "libpatchtarget", path_out, size);
  if (err != 0) {
    fprintf(stderr, "copying %s to /tmp: %s\n", g_lib_path, strerror(err));
    _exit(CHILD_DLOPEN_FAILED);
  }
}

// The name a library is loaded by.
enum LoadName { BY_PATH, BY_RELATIVE_PATH, BY_SYMLINK };

// Loads a temporary copy of the test DSO and unlinks the file, before or
// after Libraries parses it, like JNI loaders that extract to a temporary
// file. The loader keeps the name it was given, while /proc/self/maps has
// the resolved absolute path.
static LoadedLib loadUnlinkedLib(bool unlink_before_parse, LoadName load_name) {
  char path[PATH_MAX];
  copyLibToTemp(path, sizeof(path));
  char name[PATH_MAX + 16];
  if (load_name == BY_RELATIVE_PATH) {
    snprintf(name, sizeof(name), "./%s", strrchr(path, '/') + 1);
    if (chdir("/tmp") != 0) exitRemoving(path, CHILD_DLOPEN_FAILED);
  } else if (load_name == BY_SYMLINK) {
    snprintf(name, sizeof(name), "%s.link.so", path);
    if (symlink(path, name) != 0) exitRemoving(path, CHILD_DLOPEN_FAILED);
  } else {
    snprintf(name, sizeof(name), "%s", path);
  }
  void* handle = dlopen(name, RTLD_NOW);
  if (load_name == BY_SYMLINK) unlink(name);
  if (handle == nullptr) exitRemoving(path, CHILD_DLOPEN_FAILED);
  if (unlink_before_parse) unlink(path);
  Libraries::instance()->updateSymbols(false);
  if (!unlink_before_parse) unlink(path);
  CodeCache* cc = Libraries::instance()->findLibraryByName("libpatchtarget");
  if (cc == nullptr) _exit(CHILD_LIB_NOT_FOUND);
  void** slot = cc->findImport(im_write);
  if (slot == nullptr) _exit(CHILD_NO_IMPORT);
  return {handle, slot, *slot};
}

// The hooks of an unlinked library must still be installed and restored: the
// loader's name no longer resolves to the file, so only the image fingerprint
// identifies it.
static void patchAndRestoreUnlinkedLibrary(bool unlink_before_parse, LoadName load_name) {
  LoadedLib lib = loadUnlinkedLib(unlink_before_parse, load_name);
  patchAndVerify(SOCKET, lib);
  unpatchAndVerifyRestored(SOCKET, lib);
}

TEST_F(LibraryPatcherIdentityTest, PatchesLibraryUnlinkedBeforeParsing) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(true, BY_PATH); });
}

TEST_F(LibraryPatcherIdentityTest, PatchesLibraryUnlinkedAfterParsing) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(false, BY_PATH); });
}

// /proc/self/maps records the absolute path, the loader keeps "./<name>".
// Unlinked after parsing: before it, Symbols::parseLibraries cannot verify a
// relatively loaded library (UnloadProtection's dlopen by the absolute path
// fails) and never reads its imports, so there would be nothing to patch.
TEST_F(LibraryPatcherIdentityTest, PatchesLibraryLoadedByRelativePathAndUnlinked) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(false, BY_RELATIVE_PATH); });
}

// Loaded through a symlink that is gone, and the file behind it unlinked.
TEST_F(LibraryPatcherIdentityTest, PatchesLibraryLoadedBySymlinkAndUnlinked) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(false, BY_SYMLINK); });
}

// Registers a CodeCache that claims the test DSO's image base, with the given
// file and image identity and a write() import pointing at *slot.
static void addCacheAtLibraryBase(CodeCache* real, u64 file_id, u64 fingerprint, void** slot) {
  if (real->imageFingerprint() == 0) _exit(CHILD_NO_FINGERPRINT);
  CodeCache* cc = new CodeCache("fake-at-same-base", -1, real->minAddress(), real->maxAddress(),
                                real->imageBase(), /*imports_patchable=*/true);
  cc->setFileId(file_id);
  cc->setImageFingerprint(fingerprint);
  cc->addImport(slot, "write");
  Libraries::instance()->addLibraryForTest(cc);
}

// Patches with a fake cache at the test DSO's base and reports whether the
// fake's slot was written. The real DSO must be hooked either way.
static bool patchWritesFakeCache(const LoadedLib& lib, u64 file_id, u64 fingerprint) {
  CodeCache* real = Libraries::instance()->findLibraryByName("libpatchtarget");
  static void* word = (void*)&SENTINEL;
  addCacheAtLibraryBase(real, file_id, fingerprint, &word);
  LibraryPatcher::patch_socket_functions();
  if (*lib.slot != (void*)NativeSocketSampler::write_hook) _exit(CHILD_SLOT_NOT_HOOKED);
  return word != (void*)&SENTINEL;
}

static CodeCache* realCache() {
  return Libraries::instance()->findLibraryByName("libpatchtarget");
}

// A stale CodeCache whose library was replaced by a different one at the
// same base must not be patched: the slot address now belongs to the new
// library. It has neither the file nor the image identity of the new one.
TEST_F(LibraryPatcherIdentityTest, PatchSkipsCacheOfDifferentImageAtSameBase) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    if (patchWritesFakeCache(lib, realCache()->fileId() + 1, realCache()->imageFingerprint() + 1)) {
      _exit(CHILD_CORRUPTED);
    }
  });
}

// The backing file alone does not identify the image when the cache has a
// fingerprint: a different build can reuse the inode of an unloaded library's
// deleted file, and is then not parsed, because the inode has been seen.
TEST_F(LibraryPatcherIdentityTest, PatchSkipsCacheOfSameFileButDifferentImage) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    if (patchWritesFakeCache(lib, realCache()->fileId(), realCache()->imageFingerprint() + 1)) {
      _exit(CHILD_CORRUPTED);
    }
  });
}

// Control for the tests above: the image identity alone is enough.
TEST_F(LibraryPatcherIdentityTest, PatchAcceptsCacheOfSameImageAtSameBase) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    if (!patchWritesFakeCache(lib, realCache()->fileId() + 1, realCache()->imageFingerprint())) {
      _exit(CHILD_SLOT_NOT_HOOKED);
    }
  });
}

// A cache without a fingerprint, e.g. one whose notes lay outside the range
// parsed, falls back to the backing file.
TEST_F(LibraryPatcherIdentityTest, PatchAcceptsCacheWithoutFingerprintOfSameFile) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    if (!patchWritesFakeCache(lib, realCache()->fileId(), 0)) {
      _exit(CHILD_SLOT_NOT_HOOKED);
    }
  });
}

TEST_F(LibraryPatcherIdentityTest, PatchSkipsCacheWithoutFingerprintOfDifferentFile) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    if (patchWritesFakeCache(lib, realCache()->fileId() + 1, 0)) {
      _exit(CHILD_CORRUPTED);
    }
  });
}

// An unlinked library cannot be stat()ed, so only the image identity is left:
// a stale cache of a different image at the same base is still rejected.
TEST_F(LibraryPatcherIdentityTest, PatchSkipsUnlinkedCacheOfDifferentImage) {
  // musl's dlclose() never unmaps, so there are no stale caches and the
  // patcher does not check identity there.
  if (OS::isMusl()) GTEST_SKIP() << "no identity check on musl";
  runInChild([]() {
    LoadedLib lib = loadUnlinkedLib(true, BY_PATH);
    if (patchWritesFakeCache(lib, realCache()->fileId(), realCache()->imageFingerprint() + 1)) {
      _exit(CHILD_CORRUPTED);
    }
  });
}

struct FingerprintQuery {
  const char* suffix;
  u64 fingerprint;
  const ElfW(Phdr)* phdrs;
  int phnum;
  uintptr_t base;
};

static int fingerprintLoadedObject(struct dl_phdr_info* info, size_t, void* data) {
  FingerprintQuery* query = (FingerprintQuery*)data;
  size_t len = strlen(info->dlpi_name), suffix_len = strlen(query->suffix);
  if (len < suffix_len || strcmp(info->dlpi_name + len - suffix_len, query->suffix) != 0) return 0;
  query->fingerprint = Symbols::imageFingerprint(info->dlpi_phdr, info->dlpi_phnum, info->dlpi_addr);
  query->phdrs = info->dlpi_phdr;
  query->phnum = info->dlpi_phnum;
  query->base = info->dlpi_addr;
  return 1;
}

// Fills query from the loaded object whose name ends in query.suffix.
static void queryLoaded(FingerprintQuery& query) {
  if (dl_iterate_phdr(fingerprintLoadedObject, &query) != 1) _exit(CHILD_LIB_NOT_FOUND);
  if (query.fingerprint == 0) _exit(CHILD_NO_FINGERPRINT);
}

// The path of a test DSO built next to g_lib_path; suffix starts with '/'.
static void testLibPath(char* path, size_t size, const char* suffix) {
  snprintf(path, size, "%s", g_lib_path);
  *strrchr(path, '/') = '\0';
  strncat(path, suffix, size - strlen(path) - 1);
}

// Loads the test DSOs ending in suffix_a and suffix_b, both at once, and
// returns their fingerprints. Skips unless their program headers are
// identical, which is what makes the two hard to tell apart.
static void fingerprintTwins(const char* suffix_a, const char* suffix_b, u64* fp_a, u64* fp_b) {
  FingerprintQuery queries[] = {{suffix_a, 0, nullptr, 0, 0}, {suffix_b, 0, nullptr, 0, 0}};
  for (FingerprintQuery& query : queries) {
    char path[PATH_MAX];
    testLibPath(path, sizeof(path), query.suffix);
    if (dlopen(path, RTLD_NOW) == nullptr) _exit(CHILD_DLOPEN_FAILED);
    queryLoaded(query);
  }
  if (queries[0].phnum != queries[1].phnum
      || memcmp(queries[0].phdrs, queries[1].phdrs, queries[0].phnum * sizeof(ElfW(Phdr))) != 0) {
    _exit(CHILD_SKIP);  // the toolchain laid the two builds out differently
  }
  *fp_a = queries[0].fingerprint;
  *fp_b = queries[1].fingerprint;
}

// Two builds that differ only in their build-id have identical program
// headers; the fingerprint must still tell them apart, through the notes.
TEST_F(LibraryPatcherIdentityTest, FingerprintCoversBuildId) {
  runInChild([]() {
    u64 a, b;
    fingerprintTwins("/libbuildid-a.so", "/libbuildid-b.so", &a, &b);
    if (a == b) _exit(CHILD_SAME_FINGERPRINT);
  });
}

// Two builds without a build-id that differ only in importing write() or
// read(): identical program headers and no notes to tell them apart. The
// fingerprint must still differ, through the import layout.
TEST_F(LibraryPatcherIdentityTest, FingerprintCoversImports) {
  runInChild([]() {
    u64 write_fp, read_fp;
    fingerprintTwins("/libnoid-write.so", "/libnoid-read.so", &write_fp, &read_fp);
    if (write_fp == read_fp) _exit(CHILD_SAME_FINGERPRINT);
  });
}

// The patched DSO is unloaded and replaced, at the same base, by a build
// without a build-id whose program headers are identical but whose GOT slot
// at the saved address holds read() instead of write(). Stopping must not
// restore write() into it.
TEST_F(LibraryPatcherIdentityTest, UnpatchDoesNotWriteIntoReplacementWithSameLayout) {
  runInChild([]() {
    char write_path[PATH_MAX], read_path[PATH_MAX];
    testLibPath(write_path, sizeof(write_path), "/libnoid-write.so");
    testLibPath(read_path, sizeof(read_path), "/libnoid-read.so");
    requireUnloadableEnvironment(write_path);

    void* handle = dlopen(write_path, RTLD_NOW);
    if (handle == nullptr) _exit(CHILD_DLOPEN_FAILED);
    Libraries::instance()->updateSymbols(false);
    CodeCache* old_cache = Libraries::instance()->findLibraryByName("libnoid-write");
    if (old_cache == nullptr) _exit(CHILD_LIB_NOT_FOUND);
    void** slot = old_cache->findImport(im_write);
    if (slot == nullptr) _exit(CHILD_NO_IMPORT);
    FingerprintQuery old_image = {"/libnoid-write.so", 0, nullptr, 0, 0};
    queryLoaded(old_image);
    ElfW(Phdr) old_phdrs[16];
    if (old_image.phnum > 16) _exit(CHILD_SKIP);
    memcpy(old_phdrs, old_image.phdrs, old_image.phnum * sizeof(ElfW(Phdr)));

    LibraryPatcher::patch_socket_functions();
    if (*slot != (void*)NativeSocketSampler::write_hook) _exit(CHILD_SLOT_NOT_HOOKED);
    if (!unload(handle, slot, write_path)) _exit(CHILD_SKIP);  // pinned: no replacement possible

    if (dlopen(read_path, RTLD_NOW) == nullptr) _exit(CHILD_DLOPEN_FAILED);
    FingerprintQuery new_image = {"/libnoid-read.so", 0, nullptr, 0, 0};
    queryLoaded(new_image);
    if (new_image.base != old_image.base || new_image.phnum != old_image.phnum
        || memcmp(new_image.phdrs, old_phdrs, new_image.phnum * sizeof(ElfW(Phdr))) != 0) {
      _exit(CHILD_SKIP);  // not the same layout at the same base
    }
    Libraries::instance()->updateSymbols(false);
    CodeCache* new_cache = Libraries::instance()->findLibraryByName("libnoid-read");
    if (new_cache == nullptr) _exit(CHILD_LIB_NOT_FOUND);
    if (new_cache->peekImport(im_read) != slot) _exit(CHILD_SKIP);  // GOTs laid out differently

    void* before = *slot;
    LibraryPatcher::unpatch_socket_functions();
    if (*slot != before) _exit(CHILD_CORRUPTED);
  });
}

// Set by the stopping thread just before it calls unpatch_socket_functions().
std::atomic<bool> g_stopper_started{false};

static void* stopSocketPatching(void*) {
  g_stopper_started.store(true);
  LibraryPatcher::unpatch_socket_functions();
  return nullptr;
}

// A foreign dl_iterate_phdr() callback, holding dl_load_write_lock, that
// patches as a refresh does: loading a library through the JVM from such a
// callback reaches Profiler::dlopen_hook(), which refreshes synchronously.
// Meanwhile another thread stops socket patching and waits for the same lock.
static int patchInsideForeignWalk(struct dl_phdr_info*, size_t, void* data) {
  pthread_t* stopper = (pthread_t*)data;
  if (pthread_create(stopper, nullptr, stopSocketPatching, nullptr) != 0) _exit(CHILD_THREAD_FAILED);
  while (!g_stopper_started.load()) sched_yield();
  usleep(200 * 1000);  // let the stopper block on dl_load_write_lock
  LibraryPatcher::patch_socket_functions();
  return 1;
}

// Patching from inside a foreign walk must not deadlock with a concurrent stop:
// the stopper must not hold the patch lock while it waits for the loader's lock.
TEST_F(LibraryPatcherLockOrderTest, PatchInsideForeignWalkDoesNotDeadlockWithStop) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    patchAndVerify(SOCKET, lib);
    signal(SIGALRM, [](int) { _exit(CHILD_DEADLOCK); });
    alarm(10);
    pthread_t stopper;
    dl_iterate_phdr(patchInsideForeignWalk, &stopper);
    pthread_join(stopper, nullptr);
    alarm(0);
  });
}

namespace {
void* foreignWrapper(void*) { return nullptr; }
}  // namespace

// Unloads a test DSO that nothing else holds, so the next pass re-checks every
// patched library.
static void bumpLoaderSubs(const char* suffix) {
  char path[PATH_MAX];
  testLibPath(path, sizeof(path), suffix);
  requireUnloadableEnvironment(path);
}

// A pass that leaves a slot unhooked keeps the entry pending, and later passes
// visit it even though no library was loaded or unloaded, including after the
// same value at two passes: that is how a GOT not relocated yet looks.
TEST_F(LibraryPatcherRecheckTest, PendingSlotIsCheckedAgainWithoutLoaderChange) {
  runInChild([]() {
    if (OS::isMusl()) _exit(CHILD_SKIP);  // musl does not report load counts
    LoadedLib lib = loadLib(PTHREAD_CREATE);
    patchAndVerify(PTHREAD_CREATE, lib);
    void* hooked = *lib.slot;

    void* foreign = reinterpret_cast<void*>(&foreignWrapper);
    *lib.slot = foreign;
    bumpLoaderSubs("/libbuildid-a.so");
    PTHREAD_CREATE.patch();
    PTHREAD_CREATE.patch();
    if (*lib.slot != foreign) _exit(CHILD_FOREIGN_TAKEN);

    // The loader's binding arrives. No library was loaded or unloaded since.
    *lib.slot = reinterpret_cast<void*>(&pthread_create);
    PTHREAD_CREATE.patch();
    if (*lib.slot != hooked) _exit(CHILD_NOT_RECHECKED);
  });
}

// Only the pending entry is visited on a pass without a load or unload: a settled
// library is left alone, so a wrapper that stays costs one entry per pass, not a
// re-walk of every patched library.
TEST_F(LibraryPatcherRecheckTest, PendingEntryDoesNotForceRecheckOfOthers) {
  runInChild([]() {
    if (OS::isMusl()) _exit(CHILD_SKIP);  // musl does not report load counts
    LoadedLib lib = loadLib(PTHREAD_CREATE);
    char settled_path[PATH_MAX];
    testLibPath(settled_path, sizeof(settled_path), "/libbuildid-a.so");
    if (dlopen(settled_path, RTLD_NOW) == nullptr) _exit(CHILD_DLOPEN_FAILED);
    Libraries::instance()->updateSymbols(false);
    CodeCache* settled = Libraries::instance()->findLibraryByName("libbuildid-a");
    if (settled == nullptr) _exit(CHILD_LIB_NOT_FOUND);
    void** settled_slot = settled->findImport(im_pthread_create);
    if (settled_slot == nullptr) _exit(CHILD_NO_IMPORT);
    void* settled_orig = *settled_slot;
    patchAndVerify(PTHREAD_CREATE, lib);
    if (*settled_slot == settled_orig) _exit(CHILD_SLOT_NOT_HOOKED);
    void* settled_hooked = *settled_slot;

    void* foreign = reinterpret_cast<void*>(&foreignWrapper);
    *lib.slot = foreign;
    bumpLoaderSubs("/libbuildid-b.so");
    PTHREAD_CREATE.patch();  // re-checks both: one pending, one settled
    if (*lib.slot != foreign) _exit(CHILD_FOREIGN_TAKEN);

    *settled_slot = reinterpret_cast<void*>(&pthread_create);
    PTHREAD_CREATE.patch();  // no load or unload since: only the pending entry
    if (*settled_slot == settled_hooked) _exit(CHILD_RECHECKED_SETTLED);
  });
}

// A full pass clears the pending flag of an entry it does not visit, so the
// entry of an unloaded library is not walked on every later pass.
TEST_F(LibraryPatcherRecheckTest, FullPassClearsPendingOfUnloadedLibrary) {
  runInChild([]() {
    if (OS::isMusl()) _exit(CHILD_SKIP);  // musl never unmaps
    LoadedLib lib = loadLib(PTHREAD_CREATE);
    patchAndVerify(PTHREAD_CREATE, lib);
    CodeCache* cc = Libraries::instance()->findLibraryByName("libpatchtarget");
    if (cc == nullptr) _exit(CHILD_LIB_NOT_FOUND);
    *lib.slot = reinterpret_cast<void*>(&foreignWrapper);
    bumpLoaderSubs("/libbuildid-a.so");
    PTHREAD_CREATE.patch();
    if (LibraryPatcherTestAccessor::entryPending(cc) != 1) _exit(CHILD_NOT_RECHECKED);

    if (!unload(lib.handle, lib.slot)) _exit(CHILD_SKIP);
    PTHREAD_CREATE.patch();  // the unload makes this a full pass
    if (LibraryPatcherTestAccessor::entryPending(cc) != 0) _exit(CHILD_STILL_PENDING);
  });
}

// Binds this binary's pthread_create PLT slot. It stands in for the profiler's
// own: the patcher is linked into the gtest executable.
static void bindOwnPltSlot() {
  pthread_t thread;
  if (pthread_create(&thread, nullptr, foreignWrapper, nullptr) != 0) _exit(CHILD_THREAD_FAILED);
  pthread_join(thread, nullptr);
}

// A pass takes the profiler's bound PLT slot before its visits: a library bound
// to that value, and to neither expected binding, is hooked in the same pass.
TEST_F(LibraryPatcherRecheckTest, PassCapturesPltBindingBeforeVisits) {
  runInChild([]() {
    LoadedLib lib = loadLib(PTHREAD_CREATE);
    bindOwnPltSlot();
    LibraryPatcher::initialize_persistent();
    LibraryPatcherTestAccessor::setLoaderPthreadCreate(reinterpret_cast<void*>(&foreignWrapper));
    LibraryPatcherTestAccessor::setNextPthreadCreate(nullptr);
    LibraryPatcherTestAccessor::setAwaitingPltBinding(true);
    LibraryPatcher::patch_libraries();
    if (LibraryPatcherTestAccessor::nextPthreadCreate() != lib.orig) _exit(CHILD_NOT_CAPTURED);
    if (*lib.slot == lib.orig) _exit(CHILD_SLOT_NOT_HOOKED);
  });
}

// The extra pass of start() runs only while the capture is awaited.
TEST_F(LibraryPatcherRecheckTest, ExtraPassRunsOnlyWhileCaptureIsAwaited) {
  runInChild([]() {
    LoadedLib lib = loadLib(PTHREAD_CREATE);
    LibraryPatcher::initialize_persistent();
    LibraryPatcherTestAccessor::setAwaitingPltBinding(false);
    LibraryPatcher::patch_libraries_awaiting_plt_binding();
    if (*lib.slot != lib.orig) _exit(CHILD_PATCHED_UNAWAITED);
    LibraryPatcherTestAccessor::setAwaitingPltBinding(true);
    LibraryPatcher::patch_libraries_awaiting_plt_binding();
    if (*lib.slot == lib.orig) _exit(CHILD_SLOT_NOT_HOOKED);
  });
}

namespace {

struct CopyIoState {
  int read_eintr = 0;
  size_t max_read = 0;
  int write_eintr = 0;
  int read_error = 0;
  int write_error = 0;
  int write_error_after_calls = 0;
  size_t max_write = 0;
  bool zero_write = false;
  int read_calls = 0;
  int write_calls = 0;
  int read_fd = -1;
  int write_fd = -1;
};

CopyIoState g_copy_io;

ssize_t injectedRead(int fd, void* buffer, size_t size) {
  ++g_copy_io.read_calls;
  g_copy_io.read_fd = fd;
  if (g_copy_io.read_eintr > 0) {
    --g_copy_io.read_eintr;
    errno = EINTR;
    return -1;
  }
  if (g_copy_io.read_error != 0) {
    errno = g_copy_io.read_error;
    return -1;
  }
  if (g_copy_io.max_read > 0 && size > g_copy_io.max_read) size = g_copy_io.max_read;
  return ::read(fd, buffer, size);
}

ssize_t injectedWrite(int fd, const void* buffer, size_t size) {
  ++g_copy_io.write_calls;
  g_copy_io.write_fd = fd;
  if (g_copy_io.write_eintr > 0) {
    --g_copy_io.write_eintr;
    errno = EINTR;
    return -1;
  }
  if (g_copy_io.write_error != 0
      && g_copy_io.write_calls > g_copy_io.write_error_after_calls) {
    errno = g_copy_io.write_error;
    return -1;
  }
  if (g_copy_io.zero_write) return 0;
  if (g_copy_io.max_write > 0 && size > g_copy_io.max_write) size = g_copy_io.max_write;
  return ::write(fd, buffer, size);
}

struct RemoveTempFile {
  explicit RemoveTempFile(char* file_path) : path(file_path) {}
  RemoveTempFile(const RemoveTempFile&) = delete;
  RemoveTempFile& operator=(const RemoveTempFile&) = delete;

  char* path;
  ~RemoveTempFile() {
    if (path[0] != '\0') unlink(path);
  }
};

bool createTempSource(const std::vector<char>& contents, char* path, size_t size) {
  if (snprintf(path, size, "/tmp/temp-file-copy-XXXXXX") < 0) return false;
  FdOwner fd(mkstemp(path));
  if (fd.get() < 0) return false;
  size_t offset = 0;
  while (offset < contents.size()) {
    ssize_t written = ::write(fd.get(), contents.data() + offset, contents.size() - offset);
    if (written < 0 && errno == EINTR) continue;
    if (written <= 0) return false;
    offset += static_cast<size_t>(written);
  }
  return true;
}

bool readTempContents(const char* path, std::vector<char>& contents) {
  FdOwner fd(open(path, O_RDONLY));
  if (fd.get() < 0) return false;
  char buffer[8192];
  while (true) {
    ssize_t n = ::read(fd.get(), buffer, sizeof(buffer));
    if (n < 0 && errno == EINTR) continue;
    if (n < 0) return false;
    if (n == 0) return true;
    contents.insert(contents.end(), buffer, buffer + static_cast<size_t>(n));
  }
}

}  // namespace

TEST(TempFileCopyTest, RetriesInterruptedIoAndCompletesPartialWrites) {
  std::vector<char> expected = {'c', 'o', 'p', 'y', '\0', 't', 'e', 's', 't'};
  char source[PATH_MAX] = {};
  RemoveTempFile remove_source{source};
  ASSERT_TRUE(createTempSource(expected, source, sizeof(source)));

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  g_copy_io = {};
  g_copy_io.read_eintr = 1;
  g_copy_io.write_eintr = 1;
  g_copy_io.max_write = 3;
  int copy_result = copyToTempFileWithIO(source, "/tmp", "temp-file-copy-test", output,
                                         sizeof(output), injectedRead, injectedWrite);
  errno = 0;
  int read_fd_status = fcntl(g_copy_io.read_fd, F_GETFD);
  int read_fd_error = errno;
  errno = 0;
  int write_fd_status = fcntl(g_copy_io.write_fd, F_GETFD);
  int write_fd_error = errno;

  EXPECT_EQ(copy_result, 0);
  EXPECT_EQ(g_copy_io.read_calls, 3);  // interrupted read, data, then EOF
  EXPECT_EQ(g_copy_io.write_calls, 4);  // interrupted write and three short writes
  EXPECT_EQ(read_fd_status, -1);
  EXPECT_EQ(read_fd_error, EBADF);
  EXPECT_EQ(write_fd_status, -1);
  EXPECT_EQ(write_fd_error, EBADF);

  std::vector<char> actual;
  ASSERT_TRUE(readTempContents(output, actual));
  EXPECT_EQ(actual, expected);
}

TEST(TempFileCopyTest, CopiesMultipleBuffersAndTail) {
  std::vector<char> expected(3 * 8192 + 37);
  for (size_t i = 0; i < expected.size(); ++i) expected[i] = static_cast<char>((i * 31) & 0xff);
  char source[PATH_MAX] = {};
  RemoveTempFile remove_source{source};
  ASSERT_TRUE(createTempSource(expected, source, sizeof(source)));

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  ASSERT_EQ(copyToTempFile(source, "/tmp", "temp-file-copy-test", output, sizeof(output)), 0);

  std::vector<char> actual;
  ASSERT_TRUE(readTempContents(output, actual));
  EXPECT_EQ(actual, expected);
}

TEST(TempFileCopyTest, ContinuesAfterPositiveShortReads) {
  std::vector<char> expected(2 * 8192 + 37);
  for (size_t i = 0; i < expected.size(); ++i) expected[i] = static_cast<char>((i * 17) & 0xff);
  char source[PATH_MAX] = {};
  RemoveTempFile remove_source{source};
  ASSERT_TRUE(createTempSource(expected, source, sizeof(source)));

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  g_copy_io = {};
  g_copy_io.max_read = 4096;
  ASSERT_EQ(copyToTempFileWithIO(source, "/tmp", "temp-file-copy-test", output,
                                 sizeof(output), injectedRead, injectedWrite), 0);
  EXPECT_GT(g_copy_io.read_calls, 2);

  std::vector<char> actual;
  ASSERT_TRUE(readTempContents(output, actual));
  EXPECT_EQ(actual, expected);
}

TEST(TempFileCopyTest, ZeroWriteReturnsEioAndRemovesPartialOutput) {
  std::vector<char> expected = {'x'};
  char source[PATH_MAX] = {};
  RemoveTempFile remove_source{source};
  ASSERT_TRUE(createTempSource(expected, source, sizeof(source)));

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  g_copy_io = {};
  g_copy_io.zero_write = true;
  EXPECT_EQ(copyToTempFileWithIO(source, "/tmp", "temp-file-copy-test", output,
                                 sizeof(output), injectedRead, injectedWrite), EIO);
  errno = 0;
  int output_status = access(output, F_OK);
  int output_error = errno;
  EXPECT_EQ(output_status, -1);
  EXPECT_EQ(output_error, ENOENT);
}

TEST(TempFileCopyTest, SourceOpenErrorRemovesCreatedOutput) {
  char source[] = "/tmp/temp-file-copy-missing-XXXXXX";
  int source_fd = mkstemp(source);
  ASSERT_GE(source_fd, 0);
  close(source_fd);
  ASSERT_EQ(unlink(source), 0);

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  EXPECT_EQ(copyToTempFile(source, "/tmp", "temp-file-copy-test", output, sizeof(output)), ENOENT);
  errno = 0;
  int output_status = access(output, F_OK);
  int output_error = errno;
  EXPECT_EQ(output_status, -1);
  EXPECT_EQ(output_error, ENOENT);
}

TEST(TempFileCopyTest, ReadErrorReturnsErrnoAndRemovesOutput) {
  std::vector<char> expected = {'x'};
  char source[PATH_MAX] = {};
  RemoveTempFile remove_source{source};
  ASSERT_TRUE(createTempSource(expected, source, sizeof(source)));

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  g_copy_io = {};
  g_copy_io.read_error = EACCES;
  EXPECT_EQ(copyToTempFileWithIO(source, "/tmp", "temp-file-copy-test", output,
                                 sizeof(output), injectedRead, injectedWrite), EACCES);
  errno = 0;
  int output_status = access(output, F_OK);
  int output_error = errno;
  EXPECT_EQ(output_status, -1);
  EXPECT_EQ(output_error, ENOENT);
}

TEST(TempFileCopyTest, WriteErrorReturnsErrnoAndRemovesPartialOutput) {
  std::vector<char> expected = {'x', 'y'};
  char source[PATH_MAX] = {};
  RemoveTempFile remove_source{source};
  ASSERT_TRUE(createTempSource(expected, source, sizeof(source)));

  char output[PATH_MAX] = {};
  RemoveTempFile remove_output{output};
  g_copy_io = {};
  g_copy_io.max_write = 1;
  g_copy_io.write_error = EACCES;
  g_copy_io.write_error_after_calls = 1;
  EXPECT_EQ(copyToTempFileWithIO(source, "/tmp", "temp-file-copy-test", output,
                                 sizeof(output), injectedRead, injectedWrite), EACCES);
  errno = 0;
  int output_status = access(output, F_OK);
  int output_error = errno;
  EXPECT_EQ(output_status, -1);
  EXPECT_EQ(output_error, ENOENT);
}

#endif // __linux__
