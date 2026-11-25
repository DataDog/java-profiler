/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Native fixture for the native-memory admission tests. One source, variants
// selected at compile time by the Makefile:
//   -DMARK_START / -DMARK_STOP  define the named marker as an exported
//                               STT_FUNC symbol that increments its counter
//   -DMARK_OBJECT               define the start marker as STT_OBJECT instead
//   -DMARK_IFUNC                define the start marker as STT_GNU_IFUNC
//                               (resolver increments its own counter; glibc only)
//   -DREFERENCE_MARKERS         only take the markers' addresses, leaving them
//                               undefined so they resolve from a dependency
// Every variant exports hook functions that call the imported malloc and
// aligned_alloc, so a regressed nested probe would write this library's GOT
// slots, and exported counters the tests read to prove classification never
// executes a marker or an IFUNC resolver.

#include <stdint.h>
#include <stdlib.h>

__attribute__((visibility("default"))) uint64_t fixture_start_marker_calls;
__attribute__((visibility("default"))) uint64_t fixture_stop_marker_calls;
__attribute__((visibility("default"))) uint64_t fixture_resolver_calls;

#if defined(MARK_START)

__attribute__((visibility("default"))) void ddprof_start_profiling(void) {
    fixture_start_marker_calls++;
}

#elif defined(MARK_OBJECT)

// Same name, wrong ELF symbol type: the classifier must report the image as
// wrong-kind, never as a recognized ddprof image.
__attribute__((visibility("default"))) char ddprof_start_profiling[1];

#elif defined(MARK_IFUNC)

// STT_GNU_IFUNC: the symbol's type is not STT_FUNC, and the resolver must
// never run during classification (glibc resolves it at relocation time
// anyway; the counter exists so tests can prove the admission check did not
// add calls). The ifunc attribute makes the exported symbol GLOBAL in
// .dynsym, so the classifier visits it as a wrong-kind match rather than
// ignoring it as a local symbol. glibc/gcc only: musl has no ifunc support.
static void fixture_start_target(void) { fixture_start_marker_calls++; }
static void (*fixture_start_resolver(void))(void) {
    fixture_resolver_calls++;
    return fixture_start_target;
}
void ddprof_start_profiling(void) __attribute__((ifunc("fixture_start_resolver")));

#endif

#if defined(MARK_STOP)

__attribute__((visibility("default"))) void ddprof_stop_profiling(void) {
    fixture_stop_marker_calls++;
}

#endif

#if defined(REFERENCE_MARKERS)

// Takes the markers' addresses only: both names end up as undefined dynamic
// symbols resolved from the dependency fixture. The classifier must ignore
// undefined imports and not recognize the image. The pointers are never
// called.
extern void ddprof_start_profiling(void);
extern void ddprof_stop_profiling(void);
__attribute__((visibility("default"))) void (*const fixture_start_ref)(void) =
    &ddprof_start_profiling;
__attribute__((visibility("default"))) void (*const fixture_stop_ref)(void) =
    &ddprof_stop_profiling;

#endif

// Forwarding hooks: the allocation imports this test-owned image depends on.
__attribute__((visibility("default"))) void* fixture_malloc_hook(size_t size) {
    return malloc(size);
}

__attribute__((visibility("default"))) void* fixture_calloc_hook(size_t count, size_t size) {
    return calloc(count, size);
}

__attribute__((visibility("default"))) void* fixture_realloc_hook(void* address, size_t size) {
    return realloc(address, size);
}

__attribute__((visibility("default"))) int fixture_posix_memalign_hook(void** memptr, size_t alignment, size_t size) {
    return posix_memalign(memptr, alignment, size);
}

__attribute__((visibility("default"))) void* fixture_aligned_alloc_hook(size_t alignment,
                                                                        size_t size) {
    return aligned_alloc(alignment, size);
}
