/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include <dlfcn.h>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <link.h>
#include <linux/limits.h>
#include <pthread.h>
#include <sys/auxv.h>
#include "symbols.h"
#include "dwarf.h"
#include "fdtransferClient.h"
#include "log.h"
#include "os.h"
#include "symbols_linux.h"

// Simple address range
struct Range {
    uintptr_t start;
    uintptr_t end;
};

static bool range_valid(const Range* r) {
    return r->start && r->end && r->end > r->start;
}

static Range g_libc = {0, 0};
static Range g_libpthread = {0, 0};
static bool g_lib_ranges_inited = false;

// Unified dl_iterate_phdr callback context
struct UnifiedCtx {
    void* fbase;           // For range_for_fbase functionality
    Range* out;            // For range_for_fbase functionality
    const void** main_phdr; // For getMainPhdr functionality
    void* libc_fbase;      // For init_lib_ranges_once functionality
    void* pthread_fbase;   // For init_lib_ranges_once functionality
    Range* libc_range;     // For init_lib_ranges_once functionality
    Range* pthread_range;  // For init_lib_ranges_once functionality
};

// Unified callback for both range computation and main phdr collection
static int unified_phdr_cb(dl_phdr_info* info, size_t /*unused*/, void* data) {
    UnifiedCtx* ctx = (UnifiedCtx*)data;

    // Main executable's program header (first entry)
    if (ctx->main_phdr != NULL && *ctx->main_phdr == NULL) {
        *ctx->main_phdr = info->dlpi_phdr;
    }

    // Range computation for specific fbase (range_for_fbase functionality)
    if (ctx->fbase != NULL && (void*)info->dlpi_addr == ctx->fbase) {
        uintptr_t minv = (uintptr_t)-1;
        uintptr_t maxv = 0;
        for (int i = 0; i < info->dlpi_phnum; i++) {
            const ElfW(Phdr)* ph = &info->dlpi_phdr[i];
            if (ph->p_type != PT_LOAD) continue;
            uintptr_t vaddr = (uintptr_t)info->dlpi_addr + ph->p_vaddr;
            uintptr_t vend = vaddr + ph->p_memsz;
            if (vaddr < minv) minv = vaddr;
            if (vend > maxv) maxv = vend;
        }
        if (minv != (uintptr_t)-1 && maxv > minv) {
            ctx->out->start = minv;
            ctx->out->end = maxv;
        }
    }

    // Library range computation (init_lib_ranges_once functionality)
    if (ctx->libc_fbase != NULL && (void*)info->dlpi_addr == ctx->libc_fbase) {
        uintptr_t minv = (uintptr_t)-1;
        uintptr_t maxv = 0;
        for (int i = 0; i < info->dlpi_phnum; i++) {
            const ElfW(Phdr)* ph = &info->dlpi_phdr[i];
            if (ph->p_type != PT_LOAD) continue;
            uintptr_t vaddr = (uintptr_t)info->dlpi_addr + ph->p_vaddr;
            uintptr_t vend = vaddr + ph->p_memsz;
            if (vaddr < minv) minv = vaddr;
            if (vend > maxv) maxv = vend;
        }
        if (minv != (uintptr_t)-1 && maxv > minv) {
            ctx->libc_range->start = minv;
            ctx->libc_range->end = maxv;
        }
    }

    if (ctx->pthread_fbase != NULL && (void*)info->dlpi_addr == ctx->pthread_fbase) {
        uintptr_t minv = (uintptr_t)-1;
        uintptr_t maxv = 0;
        for (int i = 0; i < info->dlpi_phnum; i++) {
            const ElfW(Phdr)* ph = &info->dlpi_phdr[i];
            if (ph->p_type != PT_LOAD) continue;
            uintptr_t vaddr = (uintptr_t)info->dlpi_addr + ph->p_vaddr;
            uintptr_t vend = vaddr + ph->p_memsz;
            if (vaddr < minv) minv = vaddr;
            if (vend > maxv) maxv = vend;
        }
        if (minv != (uintptr_t)-1 && maxv > minv) {
            ctx->pthread_range->start = minv;
            ctx->pthread_range->end = maxv;
        }
    }

    return 0; // continue iteration
}

// Main program header - initialized lazily
static const void* _main_phdr = NULL;
static pthread_once_t _main_phdr_once = PTHREAD_ONCE_INIT;
static const char* _ld_base = (const char*)getauxval(AT_BASE);

// Initialize main phdr once
static void init_main_phdr_once() {
    UnifiedCtx ctx = {NULL, NULL, &_main_phdr, NULL, NULL, NULL, NULL};
    dl_iterate_phdr(&unified_phdr_cb, &ctx);
}

// Ensure main phdr is initialized
static void ensure_main_phdr_initialized() {
    pthread_once(&_main_phdr_once, init_main_phdr_once);
}

static Range range_for_fbase(void* fbase) {
    Range r = {0, 0};
    if (!fbase) return r;
    UnifiedCtx ctx = {fbase, &r, NULL, NULL, NULL, NULL, NULL};
    dl_iterate_phdr(&unified_phdr_cb, &ctx);
    return r;
}

static void init_lib_ranges_once() {
    if (g_lib_ranges_inited) return;
    g_lib_ranges_inited = true;

    // libc anchor: prefer gnu_get_libc_version if present; fallback to strlen
    void* libc_sym = dlsym(RTLD_DEFAULT, "gnu_get_libc_version");
    if (!libc_sym) libc_sym = (void*)&strlen;

    Dl_info di = {0};
    void* libc_fbase = NULL;
    if (dladdr(libc_sym, &di) && di.dli_fbase) {
        libc_fbase = di.dli_fbase;
    }

    // pthread anchor: pthread_create (on glibc >= 2.34 this lives in libc)
    Dl_info di2 = {0};
    void* pthread_fbase = NULL;
    if (dladdr((void*)&pthread_create, &di2) && di2.dli_fbase) {
        pthread_fbase = di2.dli_fbase;
    }

    // Use unified dl_iterate_phdr call to get all information at once
    UnifiedCtx ctx = {NULL, NULL, &_main_phdr, libc_fbase, pthread_fbase, &g_libc, &g_libpthread};
    dl_iterate_phdr(&unified_phdr_cb, &ctx);

    // If pthread couldn't be resolved separately, treat it as libc
    if (!range_valid(&g_libpthread)) g_libpthread = g_libc;
}

static bool pc_in_range(uintptr_t pc, const Range* r) {
    return range_valid(r) && pc >= r->start && pc < r->end;
}

#ifdef __x86_64__

#include <poll.h>
#include "vmEntry.h"

// Workaround for JDK-8312065 on JDK 8:
// replace poll() implementation with ppoll() which is restartable
static int poll_hook(struct pollfd* fds, nfds_t nfds, int timeout) {
    if (timeout >= 0) {
        struct timespec ts;
        ts.tv_sec = timeout / 1000;
        ts.tv_nsec = (timeout % 1000) * 1000000;
        return ppoll(fds, nfds, &ts, NULL);
    } else {
        return ppoll(fds, nfds, NULL, NULL);
    }
}

static void applyPatch(CodeCache* cc) {
    static bool patch_libnet = VM::hotspot_version() == 8;

    if (patch_libnet) {
        size_t len = strlen(cc->name());
        if (len >= 10 && strcmp(cc->name() + len - 10, "/libnet.so") == 0) {
            UnloadProtection handle(cc);
            if (handle.isValid()) {
                cc->patchImport(im_poll, (void*)poll_hook);
                patch_libnet = false;
            }
        }
    }
}

#else

static void applyPatch(CodeCache* cc) {}

#endif


static bool isMainExecutable(const char* image_base, const void* map_end) {
    ensure_main_phdr_initialized();
    return _main_phdr != NULL && _main_phdr >= image_base && _main_phdr < map_end;
}

static bool isLoader(const char* image_base) {
    return _ld_base == image_base;
}

class SymbolDesc {
  private:
    const char* _addr;
    const char* _desc;

  public:
      SymbolDesc(const char* s) {
          _addr = s;
          _desc = strchr(_addr, ' ');
      }

      const char* addr() { return (const char*)strtoul(_addr, NULL, 16); }
      char type()        { return _desc != NULL ? _desc[1] : 0; }
      const char* name() { return _desc + 3; }
};

class MemoryMapDesc {
  private:
    const char* _addr;
    const char* _end;
    const char* _perm;
    const char* _offs;
    const char* _dev;
    const char* _inode;
    const char* _file;

  public:
      MemoryMapDesc(const char* s) {
          _addr = s;
          _end = strchr(_addr, '-') + 1;
          _perm = strchr(_end, ' ') + 1;
          _offs = strchr(_perm, ' ') + 1;
          _dev = strchr(_offs, ' ') + 1;
          _inode = strchr(_dev, ' ') + 1;
          _file = strchr(_inode, ' ');

          if (_file != NULL) {
              while (*_file == ' ') _file++;
          }
      }

      const char* file()    { return _file; }
      bool isReadable()     { return _perm[0] == 'r'; }
      bool isExecutable()   { return _perm[2] == 'x'; }
      const char* addr()    { return (const char*)strtoul(_addr, NULL, 16); }
      const char* end()     { return (const char*)strtoul(_end, NULL, 16); }
      unsigned long offs()  { return strtoul(_offs, NULL, 16); }
      unsigned long inode() { return strtoul(_inode, NULL, 10); }

      unsigned long dev() {
          char* colon;
          unsigned long major = strtoul(_dev, &colon, 16);
          unsigned long minor = strtoul(colon + 1, NULL, 16);
          return major << 8 | minor;
      }
};

struct SharedLibrary {
    char* file;
    const char* map_start;
    const char* map_end;
    const char* image_base;
};


#ifdef __LP64__
const unsigned char ELFCLASS_SUPPORTED = ELFCLASS64;
typedef Elf64_Ehdr ElfHeader;
typedef Elf64_Shdr ElfSection;
typedef Elf64_Phdr ElfProgramHeader;
typedef Elf64_Nhdr ElfNote;
typedef Elf64_Sym  ElfSymbol;
typedef Elf64_Rel  ElfRelocation;
typedef Elf64_Dyn  ElfDyn;
#define ELF_R_TYPE ELF64_R_TYPE
#define ELF_R_SYM  ELF64_R_SYM
#else
const unsigned char ELFCLASS_SUPPORTED = ELFCLASS32;
typedef Elf32_Ehdr ElfHeader;
typedef Elf32_Shdr ElfSection;
typedef Elf32_Phdr ElfProgramHeader;
typedef Elf32_Nhdr ElfNote;
typedef Elf32_Sym  ElfSymbol;
typedef Elf32_Rel  ElfRelocation;
typedef Elf32_Dyn  ElfDyn;
#define ELF_R_TYPE ELF32_R_TYPE
#define ELF_R_SYM  ELF32_R_SYM
#endif // __LP64__

#if defined(__x86_64__)
#  define R_GLOB_DAT R_X86_64_GLOB_DAT
#  define R_ABS64 R_X86_64_64
#elif defined(__i386__)
#  define R_GLOB_DAT R_386_GLOB_DAT
#  define R_ABS64 -1
#elif defined(__arm__) || defined(__thumb__)
#  define R_GLOB_DAT R_ARM_GLOB_DAT
#  define R_ABS64 -1
#elif defined(__aarch64__)
#  define R_GLOB_DAT R_AARCH64_GLOB_DAT
#  define R_ABS64 R_AARCH64_ABS64
#elif defined(__PPC64__)
#  define R_GLOB_DAT R_PPC64_GLOB_DAT
#  define R_ABS64 -1
#elif defined(__riscv) && (__riscv_xlen == 64)
// RISC-V does not have GLOB_DAT relocation, use something neutral,
// like the impossible relocation number.
#  define R_GLOB_DAT -1
#  define R_ABS64 -1
#elif defined(__loongarch_lp64)
// LOONGARCH does not have GLOB_DAT relocation, use something neutral,
// like the impossible relocation number.
#  define R_GLOB_DAT -1
#  define R_ABS64 -1
#else
#  error "Compiling on unsupported arch"
#endif


static char _debuginfod_cache_buf[PATH_MAX] = {0};

class ElfParser {
  private:
    CodeCache* _cc;
    const char* _base;
    const char* _file_name;
    bool _relocate_dyn;
    ElfHeader* _header;
    const char* _sections;
    const char* _vaddr_diff;

    ElfParser(CodeCache* cc, const char* base, const void* addr, const char* file_name, bool relocate_dyn) {
        _cc = cc;
        _base = base;
        _file_name = file_name;
        _relocate_dyn = relocate_dyn;
        _header = (ElfHeader*)addr;
        _sections = (const char*)addr + _header->e_shoff;
    }

    bool validHeader() {
        unsigned char* ident = _header->e_ident;
        return ident[0] == 0x7f && ident[1] == 'E' && ident[2] == 'L' && ident[3] == 'F'
            && ident[4] == ELFCLASS_SUPPORTED && ident[5] == ELFDATA2LSB && ident[6] == EV_CURRENT
            && _header->e_shstrndx != SHN_UNDEF;
    }

    ElfSection* section(int index) {
        return (ElfSection*)(_sections + index * _header->e_shentsize);
    }

    const char* at(ElfSection* section) {
        return (const char*)_header + section->sh_offset;
    }

    const char* at(ElfProgramHeader* pheader) {
        if (_header->e_type == ET_EXEC) {
            return (const char*)pheader->p_vaddr;
        }
        return _vaddr_diff == NULL ? (const char*)pheader->p_vaddr : _vaddr_diff + pheader->p_vaddr;
    }

    const char* base() {
        return _header->e_type == ET_EXEC ? NULL : _vaddr_diff;
    }

    char* dyn_ptr(ElfDyn* dyn) {
        // GNU dynamic linker relocates pointers in the dynamic section, while musl doesn't.
        // Also, [vdso] is not relocated, and its vaddr may differ from the load address.
        if (_relocate_dyn || (_base != NULL && (char*)dyn->d_un.d_ptr < _base)) {
            return _vaddr_diff == NULL ? (char*)dyn->d_un.d_ptr : (char*)_vaddr_diff + dyn->d_un.d_ptr;
        } else {
            return (char*)dyn->d_un.d_ptr;
        }
    }

    ElfSection* findSection(uint32_t type, const char* name);
    ElfProgramHeader* findProgramHeader(uint32_t type);

    void calcVirtualLoadAddress();
    void parseDynamicSection();
    void parseDwarfInfo();
    uint32_t getSymbolCount(uint32_t* gnu_hash);
    void loadSymbols(bool use_debug);
    bool loadSymbolsFromDebug(const char* build_id, const int build_id_len);
    bool loadSymbolsFromDebuginfodCache(const char* build_id, const int build_id_len);
    bool loadSymbolsUsingBuildId();
    bool loadSymbolsUsingDebugLink();
    void loadSymbolTable(const char* symbols, size_t total_size, size_t ent_size, const char* strings);
    void addRelocationSymbols(ElfSection* reltab, const char* plt);
    const char* getDebuginfodCache();

  public:
    static void parseProgramHeaders(CodeCache* cc, const char* base, const char* end, bool relocate_dyn);
    static bool parseFile(CodeCache* cc, const char* base, const char* file_name, bool use_debug);
};


ElfSection* ElfParser::findSection(uint32_t type, const char* name) {
    const char* strtab = at(section(_header->e_shstrndx));

    for (int i = 0; i < _header->e_shnum; i++) {
        ElfSection* section = this->section(i);
        if (section->sh_type == type && section->sh_name != 0) {
            if (strcmp(strtab + section->sh_name, name) == 0) {
                return section;
            }
        }
    }

    return NULL;
}

ElfProgramHeader* ElfParser::findProgramHeader(uint32_t type) {
    const char* pheaders = (const char*)_header + _header->e_phoff;

    for (int i = 0; i < _header->e_phnum; i++) {
        ElfProgramHeader* pheader = (ElfProgramHeader*)(pheaders + i * _header->e_phentsize);
        if (pheader->p_type == type) {
            return pheader;
        }
    }

    return NULL;
}

bool ElfParser::parseFile(CodeCache* cc, const char* base, const char* file_name, bool use_debug) {
    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        return false;
    }

    size_t length = (size_t)lseek(fd, 0, SEEK_END);
    void* addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    if (addr == MAP_FAILED) {
        Log::warn("Could not parse symbols from %s: %s", file_name, strerror(errno));
    } else {
        ElfParser elf(cc, base, addr, file_name, false);
        if (elf.validHeader()) {
            elf.calcVirtualLoadAddress();
            elf.loadSymbols(use_debug);
        }
        munmap(addr, length);
    }
    return true;
}

void ElfParser::parseProgramHeaders(CodeCache* cc, const char* base, const char* end, bool relocate_dyn) {
    ElfParser elf(cc, base, base, NULL, relocate_dyn);
    if (elf.validHeader() && base + elf._header->e_phoff < end) {
        cc->setTextBase(base);
        elf.calcVirtualLoadAddress();
        elf.parseDynamicSection();
        elf.parseDwarfInfo();
    }
}

void ElfParser::calcVirtualLoadAddress() {
    // Find a difference between the virtual load address (often zero) and the actual DSO base
    if (_base == NULL) {
        _vaddr_diff = NULL;
        return;
    }
    const char* pheaders = (const char*)_header + _header->e_phoff;
    for (int i = 0; i < _header->e_phnum; i++) {
        ElfProgramHeader* pheader = (ElfProgramHeader*)(pheaders + i * _header->e_phentsize);
        if (pheader->p_type == PT_LOAD) {
            _vaddr_diff = _base - pheader->p_vaddr;
            return;
        }
    }
    _vaddr_diff = _base;
}

void ElfParser::parseDynamicSection() {
    ElfProgramHeader* dynamic = findProgramHeader(PT_DYNAMIC);
    if (dynamic != NULL) {
        const char* symtab = NULL;
        const char* strtab = NULL;
        char* jmprel = NULL;
        char* rel = NULL;
        size_t pltrelsz = 0;
        size_t relsz = 0;
        size_t relent = 0;
        size_t relcount = 0;
        size_t syment = 0;
        uint32_t nsyms = 0;

        const char* dyn_start = at(dynamic);
        const char* dyn_end = dyn_start + dynamic->p_memsz;
        for (ElfDyn* dyn = (ElfDyn*)dyn_start; dyn < (ElfDyn*)dyn_end; dyn++) {
            switch (dyn->d_tag) {
                case DT_SYMTAB:
                    symtab = dyn_ptr(dyn);
                    break;
                case DT_STRTAB:
                    strtab = dyn_ptr(dyn);
                    break;
                case DT_SYMENT:
                    syment = dyn->d_un.d_val;
                    break;
                case DT_HASH:
                    nsyms = ((uint32_t*)dyn_ptr(dyn))[1];
                    break;
                case DT_GNU_HASH:
                    if (nsyms == 0) {
                        nsyms = getSymbolCount((uint32_t*)dyn_ptr(dyn));
                    }
                    break;
                case DT_JMPREL:
                    jmprel = dyn_ptr(dyn);
                    break;
                case DT_PLTRELSZ:
                    pltrelsz = dyn->d_un.d_val;
                    break;
                case DT_RELA:
                case DT_REL:
                    rel = dyn_ptr(dyn);
                    break;
                case DT_RELASZ:
                case DT_RELSZ:
                    relsz = dyn->d_un.d_val;
                    break;
                case DT_RELAENT:
                case DT_RELENT:
                    relent = dyn->d_un.d_val;
                    break;
                case DT_RELACOUNT:
                case DT_RELCOUNT:
                    relcount = dyn->d_un.d_val;
                    break;
            }
        }

        if (symtab == NULL || strtab == NULL || syment == 0 || relent == 0) {
            return;
        }

        if (!_cc->hasDebugSymbols() && nsyms > 0) {
            loadSymbolTable(symtab, syment * nsyms, syment, strtab);
        }

        const char* base = this->base();
        if (jmprel != NULL && pltrelsz != 0) {
            // Parse .rela.plt table
            for (size_t offs = 0; offs < pltrelsz; offs += relent) {
                ElfRelocation* r = (ElfRelocation*)(jmprel + offs);
                ElfSymbol* sym = (ElfSymbol*)(symtab + ELF_R_SYM(r->r_info) * syment);
                if (sym->st_name != 0) {
                    _cc->addImport((void**)(base + r->r_offset), strtab + sym->st_name);
                }
            }
        }

        if (rel != NULL && relsz != 0) {
            // Relocation entries for imports can be found in .rela.dyn, for example
            // if a shared library is built without PLT (-fno-plt). However, if both
            // entries exist, addImport saves them both.
            for (size_t offs = relcount * relent; offs < relsz; offs += relent) {
                ElfRelocation* r = (ElfRelocation*)(rel + offs);
                if (ELF_R_TYPE(r->r_info) == R_GLOB_DAT || ELF_R_TYPE(r->r_info) == R_ABS64) {
                    ElfSymbol* sym = (ElfSymbol*)(symtab + ELF_R_SYM(r->r_info) * syment);
                    if (sym->st_name != 0) {
                        _cc->addImport((void**)(base + r->r_offset), strtab + sym->st_name);
                    }
                }
            }
        }
    }
}

void ElfParser::parseDwarfInfo() {
    if (!DWARF_SUPPORTED) return;

    ElfProgramHeader* eh_frame_hdr = findProgramHeader(PT_GNU_EH_FRAME);
    if (eh_frame_hdr != NULL) {
        if (eh_frame_hdr->p_vaddr != 0) {
            DwarfParser dwarf(_cc->name(), _base, at(eh_frame_hdr));
            _cc->setDwarfTable(dwarf.table(), dwarf.count());
        } else if (strcmp(_cc->name(), "[vdso]") == 0) {
            FrameDesc* table = (FrameDesc*)malloc(sizeof(FrameDesc));
            *table = FrameDesc::empty_frame;
            _cc->setDwarfTable(table, 1);
        }
    }
}

uint32_t ElfParser::getSymbolCount(uint32_t* gnu_hash) {
    uint32_t nbuckets = gnu_hash[0];
    uint32_t* buckets = &gnu_hash[4] + gnu_hash[2] * (sizeof(size_t) / 4);

    uint32_t nsyms = 0;
    for (uint32_t i = 0; i < nbuckets; i++) {
        if (buckets[i] > nsyms) nsyms = buckets[i];
    }

    if (nsyms > 0) {
        uint32_t* chain = &buckets[nbuckets] - gnu_hash[1];
        while (!(chain[nsyms++] & 1));
    }
    return nsyms;
}

void ElfParser::loadSymbols(bool use_debug) {
    ElfSection* symtab = findSection(SHT_SYMTAB, ".symtab");
    if (symtab != NULL) {
        // Parse debug symbols from the original .so
        ElfSection* strtab = section(symtab->sh_link);
        loadSymbolTable(at(symtab), symtab->sh_size, symtab->sh_entsize, at(strtab));
        _cc->setDebugSymbols(true);
    } else if (use_debug) {
        // Try to load symbols from an external debuginfo library
        loadSymbolsUsingBuildId() || loadSymbolsUsingDebugLink();
    }

    if (use_debug) {
        // Synthesize names for PLT stubs
        ElfSection* plt = findSection(SHT_PROGBITS, ".plt");
        if (plt != NULL) {
            _cc->setPlt(plt->sh_addr, plt->sh_size);
            ElfSection* reltab = findSection(SHT_RELA, ".rela.plt");
            if (reltab != NULL || (reltab = findSection(SHT_REL, ".rel.plt")) != NULL) {
                addRelocationSymbols(reltab, base() + plt->sh_addr + PLT_HEADER_SIZE);
            }
        }
    }
}

const char* ElfParser::getDebuginfodCache() {
    if (_debuginfod_cache_buf[0]) {
        return _debuginfod_cache_buf;
    }

    const char* env_vars[] = {"DEBUGINFOD_CACHE_PATH", "XDG_CACHE_HOME", "HOME"};
    const char* suffixes[] = {"/", "debuginfod_client/", ".cache/debuginfod_client/"};

    for (int i = 0; i < sizeof(env_vars) / sizeof(env_vars[0]); i++) {
        const char* env_val = getenv(env_vars[i]);
        if (!env_val || !env_val[0]) {
            continue;
        }

        if (snprintf(_debuginfod_cache_buf, sizeof(_debuginfod_cache_buf), "%s/%s", env_val, suffixes[i]) < sizeof(_debuginfod_cache_buf)) {
            return _debuginfod_cache_buf;
        }
    }

    _debuginfod_cache_buf[0] = '\0';
    return _debuginfod_cache_buf;
}

bool ElfParser::loadSymbolsFromDebug(const char* build_id, const int build_id_len) {
    char path[PATH_MAX];
    char* p = path + snprintf(path, sizeof(path), "/usr/lib/debug/.build-id/%02hhx/", build_id[0]);
    for (int i = 1; i < build_id_len; i++) {
        p += snprintf(p, 3, "%02hhx", build_id[i]);
    }
    strcpy(p, ".debug");

    return parseFile(_cc, _base, path, false);
}

bool ElfParser::loadSymbolsFromDebuginfodCache(const char* build_id, const int build_id_len) {
    const char* debuginfod_cache = getDebuginfodCache();
    if (debuginfod_cache == NULL || !debuginfod_cache[0]) {
        return false;
    }

    char path[PATH_MAX];
    const int debuginfod_cache_len = strlen(debuginfod_cache);
    if (debuginfod_cache_len + build_id_len + strlen("/debuginfo") >= sizeof(path)) {
        Log::warn("Path too long, skipping loading symbols: %s", debuginfod_cache);
        return false;
    }

    char* p = strcpy(path, debuginfod_cache);
    p += debuginfod_cache_len;
    for (int i = 0; i < build_id_len; i++) {
        p += snprintf(p, 3, "%02hhx", build_id[i]);
    }
    strcpy(p, "/debuginfo");

    return parseFile(_cc, _base, path, false);
}

// Load symbols from the first file that exists in the following locations, in order, where abcdef1234 is Build ID.
//   /usr/lib/debug/.build-id/ab/cdef1234.debug
//   $DEBUGINFOD_CACHE_PATH/abcdef1234/debuginfo
//   $XDG_CACHE_HOME/debuginfod_client/abcdef1234/debuginfo
//   $HOME/.cache/debuginfod_client/abcdef1234/debuginfo
bool ElfParser::loadSymbolsUsingBuildId() {
    ElfSection* section = findSection(SHT_NOTE, ".note.gnu.build-id");
    if (section == NULL || section->sh_size <= 16) {
        return false;
    }

    ElfNote* note = (ElfNote*)at(section);
    if (note->n_namesz != 4 || note->n_descsz < 2 || note->n_descsz > 64) {
        return false;
    }

    const char* build_id = (const char*)note + sizeof(*note) + 4;
    int build_id_len = note->n_descsz;

    return loadSymbolsFromDebug(build_id, build_id_len)
        || loadSymbolsFromDebuginfodCache(build_id, build_id_len);
}

// Look for debuginfo file specified in .gnu_debuglink section
bool ElfParser::loadSymbolsUsingDebugLink() {
    ElfSection* section = findSection(SHT_PROGBITS, ".gnu_debuglink");
    if (section == NULL || section->sh_size <= 4) {
        return false;
    }

    const char* basename = strrchr(_file_name, '/');
    if (basename == NULL) {
        return false;
    }

    char* dirname = strndup(_file_name, basename - _file_name);
    if (dirname == NULL) {
        return false;
    }

    const char* debuglink = at(section);
    char path[PATH_MAX];
    bool result = false;

    // 1. /path/to/libjvm.so.debug
    if (strcmp(debuglink, basename + 1) != 0 &&
        snprintf(path, PATH_MAX, "%s/%s", dirname, debuglink) < PATH_MAX) {
        result = parseFile(_cc, _base, path, false);
    }

    // 2. /path/to/.debug/libjvm.so.debug
    if (!result && snprintf(path, PATH_MAX, "%s/.debug/%s", dirname, debuglink) < PATH_MAX) {
        result = parseFile(_cc, _base, path, false);
    }

    // 3. /usr/lib/debug/path/to/libjvm.so.debug
    if (!result && snprintf(path, PATH_MAX, "/usr/lib/debug%s/%s", dirname, debuglink) < PATH_MAX) {
        result = parseFile(_cc, _base, path, false);
    }

    free(dirname);
    return result;
}

void ElfParser::loadSymbolTable(const char* symbols, size_t total_size, size_t ent_size, const char* strings) {
    const char* base = this->base();
    for (const char* symbols_end = symbols + total_size; symbols < symbols_end; symbols += ent_size) {
        ElfSymbol* sym = (ElfSymbol*)symbols;
        if (sym->st_name != 0 && sym->st_value != 0) {
            // Skip special AArch64 mapping symbols: $x and $d
            if (sym->st_size != 0 || sym->st_info != 0 || strings[sym->st_name] != '$') {
                const char* addr;
                if (base != NULL) {
                    // Check for overflow when adding sym->st_value to base
                    uintptr_t base_addr = (uintptr_t)base;
                    uint64_t symbol_value = sym->st_value;
                    
                    // Skip this symbol if addition would overflow
                    // First check if symbol_value exceeds the address space
                    if (symbol_value > UINTPTR_MAX) {
                        continue;
                    }
                    // Then check if addition would overflow
                    if (base_addr > UINTPTR_MAX - (uintptr_t)symbol_value) {
                        continue;
                    }
                    
                    // Perform addition using integer arithmetic to avoid pointer overflow
                    addr = (const char*)(base_addr + (uintptr_t)symbol_value);
                } else {
                    addr = (const char*)sym->st_value;
                }
                _cc->add(addr, (int)sym->st_size, strings + sym->st_name);
            }
        }
    }
}

void ElfParser::addRelocationSymbols(ElfSection* reltab, const char* plt) {
    ElfSection* symtab = section(reltab->sh_link);
    const char* symbols = at(symtab);

    ElfSection* strtab = section(symtab->sh_link);
    const char* strings = at(strtab);

    const char* relocations = at(reltab);
    const char* relocations_end = relocations + reltab->sh_size;
    for (; relocations < relocations_end; relocations += reltab->sh_entsize) {
        ElfRelocation* r = (ElfRelocation*)relocations;
        ElfSymbol* sym = (ElfSymbol*)(symbols + ELF_R_SYM(r->r_info) * symtab->sh_entsize);

        char name[256];
        if (sym->st_name == 0) {
            strcpy(name, "@plt");
        } else {
            const char* sym_name = strings + sym->st_name;
            snprintf(name, sizeof(name), "%s%cplt", sym_name, sym_name[0] == '_' && sym_name[1] == 'Z' ? '.' : '@');
            name[sizeof(name) - 1] = 0;
        }

        _cc->add(plt, PLT_ENTRY_SIZE, name);
        plt += PLT_ENTRY_SIZE;
    }
}


Mutex Symbols::_parse_lock;
bool Symbols::_have_kernel_symbols = false;
bool Symbols::_libs_limit_reported = false;
static std::unordered_set<u64> _parsed_inodes;
static bool _in_parse_libraries = false;

void Symbols::parseKernelSymbols(CodeCache* cc) {
    int fd;
    if (FdTransferClient::hasPeer()) {
        fd = FdTransferClient::requestKallsymsFd();
    } else {
        fd = open("/proc/kallsyms", O_RDONLY);
    }

    if (fd == -1) {
        Log::warn("open(\"/proc/kallsyms\"): %s", strerror(errno));
        return;
    }

    FILE* f = fdopen(fd, "r");
    if (f == NULL) {
        Log::warn("fdopen(): %s", strerror(errno));
        close(fd);
        return;
    }

    char str[256];
    while (fgets(str, sizeof(str) - 8, f) != NULL) {
        size_t len = strlen(str) - 1; // trim the '\n'
        strcpy(str + len, "_[k]");

        SymbolDesc symbol(str);
        char type = symbol.type();
        if (type == 'T' || type == 't' || type == 'W' || type == 'w') {
            const char* addr = symbol.addr();
            if (addr != NULL) {
                if (!_have_kernel_symbols) {
                    if (strncmp(symbol.name(), "__LOAD_PHYSICAL_ADDR", 20) == 0 ||
                        strncmp(symbol.name(), "phys_startup", 12) == 0) {
                        continue;
                    }
                    _have_kernel_symbols = true;
                }
                cc->add(addr, 0, symbol.name());
            }
        }
    }

    fclose(f);
}

static void collectSharedLibraries(std::unordered_map<u64, SharedLibrary>& libs, int max_count) {
    FILE* f = fopen("/proc/self/maps", "r");
    if (f == NULL) {
        return;
    }

    const char* image_base = NULL;
    u64 last_inode = 0;
    char* str = NULL;
    size_t str_size = 0;
    ssize_t len;

    while (max_count > 0 && (len = getline(&str, &str_size, f)) > 0) {
        str[len - 1] = 0;

        MemoryMapDesc map(str);
        if (!map.isReadable() || map.file() == NULL || map.file()[0] == 0) {
            continue;
        }

        u64 inode = u64(map.dev()) << 32 | map.inode();
        if (_parsed_inodes.find(inode) != _parsed_inodes.end()) {
            continue;  // shared object is already parsed
        }
        if (inode == 0 && strcmp(map.file(), "[vdso]") != 0) {
            continue;  // all shared libraries have inode, except vDSO
        }

        const char* map_start = map.addr();
        const char* map_end = map.end();
        if (inode != last_inode && map.offs() == 0) {
            image_base = map_start;
            last_inode = inode;
        }

        if (map.isExecutable()) {
            SharedLibrary& lib = libs[inode];
            if (lib.file == nullptr) {
                lib.file = strdup(map.file());
                lib.map_start = map_start;
                lib.map_end = map_end;
                lib.image_base = inode == last_inode ? image_base : NULL;
                max_count--;
            } else {
                // The same library may have multiple executable segments mapped
                lib.map_end = map_end;
            }
        }
    }

    free(str);
    fclose(f);
}

void Symbols::parseLibraries(CodeCacheArray* array, bool kernel_symbols) {
    MutexLocker ml(_parse_lock);

    if (_in_parse_libraries || array->count() >= MAX_NATIVE_LIBS) {
        return;
    }
    _in_parse_libraries = true;

    if (kernel_symbols && !haveKernelSymbols()) {
        CodeCache* cc = new CodeCache("[kernel]");
        parseKernelSymbols(cc);

        if (haveKernelSymbols()) {
            cc->sort();
            array->add(cc);
            // Update global native code bounds for PC validation in stack walker
            NativeCodeBounds::updateBounds(cc->minAddress(), cc->maxAddress());
        } else {
            delete cc;
        }
    }

    std::unordered_map<u64, SharedLibrary> libs;
    collectSharedLibraries(libs, MAX_NATIVE_LIBS - array->count());

    for (auto& it : libs) {
        u64 inode = it.first;
        _parsed_inodes.insert(inode);

        SharedLibrary& lib = it.second;
        CodeCache* cc = new CodeCache(lib.file, array->count(), lib.map_start, lib.map_end, lib.image_base);

        if (strchr(lib.file, ':') != NULL) {
            // Do not try to parse pseudofiles like anon_inode:name, /memfd:name
        } else if (strcmp(lib.file, "[vdso]") == 0) {
            ElfParser::parseProgramHeaders(cc, lib.map_start, lib.map_end, true);
        } else if (lib.image_base == NULL) {
            // Unlikely case when image base has not been found: not safe to access program headers.
            // Be careful: executable file is not always ELF, e.g. classes.jsa
            ElfParser::parseFile(cc, lib.map_start, lib.file, true);
        } else {
            // Parse debug symbols first
            ElfParser::parseFile(cc, lib.image_base, lib.file, true);

            UnloadProtection handle(cc);
            if (handle.isValid()) {
                ElfParser::parseProgramHeaders(cc, lib.image_base, lib.map_end, OS::isMusl());
            }
        }

        free(lib.file);

        cc->sort();
        applyPatch(cc);
        array->add(cc);

        // Update global native code bounds for PC validation in stack walker
        NativeCodeBounds::updateBounds(cc->minAddress(), cc->maxAddress());
    }

    if (array->count() >= MAX_NATIVE_LIBS && !_libs_limit_reported) {
        Log::warn("Number of parsed libraries reached the limit of %d", MAX_NATIVE_LIBS);
        _libs_limit_reported = true;
    }

    _in_parse_libraries = false;
}

// Check that the base address of the shared object has not changed
static bool verifyBaseAddress(const CodeCache* cc, void* lib_handle) {
    Dl_info dl_info;
    struct link_map* map;

    if (dlinfo(lib_handle, RTLD_DI_LINKMAP, &map) != 0 || dladdr(map->l_ld, &dl_info) == 0) {
        return false;
    }

    return cc->imageBase() == (const char*)dl_info.dli_fbase;
}

UnloadProtection::UnloadProtection(const CodeCache *cc) {
    if (OS::isMusl() || isMainExecutable(cc->imageBase(), cc->maxAddress()) || isLoader(cc->imageBase())) {
        _lib_handle = NULL;
        _valid = true;
        return;
    }

    // dlopen() can reopen previously loaded libraries even if the underlying file has been deleted
    const char* stripped_name = cc->name();
    size_t name_len = strlen(stripped_name);
    if (name_len > 10 && strcmp(stripped_name + name_len - 10, " (deleted)") == 0) {
        char* buf = (char*) alloca(name_len - 9);
        *stpncpy(buf, stripped_name, name_len - 10) = 0;
        stripped_name = buf;
    }

    // Protect library from unloading while parsing in-memory ELF program headers.
    // Also, dlopen() ensures the library is fully loaded.
    _lib_handle = dlopen(stripped_name, RTLD_LAZY | RTLD_NOLOAD);
    _valid = _lib_handle != NULL && verifyBaseAddress(cc, _lib_handle);
}

UnloadProtection::~UnloadProtection() {
    if (_lib_handle != NULL) {
        dlclose(_lib_handle);
    }
}

void Symbols::initLibraryRanges() {
    init_lib_ranges_once();
}

bool Symbols::isLibcOrPthreadAddress(uintptr_t pc) {
    // Fast, allocation-free integer checks — no strings involved.
    // initLibraryRanges() must have been called during profiler startup.
    if (pc_in_range(pc, &g_libc)) return true;
    if (pc_in_range(pc, &g_libpthread)) return true;
    return false;
}


// Implementation of clearParsingCaches for test compatibility
void Symbols::clearParsingCaches() {
    _parsed_inodes.clear();
}

// GNU build-id extraction implementation
//
// The build-id is a unique identifier embedded in ELF binaries and shared libraries.
// It is stored in a PT_NOTE program header segment as an ELF note with type NT_GNU_BUILD_ID.
//
// References:
// - ELF Specification: https://refspecs.linuxfoundation.org/elf/elf.pdf
// - ELF Note Section: https://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/noteobject.html
// - GNU build-id: https://fedoraproject.org/wiki/Releases/FeatureBuildId
// - GNU binutils ld --build-id: https://sourceware.org/binutils/docs/ld/Options.html
// - readelf(1) --notes: https://man7.org/linux/man-pages/man1/readelf.1.html
//
// Build-ID format:
// - Located in PT_NOTE program header segments (p_type == PT_NOTE)
// - Stored as ELF note with:
//   - n_namesz = 4 (length of "GNU\0")
//   - n_descsz = build-id length (typically 20 bytes for SHA1)
//   - n_type = NT_GNU_BUILD_ID (3)
//   - name = "GNU\0"
//   - desc = build-id bytes
// - All fields are 4-byte aligned as per ELF note format

// GNU build-id note constants
#define NT_GNU_BUILD_ID 3
#define GNU_BUILD_ID_NAME "GNU"

char* SymbolsLinux::extractBuildId(const char* file_path, size_t* build_id_len) {
    if (!file_path || !build_id_len) {
        return nullptr;
    }

    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        return nullptr;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return nullptr;
    }

    void* elf_base = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    if (elf_base == MAP_FAILED) {
        return nullptr;
    }

    char* result = extractBuildIdFromMemory(elf_base, st.st_size, build_id_len);

    munmap(elf_base, st.st_size);
    return result;
}

char* SymbolsLinux::extractBuildIdFromMemory(const void* elf_base, size_t elf_size, size_t* build_id_len) {
    if (!elf_base || !build_id_len || elf_size < sizeof(Elf64_Ehdr)) {
        return nullptr;
    }

    const Elf64_Ehdr* ehdr = static_cast<const Elf64_Ehdr*>(elf_base);

    // Verify ELF magic
    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
        return nullptr;
    }

    // Only handle 64-bit ELF for now
    if (ehdr->e_ident[EI_CLASS] != ELFCLASS64) {
        return nullptr;
    }

    // Check if we have program headers
    if (ehdr->e_phoff == 0 || ehdr->e_phnum == 0) {
        return nullptr;
    }

    // Verify program header table is within file bounds
    if (ehdr->e_phoff + ehdr->e_phnum * sizeof(Elf64_Phdr) > elf_size) {
        return nullptr;
    }

    // Verify program header offset is properly aligned
    if (ehdr->e_phoff % alignof(Elf64_Phdr) != 0) {
        return nullptr;
    }

    const char* base = static_cast<const char*>(elf_base);
    const Elf64_Phdr* phdr = reinterpret_cast<const Elf64_Phdr*>(base + ehdr->e_phoff);

    // Search for PT_NOTE segments
    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type == PT_NOTE && phdr[i].p_filesz > 0) {
            // Ensure note segment is within file bounds
            if (phdr[i].p_offset + phdr[i].p_filesz > elf_size) {
                continue;
            }

            const void* note_data = base + phdr[i].p_offset;
            const uint8_t* build_id_bytes = findBuildIdInNotes(note_data, phdr[i].p_filesz, build_id_len);

            if (build_id_bytes) {
                return buildIdToHex(build_id_bytes, *build_id_len);
            }
        }
    }

    return nullptr;
}

const uint8_t* SymbolsLinux::findBuildIdInNotes(const void* note_data, size_t note_size, size_t* build_id_len) {
    const char* data = static_cast<const char*>(note_data);
    size_t offset = 0;

    // Parse ELF note entries within the PT_NOTE segment
    // Each note has the structure:
    //   typedef struct {
    //     Elf64_Word n_namesz;  // Length of name field (including null terminator)
    //     Elf64_Word n_descsz;  // Length of descriptor (build-id bytes)
    //     Elf64_Word n_type;    // Note type (NT_GNU_BUILD_ID == 3)
    //     // Followed by name (4-byte aligned)
    //     // Followed by descriptor (4-byte aligned)
    //   } Elf64_Nhdr;
    // Reference: https://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/noteobject.html
    while (offset < note_size) {
        // Ensure there is enough space for the note header itself
        if (note_size - offset < sizeof(Elf64_Nhdr)) {
            break;
        }

        const Elf64_Nhdr* nhdr = reinterpret_cast<const Elf64_Nhdr*>(data + offset);

        // Calculate aligned sizes (4-byte alignment as per ELF spec)
        size_t name_size_aligned = (nhdr->n_namesz + 3) & ~static_cast<size_t>(3);
        size_t desc_size_aligned = (nhdr->n_descsz + 3) & ~static_cast<size_t>(3);

        // Check bounds using subtraction to avoid overflow
        size_t remaining = note_size - offset - sizeof(Elf64_Nhdr);
        if (name_size_aligned > remaining) {
            break;
        }
        remaining -= name_size_aligned;
        if (desc_size_aligned > remaining) {
            break;
        }

        // Check if this is a GNU build-id note
        if (nhdr->n_type == NT_GNU_BUILD_ID && nhdr->n_namesz > 0 && nhdr->n_descsz > 0) {
            const char* name = data + offset + sizeof(Elf64_Nhdr);

            // Verify GNU build-id name (including null terminator)
            if (nhdr->n_namesz == 4 && strncmp(name, GNU_BUILD_ID_NAME, 3) == 0 && name[3] == '\0') {
                const uint8_t* desc = reinterpret_cast<const uint8_t*>(data + offset + sizeof(Elf64_Nhdr) + name_size_aligned);
                *build_id_len = nhdr->n_descsz;
                return desc;
            }
        }

        offset += sizeof(Elf64_Nhdr) + name_size_aligned + desc_size_aligned;
    }

    return nullptr;
}

char* SymbolsLinux::buildIdToHex(const uint8_t* build_id_bytes, size_t byte_len) {
    if (!build_id_bytes || byte_len == 0) {
        return nullptr;
    }

    // Allocate string for hex representation (2 chars per byte + null terminator)
    char* hex_str = static_cast<char*>(malloc(byte_len * 2 + 1));
    if (!hex_str) {
        return nullptr;
    }

    for (size_t i = 0; i < byte_len; i++) {
        snprintf(hex_str + i * 2, 3, "%02x", build_id_bytes[i]);
    }

    hex_str[byte_len * 2] = '\0';
    return hex_str;
}

#endif // __linux__
