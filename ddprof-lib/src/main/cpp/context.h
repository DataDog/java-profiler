/*
 * Copyright 2021, 2025 Datadog, Inc
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

#ifndef _CONTEXT_H
#define _CONTEXT_H

#include "arch_dd.h"
#include "arguments.h"
#include "common.h"
#include "os_dd.h"
#include "vmEntry.h"
#include <cstddef>

// Custom labels ABI v1 structures (see docs/custom-labels-v1.md)
typedef struct {
  size_t len;
  const unsigned char* buf;
} custom_labels_string_t;

typedef struct {
  custom_labels_string_t key;
  custom_labels_string_t value;
} custom_labels_label_t;

typedef struct {
  custom_labels_label_t* storage;
  size_t count;
  size_t capacity;
} custom_labels_labelset_t;

// Custom labels configuration
static const size_t DD_LABELS_CAPACITY = 10;
static const size_t DD_LABEL_KEY_MAX_SIZE = 128;
static const size_t DD_LABEL_VALUE_MAX_SIZE = 256;

// Reserved label indices for trace context
static const size_t DD_LABEL_SPAN_ID_INDEX = 0;
static const size_t DD_LABEL_ROOT_SPAN_ID_INDEX = 1;
static const char DD_LABEL_SPAN_ID_KEY[] = "span-id";
static const char DD_LABEL_ROOT_SPAN_ID_KEY[] = "root-span-id";

// Memory layout constants
static const size_t DD_LABELSET_HEADER_SIZE = sizeof(custom_labels_labelset_t);
static const size_t DD_LABEL_METADATA_SIZE = sizeof(custom_labels_label_t);
static const size_t DD_LABEL_ARRAY_SIZE = DD_LABELS_CAPACITY * DD_LABEL_METADATA_SIZE;
static const size_t DD_LABEL_STRINGS_SIZE = DD_LABELS_CAPACITY * (DD_LABEL_KEY_MAX_SIZE + DD_LABEL_VALUE_MAX_SIZE);
static const size_t DD_CONTEXT_BUFFER_SIZE = DD_LABELSET_HEADER_SIZE + DD_LABEL_ARRAY_SIZE + DD_LABEL_STRINGS_SIZE;

/**
 * Thread-local context storage with custom labels support.
 *
 * Memory layout (4184 bytes):
 * [0-23]:    custom_labels_labelset_t header
 * [24-343]:  Label metadata array (10 × 32 bytes)
 * [344-4183]: String buffers (10 × 384 bytes)
 */
class alignas(DEFAULT_CACHE_LINE_SIZE) Context {
private:
  unsigned char buffer[DD_CONTEXT_BUFFER_SIZE];

  custom_labels_labelset_t* labelset() {
    return reinterpret_cast<custom_labels_labelset_t*>(buffer);
  }

  custom_labels_label_t* labels() {
    return reinterpret_cast<custom_labels_label_t*>(buffer + DD_LABELSET_HEADER_SIZE);
  }

  unsigned char* string_buffer(size_t label_index) {
    return buffer + DD_LABELSET_HEADER_SIZE + DD_LABEL_ARRAY_SIZE +
           (label_index * (DD_LABEL_KEY_MAX_SIZE + DD_LABEL_VALUE_MAX_SIZE));
  }

public:
  Context();

  // Initialize the context with pre-allocated buffers
  void initialize();

  // Set trace context (updates labels 0 and 1)
  void setTraceContext(u64 spanId, u64 rootSpanId);

  // Set a custom label (uses labels 2-9)
  bool setLabel(const char* key, size_t key_len, const char* value, size_t value_len);

  // Remove a custom label by key
  bool removeLabel(const char* key, size_t key_len);

  // Clear all custom labels (preserves span-id/root-span-id)
  void clearCustomLabels();

  // Helper methods to extract span IDs as u64 (for backward compatibility)
  u64 getSpanId() const;
  u64 getRootSpanId() const;

  // Debug: dump context labels to TEST_LOG
  void dumpLabels() const;

private:
  // Internal: Get the labelset pointer (for debugging and internal use only)
  custom_labels_labelset_t* getLabelset() { return labelset(); }

  // Internal: Get raw buffer pointer
  unsigned char* getBuffer() { return buffer; }

  // Allow Recording class to access internal labelset for JFR serialization
  friend class Recording;
};

static Context DD_EMPTY_CONTEXT;

class Contexts {
public:
  static Context& initializeContextTls();
  static Context& get();
};

// ABI compliance: exported symbols
DLLEXPORT extern thread_local Context context_tls_v1;
DLLEXPORT extern thread_local custom_labels_labelset_t* custom_labels_current_set;
DLLEXPORT extern const u32 custom_labels_abi_version;

#endif /* _CONTEXT_H */
