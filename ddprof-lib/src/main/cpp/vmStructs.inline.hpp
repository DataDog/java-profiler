#ifndef _VMSTRUCTS_INLINE_H
#define _VMSTRUCTS_INLINE_H

#include "vmStructs.h"

VMNMethod* VMMethod::code() {
    assert(_method_code_offset >= 0);
    const void* code_ptr = *(const void**) at(_method_code_offset);
    return VMNMethod::cast(code_ptr);
}


#endif // _VMSTRUCTS_INLINE_H
