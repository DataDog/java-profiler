---
id: find-dangling-jclass-local-ref-cache
type: finding
status: confirmed-and-fixed
depends_on: [find-test-seam-aliasing]
related: [find-test-seam-aliasing, find-engine-seam-data-race]
tags: [root-cause, fix, jni, crash, test-seams, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# java/lang/Object jclass cached as a LOCAL ref dangles across JNI invocations

Observed: SIGSEGV (hs_err) inside `jni_NewObjectArray` on the SECOND
`runReferenceChainPass0()` call from a Java test thread -
`ReferenceChainTracker::_cached_object_class` held a jclass obtained via
`FindClass()` and cached with a `_cached_object_class_jni` JNIEnv* key.

## Root cause (JNI semantics)

A local ref is freed when its creating native method invocation returns to
Java. The cache was safe for the BFS thread (a native attach that never
returns to Java), which was its only caller - the JNI-entered test seams
broke that assumption: pass 1 caches the local ref, returns to Java, the
JVM frees it, pass 2 passes the dangling jclass into `NewObjectArray()`.

## Fix

`_cached_object_class` is now a GLOBAL ref (valid across invocations,
threads, and detach/attach cycles), which also made the JNIEnv*-identity
keying, the detach-time invalidation in threadLoop's Cleanup, and the
startThread() stale-cache clearing all unnecessary - deleted. Never freed:
java/lang/Object is a bootstrap class and the tracker is a
process-lifetime singleton. The gtest mock JNIEnv needed a `NewGlobalRef`
slot added (mock = identity - the fixture's fake refs are raw pointers).
