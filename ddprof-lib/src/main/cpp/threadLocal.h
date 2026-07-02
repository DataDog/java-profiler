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
 * pthread_(get/set)specific() are not async-signal-safe, according to 
 * https://man7.org/linux/man-pages/man7/signal-safety.7.html
 * 
 * In POSIX implementation, pthread_setspecific() call can trigger memory allocation
 * if the slot is not available.
 * Because we depend on the APIs to maintain per-thread data, we need to workaround the
 * problem - call pthread_setspecific() at least once before signal is enabled for the
 * thread (ideally, the value is set before signal is enabled).
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

#include <unistd.h>

// The function to create value if it does not exist
typedef void* (*CREATE_FUNC)(void);
// Cleanup the value when deleting the key
typedef void (*CLEAN_FUNC)(void*);

static constexpr pthread_key_t INVALID_KEY = pthread_key_t(-1);

template <typename T, CREATE_FUNC C = nullptr, CLEAN_FUNC F = nullptr>
class ThreadLocal {
protected:
    pthread_key_t _key;
 
public:
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;

    ThreadLocal() : _key(INVALID_KEY) {
        static_assert(sizeof(T) == sizeof(void*),
                      "ThreadLocal<T> requires sizeof(T)==sizeof(void*); use a pointer type or add a specialization");
        if (pthread_key_create(&_key, F) != 0) {
            _key = INVALID_KEY;
        }
        // What to do if we can not create a key?
        // We probably want to shutdown profiler gracefully, instead of
        // aborting user application - We will need this mechanism globally,
        // defer to a separate task.
        assert(isKeyValid());
    }

    ~ThreadLocal() {
        if(isKeyValid()) {
            pthread_key_delete(_key);
        } else {
            assert(false && "Invalid pthread key");
        }
    }

    bool isKeyValid() const {
        return _key != INVALID_KEY;
    }

    /**
     * set(nullptr) will result in the value being recreated when get() is called
     * when CREATE_FUNC is not nullptr.
     * Note: caller is responsible to free old value, which mirrors thread_local
     */
    void set(T value) {
        assert(isKeyValid() && "Invalid pthread key");
        int err = pthread_setspecific(_key, reinterpret_cast<const void*>(value));
        assert(err == 0);
    }

    T get() {
        assert(isKeyValid() && "Invalid pthread key");
        void* p = pthread_getspecific(_key);
        if (p == nullptr && C != nullptr) {
            p = C();
            set((T)p);
        }
        return reinterpret_cast<T>(p);
    }

    // Clear the value
    void clear() {
        assert(isKeyValid() && "Invalid pthread key");
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

public:
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;

    ThreadLocal() : _key(INVALID_KEY) {
        // Only support 64-bit platforms, double and void* are the same size
        static_assert(sizeof(void*) == 8);
        static_assert(sizeof(double) == 8);
        if (pthread_key_create(&_key, nullptr) != 0) {
            _key = INVALID_KEY;
        }
        // What to do if we can not create a key?
        assert(isKeyValid() && "Invalid pthread key");
    }

    ~ThreadLocal() {
        if(isKeyValid()) {
            pthread_key_delete(_key);
        } else {
            assert(isKeyValid() && "Invalid pthread key");
        }
    }

    bool isKeyValid() const {
        return _key != INVALID_KEY;
    }

    // double <--> u64 cast, preserve bit format
    // Can use std::bit_cast after upgrade C++ version to 20
    void set(double value) {
        assert(isKeyValid() && "Invalid pthread key");
        u64 val;
        memcpy(&val, &value, sizeof(value));
        int err = pthread_setspecific(_key, reinterpret_cast<const void*>(val));
        assert(err == 0);
    }

    double get() const {
        assert(isKeyValid() && "Invalid pthread key");
        void* p = pthread_getspecific(_key);
        if (p == nullptr) {
            return 0.0;
        }

        u64 val = reinterpret_cast<u64>(p);
        double value;
        memcpy(&value, &val, sizeof(val));
        return value;
    }

    void clear() {
        assert(isKeyValid() && "Invalid pthread key");
        int err = pthread_setspecific(_key, nullptr);
        assert(err == 0);
    }
};

class JVMThread;

/**
 * This thread local mirrors JVM's Thread::current(). The value is set by JVM
 * and it is read-only variable.
 */
template <>
class ThreadLocal<JVMThread*> {
protected:
    pthread_key_t _key;

public:
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;

    ThreadLocal() : _key(INVALID_KEY) {
    }

    // The key is created by JVM, find out the key.
    // This method should be called very early at Profiler startup
    // time
    bool initialize(void* current_thread) {
        // Called from known JavaThread, it must not be nullptr.
        assert(current_thread != nullptr && "Should not reach here");
        if (current_thread == nullptr) {
            // A NULL current_thread would make the scan below match the
            // first never-created key (pthread_getspecific() also returns
            // NULL for it), silently producing a bogus _key. Bail out
            // instead and leave _key == INVALID_KEY.
            return false;
        }

        long max_keys = sysconf(_SC_THREAD_KEYS_MAX);
        if (max_keys <= 0 || max_keys > 1024) {
            max_keys = 1024;  // fallback/cap; matches historical scan bound
        }
        for (long i = 0; i < max_keys; i++) {
            if (pthread_getspecific((pthread_key_t)i) == current_thread) {
                _key = pthread_key_t(i);
                break;
            }
        }
        assert(isKeyValid() && "Invalid thread key");
        return isKeyValid();
    }

    bool isKeyValid() const {
        return _key != INVALID_KEY;
    }

    pthread_key_t key() const {
        return _key;
    }

    void set(JVMThread* value) {
        assert(false && "Should not reach here, value is set by JVM");
    }

    void* get() const {
        assert(isKeyValid() && "Invalid pthread key");
        if (!isKeyValid()) {
            return nullptr;
        }
        return pthread_getspecific(_key);
    }

    void clear() {
        assert(false && "Should not reach here");
    }
};


#endif // _THREADLOCAL_H
