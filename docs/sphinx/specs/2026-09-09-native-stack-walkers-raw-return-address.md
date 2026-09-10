# Spec: native-stack-walkers-raw-return-address

## Problem

`StackWalker::walkFP` and `StackWalker::walkDwarf`
(`ddprof-lib/src/main/cpp/stackWalker.cpp`) record the *raw* program counter for
every frame, including frames whose `pc` was loaded out of a return-address slot
or a link register. A return address is the address of the instruction **after**
the call, so it is not guaranteed to lie inside the calling function or inside
the DWARF/SFrame row that describes the call site.

Two distinct consequences, both range-lookup failures:

1. **Wrong unwind info (highest severity).** `walkDwarf:172-173` performs
   `profiler->findLibraryByAddress(pc)` and `cc->findFrameDesc(pc)` on the raw
   return address. `CodeCache::findFrameDesc` (`codeCache.cpp:482-509`) binary
   searches `_dwarf_table` by `target_loc = (const char*)pc - _text_base` and
   returns the exact `loc` match, else the largest row with `loc < target_loc`
   (`codeCache.cpp:502-503`). A DWARF row legitimately *begins* at a return
   address whenever the instruction after the call changes CFA state — an
   argument-cleanup `pop`, an epilogue restore, any `DW_CFA_advance_loc` landing
   there. In that ordinary case the raw return address selects the row that
   describes the CFA *after* the call returns, while unwinding the caller
   requires the state *at* the call. Wrong CFA rule → wrong `sp` → the
   `sp < prev_sp || sp >= prev_sp + MAX_FRAME_SIZE` guard at `:188` truncates
   the walk, or the walk continues with a corrupted `sp`. The blast radius is
   "every non-leaf frame whose next DWARF row starts at the return address", not
   only the `noreturn` boundary case.

2. **Wrong symbol / wrong image offset.** Downstream consumers treat
   `callchain[i]` as an instruction address:
   `Profiler::convertNativeTrace` (`profiler.cpp:451-455`,
   `findLibraryByAddress` + `CodeCache::binarySearch`) and
   `Profiler::populateRemoteFrame` (`profiler.cpp:353`,
   `pc_offset = pc - imageBase()`, shipped with the build-id for offline
   symbolication). When a call is the **last** instruction of its function —
   legal codegen when the callee is `noreturn`: `abort`, `exit`,
   `__assert_fail`, `__stack_chk_fail`, `__cxa_throw` (every C++ `throw`),
   `_Unwind_Resume` (every C++ cleanup path), `longjmp`, `std::terminate` — the
   return address is the first byte of the *next* symbol in link order, and
   `binarySearch` returns that unrelated symbol.

The existing mitigation covers only the benign half. `CodeCache::binarySearch`'s
fallback (`codeCache.cpp:288-299`) fires only when the search finds *no*
containing blob, i.e. when the return address landed in inter-function alignment
padding. When the next function begins **exactly** at the return address with no
padding, the main loop matches it and returns the wrong symbol; the fallback
never runs. That is precisely the case that needs fixing, and it makes the defect
build-dependent: the same source, compiled with different alignment, flips
between correct and wrong.

For remote symbolication the offset is off by one call site on **every** non-leaf
frame, not only at boundaries.

## Correct behaviour

Each walker must keep two distinct notions of "pc" inside its walk loop:

- **Walking pc** — raw, unchanged. This is the mechanical state of the unwinder
  and is the value that must be used wherever the *executed* or *resumed*
  address is what matters: the `DW_PC_OFFSET` pc advance
  (`stackWalker.cpp:199`), the `pc == prev_pc` no-progress guard (`:230`), the
  `JVMSupport::isJitCode(pc)` range test (`:75`, `:161`), the
  `JVMSupport::canUnwind(frame, pc)` test (`:75`, `:161`), and the Java-frame
  handoff `java_ctx->set(pc, sp, fp)` (`:77`, `:165`).
- **Attribution pc** — derived: `pc_is_return_address ? pc - 1 : pc`. Any byte
  inside the call instruction resolves correctly on both variable-width
  (x86_64) and fixed-width (aarch64, ppc64le, riscv64, loongarch64) ISAs, which
  is why gdb, perf, libunwind and Breakpad all subtract 1. This is the value
  stored into `callchain[]`, the value fed to the
  `findLibraryByAddress` / `findFrameDesc` pair (`:172-173`), and the value fed
  to the `DW_REG_PLT` stub-offset test (`:182`).

Because the *stored* value becomes the attribution address,
`convertNativeTrace`, `binarySearch` / `findNativeMethod` and
`populateRemoteFrame` become correct **with no change and no extra state
threaded through them**. That is the whole point of fixing at collection time.

### The predicate is "came out of a return-address slot", not `depth != 0`

`depth == 0` is not a sufficient test for "genuine interrupted PC". When
`ucontext == NULL` both walkers seed `pc = callerPC()`
(`stackWalker.cpp:33`, `:118`), and on every architecture except aarch64
`callerPC()` is `__builtin_return_address(0)` — itself a return address
(`arch.h:103` x86_64/i386, `:125` arm, `:169` ppc64le, `:194` riscv64,
`:215` loongarch64). Only aarch64 (`arch.h:146`,
`asm volatile("adr %0, .")`) yields a real instruction address.

That path is live in production, not test-only: `mallocTracer.cpp:354` and
`nativeSocketSampler.cpp:273` call `recordSample(NULL, …)` →
`Profiler::getNativeTrace(ucontext=NULL, …)` → `walkDwarf`/`walkFP(NULL, …)`
(`profiler.cpp:325`/`:329`). It is also exercised by `stackWalker_ut.cpp:241`
and `:256`.

Frame 0 on that path is never *symbolized* — both producers are hook-prefixed
samples and `convertNativeTrace` discards every frame up to the
`MARK_JAVA_PROFILER` boundary — but frame 0's `findFrameDesc` result supplies
the CFA rule that drives the **entire rest** of the walk. A wrong row at frame 0
mis-computes `sp` and can truncate or corrupt every frame after it, including
the frames that do get symbolized. So the seed must be classified per-arch
rather than assumed raw.

Each walker therefore carries an explicit boolean, seeded at entry and set at
**every** point where `pc` is replaced:

```
bool pc_is_ra = (ucontext == NULL) && CALLER_PC_IS_RETURN_ADDRESS;   // seed
...
pc_is_ra = true;    // at every pc replacement
```

#### `DW_PC_OFFSET` is a pc replacement and must set the flag

`:199` derives the next `pc` arithmetically rather than from memory, which makes
it easy to mis-read as "carry the flag through unchanged". That is wrong.
`DW_PC_OFFSET` is produced **only** from `DW_CFA_val_expression` on the
return-address column (`dwarf.cpp:455-460`:
`case DW_CFA_val_expression: if (getLeb() == DW_REG_PC) { int pc_off = parseExpression(); if (pc_off != 0) { fp_off = DW_PC_OFFSET | (pc_off << 1); } }`;
`DW_REG_PC` is the RA column — `dwarf.h:31` x86_64, `:43` i386, `:55` aarch64,
`:67` arm). The value `:199` computes is therefore the **caller's return
address**, regardless of what the current frame's `pc` was.

So when the current `pc` is a genuine interrupted PC (`pc_is_ra == false` — any
`ucontext`-supplied walk, and the `ucontext == NULL` seed on aarch64) and that
frame's FDE carries `DW_PC_OFFSET`, the derived caller `pc` *is* a return
address while a carried-through flag would still read `false`. The next
iteration would then store it raw into `callchain[]` and feed it raw to
`findLibraryByAddress` / `findFrameDesc` — the primary defect of this spec,
surviving on a live path. `:199` must set `pc_is_ra = true`.

With that, there is no path in either walker that turns a return-address `pc`
back into a genuine interrupted PC, so the flag is **monotone**: seeded once,
set to `true` at each pc replacement — memory slot, link register, or
`DW_PC_OFFSET` — and never cleared.

Under this rule the practical effect equals `depth != 0` on aarch64 and
`depth != 0 || ucontext == NULL` elsewhere — but the flag, not `depth`, is the
contract, both because of the seed and because the deferred `walkVM` will need
the same notion with a completely different relationship to `depth`.

### The PLT arm must use the same address as the FDE lookup

`stackWalker.cpp:182` — `sp += ((uintptr_t)pc & 15) >= 11 ? cfa_off * 2 : cfa_off;`
— sits inside `while (depth < actual_max_depth)` with **no depth guard**, and
`DW_REG_PLT` is produced at `dwarf.cpp:420` for any
`DW_CFA_def_cfa_expression` of length 11, with no leaf restriction. So "PLT is
only meaningful for the leaf" is unsupported. `findFrameDesc` and the
`DW_REG_PLT` arm are a pair keyed on the same address and must not be split:
since `findFrameDesc` must receive the adjusted address (that is the fix), the
PLT arm receives the adjusted address too. The low-bits test asks "how far into
the 16-byte PLT stub is the call site", and for a non-leaf PLT frame the call
site is at `pc - 1`. For the leaf (`pc_is_ra == false`) the value is unchanged,
so the historically-tuned `>= 11` threshold behaves exactly as today on the only
path it was tuned against.

`codeCache.cpp:504`'s `target_loc - _plt_offset < _plt_size` branch is not a
second decision on the same footing and needs no separate tuning: it is
reachable only when `low == 0`, i.e. when no DWARF row at all precedes
`target_loc`. It receives the adjusted address as a consequence of
`findFrameDesc` receiving it, which is correct and consistent.

### `isJitCode` keeps the raw pc — decision, not omission

After this change, within a single loop iteration frame N's JIT/Java-handoff
classification (`:75`, `:161`) uses the **raw** return address while its library
and FDE lookups two lines later (`:172-173`) use the **adjusted** address. The
invariant:

> `isJitCode`, `canUnwind` and `java_ctx->set` all operate on a *resume*
> address, not an attribution address. When the walk hands off to the JVM-side
> walker, the JVM must receive the exact address execution will resume at, so
> the raw return address is the only correct input. The decision of *whether* to
> hand off must be made with the same address that would be handed off, or the
> two could disagree about which code blob the frame belongs to.

Accepted consequences, bounded to one byte at nmethod boundaries:

- A return address equal to an nmethod's first byte is classified JIT and the
  native walk hands off, while `pc - 1` belongs to the preceding blob. Correct:
  the JVM resumes at that nmethod.
- A return address one byte past an nmethod's end is classified native, so the
  frame is stored, and `findLibraryByAddress(pc - 1)` resolves it into the JIT
  code cache — the frame is attributed to the JIT blob it actually called from,
  which is the *better* answer. Unchanged from today for the `isJitCode` half;
  only the attribution improves.

Making `isJitCode` use the adjusted address is explicitly **rejected**: it would
hand `java_ctx` an address one byte before the resume point, or require two
different addresses in the handoff path — a larger behaviour change on the
Java-frame boundary than this fix warrants.

## Constraints

- **Scope is closed.** The only production files this change edits:
  - `ddprof-lib/src/main/cpp/arch.h` — new `CALLER_PC_IS_RETURN_ADDRESS`
    constant, one per arch block.
  - `ddprof-lib/src/main/cpp/stackWalker.inline.h` — new shared
    `attributionPC` helper.
  - `ddprof-lib/src/main/cpp/stackWalker.cpp` — `walkFP` and `walkDwarf`.

  **Do not edit**, in this change:
  - `ddprof-lib/src/main/cpp/hotspot/hotspotSupport.cpp` (`walkVM`) — confirmed
    sibling, deferred (see Scope).
  - `ddprof-lib/src/main/cpp/perfEvents_linux.cpp` (`walkKernel`) — sibling with
    a mode-dependent premise, deferred.
  - `ddprof-lib/src/main/cpp/codeCache.cpp:288-299` — the `binarySearch`
    fallback. Leave exactly as is; still load-bearing for the two deferred
    walkers, which continue to supply raw return addresses.
  - `ddprof-lib/src/main/cpp/profiler.cpp` (`convertNativeTrace`,
    `populateRemoteFrame`) — these become correct *without* modification.
- **Signal-handler context.** Both walkers run inside a signal handler under
  `sigsetjmp` / `JmpCtxScope` crash protection. The fix must add no allocation,
  no locking, no new memory dereference. A `bool` local plus one predicated
  subtraction satisfies this.
- **Do not touch the crash-recovery `depth` bookkeeping** at `:58-70` /
  `:144-156`. `depth` is `volatile int` (`:42`, `:127`) solely because it is read
  after `siglongjmp`, not for sequencing. The existing
  `callchain[depth++] = pc;` form is well-defined C++; the only change is the
  *value* stored. The new `bool` must not be made `volatile` or coupled to
  `depth`.
- **Genuinely-interrupted PCs stay raw.** Only addresses that came out of a
  return-address slot, a link register, or `__builtin_return_address` get
  decremented. A `ucontext`-supplied PC and an aarch64 `callerPC()` are real
  instruction addresses.
- **Remote-symbolication wire format is unchanged.** `RemoteFramePacker::pack`
  layout, `BCI_NATIVE_FRAME_REMOTE`, and the build-id contract stay as-is; only
  the *value* of `pc_offset` shifts by one byte for non-leaf frames.
- **Mark-based walk termination must keep working.** `NativeFunc::read_mark`
  reads the mark from the symbol name returned by `binarySearch`; a
  correctly-attributed address returns the same or a *more* correct symbol, so
  `MARK_JAVA_PROFILER` / `MARK_THREAD_ENTRY` / `MARK_INTERPRETER` termination is
  preserved — including the hook-prefix skip logic in `profiler.cpp:449-475`.
  Verify by test, do not assume.
- **"index 0 is the leaf" is never a valid downstream rule.**
  `profiler.cpp:317-331` fills `callchain[0..native_frames)` from
  `PerfEvents::walkKernel` first, then appends the `walkDwarf`/`walkFP` output.
  So `callchain[0]` is not reliably the interrupted user PC — an additional
  reason the adjustment must happen inside each producer, where leaf-ness is
  locally known.
- **The `-1` cannot newly trip the unsigned `target_loc` wrap.**
  `findFrameDesc` computes `u32 target_loc = (const char*)pc - _text_base`
  (`codeCache.cpp:487`) with no lower-bound check; an address below `_text_base`
  wraps to a huge value and the last row is returned. A return address is never
  the first byte of a `CodeCache`'s text — a call instruction must have preceded
  it inside the same image — so `pc - 1` stays within the image. The pre-existing
  missing lower-bound check is not touched.
- **Style.** `arch.h` declares per-arch scalars as namespace-scope `const`;
  follow that. Express the attribution rule **once**, as an inline helper in
  `stackWalker.inline.h` next to the existing helpers, so the arch-dependent
  `callerPC()` nuance lives in exactly one place and the deferred
  `walkVM`/`walkKernel` work can adopt it without redefining the rule. Compute
  the adjusted value into a named local rather than nesting the helper call
  inside the `callchain[depth++] = …` store (readability only).

## Scope

### Primary fixes

- `ddprof-lib/src/main/cpp/arch.h` (6 arch blocks) — *missing arch predicate* —
  add `const bool CALLER_PC_IS_RETURN_ADDRESS`, `false` for aarch64 (`:146`
  uses `adr`, a real instruction address), `true` for x86_64/i386 (`:103`), arm
  (`:125`), ppc64le (`:169`), riscv64 (`:194`), loongarch64 (`:215`) — all
  `__builtin_return_address(0)`.
- `ddprof-lib/src/main/cpp/stackWalker.inline.h` — *rule expressed nowhere* —
  add `attributionPC(const void* pc, bool pc_is_return_address)` returning
  `pc_is_return_address ? (const void*)((const char*)pc - 1) : pc`.
- `ddprof-lib/src/main/cpp/stackWalker.cpp:81` (`walkFP`) — *off-by-one address
  semantics* — store the attribution pc, not the raw `pc`. Seed `pc_is_ra` at
  `:32-40`; set it `true` after the return-address load at `:93`.
- `ddprof-lib/src/main/cpp/stackWalker.cpp:169` (`walkDwarf`) — same defect,
  same store. Seed `pc_is_ra` at `:117-125`; set it `true` after the
  return-address load at `:214`, after the link-register recovery at `:216`, and
  in the `DW_PC_OFFSET` branch at `:198-199` (see "`DW_PC_OFFSET` is a pc
  replacement" above — that branch yields the RA column's value, so the derived
  pc is a return address even when the current one was not).
- `ddprof-lib/src/main/cpp/stackWalker.cpp:172-173` (`walkDwarf`) — *wrong
  unwind info selected*; the highest-severity instance. Feed the attribution pc
  to **both** `findLibraryByAddress` and `findFrameDesc` — at a library boundary
  the raw return address can select the wrong `CodeCache` entirely.
- `ddprof-lib/src/main/cpp/stackWalker.cpp:182` (`walkDwarf`, `DW_REG_PLT`) —
  *address inconsistent with the FDE lookup it pairs with* — feed the same
  attribution pc to the `(uintptr_t)pc & 15) >= 11` stub-offset test.

Explicitly left reading the raw `pc`: `:75`, `:77`, `:161`, `:165`
(`isJitCode` / `canUnwind` / `java_ctx->set`), `:199` (the `DW_PC_OFFSET`
*arithmetic* — `pc + (fp_off >> 1)` operates on the walking pc; only the flag
changes there), `:230` (`pc == prev_pc` no-progress guard), `:93`/`:214`
(`inDeadZone` on the freshly loaded slot value).

### Auto-expanded sibling fixes

Defect class: *a return address is consumed as if it were an
executing-instruction address by a range-based lookup (symbol table, FDE table,
or image offset)*. Every producer of a native PC chain was checked. Two
confirmed siblings; both **deferred**, recorded so the follow-up is grounded and
so a later report does not attribute their state to this change.

- `ddprof-lib/src/main/cpp/hotspot/hotspotSupport.cpp:872-873` (`walkVM`) —
  *return address consumed by a range-based FDE lookup* — **confirmed reachable,
  deferred.** Evidence: it duplicates the whole DWARF loop —
  `findLibraryByAddress`/`findFrameDesc` at `:872-873`, `DW_REG_PLT` at `:895`,
  `DW_PC_OFFSET` at `:911` — and symbolizes through
  `profiler->resolveNativeFrameForWalkVM((uintptr_t)pc, …)` at `:735` and again
  for `prev_native_pc` at `:845`. Same raw-return-address exposure, same
  wrong-FDE severity.
  ```
  FLOW: signal handler → Profiler::getNativeTrace (_cstack >= CSTACK_VM)
        → HotspotSupport::walkVM → loop at :860+ → findFrameDesc(raw pc)
        and resolveNativeFrameForWalkVM(raw pc)
  PRECONDITION: a DWARF row or a symbol boundary begins exactly at the
        return address (ordinary CFA-advance case, or a noreturn tail call)
  REACHABLE: yes — CSTACK_VM is a supported cstack mode
  CONCLUSION: same severity as the primary walkDwarf instance; deferred
        because leaf-ness is NOT depth == 0 here — depth counts emitted frames
        including Java pseudo-frames and is reset to 0 at the hook boundary,
        and pc is replaced from stack slots in several places (unwindPrologue,
        unwindStub, the frameSize() fallback at :674-676, the nm->isEntryFrame
        anchor path, the anchor-recovery paths around :492-521). Threading a
        correct pc_is_return_address through all of those is its own design
        with its own CSTACK_VM verification, which this change's acceptance
        criteria do not cover. Folding it in would make this change
        unverifiable on the hottest sampling path.
  ```
- `ddprof-lib/src/main/cpp/perfEvents_linux.cpp:1068-1077` (`walkKernel`) —
  *return address stored raw into the callchain* — **reachable but
  mode-dependent, deferred.** Evidence: `callchain[depth++] = iptr;` at `:1076`
  stores kernel-supplied `ip` values verbatim. What the callchain *contains*
  depends on `_cstack`, and a single uniform rule is wrong:
  ```
  FLOW: PerfEvents::walkKernel → ring-buffer PERF_RECORD_SAMPLE callchain loop
        → callchain[depth++] = iptr → Profiler::convertNativeTrace symbolizes it
  PRECONDITION: mode-dependent —
    CSTACK_FP / CSTACK_DWARF: attr.exclude_callchain_user = 1 (:874-876,
      :878-880; the CPU-event config also sets it unconditionally at :634), so
      the callchain is KERNEL-ONLY. The first entry is the interrupted kernel
      PC; every entry after it is a kernel return address. A
      PERF_CONTEXT_USER-marker-based rule is NOT applicable — there is no user
      half to mark.
    CSTACK_DEFAULT (the only mode not setting exclude_callchain_user, since
      CSTACK_DEFAULT < CSTACK_FP in arguments.h:65): the kernel-supplied USER
      callchain is present AND getNativeTrace still appends walkFP output
      (profiler.cpp:329), so the interrupted user PC is emitted twice and the
      user portion duplicates the FP walk. That is a distinct pre-existing
      defect which must be resolved first — the leaf rule depends on which
      producer owns the user frames.
    CSTACK_LBR: the entries at :1089, :1100, :1106 are BRANCH source/target
      addresses, not return addresses — `from` is the branch instruction itself
      and `to` is a real branch target — so neither is ever decremented, here
      or in a follow-up.
  REACHABLE: yes for CSTACK_FP/CSTACK_DWARF (kernel frames misattributed at
        kernel-symbol boundaries); no — structurally inapplicable for CSTACK_LBR
  CONCLUSION: real sibling for the kernel-only modes, but the correct rule
        cannot be specified until the CSTACK_DEFAULT duplicate-user-frames
        defect is resolved. Deferred. Note that the loop consumes and drops the
        ip >= PERF_CONTEXT_MAX markers without incrementing depth, so any
        context-aware rule must key off them before they are dropped.
  ```
- `ddprof-lib/src/main/cpp/codeCache.cpp:288-299` — **not a defect; leave
  exactly as is.** Verified as the bug report describes: a
  `_blobs[low - 1]._end == address` clause (return address past the end) plus an
  independent zero-size-symbol clause. The return-address clause becomes partly
  redundant for the two walkers fixed here, but stays load-bearing for `walkVM`
  and `walkKernel`. Removing it is out of scope for this change and for the
  follow-ups until both deferred walkers are fixed.
- **No structural siblings** in `dwarf.cpp` / `sframe.cpp` (table *producers*,
  keyed by `loc`, address-semantics-agnostic) or in JFR-side symbolization
  (consumes stored names and packed offsets, not PCs).

## Assumptions

Resolved autonomously; this was an unattended run, so the two open questions the
design raised were decided rather than escalated. Both are recorded here and
should be restated in the PR description.

- **Arch-dependent seed is the intent.** Add `CALLER_PC_IS_RETURN_ADDRESS` and
  leave `callerPC()` alone, rather than normalizing `callerPC()` so every arch
  returns an instruction address. Ground: `callerPC()` has other callers whose
  expectations would silently change, and the aarch64 `adr` form cannot be made
  to *produce* a return address without a semantic change in the opposite
  direction. The consequence — the malloc/socket sampling paths
  (`mallocTracer.cpp:354`, `nativeSocketSampler.cpp:273`) classify their seed
  frame differently per arch — is correct rather than accidental: the seed
  genuinely *is* a return address on those arches and genuinely is not on
  aarch64. Confidence ≈ 85%.
- **Remote symbolication tolerates a mid-instruction offset.** `pc_offset`
  (`profiler.cpp:353`) crosses a boundary this repo does not own and no offline
  resolver is present here to cite. Assumed safe because every ELF/DWARF
  resolver in use for this purpose (`addr2line`, `blazesym`, `symbolic`,
  Breakpad) is range-based, resolves `[low, high)` symbol and line ranges, and
  is fed `pc - 1` by the very tools this fix imitates (`perf script`, `gdb`).
  A mid-instruction offset resolves to the same symbol and the same line as the
  call site — which is the *intended* improvement, since today's offset points
  one call site too far. **Action for the PR: name the backend consumer and get
  this confirmed rather than assumed.** Confidence ≈ 80%.
- Keep the walking `pc` raw and derive a separate attribution address rather
  than decrementing `pc` in place. In-place decrement would silently shift the
  `DW_PC_OFFSET` arithmetic, the `pc == prev_pc` no-progress guard, and the JIT
  handoff address. Confidence ≈ 98%.
- Use the adjusted address for *both* halves of the unwind lookup
  (`findLibraryByAddress` and `findFrameDesc`), not just `findFrameDesc`: at a
  library boundary the raw return address can select the wrong `CodeCache`
  entirely. Confidence ≈ 95%.
- Treat every pc loaded from a return-address slot uniformly, including frames
  recovered via the link register (`:216`) and via `DW_PC_OFFSET`. Where such an
  address is in fact an interrupted PC (a signal-trampoline crossing), `-1`
  still resolves to the same function unless the interrupted instruction is the
  very first byte of a function; the uniform rule matches `perf`/`gdb` and is
  strictly better than the status quo. Confidence ≈ 92%.
- `isJitCode` / `canUnwind` / `java_ctx` keep the raw pc, and the resulting
  same-iteration disagreement with the attribution lookups is accepted and
  bounded to one byte at nmethod boundaries. Confidence ≈ 90%.
- **The boundary regression test can be built without touching the build
  system.** The gtest task compiles `**/*.cpp` only
  (`build-logic/conventions/src/main/kotlin/com/datadoghq/native/gtest/GtestTaskBuilder.kt:121`),
  and the repo contains no `.S` sources, so a separate hand-written assembly
  translation unit or a purpose-built shared library would require build-logic
  changes. Instead, emit the two provably-adjacent symbols from a **top-level
  `asm()` block inside the test `.cpp`** — same assembler, no `.align`/`.p2align`
  between the two `.globl` labels, so adjacency is structural — and assert
  adjacency at runtime before asserting the walk result. This satisfies the
  design's requirement that the fixture not rely on compiler-chosen alignment,
  which is exactly what masks the bug today. Confidence ≈ 88%.
