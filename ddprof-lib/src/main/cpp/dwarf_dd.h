#ifndef _DWARF_DD_H
#define _DWARF_DD_H

#include "arch_dd.h"
#include "dwarf.h"
#include <stddef.h>

#if defined(__x86_64__)
const int LINKED_FRAME_CLANG_SIZE = LINKED_FRAME_SIZE;

#elif defined(__i386__)

const int LINKED_FRAME_CLANG_SIZE = LINKED_FRAME_SIZE;

#elif defined(__aarch64__)

// clang compiler uses different frame layout than GCC
const int LINKED_FRAME_CLANG_SIZE = 2 * DW_STACK_SLOT;

#else

const int LINKED_FRAME_CLANG_SIZE = LINKED_FRAME_SIZE;

#endif

namespace ddprof {
struct FrameDesc : ::FrameDesc {
  using ::FrameDesc::FrameDesc;
  static ::FrameDesc default_clang_frame;
};
}

#endif // _DWARF_DD_H
