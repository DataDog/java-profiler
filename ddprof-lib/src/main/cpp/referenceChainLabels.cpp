/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChains.h"
#include "referenceChainInternal.h"
#include "common.h"
#include "counters.h"
#include "jniHelper.h"
#include "jvmThread.h"
#include "livenessTracker.h"
#include "log.h"
#include "objectSampler.h"
#include "os.h"
#include "profiler.h"
#include "rcDebugLevel.h"
#include "tsc.h"
#include "vmEntry.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_set>

// Retention-edge labels: naming the field each chain hop is retained
namespace {

// Fallback label for a hop whose edge is not a field reference (or whose field ordinal could not be
// decoded) - the edge KIND, never a fabricated name.
const char *hopEdgeKindLabel(u8 kind) {
  switch (kind) {
  case JVMTI_HEAP_REFERENCE_CLASS:
    return "class";
  case JVMTI_HEAP_REFERENCE_FIELD:
    return "field";
  case JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT:
    return "element";
  case JVMTI_HEAP_REFERENCE_CLASS_LOADER:
    return "class_loader";
  case JVMTI_HEAP_REFERENCE_SIGNERS:
    return "signers";
  case JVMTI_HEAP_REFERENCE_PROTECTION_DOMAIN:
    return "protection_domain";
  case JVMTI_HEAP_REFERENCE_INTERFACE:
    return "interface";
  case JVMTI_HEAP_REFERENCE_STATIC_FIELD:
    return "static_field";
  case JVMTI_HEAP_REFERENCE_CONSTANT_POOL:
    return "constant_pool";
  case JVMTI_HEAP_REFERENCE_SUPERCLASS:
    return "superclass";
  case JVMTI_HEAP_REFERENCE_JNI_GLOBAL:
    return "jni_global";
  case JVMTI_HEAP_REFERENCE_SYSTEM_CLASS:
    return "system_class";
  case JVMTI_HEAP_REFERENCE_MONITOR:
    return "monitor";
  case JVMTI_HEAP_REFERENCE_STACK_LOCAL:
    return "stack_local";
  case JVMTI_HEAP_REFERENCE_JNI_LOCAL:
    return "jni_local";
  case JVMTI_HEAP_REFERENCE_THREAD:
    return "thread";
  case JVMTI_HEAP_REFERENCE_OTHER:
    return "other";
  default:
    return "unknown";
  }
}

// Appends the own-declared field names of `cls` to *out, in GetClassFields() order.
bool appendClassFieldNames(jvmtiEnv *jvmti, JNIEnv *jni, jclass cls,
                            std::vector<std::string> *out) {
  jint count = 0;
  jfieldID *fields = nullptr;
  if (jvmti->GetClassFields(cls, &count, &fields) != JVMTI_ERROR_NONE) {
    return false;
  }
  bool ok = true;
  for (jint i = 0; i < count; i++) {
    char *name = nullptr;
    if (jvmti->GetFieldName(cls, fields[i], &name, nullptr, nullptr) !=
            JVMTI_ERROR_NONE ||
        name == nullptr) {
      ok = false;
      break;
    }
    out->emplace_back(name);
    jvmti->Deallocate((unsigned char *)name);
  }
  jvmti->Deallocate((unsigned char *)fields);
  return ok;
}

// Counts `iface`'s own declared fields plus every transitive superinterface's, each interface
// counted exactly once (keyed on the shared `seen` set insert - an interface's own fields go in
// only when its tag is newly seen, so a diamond's shared parent contributes once no matter how many
// branches reach it).
jlong interfaceSubtreeFieldCount(jvmtiEnv *jvmti, JNIEnv *jni, jclass iface,
                                 std::unordered_set<jlong> *seen) {
  jlong tag = 0;
  if (jvmti->GetTag(iface, &tag) != JVMTI_ERROR_NONE || tag == 0) {
    // Untagged interface: cannot dedupe reliably - fail the whole decode rather than risk double
    // counting.
    return -1;
  }
  if (!seen->insert(tag).second) {
    return 0; // already counted this interface (a shared subinterface)
  }
  jlong total = 0;
  jint field_count = 0;
  jfieldID *fields = nullptr;
  if (jvmti->GetClassFields(iface, &field_count, &fields) ==
      JVMTI_ERROR_NONE) {
    // This interface's own fields count toward any implementor's ordinal base - matching the spec's
    // "count of the fields in all the interfaces implemented by C" (jvmtiHeapReferenceInfoField).
    total += field_count;
    jvmti->Deallocate((unsigned char *)fields);
  }
  jint iface_count = 0;
  jclass *supers = nullptr;
  if (jvmti->GetImplementedInterfaces(iface, &iface_count, &supers) !=
      JVMTI_ERROR_NONE) {
    return -1;
  }
  bool ok = true;
  for (jint i = 0; i < iface_count; i++) {
    if (supers[i] == nullptr) {
      continue;
    }
    jlong sub = interfaceSubtreeFieldCount(jvmti, jni, supers[i], seen);
    jni->DeleteLocalRef(supers[i]);
    if (sub < 0) {
      ok = false;
    } else if (ok) {
      total += sub;
    }
  }
  jvmti->Deallocate((unsigned char *)supers);
  return ok ? total : -1;
}

// Sums the field counts of every interface transitively implemented/extended by `cls`, each
// interface counted exactly once (see interfaceSubtreeFieldCount() above - the own-field add lives
// behind the shared seen-set insert, so an interface diamond no longer double-counts its shared
// parent).
jlong interfaceFieldCount(jvmtiEnv *jvmti, JNIEnv *jni, jclass cls,
                          std::unordered_set<jlong> *seen) {
  jint iface_count = 0;
  jclass *ifaces = nullptr;
  if (jvmti->GetImplementedInterfaces(cls, &iface_count, &ifaces) !=
      JVMTI_ERROR_NONE) {
    return -1;
  }
  jlong total = 0;
  bool ok = true;
  for (jint i = 0; i < iface_count; i++) {
    if (ifaces[i] == nullptr) {
      continue;
    }
    jlong sub = interfaceSubtreeFieldCount(jvmti, jni, ifaces[i], seen);
    jni->DeleteLocalRef(ifaces[i]);
    if (sub < 0) {
      ok = false;
    } else if (ok) {
      total += sub;
    }
  }
  jvmti->Deallocate((unsigned char *)ifaces);
  return ok ? total : -1;
}

} // namespace

const ReferenceChainTracker::HopLabelClass *
ReferenceChainTracker::hopLabelClassFor(jvmtiEnv *jvmti, JNIEnv *jni,
                                        jlong class_tag) {
  auto it = _hop_label_cache.find(class_tag);
  if (it != _hop_label_cache.end()) {
    return &it->second;
  }
  // Bounded: chains reference few distinct referrer classes; a wholesale clear at the cap (rather
  // than LRU eviction) keeps this O(1) and is correct because the cache is purely derived state -
  // any cleared entry is transparently rebuilt on its next hop.
  if (_hop_label_cache.size() >= HOP_LABEL_CLASS_CACHE_CAP) {
    _hop_label_cache.clear();
  }
  HopLabelClass entry{};
  entry.class_tag = class_tag;
  entry.decode_failed = true; // until proven otherwise
  do {
    // GetSuperclass is a JNI (not JVMTI) function - modern JVMTI dropped it (the spec delivers
    // superclass references via heap callbacks, jvmti.xml's JVMTI_HEAP_REFERENCE_SUPERCLASS note);
    // the rest are JVMTI slots.
    if (jvmti->functions->GetObjectsWithTags == nullptr ||
        jvmti->functions->IsInterface == nullptr ||
        jvmti->functions->GetImplementedInterfaces == nullptr ||
        jvmti->functions->GetClassFields == nullptr ||
        jvmti->functions->GetFieldName == nullptr ||
        jni->functions->GetSuperclass == nullptr) {
      break;
    }
    // Resolve the class object from its raw tag (negative - the shared allocator's class tags;
    // GetObjectsWithTags accepts any tag value).
    jint count = 0;
    jobject *objects = nullptr;
    jlong *tags = nullptr;
    if (jvmti->GetObjectsWithTags(1, &class_tag, &count, &objects, &tags) !=
            JVMTI_ERROR_NONE ||
        count != 1 || objects == nullptr || objects[0] == nullptr) {
      // Both result arrays are JVMTI-allocated on success and must be Deallocate()d by the caller -
      // same contract as every other GetObjectsWithTags() call site in this file.
      if (objects != nullptr) {
        jvmti->Deallocate((unsigned char *)objects);
      }
      if (tags != nullptr) {
        jvmti->Deallocate((unsigned char *)tags);
      }
      break;
    }
    jclass cls = (jclass)objects[0];
    // The arrays were only needed to obtain the class object - the jobject handle stays valid on
    // its own - so release them before the (multiple, break-exited) decode branches below, which
    // otherwise all leak them.
    jvmti->Deallocate((unsigned char *)objects);
    jvmti->Deallocate((unsigned char *)tags);
    jboolean is_interface = JNI_FALSE;
    std::vector<std::string> names;
    bool ok = false;
    if (jvmti->IsInterface(cls, &is_interface) == JVMTI_ERROR_NONE) {
      if (is_interface) {
        // The spec's INTERFACE branch: base = fields of all superinterfaces of I, then I's own
        // fields (jvmtiHeapReferenceInfoField).
        std::unordered_set<jlong> seen;
        jlong base = interfaceFieldCount(jvmti, jni, cls, &seen);
        if (base >= 0) {
          names.resize((size_t)base); // positioned but unnamed: ordinal [0,
                                     // base) is interface fields, only reachable through an
                                     // interface branch decode of a superinterface
          ok = appendClassFieldNames(jvmti, jni, cls, &names);
        }
      } else {
        // The spec's CLASS branch: base = fields of all interfaces implemented by C, then the
        // superclass chain root-first (java.lang.Object's fields first, C's own last), each class's
        // fields in GetClassFields() order.
        std::unordered_set<jlong> seen;
        jlong base = interfaceFieldCount(jvmti, jni, cls, &seen);
        if (base >= 0) {
          names.resize((size_t)base);
          // GetSuperclass walks UP, so gather then append in reverse (root first).
          jclass supers[128];
          int depth = 0;
          jclass k = cls;
          while (k != nullptr &&
                 depth < (int)(sizeof(supers) / sizeof(supers[0]))) {
            supers[depth++] = k;
            k = jni->GetSuperclass(k);
          }
          ok = (k == nullptr); // deeper than 128 classes: fail rather than
                              // misname
          for (int i = depth - 1; ok && i >= 0; i--) {
            ok = appendClassFieldNames(jvmti, jni, supers[i], &names);
          }
          for (int i = 0; i < depth; i++) {
            jni->DeleteLocalRef(supers[i]);
          }
          // supers[0] IS cls - the loop above already deleted it. Null it so the shared cleanup
          // below does not delete the same local ref a second time (checked JNI reports an invalid
          // local ref and aborts).
          cls = nullptr;
        }
      }
    }
    if (cls != nullptr) {
      jni->DeleteLocalRef(cls);
    }
    if (!ok) {
      break;
    }
    entry.field_names = std::move(names);
    entry.decode_failed = false;
  } while (false);
  auto inserted = _hop_label_cache.emplace(class_tag, std::move(entry));
  return &inserted.first->second;
}

void ReferenceChainTracker::resolveHopEdgeLabel(jvmtiEnv *jvmti, JNIEnv *jni,
                                                ChainHopEdge edge, char *out,
                                                size_t out_cap) {
  if (jvmti != nullptr && jni != nullptr &&
      (edge.edge_kind == JVMTI_HEAP_REFERENCE_FIELD ||
       edge.edge_kind == JVMTI_HEAP_REFERENCE_STATIC_FIELD) &&
      edge.field_index >= 0 && edge.referrer_class_tag != 0 && out_cap > 0) {
    const HopLabelClass *labels =
        hopLabelClassFor(jvmti, jni, edge.referrer_class_tag);
    if (labels != nullptr && !labels->decode_failed &&
        (size_t)edge.field_index < labels->field_names.size()) {
      const std::string &name =
          labels->field_names[(size_t)edge.field_index];
      if (!name.empty()) {
        size_t n = name.size() < out_cap - 1 ? name.size() : out_cap - 1;
        memcpy(out, name.data(), n);
        out[n] = '\0';
        return;
      }
      // Empty positioned slot (an interface-field ordinal below the class's own base) - fall
      // through to the kind label.
    }
  }
  if (out_cap > 0) {
    snprintf(out, out_cap, "%s", hopEdgeKindLabel(edge.edge_kind));
  }
}

void ReferenceChainTracker::fillHopEdgeLabels(
    jvmtiEnv *jvmti, JNIEnv *jni, const std::vector<ChainHopEdge> &edges,
    std::vector<ReferenceChainHop> *out) {
  char label[MAX_HOP_EDGE_LABEL + 1];
  for (size_t i = 0; i < edges.size() && i < out->size(); i++) {
    resolveHopEdgeLabel(jvmti, jni, edges[i], label, sizeof(label));
    (*out)[i].edge_label = label;
  }
}

