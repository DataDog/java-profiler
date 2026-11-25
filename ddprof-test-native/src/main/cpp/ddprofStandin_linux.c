/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Linux-only ddprof test double inside libddproftest: it exports the ddprof
// marker names with call counters and JNI entry points that save, rewrite
// and restore the profiler's own allocation GOT slots, the way the real
// ddprof hook owner would. Production code never calls any of this; only
// Linux child-JVM tests do. Because this file is part of libddproftest, every
// existing nativemem test also runs with a loaded ddprof-marker image that is
// not intercepting anything (the loaded-but-not-intercepting control).
#ifdef __linux__

/* dl_phdr_info and dl_iterate_phdr are GNU extensions: define _GNU_SOURCE
 * before any include. */
#define _GNU_SOURCE

#include <jni.h>

#include <elf.h>
#include <link.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

// Marker call counters: the admission check must never execute a marker, so
// tests assert these stay 0 across classification.
uint64_t standin_start_calls;
uint64_t standin_stop_calls;

__attribute__((visibility("default"))) void ddprof_start_profiling(void) {
  standin_start_calls++;
}

__attribute__((visibility("default"))) void ddprof_stop_profiling(void) {
  standin_stop_calls++;
}

/* Saved forwarding values and the stand-in forwarders. The forwarders call
 * the saved values through these local copies, never through the stand-in's
 * own GOT, so a rewritten slot cannot recurse into the stand-in. */
static void* (*saved_malloc)(size_t);
static void* (*saved_calloc)(size_t, size_t);
static void* (*saved_realloc)(void*, size_t);
static int (*saved_posix_memalign)(void**, size_t, size_t);
static void* (*saved_aligned_alloc)(size_t, size_t);

static void* standin_malloc(size_t size) { return saved_malloc(size); }
static void* standin_calloc(size_t num, size_t size) { return saved_calloc(num, size); }
static void* standin_realloc(void* addr, size_t size) { return saved_realloc(addr, size); }
static int standin_posix_memalign(void** memptr, size_t alignment, size_t size) {
  return saved_posix_memalign(memptr, alignment, size);
}
static void* standin_aligned_alloc(size_t alignment, size_t size) {
  return saved_aligned_alloc(alignment, size);
}

/* The five allocation symbols, in binding index order. */
static const char* const OPERATION_NAMES[5] = {"malloc", "calloc", "realloc", "posix_memalign",
                                               "aligned_alloc"};
static void* const STANDIN_HOOKS[5] = {(void*)standin_malloc, (void*)standin_calloc, (void*)standin_realloc,
                                       (void*)standin_posix_memalign, (void*)standin_aligned_alloc};

/* Found GOT slot addresses per operation (a JUMP_SLOT and possibly a
 * GLOB_DAT entry each) and the values saved from them. */
#define MAX_SLOTS_PER_OP 4
static void** operation_slots[5][MAX_SLOTS_PER_OP];
static void* operation_saved[5][MAX_SLOTS_PER_OP];
static int operation_slot_count[5];
static int installed;

static int appendOperationSlot(void*** slots, int* count, int capacity, void** slot) {
  if (*count >= capacity) return -1;
  slots[*count] = slot;
  (*count)++;
  return 0;
}

struct ProfilerImage {
  uintptr_t bias;
  const ElfW(Phdr)* phdr;
  ElfW(Half) phnum;
};

// Checked arithmetic without __builtin_*_overflow: libddproftest also builds
// on EL7, whose stock gcc 4.8.5 predates those builtins (GCC 5).
static int checkedAdd(uintptr_t a, uintptr_t b, uintptr_t* out) {
  if (UINTPTR_MAX - a < b) return -1;
  *out = a + b;
  return 0;
}

static int checkedMul(size_t a, size_t b, size_t* out) {
  if (a != 0 && SIZE_MAX / a < b) return -1;
  *out = a * b;
  return 0;
}

static int imageAddress(const struct ProfilerImage* image, uintptr_t vaddr, uintptr_t* address) {
  return checkedAdd(image->bias, vaddr, address) ? -1 : 0;
}

// Check ranges by subtraction so neither segment nor address end arithmetic can wrap.
static int readableRange(const struct ProfilerImage* image, uintptr_t address, size_t size) {
  for (ElfW(Half) i = 0; i < image->phnum; i++) {
    const ElfW(Phdr)* ph = &image->phdr[i];
    uintptr_t start;
    uintptr_t end;
    if (ph->p_type != PT_LOAD || (ph->p_flags & PF_R) == 0 || imageAddress(image, ph->p_vaddr, &start) != 0
        || checkedAdd(start, (uintptr_t)ph->p_filesz, &end) != 0 || address < start || address > end) {
      continue;
    }
    uintptr_t offset = address - start;
    if (offset <= ph->p_filesz && size <= ph->p_filesz - offset) return 1;
  }
  return 0;
}

// glibc relocates dynamic-section pointers in place; musl leaves them as
// image-relative virtual addresses. Failure must not fall back to the raw value.
static int dynamicPointer(uintptr_t raw, const struct ProfilerImage* image, uintptr_t* address) {
  uintptr_t min_vaddr = UINTPTR_MAX;
  for (ElfW(Half) i = 0; i < image->phnum; i++) {
    if (image->phdr[i].p_type == PT_LOAD && image->phdr[i].p_vaddr < min_vaddr) {
      min_vaddr = image->phdr[i].p_vaddr;
    }
  }
  if (min_vaddr == UINTPTR_MAX) return -1;
  long page_size = sysconf(_SC_PAGESIZE);
  if (page_size <= 0) return -1;
  uintptr_t base_page;
  uintptr_t page_mask = (uintptr_t)page_size - 1;
  if (imageAddress(image, min_vaddr & ~page_mask, &base_page) != 0) return -1;
  if (raw >= base_page) {
    *address = raw;
    return 0;
  }
  return imageAddress(image, raw, address);
}

static int findProfilerImage(struct dl_phdr_info* info, size_t size, void* data) {
  (void)size;
  struct ProfilerImage* image = (struct ProfilerImage*)data;
  if (info->dlpi_name != NULL && strstr(info->dlpi_name, "libjavaProfiler") != NULL) {
    image->bias = (uintptr_t)info->dlpi_addr;
    image->phdr = info->dlpi_phdr;
    image->phnum = (ElfW(Half))info->dlpi_phnum;
    return 1;
  }
  return 0;
}

enum OperationLookupResult {
  OPERATION_LOOKUP_INVALID_INDEX = -1,
  OPERATION_LOOKUP_INVALID_NAME_OFFSET = -2,
  OPERATION_LOOKUP_UNTERMINATED_NAME = -3,
  OPERATION_LOOKUP_NO_MATCH = -4,
  OPERATION_LOOKUP_INVALID_TABLE = -5,
};

/* Resolves an operation name only after validating its supplied ELF table bounds. */
static int operationIndex(const ElfW(Sym)* symtab, size_t nsyms, const char* strtab, size_t strsz,
                          size_t sym_index) {
  if (symtab == NULL || strtab == NULL || strsz == 0) return OPERATION_LOOKUP_INVALID_TABLE;
  if (sym_index >= nsyms) return OPERATION_LOOKUP_INVALID_INDEX;
  size_t st_name = symtab[sym_index].st_name;
  if (st_name >= strsz) return OPERATION_LOOKUP_INVALID_NAME_OFFSET;
  const char* name = strtab + st_name;
  if (memchr(name, '\0', strsz - st_name) == NULL) return OPERATION_LOOKUP_UNTERMINATED_NAME;
  for (int op = 0; op < 5; op++) {
    if (strcmp(name, OPERATION_NAMES[op]) == 0) return op;
  }
  return OPERATION_LOOKUP_NO_MATCH;
}

/* Locates the libjavaProfiler image and records every JUMP_SLOT/GLOB_DAT
 * relocation for the five allocation symbols. Every ELF-derived read range
 * must be readable and file-backed; malformed metadata fails closed. */
static int locateOperationSlots(struct ProfilerImage* image) {
  memset(operation_slot_count, 0, sizeof(operation_slot_count));
  const ElfW(Phdr)* dynamic = NULL;
  for (ElfW(Half) i = 0; i < image->phnum; i++) {
    if (image->phdr[i].p_type == PT_DYNAMIC) {
      dynamic = &image->phdr[i];
      break;
    }
  }
  if (dynamic == NULL || dynamic->p_filesz < sizeof(ElfW(Dyn))
      || dynamic->p_filesz % sizeof(ElfW(Dyn)) != 0) {
    return -1;
  }
  uintptr_t dyn_addr;
  if (imageAddress(image, dynamic->p_vaddr, &dyn_addr) != 0 || !readableRange(image, dyn_addr, dynamic->p_filesz)) {
    return -1;
  }
  const ElfW(Dyn)* dyn = (const ElfW(Dyn)*)dyn_addr;

  uintptr_t jmprel = 0;
  size_t pltrelsz = 0;
  uintptr_t rela = 0;
  size_t relasz = 0;
  const ElfW(Sym)* symtab = NULL;
  const char* strtab = NULL;
  size_t strsz = 0;
  size_t dyn_count = dynamic->p_filesz / sizeof(*dyn);
  int found_null = 0;
  for (size_t i = 0; i < dyn_count; i++) {
    const ElfW(Dyn)* d = &dyn[i];
    if (d->d_tag == DT_NULL) {
      found_null = 1;
      break;
    }
    switch (d->d_tag) {
      case DT_JMPREL: {
        uintptr_t address;
        if (dynamicPointer((uintptr_t)d->d_un.d_ptr, image, &address) != 0) return -1;
        jmprel = address;
        break;
      }
      case DT_PLTRELSZ:
        pltrelsz = (size_t)d->d_un.d_val;
        break;
      case DT_RELA: {
        uintptr_t address;
        if (dynamicPointer((uintptr_t)d->d_un.d_ptr, image, &address) != 0) return -1;
        rela = address;
        break;
      }
      case DT_RELASZ:
        relasz = (size_t)d->d_un.d_val;
        break;
      case DT_SYMTAB: {
        uintptr_t address;
        if (dynamicPointer((uintptr_t)d->d_un.d_ptr, image, &address) != 0) return -1;
        symtab = (const ElfW(Sym)*)address;
        break;
      }
      case DT_STRTAB: {
        uintptr_t address;
        if (dynamicPointer((uintptr_t)d->d_un.d_ptr, image, &address) != 0) return -1;
        strtab = (const char*)address;
        break;
      }
      case DT_STRSZ:
        strsz = (size_t)d->d_un.d_val;
        break;
      default:
        break;
    }
  }
  if (!found_null || symtab == NULL || strtab == NULL || strsz == 0) return -1;
  uintptr_t symtab_addr = (uintptr_t)symtab;
  uintptr_t strtab_addr = (uintptr_t)strtab;
  if (strtab_addr <= symtab_addr) return -1;
  size_t nsyms = (size_t)((strtab_addr - symtab_addr) / sizeof(*symtab));
  size_t symtab_size;
  if (nsyms == 0 || checkedMul(nsyms, sizeof(*symtab), &symtab_size) != 0
      || !readableRange(image, symtab_addr, symtab_size) || !readableRange(image, strtab_addr, strsz)) {
    return -1;
  }

  for (int table = 0; table < 2; table++) {
    uintptr_t base = table == 0 ? jmprel : rela;
    size_t size = table == 0 ? pltrelsz : relasz;
    if (size == 0) continue;
    if (base == 0 || size % sizeof(ElfW(Rela)) != 0 || !readableRange(image, base, size)) return -1;
    for (size_t off = 0; off < size; off += sizeof(ElfW(Rela))) {
      const ElfW(Rela)* entry = (const ElfW(Rela)*)(base + off);
      unsigned int reloc_type = ELF64_R_TYPE(entry->r_info);
#if defined(__aarch64__)
      if (reloc_type != R_AARCH64_JUMP_SLOT && reloc_type != R_AARCH64_GLOB_DAT) continue;
#elif defined(__x86_64__)
      if (reloc_type != R_X86_64_JUMP_SLOT && reloc_type != R_X86_64_GLOB_DAT) continue;
#else
      continue;
#endif
      size_t sym_index = ELF64_R_SYM(entry->r_info);
      int op = operationIndex(symtab, nsyms, strtab, strsz, sym_index);
      if (op == OPERATION_LOOKUP_NO_MATCH) continue;
      if (op < 0) return -1;
      uintptr_t slot_addr;
      if (imageAddress(image, entry->r_offset, &slot_addr) != 0 || !readableRange(image, slot_addr, sizeof(void*))) {
        return -1;
      }
      void** slot = (void**)slot_addr;
      if (appendOperationSlot(operation_slots[op], &operation_slot_count[op], MAX_SLOTS_PER_OP, slot) != 0) {
        return -1;
      }
    }
  }
  for (int op = 0; op < 5; op++) {
    if (operation_slot_count[op] == 0) return -1;
  }
  return 0;
}

/* Makes one GOT page writable. GLOB_DAT relocation slots sit in a RELRO
 * region that the loader made read-only, so the rewrite needs its own
 * mprotect; the test process keeps no write-protection guarantees. */
static int makeSlotWritable(void** slot) {
  long page_size = sysconf(_SC_PAGESIZE);
  uintptr_t page = (uintptr_t)slot & ~((uintptr_t)page_size - 1);
  return mprotect((void*)page, page_size, PROT_READ | PROT_WRITE);
}

static int rewriteSlots(void* const* new_values, int save_existing) {
  struct ProfilerImage image;
  memset(&image, 0, sizeof(image));
  if (dl_iterate_phdr(findProfilerImage, &image) == 0) return -1;
  if (locateOperationSlots(&image) != 0) return -1;

  /* Snapshot every original and wire the saved_* forwarder targets before
   * any hook is published: a concurrent JVM thread that allocates after a
   * hook became visible would otherwise reach a still-null target. The
   * plain stores rely on the same word-store visibility the GOT rewrite
   * itself relies on, as the production patchers do. */
  if (save_existing) {
    for (int op = 0; op < 5; op++) {
      for (int i = 0; i < operation_slot_count[op]; i++) {
        operation_saved[op][i] = *operation_slots[op][i];
      }
    }
    saved_malloc = (void* (*)(size_t))operation_saved[0][0];
    saved_calloc = (void* (*)(size_t, size_t))operation_saved[1][0];
    saved_realloc = (void* (*)(void*, size_t))operation_saved[2][0];
    saved_posix_memalign = (int (*)(void**, size_t, size_t))operation_saved[3][0];
    saved_aligned_alloc = (void* (*)(size_t, size_t))operation_saved[4][0];
  }
  for (int op = 0; op < 5; op++) {
    for (int i = 0; i < operation_slot_count[op]; i++) {
      void** slot = operation_slots[op][i];
      if (makeSlotWritable(slot) != 0) return -1;
      *slot = (void*)new_values[op];
    }
  }
  return 0;
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativemem_DdprofStandin_install(JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  if (installed) return 0;
  /* The installer skips only an already-installed stand-in; slot values are
 * saved before the rewrite, and restore() puts the originals back. */
  if (rewriteSlots(STANDIN_HOOKS, 1) != 0) return -1;
  installed = 1;
  return 0;
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativemem_DdprofStandin_restore(JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  if (!installed) return 0;
  for (int op = 0; op < 5; op++) {
    for (int i = 0; i < operation_slot_count[op]; i++) {
      void** slot = operation_slots[op][i];
      if (makeSlotWritable(slot) != 0) return -1;
      *slot = operation_saved[op][i];
    }
  }
  installed = 0;
  return 0;
}

JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_nativemem_DdprofStandin_savedMalloc(JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  return operation_slot_count[0] > 0 ? (jlong)(uintptr_t)operation_saved[0][0] : 0;
}

JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_nativemem_DdprofStandin_startMarkerCalls(JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  return (jlong)standin_start_calls;
}

JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_nativemem_DdprofStandin_stopMarkerCalls(JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  return (jlong)standin_stop_calls;
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativemem_NativememDdprofExclusionTest_checkMalformedMetadata(
    JNIEnv* env, jclass clazz, jint scenario) {
  (void)env;
  (void)clazz;
  ElfW(Sym) symtab[2];
  memset(symtab, 0, sizeof(symtab));
  char strtab[] = {'m', 'a', 'l', 'l', 'o', 'c', '\0', '\0'};
  size_t nsyms = 1;
  size_t strsz = 7;
  size_t sym_index = 0;

  switch (scenario) {
    case 0:
      symtab[1].st_name = 0;
      sym_index = 1;
      return operationIndex(symtab, nsyms, strtab, strsz, sym_index);
    case 1:
      symtab[0].st_name = 6;
      strsz = 6;
      return operationIndex(symtab, nsyms, strtab, strsz, sym_index);
    case 2:
      strtab[6] = 'x';
      strsz = 6;
      return operationIndex(symtab, nsyms, strtab, strsz, sym_index);
    case 3: {
      ElfW(Phdr) phdr[1];
      memset(phdr, 0, sizeof(phdr));
      phdr[0].p_type = PT_LOAD;
      phdr[0].p_flags = PF_R;
      phdr[0].p_filesz = 0x1000;
      struct ProfilerImage image = {UINTPTR_MAX - 0x800, phdr, 1};
      uintptr_t address;
      return dynamicPointer(0x1000, &image, &address);
    }
    case 4: {
      ElfW(Phdr) phdr[1];
      memset(phdr, 0, sizeof(phdr));
      phdr[0].p_type = PT_LOAD;
      phdr[0].p_flags = PF_W;
      phdr[0].p_vaddr = 0x1000;
      phdr[0].p_filesz = 0x40;
      struct ProfilerImage image = {0, phdr, 1};
      return readableRange(&image, 0x1000, 1);
    }
    case 5: {
      ElfW(Dyn) entries[1];
      ElfW(Phdr) phdr[2];
      memset(entries, 0, sizeof(entries));
      memset(phdr, 0, sizeof(phdr));
      phdr[0].p_type = PT_DYNAMIC;
      phdr[0].p_vaddr = (ElfW(Addr))(uintptr_t)entries;
      phdr[0].p_filesz = sizeof(entries);
      phdr[1].p_type = PT_LOAD;
      phdr[1].p_flags = PF_W;
      phdr[1].p_vaddr = (ElfW(Addr))(uintptr_t)entries;
      phdr[1].p_filesz = sizeof(entries);
      struct ProfilerImage image = {0, phdr, 2};
      return locateOperationSlots(&image);
    }
    case 6: {
      ElfW(Phdr) phdr[1];
      memset(phdr, 0, sizeof(phdr));
      phdr[0].p_type = PT_LOAD;
      phdr[0].p_flags = PF_R;
      phdr[0].p_vaddr = 0x1000;
      phdr[0].p_filesz = 0x40;
      struct ProfilerImage image = {0, phdr, 1};
      return readableRange(&image, 0x1030, 0x11);
    }
    case 7: {
      ElfW(Phdr) phdr[1];
      memset(phdr, 0, sizeof(phdr));
      phdr[0].p_type = PT_LOAD;
      phdr[0].p_flags = PF_R;
      phdr[0].p_filesz = 0x40;
      struct ProfilerImage image = {UINTPTR_MAX - 0x10, phdr, 1};
      return readableRange(&image, image.bias, 1);
    }
    default:
      return OPERATION_LOOKUP_INVALID_TABLE;
  }
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativemem_NativememDdprofExclusionTest_checkSlotCapacityOverflow(
    JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  void* first_value = NULL;
  void* second_value = NULL;
  void** slots[2] = {NULL, NULL};
  int count = 0;
  if (appendOperationSlot(slots, &count, 1, &first_value) != 0) return -1;
  if (appendOperationSlot(slots, &count, 1, &second_value) != -1) return -2;
  return count == 1 && slots[0] == &first_value && slots[1] == NULL ? 0 : -3;
}

#endif /* __linux__ */
