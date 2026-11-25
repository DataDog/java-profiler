# Untrusted Binary Parsing

Applies to code that decodes ELF images and DWARF unwind data: `ElfParser` in
`symbols_linux.cpp`, `DwarfParser` in `dwarf.h`/`dwarf.cpp`. Every offset, size, count,
index and LEB128 value read from the image is attacker-controlled.

## Rules

1. **Validate in integer space, then form the pointer.** Check
   `off > size || len > size - off` before computing `base + off`. Never form
   `base + off` and range-check the result: pointer arithmetic past one-past-end is UB,
   the `asan` preset aborts on it (`-fsanitize=pointer-overflow -fno-sanitize-recover=all`
   in `ConfigurationPresets.kt`), and a wrapped value can land back inside the image and
   pass the check. Reference: `ElfParser::contentAt()` and `phdrAt()`. The same applies to
   subtraction: check `cie_offset > fde_start - _section_start` before `fde_start - cie_offset`.
2. **One accessor per kind of read, on every path.** Once a parser has a bounded accessor
   (`inImage()`, `sectionAt()`, `phdrAt()`, `contentAt()`, `strAt()`, `canRead()`), every
   read of that kind goes through it — file-section and dynamic-section paths, section and
   program headers, `.rela.plt` and `.rela.dyn` loops. Bound a symbol index by the table
   size before dereferencing the entry. Before finishing, grep the file for the raw form
   (`strtab +`, `_ptr +=`, `e_phoff`) and route or justify each hit.
3. **Clamp after an advance by a decoded value.** After `_ptr += getLeb()` clamp `_ptr` to
   `_section_end`; a bounded overload that takes an `end` argument clamps `end` to
   `_section_end` on entry (`getLeb(const char* end)`, `getSLeb(const char* end)`).
4. **A missing size field gets a finite, logged fallback.** When a size the bounds depend
   on is absent (e.g. no `DT_STRSZ`), fall back to a named finite cap and log it with
   `Log::warn`; never fall back to `SIZE_MAX` (unbounded `memchr`) and never let a zero size
   silently reject every entry.
5. **Pin each bound with a gtest.** Add the case to `ddprof-lib/src/test/cpp`
   (`elfparser_ut.cpp`, `dwarf_ut.cpp`) and reach the branch: set the flag that gates it
   (e.g. `use_debug=true` for `addRelocationSymbols`). Fuzz targets
   (`ddprof-lib/src/test/fuzz/`) run nightly and on the `test:fuzz` label only, so they do
   not replace the gtest. Pair each rejected input with an accepted one, because a
   result such as `count() == 0` holds for any early exit.
