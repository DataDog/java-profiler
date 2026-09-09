/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <assert.h>
#include <inttypes.h>

#include "buffers.h"
#include "callTraceHashTable.h"
#include "context.h"
#include "context_api.h"
#include "counters.h"
#include "nativeMem.h"
#include "dictionary.h"
#include "flightRecorder.inline.h"
#include "incbin.h"
#include "jfrMetadata.h"
#include "jniHelper.h"
#include "jvmSupport.inline.h"
#include "os.h"
#include "profiler.h"
#include "signalSafety.h"
#include "rustDemangler.h"
#include "safeAccess.h"
#include "spinLock.h"
#include "unwindStats.h"
#include "symbols.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "hotspot/vmStructs.h"
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

// JVM spec SS4.7.3 caps a method's bytecode (code_length) at 65535 bytes (u2),
// so a well-formed LineNumberTable can never have more entries than that.
// Used to sanity-bound line_number_table_size before it drives the byte-count
// passed to SafeAccess::safeCopy(): if GetLineNumberTable()
// returns a corrupted pointer for a stale jmethodID (see the TOCTOU race
// documented in fillJavaMethodInfo below), the paired out-param size is just
// as likely to be corrupted, and an implausible size should be rejected
// before it is trusted to compute a byte range.
static const jint MAX_LINE_NUMBER_TABLE_ENTRIES = 65535;

// Compute a non-negative event duration from TSC timestamps.  Unsigned u64
// subtraction wraps to a near-2^64 value when end < start, which can happen if
// the thread migrates cores between the two TSC reads and the per-core counters
// are not perfectly synchronised.  Clamp such inversions to 0 so the emitted
// duration is never an absurd outlier.
static inline u64 safeDuration(u64 start_time, u64 end_time) {
  return end_time >= start_time ? end_time - start_time : 0;
}

SharedLineNumberTable::~SharedLineNumberTable() {
  // _ptr is the buffer jvmti->GetLineNumberTable() itself returned (see
  // Lookup::fillJavaMethodInfo), not a copy -- freed here via
  // jvmti->Deallocate(), not plain free(). On HotSpot, JvmtiEnv
  // Allocate()/Deallocate() are os::malloc()/os::free(), which route through
  // native memory tracking; freeing with plain free() can result in crash
  // whenever -XX:NativeMemoryTracking is enabled, because native memory tracking
  // adds a header to malloc'd block.
  if (_table != nullptr) {
    VM::jvmti()->Deallocate((unsigned char *)_table);
    Counters::decrement(LINE_NUMBER_TABLES);
    // _size is the JVMTI entry count passed at construction (see
    // fillJavaMethodInfo), so the byte size matches the allocation.
    NativeMem::record(NM_LINE_TABLES, -(long long)((size_t)_size *
                                                   sizeof(jvmtiLineNumberEntry)));
  }
}
class ResolveMethodState {
public:
  volatile bool _framePushed;
  char* volatile _demangled;
  char* volatile _class_name;
  char* volatile _method_name;
  char* volatile _method_signature;
  // GetLineNumberTable()'s result. Tracked here for the same reason as the
  // strings above: it is assigned between sigsetjmp() and a possible
  // siglongjmp() out of a fault raised by a later JVMTI/JNI call in
  // fillJavaMethodInfo() (Thread.run/main's FindClass/GetMethodID/
  // CallBooleanMethod), and until then this local has no other owner.
  // release() frees it via jvmti->Deallocate() on that recovery path, and on
  // the "rejected as unreadable/erroring" path fillJavaMethodInfo() also
  // handles inline -- but never on the success path, where ownership passes
  // to mi->_line_number_table instead (also freed via jvmti->Deallocate(),
  // just later; see SharedLineNumberTable) and this field is nulled out.
  jvmtiLineNumberEntry* volatile _line_number_table;

  // Non-copyable
  ResolveMethodState(const ResolveMethodState&) = delete;
  ResolveMethodState& operator=(const ResolveMethodState&) = delete;

  ResolveMethodState();
  ~ResolveMethodState();
  void release();
};

ResolveMethodState::ResolveMethodState() :
  _framePushed(false), _demangled(nullptr), _class_name(nullptr), _method_name(nullptr),
  _method_signature(nullptr), _line_number_table(nullptr) {
}

ResolveMethodState::~ResolveMethodState() {
  release();
}

// Don't expect following JNI and JVMTI calls to fail, as they are public APIs
// of JVM
void ResolveMethodState::release() {
  if (_framePushed) {
    JNIEnv* jni = VM::jni();
    jni->PopLocalFrame(nullptr);
    _framePushed = false;
  }

  if (_demangled != nullptr) {
    free(_demangled);
    _demangled = nullptr;
  }
  jvmtiEnv* jvmti = VM::jvmti();
  if (_method_name != nullptr) {
    jvmti->Deallocate((unsigned char*)_method_name);
    _method_name = nullptr;
  }
  if (_method_signature != nullptr) {
    jvmti->Deallocate((unsigned char*)_method_signature);
    _method_signature = nullptr;
  }
  if (_class_name != nullptr) {
    jvmti->Deallocate((unsigned char*)_class_name);
    _class_name = nullptr;
  }
  if (_line_number_table != nullptr) {
    jvmti->Deallocate((unsigned char*)_line_number_table);
    _line_number_table = nullptr;
  }
}

void Lookup::fillNativeMethodInfo(MethodInfo *mi, const char *name,
                                  const char *lib_name, ResolveMethodState& state) {
  mi->_class = _classes->lookupDuringDump("", 0, Profiler::maxClassMapSize());
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
    
    state._demangled = abi::__cxa_demangle(name, NULL, NULL, &status);
    if (state._demangled != NULL) {
      cutArguments(state._demangled);
      mi->_sig = _symbols.lookup("()L;");
      mi->_type = FRAME_CPP;

      // Rust legacy demangling
      if (RustDemangler::is_probably_rust_legacy(state._demangled)) {
        std::string rust_demangled = RustDemangler::demangle(state._demangled);
        mi->_name = _symbols.lookup(rust_demangled.c_str());
      } else {
        mi->_name = _symbols.lookup(state._demangled);
      }
      free(state._demangled);
      state._demangled = nullptr;
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
  mi->_class = _classes->lookupDuringDump(rfi->build_id, strlen(rfi->build_id),
                                           Profiler::maxClassMapSize());

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

bool Lookup::fillJavaMethodInfo(MethodInfo *mi, jmethodID method,
                                bool first_time, ResolveMethodState& state) {
  JNIEnv *jni = VM::jni();
  if (jni->PushLocalFrame(64) != 0) {
    return false;
  }
  state._framePushed = true;

  jvmtiEnv *jvmti = VM::jvmti();

  jvmtiPhase phase;
  jclass method_class = NULL;
  // invariant: these strings must remain null, or be assigned by JVMTI
  char* volatile &class_name = state._class_name;
  char* volatile &method_name = state._method_name;
  char* volatile &method_sig = state._method_signature;
  u32 class_name_id = 0;
  u32 method_name_id = 0;
  u32 method_sig_id = 0;

  jint line_number_table_size = 0;
  jvmtiLineNumberEntry *line_number_table = NULL;


  jvmti->GetPhase(&phase);
  if ((phase & (JVMTI_PHASE_START | JVMTI_PHASE_LIVE)) != 0) {
    bool entry = false;
    bool readable = false;
    const size_t probe_len = 256;
    if (VMMethod::check_jmethodID(method) &&
        jvmti->GetMethodDeclaringClass(method, &method_class) == JVMTI_ERROR_NONE &&
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
        jvmti->GetClassSignature(method_class, (char**)&class_name, NULL) == JVMTI_ERROR_NONE &&
        jvmti->GetMethodName(method, (char**)&method_name, (char**)&method_sig, NULL) == JVMTI_ERROR_NONE) {
      // The JVMTI strings should be non-null and mapped per spec, but crash
      // telemetry shows both `strncmp` and `jvmti_Deallocate` faulting on them.
      // Probe each pointer over a range covering the longest prefix
      // compared below (~50 bytes) plus headroom for strlen, and NULL any that
      // fails so the unconditional Deallocate block at end of this function
      // skips it (os::free faults on an unmapped pointer just like strncmp).
      // Accept a small leak on the corruption path. Probes run independently
      // so a single bad pointer does not leak its siblings. Best-effort only:
      // a concurrent munmap between probe and use can still fault; the SIGSEGV
      // handler is the second line of defence.
      auto probe = [&](char* volatile & ptr) -> bool {
        if (ptr == nullptr || !SafeAccess::isReadableRange(ptr, probe_len)) {
          ptr = nullptr;
          return false;
        }
        return true;
      };
      readable = probe(class_name) & probe(method_name) & probe(method_sig);
    }
    if (readable) {
      const size_t class_name_len = strnlen(class_name, 65536);
      const char* normalized_class_name =
          class_name_len >= 2 ? class_name + 1 : "";
      const size_t normalized_class_name_len =
          class_name_len >= 2 ? class_name_len - 2 : 0;

      if (first_time) {
        jvmtiError line_table_error = jvmti->GetLineNumberTable(method, &line_number_table_size,
                                  &line_number_table);
        
        bool is_table_valid = (line_number_table_size >= 0 && line_number_table_size <= MAX_LINE_NUMBER_TABLE_ENTRIES);
        bool is_table_readable =  (line_number_table != nullptr && is_table_valid &&
                                   (line_number_table_size > 0 ?
                                    SafeAccess::isReadableRange(line_number_table, line_number_table_size * sizeof(jvmtiLineNumberEntry)) :
                                    SafeAccess::isReadable(line_number_table)));
        if (line_table_error != JVMTI_ERROR_NONE ||
            // On Hotspot, it returns a malloc'd pointer even table size = 0, but there is no point to keep it
            line_number_table_size == 0 ||
            // a corrupted table 
            !is_table_valid ||
            !is_table_readable) {
            if (is_table_readable) {
              jvmti->Deallocate((unsigned char*)line_number_table);
            }

            // Only a genuinely corrupt/unreadable table output should count
            // here: JVMTI_ERROR_ABSENT_INFORMATION (compiled without debug
            // line info) and other non-success errors are ordinary, expected
            // outcomes with no table to speak of, not corruption -- counting
            // them would swamp this signal with normal methods and mask real
            // stale/corrupted-jmethodID failures.
            if (line_table_error == JVMTI_ERROR_NONE && (!is_table_valid || !is_table_readable)) {
              Counters::increment(LINE_NUMBER_TABLE_UNREADABLE);
            }
            line_number_table = nullptr;
            line_number_table_size = 0;
        }
        // Mirror into state immediately, before anything else in this
        // function runs: a later JVMTI/JNI call below (Thread.run/main's
        // FindClass/GetMethodID/CallBooleanMethod, or this function's own
        // trailing Deallocate() further down) can fault and siglongjmp out
        // before line_number_table is otherwise handled, and this local
        // variable is not tracked by anything the landing pad can see.
        // state.release() is what frees it on that recovery path.
        state._line_number_table = line_number_table;
      }

      // Check if the frame is Thread.run or inherits from it
      if (strncmp(method_name, "run", 4) == 0 &&
          strncmp(method_sig, "()V", 3) == 0) {
        jclass Thread_class = jni->FindClass("java/lang/Thread");
        jclass Class_class = jni->FindClass("java/lang/Class");
        if (Thread_class != nullptr && Class_class != nullptr) {
          jmethodID isAssignableFrom =
              jni->GetMethodID(Class_class, "isAssignableFrom", "(Ljava/lang/Class;)Z");
          if (isAssignableFrom != nullptr) {
            entry = jni->CallBooleanMethod(Thread_class, isAssignableFrom, method_class);
            if (jniExceptionCheck(jni)) {
              entry = false;
            }
          }
        }
        // Clear any exceptions from the reflection calls above
        jniExceptionCheck(jni);
      } else if (strncmp(method_name, "main", 5) == 0 &&
                 strncmp(method_sig, "([Ljava/lang/String;)V", 22) == 0) {
        // public static void main(String[] args) - 'public static' translates
        // to modifier bits 0 and 3, hence check for '9'
        entry = true;
      }

      // maybe we should store the lookups below in initialisation-time
      // constants...
      if (has_prefix(class_name,
                     "Ljdk/internal/reflect/GeneratedConstructorAccessor")) {
        class_name_id = _classes->lookupDuringDump(
            "jdk/internal/reflect/GeneratedConstructorAccessor",
            strlen("jdk/internal/reflect/GeneratedConstructorAccessor"),
            Profiler::maxClassMapSize());
        method_name_id =
            _symbols.lookup("Object "
                            "jdk.internal.reflect.GeneratedConstructorAccessor."
                            "newInstance(Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name,
                            "Lsun/reflect/GeneratedConstructorAccessor")) {
        class_name_id = _classes->lookupDuringDump(
            "sun/reflect/GeneratedConstructorAccessor",
            strlen("sun/reflect/GeneratedConstructorAccessor"),
            Profiler::maxClassMapSize());
        method_name_id = _symbols.lookup(
            "Object "
            "sun.reflect.GeneratedConstructorAccessor.newInstance(Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name,
                            "Ljdk/internal/reflect/GeneratedMethodAccessor")) {
        class_name_id = _classes->lookupDuringDump(
            "jdk/internal/reflect/GeneratedMethodAccessor",
            strlen("jdk/internal/reflect/GeneratedMethodAccessor"),
            Profiler::maxClassMapSize());
        method_name_id =
            _symbols.lookup("Object "
                            "jdk.internal.reflect.GeneratedMethodAccessor."
                            "invoke(Object, Object[])");
        method_sig_id = _symbols.lookup(method_sig);
      } else if (has_prefix(class_name,
                            "Lsun/reflect/GeneratedMethodAccessor")) {
        class_name_id = _classes->lookupDuringDump(
            "sun/reflect/GeneratedMethodAccessor",
            strlen("sun/reflect/GeneratedMethodAccessor"),
            Profiler::maxClassMapSize());
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
          class_name_id = _classes->lookupDuringDump(
              "java/lang/invoke/LambdaForm$MH",
              strlen("java/lang/invoke/LambdaForm$MH"),
              Profiler::maxClassMapSize());
        } else if (has_prefix(class_name + lambdaFormPrefixLength, "BMH")) {
          class_name_id = _classes->lookupDuringDump(
              "java/lang/invoke/LambdaForm$BMH",
              strlen("java/lang/invoke/LambdaForm$BMH"),
              Profiler::maxClassMapSize());
        } else if (has_prefix(class_name + lambdaFormPrefixLength, "DMH")) {
          class_name_id = _classes->lookupDuringDump(
              "java/lang/invoke/LambdaForm$DMH",
              strlen("java/lang/invoke/LambdaForm$DMH"),
              Profiler::maxClassMapSize());
        } else {
          // don't recognise the suffix, so don't normalise
          class_name_id = _classes->lookupDuringDump(
              normalized_class_name, normalized_class_name_len,
              Profiler::maxClassMapSize());
        }
        method_name_id = _symbols.lookup(method_name);
        method_sig_id = _symbols.lookup(method_sig);
      } else {
        class_name_id = _classes->lookupDuringDump(
            normalized_class_name, normalized_class_name_len,
            Profiler::maxClassMapSize());
        method_name_id = _symbols.lookup(method_name);
        method_sig_id = _symbols.lookup(method_sig);
      }
    } else {
      Counters::increment(JMETHODID_SKIPPED);
      class_name_id = _classes->lookupDuringDump("", 0, Profiler::maxClassMapSize());
      method_name_id = _symbols.lookup("<unloaded>");
      method_sig_id = _symbols.lookup("()L;");
    }

    mi->_class = class_name_id;
    mi->_name = method_name_id;
    mi->_sig = method_sig_id;
    mi->_type = FRAME_INTERPRETED;
    mi->_is_entry = entry;
    // Only touch mi->_line_number_table when a table was actually fetched
    // this call (first_time, and GetLineNumberTable succeeded with a
    // readable result -- see above). Every other call leaves
    // line_number_table/line_number_table_size at their initial NULL/0,
    // and mi->_key persists across chunks while only _mark gets cleared, so
    // a re-fill of an already-known method must not clobber the real table
    // fetched on its first chunk with an empty one.
    if (line_number_table != nullptr) {
      mi->_line_number_table = std::make_shared<SharedLineNumberTable>(
                  line_number_table_size, line_number_table);
      // Increment counter for tracking live line number tables
      Counters::increment(LINE_NUMBER_TABLES);
      NativeMem::record(NM_LINE_TABLES, (long long)((size_t)line_number_table_size * sizeof(jvmtiLineNumberEntry)));
      state._line_number_table = nullptr;
    }
    return true;
  }
  // Phase is neither START nor LIVE (e.g. a record-on-shutdown dump after the
  // JVM has moved into JVMTI_PHASE_DEAD): none of mi's fields were touched
  // above, unlike the "readable == false" case inside the branch above (which
  // still fills mi with the deliberate "<unloaded>" sentinel and returns true
  // via the return above).
  return false;
}

bool Lookup::resolveVTableReceiver(VMSymbol *sym, char *buf, size_t bufsize,
                                    u32 *out_class_id) {
  if (sym == nullptr || !SafeAccess::isReadable(sym)) {
    return false;
  }
  // Read the 4-byte word containing the u2 length field. In all HotSpot
  // versions we support the length is at offset 0 of Symbol; we still go
  // through VMStructs in case that ever changes. The low 16 bits hold the
  // length on little-endian targets (all supported platforms).
  int32_t *len_word_addr =
      (int32_t *)((char *)sym + VMSymbol::lengthOffset());
  int32_t w1 = SafeAccess::safeFetch32(len_word_addr, -1);
  int32_t w2 = SafeAccess::safeFetch32(len_word_addr, 0);
  if (w1 == -1 && w2 == 0) {
    return false;
  }
  unsigned len = (unsigned)(w1 & 0xFFFF);
  // Bounds: a usable internal class name needs at least 1 byte (single-char
  // descriptors like "B"/"C" for primitives never appear as vtable receivers
  // because primitives can't be receivers of virtual or interface dispatch).
  // Upper bound is the caller-provided buffer; class names above this length
  // are dropped — operators see VTABLE_RECEIVER_RESOLVE_FAILED rise.
  if (len == 0 || len > bufsize) {
    return false;
  }
  const void *body = (const char *)sym + VMSymbol::bodyOffset();
  if (!SafeAccess::safeCopy(buf, body, len)) {
    return false;
  }
  // Reject anything that doesn't look like a JVM internal class name.
  // Valid bytes for slash-separated internal names: '/', '$', '[', ';', '_',
  // alnum. Rejecting reduces — but does not eliminate — the case where the
  // Symbol slot was reused for unrelated data that happens to be printable.
  for (unsigned i = 0; i < len; i++) {
    unsigned char c = (unsigned char)buf[i];
    if (c < 0x20 || c >= 0x7F) {
      return false;
    }
  }
  // lookupDuringDump (not lookup) because this runs inside writeCpool, after
  // rotate(): standby holds the pre-rotate snapshot that writeClasses() will
  // serialize.  Plain lookup() would insert into the new active only, leaving
  // the stack frame's class_id absent from this chunk's class pool.
  // (Plain lookup() remains correct for non-dump callers — e.g. Profiler::
  // lookupClass on JVM threads — where the next rotate() will propagate.)
  u32 class_id = _classes->lookupDuringDump(buf, len, Profiler::maxClassMapSize());
  // Apply synthetic-accessor/LambdaForm normalisation so that the many
  // distinct names HotSpot generates for these families (..Accessor1234,
  // LambdaForm$MH/0x...) collapse to one bucket each in the JFR class pool.
  // Folding the normalisation inside resolveVTableReceiver keeps the call
  // site in resolveMethod minimal and ensures the cache stores normalised
  // class ids (so MethodMap deduplication works for these families too).
  if (has_prefix_n(buf, len,
                   "jdk/internal/reflect/GeneratedConstructorAccessor")) {
    static const char kName[] = "jdk/internal/reflect/GeneratedConstructorAccessor";
    class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
  } else if (has_prefix_n(buf, len, "sun/reflect/GeneratedConstructorAccessor")) {
    static const char kName[] = "sun/reflect/GeneratedConstructorAccessor";
    class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
  } else if (has_prefix_n(buf, len,
                          "jdk/internal/reflect/GeneratedMethodAccessor")) {
    static const char kName[] = "jdk/internal/reflect/GeneratedMethodAccessor";
    class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
  } else if (has_prefix_n(buf, len, "sun/reflect/GeneratedMethodAccessor")) {
    static const char kName[] = "sun/reflect/GeneratedMethodAccessor";
    class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
  } else if (has_prefix_n(buf, len, "java/lang/invoke/LambdaForm$")) {
    size_t prefix_len = strlen("java/lang/invoke/LambdaForm$");
    const char *suffix = buf + prefix_len;
    size_t suffix_len = len - prefix_len;
    if (suffix_len >= 2 && suffix[0] == 'M' && suffix[1] == 'H') {
      static const char kName[] = "java/lang/invoke/LambdaForm$MH";
      class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
    } else if (suffix_len >= 3 && suffix[0] == 'B' && suffix[1] == 'M' &&
               suffix[2] == 'H') {
      static const char kName[] = "java/lang/invoke/LambdaForm$BMH";
      class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
    } else if (suffix_len >= 3 && suffix[0] == 'D' && suffix[1] == 'M' &&
               suffix[2] == 'H') {
      static const char kName[] = "java/lang/invoke/LambdaForm$DMH";
      class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
    }
  }
  *out_class_id = class_id;
  return true;
}

u32 Lookup::resolveVTableReceiverCached(void *sym) {
  auto cached = _vtable_receiver_cache.find(sym);
  if (cached != _vtable_receiver_cache.end()) {
    return cached->second;
  }
  // Stack buffer sized to fit virtually every real class name. HotSpot
  // Symbol length is u2 (max 65535); names beyond 4096 bytes are rare
  // (deeply nested LambdaForm signatures, large CGLIB proxies) and are
  // recorded as resolve failures via the sentinel below.
  char buf[4096];
  u32 class_id = 0;
  if (!resolveVTableReceiver((VMSymbol *)sym, buf, sizeof(buf), &class_id)) {
    Counters::increment(VTABLE_RECEIVER_RESOLVE_FAILED);
    // Explicit sentinel so JFR renders an obvious "we couldn't read it"
    // marker instead of an empty class name (which is indistinguishable
    // from a parser/encoder error downstream).
    static const char kName[] = "<unresolved_vtable_receiver>";
    class_id = _classes->lookupDuringDump(kName, sizeof(kName) - 1, Profiler::maxClassMapSize());
  }
  _vtable_receiver_cache[sym] = class_id;
  return class_id;
}

static const char *const UNKNOWN_METHOD_NAME = "unknown";

// _mark doubles as "already filled in for this chunk" (writeMethods() clears it
// after serializing), exactly as it does for a MethodMap row.
MethodInfo *Lookup::unknownMethod() {
  if (!_unknown_method._mark) {
    ResolveMethodState state;
    _unknown_method._key = _method_map->unknownMethodId();
    fillNativeMethodInfo(&_unknown_method, UNKNOWN_METHOD_NAME, nullptr, state);
    _unknown_method._mark = true; // last; see the note in fillMethod()
  }
  return &_unknown_method;
}

unsigned long Lookup::methodKey(const ASGCT_CallFrame &frame,
                                jmethodID method_id, jint bci,
                                u32 vtable_class_id) {
  // A null method_id never reaches here -- both callers divert it to
  // unknownMethod(), which is not a map entry and so has no key.
  assert(method_id != nullptr);
  if (bci == BCI_ERROR || bci == BCI_NATIVE_FRAME) {
    return MethodMap::makeKey(frame.native_function_name);
  }
  if (bci == BCI_NATIVE_FRAME_REMOTE) {
    return MethodMap::makeKey(frame.packed_remote_frame);
  }
  if (bci == BCI_VTABLE_RECEIVER) {
    return MethodMap::makeVTableReceiverKey(vtable_class_id);
  }
  [[maybe_unused]] FrameTypeId frame_type = FrameType::decode(bci);
  assert(frame_type == FRAME_INTERPRETED || frame_type == FRAME_JIT_COMPILED ||
         frame_type == FRAME_INLINED || frame_type == FRAME_C1_COMPILED ||
         VM::isOpenJ9()); // OpenJ9 may have bugs that produce invalid frame types
  return MethodMap::makeKey(method_id);
}


MethodInfo *Lookup::resolveMethod(ASGCT_CallFrame &frame) {
  jint bci = frame.bci;
  jmethodID method_id = frame.method_id;

  // HotSpot's VM stack walker uses this sentinel when it could not validate a
  // Method*. It is not a JNI/JVMTI jmethodID and must never reach
  // fillJavaMethodInfo(). Keep the frame structurally intact, but serialize it
  // as the shared unknown method.
  if (VM::isHotspot() && method_id == JMETHODID_NOT_WALKABLE) {
    method_id = nullptr;
  }
  // Fill the shared "unknown" row *before* arming. The recovery branch below
  // runs with protection already disarmed, so it must not allocate -- a second
  // fault there would be unrecoverable -- and filling the row does allocate
  // (symbol/class dictionary inserts). Once filled it stays filled for the rest
  // of the chunk, so this costs one flag test per call after the first.
  MethodInfo* unknown_method = unknownMethod();

  // Nothing to symbolicate and nothing that can fault, so no protection is
  // armed for this case at all.
  if (method_id == nullptr) {
    return unknown_method;
  }

  // Fast path, deliberately unprotected. For anything but a raw-pointer or
  // BCI_VTABLE_RECEIVER frame, methodKey() reads no VM metadata (see its
  // comment) and an already-marked row needs no symbolication -- there is
  // nothing here that can fault, hence nothing to recover from. Worth
  // special-casing because it is the common case once a chunk is warm, and
  // arming the protection below is not free: initCurrentThreadSignalSafe()
  // blocks and unblocks signals and sigsetjmp(..., 1) reads the signal mask,
  // three syscalls on a loop that runs once per frame per trace.
  if (!FrameType::isRawPointer(bci) && bci != BCI_VTABLE_RECEIVER) {
    MethodMap::iterator it = _method_map->find(methodKey(frame, method_id, bci, 0));
    if (it != _method_map->end() && it->second._mark) {
      return &it->second;
    }
  }

  // Slow path: symbolication reads VM metadata that a concurrent class unload
  // may already have freed, so wrap it in a siglongjmp window that
  // Profiler::checkFault() jumps back through on SIGSEGV/SIGBUS.
  //
  // Runs on the dump thread (finishChunk), never in a signal handler, so
  // initCurrentThreadSignalSafe() can only fail on OOM.
  ProfiledThread *prof_thread = ProfiledThread::initCurrentThreadSignalSafe();
  if (prof_thread == nullptr) {
    Counters::increment(METHOD_RESOLUTION_DROPPED_TLS);
    return unknown_method;
  }

  return fillMethod(frame, method_id, bci, prof_thread);
}

MethodInfo *Lookup::fillMethod(ASGCT_CallFrame &frame, jmethodID method_id,
                               jint bci, ProfiledThread* const prof_thread) {

  assert(prof_thread != nullptr);
                                  // Resolve native method
  if (FrameType::isRawPointer(bci)) {
    method_id = JVMSupport::resolve(frame.method);
    if (method_id == nullptr) {
      return unknownMethod();
    }
  }

  assert(method_id != nullptr && "Already filtered by caller");
  // Reinstates the thread's previous landing pad on every exit from this frame,
  // including a std::bad_alloc thrown by one of the map or dictionary inserts
  // underneath. Leaving ours installed past the end of this frame would leave
  // checkFault() jumping into a dead stack frame.
  JmpCtxScope jmp_scope(prof_thread);
  ResolveMethodState state;

  sigjmp_buf crash_protection_ctx;
  // savemask must be 1: the siglongjmp originates inside segvHandler, where
  // the kernel has SIGSEGV blocked, so without restoring the saved mask the
  // signal would stay blocked and the next fault on this thread would be
  // fatal.
  if (sigsetjmp(crash_protection_ctx, 1) != 0) {
    // checkFault() absorbed a fault raised somewhere in fillMethod() and
    // jumped back here, bypassing the SIGNAL_HANDLER_GUARD() destructor in
    // segvHandler()/busHandler(); compensate for it, then disarm before
    // touching anything else.
    SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
    jmp_scope.restore();
    Counters::increment(METHOD_RESOLVE_FAULT_RECOVERED);
    // state.release() may fault. Unfortunately, it faults outside of profiler
    // code where checkFault() can not absorb.
    state.release();
    // A member, already filled above -- no map lookup, no allocation, and no
    // reliance on a local surviving siglongjmp (the value of a non-volatile
    // local assigned after sigsetjmp() is indeterminate here).
    return &_unknown_method;
  }
  jmp_scope.install(&crash_protection_ctx);


  // Inject fault to test siglongjmp protection. Sits inside the window
  // resolveMethod() arms around this function, which is the point: this is
  // never compiled into a production build (it needs -PenableFaultInjection).
  INJECT_CRASH_LIKELY();

  // BCI_VTABLE_RECEIVER: method holds a VMSymbol* (see vmEntry.h). Resolve
  // to a class_id via the per-dump cache once, then key MethodMap by the
  // resolved class_id so two distinct Symbol addresses for the same class
  // name (class unload + reload within a chunk) collapse to one MethodInfo
  // row.
  u32 vtable_class_id = 0;
  if (bci == BCI_VTABLE_RECEIVER) {
    vtable_class_id = resolveVTableReceiverCached((void *)method_id);
  }

  MethodInfo *mi = &(*_method_map)[methodKey(frame, method_id, bci, vtable_class_id)];

  if (!mi->_mark) {
    bool first_time = mi->_key == 0;
    bool filled = true;
    if (bci == BCI_ERROR) {
      fillNativeMethodInfo(mi, (const char *)method_id, nullptr, state);
    } else if (bci == BCI_NATIVE_FRAME) {
      const char *name = (const char *)method_id;
      fillNativeMethodInfo(mi, name,
                           Profiler::instance()->getLibraryName(name), state);
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
        fillNativeMethodInfo(mi, name_buf, nullptr, state);
      } else {
        TEST_LOG("WARNING: Library lookup failed for index %u", lib_index);
        fillNativeMethodInfo(mi, "unknown_library", nullptr, state);
      }
    } else if (bci == BCI_VTABLE_RECEIVER) {
      // Synthetic vtable-receiver frame: method_id holds a VMSymbol*
      // captured in walkVM. The Symbol -> class_id resolution (with
      // synthetic-accessor/LambdaForm normalisation) was already done
      // above via resolveVTableReceiverCached, which also handles
      // resolution failures by mapping them to "<unresolved_vtable_receiver>"
      // and incrementing VTABLE_RECEIVER_RESOLVE_FAILED.
      mi->_class = vtable_class_id;
      mi->_name = _symbols.lookup("<vtable_receiver>");
      mi->_sig = _symbols.lookup("()V");
      mi->_type = FRAME_NATIVE;
      mi->_is_entry = false;
    } else {
      filled = fillJavaMethodInfo(mi, method_id, first_time, state);
    }
    // Mark last, never before the fill above, and only when the fill actually
    // ran to completion. Two distinct ways the fill can not reach here:
    //   1. It can siglongjmp straight out of this whole function (fillMethod)
    //      on stale VM metadata -- ordering alone handles that, since the
    //      unwind skips this statement (and everything below it) entirely.
    //   2. fillJavaMethodInfo() can return normally without touching mi at
    //      all (PushLocalFrame failed, or the JVM isn't in JVMTI_PHASE_START/
    //      JVMTI_PHASE_LIVE) -- control returns here just like the success
    //      case, so ordering alone does NOT catch this one; its `filled`
    //      return value does.
    // Marking (or allocating a key for) an unfilled row would leave it
    // permanently stuck as an empty class/name/sig typed FRAME_INTERPRETED:
    // writeMethods() serializes any marked row, and every later frame with
    // this key would reuse it via the _mark fast path in resolveMethod(),
    // rather than retrying the fill. Left unmarked, the row is retried by the
    // next frame that needs it, and eventually aged out by
    // cleanupUnreferencedMethods() if nothing ever fills it.
    if (filled) {
      if (first_time) {
        // Allocate a method-pool id that is unique among live methods. Must not
        // be derived from the map size: cleanupUnreferencedMethods() erases
        // entries, so size()+1 would reissue an id still owned by a surviving
        // method, producing duplicate ids in the chunk's method constant pool
        // (PROF-15130). The allocator recycles ids freed on erase instead.
        mi->_key = _method_map->allocId();
      }
      mi->_mark = true;
    } else {
      // Unfilled: mi stays unmarked (see above) for a future frame to retry,
      // but *this* frame still needs a valid, already-marked row to reference
      // right now -- the shared unknown-method row, same as every other
      // resolution-failed path in this function (nullptr method_id above,
      // raw-pointer resolve failure, the siglongjmp recovery branch).
      // Returning mi itself here would hand the caller a key of 0 (never
      // allocated) for a row writeMethods() will never emit, a dangling
      // method-pool reference in the chunk.
      return unknownMethod();
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
    : _fd(fd), _method_map(), _has_post_flush(false) {

  memset(_post_flush_live, 0, sizeof(_post_flush_live));
  memset(_post_flush_max, 0, sizeof(_post_flush_max));

  args.save(_args);
  _chunk_start = lseek(_fd, 0, SEEK_END);
  _start_time = OS::micros();
  _start_ticks = TSC::ticks();
  _recording_start_time = _start_time;
  _recording_start_ticks = _start_ticks;
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

off_t Recording::finishChunk(bool end_recording, bool do_cleanup) {
  jvmtiEnv *jvmti = VM::jvmti();
  JNIEnv *env = VM::jni();

  jclass *classes;
  jint count = 0;
  // Pin all currently-loaded classes for the duration of finishChunk().
  // resolveMethod() calls GetLineNumberTable/GetClassSignature/GetMethodName on
  // jmethodIDs of classes that were loaded when the sample was taken but could
  // be unloaded concurrently by the GC before we flush.  Holding a local JNI
  // reference to each class makes it a GC root, closing that race window.
  // Note: this only guards against concurrent unloading that starts AFTER this
  // call.  Classes already unloaded before finishChunk() was entered are not
  // present in the list and receive no protection here.
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
  updateNativeMemStats();
  writeCounters(_buf);
  writeNativeMem(_buf);

  // Keep a simple stats for where we failed to unwind
  // For the sakes of simplicity we are not keeping the count of failed unwinds which would also be
  // just 'eventually consistent' because we do not want to block the unwinding while writing out the stats.
  writeUnwindFailures(_buf);

  for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
    flush(&_buf[i]);
  }

  off_t cpool_offset = lseek(_fd, 0, SEEK_CUR);
  int count_offset_in_cpool = 0;
  int pool_count = writeCpool(_buf, &count_offset_in_cpool);
  flush(_buf);

  off_t cpool_end = lseek(_fd, 0, SEEK_CUR);

  // Patch cpool size field
  _buf->putVar32(0, cpool_end - cpool_offset);
  ssize_t result = pwrite(_fd, _buf->data(), 5, cpool_offset);
  (void)result;

  // Patch the constant pool count placeholder (written as a 1-byte put8 in
  // writeCpool). Done flush-safe via pwrite to the FILE offset, mirroring the
  // size patch above: _buf has been flushed/reset, so _buf->data() is scratch.
  _buf->put8(0, (char)pool_count);
  result = pwrite(_fd, _buf->data(), 1, cpool_offset + count_offset_in_cpool);
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

  // Run method_map cleanup while the class pins from GetLoadedClasses are still
  // held.  Line number tables are now malloc'd copies (fillJavaMethodInfo copies
  // the JVMTI buffer and calls Deallocate() immediately), so ~SharedLineNumberTable()
  // calls free() — safe regardless of class-unload state.  Cleanup runs before
  // DeleteLocalRef to ensure erased jmethodID keys have not yet been recycled by
  // a newly-loaded class.
  if (do_cleanup) {
    cleanupUnreferencedMethods();
  }

  // Serialization (and, on this path, method-map cleanup) is complete: the
  // dictionary has grown and any memory cleanupUnreferencedMethods() just
  // freed is already reflected in NativeMem. Capture that state now for the
  // next chunk to emit, and refresh the JNI-visible counter mirrors so a live
  // process reading getDebugCounters0() after a dump() sees post-serialization
  // values rather than pre-.
  capturePostFlushNativeMem();

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

// Finish the current chunk, move it to the external file `fd` (must be a valid
// open descriptor), then restart the continuous recording file with a fresh
// chunk header. Callers guarantee fd > -1 (see FlightRecorder::dump).
void Recording::switchChunk(int fd) {
  _chunk_start = finishChunk(/*end_recording=*/true, /*do_cleanup=*/true);

  TEST_LOG("MethodMap: %zu methods after cleanup", _method_map.size());

  _start_time = _stop_time;
  _start_ticks = _stop_ticks;
  _bytes_written = 0;

  // move the chunk to the external file and reset the continuous recording file
  OS::copyFile(_fd, fd, 0, _chunk_start);
  OS::truncateFile(_fd);
  _chunk_start = 0;

  // the recording file is restarted, so write out all the info events again
  writeHeader(_buf);
  writeMetadata(_buf);
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

void Recording::cleanupUnreferencedMethods() {
  if (!_args._enable_method_cleanup) {
    return;  // Feature disabled
  }

  const int AGE_THRESHOLD = 3;  // Remove after 3 consecutive chunks without reference
  size_t removed_count = 0;
  size_t removed_with_line_tables = 0;
  [[maybe_unused]] size_t total_before = _method_map.size();

  for (MethodMap::iterator it = _method_map.begin(); it != _method_map.end(); ) {
    MethodInfo& mi = it->second;

    if (!mi._referenced) {
      // Method not referenced in this chunk
      mi._age++;

      if (mi._age >= AGE_THRESHOLD) {
        // Method hasn't been used for N chunks, safe to remove
        // SharedLineNumberTable will be automatically deallocated via shared_ptr destructor
        bool has_line_table = (mi._line_number_table != nullptr && mi._line_number_table->_table != nullptr);
        if (has_line_table) {
          removed_with_line_tables++;
        }
        // Recycle the erased method's pool id so a later method can reuse it
        // without colliding with any still-live method (PROF-15130).
        _method_map.freeId(mi._key);
        it = _method_map.erase(it);
        removed_count++;
        continue;
      }
    } else {
      // Method was referenced, reset age
      mi._age = 0;
    }

    ++it;
  }

  if (removed_count > 0) {
    TEST_LOG("Cleaned up %zu unreferenced methods (age >= %d chunks, %zu with line tables, total: %zu -> %zu)",
            removed_count, AGE_THRESHOLD, removed_with_line_tables, total_before, _method_map.size());

    // Log current count of live line number tables
    [[maybe_unused]] long long live_tables = Counters::getCounter(LINE_NUMBER_TABLES);
    TEST_LOG("Live line number tables after cleanup: %lld", live_tables);
  }
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
  for (size_t i = 0; i < strings.size(); i++) {
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

size_t Recording::countSerializableChildren(
    const std::vector<const Element *> &children, int depth) {
  // Children one level deeper than `depth` are what writeElement() would
  // truncate on its own depth check, so exclude them here too, before being
  // counted, so child_count always matches the number of children actually
  // serialized below (an inflated count would make the metadata stream
  // itself malformed).
  bool truncate_children = depth + 1 > 10;

  size_t child_count = 0;
  for (size_t i = 0; i < children.size(); i++) {
    if (children[i] == nullptr) {
      Counters::increment(METADATA_TREE_NULL_CHILD);
      fprintf(stderr, "[ddprof] [WARN] writeElement skipping null child at index %zu\n", i);
    } else if (truncate_children) {
      Counters::increment(METADATA_TREE_DEPTH_EXCEEDED);
      fprintf(stderr, "[ddprof] [WARN] writeElement truncating child at index %zu, depth limit exceeded\n", i);
    } else {
      child_count++;
    }
  }
  return child_count;
}

void Recording::writeElement(Buffer *buf, const Element *e, int depth) {
  if (e == nullptr) {
    return;
  }

  buf->putVar64(e->_name);

  buf->putVar64(e->_attributes.size());
  for (size_t i = 0; i < e->_attributes.size(); i++) {
    flushIfNeeded(buf);
    buf->putVar64(e->_attributes[i]._key);
    buf->putVar64(e->_attributes[i]._value);
  }

  bool truncate_children = depth + 1 > 10;
  size_t child_count = countSerializableChildren(e->_children, depth);

  buf->putVar64(child_count);
  if (!truncate_children) {
    for (size_t i = 0; i < e->_children.size(); i++) {
      if (e->_children[i] == nullptr) {
        continue;
      }
      flushIfNeeded(buf);
      writeElement(buf, e->_children[i], depth + 1);
    }
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
  writeBoolSetting(buf, T_ACTIVE_RECORDING, "sanityCheckFailed",
                   Profiler::instance()->sanityCheckFailed());
  if (Profiler::instance()->sanityCheckFailed()) {
    writeStringSetting(buf, T_ACTIVE_RECORDING, "sanityCheckDetail",
                       Profiler::instance()->sanityCheckMessage());
  }
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
  writeBoolSetting(buf, T_MALLOC, "enabled", args._nativemem >= 0);
  if (args._nativemem >= 0) {
    writeIntSetting(buf, T_MALLOC, "nativemem", args._nativemem);
    // samplingInterval=-1 signals "record every allocation"; mirrors shouldSample's interval<=1 threshold.
    writeIntSetting(buf, T_MALLOC, "samplingInterval", args._nativemem <= 1 ? -1 : args._nativemem);
  }

  writeBoolSetting(buf, T_ACTIVE_RECORDING, "debugSymbols",
                   VM::libjvm()->hasDebugSymbols());
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

  Libraries *libraries = Libraries::instance();
  const CodeCacheArray &native_libs = libraries->native_libs();
  int native_lib_count = native_libs.count();

  // Emit jdk.NativeLibrary events for newly loaded libraries.
  // CodeCacheArray::add() stores the pointer before advancing count(),
  // so all indices < native_lib_count are guaranteed non-NULL.
  for (int i = _recorded_lib_count; i < native_lib_count; i++) {
    CodeCache* lib = native_libs[i];

    flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - MAX_STRING_LENGTH);
    int start = buf->skip(5);
    buf->putVar64(T_NATIVE_LIBRARY);
    buf->putVar64(_start_ticks);
    buf->putUtf8(lib->name());
    buf->putVar64((uintptr_t)lib->minAddress());
    buf->putVar64((uintptr_t)lib->maxAddress());
    buf->putUtf8(lib->hasBuildId() ? lib->buildId() : "");
    buf->putVar64((uintptr_t)lib->loadBias());
    buf->putVar32(start, buf->offset() - start);
    flushIfNeeded(buf);
  }

  _recorded_lib_count = native_lib_count;
}

int Recording::writeCpool(Buffer *buf, int *count_offset_in_cpool) {
  // Offset of the cpool start within the buffer. The header below is tiny and
  // flush-free, so the placeholder offset captured relative to this start is a
  // stable cpool-relative offset usable for a flush-safe back-patch by the
  // caller (mirrors the cpool SIZE patch).
  int cpool_start = buf->offset();
  buf->skip(5); // size will be patched later
  buf->putVar64(T_CPOOL);
  buf->putVar64(_start_ticks);
  buf->put8(0);
  buf->put8(0);
  buf->put8(1);
  // Constant pool count. We cannot precompute it: the Method/Class/Package/Symbol
  // pools are only fully populated as a side effect of writeStackTraces/writeMethods
  // (fillJavaMethodInfo), and empty variable pools are skipped entirely. Write a
  // 1-byte placeholder here and back-patch it flush-safe in the caller.
  *count_offset_in_cpool = buf->offset() - cpool_start;
  buf->put8(0);

  // Profiler::rotateDictsAndRun() rotates the three dictionaries before this
  // path runs, so classMap()->standby() returns an old-active snapshot stable
  // for the lifetime of writeCpool().
  // writeClasses() collects the COMPLETE class set from standby(): regular Java
  // classes are inserted into the new-active by fillJavaMethodInfo during
  // writeStackTraces/writeMethods, and those would not appear in the snapshot —
  // standby() captures the pre-rotation state which writeClasses extends.
  Lookup lookup(this, &_method_map, Profiler::instance()->classMap());
  // CONSTANT pools: always non-empty, always emitted -> 5 sections.
  // writeThreads always emits: it inserts _tid unconditionally before checking.
  writeFrameTypes(buf);
  writeThreadStates(buf);
  writeExecutionModes(buf);
  writeLogLevels(buf);
  writeThreads(buf);
  int pool_count = 5;
  // VARIABLE pools: each returns 1 if emitted, 0 if empty (and thus skipped).
  pool_count += writeStackTraces(buf, &lookup);
  pool_count += writeMethods(buf, &lookup);
  pool_count += writeClasses(buf, &lookup);
  pool_count += writePackages(buf, &lookup);
  pool_count += writeConstantPoolSection(buf, T_SYMBOL, &lookup._symbols);
  pool_count += writeConstantPoolSection(
      buf, T_STRING, Profiler::instance()->stringLabelMap()->standby());
  pool_count += writeConstantPoolSection(
      buf, T_ATTRIBUTE_VALUE, Profiler::instance()->contextValueMap()->standby());
  flushIfNeeded(buf);
  return pool_count;
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
  threads.insert(_tid);  // always present: the recording thread itself

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

int Recording::writeStackTraces(Buffer *buf, Lookup *lookup) {
  // Reset all referenced flags before processing
  for (MethodMap::iterator it = _method_map.begin(); it != _method_map.end(); ++it) {
    it->second._referenced = false;
  }

  // Tracks how many traces were written so the empty pool can be skipped.
  // Note: even with zero traces, the methods marking pass below must still run
  // via processCallTraces, but no T_STACK_TRACE section is emitted in that case.
  int trace_count = 0;
  // Use safe trace processing with guaranteed lifetime during callback execution
  Profiler::instance()->processCallTraces([this, buf, lookup, &trace_count](const CallTraceSet& traces) {
    if (traces.empty()) {
      return;
    }
    trace_count = (int)traces.size();
    buf->putVar64(T_STACK_TRACE);
    buf->putVar64(traces.size());
    for (auto it = traces.begin(); it != traces.end(); ++it) {
      CallTrace *trace = *it;
      buf->putVar64(trace->trace_id);
      if (trace->num_frames > 0) {
        MethodInfo *mi =
            lookup->resolveMethod(trace->frames[trace->num_frames - 1]);
        mi->_referenced = true;  // Mark method as referenced
        if (mi->_type < FRAME_NATIVE) {
          buf->put8(mi->_is_entry ? 0 : 1);
        } else {
          buf->put8(trace->truncated);
        }
      }
      buf->putVar64(trace->num_frames);
      for (int i = 0; i < trace->num_frames; i++) {
        MethodInfo *mi = lookup->resolveMethod(trace->frames[i]);
        mi->_referenced = true;  // Mark method as referenced
        buf->putVar64(mi->_key);
        jint bci = trace->frames[i].bci;
        if (mi->_type < FRAME_NATIVE) {
          FrameTypeId type = FrameType::decode(bci);
          bci = FrameType::bci(bci);
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
  return trace_count > 0 ? 1 : 0;
}

// Serializes one method-pool entry and clears its mark, so the next chunk
// re-resolves it (symbol/class ids are per-chunk).
static void writeMethodEntry(Buffer *buf, MethodInfo &mi) {
  mi._mark = false;
  buf->putVar64(mi._key);
  buf->putVar64(mi._class);
  buf->putVar64(mi._name);
  buf->putVar64(mi._sig);
  buf->putVar64(mi._modifiers);
  buf->putVar64(mi.isHidden());
}

int Recording::writeMethods(Buffer *buf, Lookup *lookup) {
  MethodMap *method_map = lookup->_method_map;

  u32 marked_count = 0;
  for (MethodMap::const_iterator it = method_map->begin();
       it != method_map->end(); ++it) {
    if (it->second._mark) {
      marked_count++;
    }
  }
  // Lookup::_unknown_method is deliberately not a map entry (see its
  // declaration), so the walk above cannot see it. It still has to be emitted:
  // writeStackTraces() wrote its _key for every frame that resolved to it, and a
  // _key absent from this pool is a dangling reference in the chunk.
  if (lookup->_unknown_method._mark) {
    marked_count++;
  }

  if (marked_count == 0) {
    return 0;
  }

  buf->putVar64(T_METHOD);
  buf->putVar64(marked_count);
  for (MethodMap::iterator it = method_map->begin(); it != method_map->end();
       ++it) {
    MethodInfo &mi = it->second;
    if (mi._mark) {
      writeMethodEntry(buf, mi);
      flushIfNeeded(buf);
    }
  }
  if (lookup->_unknown_method._mark) {
    writeMethodEntry(buf, lookup->_unknown_method);
    flushIfNeeded(buf);
  }
  return 1;
}

int Recording::writeClasses(Buffer *buf, Lookup *lookup) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  std::map<u32, const char *> classes;
  // standby() returns the dump buffer — the stable snapshot captured by
  // rotate() for this recording cycle.  No other thread writes to this
  // buffer after rotate() completes: rotate() drained all in-flight
  // cross-thread writers via waitForRefCountToClear() before returning.
  lookup->_classes->standby()->collect(classes);

  if (classes.empty()) {
    return 0;
  }

  buf->putVar64(T_CLASS);
  buf->putVar64(classes.size());
  for (std::map<u32, const char *>::const_iterator it = classes.begin();
       it != classes.end(); ++it) {
    const char *name = it->second;
    buf->putVar64(it->first);
    buf->putVar64(0); // classLoader
    buf->putVar64(lookup->getSymbol(name));
    buf->putVar64(lookup->getPackage(name));
    buf->putVar64(0); // access flags
    flushIfNeeded(buf);
  }
  return 1;
}

int Recording::writePackages(Buffer *buf, Lookup *lookup) {
  std::map<u32, const char *> packages;
  lookup->_packages.collect(packages);

  if (packages.empty()) {
    return 0;
  }

  buf->putVar32(T_PACKAGE);
  buf->putVar32(packages.size());
  for (std::map<u32, const char *>::const_iterator it = packages.begin();
       it != packages.end(); ++it) {
    buf->putVar64(it->first);
    buf->putVar64(lookup->getSymbol(it->second));
    flushIfNeeded(buf);
  }
  return 1;
}

int Recording::writeConstantPoolSection(
    Buffer *buf, JfrType type, std::map<u32, const char *> &constants) {
  if (constants.empty()) {
    return 0;
  }
  flushIfNeeded(buf);
  buf->putVar64(type);
  buf->putVar64(constants.size());
  for (std::map<u32, const char *>::const_iterator it = constants.begin();
       it != constants.end(); ++it) {
    int length = strlen(it->second);
    // 5 is max varint length
    flushIfNeeded(buf, RECORDING_BUFFER_LIMIT - length - 5);
    buf->putVar64(it->first);
    buf->putUtf8(it->second, length);
  }
  return 1;
}

int Recording::writeConstantPoolSection(Buffer *buf, JfrType type,
                                        Dictionary *dictionary) {
  std::map<u32, const char *> constants;
  dictionary->collect(constants);
  return writeConstantPoolSection(buf, type, constants);
}

int Recording::writeConstantPoolSection(Buffer *buf, JfrType type,
                                        StringDictionaryBuffer *buffer) {
  std::map<u32, const char *> constants;
  buffer->collect(constants);
  return writeConstantPoolSection(buf, type, constants);
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

void Recording::capturePostFlushNativeMem() {
  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    NativeMemCategory cat = (NativeMemCategory)c;
    _post_flush_live[c] = NativeMem::live(cat);
    _post_flush_max[c] = NativeMem::max(cat);
  }
  _has_post_flush = true;
  // Deliberately NOT NativeMem::sample(): that advances a 64-tick moving
  // average window, so calling it a second time per chunk would silently
  // redefine avg() as a 32-chunk mean. NATIVE_MEM_AVG_BYTES is refreshed here
  // too (to the unchanged avgTotal() from the last sample() tick, not
  // recomputed) purely so the three JNI-visible mirrors stay a coherent
  // triple -- callers must still be aware avg reflects the last sampled tick,
  // not this instant, since it cannot be advanced without a second
  // window-mutating sample().
  Counters::set(NATIVE_MEM_LIVE_BYTES, NativeMem::liveTotal());
  Counters::set(NATIVE_MEM_AVG_BYTES, NativeMem::avgTotal());
  Counters::set(NATIVE_MEM_MAX_BYTES, NativeMem::maxTotal());
}

void Recording::updateNativeMemStats() {
  // Refresh the moving-window averages and the observed total peak. Per-category
  // peaks are maintained precisely at allocation time, so they are not sampled
  // here; the total peak is bracketed instead (see writeNativeMem).
  NativeMem::sample();

  // Mirror the totals into the flat counter table so they flow out through the
  // existing counter path (JFR T_DATADOG_COUNTER events and the JNI debug
  // counters). NATIVE_MEM_MAX_BYTES carries the upper bound on the total peak
  // (sum of precise per-category peaks); the observed sampled total and the
  // per-category values are emitted by writeNativeMem().
  Counters::set(NATIVE_MEM_LIVE_BYTES, NativeMem::liveTotal());
  Counters::set(NATIVE_MEM_AVG_BYTES, NativeMem::avgTotal());
  Counters::set(NATIVE_MEM_MAX_BYTES, NativeMem::maxTotal());
}

void Recording::writeNativeMem(Buffer *buf) {
  // Emit native-memory stats as counter events, reusing the counter event format
  // so they land alongside the totals without needing a dedicated event type or
  // a slot in the counter table.
  auto emit = [&](const char *label, long long value) {
    // Clamp to 0 before encoding: the value is serialized as an unsigned varint
    // (putVar64), so a negative live gauge would emit a huge value and corrupt
    // the counter stream. avg/max are already non-negative; live is clamped
    // here to match sample()/liveTotal().
    if (value < 0) {
      value = 0;
    }
    int start = buf->skip(1);
    buf->putVar64(T_DATADOG_COUNTER);
    buf->putVar64(_start_ticks);
    buf->putUtf8(label);
    buf->putVar64(value);
    writeEventSizePrefix(buf, start);
    flushIfNeeded(buf);
  };

  // Per-category live/avg/max, named "<metric>.<category>". The max here is the
  // precise per-category peak tracked at allocation time.
  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    NativeMemCategory cat = (NativeMemCategory)c;
    const char *name = NativeMem::categoryName(cat);
    const struct {
      const char *prefix;
      long long value;
    } metrics[] = {
        {"native_mem_live_bytes.", NativeMem::live(cat)},
        {"native_mem_avg_bytes.", NativeMem::avg(cat)},
        {"native_mem_max_bytes.", NativeMem::max(cat)},
    };
    for (const auto &m : metrics) {
      char label[64];
      snprintf(label, sizeof(label), "%s%s", m.prefix, name);
      emit(label, m.value);
    }
  }

  // State immediately after the PREVIOUS chunk's writeCpool(), which is the
  // only way to see what serialization itself costs -- the in-chunk values
  // above are necessarily sampled before it runs. Absent on the first chunk,
  // since no flush has happened yet.
  if (_has_post_flush) {
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
      const char *name = NativeMem::categoryName((NativeMemCategory)c);
      char label[64];
      snprintf(label, sizeof(label), "native_mem_post_flush_live_bytes.%s", name);
      emit(label, _post_flush_live[c]);
      snprintf(label, sizeof(label), "native_mem_post_flush_max_bytes.%s", name);
      emit(label, _post_flush_max[c]);
    }
  }

  // NATIVE_MEM_MAX_BYTES already carries the upper bound on the total peak (sum
  // of precise per-category peaks); here we also emit the largest observed
  // sampled total (a non-atomic per-category sum; approximate).
  emit("native_mem_max_observed_total_bytes", NativeMem::maxTotalObserved());
}

void Recording::writeCounters(Buffer *buf) {
  long long *counters = Counters::getCounters();
  if (counters) {
    std::vector<const char *> names = Counters::describeCounters();
    for (size_t i = 0; i < names.size(); i++) {
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
#ifdef DEBUG
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
#endif // DEBUG
}

void Recording::writeContextSnapshot(Buffer *buf, Context &context) {
  buf->putVar64(context.spanId);
  buf->putVar64(context.rootSpanId);

  for (size_t i = 0; i < Profiler::instance()->numContextAttributes(); i++) {
    buf->putVar32(context.get_tag(i).value);
  }
}

void Recording::writeCurrentContext(Buffer *buf) {
  u64 spanId = 0;
  u64 rootSpanId = 0;
  bool hasContext = ContextApi::get(spanId, rootSpanId);
  // spanId/rootSpanId are initialized to 0 above; ContextApi::get() only updates them
  // on success, so 0s are always written when there is no valid context.
  buf->putVar64(spanId);
  buf->putVar64(rootSpanId);

  size_t numAttrs = Profiler::instance()->numContextAttributes();
  ProfiledThread* thrd = hasContext ? ProfiledThread::current() : nullptr;
  for (size_t i = 0; i < numAttrs; i++) {
    buf->putVar32(thrd != nullptr ? thrd->getOtelTagEncoding(i) : 0);
  }
}

void Recording::writeEventSizePrefix(Buffer *buf, int start) {
  int size = buf->offset() - start;
  assert(size < MAX_JFR_EVENT_SIZE);
  buf->put8(start, size);
}

void Recording::recordExecutionSample(Buffer *buf, int tid, u64 call_trace_id,
                                      u64 correlation_id,
                                      ExecutionEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_EXECUTION_SAMPLE);
  buf->putVar64(TSC::ticks());
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->put8(static_cast<int>(event->_thread_state));
  buf->put8(static_cast<int>(event->_execution_mode));
  buf->putVar64(event->_weight);
  buf->putVar64(correlation_id);
  writeCurrentContext(buf);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordMethodSample(Buffer *buf, int tid, u64 call_trace_id,
                                   u64 correlation_id,
                                   ExecutionEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_METHOD_SAMPLE);
  buf->putVar64(TSC::ticks());
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->put8(static_cast<int>(event->_thread_state));
  buf->put8(static_cast<int>(event->_execution_mode));
  buf->putVar64(event->_weight);
  buf->putVar64(correlation_id);
  writeCurrentContext(buf);
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
  buf->putVar64(event->_num_suppressed_sampled_run);
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
  writeCurrentContext(buf);
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
  writeCurrentContext(buf);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordMallocSample(Buffer *buf, int tid, u64 call_trace_id,
                                   MallocEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_MALLOC);
  buf->putVar64(event->_start_time);
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->putVar64(event->_address);
  buf->putVar64(event->_size);
  buf->putFloat(event->_weight);
  writeCurrentContext(buf);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordNativeSocketSample(Buffer *buf, int tid, u64 call_trace_id,
                                         NativeSocketEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_NATIVE_SOCKET);
  buf->putVar64(event->_start_time);
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->putVar64(safeDuration(event->_start_time, event->_end_time));
  static const char* const kOpNames[] = {"SEND", "RECV", "WRITE", "READ"};
  buf->putUtf8(event->_operation < 4 ? kOpNames[event->_operation] : "UNKNOWN");
  buf->putUtf8(event->_remote_addr);
  buf->putVar64(event->_bytes);
  buf->putFloat(event->_weight);
  writeCurrentContext(buf);
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
  writeContextSnapshot(buf, event->_ctx);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordMonitorBlocked(Buffer *buf, int tid, u64 call_trace_id,
                                     LockEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_MONITOR_ENTER);
  buf->putVar64(event->_start_time);
  buf->putVar64(safeDuration(event->_start_time, event->_end_time));
  buf->putVar64(tid);
  buf->putVar64(call_trace_id);
  buf->putVar64(event->_id);
  buf->put8(0);
  buf->putVar64(event->_address);
  writeCurrentContext(buf);
  writeEventSizePrefix(buf, start);
  flushIfNeeded(buf);
}

void Recording::recordThreadPark(Buffer *buf, int tid, u64 call_trace_id,
                                 LockEvent *event) {
  int start = buf->skip(1);
  buf->putVar64(T_THREAD_PARK);
  buf->putVar64(event->_start_time);
  buf->putVar64(safeDuration(event->_start_time, event->_end_time));
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
    _thread_ids[lock_index][active].insert(tid);  // ThreadIdTable::insert is signal-safe (atomics only)
}

Error FlightRecorder::start(Arguments &args, bool reset) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  ExclusiveLockGuard locker(&_rec_lock);
  const char *file = args.file();
  if (file == NULL || file[0] == 0) {
    _filename = "";
    return Error("Flight Recorder output file is not specified");
  }
  _filename = file;
  _args = args;

  TSC::enable(args._clock);

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
  // The Recording embeds the JFR RecordingBuffer array and the cpu-monitor
  // buffer, so its allocation size is the profiler's JFR buffer footprint.
  NativeMem::record(NM_JFR_BUFFERS, (long long)sizeof(Recording));
  return Error::OK;
}

void FlightRecorder::stop() {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  ExclusiveLockGuard locker(&_rec_lock);
  Recording* rec = _rec;
  if (rec != nullptr) {
    // NULL first, deallocate later
    _rec = nullptr;
    // Decrement AFTER delete: ~Recording() runs finishChunk(), which emits the
    // native-memory counters for the final chunk. The Recording buffers are
    // still live during that serialization, so account the free only once it
    // has actually happened.
    delete rec;
    NativeMem::record(NM_JFR_BUFFERS, -(long long)sizeof(Recording));
  }
}

Error FlightRecorder::dump(const char *filename, const int length) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  assert(length >= 0);
  ExclusiveLockGuard locker(&_rec_lock);
  Recording* rec = _rec;
  if (rec != nullptr) {
    if (_filename.length() != static_cast<size_t>(length) ||
        strncmp(filename, _filename.c_str(), length) != 0) {
      // if the filename to dump the recording to is specified move the current
      // working file there
      int copy_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
      if (copy_fd == -1) {
        return Error("Could not open recording file for dump");
      }
      rec->switchChunk(copy_fd);
      close(copy_fd);
      return Error::OK;
    }
    return Error(
      "Can not dump recording to itself. Provide a different file name!");
  }
  return Error("No active recording");
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
  DEBUG_ASSERT_NOT_IN_SIGNAL();
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
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      Buffer *buf = rec->buffer(lock_index);
      rec->writeHeapUsage(buf, value, live);
    }
  }
}

bool FlightRecorder::recordEvent(int lock_index, int tid, u64 call_trace_id,
                                 int event_type, Event *event) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      RecordingBuffer *buf = rec->buffer(lock_index);
      switch (event_type) {
      case BCI_CPU:
          rec->recordExecutionSample(buf, tid, call_trace_id, 0,
                                     (ExecutionEvent *)event);
          break;
        case BCI_WALL:
          rec->recordMethodSample(buf, tid, call_trace_id, 0,
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
        case BCI_NATIVE_MALLOC:
          rec->recordMallocSample(buf, tid, call_trace_id, (MallocEvent *)event);
          break;
        case BCI_NATIVE_SOCKET:
          rec->recordNativeSocketSample(buf, tid, call_trace_id, (NativeSocketEvent *)event);
          break;
        default:
          return false;
        }
        rec->flushIfNeeded(buf);
        rec->addThread(lock_index, tid);
        return true;
      }
  } else {
    Counters::increment(SAMPLES_DROPPED_REC_LOCK);
  }
  return false;
}

bool FlightRecorder::recordEventDelegated(int lock_index, int tid,
                                          u64 correlation_id, int event_type,
                                          Event *event) {
  OptionalSharedLockGuard locker(&_rec_lock);
  if (locker.ownsLock()) {
    Recording* rec = _rec;
    if (rec != nullptr) {
      RecordingBuffer *buf = rec->buffer(lock_index);
      switch (event_type) {
        case BCI_CPU:
          rec->recordExecutionSample(buf, tid, 0, correlation_id,
                                     (ExecutionEvent *)event);
          break;
        case BCI_WALL:
          rec->recordMethodSample(buf, tid, 0, correlation_id,
                                  (ExecutionEvent *)event);
          break;
        default:
          // Delegation is only wired for CPU/wall samples in v1.
          return false;
      }
      rec->flushIfNeeded(buf);
      rec->addThread(lock_index, tid);
      return true;
    }
  } else {
    Counters::increment(SAMPLES_DROPPED_REC_LOCK);
  }
  return false;
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
