// Copyright 2026, Datadog, Inc.

#ifdef __linux__

#include "threadExitRegistry.h"
#include <sys/syscall.h>
#include <unistd.h>

uint64_t ThreadExitRegistry::currentId() {
    return syscall(SYS_gettid);
}

#endif // __linux__
