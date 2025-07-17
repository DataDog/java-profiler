#include "os_dd.h"
#ifdef __linux__

#include <arpa/inet.h>
#include <byteswap.h>
#include <dirent.h>
#include <fcntl.h>
#include <sched.h>
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

#ifndef __musl__
#include <malloc.h>
#endif

int ddprof::OS::truncateFile(int fd) {
  int rslt = ftruncate(fd, 0);
  if (rslt == 0) {
    return lseek(fd, 0, SEEK_SET);
  }
  return rslt;
}

SigAction OS::replaceSigbusHandler(SigAction action) {
  struct sigaction sa;
  sigaction(SIGBUS, NULL, &sa);
  SigAction old_action = sa.sa_sigaction;
  sa.sa_sigaction = action;
  sigaction(SIGBUS, &sa, NULL);
  return old_action;
}

#endif

