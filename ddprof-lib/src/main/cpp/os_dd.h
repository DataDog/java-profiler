#ifndef _OS_DD_H
#define _OS_DD_H

#include "arch_dd.h"
#include "os.h"

namespace ddprof {
class OS : public ::OS {
 public:
  static int truncateFile(int fd);
  static SigAction replaceSigbusHandler(SigAction action);
  static int getMaxThreadId(int floor) {
      int maxThreadId = ::OS::getMaxThreadId();
      return maxThreadId < floor ? floor : maxThreadId;
    }
};
}

#endif // _OS_DD_H