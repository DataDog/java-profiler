#include <dlfcn.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "debug.h"

#ifdef __linux__
static int sighandler_tid = -1;

extern "C" void *__libc_malloc(size_t size);

/*
 * malloc and set_sighandler_tid must keep C linkage and default visibility:
 * malloc is interposed only when the dynamic linker resolves the unmangled
 * "malloc" name against this preloaded library, and Shims (debugSupport.cpp)
 * looks up "set_sighandler_tid" by the same unmangled name. The build compiles
 * with -fvisibility=hidden, so C++ mangling or hidden visibility silently
 * defeats both.
 */
extern "C" __attribute__((visibility("default"))) void *malloc(size_t size) {
    void *result = NULL;
    int handler_tid = __atomic_load_n(&sighandler_tid, __ATOMIC_ACQUIRE);
    int tid = handler_tid != -1 ? syscall(__NR_gettid) : -2;
    if (tid == handler_tid) {
        fprintf(stderr, "!!!! MALLOC in signal handler !!!\n");
        raise(SIGSEGV);
    } else {
        result = __libc_malloc(size);
    }

    return result;
}

extern "C" __attribute__((visibility("default"))) void set_sighandler_tid(int tid) {
    __atomic_store_n(&sighandler_tid, tid, __ATOMIC_RELEASE);
}
#endif // __linux__
