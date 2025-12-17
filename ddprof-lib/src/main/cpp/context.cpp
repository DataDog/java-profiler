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

#include "context.h"
#include "counters.h"
#include "os_dd.h"
#include "thread.h"
#include <cstring>
#include <cstdio>

// ABI compliance: exported symbols
DLLEXPORT thread_local Context context_tls_v1;
DLLEXPORT thread_local custom_labels_labelset_t* custom_labels_current_set = nullptr;
DLLEXPORT const u32 custom_labels_abi_version = 1;

Context::Context() {
  memset(buffer, 0, DD_CONTEXT_BUFFER_SIZE);
}

void Context::initialize() {
  // Initialize labelset header
  custom_labels_labelset_t* ls = labelset();
  ls->storage = labels();
  ls->count = 2; // Start with 2 reserved labels (span-id, root-span-id)
  ls->capacity = DD_LABELS_CAPACITY;

  // Initialize label metadata array
  custom_labels_label_t* label_array = labels();
  for (size_t i = 0; i < DD_LABELS_CAPACITY; i++) {
    unsigned char* key_buf = string_buffer(i);
    unsigned char* value_buf = key_buf + DD_LABEL_KEY_MAX_SIZE;

    label_array[i].key.len = 0;
    label_array[i].key.buf = key_buf;
    label_array[i].value.len = 0;
    label_array[i].value.buf = nullptr; // NULL indicates absent value
  }

  // Pre-populate reserved labels (indices 0 and 1)
  // Label 0: "span-id"
  size_t span_id_key_len = strlen(DD_LABEL_SPAN_ID_KEY);
  memcpy((void*)label_array[DD_LABEL_SPAN_ID_INDEX].key.buf, DD_LABEL_SPAN_ID_KEY, span_id_key_len);
  label_array[DD_LABEL_SPAN_ID_INDEX].key.len = span_id_key_len;
  label_array[DD_LABEL_SPAN_ID_INDEX].value.buf = nullptr; // Will be set when trace context is set

  // Label 1: "root-span-id"
  size_t root_span_id_key_len = strlen(DD_LABEL_ROOT_SPAN_ID_KEY);
  memcpy((void*)label_array[DD_LABEL_ROOT_SPAN_ID_INDEX].key.buf, DD_LABEL_ROOT_SPAN_ID_KEY, root_span_id_key_len);
  label_array[DD_LABEL_ROOT_SPAN_ID_INDEX].key.len = root_span_id_key_len;
  label_array[DD_LABEL_ROOT_SPAN_ID_INDEX].value.buf = nullptr; // Will be set when trace context is set

  // Update global pointer for ABI compliance
  custom_labels_current_set = ls;
}

void Context::setTraceContext(u64 spanId, u64 rootSpanId) {
  custom_labels_label_t* label_array = labels();

  // Format span ID as decimal string
  unsigned char* span_value_buf = string_buffer(DD_LABEL_SPAN_ID_INDEX) + DD_LABEL_KEY_MAX_SIZE;
  int span_len = snprintf((char*)span_value_buf, DD_LABEL_VALUE_MAX_SIZE, "%llu", (unsigned long long)spanId);
  if (span_len > 0 && span_len < (int)DD_LABEL_VALUE_MAX_SIZE) {
    label_array[DD_LABEL_SPAN_ID_INDEX].value.buf = span_value_buf;
    label_array[DD_LABEL_SPAN_ID_INDEX].value.len = span_len;
  }

  // Format root span ID as decimal string
  unsigned char* root_span_value_buf = string_buffer(DD_LABEL_ROOT_SPAN_ID_INDEX) + DD_LABEL_KEY_MAX_SIZE;
  int root_span_len = snprintf((char*)root_span_value_buf, DD_LABEL_VALUE_MAX_SIZE, "%llu", (unsigned long long)rootSpanId);
  if (root_span_len > 0 && root_span_len < (int)DD_LABEL_VALUE_MAX_SIZE) {
    label_array[DD_LABEL_ROOT_SPAN_ID_INDEX].value.buf = root_span_value_buf;
    label_array[DD_LABEL_ROOT_SPAN_ID_INDEX].value.len = root_span_len;
  }
}

bool Context::setLabel(const char* key, size_t key_len, const char* value, size_t value_len) {
  if (key == nullptr || key_len == 0 || value == nullptr) {
    return false;
  }

  custom_labels_labelset_t* ls = labelset();
  custom_labels_label_t* label_array = labels();

  // Truncate key and value if needed
  size_t actual_key_len = key_len < DD_LABEL_KEY_MAX_SIZE ? key_len : DD_LABEL_KEY_MAX_SIZE;
  size_t actual_value_len = value_len < DD_LABEL_VALUE_MAX_SIZE ? value_len : DD_LABEL_VALUE_MAX_SIZE;

  // Search for existing label with matching key (starting from index 2)
  for (size_t i = 2; i < ls->count; i++) {
    if (label_array[i].key.len == actual_key_len &&
        memcmp(label_array[i].key.buf, key, actual_key_len) == 0) {
      // Update existing label value
      unsigned char* value_buf = string_buffer(i) + DD_LABEL_KEY_MAX_SIZE;
      memcpy(value_buf, value, actual_value_len);
      label_array[i].value.buf = value_buf;
      label_array[i].value.len = actual_value_len;
      return true;
    }
  }

  // Add new label if space available
  if (ls->count < DD_LABELS_CAPACITY) {
    size_t idx = ls->count;
    unsigned char* key_buf = string_buffer(idx);
    unsigned char* value_buf = key_buf + DD_LABEL_KEY_MAX_SIZE;

    // Copy key
    memcpy(key_buf, key, actual_key_len);
    label_array[idx].key.buf = key_buf;
    label_array[idx].key.len = actual_key_len;

    // Copy value
    memcpy(value_buf, value, actual_value_len);
    label_array[idx].value.buf = value_buf;
    label_array[idx].value.len = actual_value_len;

    ls->count++;
    return true;
  }

  return false; // No space available
}

bool Context::removeLabel(const char* key, size_t key_len) {
  if (key == nullptr || key_len == 0) {
    return false;
  }

  custom_labels_labelset_t* ls = labelset();
  custom_labels_label_t* label_array = labels();

  size_t actual_key_len = key_len < DD_LABEL_KEY_MAX_SIZE ? key_len : DD_LABEL_KEY_MAX_SIZE;

  // Search for label (starting from index 2 to preserve reserved labels)
  for (size_t i = 2; i < ls->count; i++) {
    if (label_array[i].key.len == actual_key_len &&
        memcmp(label_array[i].key.buf, key, actual_key_len) == 0) {
      // Mark as absent by setting value.buf to null
      label_array[i].value.buf = nullptr;
      label_array[i].value.len = 0;
      return true;
    }
  }

  return false;
}

void Context::clearCustomLabels() {
  custom_labels_labelset_t* ls = labelset();
  custom_labels_label_t* label_array = labels();

  // Clear custom labels (indices 2 and above)
  for (size_t i = 2; i < ls->count; i++) {
    label_array[i].value.buf = nullptr;
    label_array[i].value.len = 0;
  }

  // Reset count to 2 (preserve reserved labels)
  ls->count = 2;
}

u64 Context::getSpanId() const {
  const custom_labels_labelset_t* ls = const_cast<Context*>(this)->labelset();
  if (ls != nullptr && ls->storage != nullptr && ls->count > DD_LABEL_SPAN_ID_INDEX) {
    const custom_labels_label_t& label = ls->storage[DD_LABEL_SPAN_ID_INDEX];
    if (label.value.buf != nullptr && label.value.len > 0) {
      char temp[32];
      size_t len = label.value.len < sizeof(temp) - 1 ? label.value.len : sizeof(temp) - 1;
      memcpy(temp, label.value.buf, len);
      temp[len] = '\0';
      return strtoull(temp, nullptr, 10);
    }
  }
  return 0;
}

u64 Context::getRootSpanId() const {
  const custom_labels_labelset_t* ls = const_cast<Context*>(this)->labelset();
  if (ls != nullptr && ls->storage != nullptr && ls->count > DD_LABEL_ROOT_SPAN_ID_INDEX) {
    const custom_labels_label_t& label = ls->storage[DD_LABEL_ROOT_SPAN_ID_INDEX];
    if (label.value.buf != nullptr && label.value.len > 0) {
      char temp[32];
      size_t len = label.value.len < sizeof(temp) - 1 ? label.value.len : sizeof(temp) - 1;
      memcpy(temp, label.value.buf, len);
      temp[len] = '\0';
      return strtoull(temp, nullptr, 10);
    }
  }
  return 0;
}

void Context::dumpLabels() const {
  const custom_labels_labelset_t* ls = const_cast<Context*>(this)->labelset();
  if (ls == nullptr) {
    TEST_LOG("===> Context: empty (no labelset)");
    return;
  }

  TEST_LOG("===> Context: tid:%d, label count=%zu, capacity=%zu", OS::threadId(), ls->count, ls->capacity);

  for (size_t i = 0; i < ls->count; i++) {
    const custom_labels_label_t& label = ls->storage[i];
    if (label.key.buf != nullptr && label.value.buf != nullptr) {
      TEST_LOG("  Label[%zu]: key='%.*s' value='%.*s'",
               i, (int)label.key.len, label.key.buf, (int)label.value.len, label.value.buf);
    } else if (label.key.buf != nullptr) {
      TEST_LOG("  Label[%zu]: key='%.*s' value=<absent>", i, (int)label.key.len, label.key.buf);
    }
  }
}

Context& Contexts::initializeContextTls() {
  Context& ctx = context_tls_v1;
  ctx.initialize();

  // Store pointer for signal-safe access
  ProfiledThread::current()->markContextTlsInitialized(&ctx);

  return ctx;
}

Context& Contexts::get() {
  ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
  if (thrd == nullptr || !thrd->isContextTlsInitialized()) {
    return DD_EMPTY_CONTEXT;
  }
  // Return via stored pointer - never access context_tls_v1 from signal handler
  // This avoids triggering TLS lazy initialization which can deadlock in malloc
  return *thrd->getContextTlsPtr();
}
