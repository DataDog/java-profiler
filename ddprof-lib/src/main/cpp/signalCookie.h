/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SIGNAL_COOKIE_H
#define SIGNAL_COOKIE_H

// Sentinels carried in siginfo_t::si_value.sival_ptr by profiler-originated
// signals (timer_create for CPU engines, rt_tgsigqueueinfo for wallclock).
// Handlers use these to distinguish signals raised by this profiler from
// signals of the same number raised by other sources in the process (e.g.
// Go's setitimer(ITIMER_PROF), foreign tgkill, or kill/raise).
//
// CTimer and ITimer are mutually exclusive CPU engines — a profiler lifetime
// uses at most one of them — so they share SignalCookie::cpu(). (ITimer
// carries no payload, so it is not actually gated; the cookie is reserved.)
//
// Cookies are addresses of static tag variables, not hand-rolled magic
// numbers: tag addresses are unique per shared-library image, cannot be
// forged by an unrelated in-process sender without reading our symbols, and
// never collide with legitimate user-space pointers in third-party code.
namespace SignalCookie {
    namespace detail {
        inline char cpu_tag;
        inline char wallclock_tag;
    }
    inline void* cpu()       { return &detail::cpu_tag; }
    inline void* wallclock() { return &detail::wallclock_tag; }
}

#endif // SIGNAL_COOKIE_H
