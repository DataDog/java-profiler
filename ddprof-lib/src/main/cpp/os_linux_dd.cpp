/*
 * Copyright 2018 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef __linux__

#include "os_dd.h"
#include <signal.h>

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
