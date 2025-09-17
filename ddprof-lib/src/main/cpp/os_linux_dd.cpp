#ifdef __linux__

#include "os_dd.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef __musl__
#include <malloc.h>
#endif

#ifdef __LP64__
#define MMAP_SYSCALL __NR_mmap
#else
#define MMAP_SYSCALL __NR_mmap2
#endif

int ddprof::OS::truncateFile(int fd) {
  int rslt = ftruncate(fd, 0);
  if (rslt == 0) {
    return lseek(fd, 0, SEEK_SET);
  }
  return rslt;
}

void ddprof::OS::mallocArenaMax(int arena_max) {
#ifndef __musl__
  mallopt(M_ARENA_MAX, arena_max);
#endif
}

SigAction ddprof::OS::replaceSigbusHandler(SigAction action) {
  struct sigaction sa;
  sigaction(SIGBUS, NULL, &sa);
  SigAction old_action = sa.sa_sigaction;
  sa.sa_sigaction = action;
  sigaction(SIGBUS, &sa, NULL);
  return old_action;
}

#endif // __linux__
