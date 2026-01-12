/*
 * Copyright 2020 Andrei Pangin
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

#ifndef _LINEARALLOCATOR_H
#define _LINEARALLOCATOR_H

#include <stddef.h>

struct Chunk {
  Chunk *prev;
  volatile size_t offs;
  // To avoid false sharing
  char _padding[56];
};

/**
 * Holds detached chunks from a LinearAllocator for deferred deallocation.
 * Used to keep trace memory alive during processor execution while allowing
 * the allocator to be reset for new allocations.
 */
struct ChunkList {
  Chunk *head;
  size_t chunk_size;

  ChunkList() : head(nullptr), chunk_size(0) {}
  ChunkList(Chunk *h, size_t sz) : head(h), chunk_size(sz) {}
};

class LinearAllocator {
private:
  size_t _chunk_size;
  Chunk *_tail;
  Chunk *_reserve;

  Chunk *allocateChunk(Chunk *current);
  void freeChunk(Chunk *current);
  void reserveChunk(Chunk *current);
  Chunk *getNextChunk(Chunk *current);

public:
  explicit LinearAllocator(size_t chunk_size);
  ~LinearAllocator();

  void clear();

  /**
   * Detaches all chunks from this allocator, returning them as a ChunkList.
   * The allocator is reset to an empty state with a fresh chunk for new allocations.
   * The detached chunks remain allocated and valid until freeChunks() is called.
   *
   * This enables deferred deallocation: reset the allocator immediately while
   * keeping old data alive until it's no longer needed.
   */
  ChunkList detachChunks();

  /**
   * Frees all chunks in a previously detached ChunkList.
   * Call this after processing is complete to deallocate the memory.
   */
  static void freeChunks(ChunkList& chunks);

  void *alloc(size_t size);
};

#endif // _LINEARALLOCATOR_H
