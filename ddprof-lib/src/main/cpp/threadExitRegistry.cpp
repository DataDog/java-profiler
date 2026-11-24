// Copyright 2026, Datadog, Inc.

#include "threadExitRegistry.h"

#include <atomic>
#include <signal.h>

#include "threadLocalData.inline.h"

namespace {
constexpr int TABLE_SIZE = 4096;
constexpr int PROBE_LIMIT = 64;
// Both identity syscalls return positive values; zero denotes an unused slot.
std::atomic<uint64_t> tids[TABLE_SIZE];
static_assert(std::atomic<uint64_t>::is_always_lock_free, "Signal-context registry must be lock-free");

unsigned slotFor(uint64_t tid) {
    return (tid * 2654435761u) & (TABLE_SIZE - 1);
}

void mark(uint64_t tid) {
    // Deletion leaves holes. Search the entire window before reusing one so
    // repeated exit callbacks cannot install duplicate marks beyond a hole.
    if (ThreadExitRegistry::contains(tid)) return;
    unsigned slot = slotFor(tid);
    // Membership publishes no dependent data; same-thread marks/consults need
    // no ordering. Atomic RMWs arbitrate slots shared with other identities.
    for (int probe = 0; probe < PROBE_LIMIT; probe++) {
        unsigned index = (slot + probe) & (TABLE_SIZE - 1);
        uint64_t occupant = 0;
        if (tids[index].compare_exchange_strong(occupant, tid, std::memory_order_relaxed)) return;
    }
    // Marks persist across lifetimes. A full window lets one insertion evict
    // even a recent mark; it need not contain 64 concurrently exiting threads.
    tids[slot].store(tid, std::memory_order_relaxed);
}
}  // namespace

#ifdef UNIT_TEST
void (*ThreadExitRegistry::beforeClearForTest)() = nullptr;
void ThreadExitRegistry::resetForTest() {
    for (auto& tid : tids) tid.store(0, std::memory_order_relaxed);
}
void ThreadExitRegistry::markForTest(uint64_t tid) { mark(tid); }
#endif

void ThreadExitRegistry::markCurrent() { mark(currentId()); }
void ThreadExitRegistry::clearCurrent() { clear(currentId()); }

void ThreadExitRegistry::clear(uint64_t tid) {
    unsigned slot = slotFor(tid);
    for (int probe = 0; probe < PROBE_LIMIT; probe++) {
        unsigned index = (slot + probe) & (TABLE_SIZE - 1);
        uint64_t occupant = tids[index].load(std::memory_order_relaxed);
        if (occupant == tid) {
#ifdef UNIT_TEST
            if (beforeClearForTest != nullptr) beforeClearForTest();
#endif
            // An eviction may replace this slot between the load and removal.
            tids[index].compare_exchange_strong(occupant, 0, std::memory_order_relaxed);
            return;
        }
    }
}

bool ThreadExitRegistry::contains(uint64_t tid) {
    unsigned slot = slotFor(tid);
    // Cleared slots do not terminate a probe chain. Scan all 64 positions,
    // including holes, so deletion cannot hide another identity's mark.
    for (int probe = 0; probe < PROBE_LIMIT; probe++) {
        unsigned index = (slot + probe) & (TABLE_SIZE - 1);
        if (tids[index].load(std::memory_order_relaxed) == tid) return true;
    }
    return false;
}

bool ThreadExitRegistry::isCurrentExiting() {
    uint64_t tid = currentId();
    if (!contains(tid)) return false;
    // TLS acquisition clears stale marks, so a mark beside live TLS is this thread's.
    if (ProfiledThread::current() != nullptr) return true;
    sigset_t mask;
    if (pthread_sigmask(SIG_BLOCK, nullptr, &mask) != 0 ||
        (sigismember(&mask, SIGPROF) == 1 && sigismember(&mask, SIGVTALRM) == 1)) {
        return true;
    }
    clear(tid);
    return false;
}
