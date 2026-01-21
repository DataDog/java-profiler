/*
 * Copyright 2021, 2022 Datadog, Inc
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

#ifndef _CONTEXT_H
#define _CONTEXT_H

#include "arch_dd.h"
#include "arguments.h"
#include "common.h"
#include "os.h"
#include "vmEntry.h"

static const u32 DD_TAGS_CAPACITY = 10;

typedef struct {
  u32 value;
} Tag;

class alignas(DEFAULT_CACHE_LINE_SIZE) Context {
public:
  volatile u64 spanId;
  volatile u64 rootSpanId;
  volatile u64 checksum;
  Tag tags[DD_TAGS_CAPACITY];

  Tag get_tag(int i) { return tags[i]; }
};

static Context DD_EMPTY_CONTEXT = {};

class Contexts {

public:
  static Context& initializeContextTls();
  static Context& get();

  static u64 checksum(u64 spanId, u64 rootSpanId) {
    u64 swappedRootSpanId = ((rootSpanId & 0xFFFFFFFFULL) << 32) | (rootSpanId >> 32);
    u64 computed = (spanId * KNUTH_MULTIPLICATIVE_CONSTANT) ^ (swappedRootSpanId * KNUTH_MULTIPLICATIVE_CONSTANT);
    return computed == 0 ? 0xffffffffffffffffull : computed;
  }
};

DLLEXPORT extern thread_local Context context_tls_v1;

#endif /* _CONTEXT_H */
