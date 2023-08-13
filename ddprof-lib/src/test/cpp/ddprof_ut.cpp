    #include <gtest/gtest.h>

    #include "buffers.h"
    #include "context.h"
    #include "counters.h"
    #include "methodCache.h"
    #include "mutex.h"
    #include "os.h"
    #include "threadFilter.h"
    #include <vector>

    ssize_t callback(char* ptr, int len) {
        fprintf(stderr, "here\n");
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

    TEST(MethodInfoCache, testSanity) {
        MethodInfoCache cache1(0, true);
        MethodInfoCache cache2(10, false);

        ASSERT_TRUE(cache1.passThrough());
        ASSERT_FALSE(cache2.passThrough());
    }

    static size_t empty_cache_slot_size = sizeof(void*) + sizeof(u64);
    static int ptr_callback_cnt = 0;
    static void ptr_callback(void* ptr) {
        ptr_callback_cnt++;
    }

    TEST(MethodInfoCache, testEmptyCache) {
        MethodInfoCache cache(0, true);

        ASSERT_TRUE(cache.get(1)->isEmpty());
    }

    TEST(MethodInfoCache, testNewMethodInfo) {
        MethodInfoCache cache(10, false);


        ASSERT_FALSE(cache.passThrough());

        char class_name[] = "klass";
        char method_name[] = "method";
        char method_sig[] = "()V";
        int modifiers = 11;
        int line_number_table_size = 0;
        void* line_number_table = (void*) new char[5];
        bool is_entry = true;
        SharedLineNumberTableDeallocator deallocateLineNumberTable = ptr_callback;

        ptr_callback_cnt = 0;
        {
            // test the abstract method info instantiation
            // the cache will obey the 'cached' flag passed to the newMethodInfo function

            // make sure info objects will go out of scope so they do not prevent deleting the line number tables
            std::shared_ptr<AbstractMethodInfo> cmi_ptr = std::dynamic_pointer_cast<CachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true));
            std::shared_ptr<AbstractMethodInfo> nmi_ptr = std::dynamic_pointer_cast<UncachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, false));
            
            ASSERT_TRUE(cmi_ptr);
            ASSERT_TRUE(nmi_ptr);
            ASSERT_TRUE(cmi_ptr.get()->isCacheable());
            ASSERT_FALSE(nmi_ptr.get()->isCacheable());
        }

        ASSERT_EQ(ptr_callback_cnt, 2); // both created instances should have been released by now
    }

    TEST(MethodInfoCache, testNewMethodInfoPassThrough) {
        MethodInfoCache cache(0, true); // a pass-through cache must have either retention or threshold or both <0

        ASSERT_TRUE(cache.passThrough());

        char class_name[] = "klass";
        char method_name[] = "method";
        char method_sig[] = "()V";
        int modifiers = 11;
        int line_number_table_size = 0;
        void* line_number_table = (void*) new char[5];
        bool is_entry = true;
        SharedLineNumberTableDeallocator deallocateLineNumberTable = ptr_callback;

        ptr_callback_cnt = 0;
        {
            // test the abstract method info instantiation
            // the cache will return 'uncached' values regardless of the 'cached' flag passed to the newMethodInfo function

            // make sure info objects will go out of scope so they do not prevent deleting the line number tables
            std::shared_ptr<AbstractMethodInfo> cmi_ptr = std::dynamic_pointer_cast<UncachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true));
            std::shared_ptr<AbstractMethodInfo> nmi_ptr = std::dynamic_pointer_cast<UncachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, false));

            ASSERT_TRUE(cmi_ptr);
            ASSERT_TRUE(nmi_ptr);
            ASSERT_FALSE(cmi_ptr.get()->isCacheable());
            ASSERT_FALSE(nmi_ptr.get()->isCacheable());
        }

        ASSERT_EQ(ptr_callback_cnt, 2); // both created instances should have been released by now
    }

    static int cached_method_info_func_cnt = 0;
    static int uncached_method_info_func_cnt = 0;
    static std::shared_ptr<AbstractMethodInfo> cached_method_info_func_callback(u64 id, MethodInfoCache* cache, bool with_cache) {
        char class_name[] = "cached_klass";
        char method_name[] = "method";
        char method_sig[] = "()V";
        int modifiers = 11;
        int line_number_table_size = 0;
        void* line_number_table = (void*) new char[5];
        bool is_entry = true;
        SharedLineNumberTableDeallocator deallocateLineNumberTable = ptr_callback;

        cached_method_info_func_cnt++;

        return cache->newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true);
    }

    static std::shared_ptr<AbstractMethodInfo> cached_method_info_func_callback_1(u64 id, MethodInfoCache* cache, bool with_cache) {
        char class_name[] = "cached_klass_1";
        char method_name[] = "method_1";
        char method_sig[] = "()V";
        int modifiers = 11;
        int line_number_table_size = 0;
        void* line_number_table = (void*) new char[5];
        bool is_entry = true;
        SharedLineNumberTableDeallocator deallocateLineNumberTable = ptr_callback;

        cached_method_info_func_cnt++;

        return cache->newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true);
    }

    static std::shared_ptr<AbstractMethodInfo> uncached_method_info_func_callback(u64 id, MethodInfoCache* cache, bool with_cache) {
        char class_name[] = "uncached_klass";
        char method_name[] = "method";
        char method_sig[] = "()V";
        int modifiers = 11;
        int line_number_table_size = 0;
        void* line_number_table = (void*) new char[5];
        bool is_entry = true;
        SharedLineNumberTableDeallocator deallocateLineNumberTable = ptr_callback;

        uncached_method_info_func_cnt++;

        return cache->newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, false);
    }

    TEST(MethodInfoCachet, testCacheReuse) {
        MethodInfoCache cache(10, false);

//        Counters::set(JMETHODID_MAP_BYTES, 0);

        ptr_callback_cnt = 0;
        cached_method_info_func_cnt = 0;
        uncached_method_info_func_cnt = 0;

        // create a cached method info
        std::shared_ptr<AbstractMethodInfo> cmi_ptr_1 = cache.getOrAdd(1, cached_method_info_func_callback);
        ASSERT_EQ(cached_method_info_func_cnt, 1);
        ASSERT_TRUE(cmi_ptr_1);
        ASSERT_TRUE(cmi_ptr_1.get()->isCacheable());

        // second attempt should retrieve it from the cache
        std::shared_ptr<AbstractMethodInfo> cmi_ptr_2 = cache.getOrAdd(1, cached_method_info_func_callback);
        // the method info creation callback should not have been called
        ASSERT_EQ(cached_method_info_func_cnt, 1);
        ASSERT_TRUE(cmi_ptr_2);

        ASSERT_EQ(cmi_ptr_1.get(), cmi_ptr_2.get());

//        // cache is containing one element; at least the key and the value pointer is still there
//        ASSERT_GT(Counters::getCounter(JMETHODID_MAP_BYTES), 1 * empty_cache_slot_size);
    }

    TEST(MethodInfoCache, testCacheUncacheable) {
        MethodInfoCache cache(10, false);

        Counters::set(JMETHODID_MAP_BYTES, 0);

        ptr_callback_cnt = 0;
        cached_method_info_func_cnt = 0;
        uncached_method_info_func_cnt = 0;

        // create an uncached method info
        std::shared_ptr<AbstractMethodInfo> cmi_ptr_1 = cache.getOrAdd(1, uncached_method_info_func_callback);
        ASSERT_EQ(uncached_method_info_func_cnt, 1);
        ASSERT_TRUE(cmi_ptr_1);
        ASSERT_FALSE(cmi_ptr_1.get()->isCacheable());

        // second attempt should retrieve it from the cache
        std::shared_ptr<AbstractMethodInfo> cmi_ptr_2 = cache.getOrAdd(1, uncached_method_info_func_callback);
        // the method info creation callback should not have been called
        ASSERT_EQ(uncached_method_info_func_cnt, 2);
        ASSERT_TRUE(cmi_ptr_2);

        ASSERT_NE(cmi_ptr_1.get(), cmi_ptr_2.get());
        
        // nothing was added to the cache
        ASSERT_EQ(0, Counters::getCounter(JMETHODID_MAP_BYTES));
    }

    TEST(MethodInfoCache, testCacheRelease) {
        MethodInfoCache cache(10, false);

        std::shared_ptr<AbstractMethodInfo> cmi_ptr_1 = cache.getOrAdd(1, cached_method_info_func_callback);
        MethodInfoCacheStats stats1 = cache.stats(); // record the cache stats after the first item has been added

        std::shared_ptr<AbstractMethodInfo> cmi_ptr_2 = cache.getOrAdd(2, cached_method_info_func_callback_1);
        MethodInfoCacheStats stats2 = cache.stats();

        // make sure that adding two different items affects the string map and dictionary
        ASSERT_NE(stats1._string_count, stats2._string_count);
        ASSERT_NE(stats1._map_size, stats2._map_size);

        cache.pin(1);
        cache.newEpoch();
        MethodInfoCacheStats stats3 = cache.stats();

        ASSERT_EQ(cache.size(), 1);
        // Item 1 was marked sticky so the internal cache stats must correspond to the ones
        // captured when only item 1 was added to the cache
        ASSERT_EQ(stats1._string_count, stats3._string_count);
        ASSERT_EQ(stats1._string_bytes, stats3._string_bytes);
        ASSERT_EQ(stats1._map_size, stats3._map_size);
        ASSERT_EQ(stats1._map_bytes, stats3._map_bytes);
    }

    TEST(MethodInfoCache, testPinUnpinAcrossEpochs) {
        MethodInfoCache cache(10, false);

        std::shared_ptr<AbstractMethodInfo> cmi_ptr = cache.getOrAdd(1, cached_method_info_func_callback);
        // first, let's pin the first item in the current epoch
        cache.pin(1);
        // proceed to new epoch; the item is still pinned
        cache.newEpoch();
        // now unpin the item
        cache.unpin(1);
        // and increment the epoch to simulate items being pinned while the cache is being cleared at the end of the epoch
        u64 previous = cache.incrementEpoch();
        // pin the item in the next epoch
        cache.pin(1);
        // and release the cache for the previous epoch
        cache.release(previous);
        ASSERT_TRUE(cache.get(1).get()->isPinned());
    }

    TEST(MethodInfoCache, testCacheLimit) {
        MethodInfoCache cache(1, false); // only 1 element can be cached

        std::shared_ptr<AbstractMethodInfo> cmi_ptr1 = cache.getOrAdd(1, cached_method_info_func_callback);
        ASSERT_TRUE(cmi_ptr1.get()->isCacheable());

        std::shared_ptr<AbstractMethodInfo> cmi_ptr2 = cache.getOrAdd(2, cached_method_info_func_callback);
        ASSERT_FALSE(cmi_ptr2.get()->isCacheable());
        ASSERT_TRUE(cmi_ptr2.get()->isEmpty());
    }

    class TestCachedMethodInfo {
      private:
        AbstractMethodInfo* _delegate;

      public:
        TestCachedMethodInfo(AbstractMethodInfo* delegate) : _delegate(delegate) {}
        void pin(u64 epoch) {
            _delegate->pin(epoch);
        }

        void unpin(u64 epoch) {
            _delegate->unpin(epoch);
        }

        bool isPinned() {
            return _delegate->isPinned();
        }
    };

    TEST(CachedMethodInfo, testPinSimple) {
        MethodInfoCache cache(10, false);

        TestCachedMethodInfo mi(cache.getOrAdd(1, cached_method_info_func_callback).get());

        mi.pin(1);
        ASSERT_TRUE(mi.isPinned());
        mi.unpin(1);
        ASSERT_FALSE(mi.isPinned());
    }

    TEST(CachedMethodInfo, testPinUnpinOutOfOrder) {
        MethodInfoCache cache(10, false);

        TestCachedMethodInfo mi(static_cast<CachedMethodInfo*>(cache.getOrAdd(1, cached_method_info_func_callback).get()));

        mi.pin(2);
        ASSERT_TRUE(mi.isPinned());
        mi.unpin(1);
        ASSERT_TRUE(mi.isPinned());
        mi.unpin(3);
        ASSERT_FALSE(mi.isPinned());
    }

    int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
