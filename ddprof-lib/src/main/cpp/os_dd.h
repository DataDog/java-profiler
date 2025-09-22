#ifndef _OS_DD_H
#define _OS_DD_H

#include "arch_dd.h"
#include "os.h"

namespace ddprof {
class OS : public ::OS {
public:
  static SigAction replaceSigsegvHandler(SigAction action);

  inline static SigAction replaceSigbusHandler(SigAction action) {
    return ::OS::replaceCrashHandler(action);
  }

  inline static int getMaxThreadId(int floor) {
    int maxThreadId = ::OS::getMaxThreadId();
    return maxThreadId < floor ? floor : maxThreadId;
  }
  static int truncateFile(int fd);
  static void mallocArenaMax(int arena_max);
};
}
#endif // _OS_DD_H
