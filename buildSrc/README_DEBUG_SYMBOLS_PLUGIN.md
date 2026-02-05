# Debug Symbols Extraction Gradle Plugin

A reusable Gradle plugin for extracting and managing debug symbols from native libraries. This plugin automates the process of splitting debug information from production binaries, reducing deployed library size while maintaining separate debug files for debugging and symbolication.

## Overview

The plugin handles the complete workflow of debug symbol extraction:
- **Extracts** debug symbols using platform-specific tools
- **Links** debug information back to stripped binaries (Linux only)
- **Strips** production binaries to minimize size
- **Copies** both debug symbols and stripped libraries to target locations

### Platform Support

- **Linux**: Uses `objcopy` to extract symbols and add GNU debuglink, `strip` to remove symbols
- **macOS**: Uses `dsymutil` to create .dSYM bundles, `strip -S` to remove symbols

### Size Reduction

Typical results for native profiling libraries:
- Original library with embedded debug info: ~6.1 MB
- Stripped library for production: ~1.2 MB (80% reduction)
- Separate debug symbols file: ~6.1 MB

## Usage

### Basic Configuration

```groovy
// Apply the plugin
apply plugin: DebugSymbolsPlugin

// Call setupDebugExtraction after link task is created
buildConfigurations.each { config ->
    def linkTask = tasks.register("linkLib${config.name.capitalize()}", SimpleLinkShared) {
        // ... link configuration
    }

    // Setup debug extraction for release builds
    if (config.name == 'release') {
        setupDebugExtraction(config, linkTask, "copyReleaseLibs")
    }
}
```

The `setupDebugExtraction` method takes three parameters:
1. **config**: The build configuration object (must have `name == 'release'` and `active == true`)
2. **linkTask**: The link task that produces the library file
3. **copyTaskName**: Optional name of the copy task to wire dependencies into

### Automatic Configuration

The plugin automatically configures reasonable defaults:

- **`libraryFile`**: Set from linkTask.outputFile
- **`debugOutputDir`**: `build/lib/main/${config.name}/${os}/${arch}/debug`
- **`strippedOutputDir`**: `build/lib/main/${config.name}/${os}/${arch}/stripped`
- **`libraryExtension`**: `'so'` on Linux, `'dylib'` on macOS
- **`libraryBaseName`**: `'libjavaProfiler'`

### Advanced Configuration

You can customize the extension before calling `setupDebugExtraction`:

```groovy
// Apply plugin
apply plugin: DebugSymbolsPlugin

// Configure debug symbols extraction
debugSymbols {
    libraryBaseName = 'myLibrary'
    skipExtraction = false  // Set to true to disable extraction
}

// Then call setupDebugExtraction as usual
```

## Configuration Properties

### DebugSymbolsExtension Properties

- **`libraryFile`** (RegularFileProperty): The linked library file to extract symbols from
  - Automatically set from linkTask.outputFile

- **`debugOutputDir`** (DirectoryProperty): Output directory for debug symbol files
  - Linux: Creates `.debug` files (e.g., `libjavaProfiler.so.debug`)
  - macOS: Creates `.dSYM` bundles (e.g., `libjavaProfiler.dylib.dSYM/`)

- **`strippedOutputDir`** (DirectoryProperty): Output directory for stripped libraries
  - Contains production-ready libraries with debug symbols removed

- **`targetDir`** (DirectoryProperty): Optional target for copying final artifacts
  - If set, both debug and stripped files are copied here

- **`skipExtraction`** (Property<Boolean>): Skip extraction even if tools are available
  - Default: `false`
  - Can also be controlled via `-Pskip-debug-extraction=true` property

- **`libraryExtension`** (Property<String>): Library file extension without dot
  - Default: `'so'` on Linux, `'dylib'` on macOS

- **`libraryBaseName`** (Property<String>): Base name of library without extension
  - Default: `'libjavaProfiler'`

- **`toolPaths`** (MapProperty<String, String>): Custom tool paths
  - Keys: `'objcopy'`, `'strip'`, `'dsymutil'`
  - Use when tools are not in PATH

## Generated Tasks

For each release configuration, the plugin creates:

### 1. extractDebugLib{Config}
**Description**: Extract debug symbols from the linked library

**Linux**:
```bash
objcopy --only-keep-debug input.so output.so.debug
```

**macOS**:
```bash
dsymutil input.dylib -o output.dylib.dSYM
```

### 2. addDebugLinkLib{Config} (Linux only)
**Description**: Add GNU debuglink section to the original library

This creates a link from the stripped library to its debug symbols file, allowing debuggers to automatically locate symbols.

```bash
objcopy --add-gnu-debuglink=output.so.debug input.so
```

### 3. stripLib{Config}
**Description**: Strip debug symbols from the library

Creates a copy of the library and strips debug information:

**Linux**:
```bash
cp input.so stripped/output.so
strip --strip-debug stripped/output.so
```

**macOS**:
```bash
cp input.dylib stripped/output.dylib
strip -S stripped/output.dylib
```

### 4. copy{Config}DebugFiles
**Description**: Copy debug symbol files to target directory

Copies `.debug` files (Linux) or `.dSYM` bundles (macOS) to the final artifact location.

## Workflow

The complete debug symbol extraction workflow:

```
linkLibRelease
    ↓
extractDebugLibRelease
    ↓
addDebugLinkLibRelease (Linux only)
    ↓
stripLibRelease
    ↓
copyReleaseLibs (wired via setupDebugExtraction)
    ↑
    └─ copyReleaseDebugFiles
```

### Linux Workflow

1. **Link**: Produce `libjavaProfiler.so` with full debug info (~6.1 MB)
2. **Extract**: Create `libjavaProfiler.so.debug` with only debug info
3. **Add Link**: Add `.gnu_debuglink` section to original library
4. **Strip**: Create `stripped/libjavaProfiler.so` (~1.2 MB)
5. **Copy**: Copy both stripped library and `.debug` file to target

### macOS Workflow

1. **Link**: Produce `libjavaProfiler.dylib` with full debug info (~6.1 MB)
2. **Extract**: Create `libjavaProfiler.dylib.dSYM/` bundle with debug info
3. **Strip**: Create `stripped/libjavaProfiler.dylib` (~1.2 MB)
4. **Copy**: Copy both stripped library and `.dSYM` bundle to target

## Skip Conditions

The plugin automatically skips debug extraction when:

1. **Tools not available**: `objcopy`/`strip` (Linux) or `dsymutil`/`strip` (macOS)
2. **Property set**: `-Pskip-debug-extraction=true`
3. **Skip native**: `-Pskip-native=true`
4. **Non-release build**: Only processes configs with `name == 'release'`
5. **Inactive config**: Only processes configs with `active == true`
6. **Extension configured**: `debugSymbols.skipExtraction = true`

When skipped, the original library with embedded debug info is used.

## Tool Installation

### Linux

**Debian/Ubuntu**:
```bash
sudo apt-get install binutils
```

**RHEL/CentOS**:
```bash
sudo yum install binutils
```

**Arch Linux**:
```bash
sudo pacman -S binutils
```

### macOS

**Xcode Command Line Tools**:
```bash
xcode-select --install
```

The tools (`dsymutil` and `strip`) are included with Xcode Command Line Tools.

## Integration Examples

### Integration with Copy Tasks

The plugin automatically wires dependencies into the specified copy task:

```groovy
if (config.name == 'release') {
    setupDebugExtraction(config, linkTask, "copyReleaseLibs")
}
```

This makes `copyReleaseLibs` depend on:
- `stripLibRelease` (copies stripped library)
- `copyReleaseDebugFiles` (copies debug symbols)

### Multiple Configurations

```groovy
buildConfigurations.each { config ->
    def linkTask = tasks.register("linkLib${config.name.capitalize()}", SimpleLinkShared) {
        // ... configuration
    }

    // Only for release builds
    if (config.name == 'release' && config.active) {
        setupDebugExtraction(config, linkTask, "copy${config.name.capitalize()}Libs")
    }
}
```

### Custom Base Name

```groovy
debugSymbols {
    libraryBaseName = 'myprofilinglib'
}

// Results in:
// - myprofilinglib.so / myprofilinglib.dylib
// - myprofilinglib.so.debug / myprofilinglib.dylib.dSYM
```

## Debugging

### Verify Tool Availability

**Linux**:
```bash
objcopy --version
strip --version
```

**macOS**:
```bash
dsymutil --version
strip --version
```

### Check Task Creation

List all tasks to verify debug extraction tasks were created:

```bash
./gradlew tasks --all | grep -i debug
```

Expected tasks:
- `extractDebugLibRelease`
- `addDebugLinkLibRelease` (Linux only)
- `stripLibRelease`
- `copyReleaseDebugFiles`

### Inspect Generated Files

**Linux**:
```bash
# Check stripped library size
ls -lh build/lib/main/release/.../stripped/libjavaProfiler.so

# Check debug file exists
ls -lh build/lib/main/release/.../debug/libjavaProfiler.so.debug

# Verify debuglink section
readelf -p .gnu_debuglink build/lib/main/release/.../stripped/libjavaProfiler.so
```

**macOS**:
```bash
# Check stripped library size
ls -lh build/lib/main/release/.../stripped/libjavaProfiler.dylib

# Check dSYM bundle
ls -lh build/lib/main/release/.../debug/libjavaProfiler.dylib.dSYM/Contents/Resources/DWARF/

# Verify symbols
dsymutil -s build/lib/main/release/.../stripped/libjavaProfiler.dylib
```

## Troubleshooting

### Tools Not Found

**Error**: "dsymutil or strip not available"

**Solution**: Install Xcode Command Line Tools (macOS) or binutils (Linux)

### Debug Link Not Working (Linux)

**Issue**: Debugger cannot find debug symbols

**Solutions**:
1. Verify `.gnu_debuglink` section exists: `readelf -p .gnu_debuglink library.so`
2. Ensure `.debug` file is in same directory as stripped library
3. Check debug file has correct name (matches debuglink section)
4. Verify GDB searches correct paths: `(gdb) show debug-file-directory`

### Stripped Library Still Large

**Issue**: Stripped library is still several MB

**Possible causes**:
1. Debug extraction was skipped - check for warnings in build log
2. Library has other non-debug data (relocation tables, symbols for dynamic linking)
3. On macOS, use `strip -S` (strips only debug) not `strip -x` (strips everything)

### .dSYM Bundle Empty (macOS)

**Issue**: .dSYM/Contents/Resources/DWARF/ directory is empty

**Solutions**:
1. Verify original library was compiled with `-g` flag
2. Check dsymutil output for errors
3. Ensure original library hasn't been stripped before extraction
4. Try manual extraction: `dsymutil -o output.dSYM input.dylib`

## Implementation Notes

### GNU Debuglink

On Linux, the plugin uses GNU debuglink to connect stripped binaries to debug files:

1. Extract symbols: `objcopy --only-keep-debug input.so output.so.debug`
2. Add link section: `objcopy --add-gnu-debuglink=output.so.debug input.so`
3. Strip binary: `strip --strip-debug input.so`

The debuglink section contains:
- Debug file name
- CRC32 checksum of debug file

Debuggers (GDB, LLDB) automatically locate debug files using this information.

### dSYM Bundles (macOS)

On macOS, dsymutil creates a directory bundle structure:

```
libjavaProfiler.dylib.dSYM/
  Contents/
    Info.plist
    Resources/
      DWARF/
        libjavaProfiler.dylib  # Debug information
```

The bundle contains:
- DWARF debug information
- Symbol tables
- Source line mappings
- Type information

### Strip Behavior

**Linux `strip --strip-debug`**:
- Removes DWARF debug sections (.debug_*)
- Keeps symbol tables for dynamic linking
- Keeps relocation information
- Typical size: ~20% of original

**macOS `strip -S`**:
- Removes debug symbols
- Keeps global symbols for linking
- Keeps relocation information
- Typical size: ~20% of original

## See Also

- `SimpleLinkShared.groovy` - Custom C++ linking task
- `buildSrc/README_GTEST_PLUGIN.md` - Google Test plugin documentation
- GNU binutils documentation: https://sourceware.org/binutils/docs/
- DWARF Debugging Standard: http://dwarfstd.org/
- Apple dSYM documentation: https://developer.apple.com/documentation/xcode/building-your-app-to-include-debugging-information
