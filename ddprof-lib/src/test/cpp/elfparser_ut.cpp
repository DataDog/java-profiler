#ifdef __linux__

#include <gtest/gtest.h>

#include "codeCache.h"
#include "symbols_linux.h"

#include <unistd.h>
#include <limits.h> // For PATH_MAX

TEST(Elf, readSymTable) {
    char cwd[PATH_MAX - 64];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        exit(1);
    }
    char path[PATH_MAX];
    snprintf(path, sizeof(path) - 1, "%s/../build/test/resources/unresolved-functions/main", cwd);
    if (access(path, R_OK) != 0) {
        fprintf(stdout, "Missing test resource %s. Skipping the test\n", path);
        exit(0);
    }
    CodeCache cc("test");
    ElfParser::parseFile(&cc, nullptr, path, false);
    fprintf(stdout, "CodeCache size: %d\n", cc.count());
}

#endif //__linux__