/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Linux-only forked gtests for the fresh-path admission state machine: the
// child process plays the other profiler by writing fixture forwarding hooks
// into the own GOT slots with its own mprotect (never through CodeCache
// writers), then drives the production MallocHooker::initialize() /
// MallocTracer::start() and observes the outcome through the UNIT_TEST-only
// MallocHookerTestAccessor seams. Zero tests on macOS: the forked own-GOT
// scenarios are Linux-only (INV-25 isolation; the writes are process-global).
// Sanitizer builds may define malloc in the executable itself, so the own
// image has no allocation import there: those scenarios skip with that
// reason, in sanitizer configurations only.

#ifdef __linux__

#include <gtest/gtest.h>

#include "codeCache.h"
#include "libraries.h"
#include "mallocAdmission.h"
#include "mallocTracer.h"
#include "os.h"

#include <dlfcn.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#if defined(__SANITIZE_ADDRESS__) || (defined(__has_feature) && __has_feature(address_sanitizer))
#define ADMISSION_UT_SANITIZER 1
#endif

extern "C" void* malloc_hook(size_t);

namespace {

// Child exit codes. Anything not listed here is unexpected.
enum ChildExit {
  CHILD_OK = 0,
  CHILD_FAIL = 20,           // a scenario assertion failed inside the child
  CHILD_SKIP = 77,           // environment cannot exercise the scenario
  CHILD_NO_OWN_LIB = 10,     // the own CodeCache was not found
  CHILD_NO_IMPORT = 11,      // the own image has no slot for the operation
  CHILD_MPROTECT = 12,       // the GOT page could not be made writable
  CHILD_DLOPEN_FAILED = 13,
  CHILD_START_UNEXPECTED = 14,  // start() returned an error other than expected
  CHILD_NO_FIXTURE_LIB = 15,    // the fixture CodeCache was not found
  CHILD_ORIG_DIRTY = 16,        // a saved pointer was written on rejection
  CHILD_STATE_DIRTY = 17,       // initialized/patched/running/patchable written
  CHILD_SLOT_DIRTY = 18,        // a fixture GOT slot changed on rejection
};

char g_fixture_path[PATH_MAX];

const char* const DDPROF_LITERAL =
    "Native-memory profiling was not started: an allocation target points to a ddprof hook. "
    "Enable only one native-memory allocation profiler for this process.";

// Resolves the ddprof-marker fixture relative to the test binary. A missing
// fixture is a build problem: fail, never skip.
void resolveFixturePath() {
  char exe[PATH_MAX - 128];
  ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
  if (len <= 0) _exit(CHILD_FAIL);
  exe[len] = '\0';
  *strrchr(exe, '/') = '\0';
  snprintf(g_fixture_path, sizeof(g_fixture_path),
           "%s/../../../test/resources/native-libs/ddprof-admission/libddprof-fixture-gnu.so", exe);
  if (access(g_fixture_path, R_OK) != 0) _exit(CHILD_FAIL);
}

// The own CodeCache: this test binary statically contains the profiler, so
// the executable is the profiler's own library.
CodeCache* findOwnLibrary() {
  Libraries::instance()->updateSymbols(false);
  return Libraries::instance()->findLibraryByAddress((void*)MallocTracer::recordMalloc);
}

// Writes value into the own image's PRIMARY GOT slot for id, through the
// loader's mapping and an explicit mprotect — never through a CodeCache
// writer. Returns the previous slot value.
void* writeOwnSlot(CodeCache* own, ImportId id, void* value, int* exit_code) {
  void** slot = own->peekImport(id, PRIMARY);
  if (slot == NULL) {
    *exit_code = CHILD_NO_IMPORT;
    return NULL;
  }
  long page_size = sysconf(_SC_PAGESIZE);
  uintptr_t page = (uintptr_t)slot & ~((uintptr_t)page_size - 1);
  if (mprotect((void*)page, page_size, PROT_READ | PROT_WRITE) != 0) {
    *exit_code = CHILD_MPROTECT;
    return NULL;
  }
  void* old = *slot;
  *slot = value;
  return old;
}

// Loads the fixture and returns the address of one of its exported
// forwarding hooks; the hook lives inside the fixture image, so a slot
// holding it makes the fixture the owning image.
void* loadFixtureHook(const char* symbol) {
  void* handle = dlopen(g_fixture_path, RTLD_NOW | RTLD_LOCAL);
  if (handle == NULL) _exit(CHILD_DLOPEN_FAILED);
  void* sym = dlsym(handle, symbol);
  if (sym == NULL) _exit(CHILD_FAIL);
  return sym;
}

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
    FAIL() << "child crashed with signal " << WTERMSIG(status);
  }
  ASSERT_TRUE(WIFEXITED(status));
  int code = WEXITSTATUS(status);
  if (code == CHILD_SKIP) {
    GTEST_SKIP() << "own image has no allocation import in this sanitizer configuration";
  }
  ASSERT_EQ(code, CHILD_OK) << "admission scenario failed in the child, exit code " << code;
}

} // namespace

// Each of the five operations' PRIMARY slot of the real own image holding a
// fixture forwarding hook rejects the fresh path with the exact DDPROF
// literal (AC-4 forked part). The slot value is chosen so
// resolveMallocSymbols() (which runs before admission) survives: every
// operation's slot is rewritten to a fixture hook whose call shape keeps the
// probes allocation-safe.
TEST(MallocHookerAdmissionTest, EveryOperationPrimarySlotRejectsFresh) {
  resolveFixturePath();
  static const ImportId OPS[5] = {im_malloc, im_calloc, im_realloc, im_posix_memalign, im_aligned_alloc};
  for (int op = 0; op < 5; op++) {
    runInChild([op]() {
      CodeCache* own = findOwnLibrary();
      if (own == NULL) _exit(CHILD_NO_OWN_LIB);
      MallocHookerTestAccessor::setInitialized(false);

      // calloc/realloc/posix_memalign get a hook whose signature keeps the
      // resolve probes safe (the probes call each operation once).
      const char* hook = (op == 0 || op == 1) ? "fixture_malloc_hook" : "fixture_aligned_alloc_hook";
      void* fixture = loadFixtureHook(hook);
      int exit_code = CHILD_OK;
      writeOwnSlot(own, OPS[op], fixture, &exit_code);
      if (exit_code != CHILD_OK) _exit(exit_code);

      Error e = MallocHooker::initialize();
      if (!e) _exit(CHILD_START_UNEXPECTED);
      if (strcmp(e.message(), DDPROF_LITERAL) != 0) _exit(CHILD_FAIL);
      _exit(CHILD_OK);
    });
  }
}

// A fresh compatibility rejection writes nothing (AC-6): no saved pointer,
// no initialization, no patching, no running flag, no writable-import flag,
// and the fixture's own GOT slots are unchanged (the nested probe never ran).
TEST(MallocHookerAdmissionTest, FreshRejectionWritesNothing) {
  resolveFixturePath();
  runInChild([]() {
    CodeCache* own = findOwnLibrary();
    if (own == NULL) _exit(CHILD_NO_OWN_LIB);
    MallocHookerTestAccessor::setInitialized(false);

    void* fixture_handle = dlopen(g_fixture_path, RTLD_NOW | RTLD_LOCAL);
    if (fixture_handle == NULL) _exit(CHILD_DLOPEN_FAILED);
    void* fixture_malloc_hook = dlsym(fixture_handle, "fixture_malloc_hook");
    void* fixture_aligned_alloc_hook = dlsym(fixture_handle, "fixture_aligned_alloc_hook");
    if (fixture_malloc_hook == NULL || fixture_aligned_alloc_hook == NULL) _exit(CHILD_FAIL);
    // The fixture was dlopen'ed after the own scan: refresh before lookup.
    Libraries::instance()->updateSymbols(false);
    CodeCache* fixture_lib = Libraries::instance()->findLibraryByAddress(fixture_malloc_hook);
    if (fixture_lib == NULL) _exit(CHILD_NO_FIXTURE_LIB);
    void** fixture_malloc_slot = fixture_lib->peekImport(im_malloc, PRIMARY);
    void** fixture_aligned_slot = fixture_lib->peekImport(im_aligned_alloc, PRIMARY);

    // Force the fixture's lazily-bound allocation slots to bind before the
    // snapshot, so the later resolve probes inside initialize() cannot
    // change them (resolveMallocSymbols()-equivalent binding).
    ((void*(*)(size_t))fixture_malloc_hook)(1);
    ((void*(*)(size_t, size_t))fixture_aligned_alloc_hook)(sizeof(void*), sizeof(void*));

    void* malloc_before = fixture_malloc_slot != NULL ? *fixture_malloc_slot : NULL;
    void* aligned_before = fixture_aligned_slot != NULL ? *fixture_aligned_slot : NULL;

    int exit_code = CHILD_OK;
    writeOwnSlot(own, im_malloc, fixture_malloc_hook, &exit_code);
    if (exit_code != CHILD_OK) _exit(exit_code);

    Arguments args;
    MallocTracer tracer;
    Error e = tracer.start(args);
    if (!e) _exit(CHILD_START_UNEXPECTED);
    if (strcmp(e.message(), DDPROF_LITERAL) != 0) _exit(CHILD_FAIL);

    // Nothing was written: no commit, no cached initialization, no patch
    // cursor, no running flag, no writable-import flag.
    if (MallocHookerTestAccessor::origMalloc() != NULL) _exit(CHILD_ORIG_DIRTY);
    if (MallocHookerTestAccessor::origCalloc() != NULL) _exit(CHILD_ORIG_DIRTY);
    if (MallocHookerTestAccessor::origRealloc() != NULL) _exit(CHILD_ORIG_DIRTY);
    if (MallocHookerTestAccessor::origPosixMemalign() != NULL) _exit(CHILD_ORIG_DIRTY);
    if (MallocHookerTestAccessor::origAlignedAlloc() != NULL) _exit(CHILD_ORIG_DIRTY);
    if (MallocHookerTestAccessor::initialized()) _exit(CHILD_STATE_DIRTY);
    if (MallocHookerTestAccessor::patchedLibs() != 0) _exit(CHILD_STATE_DIRTY);
    if (MallocTracer::running()) _exit(CHILD_STATE_DIRTY);
    if (own->importsPatchableForTest()) _exit(CHILD_STATE_DIRTY);

    // The fixture's allocation slots were not patched (no nested probe).
    void* malloc_after = fixture_malloc_slot != NULL ? *fixture_malloc_slot : NULL;
    void* aligned_after = fixture_aligned_slot != NULL ? *fixture_aligned_slot : NULL;
    if (malloc_after != malloc_before || aligned_after != aligned_before) _exit(CHILD_SLOT_DIRTY);
    _exit(CHILD_OK);
  });
}

// A saved ddprof forwarding target cannot hide behind current Java hooks
// (AC-7): the cached path follows the rewritten slot to the saved fixture
// hook and rejects with the DDPROF literal.
TEST(MallocHookerAdmissionTest, SavedFixtureHookBehindJavaHooksRejects) {
  resolveFixturePath();
  runInChild([]() {
    CodeCache* own = findOwnLibrary();
    if (own == NULL) _exit(CHILD_NO_OWN_LIB);
    MallocHookerTestAccessor::setInitialized(false);

    void* fixture = loadFixtureHook("fixture_malloc_hook");
    int exit_code = CHILD_OK;
    // Own slot holds the Java (profiler) hook, as after an earlier session.
    writeOwnSlot(own, im_malloc, (void*)malloc_hook, &exit_code);
    if (exit_code != CHILD_OK) _exit(exit_code);
    // The saved forwarding state points at the fixture hook, as an earlier
    // unguarded library would have saved it.
    MallocHookerTestAccessor::seedOrigMalloc(fixture);
    MallocHookerTestAccessor::setInitialized(true);

    Error e = MallocHooker::initialize();
    if (!e) _exit(CHILD_START_UNEXPECTED);
    if (strcmp(e.message(), DDPROF_LITERAL) != 0) _exit(CHILD_FAIL);
    _exit(CHILD_OK);
  });
}

// A clean saved allocator cannot hide a later ddprof hook in the current
// import (AC-7): the fixture hook in the own slot rejects on the cached path
// and the saved pointers stay bit-identical.
TEST(MallocHookerAdmissionTest, SavedAllocatorWithFixtureHookInSlotRejects) {
  resolveFixturePath();
  runInChild([]() {
    CodeCache* own = findOwnLibrary();
    if (own == NULL) _exit(CHILD_NO_OWN_LIB);
    MallocHookerTestAccessor::setInitialized(false);

    void* fixture = loadFixtureHook("fixture_malloc_hook");
    int exit_code = CHILD_OK;
    void* allocator = writeOwnSlot(own, im_malloc, fixture, &exit_code);
    if (exit_code != CHILD_OK) _exit(exit_code);
    if (allocator == NULL || allocator == fixture) _exit(CHILD_FAIL);
    // The saved state holds the clean allocator the slot used to forward to.
    MallocHookerTestAccessor::seedOrigMalloc(allocator);
    MallocHookerTestAccessor::seedOrigCalloc(allocator);
    MallocHookerTestAccessor::setInitialized(true);

    Error e = MallocHooker::initialize();
    if (!e) _exit(CHILD_START_UNEXPECTED);
    if (strcmp(e.message(), DDPROF_LITERAL) != 0) _exit(CHILD_FAIL);
    // The saved pointers were never modified for the comparison.
    if (MallocHookerTestAccessor::origMalloc() != allocator) _exit(CHILD_FAIL);
    if (MallocHookerTestAccessor::origCalloc() != allocator) _exit(CHILD_FAIL);
    _exit(CHILD_OK);
  });
}

#endif // __linux__
