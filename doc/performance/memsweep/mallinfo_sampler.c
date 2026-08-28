// LD_PRELOAD shim that periodically samples glibc's arena accounting, for
// ATTRIBUTING free-but-held arena waste to the profiler.
//
// Why this exists when the profiler already reports mallinfo2: those counters
// ride the profiler's own JFR, so the tracing-only arm of a paired experiment
// emits nothing and no paired delta can be formed. Arena waste is a
// process-wide property, so attributing any of it to the profiler requires the
// same figure from a run WITHOUT the profiler. This shim supplies it, since
// LD_PRELOAD is independent of whether the profiler is attached.
//
// Distinct from malloc_info_probe.c, which answers a different question ("is
// the residual reclaimable?") and deliberately calls malloc_trim(0) between two
// dumps. Trimming would change the arena state being measured, so this sampler
// never trims and never dumps XML -- it only observes.
//
// PASSIVITY MATTERS. A probe that allocates perturbs the arena it is measuring,
// which would be self-defeating. After the one-off setup in the constructor the
// sampling loop is allocation-free: mallinfo2() does not allocate, snprintf()
// into a stack buffer does not allocate for these conversions, and write() to
// an already-open fd does not allocate. No stdio, no malloc, on the hot path.
//
// Build: gcc -shared -fPIC -O2 -o mallinfo_sampler.so mallinfo_sampler.c -lpthread
// Use:   LD_PRELOAD=/path/mallinfo_sampler.so  MALLINFO_OUT=/dir  java ...
//        MALLINFO_INTERVAL_MS defaults to 1000.
//
// Output: one line per sample, "<epoch_ms> <arena> <in_use> <free_held>
// <trimmable> <mmap>" in bytes, to <MALLINFO_OUT>/<pid>.mallinfo.txt
#define _GNU_SOURCE
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static int   g_fd = -1;
static long  g_interval_ms = 1000;

static long now_ms(void) {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

static void *sampler(void *arg) {
  (void)arg;
  // mallinfo2 walks every arena taking each arena lock, so it is not free --
  // but at a 1 s cadence against a 300 s run that is negligible, and it is the
  // only way to see the free/in-use split from outside the allocator.
  for (;;) {
    struct mallinfo2 mi = mallinfo2();
    char buf[256];
    int n = snprintf(buf, sizeof(buf), "%ld %zu %zu %zu %zu %zu\n", now_ms(),
                     mi.arena, mi.uordblks, mi.fordblks, mi.keepcost, mi.hblkhd);
    if (n > 0 && g_fd >= 0) {
      ssize_t ignored = write(g_fd, buf, (size_t)n);
      (void)ignored;
    }
    struct timespec req = {g_interval_ms / 1000,
                           (g_interval_ms % 1000) * 1000000L};
    nanosleep(&req, NULL);
  }
  return NULL;
}

__attribute__((constructor)) static void init(void) {
  const char *dir = getenv("MALLINFO_OUT");
  if (dir == NULL || *dir == '\0') {
    return;  // not configured: stay completely inert
  }
  const char *iv = getenv("MALLINFO_INTERVAL_MS");
  if (iv != NULL && *iv != '\0') {
    long v = atol(iv);
    if (v >= 50) {
      g_interval_ms = v;
    }
  }

  char path[512];
  snprintf(path, sizeof(path), "%s/%d.mallinfo.txt", dir, (int)getpid());
  // Opened once here so the sampling loop never touches the filesystem
  // metadata path again, and so a failure is silent rather than fatal: this is
  // a diagnostic, and it must never take down the process under measurement.
  g_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (g_fd < 0) {
    return;
  }

  pthread_t t;
  if (pthread_create(&t, NULL, sampler, NULL) != 0) {
    close(g_fd);
    g_fd = -1;
    return;
  }
  pthread_detach(t);
}
