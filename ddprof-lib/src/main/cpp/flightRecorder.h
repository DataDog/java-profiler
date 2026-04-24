/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FLIGHTRECORDER_H
#define _FLIGHTRECORDER_H

#include <map>
#include <unordered_set>

#include <limits.h>
#include <string.h>

#include "arch.h"
#include "arguments.h"
#include "buffers.h"
#include "counters.h"
#include "dictionary.h"
#include "event.h"
#include "frame.h"
#include "jfrMetadata.h"
#include "log.h"
#include "methodInfo.h"
#include "mutex.h"
#include "objectSampler.h"
#include "threadFilter.h"
#include "threadIdTable.h"
#include "vmEntry.h"

const u64 MAX_JLONG = 0x7fffffffffffffffULL;
const u64 MIN_JLONG = 0x8000000000000000ULL;
const int MAX_JFR_EVENT_SIZE = 256;
const int JFR_EVENT_FLUSH_THRESHOLD = RECORDING_BUFFER_LIMIT;
const int MAX_VAR64_LENGTH = 10;
const int MAX_VAR32_LENGTH = 5;

#ifndef CONCURRENCY_LEVEL
const int CONCURRENCY_LEVEL = 16;
#endif
const u16 ACC_SYNTHETIC = 0x1000;
const u16 ACC_BRIDGE = 0x0040;
const u16 ACC_HIDDEN = ACC_SYNTHETIC | ACC_BRIDGE;

class Profiler;
class Lookup;

struct CpuTime {
  u64 real;
  u64 user;
  u64 system;
};

struct CpuTimes {
  CpuTime proc;
  CpuTime total;
};
class Recording {
  friend ObjectSampler;
  friend Profiler;
  friend Lookup;

private:
  static char *_agent_properties;
  static char *_jvm_args;
  static char *_jvm_flags;
  static char *_java_command;

  RecordingBuffer _buf[CONCURRENCY_LEVEL];
  // we have several tables to avoid lock contention
  // we have a second dimension to allow a switch in the active table
  ThreadIdTable _thread_ids[CONCURRENCY_LEVEL][2];
  std::atomic<int> _active_index{0};  // 0 or 1 globally

  int _fd;
  off_t _chunk_start;
  MethodMap _method_map;

  Arguments _args;
  u64 _start_time;
  u64 _recording_start_time;
  u64 _start_ticks;
  u64 _recording_start_ticks;
  u64 _stop_time;
  u64 _stop_ticks;

  u64 _base_id;
  u64 _bytes_written;

  int _tid;
  int _available_processors;
  int _recorded_lib_count;

  bool _cpu_monitor_enabled;
  Buffer _cpu_monitor_buf;
  CpuTimes _last_times;

  static float ratio(float value) {
    return value < 0 ? 0 : value > 1 ? 1 : value;
  }

public:
  Recording(int fd, Arguments &args);
  ~Recording();

  void copyTo(int target_fd);
  off_t finishChunk();

  off_t finishChunk(bool end_recording);
  void switchChunk(int fd);

  void cpuMonitorCycle();
  void appendRecording(const char *target_file, size_t size);

  RecordingBuffer *buffer(int lock_index);

  bool parseAgentProperties();

  void flush(Buffer *buf);
  void flushIfNeeded(Buffer *buf, int limit = JFR_EVENT_FLUSH_THRESHOLD);
  void writeHeader(Buffer *buf);

  void writeMetadata(Buffer *buf);

  void writeElement(Buffer *buf, const Element *e);

  void writeEventSizePrefix(Buffer *buf, int start);

  void writeRecordingInfo(Buffer *buf);

  void writeSettings(Buffer *buf, Arguments &args);

  void writeStringSetting(Buffer *buf, int category, const char *key,
                          const char *value);

  void writeBoolSetting(Buffer *buf, int category, const char *key, bool value);

  void writeIntSetting(Buffer *buf, int category, const char *key,
                       long long value);
  void writeListSetting(Buffer *buf, int category, const char *key,
                        const char *base, int offset);

  void writeDatadogSetting(Buffer *buf, int length, const char *name,
                           const char *value, const char *unit);

  void writeDatadogProfilerConfig(Buffer *buf, long cpuInterval,
                                  long wallInterval, long allocInterval,
                                  long memleakInterval, long memleakCapacity,
                                  double memleakRatio, bool gcGenerations,
                                  int modeMask, const char *cpuEngine);

  void writeHeapUsage(Buffer *buf, long value, bool live);
  void writeOsCpuInfo(Buffer *buf);
  void writeJvmInfo(Buffer *buf);
  void writeSystemProperties(Buffer *buf);
  void writeNativeLibraries(Buffer *buf);
  void writeCpool(Buffer *buf);

  void writeFrameTypes(Buffer *buf);

  void writeThreadStates(Buffer *buf);

  void writeExecutionModes(Buffer *buf);
  void writeThreads(Buffer *buf);

  void writeStackTraces(Buffer *buf, Lookup *lookup);

  void writeMethods(Buffer *buf, Lookup *lookup);

  void writeClasses(Buffer *buf, Lookup *lookup);

  void writePackages(Buffer *buf, Lookup *lookup);

  void writeConstantPoolSection(Buffer *buf, JfrType type,
                                std::map<u32, const char *> &constants);

  void writeConstantPoolSection(Buffer *buf, JfrType type,
                                Dictionary *dictionary);

  void writeLogLevels(Buffer *buf);

  void writeCounters(Buffer *buf);

  void writeUnwindFailures(Buffer *buf);

  void writeContextSnapshot(Buffer *buf, Context &context);
  void writeCurrentContext(Buffer *buf);

  void recordExecutionSample(Buffer *buf, int tid, u64 call_trace_id,
                             ExecutionEvent *event);
  void recordMethodSample(Buffer *buf, int tid, u64 call_trace_id,
                          ExecutionEvent *event);
  void recordWallClockEpoch(Buffer *buf, WallClockEpochEvent *event);
  void recordTraceRoot(Buffer *buf, int tid, TraceRootEvent *event);
  void recordQueueTime(Buffer *buf, int tid, QueueTimeEvent *event);
  void recordAllocation(RecordingBuffer *buf, int tid, u64 call_trace_id,
                        AllocEvent *event);
  void recordMallocSample(Buffer *buf, int tid, u64 call_trace_id,
                          MallocEvent *event);
  void recordHeapLiveObject(Buffer *buf, int tid, u64 call_trace_id,
                            ObjectLivenessEvent *event);
  void recordMonitorBlocked(Buffer *buf, int tid, u64 call_trace_id,
                            LockEvent *event);
  void recordThreadPark(Buffer *buf, int tid, u64 call_trace_id,
                        LockEvent *event);
  void recordCpuLoad(Buffer *buf, float proc_user, float proc_system,
                     float machine_total);

  void addThread(int lock_index, int tid);

private:
  void cleanupUnreferencedMethods();
};
class FlightRecorder {
  friend Profiler;

private:
  std::string _filename;
  Arguments _args;

  SpinLock _rec_lock;
  Recording* _rec;

  Error newRecording(bool reset);

public:
  FlightRecorder() : _rec(NULL) {}
  Error start(Arguments &args, bool reset);
  void stop();
  Error dump(const char *filename, const int length);
  void flush();
  void wallClockEpoch(int lock_index, WallClockEpochEvent *event);
  void recordTraceRoot(int lock_index, int tid, TraceRootEvent *event);
  void recordQueueTime(int lock_index, int tid, QueueTimeEvent *event);

  bool active() const { return _rec != NULL; }

  void recordEvent(int lock_index, int tid, u64 call_trace_id, int event_type,
                   Event *event);

  void recordLog(LogLevel level, const char *message, size_t len);

  void recordDatadogSetting(int lock_index, int length, const char *name,
                            const char *value, const char *unit);

  void recordHeapUsage(int lock_index, long value, bool live);
};

#endif // _FLIGHTRECORDER_H
