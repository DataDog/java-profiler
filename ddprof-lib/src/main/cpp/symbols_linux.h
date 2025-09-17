#ifndef _SYMBOLS_LINUX_H
#define _SYMBOLS_LINUX_H

#include "symbols.h"

// Forward declaration for ElfParser functionality from cpp-external/symbols_linux.cpp
// The actual implementation will be available through the patched upstream file
class ElfParser {
public:
    static bool parseFile(CodeCache* cc, const char* base, const char* file_name, bool use_debug);
};

#endif // _SYMBOLS_LINUX_H
