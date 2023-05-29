/*
 * Copyright 2018 Andrei Pangin
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

#include <assert.h>

#include <map>
#include <string>
#include <arpa/inet.h>
#include <cxxabi.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "buffers.h"
#include "context.h"
#include "flightRecorder.h"
#include "incbin.h"
#include "jfrMetadata.h"
#include "jvm.h"
#include "dictionary.h"
#include "os.h"
#include "profiler.h"
#include "spinLock.h"
#include "symbols.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "vmStructs.h"

const u64 MAX_JLONG = 0x7fffffffffffffffULL;
const u64 MIN_JLONG = 0x8000000000000000ULL;
const int MAX_JFR_EVENT_SIZE = 256;
const int JFR_EVENT_FLUSH_THRESHOLD = RECORDING_BUFFER_LIMIT;


static SpinLock _rec_lock(1);

static jmethodID _start_method;
static jmethodID _stop_method;
static jmethodID _box_method;

static const char* const SETTING_RING[] = {NULL, "kernel", "user", "any"};
static const char* const SETTING_CSTACK[] = {NULL, "no", "fp", "dwarf", "lbr"};


struct CpuTime {
    u64 real;
    u64 user;
    u64 system;
};

struct CpuTimes {
    CpuTime proc;
    CpuTime total;
};


class MethodInfo {
  public:
    MethodInfo() : _mark(false), _is_entry(false), _key(0), _modifiers(0),
     _class(0), _name(0), _sig(0), _line_number_table_size(0), _line_number_table(),
     _type() {}

    bool _mark;
    bool _is_entry;
    u32 _key;
    u32 _class;
    u32 _name;
    u32 _sig;
    jint _modifiers;
    jint _line_number_table_size;
    jvmtiLineNumberEntry* _line_number_table;
    FrameTypeId _type;

    jint getLineNumber(jint bci) {
        if (_line_number_table_size == 0) {
            return 0;
        }

        int i = 1;
        while (i < _line_number_table_size && bci >= _line_number_table[i].start_location) {
            i++;
        }
        return _line_number_table[i - 1].line_number;
    }

    bool isHidden() {
        // 0x1400 = ACC_SYNTHETIC(0x1000) | ACC_BRIDGE(0x0040)
        return _modifiers == 0 || (_modifiers & 0x1040);
    }
};

class MethodMap : public std::map<jmethodID, MethodInfo> {
  public:
    MethodMap() {
    }

    ~MethodMap() {
        jvmtiEnv* jvmti = VM::jvmti();
        for (const_iterator it = begin(); it != end(); ++it) {
            jvmtiLineNumberEntry* line_number_table = it->second._line_number_table;
            if (line_number_table != NULL) {
                jvmti->Deallocate((unsigned char*)line_number_table);
            }
        }
    }
};

class Lookup {
  public:
    MethodMap* _method_map;
    Dictionary* _classes;
    Dictionary _packages;
    Dictionary _symbols;

  private:
    void fillNativeMethodInfo(MethodInfo* mi, const char* name, const char* lib_name) {
        mi->_class = _classes->lookup("");
        // TODO return the library name once we figured out how to cooperate with the backend
//        if (lib_name == NULL) {
//            mi->_class = _classes->lookup("");
//        } else if (lib_name[0] == '[' && lib_name[1] != 0) {
//            mi->_class = _classes->lookup(lib_name + 1, strlen(lib_name) - 2);
//        } else {
//            mi->_class = _classes->lookup(lib_name);
//        }

        mi->_modifiers = 0x100;
        mi->_line_number_table_size = 0;
        mi->_line_number_table = NULL;

        if (name[0] == '_' && name[1] == 'Z') {
            int status;
            char* demangled = abi::__cxa_demangle(name, NULL, NULL, &status);
            if (demangled != NULL) {
                cutArguments(demangled);
                mi->_name = _symbols.lookup(demangled);
                mi->_sig = _symbols.lookup("()L;");
                mi->_type = FRAME_CPP;
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

    void cutArguments(char* func) {
        char* p = strrchr(func, ')');
        if (p == NULL) return;

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

    void fillJavaMethodInfo(MethodInfo* mi, jmethodID method, bool first_time) {
        jvmtiEnv* jvmti = VM::jvmti();
        JNIEnv* jni = VM::jni();

        jclass method_class;
        char* class_name = NULL;
        char* method_name = NULL;
        char* method_sig = NULL;

        jint class_modifiers = 0;
        if (JVM::is_readable_pointer((void*)method) && jvmti->GetMethodDeclaringClass(method, &method_class) == 0 &&
            jvmti->GetClassSignature(method_class, &class_name, NULL) == 0 &&
            jvmti->GetMethodName(method, &method_name, &method_sig, NULL) == 0) {
            mi->_class = _classes->lookup(class_name + 1, strlen(class_name) - 2);
            mi->_name = _symbols.lookup(method_name);
            mi->_sig = _symbols.lookup(method_sig);

            if (first_time) {
                if (jvmti->GetClassModifiers(method_class, &class_modifiers) == 0 && jvmti->GetMethodModifiers(method, &mi->_modifiers) == 0) {
                    // class constants are written without the modifiers info
                    // in order to be able to identify 'hidden' frames the "SYNTHETIC" and "BRIDGE" modifiers will be propagated to methods
                    if (class_modifiers & 0x1000) {
                        mi->_modifiers |= 0x1000;
                    }
                    if (class_modifiers & 0x0040) {
                        mi->_modifiers |= 0x0040;
                    }
                }
                // Check if the frame is Thread.run or inherits from it
                if (strncmp(method_name, "run", 3) == 0 && strncmp(method_sig, "()V", 3) == 0) {
                    jclass Thread_class = jni->FindClass("java/lang/Thread");
                    jmethodID equals =
                        jni->GetMethodID(jni->FindClass("java/lang/Class"), "equals", "(Ljava/lang/Object;)Z");
                    jclass klass = method_class;
                    do {
                        if (jni->CallBooleanMethod(Thread_class, equals, klass)) {
                            mi->_is_entry = true;
                            break;
                        }
                    } while ((klass = jni->GetSuperclass(klass)) != NULL);
                } else if ((mi->_modifiers & 9) != 0 && strncmp(method_name, "main", 4) == 0 && strncmp(method_sig, "(Ljava/lang/String;)V", 21)) {
                    // public static void main(String[] args) - 'public static' translates to modifier bits 0 and 3, hence check for '9'
                    mi->_is_entry = true;
                }
            }
        } else {
            mi->_class = _classes->lookup("");
            mi->_name = _symbols.lookup("jvmtiError");
            mi->_sig = _symbols.lookup("()L;");
        }

        jvmti->Deallocate((unsigned char*)method_sig);
        jvmti->Deallocate((unsigned char*)method_name);
        jvmti->Deallocate((unsigned char*)class_name);

        if (first_time && jvmti->GetLineNumberTable(method, &mi->_line_number_table_size, &mi->_line_number_table) != 0) {
            mi->_line_number_table_size = 0;
            mi->_line_number_table = NULL;
        }

        mi->_type = FRAME_INTERPRETED;
    }

  public:
    Lookup(MethodMap* method_map, Dictionary* classes) :
        _method_map(method_map), _classes(classes), _packages(), _symbols() {}

    MethodInfo* resolveMethod(ASGCT_CallFrame& frame) {
        jmethodID method = frame.method_id;
        MethodInfo* mi = &(*_method_map)[method];

        bool first_time = mi->_key == 0;
        if (first_time) {
            mi->_key = _method_map->size();
        }

        if (!mi->_mark) {
            mi->_mark = true;
            if (method == NULL) {
                fillNativeMethodInfo(mi, "unknown", NULL);
            } else if (frame.bci == BCI_ERROR) {
                fillNativeMethodInfo(mi, (const char*)method, NULL);
            } else if (frame.bci == BCI_NATIVE_FRAME) {
                const char* name = (const char*)method;
                fillNativeMethodInfo(mi, name, Profiler::instance()->getLibraryName(name));
            } else {
                fillJavaMethodInfo(mi, method, first_time);
            }
        }

        return mi;
    }

    u32 getPackage(const char* class_name) {
        const char* package = strrchr(class_name, '/');
        if (package == NULL) {
            return 0;
        }
        if (package[1] >= '0' && package[1] <= '9') {
            // Seems like a hidden or anonymous class, e.g. com/example/Foo/0x012345
            do {
                if (package == class_name) return 0;
            } while (*--package != '/');
        }
        if (class_name[0] == '[') {
            class_name = strchr(class_name, 'L') + 1;
        }
        return _packages.lookup(class_name, package - class_name);
    }

    u32 getSymbol(const char* name) {
        return _symbols.lookup(name);
    }
};

class Recording {
  friend ObjectSampler;
  friend Profiler;

  private:
    static char* _agent_properties;
    static char* _jvm_args;
    static char* _jvm_flags;
    static char* _java_command;

    RecordingBuffer _buf[CONCURRENCY_LEVEL];
    int _fd;
    off_t _chunk_start;
    ThreadFilter _thread_set;
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
    Recording(int fd, Arguments& args) : _fd(fd), _thread_set(), _method_map() {
        
        args.save(_args);
        _chunk_start = lseek(_fd, 0, SEEK_END);
        _start_time = OS::micros();
        _start_ticks = TSC::ticks();
        _recording_start_time = _start_time;
        _recording_start_ticks = _start_ticks;
        _base_id = 0;
        _bytes_written = 0;

        _tid = OS::threadId();
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
            _last_times.proc.real = OS::getProcessCpuTime(&_last_times.proc.user, &_last_times.proc.system);
            _last_times.total.real = OS::getTotalCpuTime(&_last_times.total.user, &_last_times.total.system);
        }
    }

    ~Recording() {
        finishChunk(true);
        close(_fd);
    }
    
    void copyTo(int target_fd) {
        OS::copyFile(_fd, target_fd, 0, finishChunk(true));
    }

    off_t finishChunk() {
        return finishChunk(false);
    }

    off_t finishChunk(bool end_recording) {
        flush(&_cpu_monitor_buf);

        writeNativeLibraries(_buf);

        const ObjectSampler* oSampler = ObjectSampler::instance();
        // write the engine dependent setting
        if (oSampler->_record_allocations) {
            writeIntSetting(_buf, T_ALLOC, "interval", oSampler->_interval);
        }
        if (oSampler->_record_liveness) {
            writeIntSetting(_buf, T_HEAP_LIVE_OBJECT, "interval", oSampler->_interval);
            writeIntSetting(_buf, T_HEAP_LIVE_OBJECT, "capacity", LivenessTracker::instance()->_table_cap);
            writeIntSetting(_buf, T_HEAP_LIVE_OBJECT, "maximum capacity", LivenessTracker::instance()->_table_max_cap);
        }

        _stop_time = OS::micros();
        _stop_ticks = TSC::ticks();

        if (end_recording) {
            writeRecordingInfo(_buf);
        }

        for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
            flush(&_buf[i]);
        }

        off_t cpool_offset = lseek(_fd, 0, SEEK_CUR);
        writeCpool(_buf);
        flush(_buf);

        off_t chunk_end = lseek(_fd, 0, SEEK_CUR);

        // Patch cpool size field
        _buf->putVar32(0, chunk_end - cpool_offset);
        ssize_t result = pwrite(_fd, _buf->data(), 5, cpool_offset);
        (void)result;

        // // Workaround for JDK-8191415: compute actual TSC frequency, in case JFR is wrong
        u64 tsc_frequency = TSC::frequency();
        // if (tsc_frequency > 1000000000) {
        //     tsc_frequency = (u64)(double(_stop_ticks - _start_ticks) / double(_stop_time - _start_time) * 1000000);
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
        return chunk_end;
    }

    void switchChunk(int fd) {
        _chunk_start = finishChunk(fd > -1);
        _start_time = _stop_time;
        _start_ticks = _stop_ticks;
        _bytes_written = 0;
        if (fd > -1) {
            // move the chunk to external file and reset the continuous recording file
            OS::copyFile(_fd, fd, 0, _chunk_start);
            OS::truncateFile(_fd);
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
            // if the recording file is to be restarted write out all the info events again
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

    void cpuMonitorCycle() {
        if (!_cpu_monitor_enabled) return;

        CpuTimes times;
        times.proc.real = OS::getProcessCpuTime(&times.proc.user, &times.proc.system);
        times.total.real = OS::getTotalCpuTime(&times.total.user, &times.total.system);

        float proc_user = 0, proc_system = 0, machine_total = 0;

        if (times.proc.real != (u64)-1 && times.proc.real > _last_times.proc.real) {
            float delta = (times.proc.real - _last_times.proc.real) * _available_processors;
            proc_user = ratio((times.proc.user - _last_times.proc.user) / delta);
            proc_system = ratio((times.proc.system - _last_times.proc.system) / delta);
        }

        if (times.total.real != (u64)-1 && times.total.real > _last_times.total.real) {
            float delta = times.total.real - _last_times.total.real;
            machine_total = ratio(((times.total.user + times.total.system) -
                                   (_last_times.total.user + _last_times.total.system)) / delta);
            if (machine_total < proc_user + proc_system) {
                machine_total = ratio(proc_user + proc_system);
            }
        }

        recordCpuLoad(&_cpu_monitor_buf, proc_user, proc_system, machine_total);
        flushIfNeeded(&_cpu_monitor_buf, BUFFER_LIMIT);

        _last_times = times;
    }

    void appendRecording(const char* target_file, size_t size) {
        int append_fd = open(target_file, O_WRONLY);
        if (append_fd >= 0) {
            lseek(append_fd, 0, SEEK_END);
            OS::copyFile(_fd, append_fd, 0, size);
            close(append_fd);
        } else {
            Log::warn("Failed to open JFR recording at %s: %s", target_file, strerror(errno));
        }
    }

    RecordingBuffer* buffer(int lock_index) {
        return &_buf[lock_index];
    }

    bool parseAgentProperties() {
        JNIEnv* env = VM::jni();
        jclass vm_support = env->FindClass("jdk/internal/vm/VMSupport");
        if (vm_support == NULL) {
            env->ExceptionClear();
            vm_support = env->FindClass("sun/misc/VMSupport");
        }
        if (vm_support != NULL) {
            jmethodID get_agent_props = env->GetStaticMethodID(vm_support, "getAgentProperties", "()Ljava/util/Properties;");
            jmethodID to_string = env->GetMethodID(env->FindClass("java/lang/Object"), "toString", "()Ljava/lang/String;");
            if (get_agent_props != NULL && to_string != NULL) {
                jobject props = env->CallStaticObjectMethod(vm_support, get_agent_props);
                if (props != NULL) {
                    jstring str = (jstring)env->CallObjectMethod(props, to_string);
                    if (str != NULL) {
                        _agent_properties = (char*)env->GetStringUTFChars(str, NULL);
                    }
                }
            }
        }
        env->ExceptionClear();

        if (_agent_properties == NULL) {
            return false;
        }

        char* p = _agent_properties + 1;
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

    void flush(Buffer* buf) {
        ssize_t result = write(_fd, buf->data(), buf->offset());
        if (result > 0) {
            atomicInc(_bytes_written, result);
        }
        buf->reset();
    }

    void flushIfNeeded(Buffer* buf, int limit = JFR_EVENT_FLUSH_THRESHOLD) {
        if (buf->offset() >= limit) {
            flush(buf);
        }
    }

    void writeHeader(Buffer* buf) {
        buf->put("FLR\0", 4);            // magic
        buf->put16(2);                   // major
        buf->put16(0);                   // minor
        buf->put64(1024 * 1024 * 1024);  // chunk size (initially large, for JMC to skip incomplete chunk)
        buf->put64(0);                   // cpool offset
        buf->put64(0);                   // meta offset
        buf->put64(_start_time * 1000);  // start time, ns
        buf->put64(0);                   // duration, ns
        buf->put64(_start_ticks);        // start ticks
        buf->put64(TSC::frequency());    // ticks per sec
        buf->put32(1);                   // features
        flushIfNeeded(buf);
    }

    void writeMetadata(Buffer* buf) {
        int metadata_start = buf->skip(5);  // size will be patched later
        buf->putVar64(T_METADATA);
        buf->putVar64(_start_ticks);
        buf->put8(0);
        buf->put8(1);

        std::vector<std::string>& strings = JfrMetadata::strings();
        buf->putVar64(strings.size());
        for (int i = 0; i < strings.size(); i++) {
            buf->putUtf8(strings[i].c_str());
        }

        writeElement(buf, JfrMetadata::root());

        buf->putVar32(metadata_start, buf->offset() - metadata_start);
        flushIfNeeded(buf);
    }

    void writeElement(Buffer* buf, const Element* e) {
        buf->putVar64(e->_name);

        buf->putVar64(e->_attributes.size());
        for (int i = 0; i < e->_attributes.size(); i++) {
            buf->putVar64(e->_attributes[i]._key);
            buf->putVar64(e->_attributes[i]._value);
        }

        buf->putVar64(e->_children.size());
        for (int i = 0; i < e->_children.size(); i++) {
            writeElement(buf, e->_children[i]);
        }
        flushIfNeeded(buf);
    }

    void writeRecordingInfo(Buffer* buf) {
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
        if (VM::java_version() >= 14) {
            buf->put8(0);
        }
        buf->put8(0);
        buf->putVar64(_recording_start_time / 1000);
        buf->putVar64((_stop_time - _recording_start_time) / 1000);
        buf->putVar32(start, buf->offset() - start);
        flushIfNeeded(buf);
    }

    void writeSettings(Buffer* buf, Arguments& args) {
        writeBoolSetting(buf, T_ACTIVE_RECORDING, "asyncprofiler", true);
        writeStringSetting(buf, T_ACTIVE_RECORDING, "version", PROFILER_VERSION);
        writeStringSetting(buf, T_ACTIVE_RECORDING, "ring", SETTING_RING[args._ring]);
        writeStringSetting(buf, T_ACTIVE_RECORDING, "cstack", SETTING_CSTACK[args._cstack]);
        writeStringSetting(buf, T_ACTIVE_RECORDING, "filter", args._filter);
        writeIntSetting(buf, T_ACTIVE_RECORDING, "jstackdepth", args._jstackdepth);
        writeIntSetting(buf, T_ACTIVE_RECORDING, "safemode", args._safe_mode);
        writeIntSetting(buf, T_ACTIVE_RECORDING, "jfropts", args._jfr_options);
        writeStringSetting(buf, T_ACTIVE_RECORDING, "loglevel", Log::LEVEL_NAME[Log::level()]);
        writeBoolSetting(buf, T_ACTIVE_RECORDING, "hotspot", VM::isHotspot());
        writeBoolSetting(buf, T_ACTIVE_RECORDING, "openj9", VM::isOpenJ9());
        for (auto attribute : args._context_attributes) {
            writeStringSetting(buf, T_ACTIVE_RECORDING, "contextattribute", attribute.c_str());
        }

        if (!((args._event != NULL && strcmp(args._event, EVENT_NOOP) != 0) || args._cpu >= 0)) {
            writeBoolSetting(buf, T_EXECUTION_SAMPLE, "enabled", false);
        } else {
            writeBoolSetting(buf, T_EXECUTION_SAMPLE, "enabled", true);
            writeIntSetting(buf, T_EXECUTION_SAMPLE, "interval", args._event != NULL ? args._interval : args._cpu);
        }
        writeBoolSetting(buf, T_METHOD_SAMPLE, "enabled", args._wall >= 0);
        if (args._wall >= 0) {
            writeIntSetting(buf, T_METHOD_SAMPLE, "interval", args._wall ? args._wall : DEFAULT_WALL_INTERVAL);
        }

        writeBoolSetting(buf, T_ALLOC, "enabled", args._record_allocations);
        writeBoolSetting(buf, T_HEAP_LIVE_OBJECT, "enabled", args._record_liveness);

        writeBoolSetting(buf, T_ACTIVE_RECORDING, "debugSymbols", VMStructs::hasDebugSymbols());
        writeBoolSetting(buf, T_ACTIVE_RECORDING, "kernelSymbols", Symbols::haveKernelSymbols());
        writeStringSetting(buf, T_ACTIVE_RECORDING, "cpuEngine", Profiler::instance()->cpuEngine()->name());
        writeStringSetting(buf, T_ACTIVE_RECORDING, "wallEngine", Profiler::instance()->wallEngine()->name());
        flushIfNeeded(buf);
    }

    void writeStringSetting(Buffer* buf, int category, const char* key, const char* value) {
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

    void writeBoolSetting(Buffer* buf, int category, const char* key, bool value) {
        writeStringSetting(buf, category, key, value ? "true" : "false");
    }

    void writeIntSetting(Buffer* buf, int category, const char* key, long long value) {
        char str[32];
        snprintf(str, sizeof(str), "%lld", value);
        writeStringSetting(buf, category, key, str);
    }

    void writeListSetting(Buffer* buf, int category, const char* key, const char* base, int offset) {
        while (offset != 0) {
            writeStringSetting(buf, category, key, base + offset);
            offset = ((int*)(base + offset))[-1];
        }
        flushIfNeeded(buf);
    }

    void writeDatadogSetting(Buffer* buf, int length, const char* name, const char* value, const char* unit) {
        flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - length);
        int start = buf->skip(5);
        buf->putVar64(T_DATADOG_SETTING);
        buf->putVar64(_start_ticks);
        buf->put8(0); // no duration, but required for compatibility with equivalent Java event
        buf->putVar32(_tid);
        buf->put8(0); // no stacktrace, but required for compatibility with equivalent Java event
        buf->putUtf8(name);
        buf->putUtf8(value);
        buf->putUtf8(unit);
        buf->putVar32(start, buf->offset() - start);
    }

    void writeOsCpuInfo(Buffer* buf) {
        struct utsname u;
        if (uname(&u) != 0) {
            return;
        }

        char str[512];
        snprintf(str, sizeof(str) - 1, "uname: %s %s %s %s", u.sysname, u.release, u.version, u.machine);
        str[sizeof(str) - 1] = 0;

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

    void writeJvmInfo(Buffer* buf) {
        if (_agent_properties == NULL && !parseAgentProperties()) {
            return;
        }

        char* jvm_name = NULL;
        char* jvm_version = NULL;

        jvmtiEnv* jvmti = VM::jvmti();
        jvmti->GetSystemProperty("java.vm.name", &jvm_name);
        jvmti->GetSystemProperty("java.vm.version", &jvm_version);

        flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - 5 * MAX_STRING_LENGTH);
        int start = buf->skip(5);
        buf->putVar64(T_JVM_INFORMATION);
        buf->putVar64(_start_ticks);
        buf->putUtf8(jvm_name);
        buf->putUtf8(jvm_version);
        buf->putUtf8(_jvm_args);
        buf->putUtf8(_jvm_flags);
        buf->putUtf8(_java_command);
        buf->putVar64(OS::processStartTime());
        buf->putVar64(OS::processId());
        buf->putVar32(start, buf->offset() - start);
        flushIfNeeded(buf);

        jvmti->Deallocate((unsigned char*)jvm_version);
        jvmti->Deallocate((unsigned char*)jvm_name);
    }

    void writeSystemProperties(Buffer* buf) {
        jvmtiEnv* jvmti = VM::jvmti();
        jint count;
        char** keys;
        if (jvmti->GetSystemProperties(&count, &keys) != 0) {
            return;
        }

        for (int i = 0; i < count; i++) {
            char* key = keys[i];
            char* value = NULL;
            if (jvmti->GetSystemProperty(key, &value) == 0) {
                flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - 2 * MAX_STRING_LENGTH);
                int start = buf->skip(5);
                buf->putVar64(T_INITIAL_SYSTEM_PROPERTY);
                buf->putVar64(_start_ticks);
                buf->putUtf8(key);
                buf->putUtf8(value);
                buf->putVar32(start, buf->offset() - start);
                jvmti->Deallocate((unsigned char*)value);
            }
        }
        flushIfNeeded(buf);

        jvmti->Deallocate((unsigned char*)keys);
    }

    void writeNativeLibraries(Buffer* buf) {
        if (_recorded_lib_count < 0) return;

        Profiler* profiler = Profiler::instance();
        CodeCacheArray& native_libs = profiler->_native_libs;
        int native_lib_count = native_libs.count();

        for (int i = _recorded_lib_count; i < native_lib_count; i++) {
            flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - MAX_STRING_LENGTH);
            int start = buf->skip(5);
            buf->putVar64(T_NATIVE_LIBRARY);
            buf->putVar64(_start_ticks);
            buf->putUtf8(native_libs[i]->name());
            buf->putVar64((uintptr_t) native_libs[i]->minAddress());
            buf->putVar64((uintptr_t) native_libs[i]->maxAddress());
            buf->putVar32(start, buf->offset() - start);
            flushIfNeeded(buf);
        }

        _recorded_lib_count = native_lib_count;
    }

    void writeCpool(Buffer* buf) {
        buf->skip(5);  // size will be patched later
        buf->putVar64(T_CPOOL);
        buf->putVar64(_start_ticks);
        buf->put8(0);
        buf->put8(0);
        buf->put8(1);
        // constant pool count - bump each time a new pool is added
        buf->put8(11);

        // Profiler::instance()->classMap() provides access to non-locked _class_map instance
        // The non-locked access is ok here as this code will never run concurrently to _class_map.clear()
        Lookup lookup(&_method_map, Profiler::instance()->classMap());
        writeFrameTypes(buf);
        writeThreadStates(buf);
        writeThreads(buf);
        writeStackTraces(buf, &lookup);
        writeMethods(buf, &lookup);
        writeClasses(buf, &lookup);
        writePackages(buf, &lookup);
        writeConstantPoolSection(buf, T_SYMBOL, &lookup._symbols);
        writeConstantPoolSection(buf, T_STRING, Profiler::instance()->stringLabelMap());
        writeConstantPoolSection(buf, T_ATTRIBUTE_VALUE, Profiler::instance()->contextValueMap());
        writeLogLevels(buf);
        flushIfNeeded(buf);
    }

    void writeFrameTypes(Buffer* buf) {
        buf->putVar32(T_FRAME_TYPE);
        buf->putVar32(7);
        buf->putVar32(FRAME_INTERPRETED);  buf->putUtf8("Interpreted");
        buf->putVar32(FRAME_JIT_COMPILED); buf->putUtf8("JIT compiled");
        buf->putVar32(FRAME_INLINED);      buf->putUtf8("Inlined");
        buf->putVar32(FRAME_NATIVE);       buf->putUtf8("Native");
        buf->putVar32(FRAME_CPP);          buf->putUtf8("C++");
        buf->putVar32(FRAME_KERNEL);       buf->putUtf8("Kernel");
        buf->putVar32(FRAME_C1_COMPILED);  buf->putUtf8("C1 compiled");
        flushIfNeeded(buf);
    }

    void writeThreadStates(Buffer* buf) {
        buf->putVar64(T_THREAD_STATE);
        buf->put8(6);
        buf->put8(JAVA_THREAD_NEW);
        buf->putUtf8("NEW");
        buf->put8(JAVA_THREAD_RUNNABLE);
        buf->putUtf8("RUNNABLE");
        buf->put8(JAVA_THREAD_BLOCKED);
        buf->putUtf8("BLOCKED");
        buf->put8(JAVA_THREAD_WAITING);
        buf->putUtf8("WAITING");
        buf->put8(JAVA_THREAD_TIMED_WAITING);
        buf->putUtf8("TIMED_WAITING");
        buf->put8(JAVA_THREAD_TERMINATED);
        buf->putUtf8("TERMINATED");
        flushIfNeeded(buf);
    }

    void writeThreads(Buffer* buf) {
        addThread(_tid);
        std::vector<int> threads;
        threads.reserve(_thread_set.size());
        _thread_set.collect(threads);
        _thread_set.clear();

        Profiler* profiler = Profiler::instance();
        MutexLocker ml(profiler->_thread_names_lock);
        std::map<int, std::string>& thread_names = profiler->_thread_names;
        std::map<int, jlong>& thread_ids = profiler->_thread_ids;
        char name_buf[32];

        buf->putVar64(T_THREAD);
        buf->putVar64(threads.size());
        for (int i = 0; i < threads.size(); i++) {
            const char* thread_name;
            jlong thread_id;
            std::map<int, std::string>::const_iterator it = thread_names.find(threads[i]);
            if (it != thread_names.end()) {
                thread_name = it->second.c_str();
                thread_id = thread_ids[threads[i]];
            } else {
                snprintf(name_buf, sizeof(name_buf), "[tid=%d]", threads[i]);
                thread_name = name_buf;
                thread_id = 0;
            }

            buf->putVar64(threads[i]);
            buf->putUtf8(thread_name);
            buf->putVar64(threads[i]);
            if (thread_id == 0) {
                buf->put8(0);
            } else {
                buf->putUtf8(thread_name);
            }
            buf->putVar64(thread_id);
            flushIfNeeded(buf);
        }
    }

    void writeStackTraces(Buffer* buf, Lookup* lookup) {
        std::map<u32, CallTrace*> traces;
        Profiler::instance()->_call_trace_storage.collectTraces(traces);

        buf->putVar64(T_STACK_TRACE);
        buf->putVar64(traces.size());
        for (std::map<u32, CallTrace*>::const_iterator it = traces.begin(); it != traces.end(); ++it) {
            CallTrace* trace = it->second;
            buf->putVar64(it->first);
            if (trace->num_frames > 0) {
                MethodInfo* mi = lookup->resolveMethod(trace->frames[trace->num_frames - 1]);
                if (mi->_type < FRAME_NATIVE) {
                    buf->put8(mi->_is_entry ? 0 : 1);
                } else {
                    buf->put8(trace->truncated);
                }
            }
            buf->putVar64(trace->num_frames);
            for (int i = 0; i < trace->num_frames; i++) {
                MethodInfo* mi = lookup->resolveMethod(trace->frames[i]);
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
    }

    void writeMethods(Buffer* buf, Lookup* lookup) {
        MethodMap* method_map = lookup->_method_map;

        u32 marked_count = 0;
        for (MethodMap::const_iterator it = method_map->begin(); it != method_map->end(); ++it) {
            if (it->second._mark) {
                marked_count++;
            }
        }

        buf->putVar64(T_METHOD);
        buf->putVar64(marked_count);
        for (MethodMap::iterator it = method_map->begin(); it != method_map->end(); ++it) {
            MethodInfo& mi = it->second;
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

    void writeClasses(Buffer* buf, Lookup* lookup) {
        std::map<u32, const char*> classes;
        // no need to lock _classes as this code will never run concurrently with resetting that dictionary
        lookup->_classes->collect(classes);

        buf->putVar64(T_CLASS);
        buf->putVar64(classes.size());
        for (std::map<u32, const char*>::const_iterator it = classes.begin(); it != classes.end(); ++it) {
            const char* name = it->second;
            buf->putVar64(it->first);
            buf->putVar64(0);  // classLoader
            buf->putVar64(lookup->getSymbol(name) | _base_id);
            buf->putVar64(lookup->getPackage(name) | _base_id);
            buf->putVar64(0);  // access flags
            flushIfNeeded(buf);
        }
    }

    void writePackages(Buffer* buf, Lookup* lookup) {
        std::map<u32, const char*> packages;
        lookup->_packages.collect(packages);

        buf->putVar32(T_PACKAGE);
        buf->putVar32(packages.size());
        for (std::map<u32, const char*>::const_iterator it = packages.begin(); it != packages.end(); ++it) {
            buf->putVar64(it->first | _base_id);
            buf->putVar64(lookup->getSymbol(it->second) | _base_id);
            flushIfNeeded(buf);
        }
    }

    void writeConstantPoolSection(Buffer* buf, JfrType type, std::map<u32, const char*>& constants) {
        flushIfNeeded(buf);
        buf->putVar64(type);
        buf->putVar64(constants.size());
        for (std::map<u32, const char*>::const_iterator it = constants.begin(); it != constants.end(); ++it) {
            int length = strlen(it->second);
            // 5 is max varint length
            flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - length - 5);
            buf->putVar64(it->first | _base_id);
            buf->putUtf8(it->second, length);
        }
    }

    void writeConstantPoolSection(Buffer* buf, JfrType type, Dictionary* dictionary) {
        std::map<u32, const char*> constants;
        dictionary->collect(constants);
        writeConstantPoolSection(buf, type, constants);
    }

    void writeLogLevels(Buffer* buf) {
        buf->putVar64(T_LOG_LEVEL);
        buf->putVar64(LOG_ERROR - LOG_TRACE + 1);
        for (int i = LOG_TRACE; i <= LOG_ERROR; i++) {
            buf->putVar32(i);
            buf->putUtf8(Log::LEVEL_NAME[i]);
            flushIfNeeded(buf);
        }
    }

    void writeContext(Buffer* buf, Context& context) {
        buf->putVar64(context.spanId);
        buf->putVar64(context.rootSpanId);
        for (size_t i = 0; i < Profiler::instance()->numContextAttributes(); i++) {
            Tag tag = context.get_tag(i);
            buf->putVar32(tag.value);
        }
    }

    void writeEventSizePrefix(Buffer* buf, int start) {
        int size = buf->offset() - start;
        assert(size < MAX_JFR_EVENT_SIZE);
        buf->put8(start, size);
    }

    void recordExecutionSample(Buffer* buf, int tid, u32 call_trace_id, ExecutionEvent* event) {
        int start = buf->skip(1);
        buf->putVar64(T_EXECUTION_SAMPLE);
        buf->putVar64(TSC::ticks());
        buf->putVar64(tid);
        buf->putVar64(call_trace_id);
        buf->putVar64(event->_thread_state);
        buf->putVar64(event->_weight);
        writeContext(buf, Contexts::get(tid));
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void recordMethodSample(Buffer* buf, int tid, u32 call_trace_id, ExecutionEvent* event) {
        int start = buf->skip(1);
        buf->putVar64(T_METHOD_SAMPLE);
        buf->putVar64(TSC::ticks());
        buf->putVar64(tid);
        buf->putVar64(call_trace_id);
        buf->putVar64(event->_thread_state);
        buf->putVar64(event->_weight);
        writeContext(buf, Contexts::get(tid));
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void recordWallClockEpoch(Buffer* buf, WallClockEpochEvent* event) {
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

    void recordTraceRoot(Buffer* buf, int tid, TraceRootEvent* event) {
        int start = buf->skip(1);
        buf->putVar64(T_ENDPOINT);
        buf->putVar64(TSC::ticks());
        buf->put8(0);
        buf->putVar32(tid);
        buf->put8(0);
        buf->putVar32(event->_label);
        buf->putVar64(event->_local_root_span_id);
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void recordAllocation(RecordingBuffer* buf, int tid, u32 call_trace_id, AllocEvent* event) {
        int start = buf->skip(1);
        buf->putVar64(T_ALLOC);
        buf->putVar64(TSC::ticks());
        buf->putVar64(tid);
        buf->putVar64(call_trace_id);
        buf->putVar64(event->_id);
        buf->putVar64(event->_size);
        buf->putFloat(event->_weight);
        writeContext(buf, Contexts::get(tid));
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void recordHeapLiveObject(Buffer* buf, int tid, u32 call_trace_id, ObjectLivenessEvent* event) {
        int start = buf->skip(1);
        buf->putVar64(T_HEAP_LIVE_OBJECT);
        buf->putVar64(event->_start_time);
        buf->putVar32(tid);
        buf->putVar32(call_trace_id);
        buf->putVar32(event->_id);
        buf->putVar64(event->_age);
        buf->putVar64(event->_alloc._size);
        buf->putFloat(event->_alloc._weight);
        writeContext(buf, event->_ctx);
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void recordMonitorBlocked(Buffer* buf, int tid, u32 call_trace_id, LockEvent* event) {
        int start = buf->skip(1);
        buf->putVar64(T_MONITOR_ENTER);
        buf->putVar64(event->_start_time);
        buf->putVar64(event->_end_time - event->_start_time);
        buf->putVar64(tid);
        buf->putVar64(call_trace_id);
        buf->putVar64(event->_id);
        buf->put8(0);
        buf->putVar64(event->_address);
        writeContext(buf, Contexts::get(tid));
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void recordThreadPark(Buffer* buf, int tid, u32 call_trace_id, LockEvent* event) {
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

    void recordCpuLoad(Buffer* buf, float proc_user, float proc_system, float machine_total) {
        int start = buf->skip(1);
        buf->putVar64(T_CPU_LOAD);
        buf->putVar64(TSC::ticks());
        buf->putFloat(proc_user);
        buf->putFloat(proc_system);
        buf->putFloat(machine_total);
        writeEventSizePrefix(buf, start);
        flushIfNeeded(buf);
    }

    void addThread(int tid) {
        if (!_thread_set.accept(tid)) {
            _thread_set.add(tid);
        }
    }
};

char* Recording::_agent_properties = NULL;
char* Recording::_jvm_args = NULL;
char* Recording::_jvm_flags = NULL;
char* Recording::_java_command = NULL;

Error FlightRecorder::start(Arguments& args, bool reset) {
    const char* file = args.file();
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
    _rec_lock.unlock();
    return ret;
}

Error FlightRecorder::newRecording(bool reset) {
    int fd = open(_filename.c_str(), O_CREAT | O_RDWR | (reset ? O_TRUNC : 0), 0644);
    if (fd == -1) {
        return Error("Could not open Flight Recorder output file");
    }

    _rec = new Recording(fd, _args);
    return Error::OK;
}

void FlightRecorder::stop() {
    if (_rec != NULL) {
        _rec_lock.lock();

        delete _rec;
        _rec = NULL;
    }
}

Error FlightRecorder::dump(const char* filename, const int length) {
    if (_rec != NULL) {
        _rec_lock.lock();
        if (_filename.length() != length || strncmp(filename, _filename.c_str(), length) != 0) {
            // if the filename to dump the recording to is specified move the current working file there
            int copy_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
            _rec->switchChunk(copy_fd);
            close(copy_fd);
            _rec_lock.unlock();
        } else {
            // need to unlock in the exceptional path as well
            _rec_lock.unlock();
            return Error("Can not dump recording to itself. Provide a different file name!");
        }
        
        return Error::OK;
    } else {
        return Error("No active recording");
    }
}

void FlightRecorder::flush() {
    if (_rec != NULL) {
        _rec_lock.lock();
        _rec->switchChunk(-1);
        _rec_lock.unlock();
    }
}

void FlightRecorder::wallClockEpoch(int lock_index, WallClockEpochEvent* event) {
    if (_rec != NULL) {
        Buffer* buf = _rec->buffer(lock_index);
        _rec->recordWallClockEpoch(buf, event);
    }
}

void FlightRecorder::recordTraceRoot(int lock_index, int tid, TraceRootEvent* event) {
    if (_rec != NULL) {
        Buffer* buf = _rec->buffer(lock_index);
        _rec->recordTraceRoot(buf, tid, event);
    }
}

void FlightRecorder::recordDatadogSetting(int lock_index, int length,
                                          const char* name, const char* value, const char* unit) {
    if (_rec != NULL) {
        Buffer *buf = _rec->buffer(lock_index);
        _rec->writeDatadogSetting(buf, length, name, value, unit);
    }
}

void FlightRecorder::recordEvent(int lock_index, int tid, u32 call_trace_id,
                                 int event_type, Event* event, u64 counter) {
    if (_rec != NULL) {
        RecordingBuffer* buf = _rec->buffer(lock_index);
        switch (event_type) {
            case 0:
                _rec->recordExecutionSample(buf, tid, call_trace_id, (ExecutionEvent*)event);
                break;
            case BCI_WALL:
                _rec->recordMethodSample(buf, tid, call_trace_id, (ExecutionEvent*)event);
                break;
            case BCI_ALLOC:
                _rec->recordAllocation(buf, tid, call_trace_id, (AllocEvent*)event);
                break;
            case BCI_LIVENESS:
                _rec->recordHeapLiveObject(buf, tid, call_trace_id, (ObjectLivenessEvent*)event);
                break;
            case BCI_LOCK:
                _rec->recordMonitorBlocked(buf, tid, call_trace_id, (LockEvent*)event);
                break;
            case BCI_PARK:
                _rec->recordThreadPark(buf, tid, call_trace_id, (LockEvent*)event);
                break;
        }
        _rec->flushIfNeeded(buf);
        _rec->addThread(tid);
    }
}

void FlightRecorder::recordLog(LogLevel level, const char* message, size_t len) {
    if (!_rec_lock.tryLockShared()) {
        // No active recording
        return;
    }

    if (len > MAX_STRING_LENGTH) len = MAX_STRING_LENGTH;
    // cppcheck-suppress obsoleteFunctions
    Buffer* buf = (Buffer*)alloca(len + 40);
    buf->reset();

    int start = buf->skip(5);
    buf->putVar64(T_LOG);
    buf->putVar64(TSC::ticks());
    buf->putVar64(level);
    buf->putUtf8(message, len);
    buf->putVar32(start, buf->offset() - start);
    _rec->flush(buf);

    _rec_lock.unlockShared();
}
