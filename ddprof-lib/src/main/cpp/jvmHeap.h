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

#ifndef _JVMHEAP_H
#define _JVMHEAP_H

#include <cstddef>

/**
 * This class only defines a layout compatible with the JDKs VirtualSpaceSummary
 * class and particularly its subclasses
 */
class VirtualSpaceSummary {
private:
  void *_start;
  void *_committed_end;
  void *_reserved_end;

public:
  long maxSize() { return (long)_reserved_end - (long)_start; }
};

/**
 * This class only defines a layout compatible with the JDKs GCHeapSummary class
 * and particularly its subclasses
 */
class GCHeapSummary {
private:
  void *vptr; // only 1-st level subclasses are used so we need to define the
              // 'synthetic' vptr field here
  VirtualSpaceSummary _heap;
  size_t _used;

public:
  long used() { return (long)_used; }

  long maxSize() { return _heap.maxSize(); }
};

/**
 * This class only defines a layout compatible with the JDKs CollectedHeap
 * class and particularly its subclasses
 */
class CollectedHeapWrapper {
private:
  void *vptr; // only 1-st level subclasses are used so we need to define the
              // 'synthetic' vptr field here
  void *_gc_heap_log; // ignored
public:
  // Historic gc information
  size_t _capacity_at_last_gc;
  size_t _used_at_last_gc;
};

#endif // _JVMHEAP_H