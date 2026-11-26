// Copyright 2026, Datadog, Inc.

#ifndef _THREAD_EXIT_REGISTRY_H
#define _THREAD_EXIT_REGISTRY_H

#include <cstdint>

// Bounded membership of exiting thread identities, consulted before crash-handler TLS.
// Registration clears stale identities; pressure eviction can reopen the bootstrap window.
class ThreadExitRegistry {
public:
    // Linux gettid and Darwin thread_selfid use raw syscalls, without TLS or Mach-port ownership.
    // Registry identities are separate from OS::threadId(), whose Darwin consumers need Mach ports.
    static uint64_t currentId();
    static void markCurrent();
    static void clearCurrent();
    static void clear(uint64_t tid);
    static bool contains(uint64_t tid);
    // Async-signal-safe; for malloc hooks, not crash handlers (reads TLS when marked).
    // A marked thread is exiting if it owns TLS or blocks profiling signals (every
    // mark site blocks first); otherwise the tid was reused and its mark is cleared.
    static bool isCurrentExiting();
#ifdef UNIT_TEST
    static void resetForTest();
    static void markForTest(uint64_t tid);
    static void (*beforeClearForTest)();
#endif
};

#endif // _THREAD_EXIT_REGISTRY_H
