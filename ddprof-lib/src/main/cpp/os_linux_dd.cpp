#ifdef __linux__

#include "os_dd.h"
#include "common.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

SigAction ddprof::OS::replaceSigsegvHandler(SigAction action) {
  return ::OS::replaceCrashHandler(action);
}

SigAction ddprof::OS::replaceSigbusHandler(SigAction action) {
  struct sigaction sa;
  sigaction(SIGBUS, NULL, &sa);
  SigAction old_action = sa.sa_sigaction;
  sa.sa_sigaction = action;
  sigaction(SIGBUS, &sa, NULL);
  return old_action;
}

bool ddprof::OS::isTlsPrimingAvailable() {
  return true; // TLS priming supported on Linux
}

int ddprof::OS::installTlsPrimeSignalHandler(SigHandler handler, int signal_offset) {
  int signal_num = SIGRTMIN + signal_offset;
  if (signal_num > SIGRTMAX) {
    TEST_LOG("No available RT signal for TLS priming: offset %d exceeds range (SIGRTMIN=%d, SIGRTMAX=%d)",
             signal_offset, SIGRTMIN, SIGRTMAX);
    return -1;
  }

  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  if (sigaction(signal_num, &sa, NULL) != 0) {
    TEST_LOG("Failed to install RT signal %d for TLS priming: %s (signal may be in use)",
             signal_num, strerror(errno));
    return -1;
  }

  TEST_LOG("Successfully installed TLS priming handler on RT signal %d", signal_num);
  return signal_num;
}

void ddprof::OS::uninstallTlsPrimeSignalHandler(int signal_num) {
  if (signal_num <= 0) {
    return;
  }

  struct sigaction sa;
  sa.sa_handler = SIG_DFL;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(signal_num, &sa, NULL) != 0) {
    TEST_LOG("Failed to uninstall RT signal %d for TLS priming: %s",
             signal_num, strerror(errno));
  } else {
    TEST_LOG("Successfully uninstalled TLS priming handler for RT signal %d", signal_num);
  }
}

void ddprof::OS::enumerateThreadIds(const std::function<void(int)>& callback) {
  DIR *task_dir = opendir("/proc/self/task");
  if (!task_dir) {
    TEST_LOG("Failed to open /proc/self/task: %s", strerror(errno));
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(task_dir)) != nullptr) {
    if (entry->d_name[0] >= '1' && entry->d_name[0] <= '9') {
      int tid = atoi(entry->d_name);
      if (tid > 0) {
        callback(tid);
      }
    }
  }
  closedir(task_dir);
}

void ddprof::OS::signalThread(int tid, int signum) {
  if (syscall(SYS_tgkill, getpid(), tid, signum) != 0 && errno != ESRCH) {
    TEST_LOG("Failed to signal thread %d with signal %d: %s", tid, signum, strerror(errno));
  }
}

int ddprof::OS::getThreadCount() {
  FILE *status = fopen("/proc/self/status", "r");
  if (!status) {
    return -1;
  }

  char line[256];
  int thread_count = -1;
  while (fgets(line, sizeof(line), status)) {
    if (sscanf(line, "Threads:\t%d", &thread_count) == 1) {
      break;
    }
  }
  fclose(status);
  return thread_count;
}

#endif // __linux__
