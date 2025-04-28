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
#include "os.h"

static const u32 DD_TAGS_CAPACITY = 10;

typedef struct {
  u32 value;
} Tag;

class Context {
public:
  u64 spanId;
  u64 rootSpanId;
  u64 checksum;
  Tag tags[DD_TAGS_CAPACITY];

  Tag get_tag(int i) { return tags[i]; }
};

// must be kept in sync with PAGE_SIZE in JavaProfiler.java
const int DD_CONTEXT_PAGE_SIZE = 1024;
const int DD_CONTEXT_PAGE_MASK = DD_CONTEXT_PAGE_SIZE - 1;
const int DD_CONTEXT_PAGE_SHIFT = __builtin_popcount(DD_CONTEXT_PAGE_MASK);

typedef struct {
  const int capacity;
  const Context *storage;
} ContextPage;

class Contexts {

private:
  static int _max_pages;
  static Context **_pages;
  static bool initialize(int pageIndex);

public:
  // get must not allocate
  static Context &get(int tid);
  static Context &empty();
  // not to be called except to share with Java callers as a DirectByteBuffer
  static ContextPage getPage(int tid);
  static int getMaxPages(int maxTid = OS::getMaxThreadId());

  // this *MUST* be called only when the profiler is completely stopped
  static void reset();
};

#endif /* _CONTEXT_H */
