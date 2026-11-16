/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <jni.h>

JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_CarrierThreadTestSupport_runPinned(JNIEnv *env, jclass cls, jobject callback) {
    jclass thread_class = (*env)->FindClass(env, "java/lang/Thread");
    if (thread_class == NULL) return 0;
    jmethodID current = (*env)->GetStaticMethodID(env, thread_class, "currentCarrierThread", "()Ljava/lang/Thread;");
    jobject carrier = current == NULL ? NULL : (*env)->CallStaticObjectMethod(env, thread_class, current);
    jlong id = 0;
    if (carrier != NULL) {
        jmethodID get_id = (*env)->GetMethodID(env, thread_class, "getId", "()J");
        if (get_id != NULL) id = (*env)->CallLongMethod(env, carrier, get_id);
        (*env)->DeleteLocalRef(env, carrier);
    }
    (*env)->DeleteLocalRef(env, thread_class);
    if ((*env)->ExceptionCheck(env)) return 0;
    jclass runnable_class = (*env)->FindClass(env, "java/lang/Runnable");
    if (runnable_class == NULL) return 0;
    jmethodID run = (*env)->GetMethodID(env, runnable_class, "run", "()V");
    /* The native activation keeps callback finally blocks on the writer's carrier. */
    if (run != NULL) (*env)->CallVoidMethod(env, callback, run);
    (*env)->DeleteLocalRef(env, runnable_class);
    return id;
}
