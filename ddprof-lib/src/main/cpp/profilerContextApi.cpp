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

#include "support/context_api.h"
#include "context.h"
#include "profiler.h"
#include "thread.h"

/**
 * Snapshot the current thread's full context into a Context struct.
 *
 * Lives in the profiler translation unit (rather than support/context_api.cpp)
 * because it needs Profiler::instance()->numContextAttributes() and
 * ProfiledThread::snapshotContext(), neither of which are available to the
 * support-only (profiler-less) build.
 */
Context ContextApi::snapshot() {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr) {
        return {};
    }
    size_t numAttrs = Profiler::instance()->numContextAttributes();
    return thrd->snapshotContext(numAttrs);
}
