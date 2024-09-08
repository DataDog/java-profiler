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

#include "context.h"
#include "counters.h"
#include "os.h"
#include <cstring>

int Contexts::_max_pages = Contexts::getMaxPages();
Context **Contexts::_pages = new Context *[_max_pages]();

static Context DD_EMPTY_CONTEXT = {};

Context &Contexts::get(int tid) {
  int pageIndex = tid >> DD_CONTEXT_PAGE_SHIFT;
  // extreme edge case: pageIndex >= _max_pages if pid_max was increased during
  // the process's runtime
  if (pageIndex < _max_pages) {
    Context *page = _pages[pageIndex];
    if (page != NULL) {
      Context &context = page[tid & DD_CONTEXT_PAGE_MASK];
      if ((context.spanId ^ context.rootSpanId) == context.checksum) {
        return context;
      }
      Counters::increment(CounterId::CONTEXT_CHECKSUM_REJECT_GETS);
    } else {
      Counters::increment(CounterId::CONTEXT_NULL_PAGE_GETS);
    }
  } else {
    Counters::increment(CounterId::CONTEXT_BOUNDS_MISS_GETS);
  }
  return empty();
}

Context &Contexts::empty() { return DD_EMPTY_CONTEXT; }

void Contexts::initialize(int pageIndex) {
  if (pageIndex >= _max_pages) {
    Counters::increment(CounterId::CONTEXT_BOUNDS_MISS_INITS);
    // extreme edge case: pageIndex >= _max_pages if pid_max was increased
    // during the process's runtime
    return;
  }
  if (__atomic_load_n(&_pages[pageIndex], __ATOMIC_ACQUIRE) == NULL) {
    u32 capacity = DD_CONTEXT_PAGE_SIZE * sizeof(Context);
    Context *page = (Context *)aligned_alloc(sizeof(Context), capacity);
    // need to zero the storage because there is no aligned_calloc
    memset(page, 0, capacity);
    if (!__sync_bool_compare_and_swap(&_pages[pageIndex], NULL, page)) {
      free(page);
    } else {
      Counters::increment(CONTEXT_STORAGE_BYTES, capacity);
      Counters::increment(CONTEXT_STORAGE_PAGES);
    }
  }
}

void Contexts::reset() {
  for (int i = 0; i < _max_pages; i++) {
    Context *page =
        (Context *)__atomic_exchange_n(&_pages[i], NULL, __ATOMIC_SEQ_CST);
    free(page);
  }
}

ContextPage Contexts::getPage(int tid) {
  int pageIndex = tid >> DD_CONTEXT_PAGE_SHIFT;
  initialize(pageIndex);
  return {.capacity = DD_CONTEXT_PAGE_SIZE * sizeof(Context),
          .storage = _pages[pageIndex]};
}

// The number of pages that can cover all allowed thread IDs
int Contexts::getMaxPages(int maxTid) {
  // Max thread id is 0-based but exclusive - eg. value of 1024 will mean that
  // max 1024 will be ever present. The following formula will 'round up' the
  // number of pages necessary to hold the given number of threads.

  //! the next sequence of computation and static cast to int needs to be split
  //! into two statements
  //  - otherwise the gtest will crash and burn while linking
  long ret = ((long)maxTid + DD_CONTEXT_PAGE_SIZE - 1) / DD_CONTEXT_PAGE_SIZE;
  int maxPages = (int)ret;
  // extreme edge case: in one reported issue, pid_max has been known to be
  // increased from a very conservative value at runtime. In case this has
  // happened, we will reserve some space for surplus pages on a best effort
  // basis. If this surplus is insufficient for the application, samples from
  // some threads will not have context associated with them.
  return maxPages < 128 ? 128 : maxPages;
}
