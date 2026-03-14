/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "wallclock/wallClock.inline.h"
#include "wallclock/wallClockJVMTI.h"

/* This method is extremely racy!
 * Thread references, that are returned from JVMTI::GetAllThreads(), only guarantee thread objects
 * are not collected by GCs, they don't prevent threads from exiting.
 * We have to be extremely careful when accessing thread's data, so it may not be valid.
 */
void WallClockJVMTI::timerLoop() {

TEST_LOG("VMTI::timerLoop()");

    // Check for enablement before attaching/dettaching the current thread
  if (!isEnabled()) {
    return;
  }

  jvmtiEnv* jvmti = VM::jvmti();
  if (jvmti == nullptr) {
    return;
  }

  // Notice:
  // We want to cache threads that are captured by collectThread(), so that we can
  // clean them up in cleanThreadRefs().
  // The approach is not ideal, but it is cleaner than cleaning individual thread
  // during filtering phases.
  jint threads_count = 0;
  jthread* threads_ptr = nullptr;

  // Attach to JVM as the first step
  VM::attachThread("Datadog Profiler Wallclock Sampler");

  jthread self;
  jvmtiError error = jvmti->GetCurrentThread(&self);
  assert(error == JVMTI_ERROR_NONE);

  JNIEnv* jni = VM::jni();
  jclass thread_class = jni->FindClass("java/lang/Thread");
  assert(thread_class != nullptr);
  jmethodID thread_get_id = jni->GetMethodID(thread_class, "threadId", "()J");
  // java.lang.thread.threadId() only exists in 19+
  if (thread_get_id == nullptr) {
    thread_get_id = jni->GetMethodID(thread_class, "getId", "()J");
  }
  assert(thread_get_id != nullptr);
  long current_thread_id = jni->CallLongMethod(self, thread_get_id);

  auto collectThreads = [&](std::vector<ThreadEntry>& threads) {
      jvmtiEnv* jvmti = VM::jvmti();
      if (jvmti == nullptr) {
          return;
      }

      if (jvmti->GetAllThreads(&threads_count, &threads_ptr) != JVMTI_ERROR_NONE ||
        threads_count == 0) {
        return;
      }

      ThreadFilter* threadFilter = Profiler::instance()->threadFilter();
      bool do_filter = threadFilter->enabled();

      // If filtering is enabled, collect the filtered TIDs first
      std::vector<long> java_tids;

      if (do_filter) {
          Profiler::instance()->threadFilter()->collect_java_tids(java_tids);
          // Sort the TIDs for efficient lookup
          std::sort(java_tids.begin(), java_tids.end());
      }

      for (int i = 0; i < threads_count; i++) {
        jthread thread = threads_ptr[i];
        long tid = jni->CallLongMethod(thread, thread_get_id);
        if (tid == current_thread_id) continue;

        if (!do_filter ||
               // Use binary search to efficiently find if tid is in filtered_tids
               std::binary_search(java_tids.begin(), java_tids.end(), tid)) {
            threads.push_back({thread, tid});
        }
      }
    };

  ThreadStateResolver* const resolver = ThreadStateResolver::getInstance();

  auto sampleThreads = [&](ThreadEntry& thread_entry, int& num_failures, int& threads_already_exited, int& permission_denied) {
    static jint max_stack_depth = (jint)Profiler::instance()->max_stack_depth();

    ExecutionEvent event;
    jthread thread = thread_entry.java;

    event._thread_state = resolver->resolveThreadState(thread);
    if (event._thread_state == OSThreadState::TERMINATED) {
        return false;
    }
    event._execution_mode = resolver->resolveThreadExecutionMode(thread);
    event._weight =  1;

    Profiler::instance()->recordJVMTISample(1, thread_entry.tid, thread_entry.java, BCI_WALL, &event, false);
    return true;
  };

  auto cleanThreadRefs = [&]() {
      JNIEnv* jni = VM::jni();
      for (jint index = 0; index < threads_count; index++) {
        jni->DeleteLocalRef(threads_ptr[index]);
      }
      jvmti->Deallocate((unsigned char*)threads_ptr);
      threads_ptr = nullptr;
      threads_count = 0;
  };

  timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, cleanThreadRefs, _reservoir_size, _interval);


  // Don't forget to detach the thread
  VM::detachThread();
}
