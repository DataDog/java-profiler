#ifdef __APPLE__

#include "os_dd.h"
#include "common.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/task.h>
#include <mach/thread_act.h>

// macOS thread management

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

SigAction ddprof::OS::replaceSigbusHandler(SigAction action) {
  return ::OS::replaceCrashHandler(action);
}

SigAction ddprof::OS::replaceSigsegvHandler(SigAction action) {
  struct sigaction sa;
  sigaction(SIGSEGV, NULL, &sa);
  SigAction old_action = sa.sa_sigaction;
  sa.sa_sigaction = action;
  sigaction(SIGSEGV, &sa, NULL);
  return old_action;
}

bool ddprof::OS::isTlsPrimingAvailable() {
  return false; // TLS priming disabled on macOS
}

int ddprof::OS::installTlsPrimeSignalHandler(SigHandler handler, int signal_offset) {
  return -1; // TLS priming not supported on macOS
}

void ddprof::OS::uninstallTlsPrimeSignalHandler(int signal_num) {
  // No-op on macOS since TLS priming is not supported
}

void ddprof::OS::enumerateThreadIds(const std::function<void(int)>& callback) {
  // Get current task
  task_t task = mach_task_self();
  
  // Get thread list
  thread_act_array_t thread_list;
  mach_msg_type_number_t thread_count;
  
  kern_return_t kr = task_threads(task, &thread_list, &thread_count);
  if (kr != KERN_SUCCESS) {
    TEST_LOG("Failed to get thread list: %d", kr);
    return;
  }
  
  // Call callback for each thread
  for (mach_msg_type_number_t i = 0; i < thread_count; i++) {
    callback(static_cast<int>(thread_list[i]));
  }
  
  // Clean up
  vm_deallocate(task, (vm_address_t)thread_list, thread_count * sizeof(thread_t));
}

void ddprof::OS::signalThread(int tid, int signum) {
  // On macOS, tid is actually a mach thread port
  thread_t thread = static_cast<thread_t>(tid);
  
  // Convert mach thread to pthread for signaling
  // This is a limitation - we can't easily signal arbitrary mach threads
  // In practice, this is mainly used for TLS priming which is disabled on macOS
  TEST_LOG("Thread signaling not fully supported on macOS (thread=%d, signal=%d)", tid, signum);
}

bool ddprof::OS::startThreadDirectoryWatcher(const std::function<void(int)>& on_new_thread, const std::function<void(int)>& on_dead_thread) {
  return false; // Thread directory watching not supported on macOS
}

int ddprof::OS::getThreadCount() {
  task_t task = mach_task_self();
  thread_act_array_t thread_list;
  mach_msg_type_number_t thread_count;
  
  kern_return_t kr = task_threads(task, &thread_list, &thread_count);
  if (kr != KERN_SUCCESS) {
    TEST_LOG("Failed to get thread count: %d", kr);
    return 0;
  }
  
  // Clean up
  vm_deallocate(task, (vm_address_t)thread_list, thread_count * sizeof(thread_t));
  
  return static_cast<int>(thread_count);
}

void ddprof::OS::stopThreadDirectoryWatcher() {
  // No-op on macOS
}

void ddprof::OS::registerCurrentThreadForTlsPriming() {
  // Not supported on macOS
}

#endif // __APPLE__
