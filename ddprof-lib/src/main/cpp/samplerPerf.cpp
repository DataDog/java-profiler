/*
 * Copyright 2026, Datadog, Inc.
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

#include "samplerPerf.h"
#include <stdio.h>

#define X_SAMPLER_NAME(id, name) name,
static const char *const SAMPLER_NAMES[] = {DD_SAMPLER_LIST(X_SAMPLER_NAME)};
#undef X_SAMPLER_NAME

const char *SamplerPerf::name(SamplerId id) {
  if (id < 0 || id >= SP_NUM_SAMPLERS) {
    return "unknown";
  }
  return SAMPLER_NAMES[id];
}

#ifdef __SAMPLER_PERF__

void SamplerPerf::primeClock() { OS::nanotime(); }

void SamplerPerf::report() {
  // Read the ticks/count pair for each sampler up front so the "did anything
  // run" decision and the printed rows agree, even though a late signal can
  // still bump the counters while we are here.
  long long ticks[SP_NUM_SAMPLERS];
  long long count[SP_NUM_SAMPLERS];
  bool any = false;
  for (int i = 0; i < SP_NUM_SAMPLERS; i++) {
    ticks[i] = Counters::getCounter(SAMPLER_TICKS_CPU, 2 * i);
    count[i] = Counters::getCounter(SAMPLER_TICKS_CPU, 2 * i + 1);
    if (count[i] > 0) {
      any = true;
    }
  }

  if (!any) {
    return;
  }

  fprintf(stdout, "[java-profiler] sampler performance (elapsed wall time, "
                  "not CPU time):\n");
  fprintf(stdout, "[java-profiler]   %-14s %14s %12s %12s\n", "sampler",
          "total (ms)", "count", "avg (ns)");

  for (int i = 0; i < SP_NUM_SAMPLERS; i++) {
    if (count[i] <= 0) {
      // Engine never ran this recording.
      continue;
    }
    u64 total_ns = ticksToNanos((u64)ticks[i]);
    fprintf(stdout, "[java-profiler]   %-14s %14.3f %12lld %12llu\n",
            name((SamplerId)i), (double)total_ns / 1000000.0, count[i],
            (unsigned long long)(total_ns / (u64)count[i]));
  }
  // Points at the two subset relationships that make these rows easy to
  // misread; the full set of caveats is in samplerPerf.h.
  fprintf(stdout,
          "[java-profiler]   note: cpu includes unwinding_ticks_async, and "
          "alloc includes liveness; do not sum them.\n");
  fflush(stdout);
}

#else // __SAMPLER_PERF__

void SamplerPerf::primeClock() {
  // Built without -PenableSamplerPerf: no probe ever calls OS::nanotime()
  // from a signal handler, so there is nothing to prime.
}

void SamplerPerf::report() {
  // Built without -PenableSamplerPerf: the counter slots do not exist.
}

#endif // __SAMPLER_PERF__
