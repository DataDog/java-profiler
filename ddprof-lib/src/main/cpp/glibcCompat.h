/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _GLIBCCOMPAT_H
#define _GLIBCCOMPAT_H

// Pins glibc functions to the oldest symbol version the shipped library
// supports, so the glibc of whatever image builds it does not decide the oldest
// host it can load on.
//
// When glibc changes a function's implementation it keeps the previous one under
// its old symbol version and makes the new one the default, so a build picks up
// the newest version available in its own libc and the artifact then requires
// that version at load time. .symver selects the interface explicitly instead.
// It chooses which of the versions already in the host's libc is called -- it
// does not bundle an implementation, so a host running a newer glibc still
// executes that glibc's code for the pinned symbol.
//
// expf is the only one needed today: glibc 2.27 added a faster implementation
// under GLIBC_2.27 and made it the default, so building on 2.28 requires
// expf@GLIBC_2.27 from source that has not changed. The GLIBC_2.17 interface is
// still exported and still maintained.
//
// Guarded to glibc: musl has no symbol versioning at all, and a .symver naming
// a GLIBC_* version fails to link there. The directive is a no-op when building
// on a glibc whose default already is the pinned version.
//
// This file exists only to hold the floor down. When the oldest supported host
// moves past these versions, delete it, drop its include from poissonSampler.h,
// and raise SHIPPED_GLIBC_FLOOR in .gitlab/config.env -- the ABI floor check in
// the build job reports what the artifact requires once the pins are gone.
#if defined(__linux__)
// __GLIBC__ is defined by features.h, which arrives with the first libc header
// -- so it must be pulled in explicitly here. Testing __GLIBC__ without it
// leaves the directive silently skipped, which looks identical to a working pin
// until the ABI floor check reports the version it was supposed to hold down.
// musl ships features.h too and defines no __GLIBC__, which is the intent.
#include <features.h>
#endif

#if defined(__linux__) && defined(__GLIBC__)
__asm__(".symver expf,expf@GLIBC_2.17");
#endif

#endif // _GLIBCCOMPAT_H
