/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _CONCURRENTHASHTABLE_H
#define _CONCURRENTHASHTABLE_H

#include "arch_dd.h"
#include "spinLock.h"

#define STRIPE_BITS 6
#define STRIPES (1 << STRIPE_BITS)
#define STRIPE_CELLS 4
#define STRIPE_MASK (STRIPES - 1)

// Lock-striped concurrent hash table inspired by Dictionary design
// Provides true N-way parallelism with independent stripe locks
template<typename K, typename V>
class ConcurrentHashTable {
private:
  struct StripeEntry {
    K key;
    V value;
    
    StripeEntry() : key(0), value() {}
  };
  
  struct Stripe {
    SpinLock lock;          // Each stripe has its own lock for N-way parallelism
    StripeEntry entries[STRIPE_CELLS];
  };
  
  Stripe _stripes[STRIPES];
  
  static u32 hash(K key) {
    // Simple hash function for integer keys
    u32 h = (u32)key;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
  }
  
public:
  ConcurrentHashTable() {
    clear();
  }
  
  // Thread-safe insert/update - uses lock striping for N-way parallelism
  void put(K key, const V& value) {
    if (key == 0) return; // Reserve 0 as empty marker
    
    u32 h = hash(key);
    u32 stripe_idx = h & STRIPE_MASK;
    Stripe& stripe = _stripes[stripe_idx];
    
    // Lock this stripe - other stripes remain accessible
    stripe.lock.lock();
    
    // Try to find existing entry or empty slot in this stripe
    for (u32 i = 0; i < STRIPE_CELLS; i++) {
      if (stripe.entries[i].key == key) {
        // Key exists, update value
        stripe.entries[i].value = value;
        stripe.lock.unlock();
        return;
      }
      
      if (stripe.entries[i].key == 0) {
        // Empty slot, claim it
        stripe.entries[i].key = key;
        stripe.entries[i].value = value;
        stripe.lock.unlock();
        return;
      }
    }
    
    stripe.lock.unlock();
    // Stripe full - drop entry (similar to Dictionary when row is full)
  }
  
  // Thread-safe lookup with shared locking for better read concurrency
  bool get(K key, V& value) {
    if (key == 0) return false;
    
    u32 h = hash(key);
    u32 stripe_idx = h & STRIPE_MASK;
    Stripe& stripe = _stripes[stripe_idx];
    
    // Use shared lock for better read concurrency
    stripe.lock.lockShared();
    
    for (u32 i = 0; i < STRIPE_CELLS; i++) {
      if (stripe.entries[i].key == key) {
        value = stripe.entries[i].value;
        stripe.lock.unlockShared();
        return true;
      }
      
      if (stripe.entries[i].key == 0) {
        stripe.lock.unlockShared();
        return false; // Empty slot, key not found
      }
    }
    
    stripe.lock.unlockShared();
    return false; // Not found in this stripe
  }
  
  // Clear all entries (not thread-safe with put/get operations)
  void clear() {
    for (u32 s = 0; s < STRIPES; s++) {
      for (u32 i = 0; i < STRIPE_CELLS; i++) {
        _stripes[s].entries[i].key = 0;
        _stripes[s].entries[i].value = V{};
      }
    }
  }
  
  u32 capacity() const { return STRIPES * STRIPE_CELLS; }
};

#endif // _CONCURRENTHASHTABLE_H