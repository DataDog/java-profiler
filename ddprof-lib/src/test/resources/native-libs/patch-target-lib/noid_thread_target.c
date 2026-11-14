/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <pthread.h>
#include <stdlib.h>

// The imported names have equal lengths. Align after the call so both real,
// correctly typed imports also give the same text/ELF layout despite their
// different argument counts. Tests inspect these imports without invoking them.
int noid_thread_entry(void* output) {
#ifdef IMPORT_POSIX
    int result = posix_memalign((void**)output, 16, 0);
#else
    int result = pthread_create((pthread_t*)output, NULL, NULL, NULL);
#endif
    __asm__ volatile(".p2align 6");
    return result;
}

// Keep DT_RELAENT present: the dynamic-import parser requires it before
// processing either the non-PLT relocations or the PLT import above.
int (*noid_thread_reference)(void*) = noid_thread_entry;
