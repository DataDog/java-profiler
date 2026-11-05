#include <dlfcn.h>

#include "debug.h"
#include "debugSupport.h"

Shims Shims::_instance;

Shims::Shims() : _tid_setter_ref(nullptr) {
#ifdef DEBUG
  // Runs during single-threaded static initialization, so the resolved
  // pointer can be stored unconditionally. The lookup must happen here:
  // setSighandlerTid is called from signal context, where dlsym is illegal
  // (it can lock and malloc). The pointer stays nullptr when libdebug.so is
  // not preloaded, making setSighandlerTid a silent no-op. The RELEASE store
  // pairs with the ACQUIRE load in setSighandlerTid so the resolved pointer
  // is visible to sampling threads.
  __atomic_store_n(&_tid_setter_ref,
                   reinterpret_cast<SetSigHandlerTidRef>(dlsym(RTLD_DEFAULT, "set_sighandler_tid")),
                   __ATOMIC_RELEASE);
#endif
}

void Shims::setSighandlerTid(int tid) {
#ifdef DEBUG
  SetSigHandlerTidRef ref = __atomic_load_n(&_tid_setter_ref, __ATOMIC_ACQUIRE);
  if (ref != nullptr) {
    ref(tid);
  }
#endif
}
