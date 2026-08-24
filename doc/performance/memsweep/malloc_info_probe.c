// LD_PRELOAD shim for the "is the residual live memory or reclaimable
// arena slack?" test in memory-sweep-results-linux.md ("Ruling out
// arena-level fragmentation as the residual's mechanism"). On receiving
// SIGRTMIN+10, dumps glibc's malloc_info() to <OUTDIR>/<pid>.before.xml,
// calls malloc_trim(0), then dumps malloc_info() again to
// <OUTDIR>/<pid>.after.xml. Comparing the two before/after tells you
// whether a with/without-agent RSS gap is reclaimable (fragmentation/arena
// slack -- malloc_trim shrinks it back) or live in-use memory (malloc_trim
// changes nothing).
//
// SIGRTMIN+10 is used instead of SIGUSR2 because HotSpot claims SIGUSR2 as
// its own thread suspend/resume ("SR") signal on Linux and intercepts it
// before an LD_PRELOAD handler installed via signal() at library-load time
// ever sees it (confirmed via the JVM's own "stray SR signal" warning when
// SIGUSR2 was tried first).
//
// Build:   gcc -shared -fPIC -O2 -o malloc_info_probe.so malloc_info_probe.c
// Use:     LD_PRELOAD=/path/to/malloc_info_probe.so java ...
//          kill -RTMIN+10 <pid>
// Output dir defaults to /tmp/memsweep_mallocinfo; override by editing
// OUTDIR_DEFAULT below (kept a compile-time constant deliberately -- this
// is a scratch diagnostic tool, not a shipped one).
#define _GNU_SOURCE
#include <malloc.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define OUTDIR_DEFAULT "/tmp/memsweep_mallocinfo"

static void handler(int sig) {
    char path[256];

    snprintf(path, sizeof(path), OUTDIR_DEFAULT "/%d.before.xml", getpid());
    FILE *f = fopen(path, "w");
    if (f) {
        malloc_info(0, f);
        fclose(f);
    }

    malloc_trim(0);

    snprintf(path, sizeof(path), OUTDIR_DEFAULT "/%d.after.xml", getpid());
    f = fopen(path, "w");
    if (f) {
        malloc_info(0, f);
        fclose(f);
    }
}

__attribute__((constructor))
static void init(void) {
    signal(SIGRTMIN + 10, handler);
}
