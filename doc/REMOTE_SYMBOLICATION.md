# Remote Symbolication Implementation

This document describes the implementation of build-id and pc/offset storage in native frames for remote symbolication in the Java profiler.

## Overview

The enhancement allows the Java profiler to store raw build-id and PC offset information for native frames instead of resolving symbols locally. This enables remote symbolication services to handle symbol resolution, which is especially useful for:

- Distributed profiling scenarios where symbol files aren't available locally
- Reduced profiler overhead by deferring symbol resolution
- Better support for stripped binaries
- Centralized symbol management

## Implementation Summary

### 1. **Build-ID Extraction** (`symbols_linux_dd.h/cpp`)

- **SymbolsLinux**: Utility class to extract GNU build-id from ELF files
- Supports both file-based and memory-based extraction
- Handles .note.gnu.build-id section parsing
- Returns hex-encoded build-id strings

### 2. **Enhanced CodeCache** (`codeCache.h/cpp`)

Added fields to store build-id information:
- `_build_id`: Hex-encoded build-id string
- `_build_id_len`: Raw build-id length in bytes
- `_load_bias`: Load bias for address calculations
- Methods: `hasBuildId()`, `buildId()`, `setBuildId()`, etc.

### 3. **Remote Frame Information** (`vmEntry.h`)

- **RemoteFrameInfo**: New structure containing:
  - `build_id`: Library build-id
  - `pc_offset`: PC offset within library
  - `lib_index`: Library table index
- **BCI_NATIVE_FRAME_REMOTE**: New frame encoding (-19)

### 4. **Enhanced Frame Collection** (`profiler.cpp`, `stackWalker_dd.h`)

Modified frame collection to support dual modes:
- **Traditional mode**: Stores resolved symbol names (existing behavior)
- **Remote mode**: Stores RemoteFrameInfo with build-id and offset

**Key Functions**:
- `resolveNativeFrame()`: Determines whether to use local or remote symbolication for a given PC
- `resolveNativeFrameForWalkVM()`: Helper for walkVM integration, wraps resolveNativeFrame()
- `allocateRemoteFrameInfo()`: Allocates from pre-allocated signal-safe pool (per lock-strip)
- `convertNativeTrace()`: Converts raw PCs to frames for walkFP/walkDwarf modes

**Stack Walker Integration**:
- **walkFP/walkDwarf**: Return raw PCs → `convertNativeTrace()` → `resolveNativeFrame()`
- **walkVM/walkVMX**: Directly call `resolveNativeFrameForWalkVM(pc, lock_index)` at native frame resolution (patched via gradle/patching.gradle)

### 5. **JFR Serialization** (`flightRecorder.cpp/h`)

- **fillRemoteFrameInfo()**: Serializes remote frame data to JFR format
- Stores `<build-id>.<remote>` in class name field (e.g., `deadbeef1234567890abcdef.<remote>`)
- Stores PC offset in signature field (e.g., `(0x1234)`)
- Uses modifier flag 0x100 (ACC_NATIVE, same as regular native frames)

### 6. **Configuration** (`arguments.h/cpp`)

- **remotesym[=BOOL]**: New profiler argument
- Default: disabled
- Can be enabled with `remotesym=true` or `remotesym=y`

### 7. **Libraries Integration** (`libraries.h/cpp`)

- **updateBuildIds()**: Extracts build-ids for all loaded libraries
- Called during profiler startup when remote symbolication is enabled
- Linux-only implementation using ELF parsing

### 8. **Upstream Stack Walker Integration** (`gradle/patching.gradle`)

Patches async-profiler's `stackWalker.h` and `stackWalker.cpp` to integrate remote symbolication:

**Header Patches (stackWalker.h)**:
- Adds `lock_index` parameter to all three `walkVM` signatures (private implementation, public with features, public with anchor)
- Enables per-strip RemoteFrameInfo pool access during stack walking

**Implementation Patches (stackWalker.cpp)**:
- Updates all `walkVM` signatures to accept and propagate `lock_index`
- **Critical patch at line 454**: Replaces `profiler->findNativeMethod(pc)` with `profiler->resolveNativeFrameForWalkVM(pc, lock_index)`
- Adds dynamic BCI selection (BCI_NATIVE_FRAME vs BCI_NATIVE_FRAME_REMOTE)
- Adds `fillFrame()` overload for void* method_id to support both symbol names and RemoteFrameInfo pointers
- Handles marked C++ interpreter frames (terminates scan if detected)

## Usage

### Enable Remote Symbolication

```bash
java -agentpath:<path_to>/libjavaProfiler.so=start,cpu,remotesym=true,file=profile.jfr MyApp
```

### Mixed Configuration

```bash
java -agentpath:<path_to>/libjavaProfiler.so=start,event=cpu,interval=1000000,remotesym=true,file=profile.jfr MyApp
```

## JFR Output Format

When remote symbolication is enabled, native frames in the JFR output contain:

- **Class Name**: `<build-id>.<remote>` (e.g., `deadbeef1234567890abcdef.<remote>`)
  - Build-ID hex string followed by `.<remote>` suffix for constant pool deduplication
- **Signature**: PC offset (e.g., `(0x1234)`)
- **Method Name**: The `<remote>` suffix from the class name indicates remote symbolication is needed
- **Modifier**: `0x100` (ACC_NATIVE, same as regular native frames)
- **Frame Type**: `FRAME_NATIVE_REMOTE` (7) - distinguishes from regular native frames

## Backward Compatibility

- **Default behavior**: No changes (remote symbolication disabled)
- **Mixed traces**: Supports both local and remote frames in same trace
- **Fallback**: Gracefully falls back to local symbolication when build-id unavailable

## Memory Management

- **Build-IDs**: Stored once per CodeCache, shared across frames (hex string allocated with malloc)
- **RemoteFrameInfo**: Pre-allocated pool per lock-strip (128 entries × CONCURRENCY_LEVEL strips = ~32KB total)
  - Signal-safe allocation using atomic counters
  - No dynamic allocation in signal handlers
  - Pool resets on profiler restart
- **Automatic cleanup**: Handled by CallTrace storage lifecycle

## Testing

### Unit Tests
- **remotesymbolication_ut.cpp**: Tests RemoteFrameInfo structure and build-id extraction
- **remoteargs_ut.cpp**: Tests argument parsing for remote symbolication option

### Test Coverage
- Build-ID extraction from ELF files
- Frame encoding/decoding
- Argument parsing
- Error handling for invalid inputs

## Platform Support

- **Linux**: Full support with ELF build-id extraction
- **macOS/Windows**: Framework in place, needs platform-specific implementation

## Performance Considerations

### Benefits
- **Reduced symbol resolution overhead** during profiling
- **Smaller memory footprint** for symbol tables
- **Faster profiling** with deferred symbolication

### Costs
- **Additional build-id extraction** during startup
- **Slightly larger frame structures** for remote frames
- **Build-ID lookup overhead** during frame collection

## Future Enhancements

1. **macOS Support**: Implement Mach-O UUID extraction
2. **Caching**: Cache build-ids across profiler sessions
3. **Compression**: Compress build-ids in JFR output
4. **Validation**: Add runtime validation of build-id consistency
5. **Dynamic Pool Sizing**: Adjust RemoteFrameInfo pool size based on workload
6. **Native Frame Modifier Optimization**: Change native frame modifiers from `0x100` to `0x0`
   - Current: All native frames use `0x100` (ACC_NATIVE) = 2-byte varint encoding
   - Proposed: Use `0x0` (no modifiers) = 1-byte varint encoding
   - Benefit: **Save 1 byte per native frame** across all JFR recordings
   - Impact: Significant space savings for native-heavy profiles (C++ applications)
   - Note: Would require coordination with JFR parsing tools

## File Structure

```
ddprof-lib/src/main/cpp/
├── symbols_linux_dd.h           # Build-ID extraction interface (Linux-specific)
├── symbols_linux_dd.cpp         # Build-ID extraction with bounds/alignment checks
├── vmEntry.h                    # Enhanced with RemoteFrameInfo and BCI constants
├── codeCache.h                  # Enhanced with build-id fields (cleaned up operator[])
├── codeCache.cpp                # Build-id storage implementation
├── profiler.h                   # Added resolveNativeFrame/ForWalkVM, RemoteFrameInfo pool
├── profiler.cpp                 # Remote symbolication logic and pool allocation
├── stackWalker_dd.h             # DataDog wrappers with lock_index parameter
├── flightRecorder.h             # Added fillRemoteFrameInfo declaration
├── flightRecorder.cpp           # Remote frame JFR serialization
├── arguments.h                  # Added _remote_symbolication field
├── arguments.cpp                # Remote symbolication argument parsing
├── libraries.h                  # Added updateBuildIds method
└── libraries.cpp                # Build-id extraction for loaded libraries

gradle/
└── patching.gradle              # Upstream stackWalker.h/cpp patches for remote symbolication

ddprof-lib/src/main/cpp-external/
├── stackWalker.h                # Patched: lock_index parameter added to all walkVM signatures
└── stackWalker.cpp              # Patched: resolveNativeFrameForWalkVM integration at line 454

ddprof-lib/src/test/cpp/
├── remotesymbolication_ut.cpp   # Unit tests for remote symbolication
└── remoteargs_ut.cpp            # Unit tests for argument parsing

ddprof-test/src/test/java/
└── RemoteSymbolicationTest.java # Integration tests for all cstack modes
```

## Implementation Notes

- **Thread Safety**: Build-ID extraction occurs during single-threaded startup
- **Signal Handler Safety**: RemoteFrameInfo uses pre-allocated pool (signal-safe, no dynamic allocation via atomic counters)
- **Error Handling**: Graceful fallback to local symbolication on failures
- **Logging**: Debug logging for build-ID extraction progress and remote symbolication usage
- **ELF Security**:
  - Bounds checking for program header table (prevents reading beyond mapped region)
  - Alignment verification for program header offset (prevents misaligned pointer access)
  - Two-stage validation for note sections (header first, then payload)
  - ELFCLASS64 verification ensures uniform 64-bit structure sizes
- **Stack Walker Integration**:
  - walkFP/walkDwarf return raw PCs, converted by `convertNativeTrace()`
  - walkVM/walkVMX directly call `resolveNativeFrameForWalkVM()` at native frame resolution point
  - No post-processing or reverse PC lookup (eliminates broken `applyRemoteSymbolicationToVMFrames` approach)

This implementation provides a solid foundation for remote symbolication while maintaining full backward compatibility and robust error handling.
