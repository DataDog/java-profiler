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

### 3. **Packed Remote Frame Data** (`profiler.h`)

- **RemoteFramePacker**: Utility struct for packing/unpacking remote symbolication data
  - Packs into 64-bit jmethodID: `pc_offset (44 bits) | mark (3 bits) | lib_index (17 bits)`
  - PC offset: 44 bits = 16 TB address range
  - Mark: 3 bits = 0-7 values (JVM internal frame markers)
  - Library index: 17 bits = 131K libraries max
- **RemoteFrameInfo**: Structure for JFR serialization (vmEntry.h):
  - `build_id`: Library build-id string
  - `pc_offset`: PC offset within library
  - `lib_index`: Library table index
- **BCI_NATIVE_FRAME_REMOTE**: Frame encoding (-19) indicates packed remote data

### 4. **Enhanced Frame Collection** (`profiler.cpp`, `stackWalker.h`)

Modified frame collection to support dual modes:
- **Traditional mode**: Stores resolved symbol names (existing behavior)
- **Remote mode**: Stores RemoteFrameInfo with build-id and offset

**Key Functions**:
- `populateRemoteFrame()`: Packs pc_offset, mark, and lib_index into jmethodID field
- `resolveNativeFrameForWalkVM()`: Resolves native frames for walkVM/walkVMX modes
  - Performs binarySearch() to get symbol name
  - Extracts mark via NativeFunc::mark() (O(1))
  - Packs data using RemoteFramePacker::pack()
- `convertNativeTrace()`: Converts raw PCs to frames for walkFP/walkDwarf modes
  - Checks marks to terminate at JVM internal frames
  - Calls populateRemoteFrame() to pack data

**Mark Checking**:
- Uses binarySearch() + NativeFunc::mark() approach (O(log n) + O(1))
- Performance identical to traditional symbolication
- Simpler than maintaining separate marked ranges index
- Mark values packed into jmethodID for later unpacking

**Stack Walker Integration**:
- **walkFP/walkDwarf**: Return raw PCs → `convertNativeTrace()` → `populateRemoteFrame()`
- **walkVM/walkVMX**: Directly call `resolveNativeFrameForWalkVM(pc, lock_index)` during stack walk (patched via gradle/patching.gradle)

### 5. **JFR Serialization** (`flightRecorder.cpp/h`)

- **resolveMethod()**: Unpacks remote frame data during JFR serialization
  - Uses RemoteFramePacker::unpackPcOffset/Mark/LibIndex()
  - Looks up library by index via Libraries::getLibraryByIndex()
  - Creates temporary RemoteFrameInfo with build_id and pc_offset
- **fillRemoteFrameInfo()**: Serializes remote frame data to JFR format
  - Stores `<build-id>.<remote>` in class name field (e.g., `deadbeef1234567890abcdef.<remote>`)
  - Stores PC offset in signature field (e.g., `(0x1234)`)
  - Uses modifier flag 0x100 (ACC_NATIVE, same as regular native frames)
- **Thread Safety**: Called during JFR serialization with lockAll() held
  - Library array is stable (no concurrent dlopen_hook modifications)
  - No additional locking needed

### 6. **Configuration** (`arguments.h/cpp`)

- **remotesym[=BOOL]**: New profiler argument
- Default: disabled
- Can be enabled with `remotesym=true` or `remotesym=y`

### 7. **Libraries Integration** (`libraries.h/cpp`, `libraries_linux.cpp`)

- **updateBuildIds()**: Extracts build-ids for all loaded libraries
  - Called during profiler startup when remote symbolication is enabled
  - Uses O(1) cache lookup via `_build_id_processed` set
  - Mirrors `_parsed_inodes` pattern from symbols_linux.cpp
  - Linux-only implementation using ELF parsing
- **getLibraryByIndex()**: Retrieves CodeCache by library index
  - Parameter type: uint32_t (matches 17-bit lib_index packing)
  - Returns nullptr if index out of bounds
  - Used during JFR serialization to unpack remote frames

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

- **Class Name**: Build-ID hex string (e.g., `deadbeef1234567890abcdef`)
  - Stored via `_classes->lookup(rfi->build_id)`
  - Deduplicated in JFR constant pool
- **Method Name**: `<remote>`
  - Constant string indicating remote symbolication needed
  - Stored via `_symbols.lookup("<remote>")`
- **Signature**: PC offset in hex (e.g., `0x1a2b`)
  - Formatted with `snprintf(buf, size, "0x%lx", pc_offset)`
  - Stored via `_symbols.lookup(offset_hex)`
  - Note: No parentheses, just hex value
- **Modifier**: `0x100` (ACC_NATIVE)
  - Same as regular native frames for consistency
- **Frame Type**: `FRAME_NATIVE_REMOTE` (7)
  - Distinguishes from regular native frames (FRAME_NATIVE = 6)
  - Allows parsers to identify frames needing remote symbolication

## Backward Compatibility

- **Default behavior**: No changes (remote symbolication disabled)
- **Mixed traces**: Supports both local and remote frames in same trace
- **Fallback**: Gracefully falls back to local symbolication when build-id unavailable

## Memory Management

- **Build-IDs**: Stored once per CodeCache, shared across frames
  - Hex string allocated with malloc (one-time, ~40 bytes per library)
  - Freed in CodeCache destructor
  - Total overhead: < 2 KB for typical applications
- **Packed Remote Frames**: No separate allocation needed
  - Data packed directly into 64-bit jmethodID field
  - Zero additional memory overhead per frame
  - Eliminates need for signal-safe pool allocation
- **JFR Serialization**: Temporary RemoteFrameInfo created during unpacking
  - Stack-allocated, no heap allocation
  - Only exists during JFR serialization with lockAll() held

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

## Observability and Metrics

The following counters track remote symbolication usage (added to `counters.h`):

- **REMOTE_SYMBOLICATION_FRAMES**: Number of frames using remote symbolication
  - Incremented in `populateRemoteFrame()` each time a remote frame is created
  - Indicates actual usage of the feature
- **REMOTE_SYMBOLICATION_LIBS_WITH_BUILD_ID**: Libraries with extracted build-IDs
  - Incremented in `updateBuildIds()` after successful build-ID extraction
  - Shows how many libraries are eligible for remote symbolication
- **REMOTE_SYMBOLICATION_BUILD_ID_CACHE_HITS**: Build-ID cache hit rate
  - Incremented when `_build_id_processed` cache prevents redundant extraction
  - Demonstrates effectiveness of O(1) caching strategy

These metrics appear in profiler statistics and can be used to monitor:
- Feature adoption rate (frames with remote symbolication vs total native frames)
- Build-ID coverage (libraries with build-IDs vs total libraries)
- Cache efficiency (cache hits vs total updateBuildIds() calls)

## Performance Considerations

### Benefits
- **Identical hot-path performance** to traditional symbolication
  - Same O(log n) binarySearch for mark checking
  - Zero additional overhead for packed representation
- **Reduced memory footprint**: 8 bytes per frame vs storing symbol strings
- **Faster profiling** with deferred full symbolication to post-processing
- **Eliminated duplicate lookups**: Single binarySearch per frame (was 2x before optimization)

### Costs
- **One-time build-ID extraction** during startup (~ms per library)
  - Cached with O(1) lookup to prevent redundant work
  - Only extracted for libraries loaded when profiler starts or via dlopen
- **Library index lookup** during JFR serialization
  - O(1) array access with lockAll() held
  - No contention (serialization is single-threaded)

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
├── stackWalker.h                # Enhanced with lock_index and truncated parameters
├── stackWalker.cpp              # Remote symbolication and truncation detection logic
├── flightRecorder.h             # Added fillRemoteFrameInfo declaration
├── flightRecorder.cpp           # Remote frame JFR serialization
├── arguments.h                  # Added _remote_symbolication field
├── arguments.cpp                # Remote symbolication argument parsing
├── libraries.h                  # Added updateBuildIds method
└── libraries.cpp                # Build-id extraction for loaded libraries

ddprof-lib/src/test/cpp/
├── remotesymbolication_ut.cpp   # Unit tests for remote symbolication
└── remoteargs_ut.cpp            # Unit tests for argument parsing

ddprof-test/src/test/java/
└── RemoteSymbolicationTest.java # Integration tests for all cstack modes
```

## Implementation Notes

### Thread Safety
- **Build-ID extraction**: Protected by `_build_id_lock` mutex in `updateBuildIds()`
- **Build-ID cache**: `_build_id_processed` set provides O(1) duplicate detection
- **JFR serialization**: Called with `lockAll()` held, library array is stable
  - No concurrent dlopen_hook modifications possible
  - No additional locking needed for `getLibraryByIndex()`

### Signal Handler Safety
- **Packed representation**: No allocations in signal handlers
  - Data packed directly into 64-bit jmethodID field
  - Zero memory overhead, eliminates need for signal-safe pools
- **Read-only operations**: binarySearch() and mark checking are signal-safe
  - No malloc, no locks (except tryLock which is acceptable)
  - Atomic operations where needed

### Error Handling
- **Graceful fallback**: Falls back to traditional symbolication when:
  - Library has no build-ID
  - Library index out of bounds during unpacking
  - Build-ID extraction fails
- **Defensive programming**: Null checks before dereferencing pointers
- **Logging**: TEST_LOG() for debugging production issues

### ELF Security
- Bounds checking for program header table (prevents reading beyond mapped region)
- Alignment verification for program header offset (prevents misaligned pointer access)
- Two-stage validation for note sections (header first, then payload)
- ELFCLASS64 verification ensures uniform 64-bit structure sizes

### Stack Walker Integration
- **walkFP/walkDwarf**: Return raw PCs → `convertNativeTrace()` → `populateRemoteFrame()`
- **walkVM/walkVMX**: Direct call to `resolveNativeFrameForWalkVM()` during stack walk
  - No post-processing or reverse PC lookup needed
  - Mark checking happens inline during frame resolution
  - Terminates stack walk at JVM internal frames (marks != 0)

### Design Evolution
- **Original approach**: Separate marked ranges index with O(log n) isMarkedAddress()
- **Current approach**: Simplified to binarySearch() + NativeFunc::mark()
  - Same O(log n) performance but ~150 lines less code
  - Eliminated complexity of maintaining separate index
  - Marks packed into jmethodID for JFR serialization

This implementation provides a solid foundation for remote symbolication while maintaining full backward compatibility and robust error handling.
