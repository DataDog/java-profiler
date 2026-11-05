#ifndef _DEBUGSUPPORT_H
#define _DEBUGSUPPORT_H

typedef void (*SetSigHandlerTidRef)(int tid);

class Shims {
private:
  static Shims _instance;
  // Written once in the constructor during single-threaded static init; read
  // cross-thread via __atomic_load_n(..., __ATOMIC_ACQUIRE) in setSighandlerTid.
  SetSigHandlerTidRef _tid_setter_ref;
  Shims();

public:
  void setSighandlerTid(int tid);
  // Returns the singleton by reference: setSighandlerTid is called from the
  // sampling handlers' SighandlerTidScope, and a by-value return would copy
  // the object on every call.
  inline static Shims& instance() { return _instance; }
};

#endif //_DEBUGSUPPORT_H