/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_UNLOADCAPTURE_H
#define _HOTSPOT_UNLOADCAPTURE_H

#include <jvmti.h>
#include <stddef.h>
#include <stdint.h>

/**
 * PROTOTYPE (phase 2 of doc/LazyJmethodIdCombinedPlan.md): keeps the names of
 * fjmethodid=lazy raw frames whose class may be unloaded before the dump.
 *
 * - The sampler adds each raw frame of a class outside the boot, platform and
 *   application loaders to a fixed-size lock-free set of (Method*, tag) pairs.
 * - GarbageCollectionStart drains the set: for each pair not captured yet, it
 *   checks the trace-ID tag against the holder and copies the names and line
 *   table into a cache, under crash protection, without JNI or JVMTI. With
 *   nothing pending it costs one atomic load.
 * - The dump takes a frame's captured name when resolve() refuses the frame.
 *
 * Enabled with DDPROF_CAPTURE_UNLOADING=1 in lazy mode, so one build can be
 * measured with and without it.
 */
class UnloadCapture {
public:
  // A captured method. Strings and the line table are malloc'd; ownership
  // passes to whoever take()s the entry.
  struct Entry {
    char* klass_name;
    char* method_name;
    char* signature;
    jvmtiLineNumberEntry* line_table;
    int line_table_size;
    bool is_thread_run;
    uint64_t generation;  // dump generation it was captured in
  };

  static bool enabled() { return _enabled; }

  // Lazy-mode start: reads the environment switch and turns on
  // GarbageCollectionStart if enabled.
  static void init(jvmtiEnv* jvmti);

  // Records the ClassLoaderData of a class from a loader that never unloads.
  static void notePermanentLoaderData(const void* cld);

  // Signal safe. Called for every lazy raw frame with its holder Klass*.
  static void onRawFrame(const void* method, const void* holder, uint32_t tag);

  static void JNICALL GarbageCollectionStart(jvmtiEnv* jvmti);

  // Dump thread: moves the entry for (method, tag) into *out, if there is one.
  static bool take(const void* method, uint32_t tag, Entry* out);

  // Dump thread, after each dump: frees entries captured before the previous
  // dump started, which no remaining trace can refer to.
  static void endDump();

  static void freeEntry(Entry& e);

private:
  static bool _enabled;
};

#endif // _HOTSPOT_UNLOADCAPTURE_H
