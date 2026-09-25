/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef _REFERENCECHAINFRONTIER_H
#define _REFERENCECHAINFRONTIER_H

#include "arch.h"
#include "common.h"
#include "spinLock.h"
#include <atomic>
#include <climits>
#include <cstring>
#include <jni.h>
#include <jvmti.h>
#include <unordered_map>
#include <vector>

namespace FrontierEntryState {
constexpr u8 FRONTIER = 0;  // discovered, not yet expanded by FollowReferences
constexpr u8 EXPANDED = 1;  // expanded; children (if any) are in the table
constexpr u8 EDGE = 2;      // on a path toward a target sample (EdgeStore)
constexpr u8 ABANDONED = 3; // tag released; entry kept only to avoid reuse
} // namespace FrontierEntryState

// Search outcome; per-pass truncation does not imply abandonment.
namespace SearchState {
constexpr u8 RUNNING = 0;   // at least one more pass may still make progress
constexpr u8 COMPLETED = 1; // reachable graph fully explored within caps
constexpr u8 ABANDONED = 2; // TTL or frontier-size cap forced an incomplete stop
} // namespace SearchState

// Reason reported when a search is abandoned.
namespace SearchAbandonReason {
constexpr u8 NONE = 0;         // not (yet) abandoned
constexpr u8 FRONTIER_CAP = 1; // frontier-size cap hit
constexpr u8 TTL = 2;          // wall-clock TTL exceeded with work still pending
// Canary candidate-discovery has made no progress for NO_PROGRESS_PASS_LIMIT consecutive passes.
constexpr u8 CANARY_STUCK = 3;
} // namespace SearchAbandonReason

// Metadata for one tagged frontier object.
typedef struct FrontierEntry {
  jlong parent_tag;    // links back to the record that discovered this one
  u32 referrer_klass;  // StringDictionary id, 0 = unresolved/none
  u32 depth;           // hop count from the frontier's seed, for the hop cap
  u8 state;            // one of FrontierEntryState's constants
  // The leak tag assigned by LivenessTracker to this specific tracked object, copied from the JVMTI
  // tag at admission time.
  jlong leak_tag;
  // jvmtiHeapReferenceKind of the edge that admitted this entry, but only meaningful when
  // parent_tag == 0 (this entry is root-attached) - 0 (no JVMTI_HEAP_REFERENCE_* value is 0) for
  // every other entry, since a non-root entry's own referrer edge kind is not what
  // reconstructChain()'s callers want to report (they want to label the chain's root, not every
  // hop).
  u8 root_kind;
  // Raw JVMTI class tag of THIS entry's own object, from the shared, process-wide allocator
  // (classTagAllocator.h) - NOT referrer_klass above (a classMap dictionary id, which can differ
  // for the same class at different times if that dictionary gets compacted/regenerated - see
  // LivenessTracker::KlassPopulationEntry::stable_class_tag's own comment for the bug this was
  // found fixing).
  jlong class_tag;

  // Retention-edge identity of the edge that admitted THIS entry, captured at admission time for
  // the same cannot-replay-the-callback reason as class_tag above: it lets the emitted
  // datadog.ReferenceChain name the field each hop is retained through, turning the bare class list
  // into a readable path ("LeakHolder.SINK -> HashMap.table -> Entry.value") - which is the
  // diagnostic point of the whole feature.
  jint referrer_field_index;

  // jvmtiHeapReferenceKind of the admitting edge for an INTERIOR hop (an entry with parent_tag != 0
  // - "this object was reached from its parent via this kind of edge").
  u8 edge_kind;

  // Referrer's class tag when the referrer is a CLASS OBJECT rather than a frontier entry (a
  // root-attached static-field admission - the referrer is the declaring class, parent_tag == 0 so
  // there is no parent entry to read a class from).
  jlong referrer_class_tag;
} FrontierEntry;

// Per-hop retention-edge identity collected by reconstructChain() alongside the class chain:
// everything needed at emission to label HOW chain[i] is retained (the field of chain[i+1] pointing
// at it, or the root edge for the last hop).
typedef struct ChainHopEdge {
  // FrontierEntry::referrer_field_index/edge_kind of the entry for chain[i]
  jint field_index; // -1 = not a field/static-field edge
  u8 edge_kind;      // admitting edge kind (root hops: root_kind)
  // The referrer's raw class tag: the PARENT entry's class_tag for interior hops,
  // FrontierEntry::referrer_class_tag for root-attached hops.
  jlong referrer_class_tag;
} ChainHopEdge;

// Higher values identify longer-lived root kinds.
inline int rootKindDurability(u8 root_kind) {
  switch (root_kind) {
  case JVMTI_HEAP_REFERENCE_STATIC_FIELD:
  case JVMTI_HEAP_REFERENCE_SYSTEM_CLASS:
    return 3;
  case JVMTI_HEAP_REFERENCE_JNI_GLOBAL:
    return 2;
  case JVMTI_HEAP_REFERENCE_MONITOR:
  case JVMTI_HEAP_REFERENCE_STACK_LOCAL:
  case JVMTI_HEAP_REFERENCE_JNI_LOCAL:
  case JVMTI_HEAP_REFERENCE_THREAD:
  case JVMTI_HEAP_REFERENCE_OTHER:
    return 1;
  default:
    return 0; // root_kind's own "not set"/non-root-attached value
  }
}

// Stack and JNI locals are transient roots.
inline bool isTransientRootKind(u8 root_kind) {
  return root_kind == JVMTI_HEAP_REFERENCE_STACK_LOCAL ||
         root_kind == JVMTI_HEAP_REFERENCE_JNI_LOCAL;
}

// Tag-indexed slot table storing FrontierEntry metadata, modeled on LivenessTracker's TrackingEntry
// table (livenessTracker.h:21-30): CAS-safe doubling resize under a signal-safe SpinLock
// (spinLock.h), reusing its shared/exclusive split so reads (lookup) never race a resize.
class alignas(alignof(SpinLock)) FrontierTable {
private:
  // Provisional default pending empirical tuning - not benchmark-derived.
  static constexpr int INITIAL_TABLE_CAPACITY = 1024;

  // mutable: capacity()/maxCapacity() below are const accessors that still need to take this lock
  // to read _table_cap/_table_max_cap safely.
  mutable SpinLock _table_lock;
  // 1 + highest index ever inserted (informational upper bound for lookup(); never shrinks, since
  // tags/slots are never reused).
  std::atomic<int> _table_size;
  int _table_cap;
  int _table_max_cap;
  FrontierEntry *_table;

  // Grows _table (doubling) until it holds at least `required_cap` slots or _table_max_cap is
  // reached.
  bool growLocked(int required_cap);

public:
  // `max_cap` <= 0 disables the table (capacity() stays 0, every insert() reports exhaustion) -
  // callers are expected to guard on the config flag before constructing one, but this makes a
  // misconfigured cap fail safe rather than crash.
  explicit FrontierTable(int max_cap);
  ~FrontierTable();

  FrontierTable(const FrontierTable &) = delete;
  FrontierTable &operator=(const FrontierTable &) = delete;

  // Writes (parent_tag, referrer_klass, depth, state) into the slot for `tag` (index = tag - 1),
  // growing the table if needed.
  bool insert(jlong tag, jlong parent_tag, u32 referrer_klass, u32 depth,
              u8 state = FrontierEntryState::FRONTIER, u8 root_kind = 0,
              jlong class_tag = 0,
              jint referrer_field_index = -1, u8 edge_kind = 0,
              jlong referrer_class_tag = 0);

  // Reads the slot for `tag` into *out. Returns false (leaving *out untouched) if `tag` is not
  // positive or has never been inserted.
  bool lookup(jlong tag, FrontierEntry *out);

  // Runs `fn(this)` with the shared lock held for the whole call, for a caller that needs to look
  // up many tags back to back (e.g. the rotation collectors' O(size()) sweeps in
  // referenceChains.cpp) under ONE lock acquisition, instead of paying SpinLock's lock/unlock cost
  // on every single lookup() call.
  template <typename Fn> void withSharedLock(Fn &&fn) const {
    SharedLockGuard guard(&_table_lock);
    fn(this);
  }

  // Same as lookup() above, but assumes the caller already holds the shared lock via
  // withSharedLock() below.
  bool lookupLocked(jlong tag, FrontierEntry *out) const;

  // Marks metadata abandoned; the caller must clear the JVMTI tag.
  void clear(jlong tag);

  // Marks the slot as part of a resolved path.
  void markEdge(jlong tag);

  // Marks the slot after all outgoing edges have been visited.
  void markExpanded(jlong tag);

  // Updates only the recorded root kind.
  void updateRootKind(jlong tag, u8 root_kind);

  // Set the leak tag on a frontier entry (the JVMTI tag assigned by LivenessTracker to this
  // specific tracked leaking object).
  void setLeakTag(jlong tag, jlong leak_tag) {
    if (tag <= 0 || tag - 1 >= (jlong)INT_MAX) {
      return;
    }
    int idx = (int)(tag - 1);
    _table_lock.lock();
    if (idx < _table_size) {
      _table[idx].leak_tag = leak_tag;
    }
    _table_lock.unlock();
  }

  // Replace a shallow root-attached entry (parent_tag == 0, depth == 0) with a deeper
  // chain-attached entry when the object is reached via a longer path.
  bool improveChain(jlong tag, jlong parent_tag, u32 referrer_klass,
                     u32 depth, u8 root_kind, jint referrer_field_index = -1,
                     u8 edge_kind = 0, jlong referrer_class_tag = 0);

  // Equal-depth re-parenting, the one case improveChain() above cannot express: a depth-1 entry
  // whose current parent is a TRANSIENT root (stack local / JNI local - a momentarily-live frame)
  // is re-parented to a DURABLE root-attached parent (static field, JNI global, thread) when one is
  // seen admitting the same object at the same depth.
  bool reparentToDurableRoot(jlong tag, jlong new_parent_tag,
                              u32 referrer_klass,
                              jint referrer_field_index = -1, u8 edge_kind = 0);

  // Walks parent_tag links starting at `target_tag` back to a root-attached entry (parent_tag ==
  // 0), appending each visited entry's referrer_klass to *out_chain in leaf-to-root order.
  bool reconstructChain(jlong target_tag, std::vector<u32> *out_chain,
                        u8 *out_root_kind = nullptr,
                        std::vector<ChainHopEdge> *out_edges = nullptr,
                        FrontierEntry *out_terminal = nullptr);

  // Search restart (ReferenceChainTracker::restartSearch(), this class's own header comment): marks
  // every slot unoccupied again without releasing _table's allocation - a new search's nextTag()
  // sequence restarts at 1, reusing these same slot indices, so lookup()/insert() must not read
  // back the previous search's now-irrelevant entries for them.
  void resetForRestart() {
    _table_lock.lock();
    _table_size.store(0, std::memory_order_relaxed);
    _table_lock.unlock();
  }

  // Debug-only test seam (ReferenceChainTracker::resetSearchStateForTest()).
  void resetCapacityForTest(int max_cap);

  // _table_cap/_table_max_cap are plain ints, not atomics like _table_size, and
  // resetCapacityForTest() (debug-only test seam, see its own comment) rewrites both under
  // _table_lock after freeing/reallocating _table.
  int capacity() const {
    _table_lock.lock();
    int cap = _table_cap;
    _table_lock.unlock();
    return cap;
  }
  int maxCapacity() const {
    _table_lock.lock();
    int max_cap = _table_max_cap;
    _table_lock.unlock();
    return max_cap;
  }

  // Current upper bound on assigned slots (mirrors _table_size's own comment: "1 + highest index
  // ever inserted").
  int size() const { return _table_size.load(std::memory_order_relaxed); }
};

// Tag-indexed table mapping a *class* tag (see ReferenceChainTracker::nextClassTag() - always
// negative, a namespace disjoint from the positive FrontierTable object tags above so a raw tag
// value alone always tells the heap-walk callback which table it belongs to) to the
// StringDictionary id of that class's resolved name (Profiler::classMap(), the same interning table
// LivenessTracker uses via Profiler::lookupClass(), livenessTracker.cpp).
class ClassTagTable {
private:
  std::unordered_map<jlong, u32> _table;

public:
  void insert(jlong class_tag, u32 dict_id) { _table[class_tag] = dict_id; }

  // Returns the StringDictionary id for `class_tag`, or 0 if it was never inserted (0 is
  // StringDictionary's own "no entry" sentinel too, so this composes with
  // FrontierEntry::referrer_klass's documented 0 = unresolved/none convention without a separate
  // "found" out-parameter).
  u32 resolve(jlong class_tag) const {
    auto it = _table.find(class_tag);
    return it != _table.end() ? it->second : 0;
  }

  size_t size() const { return _table.size(); }

  // Drops every cached class_tag -> dict_id mapping - used when the underlying StringDictionary
  // itself was reset (see ReferenceChainTracker::_last_class_map_generation's comment) and every id
  // here now points at a namespace that no longer exists.
  void clear() { _table.clear(); }
};


#endif // _REFERENCECHAINFRONTIER_H
