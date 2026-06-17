/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __TLS_H
#define __TLS_H

#include <cassert>
#include <cstring>
#include <pthread.h>
#include "arch.h"

typedef void (*CLEAN_FUNC)(void*);

template <typename T, CLEAN_FUNC F = nullptr>
class ThreadLocal {
protected:
    static inline pthread_key_t _key;
    static inline pthread_once_t _key_once = PTHREAD_ONCE_INIT;
 
    static void create_thread_key() {
        pthread_key_create(&_key, F);
    }
public:
    ThreadLocal() {
        pthread_once(&_key_once, create_thread_key);;
    }
    ~ThreadLocal() {
        pthread_key_delete(_key);
    }
    static void set(T value) {
        pthread_setspecific(_key, (const void*)value);
    }

    static T get() {
        return (T)pthread_getspecific(_key);
    }
};

template <>
class ThreadLocal<double> {
protected:
    static inline pthread_key_t _key;
    static inline pthread_once_t _key_once = PTHREAD_ONCE_INIT;

    static void create_thread_key() {
        pthread_key_create(&_key, nullptr);
    }
public:
    ThreadLocal() {
        pthread_once(&_key_once, create_thread_key);
    }
    ~ThreadLocal() {
        pthread_key_delete(_key);
    }

    // double <--> u64 cast, preserve bit format
    // Can use std::bit_cast after upgrade C++ version to 20
    static void set(double value) {
        u64 val;
        memcpy(&val, &value, sizeof(value));
        pthread_setspecific(_key, (const void*)val);
    }

    static double get() {
        u64 val = (u64)pthread_getspecific(_key);
        double value;
        memcpy(&value, &val, sizeof(val));
        return value;
    }
};

#endif // __TLS_H
