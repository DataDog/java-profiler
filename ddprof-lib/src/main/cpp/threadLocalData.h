#ifndef THREADLOCALDATA_H
#define THREADLOCALDATA_H

class ThreadLocalData {
protected:
  bool _unwinding_Java;

public:
  ThreadLocalData() : _unwinding_Java(false) {}
  virtual bool is_unwinding_Java() final { return _unwinding_Java; }

  virtual void set_unwinding_Java(bool unwinding_Java) final {
    _unwinding_Java = unwinding_Java;
  }
};

#endif // THREADLOCALDATA_H
