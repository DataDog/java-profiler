/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LOCKFREE_H
#define _LOCKFREE_H

#include "common.h"

#include <atomic>
#include <cstddef>
#include <cstdint>

/**
 * Lock-free atomic primitives and utilities.
 *
 * This header provides building blocks for lock-free data structures:
 * - PaddedAtomic: Cache-line padded atomics to prevent false sharing
 * - LockFreeBitset: Lock-free bitset for concurrent membership tracking
 *
 * For complete synchronization classes (SpinLock, mutexes), see spinLock.h
 */

// Cache line size for preventing false sharing (typical for x86/ARM)
// Note: This duplicates DEFAULT_CACHE_LINE_SIZE from arch_dd.h for standalone use
constexpr size_t CACHE_LINE_SIZE = 64;

/**
 * Atomic value padded to its own cache line to prevent false sharing.
 *
 * Use this when you have an array of atomics that are frequently accessed
 * by different threads. Without padding, atomics in adjacent array elements
 * may share a cache line, causing false sharing that degrades performance.
 *
 * False sharing occurs when:
 * - Thread A modifies atomic at index 0
 * - Thread B modifies atomic at index 1
 * - Both atomics are on the same cache line
 * - CPU must invalidate entire cache line, forcing both threads to reload
 *
 * Example usage:
 *   static PaddedAtomic<uint64_t> counters[128];  // Each counter on own cache line
 *   counters[i].value.fetch_add(1, std::memory_order_relaxed);
 *
 * @tparam T The atomic value type (e.g., uint64_t, int, bool)
 */
template<typename T>
struct alignas(CACHE_LINE_SIZE) PaddedAtomic {
  std::atomic<T> value;
  // Padding is automatic due to alignas - ensures this struct occupies full cache line
};

/**
 * Lock-free bitset for concurrent membership tracking.
 *
 * A fixed-size bitset that supports lock-free set, clear, and test operations.
 * Uses cache-line padded atomic words to prevent false sharing between threads
 * operating on different portions of the bitset.
 *
 * Hash-based operations use double-hashing with two independent hash functions
 * to minimize false positives. A key is considered "set" only if both
 * corresponding bits (from both hash functions) are set. This reduces the
 * false positive probability from p to p² compared to single-hash approaches.
 *
 * Thread safety:
 * - All operations are lock-free and async-signal-safe
 * - Uses atomic operations with appropriate memory ordering
 * - Safe to call from signal handlers
 *
 * Example usage:
 *   static LockFreeBitset<8192> threadSet;
 *
 *   // Hash-based operations (for integer keys like thread IDs)
 *   threadSet.set(tid);              // Mark thread as member
 *   if (threadSet.test(tid)) { ... } // Check membership
 *   threadSet.clear(tid);            // Remove from set
 *
 *   // Raw bit operations (when you manage indexing yourself)
 *   threadSet.setRaw(42);            // Set bit 42
 *   threadSet.clearRaw(42);          // Clear bit 42
 *
 * @tparam NumBits Total number of bits per array (should be power of 2 for efficient hashing)
 */
template<size_t NumBits>
class LockFreeBitset {
public:
  static constexpr size_t NUM_BITS = NumBits;
  static constexpr size_t BITS_PER_WORD = 64;
  static constexpr size_t NUM_WORDS = (NumBits + BITS_PER_WORD - 1) / BITS_PER_WORD;

  /**
   * Initializes the bitset with all bits cleared in both arrays.
   */
  void init() {
    for (size_t i = 0; i < NUM_WORDS * 2; i++) {
      _words[i].value.store(0, std::memory_order_relaxed);
    }
  }

  /**
   * Sets the bits for the given key using double-hash indexing.
   * Sets bits in both arrays using two independent hash functions.
   *
   * @param key Integer key to hash and set
   */
  void set(size_t key) {
    setBit(hashKey1(key), 0);  // Array 1 at even indices
    setBit(hashKey2(key), 1);  // Array 2 at odd indices
  }

  /**
   * Clears the bits for the given key using double-hash indexing.
   * Clears bits in both arrays using two independent hash functions.
   *
   * @param key Integer key to hash and clear
   */
  void clear(size_t key) {
    clearBit(hashKey1(key), 0);  // Array 1 at even indices
    clearBit(hashKey2(key), 1);  // Array 2 at odd indices
  }

  /**
   * Tests if the key is set using double-hash indexing.
   * Returns true only if BOTH bits (from both hash functions) are set.
   * This minimizes false positives compared to single-hash approaches.
   *
   * @param key Integer key to hash and test
   * @return true if both bits are set, false otherwise
   */
  bool test(size_t key) const {
    return testBit(hashKey1(key), 0) && testBit(hashKey2(key), 1);
  }

  /**
   * Sets the bit at the given raw index in the primary array (no hashing).
   *
   * @param bit_index Raw bit index (0 to NumBits-1)
   */
  void setRaw(size_t bit_index) {
    setBit(bit_index, 0);  // Use array 1 (even indices)
  }

  /**
   * Clears the bit at the given raw index in the primary array (no hashing).
   *
   * @param bit_index Raw bit index (0 to NumBits-1)
   */
  void clearRaw(size_t bit_index) {
    clearBit(bit_index, 0);  // Use array 1 (even indices)
  }

  /**
   * Tests if the bit at the given raw index is set in the primary array (no hashing).
   *
   * @param bit_index Raw bit index (0 to NumBits-1)
   * @return true if the bit is set, false otherwise
   */
  bool testRaw(size_t bit_index) const {
    return testBit(bit_index, 0);  // Use array 1 (even indices)
  }

  /**
   * Clears all bits in both arrays.
   */
  void clearAll() {
    init();
  }

private:
  // Second hash constant - FNV offset basis provides good independence from Knuth constant
  static constexpr size_t HASH2_CONSTANT = 0x517cc1b727220a95ULL;

  // Interleaved array layout for L1 cache optimization.
  // Layout: [word1_0, word2_0, word1_1, word2_1, ..., word1_N-1, word2_N-1]
  // When test() accesses both hash positions, if they map to similar word indices,
  // they'll be on adjacent cache lines, improving cache hit rate.
  // Total memory: NUM_WORDS * 2 * 64 bytes (e.g., 256 * 2 * 64 = 32 KB for 16384 bits)
  PaddedAtomic<uint64_t> _words[NUM_WORDS * 2];

  /**
   * Primary hash function using Knuth multiplicative hash.
   */
  static size_t hashKey1(size_t key) {
    return (key * KNUTH_MULTIPLICATIVE_CONSTANT) % NumBits;
  }

  /**
   * Secondary hash function using upper bits of multiplication.
   * While hash1 uses lower bits (via modulo), hash2 uses upper bits
   * to provide true independence between the two hash functions.
   */
  static size_t hashKey2(size_t key) {
    // Use upper 32 bits of the multiplication result
    // This provides independence from hash1 which uses lower bits via modulo
    size_t product = key * HASH2_CONSTANT;
    return (product >> 32) % NumBits;
  }

  /**
   * Sets a bit in the interleaved array.
   * @param bit_index The bit index within the logical array
   * @param array_offset 0 for array1 (even indices), 1 for array2 (odd indices)
   */
  void setBit(size_t bit_index, size_t array_offset) {
    size_t word_index = bit_index / BITS_PER_WORD;
    size_t interleaved_index = word_index * 2 + array_offset;
    uint64_t bit_mask = 1ULL << (bit_index % BITS_PER_WORD);
    _words[interleaved_index].value.fetch_or(bit_mask, std::memory_order_release);
  }

  /**
   * Clears a bit in the interleaved array.
   * @param bit_index The bit index within the logical array
   * @param array_offset 0 for array1 (even indices), 1 for array2 (odd indices)
   */
  void clearBit(size_t bit_index, size_t array_offset) {
    size_t word_index = bit_index / BITS_PER_WORD;
    size_t interleaved_index = word_index * 2 + array_offset;
    uint64_t bit_mask = 1ULL << (bit_index % BITS_PER_WORD);
    _words[interleaved_index].value.fetch_and(~bit_mask, std::memory_order_release);
  }

  /**
   * Tests a bit in the interleaved array.
   * @param bit_index The bit index within the logical array
   * @param array_offset 0 for array1 (even indices), 1 for array2 (odd indices)
   */
  bool testBit(size_t bit_index, size_t array_offset) const {
    size_t word_index = bit_index / BITS_PER_WORD;
    size_t interleaved_index = word_index * 2 + array_offset;
    uint64_t bit_mask = 1ULL << (bit_index % BITS_PER_WORD);
    uint64_t word = _words[interleaved_index].value.load(std::memory_order_acquire);
    return (word & bit_mask) != 0;
  }
};

#endif // _LOCKFREE_H
