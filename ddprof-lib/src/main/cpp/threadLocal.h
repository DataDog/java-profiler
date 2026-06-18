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
 
public:
    ThreadLocal() {
        int err = pthread_key_create(&_key, F);
        // What to do if we can not create a key?
        assert(err == 0);
    }

    ~ThreadLocal() {
        pthread_key_delete(_key);
    }

    void set(T value) {
        int err = pthread_setspecific(_key, (const void*)value);
        assert(err == 0);
    }

    T get() {
        void* p = pthread_getspecific(_key);
        if (p == nullptr && C != nullptr) {
            p = C();
            set((T)p);
        }
        return (T)p;
    }

    // Clear the value
    void clear() {
        void* p = nullptr;
        if (F != nullptr && (p = pthread_getspecific(_key)) != nullptr) {
            int err = pthread_setspecific(_key, nullptr);
            assert(err == 0);
            F(p);
        }
    }
};

template <>
class ThreadLocal<double> {
protected:
    pthread_key_t _key;
public:
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;

    ThreadLocal() {
        // Only support 64-bit platforms, double and void* are the same size
        static_assert(sizeof(void*) == 8);
        static_assert(sizeof(double) == 8);
        int err = pthread_key_create(&_key, nullptr);
        // What to do if we can not create a key?
        assert(err == 0);
    }

    ~ThreadLocal() {
        pthread_key_delete(_key);
    }

    // double <--> u64 cast, preserve bit format
    // Can use std::bit_cast after upgrade C++ version to 20
    void set(double value) {
        u64 val;
        memcpy(&val, &value, sizeof(value));
        int err = pthread_setspecific(_key, (const void*)val);
        assert(err == 0);
    }

    double get() {
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
        int err = pthread_setspecific(_key, nullptr);
        assert(err == 0);
    }
};

#endif // __THREADLOCAL_H__
