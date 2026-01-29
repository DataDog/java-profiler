// Unless explicitly stated otherwise all files in this repository are licensed under the Apache License (Version 2.0).
// This product includes software developed at Datadog (https://www.datadoghq.com/) Copyright 2025 Datadog, Inc.

#include "otel_process_ctx.h"
#include "common.h"

#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif

#ifdef __cplusplus
  #include <atomic>
  using std::atomic_thread_fence;
  using std::memory_order_seq_cst;
#else
  #include <stdatomic.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ADD_QUOTES_HELPER(x) #x
#define ADD_QUOTES(x) ADD_QUOTES_HELPER(x)

#ifndef PR_SET_VMA
  #define PR_SET_VMA            0x53564d41
  #define PR_SET_VMA_ANON_NAME  0
#endif

static const otel_process_ctx_data empty_data = {
  .deployment_environment_name = NULL,
  .host_name = NULL,
  .service_instance_id = NULL,
  .service_name = NULL,
  .service_version = NULL,
  .telemetry_sdk_language = NULL,
  .telemetry_sdk_version = NULL,
  .telemetry_sdk_name = NULL,
  .resources = NULL,
  .tls_config = NULL
};

#if (defined(OTEL_PROCESS_CTX_NOOP) && OTEL_PROCESS_CTX_NOOP) || !defined(__linux__)
  // NOOP implementations when OTEL_PROCESS_CTX_NOOP is defined or not on Linux

  otel_process_ctx_result otel_process_ctx_publish(const otel_process_ctx_data *data) {
    (void) data; // Suppress unused parameter warning
    return (otel_process_ctx_result) {.success = false, .error_message = "OTEL_PROCESS_CTX_NOOP mode is enabled - no-op implementation (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }

  bool otel_process_ctx_drop_current(void) {
    return true; // Nothing to do, this always succeeds
  }

  #ifndef OTEL_PROCESS_CTX_NO_READ
    otel_process_ctx_read_result otel_process_ctx_read(void) {
      return (otel_process_ctx_read_result) {.success = false, .error_message = "OTEL_PROCESS_CTX_NOOP mode is enabled - no-op implementation (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    bool otel_process_ctx_read_drop(otel_process_ctx_read_result *result) {
      (void) result; // Suppress unused parameter warning
      return false;
    }
  #endif // OTEL_PROCESS_CTX_NO_READ
#else // OTEL_PROCESS_CTX_NOOP

#include <sys/mman.h>
#include <sys/prctl.h>
#include <linux/memfd.h>
#include <sys/syscall.h>
#include <time.h>

// memfd_create may not be available in older glibc, use syscall wrapper
#ifndef MFD_CLOEXEC
  #define MFD_CLOEXEC 0x0001U
#endif

static int otel_memfd_create(const char *name, unsigned int flags) {
  return (int)syscall(__NR_memfd_create, name, flags);
}
/**
 * The process context data that's written into the published memory mapping.
 *
 * An outside-of-process reader will read this struct + otel_process_payload to get the data.
 * This structure follows the OpenTelemetry Process Context v2 specification.
 *
 * Header layout (v2):
 * - signature[8]:      "OTEL_CTX"
 * - version:           uint32 = 2
 * - payload_size:      uint32 (size of protobuf payload)
 * - published_at_ns:   uint64 (timestamp in nanoseconds since epoch, 0 = update in progress)
 * - payload:           pointer to protobuf-encoded Resource message
 */
typedef struct __attribute__((packed, aligned(8))) {
  char otel_process_ctx_signature[8];   // Always "OTEL_CTX"
  uint32_t otel_process_ctx_version;    // Protocol version (currently 2)
  uint32_t otel_process_payload_size;   // Size of protobuf payload in bytes
  uint64_t published_at_ns;             // Timestamp in nanoseconds since epoch (0 = update in progress)
  char *otel_process_payload;           // Points to protobuf-encoded opentelemetry.proto.resource.v1.Resource
} otel_process_ctx_mapping;

/**
 * The full state of a published process context.
 *
 * This is returned as an opaque type to the caller.
 *
 * It is used to store the all data for the process context and that needs to be kept around while the context is published.
 */
typedef struct {
  // The pid of the process that published the context.
  pid_t publisher_pid;
  // The actual mapping of the process context. Note that because we `madvise(..., MADV_DONTFORK)` this mapping is not
  // propagated to child processes and thus `mapping` is only valid on the process that published the context.
  otel_process_ctx_mapping *mapping;
  // Size of the mapping in bytes
  long mapping_size;
  // The process context payload.
  char *payload;
  // Whether the mapping was created via memfd (true) or anonymous mmap (false)
  bool is_memfd;
} otel_process_ctx_state;

/**
 * Only one context is active, so we keep its state as a global.
 */
static otel_process_ctx_state published_state;

static otel_process_ctx_result otel_process_ctx_encode_payload(char **out, uint32_t *out_size, otel_process_ctx_data data);

// We use a mapping size of 2 pages explicitly as a hint when running on legacy kernels that don't support the
// PR_SET_VMA_ANON_NAME prctl call; see below for more details.
static long size_for_mapping(void) {
  long page_size_bytes = sysconf(_SC_PAGESIZE);
  if (page_size_bytes < 4096) {
    return -1;
  }
  // Per PR #34: Use 1 page instead of 2
  return page_size_bytes;
}

// Get current timestamp in nanoseconds since epoch
static uint64_t get_timestamp_ns(void) {
  struct timespec ts;
  if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
    return 0;
  }
  return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

/**
 * The process context is designed to be read by an outside-of-process reader. Thus, for concurrency purposes the steps
 * on this method are ordered in a way to avoid races, or if not possible to avoid, to allow the reader to detect if there was a race.
 *
 * This implements the OpenTelemetry Process Context v2 publication protocol:
 * 1. Try memfd_create first, fall back to anonymous mmap
 * 2. Apply MADV_DONTFORK to prevent fork inheritance
 * 3. Populate header fields (version, payload_size, payload pointer)
 * 4. Issue memory barrier
 * 5. Write signature last to ensure readers observe complete data
 * 6. Set published_at_ns timestamp to signal data is ready
 * 7. Name the mapping via prctl for discovery
 */
otel_process_ctx_result otel_process_ctx_publish(const otel_process_ctx_data *data) {
  TEST_LOG("otel_process_ctx_publish: Starting publication, pid=%d", getpid());

  // Step: Drop any previous context if it exists
  // No state should be around anywhere after this step.
  if (!otel_process_ctx_drop_current()) {
    TEST_LOG("otel_process_ctx_publish: Failed to drop previous context");
    return (otel_process_ctx_result) {.success = false, .error_message = "Failed to drop previous context (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }

  // Step: Determine size for mapping
  long mapping_size = size_for_mapping();
  if (mapping_size == -1) {
    TEST_LOG("otel_process_ctx_publish: Failed to get page size");
    return (otel_process_ctx_result) {.success = false, .error_message = "Failed to get page size (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }
  TEST_LOG("otel_process_ctx_publish: Mapping size=%ld bytes", mapping_size);

  // Step: Prepare the payload to be published (protobuf-encoded Resource message)
  // The payload SHOULD be ready and valid before trying to actually create the mapping.
  if (!data) {
    TEST_LOG("otel_process_ctx_publish: data is NULL");
    return (otel_process_ctx_result) {.success = false, .error_message = "otel_process_ctx_data is NULL (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }
  uint32_t payload_size = 0;
  otel_process_ctx_result result = otel_process_ctx_encode_payload(&published_state.payload, &payload_size, *data);
  if (!result.success) {
    TEST_LOG("otel_process_ctx_publish: Failed to encode payload: %s", result.error_message);
    return result;
  }
  TEST_LOG("otel_process_ctx_publish: Encoded payload size=%u bytes", payload_size);

  // Step: Create the mapping
  // Per v2 spec, prefer memfd_create("OTEL_CTX", ...) with fallback to anonymous mmap
  published_state.publisher_pid = getpid();
  published_state.mapping_size = mapping_size;
  published_state.is_memfd = false;

  int memfd = otel_memfd_create("OTEL_CTX", MFD_CLOEXEC);
  TEST_LOG("otel_process_ctx_publish: memfd_create result=%d", memfd);
  if (memfd >= 0) {
    // memfd_create succeeded - use shared mapping
    if (ftruncate(memfd, mapping_size) == 0) {
      published_state.mapping = (otel_process_ctx_mapping *)
        mmap(NULL, mapping_size, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0);
      if (published_state.mapping != MAP_FAILED) {
        published_state.is_memfd = true;
        TEST_LOG("otel_process_ctx_publish: memfd mapping successful at %p", published_state.mapping);
      } else {
        TEST_LOG("otel_process_ctx_publish: memfd mmap failed");
      }
    } else {
      TEST_LOG("otel_process_ctx_publish: ftruncate failed");
    }
    close(memfd);
  }

  // Fallback to anonymous mapping if memfd failed
  if (!published_state.is_memfd) {
    TEST_LOG("otel_process_ctx_publish: Falling back to anonymous mmap");
    published_state.mapping = (otel_process_ctx_mapping *)
      mmap(NULL, mapping_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  }

  if (published_state.mapping == MAP_FAILED) {
    TEST_LOG("otel_process_ctx_publish: Failed to allocate mapping");
    otel_process_ctx_drop_current();
    return (otel_process_ctx_result) {.success = false, .error_message = "Failed to allocate mapping (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }
  TEST_LOG("otel_process_ctx_publish: Mapping created at %p (is_memfd=%d)", published_state.mapping, published_state.is_memfd);

  // Step: Setup MADV_DONTFORK
  // This ensures that the mapping is not propagated to child processes (they should call publish again).
  if (madvise(published_state.mapping, mapping_size, MADV_DONTFORK) == -1) {
    if (otel_process_ctx_drop_current()) {
      return (otel_process_ctx_result) {.success = false, .error_message = "Failed to setup MADV_DONTFORK (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
    } else {
      return (otel_process_ctx_result) {.success = false, .error_message = "Failed to drop previous context (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
    }
  }

  // Step: Populate the mapping header (v2 format)
  // Per v2 spec: signature is written LAST to ensure readers never observe incomplete data
  // Initialize with signature zeroed, published_at_ns = 0 (signals "not ready yet")
  *published_state.mapping = (otel_process_ctx_mapping) {
    .otel_process_ctx_signature = {0},  // Set in final step below
    .otel_process_ctx_version = 2,      // v2 protocol
    .otel_process_payload_size = payload_size,
    .published_at_ns = 0,               // Will be set after signature
    .otel_process_payload = published_state.payload
  };

  // Step: Memory barrier before signature
  // Ensures all header fields are visible before signature is written
  atomic_thread_fence(memory_order_seq_cst);

  // Step: Write signature LAST (per v2 spec requirement)
  // After this, external readers can see the signature and know header is valid
  memcpy(published_state.mapping->otel_process_ctx_signature, "OTEL_CTX",
         sizeof(published_state.mapping->otel_process_ctx_signature));

  // Step: Memory barrier after signature
  atomic_thread_fence(memory_order_seq_cst);

  // Step: Set published_at_ns to signal data is ready
  // Per v2 spec: non-zero timestamp indicates active, valid data
  uint64_t timestamp = get_timestamp_ns();
  if (timestamp == 0) timestamp = 1; // Ensure non-zero (0 = update in progress)
  __atomic_store_n(&published_state.mapping->published_at_ns, timestamp, __ATOMIC_RELEASE);
  TEST_LOG("otel_process_ctx_publish: Set published_at_ns=%llu", (unsigned long long)timestamp);

  // NOTE: Per PR #34 spec update - mapping remains writable (rw-p or rw-s)
  // This allows for in-place updates and matches the reference implementation.
  // The mprotect to PROT_READ has been removed as the reader now accepts rw permissions.
  TEST_LOG("otel_process_ctx_publish: Mapping kept writable for in-place updates");

  // Step: Name the mapping for discovery
  // On memfd, the mapping appears as /memfd:OTEL_CTX in /proc/pid/maps
  // On anonymous mmap with prctl naming, it appears as [anon:OTEL_CTX]
  if (!published_state.is_memfd) {
    // Only need prctl naming for anonymous mappings; memfd is already named
    int prctl_result = prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, published_state.mapping, mapping_size, "OTEL_CTX");
    TEST_LOG("otel_process_ctx_publish: prctl naming result=%d (is_memfd=false)", prctl_result);
    if (prctl_result == -1) {
      // Naming is a Linux 5.17+ feature. Failure is acceptable:
      // 1. External tools can still detect via memfd name or magic number scanning
      // 2. prctl hooks can still observe the call attempt
      TEST_LOG("otel_process_ctx_publish: prctl naming failed (expected on kernels < 5.17)");
    }
  } else {
    TEST_LOG("otel_process_ctx_publish: Skipped prctl naming (using memfd)");
  }

  TEST_LOG("otel_process_ctx_publish: Successfully published context at %p, signature='%.8s', version=%u, payload_size=%u, timestamp=%llu",
           published_state.mapping,
           published_state.mapping->otel_process_ctx_signature,
           published_state.mapping->otel_process_ctx_version,
           published_state.mapping->otel_process_payload_size,
           (unsigned long long)published_state.mapping->published_at_ns);

  return (otel_process_ctx_result) {.success = true, .error_message = NULL};
}

bool otel_process_ctx_drop_current(void) {
  otel_process_ctx_state state = published_state;

  if (state.mapping == NULL || state.mapping == MAP_FAILED) {
    TEST_LOG("otel_process_ctx_drop_current: No active mapping to drop");
    return true;
  }

  TEST_LOG("otel_process_ctx_drop_current: Dropping mapping at %p (publisher_pid=%d, current_pid=%d)",
           state.mapping, state.publisher_pid, getpid());

  // Zero out the state and make sure no operations below are reordered with zeroing
  published_state = (otel_process_ctx_state) {.publisher_pid = 0, .mapping = NULL, .mapping_size = 0, .payload = NULL, .is_memfd = false};
  atomic_thread_fence(memory_order_seq_cst);

  // The mapping only exists if it was created by the current process; if it was inherited by a fork it doesn't exist anymore
  // (due to the MADV_DONTFORK) and we don't need to do anything to it.
  if (state.mapping != NULL && state.mapping != MAP_FAILED && getpid() == state.publisher_pid) {
    if (state.mapping_size <= 0 || munmap(state.mapping, state.mapping_size) == -1) {
      TEST_LOG("otel_process_ctx_drop_current: Failed to munmap");
      return false;
    }
    TEST_LOG("otel_process_ctx_drop_current: Successfully unmapped");
  }

  // The payload may have been inherited from a parent. This is a regular malloc so we need to free it so we don't leak.
  if (state.payload) {
    TEST_LOG("otel_process_ctx_drop_current: Freeing payload");
    free(state.payload);
  }

  return true;
}

// =============================================================================
// Minimal Protobuf Encoder for OpenTelemetry Resource message (v2 spec)
// =============================================================================
//
// Encodes opentelemetry.proto.resource.v1.Resource message containing KeyValue attributes.
// Wire format reference: https://protobuf.dev/programming-guides/encoding/
//
// Message hierarchy:
//   Resource { repeated KeyValue attributes = 1; }
//   KeyValue { string key = 1; AnyValue value = 2; }
//   AnyValue { oneof value { string string_value = 1; ... } }

// Write a varint (variable-length integer) to buffer, return bytes written
static size_t pb_write_varint(uint8_t *buf, uint64_t value) {
  size_t bytes = 0;
  while (value > 0x7F) {
    buf[bytes++] = (uint8_t)((value & 0x7F) | 0x80);
    value >>= 7;
  }
  buf[bytes++] = (uint8_t)(value & 0x7F);
  return bytes;
}

// Calculate varint size without writing
static size_t pb_varint_size(uint64_t value) {
  size_t bytes = 1;
  while (value > 0x7F) {
    bytes++;
    value >>= 7;
  }
  return bytes;
}

// Write a length-delimited string field: [tag][length][bytes]
// Returns bytes written
static size_t pb_write_string_field(uint8_t *buf, uint32_t field_num, const char *str, size_t len) {
  size_t pos = 0;
  // Tag: (field_num << 3) | wire_type, wire_type 2 = length-delimited
  uint32_t tag = (field_num << 3) | 2;
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, len);
  memcpy(buf + pos, str, len);
  pos += len;
  return pos;
}

// Calculate size of a string field
static size_t pb_string_field_size(uint32_t field_num, size_t len) {
  uint32_t tag = (field_num << 3) | 2;
  return pb_varint_size(tag) + pb_varint_size(len) + len;
}

// Calculate size of AnyValue message containing a string_value (field 1)
static size_t pb_anyvalue_string_size(size_t value_len) {
  // AnyValue { string string_value = 1; }
  return pb_string_field_size(1, value_len);
}

// Write AnyValue message containing a string_value (field 1)
static size_t pb_write_anyvalue_string(uint8_t *buf, const char *value, size_t value_len) {
  return pb_write_string_field(buf, 1, value, value_len);
}

// Forward declarations for functions used before their definitions
static size_t pb_keyvalue_size(size_t key_len, size_t value_len);
static size_t pb_write_keyvalue(uint8_t *buf, const char *key, size_t key_len, const char *value, size_t value_len);

// =============================================================================
// Int64 Value Encoding (AnyValue.int_value = field 3, wire type 0)
// =============================================================================

// Calculate size of AnyValue message containing an int_value (field 3)
static size_t pb_anyvalue_int_size(int64_t value) {
  // AnyValue { int64 int_value = 3; }
  // tag (1 byte: field 3, wire type 0) + varint-encoded value
  return 1 + pb_varint_size((uint64_t)value);
}

// Write AnyValue message containing an int_value (field 3)
static size_t pb_write_anyvalue_int(uint8_t *buf, int64_t value) {
  size_t pos = 0;
  buf[pos++] = (3 << 3) | 0;  // field 3, wire type 0 (varint)
  pos += pb_write_varint(buf + pos, (uint64_t)value);
  return pos;
}

// Calculate size of KeyValue message with int64 value
static size_t pb_keyvalue_int_size(size_t key_len, int64_t value) {
  // KeyValue { string key = 1; AnyValue value = 2; }
  size_t key_field_size = pb_string_field_size(1, key_len);
  size_t anyvalue_size = pb_anyvalue_int_size(value);
  // value field (field 2) is embedded message (wire type 2)
  size_t value_field_size = pb_varint_size((2 << 3) | 2) + pb_varint_size(anyvalue_size) + anyvalue_size;
  return key_field_size + value_field_size;
}

// Write KeyValue message with int64 value
static size_t pb_write_keyvalue_int(uint8_t *buf, const char *key, size_t key_len, int64_t value) {
  size_t pos = 0;

  // Field 1: string key
  pos += pb_write_string_field(buf + pos, 1, key, key_len);

  // Field 2: AnyValue value (embedded message)
  size_t anyvalue_size = pb_anyvalue_int_size(value);
  uint32_t tag = (2 << 3) | 2;  // field 2, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, anyvalue_size);
  pos += pb_write_anyvalue_int(buf + pos, value);

  return pos;
}

// =============================================================================
// KvList Value Encoding (AnyValue.kvlist_value = field 6, wire type 2)
// KeyValueList { repeated KeyValue values = 1; }
// =============================================================================

// Calculate size of KeyValueList message (just the content, no outer tag/length)
static size_t pb_keyvaluelist_content_size(const char **pairs, size_t num_pairs) {
  size_t size = 0;
  for (size_t i = 0; i < num_pairs; i++) {
    size_t key_len = strlen(pairs[i * 2]);
    size_t value_len = strlen(pairs[i * 2 + 1]);
    // Each KeyValue is in field 1 of KeyValueList
    size_t kv_size = pb_keyvalue_size(key_len, value_len);
    // tag + length prefix + content
    size += pb_varint_size((1 << 3) | 2) + pb_varint_size(kv_size) + kv_size;
  }
  return size;
}

// Write KeyValueList message content (just the repeated KeyValue entries)
static size_t pb_write_keyvaluelist_content(uint8_t *buf, const char **pairs, size_t num_pairs) {
  size_t pos = 0;
  for (size_t i = 0; i < num_pairs; i++) {
    const char *key = pairs[i * 2];
    const char *value = pairs[i * 2 + 1];
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);

    // Write as embedded message: field 1 (values), wire type 2
    size_t kv_size = pb_keyvalue_size(key_len, value_len);
    uint32_t tag = (1 << 3) | 2;
    pos += pb_write_varint(buf + pos, tag);
    pos += pb_write_varint(buf + pos, kv_size);
    pos += pb_write_keyvalue(buf + pos, key, key_len, value, value_len);
  }
  return pos;
}

// Calculate size of AnyValue message containing a kvlist_value (field 6)
static size_t pb_anyvalue_kvlist_size(const char **pairs, size_t num_pairs) {
  // AnyValue { KeyValueList kvlist_value = 6; }
  size_t kvlist_size = pb_keyvaluelist_content_size(pairs, num_pairs);
  // tag (1 byte: field 6, wire type 2) + length varint + content
  return 1 + pb_varint_size(kvlist_size) + kvlist_size;
}

// Write AnyValue message containing a kvlist_value (field 6)
static size_t pb_write_anyvalue_kvlist(uint8_t *buf, const char **pairs, size_t num_pairs) {
  size_t pos = 0;
  buf[pos++] = (6 << 3) | 2;  // field 6, wire type 2 (length-delimited)
  size_t kvlist_size = pb_keyvaluelist_content_size(pairs, num_pairs);
  pos += pb_write_varint(buf + pos, kvlist_size);
  pos += pb_write_keyvaluelist_content(buf + pos, pairs, num_pairs);
  return pos;
}

// Calculate size of KeyValue message with kvlist value
static size_t pb_keyvalue_kvlist_size(size_t key_len, const char **pairs, size_t num_pairs) {
  // KeyValue { string key = 1; AnyValue value = 2; }
  size_t key_field_size = pb_string_field_size(1, key_len);
  size_t anyvalue_size = pb_anyvalue_kvlist_size(pairs, num_pairs);
  // value field (field 2) is embedded message (wire type 2)
  size_t value_field_size = pb_varint_size((2 << 3) | 2) + pb_varint_size(anyvalue_size) + anyvalue_size;
  return key_field_size + value_field_size;
}

// Write KeyValue message with kvlist value
static size_t pb_write_keyvalue_kvlist(uint8_t *buf, const char *key, size_t key_len, const char **pairs, size_t num_pairs) {
  size_t pos = 0;

  // Field 1: string key
  pos += pb_write_string_field(buf + pos, 1, key, key_len);

  // Field 2: AnyValue value (embedded message)
  size_t anyvalue_size = pb_anyvalue_kvlist_size(pairs, num_pairs);
  uint32_t tag = (2 << 3) | 2;  // field 2, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, anyvalue_size);
  pos += pb_write_anyvalue_kvlist(buf + pos, pairs, num_pairs);

  return pos;
}

// =============================================================================
// Array Value Encoding (AnyValue.array_value = field 5, wire type 2)
// ArrayValue { repeated AnyValue values = 1; }
// =============================================================================

// Calculate size of ArrayValue message content (repeated AnyValue entries with string values)
static size_t pb_arrayvalue_strings_content_size(const char **strings, size_t count) {
  size_t size = 0;
  for (size_t i = 0; i < count; i++) {
    size_t str_len = strlen(strings[i]);
    // Each string is wrapped in AnyValue (field 1 = string_value)
    size_t anyvalue_size = pb_anyvalue_string_size(str_len);
    // tag + length prefix + content
    size += pb_varint_size((1 << 3) | 2) + pb_varint_size(anyvalue_size) + anyvalue_size;
  }
  return size;
}

// Write ArrayValue message content (repeated AnyValue entries with string values)
static size_t pb_write_arrayvalue_strings_content(uint8_t *buf, const char **strings, size_t count) {
  size_t pos = 0;
  for (size_t i = 0; i < count; i++) {
    size_t str_len = strlen(strings[i]);
    size_t anyvalue_size = pb_anyvalue_string_size(str_len);

    // Write as embedded AnyValue: ArrayValue.values = field 1, wire type 2
    uint32_t tag = (1 << 3) | 2;
    pos += pb_write_varint(buf + pos, tag);
    pos += pb_write_varint(buf + pos, anyvalue_size);
    pos += pb_write_anyvalue_string(buf + pos, strings[i], str_len);
  }
  return pos;
}

// Calculate size of AnyValue message containing an array_value (field 5)
static size_t pb_anyvalue_array_strings_size(const char **strings, size_t count) {
  // AnyValue { ArrayValue array_value = 5; }
  size_t array_size = pb_arrayvalue_strings_content_size(strings, count);
  // tag (1 byte: field 5, wire type 2) + length varint + content
  return 1 + pb_varint_size(array_size) + array_size;
}

// Write AnyValue message containing an array_value (field 5) with strings
static size_t pb_write_anyvalue_array_strings(uint8_t *buf, const char **strings, size_t count) {
  size_t pos = 0;
  buf[pos++] = (5 << 3) | 2;  // field 5, wire type 2 (length-delimited)
  size_t array_size = pb_arrayvalue_strings_content_size(strings, count);
  pos += pb_write_varint(buf + pos, array_size);
  pos += pb_write_arrayvalue_strings_content(buf + pos, strings, count);
  return pos;
}

// Calculate size of KeyValue message with array value (array of strings)
static size_t pb_keyvalue_array_strings_size(size_t key_len, const char **strings, size_t count) {
  // KeyValue { string key = 1; AnyValue value = 2; }
  size_t key_field_size = pb_string_field_size(1, key_len);
  size_t anyvalue_size = pb_anyvalue_array_strings_size(strings, count);
  // value field (field 2) is embedded message (wire type 2)
  size_t value_field_size = pb_varint_size((2 << 3) | 2) + pb_varint_size(anyvalue_size) + anyvalue_size;
  return key_field_size + value_field_size;
}

// Write KeyValue message with array value (array of strings)
static size_t pb_write_keyvalue_array_strings(uint8_t *buf, const char *key, size_t key_len, const char **strings, size_t count) {
  size_t pos = 0;

  // Field 1: string key
  pos += pb_write_string_field(buf + pos, 1, key, key_len);

  // Field 2: AnyValue value (embedded message with array_value)
  size_t anyvalue_size = pb_anyvalue_array_strings_size(strings, count);
  uint32_t tag = (2 << 3) | 2;  // field 2, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, anyvalue_size);
  pos += pb_write_anyvalue_array_strings(buf + pos, strings, count);

  return pos;
}

// =============================================================================
// String Value KeyValue (existing implementation renamed for clarity)
// =============================================================================

// Calculate size of KeyValue message
static size_t pb_keyvalue_size(size_t key_len, size_t value_len) {
  // KeyValue { string key = 1; AnyValue value = 2; }
  size_t key_field_size = pb_string_field_size(1, key_len);
  size_t anyvalue_size = pb_anyvalue_string_size(value_len);
  // value field (field 2) is embedded message (wire type 2)
  size_t value_field_size = pb_varint_size((2 << 3) | 2) + pb_varint_size(anyvalue_size) + anyvalue_size;
  return key_field_size + value_field_size;
}

// Write KeyValue message
static size_t pb_write_keyvalue(uint8_t *buf, const char *key, size_t key_len, const char *value, size_t value_len) {
  size_t pos = 0;

  // Field 1: string key
  pos += pb_write_string_field(buf + pos, 1, key, key_len);

  // Field 2: AnyValue value (embedded message)
  size_t anyvalue_size = pb_anyvalue_string_size(value_len);
  uint32_t tag = (2 << 3) | 2;  // field 2, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, anyvalue_size);
  pos += pb_write_anyvalue_string(buf + pos, value, value_len);

  return pos;
}

// Validate pairs array and calculate total payload size
static otel_process_ctx_result pb_validate_and_calculate_size(size_t *out_size, size_t *out_num_pairs, const char **pairs) {
  size_t num_entries = 0;
  for (size_t i = 0; pairs[i] != NULL; i++) num_entries++;

  if (num_entries % 2 != 0) {
    return (otel_process_ctx_result) {.success = false, .error_message = "Pairs array has odd number of entries (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }
  *out_num_pairs = num_entries / 2;

  // Calculate size for Resource message: repeated KeyValue attributes (field 1)
  *out_size = 0;
  for (size_t i = 0; i < *out_num_pairs; i++) {
    size_t key_len = strlen(pairs[i * 2]);
    size_t value_len = strlen(pairs[i * 2 + 1]);

    if (key_len > INT16_MAX || value_len > INT16_MAX) {
      return (otel_process_ctx_result) {.success = false, .error_message = "Key or value exceeds INT16_MAX limit (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
    }

    // Each KeyValue is an embedded message in field 1 of Resource
    size_t kv_size = pb_keyvalue_size(key_len, value_len);
    // Field tag + length prefix + message content
    *out_size += pb_varint_size((1 << 3) | 2) + pb_varint_size(kv_size) + kv_size;
  }

  return (otel_process_ctx_result) {.success = true, .error_message = NULL};
}

// Write all key-value pairs as Resource.attributes field (field 1, repeated KeyValue)
static size_t pb_write_attributes(uint8_t *buf, const char **pairs, size_t num_pairs) {
  size_t pos = 0;

  for (size_t i = 0; i < num_pairs; i++) {
    const char *key = pairs[i * 2];
    const char *value = pairs[i * 2 + 1];
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);

    // Write as embedded message: field 1 (attributes), wire type 2
    size_t kv_size = pb_keyvalue_size(key_len, value_len);
    uint32_t tag = (1 << 3) | 2;
    pos += pb_write_varint(buf + pos, tag);
    pos += pb_write_varint(buf + pos, kv_size);
    pos += pb_write_keyvalue(buf + pos, key, key_len, value, value_len);
  }

  return pos;
}

// Helper: Write a single KeyValue (string) as a Resource.attributes field (field 1)
static size_t pb_write_attribute_string(uint8_t *buf, const char *key, const char *value) {
  size_t key_len = strlen(key);
  size_t value_len = strlen(value);
  size_t kv_size = pb_keyvalue_size(key_len, value_len);

  size_t pos = 0;
  uint32_t tag = (1 << 3) | 2;  // field 1, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, kv_size);
  pos += pb_write_keyvalue(buf + pos, key, key_len, value, value_len);
  return pos;
}

// Helper: Write a single KeyValue (int64) as a Resource.attributes field (field 1)
static size_t pb_write_attribute_int(uint8_t *buf, const char *key, int64_t value) {
  size_t key_len = strlen(key);
  size_t kv_size = pb_keyvalue_int_size(key_len, value);

  size_t pos = 0;
  uint32_t tag = (1 << 3) | 2;  // field 1, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, kv_size);
  pos += pb_write_keyvalue_int(buf + pos, key, key_len, value);
  return pos;
}

// Helper: Write a single KeyValue (kvlist) as a Resource.attributes field (field 1)
static size_t pb_write_attribute_kvlist(uint8_t *buf, const char *key, const char **pairs, size_t num_pairs) {
  size_t key_len = strlen(key);
  size_t kv_size = pb_keyvalue_kvlist_size(key_len, pairs, num_pairs);

  size_t pos = 0;
  uint32_t tag = (1 << 3) | 2;  // field 1, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, kv_size);
  pos += pb_write_keyvalue_kvlist(buf + pos, key, key_len, pairs, num_pairs);
  return pos;
}

// Helper: Calculate size of a single KeyValue (string) as a Resource.attributes field (field 1)
static size_t pb_attribute_string_size(const char *key, const char *value) {
  size_t key_len = strlen(key);
  size_t value_len = strlen(value);
  size_t kv_size = pb_keyvalue_size(key_len, value_len);
  return pb_varint_size((1 << 3) | 2) + pb_varint_size(kv_size) + kv_size;
}

// Helper: Calculate size of a single KeyValue (int64) as a Resource.attributes field (field 1)
static size_t pb_attribute_int_size(const char *key, int64_t value) {
  size_t key_len = strlen(key);
  size_t kv_size = pb_keyvalue_int_size(key_len, value);
  return pb_varint_size((1 << 3) | 2) + pb_varint_size(kv_size) + kv_size;
}

// Helper: Calculate size of a single KeyValue (kvlist) as a Resource.attributes field (field 1)
static size_t pb_attribute_kvlist_size(const char *key, const char **pairs, size_t num_pairs) {
  size_t key_len = strlen(key);
  size_t kv_size = pb_keyvalue_kvlist_size(key_len, pairs, num_pairs);
  return pb_varint_size((1 << 3) | 2) + pb_varint_size(kv_size) + kv_size;
}

// Helper: Calculate size of a single KeyValue (array of strings) as a Resource.attributes field (field 1)
static size_t pb_attribute_array_strings_size(const char *key, const char **strings, size_t count) {
  size_t key_len = strlen(key);
  size_t kv_size = pb_keyvalue_array_strings_size(key_len, strings, count);
  return pb_varint_size((1 << 3) | 2) + pb_varint_size(kv_size) + kv_size;
}

// Helper: Write a single KeyValue (array of strings) as a Resource.attributes field (field 1)
static size_t pb_write_attribute_array_strings(uint8_t *buf, const char *key, const char **strings, size_t count) {
  size_t key_len = strlen(key);
  size_t kv_size = pb_keyvalue_array_strings_size(key_len, strings, count);

  size_t pos = 0;
  uint32_t tag = (1 << 3) | 2;  // field 1, wire type 2
  pos += pb_write_varint(buf + pos, tag);
  pos += pb_write_varint(buf + pos, kv_size);
  pos += pb_write_keyvalue_array_strings(buf + pos, key, key_len, strings, count);
  return pos;
}

/**
 * Encode the payload as protobuf opentelemetry.proto.resource.v1.Resource message.
 *
 * This implements a minimal protobuf encoder supporting string, int64, and kvlist attributes.
 * The Resource message contains repeated KeyValue in field 1 (attributes).
 */
static otel_process_ctx_result otel_process_ctx_encode_payload(char **out, uint32_t *out_size, otel_process_ctx_data data) {
  // Build array of key-value pairs using OpenTelemetry semantic convention keys
  const char *pairs[] = {
    "deployment.environment.name", data.deployment_environment_name,
    "host.name", data.host_name,
    "service.instance.id", data.service_instance_id,
    "service.name", data.service_name,
    "service.version", data.service_version,
    "telemetry.sdk.language", data.telemetry_sdk_language,
    "telemetry.sdk.version", data.telemetry_sdk_version,
    "telemetry.sdk.name", data.telemetry_sdk_name,
    NULL
  };

  // Validate and calculate size for standard pairs
  size_t num_pairs = 0, pairs_size = 0;
  otel_process_ctx_result result = pb_validate_and_calculate_size(&pairs_size, &num_pairs, pairs);
  if (!result.success) return result;

  // Validate and calculate size for additional resources
  size_t resources_num_pairs = 0, resources_size = 0;
  if (data.resources != NULL) {
    result = pb_validate_and_calculate_size(&resources_size, &resources_num_pairs, (const char **)data.resources);
    if (!result.success) return result;
  }

  // Calculate size for TLS config if present
  size_t tls_config_size = 0;
  size_t tls_keymap_count = 0;
  if (data.tls_config != NULL) {
    // threadlocal.schema_version = schema_version string (e.g. "tlsdesc_v1_dev")
    if (data.tls_config->schema_version != NULL) {
      tls_config_size += pb_attribute_string_size("threadlocal.schema_version", data.tls_config->schema_version);
    }

    // threadlocal.max_record_size = <int> (int64)
    tls_config_size += pb_attribute_int_size("threadlocal.max_record_size", data.tls_config->max_record_size);

    // threadlocal.attribute_key_map = <array of strings> (position = key index)
    if (data.tls_config->attribute_key_map != NULL) {
      // Count entries in attribute_key_map (each entry is a key name, position = index)
      for (size_t i = 0; data.tls_config->attribute_key_map[i] != NULL; i++) {
        tls_keymap_count++;
      }
      tls_config_size += pb_attribute_array_strings_size("threadlocal.attribute_key_map",
                                                          (const char **)data.tls_config->attribute_key_map,
                                                          tls_keymap_count);
    }
  }

  size_t total_size = pairs_size + resources_size + tls_config_size;

  // Allocate buffer for protobuf payload
  uint8_t *encoded = (uint8_t *) calloc(total_size, 1);
  if (!encoded) {
    return (otel_process_ctx_result) {.success = false, .error_message = "Failed to allocate memory for payload (" __FILE__ ":" ADD_QUOTES(__LINE__) ")"};
  }

  // Write standard pairs
  size_t pos = pb_write_attributes(encoded, pairs, num_pairs);

  // Write additional resources
  if (data.resources != NULL) {
    pos += pb_write_attributes(encoded + pos, (const char **)data.resources, resources_num_pairs);
  }

  // Write TLS config if present
  if (data.tls_config != NULL) {
    // threadlocal.schema_version = schema_version string (e.g. "tlsdesc_v1_dev")
    if (data.tls_config->schema_version != NULL) {
      pos += pb_write_attribute_string(encoded + pos, "threadlocal.schema_version", data.tls_config->schema_version);
    }

    // threadlocal.max_record_size = <int>
    pos += pb_write_attribute_int(encoded + pos, "threadlocal.max_record_size", data.tls_config->max_record_size);

    // threadlocal.attribute_key_map = <array of strings> (position = key index)
    if (data.tls_config->attribute_key_map != NULL && tls_keymap_count > 0) {
      pos += pb_write_attribute_array_strings(encoded + pos, "threadlocal.attribute_key_map",
                                               (const char **)data.tls_config->attribute_key_map,
                                               tls_keymap_count);
    }
  }

  *out = (char *)encoded;
  *out_size = (uint32_t)total_size;

  return (otel_process_ctx_result) {.success = true, .error_message = NULL};
}

#ifndef OTEL_PROCESS_CTX_NO_READ
  #include <inttypes.h>
  #include <limits.h>
  #include <sys/uio.h>

  // Note: The below parsing code is only for otel_process_ctx_read and is only provided for debugging
  // and testing purposes.

  static void *parse_mapping_start(char *line) {
    char *endptr = NULL;
    unsigned long long start = strtoull(line, &endptr, 16);
    if (start == 0 || start == ULLONG_MAX) return NULL;
    return (void *)(uintptr_t) start;
  }

  static bool is_otel_process_ctx_mapping(char *line) {
    size_t line_len = strlen(line);
    if (line[line_len-1] == '\n') line[--line_len] = '\0';

    // Validate expected permissions (accept both old and new formats for backward compatibility)
    // Per PR #34: new mappings stay writable (rw-p or rw-s) for in-place updates
    // Accept both: r--p/r--s (old, read-only) and rw-p/rw-s (new, read-write)
    if (strstr(line, " r--p ") == NULL && strstr(line, " r--s ") == NULL &&
        strstr(line, " rw-p ") == NULL && strstr(line, " rw-s ") == NULL) {
      return false;
    }

    // Validate expected context size
    int64_t start, end;
    if (sscanf(line, "%" PRIx64 "-%" PRIx64, &start, &end) != 2) return false;
    if (start == 0 || end == 0 || end <= start) return false;
    if ((end - start) != size_for_mapping()) return false;

    // Check for memfd mapping: /memfd:OTEL_CTX (deleted) or similar
    if (strstr(line, "/memfd:OTEL_CTX") != NULL) {
      return true;
    }

    // Check for named anonymous mapping: [anon:OTEL_CTX]
    const char *anon_name = "[anon:OTEL_CTX]";
    size_t anon_name_len = strlen(anon_name);
    if (line_len >= anon_name_len && memcmp(line + (line_len - anon_name_len), anon_name, anon_name_len) == 0) {
      return true;
    }

    // Fallback: scan for OTEL_CTX signature in memory (for older kernels)
    void *addr = parse_mapping_start(line);
    if (addr == NULL) return false;

    // Read 8 bytes at the address using process_vm_readv (to avoid any issues with concurrency/races)
    char buffer[8];
    struct iovec local[] = {{.iov_base = buffer, .iov_len = sizeof(buffer)}};
    struct iovec remote[] = {{.iov_base = addr, .iov_len = sizeof(buffer)}};

    ssize_t bytes_read = process_vm_readv(getpid(), local, 1, remote, 1, 0);
    if (bytes_read != sizeof(buffer)) return false;

    return memcmp(buffer, "OTEL_CTX", sizeof(buffer)) == 0;
  }

  static otel_process_ctx_mapping *try_finding_mapping(void) {
    char line[8192];
    otel_process_ctx_mapping *result = NULL;

    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp) return result;

    while (fgets(line, sizeof(line), fp)) {
      if (is_otel_process_ctx_mapping(line)) {
        result = (otel_process_ctx_mapping *)parse_mapping_start(line);
        break;
      }
    }

    fclose(fp);
    return result;
  }

  // =============================================================================
  // Minimal Protobuf Decoder for OpenTelemetry Resource message (v2 spec)
  // =============================================================================

  // Read a varint from buffer, return bytes consumed (0 on error)
  static size_t pb_read_varint(const uint8_t *buf, size_t buf_len, uint64_t *out_value) {
    *out_value = 0;
    size_t bytes = 0;
    int shift = 0;
    while (bytes < buf_len && bytes < 10) {  // varints are at most 10 bytes
      uint8_t b = buf[bytes++];
      *out_value |= (uint64_t)(b & 0x7F) << shift;
      if ((b & 0x80) == 0) return bytes;
      shift += 7;
    }
    return 0;  // Error: varint too long or buffer overflow
  }

  // Decode a length-delimited string field, return bytes consumed (0 on error)
  // Allocates and null-terminates the string into *out_str
  static size_t pb_read_string(const uint8_t *buf, size_t buf_len, char **out_str) {
    uint64_t len;
    size_t varint_size = pb_read_varint(buf, buf_len, &len);
    if (varint_size == 0 || varint_size + len > buf_len) return 0;

    *out_str = (char *)calloc(len + 1, 1);
    if (!*out_str) return 0;
    memcpy(*out_str, buf + varint_size, len);
    (*out_str)[len] = '\0';

    return varint_size + len;
  }

  // Skip a length-delimited field, return bytes consumed (0 on error)
  static size_t pb_skip_length_delimited(const uint8_t *buf, size_t buf_len) {
    uint64_t len;
    size_t varint_size = pb_read_varint(buf, buf_len, &len);
    if (varint_size == 0 || varint_size + len > buf_len) return 0;
    return varint_size + len;
  }

  // Decode AnyValue message expecting string_value (field 1) or int_value (field 3)
  // For int_value, converts to string representation
  // For kvlist_value (field 6), returns "<kvlist>" placeholder
  // Returns the string (caller must free), or NULL on error
  static char *pb_decode_anyvalue(const uint8_t *buf, size_t buf_len) {
    size_t pos = 0;
    while (pos < buf_len) {
      uint64_t tag;
      size_t tag_size = pb_read_varint(buf + pos, buf_len - pos, &tag);
      if (tag_size == 0) return NULL;
      pos += tag_size;

      uint32_t field_num = (uint32_t)(tag >> 3);
      uint32_t wire_type = (uint32_t)(tag & 0x07);

      if (field_num == 1 && wire_type == 2) {
        // string_value (field 1, wire type 2 = length-delimited)
        char *value;
        size_t field_size = pb_read_string(buf + pos, buf_len - pos, &value);
        if (field_size == 0) return NULL;
        return value;
      } else if (field_num == 3 && wire_type == 0) {
        // int_value (field 3, wire type 0 = varint)
        uint64_t int_value;
        size_t varint_size = pb_read_varint(buf + pos, buf_len - pos, &int_value);
        if (varint_size == 0) return NULL;
        // Convert int to string
        char *str = (char *)calloc(32, 1);
        if (!str) return NULL;
        snprintf(str, 32, "%" PRId64, (int64_t)int_value);
        return str;
      } else if (field_num == 6 && wire_type == 2) {
        // kvlist_value (field 6, wire type 2 = length-delimited)
        // Skip the content but return a placeholder
        size_t skip = pb_skip_length_delimited(buf + pos, buf_len - pos);
        if (skip == 0) return NULL;
        char *placeholder = (char *)calloc(16, 1);
        if (!placeholder) return NULL;
        strcpy(placeholder, "<kvlist>");
        return placeholder;
      } else if (wire_type == 2) {
        // Skip other length-delimited fields
        size_t skip = pb_skip_length_delimited(buf + pos, buf_len - pos);
        if (skip == 0) return NULL;
        pos += skip;
      } else if (wire_type == 0) {
        // Skip varint fields
        uint64_t dummy;
        size_t skip = pb_read_varint(buf + pos, buf_len - pos, &dummy);
        if (skip == 0) return NULL;
        pos += skip;
      } else {
        // Unsupported wire type
        return NULL;
      }
    }
    return NULL;  // value not found
  }

  // Decode KeyValue message: field 1 = key (string), field 2 = value (AnyValue)
  // Returns true on success, fills key and value (caller must free)
  static bool pb_decode_keyvalue(const uint8_t *buf, size_t buf_len, char **out_key, char **out_value) {
    *out_key = NULL;
    *out_value = NULL;

    size_t pos = 0;
    while (pos < buf_len) {
      uint64_t tag;
      size_t tag_size = pb_read_varint(buf + pos, buf_len - pos, &tag);
      if (tag_size == 0) break;
      pos += tag_size;

      uint32_t field_num = (uint32_t)(tag >> 3);
      uint32_t wire_type = (uint32_t)(tag & 0x07);

      if (wire_type != 2) {
        // Skip non-length-delimited fields
        if (wire_type == 0) {
          uint64_t dummy;
          size_t skip = pb_read_varint(buf + pos, buf_len - pos, &dummy);
          if (skip == 0) goto error;
          pos += skip;
        } else {
          goto error;  // Unsupported wire type
        }
        continue;
      }

      // Read length
      uint64_t field_len;
      size_t len_size = pb_read_varint(buf + pos, buf_len - pos, &field_len);
      if (len_size == 0 || pos + len_size + field_len > buf_len) goto error;
      pos += len_size;

      if (field_num == 1) {
        // key (string)
        *out_key = (char *)calloc(field_len + 1, 1);
        if (!*out_key) goto error;
        memcpy(*out_key, buf + pos, field_len);
        (*out_key)[field_len] = '\0';
      } else if (field_num == 2) {
        // value (AnyValue message)
        *out_value = pb_decode_anyvalue(buf + pos, field_len);
        if (!*out_value) goto error;
      }
      pos += field_len;
    }

    if (*out_key && *out_value) return true;

  error:
    if (*out_key) { free(*out_key); *out_key = NULL; }
    if (*out_value) { free(*out_value); *out_value = NULL; }
    return false;
  }

  // Decode protobuf-encoded Resource message into otel_process_ctx_data
  static bool otel_process_ctx_decode_payload(const uint8_t *payload, size_t payload_size, otel_process_ctx_data *data_out) {
    // Initialize output data
    data_out->deployment_environment_name = NULL;
    data_out->host_name = NULL;
    data_out->service_instance_id = NULL;
    data_out->service_name = NULL;
    data_out->service_version = NULL;
    data_out->telemetry_sdk_language = NULL;
    data_out->telemetry_sdk_version = NULL;
    data_out->telemetry_sdk_name = NULL;
    data_out->resources = NULL;
    data_out->tls_config = NULL;  // TLS config is not decoded back (write-only)

    // Allocate resources array (estimate max 64 extra attributes)
    data_out->resources = (char **) calloc(128 + 1, sizeof(char *));
    if (!data_out->resources) return false;
    int resources_index = 0;

    size_t pos = 0;
    while (pos < payload_size) {
      uint64_t tag;
      size_t tag_size = pb_read_varint(payload + pos, payload_size - pos, &tag);
      if (tag_size == 0) break;
      pos += tag_size;

      uint32_t field_num = (uint32_t)(tag >> 3);
      uint32_t wire_type = (uint32_t)(tag & 0x07);

      if (field_num == 1 && wire_type == 2) {
        // attributes field (repeated KeyValue, field 1, wire type 2)
        uint64_t kv_len;
        size_t len_size = pb_read_varint(payload + pos, payload_size - pos, &kv_len);
        if (len_size == 0 || pos + len_size + kv_len > payload_size) return false;
        pos += len_size;

        char *key = NULL, *value = NULL;
        if (!pb_decode_keyvalue(payload + pos, kv_len, &key, &value)) {
          pos += kv_len;
          continue;  // Skip malformed KeyValue
        }
        pos += kv_len;

        // Assign to appropriate field based on key
        if (strcmp(key, "deployment.environment.name") == 0) {
          free(key); data_out->deployment_environment_name = value;
        } else if (strcmp(key, "host.name") == 0) {
          free(key); data_out->host_name = value;
        } else if (strcmp(key, "service.instance.id") == 0) {
          free(key); data_out->service_instance_id = value;
        } else if (strcmp(key, "service.name") == 0) {
          free(key); data_out->service_name = value;
        } else if (strcmp(key, "service.version") == 0) {
          free(key); data_out->service_version = value;
        } else if (strcmp(key, "telemetry.sdk.language") == 0) {
          free(key); data_out->telemetry_sdk_language = value;
        } else if (strcmp(key, "telemetry.sdk.version") == 0) {
          free(key); data_out->telemetry_sdk_version = value;
        } else if (strcmp(key, "telemetry.sdk.name") == 0) {
          free(key); data_out->telemetry_sdk_name = value;
        } else {
          // Unknown key, put into resources
          if (resources_index < 126) {  // Leave room for NULL terminator
            data_out->resources[resources_index++] = key;
            data_out->resources[resources_index++] = value;
          } else {
            free(key);
            free(value);
          }
        }
      } else if (wire_type == 2) {
        // Skip other length-delimited fields (e.g., dropped_attributes_count, entity_refs)
        size_t skip = pb_skip_length_delimited(payload + pos, payload_size - pos);
        if (skip == 0) return false;
        pos += skip;
      } else if (wire_type == 0) {
        // Skip varint fields
        uint64_t dummy;
        size_t skip = pb_read_varint(payload + pos, payload_size - pos, &dummy);
        if (skip == 0) return false;
        pos += skip;
      } else {
        // Unsupported wire type
        return false;
      }
    }

    // Verify all required fields were found
    return data_out->deployment_environment_name != NULL &&
           data_out->host_name != NULL &&
           data_out->service_instance_id != NULL &&
           data_out->service_name != NULL &&
           data_out->service_version != NULL &&
           data_out->telemetry_sdk_language != NULL &&
           data_out->telemetry_sdk_version != NULL &&
           data_out->telemetry_sdk_name != NULL;
  }

  void otel_process_ctx_read_data_drop(otel_process_ctx_data data) {
    if (data.deployment_environment_name) free(data.deployment_environment_name);
    if (data.host_name) free(data.host_name);
    if (data.service_instance_id) free(data.service_instance_id);
    if (data.service_name) free(data.service_name);
    if (data.service_version) free(data.service_version);
    if (data.telemetry_sdk_language) free(data.telemetry_sdk_language);
    if (data.telemetry_sdk_version) free(data.telemetry_sdk_version);
    if (data.telemetry_sdk_name) free(data.telemetry_sdk_name);
    if (data.resources) {
      for (int i = 0; data.resources[i] != NULL; i++) free(data.resources[i]);
      free(data.resources);
    }
    // Note: tls_config is not decoded back from payload (write-only), so it's always NULL here
    // But if we ever did decode it, we'd need to free attribute_key_map entries here
  }

  otel_process_ctx_read_result otel_process_ctx_read(void) {
    otel_process_ctx_mapping *mapping = try_finding_mapping();
    if (!mapping) {
      return (otel_process_ctx_read_result) {.success = false, .error_message = "No OTEL_CTX mapping found (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    // Validate signature
    if (strncmp(mapping->otel_process_ctx_signature, "OTEL_CTX", sizeof(mapping->otel_process_ctx_signature)) != 0) {
      return (otel_process_ctx_read_result) {.success = false, .error_message = "Invalid OTEL_CTX signature (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    // Check version (v2 required)
    if (mapping->otel_process_ctx_version != 2) {
      return (otel_process_ctx_read_result) {.success = false, .error_message = "Unsupported OTEL_CTX version (expected 2) (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    // Check published_at_ns (0 = update in progress, per v2 spec)
    uint64_t timestamp = __atomic_load_n(&mapping->published_at_ns, __ATOMIC_ACQUIRE);
    if (timestamp == 0) {
      return (otel_process_ctx_read_result) {.success = false, .error_message = "Context update in progress (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    otel_process_ctx_data data = empty_data;

    // Decode protobuf payload
    if (!otel_process_ctx_decode_payload((const uint8_t *)mapping->otel_process_payload,
                                         mapping->otel_process_payload_size, &data)) {
      otel_process_ctx_read_data_drop(data);
      return (otel_process_ctx_read_result) {.success = false, .error_message = "Failed to decode payload (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    // Re-check timestamp to detect concurrent update (per v2 spec reading protocol)
    uint64_t timestamp_after = __atomic_load_n(&mapping->published_at_ns, __ATOMIC_ACQUIRE);
    if (timestamp_after != timestamp) {
      otel_process_ctx_read_data_drop(data);
      return (otel_process_ctx_read_result) {.success = false, .error_message = "Context changed during read (" __FILE__ ":" ADD_QUOTES(__LINE__) ")", .data = empty_data};
    }

    return (otel_process_ctx_read_result) {.success = true, .error_message = NULL, .data = data};
  }

  bool otel_process_ctx_read_drop(otel_process_ctx_read_result *result) {
    if (!result || !result->success) return false;

    // Free allocated strings in the data
    otel_process_ctx_read_data_drop(result->data);

    // Reset the result to empty state
    *result = (otel_process_ctx_read_result) {.success = false, .error_message = "Data dropped", .data = empty_data};

    return true;
  }
#endif // OTEL_PROCESS_CTX_NO_READ

#endif // OTEL_PROCESS_CTX_NOOP
