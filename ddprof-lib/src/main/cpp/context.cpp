/*
 * Copyright 2021, 2022 Datadog, Inc
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

#include "context.h"
#include "counters.h"
#include "os_dd.h"
#include "thread.h"
#include <cstring>

DLLEXPORT thread_local Context context_tls_v1;

Context& Contexts::initializeContextTls() {
  Context& ctx = context_tls_v1;
  // Store pointer for signal-safe access
  // Use getOrCreate() because this can be called before profiling starts
  // (e.g., context TLS init during library loading, before onThreadStart callback)
  ProfiledThread::getOrCreate()->markContextTlsInitialized(&ctx);
  return ctx;
}

Context& Contexts::get() {
  ProfiledThread* thrd = ProfiledThread::get();
  if (thrd == nullptr || !thrd->isContextTlsInitialized()) {
    return DD_EMPTY_CONTEXT;
  }
  // Return via stored pointer - never access context_tls_v1 from signal handler
  // This avoids triggering TLS lazy initialization which can deadlock in malloc
  return *thrd->getContextTlsPtr();
}
