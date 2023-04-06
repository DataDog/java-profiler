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

class Counters {
public:
    #ifdef COUNTERS
        static volatile u64* _counters;
    #endif // COUNTERS
    enum Id {
        CONTEXT_STORAGE_BYTES,
        CONTEXT_STORAGE_PAGES,
        FIRST = CONTEXT_STORAGE_BYTES,
        LAST = CONTEXT_STORAGE_PAGES
    };
    static constexpr int size() {
        return (LAST + 1 - FIRST) * sizeof(u64) * 8;
    }
    static void increment(Counters::Id counter, u64 delta = 1) {
        #ifdef COUNTERS
        atomicInc(_counters[counter * 8], delta);
        #endif // COUNTERS
    }
    static void decrement(Counters::Id counter, u64 delta = 1) {
        #ifdef COUNTERS
        increment(counter, -delta);
        #endif // COUNTERS
    }
    static std::vector<const char*> describeCounters() {
        std::vector<const char*> names;
        names.push_back("context_storage:bytes");
        names.push_back("context_storage:pages");
        return names;
    }

};


#endif //JAVA_PROFILER_LIBRARY_COUNTERS_H
