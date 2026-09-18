# Specification: Transparent SFrame Loading as Alternative to .eh_frame

## Objective

Add SFrame V2 parsing as a transparent optimization in the native unwind table loading path. When the profiler loads a shared library, it checks for a `.sframe` section first. If present and valid, it parses SFrame data into the existing `FrameDesc*` table. If absent or invalid, it falls back to the existing `.eh_frame` DWARF path. No new user-visible CStack mode. No changes to walk-time code.

## Background

The profiler loads native unwind tables from `.eh_frame` sections via DWARF CFI opcode interpretation at library load time. SFrame is a simpler ELF section format (`.sframe`) that directly encodes CFA/FP/RA offsets in flat, binary-searchable tables without requiring a bytecode interpreter. On modern Linux distros (Fedora 43+, glibc 2.42+, binutils 2.40+), libraries ship `.sframe` sections alongside `.eh_frame`.

SFrame is Linux/ELF only. macOS is unaffected.

Reference: https://sourceware.org/binutils/docs/sframe-spec.html

## Scope

### In scope
- SFrame V2 parser producing `FrameDesc*` tables identical to what the DWARF parser produces
- x86_64 and aarch64 architecture support
- Per-library fallback: use `.sframe` when present, `.eh_frame` otherwise
- Aarch64 GCC vs Clang default frame detection (matching existing DwarfParser behavior)
- Unit tests following existing `dwarf_ut.cpp` patterns
- Bounds-checking for all reads from the SFrame section

### Out of scope
- No new `CSTACK_SFRAME` user-visible mode
- No SFrame V3 support (add later when V3 stabilizes)
- No PCMASK FDE type support (rare, used for PLT stubs; fall back to DWARF for those libraries)
- No macOS changes
- No changes to `StackWalker::walkDwarf()` or `CodeCache::findFrameDesc()`

## Architecture

### Current loading path (unchanged for .eh_frame)

```
ElfParser::parseDwarfInfo()   [symbols_linux.cpp:593]
  -> findProgramHeader(PT_GNU_EH_FRAME)
  -> DwarfParser(name, image_base, eh_frame_hdr_ptr)   [dwarf.cpp]
     - Interprets DWARF CFI opcodes (DW_CFA_*)
     - Builds sorted FrameDesc* table
  -> CodeCache::setDwarfTable(table, count, defaultFrame)   [codeCache.cpp:397]

At walk time:
  CodeCache::findFrameDesc(pc)   [codeCache.cpp:403]
    - Binary search: target_loc = (char*)pc - _text_base
    - Returns FrameDesc with cfa, fp_off, pc_off
  StackWalker::walkDwarf()   [stackWalker.cpp:81]
    - Uses FrameDesc fields to step through frames
```

### New loading path (SFrame, tried first)

```
ElfParser::parseDwarfInfo()   [symbols_linux.cpp:593]
  -> findProgramHeader(PT_GNU_SFRAME)            // NEW: try SFrame first
  -> SFrameParser(name, section_base, size, section_offset)   [sframe.cpp]
     - Direct struct reads, no opcode interpretation
     - Builds sorted FrameDesc* table
  -> CodeCache::setDwarfTable(table, count, defaultFrame)
  -> return on success; fall through to DWARF on failure

  -> findProgramHeader(PT_GNU_EH_FRAME)          // existing fallback
  -> DwarfParser(...)
  ...
```

Walk-time code is identical -- both paths produce the same `FrameDesc` table format.

## Files to Create

### `ddprof-lib/src/main/cpp/sframe.h`

Header with SFrame format definitions and parser class declaration.

**Constants** (define locally; older `<elf.h>` may lack them):

```cpp
#ifndef PT_GNU_SFRAME
#define PT_GNU_SFRAME 0x6474e554
#endif

// SFrame header constants
const uint16_t SFRAME_MAGIC     = 0xDEE2;
const uint8_t  SFRAME_VERSION_2 = 2;
const uint8_t  SFRAME_F_FDE_SORTED = 0x01;

// ABI/architecture identifiers
const uint8_t SFRAME_ABI_AARCH64_ENDIAN_LITTLE = 2;
const uint8_t SFRAME_ABI_AMD64_ENDIAN_LITTLE   = 3;

// FDE info byte accessors
//   bit 0:   FDE type (0=PCINC, 1=PCMASK)
//   bits 1-2: FRE type (start address size: 0=1B, 1=2B, 2=4B)
#define SFRAME_FUNC_FDE_TYPE(info) ((info) & 0x1)
#define SFRAME_FUNC_FRE_TYPE(info) (((info) >> 1) & 0x3)

// FRE info byte accessors
//   bit 0:    CFA base register (0=SP, 1=FP)
//   bits 1-2: offset encoding size (0=1B, 1=2B, 2=4B)
//   bit 3:    RA tracked
//   bit 4:    FP tracked
//   bit 7:    mangled RA (PAC on aarch64)
#define SFRAME_FRE_BASE_REG(info)    ((info) & 0x1)
#define SFRAME_FRE_OFFSET_SIZE(info) (((info) >> 1) & 0x3)
#define SFRAME_FRE_RA_TRACKED(info)  (((info) >> 3) & 0x1)
#define SFRAME_FRE_FP_TRACKED(info)  (((info) >> 4) & 0x1)

// Offset size codes
const int SFRAME_FRE_OFFSET_1B = 0;
const int SFRAME_FRE_OFFSET_2B = 1;
const int SFRAME_FRE_OFFSET_4B = 2;

// FRE start address size codes (from FDE info)
const int SFRAME_FRE_TYPE_ADDR1 = 0;
const int SFRAME_FRE_TYPE_ADDR2 = 1;
const int SFRAME_FRE_TYPE_ADDR4 = 2;
```

**On-disk structs** (packed, little-endian):

```cpp
struct __attribute__((packed)) SFrameHeader {  // 28 bytes
    uint16_t magic;
    uint8_t  version;
    uint8_t  flags;
    uint8_t  abi_arch;
    int8_t   cfa_fixed_fp_offset;
    int8_t   cfa_fixed_ra_offset;   // -8 on x86_64, 0 on aarch64 (per-FRE)
    uint8_t  auxhdr_len;
    uint32_t num_fdes;
    uint32_t num_fres;
    uint32_t fre_len;               // total bytes in FRE sub-section
    uint32_t fdeoff;                // offset to FDE array from end of header+auxhdr
    uint32_t freoff;                // offset to FRE section from end of header+auxhdr
};

struct __attribute__((packed)) SFrameFDE {     // 20 bytes
    int32_t  start_addr;            // signed, relative to .sframe section start (V2)
    uint32_t func_size;
    uint32_t fre_off;               // byte offset into FRE sub-section
    uint32_t fre_num;               // number of FREs for this function
    uint8_t  info;                  // FDE type (bit 0) | FRE type (bits 1-2)
    uint8_t  rep_size;              // for repeated block encoding
    uint16_t padding;
};
```

**SFrameParser class**:

```cpp
class SFrameParser {
  private:
    const char* _name;              // library name for diagnostics
    const char* _section_base;      // runtime address of .sframe section
    size_t _section_size;
    u32 _section_offset;            // section_runtime_addr - library_base (for loc computation)

    int _capacity;
    int _count;
    FrameDesc* _table;
    int _linked_frame_size;         // for aarch64 GCC vs Clang detection; -1 = undetected

    bool parseFDE(const SFrameHeader* hdr, const SFrameFDE* fde,
                  const char* fre_section, const char* fre_end);
    FrameDesc* addRecord(u32 loc, u32 cfa, int fp_off, int pc_off);

  public:
    SFrameParser(const char* name, const char* section_base,
                 size_t section_size, u32 section_offset);
    ~SFrameParser();

    bool parse();  // returns false on invalid/unsupported section (triggers DWARF fallback)

    // Ownership of table() transfers to caller on success.
    // Caller frees with free(). After calling table(), do not use the parser further.
    FrameDesc* table() const { return _table; }
    int count() const { return _count; }

    const FrameDesc& detectedDefaultFrame() const;
};
```

Include `dwarf.h` for `FrameDesc`, `DW_REG_SP`, `DW_REG_FP`, `DW_SAME_FP`, `DW_LINK_REGISTER`, `LINKED_FRAME_SIZE`, `LINKED_FRAME_CLANG_SIZE`, `DWARF_SUPPORTED`.

### `ddprof-lib/src/main/cpp/sframe.cpp`

**Constructor:**
- Store name, section_base, section_size, section_offset
- Allocate `_table = (FrameDesc*)malloc(128 * sizeof(FrameDesc))`, `_capacity = 128`, `_count = 0`
- Set `_linked_frame_size = -1`

**Destructor:**
- Free `_table` if non-null (handles the case where `parse()` fails but caller doesn't call `table()`)

**`parse()` method:**
1. If `_section_size < sizeof(SFrameHeader)` return false
2. Cast `_section_base` to `const SFrameHeader*`
3. Validate `magic == SFRAME_MAGIC`
4. Validate `version == SFRAME_VERSION_2`
5. Validate `abi_arch` matches current architecture:
   - `__x86_64__` -> `SFRAME_ABI_AMD64_ENDIAN_LITTLE`
   - `__aarch64__` -> `SFRAME_ABI_AARCH64_ENDIAN_LITTLE`
   - Other -> return false
6. Compute: `data_start = _section_base + sizeof(SFrameHeader) + hdr->auxhdr_len`
7. Compute: `fde_array = (const SFrameFDE*)(data_start + hdr->fdeoff)`
8. Compute: `fre_section = data_start + hdr->freoff`
9. Compute: `fre_end = fre_section + hdr->fre_len`
10. Bounds check: `(const char*)fde_array + hdr->num_fdes * sizeof(SFrameFDE) <= _section_base + _section_size`
11. Bounds check: `fre_end <= _section_base + _section_size`
12. For each FDE i in 0..num_fdes-1:
    - Skip if `SFRAME_FUNC_FDE_TYPE(fde->info) != 0` (PCMASK not supported)
    - Skip if `fde->fre_num == 0`
    - Call `parseFDE(hdr, fde, fre_section, fre_end)`. On false, continue (skip corrupt FDE)
13. Sort: `qsort(_table, _count, sizeof(FrameDesc), FrameDesc::comparator)`
14. Return `_count > 0`

**`parseFDE()` method:**
1. Determine FRE start address size from `SFRAME_FUNC_FRE_TYPE(fde->info)`:
   - 0 -> 1 byte (uint8_t)
   - 1 -> 2 bytes (uint16_t)
   - 2 -> 4 bytes (uint32_t)
   - other -> return false
2. Compute `fre_ptr = fre_section + fde->fre_off`
3. For each FRE j in 0..fde->fre_num-1:
   a. Bounds check: `fre_ptr < fre_end`
   b. Read FRE start address offset (unsigned, 1/2/4 bytes per step 1)
   c. Read FRE info byte (1 byte)
   d. Determine offset encoding size from `SFRAME_FRE_OFFSET_SIZE(fre_info)`:
      - 0 -> 1 byte (int8_t)
      - 1 -> 2 bytes (int16_t)
      - 2 -> 4 bytes (int32_t)
      - other -> return false
   e. Bounds check remaining read size
   f. Read CFA offset (signed, size from step d)
   g. Read FP offset if `SFRAME_FRE_FP_TRACKED(fre_info)` (signed, same size)
   h. Read RA offset if `hdr->cfa_fixed_ra_offset == 0 && SFRAME_FRE_RA_TRACKED(fre_info)` (signed, same size)
   i. Translate to FrameDesc (see translation rules below)
   j. Call `addRecord(loc, cfa, fp_off, pc_off)`
4. Return true

**SFrame to FrameDesc translation rules:**

```
// Address: section-relative -> image-base-relative
loc = _section_offset + (u32)((int32_t)fde->start_addr + fre_start_addr_offset)

// CFA register mapping
cfa_reg = SFRAME_FRE_BASE_REG(fre_info) ? DW_REG_FP : DW_REG_SP
cfa = ((u32)cfa_offset << 8) | cfa_reg

// Frame pointer
fp_off = SFRAME_FRE_FP_TRACKED(fre_info) ? fre_fp_offset : DW_SAME_FP

// Return address / program counter
if (hdr->cfa_fixed_ra_offset != 0) {
    // x86_64: RA is always at CFA + fixed offset (typically -8)
    pc_off = (int)hdr->cfa_fixed_ra_offset;
} else if (SFRAME_FRE_RA_TRACKED(fre_info)) {
    // aarch64: RA location varies per frame
    pc_off = fre_ra_offset;
} else {
    // aarch64 leaf: RA in link register, not on stack
    pc_off = DW_LINK_REGISTER;
}
```

**Default frame detection** (for aarch64 GCC vs Clang):
```cpp
const FrameDesc& SFrameParser::detectedDefaultFrame() const {
    if (_linked_frame_size == LINKED_FRAME_CLANG_SIZE &&
        LINKED_FRAME_CLANG_SIZE != LINKED_FRAME_SIZE) {
        return FrameDesc::default_clang_frame;
    }
    return FrameDesc::default_frame;
}
```

In `parseFDE()`, when translating a FRE: if `_linked_frame_size < 0` and `cfa_reg == DW_REG_FP` and `cfa_offset > 0`, set `_linked_frame_size = cfa_offset`. This matches `DwarfParser::addRecord()` logic at `dwarf.cpp:512-514`.

**`addRecord()` method:**
```cpp
FrameDesc* SFrameParser::addRecord(u32 loc, u32 cfa, int fp_off, int pc_off) {
    if (_count >= _capacity) {
        FrameDesc* resized = (FrameDesc*)realloc(_table, _capacity * 2 * sizeof(FrameDesc));
        if (!resized) return NULL;
        _capacity *= 2;
        _table = resized;
    }
    FrameDesc* fd = &_table[_count++];
    fd->loc = loc;
    fd->cfa = cfa;
    fd->fp_off = fp_off;
    fd->pc_off = pc_off;
    return fd;
}
```

## Files to Modify

### `ddprof-lib/src/main/cpp/symbols_linux.cpp`

Add `#include "sframe.h"` near existing `#include "dwarf.h"`.

Replace `parseDwarfInfo()` (currently at line 593):

```cpp
void ElfParser::parseDwarfInfo() {
    if (!DWARF_SUPPORTED) return;

    // Try SFrame first (simpler format, faster parsing, no opcode interpretation)
    ElfProgramHeader* sframe_phdr = findProgramHeader(PT_GNU_SFRAME);
    if (sframe_phdr != NULL && sframe_phdr->p_vaddr != 0) {
        const char* section_base = at(sframe_phdr);
        u32 section_offset = (u32)(section_base - _base);
        SFrameParser sframe(_cc->name(), section_base,
                            (size_t)sframe_phdr->p_memsz, section_offset);
        if (sframe.parse()) {
            _cc->setDwarfTable(sframe.table(), sframe.count(),
                               sframe.detectedDefaultFrame());
            return;
        }
        // SFrame parse failed; fall through to DWARF
    }

    // Existing DWARF path (unchanged)
    ElfProgramHeader* eh_frame_hdr = findProgramHeader(PT_GNU_EH_FRAME);
    if (eh_frame_hdr != NULL) {
        if (eh_frame_hdr->p_vaddr != 0) {
            DwarfParser dwarf(_cc->name(), _base, at(eh_frame_hdr));
            _cc->setDwarfTable(dwarf.table(), dwarf.count(),
                               dwarf.detectedDefaultFrame());
        } else if (strcmp(_cc->name(), "[vdso]") == 0) {
            FrameDesc* table = (FrameDesc*)malloc(sizeof(FrameDesc));
            *table = FrameDesc::empty_frame;
            _cc->setDwarfTable(table, 1);
        }
    }
}
```

**Address translation explained:**
- `_base` is the library's runtime load address (same value stored as `_text_base` in CodeCache)
- `at(sframe_phdr)` returns the runtime address of the `.sframe` section
- `section_offset = at(sframe_phdr) - _base` = section's offset within the loaded image
- SFrame FDE `start_addr` is relative to section start
- So `loc = section_offset + fde->start_addr + fre_offset` = offset from library base
- At walk time: `findFrameDesc(pc)` computes `target_loc = pc - _text_base` = offset from library base
- These match.

## Test File

### `ddprof-lib/src/test/cpp/sframe_ut.cpp`

Guard with `#ifdef __linux__` (SFrame is Linux/ELF only).

Use gtest framework matching `dwarf_ut.cpp` patterns. Include `gtest_crash_handler.h`.

**Test helpers** — functions to construct in-memory SFrame binary data:
- `buildHeader(buf, abi_arch, cfa_fixed_ra_offset, num_fdes, num_fres, fre_len, fdeoff, freoff)` -- appends a valid SFrameHeader
- `buildFDE(buf, start_addr, func_size, fre_off, fre_num, fre_type)` -- appends an SFrameFDE
- `buildFRE_1B(buf, start_offset, fre_info, cfa_off, [fp_off], [ra_off])` -- appends a 1-byte-offset FRE
- Similar helpers for 2B and 4B FREs

**Test cases:**

| Test | What it verifies |
|------|-----------------|
| `InvalidMagic` | `parse()` returns false for wrong magic |
| `UnsupportedVersion` | `parse()` returns false for version != 2 |
| `WrongArch` | `parse()` returns false for mismatched abi_arch |
| `TruncatedSection` | `parse()` returns false when section_size < sizeof(SFrameHeader) |
| `EmptyFDEArray` | `parse()` returns false when num_fdes == 0 |
| `SingleFDE_SingleFRE_SPBased` | Single function, SP-based CFA. Verify loc, cfa reg=SP, cfa offset, fp_off=DW_SAME_FP, pc_off from fixed RA |
| `SingleFDE_SingleFRE_FPBased` | FP-based CFA with FP tracked. Verify cfa reg=FP, fp_off set |
| `FixedRAOffset` | x86_64 style: `cfa_fixed_ra_offset=-8`. Verify pc_off=-8 regardless of FRE flags |
| `PerFRE_RA` | aarch64 style: `cfa_fixed_ra_offset=0`, RA tracked. Verify pc_off from FRE |
| `PerFRE_RA_Untracked` | aarch64 leaf: RA not tracked. Verify pc_off=DW_LINK_REGISTER |
| `MultipleFDEs` | 3 FDEs with multiple FREs each. Verify all entries present and sorted by loc |
| `OffsetSize_2B` | FRE with 2-byte offset encoding. Verify correct value decoding |
| `OffsetSize_4B` | FRE with 4-byte offset encoding |
| `AddressTranslation` | Verify `loc = section_offset + fde.start_addr + fre.start_offset` with non-zero section_offset |
| `EmptyFDE_Skipped` | FDE with fre_num=0 produces no records |
| `PCMASK_Skipped` | FDE with PCMASK type is skipped |
| `BoundsCheck_FREOverrun` | FRE data extends past fre_end. parseFDE returns false for that FDE, remaining FDEs still parsed |
| `ParseFailure_FreesTable` | On failure, verify parse() returns false and no memory is leaked (destructor frees) |

## Build Integration

No build file changes needed. The build system (`NativeBuildPlugin` / `GtestTaskBuilder`) auto-discovers source files in `ddprof-lib/src/main/cpp/` and test files in `ddprof-lib/src/test/cpp/`. New `.cpp` and `.h` files are picked up automatically.

Verify: `./gradlew ddprof-lib:compileRelease` compiles the new files; `./gradlew ddprof-test:testDebug` runs the new tests.

## Verification Plan

1. **Unit tests**: Run `./gradlew ddprof-test:testDebug` -- new SFrame tests pass, existing DWARF tests unaffected
2. **Build**: `./gradlew ddprof-lib:compileRelease` succeeds on Linux (both x86_64 and aarch64 CI)
3. **macOS**: Build succeeds (SFrame code compiles but `PT_GNU_SFRAME` is never found since macOS uses Mach-O, not ELF)
4. **Integration on modern Linux**: On a system with `.sframe` support (Fedora 43+), profile a Java app with `cstack=dwarf`. Verify native stacks are collected. Optionally add a `Log::info` in the SFrame path during development to confirm it's taken.
5. **Fallback on older Linux**: On a system without `.sframe`, verify the DWARF path is taken as before (no behavior change)
6. **Correctness comparison**: On a system with `.sframe`, compare profiler output between SFrame path and DWARF-only path (disable SFrame temporarily). Stack traces should be identical.

## Constraints

- Linux only. macOS path (`symbols_macos.cpp`) is not modified.
- No external dependencies. Parser is self-contained.
- No heap allocation at walk time. All parsing happens at library load time.
- Allocation during parsing (malloc/realloc for table) is acceptable.
- Must handle mixed environments: some libraries have `.sframe`, others don't.
- Must support both x86_64 and aarch64.
- Older `<elf.h>` headers may lack `PT_GNU_SFRAME` -- define locally with `#ifndef` guard.
