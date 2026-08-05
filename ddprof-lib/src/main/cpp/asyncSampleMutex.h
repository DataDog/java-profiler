/*
 * Copyright 2026, Datadog, Inc
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

#ifndef ASYNCSAMPLEMUTEX_H
#define ASYNCSAMPLEMUTEX_H

#include "threadLocalData.h"

// controls access to AGCT
class AsyncSampleMutex {
private:
  ThreadLocalData *_threadLocalData;
  bool _acquired;

  bool try_acquire() {
    if (_threadLocalData != nullptr && !_threadLocalData->is_unwinding_Java()) {
      _threadLocalData->set_unwinding_Java(true);
      return true;
    }
    return false;
  }

public:
  AsyncSampleMutex(ThreadLocalData *threadLocalData)
      : _threadLocalData(threadLocalData) {
    _acquired = try_acquire();
  }

  AsyncSampleMutex(AsyncSampleMutex &other) = delete;

  ~AsyncSampleMutex() {
    if (_acquired) {
      _threadLocalData->set_unwinding_Java(false);
    }
  }

  bool acquired() { return _acquired; }
};

#endif // ASYNCSAMPLEMUTEX_H
