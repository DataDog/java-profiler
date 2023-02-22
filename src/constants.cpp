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

#include "constants.h"
#include "arch.h"

char*** Constants::_pages = new char**[DD_MAX_CONSTANTS_PAGES]();

void Constants::initialize(int pageIndex) {
    if (__atomic_load_n(&_pages[pageIndex], __ATOMIC_ACQUIRE) == NULL) {
        u32 capacity = DD_CONSTANTS_PAGE_SIZE * sizeof(char*);
        char** page = (char**) calloc(sizeof(char*), capacity);
        if (!__sync_bool_compare_and_swap(&_pages[pageIndex], NULL, page)) {
            free(page);
        }
    }
}

static inline char* nullTerminatedCopy(const char* key, size_t length) {
    char* result = (char*)malloc(length + 1);
    memcpy(result, key, length);
    result[length] = 0;
    return result;
}

void Constants::set(const char* symbol, size_t length, u32 encoding) {
    // encoding 0 <=> NULL
    if (encoding > 0) {
        int pageIndex = encoding / DD_CONSTANTS_PAGE_SIZE;
        if (pageIndex < DD_MAX_CONSTANTS_PAGES) {
            initialize(pageIndex);
            char *toInsert = nullTerminatedCopy(symbol, length);
            _pages[pageIndex][encoding % DD_CONSTANTS_PAGE_SIZE] = toInsert;
        }
    }
}
