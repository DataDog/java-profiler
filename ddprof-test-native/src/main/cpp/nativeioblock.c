/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#define _GNU_SOURCE

#include <jni.h>

#if defined(__linux__)

#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

struct delayed_write_args {
    int fd;
    int delay_ms;
};

struct delayed_connect_args {
    int port;
    int delay_ms;
};

static void sleep_ms(int delay_ms) {
    if (delay_ms <= 0) {
        return;
    }
    struct timespec ts;
    ts.tv_sec = delay_ms / 1000;
    ts.tv_nsec = (long)(delay_ms % 1000) * 1000000L;
    while (nanosleep(&ts, &ts) != 0 && errno == EINTR) {
    }
}

static void throw_io_exception(JNIEnv* env, const char* operation) {
    jclass exception_class = (*env)->FindClass(env, "java/io/IOException");
    if (exception_class == NULL) {
        return;
    }
    char message[256];
    snprintf(message, sizeof(message), "%s failed: %s", operation, strerror(errno));
    (*env)->ThrowNew(env, exception_class, message);
}

static void throw_out_of_memory(JNIEnv* env) {
    jclass exception_class = (*env)->FindClass(env, "java/lang/OutOfMemoryError");
    if (exception_class != NULL) {
        (*env)->ThrowNew(env, exception_class, "native allocation failed");
    }
}

static void* delayed_write(void* arg) {
    struct delayed_write_args* args = (struct delayed_write_args*)arg;
    sleep_ms(args->delay_ms);
    uint64_t value = 1;
    while (write(args->fd, &value, sizeof(value)) < 0 && errno == EINTR) {
    }
    close(args->fd);
    free(args);
    return NULL;
}

static void* delayed_connect(void* arg) {
    struct delayed_connect_args* args = (struct delayed_connect_args*)arg;
    sleep_ms(args->delay_ms);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd >= 0) {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        addr.sin_port = htons((uint16_t)args->port);
        connect(fd, (struct sockaddr*)&addr, sizeof(addr));
        close(fd);
    }
    free(args);
    return NULL;
}

static int start_delayed_write(JNIEnv* env, int fd, int delay_ms) {
    struct delayed_write_args* args =
        (struct delayed_write_args*)malloc(sizeof(struct delayed_write_args));
    if (args == NULL) {
        throw_out_of_memory(env);
        return -1;
    }
    args->fd = fd;
    args->delay_ms = delay_ms;
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, delayed_write, args);
    if (rc != 0) {
        free(args);
        errno = rc;
        throw_io_exception(env, "pthread_create");
        return -1;
    }
    pthread_detach(thread);
    return 0;
}

static int start_delayed_connect(JNIEnv* env, int port, int delay_ms) {
    struct delayed_connect_args* args =
        (struct delayed_connect_args*)malloc(sizeof(struct delayed_connect_args));
    if (args == NULL) {
        throw_out_of_memory(env);
        return -1;
    }
    args->port = port;
    args->delay_ms = delay_ms;
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, delayed_connect, args);
    if (rc != 0) {
        free(args);
        errno = rc;
        throw_io_exception(env, "pthread_create");
        return -1;
    }
    pthread_detach(thread);
    return 0;
}

static void block_with_poll_like(JNIEnv* env, jint delay_ms, int use_ppoll) {
    int fds[2];
    if (pipe(fds) != 0) {
        throw_io_exception(env, "pipe");
        return;
    }
    if (start_delayed_write(env, fds[1], delay_ms) != 0) {
        close(fds[0]);
        close(fds[1]);
        return;
    }

    struct pollfd pfd;
    pfd.fd = fds[0];
    pfd.events = POLLIN;
    pfd.revents = 0;
    int rc;
    if (use_ppoll) {
        rc = ppoll(&pfd, 1, NULL, NULL);
    } else {
        rc = poll(&pfd, 1, -1);
    }
    close(fds[0]);
    if (rc < 0) {
        throw_io_exception(env, use_ppoll ? "ppoll" : "poll");
    }
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingPpoll(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    block_with_poll_like(env, delay_ms, 1);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingPselect(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    int fds[2];
    if (pipe(fds) != 0) {
        throw_io_exception(env, "pipe");
        return;
    }
    if (start_delayed_write(env, fds[1], delay_ms) != 0) {
        close(fds[0]);
        close(fds[1]);
        return;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fds[0], &readfds);
    int rc = pselect(fds[0] + 1, &readfds, NULL, NULL, NULL, NULL);
    close(fds[0]);
    if (rc < 0) {
        throw_io_exception(env, "pselect");
    }
}

static void block_with_epoll(JNIEnv* env, jint delay_ms, int use_pwait) {
    int event_fd = eventfd(0, EFD_CLOEXEC);
    if (event_fd < 0) {
        throw_io_exception(env, "eventfd");
        return;
    }
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        close(event_fd);
        throw_io_exception(env, "epoll_create1");
        return;
    }
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = event_fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, event_fd, &event) != 0) {
        close(epfd);
        close(event_fd);
        throw_io_exception(env, "epoll_ctl");
        return;
    }
    if (start_delayed_write(env, event_fd, delay_ms) != 0) {
        close(epfd);
        close(event_fd);
        return;
    }

    struct epoll_event out_event;
    int rc;
    if (use_pwait) {
        rc = epoll_pwait(epfd, &out_event, 1, -1, NULL);
    } else {
        rc = epoll_wait(epfd, &out_event, 1, -1);
    }
    close(epfd);
    if (rc < 0) {
        throw_io_exception(env, use_pwait ? "epoll_pwait" : "epoll_wait");
    }
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingEpollWait(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    block_with_epoll(env, delay_ms, 0);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingEpollPwait(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    block_with_epoll(env, delay_ms, 1);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingAccept4(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw_io_exception(env, "socket");
        return;
    }
    int one = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = 0;
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ||
        listen(server_fd, 1) != 0) {
        close(server_fd);
        throw_io_exception(env, "bind/listen");
        return;
    }

    socklen_t addr_len = sizeof(addr);
    if (getsockname(server_fd, (struct sockaddr*)&addr, &addr_len) != 0) {
        close(server_fd);
        throw_io_exception(env, "getsockname");
        return;
    }
    if (start_delayed_connect(env, ntohs(addr.sin_port), delay_ms) != 0) {
        close(server_fd);
        return;
    }

    int accepted_fd = accept4(server_fd, NULL, NULL, SOCK_CLOEXEC);
    if (accepted_fd >= 0) {
        close(accepted_fd);
    }
    close(server_fd);
    if (accepted_fd < 0) {
        throw_io_exception(env, "accept4");
    }
}

#else

static void unsupported(JNIEnv* env) {
    jclass exception_class = (*env)->FindClass(env, "java/lang/UnsupportedOperationException");
    if (exception_class != NULL) {
        (*env)->ThrowNew(env, exception_class, "Native I/O block helper is Linux-only");
    }
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingAccept4(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    (void)delay_ms;
    unsupported(env);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingPpoll(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    (void)delay_ms;
    unsupported(env);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingPselect(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    (void)delay_ms;
    unsupported(env);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingEpollWait(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    (void)delay_ms;
    unsupported(env);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeIoBlockHelper_blockingEpollPwait(
    JNIEnv* env, jclass clazz, jint delay_ms) {
    (void)clazz;
    (void)delay_ms;
    unsupported(env);
}

#endif
