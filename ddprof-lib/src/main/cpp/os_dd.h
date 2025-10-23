#ifndef _OS_DD_H
#define _OS_DD_H

#include "arch_dd.h"
#include "os.h"
#include <functional>

namespace ddprof {
class OS : public ::OS {
public:
  static SigAction replaceSigsegvHandler(SigAction action);
  static SigAction replaceSigbusHandler(SigAction action);

  inline static int getMaxThreadId(int floor) {
    int maxThreadId = ::OS::getMaxThreadId();
    return maxThreadId < floor ? floor : maxThreadId;
  }
  static int truncateFile(int fd);
  static void mallocArenaMax(int arena_max);

  // TLS priming support
  static bool isTlsPrimingAvailable();
  static int installTlsPrimeSignalHandler(SigHandler handler, int signal_offset = 4);
  static void uninstallTlsPrimeSignalHandler(int signal_num);
  static void enumerateThreadIds(const std::function<void(int)>& callback);
  static bool startThreadDirectoryWatcher(const std::function<void(int)>& on_new_thread, const std::function<void(int)>& on_dead_thread);
  static int getThreadCount();
  static void stopThreadDirectoryWatcher();
  // Thread registration for TLS priming (macOS only)
  static void registerCurrentThreadForTlsPriming();
};
}
#endif // _OS_DD_H
