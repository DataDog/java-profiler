#ifndef _FRAME_H
#define _FRAME_H

enum FrameTypeId {
  FRAME_INTERPRETED = 0,
  FRAME_INTERPRETED_METHOD = 8,
  FRAME_JIT_COMPILED = 2,
  FRAME_INLINED = 3,
  FRAME_NATIVE = 4,
  FRAME_CPP = 5,
  FRAME_KERNEL = 5,
  FRAME_C1_COMPILED = 6,
  FRAME_NATIVE_REMOTE = 7,  // Native frame with remote symbolication (build-id + pc-offset)
};

class FrameType {
public:
  static inline int encode(int type, int bci) {
    return (1 << 24) | (type << 25) | (bci & 0xffffff);
  }

  static inline FrameTypeId decode(int bci) {
    return (bci >> 24) > 0 ? (FrameTypeId)(bci >> 25) : FRAME_JIT_COMPILED;
  }
};

#endif // _FRAME_H
