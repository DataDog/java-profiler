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
        MethodInfoCache cache1(-1, -1);
        MethodInfoCache cache2(0, 0);
        MethodInfoCache cache3(1, 1);

        ASSERT_TRUE(cache1.passThrough());
        ASSERT_FALSE(cache2.passThrough());
        ASSERT_FALSE(cache3.passThrough());
    }

    static size_t empty_cache_slot_size = sizeof(void*) + sizeof(u64);
    static int ptr_callback_cnt = 0;
    static void ptr_callback(void* ptr) {
        ptr_callback_cnt++;
    }

    TEST(MethodInfoCache, testEmptyCache) {
        MethodInfoCache cache(10, 2);

        ASSERT_TRUE(cache.get(1)->empty());
    }

    TEST(MethodInfoCache, testNewMethodInfo) {
        MethodInfoCache cache(0, 0); // a non pass-through cache must have either retention or threshold or both >=0


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
        MethodInfoCache cache(-1, -1); // a pass-through cache must have either retention or threshold or both <0

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

    TEST(MethodInfoCache, testCacheRetention) {
        MethodInfoCache cache(0, 0);

        Counters::set(JMETHODID_MAP_BYTES, 0);

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
            // make sure cmi will go out of scope so it does not prevent deleting the line number table
            std::shared_ptr<CachedMethodInfo> cmi_ptr = std::static_pointer_cast<CachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true));

            if (!cache.add(1, cmi_ptr)) {
                FAIL();
            }

            CachedMethodInfo cmi = *cmi_ptr.get();

            AbstractMethodInfo* cached = cache.get(1).get();
            ASSERT_NE(nullptr, cached);
            ASSERT_FALSE(cached->empty());

            ASSERT_EQ(cmi.className(), cached->className());
            ASSERT_EQ(cmi.methodName(), cached->methodName());
            ASSERT_EQ(cmi.methodSignature(), cached->methodSignature());
        }
        // method info is still cached - the line number table must not have been deallocated yet
        ASSERT_EQ(0, ptr_callback_cnt);

        // bump to epoch 1
        cache.incEpoch();

        // with the threshold == 0 and retention == 0 the cached entry should have been removed
        ASSERT_EQ(cache.get(1), nullptr);
        // the line number table should have been deallocated as well
        ASSERT_EQ(1, ptr_callback_cnt);

        // cache should be completely empty at this point; the key and the value pointer is still there, though
        ASSERT_EQ(1 * empty_cache_slot_size, Counters::getCounter(JMETHODID_MAP_BYTES));
    }

    TEST(MethodInfoCache, testCacheRetention2) {
        MethodInfoCache cache(0, 2);
        
        Counters::set(JMETHODID_MAP_BYTES, 0);

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
            // make sure cmi will go out of scope so it does not prevent deleting the line number table
            std::shared_ptr<CachedMethodInfo> cmi_ptr = std::static_pointer_cast<CachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true));
            cache.add(1, cmi_ptr);
        }

        // method info is still cached - the line number table must not have been deallocated yet
        ASSERT_EQ(0, ptr_callback_cnt);

        // bump to epoch 1
        cache.incEpoch();

        // epoch diff = 1, retention == 2; entry should still be there
        ASSERT_FALSE(cache.get(1, false)->empty());

        // bump to epoch 2
        cache.incEpoch();
        // epoch diff = 2, retention == 2; entry should still be there
        ASSERT_FALSE(cache.get(1, false)->empty());

        // bump to epoch 3
        cache.incEpoch();
        // epoch diff = 3, retention == 2; entry should be removed
        ASSERT_EQ(cache.get(1, false), nullptr);

        // the line number table should have been deallocated as well
        ASSERT_EQ(1, ptr_callback_cnt);

        // cache should be completely empty at this point; the key and the value pointer is still there, though
        ASSERT_EQ(1 * empty_cache_slot_size, Counters::getCounter(JMETHODID_MAP_BYTES));
    }

    TEST(MethodInfoCache, testCacheThreshold) {
        MethodInfoCache cache(1, 0);

        Counters::set(JMETHODID_MAP_BYTES, 0);

        char class_name[] = "klass";
        char method_name[] = "method";
        char method_sig[] = "()V";
        int modifiers = 11;
        int line_number_table_size = 0;
        void* line_number_table = (void*) new char[5];
        bool is_entry = true;
        SharedLineNumberTableDeallocator deallocateLineNumberTable = ptr_callback;

        u64 id1 = 1;
        u64 id2 = 2;
        ptr_callback_cnt = 0;
        {
            // make sure cmi will go out of scope so it does not prevent deleting the line number table
            std::shared_ptr<CachedMethodInfo> cmi_ptr = std::static_pointer_cast<CachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true));
            if (!cache.add(id1, cmi_ptr)) {
                FAIL();
            }

            CachedMethodInfo cmi = *cmi_ptr.get();

            AbstractMethodInfo* cached = cache.get(id1).get();
            ASSERT_NE(cached, nullptr);

            ASSERT_EQ(cmi.className(), cached->className());
            ASSERT_EQ(cmi.methodName(), cached->methodName());
            ASSERT_EQ(cmi.methodSignature(), cached->methodSignature());
        }
        AbstractMethodInfo* cached = cache.get(id1).get();
        ASSERT_FALSE(cached->empty());

        // method info is still cached - the line number table must not have been deallocated yet
        ASSERT_EQ(ptr_callback_cnt, 0);

        // bump to epoch 1
        cache.incEpoch();

        // with the threshold == 1 and retention == 0 the cached entry should still be there
        ASSERT_FALSE(cache.get(id1)->empty());

        // the line number table should not have been deallocated as well
        ASSERT_EQ(ptr_callback_cnt, 0);

        {
            // add second method info
            // make sure cmi will go out of scope so it does not prevent deleting the line number table
            std::shared_ptr<CachedMethodInfo> cmi_ptr = std::static_pointer_cast<CachedMethodInfo>(cache.newMethodInfo(class_name, method_name, method_sig, modifiers, line_number_table_size, line_number_table, deallocateLineNumberTable, true));
            if (!cache.add(id2, cmi_ptr)) {
                FAIL();
            }

            CachedMethodInfo cmi = *cmi_ptr.get();

            AbstractMethodInfo* cached = cache.get(id2).get();
            ASSERT_FALSE(cached->empty());

            ASSERT_EQ(cmi.className(), cached->className());
            ASSERT_EQ(cmi.methodName(), cached->methodName());
            ASSERT_EQ(cmi.methodSignature(), cached->methodSignature());
        }

        // bump to epoch 2
        cache.incEpoch();

        // the threshold has been crossed; the cache should have been cleaned up
        ASSERT_EQ(cache.get(id1), nullptr);
        ASSERT_EQ(cache.get(id2), nullptr);
        ASSERT_EQ(ptr_callback_cnt, 2);
        
        // cache should be completely empty at this point; the key and the value pointer is still there, though
        ASSERT_EQ(2 * empty_cache_slot_size, Counters::getCounter(JMETHODID_MAP_BYTES));
    }


    static int cached_method_info_func_cnt = 0;
    static int uncached_method_info_func_cnt = 0;
    static std::shared_ptr<AbstractMethodInfo> cached_method_info_func_callback(u64 id, MethodInfoCache* cache) {
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

    static std::shared_ptr<AbstractMethodInfo> uncached_method_info_func_callback(u64 id, MethodInfoCache* cache) {
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

    TEST(MethodInfoCache, testCacheReuse) {
        MethodInfoCache cache(0, 0);

        Counters::set(JMETHODID_MAP_BYTES, 0);

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

        // cache is containing one element; at least the key and the value pointer is still there
        ASSERT_GT(Counters::getCounter(JMETHODID_MAP_BYTES), 1 * empty_cache_slot_size);
    }

    TEST(MethodInfoCache, testCacheReuseWithExpiration) {
        MethodInfoCache cache(0, 0);

        Counters::set(JMETHODID_MAP_BYTES, 0);

        ptr_callback_cnt = 0;
        cached_method_info_func_cnt = 0;
        uncached_method_info_func_cnt = 0;

        {
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
        }


        cache.incEpoch(); // force eviction
        std::shared_ptr<AbstractMethodInfo> cmi_ptr = cache.getOrAdd(1, cached_method_info_func_callback);
        // the evicted entry should not be re-resolved and re-added
        ASSERT_EQ(cached_method_info_func_cnt, 1);
        ASSERT_FALSE(cmi_ptr);

        // cache should be completely empty at this point; the key and the value pointer is still there, though
        ASSERT_EQ(1 * empty_cache_slot_size, Counters::getCounter(JMETHODID_MAP_BYTES));
    }

    TEST(MethodInfoCache, testCacheUncacheable) {
        MethodInfoCache cache(0, 0);

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

    int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
