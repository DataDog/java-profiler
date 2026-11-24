/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Non-Linux owner classification for the native-memory admission check: the
// ELF/loader-based inspection is Linux-only, so elsewhere no image is
// recognized and every target is NOT_RECOGNIZED. The shared admission logic
// in mallocAdmission.cpp still runs (derivation, own-hook rules, combination),
// only image ownership recognition is absent on this platform.
#ifndef __linux__

#include "mallocAdmission.h"

int MallocAdmission::classifyOwners(const void* const* targets, int count, AdmissionVerdict* verdicts) {
    for (int i = 0; i < count; i++) {
        verdicts[i].outcome = NOT_RECOGNIZED;
        verdicts[i].reason = NONE;
    }
    return 0;
}

#endif // !__linux__
