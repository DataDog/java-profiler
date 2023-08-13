#ifndef _FRAME_H
#define _FRAME_H


enum FrameTypeId {
    FRAME_INTERPRETED  = 0,
    FRAME_JIT_COMPILED = 1,
    FRAME_INLINED      = 2,
    FRAME_NATIVE       = 3,
    FRAME_CPP          = 4,
    FRAME_KERNEL       = 5,
    FRAME_C1_COMPILED  = 6,
};

const static int FRAME_UNRESOLVED = 16 << 25;

class FrameType {
  public:
    static inline int encode(int type, int bci) {
        return (1 << 24) | (type << 25) | (bci & 0xffffff) | (bci & FRAME_UNRESOLVED);
    }

    static inline FrameTypeId decode(int bci) {
        bci &= ~FRAME_UNRESOLVED;
        return (bci >> 24) > 0 ? (FrameTypeId)(bci >> 25) : FRAME_JIT_COMPILED;
    }
};

#endif // _FRAME_H

