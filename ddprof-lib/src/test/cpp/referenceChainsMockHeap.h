/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Shared scripted heap-graph mock for the reference-chain tracker, gtest-free
// by design: extracted verbatim from ReferenceChainsBfsTest so the libFuzzer
// heap-graph target (src/test/fuzz/fuzz_referenceChainHeap.cpp) drives the
// exact same mock JVMTI/JNI surface as the gtest suite instead of a diverging
// copy. The mock callbacks model FollowReferences/GetObjectsWithTags
// semantics - their comments are the contract; do not weaken them here
// without checking the production code's assumptions.
// Needs referenceChainsTestAccessors.h included first (the mock's setUp()
// calls ReferenceChainsTestAccessor::reset()).

#ifndef REFERENCE_CHAINS_MOCK_HEAP_H
#define REFERENCE_CHAINS_MOCK_HEAP_H

#include <jni.h>
#include <jvmti.h>

#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "os.h"

namespace {
struct ScriptedEdge {
    jvmtiHeapReferenceKind kind;
    int referrer_idx; // -1 = heap root (no referrer)
    int referee_idx;  // index into ReferenceChainsBfsTest::node_tags
    int class_idx;    // index into ReferenceChainsBfsTest::classes, or -1
};

struct ScriptedClass {
    void *klass;
    const char *signature; // JVMTI class signature, e.g. "Lcom/example/Foo;"
};

// Retention-edge label decode fixtures (ReferenceChainsBfsTest's field_decode_hierarchy + the
// hierarchy-introspection mock slots): a fake class hierarchy the slots read, mirroring just enough
// JVMTI class shape for the spec-ordinal decoder (own-declared fields in GetClassFields order,
// direct superclass, directly implemented/extended interfaces).
struct FakeField {
    void *id;       // fake jfieldID
    const char *name;
};
struct FakeClass {
    bool is_interface;
    void *super;                     // fake jclass, or nullptr
    std::vector<void *> interfaces;  // directly implemented/extended
    std::vector<FakeField> fields;   // own-declared, GetClassFields order
};
} // namespace

// Shared SetEventNotificationMode stub - start() calls VM::jvmti()->SetEventNotificationMode(),
// which would dereference the real (null, no live JVM) jvmtiEnv.
inline jvmtiError JNICALL mock_SetEventNotificationMode(jvmtiEnv *, jvmtiEventMode,
                                                        jvmtiEvent, jthread, ...) {
    return JVMTI_ERROR_NONE;
}

// The scripted heap-graph mock (moved verbatim from ReferenceChainsBfsTest; the
// gtest fixture below inherits it so TEST_F bodies keep compiling unchanged).
class ReferenceChainsMockHeap {
public:
    // All members public: the fuzz target (fuzz_referenceChainHeap.cpp) drives
    // the harness from outside a gtest fixture subclass, and the gtest TEST_F
    // bodies access them through fixture inheritance either way.
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ mock_jni{};

    std::unordered_map<void *, jlong> tags;
    std::vector<ScriptedClass> classes;
    std::vector<ScriptedEdge> script;
    std::vector<jlong> node_tags;

    // node_tags[idx] mirrors "the object's *current* live JVMTI tag" (0 once releaseSearchTags()
    // clears it, exactly like a real GetTag() would report after SetTag(obj, 0)).
    std::vector<jlong> tags_ever_assigned;

    // Tags that GetObjectsWithTags() below reports as unresolvable, simulating the referenced
    // object having died (GC'd) between passes - see the resolve-or-drop tests.
    std::unordered_set<jlong> dead_tags;

    // When true, mock_GetObjectsWithTags() below fails outright (as if the real JVMTI call had hit
    // e.g. JVMTI_ERROR_OUT_OF_MEMORY), for ReleaseSearchTagsFailureTest - simulates
    // releaseSearchTags()'s own GetObjectsWithTags() call failing rather than an individual tag
    // failing to resolve (dead_tags above).
    bool fail_get_objects_with_tags = false;

    // When non-zero, mock_GetObjectsWithTags() below busy-waits this many nanoseconds.
    u64 gotw_delay_ns = 0;

    // Synthetic frontier-holder arrays for expandFrontier()'s array-holder walk:
    // mock_NewObjectArray() hands back an opaque handle, mock_SetObjectArrayElement() records its
    // elements here, and mock_FollowReferences() treats every recorded element as an expansion seed
    // (one hop, gated by the production callback's batch_tags) when the holder is passed as
    // initial_object.
    std::unordered_map<jobject, std::vector<jobject>> holders;
    uintptr_t next_holder = 0xF00D0000;

    // FindClass(name) -> registered fake class (see mock_FindClass' own comment): names
    // descendFromAnchor()'s resolutions look up ("java/lang/ClassLoader", "java/lang/ThreadGroup",
    // "java/security/ProtectionDomain", "java/lang/ThreadLocal$ThreadLocalMap",
    // "java/lang/Thread").
    std::unordered_map<std::string, void *> find_classes;
    // Fake class returned by mock_GetObjectClass() for unregistered objects
    // (walkCandidateThreadLocals()'s fresh-anchor admission path).
    void *thread_class = nullptr;

    // DeleteGlobalRef call count (see mock_DeleteGlobalRef).
    int global_refs_deleted_ = 0;

    jvmtiEnv *orig_jvmti = nullptr;

    // One live harness per process (the production callbacks are static members
    // keyed off this pointer). inline static: the header is included by both the
    // gtest TU and the fuzz TU.
    inline static ReferenceChainsMockHeap *active_fixture = nullptr;

    void setUp() {
        active_fixture = this;
        // See ReferenceChainsTestAccessor's own comment - without this, a prior test in this suite
        // that drove the search to SearchState::COMPLETED/ABANDONED would make every runPass() call
        // below a permanent no-op.
        ReferenceChainsTestAccessor::reset();
        jvmti_tbl = jvmtiInterface_1_{};
        // start() calls VM::jvmti()->SetEventNotificationMode() - stub it and swap VM::_jvmti
        // (VMTestAccessor, declared above) the same way ReferenceChainsTest's fixture does, so
        // start() does not dereference the real (null, no live JVM) jvmtiEnv.
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.SetTag = &mock_SetTag;
        jvmti_tbl.GetTag = &mock_GetTag;
        jvmti_tbl.GetLoadedClasses = &mock_GetLoadedClasses;
        jvmti_tbl.GetClassLoader = &mock_GetClassLoader;
        jvmti_tbl.GetClassSignature = &mock_GetClassSignature;
        jvmti_tbl.Deallocate = &mock_Deallocate;
        jvmti_tbl.FollowReferences = &mock_FollowReferences;
        jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
        jvmti_tbl.GetObjectsWithTags = &mock_GetObjectsWithTags;
        // Retention-edge label decode path (hopLabelClassFor()).
        jvmti_tbl.IsInterface = &mock_IsInterface;
        jvmti_tbl.GetImplementedInterfaces = &mock_GetImplementedInterfaces;
        jvmti_tbl.GetClassFields = &mock_GetClassFields;
        jvmti_tbl.GetFieldName = &mock_GetFieldName;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
        jni_tbl.FindClass = &mock_FindClass;
        jni_tbl.GetObjectClass = &mock_GetObjectClass;
        jni_tbl.GetSuperclass = &mock_JniGetSuperclass;
        jni_tbl.NewGlobalRef = &mock_NewGlobalRef;
        jni_tbl.DeleteGlobalRef = &mock_DeleteGlobalRef;
        jni_tbl.EnsureLocalCapacity = &mock_EnsureLocalCapacity;
        jni_tbl.NewObjectArray = &mock_NewObjectArray;
        jni_tbl.SetObjectArrayElement = &mock_SetObjectArrayElement;
        jni_tbl.ExceptionCheck = &mock_ExceptionCheck;
        jni_tbl.ExceptionClear = &mock_ExceptionClear;
        mock_jni.functions = &jni_tbl;
    }

    void tearDown() {
        VMTestAccessor::setJvmti(orig_jvmti);
        active_fixture = nullptr;
    }

    // Registers a fake class (matched by identity, not by any real JNI semantics) that
    // resolveLoadedClasses() will discover via the mocked GetLoadedClasses().
    int addClass(void *klass, const char *signature) {
        classes.push_back({klass, signature});
        return (int)classes.size() - 1;
    }

    // addClass() + a mock_FindClass(name) registry entry in one step, for the classes
    // descendFromAnchor()'s resolution helpers look up by name (see find_classes' own comment).
    int registerClassForFindClass(void *klass, const char *name,
                                   const char *signature) {
        int idx = addClass(klass, signature);
        find_classes[name] = klass;
        return idx;
    }

    // Adds an as-yet-untagged frontier node, returning its index into node_tags for use as a
    // ScriptedEdge referrer_idx/referee_idx.
    int addNode() {
        node_tags.push_back(0);
        tags_ever_assigned.push_back(0);
        return (int)node_tags.size() - 1;
    }

    // Reverse lookup from a node's synthetic identity (&node_tags[idx], see mock_FollowReferences'
    // initial_object handling below) back to its index.
    int indexOfNode(jobject obj) const {
        for (size_t i = 0; i < node_tags.size(); i++) {
            if (obj == (jobject)&node_tags[i]) {
                return (int)i;
            }
        }
        return -1;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        // releaseSearchTags() calls SetTag(obj, 0) on the resolved objects GetObjectsWithTags()
        // (below) hands back for a frontier node - route that through node_tags[idx] directly (the
        // same storage GetObjectsWithTags's resolution and the production callback's tag_ptr writes
        // both key off of), so the release is actually observable, not just recorded in a side map
        // nothing else reads.
        int idx = active_fixture->indexOfNode(object);
        if (idx >= 0) {
            active_fixture->node_tags[idx] = tag;
            return JVMTI_ERROR_NONE;
        }
        if (tag == 0) {
            active_fixture->tags.erase(object);
        } else {
            active_fixture->tags[object] = tag;
        }
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetTag(jvmtiEnv *, jobject object, jlong *tag_ptr) {
        int idx = active_fixture->indexOfNode(object);
        if (idx >= 0) {
            *tag_ptr = active_fixture->node_tags[idx];
            return JVMTI_ERROR_NONE;
        }
        auto it = active_fixture->tags.find(object);
        *tag_ptr = it != active_fixture->tags.end() ? it->second : 0;
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetLoadedClasses(jvmtiEnv *, jint *count_ptr,
                                                     jclass **classes_ptr) {
        auto &classes = active_fixture->classes;        *count_ptr = (jint)classes.size();
        *classes_ptr = classes.empty()
                ? nullptr
                : (jclass *)malloc(sizeof(jclass) * classes.size());
        for (size_t i = 0; i < classes.size(); i++) {
            (*classes_ptr)[i] = (jclass)classes[i].klass;
        }
        return JVMTI_ERROR_NONE;
    }

    // admitStaticFieldRoots()'s app-classes-first partition (referenceChains.cpp) calls this for
    // every loaded class.
    static jvmtiError JNICALL mock_GetClassLoader(jvmtiEnv *, jclass,
                                                   jobject *classloader_ptr) {
        *classloader_ptr = nullptr;
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetClassSignature(jvmtiEnv *, jclass klass,
                                                       char **signature_ptr,
                                                       char **generic_ptr) {
        for (auto &c : active_fixture->classes) {
            if (c.klass == (void *)klass) {
                *signature_ptr = strdup(c.signature);
                if (generic_ptr != nullptr) {
                    *generic_ptr = nullptr;
                }
                return JVMTI_ERROR_NONE;
            }
        }
        return JVMTI_ERROR_INVALID_CLASS;
    }

    static jvmtiError JNICALL mock_Deallocate(jvmtiEnv *, unsigned char *mem) {
        free(mem);
        return JVMTI_ERROR_NONE;
    }

    static void JNICALL mock_DeleteLocalRef(JNIEnv *, jobject) {
        // no-op: this fixture's fake jobject/jclass values are not real JNI local refs.
    }

    // Retention-edge label decode fixtures (fillHopEdgeLabels()/ hopLabelClassFor()): a fake class
    // hierarchy the hierarchy-introspection slots below read, plus a tag -> fake jclass map (the
    // decoder resolves the referrer class from its raw tag via GetObjectsWithTags - the test
    // populates field_decode_classes from resolveLoadedClasses()-minted tags, and
    // mock_GetObjectsWithTags consults it first).
    std::unordered_map<jlong, void *> field_decode_classes;
    std::unordered_map<void *, FakeClass> field_decode_hierarchy;

    // The hierarchy-introspection slots the decoder needs (IsInterface/
    // GetImplementedInterfaces/GetClassFields/GetFieldName on the JVMTI table, GetSuperclass on the
    // JNI table - modern JVMTI dropped its own GetSuperclass).
    static jvmtiError JNICALL mock_IsInterface(jvmtiEnv *, jclass cls,
                                               jboolean *is_interface_ptr) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        if (it == active_fixture->field_decode_hierarchy.end()) {
            return JVMTI_ERROR_INVALID_CLASS;
        }
        *is_interface_ptr = it->second.is_interface ? JNI_TRUE : JNI_FALSE;
        return JVMTI_ERROR_NONE;
    }
    static jclass JNICALL mock_JniGetSuperclass(JNIEnv *, jclass cls) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        return it == active_fixture->field_decode_hierarchy.end()
                       ? nullptr
                       : (jclass)it->second.super;
    }
    static jvmtiError JNICALL mock_GetImplementedInterfaces(
            jvmtiEnv *, jclass cls, jint *count_ptr, jclass **ifaces_ptr) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        if (it == active_fixture->field_decode_hierarchy.end()) {
            return JVMTI_ERROR_INVALID_CLASS;
        }
        const std::vector<void *> &ifaces = it->second.interfaces;
        *count_ptr = (jint)ifaces.size();
        *ifaces_ptr = ifaces.empty()
                ? nullptr
                : (jclass *)malloc(sizeof(jclass) * ifaces.size());
        for (size_t i = 0; i < ifaces.size(); i++) {
            (*ifaces_ptr)[i] = (jclass)ifaces[i];
        }
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL mock_GetClassFields(
            jvmtiEnv *, jclass cls, jint *count_ptr, jfieldID **fields_ptr) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        if (it == active_fixture->field_decode_hierarchy.end()) {
            return JVMTI_ERROR_INVALID_CLASS;
        }
        const std::vector<FakeField> &fields = it->second.fields;
        *count_ptr = (jint)fields.size();
        *fields_ptr = fields.empty()
                ? nullptr
                : (jfieldID *)malloc(sizeof(jfieldID) * fields.size());
        for (size_t i = 0; i < fields.size(); i++) {
            (*fields_ptr)[i] = (jfieldID)fields[i].id;
        }
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL mock_GetFieldName(
            jvmtiEnv *, jclass, jfieldID field, char **name_ptr,
            char ** /*signature_ptr*/, char ** /*generic_ptr*/) {
        for (const auto &kv : active_fixture->field_decode_hierarchy) {
            for (const FakeField &f : kv.second.fields) {
                if (f.id == (void *)field) {
                    size_t len = strlen(f.name) + 1;
                    char *name = (char *)malloc(len);
                    memcpy(name, f.name, len);
                    *name_ptr = name;
                    return JVMTI_ERROR_NONE;
                }
            }
        }
        return JVMTI_ERROR_INVALID_FIELDID;
    }

    // expandFrontier()/admitStaticFieldRoots() resolve java/lang/Object once as the holder array's
    // element type - a non-null fake jclass is all it needs (the type is never introspected, only
    // passed to NewObjectArray()).
    static jclass JNICALL mock_FindClass(JNIEnv *, const char *name) {
        auto it = active_fixture->find_classes.find(name);
        if (it != active_fixture->find_classes.end()) {
            return (jclass)it->second;
        }
        return (jclass)0xC1A55;
    }

    // walkCandidateThreadLocals()'s fresh-anchor admission calls GetObjectClass(thread) -
    // unregistered classes return the fixture's fake Thread class (set_thread_class) so the anchor
    // entry's class tag resolves through the same mocked GetTag/tagging path.
    static jclass JNICALL mock_GetObjectClass(JNIEnv *, jobject) {
        return (jclass)active_fixture->thread_class;
    }


    // The production code wraps that fake jclass in a global ref (a real local ref would dangle
    // across JNI-entered test seams - see _cached_object_class's own comment).
    static jobject JNICALL mock_NewGlobalRef(JNIEnv *, jobject obj) {
        return obj;
    }

    // Counts DeleteGlobalRef calls - the deferred thread-ref teardown test
    // (ThreadRefUnregisterDefersGlobalRefDeletion) asserts on the count.
    static void JNICALL mock_DeleteGlobalRef(JNIEnv *, jobject) {
        active_fixture->global_refs_deleted_++;
    }

    static jint JNICALL mock_EnsureLocalCapacity(JNIEnv *, jint) {
        return JNI_OK;
    }

    // expandFrontier() calls jniExceptionCheck() after every upcall that can legally throw
    // (NewObjectArray/SetObjectArrayElement/EnsureLocalCapacity failures) - this fixture's mocks
    // never throw, so there is never a pending exception to report or clear.
    static jboolean JNICALL mock_ExceptionCheck(JNIEnv *) {
        return JNI_FALSE;
    }

    static void JNICALL mock_ExceptionClear(JNIEnv *) {
        // no-op: mock_ExceptionCheck() never reports a pending exception.
    }

    // Hands back a fresh opaque holder handle and registers it in `holders` so
    // mock_SetObjectArrayElement()/mock_FollowReferences() can find its elements.
    static jobjectArray JNICALL mock_NewObjectArray(JNIEnv *, jsize, jclass,
                                                     jobject) {
        jobject handle = (jobject)(active_fixture->next_holder++);
        active_fixture->holders[handle] = {};
        return (jobjectArray)handle;
    }

    static void JNICALL mock_SetObjectArrayElement(JNIEnv *, jobjectArray array,
                                                    jsize idx, jobject value) {        active_fixture->holders[(jobject)array].push_back(value);
    }

    // runPassManualWalk()'s root enumeration (the default, non-fallback path): reports each
    // scripted root edge's referee to heapRootCallback() exactly as a real
    // IterateOverReachableObjects() reports a root-held object - tag_ptr only, no oop, no
    // transitive children (see runPassManualWalk()'s own comment).
    static jvmtiError JNICALL mock_IterateOverReachableObjects(
            jvmtiEnv *, jvmtiHeapRootCallback heap_root_cb,
            jvmtiStackReferenceCallback, jvmtiObjectReferenceCallback,
            const void *user_data) {
        for (auto &e : active_fixture->script) {
            if (e.referrer_idx != -1) {
                continue;
            }
            jlong class_tag = 0;
            if (e.class_idx >= 0) {
                class_tag = active_fixture->tags[active_fixture->classes[e.class_idx].klass];
            }
            jlong *tag_ptr = &active_fixture->node_tags[e.referee_idx];
            jvmtiIterationControl ctl = heap_root_cb(
                    JVMTI_HEAP_ROOT_JNI_GLOBAL, class_tag, /*size=*/0, tag_ptr,
                    const_cast<void *>(user_data));
            if (*tag_ptr != 0) {
                active_fixture->tags_ever_assigned[e.referee_idx] = *tag_ptr;
            }
            if (ctl == JVMTI_ITERATION_ABORT) {
                break;
            }
        }
        return JVMTI_ERROR_NONE;
    }

    // Resolves each requested tag to its node's synthetic identity (&node_tags[idx]) by scanning
    // node_tags for a matching current value - mirroring real GetObjectsWithTags()'s "only
    // currently-live tags come back" contract.
    static jvmtiError JNICALL mock_GetObjectsWithTags(
            jvmtiEnv *, jint tag_count, const jlong *req_tags, jint *count_ptr,
            jobject **object_result_ptr, jlong **tag_result_ptr) {
        if (active_fixture->fail_get_objects_with_tags) {
            // Deliberately leave *count_ptr/*object_result_ptr/*tag_result_ptr untouched - a real
            // failed JVMTI call makes no promise about them, and releaseSearchTags() must not read
            // them on this path.
            return JVMTI_ERROR_OUT_OF_MEMORY;
        }
        if (active_fixture->gotw_delay_ns != 0) {
            u64 until = OS::nanotime() + active_fixture->gotw_delay_ns;
            while (OS::nanotime() < until) {
                // busy-wait: a sleep could overshoot by scheduler latency, and the overshoot
                // direction matters for the one-batch deadline arithmetic the callers of this knob
                // rely on.
            }
        }
        std::vector<jobject> objs;
        std::vector<jlong> found;
        for (jint i = 0; i < tag_count; i++) {
            jlong want = req_tags[i];
            if (want == 0 || active_fixture->dead_tags.count(want) > 0) {
                continue;
            }
            // The decoder resolves a referrer CLASS from its raw (negative) tag - no node carries
            // one, so the tag -> fake jclass map (field_decode_classes, see its own comment) serves
            // it.
            auto fd = active_fixture->field_decode_classes.find(want);
            if (fd != active_fixture->field_decode_classes.end()) {
                objs.push_back((jobject)fd->second);
                found.push_back(want);
                break;
            }
            for (size_t idx = 0; idx < active_fixture->node_tags.size(); idx++) {
                if (active_fixture->node_tags[idx] == want) {
                    objs.push_back((jobject)&active_fixture->node_tags[idx]);
                    found.push_back(want);
                    break;
                }
            }
        }
        *count_ptr = (jint)objs.size();
        *object_result_ptr = objs.empty()
                ? nullptr : (jobject *)malloc(sizeof(jobject) * objs.size());
        *tag_result_ptr = found.empty()
                ? nullptr : (jlong *)malloc(sizeof(jlong) * found.size());
        for (size_t i = 0; i < objs.size(); i++) {
            (*object_result_ptr)[i] = objs[i];
            (*tag_result_ptr)[i] = found[i];
        }
        return JVMTI_ERROR_NONE;
    }

    // Plays back `script` against the real production heap_reference_callback, modelling enough of
    // FollowReferences' actual semantics for these heap-walk tests to be meaningful: - "a reference
    // from A to B is not traversed until A is visited" - an edge whose referrer was not returned
    // JVMTI_VISIT_OBJECTS for (or was never itself visited) is skipped, exactly as a real traversal
    // would never reach it.
    static jvmtiError JNICALL mock_FollowReferences(
            jvmtiEnv *, jint, jclass, jobject initial_object,
            const jvmtiHeapCallbacks *callbacks, const void *user_data) {
        std::unordered_map<int, bool> expandable;        // seed_idx == -2 marks the root walk (initial_object == NULL); any
        // other value marks an expansion walk seeded from one or more boundary objects, in which
        // case root edges are never replayed.
        int seed_idx = -2;
        // The transient holder array itself is never tagged (mirrors real production:
        // admitStaticFieldRoots()/expandFrontier() never call SetTag on the frontier-holder array
        // they build), so every holder->element ARRAY_ELEMENT edge below is replayed with a
        // referrer tag of 0.
        static jlong holder_tag = 0;
        if (initial_object != nullptr) {
            auto holder_it = active_fixture->holders.find(initial_object);
            if (holder_it != active_fixture->holders.end()) {
                // Array-holder walk (expandFrontier()'s already-tagged boundary batch, or
                // admitStaticFieldRoots()'s negative- tagged class-object seed): actually invoke
                // the production callback for each holder->element edge, exactly like a real
                // FollowReferences(initial_object=holder_array) call would - this is what lets
                // heap_reference_callback()'s own tag-sign/reference_kind logic (e.g. the *tag_ptr
                // < 0 early-return and its admitStaticFieldRoots() carve-out) actually run, rather
                // than assuming every element is expandable.
                seed_idx = -1;
                for (jobject elem : holder_it->second) {
                    int idx = active_fixture->indexOfNode(elem);
                    if (idx < 0) {
                        continue;
                    }
                    jlong *tag_ptr = &active_fixture->node_tags[idx];
                    jint ctl = callbacks->heap_reference_callback(
                            JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, nullptr,
                            /*class_tag=*/0, /*referrer_class_tag=*/0,
                            /*size=*/0, tag_ptr, &holder_tag,
                            /*length=*/-1, const_cast<void *>(user_data));
                    if (*tag_ptr != 0) {
                        active_fixture->tags_ever_assigned[idx] = *tag_ptr;
                    }
                    if (ctl & JVMTI_VISIT_ABORT) {
                        return JVMTI_ERROR_NONE;
                    }
                    expandable[idx] = (ctl & JVMTI_VISIT_OBJECTS) != 0;                }
            } else {
                seed_idx = active_fixture->indexOfNode(initial_object);
                expandable[seed_idx] = true;
            }
        }
        for (auto &e : active_fixture->script) {
            if (e.referrer_idx == -1) {
                if (seed_idx != -2) {
                    continue; // resumed pass: never replay root edges
                }
            } else {
                auto it = expandable.find(e.referrer_idx);
                if (it == expandable.end() || !it->second) {                    continue;
                }
            }            jlong class_tag = 0;
            if (e.class_idx >= 0) {
                class_tag = active_fixture->tags[active_fixture->classes[e.class_idx].klass];
            }
            jlong *referrer_tag_ptr = e.referrer_idx >= 0
                    ? &active_fixture->node_tags[e.referrer_idx] : nullptr;
            jlong *tag_ptr = &active_fixture->node_tags[e.referee_idx];
            jint ctl = callbacks->heap_reference_callback(
                    e.kind, nullptr, class_tag, /*referrer_class_tag=*/0,
                    /*size=*/0, tag_ptr, referrer_tag_ptr, /*length=*/-1,
                    const_cast<void *>(user_data));
            if (*tag_ptr != 0) {
                active_fixture->tags_ever_assigned[e.referee_idx] = *tag_ptr;
            }
            if (ctl & JVMTI_VISIT_ABORT) {
                return JVMTI_ERROR_NONE;
            }
            expandable[e.referee_idx] = (ctl & JVMTI_VISIT_OBJECTS) != 0;
        }
        return JVMTI_ERROR_NONE;
    }

};

#endif // REFERENCE_CHAINS_MOCK_HEAP_H
