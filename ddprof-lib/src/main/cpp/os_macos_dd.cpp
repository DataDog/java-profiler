#ifdef __APPLE__

#include "os_dd.h"
#include <signal.h>
#include <unistd.h>

int ddprof::OS::truncateFile(int fd) {
  int rslt = ftruncate(fd, 0);
  if (rslt == 0) {
    return lseek(fd, 0, SEEK_SET);
  }
  return rslt;
}

void ddprof::OS::mallocArenaMax(int arena_max) {
  // Not supported on macOS
}

SigAction ddprof::OS::replaceSigsegvHandler(SigAction action) {
  struct sigaction sa;
  sigaction(SIGSEGV, NULL, &sa);
  SigAction old_action = sa.sa_sigaction;
  sa.sa_sigaction = action;
  sigaction(SIGSEGV, &sa, NULL);
  return old_action;
}

#endif // __APPLE__
