/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
// Force pthread_setspecific into .rela.dyn with R_X86_64_GLOB_DAT.
int (*indirect_pthread_setspecific)(pthread_key_t, const void*);
// Force pthread_exit into .rela.dyn with R_X86_64_64.
void (*static_pthread_exit)(void*) = pthread_exit;
// Force read into .rela.plt (direct call) and two distinct .rela.dyn slots.
ssize_t (*static_read)(int, void*, size_t) = read;
ssize_t (*static_read_second)(int, void*, size_t) = read;
void* thread_function(void* arg) {
    printf("Thread running\n");
    return NULL;
}
// Not indended to be executed.
int reladyn() {
    pthread_t thread;
    pthread_key_t key;
    pthread_key_create(&key, NULL);
    // Direct call, forces into .rela.plt.
    pthread_create(&thread, NULL, thread_function, NULL);
    // Assign to a function pointer at runtime, forces into .rela.dyn as R_X86_64_GLOB_DAT.
    indirect_pthread_setspecific = pthread_setspecific;
    indirect_pthread_setspecific(key, "Thread-specific value");
    // Use pthread_exit via the static pointer, forces into .rela.dyn as R_X86_64_64.
    static_pthread_exit(NULL);
    return 0;
}

ssize_t reladyn_direct_read(int fd, void* buffer, size_t size) {
    return read(fd, buffer, size);
}

ssize_t reladyn_indirect_read(int fd, void* buffer, size_t size) {
    return static_read(fd, buffer, size);
}

ssize_t reladyn_second_indirect_read(int fd, void* buffer, size_t size) {
    return static_read_second(fd, buffer, size);
}
