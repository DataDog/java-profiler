#include <dlfcn.h>
#include <cstddef>

#include "debugSupport.h"
#include "debug.h"

Shims Shims::_instance;

Shims::Shims() : _tid_setter_ref(NULL) {
    #ifdef DEBUG
    if (_tid_setter_ref == NULL) {
        void* sym_handle = dlsym(RTLD_DEFAULT, "set_sighandler_tid");
        __atomic_compare_exchange_n(&_tid_setter_ref, (SetSigHandlerTidRef *)(&sym_handle), NULL, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
    }
    #endif
}

void Shims::setSighandlerTid(int tid) {
    #ifdef DEBUG
    SetSigHandlerTidRef ref = __atomic_load_n(&_tid_setter_ref, __ATOMIC_ACQUIRE);
    if (ref != NULL) {
        ref(tid);
    }
    #endif
}