#ifndef THREADLOCALDATA_H
#define THREADLOCALDATA_H

#include "threadState.h"

class ThreadLocalData {
protected:
  bool _unwinding_Java;
  ThreadState _state;

public:
  ThreadLocalData() : _unwinding_Java(false), _state(ThreadState::UNKNOWN) {}
  virtual bool is_unwinding_Java() final { return _unwinding_Java; }

  virtual void set_unwinding_Java(bool unwinding_Java) final {
    _unwinding_Java = unwinding_Java;
  }

  virtual void set_thread_state(ThreadState state) final {
      _state = state;
  }

  virtual ThreadState get_thread_state() final {
      return _state;
  }
};

#endif // THREADLOCALDATA_H
