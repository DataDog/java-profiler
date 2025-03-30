#ifdef __linux__
#include "symbols.h"

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>

class SymbolDesc {
private:
  const char *_addr;
  const char *_desc;

public:
  SymbolDesc(const char *s) {
    _addr = s;
    _desc = strchr(_addr, ' ');
  }

  const char *addr() { return (const char *)strtoul(_addr, NULL, 16); }
  char type() { return _desc != NULL ? _desc[1] : 0; }
  const char *name() { return _desc + 3; }
};

class MemoryMapDesc {
private:
  const char *_addr;
  const char *_end;
  const char *_perm;
  const char *_offs;
  const char *_dev;
  const char *_inode;
  const char *_file;

public:
  MemoryMapDesc(const char *s) {
    _addr = s;
    _end = strchr(_addr, '-') + 1;
    _perm = strchr(_end, ' ') + 1;
    _offs = strchr(_perm, ' ') + 1;
    _dev = strchr(_offs, ' ') + 1;
    _inode = strchr(_dev, ' ') + 1;
    _file = strchr(_inode, ' ');

    if (_file != NULL) {
      while (*_file == ' ')
        _file++;
    }
  }

  const char *file() { return _file; }
  bool isReadable() { return _perm[0] == 'r'; }
  bool isExecutable() { return _perm[2] == 'x'; }
  const char *addr() { return (const char *)strtoul(_addr, NULL, 16); }
  const char *end() { return (const char *)strtoul(_end, NULL, 16); }
  unsigned long offs() { return strtoul(_offs, NULL, 16); }
  unsigned long inode() { return strtoul(_inode, NULL, 10); }

  unsigned long dev() {
    char *colon;
    unsigned long major = strtoul(_dev, &colon, 16);
    unsigned long minor = strtoul(colon + 1, NULL, 16);
    return major << 8 | minor;
  }
};

#ifdef __LP64__
const unsigned char ELFCLASS_SUPPORTED = ELFCLASS64;
typedef Elf64_Ehdr ElfHeader;
typedef Elf64_Shdr ElfSection;
typedef Elf64_Phdr ElfProgramHeader;
typedef Elf64_Nhdr ElfNote;
typedef Elf64_Sym ElfSymbol;
typedef Elf64_Rel ElfRelocation;
typedef Elf64_Dyn ElfDyn;
#define ELF_R_TYPE ELF64_R_TYPE
#define ELF_R_SYM ELF64_R_SYM
#else
const unsigned char ELFCLASS_SUPPORTED = ELFCLASS32;
typedef Elf32_Ehdr ElfHeader;
typedef Elf32_Shdr ElfSection;
typedef Elf32_Phdr ElfProgramHeader;
typedef Elf32_Nhdr ElfNote;
typedef Elf32_Sym ElfSymbol;
typedef Elf32_Rel ElfRelocation;
typedef Elf32_Dyn ElfDyn;
#define ELF_R_TYPE ELF32_R_TYPE
#define ELF_R_SYM ELF32_R_SYM
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

#ifdef __musl__
static const bool MUSL = true;
#else
static const bool MUSL = false;
#endif // __musl__

#define ROOT_SYMBOL_KIND(X)                                                  \
  X(_start, "_start")                                                        \
  X(start_thread, "start_thread")                                            \
  X(_ZL19thread_native_entryP6Thread, "_ZL19thread_native_entryP6Thread")    \
  X(_thread_start, "_thread_start")                                          \
  X(thread_start, "thread_start")

#define X_ENUM(a, b) a,
typedef enum RootSymbolKind : int {
  ROOT_SYMBOL_KIND(X_ENUM) LAST_ROOT_SYMBOL_KIND
} RootSymbolKind;
#undef X_ENUM

typedef struct {
  const char* name;
  RootSymbolKind kind;
} RootSymbolEntry;

#define X_ENTRY(a, b) { b, a },
static const RootSymbolEntry root_symbol_table[] = {
  ROOT_SYMBOL_KIND(X_ENTRY)
};
#undef X_ENTRY

class ElfParser {
friend Symbols;
private:
  static uintptr_t _root_symbols[LAST_ROOT_SYMBOL_KIND];

  CodeCache *_cc;
  const char *_base;
  const char *_file_name;
  size_t _length;
  bool _relocate_dyn;
  ElfHeader *_header;
  const char *_sections;
  const char *_vaddr_diff;

  ElfParser(CodeCache *cc, const char *base, const void *addr,
            const char *file_name, size_t length, bool relocate_dyn) {
    _cc = cc;
    _base = base;
    _file_name = file_name;
    _length = length;
    _relocate_dyn = relocate_dyn && base != nullptr;
    _header = (ElfHeader *)addr;
    _sections = (const char *)addr + _header->e_shoff;
  }

  bool validHeader() {
    unsigned char *ident = _header->e_ident;
    return ident[0] == 0x7f && ident[1] == 'E' && ident[2] == 'L' &&
           ident[3] == 'F' && ident[4] == ELFCLASS_SUPPORTED &&
           ident[5] == ELFDATA2LSB && ident[6] == EV_CURRENT &&
           _header->e_shstrndx != SHN_UNDEF;
  }

  ElfSection *section(int index) {
    if (index >= _header->e_shnum) {
      // invalid section index
      return NULL;
    }
    return (ElfSection *)(_sections + index * _header->e_shentsize);
  }

  const char *at(ElfSection *section) {
    return (const char *)_header + section->sh_offset;
  }

  const char *at(ElfProgramHeader *pheader) {
    return _header->e_type == ET_EXEC ? (const char *)pheader->p_vaddr
                                      : _vaddr_diff + pheader->p_vaddr;
  }

  char *dyn_ptr(ElfDyn *dyn) {
    // GNU dynamic linker relocates pointers in the dynamic section, while musl
    // doesn't. Also, [vdso] is not relocated, and its vaddr may differ from the
    // load address.
    if (_relocate_dyn || (char *)dyn->d_un.d_ptr < _base) {
      return (char *)_vaddr_diff + dyn->d_un.d_ptr;
    } else {
      return (char *)dyn->d_un.d_ptr;
    }
  }

  ElfSection *findSection(uint32_t type, const char *name);
  ElfProgramHeader *findProgramHeader(uint32_t type);

  void calcVirtualLoadAddress();
  void parseDynamicSection();
  void parseDwarfInfo();
  uint32_t getSymbolCount(uint32_t *gnu_hash);
  void loadSymbols(bool use_debug);
  bool loadSymbolsUsingBuildId();
  bool loadSymbolsUsingDebugLink();
  void loadSymbolTable(const char *symbols, size_t total_size, size_t ent_size,
                       const char *strings);
  void addRelocationSymbols(ElfSection *reltab, const char *plt);

  void addSymbol(const void *start, int length, const char *name, bool update_bounds = false);

public:
  static void parseProgramHeaders(CodeCache *cc, const char *base,
                                  const char *end, bool relocate_dyn);
  static bool parseFile(CodeCache *cc, const char *base, const char *file_name,
                        bool use_debug);
};

#endif //__linux__