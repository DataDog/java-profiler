/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Classification tests for the native-memory admission marker lookup.
//
// Two slices:
// - loaded fixture DSOs built by :ddprof-lib:buildNativeLibs (real ELF bytes);
// - synthesized images (in-memory buffers with program headers, dynamic
//   section, hash tables, .dynsym and .dynstr, passed to the production
//   classifyImage() with p_vaddr 0 and load bias = buffer address), covering
//   what a loader refuses to load: missing tables, no PT_DYNAMIC, zero bucket
//   counts, out-of-range buckets and chains, unterminated and cyclic chains,
//   overflowing sizes and indices, out-of-range st_name, local/hidden
//   entries, duplicate definitions and wrong kinds.
//
// This file contributes zero tests on non-Linux platforms.

#ifdef __linux__

#include <gtest/gtest.h>

#include <dlfcn.h>
#include <elf.h>
#include <fcntl.h>
#include <limits.h>
#include <link.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../../main/cpp/mallocAdmission_linux.h"

namespace {

// Copies a fixture to a uniquely named file (mkstemp pattern) and returns its
// path. The caller owns the path buffer.
std::string copyFixture(const char* source) {
    char tmpl[] = "/tmp/ddprof-admission-XXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) return std::string();
    close(fd);
    std::string target(tmpl);
    // Copy the bytes: the load path must not depend on the original resource
    // name, and the copy is unlinked while mapped.
    FILE* in = fopen(source, "rb");
    FILE* out = fopen(target.c_str(), "wb");
    if (in == nullptr || out == nullptr) {
        if (in != nullptr) fclose(in);
        if (out != nullptr) fclose(out);
        return std::string();
    }
    char buffer[8192];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        if (fwrite(buffer, 1, n, out) != n) {
            fclose(in);
            fclose(out);
            return std::string();
        }
    }
    fclose(in);
    fclose(out);
    return target;
}

// Locates the program headers of a dlopen'ed object: dlinfo gives its link
// map entry, dl_iterate_phdr the matching dl_phdr_info.
struct LoadedPhdrs {
    const ElfW(Phdr)* phdrs;
    int phnum;
    uintptr_t load_bias;
};

int findLoadedObject(struct dl_phdr_info* info, size_t, void* data) {
    LoadedPhdrs* query = (LoadedPhdrs*)data;
    if ((uintptr_t)info->dlpi_addr == query->load_bias) {
        query->phdrs = info->dlpi_phdr;
        query->phnum = info->dlpi_phnum;
        return 1;
    }
    return 0;
}

// dlopens a fixture and returns its program headers through the loader's own
// reporting, not from a re-read file: classification sees the same mapping
// the process runs from.
bool loadFixture(const char* path, int flags, void** handle_out, LoadedPhdrs* phdrs_out) {
    *handle_out = dlopen(path, flags);
    if (*handle_out == nullptr) {
        const char* error = dlerror();
        ADD_FAILURE() << "dlopen(" << path << ") failed: " << (error ? error : "no error");
        return false;
    }
    struct link_map* map = nullptr;
    if (dlinfo(*handle_out, RTLD_DI_LINKMAP, &map) != 0 || map == nullptr) {
        const char* error = dlerror();
        ADD_FAILURE() << "dlinfo failed: " << (error ? error : "no error");
        return false;
    }
    phdrs_out->load_bias = (uintptr_t)map->l_addr;
    phdrs_out->phdrs = nullptr;
    phdrs_out->phnum = 0;
    dl_iterate_phdr(findLoadedObject, phdrs_out);
    if (phdrs_out->phdrs == nullptr) {
        ADD_FAILURE() << "dl_iterate_phdr found no object at load bias "
                      << (void*)phdrs_out->load_bias;
        return false;
    }
    return true;
}

std::string fixturePath(const char* variant) {
    char exe[PATH_MAX - 128];
    ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
    if (len <= 0) return std::string();
    exe[len] = '\0';
    *strrchr(exe, '/') = '\0';
    char path[PATH_MAX];
    snprintf(path, sizeof(path),
             "%s/../../../test/resources/native-libs/ddprof-admission/libddprof-fixture-%s.so", exe,
             variant);
    struct stat st;
    if (stat(path, &st) != 0) return std::string();
    return std::string(path);
}

AdmissionVerdict classifyFixture(const LoadedPhdrs& image) {
    return ElfMarkerLookup::classifyImage(image.phdrs, image.phnum, image.load_bias);
}

// Reads an exported uint64_t counter from a loaded fixture; the counters are
// dlsym'ed, not linked, because the fixtures are dlopen'ed test resources.
uint64_t readCounter(void* handle, const char* name) {
    void* sym = dlsym(handle, name);
    EXPECT_NE(sym, nullptr) << "Missing counter " << name;
    if (sym == nullptr) return UINT64_MAX;
    return *(uint64_t*)sym;
}

class MallocAdmissionElfTest : public ::testing::Test {};

// A recognized ddprof image classifies as DDPROF even when copied to a
// random path and unlinked while mapped: identity follows the image, not the
// pathname (AC-5).
TEST(MallocAdmissionElfTest, RenamedAndUnlinkedFixtureIsDDProf) {
    std::string source = fixturePath("gnu");
    ASSERT_FALSE(source.empty()) << "Missing fixture libddprof-fixture-gnu.so (built by "
                                    ":ddprof-lib:buildNativeLibs)";
    std::string copy = copyFixture(source.c_str());
    ASSERT_FALSE(copy.empty());
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(copy.c_str(), RTLD_NOW, &handle, &image));
    unlink(copy.c_str());
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, DDPROF);
    EXPECT_EQ(verdict.reason, NONE);
    dlclose(handle);
}

// The hash-table kind must not matter: GNU-only, SysV-only and both-table
// builds of the same markers all classify as DDPROF.
TEST(MallocAdmissionElfTest, HashTableVariantsAreDDProf) {
    const char* variants[] = {"gnu", "sysv", "both"};
    for (const char* variant : variants) {
        std::string path = fixturePath(variant);
        ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
        void* handle = nullptr;
        LoadedPhdrs image = {};
        ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
        AdmissionVerdict verdict = classifyFixture(image);
        EXPECT_EQ(verdict.outcome, DDPROF) << variant;
        EXPECT_EQ(verdict.reason, NONE) << variant;
        dlclose(handle);
    }
}

// A hook-only image (same allocation imports, no markers) is not recognized.
TEST(MallocAdmissionElfTest, NoMarkerFixtureIsNotRecognized) {
    std::string path = fixturePath("nomark");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(verdict.reason, NONE);
    dlclose(handle);
}

// Markers that exist only as undefined imports of a dependency are not owned
// definitions: the importing image is NOT_RECOGNIZED, the defining dependency
// is DDPROF.
TEST(MallocAdmissionElfTest, DependencyOnlyMarkersAreNotRecognized) {
    std::string dep = fixturePath("dep");
    std::string deponly = fixturePath("deponly");
    ASSERT_FALSE(dep.empty()) << "Missing fixture " << dep;
    ASSERT_FALSE(deponly.empty()) << "Missing fixture " << deponly;
    void* dep_handle = nullptr;
    LoadedPhdrs dep_image = {};
    // RTLD_GLOBAL so the dependent fixture's undefined markers resolve from it.
    ASSERT_TRUE(loadFixture(dep.c_str(), RTLD_NOW | RTLD_GLOBAL, &dep_handle, &dep_image));
    void* deponly_handle = nullptr;
    LoadedPhdrs deponly_image = {};
    ASSERT_TRUE(loadFixture(deponly.c_str(), RTLD_NOW, &deponly_handle, &deponly_image));
    AdmissionVerdict deponly_verdict = classifyFixture(deponly_image);
    EXPECT_EQ(deponly_verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(deponly_verdict.reason, NONE);
    AdmissionVerdict dep_verdict = classifyFixture(dep_image);
    EXPECT_EQ(dep_verdict.outcome, DDPROF);
    EXPECT_EQ(dep_verdict.reason, NONE);
    dlclose(deponly_handle);
    dlclose(dep_handle);
}

// One marker alone is partial recognition: INDETERMINATE, never a clean
// DDPROF or a silent NOT_RECOGNIZED.
TEST(MallocAdmissionElfTest, OneMarkerIsIndeterminatePartial) {
    std::string path = fixturePath("onemark");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, INDETERMINATE);
    EXPECT_EQ(verdict.reason, PARTIAL_MARKERS);
    dlclose(handle);
}

// A marker with the wrong ELF symbol type fails the image closed.
TEST(MallocAdmissionElfTest, ObjectMarkerIsIndeterminateWrongKind) {
    std::string path = fixturePath("object");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, INDETERMINATE);
    EXPECT_EQ(verdict.reason, WRONG_KIND_MARKER);
    dlclose(handle);
}

// An STT_GNU_IFUNC marker is also wrong-kind. The fixture is glibc-only; on
// musl the admission rules are still covered by the synthesized-image tests.
TEST(MallocAdmissionElfTest, IfuncMarkerIsIndeterminateWrongKind) {
    std::string path = fixturePath("ifunc");
    if (path.empty()) {
        GTEST_SKIP() << "libddprof-fixture-ifunc.so is glibc-only (musl has no ifunc support)";
    }
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, INDETERMINATE);
    EXPECT_EQ(verdict.reason, WRONG_KIND_MARKER);

    // Classification must never execute a marker or an IFUNC resolver
    // (AC-13): glibc resolved the resolver once at relocation time, and the
    // admission check must not have added a call.
    uint64_t resolver_calls = readCounter(handle, "fixture_resolver_calls");
    ASSERT_NE(resolver_calls, UINT64_MAX);
    (void)classifyFixture(image);
    EXPECT_EQ(readCounter(handle, "fixture_resolver_calls"), resolver_calls);
    dlclose(handle);
}

// Classifying a recognized image must not execute its markers (AC-13).
TEST(MallocAdmissionElfTest, ClassificationDoesNotCallMarkers) {
    std::string path = fixturePath("gnu");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    uint64_t start_calls = readCounter(handle, "fixture_start_marker_calls");
    uint64_t stop_calls = readCounter(handle, "fixture_stop_marker_calls");
    ASSERT_NE(start_calls, UINT64_MAX);
    ASSERT_NE(stop_calls, UINT64_MAX);
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, DDPROF);
    EXPECT_EQ(readCounter(handle, "fixture_start_marker_calls"), start_calls);
    EXPECT_EQ(readCounter(handle, "fixture_stop_marker_calls"), stop_calls);
    dlclose(handle);
}

// ---------------------------------------------------------------------------
// Synthesized images (AC-12). The hashes mirror the production formulas in
// mallocAdmission_linux.cpp (same constants): the tests must place symbols in
// exactly the buckets the classifier computes, so a divergent copy would be
// caught by the well-formed DDPROF cases failing.

const char* const SYNTH_START = "ddprof_start_profiling";
const char* const SYNTH_STOP = "ddprof_stop_profiling";

uint32_t synthGnuHash(const char* name, size_t len) {
    uint32_t h = 5381;
    for (size_t i = 0; i < len; i++) {
        h = h * 33 + (unsigned char)name[i];
    }
    return h;
}

uint32_t synthSysvHash(const char* name, size_t len) {
    uint32_t h = 0;
    for (size_t i = 0; i < len; i++) {
        h = (h << 4) + (unsigned char)name[i];
        uint32_t g = h & 0xf0000000u;
        if (g != 0) h ^= g >> 24;
        h &= ~g;
    }
    return h;
}

constexpr uint8_t synthInfo(unsigned bind, unsigned type) { return (uint8_t)((bind << 4) | type); }

// The smallest bucket count in [2, 64] that places the two marker names in
// different buckets under `hash`. With a shared bucket one marker's chain
// includes the other's symbol, and the queried name-extent check (correctly)
// fails closed on the shorter name — the tests below need the markers found,
// not that rejection.
template <typename HashFn>
static uint32_t synthBucketCount(HashFn hash) {
    for (uint32_t nb = 2; nb < 64; nb++) {
        if (hash(SYNTH_START, strlen(SYNTH_START)) % nb != hash(SYNTH_STOP, strlen(SYNTH_STOP)) % nb) {
            return nb;
        }
    }
    return 64;
}

// One .dynsym entry to synthesize. `name` is kept for hash computation; the
// classifier only sees `name_off`.
struct SynthSymbol {
    const char* name;    // nullptr for the reserved null symbol
    uint32_t name_off;   // offset of the name inside the image's string table
    uint8_t info;        // (bind << 4) | type
    uint8_t other;       // visibility in the low two bits
    uint16_t shndx;
};

struct GnuTableOffsets {
    size_t header;
    size_t buckets;
    size_t chains;
    uint32_t nbuckets;
    uint32_t symoffset;
};

struct SysvTableOffsets {
    size_t header;
    size_t buckets;
    size_t chains;
    uint32_t nbucket;
    uint32_t nchain;
};

// Builds one synthetic image in an 8-byte-aligned backing store. All appends
// return byte offsets; pokes (corruption writes) must happen after the last
// append, since the backing store may move on growth. The image is one
// PT_LOAD covering the whole buffer (p_vaddr 0) plus an optional PT_DYNAMIC.
class SynthImage {
  public:
    SynthImage() { words_.reserve(1 << 19); }  // 4 MB: the chain-limit tests need ~400 KB

    size_t addString(const char* s) {
        pushBytes(s, strlen(s) + 1);
        return start_of_last_string_;
    }

    size_t addSymtab(const std::vector<SynthSymbol>& syms) {
        align8();
        size_t off = offset();
        for (const SynthSymbol& s : syms) {
            ElfW(Sym) e;
            memset(&e, 0, sizeof(e));
            e.st_name = s.name_off;
            e.st_info = s.info;
            e.st_other = s.other;
            e.st_shndx = s.shndx;
            e.st_value = 0x1000;
            e.st_size = 4;
            pushBytes(&e, sizeof(e));
        }
        return off;
    }

    // A well-formed DT_GNU_HASH over syms [symoffset, syms.size()): one bloom
    // word, per-bucket first-symbol indexes, per-symbol chain words with the
    // end bit on the last symbol of each bucket.
    GnuTableOffsets addGnuTable(const std::vector<SynthSymbol>& syms, uint32_t nbuckets,
                                uint32_t symoffset) {
        align8();
        size_t header = offset();
        uint32_t bloom_size = 1, bloom_shift = 0;
        pushU32(nbuckets);
        pushU32(symoffset);
        pushU32(bloom_size);
        pushU32(bloom_shift);
        uint64_t bloom = 0;
        for (size_t i = symoffset; i < syms.size(); i++) {
            bloom |= (uint64_t)1 << (synthGnuHash(syms[i].name, strlen(syms[i].name)) % 64);
        }
        pushBytes(&bloom, sizeof(bloom));
        size_t buckets = offset();
        std::vector<uint32_t> bkt(nbuckets, 0), last(nbuckets, 0);
        std::vector<uint32_t> chn(syms.size() - symoffset, 0);
        for (size_t i = symoffset; i < syms.size(); i++) {
            uint32_t h = synthGnuHash(syms[i].name, strlen(syms[i].name));
            uint32_t b = h % nbuckets;
            if (bkt[b] == 0) bkt[b] = (uint32_t)i;
            last[b] = (uint32_t)i;
            chn[i - symoffset] = h & ~1u;
        }
        for (uint32_t b = 0; b < nbuckets; b++) {
            if (last[b] != 0) chn[last[b] - symoffset] |= 1u;
        }
        for (uint32_t v : bkt) pushU32(v);
        size_t chains = offset();
        for (uint32_t v : chn) pushU32(v);
        gnu_off_ = header;
        has_gnu_ = true;
        return {header, buckets, chains, nbuckets, symoffset};
    }

    // A well-formed DT_HASH: nbucket buckets, nchain chain words (default: one
    // per symbol), chains linked per bucket with the SysV convention.
    SysvTableOffsets addSysvTable(const std::vector<SynthSymbol>& syms, uint32_t nbucket,
                                  uint32_t nchain = 0) {
        align8();
        size_t header = offset();
        if (nchain == 0) nchain = (uint32_t)syms.size();
        pushU32(nbucket);
        pushU32(nchain);
        size_t buckets = offset();
        std::vector<uint32_t> bkt(nbucket, 0);
        std::vector<uint32_t> chn(nchain, 0);
        for (size_t i = syms.size(); i-- > 1;) {
            uint32_t h = synthSysvHash(syms[i].name, strlen(syms[i].name));
            uint32_t b = h % nbucket;
            chn[i] = bkt[b];
            bkt[b] = (uint32_t)i;
        }
        for (uint32_t v : bkt) pushU32(v);
        size_t chains = offset();
        for (uint32_t v : chn) pushU32(v);
        sysv_off_ = header;
        has_sysv_ = true;
        return {header, buckets, chains, nbucket, nchain};
    }

    void addDynamic(const std::vector<std::pair<uint64_t, uint64_t>>& entries) {
        align8();
        dyn_off_ = offset();
        std::vector<ElfW(Dyn)> d;
        d.reserve(entries.size() + 1);
        for (const auto& e : entries) {
            ElfW(Dyn) one;
            one.d_tag = e.first;
            one.d_un.d_val = e.second;
            d.push_back(one);
        }
        ElfW(Dyn) null;
        null.d_tag = DT_NULL;
        null.d_un.d_val = 0;
        d.push_back(null);
        pushBytes(d.data(), d.size() * sizeof(ElfW(Dyn)));
        dyn_filesz_ = d.size() * sizeof(ElfW(Dyn));
        has_dynamic_ = true;
    }

    // Byte offset of the dynamic entry with the given tag (for later patching);
    // the tag must be present.
    size_t lastDynamicEntryOffset(uint64_t tag) const {
        const uint8_t* base = (const uint8_t*)words_.data();
        for (size_t off = dyn_off_; off + sizeof(ElfW(Dyn)) <= dyn_off_ + dyn_filesz_;
             off += sizeof(ElfW(Dyn))) {
            uint64_t entry_tag;
            memcpy(&entry_tag, base + off, sizeof(entry_tag));
            if (entry_tag == tag) return off;
        }
        ADD_FAILURE() << "dynamic entry " << tag << " not found";
        return dyn_off_;
    }

    void startStringTable() {
        align8();
        strtab_off_ = offset();
    }

    // Records the string-table extent: must run after the last addString() and
    // before any other append, since DT_STRSZ covers only the strings.
    void finishStringTable() { strsz_ = offset() - strtab_off_; }

    size_t strtabOffset() const { return strtab_off_; }

    size_t strtabSize() const { return strsz_; }

    // Byte-level writes for corruption tests: only valid after the last append.
    void pokeU32(size_t off, uint32_t v) { memcpy(base() + off, &v, sizeof(v)); }


    void pokeU64(size_t off, uint64_t v) { memcpy(base() + off, &v, sizeof(v)); }

    // Appends raw 32-bit words (chain-limit spans, extra chain entries).
    void pushU32(uint32_t v) { pushBytes(&v, sizeof(v)); }

    // Lays out the program headers and classifies. load_flags defaults to the
    // readable+executable mapping a loader reports; filesz_cap truncates the
    // PT_LOAD's readable extent to make later bytes unreadable.
    AdmissionVerdict classify(int load_flags = PF_R | PF_X, size_t filesz_cap = 0) {
        while (offset() % 8 != 0) pushByte(0);
        memset(phdrs_, 0, sizeof(phdrs_));
        phnum_ = 0;
        phdrs_[phnum_].p_type = PT_LOAD;
        phdrs_[phnum_].p_offset = 0;
        phdrs_[phnum_].p_vaddr = 0;
        phdrs_[phnum_].p_filesz = filesz_cap != 0 ? filesz_cap : offset();
        phdrs_[phnum_].p_memsz = phdrs_[phnum_].p_filesz;
        phdrs_[phnum_].p_flags = load_flags;
        phdrs_[phnum_].p_align = 8;
        phnum_++;
        if (has_dynamic_) {
            phdrs_[phnum_].p_type = PT_DYNAMIC;
            phdrs_[phnum_].p_vaddr = dyn_off_;
            phdrs_[phnum_].p_filesz = dyn_filesz_;
            phdrs_[phnum_].p_flags = PF_R;
            phnum_++;
        }
        return ElfMarkerLookup::classifyImage(phdrs_, phnum_, (uintptr_t)base());
    }

    size_t gnuTableOffset() const { return gnu_off_; }
    size_t sysvTableOffset() const { return sysv_off_; }
    bool hasGnu() const { return has_gnu_; }
    bool hasSysv() const { return has_sysv_; }

  private:
    uint8_t* base() { return (uint8_t*)words_.data(); }

    size_t offset() const { return words_.size() * sizeof(uint64_t) + partial_n_; }

    void pushByte(uint8_t b) {
        partial_ |= (uint64_t)b << (partial_n_ * 8);
        if (++partial_n_ == sizeof(uint64_t)) {
            words_.push_back(partial_);
            partial_ = 0;
            partial_n_ = 0;
        }
    }

    void pushBytes(const void* p, size_t n) {
        const uint8_t* b = (const uint8_t*)p;
        start_of_last_string_ = offset();
        for (size_t i = 0; i < n; i++) pushByte(b[i]);
    }

    void align8() {
        while (offset() % 8 != 0) pushByte(0);
    }

    std::vector<uint64_t> words_;
    uint64_t partial_ = 0;
    unsigned partial_n_ = 0;
    size_t start_of_last_string_ = 0;
    size_t strtab_off_ = 0;
    size_t strsz_ = 0;
    size_t dyn_off_ = 0;
    size_t dyn_filesz_ = 0;
    size_t gnu_off_ = 0;
    size_t sysv_off_ = 0;
    bool has_dynamic_ = false;
    bool has_gnu_ = false;
    bool has_sysv_ = false;
    ElfW(Phdr) phdrs_[3];
    int phnum_ = 0;
};

// The shared skeleton: string table with the two marker names, a symbol list,
// a well-formed GNU hash table and a complete dynamic section.
struct SynthDefaults {
    SynthImage img;
    std::vector<SynthSymbol> syms;
    GnuTableOffsets gnu{};

    static SynthDefaults markers() {
        SynthDefaults d;
        d.img.startStringTable();
        size_t start_off = d.img.addString(SYNTH_START);
        size_t stop_off = d.img.addString(SYNTH_STOP);
        d.img.finishStringTable();
        d.syms = {{nullptr, 0, 0, 0, 0},
                  {SYNTH_START, (uint32_t)start_off, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 1},
                  {SYNTH_STOP, (uint32_t)stop_off, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 2}};
        return d;
    }

    void finish() {
        size_t symtab = img.addSymtab(syms);
        gnu = img.addGnuTable(syms, synthBucketCount(synthGnuHash), 1);
        img.addDynamic({{DT_SYMTAB, symtab},
                        {DT_STRTAB, img.strtabOffset()},
                        {DT_STRSZ, img.strtabSize()},
                        {DT_GNU_HASH, gnu.header}});
    }
};

// A well-formed synthesized GNU-hash image classifies as DDPROF: recognition
// does not depend on real loader bytes.
TEST(MallocAdmissionElfSynthTest, WellFormedGnuHashIsDDProf) {
    SynthDefaults d = SynthDefaults::markers();
    d.finish();
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, DDPROF);
    EXPECT_EQ(v.reason, NONE);
}

// Same for a SysV-only image: DT_HASH alone must be enough.
TEST(MallocAdmissionElfSynthTest, WellFormedSysvHashIsDDProf) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    SysvTableOffsets sysv = d.img.addSysvTable(d.syms, synthBucketCount(synthSysvHash));
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_HASH, sysv.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, DDPROF);
    EXPECT_EQ(v.reason, NONE);
}

// No PT_DYNAMIC segment: the image cannot be inspected at all. The dynamic
// entries are appended (so the buffer is a realistic shape) but no PT_DYNAMIC
// phdr points at them: classify() only emits PT_DYNAMIC after addDynamic().
TEST(MallocAdmissionElfSynthTest, NoDynamicSegmentIsIndeterminate) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    (void)d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    (void)symtab;
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, NO_DYNAMIC);
}

// DT_STRSZ missing: the string table extent is unknown.
TEST(MallocAdmissionElfSynthTest, MissingStrszIsBadDynamic) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    d.img.addDynamic({{DT_SYMTAB, symtab}, {DT_STRTAB, d.img.strtabOffset()}, {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_DYNAMIC);
}

// DT_STRTAB pointing outside every PT_LOAD: the string table is unreadable.
TEST(MallocAdmissionElfSynthTest, UnreadableStrtabIsBadDynamic) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    d.img.addDynamic({{DT_SYMTAB, symtab}, {DT_STRTAB, 0x700000000000ULL}, {DT_STRSZ, 64}, {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_DYNAMIC);
}

// Neither DT_GNU_HASH nor DT_HASH: no lookup structure.
TEST(MallocAdmissionElfSynthTest, NoHashTableIsIndeterminate) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    d.img.addDynamic({{DT_SYMTAB, symtab}, {DT_STRTAB, d.img.strtabOffset()}, {DT_STRSZ, d.img.strtabSize()}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, NO_HASH_TABLE);
}

// A malformed GNU table must be reported, never papered over with a valid
// SysV table in the same image (the walk uses DT_GNU_HASH when present).
TEST(MallocAdmissionElfSynthTest, MalformedGnuTableIsNotPaperedBySysv) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    SysvTableOffsets sysv = d.img.addSysvTable(d.syms, synthBucketCount(synthSysvHash));
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, gnu.header},
                      {DT_HASH, sysv.header}});
    d.img.pokeU32(gnu.header, 0);  // nbuckets = 0
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// GNU zero bucket count.
TEST(MallocAdmissionElfSynthTest, GnuZeroBucketsIsBadHashTable) {
    SynthDefaults d = SynthDefaults::markers();
    d.finish();
    d.img.pokeU32(d.gnu.header, 0);
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// A GNU bucket below symoffset is malformed (symbols below symoffset are not
// in the chain array). symoffset 2 needs a filler symbol at index 1.
TEST(MallocAdmissionElfSynthTest, GnuBucketBelowSymoffsetIsBadHashTable) {
    SynthImage img;
    img.startStringTable();
    size_t f = img.addString("filler_a");
    size_t s = img.addString(SYNTH_START);
    size_t p = img.addString(SYNTH_STOP);
    img.finishStringTable();
    std::vector<SynthSymbol> syms = {
        {nullptr, 0, 0, 0, 0},
        {"filler_a", (uint32_t)f, synthInfo(STB_GLOBAL, STT_OBJECT), STV_DEFAULT, 3},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 1},
        {SYNTH_STOP, (uint32_t)p, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 2}};
    size_t symtab = img.addSymtab(syms);
    GnuTableOffsets gnu = img.addGnuTable(syms, 4, 2);
    img.addDynamic({{DT_SYMTAB, symtab},
                    {DT_STRTAB, img.strtabOffset()},
                    {DT_STRSZ, img.strtabSize()},
                    {DT_GNU_HASH, gnu.header}});
    // Corrupt the START marker's bucket to 1: nonzero but below symoffset 2.
    uint32_t start_bucket = synthGnuHash(SYNTH_START, strlen(SYNTH_START)) % 4;
    img.pokeU32(gnu.buckets + start_bucket * 4, 1);
    AdmissionVerdict v = img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// A GNU bucket far beyond the chain array: the chain read is out of range.
TEST(MallocAdmissionElfSynthTest, GnuOutOfRangeBucketIsBadHashTable) {
    SynthDefaults d = SynthDefaults::markers();
    d.finish();
    uint32_t nb = synthBucketCount(synthGnuHash);
    ASSERT_EQ(d.gnu.nbuckets, nb);
    uint32_t start_bucket = synthGnuHash(SYNTH_START, strlen(SYNTH_START)) % nb;
    d.img.pokeU32(d.gnu.buckets + start_bucket * 4, 0xFFFFFFF0u);
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// A chain array beyond the PT_LOAD's readable extent: bucket readable, chain
// word not (p_filesz truncation at the chains start). The dynamic section is
// laid out before the hash table so the truncation only blinds the walk, not
// the metadata stage.
TEST(MallocAdmissionElfSynthTest, GnuUnreadableChainWordIsBadHashTable) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, 0}});  // patched below once the table exists
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    d.img.pokeU64(d.img.lastDynamicEntryOffset(DT_GNU_HASH) + 8, gnu.header);
    AdmissionVerdict v = d.img.classify(PF_R | PF_X, gnu.chains);
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// SysV zero bucket count.
TEST(MallocAdmissionElfSynthTest, SysvZeroBucketsIsBadHashTable) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    SysvTableOffsets sysv = d.img.addSysvTable(d.syms, 4);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_HASH, sysv.header}});
    d.img.pokeU32(sysv.header, 0);
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// A SysV chain index at or beyond nchain.
TEST(MallocAdmissionElfSynthTest, SysvIndexBeyondNchainIsBadHashTable) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    SysvTableOffsets sysv = d.img.addSysvTable(d.syms, 1);  // nchain = 3
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_HASH, sysv.header}});
    d.img.pokeU32(sysv.buckets, 5);  // index 5 >= nchain 3
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// A GNU chain that never sets the end bit: the walk stops at
// MAX_HASH_CHAIN_STEPS and reports CHAIN_LIMIT, not a hang.
TEST(MallocAdmissionElfSynthTest, GnuUnterminatedChainIsChainLimit) {
    SynthDefaults d = SynthDefaults::markers();
    // Make both markers ignorable so the aggregation never short-circuits:
    // the pinned outcome comes only from the chain walk, not from a finding.
    d.syms[1].info = synthInfo(STB_GLOBAL, STT_OBJECT);
    d.syms[2].info = synthInfo(STB_LOCAL, STT_FUNC);
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    // Zero 70000 chain words (no end bit anywhere) and start the walk with a
    // matching non-terminal word, then 65535 mismatched zeros: CHAIN_LIMIT.
    for (int i = 0; i < 70000; i++) d.img.pushU32(0);
    for (uint32_t i = 0; i < 70000; i++) d.img.pokeU32(gnu.chains + i * 4, 0);
    d.img.pokeU32(gnu.chains, synthGnuHash(SYNTH_START, strlen(SYNTH_START)) & ~1u);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, CHAIN_LIMIT);
}

// A SysV chain that loops through readable filler symbols: bounded by
// MAX_HASH_CHAIN_STEPS (nchain 100000 is above the cap), reports CHAIN_LIMIT.
TEST(MallocAdmissionElfSynthTest, SysvCyclicChainIsChainLimit) {
    SynthImage img;
    img.startStringTable();
    size_t f = img.addString("filler_b");
    size_t s = img.addString(SYNTH_START);
    size_t p = img.addString(SYNTH_STOP);
    img.finishStringTable();
    std::vector<SynthSymbol> syms;
    syms.push_back({nullptr, 0, 0, 0, 0});
    for (int i = 1; i <= 15; i++) {
        syms.push_back({"filler_b", (uint32_t)f, synthInfo(STB_GLOBAL, STT_OBJECT), STV_DEFAULT,
                        (uint16_t)(100 + i)});
    }
    syms.push_back({SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 1});
    syms.push_back({SYNTH_STOP, (uint32_t)p, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 2});
    size_t symtab = img.addSymtab(syms);
    SysvTableOffsets sysv = img.addSysvTable(syms, 1, 100000);
    img.addDynamic({{DT_SYMTAB, symtab},
                    {DT_STRTAB, img.strtabOffset()},
                    {DT_STRSZ, img.strtabSize()},
                    {DT_HASH, sysv.header}});
    img.pokeU32(sysv.chains + 5 * 4, 5);  // chain[5] = 5: self-loop
    AdmissionVerdict v = img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, CHAIN_LIMIT);
}

// bloom_size so large that the bucket array address leaves the readable
// extent: the bucket read fails.
TEST(MallocAdmissionElfSynthTest, GnuHugeBloomSizeIsBadHashTable) {
    SynthDefaults d = SynthDefaults::markers();
    d.finish();
    d.img.pokeU32(d.gnu.header + 8, 0x20000000u);  // bloom_size = 512M words = 4 GB
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_HASH_TABLE);
}

// A matched symbol whose index lands beyond the readable symbol table.
TEST(MallocAdmissionElfSynthTest, GnuOutOfRangeSymbolIndexIsBadSymbol) {
    SynthDefaults d = SynthDefaults::markers();
    size_t symtab = d.img.addSymtab(d.syms);
    // nbuckets 1: the marker's chain index is hash % 1 = 0; move the bucket to
    // symoffset + 0x40000 so the chain word (readable, appended below) matches
    // the hash with the end bit set, and sym_index = symoffset + 0x40000 reads
    // past the 3-entry symtab.
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, 1, 1);
    uint32_t chain_index = 0x40000;
    for (uint32_t i = 0; i < chain_index; i++) d.img.pushU32(0);
    d.img.pokeU32(gnu.buckets, 1 + chain_index);
    d.img.pokeU32(gnu.chains + chain_index * 4,
                  synthGnuHash(SYNTH_START, strlen(SYNTH_START)) | 1u);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_SYMBOL);
}

// A matched symbol whose st_name leaves the string table (including the
// marker length and the terminator) is out of range.
TEST(MallocAdmissionElfSynthTest, StNameOutOfRangeIsBadSymbol) {
    SynthDefaults d = SynthDefaults::markers();
    d.syms[1].name_off = 0xFFFFFFF0u;
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_SYMBOL);
}

// A PT_LOAD without PF_R: the admission reader must not treat the mapping as
// readable even though the address range is backed.
TEST(MallocAdmissionElfSynthTest, NonReadableLoadSegmentIsBadDynamic) {
    SynthDefaults d = SynthDefaults::markers();
    d.finish();
    AdmissionVerdict v = d.img.classify(PF_X | PF_W);
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, BAD_DYNAMIC);
}

// A wrong-kind marker (STT_OBJECT) fails the image closed.
TEST(MallocAdmissionElfSynthTest, SynthesizedObjectMarkerIsWrongKind) {
    SynthDefaults d = SynthDefaults::markers();
    d.syms[1].info = synthInfo(STB_GLOBAL, STT_OBJECT);
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, WRONG_KIND_MARKER);
}

// STT_GNU_IFUNC is also wrong-kind. Synthesized, so it runs on musl too
// (the real-ifunc fixture is glibc-only).
TEST(MallocAdmissionElfSynthTest, SynthesizedIfuncMarkerIsWrongKind) {
    SynthDefaults d = SynthDefaults::markers();
    d.syms[1].info = synthInfo(STB_GLOBAL, STT_GNU_IFUNC);
    size_t symtab = d.img.addSymtab(d.syms);
    GnuTableOffsets gnu = d.img.addGnuTable(d.syms, synthBucketCount(synthGnuHash), 1);
    d.img.addDynamic({{DT_SYMTAB, symtab},
                      {DT_STRTAB, d.img.strtabOffset()},
                      {DT_STRSZ, d.img.strtabSize()},
                      {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = d.img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, WRONG_KIND_MARKER);
}

// The same marker name defined twice as a qualifying function: ambiguous.
TEST(MallocAdmissionElfSynthTest, DuplicateMarkersAreAmbiguous) {
    SynthImage img;
    img.startStringTable();
    size_t s = img.addString(SYNTH_START);
    size_t p = img.addString(SYNTH_STOP);
    img.finishStringTable();
    std::vector<SynthSymbol> syms = {
        {nullptr, 0, 0, 0, 0},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 1},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 2},
        {SYNTH_STOP, (uint32_t)p, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 3}};
    size_t symtab = img.addSymtab(syms);
    GnuTableOffsets gnu = img.addGnuTable(syms, synthBucketCount(synthGnuHash), 1);
    img.addDynamic({{DT_SYMTAB, symtab},
                    {DT_STRTAB, img.strtabOffset()},
                    {DT_STRSZ, img.strtabSize()},
                    {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, AMBIGUOUS_MARKER);
}

// The ownership rules must ignore undefined, local and hidden entries rather
// than count them: three such start-marker entries plus two proper markers
// still classify as DDPROF (not AMBIGUOUS, not WRONG_KIND, not PARTIAL).
TEST(MallocAdmissionElfSynthTest, IgnoredEntriesDoNotCount) {
    SynthImage img;
    img.startStringTable();
    size_t s = img.addString(SYNTH_START);
    size_t p = img.addString(SYNTH_STOP);
    img.finishStringTable();
    std::vector<SynthSymbol> syms = {
        {nullptr, 0, 0, 0, 0},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, SHN_UNDEF},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_LOCAL, STT_FUNC), STV_DEFAULT, 1},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_HIDDEN, 2},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 3},
        {SYNTH_STOP, (uint32_t)p, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 4}};
    size_t symtab = img.addSymtab(syms);
    GnuTableOffsets gnu = img.addGnuTable(syms, synthBucketCount(synthGnuHash), 1);
    img.addDynamic({{DT_SYMTAB, symtab},
                    {DT_STRTAB, img.strtabOffset()},
                    {DT_STRSZ, img.strtabSize()},
                    {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = img.classify();
    EXPECT_EQ(v.outcome, DDPROF);
    EXPECT_EQ(v.reason, NONE);
}

// Only the start marker defined: partial recognition.
TEST(MallocAdmissionElfSynthTest, PartialMarkersAreIndeterminate) {
    SynthImage img;
    img.startStringTable();
    size_t s = img.addString(SYNTH_START);
    img.addString(SYNTH_STOP);  // in the string table, but no symbol defines it
    img.finishStringTable();
    std::vector<SynthSymbol> syms = {
        {nullptr, 0, 0, 0, 0},
        {SYNTH_START, (uint32_t)s, synthInfo(STB_GLOBAL, STT_FUNC), STV_DEFAULT, 1}};
    size_t symtab = img.addSymtab(syms);
    GnuTableOffsets gnu = img.addGnuTable(syms, synthBucketCount(synthGnuHash), 1);
    img.addDynamic({{DT_SYMTAB, symtab},
                    {DT_STRTAB, img.strtabOffset()},
                    {DT_STRSZ, img.strtabSize()},
                    {DT_GNU_HASH, gnu.header}});
    AdmissionVerdict v = img.classify();
    EXPECT_EQ(v.outcome, INDETERMINATE);
    EXPECT_EQ(v.reason, PARTIAL_MARKERS);
}

}  // namespace

#endif  // __linux__
