/*
 * Copyright 2017 Andrei Pangin
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

#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H

#include <cstring>
#include <stddef.h>
#include <string>
#include <vector>

#include "arch.h"

const long DEFAULT_CPU_INTERVAL = 10 * 1000 * 1000;  // 10 ms
const long DEFAULT_WALL_INTERVAL = 50 * 1000 * 1000; // 50 ms
const long DEFAULT_ALLOC_INTERVAL = 524287;          // 512 KiB
const int DEFAULT_WALL_THREADS_PER_TICK = 16;
const int DEFAULT_JSTACKDEPTH = 2048;

// Every constant below is a provisional default pending empirical tuning -
// none are backed by a benchmark run against this codebase; replacing them
// with measured values is outstanding JMH/async-profiler benchmark work.
// Per-constant notes only carry what a name does not already say.
//
// Hop cap: mirrors HotSpot's own JFR leak-profiler chain cap (~200 hops,
// split 100/100 from leaf and from root) - the closest real-world precedent
// for a referrer-type chain length.
// Sub-option bitmask for the auto-tuner: tracks which referencechains
// sub-options were explicitly set by the operator, so the auto-tuner
// only overrides defaults that weren't.
constexpr u8 REF_CHAINS_TUNED_HOP_CAP = 1 << 0;
constexpr u8 REF_CHAINS_TUNED_BUDGET = 1 << 1;
constexpr u8 REF_CHAINS_TUNED_TTL = 1 << 2;
constexpr u8 REF_CHAINS_TUNED_FRONTIER_CAP = 1 << 3;
constexpr u8 REF_CHAINS_TUNED_PAUSE_TARGET = 1 << 4;
constexpr u8 REF_CHAINS_TUNED_PAIN_BUDGET = 1 << 5;
constexpr u8 REF_CHAINS_TUNED_FIRST_PASS_BUDGET = 1 << 6;

const int DEFAULT_REFERENCE_CHAINS_HOP_CAP = 200;
// Per-pass edge budget: a round middle value keeping a single
// FollowReferences-triggered safepoint short without forcing an impractical
// number of passes.
const int DEFAULT_REFERENCE_CHAINS_BUDGET = 1000;      // edges expanded per BFS pass
// Per-search TTL: bounds a slow or stalled search to a human-noticeable
// lifetime.
const long DEFAULT_REFERENCE_CHAINS_TTL_MS = 60000;    // per-search wall-clock TTL
// Frontier-size cap: same order of magnitude as LivenessTracker's tuned
// ceiling (MAX_TRACKING_TABLE_SIZE = 262144, livenessTracker.h), quartered -
// a frontier entry is smaller but per-hop fan-out can be large. Conservative
// guess, pending a frontier peak-occupancy measurement.
const int DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP = 65536; // max live frontier entries per search
// Pause-time-SLO ceiling (pause-time pacing controller): target ceiling,
// per pass, on wall-clock time spent inside the safepoint-triggering
// FollowReferences/GetObjectsWithTags call
// the pause-time pacing controller adapts the effective budget/cadence toward.
const long DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS = 50; // ms per pass
// Pain budget refill rate (the restarted-search pain budget):
// percent (1 = 1%) of wall-clock time a *restarted* search may spend inside
// safepointing calls, on average, before a later restart waits for the
// previous search's debt to drain.
const int DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT = 1;
// First-pass edge budget override for the search's one-and-only root-seeded
// FollowReferences call: unlike the per-pass budget, this spends once per
// search, so a much larger one-time ceiling is affordable. 0 means no
// override - the engine auto-scales it from the per-pass budget at startup.
const int DEFAULT_REFERENCE_CHAINS_FIRST_PASS_BUDGET = 0;
const int MAX_REFERENCE_CHAINS_FIRST_PASS_BUDGET =
    DEFAULT_REFERENCE_CHAINS_BUDGET * 1000;
// Upper clamps: large enough that no legitimate configuration hits them,
// small enough to fail a mistyped value safely instead of feeding it into a
// loop bound or an allocation.
const int MAX_REFERENCE_CHAINS_HOP_CAP = DEFAULT_REFERENCE_CHAINS_HOP_CAP * 1000;
const int MAX_REFERENCE_CHAINS_BUDGET = DEFAULT_REFERENCE_CHAINS_BUDGET * 1000;
const int MAX_REFERENCE_CHAINS_FRONTIER_CAP =
    DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP * 1000;

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
  CSTACK_DEFAULT,  // use perf_event_open stack if available or Frame Pointer links otherwise
  CSTACK_NO,       // do not collect native frames
  CSTACK_FP,       // walk stack using Frame Pointer links
  CSTACK_DWARF,    // use DWARF unwinding info from .eh_frame section
  CSTACK_LBR,      // Last Branch Record hardware capability
  CSTACK_VM        // unwind using HotSpot VMStructs (vmx mode uses CSTACK_VM with _features.mixed=1)
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

enum Clock {
    CLK_DEFAULT,
    CLK_TSC,
    CLK_MONOTONIC
};

// Keep this in sync with JfrSync.java
enum EventMask {
    EM_CPU          = 1,
    EM_ALLOC        = 2,
    EM_LOCK         = 4,
    EM_WALL         = 8,
    EM_NATIVEMEM    = 16,
    EM_METHOD_TRACE = 32,
    EM_NATIVESOCKET = 64
};
constexpr int EVENT_MASK_SIZE = 7;

struct StackWalkFeatures {
    // Deprecated stack recovery techniques used to workaround AsyncGetCallTrace flaws
    unsigned short unknown_java  : 1;
    unsigned short unwind_stub   : 1;
    unsigned short unwind_comp   : 1;
    unsigned short unwind_native : 1;
    unsigned short java_anchor   : 1;
    unsigned short gc_traces     : 1;

    // Common features
    unsigned short stats         : 1;  // collect stack walking duration statistics

    // Additional HotSpot-specific features
    unsigned short jnienv        : 1;  // verify JNIEnv* obtained using VMStructs
    unsigned short probe_sp      : 1;  // when AsyncGetCallTrace fails, adjust SP and retry
    unsigned short mixed         : 1;  // mixed stack traces with Java and native frames interleaved
    unsigned short vtable_target : 1;  // show receiver classes of vtable/itable stubs
    unsigned short comp_task     : 1;  // display current compilation task for JIT threads
    unsigned short pc_addr       : 1;  // record exact PC address for each sample
    unsigned short carrier_frames: 1;  // walk through VT continuation boundary to carrier frames (enabled automatically with cstack=vmx)
    unsigned short _padding      : 2;  // pad structure to 16 bits
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
  bool _wall_precheck;
  int _wall_threads_per_tick;
  WallclockSampler _wallclock_sampler;
  long _memory;
  bool _record_allocations;
  bool _record_liveness;
  double _live_samples_ratio;
  bool _record_heap_usage;
  bool _gc_generations;
  // Reference-chain tracking. Read by the reference-chain engine at startup
  // to size the frontier table and seed the per-search hop/budget/TTL
  // tunables and the pause-time-SLO ceiling its pacing controller adapts
  // the effective budget/cadence toward.
  bool _reference_chains;
  int _reference_chains_hop_cap;
  int _reference_chains_budget;
  long _reference_chains_ttl_ms;
  int _reference_chains_frontier_cap;
  long _reference_chains_pause_target_ms;
  int _reference_chains_pain_budget_percent;
  int _reference_chains_first_pass_budget;
  // Bitmask of REF_CHAINS_TUNED_*: which sub-options were explicitly
  // set by the operator, so the auto-tuner knows which defaults it may
  // override. 0 = all defaults, none explicitly set.
  u8 _reference_chains_tuned_mask;
  // Explicit opt-in for the legacy whole-graph JVMTI FollowReferences walk.
  long _nativemem;
  int  _jstackdepth;
  int _safe_mode;
  StackWalkFeatures _features;
  const char* _file;
  const char* _log;
  const char* _loglevel;
  const char* _unknown_arg;
  const char* _filter;
  CStack _cstack;
  Clock _clock;
  int _jfr_options;
  std::vector<std::string> _context_attributes;
  bool _lightweight;
  bool _enable_method_cleanup;
  bool _remote_symbolication;  // Enable remote symbolication for native frames
  bool _skip_sanity_checks;
  bool _jvmtistacks;           // Delegate CPU/wall stack walks to HotSpot JFR RequestStackTrace extension
  bool _nativesocket;
  long _nativesocket_interval;  // initial sampling period in nanoseconds; 0 = engine default
  bool _force_jmethodID;       // Load all jmethodIDs, true by default

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
        _wall_precheck(false),
        _wall_threads_per_tick(DEFAULT_WALL_THREADS_PER_TICK),
        _wallclock_sampler(ASGCT),
        _memory(-1),
        _record_allocations(false),
        _record_liveness(false),
        _live_samples_ratio(0.1), // default to liveness-tracking 10% of the allocation samples
        _record_heap_usage(false),
        _gc_generations(false),
        _reference_chains(false),
        _reference_chains_hop_cap(DEFAULT_REFERENCE_CHAINS_HOP_CAP),
        _reference_chains_budget(DEFAULT_REFERENCE_CHAINS_BUDGET),
        _reference_chains_ttl_ms(DEFAULT_REFERENCE_CHAINS_TTL_MS),
        _reference_chains_frontier_cap(DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP),
        _reference_chains_pause_target_ms(DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS),
        _reference_chains_pain_budget_percent(DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT),
        _reference_chains_first_pass_budget(DEFAULT_REFERENCE_CHAINS_FIRST_PASS_BUDGET),
        _reference_chains_tuned_mask(0),
        _nativemem(-1),
        _jstackdepth(DEFAULT_JSTACKDEPTH),
        _safe_mode(0),
        _features{1, 1, 1, 1, 1, 1},
        _file(NULL),
        _log(NULL),
        _loglevel(NULL),
        _unknown_arg(NULL),
        _filter(NULL),
        _cstack(CSTACK_DEFAULT),
        _clock(CLK_DEFAULT),
        _jfr_options(0),
        _context_attributes({}),
        _lightweight(false),
        _enable_method_cleanup(true),
        _remote_symbolication(false),
        _skip_sanity_checks(false),
        _jvmtistacks(false),
        _nativesocket(false),
        _nativesocket_interval(0),
        _force_jmethodID(true) {}

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
