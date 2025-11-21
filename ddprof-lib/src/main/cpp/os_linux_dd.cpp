#ifdef __linux__

#include "os_dd.h"
#include "common.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <memory>

#ifndef __musl__
#include <malloc.h>
#endif

#ifdef __LP64__
#define MMAP_SYSCALL __NR_mmap
#else
#define MMAP_SYSCALL __NR_mmap2
#endif

// Thread directory watcher state
static std::atomic<bool> g_watcher_running{false};
static std::atomic<int> g_watcher_fd{-1};
static pthread_t g_watcher_thread;
static std::atomic<bool> g_watcher_thread_created{false};
static std::function<void(int)> g_on_new_thread;
static std::function<void(int)> g_on_dead_thread;

static void* threadDirectoryWatcherLoop(void* arg);

// Fork handler to reset watcher state in child process
static void resetWatcherStateInChild() {
  // After fork(), child process doesn't have the watcher thread
  // Reset all state to prevent deadlock when child tries to cleanup
  g_watcher_running.store(false);
  g_watcher_thread_created.store(false);

  // Close the inherited fd in child to prevent issues
  int fd = g_watcher_fd.exchange(-1);
  if (fd >= 0) {
    close(fd);
  }

  // Clear callback functions to prevent accidental invocation
  g_on_new_thread = nullptr;
  g_on_dead_thread = nullptr;
}

// Register fork handler on first use
static void ensureForkHandlerRegistered() {
  static bool registered = false;
  if (!registered) {
    pthread_atfork(nullptr, nullptr, resetWatcherStateInChild);
    registered = true;
  }
}

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

bool ddprof::OS::startThreadDirectoryWatcher(const std::function<void(int)>& on_new_thread, const std::function<void(int)>& on_dead_thread) {
  // Ensure fork handler is registered to prevent deadlock in child processes
  ensureForkHandlerRegistered();

  if (g_watcher_running.load()) {
    return true; // Already running
  }

  int inotify_fd = inotify_init1(IN_CLOEXEC | IN_NONBLOCK);
  if (inotify_fd == -1) {
    TEST_LOG("Failed to initialize inotify: %s", strerror(errno));
    return false;
  }

  int watch_fd = inotify_add_watch(inotify_fd, "/proc/self/task", IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
  if (watch_fd == -1) {
    TEST_LOG("Failed to add inotify watch on /proc/self/task: %s", strerror(errno));
    close(inotify_fd);
    return false;
  }

  g_on_new_thread = on_new_thread;
  g_on_dead_thread = on_dead_thread;
  g_watcher_fd.store(inotify_fd);
  g_watcher_running.store(true);

  if (pthread_create(&g_watcher_thread, nullptr, threadDirectoryWatcherLoop, nullptr) != 0) {
    TEST_LOG("Failed to create thread directory watcher thread: %s", strerror(errno));
    g_watcher_running.store(false);
    g_watcher_fd.store(-1);
    close(inotify_fd);
    return false;
  }

  g_watcher_thread_created.store(true);
  TEST_LOG("Started thread directory watcher (thread will be joined on cleanup)");
  return true;
}

void ddprof::OS::stopThreadDirectoryWatcher() {
  if (!g_watcher_running.load()) {
    return;
  }

  TEST_LOG("Stopping thread directory watcher...");

  // Signal the watcher thread to stop
  g_watcher_running.store(false);

  // Close the inotify fd to wake up select()
  int fd = g_watcher_fd.exchange(-1);
  if (fd >= 0) {
    close(fd);
  }

  // Wait for the watcher thread to actually terminate
  if (g_watcher_thread_created.load()) {
    TEST_LOG("Waiting for watcher thread to terminate...");
    void* retval;
    int join_result = pthread_join(g_watcher_thread, &retval);
    if (join_result != 0) {
      TEST_LOG("Failed to join watcher thread: %s", strerror(join_result));
    } else {
      TEST_LOG("Watcher thread terminated successfully");
    }
    g_watcher_thread_created.store(false);
  }

  TEST_LOG("Thread directory watcher stopped");
}

static void* threadDirectoryWatcherLoop(void* arg) {
  const int fd = g_watcher_fd.load();
  if (fd < 0) return nullptr;

  char buffer[4096];
  fd_set readfds;
  struct timeval timeout;

  while (g_watcher_running.load()) {
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int ret = select(fd + 1, &readfds, nullptr, nullptr, &timeout);
    if (ret < 0) {
      if (errno != EINTR) {
        TEST_LOG("Thread directory watcher select failed: %s", strerror(errno));
        break;
      }
      continue;
    }

    if (ret == 0) continue; // Timeout, check running flag

    ssize_t len = read(fd, buffer, sizeof(buffer));
    if (len <= 0) {
      if (len < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
        TEST_LOG("Thread directory watcher read failed: %s", strerror(errno));
        break;
      }
      continue;
    }

    // Parse inotify events
    for (ssize_t i = 0; i < len;) {
      struct inotify_event *event = (struct inotify_event *)(buffer + i);

      if (event->mask & IN_Q_OVERFLOW) {
        TEST_LOG("Thread directory watcher queue overflow, triggering full rescan");
        // TODO: Trigger full rescan callback
      } else if (event->len > 0 && event->name[0] >= '1' && event->name[0] <= '9') {
        int tid = atoi(event->name);
        if (tid > 0) {
          if (event->mask & (IN_CREATE | IN_MOVED_TO)) {
            if (g_on_new_thread) g_on_new_thread(tid);
          } else if (event->mask & (IN_DELETE | IN_MOVED_FROM)) {
            if (g_on_dead_thread) g_on_dead_thread(tid);
          }
        }
      }

      i += sizeof(struct inotify_event) + event->len;
    }
  }

  return nullptr;
}

#endif // __linux__
