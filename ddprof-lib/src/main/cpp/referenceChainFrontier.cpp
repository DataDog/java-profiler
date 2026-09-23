/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChainFrontier.h"
#include "counters.h"
#include "log.h"
#include "rcDebugLevel.h"
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

FrontierTable::FrontierTable(int max_cap)
    : _table_size(0), _table_cap(0), _table_max_cap(std::max(max_cap, 0)),
      _table(nullptr) {
  _table_cap = std::min(INITIAL_TABLE_CAPACITY, _table_max_cap);
  if (_table_cap > 0) {
    _table = (FrontierEntry *)calloc(_table_cap, sizeof(FrontierEntry));
    if (_table == nullptr) {
      _table_cap = 0;
    }
  }
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       (jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, _table_cap);
}

FrontierTable::~FrontierTable() {
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       -(jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, -_table_cap);
  free(_table);
}

void FrontierTable::resetCapacityForTest(int max_cap) {
  _table_lock.lock();
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       -(jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, -_table_cap);
  free(_table);
  _table = nullptr;
  _table_max_cap = std::max(max_cap, 0);
  _table_cap = std::min(INITIAL_TABLE_CAPACITY, _table_max_cap);
  if (_table_cap > 0) {
    _table = (FrontierEntry *)calloc(_table_cap, sizeof(FrontierEntry));
    if (_table == nullptr) {
      _table_cap = 0;
    }
  }
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       (jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, _table_cap);
  _table_size.store(0, std::memory_order_relaxed);
  _table_lock.unlock();
}

bool FrontierTable::growLocked(int required_cap) {
  if (required_cap <= _table_cap) {
    return true;
  }
  if (_table_cap >= _table_max_cap) {
    return false;
  }

  int newcap = _table_cap;
  while (newcap < required_cap && newcap < _table_max_cap) {
    newcap = newcap == 0 ? std::min(INITIAL_TABLE_CAPACITY, _table_max_cap)
                          : std::min(newcap * 2, _table_max_cap);
  }
  if (newcap <= _table_cap) {
    return false;
  }

  FrontierEntry *tmp =
      (FrontierEntry *)realloc(_table, sizeof(FrontierEntry) * newcap);
  if (tmp == nullptr) {
    Log::debug(
        "ReferenceChains: frontier table resize to %d entries failed", newcap);
    return false;
  }
  // realloc() does not zero the newly grown region - clear it so lookup() never returns garbage
  // state for a slot that hasn't been inserted yet.
  memset(tmp + _table_cap, 0, sizeof(FrontierEntry) * (newcap - _table_cap));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       (jlong)(newcap - _table_cap) * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY,
                       newcap - _table_cap);
  _table = tmp;
  _table_cap = newcap;
  return _table_cap >= required_cap;
}

bool FrontierTable::insert(jlong tag, jlong parent_tag, u32 referrer_klass,
                            u32 depth, u8 state, u8 root_kind,
                            jlong class_tag, jint referrer_field_index,
                            u8 edge_kind, jlong referrer_class_tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);

  // Exclusive lock for the whole write (growLocked() already requires it) - a shared lock here
  // would not exclude lookup()'s own shared-mode read of the same slot, letting a concurrent reader
  // observe a torn entry.
  _table_lock.lock();
  if (idx >= _table_cap && !growLocked(idx + 1)) {
    _table_lock.unlock();
    Log::debug("ReferenceChains: frontier table capacity exhausted "
               "(cap=%d, max=%d, tag=%lld)",
               _table_cap, _table_max_cap, (long long)tag);
    return false;
  }
  _table[idx].parent_tag = parent_tag;
  _table[idx].referrer_klass = referrer_klass;
  _table[idx].depth = depth;
  _table[idx].state = state;
  _table[idx].root_kind = root_kind;
  _table[idx].class_tag = class_tag;
  _table[idx].leak_tag = 0;
  _table[idx].referrer_field_index = referrer_field_index;
  _table[idx].edge_kind = edge_kind;
  _table[idx].referrer_class_tag = referrer_class_tag;
  _table_lock.unlock();

  int sz = _table_size.load(std::memory_order_relaxed);
  while (sz < idx + 1 &&
         !_table_size.compare_exchange_weak(sz, idx + 1,
                                             std::memory_order_relaxed)) {
    // sz reloaded with the current value by compare_exchange_weak on failure; retry until either
    // this thread wins or another thread already advanced _table_size past idx + 1.
  }
  return true;
}

bool FrontierTable::lookup(jlong tag, FrontierEntry *out) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);

  bool found = false;
  _table_lock.lockShared();
  if (idx < _table_size) {
    *out = _table[idx];
    found = true;
  }
  _table_lock.unlockShared();
  return found;
}

bool FrontierTable::lookupLocked(jlong tag, FrontierEntry *out) const {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);
  if (idx < _table_size) {
    *out = _table[idx];
    return true;
  }
  return false;
}

void FrontierTable::clear(jlong tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  // Exclusive lock: this mutates a slot lookup() may be reading concurrently under its own shared
  // lock (see insert()'s own comment above).
  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].state = FrontierEntryState::ABANDONED;
  }
  _table_lock.unlock();
}

void FrontierTable::markEdge(jlong tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].state = FrontierEntryState::EDGE;
  }
  _table_lock.unlock();
}

void FrontierTable::markExpanded(jlong tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].state = FrontierEntryState::EXPANDED;
  }
  _table_lock.unlock();
}

void FrontierTable::updateRootKind(jlong tag, u8 root_kind) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].root_kind = root_kind;
  }
  _table_lock.unlock();
}

bool FrontierTable::improveChain(jlong tag, jlong parent_tag,
                                  u32 referrer_klass, u32 depth,
                                  u8 root_kind, jint referrer_field_index,
                                  u8 edge_kind, jlong referrer_class_tag) {
  // Replace a shallow root-attached entry (parent_tag == 0, depth == 0) with a deeper
  // chain-attached entry when the object is reached via a longer path.
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  // a "chain" whose parent is the entry itself is never an improvement - it is the self-edge a
  // this-field produces, and it is REAL in the heap: every java.util.Collections$Synchronized*
  // holder carries mutex == this, so walking such a holder's own subtree (the rotation anchor walk
  // or a BFS descent) re-reports the holder as its own child through that field.
  if (parent_tag == tag) {
    return false;
  }
  // Ancestor-walk bound for the cycle guard below - see its comment.
  static constexpr int IMPROVE_CHAIN_GUARD_MAX_HOPS = 4096;
  {
    int guard_hops = 0;
    jlong cur = parent_tag;
    while (cur > 0 && guard_hops <= IMPROVE_CHAIN_GUARD_MAX_HOPS) {
      if (cur == tag) {
        TEST_LOG_SUMMARY("FrontierTable::improveChain refused: new parent "
                 "chain routes through the entry (cycle) tag=%lld "
                 "parent_tag=%lld depth=%u",
                 (long long)tag, (long long)parent_tag, depth);
        return false;
      }
      FrontierEntry guard_entry{};
      if (!lookup(cur, &guard_entry)) {
        break;
      }
      cur = guard_entry.parent_tag;
      guard_hops++;
    }
    if (cur != 0) {
      // The parent chain neither reached a root nor was fully verified within the guard bound -
      // applying this improve could embed an unresolvable (cyclic or dangling) chain.
      TEST_LOG_SUMMARY("FrontierTable::improveChain refused: unverifiable "
               "parent chain tag=%lld parent_tag=%lld depth=%u "
               "walk_stopped_at=%lld",
               (long long)tag, (long long)parent_tag, depth,
               (long long)cur);
      return false;
    }
  }

  int idx = (int)(tag - 1);

  _table_lock.lock();
  bool improved = false;
  if (idx < _table_size && depth > _table[idx].depth) {
    _table[idx].parent_tag = parent_tag;
    _table[idx].referrer_klass = referrer_klass;
    _table[idx].depth = depth;
    _table[idx].root_kind = root_kind;
    _table[idx].referrer_field_index = referrer_field_index;
    _table[idx].edge_kind = edge_kind;
    _table[idx].referrer_class_tag = referrer_class_tag;
    improved = true;
  }
  _table_lock.unlock();
  return improved;
}

bool FrontierTable::reparentToDurableRoot(jlong tag, jlong new_parent_tag,
                                          u32 referrer_klass,
                                          jint referrer_field_index,
                                          u8 edge_kind) {
  // See the declaration's own comment (referenceChains.h) for why this exists as a sibling of
  // improveChain(): equal-depth depth-1 noise->real re-parenting.
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX || new_parent_tag <= 0 ||
      new_parent_tag - 1 > (jlong)INT_MAX || new_parent_tag == tag) {
    return false;
  }
  int idx = (int)(tag - 1);
  int new_par_idx = (int)(new_parent_tag - 1);

  _table_lock.lock();
  bool swapped = false;
  if (idx < _table_size && _table[idx].depth == 1 &&
      _table[idx].parent_tag > 0 && _table[idx].parent_tag != new_parent_tag) {
    int old_par_idx = (int)(_table[idx].parent_tag - 1);
    if (old_par_idx >= 0 && old_par_idx < _table_size &&
        new_par_idx < _table_size &&
        _table[new_par_idx].parent_tag == 0 &&
        _table[new_par_idx].root_kind != 0 &&
        !isTransientRootKind(_table[new_par_idx].root_kind) &&
        _table[old_par_idx].parent_tag == 0 &&
        isTransientRootKind(_table[old_par_idx].root_kind)) {
      // New parent is a root-attached DURABLE root (static field, JNI global, thread) and the
      // current parent is a root-attached TRANSIENT one - same depth, strictly better retention
      // explanation.
      _table[idx].parent_tag = new_parent_tag;
      _table[idx].referrer_klass = referrer_klass;
      _table[idx].referrer_field_index = referrer_field_index;
      _table[idx].edge_kind = edge_kind;
      swapped = true;
    }
  }
  _table_lock.unlock();
  return swapped;
}

bool FrontierTable::reconstructChain(jlong target_tag,
                                      std::vector<u32> *out_chain,
                                      u8 *out_root_kind,
                                      std::vector<ChainHopEdge> *out_edges,
                                      FrontierEntry *out_terminal) {
  FrontierEntry entry{};
  if (!lookup(target_tag, &entry)) {
    return false;
  }

  std::vector<u32> chain;
  std::vector<ChainHopEdge> edges;
  jlong tag = target_tag;
  u8 root_kind = 0;
  int hops = 0;
  // Bounded by maxCapacity(): every tag maps to a distinct slot (this table's "tags/slots are never
  // reused" invariant, see the class comment above), so a well-formed parent_tag chain can visit at
  // most maxCapacity() slots before either reaching parent_tag == 0 or repeating a slot.
  for (; hops <= maxCapacity() && tag != 0; hops++) {
    if (!lookup(tag, &entry)) {
      // parent_tag pointed at a tag that was never inserted - should not happen for a chain built
      // entirely within one BFS pass, but do not fabricate a partial chain silently.
      TEST_LOG_SUMMARY("FrontierTable::reconstructChain broken chain: "
               "target=%lld failed at hop=%d tag=%lld (parent tag never "
               "inserted)",
               (long long)target_tag, hops, (long long)tag);
      return false;
    }
    chain.push_back(entry.referrer_klass);
    if (out_edges != nullptr) {
      // edges[i] describes the edge INTO chain[i]: the entry's own recorded edge identity, plus the
      // referrer's class tag - the parent entry's own class for interior hops, the declaring class
      // for root-attached static edges (FrontierEntry::referrer_class_tag, filled only there, since
      // a class-object referrer has no parent entry to read from).
      ChainHopEdge hop{};
      hop.field_index = entry.referrer_field_index;
      if (entry.parent_tag == 0) {
        hop.edge_kind = entry.root_kind;
        hop.referrer_class_tag = entry.referrer_class_tag;
      } else {
        hop.edge_kind = entry.edge_kind;
        FrontierEntry parent_entry{};
        hop.referrer_class_tag =
            lookup(entry.parent_tag, &parent_entry) ? parent_entry.class_tag : 0;
      }
      edges.push_back(hop);
    }
    // Deliberately NOT marking the walked entries EDGE: the EDGE state was write-only "degenerate
    // EdgeStore" bookkeeping (nothing ever reads it), while the rotation collectors select EXPANDED
    // entries - demoting a resolved path's holders to EDGE made them permanently invisible to
    // rotation, so later leak instances behind a changed holder were never re-discovered.
    root_kind = entry.root_kind;
    tag = entry.parent_tag;
  }
  if (tag != 0) {
    // Ran past the defensive hop bound without reaching a root-attached entry (parent_tag == 0) - a
    // corrupted/cyclic chain.
    {
      jlong dbg = target_tag;
      FrontierEntry dbg_e{};
      char pairs[256];
      size_t off = 0;
      for (int d = 0; d < 12 && dbg != 0 && off < sizeof(pairs) - 24; d++) {
        if (!lookup(dbg, &dbg_e)) {
          break;
        }
        off += (size_t)snprintf(pairs + off, sizeof(pairs) - off, "%lld->%lld ",
                                (long long)dbg, (long long)dbg_e.parent_tag);
        dbg = dbg_e.parent_tag;
      }
      TEST_LOG_SUMMARY("FrontierTable::reconstructChain hop bound: "
               "target=%lld stuck at tag=%lld after %d hops - cyclic or "
               "corrupt parent chain; hops: %.*s",
               (long long)target_tag, (long long)tag, hops, (int)off, pairs);
    }
    return false;
  }

  *out_chain = std::move(chain);
  if (out_edges != nullptr) {
    *out_edges = std::move(edges);
  }
  if (out_root_kind != nullptr) {
    // The loop's last iteration is always the root-attached entry (the one whose parent_tag == 0
    // that just ended the loop), so root_kind here is that entry's own FrontierEntry::root_kind.
    *out_root_kind = root_kind;
  }
  if (out_terminal != nullptr) {
    // `entry` still holds the loop's last successful lookup - the root-attached entry that ended
    // the walk.
    *out_terminal = entry;
  }
  return true;
}

