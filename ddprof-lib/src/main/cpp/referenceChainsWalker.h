/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFERENCECHAINSWALKER_H
#define _REFERENCECHAINSWALKER_H

#include "arch.h"
#include "hotspot/vmStructs.h"

// doc/architecture/LiveHeapReferenceChains-VMStructsWalkImplementationPlan.md,
// Phase 3: a manual, JVMTI-independent one-hop field/element walker for a
// single object, built directly on the VMStructs primitives (oop-map blocks,
// array layout_helper decoding, compressed-oop decode) landed in Phases 1-2.
// Deliberately ignorant of FrontierTable/tag semantics - this component only
// discovers direct oop children and reports them to a caller-supplied
// visitor; admission into the frontier (tag allocation, budget accounting,
// root-kind attribution) is Phase 4's job, done by the caller of
// FieldWalker::walkOneHop().
//
// Safety contract this component assumes but does not itself enforce: `obj`
// is a valid, live, non-moving oop for the duration of the call. That only
// holds while the VM is at a safepoint (mirrors the same assumption
// heapReferenceCallback() relies on for its own raw-oop reads inside
// FollowReferences, referenceChains.h's header comment) - callers outside a
// safepoint (e.g. the debug-native test seam) are responsible for pinning
// that guarantee some other way (a non-concurrent-GC test JVM configuration,
// or wrapping the call in a real JVMTI Heap-category operation).
class FieldWalker {
public:
  // One child oop discovered by walkOneHop(), together with the slot it came
  // from: an instance field's byte offset (mirrors
  // jvmtiHeapReferenceInfoField::index/offset shape) or an array element
  // index. `child` may be 0 (null field/element) - the visitor decides
  // whether to skip nulls; walkOneHop() itself never filters them, since
  // "null fields are skipped, not crashed on" is a walkOneHop()-level
  // guarantee about not dereferencing null, not about hiding them from the
  // visitor.
  typedef void (*Visitor)(uintptr_t child, int field_slot, void *user_data);

  // Fail-closed gate mirroring VMKlass::oopMapAvailable()/
  // arrayLayoutAvailable(): false if any VMStructs primitive walkOneHop()
  // depends on failed to resolve. Callers (Phase 4's dispatch gate) must
  // check this before ever calling walkOneHop().
  static bool available() {
    return VMKlass::oopMapAvailable() && VMKlass::arrayLayoutAvailable();
  }

  FieldWalker();
  ~FieldWalker();

  // Visits every direct oop-typed field (instance) or element (object array)
  // of `obj`, calling `visitor(child, field_slot, user_data)` for each, up
  // to `max_children` visits per call. Returns the number of children
  // actually produced. A primitive array or a klass with no oop map yields
  // zero. A self-referential cycle (obj is its own field's value) is
  // reported like any other child exactly once per occurrence in the
  // oop-map/array - deduping repeat discoveries across hops is the frontier
  // table's job (tag-already-admitted checks), not this component's.
  //
  // If the object has more children than fit in one call (`max_children`
  // reached before exhausting the oop-map/array), the walk is left
  // resumable: the next call to walkOneHop() with the *same* `obj` continues
  // from where this call stopped rather than restarting, as long as no
  // intervening beginWalk()/walkOneHop() call was made for a different
  // object. Call hasMore() to check whether a resume is pending.
  int walkOneHop(uintptr_t obj, Visitor visitor, void *user_data, int max_children);

  // True if a prior walkOneHop() call stopped mid-object (max_children
  // reached) and a same-object resume is pending.
  bool hasMore() const { return _stack_size > 0; }

private:
  // Explicit heap-allocated (calloc/realloc, mirroring FrontierTable's own
  // growth path, referenceChains.cpp:33) work-list, not C++ recursion or an
  // STL container - this is the "not broken, understated" constraint from
  // the design doc: walkOneHop() must not risk a Java-heap allocation or a
  // safepoint-triggering call while it holds the VM at (what Phase 4's real
  // caller guarantees is) a safepoint. In practice at most one frame is ever
  // live at a time (an instance's oop-map blocks and an array's elements are
  // both flat, not nested), but modeling it as a stack rather than a bare
  // struct field is what makes a future nested-structure extension (if one
  // is ever needed) an addition here rather than a rewrite, and is what
  // makes the mid-object resume (`max_children` cutoff) a natural "leave the
  // top frame in place" operation instead of a special case.
  struct WalkFrame {
    uintptr_t obj;         // the object this frame is walking
    bool is_object_array;  // true: array element iteration; false: oop-map iteration
    int block_or_index;    // instance: current oop-map block index; array: next element index
    int offset_in_block;   // instance only: next field offset within the current block
  };

  WalkFrame *_stack;
  int _stack_size;
  int _stack_cap;

public:
  // Setter for ManualWalkGuard (referenceChainsWalker.cpp, anonymous
  // namespace) to flip the flag for the duration of walkOneHop() - not
  // itself part of the public API, but a free function/anonymous-namespace
  // class can't be granted friend access to a private static member
  // declared here without naming it at its actual (anonymous) namespace,
  // so this is exposed as a narrow setter instead.
  static void setInManualWalk(bool value) { t_inManualWalk = value; }

private:
  // debug-build-only self-check that the C-heap growth path below is only
  // ever reached from inside a guarded walkOneHop() call - see .cpp for the
  // full rationale and its documented limits.
  static thread_local bool t_inManualWalk;

  void push(const WalkFrame &frame);
  WalkFrame &top();
  void pop();
  bool growIfNeeded();

  int walkInstance(WalkFrame &frame, Visitor visitor, void *user_data, int max_children, bool *exhausted);
  int walkObjectArray(WalkFrame &frame, Visitor visitor, void *user_data, int max_children, bool *exhausted);
};

#endif // _REFERENCECHAINSWALKER_H
