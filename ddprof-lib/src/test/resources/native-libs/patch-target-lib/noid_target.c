/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <unistd.h>

// Built twice without a build-id, once calling write() and once read() (IMPORT).
// The two builds differ only in that import, so they can have identical program
// headers and an equal GOT layout: the same slot address holds write() in one
// and read() in the other.
ssize_t noid_entry(int fd, void* buf, size_t len) {
    return IMPORT(fd, buf, len);
}
