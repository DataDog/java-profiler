/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Definitions of the VM static members that libJavaSupport needs at link time.
// Initialization happens in vmEntry.cpp (libjavaProfiler).
#include "vmEntry.h"

JavaVM *VM::_vm;
jvmtiEnv *VM::_jvmti = NULL;
int VM::_hotspot_version = 0;
bool VM::_openj9 = false;
bool VM::_hotspot = false;
bool VM::_zing = false;
