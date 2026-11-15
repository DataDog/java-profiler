---
id: musl-glibc-unwind-evidence
title: Primary-source verification: statements after the t07 while(true) loop are unreachable
kind: finding
tags: []
applies_to: []
source: implement-github-issue-sphinx/musl-glibc-unwind-evidence
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# Primary-source verification: statements after the t07 while(true) loop are unreachable

## musl (git.musl-libc.org, src/thread/)
- `pthread_testcancel.c`: `__pthread_testcancel` → `__testcancel()` →
  `pthread_cancel.c::__testcancel()`: `if (self->cancel && !self->canceldisable) __cancel();`
- `pthread_cancel.c::__cancel()`: `if (canceldisable == ENABLE || cancelasync) pthread_exit(PTHREAD_CANCELED);`
  → `_Noreturn __pthread_exit` (pthread_create.c:54): runs the `self->cancelbuf` chain
  (cleanup handlers from pthread_cleanup_push) then exits the thread.
  ⇒ control NEVER returns from pthread_testcancel when cancel is pending; loop has no other exit.
- `include/pthread.h:215-216`: `#define pthread_cleanup_push(f, x) do { struct __ptcb __cb; ...`
  / `#define pthread_cleanup_pop(r) ... } while(0)` ⇒ pop is LEXICALLY REQUIRED (macro pairing),
  cannot be removed.
- musl `__pthread_exit` (pthread_create.c:63-68): walks `self->cancelbuf` calling `f(x)` —
  the cleanup callback DOES run on musl cancellation (test assertions rely on this).

## glibc (bminor/glibc master, nptl/)
- `nptl/unwind.c:unwind_stop()`: `do_longjump` set when `_UA_END_OF_STACK` or
  `_JMPBUF_CFA_UNWINDS_ADJ(buf->cancel_jmp_buf[0].jmp_buf, ...)` → longjmps back to the
  cancel_jmp_buf registered by `__pthread_register_cancel`.
- `nptl/pthread_cancel.c:161-165`: `PTHREAD_STATIC_FN_REQUIRE (___pthread_unwind_next)` —
  unwinder linked in from `__do_cancel`.
  ⇒ cancellation at pthread_testcancel longjmps into the __sigsetjmp handler block; loop
  never exits normally; statements after the loop are unreachable.

## Conclusion
Both musl `ProfiledThread::release(); return nullptr;` (after loop+pop, lines 356-357 main)
and the historical glibc `__pthread_unregister_cancel/sigaction/release` are provably dead.
The glibc side is already fixed on main; only the musl side remains.
