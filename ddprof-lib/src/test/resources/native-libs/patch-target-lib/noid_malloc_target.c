/* Copyright 2026, Datadog, Inc. */
#include <stdlib.h>

// Equal-length import names keep the ELF layout unchanged without a build-id.
void* noid_malloc_entry(size_t size) {
    return IMPORT(size);
}
