/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */


#include "lookup.h"

#include <cxxabi.h>
#include <inttypes.h>
#include <stdio.h>

#include "codeCache.h"
#include "common.h"
#include "counters.h"
#include "jniHelper.h"
#include "jvmSupport.h"
#include "libraries.h"
#include "methodInfo.h"
#include "profiler.h"
#include "rustDemangler.h"

#include "hotspot/vmStructs.inline.h"

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

void Lookup::fillRemoteFrameInfo(MethodInfo *mi, const RemoteFrameInfo *rfi) {
  // Store build-id in the class name field
  mi->_class = _classes->lookup(rfi->build_id);

  // Store PC offset in hex format in the signature field
  char offset_hex[32];
  snprintf(offset_hex, sizeof(offset_hex), "0x%" PRIxPTR, rfi->pc_offset);
  mi->_sig = _symbols.lookup(offset_hex);

  // Use same modifiers as regular native frames (0x100 = ACC_NATIVE for consistency)
  mi->_modifiers = 0x100;
  // Use FRAME_NATIVE_REMOTE type to indicate remote symbolication
  mi->_type = FRAME_NATIVE_REMOTE;
  mi->_line_number_table = nullptr;

  // Method name indicates need for remote symbolication
  mi->_name = _symbols.lookup("<remote>");
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

  jint line_number_table_size = 0;
  jvmtiLineNumberEntry *line_number_table = NULL;

  jvmti->GetPhase(&phase);
  if ((phase & (JVMTI_PHASE_START | JVMTI_PHASE_LIVE)) != 0) {
    if (VMMethod::check_jmethodID(method) &&
        jvmti->GetMethodDeclaringClass(method, &method_class) == 0 &&
        // GetMethodDeclaringClass may return a jclass wrapping a stale/garbage oop when the class was
        // unloaded between sample capture and dump (TOCTOU race with class unloading). Guard against
        // null handles before calling GetClassSignature.
        method_class != NULL &&
        // On some older versions of J9, the JVMTI call to GetMethodDeclaringClass will return OK = 0, but when a
        // classloader is unloaded they free all JNIIDs. This means that anyone holding on to a jmethodID is
        // pointing to corrupt data and the behaviour is undefined.
        // The behaviour is adjusted so that when asgct() is used or if `-XX:+KeepJNIIDs` is specified,
        // when a classloader is unloaded, the jmethodIDs are not freed, but instead marked as -1.
        // The check below mitigates these crashes on J9.
        (!VM::isOpenJ9() || method_class != reinterpret_cast<jclass>(-1)) &&
        jvmti->GetClassSignature(method_class, &class_name, NULL) == JVMTI_ERROR_NONE &&
        jvmti->GetMethodName(method, &method_name, &method_sig, NULL) == JVMTI_ERROR_NONE) {
      if (first_time) {
        // Populate modifier (async profiler has this call)
        if (jvmti->GetMethodModifiers(method, &mi->_modifiers) != JVMTI_ERROR_NONE) {
          mi->_modifiers = 0;
        }
        jvmtiError line_table_error = jvmti->GetLineNumberTable(method, &line_number_table_size,
                                  &line_number_table);
        // Defensive: if GetLineNumberTable failed, clean up any potentially allocated memory
        // Some buggy JVMTI implementations might allocate despite returning an error
        if (line_table_error != JVMTI_ERROR_NONE) {
          if (line_number_table != nullptr) {
            // Try to deallocate to prevent leak from buggy JVM
            jvmti->Deallocate((unsigned char *)line_number_table);
          }
          line_number_table = nullptr;
          line_number_table_size = 0;
        }
      }

      fillMethodInfo(mi, method_class, class_name, method_name, method_sig, line_number_table_size, line_number_table);

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
    } else {
      Counters::increment(JMETHODID_SKIPPED);
      mi->_class = _classes->lookup("");
      mi->_name = _symbols.lookup("jvmtiError");
      mi->_sig = _symbols.lookup("()L;");
      mi->_type = FRAME_INTERPRETED;
      mi->_is_entry = false;
    }
  }
  jni->PopLocalFrame(NULL);
}

void Lookup::fillMethodInfo(MethodInfo *mi, jclass method_class, char* class_name, char* method_name, char* method_sig, jint line_number_table_size, jvmtiLineNumberEntry* line_number_table) {
  bool entry = false;
  u32 class_name_id = 0;
  u32 method_name_id = 0;
  u32 method_sig_id = 0;

  JNIEnv *jni = VM::jni();
  if (jni == nullptr) {
    return;
  }

  // Check if the frame is Thread.run or inherits from it
  if (strncmp(method_name, "run", 4) == 0 &&
      strncmp(method_sig, "()V", 3) == 0) {
    jclass Thread_class = jni->FindClass("java/lang/Thread");
    jclass Class_class = jni->FindClass("java/lang/Class");
    if (Thread_class != nullptr && Class_class != nullptr) {
      jmethodID equals = jni->GetMethodID(Class_class,
                                          "equals", "(Ljava/lang/Object;)Z");
      if (equals != nullptr) {
        jclass klass = method_class;
        do {
          entry = jni->CallBooleanMethod(Thread_class, equals, klass);
          if (jniExceptionCheck(jni)) {
            entry = false;
            break;
          }
          if (entry) {
            break;
          }
        } while ((klass = jni->GetSuperclass(klass)) != NULL);
      }
    }
    // Clear any exceptions from the reflection calls above
    jniExceptionCheck(jni);
  } else if (strncmp(method_name, "main", 5) == 0 &&
             strncmp(method_sig, "(Ljava/lang/String;)V", 21) == 0) {
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

    mi->_class = class_name_id;
    mi->_name = method_name_id;
    mi->_sig = method_sig_id;
    mi->_type = FRAME_INTERPRETED;
    mi->_is_entry = entry;
    if (line_number_table != nullptr) {
      mi->_line_number_table = std::make_shared<SharedLineNumberTable>(
          line_number_table_size, line_number_table);
      // Increment counter for tracking live line number tables
      Counters::increment(LINE_NUMBER_TABLES);
    }
}

MethodInfo *Lookup::resolveMethod(ASGCT_CallFrame &frame) {
  static const char* UNKNOWN = "unknown";
  static const char* NOT_WALKABLE = "not_walkable";

  unsigned long key;
  jint bci = frame.bci;
  FrameTypeId frame_type = FrameType::decode(bci);
  jmethodID method_id = frame.method_id;

  // Resolve this frame into FRAME_INTERPRETED
  if (FrameType::isRawPointer(bci)) {
    method_id = JVMSupport::resolve(frame.method);

    TEST_LOG("Lookup resolving method: 0x%zu to 0x%zu", (unsigned long)frame.method, (unsigned long)method_id);
    frame.bci = FrameType::encode(frame_type, frame.bci);
    frame.method_id = method_id;
  }

  if (method_id == nullptr) {
    key = MethodMap::makeKey(UNKNOWN);
  } else if (method_id == JMETHODID_NOT_WALKABLE) {
    key = MethodMap::makeKey(NOT_WALKABLE);
  } else if (bci == BCI_ERROR || bci == BCI_NATIVE_FRAME) {
    key = MethodMap::makeKey(frame.native_function_name);
  } else if (bci == BCI_NATIVE_FRAME_REMOTE) {
    key = MethodMap::makeKey(frame.packed_remote_frame);
  } else {
    assert(frame_type == FRAME_INTERPRETED || frame_type == FRAME_JIT_COMPILED ||
           frame_type == FRAME_INLINED || frame_type == FRAME_C1_COMPILED ||
           VM::isOpenJ9()); // OpenJ9 may have bugs that produce invalid frame types
    key = MethodMap::makeKey(method_id);
  }

  MethodInfo *mi = &(*_method_map)[key];

  if (!mi->_mark) {
    mi->_mark = true;
    bool first_time = mi->_key == 0;
    if (first_time) {
      mi->_key = _method_map->size() + 1; // avoid zero key
    }
    if (method_id == nullptr) {
      fillNativeMethodInfo(mi, UNKNOWN, nullptr);
    } else if (method_id == JMETHODID_NOT_WALKABLE) {
      fillNativeMethodInfo(mi, NOT_WALKABLE, nullptr);
    } else if (bci == BCI_ERROR) {
      fillNativeMethodInfo(mi, (const char *)method_id, nullptr);
    } else if (bci == BCI_NATIVE_FRAME) {
      const char *name = (const char *)method_id;
      fillNativeMethodInfo(mi, name,
                           Profiler::instance()->getLibraryName(name));
    } else if (bci == BCI_NATIVE_FRAME_REMOTE) {
      // Unpack remote symbolication data using utility struct
      // Layout: pc_offset (44 bits) | mark (3 bits) | lib_index (15 bits)
      unsigned long packed_remote_frame = frame.packed_remote_frame;
      uintptr_t pc_offset = Profiler::RemoteFramePacker::unpackPcOffset(packed_remote_frame);
      [[maybe_unused]] char mark = Profiler::RemoteFramePacker::unpackMark(packed_remote_frame);
      uint32_t lib_index = Profiler::RemoteFramePacker::unpackLibIndex(packed_remote_frame);

      TEST_LOG("Unpacking remote frame: packed=0x%zx, pc_offset=0x%lx, mark=%d, lib_index=%u",
               packed_remote_frame, pc_offset, (int)mark, lib_index);

      // Lookup library by index to get build_id
      // Note: This is called during JFR serialization with lockAll() held (see Profiler::dump),
      // so the library array is stable - no concurrent dlopen_hook calls can modify it.
      CodeCache* lib = Libraries::instance()->getLibraryByIndex(lib_index);
      if (lib != nullptr && lib->hasBuildId() && Profiler::instance()->isRemoteSymbolication()) {
        TEST_LOG("Found library: %s, build_id=%s", lib->name(), lib->buildId());
        // Remote symbolication: defer to backend
        RemoteFrameInfo rfi(lib->buildId(), pc_offset, lib_index);
        fillRemoteFrameInfo(mi, &rfi);
      } else if (lib != nullptr) {
        // Locally unsymbolized: render as [libname+0xoffset]
        char name_buf[256];
        const char* s = lib->name();
        const char* basename = strrchr(s, '/');
        if (basename) basename++; else basename = s;
        snprintf(name_buf, sizeof(name_buf), "[%s+0x%" PRIxPTR "]", basename, pc_offset);
        fillNativeMethodInfo(mi, name_buf, nullptr);
      } else {
        TEST_LOG("WARNING: Library lookup failed for index %u", lib_index);
        fillNativeMethodInfo(mi, "unknown_library", nullptr);
      }
    } else {
        fillJavaMethodInfo(mi, method_id, first_time);
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

u32 Lookup::getSymbol(const char *name) {
  return _symbols.lookup(name); 
}
