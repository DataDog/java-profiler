/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef FIXTURE_DIRECTORY_ANCHOR
// Production discovers the native-library directory through libjava.so.
int socket_patch_directory_anchor(void) {
    return 1;
}
#else
int socket_patch_thread(pthread_t* thread, void* (*routine)(void*), void* arg) {
    return pthread_create(thread, NULL, routine, arg);
}

ssize_t socket_patch_read(int fd, void* buffer, size_t size) {
    return read(fd, buffer, size);
}

ssize_t socket_patch_write(int fd, const void* buffer, size_t size) {
    return write(fd, buffer, size);
}
#endif
