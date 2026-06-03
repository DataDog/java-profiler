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

#include "context_api.h"
#include "context.h"
#include "guards.h"
#include "otel_context.h"
#include "profiler.h"
#include "thread.h"
#include <cstring>

/**
 * Initialize context TLS for the current thread on first use.
 * Must be called with signals blocked to prevent musl TLS deadlock:
 * on musl, the first write to a TLS variable triggers lazy slot allocation,
 * which acquires an internal lock that is also held during signal delivery,
 * causing deadlock if a signal fires mid-init.
 * The OtelThreadContextRecord is already zero-initialized by the ProfiledThread ctor.
 */
void ContextApi::initializeContextTLS(ProfiledThread* thrd) {
    SignalBlocker blocker;
    // Set the TLS pointer permanently to this thread's record.
    // This first write triggers musl's TLS slot initialization (see above).
    // The pointer remains stable for the thread's lifetime; external profilers
    // rely solely on the valid flag for consistency, not pointer nullness.
    otel_thread_ctx_v1 = thrd->getOtelContextRecord();
    thrd->markContextInitialized();
}

bool ContextApi::get(u64& span_id, u64& root_span_id) {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr || !thrd->isContextInitialized()) {
        return false;
    }

    OtelThreadContextRecord* record = thrd->getOtelContextRecord();
    if (__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
        return false;
    }
    u64 val = 0;
    for (int i = 0; i < 8; i++) { val = (val << 8) | record->span_id[i]; }
    span_id = val;

    root_span_id = thrd->getOtelLocalRootSpanId();
    return true;
}

Context ContextApi::snapshot() {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr) {
        return {};
    }
    size_t numAttrs = Profiler::instance()->numContextAttributes();
    return thrd->snapshotContext(numAttrs);
}
