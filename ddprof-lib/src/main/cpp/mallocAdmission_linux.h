/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Linux-only declarations for the admission-time ELF marker lookup. Include
// only from _linux translation units; there is no non-Linux counterpart.
#ifdef __linux__

#ifndef _MALLOC_ADMISSION_LINUX_H
#define _MALLOC_ADMISSION_LINUX_H

#include <stdint.h>

#include "mallocAdmission.h"

// Bound on entries visited by one GNU or SysV hash-chain walk. The tested
// released ddprof images have a longest GNU chain of 2; any image exceeding this
// work cap is conservatively INDETERMINATE (CHAIN_LIMIT), even if valid.
constexpr int MAX_HASH_CHAIN_STEPS = 65536;

namespace ElfMarkerLookup {

// Classifies one loaded image: does it export the two ddprof marker names as
// ordinary exported functions? Takes the same triple as
// Symbols::imageFingerprint(): program headers, their count and the load
// bias. Test-facing wrapper around the internal-linkage classifier the
// dl_iterate_phdr callback uses; reads only, executes nothing in the image.
AdmissionVerdict classifyImage(const void* phdrs, int phnum, uintptr_t load_bias);

} // namespace ElfMarkerLookup

#endif // _MALLOC_ADMISSION_LINUX_H

#endif // __linux__
