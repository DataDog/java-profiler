// Replaceable global operator new/delete for alloc_ledger_probe.
//
// WHY THIS FILE EXISTS. The probe's purpose is to attribute live bytes to the
// code that asked for them. libstdc++'s operator new reaches malloc through
// its own PLT, so the return address observed inside a malloc interposer lies
// inside libstdc++.so.6 -- not inside libjavaProfiler.so. The profiler's
// allocation surface is almost entirely `new`, STL containers, and
// CountingAllocator<T, Category> (which wraps ::operator new), so without
// these definitions every byte would be attributed to libstdc++ and the site
// list would be worthless.
//
// Defining the replaceable global operators in a preloaded object makes them
// win for the whole process. Each forwards to probe_*_impl with its own
// return address, and those call real_malloc/real_free directly rather than
// the interposed malloc/free -- so libstdc++'s operator new is never entered
// and an allocation can never be recorded twice.
//
// Built together with alloc_ledger_probe.c into one .so; see
// run_ledger_capture.sh.

#include <cstddef>
#include <new>

extern "C" {
void *probe_new_impl(size_t n, void *caller);
void *probe_new_aligned_impl(size_t n, size_t align, void *caller);
void probe_delete_impl(void *p);
}

#define RA() __builtin_return_address(0)

// Throwing forms must raise std::bad_alloc; the nothrow forms must not.
static inline void *checked(void *p) {
  if (p == nullptr) {
    throw std::bad_alloc();
  }
  return p;
}

void *operator new(std::size_t n) { return checked(probe_new_impl(n, RA())); }
void *operator new[](std::size_t n) { return checked(probe_new_impl(n, RA())); }

void *operator new(std::size_t n, const std::nothrow_t &) noexcept {
  return probe_new_impl(n, RA());
}
void *operator new[](std::size_t n, const std::nothrow_t &) noexcept {
  return probe_new_impl(n, RA());
}

void *operator new(std::size_t n, std::align_val_t a) {
  return checked(probe_new_aligned_impl(n, static_cast<size_t>(a), RA()));
}
void *operator new[](std::size_t n, std::align_val_t a) {
  return checked(probe_new_aligned_impl(n, static_cast<size_t>(a), RA()));
}
void *operator new(std::size_t n, std::align_val_t a,
                   const std::nothrow_t &) noexcept {
  return probe_new_aligned_impl(n, static_cast<size_t>(a), RA());
}
void *operator new[](std::size_t n, std::align_val_t a,
                     const std::nothrow_t &) noexcept {
  return probe_new_aligned_impl(n, static_cast<size_t>(a), RA());
}

void operator delete(void *p) noexcept { probe_delete_impl(p); }
void operator delete[](void *p) noexcept { probe_delete_impl(p); }
void operator delete(void *p, std::size_t) noexcept { probe_delete_impl(p); }
void operator delete[](void *p, std::size_t) noexcept { probe_delete_impl(p); }
void operator delete(void *p, const std::nothrow_t &) noexcept {
  probe_delete_impl(p);
}
void operator delete[](void *p, const std::nothrow_t &) noexcept {
  probe_delete_impl(p);
}
void operator delete(void *p, std::align_val_t) noexcept {
  probe_delete_impl(p);
}
void operator delete[](void *p, std::align_val_t) noexcept {
  probe_delete_impl(p);
}
void operator delete(void *p, std::size_t, std::align_val_t) noexcept {
  probe_delete_impl(p);
}
void operator delete[](void *p, std::size_t, std::align_val_t) noexcept {
  probe_delete_impl(p);
}
void operator delete(void *p, std::align_val_t,
                     const std::nothrow_t &) noexcept {
  probe_delete_impl(p);
}
void operator delete[](void *p, std::align_val_t,
                       const std::nothrow_t &) noexcept {
  probe_delete_impl(p);
}
