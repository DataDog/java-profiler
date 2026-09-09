/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FLIGHTRECORDER_H
#define _FLIGHTRECORDER_H

#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <limits.h>
#include <string.h>

#include "arch.h"
#include "arguments.h"
#include "buffers.h"
#include "common.h"
#include "countingAllocator.h"
#include "counters.h"
#include "nativeMem.h"
#include "dictionary.h"
#include "stringDictionary.h"
#include "event.h"
#include "frame.h"
#include "jfrMetadata.h"
#include "log.h"
#include "mutex.h"
#include "objectSampler.h"
#include "threadFilter.h"
#include "threadIdTable.h"
#include "vmEntry.h"

class VMSymbol;  // hotspot/vmStructs.h
class ProfiledThread;

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

class SharedLineNumberTable {
public:
  int _size;
  // The buffer jvmti->GetLineNumberTable() returned, held directly (not a
  // copy) and freed via jvmti->Deallocate() (see ~SharedLineNumberTable())
  // so native-memory-tracking accounting stays correct. Per the JVMTI spec
  // this array is a fresh, caller-owned allocation decoupled from the
  // Method's lifetime, so holding onto it is safe across class unload.
  jvmtiLineNumberEntry* _table;

  SharedLineNumberTable(int size, jvmtiLineNumberEntry *ptr) : _size(size), _table(ptr) {}
  ~SharedLineNumberTable();
};

class MethodInfo {
public:
  MethodInfo()
      : _mark(false), _is_entry(false), _referenced(false), _age(0), _key(0), _class(0),
        _name(0), _sig(0), _modifiers(0), _line_number_table(nullptr), _type() {}

  bool _mark;
  bool _is_entry;
  bool _referenced;  // Tracked during writeStackTraces() for cleanup
  int _age;          // Consecutive chunks without reference (0 = recently used)
  u32 _key;
  u32 _class;
  u32 _name;
  u32 _sig;
  jint _modifiers;
  std::shared_ptr<SharedLineNumberTable> _line_number_table;
  FrameTypeId _type;

  inline jint getLineNumber(jint bci);
  inline bool isHidden();
};

// MethodMap's key can be derived from 3 sources:
// 1) jmethodID for Java methods
// 2) void* address for native method names
// 3) Encoded RemoteFrameInfo
// The values of the keys are potentially overlapping, so we use 
// the highest 2 bits to distinguish them.
// Key encoding (top two bits):
//   00 - jmethodID
//   10 - void* address (native frame names)
//   01 - RemoteFrameInfo (packed remote symbolication)
//   11 - vtable_receiver class_id (BCI_VTABLE_RECEIVER frames)
class MethodMap
    : public std::map<unsigned long, MethodInfo, std::less<unsigned long>,
                       CountingAllocator<std::pair<const unsigned long, MethodInfo>,
                                          NM_METHOD_MAP>> {
public:
  static constexpr unsigned long ADDRESS_MARK = 0x8000000000000000ULL;
  static constexpr unsigned long REMOTE_FRAME_MARK = 0x4000000000000000ULL;
  static constexpr unsigned long VTABLE_RECEIVER_MARK = ADDRESS_MARK | REMOTE_FRAME_MARK;
  static constexpr unsigned long KEY_TYPE_MASK = ADDRESS_MARK | REMOTE_FRAME_MARK;

  MethodMap() {}

  static unsigned long makeKey(jmethodID method) {
    unsigned long key = (unsigned long)method;
    assert((key & KEY_TYPE_MASK) == 0);
    return key;
  }

  static unsigned long makeKey(const char* addr) {
    unsigned long key = (unsigned long)addr;
    assert((key & KEY_TYPE_MASK) == 0);
    return (key | ADDRESS_MARK);
  }

  static unsigned long makeKey(unsigned long packed_remote_frame) {
    unsigned long key = packed_remote_frame;
    assert((key & KEY_TYPE_MASK) == 0);
    return (key | REMOTE_FRAME_MARK);}

  // BCI_VTABLE_RECEIVER frames key by the resolved class_id (not by the
  // VMSymbol* captured at sample time), so two distinct Symbol addresses
  // for the same class name collapse to a single MethodInfo row.
  static unsigned long makeVTableReceiverKey(u32 class_id) {
    unsigned long key = (unsigned long)class_id;
    assert((key & KEY_TYPE_MASK) == 0);
    return (key | VTABLE_RECEIVER_MARK);
  }

  // JFR method-pool id allocator. Ids must be unique among the methods written
  // in a single chunk, but may be recycled once a method is erased by
  // cleanupUnreferencedMethods() — an erased method is never written again, so
  // its id is free for reuse. Recycling freed ids bounds the id range to the
  // peak number of live methods (keeping LEB128 encoding compact) while
  // guaranteeing no two live methods ever share an id. Id 0 stays reserved as
  // the "no entry" sentinel. Single-threaded: only touched on the dump thread
  // (allocId from resolveMethod under lockAll, freeId from
  // cleanupUnreferencedMethods under the recording lock).
  u32 allocId() {
    if (!_free_ids.empty()) {
      u32 id = _free_ids.back();
      _free_ids.pop_back();
      return id;
    }
    return ++_id_high_water;
  }

  void freeId(u32 id) {
    if (id != 0) {
      _free_ids.push_back(id);
    }
  }

  // Pool id for Lookup::_unknown_method, the shared row for frames that could
  // not be resolved. That row deliberately lives outside this map (see
  // Lookup::unknownMethod()), so it needs an id that no map entry can ever be
  // given: drawn from the same counter so it cannot collide, but drawn only
  // once for the life of the recording and never recycled, since
  // cleanupUnreferencedMethods() only ever erases -- and frees the ids of --
  // actual map entries.
  u32 unknownMethodId() {
    if (_unknown_method_id == 0) {
      _unknown_method_id = allocId();
    }
    return _unknown_method_id;
}

private:
  u32 _id_high_water = 0;
  u32 _unknown_method_id = 0;
  std::vector<u32> _free_ids;
};

class Recording {
  friend ObjectSampler;
  friend Profiler;
  friend Lookup;
  // Grants gtest access to the private countSerializableChildren() helper below,
  // since Recording itself can't be constructed in a plain gtest binary (its
  // constructor needs a live JVMTI environment). Same pattern as
  // VMTestAccessor/ProfilerTestAccessor in the test sources.
  friend class RecordingTestAccessor;

private:
  static char *_agent_properties;
  static char *_jvm_args;
  static char *_jvm_flags;
  static char *_java_command;

  // Determines how many of `children` writeElement() will actually serialize
  // at the given depth, applying the same null-child and depth-limit skip
  // rules the recursive writer uses. Both the child_count written to the
  // buffer and the recursion in writeElement() call this single function, so
  // the encoded count can never diverge from what actually gets serialized.
  static size_t countSerializableChildren(
      const std::vector<const Element *> &children, int depth);

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

  u64 _bytes_written;

  int _tid;
  int _available_processors;
  int _recorded_lib_count;

  bool _cpu_monitor_enabled;
  Buffer _cpu_monitor_buf;
  CpuTimes _last_times;

  // Per-category NativeMem state captured immediately AFTER writeCpool(), and
  // emitted by the following chunk.
  //
  // The chunk's own counters are necessarily sampled before serialization: the
  // chunk header records cpool_offset as the boundary between the event section
  // and the constant pool, so no event may be appended once writeCpool() has
  // run. But writeCpool() is where the method map is built and the dictionary
  // grows -- by two orders of magnitude in a large recording -- so a consumer
  // reading only the in-chunk values never sees the cost of serialization.
  //
  // The post-flush live values are the genuinely new signal here. The
  // post-flush max is NativeMem::max(cat), a lifetime monotonic high-water
  // mark that nothing resets in production, so it carries the same
  // cross-flush attribution ambiguity as native_mem_max_bytes -- a per-flush
  // peak can only be recovered by a consumer differencing
  // post_flush_max[N] against the in-chunk native_mem_max_bytes emitted in
  // chunk N.
  bool _has_post_flush;
  long long _post_flush_live[NM_NUM_CATEGORIES];
  long long _post_flush_max[NM_NUM_CATEGORIES];
  void capturePostFlushNativeMem();

  static float ratio(float value) {
    return value < 0 ? 0 : value > 1 ? 1 : value;
  }

public:
  Recording(int fd, Arguments &args);
  ~Recording();

  void copyTo(int target_fd);
  off_t finishChunk();

  off_t finishChunk(bool end_recording, bool do_cleanup = false);
  void switchChunk(int fd);

  void cpuMonitorCycle();
  void appendRecording(const char *target_file, size_t size);

  RecordingBuffer *buffer(int lock_index);

  bool parseAgentProperties();

  void flush(Buffer *buf);
  void flushIfNeeded(Buffer *buf, int limit = JFR_EVENT_FLUSH_THRESHOLD);
  void writeHeader(Buffer *buf);

  void writeMetadata(Buffer *buf);

  void writeElement(Buffer *buf, const Element *e, int depth = 0);

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
  // Writes the cpool checkpoint. Returns the number of pool sections actually
  // emitted (empty variable pools are skipped) and reports the byte offset of
  // the pool-count placeholder within the cpool via *count_offset_in_cpool, so
  // the caller can back-patch it flush-safe alongside the cpool size field.
  int writeCpool(Buffer *buf, int *count_offset_in_cpool);

  void writeFrameTypes(Buffer *buf);

  void writeThreadStates(Buffer *buf);

  void writeExecutionModes(Buffer *buf);
  // writeThreads always emits: _tid is inserted unconditionally so the thread
  // pool is never empty. The following variable-pool writers return 1 if a
  // section was emitted, 0 if the pool was empty and skipped.
  void writeThreads(Buffer *buf);

  int writeStackTraces(Buffer *buf, Lookup *lookup);

  int writeMethods(Buffer *buf, Lookup *lookup);

  int writeClasses(Buffer *buf, Lookup *lookup);

  int writePackages(Buffer *buf, Lookup *lookup);

  int writeConstantPoolSection(Buffer *buf, JfrType type,
                               std::map<u32, const char *> &constants);

  int writeConstantPoolSection(Buffer *buf, JfrType type,
                               Dictionary *dictionary);
  int writeConstantPoolSection(Buffer *buf, JfrType type,
                               StringDictionaryBuffer *buffer);

  void writeLogLevels(Buffer *buf);

  void writeCounters(Buffer *buf);

  void updateNativeMemStats();
  void writeNativeMem(Buffer *buf);

  void writeUnwindFailures(Buffer *buf);

  void writeContextSnapshot(Buffer *buf, Context &context);
  void writeCurrentContext(Buffer *buf);

  void recordExecutionSample(Buffer *buf, int tid, u64 call_trace_id,
                             u64 correlation_id, ExecutionEvent *event);
  void recordMethodSample(Buffer *buf, int tid, u64 call_trace_id,
                          u64 correlation_id, ExecutionEvent *event);
  void recordWallClockEpoch(Buffer *buf, WallClockEpochEvent *event);
  void recordTraceRoot(Buffer *buf, int tid, TraceRootEvent *event);
  void recordQueueTime(Buffer *buf, int tid, QueueTimeEvent *event);
  void recordAllocation(RecordingBuffer *buf, int tid, u64 call_trace_id,
                        AllocEvent *event);
  void recordMallocSample(Buffer *buf, int tid, u64 call_trace_id,
                          MallocEvent *event);
  void recordNativeSocketSample(Buffer *buf, int tid, u64 call_trace_id,
                                NativeSocketEvent *event);
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

class ResolveMethodState;
class Lookup {
public:
  Recording *_rec;
  MethodMap *_method_map;
  StringDictionary *_classes;
  // Per-dump VMSymbol* -> resolved class_id cache for BCI_VTABLE_RECEIVER
  // frames. Two purposes: (1) amortise the SafeAccess work to once per
  // distinct Symbol pointer per dump; (2) the resolved class_id is used
  // as the MethodMap key, so distinct Symbol* addresses for the same
  // class name (class unload/reload mid-chunk) collapse to a single
  // MethodInfo row.
  std::unordered_map<void*, u32, std::hash<void*>, std::equal_to<void*>,
                      CountingAllocator<std::pair<void* const, u32>, NM_JFR_BUFFERS>>
      _vtable_receiver_cache;
  Dictionary _packages;
  Dictionary _symbols;

  // The single row every frame that could not be resolved collapses onto.
  //
  // Deliberately NOT a MethodMap entry: resolveMethod()'s siglongjmp landing pad
  // hands this row back with crash protection already disarmed, so it must be
  // reachable without touching the map, whose operator[] allocates a node and
  // can throw std::bad_alloc.
  //
  // Because it is outside the map, the map walk in writeMethods() cannot see it,
  // so writeMethods() emits it separately. It has to reach the method pool:
  // writeStackTraces() writes its _key for every frame that resolved to it, and
  // a _key with no matching pool entry is a dangling reference in the chunk.
  // Public for that reason, matching _method_map/_symbols above.
  MethodInfo _unknown_method;

private:
  void fillNativeMethodInfo(MethodInfo *mi, const char *name,
                            const char *lib_name, ResolveMethodState& state);
  void fillRemoteFrameInfo(MethodInfo *mi, const RemoteFrameInfo *rfi);
  void cutArguments(char *func);
  // Returns false without writing any of mi's fields when there was nothing
  // to fill (JNI PushLocalFrame failed, or the JVM isn't in JVMTI_PHASE_START/
  // JVMTI_PHASE_LIVE) -- callers must not mark/allocate a key for mi in that
  // case. Every other path (including the "<unloaded>" stale-jmethodID
  // sentinel) fully populates mi and returns true.
  bool fillJavaMethodInfo(MethodInfo *mi, jmethodID method, bool first_time, ResolveMethodState& state);
  bool has_prefix(const char *str, const char *prefix) const {
    return strncmp(str, prefix, strlen(prefix)) == 0;
  }
  // Length-bounded variant for buffers that may not be NUL-terminated.
  bool has_prefix_n(const char *buf, size_t buf_len, const char *prefix) const {
    size_t plen = strlen(prefix);
    return buf_len >= plen && strncmp(buf, prefix, plen) == 0;
  }

  // Resolves a VMSymbol* captured at sample time (BCI_VTABLE_RECEIVER) into a
  // class id in _classes, applying the synthetic-accessor/LambdaForm
  // normalisation inline. Crash-safe under concurrent class unloading: all
  // reads of the Symbol go through SafeAccess (safefetch + bounded copy), so
  // a Symbol freed and its page unmapped between sample and dump cannot
  // SIGSEGV the dump thread. On success returns true and fills *out_class_id
  // with the normalised class id. `buf` is a working area used internally;
  // its contents on return are unspecified.
  bool resolveVTableReceiver(VMSymbol *sym, char *buf, size_t bufsize,
                             u32 *out_class_id);

  // Cache wrapper: look up Symbol* in _vtable_receiver_cache; on miss,
  // resolve via resolveVTableReceiver and cache the result. On any
  // resolution failure (SafeAccess fault, length out of range, non-printable
  // bytes) returns the sentinel "<unresolved_vtable_receiver>" class_id and
  // increments VTABLE_RECEIVER_RESOLVE_FAILED.
  u32 resolveVTableReceiverCached(void *sym);

  // The MethodMap entry `frame` belongs to. Factored out so resolveMethod()'s
  // unprotected fast path and fillMethod()'s protected slow path can never
  // disagree about which entry a frame maps to -- ASGCT_CallFrame's method_id /
  // native_function_name / packed_remote_frame / method fields are a union, so
  // the bci branching below is the only thing that gives the payload a meaning.
  //
  // Reads the union's *value* only: MethodMap::makeKey() hashes a pointer, it
  // never dereferences it. So for every bci except BCI_VTABLE_RECEIVER -- whose
  // class_id the caller must resolve from a VMSymbol* first -- computing a key
  // touches no VM metadata and cannot fault.
  unsigned long methodKey(const ASGCT_CallFrame &frame, jmethodID method_id,
                          jint bci, u32 vtable_class_id);
  // Resolves and fills in the MethodInfo for `frame`. This is the part that
  // reads VM metadata and may therefore fault; resolveMethod() wraps it in the
  // sigsetjmp/siglongjmp window.
  MethodInfo *fillMethod(ASGCT_CallFrame &frame, jmethodID method_id, jint bci,
                         ProfiledThread* const prof_thread);

  // Materializes _unknown_method for this dump (filling it on first use) and
  // returns it.
  MethodInfo *unknownMethod();

public:
  Lookup(Recording *rec, MethodMap *method_map, StringDictionary *classes)
      : _rec(rec), _method_map(method_map), _classes(classes), _packages(),
        _symbols() {}

  MethodInfo *resolveMethod(ASGCT_CallFrame &frame);
  u32 getPackage(const char *class_name);
  u32 getSymbol(const char *name);
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
  void wallClockEpoch(int lock_index, WallClockEpochEvent *event);
  void recordTraceRoot(int lock_index, int tid, TraceRootEvent *event);
  void recordQueueTime(int lock_index, int tid, QueueTimeEvent *event);

  bool active() const { return _rec != NULL; }

  bool recordEvent(int lock_index, int tid, u64 call_trace_id, int event_type,
                   Event *event);

  // Emit a BCI_CPU / BCI_WALL sample with no stack-trace attached to our
  // recording. `correlation_id` is the same jlong passed to the HotSpot
  // RequestStackTrace extension so downstream tooling can join our event with
  // the JVM-emitted jdk.StackTraceRequest.
  bool recordEventDelegated(int lock_index, int tid, u64 correlation_id,
                            int event_type, Event *event);

  void recordLog(LogLevel level, const char *message, size_t len);

  void recordDatadogSetting(int lock_index, int length, const char *name,
                            const char *value, const char *unit);

  void recordHeapUsage(int lock_index, long value, bool live);
};

#endif // _FLIGHTRECORDER_H
