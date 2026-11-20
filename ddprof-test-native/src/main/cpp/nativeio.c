/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#define _GNU_SOURCE
#include <jni.h>

#if defined(__linux__)
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <link.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>

/* Read actual installed JDK import slots, not exported test-only profiler APIs. */
struct imports {
    void *functions[4];
};

static void collect_relocations(struct imports *imports, ElfW(Addr) base,
                                const ElfW(Rela) *relocations, size_t bytes,
                                const ElfW(Sym) *symbols, const char *strings) {
    static const char *names[] = {"send", "recv", "write", "read"};
    for (size_t index = 0; index < bytes / sizeof(*relocations); index++) {
        const ElfW(Rela) *relocation = relocations + index;
        unsigned type = ELF64_R_TYPE(relocation->r_info);
#if defined(__x86_64__)
        if (type != R_X86_64_JUMP_SLOT && type != R_X86_64_GLOB_DAT) continue;
#elif defined(__aarch64__)
        if (type != R_AARCH64_JUMP_SLOT && type != R_AARCH64_GLOB_DAT) continue;
#else
#error Unsupported native I/O qualification architecture
#endif
        const char *name = strings + symbols[ELF64_R_SYM(relocation->r_info)].st_name;
        for (int op = 0; op < 4; op++) {
            if (strcmp(name, names[op]) == 0) {
                void **slot = (void **)(base + relocation->r_offset);
                void *function = __atomic_load_n(slot, __ATOMIC_ACQUIRE);
                /* A libc import is not evidence that the profiler hook ran. */
                if (function != NULL && function != dlsym(RTLD_DEFAULT, name)) {
                    imports->functions[op] = function;
                }
            }
        }
    }
}

static ElfW(Addr) dynamic_pointer(ElfW(Addr) base, ElfW(Addr) value) {
    return value < base ? base + value : value;
}

static int collect_imports(struct dl_phdr_info *info, size_t size, void *data) {
    const char *name = strrchr(info->dlpi_name, '/');
    /* IBM Java 8 reaches libc through libjava's JCL bridge; only hooked slots are recorded,
     * so an unpatched OpenJDK libjava contributes nothing. */
    if (name == NULL || (strcmp(name, "/libnet.so") != 0 && strcmp(name, "/libnio.so") != 0 &&
                         strcmp(name, "/libjava.so") != 0)) return 0;
    ElfW(Addr) base = info->dlpi_addr;
    const ElfW(Dyn) *dynamic = NULL;
    for (int index = 0; index < info->dlpi_phnum; index++) {
        if (info->dlpi_phdr[index].p_type == PT_DYNAMIC) {
            dynamic = (const ElfW(Dyn) *)(base + info->dlpi_phdr[index].p_vaddr);
        }
    }
    if (dynamic == NULL) return 0;
    const ElfW(Sym) *symbols = NULL;
    const char *strings = NULL;
    const ElfW(Rela) *relocations = NULL, *plt = NULL;
    size_t bytes = 0, plt_bytes = 0;
    long plt_type = 0;
    for (; dynamic->d_tag != DT_NULL; dynamic++) {
        ElfW(Addr) pointer = dynamic_pointer(base, dynamic->d_un.d_ptr);
        switch (dynamic->d_tag) {
            case DT_SYMTAB: symbols = (const ElfW(Sym) *)pointer; break;
            case DT_STRTAB: strings = (const char *)pointer; break;
            case DT_RELA: relocations = (const ElfW(Rela) *)pointer; break;
            case DT_RELASZ: bytes = dynamic->d_un.d_val; break;
            case DT_JMPREL: plt = (const ElfW(Rela) *)pointer; break;
            case DT_PLTRELSZ: plt_bytes = dynamic->d_un.d_val; break;
            case DT_PLTREL: plt_type = dynamic->d_un.d_val; break;
        }
    }
    if (symbols != NULL && strings != NULL) {
        if (relocations != NULL) collect_relocations(data, base, relocations, bytes, symbols, strings);
        if (plt != NULL && plt_type == DT_RELA) collect_relocations(data, base, plt, plt_bytes, symbols, strings);
    }
    return 0;
}

/* Exercise the production import target while a real profiler/JVM is running.
 * A /dev/full stdout makes DEBUG instrumentation observably alter errno unless
 * both pre-original work and sampled recording are guarded. No JVM identity is
 * synthesized and no production originals/active flags are overridden.
 * Returns -2 when only the low-FD pass ran and passed.
 */
JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativesocket_NativeIoErrnoTest_exerciseImports(JNIEnv *env, jclass cls) {
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) != 0) return 28;
    /* F_DUPFD to 65536 needs a higher limit; the low-FD pass runs regardless. */
    int passes = limit.rlim_max > 65536u ? 2 : 1;
    struct imports imports = {{NULL, NULL, NULL, NULL}};
    dl_iterate_phdr(collect_imports, &imports);
    for (int op = 0; op < 4; op++) if (imports.functions[op] == NULL) return 10 + op;
    int saved_stdout = dup(STDOUT_FILENO);
    int full = open("/dev/full", O_WRONLY | O_CLOEXEC);
    if (saved_stdout < 0 || full < 0) {
        if (saved_stdout >= 0) close(saved_stdout);
        if (full >= 0) close(full);
        return 20;
    }
    fflush(stdout);
    if (dup2(full, STDOUT_FILENO) < 0) {
        close(saved_stdout);
        close(full);
        return 21;
    }
    close(full);
    int failure = 0;
    for (int high = 0; high < passes && failure == 0; high++) {
        int sockets[2];
        if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, sockets) != 0) { failure = 22; break; }
        struct timeval timeout = {2, 0};
        if (setsockopt(sockets[0], SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0 ||
            setsockopt(sockets[0], SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) != 0 ||
            setsockopt(sockets[1], SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0 ||
            setsockopt(sockets[1], SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) != 0) {
            close(sockets[0]); close(sockets[1]); failure = 27; break;
        }
        int target = fcntl(sockets[0], F_DUPFD_CLOEXEC, high ? 65536 : 0);
        close(sockets[0]);
        if (target < 0) { close(sockets[1]); failure = 23; break; }
        for (int iteration = 0; iteration < 128 && failure == 0; iteration++) {
            for (int op = 0; op < 4; op++) {
                char byte = 'x';
                if (op == 1 || op == 3) {
                    if (write(sockets[1], &byte, 1) != 1) { failure = 24; break; }
                }
                errno = E2BIG;
                ssize_t result;
                if (op < 2) result = ((ssize_t (*)(int, void *, size_t, int))imports.functions[op])(target, &byte, 1, 0);
                else result = ((ssize_t (*)(int, void *, size_t))imports.functions[op])(target, &byte, 1);
                int observed_errno = errno;
                if (result != 1 || observed_errno != E2BIG) { failure = 30 + op; break; }
                if (op == 0 || op == 2) {
                    if (read(sockets[1], &byte, 1) != 1) { failure = 25; break; }
                }
            }
        }
        close(target);
        close(sockets[1]);
    }
    fflush(stdout);
    if (dup2(saved_stdout, STDOUT_FILENO) < 0) failure = 26;
    close(saved_stdout);
    clearerr(stdout);
    return failure == 0 && passes == 1 ? -2 : failure;
}
static void pinned_read_failure(JNIEnv *env, const char *message) {
    jclass error = (*env)->FindClass(env, "java/lang/IllegalStateException");
    if (error != NULL) {
        (*env)->ThrowNew(env, error, message);
        (*env)->DeleteLocalRef(env, error);
    }
}

JNIEXPORT jintArray JNICALL
Java_com_datadoghq_profiler_wallclock_NativeSocketTaskBlockTest_openPinnedSocket0(JNIEnv *env, jclass cls) {
    int sockets[2];
    if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, sockets) != 0) {
        pinned_read_failure(env, "socketpair failed");
        return NULL;
    }
    struct timeval timeout = {5, 0};
    if (setsockopt(sockets[0], SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0) {
        close(sockets[0]); close(sockets[1]);
        pinned_read_failure(env, "socket timeout setup failed");
        return NULL;
    }
    jintArray result = (*env)->NewIntArray(env, 2);
    if (result == NULL) {
        close(sockets[0]); close(sockets[1]);
        return NULL;
    }
    jint values[2] = {sockets[0], sockets[1]};
    (*env)->SetIntArrayRegion(env, result, 0, 2, values);
    return result;
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_wallclock_NativeSocketTaskBlockTest_pinnedRead0(
        JNIEnv *env, jclass cls, jint fd, jlongArray observed, jobject entered) {
    struct imports imports = {{NULL, NULL, NULL, NULL}};
    dl_iterate_phdr(collect_imports, &imports);
    if (imports.functions[3] == NULL) {
        pinned_read_failure(env, "no installed JDK read hook");
        return -1;
    }
    jclass thread_class = (*env)->FindClass(env, "java/lang/Thread");
    if (thread_class == NULL) return -1;
    jmethodID carrier_method = (*env)->GetStaticMethodID(env, thread_class, "currentCarrierThread", "()Ljava/lang/Thread;");
    if (carrier_method == NULL) { (*env)->DeleteLocalRef(env, thread_class); return -1; }
    jobject carrier = (*env)->CallStaticObjectMethod(env, thread_class, carrier_method);
    if (carrier == NULL) { (*env)->DeleteLocalRef(env, thread_class); return -1; }
    jmethodID id_method = (*env)->GetMethodID(env, thread_class, "getId", "()J");
    if (id_method == NULL) {
        (*env)->DeleteLocalRef(env, carrier); (*env)->DeleteLocalRef(env, thread_class);
        return -1;
    }
    /* Observe the actual carrier through the JDK, independently of profiler TLS/JFR. */
    jlong identity[2] = {(*env)->CallLongMethod(env, carrier, id_method), syscall(SYS_gettid)};
    (*env)->DeleteLocalRef(env, carrier);
    (*env)->DeleteLocalRef(env, thread_class);
    if ((*env)->ExceptionCheck(env)) return -1;
    (*env)->SetLongArrayRegion(env, observed, 0, 2, identity);
    jclass latch_class = (*env)->GetObjectClass(env, entered);
    if (latch_class == NULL) return -1;
    jmethodID count_down = (*env)->GetMethodID(env, latch_class, "countDown", "()V");
    if (count_down != NULL) (*env)->CallVoidMethod(env, entered, count_down);
    (*env)->DeleteLocalRef(env, latch_class);
    if (count_down == NULL || (*env)->ExceptionCheck(env)) return -1;
    jmethodID validate = (*env)->GetStaticMethodID(env, cls, "assertCleanPinnedReadContext", "()V");
    if (validate == NULL) return -1;
    (*env)->CallStaticVoidMethod(env, cls, validate);
    if ((*env)->ExceptionCheck(env)) return -1;
    char byte = 0;
    ssize_t result = ((ssize_t (*)(int, void *, size_t))imports.functions[3])(fd, &byte, 1);
    int read_errno = errno;
    jlong diagnostics[3] = {result, read_errno, byte};
    (*env)->SetLongArrayRegion(env, observed, 2, 3, diagnostics);
    return result == 1 && byte == 1 ? 1 : -1;
}

JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_wallclock_NativeSocketTaskBlockTest_releasePinnedRead0(JNIEnv *env, jclass cls, jint fd) {
    char byte = 1;
    return write(fd, &byte, 1);
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_NativeSocketTaskBlockTest_closePinnedSocket0(JNIEnv *env, jclass cls, jint fd) {
    if (close(fd) != 0) pinned_read_failure(env, "socket close failed");
}

#else
JNIEXPORT jint JNICALL
Java_com_datadoghq_profiler_nativesocket_NativeIoErrnoTest_exerciseImports(JNIEnv *env, jclass cls) {
    return -1;
}
#endif
