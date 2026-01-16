/*
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

#ifdef __linux__

#include "common.h"
#include "counters.h"
#include "libraries.h"
#include "symbols_linux_dd.h"

#include <mutex>
#include <unordered_set>

// Track which libraries have had build-ID extraction attempted
// Mirrors the _parsed_inodes pattern from symbols_linux.cpp for O(1) skip
static std::unordered_set<const CodeCache*> _build_id_processed;
static std::mutex _build_id_lock;

void Libraries::updateBuildIds() {
  std::lock_guard<std::mutex> lock(_build_id_lock);

  int lib_count = _native_libs.count();

  for (int i = 0; i < lib_count; i++) {
    CodeCache* lib = _native_libs.at(i);
    if (lib == nullptr) {
      continue;
    }

    // O(1) check: Skip if already processed
    // Mirrors _parsed_inodes pattern from symbols_linux.cpp for optimal performance
    if (_build_id_processed.find(lib) != _build_id_processed.end()) {
      Counters::increment(REMOTE_SYMBOLICATION_BUILD_ID_CACHE_HITS);
      continue;
    }

    // Mark as processed immediately to avoid re-processing on errors
    _build_id_processed.insert(lib);

    // Skip if already has build-id (e.g., from JFR metadata load)
    if (lib->hasBuildId()) {
      continue;
    }

    const char* lib_name = lib->name();
    if (lib_name == nullptr) {
      continue;
    }

    // Extract build-id from library file (only happens once per library)
    size_t build_id_len;
    char* build_id = ddprof::SymbolsLinux::extractBuildId(lib_name, &build_id_len);

    if (build_id != nullptr) {
      // Set build-id and calculate load bias
      lib->setBuildId(build_id, build_id_len);

      // Calculate load bias: difference between runtime address and file base
      // For now, use image_base as the load bias base
      if (lib->imageBase() != nullptr) {
        lib->setLoadBias((uintptr_t)lib->imageBase());
      }

      free(build_id); // setBuildId makes its own copy

      // Track libraries with build-IDs
      Counters::increment(REMOTE_SYMBOLICATION_LIBS_WITH_BUILD_ID);
    } else {
      TEST_LOG("updateBuildIds: NO build-id found for %s", lib_name);
    }
  }
}

#endif // __linux__
