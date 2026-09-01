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

#include "arch.h"
#include <cassert>

static const u32 DD_TAGS_CAPACITY = 10;

typedef struct {
  u32 value;
} Tag;

class alignas(DEFAULT_CACHE_LINE_SIZE) Context {
public:
  u64 spanId;
  u64 rootSpanId;
private:
  Tag tags[DD_TAGS_CAPACITY];
public:
  u32 getTag(int i) {
    assert(i >= 0 && (u32)i < DD_TAGS_CAPACITY);
    return i >= 0 && (u32)i < DD_TAGS_CAPACITY ? tags[i].value : 0;
  }
  
  void setTag(int i, u32 value) {
    assert(i >= 0 && (u32)i < DD_TAGS_CAPACITY);
    if (i >= 0 && (u32)i < DD_TAGS_CAPACITY) {
      tags[i].value = value;
    }
  }
};

#endif /* _CONTEXT_H */
