/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Definitions of the VM static members that libJavaSupport needs at link time.
// Initialization happens in vmEntry.cpp (libjavaProfiler).
#include "vmEntry.h"

#include <stdlib.h>
#include <string.h>

JavaVM *VM::_vm;
jvmtiEnv *VM::_jvmti = NULL;
int VM::_hotspot_version = 0;
bool VM::_openj9 = false;
bool VM::_hotspot = false;
bool VM::_zing = false;

// Parses the HotSpot version out of the "java.vm.version" property.  Lives in
// the support library so it is usable both by the profiler (via JVMTI) and by
// JVMAccess when libJavaSupport is loaded standalone (via JNI).
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
