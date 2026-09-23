/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

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

class ReferenceChainsBfsTest : public ::testing::Test {
protected:
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

    static ReferenceChainsBfsTest *active_fixture;

    void SetUp() override {
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

    void TearDown() override {
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

ReferenceChainsBfsTest *ReferenceChainsBfsTest::active_fixture = nullptr;

TEST_F(ReferenceChainsBfsTest, ReconstructsChainForSyntheticGraph) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *classA = (void *)0x2001, *classB = (void *)0x2002,
         *classTarget = (void *)0x2003;
    int ca = addClass(classA, "Lcom/rc/phase3/graph/A;");
    int cb = addClass(classB, "Lcom/rc/phase3/graph/B;");
    int ct = addClass(classTarget, "Lcom/rc/phase3/graph/Target;");

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeTarget = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, ca},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, cb},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeTarget, ct},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    // A single pass that reaches full exhaustion of the reachable graph completes the search and
    // releases every tag it assigned - so the tag must be fetched via tags_ever_assigned (captured
    // at assignment time), not node_tags (already reset to 0 by releaseSearchTags() by the time
    // runPass() returns; see ReleasesTagsOnCompletion below for the release itself).
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    jlong targetTag = tags_ever_assigned[nodeTarget];
    ASSERT_NE(0, targetTag);
    EXPECT_EQ(0, node_tags[nodeTarget]); // released - see the comment above

    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(targetTag, &chain));
    ASSERT_EQ(3u, chain.size());

    int expectedTarget = Profiler::instance()->lookupClass(
        "com/rc/phase3/graph/Target", strlen("com/rc/phase3/graph/Target"));
    int expectedB = Profiler::instance()->lookupClass(
        "com/rc/phase3/graph/B", strlen("com/rc/phase3/graph/B"));
    int expectedA = Profiler::instance()->lookupClass(
        "com/rc/phase3/graph/A", strlen("com/rc/phase3/graph/A"));
    ASSERT_NE(-1, expectedTarget);
    ASSERT_NE(-1, expectedB);
    ASSERT_NE(-1, expectedA);

    EXPECT_EQ((u32)expectedTarget, chain[0]);
    EXPECT_EQ((u32)expectedB, chain[1]);
    EXPECT_EQ((u32)expectedA, chain[2]);

    // buildChainEvent() wraps the same reconstructChain() call into the ReferenceChainEvent shape
    // Recording::recordReferenceChain() (flightRecorder.cpp) expects - same chain/order, plus the
    // target's own depth from FrontierEntry.
    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, targetTag,
                                          &event));
    EXPECT_EQ((u64)targetTag, event._target_tag);
    EXPECT_EQ(2u, event._depth); // root(A, depth0) -> B(depth1) -> Target(depth2)
    ASSERT_EQ(chain.size(), event._hops.size());
    for (size_t i = 0; i < chain.size(); i++) {
      EXPECT_EQ(chain[i], event._hops[i].klass_id);
    }

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BuildChainEventFailsForUnknownTag) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainEvent event;
    EXPECT_FALSE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, 12345,
                                          &event));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BuildAbandonedEventFailsUnlessSearchAbandoned) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Freshly started: never abandoned (never even run a pass yet).
    ReferenceChainAbandonedEvent event;
    EXPECT_FALSE(tracker->buildAbandonedEvent(&event));

    int nodeA = addNode();
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}};
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    // Small graph, no caps hit -> COMPLETED, not ABANDONED.
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_FALSE(tracker->buildAbandonedEvent(&event));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, HopCapStopsAdmittingBeyondCap) {
    Arguments args;
    // hops=1: only depth 0 (direct root references) may be admitted.
    ASSERT_FALSE(args.parse("referencechains=true:hops=1:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // depth 0 - admitted
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // depth 1 - capped
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated); // hop cap is not truncation - a normal boundary
    // Not truncated -> graph fully explored within the hop cap -> the search completes and releases
    // its tags in the same call (see the previous test's comment) - fetch nodeA's tag via
    // tags_ever_assigned, not node_tags.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeB]); // never admitted into the frontier

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BudgetExhaustionTruncatesAndIsReported) {
    Arguments args;
    // budget=1: root enumeration and the expand phase draw from separate budget pools (see
    // runPassManualWalk()'s own comment), each sized 1 here - root enum admits nodeA, then the
    // expand phase's own 1-unit budget admits exactly one of nodeA's two children before
    // exhausting.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // admitted via root enum
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // admitted via expand
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeC, -1},   // expand budget exhausted
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    // Budget exhaustion for *this pass* leaves pending work (nodeC's own edge was never even
    // attempted) - the search stays RUNNING, not COMPLETED, so no tag release happens yet and
    // node_tags[nodeA]/[nodeB] are still the real assigned tags.
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_NE(0, node_tags[nodeB]);
    EXPECT_EQ(0, node_tags[nodeC]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, PreTaggedClassObjectsAreNeverExpandedOrAdmitted) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    node_tags[classNode] = -7; // simulate a class object already tagged by
                               // resolveLoadedClasses() before this pass - see ClassTagTable's
                               // tag-sign convention.
    int fieldTargetNode = addNode();

    script = {
        // A root reference straight to the class object (e.g. a JVMTI_HEAP_REFERENCE_SYSTEM_CLASS
        // root edge in a real walk).
        {JVMTI_HEAP_REFERENCE_SYSTEM_CLASS, -1, classNode, -1},
        // A static field of that class - must never be delivered by a real FollowReferences call,
        // since the class-object edge above must not return JVMTI_VISIT_OBJECTS;
        // mock_FollowReferences enforces this the same way a real traversal would (see its own
        // comment).
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    EXPECT_EQ(-7, node_tags[classNode]); // untouched - never treated as a
                                         // frontier object
    EXPECT_EQ(0, node_tags[fieldTargetNode]); // never reached - the class
                                               // edge above must not expand

    tracker->stop();
}

// Regression test for admitStaticFieldRoots(): an object retained solely by a static field (no
// other GC root reaches it) must still be discovered.
TEST_F(ReferenceChainsBfsTest, DiscoversObjectRetainedOnlyByStaticField) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int fieldTargetNode = addNode();
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/Holder;");

    script = {
        // No GC-root path to fieldTargetNode at all - it is reachable only via classNode's static
        // field.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    // classNode got tagged negative by the real resolveLoadedClasses() scan (not manually, unlike
    // PreTaggedClassObjectsAreNeverExpandedOrAdmitted above), and was never itself admitted as a
    // frontier object.
    EXPECT_LT(node_tags[classNode], 0);

    jlong target_tag = tags_ever_assigned[fieldTargetNode];
    ASSERT_NE(0, target_tag);

    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(target_tag, &chain));
    ASSERT_EQ(1u, chain.size());

    FrontierEntry entry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(target_tag, &entry));
    EXPECT_EQ(0, entry.parent_tag); // root-attached, not a child hop
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, entry.root_kind);

    // buildChainEvent() appends the root TYPE (the declaring class) as the chain's root-side end:
    // the frontier path's terminal element is the static field's holder instance, one hop below the
    // root type.
    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, target_tag,
                                          &event));
    int expectedHolder = Profiler::instance()->lookupClass(
        "com/rc/statics/Holder", strlen("com/rc/statics/Holder"));
    ASSERT_NE(-1, expectedHolder);
    ASSERT_EQ(2u, event._hops.size());
    EXPECT_EQ(chain[0], event._hops[0].klass_id); // the target's own class, unchanged
    EXPECT_EQ((u32)expectedHolder, event._hops[1].klass_id);
    // One label per hop (recordReferenceChain() drops ALL labels when any is empty); the root-type
    // hop's own edge is the unlabeled root edge (field_index -1).
    ASSERT_EQ(2u, event._hops.size());
    EXPECT_FALSE(event._hops[0].edge_label.empty());
    EXPECT_FALSE(event._hops[1].edge_label.empty());

    tracker->stop();
}

// Regression test for the resolveLoadedClasses() scan-skip guard: it must compare `class_count !=
// _last_resolved_class_count`, not `class_count > _last_resolved_class_count`.
TEST_F(ReferenceChainsBfsTest, ResolveLoadedClassesRescansAfterClassCountShrinksAndPartiallyRegrows) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *classA = (void *)0x3001, *classB = (void *)0x3002, *classC = (void *)0x3003;
    addClass(classA, "Lcom/rc/regress/A;");
    int idxB = addClass(classB, "Lcom/rc/regress/B;");

    // Pass 1: both A and B loaded (count == 2) - both get resolved/tagged.
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classA));
    ASSERT_NE(0u, tags.count(classB));
    EXPECT_NE(0, tags[classA]);
    EXPECT_NE(0, tags[classB]);

    // Simulate B's classloader being GC'd: GetLoadedClasses() now reports only A (count shrinks 2
    // -> 1), exactly like a real class unload.
    classes.erase(classes.begin() + idxB);
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1, ReferenceChainsTestAccessor::lastResolvedClassCount());

    // Simulate a *different* class C loading back in, bringing the count back to 2 - the same count
    // as pass 1's peak, but not the same class set.
    addClass(classC, "Lcom/rc/regress/C;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classC));
    EXPECT_NE(0, tags[classC]); // the regression this test guards against

    tracker->stop();
}

// Incremental resumption across passes (ReferenceChainTracker::

TEST_F(ReferenceChainsBfsTest, MultiPassResumptionReconstructsChainAcrossPasses) {
    Arguments args;
    // budget=1 forces each pass to admit at most one new frontier entry, so this 3-hop chain cannot
    // be discovered within a single pass - exercising expandFrontier() (resumed passes), not just
    // the first pass's root walk.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeTarget = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeTarget, -1},
    };

    // Drive the search to completion one pass at a time, exactly as threadLoop() would once wired
    // up (each call bounded by `budget`).
    bool truncated = true;
    int passes_issued = 0;
    while (tracker->searchState() == SearchState::RUNNING && passes_issued < 20) {
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        passes_issued++;
    }

    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_GT(tracker->passesRun(), 1); // did not fit in a single pass
    EXPECT_EQ(tracker->passesRun(), passes_issued);

    jlong targetTag = tags_ever_assigned[nodeTarget];
    ASSERT_NE(0, targetTag);
    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(targetTag, &chain));
    // Depth/parent_tag linkage survived resumption intact - all 3 hops walk back to a root-attached
    // (depth 0) entry, which reconstructChain() requires to succeed at all (see its own "reaching
    // parent_tag == 0" contract).
    EXPECT_EQ(3u, chain.size());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, FrontierCapHitAbandonsImmediately) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ASSERT_EQ(1, tracker->frontierTable()->maxCapacity());

    int nodeA = addNode();
    int nodeB = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // fits (the one slot)
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // frontier cap hit
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    // Frontier-size cap hit -- the search abandons immediately (design doc's Termination-section
    // priority 1).
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());
    ASSERT_EQ(SearchAbandonReason::FRONTIER_CAP, tracker->abandonReason());

    // nodeA was admitted (frontier cap=1 allowed one entry), then its tag was released as part of
    // this same pass's abandon handling (the mock GetObjectsWithTags() succeeds by default).
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    // nodeB was never admitted (frontier cap hit).
    EXPECT_EQ(0, node_tags[nodeB]);

    tracker->stop();
}

// releaseSearchTags()'s GetObjectsWithTags() call failing must NOT be treated as "released" - see
// that method's own comment for why: marking a tag ABANDONED (or resetting _next_tag on restart)
// while its object might still be live would let a restarted search's fresh tags collide with it,
// corrupting FrontierTable's tag-uniqueness invariant.
TEST_F(ReferenceChainsBfsTest, ReleaseSearchTagsFailureBlocksTagReuseUntilItSucceeds) {
    Arguments args;
    // framecap=1 with a self-cycle: pass 1 admits nodeA (the frontier's only slot); the
    // nodeA->nodeA edge then finds nodeA ALREADY_ADMITTED rather than hitting the frontier cap (no
    // new slot is needed for an edge back to an already-tagged object), so the search stays RUNNING
    // and only the no-progress detector - after NO_PROGRESS_PASS_LIMIT stale passes - can abandon
    // it.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1:ttl=0"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    // nodeA -> nodeA self-cycle. With framecap=1, pass 1 admits nodeA; the self-cycle edge is
    // ALREADY_ADMITTED, not a fresh frontier slot.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeA, -1}, // self-cycle
    };

    long long failedBefore =
        Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED);

    fail_get_objects_with_tags = true;
    bool truncated = false;
    // Pass 1: admits nodeA; the self-cycle keeps the pass truncated without growing the frontier
    // further.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_NE(0, node_tags[nodeA]);

    // Run enough stale passes to trigger no-progress abandonment.
    for (int i = 1; i < ReferenceChainTracker::NO_PROGRESS_PASS_LIMIT + 1; i++) {
      ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
      ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    }
    // The next pass should abandon via no-progress.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());

    // GetObjectsWithTags() failed - nodeA's still-live tag must NOT have been cleared, and the
    // failure must be counted.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_NE(0, node_tags[nodeA]) << "tag must not be cleared when the "
                                       "release batch itself failed";
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 1,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // While the release is still outstanding, shouldRunPass() must force a retry unconditionally.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState())
        << "must retry the release in place, not restart, while tags are "
           "still unreleased";

    // A further runPass() call retries the release; still failing.
    int passesBefore = tracker->passesRun();
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(passesBefore, tracker->passesRun());
    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // Once GetObjectsWithTags() starts succeeding again.
    fail_get_objects_with_tags = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED))
        << "a successful release must not itself count as a failure";

    tracker->stop();
}

// Regression test for the CANARY_STUCK/frontier-wipe convergence bug: prior to this fix,
// runPass()'s canary-stuck branch fired purely off _passes_since_last_candidate_progress, so a
// search whose candidate simply had not been found yet was abandoned - and its frontier
// destructively wiped by the next restartSearch() - after only CANARY_NO_PROGRESS_PASS_LIMIT
// passes, even while the whole-graph frontier was still growing every single pass.
TEST_F(ReferenceChainsBfsTest, CanaryStuckRequiresWholeGraphFrontierAlsoStalled) {
    Arguments args;
    // budget=1: exactly one new frontier admission per pass, so the frontier grows every single
    // pass for as long as the chain has unexplored nodes left - _passes_since_last_progress never
    // leaves 0.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A chain longer than the number of passes driven below, so the frontier still has pending work
    // - and is still growing one node per pass - at every pass this test checks.
    constexpr int kChainLength = 50;
    std::vector<int> nodes;
    for (int i = 0; i < kChainLength; i++) {
        nodes.push_back(addNode());
    }
    script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1});
    for (int i = 1; i < kChainLength; i++) {
        script.push_back(
            {JVMTI_HEAP_REFERENCE_FIELD, nodes[i - 1], nodes[i], -1});
    }

    // A canary candidate that this graph never actually contains (no node is ever tagged with the
    // candidate's marker tag) - the candidate-specific stuck counter
    // (_passes_since_last_candidate_progress) climbs every pass with zero discovery progress,
    // exactly like the live-pod scenario chasing a candidate deeper than the old fixed
    // CANARY_NO_PROGRESS_PASS_LIMIT (30) passes could reach.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);

    bool truncated = true;
    // One more pass than the old fixed CANARY_NO_PROGRESS_PASS_LIMIT: long enough that the pre-fix
    // single-condition check would already have abandoned the search, but short enough that the
    // 40-node chain still has unexplored work left, so the frontier is still genuinely growing
    // every pass.
    for (int i = 0; i < ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT + 2;
         i++) {
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        ASSERT_EQ(0, tracker->passesSinceLastProgressForTest())
            << "pass " << i << ": frontier must still be growing every pass";
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState())
            << "pass " << i
            << ": a canary search must not be abandoned while the "
               "whole-graph frontier is still growing, even if its specific "
               "candidate has not yet been found";
    }
    // The narrower candidate-stuck counter climbed the whole time - this is what the old,
    // single-condition check would have abandoned on alone.
    EXPECT_GE(ReferenceChainsTestAccessor::passesSinceLastCandidateProgress(),
              ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT);

    tracker->stop();
}

// Canary-lane backoff pacing (option A): a chase with unresolved candidates runs back-to-back only
// while it is fresh or making candidate progress; each pass with NO candidate progress doubles the
// spacing multiplier (_canary_backoff_mult) up to CANARY_BACKOFF_MULT_MAX, progress resets it to 1,
// and the OOM urgency ramp overrides the gate entirely.
TEST_F(ReferenceChainsBfsTest, CanaryLaneBacksOffWithoutProgressAndResetsOnProgress) {
    Arguments args;
    // Same shape as CanaryStuckRequiresWholeGraphFrontierAlsoStalled above: budget=1 with a long
    // chain keeps the frontier growing one node per pass, so the CANARY_STUCK detector (which also
    // requires a stalled frontier) never fires and the chase stays RUNNING through the whole loop
    // below.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    constexpr int kChainLength = 50;
    std::vector<int> nodes;
    for (int i = 0; i < kChainLength; i++) {
        nodes.push_back(addNode());
    }
    script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1});
    for (int i = 1; i < kChainLength; i++) {
        script.push_back(
            {JVMTI_HEAP_REFERENCE_FIELD, nodes[i - 1], nodes[i], -1});
    }

    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    bool truncated = true;

    // Pass 1: the candidate admission itself raises the progress mark (0 -> 1), so this counts as
    // progress and the multiplier stays at 1 - back-to-back.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryBackoffMult());
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a fresh chase must be allowed to run back-to-back";

    // Pass 2: no candidate progress -> first doubling (1 -> 2).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(2, ReferenceChainsTestAccessor::canaryBackoffMult());
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/2, /*ema_ms=*/100, OS::nanotime());
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a no-progress canary pass must hold off the next one";
    // Beyond the spacing, the chase is allowed again - the backoff paces, it never abandons.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(
        ReferenceChainsTestAccessor::lastCanaryPassNs() +
        2ULL * 100ULL * 1000000ULL + 1))
        << "elapsed spacing must re-admit the canary pass";

    // The OOM urgency ramp overrides the backoff gate entirely.
    ReferenceChainsTestAccessor::setOomRampActive(true);
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "urgency must bypass the canary backoff";
    ReferenceChainsTestAccessor::setOomRampActive(false);

    // Consecutive no-progress passes double the multiplier up to the cap (seeded at 8 so one more
    // pass reaches it, the next holds it).
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/8, /*ema_ms=*/100, OS::nanotime());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult())
        << "the multiplier must hold at its cap, not grow past it";

    // Candidate progress (a new candidate admitted into a slot) resets the lane to back-to-back.
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(1, /*klass_id=*/987);
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryBackoffMult())
        << "candidate progress must reset the spacing multiplier to 1";
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ChainCompletesWithoutAbandonment) {
    Arguments args;
    // budget=1 on a graph where each pass admits exactly one new edge until the chain is exhausted,
    // then the frontier stops growing.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();
    int nodeD = addNode();

    // A chain one node longer than either pass's 1-edge expand budget can fully drain in a single
    // call, so each pass still ends truncated (see mock_FollowReferences()'s own comment: an
    // array-holder walk chains through as many script edges as it can admit before budget aborts
    // it) and there is still pending work left for the no-progress check to catch once the chain is
    // fully discovered.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeC, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeC, nodeD, -1},
    };

    bool truncated = false;
    // Pass 1: root enum admits nodeA, expand admits nodeB, aborts on nodeB->nodeC for lack of
    // budget - truncated, frontier grew (progress).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 2: admits nodeC, aborts on nodeC->nodeD - still truncated, still growing (progress).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 3: admits nodeD, chain exhausted - no longer truncated, no pending frontier, natural
    // completion.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Tags released.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_NE(0, tags_ever_assigned[nodeB]);
    EXPECT_EQ(0, node_tags[nodeB]);

    // No-progress (not TTL) is reported as the reason when the frontier stalls.
    EXPECT_EQ(SearchAbandonReason::NONE, tracker->abandonReason());
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, NoProgressAbandonsSearchAndReleasesTags) {
    // Verify the progress-based abandonment wiring: the no-progress limit is accessible, positive,
    // and reset to 0 by resetSearchStateForTest().
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Verify the no-progress limit is accessible and positive.
    EXPECT_GT(ReferenceChainTracker::NO_PROGRESS_PASS_LIMIT, 0);

    // Verify that a fresh search starts with zero passes since last progress.
    EXPECT_EQ(0, tracker->passesSinceLastProgressForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ResolveOrDropPrunesDeadFrontierEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    // A second root that root enumeration's own 1-unit budget (firstpassbudget=1) can't reach this
    // pass - the resulting root-enum truncation makes runPassManualWalk() return before
    // expandFrontier() ever runs (see its own comment on frontier-cap-hit/budget-exhausted
    // root-enum truncation), so nodeA is admitted but never gets a chance to expand nodeA->nodeB.
    int decoyRoot = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, decoyRoot, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated)); // pass 1
    ASSERT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    jlong aTag = tags_ever_assigned[nodeA];
    ASSERT_NE(0, aTag);
    // Simulate nodeA dying (collected) between pass 1 and pass 2 - GetObjectsWithTags will no
    // longer report it as live.
    dead_tags.insert(aTag);

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated)); // pass 2: resolve-or-drop
    EXPECT_FALSE(truncated);
    // The dead branch was pruned for free - with nothing else pending, the search completes rather
    // than staying RUNNING or being ABANDONED.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(2, tracker->passesRun());

    FrontierEntry entry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(aTag, &entry));
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state);

    // nodeB was never discovered - nodeA's subtree was pruned, not expanded.
    EXPECT_EQ(0, tags_ever_assigned[nodeB]);

    tracker->stop();
}

// pollWatchedTargets() (design doc's Open Question 3 bridging

// =========================================================================== Pod-in-a-jar system
// harness (design node: design-pod-in-a-jar-harness; meta-whackamole-analysis): the REAL tracker
// loop (shouldRunPass -> runPass -> pollWatchedTargets, the exact threadLoop body) driven over the
// scripted mock heap, asserting SYSTEM INVARIANTS instead of unit symptoms.
