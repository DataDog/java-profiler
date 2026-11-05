#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Exported by libdebug.so (LD_PRELOAD); resolved by Shims via
 * dlsym(RTLD_DEFAULT, "set_sighandler_tid"). C linkage is mandatory: a
 * C++-mangled symbol can never match the plain dlsym name.
 */
void set_sighandler_tid(int tid);

#ifdef __cplusplus
}
#endif

#endif // _DEBUG_H
