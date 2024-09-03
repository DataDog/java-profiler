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

#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H

#include <cstring>
#include <stddef.h>
#include <string>
#include <vector>

const long DEFAULT_CPU_INTERVAL = 10 * 1000 * 1000;  // 10 ms
const long DEFAULT_WALL_INTERVAL = 50 * 1000 * 1000; // 50 ms
const long DEFAULT_ALLOC_INTERVAL = 524287;          // 512 KiB
const int DEFAULT_WALL_THREADS_PER_TICK = 16;
const int DEFAULT_JSTACKDEPTH = 2048;

const char *const EVENT_NOOP = "noop";
const char *const EVENT_CPU = "cpu";
const char *const EVENT_ALLOC = "alloc";
const char *const EVENT_WALL = "wall";
const char *const EVENT_ITIMER = "itimer";
const char *const EVENT_CTIMER = "ctimer";

enum Action {
  ACTION_NONE,
  ACTION_START,
  ACTION_RESUME,
  ACTION_STOP,
  ACTION_CHECK,
  ACTION_STATUS,
  ACTION_LIST,
  ACTION_VERSION
};

enum Ring {
  RING_KERNEL = 1,
  RING_USER = 1 << 1,
  RING_ANY = RING_KERNEL | RING_USER,
};

enum Style {
  STYLE_SIMPLE = 1,
  STYLE_DOTTED = 2,
  STYLE_SIGNATURES = 4,
  STYLE_ANNOTATE = 8,
  STYLE_LIB_NAMES = 16
};

enum CStack {
  CSTACK_DEFAULT,
  CSTACK_NO,
  CSTACK_FP,
  CSTACK_DWARF,
  CSTACK_LBR,
  CSTACK_VM
};

enum Output { OUTPUT_NONE, OUTPUT_COLLAPSED, OUTPUT_JFR };

enum JfrOption {
  NO_SYSTEM_INFO = 0x1,
  NO_SYSTEM_PROPS = 0x2,
  NO_NATIVE_LIBS = 0x4,
  NO_CPU_LOAD = 0x8,

  JFR_SYNC_OPTS =
      NO_SYSTEM_INFO | NO_SYSTEM_PROPS | NO_NATIVE_LIBS | NO_CPU_LOAD
};

enum WallclockSampler {
    ASGCT,
    JVMTI
};

struct Multiplier {
  char symbol;
  long multiplier;
};

class Error {
private:
  const char *_message;

public:
  static const Error OK;

  explicit Error(const char *message) : _message(message) {}

  const char *message() { return _message; }

  operator bool() { return _message != NULL; }
};

class Arguments {
private:
  char *_buf;
  bool _shared;
  bool _persistent;
  const char *expandFilePattern(const char *pattern);
  static long long hash(const char *arg);
  static long parseUnits(const char *str, const Multiplier *multipliers);
  static bool isCpuEvent(const char *event) {
    // event == NULL will default to EVENT_CPU
    return event == NULL || strcmp(event, EVENT_CPU) == 0 ||
           strcmp(event, EVENT_ITIMER) == 0 || strcmp(event, EVENT_CTIMER) == 0;
  }

public:
  Action _action;
  Ring _ring;
  const char *_event;
  long _interval;
  long _cpu;
  long _wall;
  bool _wall_collapsing;
  int _wall_threads_per_tick;
  WallclockSampler _wallclock_sampler;
    long _memory;
    bool _record_allocations;
    bool _record_liveness;
    double _live_samples_ratio;
    bool _record_heap_usage;
    bool _gc_generations;
    int  _jstackdepth;
    int _safe_mode;
    const char* _file;
    const char* _log;
    const char* _loglevel;
    const char* _unknown_arg;
    const char* _filter;
    CStack _cstack;
    int _jfr_options;
    std::vector<std::string> _context_attributes;
    bool _lightweight;

  Arguments(bool persistent = false)
      : _buf(NULL),
        _shared(false),
        _persistent(persistent),
        _action(ACTION_NONE),
        _ring(RING_ANY),
        _event(NULL),
        _interval(0),
        _cpu(-1),
        _wall(-1),
        _wall_collapsing(false),
        _wall_threads_per_tick(DEFAULT_WALL_THREADS_PER_TICK),
        _memory(-1),
        _record_allocations(false),
        _record_liveness(false),
        _live_samples_ratio(0.1), // default to liveness-tracking 10% of the allocation samples
        _record_heap_usage(false),
        _gc_generations(false),
        _jstackdepth(DEFAULT_JSTACKDEPTH),
        _safe_mode(0),
        _file(NULL),
        _log(NULL),
        _loglevel(NULL),
        _unknown_arg(NULL),
        _filter(NULL),
        _cstack(CSTACK_DEFAULT),
        _jfr_options(0),
        _context_attributes({}),
        _lightweight(false),
        _wallclock_sampler(ASGCT) {}

  ~Arguments();

  void save(Arguments &other);

  Error parse(const char *args);

  const char *file();

  bool hasOption(JfrOption option) const {
    return (_jfr_options & option) != 0;
  }

  long cpuSamplerInterval() const {
    return isCpuEvent(_event) ? (_cpu > 0        ? _cpu
                                 : _interval > 0 ? _interval
                                                 : DEFAULT_CPU_INTERVAL)
                              : 0;
  }

  friend class FrameName;
  friend class Recording;
};

#endif // _ARGUMENTS_H
