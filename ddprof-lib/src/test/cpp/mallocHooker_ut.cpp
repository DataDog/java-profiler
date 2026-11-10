/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "codeCache.h"
#include "mallocTracer.h"
#include "symbols.h"

#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <mach-o/loader.h>
#endif

class MallocHookerTestAccessor {
public:
  static void patchSlot(CodeCache* cc, void** location, void* hook, void* orig) {
    MallocHooker::patchSlot(cc, location, hook, orig);
  }
  static void restoreSlot(int index) { MallocHooker::restoreSlot(MallocHooker::_entries[index]); }
  static const MallocPatchEntry& entry(int index) { return MallocHooker::_entries[index]; }
  static int entryCount() { return MallocHooker::_entry_count; }
  static void setOrig(int index, void* orig) { MallocHooker::_entries[index]._orig = orig; }
  // Forgets the entries without restoring them: the tests patch slots in their
  // own frame, which are dead by the time a later test could restore them.
  static void setEntryCount(int count) { MallocHooker::_entry_count = count; }
  // Also zeroes the table: a stale entry whose dead stack slot address a later
  // test reuses would otherwise be taken for that test's slot.
  static void clearEntries() {
    memset(MallocHooker::_entries, 0, sizeof(MallocHooker::_entries));
    MallocHooker::_entry_count = 0;
    MallocHooker::_kept_count = 0;
  }
  static int maxEntries() { return MallocHooker::MAX_MALLOC_ENTRIES; }
  static int maxOrphanEntries() { return MallocHooker::MAX_ORPHAN_ENTRIES; }
  static void setEntry(int index, CodeCache* lib, void* orig, bool orig_resolved) {
    MallocPatchEntry& e = MallocHooker::_entries[index];
    e._lib = lib;
    e._location = reinterpret_cast<void**>(0x10000 + index * sizeof(void*));
    e._hook = nullptr;
    e._orig = orig;
    e._orig_resolved = orig_resolved;
  }
  static void keepUnrestoredEntries() { MallocHooker::keepUnrestoredEntries(); }
  static int patchedLibs() { return MallocHooker::_patched_libs; }
  static void setPatchedLibs(int count) { MallocHooker::_patched_libs = count; }
  static void unpatchLibraries() { MallocHooker::unpatchLibraries(); }
};

namespace {

// Distinct functions standing in for the hook, the real allocator and what a
// fresh GOT slot holds before binding (a PLT stub) or after another interposer.
void* fake_hook(size_t) { return nullptr; }
void* fake_original(size_t) { return reinterpret_cast<void*>(1); }
void* fake_plt_stub(size_t) { return reinterpret_cast<void*>(2); }
void* fake_foreign(size_t) { return reinterpret_cast<void*>(3); }

void* hook() { return reinterpret_cast<void*>(&fake_hook); }
void* original() { return reinterpret_cast<void*>(&fake_original); }
void* pltStub() { return reinterpret_cast<void*>(&fake_plt_stub); }
void* foreign() { return reinterpret_cast<void*>(&fake_foreign); }

// Not a loaded image: no walk can verify it, and its range overlaps no mapping.
const char* const kUnloadedPath = "/tmp/ddprof_test/libnot-loaded.so";
const void* const kForeignMin = reinterpret_cast<const void*>(0x1000);
const void* const kForeignMax = reinterpret_cast<const void*>(0x2000);

} // namespace

class MallocHookerSlots : public ::testing::Test {
protected:
  CodeCache lib{kUnloadedPath, -1, kForeignMin, kForeignMax};
  int saved_patched_libs = 0;

  void SetUp() override {
    MallocHookerTestAccessor::clearEntries();
    saved_patched_libs = MallocHookerTestAccessor::patchedLibs();
  }
  void TearDown() override {
    MallocHookerTestAccessor::clearEntries();
    MallocHookerTestAccessor::setPatchedLibs(saved_patched_libs);
  }
};

// The entry records what the slot held, not the resolved original: a lazily
// bound slot holds the PLT stub, and that is what a restore must put back.
TEST_F(MallocHookerSlots, PatchRecordsSlotContentAndWritesHook) {
  void* slot = pltStub();

  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  EXPECT_EQ(hook(), slot);
  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());
  const MallocPatchEntry& e = MallocHookerTestAccessor::entry(0);
  EXPECT_EQ(&lib, e._lib);
  EXPECT_EQ(&slot, e._location);
  EXPECT_EQ(hook(), e._hook);
  EXPECT_EQ(pltStub(), e._orig);
}

// A slot still hooked by a recording whose entry was dropped is recorded again
// with the known original, so this recording's stop() unhooks it.
TEST_F(MallocHookerSlots, PatchRecordsHookedSlotWithoutEntryAgainstKnownOriginal) {
  void* slot = hook();

  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());
  EXPECT_EQ(original(), MallocHookerTestAccessor::entry(0)._orig);
  MallocHookerTestAccessor::restoreSlot(0);
  EXPECT_EQ(original(), slot);
}

// A kept entry whose slot no longer holds our hook (the library reloaded and the
// interposer left) is replaced, not joined by a second entry: both would restore
// on stop(), and the stale original could win.
TEST_F(MallocHookerSlots, PatchReplacesKeptEntryOfSlotThatNoLongerHoldsHook) {
  void* slot = hook();
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());
  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());
  MallocHookerTestAccessor::setOrig(0, foreign());  // the original the kept entry saved
  MallocHookerTestAccessor::keepUnrestoredEntries();
  slot = pltStub();                                 // the reloaded library's fresh slot

  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());
  EXPECT_EQ(pltStub(), MallocHookerTestAccessor::entry(0)._orig);
  MallocHookerTestAccessor::restoreSlot(0);
  EXPECT_EQ(pltStub(), slot);
}

// Two caches of one image (a reload at the same base) both patch the slot in one
// recording: the second finds our hook there and must not record the resolved
// original over the PLT stub the first one saved.
TEST_F(MallocHookerSlots, SecondCacheOfSameImageDoesNotReplaceSavedOriginal) {
  CodeCache other{kUnloadedPath, -1, kForeignMin, kForeignMax};
  void* slot = pltStub();
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  MallocHookerTestAccessor::patchSlot(&other, &slot, hook(), original());

  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());
  EXPECT_EQ(pltStub(), MallocHookerTestAccessor::entry(0)._orig);
  MallocHookerTestAccessor::restoreSlot(0);
  EXPECT_EQ(pltStub(), slot);
}

// Over the orphan cap, the entries dropped are those whose original patchSlot()
// rebuilds anyway; another interposer's wrapper survives wherever it sits.
TEST_F(MallocHookerSlots, KeepUnrestoredEntriesDropsRebuildableOnesFirst) {
  const int cap = MallocHookerTestAccessor::maxOrphanEntries();
  const int foreign_count = 10;
  const int total = cap + foreign_count + 5;
  for (int i = 0; i < total - foreign_count; i++) {
    MallocHookerTestAccessor::setEntry(i, &lib, original(), true);
  }
  // Last, where a prefix cut would drop them.
  for (int i = total - foreign_count; i < total; i++) {
    MallocHookerTestAccessor::setEntry(i, &lib, foreign(), false);
  }
  MallocHookerTestAccessor::setEntry(0, nullptr, original(), true);  // restored
  MallocHookerTestAccessor::setEntryCount(total);

  MallocHookerTestAccessor::keepUnrestoredEntries();

  ASSERT_EQ(cap, MallocHookerTestAccessor::entryCount());
  int foreign_kept = 0;
  for (int i = 0; i < cap; i++) {
    EXPECT_NE(nullptr, MallocHookerTestAccessor::entry(i)._lib) << "restored entry kept at " << i;
    foreign_kept += MallocHookerTestAccessor::entry(i)._orig == foreign();
  }
  EXPECT_EQ(foreign_count, foreign_kept);
}

// The entry notes whether its original is the resolved one.
TEST_F(MallocHookerSlots, PatchNotesWhetherOriginalIsResolved) {
  void* resolved_slot = original();
  void* foreign_slot = foreign();

  MallocHookerTestAccessor::patchSlot(&lib, &resolved_slot, hook(), original());
  MallocHookerTestAccessor::patchSlot(&lib, &foreign_slot, hook(), original());

  ASSERT_EQ(2, MallocHookerTestAccessor::entryCount());
  EXPECT_TRUE(MallocHookerTestAccessor::entry(0)._orig_resolved);
  EXPECT_FALSE(MallocHookerTestAccessor::entry(1)._orig_resolved);
  MallocHookerTestAccessor::restoreSlot(0);
  MallocHookerTestAccessor::restoreSlot(1);
}

// Every hook must be restorable, so a slot that cannot be recorded stays unhooked.
TEST_F(MallocHookerSlots, PatchLeavesSlotAloneWhenTableIsFull) {
  void* slot = original();
  int full = MallocHookerTestAccessor::maxEntries();
  MallocHookerTestAccessor::setEntryCount(full);

  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  EXPECT_EQ(original(), slot);
  EXPECT_EQ(full, MallocHookerTestAccessor::entryCount());
}

// A stale hook that cannot be recorded would never be restored by stop(), so it
// is unhooked at once.
TEST_F(MallocHookerSlots, PatchUnhooksStaleHookWhenTableIsFull) {
  void* slot = hook();
  int full = MallocHookerTestAccessor::maxEntries();
  MallocHookerTestAccessor::setEntryCount(full);

  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  EXPECT_EQ(original(), slot);
  EXPECT_EQ(full, MallocHookerTestAccessor::entryCount());
}

// Nothing to patch without a slot, or nothing to forward to without an original.
TEST_F(MallocHookerSlots, PatchIgnoresMissingSlotOrOriginal) {
  void* slot = original();

  MallocHookerTestAccessor::patchSlot(&lib, nullptr, hook(), original());
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), nullptr);

  EXPECT_EQ(original(), slot);
  EXPECT_EQ(0, MallocHookerTestAccessor::entryCount());
}

TEST_F(MallocHookerSlots, RestorePutsRecordedContentBack) {
  void* slot = pltStub();
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  MallocHookerTestAccessor::restoreSlot(0);

  EXPECT_EQ(pltStub(), slot);
}

// Restore only undoes our own write: an interposer that re-patched the slot
// after us keeps its interception.
TEST_F(MallocHookerSlots, RestoreLeavesSlotRepatchedBySomeoneElse) {
  void* slot = original();
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());
  slot = foreign();

  MallocHookerTestAccessor::restoreSlot(0);

  EXPECT_EQ(foreign(), slot);
}

#ifdef __linux__
// unpatchLibraries() writes only through slots of libraries the walk visits. The
// entries of one it cannot verify are kept, not written through, so a later
// patchSlot() still knows the slot's true original. A cache without an image
// base (never parsed) is not even a candidate, so its slot is not written on
// any libc.
TEST_F(MallocHookerSlots, UnpatchKeepsEntriesOfLibraryItCannotVerify) {
  void* slot = original();
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());
  MallocHookerTestAccessor::setPatchedLibs(3);

  MallocHookerTestAccessor::unpatchLibraries();

  EXPECT_EQ(1, MallocHookerTestAccessor::entryCount());
  EXPECT_EQ(0, MallocHookerTestAccessor::patchedLibs());
  EXPECT_EQ(hook(), slot);
}

// A slot whose entry survived stop() is not re-recorded against the resolved
// original: its true original (here a PLT stub) is what a later restore needs.
TEST_F(MallocHookerSlots, RehookOfKeptEntryKeepsTrueOriginal) {
  void* slot = pltStub();
  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());
  MallocHookerTestAccessor::setPatchedLibs(3);
  MallocHookerTestAccessor::unpatchLibraries();
  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());

  MallocHookerTestAccessor::patchSlot(&lib, &slot, hook(), original());

  ASSERT_EQ(1, MallocHookerTestAccessor::entryCount());
  EXPECT_EQ(pltStub(), MallocHookerTestAccessor::entry(0)._orig);
  MallocHookerTestAccessor::restoreSlot(0);
  EXPECT_EQ(pltStub(), slot);
}
#endif // __linux__

#ifdef __APPLE__
namespace {

// A minimal 64-bit Mach-O header followed by load commands.
struct FakeImage {
  mach_header_64 header;
  uuid_command uuid;
};

FakeImage fakeImage(uint8_t uuid_seed, bool with_uuid) {
  FakeImage image;
  memset(&image, 0, sizeof(image));
  image.header.magic = MH_MAGIC_64;
  image.header.ncmds = with_uuid ? 1 : 0;
  image.header.sizeofcmds = with_uuid ? sizeof(uuid_command) : 0;
  image.uuid.cmd = LC_UUID;
  image.uuid.cmdsize = sizeof(uuid_command);
  for (int i = 0; i < 16; i++) {
    image.uuid.uuid[i] = static_cast<uint8_t>(uuid_seed + i);
  }
  return image;
}

// The cache the parser builds for the image containing malloc, with its UUID.
struct LoadedImage {
  Dl_info info;
  CodeCache* cc;
  LoadedImage() {
    if (dladdr(reinterpret_cast<void*>(&malloc), &info) == 0) {
      cc = nullptr;
      return;
    }
    cc = new CodeCache(info.dli_fname, -1, info.dli_fbase,
                       static_cast<const char*>(info.dli_fbase) + 1);
    cc->setImageFingerprint(Symbols::imageFingerprint(info.dli_fbase));
  }
  ~LoadedImage() { delete cc; }
  LoadedImage(const LoadedImage&) = delete;
  LoadedImage& operator=(const LoadedImage&) = delete;
};

} // namespace

TEST(MachOImageFingerprint, DerivedFromUuid) {
  FakeImage a = fakeImage(1, true);
  FakeImage same = fakeImage(1, true);
  FakeImage b = fakeImage(2, true);

  u64 fa = Symbols::imageFingerprint(&a);
  EXPECT_NE(0u, fa);
  EXPECT_EQ(fa, Symbols::imageFingerprint(&same));
  EXPECT_NE(fa, Symbols::imageFingerprint(&b));
}

TEST(MachOImageFingerprint, UnknownWithoutUuidOrForeignHeader) {
  FakeImage no_uuid = fakeImage(1, false);
  FakeImage not_64bit = fakeImage(1, true);
  not_64bit.header.magic = MH_MAGIC;

  EXPECT_EQ(0u, Symbols::imageFingerprint(&no_uuid));
  EXPECT_EQ(0u, Symbols::imageFingerprint(&not_64bit));
  EXPECT_EQ(0u, Symbols::imageFingerprint(nullptr));
}

// isCurrentImage() is file-local; observe it through unpatchLibraries(), which
// restores a library's recorded slots only if the image is the one cached.
static bool restoredBySlotWithFingerprint(LoadedImage& image, u64 fingerprint) {
  image.cc->setImageFingerprint(fingerprint);
  void* slot = original();
  MallocHookerTestAccessor::patchSlot(image.cc, &slot, hook(), original());
  MallocHookerTestAccessor::unpatchLibraries();
  return slot == original();
}

TEST(MallocHookerCurrentImage, AcceptsImageWithRecordedUuid) {
  LoadedImage image;
  ASSERT_NE(nullptr, image.cc);
  u64 uuid = image.cc->imageFingerprint();
  ASSERT_NE(0u, uuid) << image.info.dli_fname << " has no LC_UUID";

  EXPECT_TRUE(restoredBySlotWithFingerprint(image, uuid));
}

// Another build of the same path loaded at the same base: its GOT slots need
// not be where the cache recorded them.
TEST(MallocHookerCurrentImage, RejectsSameBaseAndPathWithOtherUuid) {
  LoadedImage image;
  ASSERT_NE(nullptr, image.cc);
  u64 other = image.cc->imageFingerprint() + 1;

  EXPECT_FALSE(restoredBySlotWithFingerprint(image, other != 0 ? other : 1));
}

// A cache without a recorded UUID keeps the base-and-path check.
TEST(MallocHookerCurrentImage, AcceptsUnknownFingerprintAtSameBaseAndPath) {
  LoadedImage image;
  ASSERT_NE(nullptr, image.cc);

  EXPECT_TRUE(restoredBySlotWithFingerprint(image, 0));
}

// parseLibraries() must record the fingerprint of every image it parses.
TEST(SymbolsParseLibraries, RecordsImageFingerprint) {
  Dl_info info;
  ASSERT_NE(0, dladdr(reinterpret_cast<void*>(&malloc), &info));
  Symbols::clearParsingCaches();
  CodeCacheArray* array = new CodeCacheArray();

  Symbols::parseLibraries(array, false);

  CodeCache* found = nullptr;
  for (int i = 0; i < array->count(); i++) {
    if (strcmp((*array)[i]->name(), info.dli_fname) == 0) found = (*array)[i];
  }
  ASSERT_NE(nullptr, found);
  EXPECT_NE(0u, found->imageFingerprint());
  EXPECT_EQ(Symbols::imageFingerprint(info.dli_fbase), found->imageFingerprint());
  for (int i = 0; i < array->count(); i++) delete (*array)[i];
  delete array;
  Symbols::clearParsingCaches();
}

// LC_UUID is found by walking load commands with their cmdsize stride.
TEST(MachOImageFingerprint, SkipsLoadCommandsBeforeUuid) {
  struct {
    mach_header_64 header;
    load_command other;
    uuid_command uuid;
  } padded;
  FakeImage plain = fakeImage(5, true);
  memset(&padded, 0, sizeof(padded));
  padded.header = plain.header;
  padded.header.ncmds = 2;
  padded.header.sizeofcmds = sizeof(load_command) + sizeof(uuid_command);
  padded.other.cmd = LC_SEGMENT_64;
  padded.other.cmdsize = sizeof(load_command);
  padded.uuid = plain.uuid;

  EXPECT_NE(0u, Symbols::imageFingerprint(&padded));
  EXPECT_EQ(Symbols::imageFingerprint(&plain), Symbols::imageFingerprint(&padded));
}

// A load command that cannot be stepped over safely ends the walk without a
// fingerprint, instead of hanging (cmdsize 0) or reading past the commands.
TEST(MachOImageFingerprint, UnknownForMalformedLoadCommands) {
  FakeImage zero_size = fakeImage(5, true);
  zero_size.header.ncmds = 2;
  zero_size.uuid.cmd = LC_SEGMENT_64;
  zero_size.uuid.cmdsize = 0;
  EXPECT_EQ(0u, Symbols::imageFingerprint(&zero_size));

  FakeImage oversized = fakeImage(5, true);
  oversized.uuid.cmd = LC_SEGMENT_64;
  oversized.uuid.cmdsize = sizeof(uuid_command) + 8;
  EXPECT_EQ(0u, Symbols::imageFingerprint(&oversized));

  FakeImage truncated_uuid = fakeImage(5, true);
  truncated_uuid.uuid.cmdsize = sizeof(load_command);
  truncated_uuid.header.sizeofcmds = sizeof(load_command);
  EXPECT_EQ(0u, Symbols::imageFingerprint(&truncated_uuid));
}

// A UUID hashing to zero must not look like "unknown fingerprint" (0).
TEST(MachOImageFingerprint, ZeroHashRemapsToOne) {
  FakeImage image = fakeImage(0, true);
  const u64 hi = 0x9e3779b97f4a7c15ULL;  // hi == lo * constant with lo == 1
  const u64 lo = 1;
  memcpy(image.uuid.uuid, &hi, sizeof(hi));
  memcpy(image.uuid.uuid + sizeof(hi), &lo, sizeof(lo));

  EXPECT_EQ(1u, Symbols::imageFingerprint(&image));
}
#endif // __APPLE__
