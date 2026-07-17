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

const long DEFAULT_CPU_INTERVAL = 10 * 1000 * 1000;  // 10 ms
const long DEFAULT_WALL_INTERVAL = 50 * 1000 * 1000; // 50 ms
const long DEFAULT_ALLOC_INTERVAL = 524287;          // 512 KiB
const int DEFAULT_WALL_THREADS_PER_TICK = 16;
const int DEFAULT_JSTACKDEPTH = 2048;

// Every constant below is a provisional default pending empirical
// tuning (see doc/architecture/LiveHeapReferenceChains-ImplementationPlan.md)
// - none of these values are backed by a benchmark run against this
// codebase. Each is chosen conservatively from cited precedent or from the
// shape of an existing, already-tuned subsystem, per the rationale below;
// a future JMH/async-profiler benchmark matrix (see
// doc/architecture/LiveHeapReferenceChains-BenchmarkPlan.md) is the intended
// path to replacing them with measured values.
//
// Hop cap: mirrors HotSpot's own JFR leak-profiler chain cap (~200 hops,
// split 100/100 from leaf and from root), cited in
// doc/architecture/LiveHeapReferenceChains.md's "Approach B" section - the
// closest real-world precedent for "how many hops does a referrer-type
// chain typically need" that this codebase can cite without measuring it
// itself.
const int DEFAULT_REFERENCE_CHAINS_HOP_CAP = 200;
// Per-pass edge budget: no cited precedent gives a number for this (JFR's
// leak profiler does not bound itself by a per-pass edge count - it runs to
// completion inside one already-scheduled GC pause). Chosen as a round,
// conservative middle value intended to keep a single FollowReferences-
// triggered safepoint short without so small a budget that a search needs
// an impractical number of passes to make progress. A future benchmark pass
// should measure per-pass wall-clock pause distribution at this value and adjust.
const int DEFAULT_REFERENCE_CHAINS_BUDGET = 1000;      // edges expanded per BFS pass
// Per-search TTL: a conservative round number (one minute) chosen so a
// slow-moving or stalled search is bounded to a human-noticeable but not
// excessive lifetime, in the absence of any measured "passes needed to
// reach a target sample at various depths" data (a future benchmark's stated goal).
const long DEFAULT_REFERENCE_CHAINS_TTL_MS = 60000;    // per-search wall-clock TTL
// Frontier-size cap: sized relative to LivenessTracker's own tuned ceiling
// (MAX_TRACKING_TABLE_SIZE = 262144, livenessTracker.h) rather than derived
// from any BFS-specific measurement - the design doc explicitly flags that
// LivenessTracker's allocation-sample-rate sizing formula does not transfer
// to a graph-search frontier (Open Question 2), so this only borrows the
// same order of magnitude, quartered as a conservative starting point since
// a FrontierEntry is smaller than a TrackingEntry but per-hop fan-out could
// still be large. Not a scaled/derived value - just a conservative guess
// pending a future frontier-table peak-occupancy measurement.
const int DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP = 65536; // max live frontier entries per search
// Pause-time-SLO ceiling (pause-time pacing controller, doc/architecture/
// LiveHeapReferenceChains-RemainingWorkPlan.md): target ceiling, per pass, on
// wall-clock time spent inside the safepoint-triggering
// FollowReferences/GetObjectsWithTags call
// (ReferenceChainTracker::updatePacing(), referenceChains.cpp). Like every
// other constant in this block this is a round, provisional default with no
// benchmark behind it - picking the real number is explicitly a future
// measurement question (design doc's Open Question 2), not a value to guess
// here; this only exists so the feedback loop this ceiling drives has
// something to target end-to-end before that measurement happens.
const long DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS = 5; // ms per pass
// Pain budget refill rate (ReferenceChainTracker::PainBudget, painBudget.h):
// the fraction of wall-clock time a *restarted* search is allowed to spend
// inside FollowReferences/GetObjectsWithTags safepoints, on average, before a
// later restart must wait for the debt from the previous search's cost to
// drain. Expressed as an integer percent (1 = 1%) for readability - see
// PainBudget's own header comment for why this single ratio needs no
// benchmark-derived tuning the way the per-pass constants above do, only a
// choice of how much background cost is acceptable. Round, provisional
// default like every other constant in this block.
const int DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT = 1;
// First-pass edge budget override: the search's one-and-only root-seeded
// FollowReferences(0, nullptr, nullptr, ...) call (ReferenceChainTracker::runPass()'s
// !_search_started branch) enumerates every GC root in one JVMTI-controlled
// traversal order and stops admitting once this budget is spent - any root
// FollowReferences had not yet reached is excluded from the frontier for the
// rest of that search (every later pass only expands forward from already-
// admitted frontier entries, see expandFrontier()'s own comment). Unlike
// DEFAULT_REFERENCE_CHAINS_BUDGET, which bounds every pass including the many
// cheap, per-node expansion passes that follow, this only ever spends once
// per search, so a much larger one-time ceiling is affordable. 0 (the
// default) means "no override - use the same budget as every other pass",
// preserving prior behavior for anyone not setting this explicitly.
const int DEFAULT_REFERENCE_CHAINS_FIRST_PASS_BUDGET = 0;
// Upper clamp for an explicit firstpassbudget override: like painbudget just
// above, firstpassbudget was previously only floored at 0 with no ceiling.
// Unlike painbudget (a percentage, naturally bounded at 100), this is a raw
// edge count, so the ceiling is expressed relative to
// DEFAULT_REFERENCE_CHAINS_BUDGET (the per-pass budget every later pass is
// bounded by) rather than as its own standalone guess: a generous but finite
// multiple still lets the one-time root pass be far larger than a normal
// pass (its intended purpose) while keeping an operator from disabling the
// safepoint-pause-bounding mechanism entirely for that first FollowReferences
// call.
const int MAX_REFERENCE_CHAINS_FIRST_PASS_BUDGET =
    DEFAULT_REFERENCE_CHAINS_BUDGET * 1000;

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
  // Reference-chain tracking (PROF-15341 - see
  // doc/architecture/LiveHeapReferenceChains-ImplementationPlan.md and
  // -RemainingWorkPlan.md). Read by ReferenceChainTracker::start()
  // (referenceChains.cpp) to size the frontier table and seed the per-search
  // hop/budget/TTL tunables and the pause-time-SLO ceiling that
  // updatePacing() adapts the effective budget/cadence toward.
  bool _reference_chains;
  int _reference_chains_hop_cap;
  int _reference_chains_budget;
  long _reference_chains_ttl_ms;
  int _reference_chains_frontier_cap;
  long _reference_chains_pause_target_ms;
  int _reference_chains_pain_budget_percent;
  int _reference_chains_first_pass_budget;
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
