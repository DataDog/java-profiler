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
#include "counters.h"
#include <cstring>
#include <stdlib.h>

u64* Counters::init() {
    u32 alignment = sizeof(u64) * 8;
    u64* counters = (u64*) aligned_alloc(alignment, DD_NUM_COUNTERS * alignment);
    memset(counters, 0, DD_NUM_COUNTERS * alignment);
    return counters;
}

#ifdef COUNTERS
volatile u64* Counters::_counters = Counters::init();
#endif // COUNTERS
