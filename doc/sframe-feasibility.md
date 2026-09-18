# SFrame Stack Walking Mode: Feasibility Analysis

## What is SFrame?

SFrame ("Simple Frame") is a stack unwinding metadata format designed as a simpler, faster-to-decode
alternative to DWARF `.eh_frame`. Originated at Oracle, inspired by the Linux kernel's ORC unwinder.
Instead of executing a DWARF bytecode VM to recover frame info, SFrame directly encodes CFA/FP/RA
offsets in flat, binary-searchable tables. No interpreter needed.

The `.sframe` ELF section (`SHT_GNU_SFRAME`, `SHF_ALLOC`) has three parts:
- **Header** (~28 bytes): magic, version, ABI/arch, fixed RA offset, FDE/FRE counts
- **FDE sub-section**: fixed-size entries sorted by start PC (binary searchable)
- **FRE sub-section**: variable-length entries encoding CFA offset, FP save offset, RA save offset

Spec: https://sourceware.org/binutils/docs/sframe-spec.html

## Current Toolchain & Kernel Status

| Component         | SFrame Status |
|-------------------|---------------|
| GNU binutils/gas  | `--gsframe` since 2.40. Linker merges `.sframe`. `readelf --sframe` works. |
| GCC               | Via assembler: `gcc -Wa,--gsframe`. No direct GCC flag. |
| LLVM/Clang        | RFC posted Jun 2025, prototype exists. **Not upstreamed yet** (controversial in LLVM project). |
| glibc             | Merged in 2.42 (Aug 2025). `ld.so` registers `.sframe` with kernel via `prctl()`. |
| Linux kernel      | Merged in 6.19 (Feb 2026). `perf_events` can do SFrame-based user-space unwinding. |
| Fedora            | `.sframe` in all packages since Fedora 43. |
| Architectures     | x86_64 (V1+), aarch64 (V1+), s390x (V2 errata 1). |
| macOS             | **Not applicable** -- ELF-only format. |

**Critical gap: No LLVM support means clang-built binaries (musl distros, Alpine, Android, ChromeOS)
lack `.sframe` sections.**

## Current Profiler Architecture (relevant parts)

The profiler has 6 CStack modes (`arguments.h:63-70`):

```
CSTACK_DEFAULT → CSTACK_FP → CSTACK_DWARF → CSTACK_LBR → CSTACK_VM
```

For native frame collection (`profiler.cpp:271-278`):
- `CSTACK_DWARF` → `StackWalker::walkDwarf()`
- Everything else → `StackWalker::walkFP()`

DWARF loading path:
1. `ElfParser::parseDwarfInfo()` finds `PT_GNU_EH_FRAME` program header
2. `DwarfParser` parses `.eh_frame_hdr` → sorted `FrameDesc*` table
3. `CodeCache::setDwarfTable()` stores the table per-library
4. At walk time, `findFrameDesc(pc)` does binary search → yields CFA reg, CFA offset, FP offset, PC offset

The `FrameDesc` struct (16 bytes) stores exactly what SFrame encodes:

```cpp
struct FrameDesc {
    u32 loc;     // PC offset relative to module base
    u32 cfa;     // CFA register + offset packed
    int fp_off;  // FP save location relative to CFA
    int pc_off;  // RA save location relative to CFA
};
```

## Feasibility Assessment

### What SFrame gives us that we don't already have

**Honestly: not much for in-process unwinding.** The profiler already parses `.eh_frame` into
the same logical structure (`FrameDesc`) that SFrame encodes natively. The DWARF bytecode VM
interpretation happens once at load time, not on the hot path. During stack walking, both approaches
reduce to: binary search → read offsets → step.

Where SFrame could help:

1. **Simpler parser.** The current `DwarfParser` (`dwarf.cpp`) is ~400 lines of LEB128 decoding,
   CIE/FDE parsing, and DW_CFA_* opcode interpretation. An SFrame parser would be ~100 lines of
   direct struct reads. Less code = fewer bugs, easier maintenance.

2. **Faster library load time.** Parsing `.eh_frame` is O(n) in the number of DWARF opcodes.
   SFrame FDEs are already in their final form -- just validate the header and memcpy the tables.
   For libraries with large `.eh_frame` sections (libc, libpthread, libstdc++), this saves
   measurable time during profiler startup.

3. **Future kernel perf_events integration.** On Linux 6.19+, `perf_events` can produce user-space
   stacks via SFrame without any in-process unwinding. This could replace `CSTACK_DWARF` entirely
   for the `cpu` event type on modern kernels, similar to how `CSTACK_DEFAULT` already uses
   perf_event_open stacks when available.

### Implementation effort

**Low.** The extension points are clean:

1. Add `CSTACK_SFRAME` to enum in `arguments.h`
2. Write `SFrameParser` (~100 LOC) that produces the same `FrameDesc*` table
3. In `symbols_linux.cpp::parseDwarfInfo()`, check for `PT_GNU_SFRAME` program header first,
   fall back to `PT_GNU_EH_FRAME`
4. No changes to `StackWalker::walkDwarf()` -- it already works on `FrameDesc` tables

Actually, option (3) means we might not even need a new CStack mode. SFrame could be a
**transparent optimization** of DWARF loading: if `.sframe` is present, parse that (faster);
otherwise fall back to `.eh_frame`. The walk-time code stays identical.

If we want `CSTACK_SFRAME` as an explicit mode, the additional work is:
5. Add mode selection logic in `profiler.cpp:1115-1121`
6. Add `"sframe"` string in argument parsing and `cstack()` method
7. Add `SFRAME_SUPPORTED` compile-time flag (Linux only, not macOS)

### What we'd need to handle

- **Mixed environments.** Some libraries will have `.sframe`, others won't. Need per-library
  fallback to `.eh_frame`. This is straightforward -- check in `parseDwarfInfo()`.
- **Version detection.** SFrame V1 is obsolete, V2 is current, V3 is emerging. Header has
  a version field; we only need to support V2+.
- **Architecture differences.** On x86_64, RA is at fixed CFA offset (-8) so the FRE doesn't
  encode it. On aarch64, RA offset is per-FRE. This maps directly to how `FrameDesc::pc_off`
  already works.
- **No macOS support.** SFrame is ELF-only. macOS path stays on `__eh_frame` parsing (recently
  added in PR #430). This is fine -- SFrame would be a Linux-only optimization.

### Risks and concerns

1. **LLVM gap is the dealbreaker for mandatory use.** Until clang emits `.sframe`, we cannot
   make it the default. It must always fall back to `.eh_frame`.

2. **Marginal benefit for in-process unwinding.** The DWARF parse cost is paid once at startup.
   Walk-time performance is identical (both are binary search + offset reads). The benefit is
   modest: slightly faster startup, simpler parser code.

3. **Kernel-side SFrame unwinding helps less than it appears.** The kernel's SFrame unwinder
   (Linux 6.19+) only produces **native** frames. Java frames still require
   `AsyncGetCallTrace` / JVMTI from a signal handler. So signal-handler unwinding cannot be
   eliminated -- you'd replace only the native portion while keeping all the signal machinery
   for Java frames. Coordinating kernel-provided native stacks with signal-handler-provided
   Java stacks adds complexity that likely exceeds the current unified in-process approach.

4. **Format is still evolving.** V2 → V3 changed terminology, added signal frame marking,
   flexible FDE types, 64-bit offsets. Supporting a moving target has a maintenance cost.

## Recommendation

**Feasible but not urgent.** Two practical approaches, in order of effort/value:

### Approach A: Transparent SFrame loading (low effort, do now if desired)

Add SFrame as an alternative `.eh_frame` loading path in `symbols_linux.cpp`. No new CStack
mode needed. When a library has both `.sframe` and `.eh_frame_hdr`, prefer `.sframe` for
faster load. Fall back seamlessly. ~200 LOC total (parser + integration).

**Value:** Cleaner parser, faster profiler startup on Fedora 43+ / newer distros.

### ~~Approach B: Kernel perf_events SFrame unwinding~~ (not viable)

The kernel's SFrame unwinder (Linux 6.19+) only produces native frames. Java frames still
require `AsyncGetCallTrace` from a signal handler, so we cannot eliminate in-process signal
handling. Coordinating kernel-provided native stacks with signal-handler-provided Java stacks
would add complexity without removing the fundamental signal-handler machinery. **Not worth
pursuing.**

### What I would not do

- Add `CSTACK_SFRAME` as a user-visible mode distinct from `CSTACK_DWARF`. The walk-time
  behavior is identical; exposing it as a separate mode adds configuration surface for no
  user-facing benefit.
- Target macOS. SFrame is inherently Linux/ELF.
- Block on LLVM support. The transparent fallback approach works fine with mixed toolchains.
