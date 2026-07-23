/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChainsWalker.h"
#include "hotspot/vmStructs.inline.h"
#include <cassert>
#include <cstdlib>

thread_local bool FieldWalker::t_inManualWalk = false;

namespace {
// Mirrors GCCallbackGuard (referenceChains.cpp) - marks this thread as
// "inside a manual field walk" for the duration of walkOneHop(). There is no
// general "no allocation/safepoint call happened" detector to plug this
// into (unlike t_inGCCallback, which a small fixed set of JVMTI Heap-call
// sites can assert against), so this only ever catches one concrete
// regression: FieldWalker's own C-heap stack-growth path (growIfNeeded())
// being reached from somewhere other than a guarded walkOneHop() call. It
// does not catch a future edit that introduces `new`/an STL container/a
// JVMTI call inside walkOneHop() itself - that class of bug still needs
// code review, as documented in the implementation plan.
class ManualWalkGuard {
public:
  ManualWalkGuard() { FieldWalker::setInManualWalk(true); }
  ~ManualWalkGuard() { FieldWalker::setInManualWalk(false); }
};
} // namespace

FieldWalker::FieldWalker() : _stack(nullptr), _stack_size(0), _stack_cap(0) {}

FieldWalker::~FieldWalker() {
  free(_stack);
}

bool FieldWalker::growIfNeeded() {
  assert(t_inManualWalk &&
         "FieldWalker's C-heap growth path must only run inside a "
         "walkOneHop() call - see ManualWalkGuard's comment");
  if (_stack_size < _stack_cap) {
    return true;
  }
  int new_cap = _stack_cap == 0 ? 4 : _stack_cap * 2;
  WalkFrame *tmp = (WalkFrame *)realloc(_stack, (size_t)new_cap * sizeof(WalkFrame));
  if (tmp == nullptr) {
    return false;
  }
  _stack = tmp;
  _stack_cap = new_cap;
  return true;
}

void FieldWalker::push(const WalkFrame &frame) {
  if (!growIfNeeded()) {
    // Out of C-heap memory: drop the frame rather than crash - the object
    // this would have walked is simply not expanded this hop, same
    // fail-soft posture FrontierTable::growLocked() takes on calloc/realloc
    // failure (referenceChains.cpp).
    return;
  }
  _stack[_stack_size++] = frame;
}

FieldWalker::WalkFrame &FieldWalker::top() {
  assert(_stack_size > 0);
  return _stack[_stack_size - 1];
}

void FieldWalker::pop() {
  assert(_stack_size > 0);
  _stack_size--;
}

// frame.offset_in_block == -1 is the sentinel for "haven't started the
// current oop-map block yet" - a real field offset is never 0 (that's the
// object header/mark word, never an oop-map block's _offset), but using an
// explicit sentinel rather than relying on that keeps the intent obvious.
static constexpr int kBlockNotStarted = -1;

int FieldWalker::walkInstance(WalkFrame &frame, Visitor visitor, void *user_data, int max_children, bool *exhausted) {
  VMKlass *klass = VMKlass::fromOop(frame.obj);
  if (klass == nullptr || !VMKlass::oopMapAvailable()) {
    *exhausted = true;
    return 0;
  }
  int produced = 0;
  int block_count = klass->oopMapCount();
  int oop_size = VMStructs::isCompressedOopsEnabled() ? (int)sizeof(uint32_t) : (int)sizeof(void *);
  while (produced < max_children && frame.block_or_index < block_count) {
    VMOopMapBlock *block = klass->oopMapBlockAt(frame.block_or_index);
    int block_offset = block->fieldOffset();
    int block_end = block_offset + block->fieldCount() * oop_size;
    if (frame.offset_in_block == kBlockNotStarted) {
      frame.offset_in_block = block_offset;
    }
    while (produced < max_children && frame.offset_in_block < block_end) {
      uintptr_t field_addr = frame.obj + (uintptr_t)frame.offset_in_block;
      uintptr_t child = VMStructs::isCompressedOopsEnabled()
                             ? VMStructs::decodeOop(*(uint32_t *)field_addr)
                             : *(uintptr_t *)field_addr;
      visitor(child, frame.offset_in_block, user_data);
      produced++;
      frame.offset_in_block += oop_size;
    }
    if (frame.offset_in_block >= block_end) {
      frame.block_or_index++;
      frame.offset_in_block = kBlockNotStarted;
    }
  }
  *exhausted = frame.block_or_index >= block_count;
  return produced;
}

int FieldWalker::walkObjectArray(WalkFrame &frame, Visitor visitor, void *user_data, int max_children, bool *exhausted) {
  VMKlass *klass = VMKlass::fromOop(frame.obj);
  if (klass == nullptr || !klass->isObjectArrayKlass()) {
    *exhausted = true;
    return 0;
  }
  int length = VMKlass::arrayLength(frame.obj);
  int produced = 0;
  while (produced < max_children && frame.block_or_index < length) {
    uintptr_t child = klass->arrayElementAt(frame.obj, frame.block_or_index);
    visitor(child, frame.block_or_index, user_data);
    produced++;
    frame.block_or_index++;
  }
  *exhausted = frame.block_or_index >= length;
  return produced;
}

int FieldWalker::walkOneHop(uintptr_t obj, Visitor visitor, void *user_data, int max_children) {
  ManualWalkGuard guard;
  if (obj == 0 || max_children <= 0) {
    return 0;
  }

  if (_stack_size == 0 || top().obj != obj) {
    // Fresh walk of `obj`: discard any stale resume state left over from a
    // different object. Phase 4 (the only intended caller) never
    // interleaves a partial walk of one object with a walkOneHop() call for
    // another, so this branch only fires on genuine first visits, never on
    // a real resume.
    _stack_size = 0;
    VMKlass *klass = VMKlass::fromOop(obj);
    if (klass == nullptr) {
      return 0;
    }
    if (!VMKlass::arrayLayoutAvailable() || !klass->isArrayKlass()) {
      if (!VMKlass::oopMapAvailable()) {
        return 0;
      }
      WalkFrame frame;
      frame.obj = obj;
      frame.is_object_array = false;
      frame.block_or_index = 0;
      frame.offset_in_block = kBlockNotStarted;
      push(frame);
    } else if (klass->isObjectArrayKlass()) {
      WalkFrame frame;
      frame.obj = obj;
      frame.is_object_array = true;
      frame.block_or_index = 0;
      frame.offset_in_block = kBlockNotStarted;
      push(frame);
    } else {
      // Primitive array: no oop children, nothing to push.
      return 0;
    }
    if (_stack_size == 0) {
      // push() dropped the frame (OOM) - nothing to walk this call.
      return 0;
    }
  }

  WalkFrame &frame = top();
  bool exhausted = false;
  int produced = frame.is_object_array ? walkObjectArray(frame, visitor, user_data, max_children, &exhausted)
                                        : walkInstance(frame, visitor, user_data, max_children, &exhausted);
  if (exhausted) {
    pop();
  }
  return produced;
}
