// Unless explicitly stated otherwise all files in this repository are licensed under the Apache License (Version 2.0).
// This product includes software developed at Datadog (https://www.datadoghq.com/) Copyright 2025 Datadog, Inc.

#ifndef _VMSTRUCTS_INLINE_H
#define _VMSTRUCTS_INLINE_H

#include "vmStructs.h"

VMNMethod* VMMethod::code() {
    assert(_method_code_offset >= 0);
    const void* code_ptr = *(const void**) at(_method_code_offset);
    return VMNMethod::cast(code_ptr);
}

VMMethod* VMThread::compiledMethod() {
    assert(_comp_method_offset >= 0);
    assert(_comp_env_offset >= 0);
    assert(_comp_task_offset >= 0);
    const char* env = *(const char**) at(_comp_env_offset);
    if (env != NULL) {
        const char* task = *(const char**) (env + _comp_task_offset);
        if (task != NULL) {
            return VMMethod::load_then_cast((const void*)(task + _comp_method_offset));
        }
    }
    return NULL;
}


#endif // _VMSTRUCTS_INLINE_H
