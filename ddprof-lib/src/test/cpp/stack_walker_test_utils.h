#ifndef _STACK_WALKER_TEST_UTILS_H
#define _STACK_WALKER_TEST_UTILS_H

#include <cstdint>
#include <vector>
#include <random>
#include <ucontext.h>

// Include project headers - use full paths for clarity
#include "stackWalker.h"
#include "dwarf.h"
#include "arch_dd.h"
#include "vmEntry.h"

// Common utilities and definitions for StackWalker tests

// Use the StackContext from stackWalker.h
// We don't need to redefine it here

// Constants for testing
const int DEFAULT_MAX_DEPTH = 128;
const int MIN_STACK_SIZE = 1024;
const int MAX_STACK_SIZE = 32768;
const uintptr_t DEAD_ZONE_SIZE = 0x1000;

// Utility functions

// Create a random stack with valid memory layout
inline std::vector<uintptr_t> createRandomStack(std::mt19937& rng, size_t stack_size) {
    std::uniform_int_distribution<uintptr_t> rand_word(1, UINTPTR_MAX);
    
    std::vector<uintptr_t> stack(stack_size);
    for (size_t i = 0; i < stack.size(); i++) {
        stack[i] = rand_word(rng);
    }
    
    return stack;
}

// Create a simple chain of frames
inline void setupFrameChain(std::vector<uintptr_t>& stack, int num_frames) {
    if (stack.size() < static_cast<size_t>(num_frames * 3)) {
        return;  // Stack too small
    }
    
    const size_t frame_size = 3; // FP, PC, and a slot for data
    
    // Start from the bottom of the stack and create a chain
    uintptr_t base_addr = reinterpret_cast<uintptr_t>(&stack[0]);
    
    for (int i = 0; i < num_frames; i++) {
        size_t frame_offset = i * frame_size;
        
        // Link to the previous frame
        if (i > 0) {
            stack[frame_offset] = base_addr + (i - 1) * frame_size * sizeof(uintptr_t);
        } else {
            stack[frame_offset] = 0; // End of chain
        }
        
        // Add a recognizable PC value
        stack[frame_offset + 1] = 0xABCD0000 + i;
        
        // Add some data
        stack[frame_offset + 2] = 0xDEADBEEF;
    }
}

// Check if an address is properly aligned
inline bool isAligned(uintptr_t addr) {
    return (addr & (sizeof(uintptr_t) - 1)) == 0;
}

// Check if an address is in the dead zone (very low or very high)
inline bool isInDeadZone(uintptr_t addr) {
    return addr < DEAD_ZONE_SIZE || addr > (UINTPTR_MAX - DEAD_ZONE_SIZE);
}

// Generate a non-dead-zone address
inline uintptr_t generateSafeAddress(std::mt19937& rng) {
    std::uniform_int_distribution<uintptr_t> rand_addr(DEAD_ZONE_SIZE, UINTPTR_MAX - DEAD_ZONE_SIZE);
    uintptr_t addr = rand_addr(rng);
    // Ensure it's aligned
    return addr & ~(sizeof(uintptr_t) - 1);
}

// Platform-specific functions for register access

// Set SP register
inline void setStackPointer(ucontext_t& context, uintptr_t value) {
#if defined(__APPLE__) && defined(__x86_64__)
    context.uc_mcontext->__ss.__rsp = value;
#elif defined(__APPLE__) && defined(__aarch64__)
    context.uc_mcontext->__ss.__sp = value;
#elif defined(__linux__) && defined(__x86_64__)
    context.uc_mcontext.gregs[REG_RSP] = value;
#elif defined(__linux__) && defined(__aarch64__)
    context.uc_mcontext.sp = value;
#endif
}

// Set FP register
inline void setFramePointer(ucontext_t& context, uintptr_t value) {
#if defined(__APPLE__) && defined(__x86_64__)
    context.uc_mcontext->__ss.__rbp = value;
#elif defined(__APPLE__) && defined(__aarch64__)
    context.uc_mcontext->__ss.__fp = value;
#elif defined(__linux__) && defined(__x86_64__)
    context.uc_mcontext.gregs[REG_RBP] = value;
#elif defined(__linux__) && defined(__aarch64__)
    context.uc_mcontext.regs[29] = value;
#endif
}

// Set PC register
inline void setProgramCounter(ucontext_t& context, uintptr_t value) {
#if defined(__APPLE__) && defined(__x86_64__)
    context.uc_mcontext->__ss.__rip = value;
#elif defined(__APPLE__) && defined(__aarch64__)
    context.uc_mcontext->__ss.__pc = value;
#elif defined(__linux__) && defined(__x86_64__)
    context.uc_mcontext.gregs[REG_RIP] = value;
#elif defined(__linux__) && defined(__aarch64__)
    context.uc_mcontext.pc = value;
#endif
}

#endif // _STACK_WALKER_TEST_UTILS_H 