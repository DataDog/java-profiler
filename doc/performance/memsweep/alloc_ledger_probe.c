// LD_PRELOAD allocation-ledger probe for the memsweep "where is the residual?"
// investigation (see memory-sweep-results-linux.md).
//
// WHAT THIS ANSWERS, and why the earlier malloc_info_probe.c could not.
//
// The residual is defined as RSS_delta - NMT_delta - NativeMem_counters. Our
// NativeMem counters record *logical* (requested) bytes; RSS pays for *chunk*
// bytes (request rounded up to glibc's size class, plus an 8-byte header).
// malloc_trim(0) cannot measure that difference -- trim only releases chunks
// glibc already considers free, whereas header+alignment overhead sits on
// *live* chunks by construction. So this probe measures both legs directly:
//
//   malloc_live_requested   sum of requested bytes over live allocations
//   malloc_live_usable      sum of malloc_usable_size() over the same
//   malloc_live_count       number of live allocations
//
// True chunk footprint ~= usable + 8*count (glibc reuses the next chunk's
// prev_size field, so usable is already request-rounded; the 8-byte header is
// the remaining per-chunk cost). inflation = that minus requested.
//
// It also keeps an mmap ledger, because the second candidate for the residual
// is mmap-backed memory that never touches malloc at all:
//
//   - the libc mmap()/munmap()/mremap() wrappers, and
//   - raw syscall(SYS_mmap)/syscall(SYS_munmap), which is what the profiler's
//     OS::safeAlloc/safeFree use (os_linux.cpp:658-670) *specifically* to be
//     uninterceptable. NM_CALLTRACE's ~48.5 MiB arena arrives this way, so an
//     mmap-wrapper-only probe would be blind to it.
//
// Every live mapping is dumped with its caller's return address, so the
// "~91 MiB anonymous region present only with the agent" that smaps could not
// name can be resolved by intersecting ledger addresses against the smaps
// snapshot taken at the same instant (both are emitted by one dump).
//
// SIGNAL HANDLING. Dumping calls fopen()/malloc_info(), which allocate. Doing
// that from a signal handler risks deadlocking against glibc's arena lock if
// the interrupted thread already held it. So the handler only does a
// self-pipe write() (async-signal-safe) and a dedicated dumper thread does the
// real work in normal thread context. SIGRTMIN+10 is used rather than SIGUSR2
// because HotSpot claims SIGUSR2 as its thread suspend/resume signal on Linux
// and never lets an LD_PRELOAD handler see it.
//
// Build:  gcc -shared -fPIC -O2 -o alloc_ledger_probe.so alloc_ledger_probe.c -ldl
// Use:    LD_PRELOAD=/path/to/alloc_ledger_probe.so java ...
//         kill -RTMIN+10 <pid>
// Env:    PROBE_OUTDIR     output directory (default /tmp/memsweep_ledger)
//         PROBE_SLOTS_LOG2 log2 of malloc hash-table slots (default 24 = 16M
//                          slots = 256 MiB of virtual, resident only as used)
//         PROBE_TRACK_REQ  0 disables the per-pointer requested-size table;
//                          usable/count still tracked (default 1)
//         PROBE_TRACK_RAW  0 disables syscall() interposition (default 1)
//
// This is a scratch diagnostic, not shipped code: it favours being obviously
// correct and self-reporting its own failure modes (insert_fail,
// free_untracked) over being fast or memory-frugal.

#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>

#define DUMP_SIG (SIGRTMIN + 10)
#define OUTDIR_DEFAULT "/tmp/memsweep_ledger"
#define MALLOC_MAX_PROBE 64
#define EV_CAP_LOG2_DEFAULT 20
#define TOMB ((uintptr_t)-1)

// Name our own anonymous mappings so smaps labels them "[anon:probe_*]".
// Without this the probe's tables cannot be told apart from any other
// anonymous region -- and since they are resident in proportion to how many
// allocations a run made, they are larger in the with-agent condition and
// would manufacture part of the delta being measured. Linux 5.17+.
#ifndef PR_SET_VMA
#define PR_SET_VMA 0x53564d41
#endif
#ifndef PR_SET_VMA_ANON_NAME
#define PR_SET_VMA_ANON_NAME 0
#endif
static void name_vma(void *addr, size_t len, const char *name) {
  if (addr && addr != MAP_FAILED) {
    prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, (unsigned long)addr,
          (unsigned long)len, (unsigned long)name);
  }
}

// ---------------------------------------------------------------- real fns

static void *(*real_malloc)(size_t);
static void *(*real_calloc)(size_t, size_t);
static void *(*real_realloc)(void *, size_t);
static void (*real_free)(void *);
static int (*real_posix_memalign)(void **, size_t, size_t);
static void *(*real_memalign)(size_t, size_t);
static void *(*real_aligned_alloc)(size_t, size_t);
static size_t (*real_usable)(void *);
static void *(*real_mmap)(void *, size_t, int, int, int, off_t);
static int (*real_munmap)(void *, size_t);
static void *(*real_mremap)(void *, size_t, size_t, int, ...);
static long (*real_syscall)(long, ...);

// ---------------------------------------------------------------- counters

static long long c_live_requested;
static long long c_live_usable;
static long long c_live_count;
static long long c_live_count_mmapped;
static long long c_alloc_calls;
static long long c_free_untracked;      // free() of a pointer we never recorded
static long long c_free_untracked_usable;
static long long c_insert_fail;         // hash table full along the probe run
static long long c_map_events;      // mmap/mmap64 via the libc wrapper
static long long c_unmap_events;    // munmap via the libc wrapper
static long long c_remap_events;    // mremap
static long long c_raw_map_events;  // syscall(SYS_mmap)   -- OS::safeAlloc
static long long c_raw_unmap_events;// syscall(SYS_munmap) -- OS::safeFree
static long long c_ev_overflow;     // events dropped because the log filled

#define ADD(x, d) __atomic_fetch_add(&(x), (long long)(d), __ATOMIC_RELAXED)
#define GET(x) __atomic_load_n(&(x), __ATOMIC_RELAXED)

// ------------------------------------------------------------- bootstrap

// dlsym() may itself call calloc(), so allocations issued before the real
// functions are resolved are served from this static arena and are never
// freed. It is BSS, hence already zeroed, which is what calloc needs.
static char boot_arena[1 << 16];
static size_t boot_used;
static int initialised;
static __thread int in_init;

static void *boot_alloc(size_t n) {
  n = (n + 15) & ~(size_t)15;
  if (boot_used + n > sizeof(boot_arena)) {
    return NULL;
  }
  void *p = boot_arena + boot_used;
  boot_used += n;
  return p;
}

static int is_boot(const void *p) {
  return (const char *)p >= boot_arena &&
         (const char *)p < boot_arena + sizeof(boot_arena);
}

// ------------------------------------------------------------ hash tables

typedef struct {
  uintptr_t key; // 0 = empty, TOMB = deleted, else the pointer
  uint64_t req;
} malloc_slot;

// Mapping activity is recorded as an append-only event log rather than a live
// set. HotSpot reserves a large range and then commits sub-ranges over it with
// MAP_FIXED, so no exact-base "live mapping" table can be right: inserting
// double counts the reservation, replacing discards it, and getting it right
// needs full interval bookkeeping. The log keeps every event losslessly and
// lets the reconstruction happen offline, where residency comes from the
// same-instant smaps snapshot anyway.
typedef struct {
  uint64_t addr;
  uint64_t len;
  uint64_t caller;
  uint32_t op;   // EV_* below
  uint32_t kind; // 0 = libc wrapper, 1 = raw syscall
} ev_t;

#define EV_MMAP 0
#define EV_MUNMAP 1
#define EV_MREMAP_OLD 2
#define EV_MREMAP_NEW 3

static malloc_slot *mtab;
static size_t mtab_slots;
static size_t mtab_bytes;
static int track_req = 1;
static int track_raw = 1;

static ev_t *evlog;
static size_t ev_cap;
static size_t evlog_bytes;
static volatile long long ev_next;

static inline uint64_t mix(uintptr_t p) {
  uint64_t x = (uint64_t)p >> 4; // malloc results are 16-byte aligned
  x ^= x >> 33;
  x *= 0xff51afd7ed558ccdULL;
  x ^= x >> 33;
  x *= 0xc4ceb9fe1a85ec53ULL;
  x ^= x >> 33;
  return x;
}

// A pointer is unique among live allocations, and we always remove an entry
// *before* handing the chunk back to glibc, so a key can never be inserted
// twice concurrently. That is what makes this lock-free table safe here.
static void mtab_insert(void *p, size_t req) {
  if (!mtab) {
    return;
  }
  size_t mask = mtab_slots - 1;
  size_t h = (size_t)mix((uintptr_t)p) & mask;
  for (size_t i = 0; i < MALLOC_MAX_PROBE; i++) {
    size_t idx = (h + i) & mask;
    uintptr_t k = __atomic_load_n(&mtab[idx].key, __ATOMIC_RELAXED);
    if (k == 0 || k == TOMB) {
      if (__atomic_compare_exchange_n(&mtab[idx].key, &k, (uintptr_t)p, 0,
                                      __ATOMIC_RELAXED, __ATOMIC_RELAXED)) {
        mtab[idx].req = req;
        return;
      }
    }
  }
  ADD(c_insert_fail, 1);
}

// Returns the recorded requested size, or UINT64_MAX if this pointer was not
// tracked (allocated before init, or lost to a full table).
static uint64_t mtab_remove(void *p) {
  if (!mtab) {
    return UINT64_MAX;
  }
  size_t mask = mtab_slots - 1;
  size_t h = (size_t)mix((uintptr_t)p) & mask;
  for (size_t i = 0; i < MALLOC_MAX_PROBE; i++) {
    size_t idx = (h + i) & mask;
    uintptr_t k = __atomic_load_n(&mtab[idx].key, __ATOMIC_RELAXED);
    if (k == (uintptr_t)p) {
      uint64_t v = mtab[idx].req;
      __atomic_store_n(&mtab[idx].key, TOMB, __ATOMIC_RELAXED);
      return v;
    }
    if (k == 0) {
      return UINT64_MAX;
    }
  }
  return UINT64_MAX;
}

static void ev_record(uint32_t op, const void *addr, size_t len,
                      uintptr_t caller, uint32_t kind) {
  switch (op) {
  case EV_MMAP:
    if (kind == 1) {
      ADD(c_raw_map_events, 1);
    } else {
      ADD(c_map_events, 1);
    }
    break;
  case EV_MUNMAP:
    if (kind == 1) {
      ADD(c_raw_unmap_events, 1);
    } else {
      ADD(c_unmap_events, 1);
    }
    break;
  default:
    ADD(c_remap_events, 1);
    break;
  }
  if (!evlog) {
    return;
  }
  long long i = __atomic_fetch_add(&ev_next, 1, __ATOMIC_RELAXED);
  if (i < 0 || (size_t)i >= ev_cap) {
    ADD(c_ev_overflow, 1);
    return;
  }
  evlog[i].addr = (uint64_t)(uintptr_t)addr;
  evlog[i].len = (uint64_t)len;
  evlog[i].caller = (uint64_t)caller;
  evlog[i].op = op;
  evlog[i].kind = kind;
}

// ------------------------------------------------------------------- init

static int dump_pipe[2] = {-1, -1};

static void handler(int sig) {
  (void)sig;
  // Only async-signal-safe work here; the dumper thread does the rest.
  char b = 'x';
  ssize_t n = write(dump_pipe[1], &b, 1);
  (void)n;
}

static void *dumper_thread(void *arg);

static void init_once(void) {
  if (__atomic_load_n(&initialised, __ATOMIC_ACQUIRE)) {
    return;
  }
  if (in_init) {
    return; // re-entered from dlsym's own allocations
  }
  in_init = 1;

  // Resolve into locals and publish only once every pointer is known. dlsym()
  // allocates, so it re-enters these interposers; publishing incrementally
  // would let one of them see a resolved malloc but a still-NULL
  // malloc_usable_size and dereference it.
  void *(*l_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");
  void *(*l_calloc)(size_t, size_t) = dlsym(RTLD_NEXT, "calloc");
  void *(*l_realloc)(void *, size_t) = dlsym(RTLD_NEXT, "realloc");
  void (*l_free)(void *) = dlsym(RTLD_NEXT, "free");
  int (*l_pma)(void **, size_t, size_t) = dlsym(RTLD_NEXT, "posix_memalign");
  void *(*l_memalign)(size_t, size_t) = dlsym(RTLD_NEXT, "memalign");
  void *(*l_aa)(size_t, size_t) = dlsym(RTLD_NEXT, "aligned_alloc");
  size_t (*l_usable)(void *) = dlsym(RTLD_NEXT, "malloc_usable_size");
  void *(*l_mmap)(void *, size_t, int, int, int, off_t) =
      dlsym(RTLD_NEXT, "mmap");
  int (*l_munmap)(void *, size_t) = dlsym(RTLD_NEXT, "munmap");
  void *(*l_mremap)(void *, size_t, size_t, int, ...) =
      dlsym(RTLD_NEXT, "mremap");
  long (*l_syscall)(long, ...) = dlsym(RTLD_NEXT, "syscall");

  if (!l_malloc || !l_free || !l_usable || !l_mmap || !l_munmap) {
    // Nothing safe to do without these; stay in bootstrap mode.
    in_init = 0;
    return;
  }

  real_calloc = l_calloc;
  real_realloc = l_realloc;
  real_posix_memalign = l_pma;
  real_memalign = l_memalign;
  real_aligned_alloc = l_aa;
  real_usable = l_usable;
  real_mmap = l_mmap;
  real_munmap = l_munmap;
  real_mremap = l_mremap;
  real_syscall = l_syscall;
  real_free = l_free;
  // Published last: every interposer gates on real_malloc being non-NULL, so
  // this store is what makes the whole set visible.
  __atomic_store_n(&real_malloc, l_malloc, __ATOMIC_RELEASE);

  const char *e = getenv("PROBE_TRACK_REQ");
  if (e && e[0] == '0') {
    track_req = 0;
  }
  e = getenv("PROBE_TRACK_RAW");
  if (e && e[0] == '0') {
    track_raw = 0;
  }

  int log2 = 23;
  e = getenv("PROBE_SLOTS_LOG2");
  if (e) {
    int v = atoi(e);
    if (v >= 10 && v <= 30) {
      log2 = v;
    }
  }

  // Both tables come straight from mmap, never from malloc: they must not
  // perturb the arena whose accounting we are measuring. Their address ranges
  // are reported in the dump so their RSS can be subtracted.
  if (track_req) {
    mtab_slots = (size_t)1 << log2;
    mtab_bytes = mtab_slots * sizeof(malloc_slot);
    void *m = real_mmap(NULL, mtab_bytes, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    mtab = (m == MAP_FAILED) ? NULL : (malloc_slot *)m;
    name_vma(mtab, mtab_bytes, "probe_mtab");
    if (!mtab) {
      mtab_slots = 0;
      mtab_bytes = 0;
    }
  }
  int ev_log2 = EV_CAP_LOG2_DEFAULT;
  e = getenv("PROBE_EV_LOG2");
  if (e) {
    int v2 = atoi(e);
    if (v2 >= 10 && v2 <= 28) {
      ev_log2 = v2;
    }
  }
  ev_cap = (size_t)1 << ev_log2;
  evlog_bytes = ev_cap * sizeof(ev_t);
  void *v = real_mmap(NULL, evlog_bytes, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  evlog = (v == MAP_FAILED) ? NULL : (ev_t *)v;
  name_vma(evlog, evlog_bytes, "probe_evlog");
  if (!evlog) {
    evlog_bytes = 0;
    ev_cap = 0;
  }

  __atomic_store_n(&initialised, 1, __ATOMIC_RELEASE);
  in_init = 0;
}

__attribute__((constructor)) static void probe_start(void) {
  init_once();

  if (pipe(dump_pipe) != 0) {
    return;
  }
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handler;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  sigaction(DUMP_SIG, &sa, NULL);

  pthread_t t;
  if (pthread_create(&t, NULL, dumper_thread, NULL) == 0) {
    pthread_detach(t);
  }
}

#define READY() (__atomic_load_n(&real_malloc, __ATOMIC_ACQUIRE) != NULL)

#define ENSURE()                                                               \
  do {                                                                         \
    if (!__atomic_load_n(&initialised, __ATOMIC_ACQUIRE)) {                    \
      init_once();                                                             \
    }                                                                          \
  } while (0)

// ------------------------------------------------------------ interposers

// glibc marks mmap-backed chunks with bit 1 of the size word preceding the
// user pointer. Verified empirically on glibc 2.35: for a normal chunk the
// footprint is usable+8, and for an mmap'd chunk usable+16 == align4096(req+16)
// exactly -- page rounding is already inside malloc_usable_size(), so the only
// per-chunk correction needed is the extra 8-byte header.
static inline int chunk_is_mmapped_glibc(const void *p) {
  return (int)((*((const size_t *)p - 1) >> 1) & 1u);
}

static void note_alloc(void *p, size_t req) {
  if (!p) {
    return;
  }
  size_t u = real_usable(p);
  ADD(c_live_usable, u);
  ADD(c_live_count, 1);
  if (chunk_is_mmapped_glibc(p)) {
    ADD(c_live_count_mmapped, 1);
  }
  ADD(c_alloc_calls, 1);
  if (track_req) {
    ADD(c_live_requested, req);
    mtab_insert(p, req);
  }
}

void *malloc(size_t n) {
  ENSURE();
  if (!READY()) {
    return boot_alloc(n);
  }
  void *p = real_malloc(n);
  note_alloc(p, n);
  return p;
}

void *calloc(size_t nmemb, size_t size) {
  ENSURE();
  if (!READY()) {
    return boot_alloc(nmemb * size);
  }
  void *p = real_calloc(nmemb, size);
  note_alloc(p, nmemb * size);
  return p;
}

void free(void *p) {
  ENSURE();
  if (!p || is_boot(p)) {
    return;
  }
  if (!READY()) {
    // Pre-init: nothing non-boot can have been handed out yet.
    return;
  }
  // Remove from the ledger *before* releasing the chunk, so the pointer cannot
  // be handed to another thread and re-inserted while we still hold the entry.
  size_t u = real_usable(p);
  if (chunk_is_mmapped_glibc(p)) {
    ADD(c_live_count_mmapped, -1);
  }
  uint64_t req = track_req ? mtab_remove(p) : UINT64_MAX;
  ADD(c_live_usable, -(long long)u);
  ADD(c_live_count, -1);
  if (track_req) {
    if (req == UINT64_MAX) {
      ADD(c_free_untracked, 1);
      ADD(c_free_untracked_usable, u);
    } else {
      ADD(c_live_requested, -(long long)req);
    }
  }
  real_free(p);
}

void *realloc(void *p, size_t n) {
  ENSURE();
  if (!READY()) {
    return boot_alloc(n);
  }
  if (p && is_boot(p)) {
    // Only reachable for dlsym-era allocations; copy conservatively out of our
    // own static arena (over-reading within it is harmless).
    void *np = real_malloc(n);
    if (np) {
      size_t avail = (size_t)(boot_arena + sizeof(boot_arena) - (char *)p);
      memcpy(np, p, n < avail ? n : avail);
      note_alloc(np, n);
    }
    return np;
  }
  size_t old_u = p ? real_usable(p) : 0;
  int old_mmapped = p ? chunk_is_mmapped_glibc(p) : 0;
  uint64_t old_req = (p && track_req) ? mtab_remove(p) : UINT64_MAX;

  void *np = real_realloc(p, n);
  if (!np && n != 0) {
    // Failure: the old block is still live, so put it back exactly as it was.
    if (p && track_req && old_req != UINT64_MAX) {
      mtab_insert(p, old_req);
    }
    return NULL;
  }
  if (p) {
    ADD(c_live_usable, -(long long)old_u);
    ADD(c_live_count, -1);
    if (old_mmapped) {
      ADD(c_live_count_mmapped, -1);
    }
    if (track_req) {
      if (old_req == UINT64_MAX) {
        ADD(c_free_untracked, 1);
        ADD(c_free_untracked_usable, old_u);
      } else {
        ADD(c_live_requested, -(long long)old_req);
      }
    }
  }
  note_alloc(np, n);
  return np;
}

int posix_memalign(void **out, size_t align, size_t n) {
  ENSURE();
  if (!READY()) {
    void *p = boot_alloc(n);
    if (!p) {
      return ENOMEM;
    }
    *out = p;
    return 0;
  }
  int rc = real_posix_memalign(out, align, n);
  if (rc == 0) {
    note_alloc(*out, n);
  }
  return rc;
}

void *memalign(size_t align, size_t n) {
  ENSURE();
  if (!READY()) {
    return boot_alloc(n);
  }
  void *p = real_memalign(align, n);
  note_alloc(p, n);
  return p;
}

void *aligned_alloc(size_t align, size_t n) {
  ENSURE();
  if (!READY()) {
    return boot_alloc(n);
  }
  void *p = real_aligned_alloc(align, n);
  note_alloc(p, n);
  return p;
}

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t off) {
  ENSURE();
  if (!real_mmap) {
    real_mmap = dlsym(RTLD_NEXT, "mmap");
    if (!real_mmap) {
      return MAP_FAILED;
    }
  }
  void *p = real_mmap(addr, len, prot, flags, fd, off);
  if (p != MAP_FAILED) {
    ev_record(EV_MMAP, p, len, (uintptr_t)__builtin_return_address(0), 0);
  }
  return p;
}

// libjvm.so imports mmap64, not mmap (verified with `nm -D`), so interposing
// only mmap sees the launcher's mappings and none of HotSpot's. On LP64 the
// two are the same libc entry point; a caller reaches exactly one of these
// wrappers, so tracking both cannot double count.
void *mmap64(void *addr, size_t len, int prot, int flags, int fd, off_t off) {
  return mmap(addr, len, prot, flags, fd, off);
}

void *mremap(void *old_addr, size_t old_len, size_t new_len, int flags, ...) {
  ENSURE();
  if (!real_mremap) {
    real_mremap = dlsym(RTLD_NEXT, "mremap");
    if (!real_mremap) {
      errno = ENOSYS;
      return MAP_FAILED;
    }
  }
  void *new_addr = NULL;
  if (flags & MREMAP_FIXED) {
    va_list ap;
    va_start(ap, flags);
    new_addr = va_arg(ap, void *);
    va_end(ap);
  }
  void *p = (flags & MREMAP_FIXED)
                ? real_mremap(old_addr, old_len, new_len, flags, new_addr)
                : real_mremap(old_addr, old_len, new_len, flags);
  if (p != MAP_FAILED) {
    uintptr_t ra = (uintptr_t)__builtin_return_address(0);
    ev_record(EV_MREMAP_OLD, old_addr, old_len, ra, 0);
    ev_record(EV_MREMAP_NEW, p, new_len, ra, 0);
  }
  return p;
}

int munmap(void *addr, size_t len) {
  ENSURE();
  if (!real_munmap) {
    real_munmap = dlsym(RTLD_NEXT, "munmap");
    if (!real_munmap) {
      return -1;
    }
  }
  int rc = real_munmap(addr, len);
  if (rc == 0) {
    ev_record(EV_MUNMAP, addr, len, (uintptr_t)__builtin_return_address(0), 0);
  }
  return rc;
}

// The profiler's OS::safeAlloc/safeFree deliberately bypass the libc wrappers
// (os_linux.cpp:658-670), so the only way to see NM_CALLTRACE's arena is to
// interpose syscall() itself. Reading six varargs when the caller passed fewer
// is safe on the x86-64/aarch64 SysV ABIs, where they are register-passed.
long syscall(long number, ...) {
  ENSURE();
  if (!real_syscall) {
    real_syscall = dlsym(RTLD_NEXT, "syscall");
    if (!real_syscall) {
      errno = ENOSYS;
      return -1;
    }
  }
  va_list ap;
  va_start(ap, number);
  long a1 = va_arg(ap, long);
  long a2 = va_arg(ap, long);
  long a3 = va_arg(ap, long);
  long a4 = va_arg(ap, long);
  long a5 = va_arg(ap, long);
  long a6 = va_arg(ap, long);
  va_end(ap);

  long r = real_syscall(number, a1, a2, a3, a4, a5, a6);
  if (!track_raw) {
    return r;
  }
#ifdef SYS_mmap
  if (number == SYS_mmap && r != -1 && (unsigned long)r >= 4096) {
    ev_record(EV_MMAP, (void *)r, (size_t)a2,
              (uintptr_t)__builtin_return_address(0), 1);
  }
#endif
  if (number == SYS_munmap && r == 0) {
    ev_record(EV_MUNMAP, (void *)a1, (size_t)a2,
              (uintptr_t)__builtin_return_address(0), 1);
  }
  return r;
}

// ------------------------------------------------------------------- dump

static void copy_file(const char *src, const char *dst) {
  int in = open(src, O_RDONLY);
  if (in < 0) {
    return;
  }
  int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (out < 0) {
    close(in);
    return;
  }
  char buf[65536];
  ssize_t n;
  while ((n = read(in, buf, sizeof(buf))) > 0) {
    ssize_t off = 0;
    while (off < n) {
      ssize_t w = write(out, buf + off, (size_t)(n - off));
      if (w <= 0) {
        break;
      }
      off += w;
    }
  }
  close(in);
  close(out);
}

static void dump_now(void) {
  const char *dir = getenv("PROBE_OUTDIR");
  if (!dir) {
    dir = OUTDIR_DEFAULT;
  }
  int pid = (int)getpid();
  char path[512];

  // Snapshot the counters first, before any dump-time allocation of our own
  // perturbs them.
  long long live_req = GET(c_live_requested);
  long long live_use = GET(c_live_usable);
  long long live_cnt = GET(c_live_count);
  long long live_mm = GET(c_live_count_mmapped);

  snprintf(path, sizeof(path), "%s/%d.ledger.txt", dir, pid);
  FILE *f = fopen(path, "w");
  if (f) {
    fprintf(f, "pid %d\n", pid);
    fprintf(f, "malloc_live_requested %lld\n", live_req);
    fprintf(f, "malloc_live_usable %lld\n", live_use);
    fprintf(f, "malloc_live_count %lld\n", live_cnt);
    fprintf(f, "malloc_live_count_mmapped %lld\n", live_mm);
    // Exact glibc footprint: usable+8 per normal chunk, usable+16 per mmap'd
    // one (page rounding is already inside usable -- verified empirically).
    fprintf(f, "malloc_live_chunk_est %lld\n",
            live_use + 8 * live_cnt + 8 * live_mm);
    fprintf(f, "malloc_alloc_calls %lld\n", GET(c_alloc_calls));
    fprintf(f, "malloc_free_untracked %lld\n", GET(c_free_untracked));
    fprintf(f, "malloc_free_untracked_usable %lld\n",
            GET(c_free_untracked_usable));
    fprintf(f, "malloc_insert_fail %lld\n", GET(c_insert_fail));
    fprintf(f, "map_events %lld\n", GET(c_map_events));
    fprintf(f, "unmap_events %lld\n", GET(c_unmap_events));
    fprintf(f, "remap_events %lld\n", GET(c_remap_events));
    fprintf(f, "raw_map_events %lld\n", GET(c_raw_map_events));
    fprintf(f, "raw_unmap_events %lld\n", GET(c_raw_unmap_events));
    fprintf(f, "ev_recorded %lld\n", GET(ev_next));
    fprintf(f, "ev_capacity %zu\n", ev_cap);
    fprintf(f, "ev_overflow %lld\n", GET(c_ev_overflow));
    fprintf(f, "track_req %d\n", track_req);
    fprintf(f, "track_raw %d\n", track_raw);
    // Our own tables are mmap'd by us and are pure measurement overhead; their
    // ranges are reported so their RSS can be subtracted from the comparison.
    fprintf(f, "probe_mtab_addr %p\n", (void *)mtab);
    fprintf(f, "probe_mtab_bytes %zu\n", mtab_bytes);
    fprintf(f, "probe_evlog_addr %p\n", (void *)evlog);
    fprintf(f, "probe_evlog_bytes %zu\n", evlog_bytes);
    fclose(f);
  }

  // Every live mapping with its caller, for intersecting against smaps.
  snprintf(path, sizeof(path), "%s/%d.mmaps.txt", dir, pid);
  f = fopen(path, "w");
  if (f && evlog) {
    fprintf(f, "# op(0=mmap,1=munmap,2=mremap_old,3=mremap_new) addr len "
               "caller kind(0=wrapper,1=rawsyscall)\n");
    long long n = GET(ev_next);
    if ((size_t)n > ev_cap) {
      n = (long long)ev_cap;
    }
    for (long long i = 0; i < n; i++) {
      fprintf(f, "%u 0x%lx %lu 0x%lx %u\n", evlog[i].op,
              (unsigned long)evlog[i].addr, (unsigned long)evlog[i].len,
              (unsigned long)evlog[i].caller, evlog[i].kind);
    }
  }
  if (f) {
    fclose(f);
  }

  // Same-instant snapshots so the ledger can be reconciled without skew.
  snprintf(path, sizeof(path), "%s/%d.smaps.txt", dir, pid);
  copy_file("/proc/self/smaps", path);
  snprintf(path, sizeof(path), "%s/%d.status.txt", dir, pid);
  copy_file("/proc/self/status", path);

  // glibc's own view, as an independent cross-check on the ledger: per-arena
  // live chunk bytes = <system current> - (<total fast> + <total rest>).
  snprintf(path, sizeof(path), "%s/%d.mallocinfo.xml", dir, pid);
  f = fopen(path, "w");
  if (f) {
    malloc_info(0, f);
    fclose(f);
  }
}

static void *dumper_thread(void *arg) {
  (void)arg;
  for (;;) {
    char b;
    ssize_t n = read(dump_pipe[0], &b, 1);
    if (n <= 0) {
      if (n < 0 && errno == EINTR) {
        continue;
      }
      return NULL;
    }
    dump_now();
  }
}
