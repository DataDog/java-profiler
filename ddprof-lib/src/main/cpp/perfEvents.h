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

#ifndef _PERFEVENTS_H
#define _PERFEVENTS_H

#ifdef __linux__

#include "arch.h"
#include "arguments.h"
#include "engine.h"
#include <signal.h>

class PerfEvent;
class PerfEventType;
class StackContext;

class PerfEvents : public Engine {
  friend class PerfEventsTestAccessor;

private:
  static bool _enabled;
  static int _max_events;
  static PerfEvent *_events;
  static PerfEventType *_event_type;
  static long _interval;
  static Ring _ring;
  static CStack _cstack;
  static bool _use_mmap_page;

  // cppcheck-suppress unusedPrivateFunction
  static u64 readCounter(siginfo_t *siginfo, void *ucontext);
  // cppcheck-suppress unusedPrivateFunction
  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);
  // Slot of tid in _events, or NULL when the table is NULL, being replaced,
  // or tid is out of range. For readers in signal context (walkKernel(),
  // resetBuffer()).
  static PerfEvent *eventFor(int tid);

  // Generation of the (_events, _max_events) pair; odd while resizeEvents()
  // replaces the table. eventFor() accepts a pair only from one even
  // generation.
  static unsigned int _events_gen;
  static void beginTableUpdate();
  static void endTableUpdate();
  // Replaces the tid-indexed table with one of max_events slots, after
  // releasing every fd and ring held by the old table. No-op when the size is
  // unchanged. On allocation failure leaves _events == NULL and
  // _max_events == -1 and returns false. Called only from sizeEventTable(),
  // with the Profiler's registration gates closed.
  bool resizeEvents(int max_events);
  // Sizes the table for start(), replacing it under a
  // Profiler::ThreadTablesFreeze only when the size changes.
  Error sizeEventTable(int max_events);

#ifdef UNIT_TEST
  // Stores fd and ring page into slot tid of the current table (test only).
  static void setSlotForTest(int tid, int fd, void *page);
  // Reads back the fd of slot tid of the current table (test only).
  static int slotFdForTest(int tid);
#endif

public:
  Error check(Arguments &args);
  Error start(Arguments &args);
  void stop();

  virtual int registerThread(int tid);
  virtual void unregisterThread(int tid);
  long interval() const { return _interval; }

  const char *name() { return "PerfEvents"; }

  static int walkKernel(int tid, const void **callchain, int max_depth,
                        StackContext *java_ctx);

  static void resetBuffer(int tid);

  static const char *getEventName(int event_id);

  // qsort() comparator for thread ids, used by start() to order the thread
  // list before matching it against tids. Public so tests can check it.
  static int compareTids(const void *a, const void *b);

  inline void enableEvents(bool enabled) {
    __atomic_store_n(&_enabled, enabled, __ATOMIC_RELEASE);
  }
};

#else

#include "engine.h"

class StackContext;

class PerfEvents : public Engine {
public:
  Error check(Arguments &args) {
    return Error("PerfEvents are unsupported on this platform");
  }

  Error start(Arguments &args) {
    return Error("PerfEvents are unsupported on this platform");
  }

  static int walkKernel(int tid, const void **callchain, int max_depth,
                        StackContext *java_ctx) {
    return 0;
  }

  inline void enableEvents(bool enabled) {}

  static void resetBuffer(int tid) {}

  static const char *getEventName(int event_id) { return NULL; }

  virtual int registerThread(int tid) { return -1; }
  virtual void unregisterThread(int tid) {}

  long interval() const { return -1; }
};

#endif // __linux__

#endif // _PERFEVENTS_H
