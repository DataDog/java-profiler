#ifndef _FRAME_H
#define _FRAME_H

#include <cassert>
#include "vmEntry.h"

enum FrameTypeId {
  FRAME_INTERPRETED = 0,
  FRAME_JIT_COMPILED = 1,
  FRAME_INLINED = 2,
  FRAME_NATIVE = 3,
  FRAME_CPP = 4,
  FRAME_KERNEL = 5,
  FRAME_C1_COMPILED = 6,
  FRAME_NATIVE_REMOTE = 7,  // Native frame with remote symbolication (build-id + pc-offset)
  FRAME_TYPE_MAX = FRAME_NATIVE_REMOTE,  // Maximum valid frame type
  FRAME_TYPE_MASK = 0x7
};

class FrameType {
  // Maximum Java method size is 65535 bytes of bytecode (JVM spec §4.7.3), so valid BCIs
  // are 0–65534; BCI_MASK = 0xffff leaves 65535 as the only unreachable value and is used
  // as a sentinel: HotSpot ScopeDesc::decode() returns -1 for method-entry and
  // synchronization-entry locations, which truncates to BCI_MASK under 16-bit masking.
  static constexpr int BCI_MASK = 0xffff;
  static constexpr int TYPE_SHIFT = 21;
  static constexpr int ENCODED_MASK = 1 << 20;  // bit indicates that value is encoded
  static constexpr int RAW_POINTER_MASK = 1 << 30;
public:
  static inline int encode(int type, int bci, bool rawPointer = false) {
    assert((!rawPointer || VM::isHotspot()) && "Raw pointer is only valid for hotspot");
    assert(type >= FRAME_INTERPRETED && type <= FRAME_TYPE_MAX);
    // HotSpot ScopeDesc::decode() returns -1 for method-entry and synchronization-entry
    // locations; map any negative BCI to 0 rather than storing 0xffff in the low bits.
    int bci_bits = (bci < 0) ? 0 : (bci & BCI_MASK);
    return ENCODED_MASK | (type << TYPE_SHIFT) | bci_bits | (rawPointer ? RAW_POINTER_MASK : 0);
  }

  static inline int bci(int bci) {
    return (bci & BCI_MASK);
  }
  
  static inline FrameTypeId decode(int bci) {
    if ((bci & ENCODED_MASK) == 0 || bci < 0) {
      // Unencoded BCI (ENCODED_SHIFT bit not set) or negative special BCI values
      return FRAME_JIT_COMPILED;
    }

    // Clamp to valid FrameTypeId range to defend against corrupted values
    return (FrameTypeId)((bci >> TYPE_SHIFT) & FRAME_TYPE_MASK);
  }

  static inline bool isRawPointer(int bci) {
    return bci > 0 && (bci & RAW_POINTER_MASK) != 0;
  }
};

#endif // _FRAME_H
