#include <dlfcn.h>

#include "debug.h"
#include "debugSupport.h"

Shims Shims::_instance;

Shims::Shims() : _tid_setter_ref(nullptr) {
#ifdef DEBUG
  // Library init, long before any sampling thread: dlsym is illegal in
  // signal context, so the lookup must happen here. Unresolved (shim not
  // preloaded) leaves the no-op nullptr; RELEASE pairs the ACQUIRE load in
  // setSighandlerTid.
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
