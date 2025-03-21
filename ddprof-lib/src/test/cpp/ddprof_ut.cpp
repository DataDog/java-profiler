    #include <gtest/gtest.h>

    #include "asyncSampleMutex.h"
    #include "buffers.h"
    #include "context.h"
    #include "counters.h"
    #include "mutex.h"
    #include "os.h"
    #include "threadFilter.h"
    #include "threadInfo.h"
    #include "threadLocalData.h"
    #include "vmEntry.h"
    #include <vector>
    #include <algorithm>  // For std::sort

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

    TEST(ThreadFilter, testThreadFilterCollect) {
        ThreadFilter filter;
        filter.init("");
        ASSERT_TRUE(filter.enabled());
        EXPECT_EQ(0, filter.size());

        // Add some thread IDs that would map to different bit positions
        std::vector<int> test_tids = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        for (int tid : test_tids) {
            filter.add(tid);
            EXPECT_TRUE(filter.accept(tid));
        }
        ASSERT_EQ(test_tids.size(), filter.size());

        // Collect all thread IDs
        std::vector<int> collected_tids;
        filter.collect(collected_tids);
        
        // Verify size matches
        ASSERT_EQ(test_tids.size(), collected_tids.size());
        
        // Sort both vectors for comparison
        std::sort(test_tids.begin(), test_tids.end());
        std::sort(collected_tids.begin(), collected_tids.end());
        
        // Verify all thread IDs are present
        for (size_t i = 0; i < test_tids.size(); i++) {
            EXPECT_EQ(test_tids[i], collected_tids[i]) 
                << "Mismatch at index " << i 
                << ": expected " << test_tids[i] 
                << ", got " << collected_tids[i];
        }

        // Test with a larger range of thread IDs
        filter.clear();
        test_tids.clear();
        for (int i = 0; i < 100; i++) {
            int tid = i * 64 + 1;  // Use IDs that would map to different words
            test_tids.push_back(tid);
            filter.add(tid);
            EXPECT_TRUE(filter.accept(tid));
        }
        ASSERT_EQ(test_tids.size(), filter.size());

        collected_tids.clear();
        filter.collect(collected_tids);
        
        ASSERT_EQ(test_tids.size(), collected_tids.size());
        std::sort(test_tids.begin(), test_tids.end());
        std::sort(collected_tids.begin(), collected_tids.end());
        
        for (size_t i = 0; i < test_tids.size(); i++) {
            EXPECT_EQ(test_tids[i], collected_tids[i]) 
                << "Mismatch at index " << i 
                << ": expected " << test_tids[i] 
                << ", got " << collected_tids[i];
        }
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

    int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
