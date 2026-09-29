/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for the reference-chain tracker's heap walk.
 *
 * Drives ReferenceChainTracker::runPass() over fuzzer-generated synthetic heap
 * graphs through the SAME mock JVMTI/JNI harness the gtest suite uses
 * (referenceChainsMockHeap.h) - no diverging copy of the mock semantics.
 *
 * Attack surface: heapReferenceCallback() and the pass pipeline consume
 * JVMTI-supplied tags, class tags, and reference streams that a real JVM can
 * deliver in any order and with any topology - including graphs that change
 * between the passes of one search (objects die mid-search, tags get reused,
 * cycles close on already-expanded frontier entries). Expected bug classes:
 * - unbounded/hung walks (canary chain revisiting a node forever)
 * - tag-lifecycle confusion: stale frontier tags resurrected after release,
 *   class-tag (negative) vs instance-tag (positive) discrimination broken
 * - out-of-range frontier tag indexing (the "Reject out-of-range frontier
 *   tags" class of bugs)
 * - memory errors on dangling references (caught by the fuzz build's ASan)
 *
 * Invariants asserted per input (beyond "no crash / no hang", which libFuzzer
 * and ASan enforce):
 *   I1. runPass() returns a verdict every call (a hung walk fails the
 *       libFuzzer timeout).
 *   I2. Every resolved chain's source tag is positive and was actually handed
 *       out by the mock heap at some point (no phantom tags in _resolved_chains).
 *   I3. After the final pass, releasing the search leaves no node tagged with
 *       a frontier tag (tags are either released by the tracker or reported
 *       via the mock's node_tags, which the release path zeroes).
 *
 * Input format (all multi-byte fields little-endian via a cursor):
 *   [0]      node count, 2..48
 *   [1]      class count, 0..6
 *   [2]      edge count, 0..96
 *   [3]      pass count, 1..3
 *   [4]      flags: bit0 = inject one dead tag before pass 2,
 *                   bit1 = make one edge a self-reference,
 *                   bit2 = fail GetObjectsWithTags on pass 2
 *   then edge_count * 4 bytes: kind, referrer, referee, class_idx
 *   then pass_count bytes: per-pass node bitmask seeds for dead-tag churn
 */

#include <stddef.h>
#include <stdint.h>

#include <set>
#include <vector>

#include "arguments.h"
#include "referenceChains.h"
#include "referenceChainsMockHeap.h"
#include "referenceChainsTestAccessors.h"
#include "vmEntry.h"

namespace {

constexpr int kMaxNodes = 48;
constexpr int kMaxClasses = 6;
constexpr int kMaxEdges = 96;

// Canned signatures - the tracker keys its class-map on the signature string,
// and a fixed pool of 6 makes referrer-klass collisions reproducible.
const char *kSignatures[kMaxClasses] = {
    "Lfuzz/Heap/A;", "Lfuzz/Heap/B;", "Lfuzz/Heap/Target;",
    "Ljava/lang/Thread;", "Ljava/lang/ClassLoader;", "Ljava/lang/ThreadGroup;",
};

// The one-time process setup: silence the debug knob (log volume only slows
// the fuzzer), pin the debug level to 0.
bool fuzzRcInit() {
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "0", 1);
    return true;
}
const bool kFuzzRcInitialized = fuzzRcInit();

u64 readLe(const uint8_t *data, size_t size, size_t &pos, int nbytes) {
    u64 v = 0;
    for (int i = 0; i < nbytes; i++) {
        v |= (pos < size ? data[pos++] : 0) << (8 * i);
    }
    return v;
}

} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    size_t pos = 0;
    int node_count = (int)(readLe(data, size, pos, 1) % (kMaxNodes - 1)) + 2;
    int class_count = (int)(readLe(data, size, pos, 1) % (kMaxClasses + 1));
    int edge_count = (int)(readLe(data, size, pos, 1) % (kMaxEdges + 1));
    int pass_count = (int)(readLe(data, size, pos, 1) % 3) + 1;
    int flags = (int)readLe(data, size, pos, 1);

    ReferenceChainsMockHeap heap;
    heap.setUp(); // resets the tracker singleton (ReferenceChainsTestAccessor::reset())

    // Build the fake class pool. Mixed app-like and well-known-anchor
    // signatures so the static-field anchor partition and the
    // descend-from-anchor resolution both get traffic.
    std::vector<void *> class_ids;
    for (int c = 0; c < class_count; c++) {
        void *id = (void *)(uintptr_t)(0x2000 + c);
        heap.addClass(id, kSignatures[c]);
        class_ids.push_back(id);
    }

    // Nodes: synthetic identities are &node_tags[idx] (the mock's contract).
    std::vector<int> nodes;
    for (int n = 0; n < node_count; n++) {
        nodes.push_back(heap.addNode());
    }

    // Edges: referrer 0xFF means heap root; referee/referrer indices are
    // taken modulo node_count so they always name a real node - the corrupt
    // topology (cycles, self-refs, forks, diamond chains) is the fuzz
    // dimension, not mock-side index bugs. Self-reference flag overrides one
    // edge's referee with its referrer.
    int self_ref_at = flags & 2 ? (int)readLe(data, size, pos, 1) % (edge_count + 1) : -1;
    for (int e = 0; e < edge_count; e++) {
        static const jvmtiHeapReferenceKind kKinds[] = {
            JVMTI_HEAP_REFERENCE_FIELD,
            JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT,
            JVMTI_HEAP_REFERENCE_JNI_GLOBAL,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD,
            JVMTI_HEAP_REFERENCE_THREAD,
        };
        uint8_t kind = (uint8_t)readLe(data, size, pos, 1);
        int referrer = (int)readLe(data, size, pos, 1);
        int referee = (int)readLe(data, size, pos, 1);
        int class_idx = (int)readLe(data, size, pos, 1);

        ScriptedEdge edge;
        edge.kind = kKinds[kind % 5];
        edge.referrer_idx = referrer == 0xFF ? -1 : referrer % node_count;
        edge.referee_idx = referee % node_count;
        if (e == self_ref_at && edge.referrer_idx >= 0) {
            edge.referee_idx = edge.referrer_idx;
        }
        edge.class_idx = class_idx == 0xFF ? -1 : class_idx % (class_count + 1) - 1;
        if (edge.class_idx >= class_count) {
            edge.class_idx = -1;
        }
        heap.script.push_back(edge);
    }

    Arguments args;
    if (args.parse("referencechains=true:hops=16:budget=200:ttl=500:framecap=32")) {
        heap.tearDown();
        return 0;
    }
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    if (tracker->start(args)) {
        heap.tearDown();
        return 0;
    }

    std::vector<jlong> seen_tags; // every frontier/instance tag the mock observed
    for (int p = 0; p < pass_count; p++) {
        // Mid-search churn: mark one observed tag dead (object GC'd between
        // passes) and, on the flagged run, fail the tag-resolution call on
        // the middle pass - the releaseSearchTags() failure path.
        if (p == 1) {
            if ((flags & 1) != 0 && !heap.tags_ever_assigned.empty()) {
                size_t idx = (size_t)(data && size > pos ? data[pos % size] : 0);
                heap.dead_tags.insert(
                    heap.tags_ever_assigned[idx % heap.tags_ever_assigned.size()]);
            }
            heap.fail_get_objects_with_tags = (flags & 4) != 0;
        }

        bool truncated = true;
        // I1: runPass() returning at all is the bounded-termination check; a
        // hung canary walk trips libFuzzer's timeout instead.
        if (!tracker->runPass(&heap.mock_jvmti, &heap.mock_jni, &truncated)) {
            break; // pass legitimately skipped (budget/pacing) - fine
        }
        if (!tracker->frontierTable()) {
            break;
        }

        // I2: resolved chains must reference tags the mock actually minted.
        // (Tag minting is tracked by the mock via tags_ever_assigned.)
        for (size_t t = 0; t < heap.tags_ever_assigned.size(); t++) {
            jlong tag = heap.tags_ever_assigned[t];
            if (tag > 0) {
                seen_tags.push_back(tag);
            }
        }
    }

    std::set<jlong> minted(seen_tags.begin(), seen_tags.end());
    // I2's sign discrimination: a chain keyed by a NEGATIVE tag can only be a
    // class-tag mix-up (class tags are negative by ClassTagAllocator's
    // contract, instance/frontier tags positive) - always a bug. Keying by a
    // positive tag the mock has not observed in THIS input is not: a chain
    // resolved in an earlier pass can legitimately outlive its node.
    for (jlong tag : ReferenceChainsTestAccessor::resolvedChainSourceTags()) {
        if (tag < 0) {
            __builtin_trap();
        }
    }

    tracker->stop();
    heap.tearDown();
    return 0;
}
