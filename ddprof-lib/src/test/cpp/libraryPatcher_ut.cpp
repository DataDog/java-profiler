/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#if defined(__linux__)

#include "codeCache.h"
#include "libraryPatcher.h"

#include <dlfcn.h>
#include <pthread.h>
#include <string.h>

// LibraryPatcherTestAccessor — friend of LibraryPatcher, exposes the internals
// the self-identification tests need.
class LibraryPatcherTestAccessor {
public:
  static const void* selfAnchor() { return LibraryPatcher::self_anchor(); }

  static bool isProfilerLibrary(CodeCache* lib) {
    return LibraryPatcher::is_profiler_library(lib);
  }

  static void patchLibraryUnlocked(CodeCache* lib) {
    LibraryPatcher::patch_library_unlocked(lib);
  }

  static int patchedCount() { return LibraryPatcher::_pthread_create.size; }
  static void setPatchedCount(int count) { LibraryPatcher::_pthread_create.size = count; }

  // Whether the entry's last visit found its library mapped and settled, or -1
  // if the library has no entry.
  static int entryMapped(CodeCache* lib) {
    for (int index = 0; index < LibraryPatcher::_pthread_create.size; index++) {
      if (LibraryPatcher::_pthread_create.entries[index].lib == lib) {
        return LibraryPatcher::_pthread_create.entries[index].mapped;
      }
    }
    return -1;
  }

  static bool declined() { return LibraryPatcher::_pthread_create.declined; }

  // Stands in for a preloaded interposer: the value the loader resolves.
  static void setLoaderPthreadCreate(void* func) { LibraryPatcher::_loader_pthread_create = func; }

  // Drops the patch table without writing the saved originals back, unlike
  // unpatch_recording_hooks(). Tests patch GOT slots that live in the test body's
  // frame, so by the time a fixture could restore them the addresses are dead;
  // forgetting the entries is what keeps one test from reaching into the next.
  static void forgetPatchTable() {
    memset(&LibraryPatcher::_pthread_create, 0, sizeof(LibraryPatcher::_pthread_create));
    LibraryPatcher::_loader_pthread_create = reinterpret_cast<void*>(&pthread_create);
  }
};

namespace {

// Stands in for the profiler's own library file after dd-trace-java's
// LibraryLoader extracts it and unlinks it: the mapping is still live, but the
// path no longer resolves, so realpath() returns nullptr.
const char* const kUnlinkedPath =
    "/tmp/ddprof_bits/pid_1/scratch/libjavaProfiler-dd-tmp-unlinked.so";

// An address range that cannot overlap any real mapping of this binary.
const void* const kForeignMin = (const void*)0x1000;
const void* const kForeignMax = (const void*)0x2000;

// Stands in for the real pthread_create that a library's GOT slot holds before
// the profiler patches it.
void* fake_original_pthread_create(void* arg) { return arg; }

// What a freshly bound GOT slot holds: the loader's pthread_create. A value that
// is neither this nor inside the library is another interposer's wrapper.
void* real_pthread_create() { return reinterpret_cast<void*>(&pthread_create); }

const void* anchorMin() {
  return (const char*)LibraryPatcherTestAccessor::selfAnchor() - 0x1000;
}

const void* anchorMax() {
  return (const char*)LibraryPatcherTestAccessor::selfAnchor() + 0x1000;
}

} // namespace

// The regression test for the self-patching crash: a cache that covers our own
// code must be recognised as ours even when its path cannot be resolved.
//
// Before the fix the only self-check was realpath(name) == profiler path. The
// profiler's library is extracted to a temp file and unlinked once loaded, so
// realpath() returned nullptr, the check reported "not self", and the profiler
// patched its own pthread_create GOT slot. pthread_create_hook() calls
// pthread_create() through that same slot, so it then called itself until the
// thread stack was exhausted — SIGSEGV, and no hs_err, since reporting a crash
// also needs stack.
TEST(LibraryPatcherSelfCheck, RecognisesSelfWhenItsLibraryFileWasUnlinked) {
  CodeCache lib(kUnlinkedPath, -1, anchorMin(), anchorMax());

  EXPECT_TRUE(LibraryPatcherTestAccessor::isProfilerLibrary(&lib));
}

// The address range is what identifies us, not the mere fact that a path failed
// to resolve: a library that is genuinely not ours stays patchable even if its
// own path is unresolvable (deleted or replaced on upgrade, say).
TEST(LibraryPatcherSelfCheck, DoesNotRecogniseForeignLibraryWithUnresolvablePath) {
  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax);

  EXPECT_FALSE(LibraryPatcherTestAccessor::isProfilerLibrary(&lib));
}

// Identity is decided by the mapping alone, so a library that is not ours stays
// patchable whatever its path says — including a perfectly resolvable one. This
// pins the contract against a future reintroduction of name matching, which is
// what failed here in the first place.
TEST(LibraryPatcherSelfCheck, DoesNotRecogniseUnrelatedResolvablePath) {
  CodeCache lib("/proc/self/cmdline", -1, kForeignMin, kForeignMax);

  EXPECT_FALSE(LibraryPatcherTestAccessor::isProfilerLibrary(&lib));
}

// A cache with no known address range (min/max default to
// NO_MIN_ADDRESS/NO_MAX_ADDRESS, for which contains() is always false) is not
// us. Naming our own library must not change that, now that the name plays no
// part in the decision.
TEST(LibraryPatcherSelfCheck, DoesNotRecogniseCacheWithUnknownAddressRange) {
  Dl_info info;
  ASSERT_NE(0, dladdr(LibraryPatcherTestAccessor::selfAnchor(), &info));

  CodeCache lib(info.dli_fname);

  EXPECT_FALSE(LibraryPatcherTestAccessor::isProfilerLibrary(&lib));
}

// The predicate dereferences nothing but the cache's bounds, so it is safe to
// call at any point — including before the profiler has started, which is when
// the patch sites used to compare against a not-yet-resolved profiler path.
TEST(LibraryPatcherSelfCheck, TreatsNullLibraryAsForeign) {
  EXPECT_FALSE(LibraryPatcherTestAccessor::isProfilerLibrary(nullptr));
}

// patch_library_unlocked() skips a cache it has already patched by comparing
// CodeCache addresses, and successive tests tend to place their cache at the
// same stack address. Start each test from an empty table so one cannot mask a
// failure in the next.
class LibraryPatcherPatching : public ::testing::Test {
protected:
  void SetUp() override { LibraryPatcherTestAccessor::forgetPatchTable(); }
};

// End to end through the patcher: given a cache that looks like the profiler's
// own unlinked library and does expose a pthread_create import, the slot must be
// left alone and nothing recorded in the patch table.
TEST_F(LibraryPatcherPatching, LeavesItsOwnPthreadCreateSlotUntouched) {
  void* const original = (void*)&fake_original_pthread_create;
  void* slot = original;

  CodeCache lib(kUnlinkedPath, -1, anchorMin(), anchorMax(), nullptr,
                /* imports_patchable */ true);
  lib.addImport(&slot, "pthread_create");
  ASSERT_EQ(&slot, lib.findImport(im_pthread_create));

  int before = LibraryPatcherTestAccessor::patchedCount();
  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(original, slot);
  EXPECT_EQ(before, LibraryPatcherTestAccessor::patchedCount());
}

// The counterpart, so the test above cannot pass by the patcher simply having
// stopped working: an identical cache that is not ours does get its slot
// redirected to the hook.
//
// pthread_create patches are persistent (never unpatched), so after calling
// unpatch_recording_hooks() the slot stays hooked and the entry count remains.
// This is by design: pthread_create patches survive stop/start cycles.
TEST_F(LibraryPatcherPatching, StillPatchesForeignPthreadCreateSlot) {
  void* const original = real_pthread_create();
  void* slot = original;

  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true);
  lib.addImport(&slot, "pthread_create");

  int before = LibraryPatcherTestAccessor::patchedCount();
  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_NE(original, slot);
  EXPECT_EQ(before + 1, LibraryPatcherTestAccessor::patchedCount());
  void* const hooked = slot;

  LibraryPatcher::unpatch_recording_hooks();

  // pthread_create patches are persistent - slot stays hooked and count unchanged
  EXPECT_EQ(hooked, slot);
  EXPECT_EQ(before + 1, LibraryPatcherTestAccessor::patchedCount());
}

// A library that both calls pthread_create through its PLT (JUMP_SLOT) and takes
// its address (GLOB_DAT) has two slots; a thread created through either must go
// through the hook, under a single entry.
TEST_F(LibraryPatcherPatching, PatchesBothPthreadCreateSlots) {
  void* const original = real_pthread_create();
  void* jump_slot = original;
  void* glob_dat = original;

  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true);
  lib.addImport(&jump_slot, "pthread_create");
  lib.addImport(&glob_dat, "pthread_create");
  ASSERT_EQ(&glob_dat, lib.findImport(im_pthread_create, SECONDARY));

  int before = LibraryPatcherTestAccessor::patchedCount();
  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_NE(original, jump_slot);
  EXPECT_EQ(jump_slot, glob_dat);
  EXPECT_EQ(before + 1, LibraryPatcherTestAccessor::patchedCount());
}

// With the entry table full, a further library is not recorded, so it is left
// unhooked rather than patched without a way to recheck it.
TEST_F(LibraryPatcherPatching, LeavesSlotUnhookedWhenEntryTableIsFull) {
  void* const original = real_pthread_create();
  void* slot = original;
  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true);
  lib.addImport(&slot, "pthread_create");
  LibraryPatcherTestAccessor::setPatchedCount(MAX_NATIVE_LIBS);

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(original, slot);
  EXPECT_EQ(MAX_NATIVE_LIBS, LibraryPatcherTestAccessor::patchedCount());
}

// A library with an entry is checked again on every patch pass. These cases
// patch once, then put a value back into the slot and patch again.
class LibraryPatcherRehook : public LibraryPatcherPatching {
protected:
  void* slot = real_pthread_create();
  CodeCache lib{kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true};
  void* hooked = nullptr;

  void SetUp() override {
    LibraryPatcherPatching::SetUp();
    lib.addImport(&slot, "pthread_create");
    LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);
    hooked = slot;
    ASSERT_NE(real_pthread_create(), hooked);
  }
};

// Someone hooked the slot after us: taking it back would silently remove their
// interception on every recheck pass.
TEST_F(LibraryPatcherRehook, LeavesForeignHookInPlace) {
  void* foreign = (void*)&fake_original_pthread_create;
  ASSERT_FALSE(lib.contains(foreign));
  slot = foreign;

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(foreign, slot);
  EXPECT_EQ(1, LibraryPatcherTestAccessor::patchedCount());
}

// A reload with lazy binding: the fresh GOT points at the library's own PLT stub.
TEST_F(LibraryPatcherRehook, RehooksSlotHoldingOwnPltStub) {
  slot = (void*)((const char*)kForeignMin + 0x10);

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(hooked, slot);
  EXPECT_EQ(1, LibraryPatcherTestAccessor::patchedCount());
}

// A reload with eager binding: the fresh GOT holds the real pthread_create.
TEST_F(LibraryPatcherRehook, RehooksSlotHoldingRealPthreadCreate) {
  slot = (void*)&pthread_create;

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(hooked, slot);
  EXPECT_EQ(1, LibraryPatcherTestAccessor::patchedCount());
}

namespace {
typedef int (*create_fn)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*);

void* return_argument(void* arg) { return arg; }
} // namespace

// The patched slot holds the production hook, whose wrapper ends the thread with
// pthread_exit(): it must pass the routine's result on to pthread_join().
TEST_F(LibraryPatcherRehook, HookedThreadJoinsWithRoutineResult) {
  create_fn create = reinterpret_cast<create_fn>(hooked);
  int sentinel = 0;
  pthread_t thread;

  ASSERT_EQ(0, create(&thread, nullptr, return_argument, &sentinel));
  void* result = nullptr;
  ASSERT_EQ(0, pthread_join(thread, &result));

  EXPECT_EQ(&sentinel, result);
}

// Another interposer's wrapper was in the slot before our first patch. Taking it
// would bypass the wrapper for the process lifetime, since the hook is never
// unpatched.
TEST_F(LibraryPatcherPatching, LeavesForeignWrapperInPlaceOnFirstPatch) {
  void* const foreign = (void*)&fake_original_pthread_create;
  void* slot = foreign;
  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true);
  lib.addImport(&slot, "pthread_create");
  ASSERT_FALSE(lib.contains(foreign));

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);
  EXPECT_EQ(foreign, slot);
  EXPECT_EQ(0, LibraryPatcherTestAccessor::patchedCount());
  // No entry, so nothing a later pass needs the loader counts to revisit.
  EXPECT_FALSE(LibraryPatcherTestAccessor::declined());

  LibraryPatcher::unpatch_recording_hooks();  // stop
  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);  // start
  EXPECT_EQ(foreign, slot);
  EXPECT_EQ(0, LibraryPatcherTestAccessor::patchedCount());
}

// The rule is per slot: the slot that holds the loader's binding is hooked, the
// one that holds a wrapper is not, and the library stays unsettled.
TEST_F(LibraryPatcherPatching, HooksOnlySlotsHoldingLoaderBinding) {
  void* const foreign = (void*)&fake_original_pthread_create;
  void* jump_slot = real_pthread_create();
  void* glob_dat = foreign;
  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true);
  lib.addImport(&jump_slot, "pthread_create");
  lib.addImport(&glob_dat, "pthread_create");

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_NE(real_pthread_create(), jump_slot);
  EXPECT_EQ(foreign, glob_dat);
  EXPECT_EQ(1, LibraryPatcherTestAccessor::patchedCount());
  EXPECT_EQ(0, LibraryPatcherTestAccessor::entryMapped(&lib));
  EXPECT_TRUE(LibraryPatcherTestAccessor::declined());
}

// A preloaded interposer is what the loader resolves, so a slot holding it is
// hooked on the first patch like one holding the libc function.
TEST_F(LibraryPatcherPatching, PatchesSlotHoldingPreloadedInterposerOnFirstPatch) {
  void* const interposer = (void*)&fake_original_pthread_create;
  LibraryPatcherTestAccessor::setLoaderPthreadCreate(interposer);
  void* slot = interposer;
  CodeCache lib(kUnlinkedPath, -1, kForeignMin, kForeignMax, nullptr,
                /* imports_patchable */ true);
  lib.addImport(&slot, "pthread_create");

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_NE(interposer, slot);
  EXPECT_EQ(1, LibraryPatcherTestAccessor::patchedCount());
  EXPECT_EQ(1, LibraryPatcherTestAccessor::entryMapped(&lib));
  EXPECT_FALSE(LibraryPatcherTestAccessor::declined());
}

// A reload resolved into a preloaded interposer (the sanitizer runtime, say) is
// not a later hook: it is hooked again, as on the first load.
TEST_F(LibraryPatcherRehook, RehooksSlotHoldingPreloadedInterposer) {
  void* const interposer = (void*)&fake_original_pthread_create;
  LibraryPatcherTestAccessor::setLoaderPthreadCreate(interposer);
  slot = interposer;

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(hooked, slot);
  EXPECT_EQ(1, LibraryPatcherTestAccessor::entryMapped(&lib));
  EXPECT_FALSE(LibraryPatcherTestAccessor::declined());
}

// A slot a pass left alone leaves the entry unsettled, so that a pass can tell
// the library still needs another look; a slot it hooked again settles it.
TEST_F(LibraryPatcherRehook, ForeignHookLeavesEntryUnsettled) {
  ASSERT_EQ(1, LibraryPatcherTestAccessor::entryMapped(&lib));
  slot = (void*)&fake_original_pthread_create;

  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);

  EXPECT_EQ(0, LibraryPatcherTestAccessor::entryMapped(&lib));
  EXPECT_TRUE(LibraryPatcherTestAccessor::declined());
}

// forgetPatchTable() resets the whole table, flags included, so one test's
// leftovers cannot reach the next.
TEST_F(LibraryPatcherRehook, ForgetPatchTableResetsEveryField) {
  slot = (void*)&fake_original_pthread_create;
  LibraryPatcherTestAccessor::patchLibraryUnlocked(&lib);
  ASSERT_TRUE(LibraryPatcherTestAccessor::declined());

  LibraryPatcherTestAccessor::forgetPatchTable();

  EXPECT_EQ(0, LibraryPatcherTestAccessor::patchedCount());
  EXPECT_EQ(-1, LibraryPatcherTestAccessor::entryMapped(&lib));
  EXPECT_FALSE(LibraryPatcherTestAccessor::declined());
}

#endif // __linux__
