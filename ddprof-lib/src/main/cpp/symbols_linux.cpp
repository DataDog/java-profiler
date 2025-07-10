/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include "symbols_linux.h"

#include "common.h"
#include "dwarf.h"
#include "log.h"
#include "safeAccess.h"
#include "symbols.h"
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <link.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>

// make sure lseek will use 64 bits offset
#define _FILE_OFFSET_BITS 64
#include <unistd.h>

uintptr_t ElfParser::_root_symbols[LAST_ROOT_SYMBOL_KIND] = {0};

ElfSection *ElfParser::findSection(uint32_t type, const char *name) {
  if (_header == NULL) {
    return NULL;
  }
  if (_header->e_shoff + (_header->e_shnum * sizeof(Elf64_Shdr)) > _length) {
    return NULL;
  }
  int idx = _header->e_shstrndx;
  ElfSection* e_section = section(idx);
  if (e_section) {
    if (e_section->sh_offset >= _length) {
        return NULL;
    }
    if (e_section->sh_offset + e_section->sh_size > _length) {
      return NULL;
    }
    if (e_section->sh_offset < _header->e_ehsize) {
      return NULL;
    }
    const char *strtab = at(e_section);
    if (strtab) {
      for (int i = 0; i < _header->e_shnum; i++) {
        ElfSection *section = this->section(i);
        if (section->sh_type == type && section->sh_name != 0) {
          if (strcmp(strtab + section->sh_name, name) == 0) {
            return section;
          }
        }
      }
    }
  }
  return NULL;
}

ElfProgramHeader *ElfParser::findProgramHeader(uint32_t type) {
  const char *pheaders = (const char *)_header + _header->e_phoff;

  for (int i = 0; i < _header->e_phnum; i++) {
    const char *unvalidated_pheader = pheaders + i * _header->e_phentsize;
    // check we can load the pointer
    void *checked = SafeAccess::load((void **)unvalidated_pheader);
    if (checked == NULL) {
      return NULL;
    } else {
      ElfProgramHeader *pheader = (ElfProgramHeader *)unvalidated_pheader;
      if (pheader->p_type == type) {
        return pheader;
      }
    }
  }

  return NULL;
}

bool ElfParser::parseFile(CodeCache *cc, const char *base,
                          const char *file_name, bool use_debug) {
  int fd = open(file_name, O_RDONLY);
  if (fd == -1) {
    return false;
  }

  size_t length = (size_t)lseek(fd, 0, SEEK_END);
  void *addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);

  if (addr == MAP_FAILED) {
    Log::warn("Could not parse symbols from %s: %s", file_name,
              strerror(errno));
  } else {
    ElfParser elf(cc, base != nullptr ? base : (const char *)addr, addr,
                  file_name, length, false);
    if (elf.validHeader()) {
      elf.loadSymbols(use_debug);
    }
    munmap(addr, length);
  }
  return true;
}

void ElfParser::parseProgramHeaders(CodeCache *cc, const char *base,
                                    const char *end, bool relocate_dyn) {
  ElfParser elf(cc, base, base, NULL, (size_t)(end - base), relocate_dyn);
  if (elf.validHeader() && base + elf._header->e_phoff < end) {
    cc->setTextBase(base);
    elf.calcVirtualLoadAddress();
    elf.parseDynamicSection();
    elf.parseDwarfInfo();
  } else {
    Log::warn("Invalid ELF header for %s: %p-%p", cc->name(), base, end);
  }
}

void ElfParser::calcVirtualLoadAddress() {
  // Find a difference between the virtual load address (often zero) and the
  // actual DSO base
  const char *pheaders = (const char *)_header + _header->e_phoff;
  for (int i = 0; i < _header->e_phnum; i++) {
    ElfProgramHeader *pheader =
        (ElfProgramHeader *)(pheaders + i * _header->e_phentsize);
    if (pheader->p_type == PT_LOAD) {
      _vaddr_diff = _base - pheader->p_vaddr;
      return;
    }
  }
  _vaddr_diff = _base;
}

void ElfParser::parseDynamicSection() {
  ElfProgramHeader *dynamic = findProgramHeader(PT_DYNAMIC);
  if (dynamic != NULL) {
    const char *symtab = NULL;
    const char *strtab = NULL;
    char *jmprel = NULL;
    char *rel = NULL;
    size_t pltrelsz = 0;
    size_t relsz = 0;
    size_t relent = 0;
    size_t relcount = 0;
    size_t syment = 0;
    uint32_t nsyms = 0;

    const char *dyn_start = at(dynamic);
    const char *dyn_end = dyn_start + dynamic->p_memsz;
    for (ElfDyn *dyn = (ElfDyn *)dyn_start; dyn < (ElfDyn *)dyn_end; dyn++) {
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
        nsyms = ((uint32_t *)dyn_ptr(dyn))[1];
        break;
      case DT_GNU_HASH:
        if (nsyms == 0) {
          nsyms = getSymbolCount((uint32_t *)dyn_ptr(dyn));
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

    if (symtab == NULL || strtab == NULL || syment == 0 || nsyms == 0 ||
        relent == 0) {
      return;
    }

    if (!_cc->hasDebugSymbols()) {
      loadSymbolTable(symtab, syment * nsyms, syment, strtab);
    }

    if (jmprel != NULL && pltrelsz != 0) {
      // Parse .rela.plt table
      for (size_t offs = 0; offs < pltrelsz; offs += relent) {
        ElfRelocation *r = (ElfRelocation *)(jmprel + offs);

          ElfSymbol *sym = (ElfSymbol *)(symtab + ELF_R_SYM(r->r_info) * syment);
          if (sym->st_name != 0) {
            _cc->addImport((void **)(_base + r->r_offset), strtab + sym->st_name);

        }
      }
    }

    if (rel != NULL && relsz != 0) {
      // Relocation entries for imports can be found in .rela.dyn, for example
      // if a shared library is built without PLT (-fno-plt). However, if both
      // entries exist, addImport saves them both.
      for (size_t offs = relcount * relent; offs < relsz; offs += relent) {
        ElfRelocation *r = (ElfRelocation *)(rel + offs);
                if (ELF_R_TYPE(r->r_info) == R_GLOB_DAT || ELF_R_TYPE(r->r_info) == R_ABS64) {
          ElfSymbol *sym =
              (ElfSymbol *)(symtab + ELF_R_SYM(r->r_info) * syment);
          if (sym->st_name != 0) {
            _cc->addImport((void **)(_base + r->r_offset),
                           strtab + sym->st_name);
          }
        }
      }}
    }
}

void ElfParser::parseDwarfInfo() {
  if (!DWARF_SUPPORTED) return;

  ElfProgramHeader* eh_frame_hdr = findProgramHeader(PT_GNU_EH_FRAME);
  if (eh_frame_hdr != NULL) {
    if (eh_frame_hdr->p_vaddr != 0) {
      // found valid eh_frame_hdr
      TEST_LOG("Found eh_frame_hdr for %s: %p", _cc->name(), at(eh_frame_hdr));
      DwarfParser dwarf(_cc->name(), _base, at(eh_frame_hdr));
      if (dwarf.count() > 0 && strcmp(_cc->name(), "[vdso]") != 0) {
        TEST_LOG("Setting dwarf table for %s: %p", _cc->name(), dwarf.table());
        _cc->setDwarfTable(dwarf.table(), dwarf.count());
        return;
      }
    }
  }
  // no valid eh_frame_hdr found; need to rely on the default linked frame descriptor
  FrameDesc *table = (FrameDesc *)malloc(sizeof(FrameDesc));
#if defined(__aarch64__)
  // default to clang frame layout - if we have gcc binary it will have the .comment section
  *table = FrameDesc::default_frame;
  Elf64_Shdr* commentSection = findSection(SHT_PROGBITS, ".comment");
  bool frame_layout_resolved = false;
  if (commentSection) {
    if (commentSection->sh_size >= 4) {  // "GCC" + NULL terminator needs at least 4 bytes
      char* commentData = (char*)at(commentSection);
      if (strstr(commentData, "GCC") != 0) {
        frame_layout_resolved = true;
        TEST_LOG(".comment section for %s :: %s, using gcc frame layout", _cc->name(), commentData);
      } else {
        TEST_LOG(".comment section for %s :: %s, using clang frame layout", _cc->name(), commentData);
      }
    }
  } else {
    TEST_LOG("No .comment section found for %s, will probe pre-amble", _cc->name());
  }
  if (!frame_layout_resolved) {
    for (int b = 0; b < _cc->count(); b++) {
      CodeBlob* blob = _cc->blob(b);
      if (blob) {
        instruction_t* ptr = (instruction_t*)blob->_start;
        instruction_t gcc_pattern = 0x910003fd;   // mov x29, sp
        instruction_t clang_pattern = 0xfd7b01a9; // stp x29, x30, [sp, #16]
        // first instruction may be noop so we are checking first 2 for the gcc pattern
        if (*(ptr + 1) == gcc_pattern || *(ptr + 2) == gcc_pattern) {
          *table = FrameDesc::default_frame;
          TEST_LOG("Found GCC pattern in code blob for %s, using gcc frame layout", _cc->name());
          frame_layout_resolved = true;
          break;
        } else if (*(ptr + 1) == clang_pattern || *(ptr + 2) == clang_pattern) {
          *table = FrameDesc::default_clang_frame;
          TEST_LOG("Found Clang pattern in code blob for %s, using clang frame layout", _cc->name());
          frame_layout_resolved = true;
          break;
        }
      }
    }
  }
  if (!frame_layout_resolved) {
    *table = FrameDesc::default_frame;
    TEST_LOG("No frame layout found for %s, using gcc frame layout", _cc->name());
  }
#else
  *table = FrameDesc::default_frame;
#endif
  _cc->setDwarfTable(table, 1);
}

uint32_t ElfParser::getSymbolCount(uint32_t *gnu_hash) {
  uint32_t nbuckets = gnu_hash[0];
  uint32_t *buckets = &gnu_hash[4] + gnu_hash[2] * (sizeof(size_t) / 4);

  uint32_t nsyms = 0;
  for (uint32_t i = 0; i < nbuckets; i++) {
    if (buckets[i] > nsyms)
      nsyms = buckets[i];
  }

  if (nsyms > 0) {
    uint32_t *chain = &buckets[nbuckets] - gnu_hash[1];
    while (!(chain[nsyms++] & 1))
      ;
  }
  return nsyms;
}

void ElfParser::loadSymbols(bool use_debug) {
  ElfSection *symtab = findSection(SHT_SYMTAB, ".symtab");
  if (symtab != NULL) {
    // Parse debug symbols from the original .so
    ElfSection *strtab = section(symtab->sh_link);
    loadSymbolTable(at(symtab), symtab->sh_size, symtab->sh_entsize,
                    at(strtab));
    _cc->setDebugSymbols(true);
  } else if (use_debug) {
    // Try to load symbols from an external debuginfo library
    loadSymbolsUsingBuildId() || loadSymbolsUsingDebugLink();
  }

  if (use_debug) {
    // Synthesize names for PLT stubs
    ElfSection *plt = findSection(SHT_PROGBITS, ".plt");
    if (plt != NULL) {
      _cc->setPlt(plt->sh_addr, plt->sh_size);
      ElfSection *reltab = findSection(SHT_RELA, ".rela.plt");
      if (reltab != NULL ||
          (reltab = findSection(SHT_REL, ".rel.plt")) != NULL) {
        addRelocationSymbols(reltab, _base + plt->sh_addr + PLT_HEADER_SIZE);
      }
    }
  }
}

void ElfParser::addSymbol(const void *start, int length, const char *name, bool update_bounds) {
  _cc->add(start, length, name, update_bounds);
  for (int i = 0; i < LAST_ROOT_SYMBOL_KIND; i++) {
    if (!strcmp(root_symbol_table[i].name, name)) {
      TEST_LOG("Adding root symbol %s: %p", name, start);
      _root_symbols[root_symbol_table[i].kind] = (uintptr_t)start;
      break;
    }
  }
}

// Load symbols from /usr/lib/debug/.build-id/ab/cdef1234.debug, where
// abcdef1234 is Build ID
bool ElfParser::loadSymbolsUsingBuildId() {
  ElfSection *section = findSection(SHT_NOTE, ".note.gnu.build-id");
  if (section == NULL || section->sh_size <= 16) {
    return false;
  }

  ElfNote *note = (ElfNote *)at(section);
  if (note->n_namesz != 4 || note->n_descsz < 2 || note->n_descsz > 64) {
    return false;
  }

  const char *build_id = (const char *)note + sizeof(*note) + 4;
  int build_id_len = note->n_descsz;

  char path[PATH_MAX];
  char *p = path + sprintf(path, "/usr/lib/debug/.build-id/%02hhx/",
                           (unsigned char)build_id[0]);
  for (int i = 1; i < build_id_len; i++) {
    p += sprintf(p, "%02hhx", (unsigned char)build_id[i]);
  }
  strcpy(p, ".debug");

  return parseFile(_cc, _base, path, false);
}

// Look for debuginfo file specified in .gnu_debuglink section
bool ElfParser::loadSymbolsUsingDebugLink() {
  ElfSection *section = findSection(SHT_PROGBITS, ".gnu_debuglink");
  if (section == NULL || section->sh_size <= 4) {
    return false;
  }

  const char *basename = strrchr(_file_name, '/');
  if (basename == NULL) {
    return false;
  }

  char *dirname = strndup(_file_name, basename - _file_name);
  if (dirname == NULL) {
    return false;
  }

  const char *debuglink = at(section);
  char path[PATH_MAX];
  bool result = false;

  // 1. /path/to/libjvm.so.debug
  if (strcmp(debuglink, basename + 1) != 0 &&
      snprintf(path, PATH_MAX, "%s/%s", dirname, debuglink) < PATH_MAX) {
    result = parseFile(_cc, _base, path, false);
  }

  // 2. /path/to/.debug/libjvm.so.debug
  if (!result &&
      snprintf(path, PATH_MAX, "%s/.debug/%s", dirname, debuglink) < PATH_MAX) {
    result = parseFile(_cc, _base, path, false);
  }

  // 3. /usr/lib/debug/path/to/libjvm.so.debug
  if (!result && snprintf(path, PATH_MAX, "/usr/lib/debug%s/%s", dirname,
                          debuglink) < PATH_MAX) {
    result = parseFile(_cc, _base, path, false);
  }

  free(dirname);
  return result;
}

void ElfParser::loadSymbolTable(const char *symbols, size_t total_size, size_t ent_size, const char *strings) {
  for (const char *symbols_end = symbols + total_size; symbols < symbols_end; symbols += ent_size) {
    ElfSymbol *sym = (ElfSymbol *)symbols;
    if (sym->st_name != 0 && sym->st_value != 0) {
      // Skip special AArch64 mapping symbols: $x and $d
      if (sym->st_size != 0 || sym->st_info != 0 ||
        strings[sym->st_name] != '$') {

        uintptr_t addr = (uintptr_t)_base + sym->st_value;
        if (addr < (uintptr_t)_base) {
          // detected wrap-around → skip
          continue;
        }

        addSymbol((void*)addr, (int)sym->st_size, strings + sym->st_name);
      }
    }
  }
}

void ElfParser::addRelocationSymbols(ElfSection *reltab, const char *plt) {
  ElfSection *symtab = section(reltab->sh_link);
  const char *symbols = at(symtab);

  ElfSection *strtab = section(symtab->sh_link);
  const char *strings = at(strtab);

  const char *relocations = at(reltab);
  const char *relocations_end = relocations + reltab->sh_size;
  for (; relocations < relocations_end; relocations += reltab->sh_entsize) {
    ElfRelocation *r = (ElfRelocation *)relocations;
    ElfSymbol *sym =
        (ElfSymbol *)(symbols + ELF_R_SYM(r->r_info) * symtab->sh_entsize);

    char name[256];
    if (sym->st_name == 0) {
      strcpy(name, "@plt");
    } else {
      const char *sym_name = strings + sym->st_name;
      snprintf(name, sizeof(name), "%s%cplt", sym_name,
               sym_name[0] == '_' && sym_name[1] == 'Z' ? '.' : '@');
      name[sizeof(name) - 1] = 0;
    }

    addSymbol(plt, PLT_ENTRY_SIZE, name);
    plt += PLT_ENTRY_SIZE;
  }
}

struct SharedLibrary {
    char* file;
    const char* map_start;
    const char* map_end;
    const char* image_base;
};

Mutex Symbols::_parse_lock;
bool Symbols::_have_kernel_symbols = false;
bool Symbols::_libs_limit_reported = false;
static std::unordered_set<u64> _parsed_inodes;

void Symbols::clearParsingCaches() {
  _parsed_libraries.clear();
  _parsed_inodes.clear();
}

void Symbols::parseKernelSymbols(CodeCache *cc) {
  int fd = open("/proc/kallsyms", O_RDONLY);

  if (fd == -1) {
    Log::warn("open(\"/proc/kallsyms\"): %s", strerror(errno));
    return;
  }

  FILE *f = fdopen(fd, "r");
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
      const char *addr = symbol.addr();
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

  FILE *f = fopen("/proc/self/maps", "r");
  if (f == NULL) {
    return;
  }

  const char *image_base = NULL;
  u64 last_inode = 0;
  char *str = NULL;
  size_t str_size = 0;
  ssize_t len;

  while (max_count > 0 && (len = getline(&str, &str_size, f)) > 0) {
    str[len - 1] = 0;
    MemoryMapDesc map(str);
    if (!map.isReadable() || map.file() == NULL || map.file()[0] == 0) {
      continue;
    }
    if (strchr(map.file(), ':') != NULL) {
      // Skip pseudofiles like anon_inode:name, /memfd:name
      continue;
    }

    u64 inode = u64(map.dev()) << 32 | map.inode();
    if (_parsed_inodes.find(inode) != _parsed_inodes.end()) {
       continue;  // shared object is already parsed
    }

    if (inode == 0 && strcmp(map.file(), "[vdso]") != 0) {
        continue;  // all shared libraries have inode, except vDSO
    }

    int count = array->count();
    if (count >= MAX_NATIVE_LIBS) {
      break;
    }

    const char* map_start = map.addr();
    const char *map_end = map.end();
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
            // The same library may have multiple executable segments mapped
            lib.map_end = map_end;
        }
    }

  free(str);
  fclose(f);
}

void Symbols::parseLibraries(CodeCacheArray *array, bool kernel_symbols) {
  MutexLocker ml(_parse_lock);

  if (array->count() >= MAX_NATIVE_LIBS) {
    return;
  }

  if (kernel_symbols && !haveKernelSymbols()) {
    CodeCache *cc = new CodeCache("[kernel]");
    parseKernelSymbols(cc);

    if (haveKernelSymbols()) {
      cc->sort();
      array->add(cc);
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
        CodeCache* cc = new CodeCache(lib.file, array->count(), false, lib.map_start, lib.map_end);

        // Strip " (deleted)" suffix so that removed library can be reopened
        size_t len = strlen(lib.file);
        if (len > 10 && strcmp(lib.file + len - 10, " (deleted)") == 0) {
            lib.file[len - 10] = 0;
        }

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

            dlerror();  // reset any error from previous dl function calls

            // Protect library from unloading while parsing in-memory ELF program headers.
            // Also, dlopen() ensures the library is fully loaded.
            // Main executable and ld-linux interpreter cannot be dlopen'ed, but dlerror() returns NULL for them.
            void* handle = dlopen(lib.file, RTLD_LAZY | RTLD_NOLOAD);
            if (handle != NULL || dlerror() == NULL) {
               if (handle != NULL) {
                    dlclose(handle);
                }
            }
        }

        free(lib.file);

        cc->sort();
        applyPatch(cc);
        array->add(cc);
    }

    if (array->count() >= MAX_NATIVE_LIBS && !_libs_limit_reported) {
        Log::warn("Number of parsed libraries reached the limit of %d", MAX_NATIVE_LIBS);
        _libs_limit_reported = true;
    }
}

bool Symbols::isRootSymbol(const void* address) {
  for (int i = 0; i < LAST_ROOT_SYMBOL_KIND; i++) {
    if (ElfParser::_root_symbols[i] == (uintptr_t)address) {
      return true;
    }
  }
  return false;
}

#endif // __linux__
