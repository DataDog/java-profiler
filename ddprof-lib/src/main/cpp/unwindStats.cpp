#include "unwindStats.h"

// initialize static members
SpinLock UnwindStats::_lock;
UnwindFailures UnwindStats::_unwind_failures;
