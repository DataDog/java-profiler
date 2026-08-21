/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t unloadable_read(int fd, void* buffer, size_t size) {
    return read(fd, buffer, size);
}
