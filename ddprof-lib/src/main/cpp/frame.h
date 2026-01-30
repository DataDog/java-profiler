#ifndef _FRAME_H
#define _FRAME_H

enum FrameTypeId {
  FRAME_INTERPRETED = 0,
  FRAME_JIT_COMPILED = 1,
  FRAME_INLINED = 2,
  FRAME_NATIVE = 3,
  FRAME_CPP = 4,
  FRAME_KERNEL = 5,
  FRAME_C1_COMPILED = 6,
  FRAME_NATIVE_REMOTE = 7,  // Native frame with remote symbolication (build-id + pc-offset)
  FRAME_TYPE_MAX = FRAME_NATIVE_REMOTE  // Maximum valid frame type
};

class FrameType {
public:
  static inline int encode(int type, int bci) {
    return (1 << 24) | (type << 25) | (bci & 0xffffff);
  }

  static inline FrameTypeId decode(int bci) {
    if ((bci >> 24) <= 0) {
      // Unencoded BCI (bit 24 not set) or negative special BCI values
      return FRAME_JIT_COMPILED;
    }
    // Clamp to valid FrameTypeId range to defend against corrupted values
    int raw_type = bci >> 25;
    return (FrameTypeId)(raw_type <= FRAME_TYPE_MAX ? raw_type : FRAME_TYPE_MAX);
  }
};

#endif // _FRAME_H
