/*
 * Copyright 2023 Datadog, Inc
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
#ifndef JAVA_PROFILER_LIBRARY_COUNTERS_H
#define JAVA_PROFILER_LIBRARY_COUNTERS_H

#include "arch.h"
#include <vector>

#define DD_COUNTER_TABLE(X) \
    X(DICTIONARY_BYTES, "dictionary:bytes") \
    X(DICTIONARY_CLASSES_BYTES, "dictionary:classes:bytes") \
    X(DICTIONARY_SYMBOLS_BYTES, "dictionary:symbols:bytes") \
    X(DICTIONARY_ENDPOINTS_BYTES, "dictionary:endpoints:bytes") \
    X(DICTIONARY_CONTEXT_BYTES, "dictionary:context:bytes") \
    X(DICTIONARY_PAGES, "dictionary:pages") \
    X(DICTIONARY_CLASSES_PAGES, "dictionary:classes:pages") \
    X(DICTIONARY_SYMBOLS_PAGES, "dictionary:symbols:pages") \
    X(DICTIONARY_ENDPOINTS_PAGES, "dictionary:endpoints:pages") \
    X(DICTIONARY_CONTEXT_PAGES, "dictionary:context:pages") \
    X(DICTIONARY_KEYS, "dictionary:keys") \
    X(DICTIONARY_CLASSES_KEYS, "dictionary:classes:keys") \
    X(DICTIONARY_SYMBOLS_KEYS, "dictionary:symbols:keys") \
    X(DICTIONARY_ENDPOINTS_KEYS, "dictionary:endpoints:keys") \
    X(DICTIONARY_CONTEXT_KEYS, "dictionary:context:keys") \
    X(DICTIONARY_KEYS_BYTES, "dictionary:keys:bytes") \
    X(DICTIONARY_CLASSES_KEYS_BYTES, "dictionary:classes:keys:bytes") \
    X(DICTIONARY_SYMBOLS_KEYS_BYTES, "dictionary:symbols:keys:bytes") \
    X(DICTIONARY_ENDPOINTS_KEYS_BYTES, "dictionary:endpoints:keys:bytes") \
    X(DICTIONARY_CONTEXT_KEYS_BYTES, "dictionary:context:keys:bytes") \
    X(CONTEXT_STORAGE_BYTES, "context_storage:bytes") \
    X(CONTEXT_STORAGE_PAGES, "context_storage:pages")       \
    X(CALLTRACE_STORAGE_BYTES, "calltrace_storage:bytes") \
    X(CALLTRACE_STORAGE_TRACES, "calltrace_storage:traces") \
    X(LINEAR_ALLOCATOR_BYTES, "linear_allocator:bytes") \
    X(LINEAR_ALLOCATOR_CHUNKS, "linear_allocator:chunks")

#define X_ENUM(a, b) a,
typedef enum CounterId {
    DD_COUNTER_TABLE(X_ENUM) DD_NUM_COUNTERS
} CounterId;
#undef X_ENUM

class Counters {
public:
    #ifdef COUNTERS
        static volatile u64* _counters;
    #endif // COUNTERS

    static constexpr int size() {
        return DD_NUM_COUNTERS * sizeof(u64) * 8;
    }

    static void increment(CounterId counter, u64 delta = 1, int offset = 0) {
        #ifdef COUNTERS
        atomicInc(_counters[(static_cast<int>(counter) + offset) * sizeof(u64)], delta);
        #endif // COUNTERS
    }

    static void decrement(CounterId counter, u64 delta = 1, int offset = 0) {
        #ifdef COUNTERS
        increment(counter, -delta, offset);
        #endif // COUNTERS
    }

    static std::vector<const char*> describeCounters() {
        #ifdef COUNTERS
        #define X_NAME(a, b) b,
        return {
            DD_COUNTER_TABLE(X_NAME)
        };
        #undef X_NAME
        #else
        return {};
        #endif // COUNTERS
    }

};


#endif //JAVA_PROFILER_LIBRARY_COUNTERS_H
