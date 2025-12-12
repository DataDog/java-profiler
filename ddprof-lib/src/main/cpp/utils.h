#ifndef _UTILS_H
#define _UTILS_H

#include <cassert>
#include <cstdint>
#include <cstddef>

inline bool is_power_of_2(size_t size) {
    return size > 0 && (size & (size - 1)) == 0;
}

template <typename T>
inline bool is_aligned(const T* ptr, size_t alignment) noexcept {
    assert(is_power_of_2(alignment));
    // Convert the pointer to an integer type
    auto iptr = reinterpret_cast<uintptr_t>(ptr);

    // Check if the integer value is a multiple of the alignment
    return ((iptr & (~(alignment - 1))) == 0);
}

inline size_t align_down(size_t size, size_t alignment) noexcept {
    assert(is_power_of_2(alignment));
    return size & (~(alignment - 1));
}

inline size_t align_up(size_t size, size_t alignment) noexcept {
    assert(is_power_of_2(alignment));
    return align_down(size + alignment - 1, alignment);
}




#endif // _UTILS_H