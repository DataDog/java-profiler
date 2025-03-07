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
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <link.h>
#include <linux/limits.h>
#include <set>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

// make sure lseek will use 64 bits offset
#define _FILE_OFFSET_BITS 64
#include <unistd.h>

ElfSection *ElfParser::findSection(uint32_t type, const char *name) {
  if (_header == nullptr) {
    TEST_LOG("Invalid ELF header");
    return nullptr;
  }
  if (_header->e_shoff + (_header->e_shnum * sizeof(Elf64_Shdr)) > _length) {
    TEST_LOG("Section header table exceeds ELF size: e_shoff=%lx, e_shnum=%u",
             _header->e_shoff, _header->e_shnum);
    return nullptr;
  }
  int idx = _header->e_shstrndx;
  ElfSection* e_section = section(idx);
  if (e_section) {
    if (e_section->sh_offset >= _length) {
      TEST_LOG("Invalid section offset: %d (%d)", e_section->sh_offset, _length);
      return nullptr;
    }
    if (e_section->sh_offset + e_section->sh_size > _length) {
      TEST_LOG("Section size extends beyond ELF bounds: offset=%lx, size=%lx, file size=%lx",
               e_section->sh_offset, e_section->sh_size, _length);
      return nullptr;
    }
    if (e_section->sh_offset < _header->e_ehsize) {
      TEST_LOG("Invalid sh_offset: %lx (overlaps ELF header, e_ehsize=%x)", e_section->sh_offset, _header->e_ehsize);
      return nullptr;
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
  } else {
    TEST_LOG("Section stringtable not found");
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
    TEST_LOG("Invalid ELF header for %s", cc->name());
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
  if (!DWARF_SUPPORTED)
    return;

  ElfProgramHeader *eh_frame_hdr = findProgramHeader(PT_GNU_EH_FRAME);
  bool dwarf_set = false;
  if (eh_frame_hdr != NULL) {
    if (eh_frame_hdr->p_vaddr != 0) {
      DwarfParser dwarf(_cc->name(), _base, at(eh_frame_hdr));
      if (dwarf.count() > 0 && strcmp(_cc->name(), "[vdso]") != 0) {
        _cc->setDwarfTable(dwarf.table(), dwarf.count());
        dwarf_set =true;
      }
    }
  }
  if (!dwarf_set) {
    TEST_LOG("No eh_frame_hdr for %s", _cc->name());
    FrameDesc *table = (FrameDesc *)malloc(sizeof(FrameDesc));
#if defined(__aarch64__)
    // default to clang frame layout - if we have gcc binary it will have the .comment section
    *table = FrameDesc::default_clang_frame;
    Elf64_Shdr* commentSection = findSection(SHT_PROGBITS, ".comment");
    if (commentSection) {
      if (commentSection->sh_size < 4) {  // "GCC" + NULL terminator needs at least 4 bytes
        TEST_LOG("Invalid .comment section size");
      } else {
        char* commentData = (char*)at(commentSection);
        if (strstr(commentData, "GCC") != 0) {
          *table = FrameDesc::default_frame;
        }
      }
    }
#else
    *table = FrameDesc::default_frame;
#endif
    TEST_LOG("Setting default frame for %s --> reg: %d, fp_off: %d", _cc->name(), table->cfa & 0xffff, table->cfa >> 16);
    _cc->setDwarfTable(table, 1);
  }
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

void ElfParser::loadSymbolTable(const char *symbols, size_t total_size,
                                size_t ent_size, const char *strings) {
  for (const char *symbols_end = symbols + total_size; symbols < symbols_end;
       symbols += ent_size) {
    ElfSymbol *sym = (ElfSymbol *)symbols;
    if (sym->st_name != 0 && sym->st_value != 0) {
      // sanity check the offsets not to exceed the file size
      if (_length == 0 || (sym->st_name < _length && sym->st_value < _length)) {
        // Skip special AArch64 mapping symbols: $x and $d
        if (sym->st_size != 0 || sym->st_info != 0 ||
            strings[sym->st_name] != '$') {
          _cc->add(_base + sym->st_value, (int)sym->st_size,
                   strings + sym->st_name);
        }
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

    _cc->add(plt, PLT_ENTRY_SIZE, name);
    plt += PLT_ENTRY_SIZE;
  }
}

Mutex Symbols::_parse_lock;
bool Symbols::_have_kernel_symbols = false;
static std::set<const void *> _parsed_libraries;
static std::set<u64> _parsed_inodes;

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

static int parseLibrariesCallback(struct dl_phdr_info *info, size_t size,
                                  void *data) {

  FILE *f = fopen("/proc/self/maps", "r");
  if (f == NULL) {
    return 1;
  }

  CodeCacheArray *array = (CodeCacheArray *)data;
  const char *image_base = NULL;
  u64 last_inode = 0;
  char *str = NULL;
  size_t str_size = 0;
  ssize_t len;

  while ((len = getline(&str, &str_size, f)) > 0) {
    str[len - 1] = 0;
    MemoryMapDesc map(str);
    if (!map.isReadable() || map.file() == NULL || map.file()[0] == 0) {
      continue;
    }
    if (strchr(map.file(), ':') != NULL) {
      // Skip pseudofiles like anon_inode:name, /memfd:name
      continue;
    }

    const char *map_start = map.addr();
    unsigned long map_offs = map.offs();

    if (map_offs == 0) {
      image_base = map_start;
      last_inode = u64(map.dev()) << 32 | map.inode();
    }

    bool existing = false;
    if (!map.isExecutable() || (existing = !_parsed_libraries.insert(map_start).second)) {
      // Not an executable segment or it has been already parsed
//      TEST_LOG("Skipping library: %s, executable: %s, existing: %s, start: %p, end: %p", map.file(), map.isExecutable() ? "true" : "false", existing ? "true" : "false", map_start, (void*)map.end());
      continue;
    }

    int count = array->count();
    if (count >= MAX_NATIVE_LIBS) {
      TEST_LOG("Too many libraries, skipping: %s", map.file());
      break;
    }

    const char *map_end = map.end();
    // Do not try to parse pseudofiles like anon_inode:name, /memfd:name
    if (strchr(map.file(), ':') == NULL) {
      CodeCache *cc = new CodeCache(map.file(), count, false, map_start, map_end);
      TEST_LOG("Procesing library: %s", map.file());
      u64 inode = u64(map.dev()) << 32 | map.inode();
      if (inode != 0) {
        // Do not parse the same executable twice, e.g. on Alpine Linux
        if (_parsed_inodes.insert(inode).second) {
          if (inode == last_inode) {
            // If last_inode is set, image_base is known to be valid and
            // readable
//            TEST_LOG("Parsing file: %s", map.file());
            ElfParser::parseFile(cc, image_base, map.file(), true);
            // Parse program headers after the file to ensure debug symbols are
            // parsed first
//            TEST_LOG("Parsing headers: %s, start: %p, end: %p", map.file(), map_start, map_end);
            ElfParser::parseProgramHeaders(cc, image_base, map_end, MUSL);
          } else if ((unsigned long)map_start > map_offs) {
            // Unlikely case when image_base has not been found.
            // Be careful: executable file is not always ELF, e.g. classes.jsa
//            TEST_LOG("Parsing file only: %s, start: %p, end: %p", map.file(), map_start, map_end);
            ElfParser::parseFile(cc, map_start - map_offs, map.file(), true);
          }
        }
      } else if (strcmp(map.file(), "[vdso]") == 0) {
//        TEST_LOG("Parsing headers: %s, start: %p, end: %p", map.file(), map_start, map_end);
        ElfParser::parseProgramHeaders(cc, map_start, map_end, true);
      } else {
        TEST_LOG("No header for: %s", map.file());
      }

      cc->sort();
      array->add(cc);
    }
  }

  free(str);
  fclose(f);
  return 1; // stop at first iteration
}

void Symbols::parseLibraries(CodeCacheArray *array, bool kernel_symbols) {
  MutexLocker ml(_parse_lock);

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

  // In glibc, dl_iterate_phdr() holds dl_load_write_lock, therefore preventing
  // concurrent loading and unloading of shared libraries.
  // Without it, we may access memory of a library that is being unloaded.
  dl_iterate_phdr(parseLibrariesCallback, array);
}

#endif // __linux__
