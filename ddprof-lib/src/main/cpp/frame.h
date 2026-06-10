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
  // Maximu size of a single Java method is 64KB of bytecode instructions
  static constexpr int BCI_MASK = 0xffff;
  static constexpr int TYPE_SHIFT = 21;
  static constexpr int ENCODED_MASK = 1 << 20;  // bit indicates that value is encoded
  static constexpr int RAW_POINTER_MASK = 1 << 30;
public:
  static inline int encode(int type, int bci, bool rawPointer = false) {
    assert((!rawPointer || VM::isHotspot()) && "Raw pointer is only valid for hotspot");
    return ENCODED_MASK | (type << TYPE_SHIFT) | (bci & BCI_MASK) | (rawPointer ? RAW_POINTER_MASK : 0);
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
