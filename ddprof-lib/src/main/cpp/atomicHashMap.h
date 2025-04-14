// Copyright (c) 2024
// This file is part of a profiler system maintained by Datadog, Inc.
// Generated with AI assistance based on known principles of lock-free data structures.
// This implementation was inspired by folly::AtomicHashMap.

#ifndef _ATOMICHASHMAP_H
#define _ATOMICHASHMAP_H

#include "common.h"
#include <atomic>
#include <vector>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <optional>
#include <cstdint>
#include <limits>

static constexpr int EMPTY_KEY = std::numeric_limits<int>::min();

template<typename KeyT, typename ValueT>
class AtomicHashMap {
public:
    AtomicHashMap() {
        for (size_t i = 0; i < MAX_THREAD_SLOTS; i++) {
            _keys[i].store(EMPTY_KEY, std::memory_order_relaxed);
            _values[i].store(false, std::memory_order_relaxed);
        }
    }

    void insert(KeyT key, ValueT value) {
        for (size_t i = 0; i < MAX_THREAD_SLOTS; i++) {
            size_t index = (std::hash<KeyT>{}(key) + i) % MAX_THREAD_SLOTS;
            KeyT expected = EMPTY_KEY;
            if (_keys[index].compare_exchange_strong(expected, key, std::memory_order_acq_rel)) {
                _values[index].store(value, std::memory_order_release);
                return;
            } else if (_keys[index].load(std::memory_order_acquire) == key) {
                _values[index].store(value, std::memory_order_release);
                return;
            }
        }
        fprintf(stderr, "[AtomicHashMap] Insert failed: map full\n");
    }

    void erase(KeyT key) {
        for (size_t i = 0; i < MAX_THREAD_SLOTS; i++) {
            size_t index = (std::hash<KeyT>{}(key) + i) % MAX_THREAD_SLOTS;
            if (_keys[index].load(std::memory_order_acquire) == key) {
                _values[index].store(false, std::memory_order_release);
                return;
            }
        }
    }

    bool find(KeyT key) const {
        for (size_t i = 0; i < MAX_THREAD_SLOTS; i++) {
            size_t index = (std::hash<KeyT>{}(key) + i) % MAX_THREAD_SLOTS;
            if (_keys[index].load(std::memory_order_acquire) == key) {
                return _values[index].load(std::memory_order_acquire);
            }
        }
        return false;
    }

    void clear() {
        for (size_t i = 0; i < MAX_THREAD_SLOTS; i++) {
            _keys[i].store(EMPTY_KEY, std::memory_order_relaxed);
            _values[i].store(false, std::memory_order_relaxed);
        }
    }

    void collect(std::vector<KeyT>& out) const {
        for (size_t i = 0; i < MAX_THREAD_SLOTS; i++) {
            KeyT key = _keys[i].load(std::memory_order_acquire);
            if (key != EMPTY_KEY && _values[i].load(std::memory_order_acquire)) {
                out.push_back(key);
            }
        }
    }

    struct Iterator {
        const AtomicHashMap* map;
        size_t index;

        Iterator(const AtomicHashMap* m, size_t i) : map(m), index(i) {
            advanceToValid();
        }

        void advanceToValid() {
            while (index < MAX_THREAD_SLOTS) {
                KeyT key = map->_keys[index].load(std::memory_order_acquire);
                bool val = map->_values[index].load(std::memory_order_acquire);
                if (key != EMPTY_KEY && val) {
                    break;
                }
                ++index;
            }
        }

        std::pair<KeyT, ValueT> operator*() const {
            return {map->_keys[index].load(std::memory_order_relaxed),
                    map->_values[index].load(std::memory_order_relaxed)};
        }

        Iterator& operator++() {
            ++index;
            advanceToValid();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }
    };

    Iterator begin() const {
        return Iterator(this, 0);
    }

    Iterator end() const {
        return Iterator(this, MAX_THREAD_SLOTS);
    }

private:
    std::atomic<KeyT> _keys[MAX_THREAD_SLOTS];
    std::atomic<ValueT> _values[MAX_THREAD_SLOTS];
};

#endif // _ATOMICHASHMAP_H
