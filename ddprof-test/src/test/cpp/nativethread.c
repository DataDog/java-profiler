/*
 * Copyright 2025, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pthread.h>
#include <stdio.h>

#include <jni.h>

#define MAX_PRIME 100000

// Burn CPU
static void do_primes() {
    unsigned long i, num, primes = 0;
    for (num = 1; num <= MAX_PRIME; ++num) {
        for (i = 2; (i <= num) && (num % i != 0); ++i);
        if (i == num)
            ++primes;
    }
}

// Function to be executed by the new thread
void* thread_function(void* arg) {
    do_primes();
    pthread_exit(NULL); // Terminate the thread, optionally returning a value
}

jlong JNICALL Java_com_datadoghq_profiler_nativethread_NativeThreadCreator_createNativeThread
  (JNIEnv * env, jclass clz) {

    // Create a new thread
    // Arguments:
    // 1. &thread_id: Pointer to the pthread_t variable where the new thread's ID will be stored.
    // 2. NULL: Pointer to thread attributes (using default attributes here).
    // 3. thread_function: Pointer to the function the new thread will execute.
    // 4. NULL: Pointer to the argument to pass to the thread_function.
     pthread_t thread_id;
    int result = pthread_create(&thread_id, NULL, thread_function, NULL);

    if (result != 0) {
        perror("Error creating thread");
        return -1L;
    }

    return (jlong) thread_id;
}

void JNICALL Java_com_datadoghq_profiler_nativethread_NativeThreadCreator_waitNativeThread
  (JNIEnv * env, jclass clz, jlong threadId) {
    pthread_t thread_id = (pthread_t)threadId;
    // Wait for the created thread to finish
    // Arguments:
    // 1. thread_id: The ID of the thread to wait for.
    // 2. NULL: Pointer to store the return value of the joined thread (not used here).
    pthread_join(thread_id, NULL);
}