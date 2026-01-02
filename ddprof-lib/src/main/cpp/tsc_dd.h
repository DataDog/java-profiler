#ifndef _TSC_DD_H
#define _TSC_DD_H

#include "tsc.h"

namespace ddprof {
class TSC : public ::TSC {
public:
  static u64 ticks_to_millis(u64 ticks) {
    return TSC_SUPPORTED ? 1000 * ticks / frequency() : ticks / 1000 / 1000;
  }
};
}

#endif // _TSC_DD_H