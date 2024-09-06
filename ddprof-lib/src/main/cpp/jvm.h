#ifndef _JVM_H
#define _JVM_H

typedef bool (*is_readable_pointer_fn)(void *);

class JVM {
private:
  static bool _is_readable_pointer_resolved;
  static is_readable_pointer_fn _is_readable_pointer;

public:
  static bool is_readable_pointer(void *ptr);
};
#endif // _JVM_H