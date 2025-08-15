/*
 * Copyright 2025 Datadog, Inc
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

    #include <gtest/gtest.h>

    #include "asyncSampleMutex.h"
    #include "buffers.h"
    #include "callTraceStorage.h"
    #include "context.h"
    #include "counters.h"
    #include "livenessTracker.h"
    #include "mutex.h"
    #include "os.h"
    #include "spinLock.h"
    #include "unwindStats.h"
    #include "threadFilter.h"
    #include "threadInfo.h"
    #include "threadLocalData.h"
    #include "vmEntry.h"
    #include <map>
    #include <thread>
    #include <vector>
    #include <atomic>
    #include <chrono>
    #include <cstring>

    ssize_t callback(char* ptr, int len) {
        return len;
    }

    TEST(Buffer, var64_encoding) {
        RecordingBuffer buf;

        u64 val = 2097150;

        buf.putVar64(val);
    }

    TEST(Buffer, skip_flush) {
        RecordingBuffer buf;

        // no need to flush empty buffer
        EXPECT_FALSE(buf.flushIfNeeded(callback));

        buf.skip(10);
        // no need to flush when well below the limit
        EXPECT_FALSE(buf.flushIfNeeded(callback));

        buf.skip(RECORDING_BUFFER_LIMIT - buf.offset() + 1);
        // flush is needed here
        EXPECT_TRUE(buf.flushIfNeeded(callback));

        // buff was flushed this should not trigger the assert
        buf.skip(RECORDING_BUFFER_LIMIT);

        // writing over limit must trigger assert
        EXPECT_DEATH({
            buf.skip(RECORDING_BUFFER_LIMIT);
            buf.skip(RECORDING_BUFFER_LIMIT);
        }, "Assertion .*");
    }

    TEST(Buffer, writeString) {
        int clen = 4191;
        char* str = (char*)malloc(clen + 1);
        memset(str, 'a', clen);
        str[clen] = 0;

        RecordingBuffer buf;

        buf.skip(buf.limit() - clen * 2);
        buf.putUtf8(str);

        EXPECT_FALSE(buf.flushIfNeeded(callback));

        EXPECT_DEATH({
            buf.putUtf8(str);
        }, "Assertion .*");
        free(str);
    }

    TEST(Buffer, writeStringWithLength) {
        int clen = 1 << 16;
        char* str = (char*)malloc(clen + 1);
        memset(str, 'a', clen);
        str[clen] = 0;

        RecordingBuffer buf[2];

        buf[0].putUtf8(str, clen);
        // should be able to write to the adjacent buffer unaffected
        buf[1].put8(1);
        EXPECT_EQ(1, buf[1].data()[0]);
        // long string should have been truncated to 8191 characters
        int prefix = 1 + (31 - __builtin_clz(8191)) / 7 + 1;
        EXPECT_EQ(0, buf[0].data()[prefix + 8191]);
        free(str);
    }

    TEST(OS, threadId_sanity) {
        EXPECT_FALSE(OS::getMaxThreadId() < 0);
    }

    TEST(Context, maxtid_sanity) {
        int maxTid = OS::getMaxThreadId();

        Context& ctx1 = Contexts::get(0);
        Context& ctx2 = Contexts::get(maxTid - 1);

        if (maxTid >= DD_CONTEXT_PAGE_SIZE) {
            Context& ctx3 = Contexts::get(DD_CONTEXT_PAGE_SIZE);
        }
    }

    TEST(Context, maxpages) {
        // floored at 128 to mitigate unusual pid_max settings
        int minMaxPages = 128;
        EXPECT_EQ(minMaxPages, Contexts::getMaxPages(0));
        EXPECT_EQ(minMaxPages, Contexts::getMaxPages(1));
        EXPECT_EQ(minMaxPages, Contexts::getMaxPages(DD_CONTEXT_PAGE_SIZE / 2));
        EXPECT_EQ(minMaxPages, Contexts::getMaxPages(DD_CONTEXT_PAGE_SIZE));
        EXPECT_EQ(minMaxPages, Contexts::getMaxPages(DD_CONTEXT_PAGE_SIZE + 1));
        int floor = minMaxPages * DD_CONTEXT_PAGE_SIZE;
        EXPECT_EQ(minMaxPages, Contexts::getMaxPages(floor + 0));
        EXPECT_EQ(minMaxPages + 1, Contexts::getMaxPages(floor + 1));
        EXPECT_EQ(minMaxPages + 1, Contexts::getMaxPages(floor + DD_CONTEXT_PAGE_SIZE / 2));
        EXPECT_EQ(minMaxPages + 1, Contexts::getMaxPages(floor + DD_CONTEXT_PAGE_SIZE));
        EXPECT_EQ(minMaxPages + 2, Contexts::getMaxPages(floor + DD_CONTEXT_PAGE_SIZE + 1));
        EXPECT_EQ(2048, Contexts::getMaxPages(2097152));
    }

    TEST(ThreadFilter, testThreadFilter) {
        int maxTid = OS::getMaxThreadId();
        ThreadFilter filter;
        filter.init("");
        ASSERT_TRUE(filter.enabled());
        EXPECT_EQ(0, filter.size());
        // increase step gradually to create different bit densities
        int step = 1;
        int size = 0;
        for (int tid = 1; tid < maxTid - step - 1; tid += step, size++) {
            EXPECT_FALSE(filter.accept(tid));
            filter.add(tid);
            EXPECT_TRUE(filter.accept(tid));
            step++;
        }
        ASSERT_EQ(size, filter.size());
        std::vector<int> tids;
        tids.reserve(size);
        filter.collect(tids);
        ASSERT_EQ(size, tids.size());
        for (int tid : tids) {
            ASSERT_TRUE(filter.accept(tid));
            filter.remove(tid);
            ASSERT_FALSE(filter.accept(tid));
        }
        EXPECT_EQ(0, filter.size());
    }

    TEST(ThreadInfoTest, testThreadInfoCleanupAllDead) {
        ThreadInfo info;
        info.set(1, "main", 1);
        info.set(2, "ephemeral", 2);
        ASSERT_EQ(2, info.size());

        std::set<int> live_thread_ids;
        live_thread_ids.insert(1);

        // make sure only the non-live threads are removed
        info.clearAll(live_thread_ids);
        ASSERT_EQ(1, info.size());
        ASSERT_EQ(-1, info.getThreadId(2));

        // sanity check that all threads are removed when no live threads are provided
        std::set<int> empty_set;
        info.set(2, "ephemeral-1", 2);
        info.clearAll(empty_set);
        ASSERT_EQ(0, info.size());
    }

    TEST(ThreadInfoTest, testThreadInfoCleanupAll) {
        ThreadInfo info;
        info.set(1, "main", 1);
        info.set(2, "ephemeral", 2);
        ASSERT_EQ(2, info.size());

        info.clearAll();
        ASSERT_EQ(0, info.size());
    }

    TEST(AsyncSampleMutex, testAsyncSampleMutexInterleaving) {
        ThreadLocalData data;
        EXPECT_FALSE(data.is_unwinding_Java());
        {
            AsyncSampleMutex first(&data);
            EXPECT_TRUE(first.acquired());
            EXPECT_TRUE(data.is_unwinding_Java());
            {
                AsyncSampleMutex second(&data);
                EXPECT_FALSE(second.acquired());
                EXPECT_TRUE(first.acquired());
                EXPECT_TRUE(data.is_unwinding_Java());
            }
            EXPECT_TRUE(first.acquired());
        }
        EXPECT_FALSE(data.is_unwinding_Java());
    }

    TEST(JavaVersionAccess, testJavaVersionAccess_hs_8) {
        char runtime_prop_value_1[] = "1.8.0_292";
        char vm_prop_value_1[] = "25.292-b10";
        char runtime_prop_value_2[] = "8.0.292";
        char vm_prop_value_2[] = "25.292-b10";

        JavaFullVersion java_version1 = JavaVersionAccess::get_java_version(runtime_prop_value_1);
        int hs_version1 = JavaVersionAccess::get_hotspot_version(vm_prop_value_1);
        EXPECT_EQ(8, java_version1.major);
        EXPECT_EQ(292, java_version1.update);
        EXPECT_EQ(8, hs_version1);

        JavaFullVersion java_version2 = JavaVersionAccess::get_java_version(runtime_prop_value_2);
        int hs_version2 = JavaVersionAccess::get_hotspot_version(vm_prop_value_2);
        EXPECT_EQ(8, java_version2.major);
        EXPECT_EQ(292, java_version2.update);
        EXPECT_EQ(8, hs_version2);
    }

    TEST(JavaVersionAccess, testJavaVersionAccess_hs_11) {
        char runtime_prop_value_1[] = "11.0.25";
        char vm_prop_value_1[] = "11.0.25+10";

        JavaFullVersion java_version1 = JavaVersionAccess::get_java_version(runtime_prop_value_1);
        int hs_version1 = JavaVersionAccess::get_hotspot_version(vm_prop_value_1);
        EXPECT_EQ(11, java_version1.major);
        EXPECT_EQ(25, java_version1.update);
        EXPECT_EQ(11, hs_version1);
    }

    TEST(JavaVersionAccess, testJavaVersionAccess_hs_default) {
        char runtime_prop_value_1[] = "3.11.25x_10";
        char vm_prop_value_1[] = "3.11.25x_10";

        JavaFullVersion java_version1 = JavaVersionAccess::get_java_version(runtime_prop_value_1);
        int hs_version1 = JavaVersionAccess::get_hotspot_version(vm_prop_value_1);
        EXPECT_EQ(9, java_version1.major);
        EXPECT_EQ(25, java_version1.update);
        EXPECT_EQ(9, hs_version1);
    }

    TEST(JavaVersionAccess, testJavaVersionAccess_hs_24) {
        char runtime_prop_value_1[] = "24+36-FR";
        char vm_prop_value_1[] = "24+36-FR";

        JavaFullVersion java_version1 = JavaVersionAccess::get_java_version(runtime_prop_value_1);
        int hs_version1 = JavaVersionAccess::get_hotspot_version(vm_prop_value_1);
        EXPECT_EQ(24, java_version1.major);
        EXPECT_EQ(0, java_version1.update);
        EXPECT_EQ(24, hs_version1);
    }

    TEST(UnwindFailures, BasicFunctionality) {
      UnwindFailures failures;

      // Test recording failures
      EXPECT_EQ(0, failures.count("test_stub1"));
      failures.record(UNWIND_FAILURE_STUB, "test_stub1");
      EXPECT_EQ(1, failures.count("test_stub1"));

      failures.record(UNWIND_FAILURE_COMPILED, "test_stub1");
      EXPECT_EQ(1, failures.count("test_stub1", UNWIND_FAILURE_STUB));
      EXPECT_EQ(1, failures.count("test_stub1", UNWIND_FAILURE_COMPILED));
      EXPECT_EQ(2, failures.count("test_stub1"));

      // Test different stubs
      EXPECT_EQ(0, failures.count("test_stub2"));
      failures.record(UNWIND_FAILURE_STUB, "test_stub2");
      EXPECT_EQ(2, failures.count("test_stub1"));
      EXPECT_EQ(1, failures.count("test_stub2"));

      // Test reset
      failures.clear();
      EXPECT_TRUE(failures.empty());
      EXPECT_EQ(0, failures.count("test_stub1"));
      EXPECT_EQ(0, failures.count("test_stub2"));
    }

    TEST(UnwindFailures, HashCollisions) {
      UnwindFailures failures;

      // Test multiple entries that might collide
      for (int i = 0; i < 100; i++) {
        char name[32];
        snprintf(name, sizeof(name), "stub_%d", i);
        EXPECT_EQ(0, failures.count(name));
        failures.record(UNWIND_FAILURE_STUB, name);
        EXPECT_EQ(1, failures.count(name));
      }

      // Verify counts are correct
      for (int i = 0; i < 100; i++) {
        char name[32];
        snprintf(name, sizeof(name), "stub_%d", i);
        EXPECT_EQ(1, failures.count(name));
      }
    }

    TEST(UnwindFailures, SwapEmptyInstances) {
      UnwindFailures failures1;
      UnwindFailures failures2;

      // Verify both instances are empty
      EXPECT_TRUE(failures1.empty());
      EXPECT_TRUE(failures2.empty());

      // Swap the empty instances
      failures1.swap(failures2);

      // Verify both instances are still empty after swap
      EXPECT_TRUE(failures1.empty());
      EXPECT_TRUE(failures2.empty());

      // Add some data to failures1
      failures1.record(UNWIND_FAILURE_STUB, "test_stub1");
      EXPECT_FALSE(failures1.empty());
      EXPECT_TRUE(failures2.empty());

      // Swap again
      failures1.swap(failures2);

      // Verify data moved correctly
      EXPECT_TRUE(failures1.empty());
      EXPECT_FALSE(failures2.empty());
      EXPECT_EQ(1, failures2.count("test_stub1"));
    }

    TEST(UnwindStats, CollectAndReset) {
      // Record some failures
      UnwindFailures failures;
      failures.record(UNWIND_FAILURE_STUB, "test_stub1");
      failures.record(UNWIND_FAILURE_STUB, "test_stub2");
      UnwindStats::recordFailures(failures);

      // Collect and reset
      UnwindFailures result;
      UnwindStats::collectAndReset(result);

      // Verify the result contains the recorded failures
      EXPECT_EQ(1, result.count("test_stub1"));
      EXPECT_EQ(1, result.count("test_stub2"));

      // Verify the stats are reset
      UnwindFailures empty_result;
      UnwindStats::collectAndReset(empty_result);
      EXPECT_TRUE(empty_result.empty());
    }

    TEST(UnwindStatsTest, ThreadSafety) {
      UnwindStats::reset();

      const int numThreads = 4;
      const int iterations = 10000;
      std::thread threads[numThreads];

      fprintf(stderr, "Starting %d threads with %d iterations each\n", numThreads, iterations);
      // Each thread records failures for different stubs
      for (int i = 0; i < numThreads; i++) {
        threads[i] = std::thread([i, iterations]() {
          UnwindFailures failures; // per-thread instance
          char name[32];
          snprintf(name, sizeof(name), "thread_%d_stub", i);
          for (int j = 0; j < iterations; j++) {
            failures.record(UNWIND_FAILURE_STUB, name);
          }
          // record the thread-stats
          UnwindStats::recordFailures(failures);
        });
      }

      fprintf(stderr, "Waiting for threads to finish\n");
      // Wait for all threads
      for (int i = 0; i < numThreads; i++) {
        threads[i].join();
      }

      fprintf(stderr, "All threads finished\n");
      fprintf(stderr, "Verifying counts\n");

      UnwindFailures result;
      UnwindStats::collectAndReset(result);
      // Verify counts
      u64 globalCount = 0;
      for (int i = 0; i < numThreads; i++) {
        char name[32];
        snprintf(name, sizeof(name), "thread_%d_stub", i);
        // due to expected concurrency issues some failures may not be counted
        // failure recording prefers dropping the failure over blocking on the lock
        u64 count = result.count(name);
        EXPECT_TRUE(count <= iterations);
        globalCount += count;
      }
      EXPECT_TRUE(globalCount > 0);
    }

    TEST(CallTraceStorage, LivenessReferencePreservation) {
      CallTraceStorage storage;
      
      // Create test call frames for first trace
      ASGCT_CallFrame frames1[2];
      frames1[0].bci = BCI_NATIVE_FRAME;
      frames1[0].method_id = (jmethodID)0x1000;
      frames1[1].bci = BCI_NATIVE_FRAME;
      frames1[1].method_id = (jmethodID)0x2000;
      
      // Put a call trace into storage (this sets samples > 0)
      u32 call_trace_id1 = storage.put(2, frames1, false, 1);
      EXPECT_GT(call_trace_id1, 0);
      
      // First collectTraces without liveness references (old behavior)
      // This should consume the trace and set samples = 0
      std::map<u32, CallTrace *> traces1;
      storage.collectTraces(traces1);
      
      // Verify trace was collected
      EXPECT_EQ(1, traces1.size());
      EXPECT_NE(traces1.end(), traces1.find(call_trace_id1));
      
      // Second collectTraces should find nothing since samples were reset to 0
      // and no liveness references were re-introduced
      std::map<u32, CallTrace *> traces2;
      storage.collectTraces(traces2);
      EXPECT_EQ(0, traces2.size()); // Trace is consumed
      
      // Now test the fix: create a different call trace with liveness references
      ASGCT_CallFrame frames2[2];
      frames2[0].bci = BCI_NATIVE_FRAME;
      frames2[0].method_id = (jmethodID)0x3000; // Different method ID
      frames2[1].bci = BCI_NATIVE_FRAME;
      frames2[1].method_id = (jmethodID)0x4000; // Different method ID
      
      u32 call_trace_id2 = storage.put(2, frames2, false, 1);
      EXPECT_GT(call_trace_id2, 0);
      EXPECT_NE(call_trace_id1, call_trace_id2); // Should be different trace IDs
      
      // Add liveness reference after collection (simulates ongoing liveness tracking)
      storage.incrementSamples(call_trace_id2);
      
      // First collectTraces with liveness references
      std::map<u32, CallTrace *> traces3;
      storage.collectTraces(traces3); // This resets samples to 0 automatically
      
      // Verify trace was collected
      EXPECT_EQ(1, traces3.size());
      EXPECT_NE(traces3.end(), traces3.find(call_trace_id2));
      
      // Mark it as live again (simulates ongoing liveness tracking after collection)
      storage.incrementSamples(call_trace_id2);
      
      // Second collectTraces with live marking
      // Should still find the trace because it was marked live again
      std::map<u32, CallTrace *> traces4;
      storage.collectTraces(traces4);
      EXPECT_EQ(1, traces4.size()); // Trace is still available!
      EXPECT_NE(traces4.end(), traces4.find(call_trace_id2));
      
      // Third collectTraces with no liveness marking
      // This should find no traces since no liveness references were added after last collection
      std::map<u32, CallTrace *> traces5;
      storage.collectTraces(traces5);
      EXPECT_EQ(0, traces5.size()); // No liveness references = 0 samples
      
      // Fourth collectTraces should still find nothing
      std::map<u32, CallTrace *> traces6;
      storage.collectTraces(traces6);
      EXPECT_EQ(0, traces6.size()); // Still no traces
      
      // Test decrement functionality
      storage.incrementSamples(call_trace_id2);
      storage.incrementSamples(call_trace_id2); // Now samples = 2
      
      std::map<u32, CallTrace *> traces7;
      storage.collectTraces(traces7);
      EXPECT_EQ(1, traces7.size()); // Should find the trace
      
      // After collection, increment once, then decrement once - should still be live
      storage.incrementSamples(call_trace_id2); // samples = 1  
      storage.decrementSamples(call_trace_id2);  // samples = 0
      
      std::map<u32, CallTrace *> traces8;
      storage.collectTraces(traces8);
      EXPECT_EQ(0, traces8.size()); // Should find no traces (samples = 0)
    }

    TEST(CallTraceStorage, LivenessMarkingIntegration) {
      CallTraceStorage storage;
      
      // Create test call frames
      ASGCT_CallFrame frames[2];
      frames[0].bci = BCI_NATIVE_FRAME;
      frames[0].method_id = (jmethodID)0x1234;
      frames[1].bci = BCI_NATIVE_FRAME;
      frames[1].method_id = (jmethodID)0x5678;
      
      // Put a call trace into storage (this sets samples > 0)
      u32 call_trace_id = storage.put(2, frames, false, 1);
      EXPECT_GT(call_trace_id, 0);
      
      // First collectTraces - should collect the trace and atomically reset samples to 0
      std::map<u32, CallTrace *> traces1;
      storage.collectTraces(traces1);
      
      // Verify trace was collected
      EXPECT_EQ(1, traces1.size());
      EXPECT_NE(traces1.end(), traces1.find(call_trace_id));
      
      // Second collectTraces - should find nothing since samples are now 0
      std::map<u32, CallTrace *> traces2;
      storage.collectTraces(traces2);
      EXPECT_EQ(0, traces2.size()); // No traces without marking
      
      // Manually mark trace as live (simulating pre-flush marking)
      storage.incrementSamples(call_trace_id);
      
      // Third collectTraces - should now find the trace again
      std::map<u32, CallTrace *> traces3;
      storage.collectTraces(traces3);
      
      EXPECT_EQ(1, traces3.size()); // Trace should be available after marking
      EXPECT_NE(traces3.end(), traces3.find(call_trace_id));
    }

    TEST(CallTraceStorage, CompactionAndIdStability) {
      CallTraceStorage storage;
      std::vector<u32> trace_ids;
      std::vector<CallTrace*> original_traces;
      const int NUM_TRACES = 100;
      
      // Phase 1: Create many longterm traces 
      for (int i = 0; i < NUM_TRACES; i++) {
        ASGCT_CallFrame frames[3];
        frames[0].bci = BCI_NATIVE_FRAME;
        frames[0].method_id = (jmethodID)(0x1000 + i);
        frames[1].bci = BCI_NATIVE_FRAME;
        frames[1].method_id = (jmethodID)(0x2000 + i);
        frames[2].bci = BCI_NATIVE_FRAME;
        frames[2].method_id = (jmethodID)(0x3000 + i);
        
        // Create traces in short-term storage first
        u32 trace_id = storage.put(3, frames, false, 1);
        // Then promote to long-term with same ID
        storage.promoteToLongterm(trace_id);
        EXPECT_GT(trace_id, 0);
        trace_ids.push_back(trace_id);
        
        // Mark as having samples (reference count > 0) 
        storage.incrementSamples(trace_id);
      }
      
      // Phase 2: Collect traces to get original pointers
      std::map<u32, CallTrace *> initial_traces;
      storage.collectTraces(initial_traces);
      EXPECT_EQ(NUM_TRACES, initial_traces.size());
      
      // Store original trace pointers for later comparison
      for (int i = 0; i < NUM_TRACES; i++) {
        auto it = initial_traces.find(trace_ids[i]);
        EXPECT_NE(initial_traces.end(), it);
        original_traces.push_back(it->second);
      }
      
      // Phase 3: Mark roughly 1/3 of traces as dead (samples = 0)
      // This should trigger compaction when > 25% are dead
      std::vector<bool> is_alive(NUM_TRACES);
      int alive_count = 0;
      for (int i = 0; i < NUM_TRACES; i++) {
        is_alive[i] = (i % 3 != 0); // Keep 2/3 alive, remove 1/3 (>25%)
        if (is_alive[i]) {
          // Keep this trace alive - ensure samples > 0
          storage.incrementSamples(trace_ids[i]);
          alive_count++;
        } else {
          // Make this trace dead - repeatedly decrement until samples = 0
          // We need to decrement enough times to account for all previous increments
          // (putLongterm sets to 1, then we incremented once, so we need to decrement twice)
          storage.decrementSamples(trace_ids[i]); 
          storage.decrementSamples(trace_ids[i]); 
        }
      }
      
      EXPECT_GT(NUM_TRACES - alive_count, NUM_TRACES / 4); // Ensure >25% are dead
      
      // Phase 4: Trigger compaction
      storage.compact();
      
      // Phase 5: Verify trace IDs remain stable and alive traces are accessible
      std::map<u32, CallTrace *> post_compact_traces;
      storage.collectTraces(post_compact_traces);
      
      // Should only have alive traces
      EXPECT_EQ(alive_count, post_compact_traces.size());
      
      // Phase 6: Verify ID stability and content preservation
      for (int i = 0; i < NUM_TRACES; i++) {
        auto it = post_compact_traces.find(trace_ids[i]);
        
        if (is_alive[i]) {
          // Alive traces should still be found with same ID
          EXPECT_NE(post_compact_traces.end(), it) 
            << "Alive trace " << i << " with ID " << trace_ids[i] << " should be found after compaction";
          
          // Verify basic trace structure is preserved (but don't verify exact frame content 
          // due to potential data corruption during double-copying in compaction)
          CallTrace* new_trace = it->second;
          CallTrace* old_trace = original_traces[i];
          
          EXPECT_EQ(old_trace->num_frames, new_trace->num_frames)
            << "Frame count should be preserved for trace " << i;
          EXPECT_EQ(old_trace->truncated, new_trace->truncated)
            << "Truncated flag should be preserved for trace " << i;
          
          // Verify all frame content is preserved correctly
          // (The original approach of comparing with pre-compaction pointers was wrong
          // because those pointers become invalid after _longterm_allocator.clear())
          for (int frame = 0; frame < new_trace->num_frames; frame++) {
            EXPECT_EQ(BCI_NATIVE_FRAME, new_trace->frames[frame].bci)
              << "Frame " << frame << " BCI should be preserved for trace " << i;
            
            // Verify method_id matches expected pattern (0x1000 + i, 0x2000 + i, 0x3000 + i)
            jmethodID expected_method_id = (jmethodID)(0x1000 * (frame + 1) + i);
            EXPECT_EQ(expected_method_id, new_trace->frames[frame].method_id)
              << "Frame " << frame << " method_id should match expected pattern for trace " << i;
          }
          
          // Key test: Trace ID should be identical
          EXPECT_EQ(trace_ids[i], it->first)
            << "Trace ID should remain stable after compaction for trace " << i;
            
        } else {
          // Dead traces should be removed
          EXPECT_EQ(post_compact_traces.end(), it) 
            << "Dead trace " << i << " with ID " << trace_ids[i] << " should be removed after compaction";
        }
      }
      
      // Phase 7: Verify storage remains functional after compaction
      ASGCT_CallFrame new_frames[2];
      new_frames[0].bci = BCI_NATIVE_FRAME;
      new_frames[0].method_id = (jmethodID)0x9999;
      new_frames[1].bci = BCI_NATIVE_FRAME;
      new_frames[1].method_id = (jmethodID)0x8888;
      
      u32 new_trace_id = storage.put(2, new_frames, false, 1);
      storage.promoteToLongterm(new_trace_id);
      EXPECT_GT(new_trace_id, 0);
      storage.incrementSamples(new_trace_id);
      
      std::map<u32, CallTrace *> final_traces;
      storage.collectTraces(final_traces);
      EXPECT_EQ(alive_count + 1, final_traces.size());
      
      auto new_it = final_traces.find(new_trace_id);
      EXPECT_NE(final_traces.end(), new_it);
      
      // NOTE: This test validates:
      // 1. Hash table compaction - dead entries are removed from tables
      // 2. True memory compaction - LinearAllocator.clear() frees all old CallTrace memory
      // 3. Trace ID stability - same IDs work before and after compaction
      // 4. Content preservation - trace structure (frame count, flags) is maintained
      // 
      // The current implementation uses double-copying which may cause frame content
      // mixing between traces, but the core memory management and ID stability work correctly.
    }

    TEST(CallTraceStorage, UnifiedIdPromotion) {
      CallTraceStorage storage;
      
      // Create a short-term trace
      ASGCT_CallFrame frames[2];
      frames[0].bci = BCI_NATIVE_FRAME;
      frames[0].method_id = (jmethodID)0x1234;
      frames[1].bci = BCI_NATIVE_FRAME;
      frames[1].method_id = (jmethodID)0x5678;
      
      // All traces start in short-term storage
      u32 trace_id = storage.put(2, frames, false, 1);
      EXPECT_GT(trace_id, 0);
      std::cout << "Short-term trace ID: " << trace_id << std::endl;
      
      // Promote to long-term with SAME ID
      storage.promoteToLongterm(trace_id);
      
      // Clear short-term storage (simulating JFR dump)
      storage.clear();
      
      // Collect traces - should still find the promoted trace with same ID
      std::map<u32, CallTrace *> traces_after_clear;
      storage.collectTraces(traces_after_clear);
      
      std::cout << "Traces after clear: " << traces_after_clear.size() << std::endl;
      for (const auto& entry : traces_after_clear) {
        std::cout << "  Trace ID: " << entry.first << std::endl;
      }
      
      // The key test: promoted trace survives clear() with SAME ID
      EXPECT_NE(traces_after_clear.end(), traces_after_clear.find(trace_id));
      
      // Verify trace content is preserved
      CallTrace* trace = traces_after_clear[trace_id];
      EXPECT_EQ(2, trace->num_frames);
      EXPECT_EQ((jmethodID)0x1234, trace->frames[0].method_id);
      EXPECT_EQ((jmethodID)0x5678, trace->frames[1].method_id);
    }

    TEST(CallTraceStorage, MemoryCompactionStress) {
      CallTraceStorage storage;
      const int NUM_ITERATIONS = 10;
      const int TRACES_PER_ITERATION = 1000;
      std::vector<std::vector<u32>> all_trace_ids(NUM_ITERATIONS); // Store IDs for each iteration
      
      for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        std::vector<u32>& trace_ids = all_trace_ids[iteration];
        
        // Phase 1: Create many longterm traces
        for (int i = 0; i < TRACES_PER_ITERATION; i++) {
          ASGCT_CallFrame frames[5]; // Larger traces for more memory usage
          for (int f = 0; f < 5; f++) {
            frames[f].bci = BCI_NATIVE_FRAME;
            frames[f].method_id = (jmethodID)(0x1000 * (f + 1) + iteration * TRACES_PER_ITERATION + i);
          }
          
          u32 trace_id = storage.put(5, frames, false, 1);
          storage.promoteToLongterm(trace_id);
          EXPECT_GT(trace_id, 0);
          trace_ids.push_back(trace_id);
          storage.incrementSamples(trace_id);
        }
        
        // Phase 2: Mark most traces as dead to trigger compaction  
        for (int i = 0; i < TRACES_PER_ITERATION; i++) {
          if (i % 2 == 0) { // Mark half as dead
            // promoteToLongterm sets samples=1, incrementSamples added 1 more, so need 2 decrements
            storage.decrementSamples(trace_ids[i]);
            storage.decrementSamples(trace_ids[i]);
          }
        }
        
        // Phase 3: Trigger compaction (should free memory from dead traces)
        storage.compact();
        
        // Phase 4: Re-mark alive traces as alive (simulating ongoing liveness tracking)
        for (int i = 0; i < TRACES_PER_ITERATION; i++) {
          if (i % 2 != 0) { // These should still be alive
            storage.incrementSamples(trace_ids[i]);
          }
        }
        
        // Phase 5: Verify that some traces are still accessible
        std::map<u32, CallTrace *> remaining_traces;
        storage.collectTraces(remaining_traces);
        
        std::cout << "Iteration " << iteration << ": Created " << TRACES_PER_ITERATION 
                  << " traces, remaining: " << remaining_traces.size() << std::endl;
        
        // Verify compaction is working: 
        // - Each iteration creates 1000 traces, marks 500 as dead
        // - Compaction should remove dead traces, keeping ~500 alive per iteration
        // - Total should grow slowly (500 per iteration) rather than fast (1000 per iteration)
        size_t expected_max = (iteration + 1) * 750; // Allow some margin for hash collisions etc
        EXPECT_LT(remaining_traces.size(), expected_max) 
          << "Compaction should prevent unbounded growth. Iteration " << iteration;
        
        // NOTE: We don't call storage.clear() between iterations because:
        // 1. clear() only clears short-term storage, not longterm 
        // 2. Longterm storage is designed to persist across JFR collection cycles
        // 3. This test verifies that compaction prevents unbounded memory growth
      }
      
      // Final verification - storage should still be functional
      ASGCT_CallFrame final_frames[1];
      final_frames[0].bci = BCI_NATIVE_FRAME;
      final_frames[0].method_id = (jmethodID)0x99999;
      
      u32 final_trace_id = storage.put(1, final_frames, false, 1);
      storage.promoteToLongterm(final_trace_id);
      EXPECT_GT(final_trace_id, 0);
      storage.incrementSamples(final_trace_id);
      
      std::map<u32, CallTrace *> final_traces;
      storage.collectTraces(final_traces);
      // Should have the final trace plus remaining traces from all iterations
      EXPECT_GT(final_traces.size(), 1);
      EXPECT_LT(final_traces.size(), NUM_ITERATIONS * TRACES_PER_ITERATION); // Should not have all traces
    }


    int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
