/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common.h"
#include "vmEntry.h"
#include "arguments.h"
#include "context.h"
#include "j9Ext.h"
#include "jniHelper.h"
#include "libraries.h"
#include "log.h"
#include "os.h"
#include "profiler.h"
#include "safeAccess.h"
#include "vmStructs.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

// JVM TI agent return codes
const int ARGUMENTS_ERROR = 100;
const int COMMAND_ERROR = 200;

static Arguments _agent_args(true);

JavaVM *VM::_vm;
jvmtiEnv *VM::_jvmti = NULL;

int VM::_java_version = 0;
int VM::_java_update_version = 0;
int VM::_hotspot_version = 0;
bool VM::_openj9 = false;
bool VM::_hotspot = false;
bool VM::_zing = false;
bool VM::_can_sample_objects = false;
bool VM::_can_intercept_binding = false;
bool VM::_is_adaptive_gc_boundary_flag_set = false;

jvmtiError(JNICALL *VM::_orig_RedefineClasses)(jvmtiEnv *, jint,
                                               const jvmtiClassDefinition *);
jvmtiError(JNICALL *VM::_orig_RetransformClasses)(jvmtiEnv *, jint,
                                                  const jclass *classes);

void *VM::_libjvm;
void *VM::_libjava;
AsyncGetCallTrace VM::_asyncGetCallTrace;
JVM_GetManagement VM::_getManagement;

static void wakeupHandler(int signo) {
  // Dummy handler for interrupting syscalls
}

static bool isVmRuntimeEntry(const char* blob_name) {
    return strcmp(blob_name, "_ZNK12MemAllocator8allocateEv") == 0
        || strncmp(blob_name, "_Z22post_allocation_notify", 26) == 0
        || strncmp(blob_name, "_ZN11OptoRuntime", 16) == 0
        || strncmp(blob_name, "_ZN8Runtime1", 12) == 0
        || strncmp(blob_name, "_ZN13SharedRuntime", 18) == 0
        || strncmp(blob_name, "_ZN18InterpreterRuntime", 23) == 0;
}

static bool isZingRuntimeEntry(const char* blob_name) {
    return strncmp(blob_name, "_ZN14DolphinRuntime", 19) == 0
        || strncmp(blob_name, "_ZN37JvmtiSampledObjectAllocEventCollector", 42) == 0;
}

static bool isZeroInterpreterMethod(const char *blob_name) {
  return strncmp(blob_name, "_ZN15ZeroInterpreter", 20) == 0 ||
         strncmp(blob_name, "_ZN19BytecodeInterpreter3run", 28) == 0;
}

static bool isOpenJ9InterpreterMethod(const char *blob_name) {
  return strncmp(blob_name, "_ZN32VM_BytecodeInterpreter", 27) == 0 ||
         strncmp(blob_name, "_ZN26VM_BytecodeInterpreter", 27) == 0 ||
         strncmp(blob_name, "bytecodeLoop", 12) == 0 ||
         strcmp(blob_name, "cInterpreter") == 0;
}

static bool isOpenJ9JitStub(const char *blob_name) {
  if (strncmp(blob_name, "jit", 3) == 0) {
    blob_name += 3;
    return strcmp(blob_name, "NewObject") == 0 ||
           strcmp(blob_name, "NewArray") == 0 ||
           strcmp(blob_name, "ANewArray") == 0;
  }
  return false;
}

static bool isOpenJ9Resolve(const char* blob_name) {
    return strncmp(blob_name, "resolve", 7) == 0;
}

static bool isOpenJ9JitAlloc(const char* blob_name) {
    return strncmp(blob_name, "old_", 4) == 0;
}

static bool isOpenJ9GcAlloc(const char* blob_name) {
    return strncmp(blob_name, "J9Allocate", 10) == 0;
}

static bool isOpenJ9JvmtiAlloc(const char* blob_name) {
    return strcmp(blob_name, "jvmtiHookSampledObjectAlloc") == 0;
}

static bool isCompilerEntry(const char* blob_name) {
    return strncmp(blob_name, "_ZN13CompileBroker25invoke_compiler_on_method", 45) == 0;
}

static bool isThreadEntry(const char* blob_name) {
    // Match thread entry point patterns for JVM threads (both HotSpot and OpenJ9) and Rust threads
    return strstr(blob_name, "thread_native_entry") != NULL ||
           strstr(blob_name, "JavaThread::") != NULL ||
           strstr(blob_name, "_ZN10JavaThread") != NULL ||     // Mangled JavaThread:: names
           strstr(blob_name, "thread_main_inner") != NULL ||
           strstr(blob_name, "thread_start") != NULL ||        // Rust thread roots
           strstr(blob_name, "start_thread") != NULL;          // glibc pthread entry
}

static void* resolveMethodId(void** mid) {
    return mid == NULL || *mid < (void*)4096 ? NULL : *mid;
}

static void resolveMethodIdEnd() {}

JavaFullVersion JavaVersionAccess::get_java_version(char* prop_value) {
  JavaFullVersion version = {8, 362}; // initial value is 8u362; an arbitrary java version
  TEST_LOG("version property: %s", prop_value);
  if (strncmp(prop_value, "1.8.0_", 6) == 0) {
    version.major = 8;
    version.update = atoi(prop_value + 6);
  } else if (strncmp(prop_value, "8.0.", 4) == 0) {
    version.major = 8;
    version.update = atoi(prop_value + 4);
  } else if (strncmp(prop_value, "25.", 3) == 0 && prop_value[3] != '0') {
    // Java 8 encoded in java.vm.version system property looks like 25.352-b08
    // The upcoming Java 25 version will have a form of '25.0.<update>' instead
    version.major = 8;
    version.update = atoi(prop_value + 3);
  } else if (strncmp(prop_value, "JRE 1.8.0", 9) == 0) {
    // IBM JDK 8 does not report the 'real' version in any property accessible
    // from JVMTI The only piece of info we can use has the following format
    // `JRE 1.8.0 <some text> 20230313_47323 <some more text>`
    // Considering that JDK 8.0.361 is the only release in 2023 we can use
    // that part of the version string to pretend anything after year 2023
    // inclusive is 8.0.361. Not perfect, but this is the only thing we have.
    version.major = 8;
    char *idx = strstr(prop_value, " 202");
    if (idx != NULL) {
      int year = atol(idx + 1);
      if (year >= 2023) {
        version.update = 361;
      } else {
        version.update = 351;
      }
    }
  } else {
    version.major = atoi(prop_value);
    if (version.major < 9) {
      version.major = 9;
    }
    char* peg_char = strchr(prop_value, '+');
    if (peg_char) {
      // terminate before the build specification
      *peg_char = '\0';
    }
    // format is 11.0.17
    // this shortcut for parsing the update version should hold till Java 99
    version.update = atoi(prop_value + 5);
  }
  return version;
}

int JavaVersionAccess::get_hotspot_version(char* prop_value) {
  int hs_version = 0;
  if (strncmp(prop_value, "25.", 3) == 0 && prop_value[3] > '0') {
    hs_version = 8;
  } else if (strncmp(prop_value, "24.", 3) == 0 && prop_value[3] > '0') {
    hs_version = 7;
  } else if (strncmp(prop_value, "20.", 3) == 0 && prop_value[3] > '0') {
    hs_version = 6;
  } else if ((hs_version = atoi(prop_value)) < 9) {
    hs_version = 9;
  }
  return hs_version;
}

CodeCache* VM::openJvmLibrary() {
  if ((void*)_asyncGetCallTrace == nullptr) {
    return nullptr;
  }

  Libraries* libraries = Libraries::instance();
  CodeCache *lib =
    isOpenJ9()
        ? libraries->findJvmLibrary("libj9vm")
        : libraries->findLibraryByAddress((const void *)_asyncGetCallTrace);
  return lib;
}

bool VM::initShared(JavaVM* vm) {
  if (_jvmti != NULL)
    return true;

  _vm = vm;
  if (_vm->GetEnv((void **)&_jvmti, JVMTI_VERSION_1_0) != 0) {
    return false;
  }

#ifdef __APPLE__
  Dl_info dl_info;
  if (dladdr((const void *)wakeupHandler, &dl_info) &&
      dl_info.dli_fname != NULL) {
    // Make sure java-profiler DSO cannot be unloaded, since it contains JVM
    // callbacks. On Linux, we use 'nodelete' linker option.
    dlopen(dl_info.dli_fname, RTLD_LAZY | RTLD_NODELETE);
  }
#endif

  bool is_zero_vm = false;
  char *prop;
  if (_jvmti->GetSystemProperty("java.vm.name", &prop) == 0) {
    _hotspot = strstr(prop, "OpenJDK") != NULL ||
               strstr(prop, "HotSpot") != NULL ||
               strstr(prop, "GraalVM") != NULL ||
               strstr(prop, "Dynamic Code Evolution") != NULL;
    is_zero_vm = strstr(prop, "Zero") != NULL;
    _zing = !_hotspot && strstr(prop, "Zing") != NULL;
    _openj9 = !_hotspot && strstr(prop, "OpenJ9") != NULL;

    _jvmti->Deallocate((unsigned char *)prop);
    prop = NULL;
  }

  _libjvm = getLibraryHandle("libjvm.so");
  _asyncGetCallTrace = (AsyncGetCallTrace)dlsym(_libjvm, "AsyncGetCallTrace");
  _getManagement = (JVM_GetManagement)dlsym(_libjvm, "JVM_GetManagement");

  Libraries *libraries = Libraries::instance();
  libraries->updateSymbols(false);

  _openj9 = !_hotspot && J9Ext::initialize(
                             _jvmti, libraries->resolveSymbol("j9thread_self*"));

  if (_openj9) {
    if (_jvmti->GetSystemProperty("jdk.extensions.version", &prop) == 0) {
      // OpenJ9 Semeru will report the version here
      // insert debug output here
    } else {
      if (prop != NULL) {
        _jvmti->Deallocate((unsigned char *)prop);
        prop = NULL;
      }
      if (_jvmti->GetSystemProperty("java.fullversion", &prop) == 0) {
        // IBM JDK 8 will report something here
        // The reported string contains JRE 1.8.0 and then later year and
        // (possibly) hash code Although not very precise, this is best we can
        // get :/ insert debug output here
      } else {
        if (prop != NULL) {
          _jvmti->Deallocate((unsigned char *)prop);
          prop = NULL;
        }
      }
    }
  }
  if (prop == NULL) {
    if (_jvmti->GetSystemProperty("java.runtime.version", &prop) == 0) {
      // insert debug output here
    } else {
      if (prop != NULL) {
        _jvmti->Deallocate((unsigned char *)prop);
        prop = NULL;
      }
    }
  }
  TEST_LOG("java.runtime.version: %s", prop);
  if (prop != NULL) {
    JavaFullVersion version = JavaVersionAccess::get_java_version(prop);
    _java_version = version.major;
    _java_update_version = version.update;
    _jvmti->Deallocate((unsigned char *)prop);
    prop = NULL;
  }
  if (_jvmti->GetSystemProperty("java.vm.version", &prop) == 0) {
    TEST_LOG("java.vm.version: %s", prop);
    if (_java_version == 0) {
      JavaFullVersion version = JavaVersionAccess::get_java_version(prop);
      _java_version = version.major;
      _java_update_version = version.update;
    }
    _hotspot_version = JavaVersionAccess::get_hotspot_version(prop);
    _jvmti->Deallocate((unsigned char *)prop);
    prop = NULL;
  }

  if (prop != NULL) {
    _jvmti->Deallocate((unsigned char *)prop);
  }

  if (_java_version == 0 && _hotspot_version > 0) {
    // sanity fallback:
    // - if we failed to resolve the _java_version but have _hotspot_version, let's use the hotspot version as java version
    _java_version = _hotspot_version;
  }
  TEST_LOG("jvm_version#%d.%d.%d", _java_version, 0, _java_update_version);

  CodeCache *lib = openJvmLibrary();
  if (lib == nullptr) {
    return false;
  }

  VMStructs::init(lib);

  // Mark thread entry points for all JVMs (critical for correct stack unwinding)
  lib->mark(isThreadEntry, MARK_THREAD_ENTRY);

  // Also mark libc/pthread libraries which contain thread start/exit points
  CodeCache* libc = libraries->findJvmLibrary("libc");
  if (libc != NULL) {
      libc->mark(isThreadEntry, MARK_THREAD_ENTRY);
  }
  CodeCache* libpthread = libraries->findJvmLibrary("libpthread");
  if (libpthread != NULL) {
      libpthread->mark(isThreadEntry, MARK_THREAD_ENTRY);
  }

  if (isOpenJ9()) {
      lib->mark(isOpenJ9InterpreterMethod, MARK_INTERPRETER);
      lib->mark(isOpenJ9Resolve, MARK_VM_RUNTIME);
      CodeCache* libjit = libraries->findJvmLibrary("libj9jit");
      if (libjit != NULL) {
          libjit->mark(isOpenJ9JitStub, MARK_INTERPRETER);
          libjit->mark(isOpenJ9JitAlloc, MARK_VM_RUNTIME);
      }
      CodeCache* libgc = libraries->findJvmLibrary("libj9gc");
      if (libgc != NULL) {
          libgc->mark(isOpenJ9GcAlloc, MARK_VM_RUNTIME);
      }
      CodeCache* libjvmti = libraries->findJvmLibrary("libj9jvmti");
      if (libjvmti != NULL) {
          libjvmti->mark(isOpenJ9JvmtiAlloc, MARK_VM_RUNTIME);
      }
  } else {
      lib->mark(isVmRuntimeEntry, MARK_VM_RUNTIME);
      if (isZing()) {
          lib->mark(isZingRuntimeEntry, MARK_VM_RUNTIME);
      } else if (is_zero_vm) {
          lib->mark(isZeroInterpreterMethod, MARK_INTERPRETER);
      } else {
          lib->mark(isCompilerEntry, MARK_COMPILER_ENTRY);
      }
  }
  return true;
}

bool VM::initLibrary(JavaVM *vm) {
  TEST_LOG("VM::initLibrary");
  if (!initShared(vm)) {
    return false;
  }
  ready(jvmti(), jni());
  return true;
}

bool VM::initProfilerBridge(JavaVM *vm, bool attach) {
  TEST_LOG("VM::initProfilerBridge");
  if (!initShared(vm)) {
    return false;
  }

  CodeCache *lib = openJvmLibrary();
  if (lib == nullptr) {
    return false;
  }

  if (!attach && hotspot_version() == 8 && OS::isLinux()) {
    // Workaround for JDK-8185348
    char *func = (char *)lib->findSymbol(
        "_ZN6Method26checked_resolve_jmethod_idEP10_jmethodID");
    if (func != NULL) {
      applyPatch(func, (const char *)resolveMethodId,
                 (const char *)resolveMethodIdEnd);
    }
  }

  jvmtiCapabilities potential_capabilities = {0};
  _jvmti->GetPotentialCapabilities(&potential_capabilities);

  _can_sample_objects =
      potential_capabilities.can_generate_sampled_object_alloc_events &&
      (!_hotspot || hotspot_version() >= 11);
  _can_intercept_binding =
      potential_capabilities.can_generate_native_method_bind_events &&
      HeapUsage::needsNativeBindingInterception();

  jvmtiCapabilities capabilities = {0};
  capabilities.can_generate_all_class_hook_events = 1;
  capabilities.can_retransform_classes = 1;
  capabilities.can_retransform_any_class = isOpenJ9() ? 0 : 1;
  // capabilities.can_generate_vm_object_alloc_events = isOpenJ9() ? 1 : 0;
  capabilities.can_generate_sampled_object_alloc_events =
      _can_sample_objects ? 1 : 0;
  capabilities.can_generate_native_method_bind_events =
      _can_intercept_binding ? 1 : 0;
  capabilities.can_generate_garbage_collection_events = 1;
  capabilities.can_get_bytecodes = 1;
  capabilities.can_get_constant_pool = 1;
  capabilities.can_get_source_file_name = 1;
  capabilities.can_get_line_numbers = 1;
  capabilities.can_generate_compiled_method_load_events = 1;
  capabilities.can_generate_monitor_events = 1;
  capabilities.can_tag_objects = 1;

  _jvmti->AddCapabilities(&capabilities);

  jvmtiEventCallbacks callbacks = {0};
  callbacks.VMInit = VMInit;
  callbacks.VMDeath = VMDeath;
  callbacks.ClassLoad = ClassLoad;
  callbacks.ClassPrepare = ClassPrepare;
  callbacks.CompiledMethodLoad = Profiler::CompiledMethodLoad;
  callbacks.DynamicCodeGenerated = Profiler::DynamicCodeGenerated;
  callbacks.ThreadStart = Profiler::ThreadStart;
  callbacks.ThreadEnd = Profiler::ThreadEnd;
  callbacks.SampledObjectAlloc = ObjectSampler::SampledObjectAlloc;
  callbacks.GarbageCollectionFinish = LivenessTracker::GarbageCollectionFinish;
  callbacks.NativeMethodBind = VMStructs::NativeMethodBind;
  _jvmti->SetEventCallbacks(&callbacks, sizeof(callbacks));

  _jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_DEATH, NULL);
  _jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_LOAD, NULL);
  _jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_PREPARE,
                                   NULL);
  _jvmti->SetEventNotificationMode(JVMTI_ENABLE,
                                   JVMTI_EVENT_DYNAMIC_CODE_GENERATED, NULL);
  _jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_NATIVE_METHOD_BIND,
                                   NULL);

  if (hotspot_version() == 0 || !CodeHeap::available()) {
    // Workaround for JDK-8173361: avoid CompiledMethodLoad events when possible
    _jvmti->SetEventNotificationMode(JVMTI_ENABLE,
                                     JVMTI_EVENT_COMPILED_METHOD_LOAD, NULL);
  } else {
    // DebugNonSafepoints is automatically enabled with CompiledMethodLoad,
    // otherwise we set the flag manually
    JVMFlag* f = JVMFlag::find("DebugNonSafepoints", {JVMFlag::Type::Bool});
    if (f != NULL && f->isDefault()) {
      f->set(1);
    }
  }

  // if the user sets -XX:+UseAdaptiveGCBoundary we will just disable the
  // profiler to avoid the risk of crashing flag was made obsolete (inert) in 15
  // (see JDK-8228991) and removed in 16 (see JDK-8231560)
  if (hotspot_version() < 15) {
    JVMFlag *f = JVMFlag::find("UseAdaptiveGCBoundary", {JVMFlag::Type::Bool});
    _is_adaptive_gc_boundary_flag_set = f != NULL && f->get();
  }

  // Make sure we reload method IDs upon class retransformation
  JVMTIFunctions *functions = *(JVMTIFunctions **)_jvmti;
  _orig_RedefineClasses = functions->RedefineClasses;
  _orig_RetransformClasses = functions->RetransformClasses;
  functions->RedefineClasses = RedefineClassesHook;
  functions->RetransformClasses = RetransformClassesHook;

  if (attach) {
    loadAllMethodIDs(_jvmti, jni());
    _jvmti->GenerateEvents(JVMTI_EVENT_DYNAMIC_CODE_GENERATED);
    _jvmti->GenerateEvents(JVMTI_EVENT_COMPILED_METHOD_LOAD);
  } else {
    _jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, NULL);
  }

  OS::installSignalHandler(WAKEUP_SIGNAL, NULL, wakeupHandler);

  return true;
}

// Run late initialization when JVM is ready
void VM::ready(jvmtiEnv *jvmti, JNIEnv *jni) {
  Profiler::check_JDK_8313796_workaround();
  Profiler::setupSignalHandlers();
  {
    JitWriteProtection jit(true);
    VMStructs::ready();
  }
  _libjava = getLibraryHandle("libjava.so");
}

void VM::applyPatch(char *func, const char *patch, const char *end_patch) {
  size_t size = end_patch - patch;
  uintptr_t start_page = (uintptr_t)func & ~OS::page_mask;
  uintptr_t end_page =
      ((uintptr_t)func + size + OS::page_mask) & ~OS::page_mask;

  if (mprotect((void *)start_page, end_page - start_page,
               PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
    memcpy(func, patch, size);
    __builtin___clear_cache(func, func + size);
    mprotect((void *)start_page, end_page - start_page, PROT_READ | PROT_EXEC);
  }
}

void *VM::getLibraryHandle(const char *name) {
  if (OS::isLinux()) {
    void *handle = dlopen(name, RTLD_LAZY);
    if (handle != NULL) {
      return handle;
    }
    Log::warn("Failed to load %s: %s", name, dlerror());
  }
  // JVM symbols are globally visible on macOS
  return RTLD_DEFAULT;
}

void VM::loadMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass) {
  bool needs_patch = VM::hotspot_version() == 8;
  if (needs_patch) {
    // Workaround for JVM bug https://bugs.openjdk.org/browse/JDK-8062116
    // Preallocate space for jmethodIDs at the beginning of the list (rather than at the end)
    // This is relevant only for JDK 8 - later versions do not have this bug
    if (VMStructs::hasClassLoaderData()) {
      VMKlass *vmklass = VMKlass::fromJavaClass(jni, klass);
      int method_count = vmklass->methodCount();
      if (method_count > 0) {
        ClassLoaderData *cld = vmklass->classLoaderData();
        cld->lock();
        for (int i = 0; i < method_count; i += MethodList::SIZE) {
          *cld->methodList() = new MethodList(*cld->methodList());
        }
        cld->unlock();
      }
    }
  }

  // CRITICAL: GetClassMethods must be called to preallocate jmethodIDs for AsyncGetCallTrace.
  // AGCT operates in signal handlers where lock acquisition is forbidden, so jmethodIDs must
  // exist before profiling encounters them. Without preallocation, AGCT cannot identify methods
  // in stack traces, breaking profiling functionality.
  //
  // JVM-internal allocation: This triggers JVM to allocate jmethodIDs internally, which persist
  // until class unload. High class churn causes significant memory growth, but this is inherent
  // to AGCT architecture and necessary for signal-safe profiling.
  //
  // See: https://mostlynerdless.de/blog/2023/07/17/jmethodids-in-profiling-a-tale-of-nightmares/
  jint method_count;
  jmethodID *methods;
  if (jvmti->GetClassMethods(klass, &method_count, &methods) == 0) {
    jvmti->Deallocate((unsigned char *)methods);
  }
}

void VM::loadAllMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni) {
    jint class_count;
    jclass *classes;
    if (jvmti->GetLoadedClasses(&class_count, &classes) == 0) {
      for (int i = 0; i < class_count; i++) {
        loadMethodIDs(jvmti, jni, classes[i]);
      }
      jvmti->Deallocate((unsigned char *)classes);
    }
}

void JNICALL VM::VMInit(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread) {
    ready(jvmti, jni);
    loadAllMethodIDs(jvmti, jni);

    // initialize the heap usage tracking only after the VM is ready
    HeapUsage::initJMXUsage(VM::jni());

    // Delayed start of profiler if agent has been loaded at VM bootstrap
    Error error = Profiler::instance()->run(_agent_args);
    if (error) {
        Log::error("%s", error.message());
    }
}

void JNICALL VM::VMDeath(jvmtiEnv *jvmti, JNIEnv *jni) {
  Profiler::instance()->shutdown(_agent_args);
}

jvmtiError
VM::RedefineClassesHook(jvmtiEnv *jvmti, jint class_count,
                        const jvmtiClassDefinition *class_definitions) {
  jvmtiError result =
      _orig_RedefineClasses(jvmti, class_count, class_definitions);

  if (result == 0) {
    // jmethodIDs are invalidated after RedefineClasses
    JNIEnv *env = jni();
    for (int i = 0; i < class_count; i++) {
      if (class_definitions[i].klass != NULL) {
        loadMethodIDs(jvmti, env, class_definitions[i].klass);
      }
    }
  }

  return result;
}

jvmtiError VM::RetransformClassesHook(jvmtiEnv *jvmti, jint class_count,
                                      const jclass *classes) {
  jvmtiError result = _orig_RetransformClasses(jvmti, class_count, classes);

  if (result == 0) {
    // jmethodIDs are invalidated after RetransformClasses
    JNIEnv *env = jni();
    for (int i = 0; i < class_count; i++) {
      if (classes[i] != NULL) {
        loadMethodIDs(jvmti, env, classes[i]);
      }
    }
  }

  return result;
}

extern "C" DLLEXPORT jint JNICALL
Agent_OnLoad(JavaVM* vm, char* options, void* reserved) {
    Error error = _agent_args.parse(options);

    Log::open(_agent_args);

    if (error) {
        Log::error("%s", error.message());
        return ARGUMENTS_ERROR;
    }

    if (!VM::initProfilerBridge(vm, false)) {
        Log::error("JVM does not support Tool Interface");
        return COMMAND_ERROR;
    }

    return 0;
}

extern "C" DLLEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
  if (!VM::initLibrary(vm)) {
    return 0;
  }
  return JNI_VERSION_1_6;
}

extern "C" DLLEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
  Profiler *profiler = Profiler::instance();
  if (profiler != NULL) {
    profiler->stop();
  }
}
