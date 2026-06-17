/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __THREADLOCAL_H__
#define __THREADLOCAL_H__

#include <cassert>
#include <cstring>
#include <pthread.h>
#include "arch.h"

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
        // Only support 64-bit platforms
        static_assert(sizeof(void*) == 8);
        int err;
        while ((err = pthread_key_create(&_key, F)) == EAGAIN);
        // What to do if we can not create a key?
        assert(err == 0);
    }

    ~ThreadLocal() {
        pthread_key_delete(_key);
    }
    void set(T value) {
        pthread_setspecific(_key, (const void*)value);
    }

    T get() {
        void* p = pthread_getspecific(_key);
        if (p == nullptr && C != nullptr) {
            p = C();
            set((T)p);
        }
        return (T)p;
    }
};

template <>
class ThreadLocal<double> {
protected:
    pthread_key_t _key;
public:
    ThreadLocal() {
        // Only support 64-bit platforms
        static_assert(sizeof(void*) == 8);
        int err;
        while ((err = pthread_key_create(&_key, nullptr)) == EAGAIN);
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
        pthread_setspecific(_key, (const void*)val);
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
};

#endif // __THREADLOCAL_H__
