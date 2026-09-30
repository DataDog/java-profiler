/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for FrontierTable (referenceChains.h).
 *
 * The fuzzer interprets each input as a sequence of table operations and
 * verifies them against an exact semantic shadow model - a byte-for-byte
 * replica of the table's documented behavior. Unlike the heap-graph target
 * (fuzz_referenceChainHeap.cpp), which drives FrontierTable indirectly through
 * the whole BFS pass pipeline, this target calls every public FrontierTable
 * method directly, including the paths a well-formed BFS pass never produces:
 * out-of-range tags, inserts that exhaust the capacity schedule, parent chains
 * that cycle or dangle, and re-parent attempts that violate the improve
 * predicates.
 *
 * Invariants asserted per input (beyond "no crash / ASan / UBSan / no hang"):
 *
 *   I1 (capacity contract): size() never exceeds maxCapacity(); insert()
 *       returns false exactly when the tag is invalid (<= 0 or tag - 1 >=
 *       INT_MAX) or growing past maxCapacity() would be required; capacity()
 *       follows the documented schedule (initial min(1024, max_cap), doubling
 *       capped at max_cap).
 *
 *   I2 (lookup fidelity): lookup(tag) succeeds iff the slot was published
 *       (idx < published size) and returns exactly the last written metadata -
 *       including the documented stale-bytes window after resetForRestart()
 *       (resetForRestart() only resets the published size; slot contents from
 *       the previous search remain until re-inserted, and contiguity of
 *       re-inserted tags is a nextTag() production property this target does
 *       not assume, so stale lookups are model-checked, not skipped).
 *
 *   I3 (chain soundness): reconstructChain() returns true iff the parent chain
 *       reaches a root-attached entry (parent_tag == 0) within maxCapacity()
 *       hops over published slots; when it returns true, the emitted chain,
 *       hop edges, root kind, and terminal entry match the model exactly.
 *       Cyclic or dangling parent chains return false - never a fabricated
 *       partial chain.
 *
 *   I4 (mutation guards): improveChain() accepts only strictly-deeper
 *       re-parents whose proposed parent chain verifies and does not route
 *       through the entry itself (the self-edge cycle guard); it refuses when
 *       the guard walk cannot reach a root within 4096 hops. reparentToDurableRoot()
 *       accepts only the documented equal-depth durable-over-transient swap.
 *       Neither touches state, class_tag, or leak_tag.
 *
 * Input format (all multi-byte fields little-endian via a cursor):
 *   [0] max capacity 0..64 (0 exercises the disabled-table path)
 *   [1] op count 0..96
 *   then the op stream; each op is an opcode byte (mod OP_MAX) plus args:
 *     0  INSERT t parent klass depth state&3 root_kind ctag_idx field edge rtag_idx
 *     1  INSERT_RAW_TAG 4-byte tag (exercises the INT_MAX guard)
 *     2  IMPROVE t parent klass depth root_kind field edge
 *     3  REPARENT t new_parent klass field edge
 *     4  CLEAR t
 *     5  MARK_EDGE t
 *     6  MARK_EXPANDED t
 *     7  UPDATE_ROOT_KIND t kind
 *     8  SET_LEAK_TAG t leak_idx
 *     9  LOOKUP t (model-compared)
 *     10 RECONSTRUCT t (model-compared)
 *     11 RESET_RESTART
 *     12 RESET_CAPACITY new_cap
 * Tag operands are raw bytes (0..255): 0 exercises the "tag <= 0" guard, and
 * tags beyond the max capacity exercise the grow/exhaustion paths.
 */

#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "referenceChains.h"

// Reports the diverging check before dying: __builtin_trap() alone gives no
// usable trace under the fuzz task's output capture.
#define CHECK_MODEL(cond, msg)                                                    \
  do {                                                                            \
    if (!(cond)) {                                                                \
      fprintf(stderr, "MODEL VIOLATION line %d: %s\n", __LINE__, msg);            \
      fflush(stderr);                                                             \
      abort();                                                                    \
    }                                                                             \
  } while (0)

namespace {

// Working-set bound: tags are one byte, so the shadow table needs 256 slots
// regardless of the table's own max capacity.
constexpr int kMaxTag = 256;
constexpr int kMaxOps = 96;
constexpr int kMaxCap = 64;

// Silence TEST_LOG_SUMMARY (the fuzz build compiles with -DDEBUG, so the
// rcDebugLevel machinery is live and its output would swamp the fuzzer log).
bool fuzzRcInit() {
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "0", 1);
    return true;
}
const bool kFuzzRcInitialized = fuzzRcInit();

struct ShadowEntry {
    jlong parent_tag = 0;
    u32 referrer_klass = 0;
    u32 depth = 0;
    u8 state = 0;
    jlong leak_tag = 0;
    u8 root_kind = 0;
    jlong class_tag = 0;
    // Defaults mirror a calloc-zeroed FrontierEntry: a published-but-never-
    // written slot (reachable when inserts skip tag contiguity, which only the
    // fuzzer does - production nextTag() mints contiguously) reads back zeros,
    // including referrer_field_index 0, not the -1 "unset" sentinel.
    jint referrer_field_index = 0;
    u8 edge_kind = 0;
    jlong referrer_class_tag = 0;
};

u64 readLe(const uint8_t *data, size_t size, size_t &pos, int nbytes) {
    u64 v = 0;
    for (int i = 0; i < nbytes; i++) {
        v |= (u64)(pos < size ? data[pos++] : 0) << (8 * i);
    }
    return v;
}

// Exact replica of FrontierTable::growLocked's schedule (referenceChainFrontier.cpp),
// minus the (unreachable at these sizes) realloc-failure branch.
int growModel(int cap, int max_cap, int required_cap) {
    if (required_cap <= cap) {
        return cap;
    }
    if (cap >= max_cap) {
        return -1;
    }
    int newcap = cap;
    while (newcap < required_cap && newcap < max_cap) {
        newcap = newcap == 0 ? std::min(1024, max_cap)
                             : std::min(newcap * 2, max_cap);
    }
    if (newcap <= cap) {
        return -1;
    }
    return newcap;
}

bool entriesEqual(const FrontierEntry &e, const ShadowEntry &s) {
    return e.parent_tag == s.parent_tag && e.referrer_klass == s.referrer_klass &&
           e.depth == s.depth && e.state == s.state && e.leak_tag == s.leak_tag &&
           e.root_kind == s.root_kind && e.class_tag == s.class_tag &&
           e.referrer_field_index == s.referrer_field_index &&
           e.edge_kind == s.edge_kind &&
           e.referrer_class_tag == s.referrer_class_tag;
}

} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    size_t pos = 0;
    int max_cap = (int)(readLe(data, size, pos, 1) % (kMaxCap + 1));
    int op_count = (int)(readLe(data, size, pos, 1) % (kMaxOps + 1));

    FrontierTable table(max_cap);

    // Shadow state. The shadow slot array is only zeroed at construction and
    // by RESET_CAPACITY (resetCapacityForTest() calloc's a fresh table);
    // RESET_RESTART (resetForRestart()) keeps stale contents - see I2.
    std::vector<ShadowEntry> shadow(kMaxTag);
    int cap = std::min(1024, max_cap);
    int published_size = 0;

    auto modelLookup = [&](jlong tag, ShadowEntry *out) -> bool {
        if (tag <= 0 || tag - 1 >= (jlong)INT_MAX) {
            return false;
        }
        int idx = (int)(tag - 1);
        if (idx >= published_size) {
            return false;
        }
        *out = shadow[idx];
        return true;
    };

    // I1 + I2 sweep: the table's published state must match the model exactly,
    // for every tag, after every op.
    auto verifySweep = [&]() {
        CHECK_MODEL(table.size() == published_size, "size() != model published size");
        CHECK_MODEL(table.capacity() == cap, "capacity() != model capacity");
        CHECK_MODEL(table.maxCapacity() == max_cap, "maxCapacity() != model max cap");
        for (int t = 0; t < kMaxTag; t++) {
            FrontierEntry entry{};
            bool found = table.lookup(t + 1, &entry);
            if (t < published_size) {
                CHECK_MODEL(found, "model says published, lookup() failed");
                if (!entriesEqual(entry, shadow[t])) {
                    fprintf(stderr,
                            "DIVERGE tag=%d got(p=%lld k=%u d=%u st=%u lt=%lld "
                            "rk=%u ct=%lld fi=%d ek=%u rt=%lld) "
                            "want(p=%lld k=%u d=%u st=%u lt=%lld rk=%u "
                            "ct=%lld fi=%d ek=%u rt=%lld)\n",
                            t, (long long)entry.parent_tag, entry.referrer_klass,
                            entry.depth, entry.state, (long long)entry.leak_tag,
                            entry.root_kind, (long long)entry.class_tag,
                            entry.referrer_field_index, entry.edge_kind,
                            (long long)entry.referrer_class_tag,
                            (long long)shadow[t].parent_tag,
                            shadow[t].referrer_klass, shadow[t].depth,
                            shadow[t].state, (long long)shadow[t].leak_tag,
                            shadow[t].root_kind, (long long)shadow[t].class_tag,
                            shadow[t].referrer_field_index, shadow[t].edge_kind,
                            (long long)shadow[t].referrer_class_tag);
                    abort();
                }
            } else {
                CHECK_MODEL(!found, "lookup() found an unpublished slot");
            }
        }
    };

    for (int op = 0; op < op_count && pos < size; op++) {
        int opcode = (int)readLe(data, size, pos, 1) % 13;
        switch (opcode) {
        case 0: { // INSERT
            jlong tag = (jlong)readLe(data, size, pos, 1);
            ShadowEntry s;
            s.parent_tag = (jlong)readLe(data, size, pos, 1);
            s.referrer_klass = (u32)readLe(data, size, pos, 1);
            s.depth = (u32)readLe(data, size, pos, 1);
            s.state = (u8)(readLe(data, size, pos, 1) & 3);
            s.root_kind = (u8)readLe(data, size, pos, 1);
            s.class_tag = -(jlong)(readLe(data, size, pos, 1) + 1);
            s.referrer_field_index = (jint)(int8_t)readLe(data, size, pos, 1);
            s.edge_kind = (u8)readLe(data, size, pos, 1);
            s.referrer_class_tag = -(jlong)(readLe(data, size, pos, 1) + 1);

            bool expected;
            if (tag <= 0 || tag - 1 >= (jlong)INT_MAX) {
                expected = false;
            } else {
                int idx = (int)(tag - 1);
                if (idx >= cap) {
                    int newcap = growModel(cap, max_cap, idx + 1);
                    if (newcap < 0) {
                        expected = false;
                    } else {
                        cap = newcap;
                        expected = true;
                    }
                } else {
                    expected = true;
                }
                if (expected) {
                    shadow[idx] = s; // insert() zeroes leak_tag via the full write
                    if (published_size < idx + 1) {
                        published_size = idx + 1;
                    }
                }
            }
            if (table.insert(tag, s.parent_tag, s.referrer_klass, s.depth,
                             s.state, s.root_kind, s.class_tag,
                             s.referrer_field_index, s.edge_kind,
                             s.referrer_class_tag) != expected) {
                CHECK_MODEL(false, "op result divergence #1");
            }
            break;
        }
        case 1: { // INSERT_RAW_TAG - 4-byte tag, hits the INT_MAX guard
            jlong tag = (jlong)readLe(data, size, pos, 4);

            bool expected;
            if (tag <= 0 || tag - 1 >= (jlong)INT_MAX) {
                expected = false;
            } else {
                int idx = (int)(tag - 1);
                if (idx >= cap) {
                    int newcap = growModel(cap, max_cap, idx + 1);
                    if (newcap < 0) {
                        expected = false;
                    } else {
                        cap = newcap;
                        expected = true;
                    }
                } else {
                    expected = true;
                }
                if (expected) {
                    // Mirror the insert(tag, 0, 0, 0, FRONTIER) call below:
                    // every field is written, including the -1 default of
                    // referrer_field_index (ShadowEntry's calloc-matching
                    // zero default does not apply - insert() overwrites all).
                    shadow[idx] = ShadowEntry();
                    shadow[idx].state = FrontierEntryState::FRONTIER;
                    shadow[idx].referrer_field_index = -1;
                    if (published_size < idx + 1) {
                        published_size = idx + 1;
                    }
                }
            }
            if (table.insert(tag, 0, 0, 0, FrontierEntryState::FRONTIER) !=
                expected) {
                CHECK_MODEL(false, "op result divergence #2");
            }
            break;
        }
        case 2: { // IMPROVE
            jlong tag = (jlong)readLe(data, size, pos, 1);
            jlong parent_tag = (jlong)readLe(data, size, pos, 1);
            u32 referrer_klass = (u32)readLe(data, size, pos, 1);
            u32 depth = (u32)readLe(data, size, pos, 1);
            u8 root_kind = (u8)readLe(data, size, pos, 1);
            jint field_index = (jint)(int8_t)readLe(data, size, pos, 1);
            u8 edge_kind = (u8)readLe(data, size, pos, 1);
            jlong referrer_class_tag = -(jlong)(readLe(data, size, pos, 1) + 1);

            // Model of improveChain(): guard walk first, then the accept
            // predicate - state, class_tag, and leak_tag untouched on success.
            bool expected = false;
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX) && parent_tag != tag) {
                static constexpr int GUARD_MAX_HOPS = 4096;
                int guard_hops = 0;
                jlong cur = parent_tag;
                while (cur > 0 && guard_hops <= GUARD_MAX_HOPS) {
                    if (cur == tag) {
                        break;
                    }
                    ShadowEntry e;
                    if (!modelLookup(cur, &e)) {
                        break;
                    }
                    cur = e.parent_tag;
                    guard_hops++;
                }
                if (cur == 0) {
                    int idx = (int)(tag - 1);
                    if (idx < published_size && depth > shadow[idx].depth) {
                        shadow[idx].parent_tag = parent_tag;
                        shadow[idx].referrer_klass = referrer_klass;
                        shadow[idx].depth = depth;
                        shadow[idx].root_kind = root_kind;
                        shadow[idx].referrer_field_index = field_index;
                        shadow[idx].edge_kind = edge_kind;
                        shadow[idx].referrer_class_tag = referrer_class_tag;
                        expected = true;
                    }
                }
            }
            if (table.improveChain(tag, parent_tag, referrer_klass, depth,
                                   root_kind, field_index, edge_kind,
                                   referrer_class_tag) != expected) {
                CHECK_MODEL(false, "op result divergence #3");
            }
            break;
        }
        case 3: { // REPARENT
            jlong tag = (jlong)readLe(data, size, pos, 1);
            jlong new_parent = (jlong)readLe(data, size, pos, 1);
            u32 referrer_klass = (u32)readLe(data, size, pos, 1);
            jint field_index = (jint)(int8_t)readLe(data, size, pos, 1);
            u8 edge_kind = (u8)readLe(data, size, pos, 1);

            bool expected = false;
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX) &&
                !(new_parent <= 0 || new_parent - 1 >= (jlong)INT_MAX) &&
                new_parent != tag) {
                int idx = (int)(tag - 1);
                int new_par_idx = (int)(new_parent - 1);
                if (idx < published_size && shadow[idx].depth == 1 &&
                    shadow[idx].parent_tag > 0 &&
                    shadow[idx].parent_tag != new_parent) {
                    int old_par_idx = (int)(shadow[idx].parent_tag - 1);
                    if (old_par_idx >= 0 && old_par_idx < published_size &&
                        new_par_idx < published_size &&
                        shadow[new_par_idx].parent_tag == 0 &&
                        shadow[new_par_idx].root_kind != 0 &&
                        !isTransientRootKind(shadow[new_par_idx].root_kind) &&
                        shadow[old_par_idx].parent_tag == 0 &&
                        isTransientRootKind(shadow[old_par_idx].root_kind)) {
                        shadow[idx].parent_tag = new_parent;
                        shadow[idx].referrer_klass = referrer_klass;
                        shadow[idx].referrer_field_index = field_index;
                        shadow[idx].edge_kind = edge_kind;
                        expected = true;
                    }
                }
            }
            if (table.reparentToDurableRoot(tag, new_parent, referrer_klass,
                                            field_index, edge_kind) !=
                expected) {
                CHECK_MODEL(false, "op result divergence #4");
            }
            break;
        }
        case 4: { // CLEAR
            jlong tag = (jlong)readLe(data, size, pos, 1);
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX)) {
                int idx = (int)(tag - 1);
                if (idx < published_size) {
                    shadow[idx].state = FrontierEntryState::ABANDONED;
                }
            }
            table.clear(tag);
            break;
        }
        case 5: { // MARK_EDGE
            jlong tag = (jlong)readLe(data, size, pos, 1);
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX)) {
                int idx = (int)(tag - 1);
                if (idx < published_size) {
                    shadow[idx].state = FrontierEntryState::EDGE;
                }
            }
            table.markEdge(tag);
            break;
        }
        case 6: { // MARK_EXPANDED
            jlong tag = (jlong)readLe(data, size, pos, 1);
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX)) {
                int idx = (int)(tag - 1);
                if (idx < published_size) {
                    shadow[idx].state = FrontierEntryState::EXPANDED;
                }
            }
            table.markExpanded(tag);
            break;
        }
        case 7: { // UPDATE_ROOT_KIND
            jlong tag = (jlong)readLe(data, size, pos, 1);
            u8 kind = (u8)readLe(data, size, pos, 1);
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX)) {
                int idx = (int)(tag - 1);
                if (idx < published_size) {
                    shadow[idx].root_kind = kind;
                }
            }
            table.updateRootKind(tag, kind);
            break;
        }
        case 8: { // SET_LEAK_TAG
            jlong tag = (jlong)readLe(data, size, pos, 1);
            jlong leak = -(jlong)(readLe(data, size, pos, 1) + 1);
            if (!(tag <= 0 || tag - 1 >= (jlong)INT_MAX)) {
                int idx = (int)(tag - 1);
                if (idx < published_size) {
                    shadow[idx].leak_tag = leak;
                }
            }
            table.setLeakTag(tag, leak);
            break;
        }
        case 9: { // LOOKUP - I2 checked by the sweep below
            (void)readLe(data, size, pos, 1);
            break;
        }
        case 10: { // RECONSTRUCT - I3
            jlong target = (jlong)readLe(data, size, pos, 1);

            // Model walk: exact replica of reconstructChain()'s loop, including
            // the mid-walk parent-lookup fallback for hop edges.
            bool expected = false;
            std::vector<u32> m_chain;
            std::vector<ChainHopEdge> m_edges;
            u8 m_root_kind = 0;
            ShadowEntry m_terminal;
            ShadowEntry entry;
            if (modelLookup(target, &entry)) {
                jlong tag = target;
                u8 root_kind = 0;
                int hops = 0;
                bool broken = false;
                while (hops <= max_cap && tag != 0) {
                    ShadowEntry cur;
                    if (!modelLookup(tag, &cur)) {
                        broken = true;
                        break;
                    }
                    m_chain.push_back(cur.referrer_klass);
                    ChainHopEdge hop{};
                    hop.field_index = cur.referrer_field_index;
                    if (cur.parent_tag == 0) {
                        hop.edge_kind = cur.root_kind;
                        hop.referrer_class_tag = cur.referrer_class_tag;
                    } else {
                        hop.edge_kind = cur.edge_kind;
                        ShadowEntry parent_entry;
                        hop.referrer_class_tag =
                            modelLookup(cur.parent_tag, &parent_entry)
                                ? parent_entry.class_tag
                                : 0;
                    }
                    m_edges.push_back(hop);
                    root_kind = cur.root_kind;
                    m_terminal = cur;
                    tag = cur.parent_tag;
                    hops++;
                }
                if (!broken && tag == 0) {
                    expected = true;
                    m_root_kind = root_kind;
                }
            }

            std::vector<u32> out_chain;
            std::vector<ChainHopEdge> out_edges;
            u8 out_root_kind = 0;
            FrontierEntry out_terminal{};
            bool result = table.reconstructChain(target, &out_chain,
                                                 &out_root_kind, &out_edges,
                                                 &out_terminal);
            if (result != expected) {
                CHECK_MODEL(false, "op result divergence #5");
            }
            if (expected) {
                if (out_chain != m_chain || out_edges.size() != m_edges.size() ||
                    out_root_kind != m_root_kind ||
                    !entriesEqual(out_terminal, m_terminal)) {
                    CHECK_MODEL(false, "op result divergence #6");
                }
                for (size_t i = 0; i < m_edges.size(); i++) {
                    if (out_edges[i].field_index != m_edges[i].field_index ||
                        out_edges[i].edge_kind != m_edges[i].edge_kind ||
                        out_edges[i].referrer_class_tag !=
                            m_edges[i].referrer_class_tag) {
                        CHECK_MODEL(false, "op result divergence #7");
                    }
                }
            }
            break;
        }
        case 11: { // RESET_RESTART - published size resets, stale bytes remain
            published_size = 0;
            table.resetForRestart();
            break;
        }
        case 12: { // RESET_CAPACITY
            int new_cap = (int)readLe(data, size, pos, 1);
            max_cap = new_cap;
            cap = std::min(1024, new_cap);
            if (cap < 0) {
                cap = 0;
            }
            published_size = 0;
            std::fill(shadow.begin(), shadow.end(), ShadowEntry());
            table.resetCapacityForTest(new_cap);
            break;
        }
        }
        verifySweep();
    }
    return 0;
}
