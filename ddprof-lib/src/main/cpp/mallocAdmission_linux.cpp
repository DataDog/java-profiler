/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Admission-time ELF image inspection (Linux only). Reads the dynamic symbol
// table of a loaded image through its program headers and decides whether the
// image defines the ddprof marker names as exported ordinary functions.
//
// Everything here runs inside a dl_iterate_phdr callback (see classifyOwners
// below): no allocation, no lock, no log, no loader call, no TLS touch and no
// call into an inspected image — only internal-linkage code and inline
// compiler builtins. All reads stay inside file-backed readable PT_LOAD
// ranges; every derived address or size is overflow-checked before use; every
// failed check yields a named INDETERMINATE reason (fail closed).
#ifdef __linux__

#include "mallocAdmission_linux.h"

#include <link.h>

#include "arch.h"
#include "loadedImage_linux.h"

namespace {

// The two marker names whose exported function definitions identify a ddprof
// hook-owner image. Lengths are compile-time constants; names are compared by
// a bounded byte loop, never by library calls.
constexpr size_t MARKER_START_LEN = sizeof("ddprof_start_profiling") - 1;
constexpr size_t MARKER_STOP_LEN = sizeof("ddprof_stop_profiling") - 1;

static bool addChecked(uintptr_t base, size_t offset, uintptr_t& out) {
    return !__builtin_add_overflow(base, static_cast<uintptr_t>(offset), &out);
}

// True if [addr, addr + size) lies inside the file-backed part of a PT_LOAD
// segment that also has the PF_R flag. LoadedImage::readable() alone does not
// test PF_R — the admission reader must not treat a mapping it may not read
// as readable, so the flag test lives here and not in the moved class.
bool readableR(const ElfProgramHeader* ph, int phnum, uintptr_t load_bias, uintptr_t addr, size_t size) {
    for (int i = 0; i < phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (!(ph[i].p_flags & PF_R)) continue;
        uintptr_t start;
        if (__builtin_add_overflow(load_bias, (uintptr_t)ph[i].p_vaddr, &start)) continue;
        if (addr < start) continue;
        uintptr_t off = addr - start;
        if (off > ph[i].p_filesz) continue;
        if (size > ph[i].p_filesz - off) continue;
        return true;
    }
    return false;
}

// The dynamic-section-derived view one image classification is built on.
// failure != NONE means the image could not be inspected far enough and the
// classification is already decided (INDETERMINATE with that reason); the
// remaining fields are then meaningless.
struct ImageMetadata {
    AdmissionReason failure;
    uintptr_t symtab;    // normalized DT_SYMTAB value (symbol entries are sizeof(ElfW(Sym)) apart)
    uintptr_t strtab;    // normalized DT_STRTAB value
    size_t strsz;        // DT_STRSZ: the whole string table must be readable
    bool has_hash;       // a usable hash table kind was found
    bool gnu_hash;       // true: DT_GNU_HASH; false: DT_HASH (no fallback from a malformed GNU table)
    uintptr_t hash;      // normalized hash-table address
};

// Resolves the metadata stage of the marker lookup: locate PT_DYNAMIC, read
// the dynamic entries up to DT_NULL within the segment's file-backed range,
// normalize pointers with LoadedImage::dynamicPointer() (glibc relocates them
// in place; musl and the vDSO do not) and require DT_SYMTAB, DT_STRTAB,
// DT_STRSZ and a hash table. Every path is complete: failure carries the
// named reason (NO_DYNAMIC, BAD_DYNAMIC, NO_HASH_TABLE).
ImageMetadata resolveMetadata(const LoadedImage& image, const ElfProgramHeader* ph, int phnum,
                              uintptr_t load_bias) {
    ImageMetadata md;
    md.failure = NONE;
    md.symtab = 0;
    md.strtab = 0;
    md.strsz = 0;
    md.has_hash = false;
    md.gnu_hash = false;
    md.hash = 0;

    const ElfProgramHeader* dyn = image.find(PT_DYNAMIC);
    if (dyn == NULL) {
        md.failure = NO_DYNAMIC;
        return md;
    }
    uintptr_t dyn_addr;
    if (__builtin_add_overflow(load_bias, (uintptr_t)dyn->p_vaddr, &dyn_addr) ||
        !readableR(ph, phnum, load_bias, dyn_addr, dyn->p_filesz)) {
        md.failure = BAD_DYNAMIC;
        return md;
    }

    const ElfW(Dyn)* entries = (const ElfW(Dyn)*)dyn_addr;
    size_t count = dyn->p_filesz / sizeof(ElfW(Dyn));
    // Separate slots for the two hash-table tags: with one shared slot the
    // later DT_HASH entry would overwrite the DT_GNU_HASH address, and a GNU
    // walk would silently run against the SysV table.
    uintptr_t symtab_raw = 0, strtab_raw = 0, gnu_raw = 0, sysv_raw = 0;
    bool has_symtab = false, has_strtab = false, has_strsz = false, has_gnu = false, has_sysv = false;
    for (size_t i = 0; i < count; i++) {
        if (entries[i].d_tag == DT_NULL) break;
        switch (entries[i].d_tag) {
            case DT_SYMTAB:
                symtab_raw = entries[i].d_un.d_ptr;
                has_symtab = true;
                break;
            case DT_STRTAB:
                strtab_raw = entries[i].d_un.d_ptr;
                has_strtab = true;
                break;
            case DT_STRSZ:
                md.strsz = (size_t)entries[i].d_un.d_val;
                has_strsz = true;
                break;
            case DT_GNU_HASH:
                gnu_raw = entries[i].d_un.d_ptr;
                has_gnu = true;
                break;
            case DT_HASH:
                sysv_raw = entries[i].d_un.d_ptr;
                has_sysv = true;
                break;
            default:
                break;
        }
    }

    if (!has_symtab || !has_strtab || !has_strsz) {
        md.failure = BAD_DYNAMIC;
        return md;
    }
    if (!image.dynamicPointer(symtab_raw, md.symtab) || !image.dynamicPointer(strtab_raw, md.strtab)) {
        md.failure = BAD_DYNAMIC;
        return md;
    }
    if (!readableR(ph, phnum, load_bias, md.strtab, md.strsz)) {
        md.failure = BAD_DYNAMIC;
        return md;
    }
    // DT_GNU_HASH when present, DT_HASH only otherwise: a malformed GNU table
    // is reported by the walk, never papered over with the SysV one.
    if (has_gnu) {
        md.has_hash = true;
        md.gnu_hash = true;
        if (!image.dynamicPointer(gnu_raw, md.hash)) md.failure = BAD_HASH_TABLE;
    } else if (has_sysv) {
        md.has_hash = true;
        md.gnu_hash = false;
        if (!image.dynamicPointer(sysv_raw, md.hash)) md.failure = BAD_HASH_TABLE;
    } else {
        md.failure = NO_HASH_TABLE;
    }
    return md;
}

// Compares at most len marker bytes and the following terminator. A shorter or
// longer unrelated symbol is a mismatch without scanning its remaining string.
// The inline byte loop avoids library calls from the loader callback.
inline bool markerNameEquals(const ImageMetadata& md, size_t st_name, const char* name, size_t len,
                             bool& matches, AdmissionReason& fail) {
    matches = false;
    if (st_name >= md.strsz) {
        fail = BAD_SYMBOL;
        return false;
    }
    uintptr_t candidate;
    if (!addChecked(md.strtab, st_name, candidate)) {
        fail = BAD_SYMBOL;
        return false;
    }
    size_t remaining = md.strsz - st_name;
    for (size_t i = 0; i < len; i++) {
        if (i >= remaining) {
            fail = BAD_SYMBOL;
            return false;
        }
        uintptr_t char_addr;
        if (!addChecked(candidate, i, char_addr)) {
            fail = BAD_SYMBOL;
            return false;
        }
        const char value = *reinterpret_cast<const char*>(char_addr);
        if (value == '\0' || value != name[i]) return true;
    }
    if (len >= remaining) {
        fail = BAD_SYMBOL;
        return false;
    }
    uintptr_t terminator;
    if (!addChecked(candidate, len, terminator)) {
        fail = BAD_SYMBOL;
        return false;
    }
    matches = *reinterpret_cast<const char*>(terminator) == '\0';
    return true;
}

// The GNU/Linux hash function used by DT_GNU_HASH tables.
inline uint32_t gnuHash(const char* name, size_t len) {
    uint32_t h = 5381;
    for (size_t i = 0; i < len; i++) {
        h = h * 33 + (unsigned char)name[i];
    }
    return h;
}

// The System V hash function used by DT_HASH tables.
inline uint32_t sysvHash(const char* name, size_t len) {
    uint32_t h = 0;
    for (size_t i = 0; i < len; i++) {
        h = (h << 4) + (unsigned char)name[i];
        uint32_t g = h & 0xf0000000u;
        if (g != 0) h ^= g >> 24;
        h &= ~g;
    }
    return h;
}

// One 32-bit hash-table word, read only inside a file-backed readable PT_LOAD
// range whose segment also has PF_R.
inline bool readU32(const ElfProgramHeader* ph, int phnum, uintptr_t load_bias, uintptr_t addr,
                    uint32_t& out) {
    if (!readableR(ph, phnum, load_bias, addr, sizeof(uint32_t))) return false;
    out = *(const uint32_t*)addr;
    return true;
}

// What one marker-name lookup found in one image: exported ordinary function
// definitions (qualifying) and same-name definitions of any other symbol type
// (wrong-kind). Ignored entries (undefined, local binding, hidden/internal
// visibility) are counted by neither.
struct MarkerFindings {
    int qualifying;
    int wrong_kind;
};

// Applies the per-entry ownership rules to one hash-matching symbol. A name
// mismatch, or an entry the ownership rules ignore, is not a finding.
bool visitSymbol(const ImageMetadata& md, const ElfProgramHeader* ph, int phnum, uintptr_t load_bias,
                 uintptr_t index, const char* name, size_t len, MarkerFindings& out,
                 AdmissionReason& fail) {
    uintptr_t offset, sym_addr;
    if (__builtin_mul_overflow(index, (uintptr_t)sizeof(ElfW(Sym)), &offset) ||
        __builtin_add_overflow(md.symtab, offset, &sym_addr)) {
        fail = BAD_SYMBOL;
        return false;
    }
    if (!readableR(ph, phnum, load_bias, sym_addr, sizeof(ElfW(Sym)))) {
        fail = BAD_SYMBOL;
        return false;
    }
    const ElfW(Sym)* sym = (const ElfW(Sym)*)sym_addr;
    bool matches;
    if (!markerNameEquals(md, sym->st_name, name, len, matches, fail)) return false;
    if (!matches) return true;
    if (sym->st_shndx == SHN_UNDEF) return true;
    unsigned int bind = ELF64_ST_BIND(sym->st_info);
    unsigned int visibility = ELF64_ST_VISIBILITY(sym->st_other);
    if ((bind != STB_GLOBAL && bind != STB_WEAK) || visibility == STV_HIDDEN ||
        visibility == STV_INTERNAL) {
        return true;
    }
    if (ELF64_ST_TYPE(sym->st_info) == STT_FUNC) {
        out.qualifying++;
    } else {
        out.wrong_kind++;
    }
    return true;
}

// Walks one DT_GNU_HASH bucket for one marker name. Bloom words are skipped:
// their size only locates the bucket array. A zero bucket means the name is
// absent; every hash match in the chain is visited up to the chain-end bit.
bool lookupGnu(const ImageMetadata& md, const ElfProgramHeader* ph, int phnum, uintptr_t load_bias,
               const char* name, size_t len, MarkerFindings& out, AdmissionReason& fail) {
    out.qualifying = 0;
    out.wrong_kind = 0;
    uintptr_t symoffset_addr, bloom_size_addr, bloom_base;
    if (!addChecked(md.hash, 4, symoffset_addr) || !addChecked(md.hash, 8, bloom_size_addr) ||
        !addChecked(md.hash, 16, bloom_base)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uint32_t nbuckets, symoffset, bloom_size;
    if (!readU32(ph, phnum, load_bias, md.hash, nbuckets) ||
        !readU32(ph, phnum, load_bias, symoffset_addr, symoffset) ||
        !readU32(ph, phnum, load_bias, bloom_size_addr, bloom_size)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uintptr_t offset, buckets;
    if (__builtin_mul_overflow((uintptr_t)bloom_size, sizeof(ElfW(Addr)), &offset) ||
        !addChecked(bloom_base, offset, buckets)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    if (nbuckets == 0) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uintptr_t index_offset, bucket_addr;
    if (__builtin_mul_overflow((uintptr_t)(gnuHash(name, len) % nbuckets), sizeof(uint32_t), &index_offset) ||
        __builtin_add_overflow(buckets, index_offset, &bucket_addr)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uint32_t bucket;
    if (!readU32(ph, phnum, load_bias, bucket_addr, bucket)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    if (bucket == 0) return true; // absent from this table
    if (bucket < symoffset) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uintptr_t chains;
    if (__builtin_mul_overflow((uintptr_t)nbuckets, sizeof(uint32_t), &offset) ||
        !addChecked(buckets, offset, chains)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uint32_t hash = gnuHash(name, len);
    uintptr_t chain_index = (uintptr_t)(bucket - symoffset);
    for (int steps = 0; steps < MAX_HASH_CHAIN_STEPS; steps++) {
        uintptr_t chain_offset, chain_addr;
        if (__builtin_mul_overflow(chain_index, sizeof(uint32_t), &chain_offset) ||
            __builtin_add_overflow(chains, chain_offset, &chain_addr)) {
            fail = BAD_HASH_TABLE;
            return false;
        }
        uint32_t chain;
        if (!readU32(ph, phnum, load_bias, chain_addr, chain)) {
            fail = BAD_HASH_TABLE;
            return false;
        }
        if ((chain | 1u) == (hash | 1u)) {
            uintptr_t sym_index;
            if (__builtin_add_overflow((uintptr_t)symoffset, chain_index, &sym_index)) {
                fail = BAD_SYMBOL;
                return false;
            }
            if (!visitSymbol(md, ph, phnum, load_bias, sym_index, name, len, out, fail)) return false;
        }
        if (chain & 1u) return true; // end of chain
        chain_index++;
    }
    fail = CHAIN_LIMIT;
    return false;
}

// Walks one DT_HASH bucket chain for one marker name. Words are 32-bit on
// x86_64 and aarch64. Index 0 ends the chain; the walk also stops after
// MAX_HASH_CHAIN_STEPS entries and after nchain entries (cycle bound).
bool lookupSysv(const ImageMetadata& md, const ElfProgramHeader* ph, int phnum, uintptr_t load_bias,
                const char* name, size_t len, MarkerFindings& out, AdmissionReason& fail) {
    out.qualifying = 0;
    out.wrong_kind = 0;
    uintptr_t nchain_addr, buckets;
    if (!addChecked(md.hash, 4, nchain_addr) || !addChecked(md.hash, 8, buckets)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uint32_t nbucket, nchain;
    if (!readU32(ph, phnum, load_bias, md.hash, nbucket) ||
        !readU32(ph, phnum, load_bias, nchain_addr, nchain)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    if (nbucket == 0) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uintptr_t offset, chains, bucket_addr;
    if (__builtin_mul_overflow((uintptr_t)nbucket, sizeof(uint32_t), &offset) ||
        !addChecked(buckets, offset, chains)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    if (__builtin_mul_overflow((uintptr_t)(sysvHash(name, len) % nbucket), sizeof(uint32_t), &offset) ||
        __builtin_add_overflow(buckets, offset, &bucket_addr)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    uint32_t index;
    if (!readU32(ph, phnum, load_bias, bucket_addr, index)) {
        fail = BAD_HASH_TABLE;
        return false;
    }
    for (uint64_t steps = 0; steps < (uint64_t)MAX_HASH_CHAIN_STEPS && steps < nchain; steps++) {
        if (index == 0) return true; // end of chain / absent
        if (index >= nchain) {
            fail = BAD_HASH_TABLE;
            return false;
        }
        if (!visitSymbol(md, ph, phnum, load_bias, (uintptr_t)index, name, len, out, fail)) return false;
        uintptr_t chain_offset, chain_addr;
        if (__builtin_mul_overflow((uintptr_t)index, sizeof(uint32_t), &chain_offset) ||
            __builtin_add_overflow(chains, chain_offset, &chain_addr)) {
            fail = BAD_HASH_TABLE;
            return false;
        }
        if (!readU32(ph, phnum, load_bias, chain_addr, index)) {
            fail = BAD_HASH_TABLE;
            return false;
        }
    }
    fail = CHAIN_LIMIT;
    return false;
}

// The complete single-image classification: metadata stage, then one bounded
// hash walk per marker name, then the marker aggregation. This is the
// implementation the dl_iterate_phdr callback calls; the public
// ElfMarkerLookup::classifyImage below only forwards to it for tests.
AdmissionVerdict classifyImageInternal(const void* phdrs, int phnum, uintptr_t load_bias) {
    const ElfProgramHeader* ph = (const ElfProgramHeader*)phdrs;
    LoadedImage image(ph, phnum, load_bias);
    ImageMetadata md = resolveMetadata(image, ph, phnum, load_bias);
    if (md.failure != NONE) {
        AdmissionVerdict verdict = {INDETERMINATE, md.failure};
        return verdict;
    }
    MarkerFindings start = {0, 0}, stop = {0, 0};
    AdmissionReason fail = NONE;
    if (md.gnu_hash) {
        if (!lookupGnu(md, ph, phnum, load_bias, "ddprof_start_profiling", MARKER_START_LEN, start, fail)) {
            AdmissionVerdict verdict = {INDETERMINATE, fail};
            return verdict;
        }
        if (!lookupGnu(md, ph, phnum, load_bias, "ddprof_stop_profiling", MARKER_STOP_LEN, stop, fail)) {
            AdmissionVerdict verdict = {INDETERMINATE, fail};
            return verdict;
        }
    } else {
        if (!lookupSysv(md, ph, phnum, load_bias, "ddprof_start_profiling", MARKER_START_LEN, start, fail)) {
            AdmissionVerdict verdict = {INDETERMINATE, fail};
            return verdict;
        }
        if (!lookupSysv(md, ph, phnum, load_bias, "ddprof_stop_profiling", MARKER_STOP_LEN, stop, fail)) {
            AdmissionVerdict verdict = {INDETERMINATE, fail};
            return verdict;
        }
    }
    // A wrong-kind or ambiguous definition fails the image closed even when
    // the other marker qualifies cleanly: partial recognition must never
    // look like a clean ddprof image.
    if (start.wrong_kind > 0 || stop.wrong_kind > 0) {
        AdmissionVerdict verdict = {INDETERMINATE, WRONG_KIND_MARKER};
        return verdict;
    }
    if (start.qualifying > 1 || stop.qualifying > 1) {
        AdmissionVerdict verdict = {INDETERMINATE, AMBIGUOUS_MARKER};
        return verdict;
    }
    bool start_present = start.qualifying == 1;
    bool stop_present = stop.qualifying == 1;
    if (start_present && stop_present) {
        AdmissionVerdict verdict = {DDPROF, NONE};
        return verdict;
    }
    if (start_present != stop_present) {
        AdmissionVerdict verdict = {INDETERMINATE, PARTIAL_MARKERS};
        return verdict;
    }
    AdmissionVerdict verdict = {NOT_RECOGNIZED, NONE};
    return verdict;
}

} // namespace

namespace ElfMarkerLookup {

AdmissionVerdict classifyImage(const void* phdrs, int phnum, uintptr_t load_bias) {
    return classifyImageInternal(phdrs, phnum, load_bias);
}

} // namespace ElfMarkerLookup

namespace {

// Fixed stack context one dl_iterate_phdr() walk carries through the
// callback. assigned[] marks targets whose verdict was already fixed by a
// previous object; classification is repeated only for objects that still
// contain at least one unassigned target.
struct OwnerWalkContext {
    const void* const* targets;
    AdmissionVerdict* verdicts;
    bool assigned[MALLOC_ADMISSION_MAX_TARGETS];
    int count;
    int unassigned;
    int images_classified;
};

// One reported object: contains the targets it owns, classifies the object
// once, and assigns that verdict to every target it contains (per-attempt
// owner deduplication; a verdict is reused only within this callback
// invocation, which is the only moment the object is known mapped).
//
// Callback contract: no allocation, no lock, no log (including TEST_LOG), no
// loader call, no TLS touch, no call into an inspected image, marker or
// IFUNC resolver, and no call through a PLT/GOT entry — only internal-
// linkage code and inline compiler builtins. The image classification is the
// internal-linkage classifier; the externally visible
// ElfMarkerLookup::classifyImage wrapper is never called from here.
int ownerWalkCallback(struct dl_phdr_info* info, size_t size, void* data) {
    OwnerWalkContext* ctx = (OwnerWalkContext*)data;
    (void)size;

    // Containment pass: overflow-checked PT_LOAD membership for each
    // unassigned target. Target pointers are stripped (PAC) before the
    // comparison; dlpi_addr and p_vaddr are loader-normalized bases.
    bool contains[MALLOC_ADMISSION_MAX_TARGETS];
    bool any = false;
    for (int t = 0; t < ctx->count; t++) {
        contains[t] = false;
        if (ctx->assigned[t]) continue;
        uintptr_t target = (uintptr_t)stripPointer(ctx->targets[t]);
        for (int i = 0; i < info->dlpi_phnum; i++) {
            const ElfProgramHeader* ph = &info->dlpi_phdr[i];
            if (ph->p_type != PT_LOAD) continue;
            uintptr_t start;
            if (__builtin_add_overflow((uintptr_t)info->dlpi_addr, (uintptr_t)ph->p_vaddr, &start)) continue;
            if (target < start) continue;
            uintptr_t end;
            if (__builtin_add_overflow(start, (uintptr_t)ph->p_memsz, &end)) continue;
            if (target >= end) continue;
            contains[t] = true;
            any = true;
            break;
        }
    }
    if (!any) return 0;

    // One classification per containing object, then every contained target
    // takes that verdict.
    AdmissionVerdict verdict = classifyImageInternal(info->dlpi_phdr, info->dlpi_phnum,
                                                     (uintptr_t)info->dlpi_addr);
    ctx->images_classified++;
    for (int t = 0; t < ctx->count; t++) {
        if (!contains[t] || ctx->assigned[t]) continue;
        ctx->verdicts[t] = verdict;
        ctx->assigned[t] = true;
        ctx->unassigned--;
    }

    // The walk ends on the first recognized ddprof owner: the start is
    // rejected regardless of the remaining targets, so they need no verdict.
    if (verdict.outcome == DDPROF) return 1;
    return ctx->unassigned == 0 ? 1 : 0;
}

// The Linux owner classification: one dl_iterate_phdr() call per attempt with
// the whole context on the stack. After the walk, every target no object
// claimed is INDETERMINATE (NO_OWNER): anonymous executable memory, or an
// object unloaded before the walk reported it. Returns the number of images
// classified.
int classifyOwnersWalk(const void* const* targets, int count, AdmissionVerdict* verdicts) {
    OwnerWalkContext ctx;
    ctx.targets = targets;
    ctx.verdicts = verdicts;
    ctx.count = count;
    ctx.unassigned = count;
    ctx.images_classified = 0;
    for (int i = 0; i < count; i++) {
        ctx.assigned[i] = false;
        verdicts[i].outcome = INDETERMINATE;
        verdicts[i].reason = NO_OWNER;
    }

    dl_iterate_phdr(ownerWalkCallback, &ctx);

    return ctx.images_classified;
}

} // namespace

// The loader-walk lifetime basis: glibc 2.39 elf/dl-iteratephdr.c takes
// dl_load_write_lock before the object loop and releases it only after the
// loop that calls the callback; glibc 2.39 elf/dl-close.c unmaps and unlinks
// a map only while holding that same lock; musl 1.2.5 src/ldso/dlclose.c
// validates the handle and never unmaps. A reported object therefore stays
// mapped for the whole callback — no loader handle is acquired and none is
// released. Containment is checked against the loader's live program headers
// of the same object, so a stale CodeCache for a reused range cannot
// misattribute the owner (LibraryPatcher::LiveLibraryWalk relies on the same
// mechanism). This walk must never be started while LibraryPatcher::_lock,
// MallocHooker::_patch_lock or Symbols::_parse_lock is held: the callers are
// the admission path inside MallocHooker::initialize(), which runs before
// patching and does not hold any of them.
int MallocAdmission::classifyOwners(const void* const* targets, int count, AdmissionVerdict* verdicts) {
    return classifyOwnersWalk(targets, count, verdicts);
}

#endif // __linux__
