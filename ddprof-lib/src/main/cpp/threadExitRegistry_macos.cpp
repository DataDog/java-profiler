// Copyright 2026, Datadog, Inc.

#ifdef __APPLE__

#include "threadExitRegistry.h"
#include <sys/syscall.h>

// Darwin's libc syscall() returns int, truncating thread_selfid's 64-bit result.
// XNU syscall_sw.h uses arm64 svc 0x80 and x64 UNIX class (2 << 24).
uint64_t ThreadExitRegistry::currentId() {
#ifdef __aarch64__
    register uint64_t result asm("x0");
    register uint64_t number asm("x16") = SYS_thread_selfid;
    asm volatile("svc #0x80" : "=r"(result), "+r"(number) : : "x1", "cc", "memory");
#elif defined(__x86_64__)
    constexpr uint64_t UNIX_SYSCALL_CLASS = 2ull << 24;
    uint64_t result = UNIX_SYSCALL_CLASS | SYS_thread_selfid;
    asm volatile("syscall" : "+a"(result) : : "rcx", "r11", "rdx", "cc", "memory");
#endif
    return result;
}

#endif // __APPLE__
