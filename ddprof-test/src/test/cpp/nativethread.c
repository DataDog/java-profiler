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


static pthread_t thread_id = { 0 };

// Function to be executed by the new thread
void* thread_function(void* arg) {
    char* message = (char*)arg; // Cast the void* argument back to a string
    printf("Thread received message: %s\n", message);
    pthread_exit(NULL); // Terminate the thread, optionally returning a value
}

jlong JNICALL Java_com_datadoghq_profiler_nativethread_NativeThreadTest_createNativeThread
  (JNIEnv * env, jclass clz) {

    char* message = "Hello from the new thread!"; // Message to pass to the thread

    // Create a new thread
    // Arguments:
    // 1. &thread_id: Pointer to the pthread_t variable where the new thread's ID will be stored.
    // 2. NULL: Pointer to thread attributes (using default attributes here).
    // 3. thread_function: Pointer to the function the new thread will execute.
    // 4. (void*)message: Pointer to the argument to pass to the thread_function.
     pthread_t thread_id;
    int result = pthread_create(&thread_id, NULL, thread_function, (void*)message);

    if (result != 0) {
        perror("Error creating thread");
        return -1L;
    }

    printf("Main thread created a new thread with ID: %lu\n", (unsigned long)thread_id);
    return (jlong) thread_id;
}

void JNICALL Java_com_datadoghq_profiler_nativethread_NativeThreadTest_waitNativeThread
  (JNIEnv * env, jclass clz, jlong threadId) {
    pthread_t thread_id = (pthread_t)threadId;
    // Wait for the created thread to finish
    // Arguments:
    // 1. thread_id: The ID of the thread to wait for.
    // 2. NULL: Pointer to store the return value of the joined thread (not used here).
    pthread_join(thread_id, NULL);
    printf("Thread %lu exited\n", (unsigned long)thread_id);
}