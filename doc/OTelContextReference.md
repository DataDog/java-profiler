# OpenTelemetry Context Reference Implementation

## Overview

The reference implementation for the OpenTelemetry context sharing specification is maintained in the `ctx-sharing-demo` repository. This document provides quick instructions for setting up and using the reference implementation to validate Java profiler integration.

## Repository Location

The reference implementation is located at:
```
~/dd/ctx-sharing-demo
```

## Quick Start

### 1. Build the Reference Implementation

```bash
cd ~/dd/ctx-sharing-demo
cargo build --release
```

This builds:
- `context-reader`: Tools for reading and validating OTEL context from running processes
- `custom-labels`: Rust library implementing the OTEL context specification
- `simple-writer`: Minimal C implementations for testing

### 2. Validate Java Process Context

Start a Java application that publishes OTEL context (e.g., demo-java):

```bash
# In one terminal - run your Java app with OTEL context
java -javaagent:ddprof.jar -jar your-app.jar
```

In another terminal, validate the context:

```bash
cd ~/dd/ctx-sharing-demo/context-reader

# Find your Java process
jps -l

# Validate context reading (replace <pid> with actual PID)
sudo ./target/release/validate <pid>
```

Expected output on success:
```
VALIDATE OK: [v2] thread=12345, labels=[trace_id=..., span_id=..., ...]
```

### 3. Read Context Continuously

To continuously read and display context from a running process:

```bash
sudo ./target/release/tail <pid>
```

This will sample the process periodically and display any active tracing context.

## Key Specification Files

### Process Context Format

**Header Structure** (`custom-labels/src/process_context/model.rs`):
```rust
pub const SIGNATURE: &[u8; 8] = b"OTEL_CTX";
pub const PROCESS_CTX_VERSION: u32 = 2;
```

**Discovery** (`custom-labels/src/process_context/reader.rs`):
- Memfd: `/memfd:OTEL_CTX` in `/proc/<pid>/maps`
- Anonymous: `[anon:OTEL_CTX]` in `/proc/<pid>/maps`
- Signature scan: Search for `OTEL_CTX` signature bytes

**Payload Encoding** (`custom-labels/src/process_context/encoding.rs`):
- Protobuf `opentelemetry.proto.resource.v1.Resource` message
- Required fields for TLS config:
  - `threadlocal.schema_version` = `"tlsdesc_v1_dev"` (String)
  - `threadlocal.max_record_size` = int64
  - `threadlocal.attribute_key_map` = Array of strings (position = key index)

### TLS Record Format (V2)

**Schema** (`custom-labels/src/customlabels_v2.h`):
```c
typedef struct {
    uint8_t trace_id[16];       // bytes 0-15 (network order)
    uint8_t span_id[8];         // bytes 16-23 (network order)
    uint8_t valid;              // byte 24 (non-zero if valid)
    uint8_t _padding;           // byte 25 (padding)
    uint16_t attrs_data_size;   // bytes 26-27 (little-endian)
    uint8_t attrs_data[];       // bytes 28+ (attributes)
} custom_labels_v2_tl_record_t;
```

**Header size**: 28 bytes

**Discovery Symbol** (`context-reader/src/v2_reader.rs`):
```
custom_labels_current_set_v2
```

Thread-local pointer to the current V2 record, or NULL if no context is set.

## Simple C Writer Example

For quick prototyping, see `simple-writer/process_context.c`:

```bash
cd ~/dd/ctx-sharing-demo/simple-writer
make
./writer_v2  # Publishes process context and waits
```

In another terminal:
```bash
# Read the context back
./reader_v2
```

## Key Implementation Points

### Process Context

1. **Mapping Permissions**: Use `rw-p` (anonymous) or `rw-s` (memfd)
   - Do NOT use `mprotect()` to make read-only
   - Writable mappings allow in-place updates (PR #34)

2. **Mapping Size**: 1 page (new) or 2 pages (old, deprecated)
   ```c
   long page_size = sysconf(_SC_PAGESIZE);
   size_t mapping_size = page_size;  // Use 1 page
   ```

3. **Update Protocol** (PR #34):
   - Set `published_at_ns = 0` (signals update in progress)
   - Memory fence
   - Update payload pointer and size
   - Memory fence
   - Set `published_at_ns = <timestamp>` (signals complete)

### TLS Records

1. **Trace/Span IDs**: Network byte order (big-endian)
   ```c
   // Write as big-endian bytes
   record->trace_id[0] = (trace_id >> 56) & 0xFF;
   record->trace_id[1] = (trace_id >> 48) & 0xFF;
   // ... etc
   ```

2. **Attributes**: `[key_index:1][length:1][value:length]` format
   - Key index references position in `attribute_key_map` array
   - Length and value follow immediately

3. **Thread Safety**: Use atomic operations for `valid` flag
   ```c
   record->valid = 0;           // Clear first
   __atomic_thread_fence(__ATOMIC_SEQ_CST);
   // ... write data ...
   __atomic_thread_fence(__ATOMIC_SEQ_CST);
   record->valid = 1;           // Set last
   ```

## Validation Modes

### Ptrace Mode (Default)

Attaches to the process using ptrace to read TLS:
```bash
sudo ./target/release/validate <pid>
```

More compatible but higher overhead.

### eBPF Mode

Uses eBPF probes for lower overhead:
```bash
sudo ./target/release/validate <pid> --mode ebpf
```

Requires kernel 5.2+ with BTF support.

## Common Issues

### "No process-context found"

**Cause**: Process context mapping not discoverable

**Check**:
```bash
cat /proc/<pid>/maps | grep -E "OTEL_CTX|rw.s.*memfd"
```

**Expected**: Should see `/memfd:OTEL_CTX` or `[anon:OTEL_CTX]` mapping

**Fix**: Ensure `otel_process_ctx_publish()` is called with valid TLS config

### "No TLS readers could be initialized"

**Cause**: Neither V1 nor V2 TLS symbols found in process

**Check**:
```bash
nm -D /path/to/libjavaProfiler.so | grep custom_labels
```

**Expected**: Should see `custom_labels_current_set_v2`

**Fix**: Ensure the profiler library is loaded and exports the TLS symbol

### "Invalid signature"

**Cause**: Signature mismatch or wrong struct layout

**Check**: Verify header structure matches exactly:
- Signature at offset 0 (8 bytes = "OTEL_CTX")
- Version at offset 8 (4 bytes = 2)
- Use `__attribute__((packed))` in C/C++

### Permission Errors

The validator requires root or CAP_SYS_PTRACE to read from other processes:

```bash
# Option 1: Run as root
sudo ./target/release/validate <pid>

# Option 2: Grant capabilities
sudo setcap cap_sys_ptrace+ep ./target/release/validate
./target/release/validate <pid>
```

## Additional Resources

- **Specification Changes**: Check git log in `custom-labels/src/process_context/`
- **Test Cases**: See `custom-labels/src/process_context/tests.rs` and `custom-labels/src/v2/tests.rs`
- **Integration Examples**:
  - Java: `demo-java/`
  - C: `simple-writer/`
  - Rust: `custom-labels/examples/`

## Updating to Latest Specification

```bash
cd ~/dd/ctx-sharing-demo
git pull
cargo build --release
```

Always rebuild both the reference implementation and the Java profiler after specification updates to ensure compatibility.
