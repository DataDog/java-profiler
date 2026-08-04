/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FLIGHTRECORDER_INLINE_H
#define _FLIGHTRECORDER_INLINE_H


#include "flightRecorder.h"
#include "jvmSupport.inline.h"

jint MethodInfo::getLineNumber(jint bci) {
    // if the shared pointer is not pointing to the line number table, consider
    // size 0
    if (!_line_number_table || _line_number_table->_size == 0) {
      return 0;
    }

    int i = 1;
    while (i < _line_number_table->_size &&
           bci >= ((jvmtiLineNumberEntry *)_line_number_table->_ptr)[i]
                      .start_location) {
      i++;
    }
    return ((jvmtiLineNumberEntry *)_line_number_table->_ptr)[i - 1]
        .line_number;
}

bool MethodInfo::isHidden() {
    return JVMSupport::isHidden(_modifiers);
}

#endif // _FLIGHTRECORDER_INLINE_H
