/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREADLOCAL_H
#define _THREADLOCAL_H

#include <cassert>
#include <cstring>
#include <pthread.h>
#include "arch.h"

/**
 * This file implements an alternative to C/C++ thread local.
 * Due to some restrictions of the language implementations, especially, on musl/aarch64,
 * they cannot be safely used in profiler.
 * 
 * How to use?
 * A ThreadLocal should be declared as a static variable, e.g.
 * 
 * static void* create_my_object() {
 *   return new MyObject();
 * }
 * 
 * static void delete_my_object(void* p) {
 *   MyObject* obj = (MyObject*)p;
 *   delete obj; 
 * }
 * 
 * static ThreadLocal<MyObject*, create_my_object, delete_my_object> var;
 * MyObject* value = var.get();
 * ...
 * var.clear();
 * ... 
 * MyObject* new_value = new MyObject();
 * var.set(new_value);
 * ...
 * var.clear();
 * 
 */

// The function to create value if it does not exist
typedef void* (*CREATE_FUNC)(void);
// Cleanup the value when deleting the key
typedef void (*CLEAN_FUNC)(void*);
template <typename T, CREATE_FUNC C = nullptr, CLEAN_FUNC F = nullptr>
class ThreadLocal {
protected:
    pthread_key_t _key;
    bool _key_valid;
 
public:
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;

    ThreadLocal() {
        static_assert(sizeof(T) == sizeof(void*),
                      "ThreadLocal<T> requires sizeof(T)==sizeof(void*); use a pointer type or add a specialization");
        _key_valid = pthread_key_create(&_key, F) == 0;
        // What to do if we can not create a key?
        // We probably want to shutdown profiler gracefully, instead of
        // aborting user application - We will need this mechanism globally,
        // defer to a separate task.
        assert(_key_valid);
    }

    ~ThreadLocal() {
        if(_key_valid) {
            pthread_key_delete(_key);
        }
    }

    /**
     * set(nullptr) will result in the value being recreated when get() is called
     * when CREATE_FUNC is not nullptr.
     * Note: caller is responsible to free old value, which mirrors thread_local
     */
    void set(T value) {
        assert(_key_valid);
        int err = pthread_setspecific(_key, reinterpret_cast<const void*>(value));
        assert(err == 0);
    }

    T get() {
        assert(_key_valid);
        void* p = pthread_getspecific(_key);
        if (p == nullptr && C != nullptr) {
            p = C();
            set((T)p);
        }
        return reinterpret_cast<T>(p);
    }

    // Clear the value
    void clear() {
        assert(_key_valid);
        void* p = pthread_getspecific(_key);
        if (p == nullptr) return;
        int err = pthread_setspecific(_key, nullptr);
        // Safety: if reset the value failed, get() can see staled value if
        // it is freed.
        if (err == 0 && F != nullptr) {
            F(p);
        }
    }
};

template <>
class ThreadLocal<double> {
protected:
    pthread_key_t _key;
    bool _key_valid;

public:
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;

    ThreadLocal() {
        // Only support 64-bit platforms, double and void* are the same size
        static_assert(sizeof(void*) == 8);
        static_assert(sizeof(double) == 8);
        _key_valid = pthread_key_create(&_key, nullptr) == 0;
        // What to do if we can not create a key?
        assert(_key_valid);
    }

    ~ThreadLocal() {
        if(_key_valid) {
            pthread_key_delete(_key);
        }
    }

    // double <--> u64 cast, preserve bit format
    // Can use std::bit_cast after upgrade C++ version to 20
    void set(double value) {
        assert(_key_valid);
        u64 val;
        memcpy(&val, &value, sizeof(value));
        int err = pthread_setspecific(_key, reinterpret_cast<const void*>(val));
        assert(err == 0);
    }

    double get() {
        assert(_key_valid);
        void* p = pthread_getspecific(_key);
        if (p == nullptr) {
            return 0.0;
        }

        u64 val = (u64)p;
        double value;
        memcpy(&value, &val, sizeof(val));
        return value;
    }

    void clear() {
        assert(_key_valid);
        int err = pthread_setspecific(_key, nullptr);
        assert(err == 0);
    }
};

#endif // _THREADLOCAL_H
