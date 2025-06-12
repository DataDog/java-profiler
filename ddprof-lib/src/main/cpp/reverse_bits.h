//
// Borrow the implementation from openjdk
// https://github.com/openjdk/jdk/blob/master/src/hotspot/share/utilities/reverse_bits.hpp
//

#ifndef REVERSE_BITS_H
#define REVERSE_BITS_H
#include "arch_dd.h"
#include <stdint.h>

static constexpr u32 rep_5555 = static_cast<u32>(UINT64_C(0x5555555555555555));
static constexpr u32 rep_3333 = static_cast<u32>(UINT64_C(0x3333333333333333));
static constexpr u32 rep_0F0F = static_cast<u32>(UINT64_C(0x0F0F0F0F0F0F0F0F));

inline u16 reverse16(u16 v) {
  u32 x = static_cast<u32>(v);
  x = ((x & rep_5555) << 1) | ((x >> 1) & rep_5555);
  x = ((x & rep_3333) << 2) | ((x >> 2) & rep_3333);
  x = ((x & rep_0F0F) << 4) | ((x >> 4) & rep_0F0F);
  return __builtin_bswap16(static_cast<u16>(x));
}

#endif //REVERSE_BITS_H
