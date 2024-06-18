#ifndef ASYNCSAMPLEMUTEX_H
#define ASYNCSAMPLEMUTEX_H

#include "threadLocalData.h"

// controls access to AGCT
class AsyncSampleMutex {
private:
    ThreadLocalData* _threadLocalData;
    bool _acquired;

    bool try_acquire() {
        if (_threadLocalData != nullptr && !_threadLocalData->is_unwinding_Java()) {
            _threadLocalData->set_unwinding_Java(true);
            return true;
        }
        return false;
    }

public:
    AsyncSampleMutex(ThreadLocalData* threadLocalData) : _threadLocalData(threadLocalData) {
        _acquired = try_acquire();
    }

    AsyncSampleMutex(AsyncSampleMutex& other) = delete;

    ~AsyncSampleMutex() {
        if (_acquired) {
            _threadLocalData->set_unwinding_Java(false);
        }
    }

    bool acquired() {
        return _acquired;
    }
};

#endif //ASYNCSAMPLEMUTEX_H
