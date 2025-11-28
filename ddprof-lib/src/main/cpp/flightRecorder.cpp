/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <assert.h>

#include "buffers.h"
#include "callTraceHashTable.h"
#include "context.h"
#include "counters.h"
#include "dictionary.h"
#include "flightRecorder.h"
#include "incbin.h"
#include "jfrMetadata.h"
#include "jniHelper.h"
#include "jvm.h"
#include "os_dd.h"
#include "profiler.h"
#include "rustDemangler.h"
#include "spinLock.h"
#include "unwindStats.h"
#include "symbols.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "vmStructs_dd.h"
#include <arpa/inet.h>
#include <cxxabi.h>
#include <errno.h>
#include <fcntl.h>
#include <map>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/utsname.h>
#include <vector>
#include <unistd.h>

static const char *const SETTING_RING[] = {NULL, "kernel", "user", "any"};
static const char *const SETTING_CSTACK[] = {NULL, "no", "fp", "dwarf", "lbr"};

static void deallocateLineNumberTable(void *ptr) {}

SharedLineNumberTable::~SharedLineNumberTable() {
  VM::jvmti()->Deallocate((unsigned char *)_ptr);
}

void Lookup::fillNativeMethodInfo(MethodInfo *mi, const char *name,
                                  const char *lib_name) {
  mi->_class = _classes->lookup("");
  // TODO return the library name once we figured out how to cooperate with the
  // backend
  //        if (lib_name == NULL) {
  //            mi->_class = _classes->lookup("");
  //        } else if (lib_name[0] == '[' && lib_name[1] != 0) {
  //            mi->_class = _classes->lookup(lib_name + 1, strlen(lib_name) -
  //            2);
  //        } else {
  //            mi->_class = _classes->lookup(lib_name);
  //        }

  mi->_modifiers = 0x100;
  mi->_line_number_table = nullptr;

  if (name[0] == '_' && name[1] == 'Z') {
    int status;
    char *demangled = abi::__cxa_demangle(name, NULL, NULL, &status);
    if (demangled != NULL) {
      cutArguments(demangled);
      mi->_sig = _symbols.lookup("()L;");
      mi->_type = FRAME_CPP;

      // Rust legacy demangling
      if (RustDemangler::is_probably_rust_legacy(demangled)) {
        std::string rust_demangled = RustDemangler::demangle(demangled);
        mi->_name = _symbols.lookup(rust_demangled.c_str());
      } else {
        mi->_name = _symbols.lookup(demangled);
      }
      free(demangled);
      return;
    }
  }

  size_t len = strlen(name);
  if (len >= 4 && strcmp(name + len - 4, "_[k]") == 0) {
    mi->_name = _symbols.lookup(name, len - 4);
    mi->_sig = _symbols.lookup("(Lk;)L;");
    mi->_type = FRAME_KERNEL;
  } else {
    mi->_name = _symbols.lookup(name);
    mi->_sig = _symbols.lookup("()L;");
    mi->_type = FRAME_NATIVE;
  }
}

void Lookup::cutArguments(char *func) {
  char *p = strrchr(func, ')');
  if (p == NULL)
    return;

  int balance = 1;
  while (--p > func) {
    if (*p == '(' && --balance == 0) {
      *p = 0;
      return;
    } else if (*p == ')') {
      balance++;
    }
  }
}

void Lookup::fillJavaMethodInfo(MethodInfo *mi, jmethodID method,
                                bool first_time) {
  JNIEnv *jni = VM::jni();
  if (jni->PushLocalFrame(64) != 0) {
    return;
  }
  jvmtiEnv *jvmti = VM::jvmti();

  jvmtiPhase phase;
  jclass method_class = NULL;
  // invariant: these strings must remain null, or be assigned by JVMTI
  char *class_name = nullptr;
  char *method_name = nullptr;
  char *method_sig = nullptr;
  u32 class_name_id = 0;
  u32 method_name_id = 0;
  u32 method_sig_id = 0;

  jint line_number_table_size = 0;
  jvmtiLineNumberEntry *line_number_table = NULL;

  jvmti->GetPhase(&phase);
  if ((phase & (JVMTI_PHASE_START | JVMTI_PHASE_LIVE)) != 0) {
    bool entry = false;
    if (ddprof::VMMethod::check_jmethodID(method) &&
        jvmti->GetMethodDeclaringClass(method, &method_class) == 0 &&
        // On some older versions of J9, the JVMTI call to GetMethodDeclaringClass will return OK = 0, but when a
        // classloader is unloaded they free all JNIIDs. This means that anyone holding on to a jmethodID is
        // pointing to corrupt data and the behaviour is undefined.
        // The behaviour is adjusted so that when asgct() is used or if `-XX:+KeepJNIIDs` is specified,
        // when a classloader is unloaded, the jmethodIDs are not freed, but instead marked as -1.
        // The nested check below is to mitigate these crashes.
        // In more recent versions, the condition above will short-circuit safely.
        ((!VM::isOpenJ9() || method_class != reinterpret_cast<jclass>(-1)) && jvmti->GetClassSignature(method_class, &class_name, NULL) == 0) &&
        jvmti->GetMethodName(method, &method_name, &method_sig, NULL) == 0) {

      if (first_time) {
        jvmti->GetLineNumberTable(method, &line_number_table_size,
                                  &line_number_table);
      }

      // Check if the frame is Thread.run or inherits from it
      if (strncmp(method_name, "run", 4) == 0 &&
          strncmp(method_sig, "()V", 3) == 0) {
        jclass Thread_class = jni->FindClass("java/lang/Thread");
        jmethodID equals = jni->GetMethodID(jni->FindClass("java/lang/Class"),
                                            "equals", "(Ljava/lang/Object;)Z");
        jclass klass = method_class;
        do {
          entry = jni->CallBooleanMethod(Thread_class, equals, klass);
          jniExceptionCheck(jni);
          if (entry) {
            break;
          }
        } while ((klass = jni->GetSuperclass(klass)) != NULL);
      } else if (strncmp(method_name, "main", 5) == 0 &&
                 strncmp(method_sig, "(Ljava/lang/String;)V", 21)) {
        // public static void main(String[] args) - 'public static' translates
        // to modifier bits 0 and 3, hence check for '9'
        entry = true;
      }

      // maybe we should store the lookups below in initialisation-time
      // constants...
      if (has_prefix(class_name,
                     "Ljdk/internal/reflect/GeneratedConstructorAccessor")) {
        class_name_id = _classes->lookup(
            "jdk/internal/reflect/GeneratedConstructorAccessor");
        method_name_id =
            _symbols.lookup("Object "
                            "jdk.internal.reflect.GeneratedConstructorAccessor."
                            "newInstance(Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name,
                            "Lsun/reflect/GeneratedConstructorAccessor")) {
        class_name_id =
            _classes->lookup("sun/reflect/GeneratedConstructorAccessor");
        method_name_id = _symbols.lookup(
            "Object "
            "sun.reflect.GeneratedConstructorAccessor.newInstance(Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name,
                            "Ljdk/internal/reflect/GeneratedMethodAccessor")) {
        class_name_id =
            _classes->lookup("jdk/internal/reflect.GeneratedMethodAccessor");
        method_name_id =
            _symbols.lookup("Object "
                            "jdk.internal.reflect.GeneratedMethodAccessor."
                            "invoke(Object, Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name,
                            "Lsun/reflect/GeneratedMethodAccessor")) {
        class_name_id = _classes->lookup("sun/reflect/GeneratedMethodAccessor");
        method_name_id = _symbols.lookup(
            "Object sun.reflect.GeneratedMethodAccessor.invoke(Object, "
            "Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name, "Ljava/lang/invoke/LambdaForm$")) {
        const int lambdaFormPrefixLength =
            strlen("Ljava/lang/invoke/LambdaForm$");
        // we want to normalise to java/lang/invoke/LambdaForm$MH,
        // java/lang/invoke/LambdaForm$DMH, java/lang/invoke/LambdaForm$BMH,
        if (has_prefix(class_name + lambdaFormPrefixLength, "MH")) {
          class_name_id = _classes->lookup("java/lang/invoke/LambdaForm$MH");
        } else if (has_prefix(class_name + lambdaFormPrefixLength, "BMH")) {
          class_name_id = _classes->lookup("java/lang/invoke/LambdaForm$BMH");
        } else if (has_prefix(class_name + lambdaFormPrefixLength, "DMH")) {
          class_name_id = _classes->lookup("java/lang/invoke/LambdaForm$DMH");
        } else {
          // don't recognise the suffix, so don't normalise
          class_name_id =
              _classes->lookup(class_name + 1, strlen(class_name) - 2);
        }
        method_name_id = _symbols.lookup(method_name);
        method_sig_id = _symbols.lookup(method_sig);
      } else {
        class_name_id =
            _classes->lookup(class_name + 1, strlen(class_name) - 2);
        method_name_id = _symbols.lookup(method_name);
        method_sig_id = _symbols.lookup(method_sig);
      }
    } else {
      Counters::increment(JMETHODID_SKIPPED);
      class_name_id = _classes->lookup("");
      method_name_id = _symbols.lookup("jvmtiError");
      method_sig_id = _symbols.lookup("()L;");
    }

    mi->_class = class_name_id;
    mi->_name = method_name_id;
    mi->_sig = method_sig_id;
    mi->_type = FRAME_INTERPRETED;
    mi->_is_entry = entry;
    if (line_number_table != nullptr) {
      mi->_line_number_table = std::make_shared<SharedLineNumberTable>(
          line_number_table_size, line_number_table);
    }

    // strings are null or came from JVMTI
    if (method_name) {
      jvmti->Deallocate((unsigned char *)method_name);
    }
    if (method_sig) {
      jvmti->Deallocate((unsigned char *)method_sig);
    }
    if (class_name) {
      jvmti->Deallocate((unsigned char *)class_name);
    }
  }
  jni->PopLocalFrame(NULL);
}

MethodInfo *Lookup::resolveMethod(ASGCT_CallFrame &frame) {
  jmethodID method = frame.method_id;
  MethodInfo *mi = &(*_method_map)[method];

  if (!mi->_mark) {
    mi->_mark = true;
    bool first_time = mi->_key == 0;
    if (first_time) {
      mi->_key = _method_map->size();
    }
    if (method == NULL) {
      fillNativeMethodInfo(mi, "unknown", NULL);
    } else if (frame.bci == BCI_ERROR) {
      fillNativeMethodInfo(mi, (const char *)method, NULL);
    } else if (frame.bci == BCI_NATIVE_FRAME) {
      const char *name = (const char *)method;
      fillNativeMethodInfo(mi, name,
                           Profiler::instance()->getLibraryName(name));
    } else {
      fillJavaMethodInfo(mi, method, first_time);
    }
  }

  return mi;
}

u32 Lookup::getPackage(const char *class_name) {
  const char *package = strrchr(class_name, '/');
  if (package == NULL) {
    return 0;
  }
  if (package[1] >= '0' && package[1] <= '9') {
    // Seems like a hidden or anonymous class, e.g. com/example/Foo/0x012345
    do {
      if (package == class_name)
        return 0;
    } while (*--package != '/');
  }
  if (class_name[0] == '[') {
    class_name = strchr(class_name, 'L') + 1;
  }
  return _packages.lookup(class_name, package - class_name);
}

u32 Lookup::getSymbol(const char *name) { return _symbols.lookup(name); }

char *Recording::_agent_properties = NULL;
char *Recording::_jvm_args = NULL;
char *Recording::_jvm_flags = NULL;
char *Recording::_java_command = NULL;

Recording::Recording(int fd, Arguments &args)
    : _fd(fd), _method_map() {

  args.save(_args);
  _chunk_start = lseek(_fd, 0, SEEK_END);
  _start_time = OS::micros();
  _start_ticks = TSC::ticks();
  _recording_start_time = _start_time;
  _recording_start_ticks = _start_ticks;
  _base_id = 0;
  _bytes_written = 0;

  _tid = OS::threadId();
  _active_index.store(0, std::memory_order_relaxed);

  VM::jvmti()->GetAvailableProcessors(&_available_processors);

  writeHeader(_buf);
  writeMetadata(_buf);
  writeSettings(_buf, args);
  if (!args.hasOption(NO_SYSTEM_INFO)) {
    writeOsCpuInfo(_buf);
    writeJvmInfo(_buf);
  }
  if (!args.hasOption(NO_SYSTEM_PROPS)) {
    writeSystemProperties(_buf);
  }
  if (!args.hasOption(NO_NATIVE_LIBS)) {
    _recorded_lib_count = 0;
    writeNativeLibraries(_buf);
  } else {
    _recorded_lib_count = -1;
  }
  flush(_buf);

  _cpu_monitor_enabled = !args.hasOption(NO_CPU_LOAD);
  if (_cpu_monitor_enabled) {
    _last_times.proc.real =
        OS::getProcessCpuTime(&_last_times.proc.user, &_last_times.proc.system);
    _last_times.total.real =
        OS::getTotalCpuTime(&_last_times.total.user, &_last_times.total.system);
  }
}

Recording::~Recording() {
  finishChunk(true);
  close(_fd);
}

void Recording::copyTo(int target_fd) {
  OS::copyFile(_fd, target_fd, 0, finishChunk(true));
}

off_t Recording::finishChunk() { return finishChunk(false); }

off_t Recording::finishChunk(bool end_recording) {
  jvmtiEnv *jvmti = VM::jvmti();
  JNIEnv *env = VM::jni();

  jclass *classes;
  jint count = 0;
  // obtaining the class list will create local refs to all loaded classes,
  // effectively preventing them from being unloaded while flushing
  jvmtiError err = jvmti->GetLoadedClasses(&count, &classes);

  flush(&_cpu_monitor_buf);

  writeNativeLibraries(_buf);

  const ObjectSampler *oSampler = ObjectSampler::instance();
  // write the engine dependent setting
  if (oSampler->_record_allocations) {
    writeIntSetting(_buf, T_ALLOC, "interval", oSampler->_interval);
  }
  if (oSampler->_record_liveness) {
    writeIntSetting(_buf, T_HEAP_LIVE_OBJECT, "interval", oSampler->_interval);
    writeIntSetting(_buf, T_HEAP_LIVE_OBJECT, "capacity",
                    LivenessTracker::instance()->_table_cap);
    writeIntSetting(_buf, T_HEAP_LIVE_OBJECT, "maximum capacity",
                    LivenessTracker::instance()->_table_max_cap);
  }
  writeDatadogProfilerConfig(
      _buf, Profiler::instance()->cpuEngine()->interval() / 1000000,
      Profiler::instance()->wallEngine()->interval() / 1000000,
      oSampler->_record_allocations ? oSampler->_interval : 0L,
      oSampler->_record_liveness ? oSampler->_interval : 0L,
      oSampler->_record_liveness ? LivenessTracker::instance()->_table_cap : 0L,
      oSampler->_record_liveness ? LivenessTracker::instance()->_subsample_ratio
                                 : 0.0,
      oSampler->_gc_generations, Profiler::instance()->eventMask(),
      Profiler::instance()->cpuEngine()->name());

  _stop_time = OS::micros();
  _stop_ticks = TSC::ticks();

  if (end_recording) {
    writeRecordingInfo(_buf);
  }

  // this will not report correct counts for any counters updated during writing
  // the constant pool because it just isn't worth the complexity and cost of
  // being able to account for the resources used in serialization during
  // serialization. Some counters we verify to balance (e.g. the anonymous
  // dictionaries) will be reported as positive, others (e.g. the classes
  // dictionary) will reflect the previous serialization. That is, some level of
  // familiarity with the code base will be required to use this diagnostic
  // information for now.
  writeCounters(_buf);

  // Keep a simple stats for where we failed to unwind
  // For the sakes of simplicity we are not keeping the count of failed unwinds which would also be
  // just 'eventually consistent' because we do not want to block the unwinding while writing out the stats.
  writeUnwindFailures(_buf);

  for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
    flush(&_buf[i]);
  }

  off_t cpool_offset = lseek(_fd, 0, SEEK_CUR);
  writeCpool(_buf);
  flush(_buf);

  off_t cpool_end = lseek(_fd, 0, SEEK_CUR);

  // Patch cpool size field
  _buf->putVar32(0, cpool_end - cpool_offset);
  ssize_t result = pwrite(_fd, _buf->data(), 5, cpool_offset);
  (void)result;

  off_t chunk_end = lseek(_fd, 0, SEEK_CUR);

  // // Workaround for JDK-8191415: compute actual TSC frequency, in case JFR is
  // wrong
  u64 tsc_frequency = TSC::frequency();
  // if (tsc_frequency > 1000000000) {
  //     tsc_frequency = (u64)(double(_stop_ticks - _start_ticks) /
  //     double(_stop_time - _start_time) * 1000000);
  // }

  // Patch chunk header
  _buf->put64(chunk_end - _chunk_start);
  _buf->put64(cpool_offset - _chunk_start);
  _buf->put64(68);
  _buf->put64(_start_time * 1000);
  _buf->put64((_stop_time - _start_time) * 1000);
  _buf->put64(_start_ticks);
  _buf->put64(tsc_frequency);
  result = pwrite(_fd, _buf->data(), 56, _chunk_start + 8);
  (void)result;

  OS::freePageCache(_fd, _chunk_start);

  _buf->reset();

  if (!err) {
    // delete all local references
    for (int i = 0; i < count; i++) {
      env->DeleteLocalRef((jobject)classes[i]);
    }
    // deallocate the class array
    jvmti->Deallocate((unsigned char *)classes);
  }
  return chunk_end;
}

void Recording::switchChunk(int fd) {
  _chunk_start = finishChunk(fd > -1);
  _start_time = _stop_time;
  _start_ticks = _stop_ticks;
  _bytes_written = 0;
  if (fd > -1) {
    // move the chunk to external file and reset the continuous recording file
    OS::copyFile(_fd, fd, 0, _chunk_start);
    ddprof::OS::truncateFile(_fd);
    // need to reset the file offset here
    _chunk_start = 0;
    _base_id = 0;
  } else {
    // same file, different logical chunk
    _base_id += 0x1000000;
  }

  writeHeader(_buf);
  writeMetadata(_buf);
  if (fd > -1) {
    // if the recording file is to be restarted write out all the info events
    // again
    writeSettings(_buf, _args);
    if (!_args.hasOption(NO_SYSTEM_INFO)) {
      writeOsCpuInfo(_buf);
      writeJvmInfo(_buf);
    }
    if (!_args.hasOption(NO_SYSTEM_PROPS)) {
      writeSystemProperties(_buf);
    }
    if (!_args.hasOption(NO_NATIVE_LIBS)) {
      _recorded_lib_count = 0;
      writeNativeLibraries(_buf);
    } else {
      _recorded_lib_count = -1;
    }
  }
  flush(_buf);
}

void Recording::cpuMonitorCycle() {
  if (!_cpu_monitor_enabled)
    return;

  CpuTimes times;
  times.proc.real = OS::getProcessCpuTime(&times.proc.user, &times.proc.system);
  times.total.real =
      OS::getTotalCpuTime(&times.total.user, &times.total.system);

  float proc_user = 0, proc_system = 0, machine_total = 0;

  if (times.proc.real != (u64)-1 && times.proc.real > _last_times.proc.real) {
    float delta =
        (times.proc.real - _last_times.proc.real) * _available_processors;
    proc_user = ratio((times.proc.user - _last_times.proc.user) / delta);
    proc_system = ratio((times.proc.system - _last_times.proc.system) / delta);
  }

  if (times.total.real != (u64)-1 &&
      times.total.real > _last_times.total.real) {
    float delta = times.total.real - _last_times.total.real;
    machine_total =
        ratio(((times.total.user + times.total.system) -
               (_last_times.total.user + _last_times.total.system)) /
              delta);
    if (machine_total < proc_user + proc_system) {
      machine_total = ratio(proc_user + proc_system);
    }
  }

  recordCpuLoad(&_cpu_monitor_buf, proc_user, proc_system, machine_total);
  flushIfNeeded(&_cpu_monitor_buf, BUFFER_LIMIT);

  _last_times = times;
}

void Recording::appendRecording(const char *target_file, size_t size) {
  int append_fd = open(target_file, O_WRONLY);
  if (append_fd >= 0) {
    lseek(append_fd, 0, SEEK_END);
    OS::copyFile(_fd, append_fd, 0, size);
    close(append_fd);
  } else {
    Log::warn("Failed to open JFR recording at %s: %s", target_file,
              strerror(errno));
  }
}

RecordingBuffer *Recording::buffer(int lock_index) { return &_buf[lock_index]; }

bool Recording::parseAgentProperties() {
  JNIEnv *env = VM::jni();
  jclass vm_support = env->FindClass("jdk/internal/vm/VMSupport");
  if (vm_support == NULL) {
    env->ExceptionClear();
    vm_support = env->FindClass("sun/misc/VMSupport");
  }
  if (vm_support != NULL) {
    jmethodID get_agent_props = env->GetStaticMethodID(
        vm_support, "getAgentProperties", "()Ljava/util/Properties;");
    jmethodID to_string = env->GetMethodID(env->FindClass("java/lang/Object"),
                                           "toString", "()Ljava/lang/String;");
    if (get_agent_props != NULL && to_string != NULL) {
      jobject props = env->CallStaticObjectMethod(vm_support, get_agent_props);
      jniExceptionCheck(env);
      if (props != NULL && !env->ExceptionCheck()) {
        jstring str = (jstring)env->CallObjectMethod(props, to_string);
        jniExceptionCheck(env);
        if (str != NULL && !env->ExceptionCheck()) {
          _agent_properties = (char *)env->GetStringUTFChars(str, NULL);
        }
      }
    }
  }
  env->ExceptionClear();

  if (_agent_properties == NULL) {
    return false;
  }

  char *p = _agent_properties + 1;
  p[strlen(p) - 1] = 0;

  while (*p) {
    if (strncmp(p, "sun.jvm.args=", 13) == 0) {
      _jvm_args = p + 13;
    } else if (strncmp(p, "sun.jvm.flags=", 14) == 0) {
      _jvm_flags = p + 14;
    } else if (strncmp(p, "sun.java.command=", 17) == 0) {
      _java_command = p + 17;
    }

    if ((p = strstr(p, ", ")) == NULL) {
      break;
    }

    *p = 0;
    p += 2;
  }

  return true;
}

void Recording::flush(Buffer *buf) {
  ssize_t result = write(_fd, buf->data(), buf->offset());
  if (result > 0) {
    atomicInc(_bytes_written, result);
  }
  buf->reset();
}

void Recording::flushIfNeeded(Buffer *buf, int limit) {
  if (buf->offset() >= limit) {
    flush(buf);
  }
}

void Recording::writeMetadata(Buffer *buf) {
  int metadata_start = buf->skip(5); // size will be patched later
  buf->putVar64(T_METADATA);
  buf->putVar64(_start_ticks);
  buf->put8(0);
  buf->put8(1);

  std::vector<std::string> &strings = JfrMetadata::strings();
  buf->putVar64(strings.size());
  for (int i = 0; i < strings.size(); i++) {
    const char *string = strings[i].c_str();
    int length = strlen(string);
    flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - length);
    buf->putUtf8(string, length);
  }

  writeElement(buf, JfrMetadata::root());

  buf->putVar32(metadata_start, buf->offset() - metadata_start);
  flushIfNeeded(buf);
}

void Recording::writeHeader(Buffer *buf) {
  buf->put("FLR\0", 4); // magic
  buf->put16(2);        // major
  buf->put16(0);        // minor
  buf->put64(
      1024 * 1024 *
      1024); // chunk size (initially large, for JMC to skip incomplete chunk)
  buf->put64(0);                  // cpool offset
  buf->put64(0);                  // meta offset
  buf->put64(_start_time * 1000); // start time, ns
  buf->put64(0);                  // duration, ns
  buf->put64(_start_ticks);       // start ticks
  buf->put64(TSC::frequency());   // ticks per sec
  buf->put32(1);                  // features
  flushIfNeeded(buf);
}

void Recording::writeElement(Buffer *buf, const Element *e) {
  buf->putVar64(e->_name);

  buf->putVar64(e->_attributes.size());
  for (int i = 0; i < e->_attributes.size(); i++) {
    flushIfNeeded(buf);
    buf->putVar64(e->_attributes[i]._key);
    buf->putVar64(e->_attributes[i]._value);
  }

  buf->putVar64(e->_children.size());
  for (int i = 0; i < e->_children.size(); i++) {
    flushIfNeeded(buf);
    writeElement(buf, e->_children[i]);
  }
  flushIfNeeded(buf);
}

void Recording::writeRecordingInfo(Buffer *buf) {
  int start = buf->skip(5);
  buf->putVar64(T_ACTIVE_RECORDING);
  buf->putVar64(_recording_start_ticks);
  buf->putVar64(_stop_ticks - _recording_start_ticks);
  buf->putVar64(_tid);
  buf->put8(0);
  buf->put8(1);
  buf->putUtf8("java-profiler " PROFILER_VERSION);
  buf->putUtf8("java-profiler.jfr");
  buf->putVar64(MAX_JLONG);
  if (VM::hotspot_version() >= 14) {
    buf->put8(0);
  }
  buf->put8(0);
  buf->putVar64(_recording_start_time / 1000);
  buf->putVar64((_stop_time - _recording_start_time) / 1000);
  buf->putVar32(start, buf->offset() - start);
  flushIfNeeded(buf);
}

void Recording::writeSettings(Buffer *buf, Arguments &args) {
  writeBoolSetting(buf, T_ACTIVE_RECORDING, "asyncprofiler", true);
  writeStringSetting(buf, T_ACTIVE_RECORDING, "version", PROFILER_VERSION);
  writeIntSetting(buf, T_ACTIVE_RECORDING, "tscfrequency", TSC::frequency());
  writeStringSetting(buf, T_ACTIVE_RECORDING, "loglevel",
                     Log::LEVEL_NAME[Log::level()]);
  writeBoolSetting(buf, T_ACTIVE_RECORDING, "hotspot", VM::isHotspot());
  writeBoolSetting(buf, T_ACTIVE_RECORDING, "openj9", VM::isOpenJ9());
  for (auto attribute : args._context_attributes) {
    writeStringSetting(buf, T_ACTIVE_RECORDING, "contextattribute",
                       attribute.c_str());
  }

  if (!((args._event != NULL && strcmp(args._event, EVENT_NOOP) != 0) ||
        args._cpu >= 0)) {
    writeBoolSetting(buf, T_EXECUTION_SAMPLE, "enabled", false);
  } else {
    writeBoolSetting(buf, T_EXECUTION_SAMPLE, "enabled", true);
    writeIntSetting(buf, T_EXECUTION_SAMPLE, "interval",
                    args.cpuSamplerInterval());
  }
  writeBoolSetting(buf, T_METHOD_SAMPLE, "enabled", args._wall >= 0);
  if (args._wall >= 0) {
    writeIntSetting(buf, T_METHOD_SAMPLE, "interval",
                    args._wall ? args._wall : DEFAULT_WALL_INTERVAL);
  }

  writeBoolSetting(buf, T_ALLOC, "enabled", args._record_allocations);
  writeBoolSetting(buf, T_HEAP_LIVE_OBJECT, "enabled", args._record_liveness);

  writeBoolSetting(buf, T_ACTIVE_RECORDING, "debugSymbols",
                   VMStructs::libjvm()->hasDebugSymbols());
  writeBoolSetting(buf, T_ACTIVE_RECORDING, "kernelSymbols",
                   Symbols::haveKernelSymbols());
  writeStringSetting(buf, T_ACTIVE_RECORDING, "cpuEngine",
                     Profiler::instance()->cpuEngine()->name());
  writeStringSetting(buf, T_ACTIVE_RECORDING, "wallEngine",
                     Profiler::instance()->wallEngine()->name());
  writeStringSetting(buf, T_ACTIVE_RECORDING, "cstack",
                     Profiler::instance()->cstack());
  flushIfNeeded(buf);
}

void Recording::writeStringSetting(Buffer *buf, int category, const char *key,
                                   const char *value) {
  flushIfNeeded(buf, RECORDING_BUFFER_LIMIT -
                         (2 * MAX_STRING_LENGTH + MAX_JFR_EVENT_SIZE));
  int start = buf->skip(5);
  buf->putVar64(T_ACTIVE_SETTING);
  buf->putVar64(_start_ticks);
  buf->put8(0);
  buf->putVar64(_tid);
  buf->put8(0);
  buf->putVar64(category);
  buf->putUtf8(key);
  buf->putUtf8(value);
  buf->putVar32(start, buf->offset() - start);
  flushIfNeeded(buf);
}

void Recording::writeBoolSetting(Buffer *buf, int category, const char *key,
                                 bool value) {
  writeStringSetting(buf, category, key, value ? "true" : "false");
}

void Recording::writeIntSetting(Buffer *buf, int category, const char *key,
                                long long value) {
  char str[32];
  snprintf(str, sizeof(str), "%lld", value);
  writeStringSetting(buf, category, key, str);
}

void Recording::writeListSetting(Buffer *buf, int category, const char *key,
                                 const char *base, int offset) {
  while (offset != 0) {
    writeStringSetting(buf, category, key, base + offset);
    offset = ((int *)(base + offset))[-1];
  }
  flushIfNeeded(buf);
}

void Recording::writeDatadogSetting(Buffer *buf, int length, const char *name,
                                    const char *value, const char *unit) {
  flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - length);
  int start = buf->skip(MAX_VAR32_LENGTH);
  buf->putVar64(T_DATADOG_SETTING);
  buf->putVar64(_start_ticks);
  buf->put8(0); // no duration, but required for compatibility with equivalent
                // Java event
  buf->putVar32(_tid);
  buf->put8(0); // no stacktrace, but required for compatibility with equivalent
                // Java event
  buf->putUtf8(name);
  buf->putUtf8(value);
  buf->putUtf8(unit);
  buf->putVar32(start, buf->offset() - start);
  flushIfNeeded(buf);
}

void Recording::writeDatadogProfilerConfig(
    Buffer *buf, long cpuInterval, long wallInterval, long allocInterval,
    long memleakInterval, long memleakCapacity, double memleakRatio,
    bool gcGenerations, int modeMask, const char *cpuEngine) {
  flushIfNeeded(buf, RECORDING_BUFFER_LIMIT -
                         (1 + 6 * MAX_VAR64_LENGTH + MAX_VAR32_LENGTH +
                          3 * MAX_STRING_LENGTH));
  int start = buf->skip(1);
  buf->putVar64(T_DATADOG_PROFILER_CONFIG);
  buf->putVar64(_start_ticks);
  buf->put8(0);
  buf->putVar64(_tid);
  buf->putVar64(cpuInterval);
  buf->putVar64(wallInterval);
  buf->putVar64(allocInterval);
  buf->putVar64(memleakInterval);
  buf->putVar64(memleakCapacity);
  buf->put8(static_cast<int>(memleakRatio * 100));
  buf->put8(gcGenerations);
  buf->putVar32(modeMask);
  buf->putUtf8(PROFILER_VERSION);
  buf->putUtf8(cpuEngine);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::writeHeapUsage(Buffer *buf, long value, bool live) {
  int start = buf->skip(1);
  buf->putVar64(T_HEAP_USAGE);
  buf->putVar64(TSC::ticks());
  buf->putVar64(value);
  buf->put8(live);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::writeOsCpuInfo(Buffer *buf) {
  struct utsname u;
  if (uname(&u) != 0) {
    return;
  }

  char str[512];
  snprintf(str, sizeof(str) - 1, "uname: %s %s %s %s", u.sysname, u.release,
           u.version, u.machine);
  str[sizeof(str) - 1] = 0;

  flushIfNeeded(buf,
                RECORDING_BUFFER_LIMIT - (2 * strlen(str) + strlen(u.machine)));

  int start = buf->skip(5);
  buf->putVar64(T_OS_INFORMATION);
  buf->putVar64(_start_ticks);
  buf->putUtf8(str);
  buf->putVar32(start, buf->offset() - start);

  start = buf->skip(5);
  buf->putVar64(T_CPU_INFORMATION);
  buf->putVar64(_start_ticks);
  buf->putUtf8(u.machine);
  buf->putUtf8(OS::getCpuDescription(str, sizeof(str) - 1) ? str : "");
  buf->put8(1);
  buf->putVar64(_available_processors);
  buf->putVar64(_available_processors);
  buf->putVar32(start, buf->offset() - start);
  flushIfNeeded(buf);
}

void Recording::writeJvmInfo(Buffer *buf) {
  if (_agent_properties == NULL && !parseAgentProperties()) {
    return;
  }

  char *jvm_name = NULL;
  char *jvm_version = NULL;

  jvmtiEnv *jvmti = VM::jvmti();
  jvmti->GetSystemProperty("java.vm.name", &jvm_name);
  jvmti->GetSystemProperty("java.vm.version", &jvm_version);

  flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - 5 * MAX_STRING_LENGTH);
  int start = buf->skip(5);
  buf->putVar64(T_JVM_INFORMATION);
  buf->putVar64(_start_ticks);
  buf->putUtf8(jvm_name);
  buf->putUtf8(jvm_version);
  buf->putUtf8(_jvm_args != nullptr ? _jvm_args : "");
  buf->putUtf8(_jvm_flags != nullptr ? _jvm_flags : "");
  buf->putUtf8(_java_command != nullptr ? _java_command : "");
  buf->putVar64(OS::processStartTime());
  buf->putVar64(OS::processId());
  buf->putVar32(start, buf->offset() - start);
  flushIfNeeded(buf);

  jvmti->Deallocate((unsigned char *)jvm_version);
  jvmti->Deallocate((unsigned char *)jvm_name);
}

void Recording::writeSystemProperties(Buffer *buf) {
  jvmtiEnv *jvmti = VM::jvmti();
  jint count;
  char **keys;
  if (jvmti->GetSystemProperties(&count, &keys) != 0) {
    return;
  }

  for (int i = 0; i < count; i++) {
    char *key = keys[i];
    char *value = NULL;
    if (jvmti->GetSystemProperty(key, &value) == 0) {
      flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - 2 * MAX_STRING_LENGTH);
      int start = buf->skip(5);
      buf->putVar64(T_INITIAL_SYSTEM_PROPERTY);
      buf->putVar64(_start_ticks);
      buf->putUtf8(key);
      buf->putUtf8(value);
      buf->putVar32(start, buf->offset() - start);
      jvmti->Deallocate((unsigned char *)value);
    }
    jvmti->Deallocate((unsigned char *)key);
  }
  flushIfNeeded(buf);

  jvmti->Deallocate((unsigned char *)keys);
}

void Recording::writeNativeLibraries(Buffer *buf) {
  if (_recorded_lib_count < 0)
    return;

  Profiler *profiler = Profiler::instance();
  CodeCacheArray &native_libs = profiler->_native_libs;
  int native_lib_count = native_libs.count();

  for (int i = _recorded_lib_count; i < native_lib_count; i++) {
    flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - MAX_STRING_LENGTH);
    int start = buf->skip(5);
    buf->putVar64(T_NATIVE_LIBRARY);
    buf->putVar64(_start_ticks);
    buf->putUtf8(native_libs[i]->name());
    buf->putVar64((uintptr_t)native_libs[i]->minAddress());
    buf->putVar64((uintptr_t)native_libs[i]->maxAddress());
    buf->putVar32(start, buf->offset() - start);
    flushIfNeeded(buf);
  }

  _recorded_lib_count = native_lib_count;
}

void Recording::writeCpool(Buffer *buf) {
  buf->skip(5); // size will be patched later
  buf->putVar64(T_CPOOL);
  buf->putVar64(_start_ticks);
  buf->put8(0);
  buf->put8(0);
  buf->put8(1);
  // constant pool count - bump each time a new pool is added
  buf->put8(12);

  // Profiler::instance()->classMap() provides access to non-locked _class_map
  // instance The non-locked access is ok here as this code will never run
  // concurrently to _class_map.clear()
  Lookup lookup(this, &_method_map, Profiler::instance()->classMap());
  writeFrameTypes(buf);
  writeThreadStates(buf);
  writeExecutionModes(buf);
  writeThreads(buf);
  writeStackTraces(buf, &lookup);
  writeMethods(buf, &lookup);
  writeClasses(buf, &lookup);
  writePackages(buf, &lookup);
  writeConstantPoolSection(buf, T_SYMBOL, &lookup._symbols);
  writeConstantPoolSection(buf, T_STRING,
                           Profiler::instance()->stringLabelMap());
  writeConstantPoolSection(buf, T_ATTRIBUTE_VALUE,
                           Profiler::instance()->contextValueMap());
  writeLogLevels(buf);
  flushIfNeeded(buf);
}

void Recording::writeFrameTypes(Buffer *buf) {
  buf->putVar32(T_FRAME_TYPE);
  buf->putVar32(7);
  buf->putVar32(FRAME_INTERPRETED);
  buf->putUtf8("Interpreted");
  buf->putVar32(FRAME_JIT_COMPILED);
  buf->putUtf8("JIT compiled");
  buf->putVar32(FRAME_INLINED);
  buf->putUtf8("Inlined");
  buf->putVar32(FRAME_NATIVE);
  buf->putUtf8("Native");
  buf->putVar32(FRAME_CPP);
  buf->putUtf8("C++");
  buf->putVar32(FRAME_KERNEL);
  buf->putUtf8("Kernel");
  buf->putVar32(FRAME_C1_COMPILED);
  buf->putUtf8("C1 compiled");
  flushIfNeeded(buf);
}

void Recording::writeThreadStates(Buffer *buf) {
  buf->putVar64(T_THREAD_STATE);
  buf->put8(10);
  buf->put8(static_cast<int>(OSThreadState::UNKNOWN));
  buf->putUtf8("UNKNOWN");
  buf->put8(static_cast<int>(OSThreadState::NEW));
  buf->putUtf8("NEW");
  buf->put8(static_cast<int>(OSThreadState::RUNNABLE));
  buf->putUtf8("RUNNABLE");
  buf->put8(static_cast<int>(OSThreadState::MONITOR_WAIT));
  buf->putUtf8("CONTENDED");
  buf->put8(static_cast<int>(OSThreadState::CONDVAR_WAIT));
  buf->putUtf8("PARKED");
  buf->put8(static_cast<int>(OSThreadState::OBJECT_WAIT));
  buf->putUtf8("WAITING");
  buf->put8(static_cast<int>(OSThreadState::BREAKPOINTED));
  buf->putUtf8("BREAKPOINT");
  buf->put8(static_cast<int>(OSThreadState::SLEEPING));
  buf->putUtf8("SLEEPING");
  buf->put8(static_cast<int>(OSThreadState::TERMINATED));
  buf->putUtf8("TERMINATED");
  buf->put8(static_cast<int>(OSThreadState::SYSCALL));
  buf->putUtf8("SYSCALL");
  flushIfNeeded(buf);
}

void Recording::writeExecutionModes(Buffer *buf) {
  buf->putVar64(T_EXECUTION_MODE);
  buf->put8(6);
  buf->put8(static_cast<int>(ExecutionMode::UNKNOWN));
  buf->putUtf8("UNKNOWN");
  buf->put8(static_cast<int>(ExecutionMode::JAVA));
  buf->putUtf8("JAVA");
  buf->put8(static_cast<int>(ExecutionMode::JVM));
  buf->putUtf8("JVM");
  buf->put8(static_cast<int>(ExecutionMode::NATIVE));
  buf->putUtf8("NATIVE");
  buf->put8(static_cast<int>(ExecutionMode::SAFEPOINT));
  buf->putUtf8("SAFEPOINT");
  buf->put8(static_cast<int>(ExecutionMode::SYSCALL));
  buf->putUtf8("SYSCALL");
  flushIfNeeded(buf);
}

void Recording::writeThreads(Buffer *buf) {
  int old_index = _active_index.fetch_xor(1, std::memory_order_acq_rel);
  // After flip: new samples go into the new active set
  // We flush from old_index (the previous active set)

  std::unordered_set<int> threads;
  threads.insert(_tid);

  for (int i = 0; i < CONCURRENCY_LEVEL; ++i) {
    // Collect thread IDs from the fixed-size table into the main set
    _thread_ids[i][old_index].collect(threads);
    _thread_ids[i][old_index].clear();
  }

  Profiler *profiler = Profiler::instance();
  ThreadInfo *t_info = &profiler->_thread_info;

  char name_buf[32];

  buf->putVar64(T_THREAD);
  buf->putVar64(threads.size());
  for (auto tid : threads) {
    const char *thread_name;
    jlong thread_id;
    std::pair<std::shared_ptr<std::string>, u64> info = t_info->get(tid);
    if (info.first) {
      thread_name = info.first->c_str();
      thread_id = info.second;
    } else {
      snprintf(name_buf, sizeof(name_buf), "[tid=%d]", tid);
      thread_name = name_buf;
      thread_id = 0;
    }

    int length = strlen(thread_name);
    int required = RECORDING_BUFFER_LIMIT -
                   (thread_id == 0 ? length + 1 : 2 * length) -
                   3 * 10; // 3x max varint length
    flushIfNeeded(buf, required);
    buf->putVar64(tid);
    buf->putUtf8(thread_name, length);
    buf->putVar64(tid);
    if (thread_id == 0) {
      buf->put8(0);
    } else {
      buf->putUtf8(thread_name, length);
    }
    buf->putVar64(thread_id);
    flushIfNeeded(buf);
  }
}

void Recording::writeStackTraces(Buffer *buf, Lookup *lookup) {
  // Use safe trace processing with guaranteed lifetime during callback execution
  Profiler::instance()->processCallTraces([this, buf, lookup](const std::unordered_set<CallTrace*>& traces) {
    buf->putVar64(T_STACK_TRACE);
    buf->putVar64(traces.size());
    for (std::unordered_set<CallTrace *>::const_iterator it = traces.begin();
         it != traces.end(); ++it) {
      CallTrace *trace = *it;
      buf->putVar64(trace->trace_id);
      if (trace->num_frames > 0) {
        MethodInfo *mi =
            lookup->resolveMethod(trace->frames[trace->num_frames - 1]);
        if (mi->_type < FRAME_NATIVE) {
          buf->put8(mi->_is_entry ? 0 : 1);
        } else {
          buf->put8(trace->truncated);
        }
      }
      buf->putVar64(trace->num_frames);
      for (int i = 0; i < trace->num_frames; i++) {
        MethodInfo *mi = lookup->resolveMethod(trace->frames[i]);
        buf->putVar64(mi->_key);
        jint bci = trace->frames[i].bci;
        if (mi->_type < FRAME_NATIVE) {
          FrameTypeId type = FrameType::decode(bci);
          bci = (bci & 0x10000) ? 0 : (bci & 0xffff);
          buf->putVar32(mi->getLineNumber(bci));
          buf->putVar32(bci);
          buf->put8(type);
        } else {
          buf->putVar32(0);
          buf->putVar32(bci);
          buf->put8(mi->_type);
        }
        flushIfNeeded(buf);
      }
      flushIfNeeded(buf);
    }
  });  // End of processCallTraces lambda
}

void Recording::writeMethods(Buffer *buf, Lookup *lookup) {
  MethodMap *method_map = lookup->_method_map;

  u32 marked_count = 0;
  for (MethodMap::const_iterator it = method_map->begin();
       it != method_map->end(); ++it) {
    if (it->second._mark) {
      marked_count++;
    }
  }

  buf->putVar64(T_METHOD);
  buf->putVar64(marked_count);
  for (MethodMap::iterator it = method_map->begin(); it != method_map->end();
       ++it) {
    MethodInfo &mi = it->second;
    if (mi._mark) {
      mi._mark = false;
      buf->putVar64(mi._key);
      buf->putVar64(mi._class);
      buf->putVar64(mi._name | _base_id);
      buf->putVar64(mi._sig | _base_id);
      buf->putVar64(mi._modifiers);
      buf->putVar64(mi.isHidden());
      flushIfNeeded(buf);
    }
  }
}

void Recording::writeClasses(Buffer *buf, Lookup *lookup) {
  std::map<u32, const char *> classes;
  // no need to lock _classes as this code will never run concurrently with
  // resetting that dictionary
  lookup->_classes->collect(classes);

  buf->putVar64(T_CLASS);
  buf->putVar64(classes.size());
  for (std::map<u32, const char *>::const_iterator it = classes.begin();
       it != classes.end(); ++it) {
    const char *name = it->second;
    buf->putVar64(it->first);
    buf->putVar64(0); // classLoader
    buf->putVar64(lookup->getSymbol(name) | _base_id);
    buf->putVar64(lookup->getPackage(name) | _base_id);
    buf->putVar64(0); // access flags
    flushIfNeeded(buf);
  }
}

void Recording::writePackages(Buffer *buf, Lookup *lookup) {
  std::map<u32, const char *> packages;
  lookup->_packages.collect(packages);

  buf->putVar32(T_PACKAGE);
  buf->putVar32(packages.size());
  for (std::map<u32, const char *>::const_iterator it = packages.begin();
       it != packages.end(); ++it) {
    buf->putVar64(it->first | _base_id);
    buf->putVar64(lookup->getSymbol(it->second) | _base_id);
    flushIfNeeded(buf);
  }
}

void Recording::writeConstantPoolSection(
    Buffer *buf, JfrType type, std::map<u32, const char *> &constants) {
  flushIfNeeded(buf);
  buf->putVar64(type);
  buf->putVar64(constants.size());
  for (std::map<u32, const char *>::const_iterator it = constants.begin();
       it != constants.end(); ++it) {
    int length = strlen(it->second);
    // 5 is max varint length
    flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - length - 5);
    buf->putVar64(it->first | _base_id);
    buf->putUtf8(it->second, length);
  }
}

void Recording::writeConstantPoolSection(Buffer *buf, JfrType type,
                                         Dictionary *dictionary) {
  std::map<u32, const char *> constants;
  dictionary->collect(constants);
  writeConstantPoolSection(buf, type, constants);
}

void Recording::writeLogLevels(Buffer *buf) {
  buf->putVar64(T_LOG_LEVEL);
  buf->putVar64(LOG_ERROR - LOG_TRACE + 1);
  for (int i = LOG_TRACE; i <= LOG_ERROR; i++) {
    buf->putVar32(i);
    buf->putUtf8(Log::LEVEL_NAME[i]);
    flushIfNeeded(buf);
  }
}

void Recording::writeCounters(Buffer *buf) {
  long long *counters = Counters::getCounters();
  if (counters) {
    std::vector<const char *> names = Counters::describeCounters();
    for (int i = 0; i < names.size(); i++) {
      int start = buf->skip(1);
      buf->putVar64(T_DATADOG_COUNTER);
      buf->putVar64(_start_ticks);
      buf->putUtf8(names[i]);
      buf->putVar64(counters[Counters::address(i)]);
      writeEventSizePrefix(buf, start);
      flushIfNeeded(buf);
    }
  }
}

void Recording::writeUnwindFailures(Buffer *buf) {
  static UnwindFailures failures;
  UnwindStats::collectAndReset(failures);

  failures.forEach([&](UnwindFailureKind kind, const char *name, u64 count) {
    int start = buf->skip(1);
    buf->putVar64(T_UNWIND_FAILURE);
    buf->putVar64(_start_ticks);
    buf->putUtf8((kind & UNWIND_FAILURE_STUB) ? "stub" : "other");
    buf->putUtf8(name);
    buf->putVar64(count);
    writeEventSizePrefix(buf, start);
    flushIfNeeded(buf);
  });
}

void Recording::writeContext(Buffer *buf, Context &context) {
  u64 spanId = 0;
  u64 rootSpanId = 0;
  u64 stored = context.checksum;
  if (stored != 0) {
    spanId = context.spanId;
    rootSpanId = context.rootSpanId;
    u64 computed = Contexts::checksum(spanId, rootSpanId);
    if (stored != computed) {
      TEST_LOG("Invalid context checksum: ctx=%p, tid=%d", &context, OS::threadId());
      spanId = 0;
      rootSpanId = 0;
    }
  }
  buf->putVar64(spanId);
  buf->putVar64(rootSpanId);

  for (size_t i = 0; i < Profiler::instance()->numContextAttributes(); i++) {
    Tag tag = context.get_tag(i);
    buf->putVar32(tag.value);
  }
}

void Recording::writeEventSizePrefix(Buffer *buf, int start) {
  int size = buf->offset() - start;
  assert(size < MAX_JFR_EVENT_SIZE);
  buf->put8(start, size);
}

void Recording::recordExecutionSample(Buffer *buf, int tid, u64 call_trace_id,
                                      ExecutionEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_EXECUTION_SAMPLE);
  buf->putVar64(TSC::ticks());
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->put8(static_cast<int>(event->_thread_state));
  buf->put8(static_cast<int>(event->_execution_mode));
  buf->putVar64(event->_weight);
  writeContext(buf, Contexts::get());
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordMethodSample(Buffer *buf, int tid, u64 call_trace_id,
                                   ExecutionEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_METHOD_SAMPLE);
  buf->putVar64(TSC::ticks());
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->put8(static_cast<int>(event->_thread_state));
  buf->put8(static_cast<int>(event->_execution_mode));
  buf->putVar64(event->_weight);
  writeContext(buf, Contexts::get());
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordWallClockEpoch(Buffer *buf, WallClockEpochEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_WALLCLOCK_SAMPLE_EPOCH);
  buf->putVar64(event->_start_time);
  buf->putVar64(event->_duration_millis);
  buf->putVar64(event->_num_samplable_threads);
  buf->putVar64(event->_num_successful_samples);
  buf->putVar64(event->_num_failed_samples);
  buf->putVar64(event->_num_exited_threads);
  buf->putVar64(event->_num_permission_denied);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordTraceRoot(Buffer *buf, int tid, TraceRootEvent *event) {
  flushIfNeeded(buf);
  int start = buf->skip(1);
  buf->putVar64(T_ENDPOINT);
  buf->putVar64(TSC::ticks());
  buf->put8(0);
  buf->putVar32(tid);
  buf->put8(0);
  buf->putVar32(event->_label);
  buf->putVar32(event->_operation);
  buf->putVar64(event->_local_root_span_id);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordQueueTime(Buffer *buf, int tid, QueueTimeEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_QUEUE_TIME);
  buf->putVar64(event->_start);
  buf->putVar64(event->_end - event->_start);
  buf->putVar64(tid);
  buf->putVar64(event->_origin);
  buf->putVar64(event->_task);
  buf->putVar64(event->_scheduler);
  buf->putVar64(event->_queueType);
  buf->putVar64(event->_queueLength);
  writeContext(buf, Contexts::get());
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordAllocation(RecordingBuffer *buf, int tid,
                                 u64 call_trace_id, AllocEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_ALLOC);
  buf->putVar64(TSC::ticks());
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->putVar64(event->_id);
  buf->putVar64(event->_size);
  buf->putFloat(event->_weight);
  writeContext(buf, Contexts::get());
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordHeapLiveObject(Buffer *buf, int tid, u64 call_trace_id,
                                     ObjectLivenessEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_HEAP_LIVE_OBJECT);
  buf->putVar64(event->_start_time);
  buf->putVar32(tid);
  buf->putVar64(call_trace_id);
  buf->putVar32(event->_id);
  buf->putVar64(event->_age);
  buf->putVar64(event->_alloc._size);
  // the _alloc._size is 0 only when running in the lightweight mode, only
  // tracking surviving generations
  buf->putFloat(
      event->_alloc._size > 0
          ? ((event->_alloc._weight * event->_alloc._size) + event->_skipped) /
                event->_alloc._size
          : 0);
  writeContext(buf, event->_ctx);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordMonitorBlocked(Buffer *buf, int tid, u64 call_trace_id,
                                     LockEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_MONITOR_ENTER);
  buf->putVar64(event->_start_time);
  buf->putVar64(event->_end_time - event->_start_time);
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->putVar64(event->_id);
  buf->put8(0);
  buf->putVar64(event->_address);
  writeContext(buf, Contexts::get());
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordThreadPark(Buffer *buf, int tid, u64 call_trace_id,
                                 LockEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_THREAD_PARK);
  buf->putVar64(event->_start_time);
  buf->putVar64(event->_end_time - event->_start_time);
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->putVar64(event->_id);
  buf->putVar64(event->_timeout);
  buf->putVar64(MIN_JLONG);
  buf->putVar64(event->_address);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordCpuLoad(Buffer *buf, float proc_user, float proc_system,
                              float machine_total) {
  int start = buf->skip(1);
  buf->putVar64(T_CPU_LOAD);
  buf->putVar64(TSC::ticks());
  buf->putFloat(proc_user);
  buf->putFloat(proc_system);
  buf->putFloat(machine_total);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

// assumption is that we hold the lock (with lock_index)
void Recording::addThread(int lock_index, int tid) {
    int active = _active_index.load(std::memory_order_acquire);
    _thread_ids[lock_index][active].insert(tid);
}

Error FlightRecorder::start(Arguments &args, bool reset) {
  ExclusiveLockGuard locker(&_rec_lock);
  const char *file = args.file();
  if (file == NULL || file[0] == 0) {
    _filename = "";
    return Error("Flight Recorder output file is not specified");
  }
  _filename = file;
  _args = args;

  if (!TSC::initialized()) {
    TSC::initialize();
  }

  Error ret = newRecording(reset);
  return ret;
}

Error FlightRecorder::newRecording(bool reset) {
  int fd =
      open(_filename.c_str(), O_CREAT | O_RDWR | (reset ? O_TRUNC : 0), 0644);
  if (fd == -1) {
    return Error("Could not open Flight Recorder output file");
  }

  _rec = new Recording(fd, _args);
  return Error::OK;
}

void FlightRecorder::stop() {
  ExclusiveLockGuard locker(&_rec_lock);
  Recording* rec = _rec;
  if (rec != nullptr) {
    // NULL first, deallocate later
    _rec = nullptr;
    delete rec;
  }
}

Error FlightRecorder::dump(const char *filename, const int length) {
  ExclusiveLockGuard locker(&_rec_lock);
  Recording* rec = _rec;
  if (rec != nullptr) {
    if (_filename.length() != length ||
        strncmp(filename, _filename.c_str(), length) != 0) {
      // if the filename to dump the recording to is specified move the current
      // working file there
      int copy_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
      rec->switchChunk(copy_fd);
      close(copy_fd);
      return Error::OK;
    }
    return Error(
      "Can not dump recording to itself. Provide a different file name!");
  }
  return Error("No active recording");
}

void FlightRecorder::flush() {
  ExclusiveLockGuard locker(&_rec_lock);
  Recording* rec = _rec;
  if (rec != nullptr) {
    jvmtiEnv* jvmti = VM::jvmti();
    JNIEnv* env = VM::jni();

    jclass** classes = NULL;
    jint count = 0;
    // obtaining the class list will create local refs to all loaded classes,
    // effectively preventing them from being unloaded while flushing
    jvmtiError err = jvmti->GetLoadedClasses(&count, classes);
    rec->switchChunk(-1);
    if (!err) {
      // deallocate all loaded classes
      for (int i = 0; i < count; i++) {
        env->DeleteLocalRef((jobject) classes[i]);
        jvmti->Deallocate((unsigned char*) classes[i]);
      }
    }
  }
}

void FlightRecorder::wallClockEpoch(int lock_index,
                                    WallClockEpochEvent *event) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      Buffer *buf = rec->buffer(lock_index);
      rec->recordWallClockEpoch(buf, event);
    }
  }
}

void FlightRecorder::recordTraceRoot(int lock_index, int tid,
                                     TraceRootEvent *event) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      Buffer *buf = rec->buffer(lock_index);
      rec->recordTraceRoot(buf, tid, event);
    }
  }
}

void FlightRecorder::recordQueueTime(int lock_index, int tid,
                                     QueueTimeEvent *event) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      Buffer *buf = rec->buffer(lock_index);
      rec->recordQueueTime(buf, tid, event);
    }
  }
}

void FlightRecorder::recordDatadogSetting(int lock_index, int length,
                                          const char *name, const char *value,
                                          const char *unit) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      Buffer *buf = rec->buffer(lock_index);
      rec->writeDatadogSetting(buf, length, name, value, unit);
    }
  }
}

void FlightRecorder::recordHeapUsage(int lock_index, long value, bool live) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      Buffer *buf = rec->buffer(lock_index);
      rec->writeHeapUsage(buf, value, live);
    }
  }
}

void FlightRecorder::recordEvent(int lock_index, int tid, u64 call_trace_id,
                                 int event_type, Event *event) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      RecordingBuffer *buf = rec->buffer(lock_index);
      switch (event_type) {
      case 0:
          rec->recordExecutionSample(buf, tid, call_trace_id,
                                     (ExecutionEvent *)event);
          break;
        case BCI_WALL:
          rec->recordMethodSample(buf, tid, call_trace_id,
                                  (ExecutionEvent *)event);
          break;
        case BCI_ALLOC:
          rec->recordAllocation(buf, tid, call_trace_id, (AllocEvent *)event);
          break;
        case BCI_LIVENESS:
          rec->recordHeapLiveObject(buf, tid, call_trace_id,
                                    (ObjectLivenessEvent *)event);
          break;
        case BCI_LOCK:
          rec->recordMonitorBlocked(buf, tid, call_trace_id, (LockEvent *)event);
          break;
        case BCI_PARK:
          rec->recordThreadPark(buf, tid, call_trace_id, (LockEvent *)event);
          break;
        }
        rec->flushIfNeeded(buf);
        rec->addThread(lock_index, tid);
      }
  }
}

void FlightRecorder::recordLog(LogLevel level, const char *message,
                               size_t len) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      if (len > MAX_STRING_LENGTH)
        len = MAX_STRING_LENGTH;
      // cppcheck-suppress obsoleteFunctions
      Buffer *buf = (Buffer *)alloca(len + 40);
      buf->reset();

      int start = buf->skip(5);
      buf->putVar64(T_LOG);
      buf->putVar64(TSC::ticks());
      buf->putVar64(level);
      buf->putUtf8(message, len);
      buf->putVar32(start, buf->offset() - start);
      _rec->flush(buf);
    }
  }
}
