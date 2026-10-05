/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Regression tests for PROF-16135: LibraryPatcher keeps raw GOT-slot addresses
// of patched DSOs (and CodeCacheArray never drops a CodeCache), but nothing
// pins those DSOs. Once a patched DSO is dlclose()d and unmapped, restoring the
// hooks on stop, or re-installing them on the next start, must not write
// through the stale address: that is a SIGSEGV if the range is unmapped and
// silent corruption if something else reused it.

#ifdef __linux__

#include <gtest/gtest.h>

#include "codeCache.h"
#include "libraries.h"
#include "libraryPatcher.h"
#include "nativeSocketSampler.h"

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <link.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

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
};

const unsigned char SENTINEL = 0xA5;

char g_lib_path[PATH_MAX];

// The LibraryPatcher patching under test.
struct PatchKind {
  const char* name;
  ImportId import;  // the test DSO's import that gets patched
  void (*patch)();
  void (*unpatch)();
};

const PatchKind SOCKET = {
  "socket", im_write,
  []() { LibraryPatcher::patch_socket_functions(); },
  []() { LibraryPatcher::unpatch_socket_functions(); },
};

const PatchKind PTHREAD_CREATE = {
  "pthread_create", im_pthread_create,
  []() {
    LibraryPatcher::initialize();
    LibraryPatcher::patch_libraries();
  },
  []() { LibraryPatcher::unpatch_libraries(); },
};

struct LoadedLib {
  void* handle;
  void** slot;  // the DSO's GOT slot for the patched import
  void* orig;   // the slot's value before patching
};

// Skips unless dlclose() really unmaps the test DSO when nothing else holds
// it (it never does on musl). Runs before the profiler sees the DSO, so a fix
// that pins patched DSOs cannot turn this into a skip.
void requireUnloadableEnvironment() {
  void* handle = dlopen(g_lib_path, RTLD_NOW);
  if (handle == nullptr) _exit(CHILD_DLOPEN_FAILED);
  dlclose(handle);
  if (dlopen(g_lib_path, RTLD_NOLOAD | RTLD_LAZY) != nullptr) _exit(CHILD_SKIP);
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
bool unload(void* handle, void** slot) {
  dlclose(handle);
  if (dlopen(g_lib_path, RTLD_NOLOAD | RTLD_LAZY) != nullptr) return false;
  // msync() fails with ENOMEM iff the range is not mapped.
  if (msync((void*)pageOf(slot), sysconf(_SC_PAGESIZE), MS_ASYNC) == 0 || errno != ENOMEM) {
    _exit(CHILD_SKIP);  // already reused by an unrelated mapping
  }
  return true;
}

// For a DSO that stayed loaded: unpatching must restore the original binding.
void unpatchAndVerifyRestored(const PatchKind& kind, const LoadedLib& lib) {
  kind.unpatch();
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

// Copies the test DSO to a fresh temporary file and returns its path in
// path_out. Exits the child on failure.
static void copyLibToTemp(char* path_out, size_t size) {
  snprintf(path_out, size, "/tmp/libpatchtarget-XXXXXX.so");
  int out = mkstemps(path_out, 3);
  int in = open(g_lib_path, O_RDONLY);
  if (out < 0 || in < 0) _exit(CHILD_DLOPEN_FAILED);
  char buf[8192];
  ssize_t n;
  while ((n = read(in, buf, sizeof(buf))) > 0) {
    if (write(out, buf, n) != n) _exit(CHILD_DLOPEN_FAILED);
  }
  close(in);
  close(out);
}

// Loads a temporary copy of the test DSO and unlinks the file, before or
// after Libraries parses it, like JNI loaders that extract to a temporary
// file. With relative, the copy is loaded as "./<name>" from its directory.
static LoadedLib loadUnlinkedLib(bool unlink_before_parse, bool relative) {
  char path[64];
  copyLibToTemp(path, sizeof(path));
  void* handle;
  if (relative) {
    char name[64];
    snprintf(name, sizeof(name), "./%s", strrchr(path, '/') + 1);
    if (chdir("/tmp") != 0) _exit(CHILD_DLOPEN_FAILED);
    handle = dlopen(name, RTLD_NOW);
  } else {
    handle = dlopen(path, RTLD_NOW);
  }
  if (handle == nullptr) _exit(CHILD_DLOPEN_FAILED);
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
// file identity check cannot stat() the file any more and has to go by path.
static void patchAndRestoreUnlinkedLibrary(bool unlink_before_parse, bool relative) {
  LoadedLib lib = loadUnlinkedLib(unlink_before_parse, relative);
  patchAndVerify(SOCKET, lib);
  unpatchAndVerifyRestored(SOCKET, lib);
}

TEST_F(LibraryPatcherIdentityTest, PatchesLibraryUnlinkedBeforeParsing) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(true, false); });
}

TEST_F(LibraryPatcherIdentityTest, PatchesLibraryUnlinkedAfterParsing) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(false, false); });
}

// /proc/self/maps records the absolute path, the loader keeps "./<name>".
// Unlinked after parsing: before it, Symbols::parseLibraries cannot verify a
// relatively loaded library (UnloadProtection's dlopen by the absolute path
// fails) and never reads its imports, so there would be nothing to patch.
TEST_F(LibraryPatcherIdentityTest, PatchesLibraryLoadedByRelativePathAndUnlinked) {
  runInChild([]() { patchAndRestoreUnlinkedLibrary(false, true); });
}

// Registers a CodeCache that claims the test DSO's image base, with the given
// file identity and a write() import pointing at *slot.
static void addCacheAtLibraryBase(CodeCache* real, const char* name, u64 file_id,
                                  u64 phdr_hash, void** slot) {
  CodeCache* cc = new CodeCache(name, -1, real->minAddress(), real->maxAddress(),
                                real->imageBase(), /*imports_patchable=*/true);
  cc->setFileId(file_id);
  cc->setProgramHeadersHash(phdr_hash);
  cc->addImport(slot, "write");
  Libraries::instance()->addLibraryForTest(cc);
}

// A stale CodeCache whose library was replaced by a different one at the
// same base must not be patched: the slot address now belongs to the new
// library. Base and file identity must both match.
TEST_F(LibraryPatcherIdentityTest, PatchSkipsCacheOfDifferentFileAtSameBase) {
  runInChild([]() {
    LoadedLib lib = loadLib(SOCKET);
    CodeCache* real = Libraries::instance()->findLibraryByName("libpatchtarget");
    static void* word = (void*)&SENTINEL;
    addCacheAtLibraryBase(real, "fake-at-same-base", real->fileId() + 1, real->programHeadersHash(), &word);
    LibraryPatcher::patch_socket_functions();
    if (*lib.slot != (void*)NativeSocketSampler::write_hook) _exit(CHILD_SLOT_NOT_HOOKED);
    if (word != (void*)&SENTINEL) _exit(CHILD_CORRUPTED);
  });
}

// Control for the test above: the same setup with a matching file identity
// is patched, so the skip there is due to the identity check.
TEST_F(LibraryPatcherIdentityTest, PatchAcceptsCacheOfSameFileAtSameBase) {
  runInChild([]() {
    loadLib(SOCKET);
    CodeCache* real = Libraries::instance()->findLibraryByName("libpatchtarget");
    static void* word = (void*)&SENTINEL;
    addCacheAtLibraryBase(real, "fake-at-same-base", real->fileId(), real->programHeadersHash(), &word);
    LibraryPatcher::patch_socket_functions();
    if (word != (void*)NativeSocketSampler::write_hook) _exit(CHILD_SLOT_NOT_HOOKED);
  });
}

// A stale cache of an unlinked library whose path is now used by a different
// unlinked library at the same base: the path matches, the layout does not.
TEST_F(LibraryPatcherIdentityTest, PatchSkipsUnlinkedCacheWithDifferentLayout) {
  runInChild([]() {
    LoadedLib lib = loadUnlinkedLib(true, false);
    CodeCache* real = Libraries::instance()->findLibraryByName("libpatchtarget");
    static void* word = (void*)&SENTINEL;
    addCacheAtLibraryBase(real, real->name(), real->fileId(), real->programHeadersHash() + 1, &word);
    LibraryPatcher::patch_socket_functions();
    if (*lib.slot != (void*)NativeSocketSampler::write_hook) _exit(CHILD_SLOT_NOT_HOOKED);
    if (word != (void*)&SENTINEL) _exit(CHILD_CORRUPTED);
  });
}

// Control for the test above: the same setup with a matching layout is patched.
TEST_F(LibraryPatcherIdentityTest, PatchAcceptsUnlinkedCacheWithSameLayout) {
  runInChild([]() {
    loadUnlinkedLib(true, false);
    CodeCache* real = Libraries::instance()->findLibraryByName("libpatchtarget");
    static void* word = (void*)&SENTINEL;
    addCacheAtLibraryBase(real, real->name(), real->fileId(), real->programHeadersHash(), &word);
    LibraryPatcher::patch_socket_functions();
    if (word != (void*)NativeSocketSampler::write_hook) _exit(CHILD_SLOT_NOT_HOOKED);
  });
}

#endif // __linux__
