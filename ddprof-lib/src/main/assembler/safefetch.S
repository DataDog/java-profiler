#ifdef __APPLE__
  # macOS prefixes symbols with _
  #define SYMBOL(s) _ ## s

  #define DECLARE_FUNC(func) \
    .globl SYMBOL(func) %% \
    .private_extern SYMBOL(func) %% \
    SYMBOL(func)
#else
  #define SYMBOL(s) s

  #define DECLARE_FUNC(func) \
    .globl func ; \
    .hidden func ; \
    .type func, %function ; \
    func
#endif // __APPLE__

#if defined(__x86_64__)
    .text

    # Support for int SafeFetch32(int* address, int defaultval);
    #
    #  %rdi : address
    #  %esi : defaultval
DECLARE_FUNC(SafeFetch32_impl):
DECLARE_FUNC(_SafeFetch32_fault):
    movl (%rdi), %eax       # load target value, may fault
    ret
DECLARE_FUNC(_SafeFetch32_continuation):
    movl %esi, %eax         # return default
    ret

#elif defined(__aarch64__)
#ifdef __APPLE__
    # Support for int SafeFetch32(int* address, int defaultval);
    #
    #  x0 : address
    #  w1 : defaultval

    # needed to align function start to 4 byte
    .align  6
DECLARE_FUNC(SafeFetch32_impl):
DECLARE_FUNC(_SafeFetch32_fault):
    ldr      w0, [x0]
    ret
DECLARE_FUNC(_SafeFetch32_continuation):
    mov      x0, x1
    ret
#else
    # Support for int SafeFetch32(int* address, int defaultval);
    #
    #  x0 : address
    #  x1 : defaultval
DECLARE_FUNC(SafeFetch32_impl):
DECLARE_FUNC(_SafeFetch32_fault):
    ldr      w0, [x0]
    ret
DECLARE_FUNC(_SafeFetch32_continuation):
    mov      x0, x1
    ret
#endif // __APPLE__

#endif
