/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GTEST_CRASH_HANDLER_H
#define GTEST_CRASH_HANDLER_H

#include <signal.h>
#include <unistd.h>
#include <sys/ucontext.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

// Platform detection for execinfo.h availability
#if defined(__GLIBC__) || (defined(__APPLE__) && defined(__MACH__)) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #define HAVE_EXECINFO_H 1
    #include <execinfo.h>
#else
    #define HAVE_EXECINFO_H 0
    // Fallback declarations for platforms without execinfo.h
#endif

/**
 * Shared crash handler for all gtest files.
 * Provides detailed crash reporting with backtrace and register information.
 * Use installGtestCrashHandler() to install and restoreDefaultSignalHandlers() to cleanup.
 */

// Global crash handler for detailed debugging of segfaults
inline void gtestCrashHandler(int sig, siginfo_t *info, void *context, const char* test_name) {
    // Prevent recursive calls
    static volatile sig_atomic_t in_crash_handler = 0;
    if (in_crash_handler) {
        // Already in crash handler - just exit to prevent infinite loop
        _exit(128 + sig);
    }
    in_crash_handler = 1;
    
    // Use async-signal-safe functions only
    const char* signal_names[] = {
        "UNKNOWN", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS",
        "SIGFPE", "SIGKILL", "SIGSEGV", "SIGUSR1", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGUSR2"
    };
    
    const char* signal_name = (sig >= 1 && sig <= 15) ? signal_names[sig] : "UNKNOWN";
    
    // Write crash info to stderr (async-signal-safe)
    write(STDERR_FILENO, "\n=== GTEST CRASH: ", 19);
    write(STDERR_FILENO, test_name, strlen(test_name));
    write(STDERR_FILENO, " ===\n", 6);
    
    // Signal type
    write(STDERR_FILENO, "Signal: ", 8);
    write(STDERR_FILENO, signal_name, strlen(signal_name));
    
    // Format signal number
    char sig_buf[32];
    snprintf(sig_buf, sizeof(sig_buf), " (%d)\n", sig);
    write(STDERR_FILENO, sig_buf, strlen(sig_buf));
    
    // Fault address for memory access violations
    if (sig == SIGSEGV || sig == SIGBUS) {
        write(STDERR_FILENO, "Fault address: 0x", 17);
        char addr_buf[32];
        snprintf(addr_buf, sizeof(addr_buf), "%lx\n", (unsigned long)info->si_addr);
        write(STDERR_FILENO, addr_buf, strlen(addr_buf));
    }
    
    // Thread ID
    write(STDERR_FILENO, "Thread ID: ", 11);
    char tid_buf[32];
    snprintf(tid_buf, sizeof(tid_buf), "%d\n", getpid());
    write(STDERR_FILENO, tid_buf, strlen(tid_buf));
    
    // Backtrace (if available)
    write(STDERR_FILENO, "\nBacktrace:\n", 12);
#if HAVE_EXECINFO_H
    void *buffer[64];
    int nptrs = backtrace(buffer, 64);
    
    // Use backtrace_symbols_fd which is async-signal-safe
    backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);
#else
    write(STDERR_FILENO, "  [Backtrace not available on this platform]\n", 45);
#endif
    
    // Register state (platform specific)
#ifdef __APPLE__
    ucontext_t *uctx = (ucontext_t *)context;
    if (uctx && uctx->uc_mcontext) {
        write(STDERR_FILENO, "\nRegister state:\n", 17);
        char reg_buf[128];
        #ifdef __x86_64__
            snprintf(reg_buf, sizeof(reg_buf), "RIP: 0x%llx, RSP: 0x%llx\n", 
                    uctx->uc_mcontext->__ss.__rip, uctx->uc_mcontext->__ss.__rsp);
        #elif defined(__aarch64__)
            snprintf(reg_buf, sizeof(reg_buf), "PC: 0x%llx, SP: 0x%llx\n",
                    uctx->uc_mcontext->__ss.__pc, uctx->uc_mcontext->__ss.__sp);
        #endif
        write(STDERR_FILENO, reg_buf, strlen(reg_buf));
    }
#endif
    
    write(STDERR_FILENO, "\n=== END CRASH INFO ===\n", 25);
    
    // Ensure output is flushed
    fsync(STDERR_FILENO);
    
    // Don't interfere with AddressSanitizer - just exit cleanly
    _exit(128 + sig);
}

// Template wrapper to pass test name to crash handler
template<const char* TestName>
void specificCrashHandler(int sig, siginfo_t *info, void *context) {
    gtestCrashHandler(sig, info, context, TestName);
}

// Install crash handler for debugging
template<const char* TestName>
void installGtestCrashHandler() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;  // Get detailed info, keep handler active
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = specificCrashHandler<TestName>;
    
    // Install for various crash signals
    sigaction(SIGSEGV, &sa, nullptr);
    sigaction(SIGBUS, &sa, nullptr);
    sigaction(SIGABRT, &sa, nullptr);
    sigaction(SIGFPE, &sa, nullptr);
    sigaction(SIGILL, &sa, nullptr);
}

// Restore default signal handlers
inline void restoreDefaultSignalHandlers() {
    signal(SIGSEGV, SIG_DFL);
    signal(SIGBUS, SIG_DFL);
    signal(SIGABRT, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    signal(SIGILL, SIG_DFL);
}

#endif // GTEST_CRASH_HANDLER_H