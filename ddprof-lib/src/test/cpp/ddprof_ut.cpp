    #include <gtest/gtest.h>

    #include "asyncSampleMutex.h"
    #include "buffers.h"
    #include "context.h"
    #include "counters.h"
    #include "mutex.h"
    #include "os.h"
    #include "unwindStats.h"
    #include "threadFilter.h"
    #include "threadInfo.h"
    #include "threadLocalData.h"
    #include "vmEntry.h"
    #include <map>
    #include <thread>
    #include <vector>

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
        for (int tid = 0; tid < maxTid - step - 1; tid += step, size++) {
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

    int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
