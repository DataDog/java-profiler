/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "signalCookie.h"

namespace SignalCookie {
    namespace detail {
        // Place tags in a named section on Linux to prevent LTO from merging
        // or reordering them across TUs (their addresses must be unique per DSO).
#ifdef __linux__
        [[gnu::section(".data.signal_cookie")]] char cpu_tag;
        [[gnu::section(".data.signal_cookie")]] char wallclock_tag;
#else
        char cpu_tag;
        char wallclock_tag;
#endif
    }
    void* cpu()       { return &detail::cpu_tag; }
    void* wallclock() { return &detail::wallclock_tag; }
}
