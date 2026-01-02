/*
 * Copyright 2017 Andrei Pangin
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

#ifndef _ARGUMENTS_DD_H
#define _ARGUMENTS_DD_H

#include "arguments.h"
#include <cstring>
#include <stddef.h>
#include <string>
#include <vector>


const long DEFAULT_CPU_INTERVAL = 10 * 1000 * 1000;  // 10 ms
const long DEFAULT_WALL_INTERVAL = 50 * 1000 * 1000; // 50 ms
const int DEFAULT_WALL_THREADS_PER_TICK = 16;

namespace ddprof {

const char *const EVENT_NOOP = "noop";

enum Ring {
  RING_KERNEL = 1,
  RING_USER = 1 << 1,
  RING_ANY = RING_KERNEL | RING_USER,
};

enum WallclockSampler {
    ASGCT,
    JVMTI
};

class Arguments : public ::Arguments {
private:
  char *_buf;
  bool _shared;
  bool _persistent;

  const char *expandFilePattern(const char *pattern);
  static long long hash(const char *arg);
  static bool isCpuEvent(const char *event) {
    // event == NULL will default to EVENT_CPU
    return event == NULL || strcmp(event, EVENT_CPU) == 0 ||
           strcmp(event, EVENT_ITIMER) == 0 || strcmp(event, EVENT_CTIMER) == 0;
  }

public:
  // DD-specific members (in addition to inherited base class members)
  Ring _ring;
  long _cpu;
  bool _wall_collapsing;
  int _wall_threads_per_tick;
  WallclockSampler _wallclock_sampler;
  long _memory;
  bool _record_allocations;
  bool _record_liveness;
  double _live_samples_ratio;
  bool _record_heap_usage;
  bool _gc_generations;
  int _safe_mode;
  std::vector<std::string> _context_attributes;
  bool _lightweight;

  Arguments(bool persistent = false)
      : ::Arguments(),
        _buf(NULL),
        _shared(false),
        _persistent(persistent),
        _ring(RING_ANY),
        _cpu(-1),
        _wall_collapsing(false),
        _wall_threads_per_tick(DEFAULT_WALL_THREADS_PER_TICK),
        _wallclock_sampler(ASGCT),
        _memory(-1),
        _record_allocations(false),
        _record_liveness(false),
        _live_samples_ratio(0.1), // default to liveness-tracking 10% of the allocation samples
        _record_heap_usage(false),
        _gc_generations(false),
        _safe_mode(0),
        _context_attributes({}),
        _lightweight(false) {}

  ~Arguments();

  void save(Arguments &other);

  Error parse(const char *args);

  const char *file();

  // bool hasOption(JfrOption option) const {
  //   return (_jfr_options & option) != 0;
  // }

  long cpuSamplerInterval() const {
    return isCpuEvent(_event) ? (_cpu > 0        ? _cpu
                                 : _interval > 0 ? _interval
                                                 : DEFAULT_INTERVAL)
                              : 0;
  }

  static long parseUnits(const char* str, const Multiplier* multipliers);

  friend class FrameName;
  friend class Recording;
};

}  // namespace ddprof

#endif // _ARGUMENTS_DD_H
