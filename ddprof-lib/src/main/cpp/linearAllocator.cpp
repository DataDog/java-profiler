/*
 * Copyright 2020 Andrei Pangin
 * Copyright 2026, Datadog, Inc
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

#include "linearAllocator.h"
#include "counters.h"
#include "os_dd.h"
#include "common.h"
#include <stdio.h>

// Enable ASan memory poisoning for better use-after-free detection
#ifdef __has_feature
  #if __has_feature(address_sanitizer)
    #define ASAN_ENABLED 1
  #endif
#endif

#ifdef __SANITIZE_ADDRESS__
  #define ASAN_ENABLED 1
#endif

#ifdef ASAN_ENABLED
  #include <sanitizer/asan_interface.h>
#endif

LinearAllocator::LinearAllocator(size_t chunk_size) {
  _chunk_size = chunk_size;
  _reserve = _tail = allocateChunk(NULL);
}

LinearAllocator::~LinearAllocator() {
  clear();
  freeChunk(_tail);
}

void LinearAllocator::clear() {
  if (_reserve->prev == _tail) {
    freeChunk(_reserve);
  }

  // ASAN POISONING: Mark all allocated memory as poisoned BEFORE freeing chunks
  // This catches use-after-free even when memory isn't munmap'd (kept in _tail)
  #ifdef ASAN_ENABLED
  int chunk_count = 0;
  size_t total_poisoned = 0;
  for (Chunk *chunk = _tail; chunk != NULL; chunk = chunk->prev) {
    // Poison from the start of usable data to the current offset
    size_t used_size = chunk->offs - sizeof(Chunk);
    if (used_size > 0) {
      void* data_start = (char*)chunk + sizeof(Chunk);
      ASAN_POISON_MEMORY_REGION(data_start, used_size);
      chunk_count++;
      total_poisoned += used_size;
    }
  }
  if (chunk_count > 0) {
    TEST_LOG("[LinearAllocator::clear] ASan poisoned %d chunks, %zu bytes total", chunk_count, total_poisoned);
  }
  #endif

  while (_tail->prev != NULL) {
    Chunk *current = _tail;
    _tail = _tail->prev;
    freeChunk(current);
  }
  _reserve = _tail;
  _tail->offs = sizeof(Chunk);

  // DON'T UNPOISON HERE - let alloc() do it on-demand!
  // This ensures ASan can catch use-after-free bugs when code accesses
  // memory that was cleared but not yet reallocated.
}

ChunkList LinearAllocator::detachChunks() {
  // Capture current state before detaching
  ChunkList result(_tail, _chunk_size);

  // Handle reserve chunk: if it's ahead of tail, it needs special handling
  if (_reserve->prev == _tail) {
    // Reserve is a separate chunk ahead of tail - it becomes part of detached list
    // We need to include it in the chain by making it the new head
    result.head = _reserve;
  }

  // Allocate a fresh chunk for new allocations
  Chunk* fresh = allocateChunk(NULL);
  if (fresh != NULL) {
    _tail = fresh;
    _reserve = fresh;
  } else {
    // CRITICAL FIX: Allocation failed, but we MUST still detach to prevent double-free.
    // Leave the allocator in an unusable state (nullptr) rather than keeping old chunks
    // attached. This is safer than silently returning empty while chunks remain attached.
    // The allocator will need fresh allocation before it can be used again.
    _tail = nullptr;
    _reserve = nullptr;
    // Note: We still return the detached chunks in result, which will be freed by caller
  }

  return result;
}

void LinearAllocator::freeChunks(ChunkList& chunks) {
  if (chunks.head == nullptr || chunks.chunk_size == 0) {
    return;
  }

  // Walk the chain and free each chunk
  Chunk* current = chunks.head;
  while (current != nullptr) {
    Chunk* prev = current->prev;
    OS::safeFree(current, chunks.chunk_size);
    Counters::decrement(LINEAR_ALLOCATOR_BYTES, chunks.chunk_size);
    Counters::decrement(LINEAR_ALLOCATOR_CHUNKS);
    current = prev;
  }

  // Mark as freed to prevent double-free
  chunks.head = nullptr;
  chunks.chunk_size = 0;
}

void *LinearAllocator::alloc(size_t size) {
  Chunk *chunk = __atomic_load_n(&_tail, __ATOMIC_ACQUIRE);

  // CRITICAL FIX: After detachChunks() fails, _tail may be nullptr.
  // We must handle this gracefully to prevent crash.
  if (chunk == nullptr) {
    return nullptr;
  }

  do {
    // Fast path: bump a pointer with CAS
    for (size_t offs = __atomic_load_n(&chunk->offs, __ATOMIC_ACQUIRE);
         offs + size <= _chunk_size;
         offs = __atomic_load_n(&chunk->offs, __ATOMIC_ACQUIRE)) {
      if (__sync_bool_compare_and_swap(&chunk->offs, offs, offs + size)) {
        void* allocated_ptr = (char *)chunk + offs;

        // ASAN UNPOISONING: Unpoison ONLY the allocated region on-demand
        // This allows ASan to detect use-after-free of memory that was cleared
        // but not yet reallocated
        #ifdef ASAN_ENABLED
        ASAN_UNPOISON_MEMORY_REGION(allocated_ptr, size);
        #endif

        if (_chunk_size / 2 - offs < size) {
          // Stepped over a middle of the chunk - it's time to prepare a new one
          reserveChunk(chunk);
        }
        return allocated_ptr;
      }
    }
  } while ((chunk = getNextChunk(chunk)) != NULL);

  return NULL;
}

Chunk *LinearAllocator::allocateChunk(Chunk *current) {
  Chunk *chunk = (Chunk *)OS::safeAlloc(_chunk_size);
  if (chunk != NULL) {
    chunk->prev = current;
    chunk->offs = sizeof(Chunk);

    // ASAN UNPOISONING: New chunks from mmap are clean, unpoison them for use
    // mmap returns memory that ASan may track as unallocated, so we need to
    // explicitly unpoison it to allow allocations
    #ifdef ASAN_ENABLED
    size_t usable_size = _chunk_size - sizeof(Chunk);
    void* data_start = (char*)chunk + sizeof(Chunk);
    ASAN_UNPOISON_MEMORY_REGION(data_start, usable_size);
    #endif

    Counters::increment(LINEAR_ALLOCATOR_BYTES, _chunk_size);
    Counters::increment(LINEAR_ALLOCATOR_CHUNKS);
  }
  return chunk;
}

void LinearAllocator::freeChunk(Chunk *current) {
  OS::safeFree(current, _chunk_size);
  Counters::decrement(LINEAR_ALLOCATOR_BYTES, _chunk_size);
  Counters::decrement(LINEAR_ALLOCATOR_CHUNKS);
}

void LinearAllocator::reserveChunk(Chunk *current) {
  Chunk *reserve = allocateChunk(current);
  if (reserve != NULL &&
      !__sync_bool_compare_and_swap(&_reserve, current, reserve)) {
    // Unlikely case that we are too late
    freeChunk(reserve);
  }
}

Chunk *LinearAllocator::getNextChunk(Chunk *current) {
  Chunk *reserve = _reserve;

  if (reserve == current) {
    // Unlikely case: no reserve yet.
    // It's probably being allocated right now, so let's compete
    reserve = allocateChunk(current);
    if (reserve == NULL) {
      // Not enough memory
      return NULL;
    }

    Chunk *prev_reserve =
        __sync_val_compare_and_swap(&_reserve, current, reserve);
    if (prev_reserve != current) {
      freeChunk(reserve);
      reserve = prev_reserve;
    }
  }

  // Expected case: a new chunk is already reserved
  Chunk *tail = __sync_val_compare_and_swap(&_tail, current, reserve);
  return tail == current ? reserve : tail;
}
