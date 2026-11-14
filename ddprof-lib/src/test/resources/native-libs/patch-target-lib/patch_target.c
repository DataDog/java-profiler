/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <pthread.h>
#include <unistd.h>

// Imports write() and pthread_create() via the PLT, giving LibraryPatcher's
// socket and pthread_create patching a GOT slot each. Plain C on purpose:
// g++-compiled DSOs can carry STB_GNU_UNIQUE symbols, which make glibc treat
// the DSO as NODELETE and would keep dlclose() from ever unmapping it.
ssize_t patch_target_write(int fd, const void* buf, size_t len) {
    return write(fd, buf, len);
}

int patch_target_spawn(pthread_t* thread, void* (*routine)(void*)) {
    return pthread_create(thread, NULL, routine, NULL);
}
