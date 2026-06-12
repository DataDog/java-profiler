# Replace __tsan_reset_range with __tsan_write_range

## Problem
`__tsan_reset_range` is not declared in `<sanitizer/tsan_interface.h>` and does not
exist in the LLVM/compiler-rt source. Using it causes GCC TSan builds to fail with
"was not declared in this scope".

## Solution
Replace `__tsan_reset_range(chunk, _chunk_size)` with `__tsan_write_range(chunk, _chunk_size)`.
Add an explicit `extern "C"` forward declaration for `__tsan_write_range` inside the
`#ifdef __SANITIZE_THREAD__` block, since the function exists in the runtime but is absent
from the public header.

## Files to change
- `ddprof-lib/src/main/cpp/linearAllocator.cpp`
  - Lines 39–41: add `extern "C"` declaration for `__tsan_write_range`
  - Line 233: replace `__tsan_reset_range` with `__tsan_write_range`

## Acceptance criteria
1. The `__tsan_reset_range` identifier no longer appears in the file.
2. A forward declaration `extern "C" void __tsan_write_range(void*, size_t);` exists
   inside `#ifdef __SANITIZE_THREAD__`.
3. `__tsan_write_range(chunk, _chunk_size)` is called at line ~233.
