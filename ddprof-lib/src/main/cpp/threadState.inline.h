#include "threadState.h"
#include "hotspot/vmStructs.h"

inline ExecutionMode getThreadExecutionMode() {
    return VM::isHotspot() ? VMThread::getExecutionMode() :
                             ExecutionMode::UNKNOWN;
}
