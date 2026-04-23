/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _OS_H
#define _OS_H

#include <functional>
#include <signal.h>
#include <stddef.h>
#include <sys/types.h>
#include "arch.h"


typedef void (*SigAction)(int, siginfo_t*, void*);
typedef void (*SigHandler)(int);
typedef void (*TimerCallback)(void*);

// Interrupt threads with this signal. The same signal is used inside JDK to interrupt I/O operations.
const int WAKEUP_SIGNAL = SIGIO;

enum ThreadState {
    THREAD_UNKNOWN,
    THREAD_RUNNING,
    THREAD_SLEEPING
};

struct ProcessInfo {
    int pid = 0;
    int ppid = 0;
    char name[16];           // Process name from /proc/{pid}/stats
    char cmdline[2048];      // Command line from /proc/{pid}/cmdline
    unsigned int uid = 0;    // User ID
    unsigned char state = 0; // Process state (R, S, D, Z, T, etc.)
    u64 start_time = 0;      // Process start time (milliseconds since epoch)

    // CPU & thread stats
    float cpu_user = 0;    // User CPU time (seconds)
    float cpu_system = 0;  // System CPU time (seconds)
    float cpu_percent = 0; // CPU utilization percentage
    int threads = 0;       // Number of threads

    // Memory stats (in bytes)
    u64 vm_size = 0;   // Total virtual memory size
    u64 vm_rss = 0;    // Resident memory size
    u64 rss_anon = 0;  // Resident anonymous memory
    u64 rss_files = 0; // Resident file mappings
    u64 rss_shmem = 0; // Resident shared memory

    // Page fault stats
    u64 minor_faults = 0; // Minor page faults (no I/O required)
    u64 major_faults = 0; // Major page faults (I/O required)

    // I/O stats
    u64 io_read = 0;  // KB read from storage
    u64 io_write = 0; // KB written to storage
};


class ThreadList {
  protected:
    u32 _index;
    u32 _count;

    ThreadList() : _index(0), _count(0) {
    }

  public:
    virtual ~ThreadList() {}

    u32 index() const { return _index; }
    u32 count() const { return _count; }

    bool hasNext() const {
        return _index < _count;
    }

    virtual int next() = 0;
    virtual void update() = 0;
};


// W^X memory support
class JitWriteProtection {
  private:
    u64 _prev;
    bool _restore;

  public:
    JitWriteProtection(bool enable);
    ~JitWriteProtection();
};


class OS {
  public:
    static const size_t page_size;
    static const size_t page_mask;
    static const long clock_ticks_per_sec;

    static u64 nanotime();
    static u64 micros();
    static u64 processStartTime();
    static void sleep(u64 nanos);
    static void uninterruptibleSleep(u64 nanos, volatile bool* flag);
    static u64 overrun(siginfo_t* siginfo);

    static u64 hton64(u64 x);
    static u64 ntoh64(u64 x);

    static int getMaxThreadId();
    static int processId();
    static int threadId();
    static const char* schedPolicy(int thread_id);
    static bool threadName(int thread_id, char* name_buf, size_t name_len);
    static ThreadState threadState(int thread_id);
    static u64 threadCpuTime(int thread_id);
    static ThreadList* listThreads();

    static bool isLinux();
    static bool isMusl();

    // Returns nullptr on sigaction() failure; returns the previous sa_sigaction otherwise.
    static SigAction installSignalHandler(int signo, SigAction action, SigHandler handler = NULL);
    static SigAction replaceCrashHandler(SigAction action);
    static int getProfilingSignal(int mode);
    static bool sendSignalToThread(int thread_id, int signo);

    // Send a signal to a specific thread with a cookie payload (synchronous —
    // the kernel queues it and returns). Uses rt_tgsigqueueinfo(2) on Linux;
    // receiver sees si_code == SI_QUEUE with the cookie in si_value.sival_ptr.
    // Engines use this when they need to discriminate their own signals from
    // foreign ones in the handler.
    static bool sendSignalWithCookie(int thread_id, int signo, void* cookie);

    // Accept-policy for a signal in a handler context. Async-signal-safe.
    //
    // Returns true iff the signal SHOULD be processed by the caller's engine:
    //   - origin check disabled (accept-all fallback, DDPROF_SIGNAL_ORIGIN_CHECK=0)
    //     → true
    //   - origin check enabled AND siginfo matches both expected_si_code and
    //     expected_cookie → true
    //   - otherwise → false
    //
    // Naming note: this is a policy predicate, NOT a pure "did this signal
    // come from us?" identification. A `false` answer means "forward this to
    // the chained handler"; a `true` answer means "process normally".
    // `expected_si_code` is SI_TIMER (timer_create) or SI_QUEUE
    // (sendSignalWithCookie).
    static bool shouldProcessSignal(siginfo_t* siginfo, int expected_si_code, void* expected_cookie);

    // Forwards a signal we decided not to process to the previously-installed
    // handler (as captured by installSignalHandler). When
    // DDPROF_FORWARD_APPLY_SIGMASK=1 is set, also reproduces the previous
    // handler's sa_mask so the chained handler sees the same signal-blocking
    // environment it would under normal kernel delivery.
    // Async-signal-safe on the fast path (no sa_mask applied). When
    // DDPROF_FORWARD_APPLY_SIGMASK=1 is set, the slow path uses raw
    // rt_sigprocmask syscalls which are async-signal-safe. The forwarded
    // handler's safety is the caller's concern.
    //
    // Drop semantics (Linux): signals whose previous disposition was SIG_DFL or
    // SIG_IGN are silently dropped — kernel-default termination is NOT reproduced
    // (terminating the process on every forwarded foreign signal would be worse
    // than ignoring it). Callers must not rely on default-action reproduction.
    //
    // macOS: always a no-op (rt_tgsigqueueinfo is unavailable so no cookie
    // discrimination is possible; all signals are accepted by the engine handler
    // and never forwarded). signalOriginCheckEnabled() returns false on macOS.
    static void forwardForeignSignal(int signo, siginfo_t* siginfo, void* ucontext);

    // Runtime feature flag: is the signal origin check active? Reads
    // DDPROF_SIGNAL_ORIGIN_CHECK env var and caches the result. Default on;
    // set to "false"/"0"/"off"/"no" to disable (regression tests only).
    // Callers running from signal-handler context must ensure
    // primeSignalOriginCheck() was called earlier from non-signal context
    // so the env-var getenv() cost is not paid during signal delivery.
    static bool signalOriginCheckEnabled();

    // Prime the signalOriginCheckEnabled() cache from non-signal context.
    // Called by engine start() paths before installing handlers so later
    // env-var overrides are picked up. Safe to call multiple times; no-op
    // after the first call unless forceReload=true (used only by unit tests).
    //
    // Without priming, the cache holds its safe defaults (origin check
    // enabled, sigmask chain disabled) — signals still classify correctly
    // even if priming never runs.
    static void primeSignalOriginCheck(bool forceReload = false);

    static void* safeAlloc(size_t size);
    static void safeFree(void* addr, size_t size);

    static bool getCpuDescription(char* buf, size_t size);
    static int getCpuCount();
    static u64 getProcessCpuTime(u64* utime, u64* stime);
    static u64 getTotalCpuTime(u64* utime, u64* stime);

    static int createMemoryFile(const char* name);
    static void copyFile(int src_fd, int dst_fd, off_t offset, size_t size);
    static void freePageCache(int fd, off_t start_offset);
    static int mprotect(void* addr, size_t size, int prot);

    static bool checkPreloaded();

    static u64 getSystemBootTime();
    static u64 getRamSize();
    static int getProcessIds(int* pids, int max_pids);
    static bool getBasicProcessInfo(int pid, ProcessInfo* info);
    static bool getDetailedProcessInfo(ProcessInfo* info);

    // DataDog-specific extensions
    static SigAction replaceSigsegvHandler(SigAction action);
    static SigAction replaceSigbusHandler(SigAction action);

    // Signal handler protection - prevents other libraries from overwriting our handlers
    static void protectSignalHandlers(SigAction segvHandler, SigAction busHandler);
    static SigAction getSegvChainTarget();
    static SigAction getBusChainTarget();
    static void* getSigactionHook();
    static void resetSignalHandlersForTesting();

    static int getMaxThreadId(int floor) {
        int maxThreadId = getMaxThreadId();
        return maxThreadId < floor ? floor : maxThreadId;
    }

    static int truncateFile(int fd);
    static void mallocArenaMax(int arena_max);
};

#endif // _OS_H
