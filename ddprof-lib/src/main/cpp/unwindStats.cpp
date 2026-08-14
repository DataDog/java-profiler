#include "unwindStats.h"

#ifdef DEBUG

// initialize static members
SpinLock UnwindStats::_lock;
UnwindFailures UnwindStats::_unwind_failures;

#endif
