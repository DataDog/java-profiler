#ifndef _FRAME_H
#define _FRAME_H

enum FrameTypeId {
  FRAME_INTERPRETED = 0,        // Interpreted Java frame, method is presented with jmethodID
  FRAME_INTERPRETED_METHOD = 1, // Interpreted Java frame, method is presented with Method*
  FRAME_JIT_COMPILED = 2,
  FRAME_INLINED = 3,
  FRAME_NATIVE = 4,
  FRAME_CPP = 5,
  FRAME_KERNEL = 6,
  FRAME_C1_COMPILED = 7,
  FRAME_NATIVE_REMOTE = 8,  // Native frame with remote symbolication (build-id + pc-offset)
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
