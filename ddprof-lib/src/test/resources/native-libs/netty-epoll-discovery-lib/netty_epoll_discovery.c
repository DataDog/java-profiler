/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef FIXTURE_DIRECTORY_ANCHOR
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/epoll.h>
#include <time.h>

extern int epoll_pwait2(int, struct epoll_event*, int, const struct timespec*,
                        const sigset_t*) __attribute__((weak));

int JNI_OnLoad_netty_transport_native_epoll(void* vm, void* reserved) {
    (void)vm;
    (void)reserved;
    return 0x00010008;
}

void JNI_OnUnload_netty_transport_native_epoll(void* vm, void* reserved) {
    (void)vm;
    (void)reserved;
}

ssize_t netty_fixture_read(int fd, void* buffer, size_t size) {
    return read(fd, buffer, size);
}

int netty_fixture_epoll_pwait2(void) {
    if (epoll_pwait2 == NULL) {
        errno = ENOSYS;
        return -1;
    }
    struct epoll_event event;
    struct timespec timeout = {0, 1};
    return epoll_pwait2(-1, &event, 1, &timeout, NULL);
}
#else
void netty_fixture_directory_anchor(void) {}
#endif
