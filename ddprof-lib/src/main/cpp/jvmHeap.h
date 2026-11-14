/*
 * Copyright 2023, 2026 Datadog, Inc
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
 * These classes only define layouts compatible with the JDKs CollectedHeap
 * class and particularly its subclasses.
 *
 * JDK-8356848 ("Separate Metaspace and GC printing"), first released in
 * JDK 25, inserted a new GCMetaspaceLog* field between the heap-log pointer
 * and the historic capacity/used-at-last-gc fields, shifting the latter by
 * one pointer width on 64-bit builds. CollectedHeapWrapperPre25 matches the
 * layout on JDK <= 24; CollectedHeapWrapperV25Plus matches JDK 25+.
 */
class CollectedHeapWrapperPre25 {
private:
  void *vptr; // only 1-st level subclasses are used so we need to define the
              // 'synthetic' vptr field here
  void *_gc_heap_log; // GCHeapLog* _heap_log; ignored
public:
  // Historic gc information
  size_t _capacity_at_last_gc;
  size_t _used_at_last_gc;
};

class CollectedHeapWrapperV25Plus {
private:
  void *vptr;
  void *_gc_heap_log;  // GCHeapLog* _heap_log; ignored
  void *_metaspace_log; // GCMetaspaceLog* _metaspace_log (added by JDK-8356848); ignored
public:
  // Historic gc information
  size_t _capacity_at_last_gc;
  size_t _used_at_last_gc;
};

// First JDK version carrying JDK-8356848's CollectedHeap layout change.
// Gate on the Java (JDK) major version, not on hotspot_version(): JDK 8 GA
// reports java.vm.version="25.0-b70", which get_hotspot_version() misparses
// as 25 (the prop_value[3] > '0' guard fails for '0'), so a hotspot_version
// gate would wrongly apply this layout to a JDK 8 object.
const int COLLECTED_HEAP_METASPACE_LOG_MIN_VERSION = 25;

inline size_t collectedHeapUsedAtLastGc(void *collected_heap, int java_version) {
  if (java_version >= COLLECTED_HEAP_METASPACE_LOG_MIN_VERSION) {
    return ((CollectedHeapWrapperV25Plus *)collected_heap)->_used_at_last_gc;
  }
  return ((CollectedHeapWrapperPre25 *)collected_heap)->_used_at_last_gc;
}

inline size_t collectedHeapCapacityAtLastGc(void *collected_heap, int java_version) {
  if (java_version >= COLLECTED_HEAP_METASPACE_LOG_MIN_VERSION) {
    return ((CollectedHeapWrapperV25Plus *)collected_heap)->_capacity_at_last_gc;
  }
  return ((CollectedHeapWrapperPre25 *)collected_heap)->_capacity_at_last_gc;
}

#endif // _JVMHEAP_H