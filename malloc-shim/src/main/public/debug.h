#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Exported by the malloc-shim (libdebug.so, LD_PRELOAD) and resolved by
 * Shims (debugSupport.cpp) via dlsym(RTLD_DEFAULT, "set_sighandler_tid").
 * C linkage is mandatory: a C++-mangled symbol can never match the plain
 * name passed to dlsym, and the same applies to malloc interposition.
 */
void set_sighandler_tid(int tid);

#ifdef __cplusplus
}
#endif

#endif // _DEBUG_H
