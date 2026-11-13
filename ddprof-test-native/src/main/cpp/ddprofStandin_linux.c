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

struct ProfilerImage {
  uintptr_t bias;
  const ElfW(Phdr)* phdr;
  ElfW(Half) phnum;
};

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

/* Locates the libjavaProfiler image and records every JUMP_SLOT/GLOB_DAT
 * relocation for the five allocation symbols. Returns 0 on success, -1 when
 * the image or the dynamic metadata cannot be inspected. */
static int locateOperationSlots(struct ProfilerImage* image) {
  memset(operation_slot_count, 0, sizeof(operation_slot_count));
  const ElfW(Phdr)* dynamic = NULL;
  for (ElfW(Half) i = 0; i < image->phnum; i++) {
    if (image->phdr[i].p_type == PT_DYNAMIC) {
      dynamic = &image->phdr[i];
      break;
    }
  }
  if (dynamic == NULL) return -1;
  const ElfW(Dyn)* dyn = (const ElfW(Dyn)*)(image->bias + dynamic->p_vaddr);

  uintptr_t jmprel = 0;
  size_t pltrelsz = 0;
  uintptr_t rela = 0;
  size_t relasz = 0;
  const ElfW(Sym)* symtab = NULL;
  const char* strtab = NULL;
  for (const ElfW(Dyn)* d = dyn; d->d_tag != DT_NULL; d++) {
    switch (d->d_tag) {
      case DT_JMPREL:
        jmprel = (uintptr_t)d->d_un.d_ptr;
        break;
      case DT_PLTRELSZ:
        pltrelsz = (size_t)d->d_un.d_val;
        break;
      case DT_RELA:
        rela = (uintptr_t)d->d_un.d_ptr;
        break;
      case DT_RELASZ:
        relasz = (size_t)d->d_un.d_val;
        break;
      case DT_SYMTAB:
        symtab = (const ElfW(Sym)*)d->d_un.d_ptr;
        break;
      case DT_STRTAB:
        strtab = (const char*)d->d_un.d_ptr;
        break;
      default:
        break;
    }
  }
  if (symtab == NULL || strtab == NULL) return -1;

  for (int table = 0; table < 2; table++) {
    uintptr_t base = table == 0 ? jmprel : rela;
    size_t size = table == 0 ? pltrelsz : relasz;
    if (base == 0) continue;
    for (size_t off = 0; off + sizeof(ElfW(Rela)) <= size; off += sizeof(ElfW(Rela))) {
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
      const char* name = strtab + symtab[sym_index].st_name;
      for (int op = 0; op < 5; op++) {
        if (strcmp(name, OPERATION_NAMES[op]) != 0) continue;
        if (operation_slot_count[op] >= MAX_SLOTS_PER_OP) break;
        void** slot = (void**)(image->bias + entry->r_offset);
        operation_slots[op][operation_slot_count[op]++] = slot;
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

  for (int op = 0; op < 5; op++) {
    for (int i = 0; i < operation_slot_count[op]; i++) {
      void** slot = operation_slots[op][i];
      if (makeSlotWritable(slot) != 0) return -1;
      if (save_existing) {
        operation_saved[op][i] = *slot;
      }
      *slot = (void*)new_values[op];
    }
  }
  if (save_existing) {
    saved_malloc = (void* (*)(size_t))operation_saved[0][0];
    saved_calloc = (void* (*)(size_t, size_t))operation_saved[1][0];
    saved_realloc = (void* (*)(void*, size_t))operation_saved[2][0];
    saved_posix_memalign = (int (*)(void**, size_t, size_t))operation_saved[3][0];
    saved_aligned_alloc = (void* (*)(size_t, size_t))operation_saved[4][0];
  }
  return 0;
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativemem_DdprofStandin_install(JNIEnv* env, jclass clazz) {
  (void)env;
  (void)clazz;
  if (installed) return 0;
  /* Never rewrite a slot whose value is already a stand-in forwarder. */
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

#endif /* __linux__ */
