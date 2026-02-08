# Frame Type vs Modifier: Design Decision for Remote Symbolication

## Final Solution: Use Frame Type Instead of Modifier

After evaluating multiple approaches, **we chose to use a new frame type (`FRAME_NATIVE_REMOTE = 7`) instead of a custom modifier flag**. This eliminates:
- ✅ All varint encoding overhead
- ✅ Any potential conflicts with Java modifiers
- ✅ Ambiguity in semantics

Remote native frames now use:
- **Modifier**: `0x0100` (ACC_NATIVE, same as regular native frames)
- **Frame Type**: `FRAME_NATIVE_REMOTE` (7)

## Java Access Modifiers (from JVM Spec)

The Java Virtual Machine specification defines the following access modifiers for classes, methods, and fields:

| Modifier | Value | Applies To | Description |
|----------|-------|------------|-------------|
| ACC_PUBLIC | 0x0001 | All | Public access |
| ACC_PRIVATE | 0x0002 | Methods/Fields | Private access |
| ACC_PROTECTED | 0x0004 | Methods/Fields | Protected access |
| ACC_STATIC | 0x0008 | Methods/Fields | Static member |
| ACC_FINAL | 0x0010 | All | Final/non-overridable |
| ACC_SYNCHRONIZED | 0x0020 | Methods | Synchronized method |
| ACC_SUPER | 0x0020 | Classes | Treat superclass invokes specially |
| ACC_BRIDGE | 0x0040 | Methods | Compiler-generated bridge method |
| ACC_VOLATILE | 0x0040 | Fields | Volatile field |
| ACC_VARARGS | 0x0080 | Methods | Variable arity method |
| ACC_TRANSIENT | 0x0080 | Fields | Not serialized |
| ACC_NATIVE | 0x0100 | Methods | Native implementation |
| **ACC_INTERFACE** | **0x0200** | **Classes** | **Interface declaration** |
| ACC_ABSTRACT | 0x0400 | Classes/Methods | Abstract class/method |
| ACC_STRICT | 0x0800 | Methods | Use strict floating-point |
| ACC_SYNTHETIC | 0x1000 | All | Compiler-generated |
| ACC_ANNOTATION | 0x2000 | Classes | Annotation type |
| ACC_ENUM | 0x4000 | Classes/Fields | Enum type/constant |
| ACC_MANDATED | 0x8000 | Parameters | Implicitly declared |

## Profiler Custom Modifiers

For the Java profiler's internal use, we define custom modifier flags that don't conflict with Java's standard modifiers:

| Modifier | Value | Usage | Notes |
|----------|-------|-------|-------|
| ACC_NATIVE | 0x0100 | Native frames | Reuses Java's ACC_NATIVE for consistency |
| ACC_SYNTHETIC | 0x1000 | Compiler-generated | Reuses Java's ACC_SYNTHETIC |
| ACC_BRIDGE | 0x0040 | Bridge methods | Reuses Java's ACC_BRIDGE |
| **ACC_REMOTE_SYMBOLICATION** | **0x10000** | **Remote native frames** | **Custom profiler flag (bit 16, outside Java range)** |

## Modifier Conflict Analysis

### Evolution of the Design

**Version 1 (Initial)**: Used `0x200`
- ❌ **CONFLICT**: Java's `ACC_INTERFACE` (0x0200)
- Issues: Could confuse JFR parsers, clash with standard modifiers

**Version 2**: Changed to `0x2000`
- ⚠️ **CONFLICT**: Java's `ACC_ANNOTATION` (0x2000)
- While theoretically safe for methods (annotations only apply to classes), still within Java's reserved range

**Version 3 (Final)**: Changed to `0x10000` (bit 16)
- ✅ **NO CONFLICTS**: Completely outside Java's standard modifier range (0x0001-0x8000)
- ✅ Clean separation from JVM specification
- ✅ Future-proof against new Java modifiers

### Why 0x10000 is the Correct Choice

**Java Modifier Range:**
- Java uses bits 0-15 (0x0001 to 0x8000)
- Highest standard modifier: `ACC_MANDATED = 0x8000` (bit 15)

**Custom Profiler Range:**
- Bits 16-30 available for custom flags (0x10000 to 0x40000000)
- `0x10000` (bit 16) is first bit outside Java range
- Clean power of 2, easy to test and debug

**Benefits:**
1. **Zero theoretical conflicts** with any Java modifier (current or future)
2. **Clear separation** between JVM standard (bits 0-15) and profiler custom (bits 16+)
3. **32-bit safe**: Well within `jint` range (signed 32-bit)
4. **JFR compatible**: `_modifiers` field supports full 32-bit values
5. **Extensible**: Room for additional custom flags (0x20000, 0x40000, etc.)

### Varint Encoding Analysis

JFR uses LEB128 variable-length encoding for modifiers. The encoding size depends on the value:

| Value Range | Example | Bytes | Notes |
|-------------|---------|-------|-------|
| 0x00-0x7F | 0 | 1 | Most compact |
| 0x80-0x3FFF | 0x0100 (ACC_NATIVE) | 2 | Standard native frames |
| 0x4000-0x1FFFFF | 0x1000 (ACC_SYNTHETIC) | 2 | High standard modifiers |
| 0x10000+ | 0x10000 | 3 | **+1 byte overhead!** |

**Critical insight**: Using `0x10000` would add **1 extra byte per remote native frame**. Over millions of frames, this becomes significant!

### Alternative Approaches Rejected

1. **Use modifier 0x0200 (bit 9)**:
   - ❌ Conflicts with ACC_INTERFACE

2. **Use modifier 0x2000 (bit 13)**:
   - ❌ Conflicts with ACC_ANNOTATION (theoretically)
   - ⚠️ Would be safe in practice (annotations only for classes)

3. **Use modifier 0x10000 (bit 16)**:
   - ❌ 3-byte varint encoding vs 2-byte for regular frames
   - ❌ **+1 byte overhead per frame** = significant space impact

4. **Use a separate field**:
   - ❌ Would require JFR metadata changes
   - ❌ Breaks backward compatibility

5. **Use frame type FRAME_NATIVE_REMOTE (CHOSEN)**:
   - ✅ Zero encoding overhead (type already serialized)
   - ✅ No modifier conflicts
   - ✅ Clear semantics

## Best Practices

When adding custom modifiers in the future:

1. **Check JVM Spec**: Always verify against latest JVM specification
2. **Consider Context**: Modifiers for methods vs classes vs fields
3. **Document Clearly**: Explain why the bit is safe to use
4. **Test Compatibility**: Verify JFR parsers handle custom modifiers correctly

## References

- Java Virtual Machine Specification (JVMS §4.1, §4.5, §4.6)
- JFR Format Specification
- Original Implementation: [elfBuildId.cpp, flightRecorder.cpp]