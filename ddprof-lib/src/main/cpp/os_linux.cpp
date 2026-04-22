/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include <arpa/inet.h>
#include <byteswap.h>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <link.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "common.h"
#include "counters.h"
#include "os.h"

#ifndef __musl__
#include <malloc.h>
#endif


#ifdef __LP64__
#  define MMAP_SYSCALL __NR_mmap
#else
#  define MMAP_SYSCALL __NR_mmap2
#endif

#define COMM_LEN 16

class LinuxThreadList : public ThreadList {
  private:
    DIR* _dir;
    int* _thread_array;
    u32 _capacity;

    void addThread(int thread_id) {
        if (_count >= _capacity) {
            _capacity = _count * 2;
            _thread_array = (int*)realloc(_thread_array, _capacity * sizeof(int));
        }
        _thread_array[_count++] = thread_id;
    }

    void fillThreadArray() {
        if (_dir != NULL) {
            rewinddir(_dir);
            struct dirent* entry;
            while ((entry = readdir(_dir)) != NULL) {
                if (entry->d_name[0] != '.') {
                    addThread(atoi(entry->d_name));
                }
            }
        }
    }

  public:
    LinuxThreadList() : ThreadList() {
        _dir = opendir("/proc/self/task");
        _capacity = 128;
        _thread_array = (int*)malloc(_capacity * sizeof(int));
        fillThreadArray();
    }

    ~LinuxThreadList() {
        free(_thread_array);
        if (_dir != NULL) {
            closedir(_dir);
        }
    }

    int next() {
        return _thread_array[_index++];
    }

    void update() {
        _index = _count = 0;
        fillThreadArray();
    }
};


JitWriteProtection::JitWriteProtection(bool enable) {
    // Not used on Linux
}

JitWriteProtection::~JitWriteProtection() {
    // Not used on Linux
}


static constexpr int MAX_SIGNALS = 64;
static SigAction installed_sigaction[MAX_SIGNALS];

// Full previous sigaction per signal, used by forwardForeignSignal to chain
// signals that do not originate from ddprof to whatever handler was installed
// before us.
//
// Write protocol: installSignalHandler takes installed_oldaction_mutex
// around the sigaction() call and the subsequent publish. This serialises
// concurrent installers and ensures the struct write + _valid flag transition
// are atomic with respect to other installers. The release-store on _valid
// synchronises with the acquire-load in forwardForeignSignal so handlers on
// other CPUs only observe the struct after it is fully written.
//
// Store-exactly-once: once installed_oldaction_valid[signo] is true, the
// slot is frozen — subsequent installSignalHandler calls do NOT overwrite
// the captured previous action. This preserves the ORIGINAL chain target
// across profiler restarts or re-installs, even if a foreign library has
// since overwritten our handler and re-chained us. Losing the original
// would break the chain back to e.g. the JVM's SIGSEGV handler.
static struct sigaction installed_oldaction[MAX_SIGNALS];
static bool             installed_oldaction_valid[MAX_SIGNALS];
static pthread_mutex_t  installed_oldaction_mutex = PTHREAD_MUTEX_INITIALIZER;

const size_t OS::page_size = sysconf(_SC_PAGESIZE);
const size_t OS::page_mask = OS::page_size - 1;
const long OS::clock_ticks_per_sec = sysconf(_SC_CLK_TCK);


u64 OS::nanotime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000000000 + ts.tv_nsec;
}

u64 OS::micros() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (u64)tv.tv_sec * 1000000 + tv.tv_usec;
}

u64 OS::processStartTime() {
    static u64 start_time = 0;

    if (start_time == 0) {
        char buf[64];
        snprintf(buf, sizeof(buf), "/proc/%d", processId());

        struct stat st;
        if (stat(buf, &st) == 0) {
            start_time = (u64)st.st_mtim.tv_sec * 1000 + st.st_mtim.tv_nsec / 1000000;
        }
    }

    return start_time;
}

void OS::sleep(u64 nanos) {
    struct timespec ts = {(time_t)(nanos / 1000000000), (long)(nanos % 1000000000)};
    nanosleep(&ts, NULL);
}

void OS::uninterruptibleSleep(u64 nanos, volatile bool* flag) {
    // Workaround nanosleep bug: https://man7.org/linux/man-pages/man2/nanosleep.2.html#BUGS
    u64 deadline = OS::nanotime() + nanos;
    struct timespec ts = {(time_t)(deadline / 1000000000), (long)(deadline % 1000000000)};
    while (*flag && clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, &ts) == EINTR);
}

u64 OS::overrun(siginfo_t* siginfo) {
    return siginfo->si_overrun;
}

u64 OS::hton64(u64 x) {
    return htonl(1) == 1 ? x : bswap_64(x);
}

u64 OS::ntoh64(u64 x) {
    return ntohl(1) == 1 ? x : bswap_64(x);
}

int OS::getMaxThreadId() {
    char buf[16] = "65536";
    int fd = open("/proc/sys/kernel/pid_max", O_RDONLY);
    if (fd != -1) {
        ssize_t r = read(fd, buf, sizeof(buf) - 1);
        (void) r;
        close(fd);
    }
    return atoi(buf);
}

int OS::processId() {
    static const int self_pid = getpid();

    return self_pid;
}

int OS::threadId() {
    return syscall(__NR_gettid);
}

const char* OS::schedPolicy(int thread_id) {
    int sched_policy = sched_getscheduler(thread_id);
    if (sched_policy >= SCHED_BATCH) {
        return sched_policy >= SCHED_IDLE ? "SCHED_IDLE" : "SCHED_BATCH";
    }
    return "SCHED_OTHER";
}

bool OS::threadName(int thread_id, char* name_buf, size_t name_len) {
    char buf[64];
    snprintf(buf, sizeof(buf), "/proc/self/task/%d/comm", thread_id);
    int fd = open(buf, O_RDONLY);
    if (fd == -1) {
        return false;
    }

    ssize_t r = read(fd, name_buf, name_len);
    close(fd);

    if (r > 0) {
        name_buf[r - 1] = 0;
        return true;
    }
    return false;
}

ThreadState OS::threadState(int thread_id) {
    char buf[512];
    snprintf(buf, sizeof(buf), "/proc/self/task/%d/stat", thread_id);
    int fd = open(buf, O_RDONLY);
    if (fd == -1) {
        return THREAD_UNKNOWN;
    }

    ThreadState state = THREAD_UNKNOWN;
    if (read(fd, buf, sizeof(buf)) > 0) {
        char* s = strchr(buf, ')');
        state = s != NULL && (s[2] == 'R' || s[2] == 'D') ? THREAD_RUNNING : THREAD_SLEEPING;
    }

    close(fd);
    return state;
}

u64 OS::threadCpuTime(int thread_id) {
    clockid_t thread_cpu_clock;
    if (thread_id) {
        thread_cpu_clock = ((~(unsigned int)(thread_id)) << 3) | 6;  // CPUCLOCK_SCHED | CPUCLOCK_PERTHREAD_MASK
    } else {
        thread_cpu_clock = CLOCK_THREAD_CPUTIME_ID;
    }

    struct timespec ts;
    if (clock_gettime(thread_cpu_clock, &ts) == 0) {
        return (u64)ts.tv_sec * 1000000000 + ts.tv_nsec;
    }
    return 0;
}

ThreadList* OS::listThreads() {
    return new LinuxThreadList();
}

bool OS::isLinux() {
    return true;
}

// _CS_GNU_LIBC_VERSION is not defined on musl
const static bool musl = confstr(_CS_GNU_LIBC_VERSION, NULL, 0) == 0 && errno != 0;

bool OS::isMusl() {
    return musl;
}

SigAction OS::installSignalHandler(int signo, SigAction action, SigHandler handler) {
    struct sigaction sa;
    struct sigaction oldsa;
    memset(&oldsa, 0, sizeof(oldsa));
    sigemptyset(&sa.sa_mask);

    if (handler != NULL) {
        sa.sa_handler = handler;
        sa.sa_flags = 0;
    } else {
        sa.sa_sigaction = action;
        sa.sa_flags = SA_SIGINFO | SA_RESTART;
        if (signo > 0 && signo < MAX_SIGNALS) {
            installed_sigaction[signo] = action;
        }
    }

    // Take the mutex around sigaction() + publish so concurrent installers
    // serialise, and a signal arriving mid-install always sees either the
    // pre-install state (_valid=false → forward is a no-op) or the fully
    // published post-install state.
    pthread_mutex_lock(&installed_oldaction_mutex);

    int rc = sigaction(signo, &sa, &oldsa);

    // Cache the full previous action so forwardForeignSignal can chain.
    // Skip on sigaction() failure — otherwise we would publish uninitialised
    // garbage as "the previous handler" and the forwarder would jump into it.
    //
    // Only store in the sigaction (3-arg) path — 1-arg handlers are used for
    // transient SIG_IGN / SIG_DFL setups (e.g. ITimer::check) and are never
    // meant to be forwarded to.
    //
    // Store-exactly-once: once a slot is marked valid, preserve that capture.
    // A foreign library may later install its own handler over ours; the
    // next time we install (profiler restart) sigaction() would return the
    // foreign handler as oldsa. Overwriting our stored oldaction with that
    // would lose the ORIGINAL chain target (e.g. JVM's handler) and is never
    // what we want — the original is what real chained delivery must reach.
    //
    // Publication is release-ordered: the struct write is visible before
    // _valid flips to true, so any handler on another CPU that observes
    // _valid==true sees a fully-initialised oldaction. See also the reader
    // side in forwardForeignSignal.
    if (rc == 0 && action != NULL && signo > 0 && signo < MAX_SIGNALS
        && !installed_oldaction_valid[signo]
        && oldsa.sa_sigaction != action) {
        installed_oldaction[signo] = oldsa;
        __atomic_store_n(&installed_oldaction_valid[signo], true, __ATOMIC_RELEASE);
    }

    pthread_mutex_unlock(&installed_oldaction_mutex);

    return rc == 0 ? oldsa.sa_sigaction : nullptr;
}

static void restoreSignalHandler(int signo, siginfo_t* siginfo, void* ucontext) {
    signal(signo, SIG_DFL);
}

SigAction OS::replaceCrashHandler(SigAction action) {
    struct sigaction sa;
    sigaction(SIGSEGV, NULL, &sa);
    SigAction old_action = sa.sa_handler == SIG_DFL ? restoreSignalHandler : sa.sa_sigaction;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = action;
    sa.sa_flags |= SA_SIGINFO | SA_RESTART | SA_NODEFER;
    sigaction(SIGSEGV, &sa, NULL);
    return old_action;
}

int OS::getProfilingSignal(int mode) {
    static int preferred_signals[2] = {SIGPROF, SIGVTALRM};

    const u64 allowed_signals =
        1ULL << SIGPROF | 1ULL << SIGVTALRM | 1ULL << SIGSTKFLT | 1ULL << SIGPWR | -(1ULL << SIGRTMIN);

    int& signo = preferred_signals[mode];
    int initial_signo = signo;
    int other_signo = preferred_signals[1 - mode];

    do {
        struct sigaction sa;
        if ((allowed_signals & (1ULL << signo)) != 0 && signo != other_signo && sigaction(signo, NULL, &sa) == 0) {
            if (sa.sa_handler == SIG_DFL || sa.sa_handler == SIG_IGN || sa.sa_sigaction == installed_sigaction[signo]) {
                return signo;
            }
        }
    } while ((signo = (signo + 53) & 63) != initial_signo);

    return signo;
}

bool OS::sendSignalToThread(int thread_id, int signo) {
    return syscall(__NR_tgkill, processId(), thread_id, signo) == 0;
}

bool OS::sendSignalWithCookie(int thread_id, int signo, void* cookie) {
    // Deliver a SIGQUEUE-style signal to a specific thread, carrying a cookie
    // the handler can use to confirm the signal originated from the profiler.
    // Uses rt_tgsigqueueinfo(2) directly so the same code path works on both
    // glibc and musl (pthread_sigqueue is a glibc-only wrapper). The kernel
    // requires si_code < 0 on user-submitted siginfo, so we set SI_QUEUE.
    // The kernel rewrites si_pid/si_uid to the caller's real credentials for
    // unprivileged senders, so setting them here is advisory at best.
    siginfo_t si;
    memset(&si, 0, sizeof(si));
    si.si_signo = signo;
    si.si_code  = SI_QUEUE;
    si.si_value.sival_ptr = cookie;
    return syscall(SYS_rt_tgsigqueueinfo, processId(), thread_id, signo, &si) == 0;
}

// File-scope origin-check state. Accessed from signal handlers on the hot
// path, written from primeSignalOriginCheck() in non-signal context. Writes
// use __ATOMIC_RELEASE; reads use __ATOMIC_RELAXED for the flag itself
// (there is no dependent data to synchronise with), plus an __ATOMIC_ACQUIRE
// on `primed` to pair with the release-store for ordering guarantees across
// the forceReload=true path used by tests.
//
// Plain `volatile` is deliberately not used here: volatile suppresses compiler
// optimisations and forces the access to hit memory, but it does not imply
// any inter-thread memory ordering, does not establish happens-before, and
// offers no protection against torn reads on wider types. Use explicit
// __atomic_* primitives when multi-thread visibility matters.
static bool s_origin_check_enabled    = true;
static bool s_origin_check_primed     = false;

// Opt-in sa_mask-respecting chain in forwardForeignSignal(). Off by default:
// saves 2× pthread_sigmask syscalls per foreign signal (~1 µs on modern Linux,
// ~30% of the per-signal end-to-end cost). Set DDPROF_FORWARD_APPLY_SIGMASK=1
// if the chained handler is known to require the kernel's normal sa_mask
// environment (rare — SIGSEGV/SIGBUS handlers are the main case and are out
// of scope here).
static bool s_forward_apply_sigmask   = false;

bool OS::shouldProcessSignal(siginfo_t* siginfo, int expected_si_code, void* expected_cookie) {
    // Relaxed load — the flag is written once in primeSignalOriginCheck()
    // (non-signal context, before any handler can fire) and never toggled
    // afterwards outside tests. No ordering requirement vs. subsequent fields.
    if (!__atomic_load_n(&s_origin_check_enabled, __ATOMIC_RELAXED)) {
        // Origin check disabled — process every signal (pre-fix behaviour).
        return true;
    }
    if (siginfo == nullptr || siginfo->si_code != expected_si_code) {
        return false;
    }
    return siginfo->si_value.sival_ptr == expected_cookie;
}

void OS::forwardForeignSignal(int signo, siginfo_t* siginfo, void* ucontext) {
    if (signo <= 0 || signo >= MAX_SIGNALS) {
        return;
    }
    // Acquire-load the valid flag — synchronises with the release-store in
    // installSignalHandler so we only touch the oldaction struct after it
    // has been fully written.
    if (!__atomic_load_n(&installed_oldaction_valid[signo], __ATOMIC_ACQUIRE)) {
        return;
    }
    // Copy the stored action into a local so we pick a self-consistent
    // snapshot even if a concurrent installSignalHandler is mid-rewrite.
    struct sigaction prev = installed_oldaction[signo];

    // By default we chain WITHOUT reproducing prev.sa_mask. Our own handler
    // was installed without SA_NODEFER so the kernel has already blocked
    // `signo` for the duration of this handler, which covers the common
    // reentrancy concern. Benchmarks show that applying sa_mask via
    // pthread_sigmask(SIG_BLOCK)+SIG_SETMASK costs ~1 µs per foreign signal
    // (two rt_sigprocmask syscalls) — ~30% per-signal overhead in the
    // slow-path micro-benchmark. In the trivyjni / Go-ITIMER_PROF scenario
    // the plan targets, prev.sa_mask is empty anyway so the correctness
    // cost is zero.
    //
    // Correctness escape hatch: set DDPROF_FORWARD_APPLY_SIGMASK=1 to
    // enable the slow path. Use this when the chained handler is known
    // to rely on the kernel's normal sa_mask environment (e.g. a JVM
    // crash handler that expects other fatal signals blocked during its
    // run). Default off keeps high-frequency profiling cheap.
    sigset_t saved_mask;
    bool need_mask = false;
    if (__atomic_load_n(&s_forward_apply_sigmask, __ATOMIC_RELAXED)) {
        // Probe prev.sa_mask for any set signal. POSIX offers no constant-time
        // "is empty?" primitive, and looping sigismember over all signals
        // inside a hot signal handler would cost more than the pthread_sigmask
        // syscalls it is meant to avoid. We memcmp against a zero-initialised
        // sigset_t instead:
        //   - glibc defines sigset_t as a fixed-size bitmap (__sigset_t
        //     containing an unsigned-long array); zero bits == empty set.
        //   - musl defines sigset_t identically (unsigned long array).
        //   - Both target platforms (linux-x86_64, linux-aarch64) initialise
        //     sigset_t via sigemptyset to all-zero bytes.
        // This is not POSIX-guaranteed but is reliable on every Linux libc
        // we ship against. A future port to a libc that encodes "empty" as
        // non-zero bytes would need sigismember loop here.
        static const sigset_t empty_sigset = {};
        need_mask = memcmp(&prev.sa_mask, &empty_sigset, sizeof(empty_sigset)) != 0;
        if (need_mask) {
            pthread_sigmask(SIG_BLOCK, &prev.sa_mask, &saved_mask);
        }
    }

    if (prev.sa_flags & SA_SIGINFO) {
        if (prev.sa_sigaction != nullptr) {
            prev.sa_sigaction(signo, siginfo, ucontext);
        }
    } else if (prev.sa_handler != SIG_DFL && prev.sa_handler != SIG_IGN
               && prev.sa_handler != nullptr) {
        // Chain to a 1-arg handler. Note: nullptr check is a safety net for
        // uninitialised previous action (not a POSIX value).
        //
        // SIG_DFL / SIG_IGN fall through with no chain call:
        //   - SIG_IGN: no handler to run — skipping matches the kernel's
        //     ignore semantics.
        //   - SIG_DFL: we do NOT reproduce the kernel's default action
        //     (which for SIGPROF/SIGVTALRM is termination). A foreign
        //     SIGPROF arriving when the prior state was SIG_DFL is simply
        //     dropped. Reproducing the default would kill the process on
        //     every foreign signal — strictly worse for the Go-ITIMER_PROF
        //     scenario the classifier is designed to handle.
        prev.sa_handler(signo);
    }

    if (need_mask) {
        pthread_sigmask(SIG_SETMASK, &saved_mask, nullptr);
    }
}

bool OS::signalOriginCheckEnabled() {
    return __atomic_load_n(&s_origin_check_enabled, __ATOMIC_RELAXED);
}

// Parse a boolean env-var value. Returns false for empty / unrecognised /
// unset, and logs a warning when the value is set but not one of the
// documented spellings so operators don't silently get the default.
// `default_value` is returned for unset (null) and silently-accepted-empty.
// Expected spellings are case-insensitive and trimmed of leading whitespace.
static bool parseBoolEnv(const char* name, const char* v, bool default_value) {
    if (v == nullptr) {
        return default_value;
    }
    // Skip leading whitespace (users who typed "=1 " in a shell).
    while (*v == ' ' || *v == '\t') ++v;
    if (*v == '\0') {
        return default_value;
    }
    if (strcasecmp(v, "false") == 0 || strcasecmp(v, "0") == 0 ||
        strcasecmp(v, "off")   == 0 || strcasecmp(v, "no") == 0) {
        return false;
    }
    if (strcasecmp(v, "true") == 0 || strcasecmp(v, "1") == 0 ||
        strcasecmp(v, "on")   == 0 || strcasecmp(v, "yes") == 0) {
        return true;
    }
    Log::warn("%s has unrecognised value %s; using default (%s). "
              "Expected one of: true/false/1/0/on/off/yes/no.",
              name, v, default_value ? "enabled" : "disabled");
    return default_value;
}

void OS::primeSignalOriginCheck(bool forceReload) {
    // Acquire-load on `primed` pairs with the release-store below. This
    // matters for forceReload=true paths in tests that concurrently write
    // the flag from non-signal context.
    if (__atomic_load_n(&s_origin_check_primed, __ATOMIC_ACQUIRE) && !forceReload) {
        return;
    }
    // Default ON — reject foreign signals.
    bool enabled = parseBoolEnv("DDPROF_SIGNAL_ORIGIN_CHECK",
                                getenv("DDPROF_SIGNAL_ORIGIN_CHECK"),
                                /*default=*/true);
    // Default OFF — slow chain path is opt-in. See s_forward_apply_sigmask.
    bool apply_mask = parseBoolEnv("DDPROF_FORWARD_APPLY_SIGMASK",
                                   getenv("DDPROF_FORWARD_APPLY_SIGMASK"),
                                   /*default=*/false);

    // Write data bits first, then publish primed=true with a release-store.
    // A concurrent signalOriginCheckEnabled() / forwardForeignSignal() that
    // sees primed=true through an acquire-load is guaranteed to see the
    // final values of enabled and apply_mask.
    //
    // IMPORTANT: the ordering guarantee only holds across prime → handler
    // (the intended usage). It does NOT hold across forceReload=true
    // reconfiguration while a signal is in flight — that is a test-only
    // path and assumes the writer and any receiver are quiesced.
    __atomic_store_n(&s_origin_check_enabled,  enabled,    __ATOMIC_RELAXED);
    __atomic_store_n(&s_forward_apply_sigmask, apply_mask, __ATOMIC_RELAXED);
    __atomic_store_n(&s_origin_check_primed,   true,       __ATOMIC_RELEASE);
}

void* OS::safeAlloc(size_t size) {
    // Naked syscall can be used inside a signal handler.
    // Also, we don't want to catch our own calls when profiling mmap.
    intptr_t result = syscall(MMAP_SYSCALL, NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (result < 0 && result > -4096) {
        return NULL;
    }
    return (void*)result;
}

void OS::safeFree(void* addr, size_t size) {
    syscall(__NR_munmap, addr, size);
}

bool OS::getCpuDescription(char* buf, size_t size) {
    int fd = open("/proc/cpuinfo", O_RDONLY);
    if (fd == -1) {
        return false;
    }

    ssize_t r = read(fd, buf, size);
    close(fd);
    if (r <= 0) {
        return false;
    }
    buf[static_cast<size_t>(r) < size ? r : size - 1] = 0;

    char* c;
    do {
        c = strchr(buf, '\n');
    } while (c != NULL && *(buf = c + 1) != '\n');

    *buf = 0;
    return true;
}

int OS::getCpuCount() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

u64 OS::getProcessCpuTime(u64* utime, u64* stime) {
    struct tms buf;
    clock_t real = times(&buf);
    *utime = buf.tms_utime;
    *stime = buf.tms_stime;
    return real;
}

u64 OS::getTotalCpuTime(u64* utime, u64* stime) {
    int fd = open("/proc/stat", O_RDONLY);
    if (fd == -1) {
        return (u64)-1;
    }

    u64 real = (u64)-1;
    char buf[128] = {0};
    if (read(fd, buf, sizeof(buf)) >= 12) {
        u64 user, nice, system, idle;
        if (sscanf(buf + 4, "%llu %llu %llu %llu", &user, &nice, &system, &idle) == 4) {
            *utime = user + nice;
            *stime = system;
            real = user + nice + system + idle;
        }
    }

    close(fd);
    return real;
}

int OS::createMemoryFile(const char* name) {
    return syscall(__NR_memfd_create, name, 0);
}

void OS::copyFile(int src_fd, int dst_fd, off_t offset, size_t size) {
    // copy_file_range() is probably better, but not supported on all kernels
    while (size > 0) {
        ssize_t bytes = sendfile(dst_fd, src_fd, &offset, size);
        if (bytes <= 0) {
            break;
        }
        size -= (size_t)bytes;
    }
}

void OS::freePageCache(int fd, off_t start_offset) {
    posix_fadvise(fd, start_offset & ~page_mask, 0, POSIX_FADV_DONTNEED);
}

int OS::mprotect(void* addr, size_t size, int prot) {
    return ::mprotect(addr, size, prot);
}

static int checkPreloadedCallback(dl_phdr_info* info, size_t size, void* data) {
    Dl_info* dl_info = (Dl_info*)data;

    Dl_info libprofiler = dl_info[0];
    Dl_info libc = dl_info[1];

    if ((void*)info->dlpi_addr == libprofiler.dli_fbase) {
        // async-profiler found first
        return 1;
    } else if ((void*)info->dlpi_addr == libc.dli_fbase) {
        // libc found first
        return -1;
    }

    return 0;
}

// Checks if async-profiler is preloaded through the LD_PRELOAD mechanism.
// This is done by analyzing the order of loaded dynamic libraries.
bool OS::checkPreloaded() {
    if (getenv("LD_PRELOAD") == NULL) {
        return false;
    }

    // Find async-profiler shared object
    Dl_info libprofiler;
    if (dladdr((const void*)OS::checkPreloaded, &libprofiler) == 0) {
        return false;
    }

    // Find libc shared object
    Dl_info libc;
    if (dladdr((const void*)exit, &libc) == 0) {
        return false;
    }

    Dl_info info[2] = {libprofiler, libc};
    return dl_iterate_phdr(checkPreloadedCallback, (void*)info) == 1;
}

u64 OS::getRamSize() {
    static u64 mem_total = 0;

    if (mem_total == 0) {
        FILE* file = fopen("/proc/meminfo", "r");
        if (!file) return 0;

        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "MemTotal:", 9) == 0) {
                mem_total = strtoull(line + 9, NULL, 10) * 1024;
                break;
            }
        }

        fclose(file);
    }

    return mem_total;
}

u64 OS::getSystemBootTime() {
    static u64 system_boot_time = 0;

    if (system_boot_time == 0) {
        FILE* file = fopen("/proc/stat", "r");
        if (!file) return 0;

        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "btime", 5) == 0) {
                system_boot_time = strtoull(line + 5, NULL, 10);
                break;
            }
        }

        fclose(file);
    }

    return system_boot_time;
}

int OS::getProcessIds(int* pids, int max_pids) {
    int count = 0;
    DIR* proc = opendir("/proc");
    if (!proc) return 0;

    for (dirent* de; (de = readdir(proc)) && count < max_pids;) {
        int pid = atoi(de->d_name);
        if (pid > 0) {
            pids[count++] = pid;
        }
    }

    closedir(proc);
    return count;
}

static bool readProcessCmdline(int pid, ProcessInfo* info) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        return false;
    }

    const size_t max_read = sizeof(info->cmdline) - 1;
    size_t len = 0;

    ssize_t r;
    while ((r = read(fd, info->cmdline + len, max_read - len))) {
        if (r > 0) {
            len += (size_t)r;
            if (len == max_read) break;
        } else {
            if (errno == EINTR) continue;
            close(fd);
            return false;
        }
    }

    close(fd);

    // Replace null bytes with spaces (arguments are separated by null bytes)
    for (size_t i = 0; i < len; i++) {
        if (info->cmdline[i] == '\0') {
            info->cmdline[i] = ' ';
        }
    }

    // Ensure null termination
    info->cmdline[len] = '\0';

    // Remove trailing space if present
    while (len > 0 && info->cmdline[len - 1] == ' ') {
        info->cmdline[--len] = '\0';
    }

    return true;
}

static bool readProcessStats(int pid, ProcessInfo* info) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);

    int fd = open(path, O_RDONLY);
    if (fd == -1) return false;

    char buffer[4096];
    size_t len = 0;

    ssize_t r;
    while ((r = read(fd, buffer + len, sizeof(buffer) - 1 - len))) {
        if (r > 0) {
            len += (size_t)r;
            if (len == sizeof(buffer) - 1) break;
        } else {
            if (errno == EINTR) continue;
            close(fd);
            return false;
        }
    }
    close(fd);

    if (len == 0) return false;
    buffer[len] = '\0';

    int parsed_pid, ppid;
    char comm[COMM_LEN] = {0};
    char state;
    u64 minflt, majflt, utime, stime;
    u64 starttime;
    u64 vsize, rss;
    int threads;
    int parsed =
        sscanf(buffer,
               "%d "                    /*  1 pid                                   */
               "(%15[^)]) "             /*  2 comm (read until ')')                 */
               "%c %d "                 /*  3 state, 4 ppid                         */
               "%*d %*d %*d %*d %*u "   /*  5-9 skip                                */
               "%llu %*u %llu %*u "     /* 10-13 minflt,-,majflt,-                  */
               "%llu %llu "             /* 14-15 utime, stime                       */
               "%*d %*d %*d %*d "       /* 16-19 skip                               */
               "%d "                    /* 20 threads                               */
               "%*d "                   /* 21 skip                                  */
               "%llu "                  /* 22 starttime                             */
               "%llu "                  /* 23 vsize                                 */
               "%llu",                  /* 24 rss                                   */
               &parsed_pid, comm, &state, &ppid, &minflt, &majflt, &utime, &stime, &threads, &starttime, &vsize, &rss);

    if (parsed < 12) return false;

    memcpy(info->name, comm, COMM_LEN);
    info->pid = parsed_pid;
    info->ppid = ppid;
    info->state = (unsigned char)state;
    info->minor_faults = minflt;
    info->major_faults = majflt;
    info->cpu_user = (float)utime / OS::clock_ticks_per_sec;
    info->cpu_system = (float)stime / OS::clock_ticks_per_sec;
    info->threads = threads;
    info->vm_size = vsize;
    // (24) rss - convert from number of pages to bytes
    info->vm_rss = rss * OS::page_size;
    info->start_time = (OS::getSystemBootTime() + starttime / OS::clock_ticks_per_sec) * 1000;
    return true;
}

static bool readProcessStatus(int pid, ProcessInfo* info) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE* file = fopen(path, "r");
    if (!file) {
        return false;
    }

    int read_count = 0;
    char line[1024];
    char key[32];
    u64 value;
    while (fgets(line, sizeof(line), file) && read_count < 6) {
        if (sscanf(line, "%31s %llu", key, &value) != 2) {
            continue;
        }

        if (strncmp(key, "Uid", 3) == 0) {
            read_count++;
            info->uid = (unsigned int)value;
        } else if (strncmp(key, "RssAnon", 7) == 0) {
            read_count++;
            info->rss_anon = value * 1024;
        } else if (strncmp(key, "RssFile", 7) == 0) {
            read_count++;
            info->rss_files = value * 1024;
        } else if (strncmp(key, "RssShmem", 8) == 0) {
            read_count++;
            info->rss_shmem = value * 1024;
        } else if (strncmp(key, "VmSize", 6) == 0) {
            read_count++;
            info->vm_size = value * 1024;
        } else if (strncmp(key, "VmRSS", 5) == 0) {
            read_count++;
            info->vm_rss = value * 1024;
        }
    }

    fclose(file);
    return true;
}

static bool readProcessIO(int pid, ProcessInfo* info) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/io", pid);
    FILE* file = fopen(path, "r");
    if (!file) return false;

    int read_count = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file) && read_count < 2) {
        if (strncmp(line, "read_bytes:", 11) == 0) {
            u64 read_bytes = strtoull(line + 11, NULL, 10);
            info->io_read = read_bytes >> 10;
            read_count++;
        } else if (strncmp(line, "write_bytes:", 12) == 0) {
            u64 write_bytes = strtoull(line + 12, NULL, 10);
            info->io_write = write_bytes >> 10;
            read_count++;
        }
    }

    fclose(file);
    return true;
}

bool OS::getBasicProcessInfo(int pid, ProcessInfo* info) {
    return readProcessStats(pid, info);
}

bool OS::getDetailedProcessInfo(ProcessInfo* info) {
    readProcessStatus(info->pid, info);
    readProcessIO(info->pid, info);
    readProcessCmdline(info->pid, info);
    return true;
}

// DataDog-specific implementations

int OS::truncateFile(int fd) {
    int rslt = ftruncate(fd, 0);
    if (rslt == 0) {
        return lseek(fd, 0, SEEK_SET);
    }
    return rslt;
}

void OS::mallocArenaMax(int arena_max) {
#ifndef __musl__
    mallopt(M_ARENA_MAX, arena_max);
#endif
}

SigAction OS::replaceSigsegvHandler(SigAction action) {
    return OS::replaceCrashHandler(action);
}

SigAction OS::replaceSigbusHandler(SigAction action) {
    struct sigaction sa;
    sigaction(SIGBUS, NULL, &sa);
    SigAction old_action = sa.sa_sigaction;
    sa.sa_sigaction = action;
    sigaction(SIGBUS, &sa, NULL);
    return old_action;
}

// ============================================================================
// sigaction interposition to prevent other libraries from overwriting our
// SIGSEGV/SIGBUS handlers. This is needed because libraries like wasmtime
// install broken signal handlers that call malloc() (not async-signal-safe).
// ============================================================================

// Our protected handlers and their chain targets
static SigAction _protected_segv_handler = nullptr;
static SigAction _protected_bus_handler = nullptr;
static volatile SigAction _segv_chain_target = nullptr;
static volatile SigAction _bus_chain_target = nullptr;

// Original handlers (JVM's) saved before we install ours - used for oldact in sigaction hook
static struct sigaction _orig_segv_sigaction;
static struct sigaction _orig_bus_sigaction;
static bool _orig_handlers_saved = false;

// Real sigaction function pointer (resolved via dlsym)
typedef int (*real_sigaction_t)(int, const struct sigaction*, struct sigaction*);
static real_sigaction_t _real_sigaction = nullptr;

void OS::protectSignalHandlers(SigAction segvHandler, SigAction busHandler) {
    // Resolve real sigaction BEFORE enabling protection, while we can still use RTLD_DEFAULT
    if (_real_sigaction == nullptr) {
        _real_sigaction = (real_sigaction_t)dlsym(RTLD_DEFAULT, "sigaction");
    }
    // Save the current (JVM's) signal handlers BEFORE we install ours.
    // These will be returned as oldact when we intercept other libraries' sigaction calls,
    // so they chain to JVM instead of back to us (which would cause infinite loops).
    if (!__atomic_load_n(&_orig_handlers_saved, __ATOMIC_ACQUIRE) && _real_sigaction != nullptr) {
        _real_sigaction(SIGSEGV, nullptr, &_orig_segv_sigaction);
        _real_sigaction(SIGBUS, nullptr, &_orig_bus_sigaction);
        __atomic_store_n(&_orig_handlers_saved, true, __ATOMIC_RELEASE);
    }
    _protected_segv_handler = segvHandler;
    _protected_bus_handler = busHandler;
}

SigAction OS::getSegvChainTarget() {
    return __atomic_load_n(&_segv_chain_target, __ATOMIC_ACQUIRE);
}

SigAction OS::getBusChainTarget() {
    return __atomic_load_n(&_bus_chain_target, __ATOMIC_ACQUIRE);
}

// sigaction_hook - intercepts sigaction(2) calls from any library via GOT patching.
//
// PROBLEM SOLVED
// ==============
// Without interception, a library (e.g. wasmtime) can overwrite our SIGSEGV handler:
//
//   Before:   kernel --> our_handler --> JVM_handler
//   After lib calls sigaction(SIGSEGV, lib_handler, &oldact):
//             kernel --> lib_handler
//   lib_handler stores oldact = our_handler as its chain target
//   => when lib chains on unhandled fault: lib_handler --> our_handler --> lib_handler --> ...
//      INFINITE LOOP
//
// HANDLER CHAIN AFTER SETUP
// ==========================
//
//   protectSignalHandlers()          replaceSigsegvHandler()     LibraryPatcher::patch_sigaction()
//         |                                  |                            |
//         v                                  v                            v
//   save JVM handler               install our_handler         GOT-patch sigaction
//   into _orig_segv_sigaction      as real OS handler          => all future sigaction()
//                                                                 calls go through us
//
//   Signal delivery chain:
//
//     kernel
//       |
//       v
//     our_handler  (installed via replaceSigsegvHandler, never displaced)
//       |
//       +-- handled by us? --> done
//       |
//       v (not handled)
//     _segv_chain_target  (lib_handler, set when we intercepted lib's sigaction call)
//       |
//       +-- handled by lib? --> done
//       |
//       v (lib chains to its saved oldact)
//     _orig_segv_sigaction  (JVM's original handler, what we returned as oldact to lib)
//       |
//       v
//     JVM handles or terminates
//
// INTERCEPTION LOGIC (this function)
// ===================================
// Case 1 - Install call [act != nullptr, SA_SIGINFO]:
//   - Save lib's handler as _segv_chain_target (we'll call it if we can't handle)
//   - Return _orig_segv_sigaction as oldact (NOT our handler, to break the loop)
//   - Do NOT actually install lib's handler (keep ours on top)
//
// Case 2 - Query-only call [act == nullptr, oldact != nullptr]:
//   - Return _orig_segv_sigaction as oldact (same reason: lib must not see our handler)
//   - A lib that queries, stores the result, then uses it as a chain target would
//     loop if we returned our handler here.
//
// Case 3 - 1-arg handler [act != nullptr, no SA_SIGINFO]:
//   - Pass through: we cannot safely chain 1-arg handlers (different calling convention)
//
// Case 4 - Any other signal, or protection not yet active:
//   - Pass through to real sigaction unchanged.
//
static int sigaction_hook(int signum, const struct sigaction* act, struct sigaction* oldact) {
    // _real_sigaction must be resolved before any GOT patching happens
    if (_real_sigaction == nullptr) {
        errno = EFAULT;
        return -1;
    }

    // If this is SIGSEGV or SIGBUS and we have protected handlers installed,
    // intercept the call to keep our handler on top.
    // We intercept both install calls (act != nullptr) and query-only calls (act == nullptr)
    // to ensure callers always see the JVM's original handler, never ours.
    // A caller that gets our handler as oldact and later chains to it would cause an
    // infinite loop: us -> them -> us -> ...
    if (signum == SIGSEGV && _protected_segv_handler != nullptr) {
        if (act != nullptr) {
            // Install call: only intercept SA_SIGINFO handlers (3-arg form) for safe chaining
            if (act->sa_flags & SA_SIGINFO) {
                SigAction new_handler = act->sa_sigaction;
                // Don't intercept if it's our own handler being installed
                if (new_handler != _protected_segv_handler) {
                    // Save their handler as our chain target
                    __atomic_exchange_n(&_segv_chain_target, new_handler, __ATOMIC_ACQ_REL);
                    if (oldact != nullptr) {
                        // Return the original (JVM's) handler, not ours, to prevent
                        // the caller from chaining back to us.
                        *oldact = _orig_segv_sigaction;
                    }
                    Counters::increment(SIGACTION_INTERCEPTED);
                    // Don't actually install their handler - keep ours on top
                    return 0;
                }
            }
            // Let 1-arg handlers (without SA_SIGINFO) pass through - we can't safely chain them
        } else if (oldact != nullptr) {
            // Query-only call: return the JVM's original handler, not ours.
            // Same reason: a caller that stores our handler and later chains to it causes loops.
            *oldact = _orig_segv_sigaction;
            return 0;
        }
    } else if (signum == SIGBUS && _protected_bus_handler != nullptr) {
        if (act != nullptr) {
            if (act->sa_flags & SA_SIGINFO) {
                SigAction new_handler = act->sa_sigaction;
                if (new_handler != _protected_bus_handler) {
                    __atomic_exchange_n(&_bus_chain_target, new_handler, __ATOMIC_ACQ_REL);
                    if (oldact != nullptr) {
                        *oldact = _orig_bus_sigaction;
                    }
                    Counters::increment(SIGACTION_INTERCEPTED);
                    return 0;
                }
            }
        } else if (oldact != nullptr) {
            *oldact = _orig_bus_sigaction;
            return 0;
        }
    }

    // For all other cases, pass through to real sigaction
    return _real_sigaction(signum, act, oldact);
}

void* OS::getSigactionHook() {
    return (void*)sigaction_hook;
}

void OS::resetSignalHandlersForTesting() {
    __atomic_store_n(&_orig_handlers_saved, false, __ATOMIC_RELEASE);
    memset(&_orig_segv_sigaction, 0, sizeof(_orig_segv_sigaction));
    memset(&_orig_bus_sigaction, 0, sizeof(_orig_bus_sigaction));
    _protected_segv_handler = nullptr;
    _protected_bus_handler = nullptr;
    __atomic_store_n(&_segv_chain_target, (SigAction)nullptr, __ATOMIC_RELEASE);
    __atomic_store_n(&_bus_chain_target, (SigAction)nullptr, __ATOMIC_RELEASE);

    // Clear the foreign-signal forwarding cache so tests that install and
    // verify chaining start from a clean slate. Hold the publish mutex so a
    // concurrent installSignalHandler cannot race with us during the reset.
    pthread_mutex_lock(&installed_oldaction_mutex);
    for (int i = 0; i < MAX_SIGNALS; ++i) {
        __atomic_store_n(&installed_oldaction_valid[i], false, __ATOMIC_RELEASE);
        memset(&installed_oldaction[i], 0, sizeof(installed_oldaction[i]));
        installed_sigaction[i] = nullptr;
    }
    pthread_mutex_unlock(&installed_oldaction_mutex);

    // _real_sigaction is intentionally not reset: safe to reuse across tests
}

#endif // __linux__
