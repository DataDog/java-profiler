/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "methodInfo.h"

#include <jvmti.h>

#include "common.h"
#include "counters.h"
#include "vmEntry.h"

SharedLineNumberTable::~SharedLineNumberTable() {
  // Always attempt to deallocate if we have a valid pointer
  // JVMTI spec requires that memory allocated by GetLineNumberTable
  // must be freed with Deallocate
  if (_ptr != nullptr) {
    jvmtiEnv *jvmti = VM::jvmti();
    if (jvmti != nullptr) {
      jvmtiError err = jvmti->Deallocate((unsigned char *)_ptr);
      // If Deallocate fails, log it for debugging (this could indicate a JVM bug)
      // JVMTI_ERROR_ILLEGAL_ARGUMENT means the memory wasn't allocated by JVMTI
      // which would be a serious bug in GetLineNumberTable
      if (err != JVMTI_ERROR_NONE) {
        TEST_LOG("Unexpected error while deallocating linenumber table: %d", err);
      }
    } else {
      TEST_LOG("WARNING: Cannot deallocate line number table - JVMTI is null");
    }
    // Decrement counter whenever destructor runs (symmetric with increment at creation)
    Counters::decrement(LINE_NUMBER_TABLES);
  }
}
