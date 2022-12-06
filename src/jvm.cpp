#include "jvm.h"
#include "vmStructs.h"

bool JVM::_is_readable_pointer_resolved = false;
is_readable_pointer_fn JVM::_is_readable_pointer = NULL;

bool JVM::is_readable_pointer(void* ptr) {
    if (!_is_readable_pointer_resolved) {
        const char* sym_name = "_ZN2os19is_readable_pointerEPKv";
        _is_readable_pointer_resolved = true;
        _is_readable_pointer = (is_readable_pointer_fn)VMStructs::libjvm()->findSymbol(sym_name);
        if (_is_readable_pointer == NULL) {
            Log::error("Can not resolve symbol %s in JVM lib\n", sym_name);
        }
    }
    // if we have no access to the symbol we can not really attempt the pointer sanitation
    return _is_readable_pointer ? _is_readable_pointer(ptr) : true;
}