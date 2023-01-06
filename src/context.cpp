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
#include "vmEntry.h"
#include "os.h"

Context** Contexts::_pages = new Context *[Contexts::getMaxPages()]();

const ContextSnapshot Contexts::get(int tid) {
    int pageIndex = tid >> DD_CONTEXT_PAGE_SHIFT;
    Context* page = _pages[pageIndex];
    if (page != NULL) {
        Context& context = page[tid & DD_CONTEXT_PAGE_MASK];
        if ((context.spanId ^ context.rootSpanId) == context.checksum && context.spanId != 0) {
            return { .spanId = context.spanId, .rootSpanId = context.rootSpanId, .parallelism = context.parallelism };
        }
    }
    return { .spanId = 0, .rootSpanId = 0, .parallelism = 1 };
}

void Contexts::initialize(int pageIndex) {
    if (__atomic_load_n(&_pages[pageIndex], __ATOMIC_ACQUIRE) == NULL) {
        u32 capacity = DD_CONTEXT_PAGE_SIZE * sizeof(Context);
        Context *page = (Context*) aligned_alloc(sizeof(Context), capacity);
        // need to zero the storage because there is no aligned_calloc
        memset(page, 0, capacity);
        if (!__sync_bool_compare_and_swap(&_pages[pageIndex], NULL, page)) {
            free(page);
        } 
    }
}

ContextPage Contexts::getPage(int tid) {
    int pageIndex = tid >> DD_CONTEXT_PAGE_SHIFT;
    initialize(pageIndex);
    return {.capacity = DD_CONTEXT_PAGE_SIZE * sizeof(Context), .storage = _pages[pageIndex]};
}

int Contexts::getMaxPages() {
    return OS::getMaxThreadId() / DD_CONTEXT_PAGE_SIZE;
}
