/*
 * Copyright 2022 Andrei Pangin
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

#ifndef _OBJECTSAMPLER_H
#define _OBJECTSAMPLER_H

#include "arch_dd.h"
#include "engine.h"
#include "jfrMetadata.h"
#include "livenessTracker.h"
#include <jvmti.h>
#include <time.h>

typedef int (*get_sampling_interval)();

class ObjectSampler : public Engine {
  friend Recording;

private:
  static ObjectSampler *const _instance;

  int _interval;
  int _configured_interval;
  bool _record_allocations;
  bool _record_liveness;
  bool _gc_generations;
  int _max_stack_depth;

  u64 _last_config_update_ts;
  u64 _alloc_event_count;

  const static int CONFIG_UPDATE_CHECK_PERIOD_SECS = 1;
  int _target_samples_per_window = 100; // ~6k samples per minute by default

  Error updateConfiguration(u64 events, double time_coefficient);

  ObjectSampler()
      : _interval(0), _configured_interval(0), _record_allocations(false),
        _record_liveness(false), _gc_generations(false), _max_stack_depth(0),
        _last_config_update_ts(0), _alloc_event_count(0) {}

protected:
  void recordAllocation(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                        int event_type, jobject object, jclass object_klass,
                        jlong size);

public:
  static ObjectSampler *const instance() { return _instance; }

  Error check(Arguments &args);
  Error start(Arguments &args);
  void stop();

  long interval() const override { return _interval; }

  static void JNICALL SampledObjectAlloc(jvmtiEnv *jvmti, JNIEnv *jni,
                                         jthread thread, jobject object,
                                         jclass object_klass, jlong size);
};

#endif // _OBJECTSAMPLER_H
