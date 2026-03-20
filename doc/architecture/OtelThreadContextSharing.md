# OTel Thread Context Sharing — Architecture & Alignment Document

## Purpose

This document tracks the alignment between the java-profiler's OTel context storage
implementation (branch `jb/otel_ctx`) and the **OTEP specification** which is the
single source of truth.

**Single Source of Truth:**
- [OTEP #4947: Thread Context](https://github.com/open-telemetry/opentelemetry-specification/pull/4947) — the thread-level context spec
- [OTEP #4719: Process Context](https://github.com/open-telemetry/opentelemetry-specification/pull/4719) — the process-level context spec (dependency of #4947)

**Reference implementation** (informational, not normative):
- [opentelemetry-ebpf-profiler PR #1229](https://github.com/open-telemetry/opentelemetry-ebpf-profiler/pull/1229)
- [ctx-sharing-demo](https://github.com/scottgerring/ctx-sharing-demo)

**Prior art cited by the OTEP:**
- [Elastic Universal Profiling Integration](https://github.com/elastic/apm/blob/149cd3e39a77a58002344270ed2ad35357bdd02d/specs/agents/universal-profiling-integration.md)
- [Polar Signals Custom Labels v1](https://github.com/polarsignals/custom-labels/blob/master/custom-labels-v1.md)
- [Datadog java-profiler ContextSetter](https://github.com/DataDog/java-profiler/blob/main/ddprof-lib/src/main/java/com/datadoghq/profiler/ContextSetter.java) (our existing shared-hashmap approach)

Last updated: 2026-03-20

---

## 1. OTEP Specification Summary

The OTEP defines two complementary mechanisms. Both are required for a conforming implementation.

### 1.1 Thread Local Context (OTEP #4947)

#### TLS Variable

A **TLSDESC** thread-local pointer named `custom_labels_current_set_v2` (working name).

- The pointer MUST appear in the **dynamic symbol table** (`dynsym`) of either the
  process binary or a shared library loaded by the process.
- The pointer points to a **Thread Local Context Record** (or is NULL when no context
  is active).
- For Java: the OTEP says "Full support. Requires calling into native library (e.g. via
  JNI or equivalent API)."

#### Thread Local Context Record Layout

28-byte fixed header + up to 612 bytes of attribute data (640 bytes total fixed allocation):

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0x00 | 16 | `trace_id` | `uint8[16]` — W3C 128-bit trace ID. Zeroes = none active. |
| 0x10 | 8 | `span_id` | `uint8[8]` — 64-bit span ID. |
| 0x18 | 1 | `valid` | `uint8` — 1 = record valid, any other value = ignore. |
| 0x19 | 1 | `_reserved` | Alignment padding. |
| 0x1A | 2 | `attrs_data_size` | `uint16` — byte size of following `attrs_data`. |
| 0x1C | N | `attrs_data` | Variable-length attribute KV pairs. |

Each attribute in `attrs_data`:

| Field | Size | Description |
|-------|------|-------------|
| `key` | 1 byte (`uint8`) | Index into process context's `attribute_key_map` |
| `length` | 1 byte (`uint8`) | Length of value string |
| `val` | `length` bytes | UTF-8 encoded value |

Recommended total record size: ≤ 640 bytes.

**Key semantics from the OTEP:**
- The `valid` flag means "this record is complete and ready for reading" — it is **not**
  a torn-read guard. The OTEP's consistency model relies on pointer-swapping: the TLS
  pointer is set to NULL before constructing a new record, then pointed at the completed
  record. A reader seeing a non-NULL pointer with `valid == 1` has a consistent snapshot.
- The `valid` field can alternatively be used to mark a record as "under modification"
  without detaching the pointer entirely (for record reuse scenarios).
- Memory barriers are required on pointer and `valid` field updates.

#### Publication Protocol (Writer — SDK Side)

**Process init:**
1. Publish `threadlocal.schema_version` and `threadlocal.attribute_key_map` to the
   Process Context (OTEP #4719).

**Context attachment (span activation on a thread):**
1. Set TLS pointer to 0 (NULL) — readers see no record during construction.
2. Obtain a buffer for the record.
3. Construct the Thread Local Context Record (trace_id, span_id, attributes).
4. Set `valid = 1`.
5. Update TLS pointer to the new record (with memory barrier).

**Context detachment:**
1. Set TLS pointer to NULL.

**Record reuse:** SDKs may cache/reuse record buffers. The `valid` field can be used
to mark in-progress modifications without NULLing the pointer.

#### Reading Protocol (Reader — External Profiler)

**Process discovery:**
1. Read Process Context (OTEP #4719) to obtain `threadlocal.schema_version` and
   `threadlocal.attribute_key_map`.
2. Scan process binary and loaded libraries for `custom_labels_current_set_v2` in
   `dynsym` table. Record the TLS offset.

**Thread sampling:**
1. Resolve TLS pointer for the target thread (TSD base + TLS offset).
2. If pointer is NULL → no active context, done.
3. Read the 28-byte header from the pointer address, then read `attrs_data_size` additional bytes for attribute data.
4. Check `valid == 1`. If not, ignore.
5. If `attrs_data_size > 0`, read `attrs_data_size` bytes from offset 28.
6. Parse attributes using the `attribute_key_map`.

### 1.2 Process Context (OTEP #4719)

#### Discovery

Parse `/proc/<pid>/maps`, look for entries with name **starting with**:
- `[anon_shmem:OTEL_CTX]` — memfd + prctl succeeded
- `[anon:OTEL_CTX]` — memfd failed, prctl succeeded
- `/memfd:OTEL_CTX` — memfd succeeded, prctl failed

#### Header Layout (32 bytes)

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0x00 | 8 | `signature` | `char[8]` — always `"OTEL_CTX"` |
| 0x08 | 4 | `version` | `uint32` — currently `2` (use `1` for dev) |
| 0x0C | 4 | `payload_size` | `uint32` — protobuf payload size in bytes |
| 0x10 | 8 | `monotonic_published_at_ns` | `uint64` — `CLOCK_BOOTTIME` timestamp; 0 = mutation in progress |
| 0x18 | 8 | `payload` | `uint64` — pointer to protobuf payload (in publisher's address space) |

#### Protobuf Payload

```protobuf
syntax = "proto3";
package opentelemetry.proto.common.v1;

message ProcessContext {
  opentelemetry.proto.resource.v1.Resource resource = 1;
  repeated opentelemetry.proto.common.v1.KeyValue extra_attributes = 2;
}
```

`extra_attributes` carries thread context reference data:

```yaml
key: "threadlocal.schema_version"
value:
  string_value: "tlsdesc_v1_dev"

key: "threadlocal.attribute_key_map"
value:
  array_value:
    values:
      - string_value: "http_route"   # index 0
      - string_value: "http_method"  # index 1
```

#### Publication Protocol

1. `memfd_create("OTEL_CTX", MFD_CLOEXEC | MFD_ALLOW_SEALING | MFD_NOEXEC_SEAL)` + `ftruncate`.
   Retry without `MFD_NOEXEC_SEAL` on failure.
2. `mmap(PROT_READ | PROT_WRITE, MAP_PRIVATE, memfd)`, close memfd.
3. Fallback: `mmap(MAP_PRIVATE | MAP_ANONYMOUS)` if memfd unavailable.
4. `madvise(MADV_DONTFORK)`.
5. Write header fields (signature, version, payload_size, payload ptr) but NOT timestamp.
6. Memory barrier.
7. Write `monotonic_published_at_ns` last.
8. `prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, ..., "OTEL_CTX")` unconditionally.

#### Reading Protocol (Seqlock)

1. Locate mapping via `/proc/<pid>/maps`.
2. Validate signature (`"OTEL_CTX"`) and version (`2`).
3. Read `monotonic_published_at_ns` — if 0, retry.
4. Memory barrier (`atomic_thread_fence(memory_order_seq_cst)`).
5. Read payload pointer and size, copy payload.
6. Memory barrier.
7. Re-read `monotonic_published_at_ns` — if changed, restart.
8. Decode protobuf.

#### Update Protocol

1. Write 0 to `monotonic_published_at_ns`.
2. Barrier.
3. Update payload pointer and size.
4. Barrier.
5. Write new (different) timestamp.
6. Re-issue `prctl` naming.

---

## 2. Current Implementation Summary (branch `jb/otel_ctx`)

### 2.1 Architecture

Uses an **OTEP #4947-compliant TLS pointer** (`custom_labels_current_set_v2`):

- `OtelThreadContextRecord` (640 bytes, packed): 28-byte header (trace_id[16], span_id[8], valid, _reserved, attrs_data_size) + attrs_data[612]
- TLS pointer exported in `dynsym` for external profiler discovery
- Per-thread record allocated on first `ContextApi::set()` and cached in `ProfiledThread`
- Signal-safe reads via `ProfiledThread::getOtelContextRecord()` (never accesses TLS directly)

### 2.2 Consistency Model

Uses OTEP pointer-swapping protocol:
- Writer: set TLS pointer to NULL → set valid=0 → populate record → set valid=1 → set TLS pointer to record
- Reader: read via ProfiledThread cached pointer, check valid == 1

### 2.3 API Layers

- `ContextApi` — unified C++ abstraction routing to profiler-mode TLS or OTEL TLS pointer
- `OtelContexts` — OTEP #4947 TLS pointer implementation
- JNI bridge: `setContext0`, `getContext0`, `isOtelMode0`
- Java: `ThreadContext` with mode-aware getters

### 2.4 Implemented (Phase 1)

- `__thread` TLS pointer `custom_labels_current_set_v2` in `dynsym`
- `OtelThreadContextRecord` matching OTEP layout (640 bytes packed: 28-byte header + 612 bytes attrs_data)
- OTEP publication protocol (pointer-swap with memory barriers)
- Byte-level trace_id/span_id encoding (big-endian, W3C trace context)
- Per-thread custom attributes via `attrs_data` (key_index + length + UTF-8 value encoding)
- Attribute key registration via `ContextApi::registerAttributeKeys()`

### 2.5 JFR Tag Encoding Sidecar

`ProfiledThread` caches pre-computed Dictionary encodings (`_otel_tag_encodings[]`) and
`_otel_local_root_span_id` alongside the OTEP record. The JNI write path populates both
the OTEP `attrs_data` (raw strings for external profilers) and the sidecar (u32 encodings
for the JFR writer). Signal handlers read only the sidecar -- O(1) array index, no
string lookups or hash-table probes per sample.

---

## 3. Gap Analysis: Current vs OTEP Specification

### 3.1 RESOLVED — Storage Mechanism (Phase 1)

| OTEP Requirement | Current Implementation | Status |
|------------------|----------------------|--------|
| `__thread` pointer (`custom_labels_current_set_v2`) in `dynsym` | TLS pointer exported via `DLLEXPORT` | **Done** |
| TLS pointer → Thread Local Context Record | Per-thread record cached in ProfiledThread | **Done** |
| TLSDESC dialect for efficient TLS access | Standard `thread_local` (compiler selects TLSDESC on supported platforms) | **Done** |
| External profilers discover via ELF symbol table | `custom_labels_current_set_v2` in `dynsym` | **Done** |

### 3.2 RESOLVED — Thread Local Context Record Layout (Phase 1)

| OTEP Field | OTEP Layout | Current Layout | Status |
|------------|-------------|----------------|--------|
| `trace_id` | `uint8[16]` packed | `uint8[16]` packed | **Done** |
| `span_id` | `uint8[8]` packed | `uint8[8]` packed | **Done** |
| `valid` | `uint8` — "record is ready" | `uint8` valid — same semantics | **Done** |
| `_reserved` | 1 byte | 1 byte | **Done** |
| `attrs_data_size` | `uint16` | `uint16` — number of valid bytes in attrs_data | **Done** |
| `attrs_data[]` | Variable-length KV pairs | `uint8[612]` with key_index+length+value encoding | **Done** (Phase 3) |
| Total fixed size | ≤ 640 bytes (packed) | 640 bytes (28-byte header + 612 bytes attrs_data) | **Done** |

### 3.3 RESOLVED — Consistency Protocol (Phase 1)

| OTEP Protocol | Current Protocol | Status |
|---------------|-----------------|--------|
| NULL TLS pointer during record construction | Pointer set to NULL before record update | **Done** |
| `valid` field for record completeness | `valid = 1` when record is ready | **Done** |
| Pointer swap (atomic pointer update) | Atomic store with release barrier | **Done** |
| Reader checks pointer then `valid` | Reads via ProfiledThread cached pointer + valid check | **Done** |

### 3.4 PARTIALLY RESOLVED — Process Context (OTEP #4719)

| OTEP Requirement | Status |
|------------------|--------|
| `OTEL_CTX` region via memfd/anon | **Done** — via Rust-based `otel_process_ctx` library |
| 32-byte header with signature, version, timestamp seqlock | **Done** — handled by `otel_process_ctx` |
| Protobuf `ProcessContext` payload | **Done** — serialized by `otel_process_ctx` |
| `threadlocal.schema_version` in extra_attributes | **Done** — published via `thread_ctx_config` |
| `threadlocal.attribute_key_map` in extra_attributes | **Done** — published via `thread_ctx_config` |
| Publication via memfd_create + prctl | **Done** — handled by `otel_process_ctx` |
| `MADV_DONTFORK` | Handled by `otel_process_ctx` |
| Seqlock read protocol (timestamp-based) | Handled by `otel_process_ctx` |

### 3.5 RESOLVED — Custom Attributes (Phase 3)

| OTEP Requirement | Status |
|------------------|--------|
| `attrs_data[]` with key-index encoding | **Done** — `OtelContexts::setAttribute()` |
| Key index → attribute name mapping via process context | **Done** — `ContextApi::registerAttributeKeys()` publishes `thread_ctx_config` |
| Recommended ≤ 640 bytes total record | **Done** — 640-byte fixed struct |
| UTF-8 string values | **Done** — values stored as raw UTF-8 bytes |

### 3.6 PARTIALLY RESOLVED — Naming

| Item | OTEP | Current | Status |
|------|------|---------|--------|
| TLS symbol name | `custom_labels_current_set_v2` | `custom_labels_current_set_v2` | **Done** |
| Process context region | `OTEL_CTX` | Handled by `otel_process_ctx` library | **Done** |
| Schema version | `tlsdesc_v1_dev` | Published via `thread_ctx_config` | **Done** (Phase 3) |
| Ring buffer region | N/A (not in spec) | Removed | **Done** |

---

## 4. Required Changes

### Phase 1: Thread Local Context (Core OTel Compatibility) — DONE

**Goal:** An OTel eBPF profiler can discover and read our trace_id + span_id.

1. **`__thread` TLS pointer** `custom_labels_current_set_v2` — exported in `dynsym` via `DLLEXPORT`
2. **`OtelThreadContextRecord`** — 640-byte packed struct matching OTEP layout (28-byte header + 612 bytes attrs_data)
3. **OTEP publication protocol** — pointer-swap with memory barriers
4. **`ContextApi` routing** — TLS init with `SignalBlocker`, record cached in `ProfiledThread`
5. **Ring buffer removed** — replaced by per-thread record pointer cached in `ProfiledThread`.
   Cross-thread reads use `ProfiledThread::getOtelContextRecord()`.

### Phase 2: Process Context (OTEP #4719) -- DONE

**Goal:** External profiler can discover schema version and attribute key map.

6. **OTEP #4719 process context region** -- implemented via C-based `otel_process_ctx` library
   (derived from upstream sig-profiling reference implementation):
   - `memfd_create("OTEL_CTX", ...)` with fallback to anonymous mmap
   - 32-byte header: signature `"OTEL_CTX"`, version `2`, payload_size,
     monotonic_published_at_ns, payload pointer
   - `madvise(MADV_DONTFORK)`, `prctl(PR_SET_VMA, ...)`

7. **Protobuf support** -- hand-rolled minimal encoder/decoder in `otel_process_ctx.cpp`.
   Serializes `ProcessContext` with `extra_attributes`:
   - `threadlocal.schema_version` = `"tlsdesc_v1_dev"`
   - `threadlocal.attribute_key_map` = registered key names

8. **Seqlock update protocol** -- implemented (timestamp-based, see `otel_process_ctx_update`).

### Phase 3: Custom Attributes — DONE

**Goal:** SDK can publish per-thread attributes like http_route.

9. **Attribute key registration API:**
   - `OTelContext.registerAttributeKeys()` → `ContextApi::registerAttributeKeys()`
   - Publishes `attribute_key_map` via `thread_ctx_config` in process context
   - Re-publishes process context with `schema_version = "tlsdesc_v1_dev"`

10. **Extended record with `attrs_data`:**
    - Key-index + length + value encoding per OTEP
    - 640-byte fixed record (28-byte header + 612 bytes attrs_data)
    - `ThreadContext.setContextAttribute()` writes to OTEP record in OTEL mode
    - JFR recording decodes attrs_data via Dictionary for constant pool encoding

### Items Removed (Phase 1)

11. **`DD_OTEL_CTX` mmap region:** Removed — replaced by TLS pointer.
12. **`OtelContextHeader` / `OtelContextSlot`:** Removed — replaced by `OtelThreadContextRecord`.
13. **`in_use` flag:** Removed — replaced by OTEP's `valid` semantics + pointer-swapping.

---

## 5. Open Questions

1. ~~**Ring buffer for cross-thread reads:**~~ **Resolved.** Ring buffer removed.
   Cross-thread reads use `ProfiledThread`'s cached record pointer. No TSD base
   resolution needed.

2. ~~**Protobuf in native agent:**~~ **Resolved.** Hand-rolled minimal protobuf
   encoder/decoder in `otel_process_ctx.cpp` (derived from upstream C reference impl).

3. ~~**Record allocation strategy:**~~ **Resolved.** One `OtelThreadContextRecord` per
   thread, allocated on first `ContextApi::set()`, cached in `ProfiledThread`, reused
   across span activations.

4. **Schema version:** `tlsdesc_v1_dev` has `_dev` suffix — will change to
   `tlsdesc_v1` when the OTEP merges.

5. **OTEP dependency:** Both OTEPs (#4947, #4719) are still open PRs.

6. ~~**TLS pointer in signal handlers:**~~ **Resolved.** Signal handlers read via
   `ProfiledThread::getOtelContextRecord()`, never accessing `custom_labels_current_set_v2`
   directly. TLS first-access is protected by `SignalBlocker`.

7. **`custom_labels_current_set_v2` name stability:** The OTEP calls this a "working
   name". It may change before the spec finalizes.

---

## 6. Relationship Between OTEP #4947, PR #1229, and the Google Doc

| Source | Role | Notes |
|--------|------|-------|
| [OTEP #4947](https://github.com/open-telemetry/opentelemetry-specification/pull/4947) | **Normative spec** — single source of truth | Opened 2026-03-16, no reviews yet |
| [OTEP #4719](https://github.com/open-telemetry/opentelemetry-specification/pull/4719) | **Normative spec** — process context (dependency) | Also open |
| [PR #1229](https://github.com/open-telemetry/opentelemetry-ebpf-profiler/pull/1229) | Reference implementation in OTel eBPF Profiler | May diverge from OTEP; some review comments suggest changes |
| [Google Doc](https://docs.google.com/document/d/1eatbHpEXXhWZEPrXZpfR58-5RIx-81mUgF69Zpn3Rz4) | Earlier draft / working document | Superseded by OTEP #4947 |
| [ctx-sharing-demo](https://github.com/scottgerring/ctx-sharing-demo) | Demo writers/readers based on PolarSignals custom-labels | Useful for testing interop |

Where OTEP #4947 and PR #1229 disagree, follow the OTEP.

---

## 7. External References

| Resource | URL |
|----------|-----|
| **OTEP #4947** (Thread Context) | https://github.com/open-telemetry/opentelemetry-specification/pull/4947 |
| **OTEP #4719** (Process Context) | https://github.com/open-telemetry/opentelemetry-specification/pull/4719 |
| eBPF Profiler PR #1229 | https://github.com/open-telemetry/opentelemetry-ebpf-profiler/pull/1229 |
| ctx-sharing-demo | https://github.com/scottgerring/ctx-sharing-demo |
| PolarSignals custom-labels | https://github.com/polarsignals/custom-labels |
| PolarSignals custom-labels v1 spec | https://github.com/polarsignals/custom-labels/blob/master/custom-labels-v1.md |
| Elastic Universal Profiling | https://github.com/elastic/apm/blob/149cd3e39a77a58002344270ed2ad35357bdd02d/specs/agents/universal-profiling-integration.md |
| OTEP #212 (Profiling Vision) | https://github.com/open-telemetry/opentelemetry-specification/blob/main/oteps/profiles/0212-profiling-vision.md |
| OTEP #239 (Profiles Data Model) | https://github.com/open-telemetry/opentelemetry-specification/blob/main/oteps/profiles/0239-profiles-data-model.md |
| TLSDESC RFC | https://www.fsfla.org/~lxoliva/writeups/TLS/RFC-TLSDESC-x86.txt |
| OTel eBPF Profiler custom-labels design | https://github.com/open-telemetry/opentelemetry-ebpf-profiler/tree/main/design-docs/00002-custom-labels |

---

## 8. Decision Log

| Date | Decision | Rationale |
|------|----------|-----------|
| 2026-03-19 | Adopt OTEP #4947 as single source of truth | OTEP is the normative spec; PR #1229 is a reference impl that may diverge |
| 2026-03-19 | Created architecture doc | Track alignment and plan incremental convergence |
| 2026-03-19 | Phase 1: Replace ring buffer with OTEP-compliant TLS pointer | Ring buffer was aligned with earlier draft spec; OTEP evolved to TLS pointer model |
